#pragma once

#include "../ThreadPool/ThreadPool.h"
#include "../ThreadPool/StructQueue.h"

namespace ThreadPool
{
    class Queue;
}

namespace WaitForReadCreator
{
    class WaitForReadCreator
    {
    public:
        void addToQueue(const ThreadPool::Queue &queue, const ThreadPool::waitForRead info) const;
    };
} // namespace WaitForReadCreator