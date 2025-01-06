/*
author          Oliver Blaser
date            06.01.2025
copyright       GPL-3.0 - Copyright (c) 2025 Oliver Blaser
*/

#ifndef IG_MIDDLEWARE_UTIL_H
#define IG_MIDDLEWARE_UTIL_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif



/*!
\defgroup grp_utility Utilities Library
`#include "middleware/util.h"`
*/

/*! \addtogroup grp_utility
 * @{
 */

#ifndef SIZEOF_ARRAY
#define SIZEOF_ARRAY(_array) (sizeof(_array) / sizeof(_array[0]))
#endif

/*! @} */



/*!
\defgroup grp_utility_string Strings Library
\ingroup grp_utility
`#include "middleware/util.h"`

Minimalistic string library implementation, with no argument checks.
*/

/*! \addtogroup grp_utility_string
 * @{
 */

/**
 * @brief Compares at most `count` characters of two possibly null terminated arrays.
 *
 * @retval Negative if `lhs` appears before `rhs` in lexicographical order
 * @retval Zero if `lhs` and `rhs` compare equal, or if `count` is zero.
 * @retval Positive value if `lhs` appears after `rhs` in lexicographical order.
 */
int UTIL_strncmp(const char* lhs, const char* rhs, size_t count);

static inline bool UTIL_strneq(const char* lhs, const char* rhs, size_t count) { return (UTIL_strncmp(lhs, rhs, count) == 0); }

/**
 * @brief Copies `src` to `dest` and appends a null terminator.
 *
 * @return Number of chars copied to `dest` (not including the null terminator)
 */
size_t UTIL_strcpy(char* dest, const char* src);

/**
 * @brief Copies at most `count` chars (not including the null terminator) of `src` to `dest` and appends a null terminator.
 *
 * @return Number of chars copied to `dest` (not including the null terminator)
 */
size_t UTIL_strncpy(char* dest, const char* src, size_t count);

size_t UTIL_strlen(const char* str);
size_t UTIL_strnlen(const char* str, size_t count);

/*! @} */



#ifdef __cplusplus
}
#endif

#endif // IG_MIDDLEWARE_UTIL_H
