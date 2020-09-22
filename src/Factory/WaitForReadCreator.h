#pragma once

#include "../ThreadPool/ThreadPool.h"

namespace WaitForReadCreator
{
    class WaitForReadCreator
    {
    public:
        void addToQueue(const ThreadPool::waitForRead info) const;
    };
} // namespace WaitForReadCreator