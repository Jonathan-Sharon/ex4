#include <unistd.h>

#include "Write.h"

#include <iostream>

void Write::FirstWrite::writeMessage(ThreadPool::Queue &queue, const ThreadPool::writeParameters info) const
{
    std::string_view toWrite{"Great!"};
    if (write(info.sockfd, toWrite.data(), toWrite.length()) < 0)
    {
        ThreadPool::ErrorWriteCreator errorWriteCreate;
        errorWriteCreate.addToQueue(queue, {std::make_shared<std::string_view>(""), info.version, info.sockfd, 1});
        return;
    }
    close(info.sockfd);
}

void Write::SecondWrite::writeMessage(ThreadPool::Queue &queue, const ThreadPool::writeParameters info) const
{
    queue.allocate();
    std::cout << info.sockfd << std::endl;
}

void Write::ErrorWrite::writeMessage(ThreadPool::Queue &queue, const ThreadPool::writeParameters info) const
{
    queue.allocate();
    std::cout << info.sockfd << std::endl;
}