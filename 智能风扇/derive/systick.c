#include "systick.h"
static uint8_t  fac_us=0;//us延时倍乘数
static uint16_t fac_ms=0;//ms延时倍乘数

//初始化systick
void systick_config(void)
{
	
		SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);//systick的时钟固定为HCLK的1/8
		fac_us=SystemCoreClock/8000000;//为系统时钟的1/8
		fac_ms=(uint16_t)fac_us*1000;//非ucos下，代表每个ms的systick时钟数
}

//us级延时
void delay_us(uint32_t nus)
{
	uint32_t temp;
	SysTick->LOAD=nus*fac_us;//时间加载
	SysTick->VAL=0x00000;   //清空计数器
	SysTick->CTRL|=1;//使能定时器 开始计数
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&((temp&(1<<16))==0));//查看CTRL的16位段COUNTFLAG的值 为1时时间到达 读取一次后自动复位为0 复位值0
	SysTick->CTRL=0; 				//失能定时器
	SysTick->VAL=0x000000;  //清空计数器
}




//ms级延时
//这里需要注意的nms的取值范围
//SysTick->LOAD为24位寄存器 所以最大延时为：nms<=0xFFFFFF*8*1000/sysclk
//sysclk单位为HZ nms单位为ms
//当sysclk=72M是 nms<=1864  当sysclk=48M是 nms<=2796
void delay_ms(uint16_t nms)
{
	uint32_t temp;
	SysTick->LOAD=nms*fac_ms;//时间加载
	SysTick->VAL=0x000000;   //清空计数器
	SysTick->CTRL|=1;//使能定时器 开始计数
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&((temp&(1<<16))==0));//查看CTRL的16位段COUNTFLAG的值 为1时时间到达 读取一次后自动复位为0 复位值0
	SysTick->CTRL=0; 				//失能定时器
	SysTick->VAL=0x000000;  //清空计数器
}
