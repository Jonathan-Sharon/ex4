#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "TCPCommunication.h"

#include <system_error>

#define THROW_SYSTEM_ERROR() \
    throw std::system_error { errno, std::system_category() }

void connect(const int argv, const char *const argc[])
{
    const auto sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        THROW_SYSTEM_ERROR();
    }

    int opt{1};
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) < 0)
    {
        close(sockfd);
        THROW_SYSTEM_ERROR();
    }

    sockaddr_in connectAddress{};
    if (0 == inet_aton("127.0.0.1", &connectAddress.sin_addr))
    {
        close(sockfd);
        throw std::runtime_error{"Failed converting IP to 4-bytes"};
    }
    connectAddress.sin_family = AF_INET;
    connectAddress.sin_port = htons(8081);
}