#pragma once

#include "../ThreadPool/StructParameters.h"
#include "../ThreadPool/ThreadPool.h"

namespace ThreadPool
{
    class Queue;
}

namespace Read
{
    class Read
    {
    public:
        virtual void readMessage(ThreadPool::Queue &queue, const ThreadPool::readParameters info) const = 0;
        virtual ~Read() = default;
    };

    class FirstRead : public Read
    {
        virtual void readMessage(ThreadPool::Queue &queue, const ThreadPool::readParameters info) const override;
        constexpr static char FIRST_WORD[] = "SOLVE";
    };

    class SecondRead : public Read
    {
        virtual void readMessage(ThreadPool::Queue &queue, const ThreadPool::readParameters info) const override;
    };

    constexpr static int BUFFER_SIZE = 1024;
    uint removeSpacesAndTabs(std::string &str);
    void WriteError(ThreadPool::Queue &queue, const ThreadPool::readParameters info, uint errorCode);
    void defaultRead(ThreadPool::Queue &queue, const ThreadPool::readParameters info, std::string &buffer);

} // namespace Read