#ifndef __MOTOR_H
#define __MOTOR_H
#include "stm32f4xx.h"
#include "delay.h"


void MotorL_PWM1_Init(u16 arr,u16 psc);//×óÂÖ
void MotorR_PWM2_Init(u16 arr,u16 psc);//ÓÒÂÖ
void encoder_tim3_init(void);
void encoder_tim4_init(void);
float read_encoder_tim3(void);
float read_encoder_tim4(void);
void Motor_GPIO_init(void);
void TIM7_Int_Init(u16 arr,u16 psc);


#endif
