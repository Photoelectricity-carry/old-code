#ifndef __PID_H
#define __PID_H
#include "sys.h"
//定义pid结构体
typedef struct
{
	float kp;
	float ki;
	float kd;
	float max_out;
	float max_iout;
	float error;          //循迹返回
	float last_error;     //上一次循迹返回
	float Pwm_return;     //pid返回值  
	float Iout;            //误差累加
    float pwmKI;           //积分项
}PIDtypedef;


extern void PID_Init(PIDtypedef *pid);
extern void PositionPIDToSPEED(float track_retern,PIDtypedef *pid);

////定义转向pid参数结构体
//typedef struct
//{
//	.kp=100,			//赋值比例值60
//	.ki=0,			//赋值积分值
//	.kd=-34			//赋值微分值-45
//}pidturn;		
////定义速度pid参数结构体
//_PID SpdPdate=
//{
//	.kp=-50,			//赋值比例值-80
//	.ki=-6,			//赋值积分值-10
//	.kd=0			//赋值微分值
//};	
#endif
