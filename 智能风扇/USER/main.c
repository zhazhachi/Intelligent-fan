#include "main.h"
volatile u8 angle_x=90;
volatile u8 angle_y=90;

int distance=0;


/*********硬件接线请查看readme.txt*********/

short  temperature=0;
u8 arr[5]={0xAA,0x00,0x00,0x00,0x0D};
int main(void)
{

	
	sysclk_config();//时钟配置
  systick_config();//滴答delay初始化
	usart_config(9600);//串口1设置初始化
	pwm_config();//舵机pwm及相关初始化
	SRF05_Init();//超声波测距初始化
	usart2_config(9600);//用来给电机控制板提供距离信息
	
	delay_ms(1000);//给mcu一点时间
	
	//DS18B20初始化
	 	while(DS18B20_Init())		
	{
		arr[3]=0xFF;
		arr[2]=0xFF;
		sendArrByte(arr);//协议详情请查看readme.txt
		delay_ms(400);
	}
	/******测试专区********/
	
	hongwai_Init();
	
	
	/******测试专区********/
	//舵机自检复位
	TIM_SetCompare1(TIM1,1450);
	delay_ms(2000);
	turnLeft(90,0); //回到0度位置
	delay_ms(3000);
	turnRight(180,0); //回到180度位置
	delay_ms(5000);
	turnLeft(90,0); //回到90度位置
	delay_ms(3000);
	TIM_SetCompare4(TIM1,1450);
	delay_ms(2000);
	turnLeft(90,1); //回到0度位置
	delay_ms(3000);
	turnRight(180,1); //回到180度位置
	delay_ms(5000);
	turnLeft(30,1); //回到30度位置  大概正前方
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
		
		

//	//	printf("温度为：%0.1f",temperature/10.0);	//显示温度部分

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
//	//	printf("温度为：%0.1f",temperature/10.0);	//显示温度部分
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









