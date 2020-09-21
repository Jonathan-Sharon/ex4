#pragma once

#include <arpa/inet.h>

#include <memory>
#include <queue>
#include <thread>
#include <vector>
#include <atomic>
#include <mutex>

namespace ThreadPool
{
    struct read
    {
        Read reader;
        time_t lastReadTime;
        int sockfd;
    };

    struct waitForRead
    {
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
        double version;
        int sockfd;
        uint errorCode;
    };

    class Queue
    {
    public:
        /**
     * @brief Construct a new Queue object
     * 
     * @param sockfd the socket file descriptor
     * @param connectAddress the connection address - used when doing accept
     * @param numberOfThreads number of threads to support the operation.
     *                        if it equals to 1, then the server is serial.
     */
        explicit Queue(const int sockfd, const sockaddr_in connectAddress, const unsigned int numberOfThreads);
        /**
         * @brief waits until there is an Read/Operation/Write to do. Once there is,
         * it does it.
         * 
         */
        void allocate();

    private:
        /**
     * @brief only return when there is Read/Operation/Write to do.
     * If one of the open file descriptors has something to send
     * then it calls for the Read constructor to add something to the read queue.
     * If more than 5 seconds have passed, it closes the file descriptors
     * 
     */
        void wait();

        /**
         * @brief In this section we check, using the select() function
         * If there is a read to do in the vector of file descriptors.
         * If there is, then it calls the Read factory.
         * 
         */
        void checkActiveFd();

        const int m_sockfd;
        const sockaddr_in m_connectAddress;
        const unsigned int m_numberOfThreads;
        const bool m_isSerial;

        std::atomic_bool m_isThereSomethingToRead;
        std::atomic_uint m_numberOfAvailableThreads;

        std::queue<read> m_readQueue;
        std::vector<waitForRead> m_waitForReadVector;
        std::queue<operate> m_operateQueue;
        std::queue<write> m_writeQueue;

        std::mutex m_readQueueMutex;
        std::mutex m_waitForReadVectorMutex;
        std::mutex m_writeQueueMutex;
        std::mutex m_operateQueueMutex;
    };
} // namespace ThreadPool