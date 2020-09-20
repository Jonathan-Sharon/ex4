#pragma once

#include <arpa/inet.h>

#include <memory>
#include <queue>
#include <thread>
#include <vector>

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
        Operate operation;
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
        Queue(const int sockfd, const sockaddr_in connectAddress, const bool m_isParallel);
        void allocate();
        bool wait();

    private:
        const int m_sockfd;
        const sockaddr_in m_connectAddress;
        const bool m_isParallel;
        bool m_isThereSomethingToRead;
        unsigned int m_numberOfAvailableThreads;
        std::queue<read> m_readQueue;
        std::queue<operate> m_operateQueue;
        std::queue<write> m_writeQueue;
    };
} // namespace Queue