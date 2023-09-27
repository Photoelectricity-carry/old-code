#ifndef MOTOR_H
#define MOTOR_H

#include "main.h"


//电机初始化函数
void motor_init(void);
//电机控制函数
void motor_set(int motor1_pwmVal, int motor2_pwmVal);

#endif

