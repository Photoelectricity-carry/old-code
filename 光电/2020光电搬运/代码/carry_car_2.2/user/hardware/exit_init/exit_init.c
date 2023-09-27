#include "exit_init.h"
#include "tcs3200.h"
#include "stm32f4xx.h"



//void EXTIX_Init(void)
//{
//	  NVIC_InitTypeDef   NVIC_InitStructure;
//	  EXTI_InitTypeDef   EXTI_InitStructure;	
//	  GPIO_InitTypeDef   GPIO_InitStructure;
//	
//    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//使能GPIOA,GPIOE时钟
//    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF,EXTI_PinSource1); //F1
//	 
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //out对应引脚
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
//    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
//    GPIO_Init(GPIOF, &GPIO_InitStructure);//
//	
//		EXTI_InitStructure.EXTI_Line = EXTI_Line1;//LINE1
//		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
//		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发 
//		EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能LINE0
//		EXTI_Init(&EXTI_InitStructure);//配置

//		NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;//外部中断1
//		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x05;//抢占优先级0
//		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
//		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
//		NVIC_Init(&NVIC_InitStructure);//配置
//}


//外部中断0服务程序
void EXTI0_IRQHandler(void)
{
 	 amount++;
	 EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE0上的中断标志位 
}	

void EXTIX_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	GPIO_InitTypeDef   GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //out对应引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOF, &GPIO_InitStructure);//	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource0);//PE2 连接到中断线2

	
  /* 配置EXTI_Line0 */
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;//LINE0
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能LINE0
  EXTI_Init(&EXTI_InitStructure);//配置
	
 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;//外部中断0
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//抢占优先级0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
	   
}




