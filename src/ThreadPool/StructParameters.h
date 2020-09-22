#pragma once

#include <ctime>
#include <memory>

namespace ThreadPool
{
    struct readParameters
    {
        int sockfd;
    };

    struct operateParameters
    {
        std::shared_ptr<std::string> readResult;
        int sockfd;
    };

    struct writeParameters
    {
        std::shared_ptr<std::string> result;
        double version;
        int sockfd;
        uint errorCode;
    };

} // namespace ThreadPool