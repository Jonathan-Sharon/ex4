#pragma once

#include "Graph/Graph.h"
#include "Operate.h"

#include "../ThreadPool/StructParameters.h"
#include "../ThreadPool/ThreadPool.h"

namespace ThreadPool {
class Queue;
}

namespace Operate {
class BFS : public Operate {
  virtual void operate(ThreadPool::Queue &queue,
                       const ThreadPool::operateParameters info) const override;
};

struct BFSObject {
  Graph::Point Point;
  std::string result;
};

} // namespace Operate