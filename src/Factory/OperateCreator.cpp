#include "OperateCreator.h"

#include "../Operations/AStar.h"
#include "../Operations/BFS.h"
#include "../Operations/BestFS.h"
#include "../Operations/DFS.h"

#include <memory>
#include <mutex>

void ThreadPool::DFSCreator::addToQueue(
    ThreadPool::Queue &queue, const ThreadPool::operateParameters info) const {
  std::unique_lock<std::mutex> lock(queue.m_operateQueueMutex);
  queue.m_operateQueue.push({std::make_shared<Operate::DFS>(), info});
}

void ThreadPool::BFSCreator::addToQueue(
    ThreadPool::Queue &queue, const ThreadPool::operateParameters info) const {
  std::unique_lock<std::mutex> lock(queue.m_operateQueueMutex);
  queue.m_operateQueue.push({std::make_shared<Operate::BFS>(), info});
}

void ThreadPool::BestFSCreator::addToQueue(
    ThreadPool::Queue &queue, const ThreadPool::operateParameters info) const {
  std::unique_lock<std::mutex> lock(queue.m_operateQueueMutex);
  queue.m_operateQueue.push({std::make_shared<Operate::BestFS>(), info});
}

void ThreadPool::AStarCreator::addToQueue(
    ThreadPool::Queue &queue, const ThreadPool::operateParameters info) const {
  std::unique_lock<std::mutex> lock(queue.m_operateQueueMutex);
  queue.m_operateQueue.push({std::make_shared<Operate::AStar>(), info});
}