#ifndef __USART_H
#define __USART_H


#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_gpio.h"
#include <stdio.h>
#include "mg996r.h"


#define USART_bufLength 5 //定义最大接收字节数
#define USART_RX_start  0xAA //数据包开头
#define USART_RX_end  0x0D //数据包开头




extern u8 USART_RX_state;  //接收状态标志和已接收字节数
extern u8 sensitivity;  //单次控制舵机转向角度（灵敏度） 自动模式下为0
extern u8 FAN_mode;



void usart2_config(uint32_t bt);
void usart_config(uint32_t bt);
void sendArrByte(u8* arr);
void sendAByte(u8 data);
int fputc(int ch, FILE *f);
int fgetc(FILE *f);

#endif
 

