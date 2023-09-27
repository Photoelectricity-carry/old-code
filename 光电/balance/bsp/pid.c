#include "pid.h"


/*ƽ�⻷pd����*/
#define BALANCE_KP		0.0f
#define BALANCE_KD		0.0f

/*�ٶȻ�pi����*/
//�ٶȻ���kp��ki�Ĺ�ϵһ���� kp = 200ki
#define VELOCITY_KP		0.0f
#define VELOCITY_KI		0.0f

/*ת��p����*/
#define TURNING_KP		0.0f

//һ�׵�ͨ�˲�ϵ��
#define FILTER_ARGUMENT	0.3f



//pid���ݽṹ��
pid_t pid = {0};

/*pid��ʼ������*/
void pid_init(pid_t * ppid){
	
}

/*ƽ�⻷pid���㺯��*/
float balance_pid_calc(balance_pid_t * pbalance_pid, gyro_driver_handle_t * pgyro){
	//�������ֵ
	pbalance_pid->angle_err = pgyro->angle.pitch - pbalance_pid->angle_balance; 
	
	//����pid���(����i����ٶ�ֱ�����������Ǽ��ٶ�����)
	pbalance_pid->out = pbalance_pid->balance_kp * (float)pbalance_pid->angle_err 
					  + pbalance_pid->balance_kd * (float)pgyro->acc.ax;
	
	return pbalance_pid->out;
}

/*�ٶȻ�pid���㺯�� ������*/
float velocity_pid_calc(velocity_pid_t * pvelocity_pid, ecd_t * pecd){
	//�����ٶ����
	pvelocity_pid->speed_err = (pecd->leftECD + pecd->rightECD)
							   - pvelocity_pid->speed_set;

    //���ٶ����һ�׵�ͨ�˲�
	//��ͨ�˲���Ŀ���Ǽ����ٶȱ仯(ʹ�ٶ��ź�ƽ��), ��С�ٶȱ仯��ֱ��pid��Ӱ��
	pvelocity_pid->speed_err_filter = (float)pvelocity_pid->speed_err * FILTER_ARGUMENT
									+ pvelocity_pid->speed_err_filter * (1 - FILTER_ARGUMENT);
	
	//�����˲����ٶ�������
	pvelocity_pid->speed_err_filter_sum += pvelocity_pid->speed_err_filter;
	/*�����޷�*/
	if (pvelocity_pid->speed_err_filter_sum > 10000.0f){
		pvelocity_pid->speed_err_filter_sum = 10000.0f;
	}
	if (pvelocity_pid->speed_err_filter_sum < -10000.0f){
		pvelocity_pid->speed_err_filter_sum = -10000.0f;
	}
	
	//����pid���
	pvelocity_pid->speed_out = pvelocity_pid->speed_kp * pvelocity_pid->speed_err_filter
							 + pvelocity_pid->speed_ki * pvelocity_pid->speed_err_filter_sum;
	
	return pvelocity_pid->speed_out;
}

/*ת��pid���㺯��*/
/*
����:
	  0*
90*			-90*
  180* -180*
*/
float turning_pid_calc(turning_pid_t * pturning_pid, gyro_driver_handle_t * pgyro){
	//����Ƕ����
	pturning_pid->turningAngle_err = pturning_pid->turningAngle - pgyro->angle.yaw;
	
	//�������
	pturning_pid->turning_out = pturning_pid->turning_kp * (float)pturning_pid->turningAngle_err;
	
	return pturning_pid->turning_out;
}


