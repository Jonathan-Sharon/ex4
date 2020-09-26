#pragma once

#include "../ThreadPool/StructParameters.h"
#include "../ThreadPool/ThreadPool.h"

namespace ThreadPool {
class Queue;
}

namespace Operate {
class Operate {
public:
  virtual void operate(ThreadPool::Queue &queue,
                       const ThreadPool::operateParameters info) const = 0;
  virtual ~Operate() = default;
};
} // namespace Operate