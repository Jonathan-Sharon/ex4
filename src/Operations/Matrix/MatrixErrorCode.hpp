#pragma once

#include "ErrorCode.h"
#include <exception>

class MatrixErrorCode : public std::exception {

private:
  ErrorCode m_err;

public:
  /**
   * @brief Construct a new Matrix Error Code object
   *
   * @param err the ErrorCode error
   */
  MatrixErrorCode(ErrorCode err);

  /**
   * @brief get a description about the error
   *
   * @return const char* the error
   */
  const char *what() const noexcept;
};