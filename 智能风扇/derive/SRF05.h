#ifndef __SRF05_H
#define __SRF05_H



#include "stm32f10x.h"
#include "systick.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_exti.h"

#define  SRF05_TRIG_GPIOB GPIO_Pin_12
#define  SRF05_ECHO_GPIOB GPIO_Pin_13


void SRF05_Init(void);
void SRF05_NVIC(void);
u32 GetEchoTimer(void);
float SRF05GetLength(void );

#endif
