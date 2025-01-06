/*
author          Oliver Blaser
date            06.01.2025
copyright       GPL-3.0 - Copyright (c) 2025 Oliver Blaser
*/

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "util.h"


int UTIL_strncmp(const char* lhs, const char* rhs, size_t count)
{
    int r = 0;

    for (size_t i = 0; i < count; ++i)
    {
        r = ((unsigned char)(*(lhs + i)) - (unsigned char)(*(rhs + i)));

        if (r != 0) { break; }
    }

    return r;
}

size_t UTIL_strcpy(char* dest, const char* src)
{
    size_t i = 0;

    while (*(src + i) != 0)
    {
        *(dest + i) = *(src + i);
        ++i;
    }

    *(dest + i) = 0;

    return i;
}

size_t UTIL_strncpy(char* dest, const char* src, size_t count)
{
    size_t i = 0;

    while ((*(src + i) != 0) && (i < count))
    {
        *(dest + i) = *(src + i);
        ++i;
    }

    *(dest + i) = 0;

    return i;
}

size_t UTIL_strlen(const char* str)
{
    size_t len = 0;
    while (*(str + len) != 0) { ++len; }
    return len;
}

size_t UTIL_strnlen(const char* str, size_t count)
{
    size_t len = 0;
    while ((*(str + len) != 0) && (len < count)) { ++len; }
    return len;
}
