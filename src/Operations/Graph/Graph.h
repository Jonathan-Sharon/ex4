#pragma once

#include "../Matrix/Matrix.hpp"

#include "../../ThreadPool/ThreadPool.h"

#include <string_view>

namespace Graph {
struct Point {
  uint row;
  uint column;
};

class Graph {
public:
  explicit Graph(const std::string_view &str);

  uint getWidth() const;
  uint getHeight() const;

  uint getStartPointX() const;
  uint getStartPointY() const;

  uint getEndPointX() const;
  uint getEndPointY() const;

  double getValue(const uint row, const uint column) const;

  void setStartPoint(const uint row, const uint column);

private:
  const std::vector<double>
  getRowValue(const size_t rowStarts, const size_t rowEnds,
              const uint valuesToRead, const std::string_view &str,
              const bool enableZeroValues, const bool endOfString) const;
  Point m_startPoint;
  Point m_endPoint;
  Matrix m_matrix;
};
} // namespace Graph