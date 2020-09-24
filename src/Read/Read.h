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
        constexpr static int BUFFER_SIZE = 1024;
        constexpr static char FIRST_WORD[] = "SOLVE";
    };

    class FirstRead : public Read
    {
        virtual void readMessage(ThreadPool::Queue &queue, const ThreadPool::readParameters info) const override;
    };

    class SecondRead : public Read
    {
        virtual void readMessage(ThreadPool::Queue &queue, const ThreadPool::readParameters info) const override;
    };

    uint removeSpacesAndTabs(std::string &str);
    inline void CreateErrorWrite(ThreadPool::Queue &queue, const ThreadPool::readParameters info, uint errorCode);
} // namespace Read