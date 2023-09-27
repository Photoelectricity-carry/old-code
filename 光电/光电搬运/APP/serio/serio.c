#include "stm32f4xx.h"
#include "timer.h"
#include "serio.h"

void zuo1_serio(int compare1,int compare2)
{
	
	TIM_SetCompare1(TIM1,compare1);
	TIM_SetCompare2(TIM1,compare2);
	
}



 void zuo2_serio(int compare3,int compare4)
 {
	
	TIM_SetCompare3(TIM1,compare3);
	TIM_SetCompare4(TIM1,compare4);
 }
 
 
 void you1_serio(int compare1,int compare2)
 {
	 TIM_SetCompare1(TIM3,compare1);
	 TIM_SetCompare2(TIM3,compare2);
 }
 
 void you2_serio(int compare3,int compare4)
 {
	 TIM_SetCompare3(TIM3,compare3);
	 TIM_SetCompare4(TIM3,compare4);
	 
 }
 