#ifndef _LED_H
#define _LED_H

#include "main.h"

#define LED_BLU_OFF()  (GPIOB->BRR |= GPIO_Pin_12)
#define LED_BLU_ON()  (GPIOB->BSRR |= GPIO_Pin_12)

#define LED_BLU_TOGGLE() (GPIOB->ODR &= ~(GPIOB->ODR&GPIO_Pin_12))

void ledConfig(void);
#endif

