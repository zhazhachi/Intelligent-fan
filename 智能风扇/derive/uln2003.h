#ifndef __ULN2003_H
#define __ULN2003_H


#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "systick.h"
#include "sys.h"


void Delay_xms(u16 x);

void motorcw(int speed);
void motorccw(int speed) ;
void moto_Init(void);
void motor_angle(int angle,int speed);

#endif



