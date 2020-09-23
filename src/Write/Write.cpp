#include "Write.h"

#include <iostream>

void Write::FirstWrite::write(ThreadPool::Queue &queue, const ThreadPool::writeParameters info) const
{
    queue.allocate();
    std::cout << info.sockfd << std::endl;
}

void Write::SecondWrite::write(ThreadPool::Queue &queue, const ThreadPool::writeParameters info) const
{
    queue.allocate();
    std::cout << info.sockfd << std::endl;
}

void Write::ErrorWrite::write(ThreadPool::Queue &queue, const ThreadPool::writeParameters info) const
{
    queue.allocate();
    std::cout << info.sockfd << std::endl;
}