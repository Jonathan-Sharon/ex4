#include <stdexcept>
#include "Communication/TCPCommunication.h"

using namespace TCPCommunication;

int main(int argc, char *argv[])
{
    if (argc == 3)
    {
        connect(argc, argv);
        return;
    }

    throw std::runtime_error("invalid input!");
}