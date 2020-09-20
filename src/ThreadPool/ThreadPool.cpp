#include <string.h>
#include <sys/time.h>

#include "ThreadPool.h"

#include <algorithm>

Queue::Queue::Queue(const int sockfd, const sockaddr_in connectAddress,
                    const unsigned int numberOfThreads) : m_sockfd{sockfd},
                                                          m_connectAddress{connectAddress},
                                                          m_numberOfThreads{numberOfThreads},
                                                          m_isSerial{numberOfThreads == 1},
                                                          m_isThereSomethingToRead{false},
                                                          m_numberOfAvailableThreads{numberOfThreads - 1}
{
}

void Queue::Queue::allocate()
{
    while (true)
    {
        wait();

        if (!m_writeQueue.empty())
        {
            if (m_isSerial == true)
            {
                m_writeQueue.front().writer.write(m_writeQueue.front().result, m_writeQueue.front().sockfd);
                m_writeQueue.pop();
                continue;
            }

            std::unique_lock<std::mutex> lock(m_writeQueueMutex);
            std::thread(m_writeQueue.front().writer.write,
                        m_writeQueue.front().result, m_writeQueue.front().sockfd);
            --m_numberOfAvailableThreads;
            m_writeQueue.pop();
            continue;
        }

        if (!m_operateQueue.empty())
        {
            if (m_isSerial == true)
            {
                m_operateQueue.front().operator.operate(m_operateQueue.front().sockfd);
                m_operateQueue.pop();
                continue;
            }

            std::unique_lock<std::mutex> lock(m_operateQueueMutex);
            std::thread(m_operateQueue.front().operator.operate, m_operateQueue.front().sockfd);
            --m_numberOfAvailableThreads;
            m_operateQueue.pop();
            continue;
        }

        if (!m_readQueue.empty())
        {
            if (m_isSerial == true)
            {
                m_readQueue.front().reader.read(m_readQueue.front().sockfd);
                m_readQueue.pop();
                continue;
            }

            std::unique_lock<std::mutex> lock(m_readQueueMutex);
            std::thread(m_readQueue.front().reader.read, m_readQueue.front().sockfd);
            --m_numberOfAvailableThreads;
            m_readQueue.pop();
            continue;
        }
    }
}

void Queue::Queue::wait()
{
    while (true)
    {
        if (!m_readQueue.empty())
        {
            return;
        }

        if (!m_operateQueue.empty())
        {
            return;
        }

        if (!m_writeQueue.empty())
        {
            return;
        }

        fd_set readfds;
        //clear the socket set
        FD_ZERO(&readfds);

        //add master socket to set
        FD_SET(m_sockfd, &readfds);
        int maxSd{m_sockfd};
        std::vector<int> sockfdVector;

        std::time_t currentTime = std::time(nullptr);
        {
            std::unique_lock<std::mutex> lock(m_timeReadVectorMutex);
            for (uint i{0}; i < m_timeReadVector.size(); ++i)
            {
                if (m_timeReadVector[i].lastReadTime + 5 <= currentTime)
                {
                    m_timeReadVector.erase(m_timeReadVector.begin() + i);
                }

                //add to read list
                FD_SET(m_timeReadVector[i].sockfd, &readfds);
                //add Also to the vector list
                sockfdVector.push_back(m_timeReadVector[i].sockfd);

                //highest file descriptor number, need it for the select function
                if (m_timeReadVector[i].sockfd > maxSd)
                {
                    maxSd = m_timeReadVector[i].sockfd;
                }
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

        for (uint i = 0; i < sockfdVector.size(); ++i)
        {
            if (sockfdVector[i] != m_sockfd && FD_ISSET(sockfdVector[i], &readfds))
            {
                //factoryOfRead
            }
        }
    }
}