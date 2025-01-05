/*
author          Oliver Blaser
date            05.01.2025
copyright       GPL-3.0 - Copyright (c) 2025 Oliver Blaser
*/

#ifndef IG_DRIVER_UART_H
#define IG_DRIVER_UART_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct
{
    const size_t rxBufferSize;
    size_t rxCount;
    size_t txCount;
    size_t txIdx;

    void* const instance;
    const uint8_t* const rxBuffer;

    bool rxBusy;
    bool txBusy;

} UART_handle_t;


extern UART_handle_t* UART_com;


void UART_init();

int UART_write(UART_handle_t* h, const uint8_t* data, size_t count);
void UART_write_block(UART_handle_t* h, const uint8_t* data, size_t count);

int UART_print(UART_handle_t* h, const char* str);
void UART_print_block(UART_handle_t* h, const char* str);

void UART_rxDataRead(UART_handle_t* h);


#ifdef __cplusplus
}
#endif

#endif // IG_DRIVER_UART_H
