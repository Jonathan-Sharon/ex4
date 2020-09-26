#pragma once

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

    typedef enum
    {
        ERROR_SUCCESS,
        ERROR_NULL_POINTER,
        ZERO_ROW_OR_COLUMN,
        EXCEEDED_ROW_OR_COLUMN,
        ALLOCATION_PROBLEM,
        MATRIXES_SIZES_ARE_NOT_VALID,
        NOT_FOUND_IN_STRING
    } ErrorCode;

    /**
 * @brief Checks if a given error code indicates a success or not.
 *
 * @param[in] code the error code.
 * @return whether the error code indicates a success or not.
 */
    bool error_isSuccess(ErrorCode code);

    /**
 * @brief gets a textual error message for a given error code.
 *
 * @param[in] code the error code.
 * @return const char* the textual representation of the error code.
 */
    const char *error_getErrorMessage(ErrorCode code);

#ifdef __cplusplus
}
#endif