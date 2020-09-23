#pragma once

#include "StructParameters.h"
#include "StructQueue.h"

#include <arpa/inet.h>

#include "../Factory/MapCreator.h"

#include <queue>
#include <thread>
#include <vector>
#include <atomic>
#include <mutex>

namespace MapCreator
{
    class MapCreator;
}

namespace ThreadPool
{

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
        static constexpr int TIME_TO_CLOSE = 5;

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

        std::unique_ptr<MapCreator::MapCreator> m_mapCreator;

        std::queue<read> m_readQueue;
        std::vector<waitForRead> m_waitForReadVector;
        std::queue<operate> m_operateQueue;
        std::queue<write> m_writeQueue;

        std::mutex m_readQueueMutex;
        std::mutex m_waitForReadVectorMutex;
        std::mutex m_writeQueueMutex;
        std::mutex m_operateQueueMutex;

        friend class FirstReadCreator;
        friend class SecondReadCreator;

        friend class FirstWriteCreator;
        friend class SecondWriteCreator;
        friend class ErrorWriteCreator;

        friend class DFSCreator;
        friend class BFSCreator;
        friend class BestFSCreator;
        friend class AStarCreator;

        friend class WaitForReadCreator;
    };

    void readThread(Queue &queue, const read read);
    void writeThread(Queue &queue, const write write);
    void operateThread(Queue &queue, const operate operate);

} // namespace ThreadPool