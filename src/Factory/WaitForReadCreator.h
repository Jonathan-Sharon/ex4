#pragma once

#include "../ThreadPool/ThreadPool.h"

namespace ThreadPool {
class Queue;
}

namespace ThreadPool {
class WaitForReadCreator {
public:
  /**
   * @brief add the Wait For Read object to the queue
   *
   * @param queue the queue to add the Wait For Read to
   * @param info the parametets to add to the queue
   */
  void addToQueue(ThreadPool::Queue &queue,
                  const ThreadPool::waitForRead info) const;
};
} // namespace ThreadPool