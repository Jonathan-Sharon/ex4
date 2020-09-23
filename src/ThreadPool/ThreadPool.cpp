#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#include "ThreadPool.h"

#include "../Factory/WaitForReadCreator.h"
#include "../Factory/ReadCreator.h"

#include <algorithm>
#include <functional>

ThreadPool::Queue::Queue(const int sockfd, const sockaddr_in connectAddress,
                         const unsigned int numberOfThreads) : m_sockfd{sockfd},
                                                               m_connectAddress{connectAddress},
                                                               m_numberOfThreads{numberOfThreads},
                                                               m_isSerial{numberOfThreads == 1},
                                                               m_isThereSomethingToRead{false},
                                                               m_numberOfAvailableThreads{numberOfThreads - 1},
                                                               m_mapCreator{std::make_unique<MapCreator::MapCreator>()}
{
}

void ThreadPool::Queue::allocate()
{
    while (true)
    {

        //Wait until there is operation to do with an available thread
        wait();

        //If the write queue is not empty, there is a write operation to do.
        if (!m_writeQueue.empty())
        {
            //If the server is serial, then call for the write operation
            //in the queue using the main thread.
            if (m_isSerial == true)
            {
                m_writeQueue.front().writer.get()->writeMessage(*this, m_writeQueue.front().parameters);
                --m_numberOfAvailableThreads;
                m_writeQueue.pop();
                continue;
            }

            //The server is parallel. Since it's the only class that can create
            //thread, and according to the wait() function there is a thread available
            //then create a thread to do the Write operation. Also, update the
            //number of available threads.
            std::unique_lock<std::mutex> lock(m_writeQueueMutex);
            std::thread(writeThread, std::ref(*this), m_writeQueue.front());
            --m_numberOfAvailableThreads;
            m_writeQueue.pop();
            continue;
        }

        //If the Operate queue is not empty, there is a OPerate operation to do.
        if (!m_operateQueue.empty())
        {
            //If the server is serial, then call for the operate operation
            //in the queue using the main thread.
            if (m_isSerial == true)
            {
                m_operateQueue.front().operation.get()->operate(*this, m_operateQueue.front().parameters);
                --m_numberOfAvailableThreads;
                m_operateQueue.pop();
                continue;
            }

            //The server is parallel. Since it's the only class that can create
            //thread, and according to the wait() function there is a thread available
            //then create a thread to do the Operate operation. Also, update the
            //number of available threads.
            std::unique_lock<std::mutex> lock(m_operateQueueMutex);
            std::thread(operateThread, std::ref(*this), m_operateQueue.front());
            --m_numberOfAvailableThreads;
            m_operateQueue.pop();
            continue;
        }

        //If the Read queue is not empty, there is a Read operation to do.
        if (!m_readQueue.empty())
        {
            //If the server is serial, then call for the Read operation
            //in the queue using the main thread.
            if (m_isSerial == true)
            {
                m_readQueue.front().reader.get()->readMessage(*this, m_readQueue.front().parameters);
                --m_numberOfAvailableThreads;
                m_readQueue.pop();
                continue;
            }

            //The server is parallel. Since it's the only class that can create
            //thread, and according to the wait() function there is a thread available
            //then create a thread to do the Read operation. Also, update the
            //number of available threads.
            std::unique_lock<std::mutex> lock(m_readQueueMutex);
            std::thread(readThread, std::ref(*this), m_readQueue.front());
            --m_numberOfAvailableThreads;
            m_readQueue.pop();
            continue;
        }
    }
}

void ThreadPool::Queue::wait()
{
    while (true)
    {
        //Check if there is an available thread
        if (m_isSerial == false && m_numberOfAvailableThreads <= 0)
        {
            continue;
        }

        if (m_numberOfAvailableThreads >= m_numberOfThreads)
        {
            throw std::runtime_error("number of available operation is bigger then number of threads");
        }

        //there is a Read operation to do.
        if (!m_readQueue.empty())
        {
            return;
        }

        //there is an Operate operation to do.
        if (!m_operateQueue.empty())
        {
            return;
        }

        //there is a Write operation to do.
        if (!m_writeQueue.empty())
        {
            return;
        }

        checkActiveFd();
    }
}

void ThreadPool::Queue::checkActiveFd()
{
    fd_set readfds;
    //clear the socket set
    FD_ZERO(&readfds);

    //add master socket to set
    FD_SET(m_sockfd, &readfds);
    int maxSd{m_sockfd};

    //get the current time
    std::time_t currentTime = std::time(nullptr);

    {
        std::unique_lock<std::mutex> lock(m_waitForReadVectorMutex);
        for (int i{static_cast<int>(m_waitForReadVector.size() - 1)}; i >= 0; --i)
        {
            //Check if 5 seconds have passed.
            //If so, close the connection
            if (m_waitForReadVector[i].lastReadTime + TIME_TO_CLOSE <= currentTime)
            {
                m_waitForReadVector.erase(m_waitForReadVector.begin() + i);
                close(m_waitForReadVector[i].sockfd);
                continue;
            }

            //add to read list
            FD_SET(m_waitForReadVector[i].sockfd, &readfds);

            //highest file descriptor number, need it for the select function
            if (m_waitForReadVector[i].sockfd > maxSd)
            {
                maxSd = m_waitForReadVector[i].sockfd;
            }
        }
    }

    //wait for an activity on one of the sockets , timeout is 0 ,
    //so select() returns immediately
    timeval timeout = {0, 0};
    int activity = select(maxSd + 1, &readfds, NULL, NULL, &timeout);

    if (activity < 0)
    {
        close(m_sockfd);
        throw std::system_error{errno, std::system_category()};
    }

    //If something happened on the master socket ,
    //then its an incoming connection
    if (FD_ISSET(m_sockfd, &readfds))
    {
        //accept the communication
        int new_socket, addrlen{sizeof(m_connectAddress)};
        if ((new_socket = accept(m_sockfd, (struct sockaddr *)&m_connectAddress,
                                 (socklen_t *)&addrlen)) < 0)
        {
            close(m_sockfd);
            throw std::system_error{errno, std::system_category()};
        }

        //add the new communication to the "Wait For Read" Queue
        ThreadPool::WaitForReadCreator waitFroReadCreator;
        waitFroReadCreator.addToQueue(*this, {std::time(nullptr), VERSION, new_socket, "First Read", ""});
    }

    {
        std::unique_lock<std::mutex> lock(m_waitForReadVectorMutex);

        //Check all other waiting reads to see if they have incoming communication
        for (int i{static_cast<int>(m_waitForReadVector.size() - 1)}; i >= 0; --i)
        {
            if (FD_ISSET(m_waitForReadVector[i].sockfd, &readfds))
            {
                //add the communication to the "Read" queue
                m_mapCreator.get()->atReadMap(m_waitForReadVector[i].readType).get()->addToQueue(*this, {m_waitForReadVector[i].operateToCreate, m_waitForReadVector[i].version, m_waitForReadVector[i].sockfd});
                m_waitForReadVector.erase(m_waitForReadVector.begin() + i);
            }
        }
    }
}

void ThreadPool::readThread(Queue &queue, const read read)
{
    read.reader.get()->readMessage(queue, read.parameters);
}

void ThreadPool::writeThread(Queue &queue, const write write)
{
    write.writer.get()->writeMessage(queue, write.parameters);
}

void ThreadPool::operateThread(Queue &queue, const operate operate)
{
    operate.operation.get()->operate(queue, operate.parameters);
}

void ThreadPool::Queue::addAvailableThread()
{
    ++m_numberOfAvailableThreads;
}