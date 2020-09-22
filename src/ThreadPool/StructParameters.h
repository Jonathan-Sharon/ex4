#pragma once

#include <ctime>
#include <memory>

namespace ThreadPool
{
    struct readParameters
    {
        time_t lastReadTime;
        int sockfd;
    };

    struct operateParameters
    {
        int sockfd;
    };

    struct writeParameters
    {
        std::unique_ptr<std::string> result;
        double version;
        int sockfd;
        uint errorCode;
    };

} // namespace ThreadPool