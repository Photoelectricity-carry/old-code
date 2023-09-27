#include "stm32f10x.h"                  
#include "uart.h"
#include "stdio.h"
#include "string.h"
#include "io_bit.h"
#include "delay.h"
#include "exti.h"
#include "tcs3200.h"


 
int main(void)
{

	u8 colour;
  
  NVIC_EncodePriority(7-2,3,3);           //端口初始化函数
 uart1_init(9600);//波特率 
//  relay_init();//继电器
  EXTIX_Init();//外部中断
	tcs3200_init(1,1);//初始化（速率调整）
  whitebalance();	//白平衡  
			

	while(1)
  { 
		
    colour=RBG_fun();	
		printf("%d ",colour);
		delay_ms(1000);
		
  }
}

