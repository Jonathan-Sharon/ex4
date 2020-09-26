#pragma once

#include "Matrix.h"
#include <cstdint>
using namespace std;
class Matrix {

public:
  /**
   * @brief Construct a new Matrix object.
   * return an exception if needed.
   *
   * @param height    get the Matrix's height
   * @param width     get thr Matrix's width
   */
  Matrix(std::uint32_t height, std::uint32_t width);

  /**
   * @brief Construct a new Matrix object. Copy Constructor.
   * return an exception if needed.
   *
   * @param other     the Matrix to be copied.
   */
  Matrix(const Matrix &other);

  /**
   * @brief Copy assignment operator.
   *
   * @param other the Matrix to be copied
   * @return      Matrix& the copied Matrix
   */
  Matrix &operator=(const Matrix &other);

  /**
   * @brief Construct a new Matrix object. Move contructor.
   *
   * @param other     the Matrix to be moved
   */
  Matrix(Matrix &&other) noexcept;

  /**
   * @brief Move assignment operator
   *
   * @param other the Matrix to be moved
   * @return      Matrix& the moved Matrix
   */
  Matrix &operator=(Matrix &&other) noexcept;

  /**
   * @brief Destroy the Matrix object
   *
   */
  ~Matrix();

  /**
   * @brief Returns the height of a given matrix.
   *
   * @param[in] matrix The matrix.
   * @param[out] result On output, contains the height of the matrix.
   */
  std::uint32_t getHeight() const;

  /**
   * @brief Returns the width of a give matrix.
   * return an exception if needed.
   *
   * @param[in] matrix The matrix.
   * @param[out] result On output, contains the height of the matrix.
   */
  std::uint32_t getWidth() const;

  /**
   * @brief Sets a value to the matrix.
   * return an exception if needed.
   *
   * @param[in, out] matrix The matrix to operate on.
   * @param[in] rowIndex Row index of the value to set.
   * @param[in] colIndex Column index of the value to setF.
   * @param[in] value Value to set.
   * @return ErrorCode
   */
  double getValue(uint32_t rowIndex, uint32_t colIndex) const;

  /**
   * @brief Sets a value to the matrix.
   * return an exception if needed.
   *
   * @param[in, out] matrix The matrix to operate on.
   * @param[in] rowIndex Row index of the value to set.
   * @param[in] colIndex Column index of the value to setF.
   * @param[in] value Value to set.
   * @return ErrorCode
   */
  void setValue(uint32_t rowIndex, uint32_t colIndex, double value);

  /**
   * @brief Computes the addition of two matrices.
   *
   * @param[out] result The address of a matrix pointer to receive
   *  the address of the resulting matrix.
   * @param[in] lhs The left hand side of the addition operation.
   * @param[in] rhs The right hand side of the addition operation.
   * @return ErrorCode
   */
  Matrix add(const Matrix &other) const;

  /**
   * @brief Computes the multiplication of two matrices.
   *
   * @param[out] result The address of a matrix pointer to receive
   *  the address of the resulting matrix.
   * @param[in] lhs The left hand side of the multiplication operation.
   * @param[in] rhs The right hand side of the multiplication operation.
   * @return ErrorCode
   */
  Matrix multiplyMatrices(const Matrix &other) const;

  /**
   * @brief Multiplies a matrix with a scalar and stores the result in
   *  the given matrix.
   *
   * @param[in, out] matrix On input, the matrix to multiply with a scalar.
   *  On output, the result of the multiplication operation.
   * @param[in] scalar The scalar to multiply with.
   * @return ErrorCode
   */
  void multiplyWithScalar(double scalar);

  /**
   * @brief similiar to get value.
   *
   * @param rowIndex Row index of the value to get
   * @param colIndex Column index of the value to get
   * @return double Value to get
   */
  double operator()(uint32_t rowIndex, uint32_t colIndex) const;

  /**
   * @brief similar to the add function.
   *
   * @param other the matrix to be added
   * @return Matrix the result matrix
   */
  Matrix operator+(const Matrix &other) const;

  /**
   * @brief similar to the muiltiplyWithMatrix function
   *
   * @param other the matrix to be multiplied
   * @return Matrix the result matrix
   */
  Matrix operator*(const Matrix &other) const;

  /**
   * @brief similar to multiplyWithScalar
   *
   * @param scalar the scalar we multiply by
   */
  void operator*(double scalar);

  /**
   * @brief rotate the Matrix
   *
   * @return Matrix the matrix to be rotated
   */
  Matrix rotate() const;

private:
  /**
   * @brief resets the matrix in order to be used again in the move contructor.
   *
   */
  void reset();
  PMatrix m_matrix;
};