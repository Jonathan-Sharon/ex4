#pragma once

#include "../Write/Write.h"

namespace WriteCreator
{
    class WriteCreator
    {
    public:
        virtual void addToQueue(const ThreadPool::writeParameters info) const = 0;
        virtual ~WriteCreator() = default;
    };

    class FirstWriteCreator : public WriteCreator
    {
    public:
        virtual void addToQueue(const ThreadPool::writeParameters info) const override;
    };

    class SecondWriteCreator : public WriteCreator
    {
    public:
        virtual void addToQueue(const ThreadPool::writeParameters info) const override;
    };

    class ErrorWriteCreator : public WriteCreator
    {
    public:
        virtual void addToQueue(const ThreadPool::writeParameters info) const override;
    };

} // namespace WriteCreator