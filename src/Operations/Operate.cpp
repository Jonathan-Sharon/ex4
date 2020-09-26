#include "Operate.h"
#include "AStar.h"
#include "BFS.h"
#include "BestFS.h"
#include "DFS.h"

#include "../Operations/Graph/Graph.h"

#include <iostream>

/**void Operate::DFS::operate(ThreadPool::Queue &queue,
                           const ThreadPool::operateParameters info) const {
  Graph::Graph graph{info.readResult};
  std::vector<std::vector<bool>>(graph.getHeight(),
                                 std::vector<bool>(graph.getWidth(), false));

  if(graph.)
  // add the new communication to the "Wait For Read" Queue
  ThreadPool::SecondWriteCreator secondWriteCreator;
  secondWriteCreator.addToQueue(queue, {"", info.version, info.sockfd, 0});
}
*/

void Operate::BFS::operate(ThreadPool::Queue &queue,
                           const ThreadPool::operateParameters info) const {
  // add the new communication to the "Wait For Read" Queue
  ThreadPool::SecondWriteCreator secondWriteCreator;
  secondWriteCreator.addToQueue(queue, {"", info.version, info.sockfd, 0});
}

void Operate::BestFS::operate(ThreadPool::Queue &queue,
                              const ThreadPool::operateParameters info) const {
  // add the new communication to the "Wait For Read" Queue
  ThreadPool::SecondWriteCreator secondWriteCreator;
  secondWriteCreator.addToQueue(queue, {"", info.version, info.sockfd, 0});
}

void Operate::AStar::operate(ThreadPool::Queue &queue,
                             const ThreadPool::operateParameters info) const {
  // add the new communication to the "Wait For Read" Queue
  ThreadPool::SecondWriteCreator secondWriteCreator;
  secondWriteCreator.addToQueue(queue, {"", info.version, info.sockfd, 0});
}
