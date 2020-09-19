#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "TCPCommunication.h"

#include <cmath>
#include <system_error>
#include <thread>
#include <climits>

#define THROW_SYSTEM_ERROR() \
  throw std::system_error { errno, std::system_category() }

void TCPCommunication::connect(const int argc, const char *const argv[])
{
  const auto sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
  {
    THROW_SYSTEM_ERROR();
  }

  int opt{1};
  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
                 sizeof(opt)) < 0)
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

  char *ptr;
  long int port = strtol(argv[1], &ptr, 10);
  if (port <= 0 || port >= std::exp2(sizeof(uint16_t) * 8))
  {
    close(sockfd);
    throw std::runtime_error{"Invalid port input"};
  }
  connectAddress.sin_port = htons(static_cast<uint16_t>(port));

  if (bind(sockfd, (struct sockaddr *)&connectAddress, sizeof(connectAddress)) < 0)
  {
    close(sockfd);
    THROW_SYSTEM_ERROR();
  }

  unsigned int backlog;
  bool isParallel;
  bool isSerial;

  if ((isParallel = (argc == 2 || strcmp(argv[argc - 1], "parallel") == 0)) == true)
  {
    backlog = std::thread::hardware_concurrency() / 3;
  }
  else if ((isSerial = (strcmp(argv[argc - 1], "serial") == 0)) == true)
  {
    backlog = 5;
  }
  else
  {
    throw std::runtime_error("invalid server-type");
  }

  if (listen(sockfd, backlog) < 0)
  {
    close(sockfd);
    THROW_SYSTEM_ERROR();
  }

  int new_socket, addrlen{sizeof(connectAddress)};
  if ((new_socket = accept(sockfd, (struct sockaddr *)&connectAddress,
                           (socklen_t *)&addrlen)) < 0)
  {
    perror("accept");
    exit(EXIT_FAILURE);
  }

  char buffer[1024]{{0}};
  read(new_socket, buffer, 1024);
  printf("%s\n", buffer);
  send(new_socket, "good", strlen("good"), 0);
  printf("Hello message sent\n");
}