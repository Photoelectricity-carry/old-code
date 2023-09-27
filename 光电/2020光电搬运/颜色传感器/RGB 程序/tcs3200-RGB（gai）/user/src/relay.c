#include "stm32f10x.h"                  // Device header
#include "relay.h"
#include "delay.h"

void relay_init(void)
{
  GPIO_InitTypeDef  GPIO_InitStruct  ;
	//�˿�ʱ��ʹ��
	RCC_APB2PeriphClockCmd  (RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD,ENABLE); 
	//�˿�PB3-6/12-15 ��ʼ��----�������
	GPIO_InitStruct.GPIO_Mode  =GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed	=GPIO_Speed_2MHz;	
  GPIO_InitStruct.GPIO_Pin		=GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_Init  ( GPIOB, &GPIO_InitStruct ) ;
  //�˿�PC6-12 ��ʼ��----�������
  GPIO_InitStruct.GPIO_Pin		=GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_Init  ( GPIOC, &GPIO_InitStruct ) ;
  //�˿�PD2 ��ʼ��----�������
  GPIO_InitStruct.GPIO_Pin		=GPIO_Pin_2;
	GPIO_Init  ( GPIOD, &GPIO_InitStruct ) ;
  
	//��ʼ״̬�õ͵�ƽ
	GPIO_ResetBits  ( GPIOB,GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15 ) ;
  GPIO_ResetBits  ( GPIOC,GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 ) ;
  GPIO_ResetBits  ( GPIOD,GPIO_Pin_2 ) ;
}

//void Close_All_Relay(void)
//{
//  SENSOR_POWER_SWITCH=0;
//  delay_ms(200);    //�ȶϵ�SENSOR�幩�磬�ٶϵ������أ���ֹ�ջ���
//  CURRENT_SWITCH=0;
//  HUB_BLUETOOTH_SWITCH=0;
//  HUB_POWER_SWITCH=0;
//  BUCHANG_POWER_SWITCH=0;
//  delay_ms(50);                          //�ȴ��̵���ȫ���ر�
//}

//void TEST_CURR_SW(u8 model)
//{
//  if(model)       //�򿪼̵��������ѹ
//  {
//    GPIO_SetBits  ( GPIOB, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15 ) ;
//    GPIO_SetBits  ( GPIOC,GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_9  ) ;
//    delay_ms(100);
//  }
//  else
//  {
//    GPIO_ResetBits  ( GPIOB, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15 ) ;
//    GPIO_ResetBits  ( GPIOC,GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_9  ) ;
//    delay_ms(100);
//  }
//}
