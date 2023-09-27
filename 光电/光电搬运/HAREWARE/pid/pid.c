#include "sys.h"
#include "pid.h"
PIDtypedef *pid;
void PID_Init(PIDtypedef *pid)
{
	
	 
    pid->kp = 0.4;
    pid->ki = 0.0005;
    pid->kd = 0.005;
    pid->max_iout = 30000;   //积分限幅
	pid->max_out=200;       //最大PID返回      
	pid->error=0;          //循迹返回
	pid->last_error=0;     //上一次循迹返回
	pid->Pwm_return=0;     //pid返回值  
	pid->Iout=0;            //误差累加
    pid->pwmKI=0;           //积分项
}

/*位置式PID控制器
*/
//int PositionPID(float retern_track, PIDtypedef *pid_turn)    //retern_track  参数输入循迹传感器输出值
//{
//	
//	static float error,Pwm,Iout,last_error;
//	error=retern_track;                         		         //计算偏差
//	Iout+=error;	                                            //求出偏差的积分
//	Pwm=  pid_turn->kp*error+pid_turn->ki*Iout+ pid_turn->kd*(error-last_error); //位置式PID控制器
//	last_error=error;                                      	 //保存上一次偏差 
//	return Pwm;    
//}

/* 为速度pid使用位置式PID控制器，对积分值进行限幅

       [in] float retern_track: 循迹传感器输出值
 */
void PositionPIDToSPEED(float track_retern,PIDtypedef *pid)
{
	
	pid->error = track_retern;                         		         //计算偏差
	pid->Iout+=pid->error;	                                            //求出偏差的积分                              //求出偏差的积分
	pid->pwmKI=(pid->ki)*pid->Iout;
	if(pid->pwmKI > pid->max_iout) pid->Iout=pid->max_iout / pid->ki;
    pid->Pwm_return=pid->kp * pid->error + pid->pwmKI + pid->kd * pid->error - pid->last_error;       //位置式PID控制器
	
	if(pid->Pwm_return>200)   pid->Pwm_return=200;                           //限幅
	else if (pid->Pwm_return<-200)  pid->Pwm_return=-200;
		pid->last_error=pid->error;                                     	 //保存上一次偏差 
}

/*
 *:根据循迹传感器pid调节小车转向使小车处于黑线中间
 * 
 *        [in]int retern_track: 循迹传感器输出的值
 *        [in]float TarSpdL:右边电机目标速度,最大速度越1.27m/s
 * @return: 返回调节电机速度的转向pwm
 */
//float ChangeTraceTurn(int track_retern)
//{    
//	
//	int error;
//	error=track_retern;
//	ipwm=PositionPIDToSPEED(error,pid_turn);
//	if(ipwm>150)		ipwm=150;//限幅
//	else if(ipwm<-150)  ipwm=-150;
//	return ipwm;
//}

/*@brief:根据pid调节左边电机到目标速度
 * @param:
 *        [in]int NowEncodeSpdL: 当前左电机编码器测速值
 *        [in]float TarSpdL:左边电机目标速度,最大速度越1.19m/s
 * @return: 返回左边电机计算后的pwm占空比
 */
//int ChangeSpeedMotorL(int NowEncodeSpdL,float TarSpdL)
//{
//	int pwm=0;
//	int error;
//	int TarEncodeSpdL;
//	TarEncodeSpdL=(int)((TarSpdL*ACircleEncoder)/(WheelOneCircleDis*100)+0.5f);//根据目标速度求出目标编码器速度
//	error=NowEncodeSpdL-TarEncodeSpdL;
//	pwm=PositionPIDToSPEED(error,pid);
//	if(pwm>600)		pwm=600;//限幅
//	else if(pwm<-600)  pwm=-600;
//	return pwm;
//}

///*@brief:根据pid调节右边电机到目标速度
// * @param:
// *        [in]int NowEncodeSpdL: 当前右电机编码器测速值
// *        [in]float TarSpdL:右边电机目标速度,最大速度越1.27m/s
// * @return: 返回右边电机计算后的pwm占空比
// */
//int ChangeSpeedMotorR(int NowEncodeSpdR,float TarSpdR)
//{
//	int pwm=0;
//	int error;
//	int TarEncodeSpdR;
//	TarEncodeSpdR=(int)((TarSpdR*ACircleEncoder)/(WheelOneCircleDis*100)+0.5f);//根据目标速度求出目标编码器速度
//	error=NowEncodeSpdR-TarEncodeSpdR;
//	pwm=PositionPIDToSPEED(error,pid);
//	if(pwm>600)		pwm=600;//限幅
//	else if(pwm<-600)  pwm=-600;
//	return pwm;
//}

/*@brief: 让小车根据循迹黑线走
 *@param:
 *        [in]TraceDate: 循迹传感器输出的值
 *        [in]TarSpeed:循迹的目标速度
 *@return: 到达目标点返回1，否则返回0
 */
//void TrackMove(int retern_track,float TarSpeed)
//{
//	int turnpwm=0;
//	int spdpwml=0,spdpwmr=0;
//	int pwml=0,pwmr=0;
//	
//	turnpwm=ChangeTraceTurn(retern_track);
//	
//	spdpwml=ChangeSpeedMotorL(NowEncodeSpdL,TarSpeed);
//	spdpwmr=ChangeSpeedMotorR(NowEncodeSpdR,TarSpeed);
//	
//	
//	pwmr=turnpwm+spdpwmr;
//	if(pwmr>600)		pwmr=600;//限幅
//	else if(pwmr<-600)  pwmr=-600;
//	pwml=-turnpwm+spdpwml;
//	if(pwml>600)		pwml=600;//限幅
//	else if(pwml<-600)  pwml=-600;
//	
////	Set_Pwm_Motor1(pwmr);				//设置电机1占空比
////	Set_Pwm_Motor2(pwml);				//设置电机2占空比
//}
