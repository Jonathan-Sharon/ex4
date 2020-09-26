#include "WriteCreator.h"

#include <iostream>
#include <memory>
#include <mutex>

void ThreadPool::FirstWriteCreator::addToQueue(
    ThreadPool::Queue &queue, const ThreadPool::writeParameters info) const {

  std::unique_lock<std::mutex> lock(queue.m_writeQueueMutex);
  queue.m_writeQueue.push({std::make_shared<Write::FirstWrite>(), info});
}

void ThreadPool::SecondWriteCreator::addToQueue(
    ThreadPool::Queue &queue, const ThreadPool::writeParameters info) const {
  std::unique_lock<std::mutex> lock(queue.m_writeQueueMutex);
  queue.m_writeQueue.push({std::make_shared<Write::SecondWrite>(), info});
}

void ThreadPool::ErrorWriteCreator::addToQueue(
    ThreadPool::Queue &queue, const ThreadPool::writeParameters info) const {
  std::unique_lock<std::mutex> lock(queue.m_writeQueueMutex);
  queue.m_writeQueue.push({std::make_shared<Write::ErrorWrite>(), info});
}