#include "pid.h"

void PID_Init(PidTypeDef *PID,float pid[3]){
    PID->Kp = pid[0];
    PID->Ki = pid[1];
    PID->Kd = pid[2];
  
}

float PID_calc(float get, float set, PidTypeDef *PID){
  
  PID->err1 = set - get;
  
  PID->Kp_OUT  = PID->Kp * (PID->err1 - PID->err2);
  PID->Ki_OUT  = PID->Ki * PID->err1;
  PID->Kd_OUT  = PID->Kd * (PID->err1 - 2*PID->err2 + PID->err3);
  
  PID->out += PID->Kp_OUT + PID->Ki_OUT + PID->Kd_OUT;

  PID->err2 = PID->err1;
	PID->err3 = PID->err2;
  
	if(PID->out>1500) PID->out=1500;
	if(PID->out<-1500) PID->out=-1500;
	
  return PID->out;
}
