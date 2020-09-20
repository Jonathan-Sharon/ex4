#pragma once

#include <arpa/inet.h>

#include <memory>
#include <queue>
#include <thread>
#include <vector>
#include <atomic>
#include <mutex>

namespace Queue
{
    struct read
    {
        Read reader;
        time_t lastReadTime;
        int sockfd;
    };

    struct operate
    {
        Operate operator;
        int sockfd;
    };

    struct write
    {
        Write writer;
        std::unique_ptr<std::string> result;
        int sockfd;
    };

    class Queue
    {
    public:
        explicit Queue(const int sockfd, const sockaddr_in connectAddress, const unsigned int numberOfThreads);
        void allocate();

    private:
        void wait();

        const int m_sockfd;
        const sockaddr_in m_connectAddress;
        const unsigned int m_numberOfThreads;
        const bool m_isSerial;

        std::atomic_bool m_isThereSomethingToRead;
        std::atomic_uint m_numberOfAvailableThreads;

        std::queue<read> m_readQueue;
        std::queue<operate> m_operateQueue;
        std::queue<write> m_writeQueue;

        std::mutex m_readQueueMutex;
        std::mutex m_writeQueueMutex;
        std::mutex m_operateQueueMutex;
    };
} // namespace Queue