#include <string.h>
#include <sys/time.h>

#include "ThreadPool.h"

Queue::Queue::Queue(const int sockfd, const sockaddr_in connectAddress, const unsigned int numberOfThreads) : m_sockfd{sockfd},
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
    }
}