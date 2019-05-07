#include "usart.h"

u8 USART_RX_BUF[USART_bufLength];
u8 USART_RX_state=0x00; //接收状态标志和已接收字节数
u8 sensitivity=10;  //单次控制舵机转向角度（灵敏度） 自动模式下为0
u8 FAN_mode=0x00;//风扇工作模式  默认0x00手动  自动时0x01

//串口1初始化  bt为设置的波特率
void usart_config(uint32_t bt)
{
		
	
		GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
		//使能USART1，GPIOA时钟
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	
	
	   //GPIO部分
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure);
   
    //USART1_RX	  PA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);  
	  
		//usart部分
	
		USART_InitStructure.USART_BaudRate = bt;//一般设置为9600;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
		USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
		USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

    USART_Init(USART1, &USART_InitStructure); //初始化串口
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
		USART_Cmd(USART1,ENABLE);//使能usart1
		
			/* 设置NVIC参数 */
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);    
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; 	   //打开USART1的全局中断
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 	 //抢占优先级为0
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 			//响应优先级为0
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 			 //使能
		NVIC_Init(&NVIC_InitStructure);

		
}

//串口2初始化  bt为设置的波特率
void usart2_config(uint32_t bt)
{
		
	
		GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
//		NVIC_InitTypeDef NVIC_InitStructure;
		//使能USART1，GPIOA时钟
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	
	   //GPIO部分
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA2
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure);
   
    //USART1_RX	  PA3
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);  
	  
		//usart部分
	
		USART_InitStructure.USART_BaudRate = bt;//一般设置为9600;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
		USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
		USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

    USART_Init(USART2, &USART_InitStructure); //初始化串口
//	//	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
		USART_Cmd(USART2,ENABLE);//使能usart1
		
			/* 设置NVIC参数 */
//		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);    
//		NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn; 	   //打开USART1的全局中断
//		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 	 //抢占优先级为0
//		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 			//响应优先级为0
//		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 			 //使能
//		NVIC_Init(&NVIC_InitStructure);

		
}


//发送一个字节
void sendByte(u8 data)
{
	uint16_t temp=data;
	USART_SendData(USART1,temp);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
}

//发送一个字节包
void sendArrByte(u8* arr)
{
	int length=sizeof(arr)+1;
	int i;
	for(i=0;i<length;i++)
	{
		sendByte(*arr++);
	}
}


		//串口1中断函数
void USART1_IRQHandler(void)	
{
	u8 tempdata;
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
	{
		tempdata=USART_ReceiveData(USART1);//接收的单个字节数据
		if(USART_RX_state)
		{
			USART_RX_BUF[USART_RX_state]=tempdata;
			USART_RX_state++;
		}
		if(USART_RX_state==0x00&&tempdata==USART_RX_start)//检查接收状态和数据开头  0xAA
		{
			USART_RX_BUF[USART_RX_state]=tempdata;
			USART_RX_state++;
		}
		else if(USART_RX_state==0x05)
				 {
						if(tempdata==USART_RX_end)  //检查下是否有结尾0D
						{
							switch(USART_RX_BUF[1])//判断消息类型
							{
								case 0x01:turnLeft(USART_RX_BUF[2],0);break;
								case 0x02:turnRight(USART_RX_BUF[2],0);break;
								case 0x03:turnLeft(USART_RX_BUF[2],1);break;//y轴向上
								case 0x04:turnRight(USART_RX_BUF[2],1);break;//y轴向下
								case 0x05:sensitivity=USART_RX_BUF[2];break;
								default:;
							}
						}
						USART_RX_state=0x00;  //复位接收状态					
				  }

	}

}


int fputc(int ch, FILE *f)
{
		/* 发送一个字节数据到USART1 */
		USART_SendData(USART1, (uint8_t) ch);
		
		/* 等待发送完毕 */
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

/// 重定向c库函数scanf到USART1
int fgetc(FILE *f)
{
		/* 等待串口1输入数据 */
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USART1);
}
