#include "ThreadPool.h"

#include <thread>
#include <condition_variable>

Queue::Queue::Queue(const int sockfd, const sockaddr_in connectAddress, const bool isParallel) : m_sockfd{sockfd}, m_connectAddress{connectAddress}, m_isParallel{isParallel}, m_isThereSomethingToRead{false}
{
    isParallel ? m_numberOfAvailableThreads = std::thread::hardware_concurrency() - 1 : 0;
}

void Queue::Queue::allocate()
{
    std::mutex cv_m;
    std::unique_lock<std::mutex> lk(cv_m);
    std::condition_variable cv;
    cv.wait(lk, wait());

    if (!m_readQueue.empty())
    {
    }
}