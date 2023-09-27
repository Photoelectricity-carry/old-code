#include "pid.h"


/*平衡环pd参数*/
#define BALANCE_KP		0.0f
#define BALANCE_KD		0.0f

/*速度环pi参数*/
//速度环中kp和ki的关系一般是 kp = 200ki
#define VELOCITY_KP		0.0f
#define VELOCITY_KI		0.0f

/*转向环p参数*/
#define TURNING_KP		0.0f

//一阶低通滤波系数
#define FILTER_ARGUMENT	0.3f



//pid数据结构体
pid_t pid = {0};

/*pid初始化函数*/
void pid_init(pid_t * ppid){
	
}

/*平衡环pid计算函数*/
float balance_pid_calc(balance_pid_t * pbalance_pid, gyro_driver_handle_t * pgyro){
	//计算误差值
	pbalance_pid->angle_err = pgyro->angle.pitch - pbalance_pid->angle_balance; 
	
	//计算pid输出(这里i项加速度直接套用陀螺仪加速度数据)
	pbalance_pid->out = pbalance_pid->balance_kp * (float)pbalance_pid->angle_err 
					  + pbalance_pid->balance_kd * (float)pgyro->acc.ax;
	
	return pbalance_pid->out;
}

/*速度环pid计算函数 正反馈*/
float velocity_pid_calc(velocity_pid_t * pvelocity_pid, ecd_t * pecd){
	//计算速度误差
	pvelocity_pid->speed_err = (pecd->leftECD + pecd->rightECD)
							   - pvelocity_pid->speed_set;

    //对速度误差一阶低通滤波
	//低通滤波的目的是减缓速度变化(使速度信号平缓), 减小速度变化对直立pid的影响
	pvelocity_pid->speed_err_filter = (float)pvelocity_pid->speed_err * FILTER_ARGUMENT
									+ pvelocity_pid->speed_err_filter * (1 - FILTER_ARGUMENT);
	
	//计算滤波后速度误差积分
	pvelocity_pid->speed_err_filter_sum += pvelocity_pid->speed_err_filter;
	/*积分限幅*/
	if (pvelocity_pid->speed_err_filter_sum > 10000.0f){
		pvelocity_pid->speed_err_filter_sum = 10000.0f;
	}
	if (pvelocity_pid->speed_err_filter_sum < -10000.0f){
		pvelocity_pid->speed_err_filter_sum = -10000.0f;
	}
	
	//计算pid输出
	pvelocity_pid->speed_out = pvelocity_pid->speed_kp * pvelocity_pid->speed_err_filter
							 + pvelocity_pid->speed_ki * pvelocity_pid->speed_err_filter_sum;
	
	return pvelocity_pid->speed_out;
}

/*转向环pid计算函数*/
/*
方向:
	  0*
90*			-90*
  180* -180*
*/
float turning_pid_calc(turning_pid_t * pturning_pid, gyro_driver_handle_t * pgyro){
	//计算角度误差
	pturning_pid->turningAngle_err = pturning_pid->turningAngle - pgyro->angle.yaw;
	
	//计算输出
	pturning_pid->turning_out = pturning_pid->turning_kp * (float)pturning_pid->turningAngle_err;
	
	return pturning_pid->turning_out;
}


