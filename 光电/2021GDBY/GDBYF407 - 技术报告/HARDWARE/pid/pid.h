#ifndef __PID_H
#define __PID_H

typedef struct{
  float Kp;
  float Kp_OUT;
  
  float Ki;
  float Ki_OUT;
  
  float Kd;
  float Kd_OUT;
  
  float out;
	float Out;
  
  float err1;
  float err2;
  float err3;
}PidTypeDef;

float PID_calc(float get1, float set, PidTypeDef *PID);
void PID_Init(PidTypeDef *PID,float pid[3]);
#endif
