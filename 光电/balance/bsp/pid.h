#ifndef _PID_H
#define _PID_H

#include "gyro_driver.h"
#include "encoder.h"

/*ƽ�⻷pid�ṹ��*/
typedef struct {
	//ƽ��Ƕ�ֵ
	int   angle_balance;
	//�Ƕ����
	int   angle_err;
	//ƽ�⻷kp
	float balance_kp;
	//ƽ�⻷kd
	float balance_kd;
	//ƽ�⻷pid���
	float out;
} balance_pid_t;

/*�ٶȻ�pid�ṹ��*/
typedef struct {
	//Ŀ���ٶ�
	int   speed_set;
	//�ٶ����
	int speed_err;
	//�ٶ�����ͨ�˲����(�����ʼ��Ϊ0)
	float speed_err_filter;
	//�ٶ�����
	float speed_err_filter_sum;
	//�ٶȻ�kp
	float speed_kp;
	//�ٶȻ�ki
	float speed_ki;
	//�ٶȻ����ֵ
	float speed_out;
} velocity_pid_t;

/*ת��pid�ṹ��*/
typedef struct {
	//ת��kp
	float turning_kp;
	//�趨�Ƕ�
	int   turningAngle;
	//�Ƕ����
	int   turningAngle_err;
	//�Ƕ����
	float turning_out;
} turning_pid_t;

/*pid�ṹ��*/
typedef struct {
	//ƽ�⻷pid
	balance_pid_t  balance;
	//�ٶȻ�pid
	velocity_pid_t velocity;
	//ת��pid
	turning_pid_t  turning;
} pid_t;


//pid��ʼ������
void pid_init(pid_t * ppid);
//ƽ�⻷pid���㺯��
float balance_pid_calc(balance_pid_t * pbalance_pid, gyro_driver_handle_t * pgyro);
//�ٶȻ�pid���㺯��
float velocity_pid_calc(velocity_pid_t * pvelocity_pid, ecd_t * pecd);
//ת��pid���㺯��
float turning_pid_calc(turning_pid_t * pturning_pid, gyro_driver_handle_t * pgyro);

#endif

