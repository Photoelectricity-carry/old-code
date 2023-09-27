#ifndef __PWM_H
#define __PWM_H	
#include "sys.h" 

void TIM4_PWM_CH1_Init(u16 arr,u16 psc);
void TIM4_PWM_CH3_Init(u16 arr,u16 psc);

void TIM2_PWM_CH3_Init(u16 arr,u16 psc);
void TIM5_PWM_CH1_Init(u16 arr,u16 psc);
void TIM3_PWM_CH3_Init(u16 arr,u16 psc,u16 ccr3);
void TIM3_PWM_CH4_Init(u16 arr,u16 psc,u16 ccr4);




#endif





