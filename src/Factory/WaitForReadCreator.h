#pragma once

#include "../ThreadPool/ThreadPool.h"

namespace ThreadPool
{
    class Queue;
}

namespace ThreadPool
{
    class WaitForReadCreator
    {
    public:
        void addToQueue(ThreadPool::Queue &queue, const ThreadPool::waitForRead info) const;
    };
} // namespace ThreadPool