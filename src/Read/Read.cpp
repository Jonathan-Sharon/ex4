#include <unistd.h>

#include "Read.h"

#include <iostream>
#include <memory>

void Read::FirstRead::readMessage(ThreadPool::Queue &queue, const ThreadPool::readParameters info) const
{
    std::string buffer(1024, '\0');
    if (read(info.sockfd, buffer.data(), buffer.size() - 1) < 0)
    {
        ThreadPool::ErrorWriteCreator errorWriteCreate;
        errorWriteCreate.addToQueue(queue, {std::make_shared<std::string_view>(""), info.version, info.sockfd, 1});
        queue.addAvailableThread();
        return;
    }

    ThreadPool::FirstWriteCreator firstWriteCreator;
    firstWriteCreator.addToQueue(queue, {std::make_shared<std::string_view>(""), info.version, info.sockfd, 0});
    queue.addAvailableThread();
}

void Read::SecondRead::readMessage(ThreadPool::Queue &queue, const ThreadPool::readParameters info) const
{
    queue.allocate();
    std::cout << info.sockfd << std::endl;
}