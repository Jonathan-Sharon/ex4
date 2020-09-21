#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#include "ThreadPool.h"

#include <algorithm>

ThreadPool::Queue::Queue(const int sockfd, const sockaddr_in connectAddress,
                         const unsigned int numberOfThreads) : m_sockfd{sockfd},
                                                               m_connectAddress{connectAddress},
                                                               m_numberOfThreads{numberOfThreads},
                                                               m_isSerial{numberOfThreads == 1},
                                                               m_isThereSomethingToRead{false},
                                                               m_numberOfAvailableThreads{numberOfThreads - 1}
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
                m_writeQueue.front().writer.write(m_writeQueue.front().result, m_writeQueue.front().version,
                                                  m_writeQueue.front().sockfd, m_writeQueue.front().errorCode);
                m_writeQueue.pop();
                continue;
            }

            //The server is parallel. Since it's the only class that can create
            //thread, and according to the wait() function there is a thread available
            //then create a thread to do the Write operation. Also, update the
            //number of available threads.
            std::unique_lock<std::mutex> lock(m_writeQueueMutex);
            std::thread(m_writeQueue.front().writer.write,
                        m_writeQueue.front().result, m_writeQueue.front().version,
                        m_writeQueue.front().sockfd, m_writeQueue.front().errorCode);
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
                m_operateQueue.front().operator.operate(m_operateQueue.front().sockfd);
                m_operateQueue.pop();
                continue;
            }

            //The server is parallel. Since it's the only class that can create
            //thread, and according to the wait() function there is a thread available
            //then create a thread to do the Operate operation. Also, update the
            //number of available threads.
            std::unique_lock<std::mutex> lock(m_operateQueueMutex);
            std::thread(m_operateQueue.front().operator.operate, m_operateQueue.front().sockfd);
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
                m_readQueue.front().reader.read(m_readQueue.front().sockfd);
                m_readQueue.pop();
                continue;
            }

            //The server is parallel. Since it's the only class that can create
            //thread, and according to the wait() function there is a thread available
            //then create a thread to do the Read operation. Also, update the
            //number of available threads.
            std::unique_lock<std::mutex> lock(m_readQueueMutex);
            std::thread(m_readQueue.front().reader.read, m_readQueue.front().sockfd);
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

    std::unique_lock<std::mutex> lock(m_waitForReadVectorMutex);
    for (int i{static_cast<int>(m_waitForReadVector.size() - 1)}; i >= 0; --i)
    {
        //Check if 5 seconds have passed.
        //If so, close the connection
        if (m_waitForReadVector[i].lastReadTime + 5 <= currentTime)
        {
            m_waitForReadVector.erase(m_waitForReadVector.begin() + i);
            close(m_waitForReadVector[i].sockfd);
        }

        //add to read list
        FD_SET(m_waitForReadVector[i].sockfd, &readfds);

        //highest file descriptor number, need it for the select function
        if (m_waitForReadVector[i].sockfd > maxSd)
        {
            maxSd = m_waitForReadVector[i].sockfd;
        }
    }

    //wait for an activity on one of the sockets , timeout is 0 ,
    //so select() returns immediately
    timeval timeout = {0, 0};
    int activity = select(maxSd + 1, &readfds, NULL, NULL, &timeout);

    if (activity < 0)
    {
        throw std::system_error{errno, std::system_category()};
    }

    //If something happened on the master socket ,
    //then its an incoming connection
    if (FD_ISSET(m_sockfd, &readfds))
    {
        //factoryOfRead
    }

    //Check all other waiting reads to see if they have incoming communication
    for (int i{static_cast<int>(m_waitForReadVector.size() - 1)}; i >= 0; --i)
    {
        if (FD_ISSET(m_waitForReadVector[i].sockfd, &readfds))
        {
            //factoryOfRead
            m_waitForReadVector.erase(m_waitForReadVector.begin() + i);
        }
    }
}