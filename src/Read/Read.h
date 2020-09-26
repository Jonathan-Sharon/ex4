#pragma once

#include "../ThreadPool/StructParameters.h"
#include "../ThreadPool/ThreadPool.h"

namespace ThreadPool {
class Queue;
}

namespace Read {
class Read {
public:
  /**
   * @brief read the massege. AfterWards, call for the appropriate function to
   * add Operate/Write to the queue
   *
   * @param queue the queue in which we need to add the next Operate/Write
   * @param info the info about the read we will do.
   */
  virtual void readMessage(ThreadPool::Queue &queue,
                           const ThreadPool::readParameters info) const = 0;
  virtual ~Read() = default;
};

class FirstRead : public Read {
  virtual void
  readMessage(ThreadPool::Queue &queue,
              const ThreadPool::readParameters info) const override;
  constexpr static char FIRST_WORD[] = "SOLVE";
};

class SecondRead : public Read {
  virtual void
  readMessage(ThreadPool::Queue &queue,
              const ThreadPool::readParameters info) const override;
};

constexpr static int BUFFER_SIZE = 1024;

/**
 * @brief removes all added tabs and spaces
 *
 * @param str the string to remove the spaces and tabs
 * @return uint number of spaces and tabs in the new string
 */
uint removeSpacesAndTabs(std::string &str);

/**
 * @brief There is an Error, so call for the appropriae Write Error
 *
 * @param queue the queue to add the WriteERror
 * @param info the info abour the read
 * @param errorCode the specif error code
 */
void WriteError(ThreadPool::Queue &queue, const ThreadPool::readParameters info,
                uint errorCode);

/**
 * @brief read which is mutual to all the reads in the protocol
 *
 * @param queue
 * @param info
 * @param buffer
 */
void defaultRead(ThreadPool::Queue &queue,
                 const ThreadPool::readParameters info, std::string &buffer);

} // namespace Read