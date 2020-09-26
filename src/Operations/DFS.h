#pragma once

#include "Operate.h"

#include "../ThreadPool/StructParameters.h"
#include "../ThreadPool/ThreadPool.h"
#include "Graph/Graph.h"

namespace ThreadPool {
class Queue;
}

namespace Operate {
class DFS : public Operate {
  virtual void operate(ThreadPool::Queue &queue,
                       const ThreadPool::operateParameters info) const override;

  bool dfs(Graph::Graph &graph, std::string &result,
           std::vector<std::vector<bool>> &visit, uint &sum) const;
};
} // namespace Operate
