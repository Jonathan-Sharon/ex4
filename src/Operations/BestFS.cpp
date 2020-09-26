#include "BestFS.h"

#include "Matrix/MatrixErrorCode.hpp"

#include <climits>
#include <queue>
#include <vector>

void Operate::BestFS::operate(ThreadPool::Queue &queue,
                              const ThreadPool::operateParameters info) const {
  try {
    Graph::Graph graph{info.readResult};
    std::string result{""};
    std::vector<std::vector<bool>> vector(
        graph.getHeight(), std::vector<bool>(graph.getWidth(), false));
    double sum{0};

    if (bestFirstSearch(graph, result, vector, sum)) {
      ThreadPool::SecondWriteCreator secondWriteCreator;
      std::string *resultString =
          new std::string(std::to_string(sum) + ",BestFS" + result);
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

bool Operate::BestFS::bestFirstSearch(Graph::Graph &graph, std::string &result,
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

  bool checkIfDone[4] = {false};

  while (true) {
    uint h{0}, f{UINT_MAX};
    std::string direction{""};

    if (checkIfDone[0] == false && startPointX + 1 < graph.getHeight() &&
        visit.at(startPointX + 1).at(startPointY) == false &&
        graph.getValue(startPointX + 1, startPointY) != 0) {

      h = graph.getValue(startPointX + 1, startPointY);
      if (sum + h < f) {
        f = sum + h;
        direction = ",Down";
      }
    }

    if (checkIfDone[1] == false && startPointY + 1 < graph.getWidth() &&
        visit.at(startPointX).at(startPointY + 1) == false &&
        graph.getValue(startPointX, startPointY + 1) != 0) {

      h = graph.getValue(startPointX, startPointY + 1);
      if (sum + h < f) {
        f = sum + h;
        direction = ",Right";
      }
    }

    if (checkIfDone[2] == false && int(startPointX - 1) >= 0 &&
        visit.at(startPointX - 1).at(startPointY) == false &&
        graph.getValue(startPointX - 1, startPointY) != 0) {

      h = graph.getValue(startPointX - 1, startPointY);
      if (sum + h < f) {
        f = sum + h;
        direction = ",Up";
      }
    }

    if (checkIfDone[3] == false && int(startPointY - 1) >= 0 &&
        visit.at(startPointX).at(startPointY - 1) == false &&
        graph.getValue(startPointX, startPointY - 1) != 0) {

      h = graph.getValue(startPointX, startPointY - 1);
      if (sum + h < f) {
        f = sum + h;
        direction = ",Left";
      }
    }

    if (direction.compare(",Down") == 0) {
      std::string tmp{result};
      result.append(direction);
      sum += graph.getValue(startPointX, startPointY);
      visit.at(startPointX).at(startPointY) = true;
      graph.setStartPoint(startPointX + 1, startPointY);
      if (bestFirstSearch(graph, result, visit, sum) == true) {
        return true;
      }

      result = tmp;
      sum -= graph.getValue(startPointX, startPointY);
      visit.at(startPointX).at(startPointY) = false;
      graph.setStartPoint(startPointX, startPointY);
      checkIfDone[0] = true;
      continue;
    }

    if (direction.compare(",Right") == 0) {
      std::string tmp{result};
      result.append(direction);
      sum += graph.getValue(startPointX, startPointY);
      visit.at(startPointX).at(startPointY) = true;
      graph.setStartPoint(startPointX, startPointY + 1);
      if (bestFirstSearch(graph, result, visit, sum) == true) {
        return true;
      }

      result = tmp;
      sum -= graph.getValue(startPointX, startPointY);
      visit.at(startPointX).at(startPointY) = false;
      graph.setStartPoint(startPointX, startPointY);
      checkIfDone[1] = true;
      continue;
    }

    if (direction.compare(",Up") == 0) {
      std::string tmp{result};
      result.append(direction);
      sum += graph.getValue(startPointX, startPointY);
      visit.at(startPointX).at(startPointY) = true;
      graph.setStartPoint(startPointX - 1, startPointY);
      if (bestFirstSearch(graph, result, visit, sum) == true) {
        return true;
      }

      result = tmp;
      sum -= graph.getValue(startPointX, startPointY);
      visit.at(startPointX).at(startPointY) = false;
      graph.setStartPoint(startPointX, startPointY);
      checkIfDone[2] = true;
      continue;
    }

    if (direction.compare(",Left") == 0) {
      std::string tmp{result};
      result.append(direction);
      sum += graph.getValue(startPointX, startPointY);
      visit.at(startPointX).at(startPointY) = true;
      graph.setStartPoint(startPointX, startPointY - 1);
      if (bestFirstSearch(graph, result, visit, sum) == true) {
        return true;
      }

      result = tmp;
      sum -= graph.getValue(startPointX, startPointY);
      visit.at(startPointX).at(startPointY) = false;
      graph.setStartPoint(startPointX, startPointY);
      checkIfDone[3] = true;
      continue;
    }

    return false;
  }
}