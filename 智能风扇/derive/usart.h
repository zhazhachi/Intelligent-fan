#ifndef __USART_H
#define __USART_H


#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_gpio.h"
#include <stdio.h>
#include "mg996r.h"


#define USART_bufLength 5 //�����������ֽ���
#define USART_RX_start  0xAA //���ݰ���ͷ
#define USART_RX_end  0x0D //���ݰ���ͷ




extern u8 USART_RX_state;  //����״̬��־���ѽ����ֽ���
extern u8 sensitivity;  //���ο��ƶ��ת��Ƕȣ������ȣ� �Զ�ģʽ��Ϊ0
extern u8 FAN_mode;



void usart2_config(uint32_t bt);
void usart_config(uint32_t bt);
void sendArrByte(u8* arr);
void sendAByte(u8 data);
int fputc(int ch, FILE *f);
int fgetc(FILE *f);

#endif
 

