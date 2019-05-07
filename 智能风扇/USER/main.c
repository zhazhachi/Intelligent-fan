#include "main.h"
volatile u8 angle_x=90;
volatile u8 angle_y=90;

int distance=0;


/*********Ӳ��������鿴readme.txt*********/

short  temperature=0;
u8 arr[5]={0xAA,0x00,0x00,0x00,0x0D};
int main(void)
{

	
	sysclk_config();//ʱ������
  systick_config();//�δ�delay��ʼ��
	usart_config(9600);//����1���ó�ʼ��
	pwm_config();//���pwm����س�ʼ��
	SRF05_Init();//����������ʼ��
	usart2_config(9600);//������������ư��ṩ������Ϣ
	
	delay_ms(1000);//��mcuһ��ʱ��
	
	//DS18B20��ʼ��
	 	while(DS18B20_Init())		
	{
		arr[3]=0xFF;
		arr[2]=0xFF;
		sendArrByte(arr);//Э��������鿴readme.txt
		delay_ms(400);
	}
	/******����ר��********/
	
	hongwai_Init();
	
	
	/******����ר��********/
	//����Լ츴λ
	TIM_SetCompare1(TIM1,1450);
	delay_ms(2000);
	turnLeft(90,0); //�ص�0��λ��
	delay_ms(3000);
	turnRight(180,0); //�ص�180��λ��
	delay_ms(5000);
	turnLeft(90,0); //�ص�90��λ��
	delay_ms(3000);
	TIM_SetCompare4(TIM1,1450);
	delay_ms(2000);
	turnLeft(90,1); //�ص�0��λ��
	delay_ms(3000);
	turnRight(180,1); //�ص�180��λ��
	delay_ms(5000);
	turnLeft(30,1); //�ص�30��λ��  �����ǰ��
	delay_ms(3000);

	
	while(1)
	{

		temperature=DS18B20_Get_Temp();	
		arr[3]=temperature&0x00FF;
		arr[2]=(temperature>>8)&0x00FF;
		sendArrByte(arr);
		distance=SRF05GetLength();
		if(distance>250)distance=250;
		USART_SendData(USART2,distance);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
		delay_ms(2500);
		
		

//	//	printf("�¶�Ϊ��%0.1f",temperature/10.0);	//��ʾ�¶Ȳ���

	}
//	while(1)
//	{
//     if(PCin(14)==0)PCout(13)=0;
//		 else PCout(13)=1;
//  		delay_ms(100);
//			
//		
//	}

	

//	
//	while(1)
//	{	    	    
//							  
//		temperature=DS18B20_Get_Temp();	
//		arr[3]=temperature&0x00FF;
//		arr[2]=(temperature>>8)&0x00FF;
//		sendArrByte(arr);
//	//	printf("�¶�Ϊ��%0.1f",temperature/10.0);	//��ʾ�¶Ȳ���
//		delay_ms(500);
//		

//	}
//		while(1)
//	{	
//		
//		
////	     TIM_SetCompare1(TIM1,499); 
////     delay_ms(5000); 

////    TIM_SetCompare1(TIM1,2444); 

////     delay_ms(5000);
//  }
}









