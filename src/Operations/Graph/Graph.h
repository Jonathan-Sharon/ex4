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
  /**
   * @brief Construct a new Graph object
   *
   * @param str the string to read and turn to Graph
   */
  explicit Graph(const std::string_view &str);

  /**
   * @brief Get the Width object
   *
   * @return uint the Graph's width
   */
  uint getWidth() const;

  /**
   * @brief Get the Height object
   *
   * @return uint the Graph's height
   */
  uint getHeight() const;

  /**
   * @brief Get the Start Point X object
   *
   * @return uint the Start point X
   */
  uint getStartPointX() const;

  /**
   * @brief Get the Start Point Y object
   *
   * @return uint the Start point Y
   */
  uint getStartPointY() const;

  /**
   * @brief Get the End Point X object
   *
   * @return uint  the End point X
   */
  uint getEndPointX() const;

  /**
   * @brief Get the End Point Y object
   *
   * @return uint
   */
  uint getEndPointY() const;

  /**
   * @brief Get the Value object
   *
   * @param row the row to read
   * @param column the colimn to write
   * @return double
   */
  double getValue(const uint row, const uint column) const;

  /**
   * @brief Set the Start Point object
   *
   * @param row the row to set the start point
   * @param column the column to set the start point
   */
  void setStartPoint(const uint row, const uint column);

private:
  /**
   * @brief Get the Row Value objects
   *
   * @param rowStarts where the row start
   * @param rowEnds where the row ends
   * @param valuesToRead number of values to read
   * @param str the string to read from
   * @param enableZeroValues is it legel to read zero values
   * @param endOfString is the "rowEnds" variable is the end of the string
   * @return const std::vector<double>
   */
  const std::vector<double>
  getRowValue(const size_t rowStarts, const size_t rowEnds,
              const uint valuesToRead, const std::string_view &str,
              const bool enableZeroValues, const bool endOfString) const;
  Point m_startPoint;
  Point m_endPoint;
  Matrix m_matrix;
};
} // namespace Graph