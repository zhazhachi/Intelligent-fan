#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "stm32f10x.h"

void systick_config(void);
void delay_us(uint32_t nus);
void delay_ms(uint16_t nms);
#endif
