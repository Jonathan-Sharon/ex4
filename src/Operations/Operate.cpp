#include "Operate.h"

#include <iostream>

void Operate::DFS::operate(ThreadPool::Queue &queue,
                           const ThreadPool::operateParameters info) const {
  // add the new communication to the "Wait For Read" Queue
  ThreadPool::SecondWriteCreator secondWriteCreator;
  secondWriteCreator.addToQueue(queue, {"", info.version, info.sockfd, 0});
}

void Operate::BFS::operate(ThreadPool::Queue &queue,
                           const ThreadPool::operateParameters info) const {
  // add the new communication to the "Wait For Read" Queue
  ThreadPool::SecondWriteCreator secondWriteCreator;
  secondWriteCreator.addToQueue(queue, {"yes", info.version, info.sockfd, 0});
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
