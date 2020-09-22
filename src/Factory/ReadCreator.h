#pragma once

#include "../Read/Read.h"

namespace ReadCreator
{
    class ReadCreator
    {
    public:
        virtual void addToQueue(const ThreadPool::readParameters info) const = 0;
        virtual ~ReadCreator() = default;
    };

    class FirstReadCreator : public ReadCreator
    {
    public:
        virtual void addToQueue(const ThreadPool::readParameters info) const override;
    };

    class SecondReadCreator : public ReadCreator
    {
    public:
        virtual void addToQueue(const ThreadPool::readParameters info) const override;
    };

} // namespace ReadCreator