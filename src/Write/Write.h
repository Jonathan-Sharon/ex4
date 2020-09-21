#pragma once

#include "../ThreadPool/ThreadPool.h"

namespace Write
{
    class Write
    {
    public:
        virtual void write(const ThreadPool::write info) const;
        virtual ~Write() = default;
    };

    class FirstWrite : public Write
    {
        virtual void write(const ThreadPool::write info) const override;
    };

    class SecondWrite : public Write
    {
        virtual void write(const ThreadPool::write info) const override;
    };
} // namespace Write