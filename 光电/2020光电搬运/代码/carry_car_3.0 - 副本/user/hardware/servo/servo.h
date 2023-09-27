#ifndef _SERVO_H
#define _SERVO_H
#include "stm32f4xx.h"

extern void servo_on(uint16_t cmd);
extern void servo_on_1(uint16_t cmd);
extern void servo_on_2(uint16_t cmd);
extern void servo_on_3(uint16_t cmd);


extern void SERVO_PWM_Init_1(void);
extern void SERVO_PWM_Init_2(void);
extern void SERVO_PWM_Init_3(void);
extern void SERVO_PWM_Init_4(void);

#endif

