#pragma once

#include "Operate.h"

#include "../ThreadPool/StructParameters.h"
#include "../ThreadPool/ThreadPool.h"

namespace ThreadPool {
class Queue;
}

namespace Operate {
class BestFS : public Operate {
  virtual void operate(ThreadPool::Queue &queue,
                       const ThreadPool::operateParameters info) const override;
};
} // namespace Operate