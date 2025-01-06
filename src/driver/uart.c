/*
author          Oliver Blaser
date            05.01.2025
copyright       GPL-3.0 - Copyright (c) 2025 Oliver Blaser
*/

/*
    basic interrupt driven (no DMA) rx/tx
*/

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "common.h"
#include "uart.h"

#include <stm32f0xx.h>


#define UART(_h) ((USART_TypeDef*)((_h)->peripheral))

#define UART_HANDLE_INIT(_peripheral, _rxBuffer, _txBuffer)                                                                                   \
    {                                                                                                                                         \
        .rxBufferSize = SIZEOF_ARRAY(_rxBuffer), .rxCount = 0, .rxIdx = 0, .txBufferSize = SIZEOF_ARRAY(_txBuffer), .txCount = 0, .txIdx = 0, \
        .peripheral = _peripheral, .rxBuffer = _rxBuffer, .txBuffer = _txBuffer, .rxBusy = true, .txBusy = false,                             \
    }
// end UART_HANDLE_INIT()


static uint8_t uart1_rxBuffer[30];
static uint8_t uart1_txBuffer[30];
static UART_handle_t uart1 = UART_HANDLE_INIT(USART1, uart1_rxBuffer, uart1_txBuffer);


// logical mapping of the peripheral instance
UART_handle_t* UART_com = &uart1;


void UART_init()
{
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

    // select HSI as clock source
    RCC->CFGR3 &= ~RCC_CFGR3_USART1SW_Msk;
    RCC->CFGR3 |= RCC_CFGR3_USART1SW_HSI;



    // USART1 pins: Rx PA3, Tx PA2
    GPIOA->MODER |= (0x02 << GPIO_MODER_MODER3_Pos) | (0x02 << GPIO_MODER_MODER2_Pos);
    GPIOA->PUPDR |= (0x01 << GPIO_PUPDR_PUPDR3_Pos); // enable pull up for Rx pin
    GPIOA->AFR[0] |= (0x01 << GPIO_AFRL_AFRL3_Pos) | (0x01 << GPIO_AFRL_AFRL2_Pos);

    // config USART1
    USART1->CR1 = USART_CR1_TE | USART_CR1_RE; // oversampling x16 ; 8Nx ; enable Tx and Rx
    USART1->CR2 = 0;                           // 1 stop bit
    USART1->CR3 = USART_CR3_OVRDIS;            // disable overrun error detection
    USART1->BRR = 69;                          // 8MHz / 69 = 115942bps (115200 +0.64%)
    NVIC_SetPriority(USART1_IRQn, 1);

    // enable USART1
    USART1->CR1 |= USART_CR1_RXNEIE | USART_CR1_UE;
    NVIC_EnableIRQ(USART1_IRQn);
}

int UART_write(UART_handle_t* h, const uint8_t* data, size_t count)
{
    if (h->txBusy) { return UART_EBUSY; }
    if (count > h->txBufferSize) { return UART_ESIZE; }

    uart1.txBusy = true;
    h->txIdx = 0;

    for (h->txCount = 0; h->txCount < count; ++(h->txCount)) { h->txBuffer[h->txCount] = data[h->txCount]; }

    UART(h)->TDR = h->txBuffer[h->txIdx];
    ++(h->txIdx);

    UART(h)->CR1 = UART(h)->CR1 | USART_CR1_TXEIE;

    return 0;
}

int UART_write_block(UART_handle_t* h, const uint8_t* data, size_t count)
{
    while (h->txBusy) { __NOP(); }
    return UART_write(h, data, count);
}

int UART_print(UART_handle_t* h, const char* str)
{
    size_t len = 0;
    while (*(str + len) != 0) { ++len; }

    return UART_write(h, (const uint8_t*)str, len);
}

int UART_print_block(UART_handle_t* h, const char* str)
{
    while (h->txBusy) { __NOP(); }
    return UART_print(h, str);
}

void UART_rxDataRead(UART_handle_t* h)
{
    h->rxCount = 0;
    h->rxIdx = 0;
    h->rxBusy = true;

    UART(h)->CR1 |= USART_CR1_RXNEIE;
}

void UART_awaitTxDone(const UART_handle_t* h)
{
    while (h->txBusy) { __NOP(); }
}



void USART1_IRQHandler()
{
    if (USART1->ISR & USART_ISR_RXNE)
    {
        ++(uart1.rxCount);

        const uint8_t rxByte = (uint8_t)(USART1->RDR);
        uart1_rxBuffer[uart1.rxIdx] = rxByte;

        if (uart1.rxIdx < (SIZEOF_ARRAY(uart1_rxBuffer) - 1)) { ++(uart1.rxIdx); }

        if (rxByte == '\n')
        {
            USART1->CR1 &= ~USART_CR1_RXNEIE;
            uart1.rxBusy = false;
        }
    }

    if (USART1->ISR & USART_ISR_TXE)
    {
        if (uart1.txIdx >= uart1.txCount)
        {
            USART1->CR1 &= ~USART_CR1_TXEIE;
            uart1.txBusy = false;
        }
        else
        {
            USART1->TDR = uart1_txBuffer[uart1.txIdx];
            ++uart1.txIdx;
        }
    }
}
