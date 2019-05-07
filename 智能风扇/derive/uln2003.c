#include "uln2003.h"

//步进电机正反转数组1
u8 phasecw[8] ={0x09,0x01,0x03,0x02,0x06,0x04,0x0c,0x08};// DA-D-CD-C-BC-B-AB-A   
u8 phaseccw[8]={0x01,0x02,0x04,0x08,0x01,0x02,0x04,0x08};// A-AB-B-BC-C-CD-D-DA.
//步进电机28BYJ-48初始化
// IN4: PA3   d
// IN3: PA2   c
// IN2: PA1   b
// IN1: PA0   a
void moto_Init(void)
{

 GPIO_InitTypeDef GPIO_InitStructure;
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 ;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_Init(GPIOA,&GPIO_InitStructure);
 GPIO_ResetBits(GPIOA,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 );
}


void Delay_xms(u16 x)
{
 u16 i,j;
 for(i=0;i<x;i++)
  for(j=0;j<112;j++);
}

//
void motorcw(int speed)
{

	PAout(0)=1;PAout(1)=0;PAout(2)=0;PAout(3)=0;
	Delay_xms(speed);
	PAout(0)=0;PAout(1)=1;PAout(2)=0;PAout(3)=0;
	Delay_xms(speed);
	PAout(0)=0;PAout(1)=0;PAout(2)=1;PAout(3)=0;
	Delay_xms(speed);
	PAout(0)=0;PAout(1)=0;PAout(2)=0;PAout(3)=1;
	Delay_xms(speed);
	
}


void motorccw(int speed)  
{  
    uint8_t i;  
  
    for(i=0;i<8;i++)  
    {  
        GPIO_Write(GPIOA,phaseccw[i]);  
        Delay_xms(speed);  
    }  
}

void motor_angle(int angle,int speed)
{
	int i,j;
	j=(int)(angle*64/(5.625*8));
	if (angle>0)
	{
	for(i=0;i<j;i++)
	  {
		  motorccw(speed);
	  }
  }
	else if(angle<0)
	{
		for(i=0;i<-j;i++)
	  {
		  motorcw(speed);
	  }
	}	
}
