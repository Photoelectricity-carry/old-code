#include "speed.h"
#include "stm32f10x_tim.h" 
#include "pwm.h"
#include "direction.h"
#include "delay.h"
void Speed(u16 Right,u16 Left)  
{
  TIM_SetCompare1(TIM4,Left);		 
  TIM_SetCompare3(TIM4,Right);	
}

void stop()
{
	Direction(0,1);
	Speed(10,10);
	delay_ms(500,0);
}

void weihoutui_quick(u16 h)
{
	Direction(1,0);
	Speed(3000,3000);
	delay_ms(300,0);
	stop();
}

void weihoutui_slow(u16 h)
{
	Direction(1,0);
	Speed(2000,2000);
	delay_ms(h,0);
	stop();
}

void weiqianjin_quick(u16 q)
{
	Direction(0,1);
	Speed(3000,3000);
	delay_ms(q,0);
	stop();
}

void weiqianjin_slow(u16 q)
{
	Direction(0,1);
	Speed(2000,2000);
	delay_ms(q,0);
	stop();
}
