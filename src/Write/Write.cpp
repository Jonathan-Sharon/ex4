#include <unistd.h>

#include "Write.h"

#include "../Factory/WaitForReadCreator.h"

#include <iostream>

void Write::FirstWrite::writeMessage(
    ThreadPool::Queue &queue, const ThreadPool::writeParameters info) const {
  std::string toWrite{"Version: " + std::to_string(info.version) + "\r\n" +
                      "status: 0\r\nresponse-length: 0\r\n\r\n"};
  if (write(info.sockfd, toWrite.data(), toWrite.length()) < 0) {
    WriteError(queue, info, 6);
    return;
  }

  // add the new communication to the "Wait For Read" Queue
  ThreadPool::WaitForReadCreator waitFroReadCreator;
  waitFroReadCreator.addToQueue(queue,
                                {std::time(nullptr), info.version, info.sockfd,
                                 "SECOND READ", info.result});
}

void Write::SecondWrite::writeMessage(
    ThreadPool::Queue &queue, const ThreadPool::writeParameters info) const {
  std::string toWrite{"Version: " + std::to_string(info.version) + "\r\n" +
                      "status: 0\r\n" + "response-length : 0\r\n\r\n" +
                      std::string(info.result)};

  if (write(info.sockfd, toWrite.data(), toWrite.length()) < 0) {
    WriteError(queue, info, 6);
    return;
  }
  close(info.sockfd);
  return;
  queue.allocate();
}

void Write::ErrorWrite::writeMessage(
    ThreadPool::Queue &queue, const ThreadPool::writeParameters info) const {
  std::string toWrite{"Version: " + std::to_string(info.version) + "\r\n" +
                      "status: " + std::to_string(info.errorCode) + "\r\n" +
                      "response-length : 0\r\n\r\n "};
  write(info.sockfd, toWrite.data(), toWrite.length());

  close(info.sockfd);
  return;
  queue.allocate();
}

inline void Write::WriteError(ThreadPool::Queue &queue,
                              const ThreadPool::writeParameters info,
                              uint errorCode) {
  ThreadPool::ErrorWriteCreator errorWriteCreate;
  errorWriteCreate.addToQueue(queue,
                              {"", info.version, info.sockfd, errorCode});
}