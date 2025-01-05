/*
author          Oliver Blaser
date            05.01.2025
copyright       GPL-3.0 - Copyright (c) 2025 Oliver Blaser
*/

#ifndef IG_DRIVER_COMMON_H
#define IG_DRIVER_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif


#ifndef BIT
#define BIT(n) (1u << (n))
#endif

#ifndef SIZEOF_ARRAY
#define SIZEOF_ARRAY(_array) (sizeof(_array) / sizeof(_array[0]))
#endif


#ifdef __cplusplus
}
#endif

#endif // IG_DRIVER_COMMON_H
