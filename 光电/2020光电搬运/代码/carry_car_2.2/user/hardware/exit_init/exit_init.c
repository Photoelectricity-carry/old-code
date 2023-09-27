#include "exit_init.h"
#include "tcs3200.h"
#include "stm32f4xx.h"



//void EXTIX_Init(void)
//{
//	  NVIC_InitTypeDef   NVIC_InitStructure;
//	  EXTI_InitTypeDef   EXTI_InitStructure;	
//	  GPIO_InitTypeDef   GPIO_InitStructure;
//	
//    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//ʹ��GPIOA,GPIOEʱ��
//    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF,EXTI_PinSource1); //F1
//	 
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //out��Ӧ����
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
//    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
//    GPIO_Init(GPIOF, &GPIO_InitStructure);//
//	
//		EXTI_InitStructure.EXTI_Line = EXTI_Line1;//LINE1
//		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
//		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش��� 
//		EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��LINE0
//		EXTI_Init(&EXTI_InitStructure);//����

//		NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;//�ⲿ�ж�1
//		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x05;//��ռ���ȼ�0
//		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
//		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
//		NVIC_Init(&NVIC_InitStructure);//����
//}


//�ⲿ�ж�0�������
void EXTI0_IRQHandler(void)
{
 	 amount++;
	 EXTI_ClearITPendingBit(EXTI_Line0); //���LINE0�ϵ��жϱ�־λ 
}	

void EXTIX_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	GPIO_InitTypeDef   GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //out��Ӧ����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(GPIOF, &GPIO_InitStructure);//	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource0);//PE2 ���ӵ��ж���2

	
  /* ����EXTI_Line0 */
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;//LINE0
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//�½��ش���
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��LINE0
  EXTI_Init(&EXTI_InitStructure);//����
	
 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;//�ⲿ�ж�0
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//��ռ���ȼ�0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	   
}




