#include "WaitForReadCreator.h"

#include <memory>
#include <mutex>

void ThreadPool::WaitForReadCreator::addToQueue(ThreadPool::Queue &queue,
                                                const ThreadPool::waitForRead info) const
{
    std::unique_lock<std::mutex> lock(queue.m_waitForReadVectorMutex);
    queue.m_waitForReadVector.push_back(info);
}