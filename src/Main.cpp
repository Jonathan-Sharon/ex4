#include <iostream>
#include <stdexcept>

#include "Communication/Communication.h"

using namespace Communication;

int main(int argc, char *argv[])
{
  if (argc == 3 || argc == 2)
  {
    connect(argc, argv);
    return 0;
  }

  throw std::runtime_error("invalid input!");
}