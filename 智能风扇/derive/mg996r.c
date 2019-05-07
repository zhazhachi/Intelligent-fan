#include "mg996r.h"


void pwm_config(void)
{
	 GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);// 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  //ʹ��GPIO����ʱ��ʹ��
	                                                                     	

   //���ø�����Ϊ�����������,���TIM1 CH1��PWM���岨��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //TIM_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//���ø�����Ϊ�����������,���TIM1 CH4��PWM���岨��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; //TIM_CH4
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	

	
	TIM_TimeBaseStructure.TIM_Period = 2999; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 80K
	TIM_TimeBaseStructure.TIM_Prescaler =71; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx

  TIM_CtrlPWMOutputs(TIM1,ENABLE);	//MOE �����ʹ��	

	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH1Ԥװ��ʹ��	 
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH4Ԥװ��ʹ��	 
	
	TIM_ARRPreloadConfig(TIM1, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
	
	TIM_Cmd(TIM1, ENABLE);  //ʹ��TIM1
}

//n���������ϣ�תx��  n=0or1(x��or y�ᣩ
void turnLeft(u8 x,u8 n)
{
	int temp;
//һ��PWM����Ϊ3ms,���ֵΪ3000
//(jiaodutemp+1)/3000*3ms=0.5ms+0.008*(jiaodu/0.74)
//jiaodutemp=499+10.811*jiaodu
	if(n)
		{
			angle_y=angle_y+x;
			if(angle_y>160)angle_y=160;//���y��������160��
			temp=499+10.811*angle_y;
			TIM_SetCompare4(TIM1,temp);
		}
	else
	{
			angle_x=angle_x+x;
			if(angle_x>180)angle_x=180;//������ܳ���180��
			temp=499+10.811*angle_x;
			TIM_SetCompare1(TIM1,temp);
	}

}	

//n�������ң��£�תx��  n=0or1(x��or y�ᣩ
void turnRight(u8 x,u8 n)
{
	int temp;
//һ��PWM����Ϊ3ms,���ֵΪ3000
//(jiaodutemp+1)/3000*3ms=0.5ms+0.008*(jiaodu/0.74)
//jiaodutemp=499+10.811*jiaodu
		if(n)
		{
			if(angle_y<x)angle_y=0;//������ܳ���0��
			else angle_y=angle_y-x;
			temp=499+10.811*angle_y;
			TIM_SetCompare4(TIM1,temp);
		}
		else
		{
			if(angle_x<x)angle_x=0;//������ܳ���0��
			else angle_x=angle_x-x;
			temp=499+10.811*angle_x;
			TIM_SetCompare1(TIM1,temp);
		}	
}	
