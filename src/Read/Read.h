#pragma once

#include "../ThreadPool/ThreadPool.h"

namespace Read
{
    class Read
    {
    public:
        virtual void read(const ThreadPool::read info) const;
        virtual ~Read() = default;
    };

    class FirstRead : public Read
    {
        virtual void read(const ThreadPool::read info) const override;
    };

    class SecondRead : public Read
    {
        virtual void read(const ThreadPool::read info) const override;
    };
} // namespace Read