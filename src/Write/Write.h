#pragma once

#include "../ThreadPool/StructParameters.h"
#include "../ThreadPool/ThreadPool.h"

namespace ThreadPool
{
    class Queue;
}

namespace Write
{
    class Write
    {
    public:
        virtual void writeMessage(ThreadPool::Queue &queue, const ThreadPool::writeParameters info) const = 0;
        virtual ~Write() = default;
    };

    class FirstWrite : public Write
    {
        virtual void writeMessage(ThreadPool::Queue &queue, const ThreadPool::writeParameters info) const override;
    };

    class SecondWrite : public Write
    {
        virtual void writeMessage(ThreadPool::Queue &queue, const ThreadPool::writeParameters info) const override;
    };

    class ErrorWrite : public Write
    {
        virtual void writeMessage(ThreadPool::Queue &queue, const ThreadPool::writeParameters info) const override;
    };
} // namespace Write