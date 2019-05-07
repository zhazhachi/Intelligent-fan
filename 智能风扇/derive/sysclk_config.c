#include "sysclk_config.h"



void sysclk_config(void)
{
	
		RCC_DeInit();//设置系统时钟为缺省值
		RCC_HSEConfig(RCC_HSE_ON);
		while(SUCCESS != RCC_WaitForHSEStartUp()){} 
    /*设置FLASH存储器延时时钟周期数*/
    FLASH_SetLatency(FLASH_Latency_2);    //FLASH_Latency_2  2延时周期 
    /*选择FLASH预取指缓存的模式*/ 
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);     // 预取指缓存使能
    /*设置PLL时钟源及倍频系数*/  
    /* Fcpu = (PLL_src * PLL_MUL) = (8 Mhz / 1) * (9) = 72Mhz   */ 
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);            
    /* Enable PLL */
    RCC_PLLCmd(ENABLE); 
     /*检查指定的RCC标志位(PLL准备好标志)设置与否*/    
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET) {}
    /* Set system clock dividers */
    RCC_HCLKConfig(RCC_SYSCLK_Div1);
    RCC_PCLK2Config(RCC_HCLK_Div1);
    RCC_PCLK1Config(RCC_HCLK_Div2);
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);   
    /* Embedded Flash Configuration */
    FLASH_SetLatency(FLASH_Latency_2);                           
    FLASH_HalfCycleAccessCmd(FLASH_HalfCycleAccess_Disable);
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
    /*SYSCLK configuration*/
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
}



