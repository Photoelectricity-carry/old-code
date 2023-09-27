#include "stm32f10x.h"                  // Device header
#include "relay.h"
#include "delay.h"

void relay_init(void)
{
  GPIO_InitTypeDef  GPIO_InitStruct  ;
	//端口时钟使能
	RCC_APB2PeriphClockCmd  (RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD,ENABLE); 
	//端口PB3-6/12-15 初始化----推挽输出
	GPIO_InitStruct.GPIO_Mode  =GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed	=GPIO_Speed_2MHz;	
  GPIO_InitStruct.GPIO_Pin		=GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_Init  ( GPIOB, &GPIO_InitStruct ) ;
  //端口PC6-12 初始化----推挽输出
  GPIO_InitStruct.GPIO_Pin		=GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_Init  ( GPIOC, &GPIO_InitStruct ) ;
  //端口PD2 初始化----推挽输出
  GPIO_InitStruct.GPIO_Pin		=GPIO_Pin_2;
	GPIO_Init  ( GPIOD, &GPIO_InitStruct ) ;
  
	//初始状态置低电平
	GPIO_ResetBits  ( GPIOB,GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15 ) ;
  GPIO_ResetBits  ( GPIOC,GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 ) ;
  GPIO_ResetBits  ( GPIOD,GPIO_Pin_2 ) ;
}

//void Close_All_Relay(void)
//{
//  SENSOR_POWER_SWITCH=0;
//  delay_ms(200);    //先断掉SENSOR板供电，再断电流表开关，防止烧坏板
//  CURRENT_SWITCH=0;
//  HUB_BLUETOOTH_SWITCH=0;
//  HUB_POWER_SWITCH=0;
//  BUCHANG_POWER_SWITCH=0;
//  delay_ms(50);                          //等待继电器全部关闭
//}

//void TEST_CURR_SW(u8 model)
//{
//  if(model)       //打开继电器，测电压
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
