/*
author          Oliver Blaser
date            05.01.2025
copyright       GPL-3.0 - Copyright (c) 2025 Oliver Blaser
*/

#ifndef IG_DRIVER_GPIO_H
#define IG_DRIVER_GPIO_H

#include <stdint.h>

#include "bits/macros.h"

#include <stm32f0xx.h>

#ifdef __cplusplus
extern "C" {
#endif


#define GPIO_BTN0   GPIOB, 1
#define GPIO_LED_rd GPIOB, 3
#define GPIO_LED_gn GPIOB, 4


void GPIO_init();

static inline uint32_t GPIO_read(const GPIO_TypeDef* port) { return (port->IDR); }

static inline void GPIO_write(GPIO_TypeDef* port, uint32_t value) { port->ODR = value; }

static inline void GPIO_set(GPIO_TypeDef* port, uint32_t mask) { port->BSRR = mask; }

static inline void GPIO_clr(GPIO_TypeDef* port, uint32_t mask) { port->BRR = mask; }

static inline int GPIO_readPin(const GPIO_TypeDef* port, uint8_t pin) { return ((port->IDR) & BIT(pin)); }

static inline void GPIO_writePin(GPIO_TypeDef* port, uint8_t pin, int state)
{
    if (state) { port->BSRR = BIT(pin); }
    else { port->BRR = BIT(pin); }
}

static inline void GPIO_setPin(GPIO_TypeDef* port, uint8_t pin) { port->BSRR = BIT(pin); }

static inline void GPIO_clrPin(GPIO_TypeDef* port, uint8_t pin) { port->BRR = BIT(pin); }

static inline void GPIO_togglePin(GPIO_TypeDef* port, uint8_t pin)
{
    if ((port->ODR) & BIT(pin)) { port->BRR = BIT(pin); }
    else { port->BSRR = BIT(pin); }
}


#ifdef __cplusplus
}
#endif

#endif // IG_DRIVER_GPIO_H
