#include "stm32f4xx.h"
#include "delay.h"
#include "exti.h"
#include "timer.h"
#include "huidu.h"
#include "motor.h"
#include "color.h"

 	u16 angel=500;
	u8 dir=1;
int i;
float r,b,g;
int main(void)
{ 
  
  EXTIX_Init ();
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	tcs3200_init(0,0);
	WhiteBalance();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init(168);
	usart3_init(115200);
	while(1)
  {
	 r= tcs3200_RED();
   g= tcs3200_GREEN();
	 b=tcs3200_BLUE();
track();
delay_ms(2);
  }
}
