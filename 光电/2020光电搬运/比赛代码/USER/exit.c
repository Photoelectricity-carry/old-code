#include "exit.h"
#include "delay.h"
#include "stm32f10x_exti.h"
#include "TCS3200.h"
  
void EXTIX_Init(void)
{
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
 	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);			//ʹ��PAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);				//ʹ��PA���ù���ʱ��

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8;						//PA.8
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 					//���ó���������
 	GPIO_Init(GPIOE, &GPIO_InitStructure);							//��ʼ��GPIOA.8 	

 	//GPIOA.4	  �ж����Լ��жϳ�ʼ������  �½��ش���	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource4);
	EXTI_InitStructure.EXTI_Line=EXTI_Line8;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);	 								//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;				//ʹ��GPIOA.8���ڵ��ⲿ�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;			//�����ȼ�0 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);  	  							//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
 
}

void EXTI9_5_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line8);  							//���LINE8�ϵ��жϱ�־λ  
	if(amount<999999)
	{
		amount++;
	}
}
