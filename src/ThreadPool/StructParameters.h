#pragma once

#include <ctime>
#include <memory>

namespace ThreadPool
{
    struct readParameters
    {
        std::string_view operateToCreate;
        double version;
        int sockfd;
    };

    struct operateParameters
    {
        std::shared_ptr<std::string_view> readResult;
        double version;
        int sockfd;
    };

    struct writeParameters
    {
        std::shared_ptr<std::string_view> result;
        double version;
        int sockfd;
        uint errorCode;
    };

} // namespace ThreadPool