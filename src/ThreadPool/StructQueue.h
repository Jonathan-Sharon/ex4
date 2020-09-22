#pragma once

#include "../Read/Read.h"
#include "../Write/Write.h"
#include "../Operations/Operate.h"

#include <memory>
#include <StructParameters.h>

namespace ThreadPool
{
    struct waitForRead
    {
        time_t lastReadTime;
        int sockfd;
        std::string readType;
        std::string lastReadData;
    };

    struct read
    {
        std::unique_ptr<Read::Read> reader;
        readParameters parameters;
    };

    struct operate
    {
        std::unique_ptr<Operate::Operate> operation;
        operateParameters parameters;
    };

    struct write
    {
        std::unique_ptr<Write::Write> writer;
        writeParameters parameters;
    };
} // namespace ThreadPool