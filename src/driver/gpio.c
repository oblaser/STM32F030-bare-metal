/*
author          Oliver Blaser
date            27.12.2024
copyright       GPL-3.0 - Copyright (c) 2024 Oliver Blaser
*/

#include <stdint.h>

#include "gpio.h"

#include "stm32f0xx.h"


void GPIO_init()
{
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

    // BTN0
    // nop

    // LED0
    GPIOA->MODER |= (0x01 << GPIO_MODER_MODER8_Pos);
}
