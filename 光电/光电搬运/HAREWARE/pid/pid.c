#include "sys.h"
#include "pid.h"
PIDtypedef *pid;
void PID_Init(PIDtypedef *pid)
{
	
	 
    pid->kp = 0.4;
    pid->ki = 0.0005;
    pid->kd = 0.005;
    pid->max_iout = 30000;   //�����޷�
	pid->max_out=200;       //���PID����      
	pid->error=0;          //ѭ������
	pid->last_error=0;     //��һ��ѭ������
	pid->Pwm_return=0;     //pid����ֵ  
	pid->Iout=0;            //����ۼ�
    pid->pwmKI=0;           //������
}

/*λ��ʽPID������
*/
//int PositionPID(float retern_track, PIDtypedef *pid_turn)    //retern_track  ��������ѭ�����������ֵ
//{
//	
//	static float error,Pwm,Iout,last_error;
//	error=retern_track;                         		         //����ƫ��
//	Iout+=error;	                                            //���ƫ��Ļ���
//	Pwm=  pid_turn->kp*error+pid_turn->ki*Iout+ pid_turn->kd*(error-last_error); //λ��ʽPID������
//	last_error=error;                                      	 //������һ��ƫ�� 
//	return Pwm;    
//}

/* Ϊ�ٶ�pidʹ��λ��ʽPID���������Ի���ֵ�����޷�

       [in] float retern_track: ѭ�����������ֵ
 */
void PositionPIDToSPEED(float track_retern,PIDtypedef *pid)
{
	
	pid->error = track_retern;                         		         //����ƫ��
	pid->Iout+=pid->error;	                                            //���ƫ��Ļ���                              //���ƫ��Ļ���
	pid->pwmKI=(pid->ki)*pid->Iout;
	if(pid->pwmKI > pid->max_iout) pid->Iout=pid->max_iout / pid->ki;
    pid->Pwm_return=pid->kp * pid->error + pid->pwmKI + pid->kd * pid->error - pid->last_error;       //λ��ʽPID������
	
	if(pid->Pwm_return>200)   pid->Pwm_return=200;                           //�޷�
	else if (pid->Pwm_return<-200)  pid->Pwm_return=-200;
		pid->last_error=pid->error;                                     	 //������һ��ƫ�� 
}

/*
 *:����ѭ��������pid����С��ת��ʹС�����ں����м�
 * 
 *        [in]int retern_track: ѭ�������������ֵ
 *        [in]float TarSpdL:�ұߵ��Ŀ���ٶ�,����ٶ�Խ1.27m/s
 * @return: ���ص��ڵ���ٶȵ�ת��pwm
 */
//float ChangeTraceTurn(int track_retern)
//{    
//	
//	int error;
//	error=track_retern;
//	ipwm=PositionPIDToSPEED(error,pid_turn);
//	if(ipwm>150)		ipwm=150;//�޷�
//	else if(ipwm<-150)  ipwm=-150;
//	return ipwm;
//}

/*@brief:����pid������ߵ����Ŀ���ٶ�
 * @param:
 *        [in]int NowEncodeSpdL: ��ǰ��������������ֵ
 *        [in]float TarSpdL:��ߵ��Ŀ���ٶ�,����ٶ�Խ1.19m/s
 * @return: ������ߵ��������pwmռ�ձ�
 */
//int ChangeSpeedMotorL(int NowEncodeSpdL,float TarSpdL)
//{
//	int pwm=0;
//	int error;
//	int TarEncodeSpdL;
//	TarEncodeSpdL=(int)((TarSpdL*ACircleEncoder)/(WheelOneCircleDis*100)+0.5f);//����Ŀ���ٶ����Ŀ��������ٶ�
//	error=NowEncodeSpdL-TarEncodeSpdL;
//	pwm=PositionPIDToSPEED(error,pid);
//	if(pwm>600)		pwm=600;//�޷�
//	else if(pwm<-600)  pwm=-600;
//	return pwm;
//}

///*@brief:����pid�����ұߵ����Ŀ���ٶ�
// * @param:
// *        [in]int NowEncodeSpdL: ��ǰ�ҵ������������ֵ
// *        [in]float TarSpdL:�ұߵ��Ŀ���ٶ�,����ٶ�Խ1.27m/s
// * @return: �����ұߵ��������pwmռ�ձ�
// */
//int ChangeSpeedMotorR(int NowEncodeSpdR,float TarSpdR)
//{
//	int pwm=0;
//	int error;
//	int TarEncodeSpdR;
//	TarEncodeSpdR=(int)((TarSpdR*ACircleEncoder)/(WheelOneCircleDis*100)+0.5f);//����Ŀ���ٶ����Ŀ��������ٶ�
//	error=NowEncodeSpdR-TarEncodeSpdR;
//	pwm=PositionPIDToSPEED(error,pid);
//	if(pwm>600)		pwm=600;//�޷�
//	else if(pwm<-600)  pwm=-600;
//	return pwm;
//}

/*@brief: ��С������ѭ��������
 *@param:
 *        [in]TraceDate: ѭ�������������ֵ
 *        [in]TarSpeed:ѭ����Ŀ���ٶ�
 *@return: ����Ŀ��㷵��1�����򷵻�0
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
//	if(pwmr>600)		pwmr=600;//�޷�
//	else if(pwmr<-600)  pwmr=-600;
//	pwml=-turnpwm+spdpwml;
//	if(pwml>600)		pwml=600;//�޷�
//	else if(pwml<-600)  pwml=-600;
//	
////	Set_Pwm_Motor1(pwmr);				//���õ��1ռ�ձ�
////	Set_Pwm_Motor2(pwml);				//���õ��2ռ�ձ�
//}
