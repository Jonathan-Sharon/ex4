#include "Graph.h"
#include "../../Read/Read.h"

#include <algorithm>
#include <iostream>
#include <string>

Graph::Graph::Graph(const std::string_view &str) : m_matrix(1, 1) {

  size_t firstEndOfRow = str.find("\r\n");
  if (firstEndOfRow == std::string::npos) {
    throw std::runtime_error("invalid graph given");
  }

  // get the matrix's sizes
  std::vector<double> matrixSizes{
      getRowValue(0, firstEndOfRow, 2, str, false, false)};
  uint32_t height = static_cast<uint32_t>(int(matrixSizes.at(0)));
  uint32_t width = static_cast<uint32_t>(int(matrixSizes.at(1)));

  // create the matrix
  this->m_matrix = Matrix(height, width);

  size_t lastRowEnds{firstEndOfRow};

  // read the string values and add them to the matrix
  for (uint32_t i = 0; i < height; ++i) {
    int column{0};
    size_t nextEndOfRow = str.find("\r\n", lastRowEnds + 2);
    if (nextEndOfRow == std::string::npos) {
      throw std::runtime_error("invalid graph given");
    }

    std::vector<double> rowValues{
        getRowValue(lastRowEnds + 2, nextEndOfRow, width, str, false, false)};
    std::for_each(rowValues.begin(), rowValues.end(),
                  [this, &column, &i](const double value) {
                    m_matrix.setValue(i, column, value);
                    ++column;
                  });
    lastRowEnds = nextEndOfRow;
  }

  // get the start point values
  size_t startPointEndOfRow = str.find("\r\n", lastRowEnds + 2);
  if (startPointEndOfRow == std::string::npos) {
    throw std::runtime_error("invalid graph given");
  }

  std::vector<double> startPointValues{
      getRowValue(lastRowEnds + 2, startPointEndOfRow, 2, str, true, false)};
  m_startPoint = {uint(startPointValues.at(0)), uint(startPointValues.at(1))};

  // get the end point values
  std::vector<double> endPointValues{
      getRowValue(startPointEndOfRow + 2, str.size(), 2, str, true, true)};

  m_endPoint = {uint(endPointValues.at(0)), uint(endPointValues.at(1))};

  // check if the values we were given are legal.
  if (m_startPoint.row >= m_matrix.getHeight() ||
      m_startPoint.column >= m_matrix.getWidth() ||
      m_endPoint.row >= m_matrix.getHeight() ||
      m_endPoint.column >= m_matrix.getWidth()) {
    throw std::runtime_error("invalid graph given");
  }
}

uint Graph::Graph::getWidth() const { return m_matrix.getWidth(); }

uint Graph::Graph::getHeight() const { return m_matrix.getHeight(); }

uint Graph::Graph::getStartPointX() const { return m_startPoint.row; }

uint Graph::Graph::getStartPointY() const { return m_startPoint.column; }

uint Graph::Graph::getEndPointX() const { return m_endPoint.row; }

uint Graph::Graph::getEndPointY() const { return m_endPoint.column; }

double Graph::Graph::getValue(const uint row, const uint column) const {
  return m_matrix.getValue(row, column);
}

void Graph::Graph::setStartPoint(const uint row, const uint column) {
  m_startPoint = {row, column};
}

const std::vector<double>
Graph::Graph::getRowValue(const size_t rowStarts, const size_t rowEnds,
                          const uint valuesToRead, const std::string_view &str,
                          const bool enableZeroValues,
                          const bool endOfString) const {

  size_t lastComma(rowStarts);
  std::vector<double> vector;

  for (uint i = 0; i < valuesToRead; ++i) {
    size_t nextComma;
    if (endOfString == true && i + 1 == valuesToRead) {
      nextComma = str.size();
    } else {
      nextComma = str.find_first_of(",\r\n", lastComma + 1);
    }

    if (nextComma == std::string::npos || nextComma > rowEnds) {
      throw std::runtime_error("invalid graph given");
    }

    std::string index = std::string(std::begin(str) + lastComma + int(i > 0),
                                    std::begin(str) + nextComma);
    if (index == "b" || index == "B") {
      vector.push_back(0);
      lastComma = nextComma;
      continue;
    }

    try {
      double value{std::stod(index)};
      if (value < 1 && (enableZeroValues == false ||
                        (enableZeroValues == true && value < 0))) {
        throw std::runtime_error("given invalid cell in the matrix");
      }

      vector.push_back(value);
    } catch (std::invalid_argument &e) {
      throw std::runtime_error("given invalid cell in the matrix");
    }

    lastComma = nextComma;
  }

  return vector;
}
