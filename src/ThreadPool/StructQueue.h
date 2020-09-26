#pragma once

#include "StructParameters.h"

#include "../Operations/Operate.h"
#include "../Read/Read.h"
#include "../Write/Write.h"

#include <memory>

namespace Read {
class Read;
}

namespace Write {
class Write;
}

namespace Operate {
class Operate;
}

namespace ThreadPool {
struct waitForRead {
  time_t lastReadTime;
  double version;
  int sockfd;
  std::string_view readType;
  std::string_view operateToCreate;
};

struct read {
  std::shared_ptr<Read::Read> reader;
  readParameters parameters;
};

struct operate {
  std::shared_ptr<Operate::Operate> operation;
  operateParameters parameters;
};

struct write {
  std::shared_ptr<Write::Write> writer;
  writeParameters parameters;
};
} // namespace ThreadPool