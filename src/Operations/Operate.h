#pragma once

#include "../ThreadPool/ThreadPool.h"

namespace Operate
{
    class Operate
    {
    public:
        virtual void operate(const ThreadPool::operate info) const;
        virtual ~Operate() = default;
    };

    class DFS : public Operate
    {
        virtual void operate(const ThreadPool::operate info) const override;
    };

    class BFS : public Operate
    {
        virtual void operate(const ThreadPool::operate info) const override;
    };

    class BestFS : public Operate
    {
        virtual void operate(const ThreadPool::operate info) const override;
    };

    class AStar : public Operate
    {
        virtual void operate(const ThreadPool::operate info) const override;
    };
} // namespace Operate