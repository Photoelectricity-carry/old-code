#ifndef GIMBALTASK_H
#define GIMBALTASK_H

#include "main.h"
#include "pid.h"
#include "CAN_Receive.h"
#include "user_lib.h"

//�������ֵ����Լ���ֵ
#define Half_ecd_range 4096
#define ecd_range 8191

//�����ʼ�� ����һ��ʱ��
#define GIMBAL_TASK_INIT_TIME 201
//��̨��������
#define GIMBAL_CONTROL_TIME 1

//���̵���ٶȻ�PID
#define M2006_MOTOR_SPEED_PID_KP 900.0f
#define M2006_MOTOR_SPEED_PID_KI 0.0f
#define M2006_MOTOR_SPEED_PID_KD 0.0f
#define M2006_MOTOR_SPEED_MAX_OUT 5000.0f
#define M2006_MOTOR_SPEED_MAX_IOUT 2500.0f

#define TRIGGER_BULLET_PID_MAX_OUT 15000.0f
#define TRIGGER_BULLET_PID_MAX_IOUT 5000.0f

//���rmp �仯�� ��ת�ٶȵı���
#define Motor_RMP_TO_SPEED 0.00290888208665721596153948461415f
#define Motor_ECD_TO_ANGLE 0.000021305288720633905968306772076277f
#define FULL_COUNT 360

//�ٶ�
#define T2006_SPEED_left  8.0f
#define T2006_SPEED_right -8.0f

#define PI_Four 0.78539816339744830961566084581988f
#define PI_Three 1.0466666666666f
#define PI_Ten 0.314f
#define PI_All 22.4247778f
#define PI_LEFT -4.5f

#define PI_LEFT_45 -2.25f
#define PI_RIGHT_45 2.55f

#define PI_RIGHT_135 7.85f
#define PI_LEFT_135 -6.75f
#define PI_RIGHT 5.5f

#define green 4
#define white  0
#define red   2
#define black 1
#define blue  3


#define zuo 0
#define you  1

#define left_go      10.0f   //��ת��
#define left_go_cha  8.0f
#define right_go     -10.0f  //��ת��
#define right_go_cha     -8.0f  

//ǰ��Ѳ��
#define left_go_slow      6.5f   //��ת��
#define left_go_cha_slow  5.0f
#define right_go_slow     -6.0f  //��ת��
#define right_go_cha_slow     -5.0f  

//����Ѳ��
#define left_goback_slow      -13.0f   //��ת��
#define left_goback_cha_slow  9.0f
#define right_goback_slow     13.0f  //��ת��
#define right_goback_cha_slow     -9.0f  




typedef enum
{
  CHASSIS_VECTOR_FOLLOW_GIMBAL_YAW,   //���̸�����̨
  CHASSIS_VECTOR_FOLLOW_CHASSIS_YAW,  //��������
  CHASSIS_VECTOR_NO_FOLLOW_YAW,       //���̲�����
  CHASSIS_VECTOR_RAW,									//����ԭʼ����
	CHASSIS_VECTOR_SPIN,								//С����
} chassis_mode_e;

typedef struct
{
  const motor_measure_t *chassis_motor_measure;
  fp32 accel;
  fp32 speed;
  fp32 speed_set;
  int16_t give_current;
} Chassis_Motor_t;


typedef struct
{
  chassis_mode_e chassis_mode;               //���̿���״̬��
	chassis_mode_e last_chassis_mode;          //�����ϴο���״̬��
	Chassis_Motor_t motor_chassis[4];          //���̵������
	PidTypeDef motor_speed_pid[4];             //���̵���ٶ�pid
	fp32 angle[4];
	int16_t ecd_count[4];
  int16_t given_current[4];
  fp32 set_angle[4];
	fp32 speed[4];
	fp32 speed_set[4];	
	
	bool_t move_flag;
	
	
} chassis_move_t;




extern void GIMBAL_task(void *pvParameters);

#endif
