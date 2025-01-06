/*
author          Oliver Blaser
date            06.01.2025
copyright       GPL-3.0 - Copyright (c) 2025 Oliver Blaser
*/

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "app.h"
#include "driver/gpio.h"
#include "driver/uart.h"
#include "middleware/util.h"



static uint16_t tmr_led = 0;


static void handleCommand(const char* cmd);


void APP_task()
{
    static bool btn_pos = false;
    static bool btn_neg = false;
    static bool btn_old = false;

    const bool btn_state = (GPIO_readPin(GPIO_BTN0) != 0);
    btn_pos = !btn_old && btn_state;
    btn_neg = btn_old && !btn_state;
    btn_old = btn_state;



    if (btn_pos)
    {
        UART_print(UART_com, "button pressed\n");
        GPIO_togglePin(GPIO_LED_rd);
    }

    if (btn_neg) { UART_print(UART_com, "button released\n"); }



    if (tmr_led == 0)
    {
        tmr_led = 50;

        GPIO_togglePin(GPIO_LED_gn);
    }



    if (!UART_com->rxBusy)
    {
        if (UART_com->rxCount <= UART_com->rxBufferSize)
        {
#if 0 // echo
            UART_write(UART_com, UART_com->rxBuffer, UART_com->rxCount);
#else
            handleCommand((const char*)(UART_com->rxBuffer));
#endif
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
}

void APP_softTimeHandler_10ms()
{
    if (tmr_led) { --tmr_led; }
}



void handleCommand(const char* cmd)
{
    char ans[30];

    if (UTIL_strneq(cmd, "get-led\n", 8))
    {
        UTIL_strcpy(ans, "led;0;0\n");
        if (GPIO_readPin(GPIO_LED_rd)) { ans[4] = '1'; }
        if (GPIO_readPin(GPIO_LED_gn)) { ans[6] = '1'; }
    }
    else if (UTIL_strneq(cmd, "set-led;rd;", 11) && (cmd[12] == '\n'))
    {
        if ((cmd[11] == '0')) { GPIO_clrPin(GPIO_LED_rd); }
        else { GPIO_setPin(GPIO_LED_rd); }

        UTIL_strcpy(ans, "OK\n");
    }
    else { UTIL_strcpy(ans, "ERROR unknown command\n"); }

    UART_print(UART_com, ans);
}
