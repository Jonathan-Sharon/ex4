#pragma once

#include "../ThreadPool/ThreadPool.h"

namespace ThreadPool
{
    class Queue;
}

namespace ThreadPool
{
    class OperateCreator
    {
    public:
        virtual void addToQueue(ThreadPool::Queue &queue, const ThreadPool::operateParameters info) const = 0;
        virtual ~OperateCreator() = default;
    };

    class DFSCreator : public OperateCreator
    {
    public:
        virtual void addToQueue(ThreadPool::Queue &queue, const ThreadPool::operateParameters info) const override;
    };

    class BFSCreator : public OperateCreator
    {
    public:
        virtual void addToQueue(ThreadPool::Queue &queue, const ThreadPool::operateParameters info) const override;
    };

    class BestFSCreator : public OperateCreator
    {
    public:
        virtual void addToQueue(ThreadPool::Queue &queue, const ThreadPool::operateParameters info) const override;
    };

    class AStarCreator : public OperateCreator
    {
    public:
        virtual void addToQueue(ThreadPool::Queue &queue, const ThreadPool::operateParameters info) const override;
    };

} // namespace ThreadPool