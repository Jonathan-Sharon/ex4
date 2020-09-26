#include "BFS.h"

#include "Matrix/MatrixErrorCode.hpp"

#include <queue>
#include <vector>

void Operate::BFS::operate(ThreadPool::Queue &queue,
                           const ThreadPool::operateParameters info) const {

  // Create the Graph and the vectors
  try {
    Graph::Graph graph{info.readResult};
    std::vector<std::vector<bool>> visited(
        graph.getHeight(), std::vector<bool>(graph.getWidth(), false));

    // Create a queue for BFS
    std::queue<BFSObject> objectQueue;

    // Mark the current node as visited and enqueue it
    visited.at(graph.getStartPointX()).at(graph.getStartPointY()) = true;
    objectQueue.push({{graph.getStartPointX(), graph.getStartPointY()}, ""});

    std::string str{""};
    double sum{0};
    bool isThereRoot{false};

    while (!objectQueue.empty()) {
      // Dequeue a vertex from queue and print it
      BFSObject object{objectQueue.front()};
      Graph::Point point{object.Point};
      objectQueue.pop();

      if (point.row == graph.getEndPointX() &&
          point.column == graph.getEndPointY()) {
        if (sum == 0) {
          isThereRoot = true;
          break;
        } else {
          sum += graph.getValue(point.row, point.column);
          str.append(object.result);
          isThereRoot = true;
          break;
        }
      }

      sum += graph.getValue(point.row, point.column);
      str.append(object.result);

      // Get all adjacent vertices of the dequeued
      // vertex s. If a adjacent has not been visited,
      // then mark it visited and enqueue it
      if (point.row + 1 < graph.getHeight() &&
          visited.at(point.row + 1).at(point.column) == false &&
          graph.getValue(point.row + 1, point.column) != 0) {

        visited.at(point.row + 1).at(point.column) = true;
        objectQueue.push({{point.row + 1, point.column}, ",Down"});
      }

      if (point.column + 1 < graph.getWidth() &&
          visited.at(point.row).at(point.column + 1) == false &&
          graph.getValue(point.row, point.column + 1) != 0) {

        visited.at(point.row).at(point.column + 1) = true;
        objectQueue.push({{point.row, point.column + 1}, ",Right"});
      }

      if (int(point.row - 1) >= 0 &&
          visited.at(point.row - 1).at(point.column) == false &&
          graph.getValue(point.row - 1, point.column) != 0) {

        visited.at(point.row - 1).at(point.column) = true;
        objectQueue.push({{point.row - 1, point.column}, ",Up"});
      }

      if (int(point.column - 1) >= 0 &&
          visited.at(point.row).at(point.column - 1) == false &&
          graph.getValue(point.row, point.column - 1) != 0) {

        visited.at(point.row).at(point.column - 1) = true;
        objectQueue.push({{point.row, point.column - 1}, ",Left"});
      }
    }

    if (isThereRoot) {
      ThreadPool::SecondWriteCreator secondWriteCreator;
      std::string *resultString =
          new std::string(std::to_string(sum) + ",BFS" + str);
      secondWriteCreator.addToQueue(
          queue, {*resultString, info.version, info.sockfd, 0});
    } else {
      Write::WriteError(
          queue, {std::string_view(""), info.version, info.sockfd, 1}, 1);
    }

  } catch (std::runtime_error &e) {
    Write::WriteError(queue,
                      {std::string_view(""), info.version, info.sockfd, 1}, 9);
  } catch (MatrixErrorCode &e) {
    Write::WriteError(queue,
                      {std::string_view(""), info.version, info.sockfd, 1}, 8);
  }
}