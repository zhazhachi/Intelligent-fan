#ifndef __MG996R_H
#define __MG996R_H


#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include "main.h"

void pwm_config(void);
void turnRight(u8 x,u8 n);
void turnLeft(u8 x,u8 n);

#endif
