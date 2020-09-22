#pragma once

#include "../ThreadPool/ThreadPool.h"

namespace ThreadPool
{
    class Queue;
}

namespace ThreadPool
{
    class WriteCreator
    {
    public:
        virtual void addToQueue(ThreadPool::Queue &queue, const ThreadPool::writeParameters info) const = 0;
        virtual ~WriteCreator() = default;
    };

    class FirstWriteCreator : public WriteCreator
    {
    public:
        virtual void addToQueue(ThreadPool::Queue &queue, const ThreadPool::writeParameters info) const override;
    };

    class SecondWriteCreator : public WriteCreator
    {
    public:
        virtual void addToQueue(ThreadPool::Queue &queue, const ThreadPool::writeParameters info) const override;
    };

    class ErrorWriteCreator : public WriteCreator
    {
    public:
        virtual void addToQueue(ThreadPool::Queue &queue, const ThreadPool::writeParameters info) const override;
    };

} // namespace ThreadPool