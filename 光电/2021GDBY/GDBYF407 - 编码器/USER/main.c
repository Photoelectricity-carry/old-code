#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include "motor.h"
#include "servo.h"
#include "track.h"
#include "pid.h"
#include "main.h"
#include "tcs3200.h"

extern int read_encoder_l(void);
extern int read_encoder_r(void);
extern void PID_clear(PidTypeDef *pid);
extern EcoderTypeDef encoder;
extern double time;

enum c{star,f5,green,white,red,black,blue,g5};
enum e{a1,b1,c1,d1,e1,a2,b2,c2,d2,e2};

PidTypeDef pid_l,pid_r;

int hfm,hfr,hfl,hbm,hbr,hbl,hd1,hd2,hd3;
double left,right;

int i,j,n;
int color[5]={0,0,0,0,0};//{white,blue,red,green,black};
int servo_angle0[3]={2,4,0};
int servo_angle1[5]={2,1,4,3,0};
int servo_angle2[5]={4,0,2,3,1};
const fp32 PID[3]={1000.0f,0.1f,5.0f};
int car_angle[8]={1600,1200,800,400,0,(-400),(-800),(-1200)};

void turn(int encoder);
void servo(int a,int c);


int main(void)
{
	PID_Init(&pid_l,PID_POSITION,PID,5000,5000);
	PID_Init(&pid_r,PID_POSITION,PID,5000,5000);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init(84);
	TRUCK_GPIO_Init();
	encoder_tim1_init();
	encoder_tim3_init();
	MotorL_PWM_Init(5000-1,1);
	MotorR_PWM_Init(5000-1,1); 
	Motor_GPIO_init();
	SERVO_TIM12_Init(20000-1,84-1);
	SERVO_TIM9_Init(20000-1,168-1);
	SERVO_TIM11_Init(20000-1,168-1);
	SERVO_TIM4_Init(20000-1,84-1);
	TIM7_Int_Init(1000-1,840-1);
	exit_init();
	tcs3200_init(1,1);
	servo_360(C1);
	servo_A(UP);
	servo_B(UP);
	servo_C(UP);
	servo_D(UP);
	servo_E(UP);
	servo_back1(1500);//1700
	servo_back2(2000);//900
	delay_ms(2000);
	
	encoder.all_num_l=0;
	encoder.all_num_r=0;
	
	
	
  while(1){
////////////////////////////////////////////////////////////////////
//
//		
//		
//		
//
////////////////////////////////////////////////////////////////////
		while(1)                                                
		{
			forward;
			servo(c1,UP);
   		if(encoder.all_num_r>5000) if(hd1==1)break;
		}
		clear;
		time=0; while(1){ stop; if(time>0.1) break;}	
		time=0;
		while(1)
		{	
			stop;
			servo(c1,DOWN);
			if(time>1) break;
		}	
		time=0;
		while(1)
		{	
			stop;
			servo(c2,DOWN);
			if(time>2) break;
		}	
		time=0;
		while(1)
		{
			stop;
			color[2]=clour_disguish();
			if(time>0.5) break;
		}
		while(1)                                                
		{
			back;
			servo(e1,UP);
   		if(hd2==1) break;
		}
		clear;
		time=0;
		while(1){stop;if(time>0.5) break;}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////		
		turn(car_angle[blue]);
		time=0; while(1){ stop; if(time>0.5) break;}	
		while(1)                                                
		{
			forward;
			servo(e1,UP);
   		if(hd1==1) {delay_ms(1);huidu;if(hd1==1) break;}
		}
		clear;
		time=0; while(1){stop;if(time>0.1) break;}
		time=0;
		while(1)
		{	
			stop;
			servo(e1,DOWN);
			if(time>1) break;
		}	
		time=0;
		while(1)
		{	
			stop;
			servo(e2,DOWN);
			if(time>2) break;
		}	
		time=0;
		while(1)
		{
			color[4]=clour_disguish();
			if(time>0.5) break;
		}
		while(1)                                                
		{
			back;
			servo(a1,UP);
   		if(hd2==1) {delay_ms(1);huidu;if(hd2==1) break;}
		}
		clear;
		time=0; while(1){stop;if(time>0.5) break;}
////////////////////////////////////////////////////////////////////////////	
////////////////////////////////////////////////////////////////////////////
		turn(car_angle[green]);
		time=0; while(1){ stop; if(time>0.5) break;}	
		while(1)                                                
		{
			forward;
			servo(a1,UP);
   		if(hd1==1) {delay_ms(1);huidu;if(hd1==1) break;}
		}
		clear;
		time=0;
		while(1){stop;if(time>0.1) break;}
		time=0;
		while(1)
		{	
			stop;
			servo(a1,DOWN);
			if(time>1) break;
		}	
		time=0;
		while(1)
		{	
			stop;
			servo(a2,DOWN);
			if(time>2) break;
		}
		time=0;		
		while(1)
		{
			color[0]=clour_disguish();
			if(time>0.5) break;
		}
		while(1)                                                
		{
			back;
   		if(hd2==1) {delay_ms(1);huidu;if(hd2==1) break;}
		}
		clear;
		time=0;
		while(1){stop;if(time>0.5) break;}
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////		
		for(i=0;i<3;i++)
		{
			turn(car_angle[color[servo_angle0[i]]]);
			time=0;
			while(1)                                                
			{
				forward;
				servo(servo_angle0[i],DOWN);
				if(encoder.all_num_r>3000) break;
			}
			clear;
			time=0; while(1){stop;if(time>0.2) break;}
			time=0;
			while(1)
			{
				servo(servo_angle0[i],UP);
				stop;
				if(time>1) break;
			}	
			clear;
			while(1)                                                
			{
				back;
				if(encoder.all_num_r<-3000)if(hd2==1)break;
			}
			time=0;
			while(1){stop;if(time>0.2) break;}
			clear;
		}
//////////////////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////////////////
		turn(car_angle[f5]);
		time=0; while(1){ stop; if(time>0.5) break;}	
		while(1)
		{
			servo(d1,UP);
			forward;
			if(encoder.all_num_r>2000) if(hd1==1) break;
		}
		clear;
		while(1)
		{
			forward0;
			servo_A(UP);
			servo_B(UP);
			servo_C(UP);
			servo_D(UP);
			servo_E(UP);
			if(encoder.all_num_r>1130) break;
		}
		servo_A(DOWN);
		servo_B(DOWN);
		servo_C(DOWN);
		servo_D(DOWN);
		servo_E(DOWN);
		time=0; while(1){ stop; if(time>1) break;}	
		time=0;
		while(1)
		{
			stop;
			servo(b2,DOWN);
			if(time>2) break;
		}		
		time=0;
		while(1)
		{
			stop;
			color[1]=clour_disguish();
			if(time>0.5) break;
		}
		clear;
		while(1)                                                
		{
			back;
			if(encoder.all_num_r<-3000)if(hd2==1)break;
		}
		color[3]=20-color[1]-color[2]-color[4]-color[0];
/////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////		
		for(i=0,j=0;i<5;i++,j++)
		{
			clear;
			turn(car_angle[color[servo_angle1[i]]]);
			time=0;
			while(1)                                                
			{
				forward;
				servo(servo_angle1[i],DOWN);
				if(encoder.all_num_r>2000)break;
			}
			clear;
			time=0; while(1){stop;if(time>0.2) break;}
			time=0;
			while(1)
			{
				servo(servo_angle1[i],UP);
				stop;
				if(time>1) break;
			}	
			clear;
			while(1)                                                
			{
				back;
				if(encoder.all_num_r<-1000)if(hd2==1)break;
			}
			time=0;
			while(1){stop;if(time>0.2) break;}
			clear;
		}
//////////////////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////////////////
		turn(car_angle[g5]);
		time=0; while(1){ stop; if(time>0.5) break;}	
		while(1)
		{
			servo(d1,UP);
			forward;
			if(encoder.all_num_r>2000) if(hd1==1) break;
		}
		clear;
		while(1)
		{
			forward0;
			servo_A(UP);
			servo_B(UP);
			servo_C(UP);
			servo_D(UP);
			servo_E(UP);
			if(encoder.all_num_r>1130) break;
		}
		servo_A(DOWN);
		servo_B(DOWN);
		servo_C(DOWN);
		servo_D(DOWN);
		servo_E(DOWN);
		time=0; while(1){ stop; if(time>1) break;}	
		clear;
		while(1)                                                
		{
			back;
			if(encoder.all_num_r<-3000)if(hd2==1)break;
		}
		time=0; while(1){ stop; if(time>0.5) break;}	
/////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////		
		for(i=0;i<5;i++)
		{
			clear;
			turn(car_angle[color[servo_angle1[i]]]);
			time=0;
			while(1)                                                
			{
				forward;
				servo(servo_angle2[i],DOWN);
				if(encoder.all_num_r>800)break;
			}
			clear;
			time=0; while(1){stop;if(time>1) break;}
			time=0;
			while(1)
			{
				servo(servo_angle2[i],UP);
				stop;
				if(time>1) break;
			}	
			clear;
			while(1)                                                
			{
				back;
				if(hd2==1)break;
			}
			time=0;
			while(1){stop;if(time>0.2) break;}
			clear;
		}		
		time=0;while(1){stop;if(time>0.2) break;}
///////////////////////////////////////////////////////////////////////////////////////////
//
//		
///////////////////////////////////////////////////////////////////////////////////////////		
		clear;
		turn(car_angle[blue]);
		time=0; while(1){ stop; if(time>0.2) break;}	
		for(i=0;i<5;i++)
		{
			clear;
			if(i>0)
			{
				while(1)
				{
					huidu;
					PID_Calc(&pid_l,encoder.speed_l,3);
					PID_Calc(&pid_r,encoder.speed_r,-3);
					motor_speed( pid_l.out, pid_r.out);
					if(encoder.all_num_l>400) {if(hbm==1||hbr==1||hbl==1) break;}
				}
				for(int i=0;i<8;i++)
				{
					car_angle[i]-=-400;
					if(car_angle[i]>1600) car_angle[i]=car_angle[i]-3200;
					if(car_angle[i]<=-1600) car_angle[i]=car_angle[i]+3200;
				}
				clear;
				time=0; while(1){ stop; if(time>0.5) break;}	
			}
		  while(1)
			{
				back;
				servo_back1(1500);
				servo_back2(2000);
				if(encoder.all_num_r<-1500) break;
			}
			time=0;while(1){stop;if(time>0.2) break;}
			while(1)
			{
				stop;
				servo_back1(1500);
				servo_back2(900);
				if(time>0.5) break;
			}
			time=0;
			while(1)
			{
				stop;
				servo_back1(1700);
				servo_back2(900);
				if(time>0.3) break;
			}
			while(1)
			{
				back;
				servo_back1(1700);
				servo_back2(900);
				if(encoder.all_num_r<-3000) break;
			}
			time=0;
			while(1)
			{
				stop;
				servo_back1(1700);
				servo_back2(1300);
				if(time>0.3) break;
			}
			time=0;
			while(1)
			{
				stop;
				servo_back1(1500);
				servo_back2(1300);
				if(time>0.5) break;
			}		
			time=0;
			while(1)
			{
				stop;
				servo_back1(1500);
				servo_back2(900);
				if(time>0.3) break;
			}
			time=0;
			while(1)
			{
				stop;
				servo_back1(1700);
				servo_back2(900);
				if(time>0.3) break;
			}	
			while(1)
			{
				back;
				servo_back1(1700);
				servo_back2(900);
				if(hd3==1) break;
			}
			time=0;
			while(1)
			{
				stop;
				servo_back1(1700);
				servo_back2(1300);
				if(time>0.3) break;
			}
			time=0;
			while(1)
			{
				stop;
				servo_back1(1500);
				servo_back2(1300);
				if(time>0.5) break;
			}		
			time=0;
			while(1)
			{
				stop;
				servo_back1(1500);
				servo_back2(900);
				if(time>0.3) break;
			}
			clear;
			time=0;while(1){stop;if(time>0.1) break;}		
			clear;
			while(1)
			{
				forward;
				if(encoder.all_num_r>20) break;//800 2000 3000  -1500 -3000 
			}
			time=0;while(1){stop;if(time>0.5) break;}	
			time=0;
			while(1)
			{
				stop;
				servo_back1(1500);
				servo_back2(2000);
				if(time>0.8) break;
			}	
			clear;
			while(1)
			{
				forward;
				if(encoder.all_num_r>3000) if(hd3==1)break;
			}
			time=0;while(1){stop;if(time>0.5) break;}
			clear;
		}
		time=0;while(1){stop;if(time>0.5) break;}
		turn(car_angle[star]);
		clear;
			while(1)
			{
				forward;
				if(encoder.all_num_r>4000) break;
			}
		while(1) {stop;}
	}
}








void turn(int encod)
{
	int en=encod;
	if(encod>0)
	{
		while(1)
		{
			huidu;
			PID_Calc(&pid_l,encoder.speed_l,-3);
			PID_Calc(&pid_r,encoder.speed_r,3);
			motor_speed( pid_l.out, pid_r.out);
			if(encoder.all_num_r>encod)if(hfm==1||hfr==1||hfl==1) break;
		}
	}
	if(encod<=0)
	{
		while(1)
		{
			huidu;
			PID_Calc(&pid_l,encoder.speed_l,3);
			PID_Calc(&pid_r,encoder.speed_r,-3);
			motor_speed( pid_l.out, pid_r.out);
			if(encoder.all_num_l>-encod) if(hfm==1||hfr==1||hfl==1) break;
		}
	}
	for(int i=0;i<8;i++)
	{
		car_angle[i]-=en;
		if(car_angle[i]>1600) car_angle[i]=car_angle[i]-3200;
		if(car_angle[i]<=-1600) car_angle[i]=car_angle[i]+3200;
	}
	clear;
	time=0;
	while(1)
		{
			stop;
			if(time>0.1) break;
		}
}

void servo(int a,int c)
{
	switch(a)
	{
		case 0: servo_360(A1); break;
		case 1: servo_360(B1); break;
		case 2: servo_360(C1); break;
		case 3: servo_360(D1); break;
		case 4: servo_360(E1); break;
		case 5: servo_360(A2); break;
		case 6: servo_360(B2); break;
		case 7: servo_360(C2); break;
		case 8: servo_360(D2); break;
		case 9: servo_360(E2); break;
		default:break;
	}
	switch(a)
	{
		case 0: servo_A(c); break;
		case 1: servo_B(c); break;
		case 2: servo_C(c); break;
		case 3: servo_D(c); break;
		case 4: servo_E(c); break;
		case 5: servo_A(c); break;
		case 6: servo_B(c); break;
		case 7: servo_C(c); break;
		case 8: servo_D(c); break;
		case 9: servo_E(c); break;
		default:break;
	}
}
