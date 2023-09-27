#ifndef __MOTOR_H
#define __MOTOR_H
#include "stm32f4xx.h"

extern void PWM1_Init(u16 arr,u16 psc);//×óÂÖ
extern void PWM2_Init(u16 arr,u16 psc);//ÓÒÂÖ
extern float HF_Get_Encode_TIM4(void);
extern void TIM4_Encoder_Init(u16 arr,u16 psc);
extern void goStraight(int speed1,int speed2);

extern void retreat(int speed1 ,int speed2);

extern void turn_right(int speed1,int speed2,int n);
		
extern void turn_left(int speed1,int speed2,int n);

extern void stop(int n);
extern void yanxianzou(int speed1, int speed2);
extern void yanxiantui(int speed1, int speed2);




#endif
