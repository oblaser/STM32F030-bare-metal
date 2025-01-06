/*
author          Oliver Blaser
date            05.01.2025
copyright       GPL-3.0 - Copyright (c) 2025 Oliver Blaser
*/

#include <stdint.h>

#include "application/app.h"
#include "driver/core.h"
#include "driver/gpio.h"
#include "driver/uart.h"


uint64_t tNow_upt_ms = 0;

static uint64_t tSoftTimeHandler = 0;


int main()
{
    CORE_init();
    GPIO_init();
    UART_init();

    UART_print_block(UART_com, "\n  --====# started #====--  \n");
    UART_awaitTxDone(UART_com);

    while (1)
    {
        APP_task();

        if ((tNow_upt_ms - tSoftTimeHandler) >= 10)
        {
            tSoftTimeHandler = tNow_upt_ms;

            APP_softTimeHandler_10ms();
        }
    }

    return (-1);
}



void SysTick_Handler()
{
    tNow_upt_ms += 10;

    // precise timers
    // if (tmr_xyz) { --tmr_xyz; }
}
