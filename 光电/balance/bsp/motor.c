#include "motor.h"
#include "tim.h"
#include "gpio.h"
#include "main.h"

#define MOTOR_TIM		TIM1
#define hMOTOR_TIM		htim1
#define phMOTOR_TIM		&htim1

#define MOTOR_LEFT_CCR  MOTOR_TIM->CCR1
#define MOTOR_RIGHT_CCR MOTOR_TIM->CCR2

/*���1��ת*/
#define motor1_forward()		{HAL_GPIO_WritePin(IN1_GPIO_Port, IN1_Pin, GPIO_PIN_SET);\
								HAL_GPIO_WritePin(IN2_GPIO_Port, IN2_Pin, GPIO_PIN_RESET);}
								
/*���1��ת*/
#define motor1_backward()		{HAL_GPIO_WritePin(IN1_GPIO_Port, IN1_Pin, GPIO_PIN_RESET);\
								HAL_GPIO_WritePin(IN2_GPIO_Port, IN2_Pin, GPIO_PIN_SET);}
								
/*���2��ת*/
#define motor2_forward()		{HAL_GPIO_WritePin(IN3_GPIO_Port, IN3_Pin, GPIO_PIN_SET);\
								HAL_GPIO_WritePin(IN4_GPIO_Port, IN4_Pin, GPIO_PIN_RESET);}

/*���2��ת*/
#define motor2_backward()		{HAL_GPIO_WritePin(IN3_GPIO_Port, IN3_Pin, GPIO_PIN_RESET);\
								HAL_GPIO_WritePin(IN4_GPIO_Port, IN4_Pin, GPIO_PIN_SET);}


/*�����ʼ������*/
void motor_init(void){
	/*�������pwm���*/
	HAL_TIM_PWM_Start(phMOTOR_TIM, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(phMOTOR_TIM, TIM_CHANNEL_2);
	//����pwm��ʼֵ
	MOTOR_TIM->CCR1 = MOTOR_TIM->CCR2 = MOTOR_TIM->CCR3 = MOTOR_TIM->CCR4 = 0;
}


/*������ƺ���*/
void motor_set(int motor1_pwmVal, int motor2_pwmVal){
	if (motor1_pwmVal >= 0){
		motor1_forward();
		MOTOR_LEFT_CCR = (uint16_t)motor1_pwmVal;
	}
	else if (motor1_pwmVal < 0){
		motor1_backward();
		MOTOR_LEFT_CCR = (uint16_t)(-motor1_pwmVal);
	}
	
	if (motor2_pwmVal >= 0){
		motor2_forward();
		MOTOR_RIGHT_CCR = (uint16_t)motor2_pwmVal;
	}
	else if (motor2_pwmVal < 0){
		MOTOR_RIGHT_CCR = (uint16_t)(-motor2_pwmVal);
	}
}

