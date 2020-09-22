#include "ReadCreator.h"

#include "../Read/Read.h"

#include <memory>
#include <mutex>

using namespace ThreadPool;

void ThreadPool::FirstReadCreator::addToQueue(ThreadPool::Queue &queue,
                                              const ThreadPool::readParameters info) const
{
    std::unique_lock<std::mutex> lock(queue.m_readQueueMutex);
    queue.m_readQueue.push({std::make_unique<Read::FirstRead>(), info});
}

void ThreadPool::SecondReadCreator::addToQueue(ThreadPool::Queue &queue,
                                               const ThreadPool::readParameters info) const
{
    std::unique_lock<std::mutex> lock(queue.m_readQueueMutex);
    queue.m_readQueue.push({std::make_unique<Read::SecondRead>(), info});
}