#pragma once

#include "../ThreadPool/ThreadPool.h"
#include "../Read/Read.h"

namespace ThreadPool
{
    class Queue;
}

namespace ThreadPool
{
    class ReadCreator
    {
    public:
        virtual void addToQueue(ThreadPool::Queue &queue, const ThreadPool::readParameters info) const = 0;
        virtual ~ReadCreator() = default;
    };

    class FirstReadCreator : public ReadCreator
    {
    public:
        virtual void addToQueue(ThreadPool::Queue &queue, const ThreadPool::readParameters info) const override;
    };

    class SecondReadCreator : public ReadCreator
    {
    public:
        virtual void addToQueue(ThreadPool::Queue &queue, const ThreadPool::readParameters info) const override;
    };

} // namespace ThreadPool