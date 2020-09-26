#include "ReadCreator.h"

#include <memory>
#include <mutex>

void ThreadPool::FirstReadCreator::addToQueue(ThreadPool::Queue &queue,
                                              const ThreadPool::readParameters info) const
{
    std::unique_lock<std::mutex> lock(queue.m_readQueueMutex);
    queue.m_readQueue.push({std::make_shared<Read::FirstRead>(), info});
}

void ThreadPool::SecondReadCreator::addToQueue(ThreadPool::Queue &queue,
                                               const ThreadPool::readParameters info) const
{
    std::unique_lock<std::mutex> lock(queue.m_readQueueMutex);
    queue.m_readQueue.push({std::make_shared<Read::SecondRead>(), info});
}