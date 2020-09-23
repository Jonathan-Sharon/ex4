#include "Read.h"

#include <iostream>

void Read::FirstRead::read(ThreadPool::Queue &queue, const ThreadPool::readParameters info) const
{
    queue.allocate();
    std::cout << info.sockfd << std::endl;
}

void Read::SecondRead::read(ThreadPool::Queue &queue, const ThreadPool::readParameters info) const
{
    queue.allocate();
    std::cout << info.sockfd << std::endl;
}