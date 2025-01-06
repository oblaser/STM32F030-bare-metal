/*
author          Oliver Blaser
date            05.01.2025
copyright       GPL-3.0 - Copyright (c) 2025 Oliver Blaser
*/

#include <stdint.h>

#include "driver/core.h"
#include "driver/gpio.h"
#include "driver/uart.h"


uint64_t tNow_upt_ms = 0;


int main()
{
    CORE_init();
    GPIO_init();
    UART_init();

    UART_print_block(UART_com, "\n====================\n");
    UART_print_block(UART_com, "started\n");
    UART_awaitTxDone(UART_com);

    while (1)
    {
        if (!UART_com->rxBusy)
        {
            if (UART_com->rxCount <= UART_com->rxBufferSize)
            {
                // echo
                UART_write(UART_com, UART_com->rxBuffer, UART_com->rxCount);
            }
            else
            {
                UART_print(UART_com, "ERROR rx buffer overflow\n");
                UART_print_block(UART_com, "\\ data: ");
                UART_write_block(UART_com, UART_com->rxBuffer, UART_com->rxBufferSize);
                UART_print_block(UART_com, "\n");
            }

            UART_rxDataRead(UART_com);
        }

        if (GPIO_readPin(GPIO_BTN0)) { GPIO_setPin(GPIO_LED_rd); }
        else { GPIO_clrPin(GPIO_LED_rd); }

        static uint64_t tLed = 0;
        if ((tNow_upt_ms - tLed) >= 500)
        {
            tLed = tNow_upt_ms;

            static int x = 0;
            if (x)
            {
                GPIO_clrPin(GPIO_LED_gn);
                x = 0;
            }
            else
            {
                GPIO_setPin(GPIO_LED_gn);
                x = 1;
            }
        }
    }

    return (-1);
}



void SysTick_Handler()
{
    tNow_upt_ms += 10;

    // ...
}
