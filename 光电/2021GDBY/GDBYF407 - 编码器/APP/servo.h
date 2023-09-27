#ifndef _SERVO_H
#define _SERVO_H
#include "stm32f4xx.h"

void SERVO_TIM12_Init(u32 arr,u32 psc);
void SERVO_TIM9_Init(u32 arr,u32 psc);
void SERVO_TIM11_Init(u32 arr,u32 psc);
void SERVO_GPIO_Init(void);
void SERVO_TIM3_Init(u32 arr,u32 psc);
void SERVO_TIM4_Init(u32 arr,u32 psc);


#endif
