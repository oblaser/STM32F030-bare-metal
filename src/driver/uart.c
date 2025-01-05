/*
author          Oliver Blaser
date            05.01.2025
copyright       GPL-3.0 - Copyright (c) 2025 Oliver Blaser
*/

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "uart.h"

#include <stm32f0xx.h>


#define UART(_h) ((USART_TypeDef*)((_h)->instance))

#define UART_HANDLE_INIT(_instance, _rxBufer)                                                                                                        \
    {                                                                                                                                                \
        .rxBufferSize = SIZEOF_ARRAY(_rxBufer), .rxCount = 0, .txCount = 0, .txIdx = 0, .instance = _instance, .rxBuffer = _rxBufer, .rxBusy = true, \
        .txBusy = false,                                                                                                                             \
    }
// end UART_HANDLE_INIT()


static uint8_t uart1_rxBuffer[50];
static UART_handle_t uart1 = UART_HANDLE_INIT(USART1, uart1_rxBuffer);


UART_handle_t* UART_com = &uart1;


void UART_init()
{
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    // select HSI as clock source
    RCC->CFGR3 &= ~RCC_CFGR3_USART1SW_Msk;
    RCC->CFGR3 |= RCC_CFGR3_USART1SW_HSI;

    // config USART1

    // Rx pin PA3

    // Tx pin PA2

    // enable USART1
}

void USART1_IRQHandler() {}
