#include "systick.h"
static uint8_t  fac_us=0;//us��ʱ������
static uint16_t fac_ms=0;//ms��ʱ������

//��ʼ��systick
void systick_config(void)
{
	
		SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);//systick��ʱ�ӹ̶�ΪHCLK��1/8
		fac_us=SystemCoreClock/8000000;//Ϊϵͳʱ�ӵ�1/8
		fac_ms=(uint16_t)fac_us*1000;//��ucos�£�����ÿ��ms��systickʱ����
}

//us����ʱ
void delay_us(uint32_t nus)
{
	uint32_t temp;
	SysTick->LOAD=nus*fac_us;//ʱ�����
	SysTick->VAL=0x00000;   //��ռ�����
	SysTick->CTRL|=1;//ʹ�ܶ�ʱ�� ��ʼ����
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&((temp&(1<<16))==0));//�鿴CTRL��16λ��COUNTFLAG��ֵ Ϊ1ʱʱ�䵽�� ��ȡһ�κ��Զ���λΪ0 ��λֵ0
	SysTick->CTRL=0; 				//ʧ�ܶ�ʱ��
	SysTick->VAL=0x000000;  //��ռ�����
}




//ms����ʱ
//������Ҫע���nms��ȡֵ��Χ
//SysTick->LOADΪ24λ�Ĵ��� ���������ʱΪ��nms<=0xFFFFFF*8*1000/sysclk
//sysclk��λΪHZ nms��λΪms
//��sysclk=72M�� nms<=1864  ��sysclk=48M�� nms<=2796
void delay_ms(uint16_t nms)
{
	uint32_t temp;
	SysTick->LOAD=nms*fac_ms;//ʱ�����
	SysTick->VAL=0x000000;   //��ռ�����
	SysTick->CTRL|=1;//ʹ�ܶ�ʱ�� ��ʼ����
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&((temp&(1<<16))==0));//�鿴CTRL��16λ��COUNTFLAG��ֵ Ϊ1ʱʱ�䵽�� ��ȡһ�κ��Զ���λΪ0 ��λֵ0
	SysTick->CTRL=0; 				//ʧ�ܶ�ʱ��
	SysTick->VAL=0x000000;  //��ռ�����
}
