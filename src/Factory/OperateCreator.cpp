#include "OperateCreator.h"

#include <memory>
#include <mutex>

void ThreadPool::DFSCreator::addToQueue(ThreadPool::Queue &queue,
                                        const ThreadPool::operateParameters info) const
{
    std::unique_lock<std::mutex> lock(queue.m_operateQueueMutex);
    queue.m_operateQueue.push({std::make_unique<Operate::DFS>(), info});
}

void ThreadPool::BFSCreator::addToQueue(ThreadPool::Queue &queue,
                                        const ThreadPool::operateParameters info) const
{
    std::unique_lock<std::mutex> lock(queue.m_operateQueueMutex);
    queue.m_operateQueue.push({std::make_unique<Operate::BFS>(), info});
}

void ThreadPool::BestFSCreator::addToQueue(ThreadPool::Queue &queue,
                                           const ThreadPool::operateParameters info) const
{
    std::unique_lock<std::mutex> lock(queue.m_operateQueueMutex);
    queue.m_operateQueue.push({std::make_unique<Operate::BestFS>(), info});
}

void ThreadPool::AStarCreator::addToQueue(ThreadPool::Queue &queue,
                                          const ThreadPool::operateParameters info) const
{
    std::unique_lock<std::mutex> lock(queue.m_operateQueueMutex);
    queue.m_operateQueue.push({std::make_unique<Operate::AStar>(), info});
}