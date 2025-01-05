/*
author          Oliver Blaser
date            05.01.2025
copyright       GPL-3.0 - Copyright (c) 2025 Oliver Blaser
*/

#ifndef IG_DRIVER_CORE_H
#define IG_DRIVER_CORE_H


#ifdef __cplusplus
extern "C" {
#endif


// fixed
#define CORE_HSI (8000000) // 8MHz
#define CORE_HSE ()        // 4..32MHz

// configured in CORE_init()
#define CORE_SYSCLK (32000000) // 32MHz
#define CORE_HCLK   (32000000) // 32MHz
#define CORE_PCLK   (16000000) // 16MHz


void CORE_init();


#ifdef __cplusplus
}
#endif

#endif // IG_DRIVER_CORE_H
