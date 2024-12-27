/*
author          Oliver Blaser
date            27.12.2024
copyright       GPL-3.0 - Copyright (c) 2024 Oliver Blaser
*/

#include <stdint.h>

#include "driver/gpio.h"


int main()
{
    GPIO_init();

    while (1)
    {
#if 0
        if (GPIO_readPin(GPIO_BTN0)) { GPIO_setPin(GPIO_LED0); }
        else { GPIO_clrPin(GPIO_LED0); }
#else
        if (GPIO_readPin(GPIO_BTN0)) { GPIO_clrPin(GPIO_LED0); }
        else { GPIO_setPin(GPIO_LED0); }
#endif
    }

    return (-1);
}
