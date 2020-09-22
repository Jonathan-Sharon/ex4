#pragma once

#include "../ThreadPool/StructParameters.h"

namespace Operate
{
    class Operate
    {
    public:
        virtual void operate(const ThreadPool::operateParameters info) const = 0;
        virtual ~Operate() = default;
    };

    class DFS : public Operate
    {
        virtual void operate(const ThreadPool::operateParameters info) const override;
    };

    class BFS : public Operate
    {
        virtual void operate(const ThreadPool::operateParameters info) const override;
    };

    class BestFS : public Operate
    {
        virtual void operate(const ThreadPool::operateParameters info) const override;
    };

    class AStar : public Operate
    {
        virtual void operate(const ThreadPool::operateParameters info) const override;
    };
} // namespace Operate