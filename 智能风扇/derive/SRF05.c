#include "SRF05.h"

u16 msHcCount = 0;//ms����
volatile int speed=250;
void SRF05_Init(void)
{  
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;     //�������ڶ�ʱ�����õĽṹ��
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
     
        //IO��ʼ��
    GPIO_InitStructure.GPIO_Pin =SRF05_TRIG_GPIOB;       //���͵�ƽ����
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�������
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOB,SRF05_TRIG_GPIOB);
     
    GPIO_InitStructure.GPIO_Pin =SRF05_ECHO_GPIOB;     //���ص�ƽ����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOB, &GPIO_InitStructure);  
        GPIO_ResetBits(GPIOB,SRF05_ECHO_GPIOB);    
     
        //��ʱ����ʼ�� ʹ�û�����ʱ��TIM2
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);   //ʹ�ܶ�ӦRCCʱ��
        //���ö�ʱ�������ṹ��
    TIM_DeInit(TIM2);
    TIM_TimeBaseStructure.TIM_Period = (1000-1); //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ         ������1000Ϊ1ms
    TIM_TimeBaseStructure.TIM_Prescaler =(72-1); //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  1M�ļ���Ƶ�� 1US����
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;//����Ƶ
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ         
        
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);   //��������жϣ����һ���ж����������ж�
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);    //�򿪶�ʱ�������ж�
    SRF05_NVIC();
    TIM_Cmd(TIM2,DISABLE);     
}


//tips��static����������������ڶ�������Դ�ļ��ڣ����Բ���Ҫ��ͷ�ļ�������
static void OpenTimerForHc()        //�򿪶�ʱ��
{
        TIM_SetCounter(TIM2,0);//�������
        msHcCount = 0;
        TIM_Cmd(TIM2, ENABLE);  //ʹ��TIMx����
}
 
static void CloseTimerForHc()        //�رն�ʱ��
{
        TIM_Cmd(TIM2, DISABLE);  //ʹ��TIMx����
}
 
 
 //NVIC����
void SRF05_NVIC()
{
            NVIC_InitTypeDef NVIC_InitStructure;
            NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    
            NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;             //ѡ�񴮿�1�ж�
            NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռʽ�ж����ȼ�����Ϊ1
            NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;         //��Ӧʽ�ж����ȼ�����Ϊ1
            NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;        //ʹ���ж�
            NVIC_Init(&NVIC_InitStructure);
}


//��ʱ��6�жϷ������
void TIM2_IRQHandler(void)   //TIM2�ж�
{
        if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //���TIM2�����жϷ������
        {
                TIM_ClearITPendingBit(TIM2, TIM_IT_Update );  //���TIMx�����жϱ�־ 
                msHcCount++;
        }
}
 

//��ȡ��ʱ��ʱ��
u32 GetEchoTimer(void)
{
        u32 t = 0;
        t = msHcCount*1000;//�õ�MS
        t += TIM_GetCounter(TIM2);//�õ�US
          TIM2->CNT = 0;  //��TIM2�����Ĵ����ļ���ֵ����
                delay_ms(50);
        return t;
}
 

//һ�λ�ȡ������������� ���β��֮����Ҫ���һ��ʱ�䣬���ϻ����ź�
//Ϊ�����������Ӱ�죬ȡ������ݵ�ƽ��ֵ���м�Ȩ�˲���


float SRF05GetLength(void )
{
        u32 t = 0;
        int i = 0;
        float lengthTemp = 0;
        float sum = 0;
        while(i!=5)
        {
				
					GPIO_WriteBit(GPIOB,SRF05_TRIG_GPIOB,Bit_SET);//���Ϳڸߵ�ƽ���

					delay_us(20);
					GPIO_WriteBit(GPIOB,SRF05_TRIG_GPIOB,Bit_RESET);
					while(GPIO_ReadInputDataBit(GPIOB,SRF05_ECHO_GPIOB)==0);      //�ȴ����տڸߵ�ƽ���
            OpenTimerForHc();        //�򿪶�ʱ��
            i = i + 1;
            while(GPIO_ReadInputDataBit(GPIOB,SRF05_ECHO_GPIOB) == 1);
            CloseTimerForHc();        //�رն�ʱ��
            t = GetEchoTimer();        //��ȡʱ��,�ֱ���Ϊ1US
            lengthTemp = ((float)t/58.0);//cm
            sum = lengthTemp + sum ;
        
    }
        lengthTemp = sum/5.0;
        return lengthTemp;
}

