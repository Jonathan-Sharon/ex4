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
        virtual void read(ThreadPool::Queue &queue, const ThreadPool::readParameters info) const = 0;
        virtual ~Read() = default;
    };

    class FirstRead : public Read
    {
        virtual void read(ThreadPool::Queue &queue, const ThreadPool::readParameters info) const override;
    };

    class SecondRead : public Read
    {
        virtual void read(ThreadPool::Queue &queue, const ThreadPool::readParameters info) const override;
    };
} // namespace Read