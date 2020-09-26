#pragma once

#include "../ThreadPool/ThreadPool.h"

namespace ThreadPool {
class Queue;
}

namespace ThreadPool {
class ReadCreator {
public:
  /**
   * @brief add the read to the queue
   *
   * @param queue the queue to add the read to
   * @param info the parametets to add to the queue
   */
  virtual void addToQueue(ThreadPool::Queue &queue,
                          const ThreadPool::readParameters info) const = 0;
  virtual ~ReadCreator() = default;
};

class FirstReadCreator : public ReadCreator {
public:
  virtual void addToQueue(ThreadPool::Queue &queue,
                          const ThreadPool::readParameters info) const override;
};

class SecondReadCreator : public ReadCreator {
public:
  virtual void addToQueue(ThreadPool::Queue &queue,
                          const ThreadPool::readParameters info) const override;
};

} // namespace ThreadPool