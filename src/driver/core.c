/*
author          Oliver Blaser
date            05.01.2025
copyright       GPL-3.0 - Copyright (c) 2025 Oliver Blaser
*/

#include <stdint.h>

#include "core.h"

#include <stm32f0xx.h>


void CORE_init()
{
    // init flash controller for higher clock frequencies
    FLASH->ACR = FLASH_ACR_PRFTBE | (0x01 << FLASH_ACR_LATENCY_Pos);



    // init clocks to achieve the desired clock frequencies defined in the header file
    RCC->CFGR |= RCC_CFGR_PLLMUL8 | RCC_CFGR_PLLSRC_HSI_DIV2 | RCC_CFGR_PPRE_2 | RCC_CFGR_HPRE_DIV1; // PLL = HSI/2 x8 ; HPRE = /1 ; PPRE = /2
    RCC->CR |= RCC_CR_PLLON;
    while (!(RCC->CR & RCC_CR_PLLRDY)) { __NOP(); }
    RCC->CFGR |= RCC_CFGR_SW_PLL;



    // init SysTick timer
    SysTick_Config(CORE_HCLK / 100); // 10ms
    NVIC_SetPriority(SysTick_IRQn, 0);



#if 0  // MCO
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

    GPIOA->AFR[1] &= ~GPIO_AFRH_AFSEL8_Msk;
    GPIOA->MODER |= (0x02 << GPIO_MODER_MODER8_Pos);
    GPIOA->OSPEEDR |= (0x03 << GPIO_OSPEEDR_OSPEEDR8_Pos);

    RCC->CFGR |= RCC_CFGR_MCOPRE_DIV2 | RCC_CFGR_MCO_SYSCLK;
#endif // MCO
}
