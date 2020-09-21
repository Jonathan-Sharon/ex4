#pragma once

#include "../ThreadPool/StructParameters.h"

namespace Read
{
    class Read
    {
    public:
        virtual void read(const ThreadPool::readParameters info) const;
        virtual ~Read() = default;
    };

    class FirstRead : public Read
    {
        virtual void read(const ThreadPool::readParameters info) const override;
    };

    class SecondRead : public Read
    {
        virtual void read(const ThreadPool::readParameters info) const override;
    };
} // namespace Read