#include "DFS.h"

#include "Matrix/MatrixErrorCode.hpp"

#include <vector>

void Operate::DFS::operate(ThreadPool::Queue &queue,
                           const ThreadPool::operateParameters info) const {

  try {
    Graph::Graph graph{info.readResult};
    std::vector<std::vector<bool>> vector(
        graph.getHeight(), std::vector<bool>(graph.getWidth(), false));
    std::string result{""};
    double sum{0};

    if (dfs(graph, result, vector, sum)) {
      ThreadPool::SecondWriteCreator secondWriteCreator;
      std::string *resultString =
          new std::string(std::to_string(sum) + ",DFS" + result);
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

bool Operate::DFS::dfs(Graph::Graph &graph, std::string &result,
                       std::vector<std::vector<bool>> &visit,
                       double &sum) const {

  uint startPointX = graph.getStartPointX();
  uint startPointY = graph.getStartPointY();
  uint endPointX = graph.getEndPointX();
  uint endPointY = graph.getEndPointY();

  if (startPointX == endPointX && startPointY == endPointY) {
    if (sum == 0) {
      return true;
    } else {
      sum += graph.getValue(startPointX, startPointY);
      return true;
    }
  }

  if (visit.at(startPointX).at(startPointY) == false &&
      startPointX + 1 < graph.getHeight() &&
      graph.getValue(startPointX + 1, startPointY) != 0) {

    visit.at(startPointX).at(startPointY) = true;
    sum += graph.getValue(startPointX, startPointY);
    result.append(",Down");

    graph.setStartPoint(startPointX + 1, startPointY);
    if (dfs(graph, result, visit, sum) == true) {
      return true;
    }
  }

  if (visit.at(startPointX).at(startPointY) == false &&
      startPointY + 1 < graph.getWidth() &&
      graph.getValue(startPointX, startPointY + 1) != 0) {

    visit.at(startPointX).at(startPointY) = true;
    sum += graph.getValue(startPointX, startPointY);
    result.append(",Right");

    graph.setStartPoint(startPointX, startPointY + 1);
    if (dfs(graph, result, visit, sum) == true) {
      return true;
    }
  }

  if (visit.at(startPointX).at(startPointY) == false &&
      int(startPointX - 1) >= 0 &&
      graph.getValue(startPointX - 1, startPointY) != 0) {

    visit.at(startPointX).at(startPointY) = true;
    sum += graph.getValue(startPointX, startPointY);
    result.append(",Up");

    graph.setStartPoint(startPointX - 1, startPointY);
    if (dfs(graph, result, visit, sum) == true) {
      return true;
    }
  }

  if (visit.at(startPointX).at(startPointY) == false &&
      int(startPointY - 1) >= 0 &&
      graph.getValue(startPointX, startPointY - 1) != 0) {

    visit.at(startPointX).at(startPointY) = true;
    sum += graph.getValue(startPointX, startPointY);
    result.append(",Left");

    graph.setStartPoint(startPointX, startPointY - 1);
    if (dfs(graph, result, visit, sum) == true) {
      return true;
    }
  }

  return false;
}
