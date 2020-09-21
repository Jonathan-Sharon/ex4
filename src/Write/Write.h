#pragma once

#include "../ThreadPool/StructParameters.h"

namespace Write
{
    class Write
    {
    public:
        virtual void write(const ThreadPool::writeParameters info) const;
        virtual ~Write() = default;
    };

    class FirstWrite : public Write
    {
        virtual void write(const ThreadPool::writeParameters info) const override;
    };

    class SecondWrite : public Write
    {
        virtual void write(const ThreadPool::writeParameters info) const override;
    };
} // namespace Write