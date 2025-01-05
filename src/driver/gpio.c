/*
author          Oliver Blaser
date            05.01.2025
copyright       GPL-3.0 - Copyright (c) 2025 Oliver Blaser
*/

#include <stdint.h>

#include "gpio.h"

#include <stm32f0xx.h>


void GPIO_init()
{
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

    // BTN0
    // nop

    // LED red
    GPIOB->MODER |= (0x01 << GPIO_MODER_MODER3_Pos);

    // LED green
    GPIOB->MODER |= (0x01 << GPIO_MODER_MODER4_Pos);
}
