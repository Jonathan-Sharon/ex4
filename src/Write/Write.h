#pragma once

#include "../ThreadPool/StructParameters.h"
#include "../ThreadPool/ThreadPool.h"

namespace ThreadPool {
class Queue;
}

namespace Write {
class Write {
public:
  /**
   * @brief write the massege. AfterWards, call for the WaitForRead with the
   * appropriate values, or close the socket fd.
   *
   * @param queue the queue in which we need to add the next Operate/Write
   * @param info the info about the read we will do.
   */
  virtual void writeMessage(ThreadPool::Queue &queue,
                            const ThreadPool::writeParameters info) const = 0;
  virtual ~Write() = default;
};

class FirstWrite : public Write {
  virtual void
  writeMessage(ThreadPool::Queue &queue,
               const ThreadPool::writeParameters info) const override;
};

class SecondWrite : public Write {
  virtual void
  writeMessage(ThreadPool::Queue &queue,
               const ThreadPool::writeParameters info) const override;
};

class ErrorWrite : public Write {
  virtual void
  writeMessage(ThreadPool::Queue &queue,
               const ThreadPool::writeParameters info) const override;
};

/**
 * @brief There has been an error so call for the appropriate Error Code
 *
 * @param queue
 * @param info
 * @param errorCode
 */
void WriteError(ThreadPool::Queue &queue,
                const ThreadPool::writeParameters info, uint errorCode);
} // namespace Write