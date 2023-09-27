#ifndef __MOTOR_H
#define __MOTOR_H
#include "stm32f4xx.h"
#include "delay.h"
#include "main.h"


typedef struct
{
	int encoder_num_l;
	int encoder_num_r;
	double speed_l;
	double speed_r;
	int all_num_l;
	int all_num_r;
} EcoderTypeDef;

void encoder_tim1_init(void);
void encoder_tim3_init(void);

void MotorL_PWM_Init(u16 arr,u16 psc);
void MotorR_PWM_Init(u16 arr,u16 psc);

int read_encoder_l(void);
int read_encoder_r(void);

void Motor_GPIO_init(void);

void TIM7_Int_Init(u16 arr,u16 psc);

void motor_speed(double left,double right);

#endif
