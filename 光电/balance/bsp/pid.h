#ifndef _PID_H
#define _PID_H

#include "gyro_driver.h"
#include "encoder.h"

/*平衡环pid结构体*/
typedef struct {
	//平衡角度值
	int   angle_balance;
	//角度误差
	int   angle_err;
	//平衡环kp
	float balance_kp;
	//平衡环kd
	float balance_kd;
	//平衡环pid输出
	float out;
} balance_pid_t;

/*速度环pid结构体*/
typedef struct {
	//目标速度
	int   speed_set;
	//速度误差
	int speed_err;
	//速度误差低通滤波输出(必须初始化为0)
	float speed_err_filter;
	//速度误差和
	float speed_err_filter_sum;
	//速度环kp
	float speed_kp;
	//速度环ki
	float speed_ki;
	//速度环输出值
	float speed_out;
} velocity_pid_t;

/*转向环pid结构体*/
typedef struct {
	//转向环kp
	float turning_kp;
	//设定角度
	int   turningAngle;
	//角度误差
	int   turningAngle_err;
	//角度输出
	float turning_out;
} turning_pid_t;

/*pid结构体*/
typedef struct {
	//平衡环pid
	balance_pid_t  balance;
	//速度环pid
	velocity_pid_t velocity;
	//转向环pid
	turning_pid_t  turning;
} pid_t;


//pid初始化函数
void pid_init(pid_t * ppid);
//平衡环pid计算函数
float balance_pid_calc(balance_pid_t * pbalance_pid, gyro_driver_handle_t * pgyro);
//速度环pid计算函数
float velocity_pid_calc(velocity_pid_t * pvelocity_pid, ecd_t * pecd);
//转向环pid计算函数
float turning_pid_calc(turning_pid_t * pturning_pid, gyro_driver_handle_t * pgyro);

#endif

