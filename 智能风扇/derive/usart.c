#include "usart.h"

u8 USART_RX_BUF[USART_bufLength];
u8 USART_RX_state=0x00; //����״̬��־���ѽ����ֽ���
u8 sensitivity=10;  //���ο��ƶ��ת��Ƕȣ������ȣ� �Զ�ģʽ��Ϊ0
u8 FAN_mode=0x00;//���ȹ���ģʽ  Ĭ��0x00�ֶ�  �Զ�ʱ0x01

//����1��ʼ��  btΪ���õĲ�����
void usart_config(uint32_t bt)
{
		
	
		GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
		//ʹ��USART1��GPIOAʱ��
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	
	
	   //GPIO����
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
    GPIO_Init(GPIOA, &GPIO_InitStructure);
   
    //USART1_RX	  PA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);  
	  
		//usart����
	
		USART_InitStructure.USART_BaudRate = bt;//һ������Ϊ9600;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
		USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
		USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

    USART_Init(USART1, &USART_InitStructure); //��ʼ������
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
		USART_Cmd(USART1,ENABLE);//ʹ��usart1
		
			/* ����NVIC���� */
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);    
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; 	   //��USART1��ȫ���ж�
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 	 //��ռ���ȼ�Ϊ0
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 			//��Ӧ���ȼ�Ϊ0
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 			 //ʹ��
		NVIC_Init(&NVIC_InitStructure);

		
}

//����2��ʼ��  btΪ���õĲ�����
void usart2_config(uint32_t bt)
{
		
	
		GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
//		NVIC_InitTypeDef NVIC_InitStructure;
		//ʹ��USART1��GPIOAʱ��
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	
	   //GPIO����
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA2
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
    GPIO_Init(GPIOA, &GPIO_InitStructure);
   
    //USART1_RX	  PA3
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);  
	  
		//usart����
	
		USART_InitStructure.USART_BaudRate = bt;//һ������Ϊ9600;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
		USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
		USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

    USART_Init(USART2, &USART_InitStructure); //��ʼ������
//	//	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
		USART_Cmd(USART2,ENABLE);//ʹ��usart1
		
			/* ����NVIC���� */
//		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);    
//		NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn; 	   //��USART1��ȫ���ж�
//		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 	 //��ռ���ȼ�Ϊ0
//		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 			//��Ӧ���ȼ�Ϊ0
//		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 			 //ʹ��
//		NVIC_Init(&NVIC_InitStructure);

		
}


//����һ���ֽ�
void sendByte(u8 data)
{
	uint16_t temp=data;
	USART_SendData(USART1,temp);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
}

//����һ���ֽڰ�
void sendArrByte(u8* arr)
{
	int length=sizeof(arr)+1;
	int i;
	for(i=0;i<length;i++)
	{
		sendByte(*arr++);
	}
}


		//����1�жϺ���
void USART1_IRQHandler(void)	
{
	u8 tempdata;
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
	{
		tempdata=USART_ReceiveData(USART1);//���յĵ����ֽ�����
		if(USART_RX_state)
		{
			USART_RX_BUF[USART_RX_state]=tempdata;
			USART_RX_state++;
		}
		if(USART_RX_state==0x00&&tempdata==USART_RX_start)//������״̬�����ݿ�ͷ  0xAA
		{
			USART_RX_BUF[USART_RX_state]=tempdata;
			USART_RX_state++;
		}
		else if(USART_RX_state==0x05)
				 {
						if(tempdata==USART_RX_end)  //������Ƿ��н�β0D
						{
							switch(USART_RX_BUF[1])//�ж���Ϣ����
							{
								case 0x01:turnLeft(USART_RX_BUF[2],0);break;
								case 0x02:turnRight(USART_RX_BUF[2],0);break;
								case 0x03:turnLeft(USART_RX_BUF[2],1);break;//y������
								case 0x04:turnRight(USART_RX_BUF[2],1);break;//y������
								case 0x05:sensitivity=USART_RX_BUF[2];break;
								default:;
							}
						}
						USART_RX_state=0x00;  //��λ����״̬					
				  }

	}

}


int fputc(int ch, FILE *f)
{
		/* ����һ���ֽ����ݵ�USART1 */
		USART_SendData(USART1, (uint8_t) ch);
		
		/* �ȴ�������� */
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

/// �ض���c�⺯��scanf��USART1
int fgetc(FILE *f)
{
		/* �ȴ�����1�������� */
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USART1);
}
