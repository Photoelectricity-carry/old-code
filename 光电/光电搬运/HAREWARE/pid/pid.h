#ifndef __PID_H
#define __PID_H
#include "sys.h"
//����pid�ṹ��
typedef struct
{
	float kp;
	float ki;
	float kd;
	float max_out;
	float max_iout;
	float error;          //ѭ������
	float last_error;     //��һ��ѭ������
	float Pwm_return;     //pid����ֵ  
	float Iout;            //����ۼ�
    float pwmKI;           //������
}PIDtypedef;


extern void PID_Init(PIDtypedef *pid);
extern void PositionPIDToSPEED(float track_retern,PIDtypedef *pid);

////����ת��pid�����ṹ��
//typedef struct
//{
//	.kp=100,			//��ֵ����ֵ60
//	.ki=0,			//��ֵ����ֵ
//	.kd=-34			//��ֵ΢��ֵ-45
//}pidturn;		
////�����ٶ�pid�����ṹ��
//_PID SpdPdate=
//{
//	.kp=-50,			//��ֵ����ֵ-80
//	.ki=-6,			//��ֵ����ֵ-10
//	.kd=0			//��ֵ΢��ֵ
//};	
#endif
