#include "Operate.h"

#include <iostream>

void Operate::DFS::operate(ThreadPool::Queue &queue, const ThreadPool::operateParameters info) const
{
    queue.allocate();
    std::cout << info.sockfd << std::endl;
}

void Operate::BFS::operate(ThreadPool::Queue &queue, const ThreadPool::operateParameters info) const
{
    queue.allocate();
    std::cout << info.sockfd << std::endl;
}

void Operate::BestFS::operate(ThreadPool::Queue &queue, const ThreadPool::operateParameters info) const
{
    queue.allocate();
    std::cout << info.sockfd << std::endl;
}

void Operate::AStar::operate(ThreadPool::Queue &queue, const ThreadPool::operateParameters info) const
{
    queue.allocate();
    std::cout << info.sockfd << std::endl;
}
