#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include "motor.h"
#include "pid.h"
#include "tcs3200.h"
#include "servo.h"
#include "math.h"
#include "truck.h"
#include "exit.h"



#define left_f GPIO_SetBits(GPIOE,GPIO_Pin_9);\
			          GPIO_ResetBits(GPIOE,GPIO_Pin_10)
#define left_b GPIO_SetBits(GPIOE,GPIO_Pin_10);\
			          GPIO_ResetBits(GPIOE,GPIO_Pin_9)	
#define right_f GPIO_SetBits(GPIOE,GPIO_Pin_11);\
			          GPIO_ResetBits(GPIOE,GPIO_Pin_12)	
#define right_b GPIO_SetBits(GPIOE,GPIO_Pin_12);\
			          GPIO_ResetBits(GPIOE,GPIO_Pin_11)
#define stop    GPIO_ResetBits(GPIOE,GPIO_Pin_9);\
								GPIO_ResetBits(GPIOE,GPIO_Pin_10);\
								GPIO_ResetBits(GPIOE,GPIO_Pin_12);\
								GPIO_ResetBits(GPIOE,GPIO_Pin_11)
								
								
#define huidu 	hfm=GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6);\
								hfr=GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7);\
								hfl=GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8);\
								hbm=GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9);\
								hbr=GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10);\
								hbl=GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11);\
								hd1=GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1);\
								hd2=GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2);\
								hd3=GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3)       

#define forward 	huidu;\
									left_f;\
									right_f;\
									if(hfl==1&&hfm==0&&hfr==0)\
										huidu_flag=0;\
									if(hfl==1&&hfm==1&&hfr==0)\
										huidu_flag=1;\
									if(hfl==0&&hfm==1&&hfr==0)\
										huidu_flag=2;\
									if(hfl==0&&hfm==1&&hfr==1)\
										huidu_flag=3;\
									if(hfl==0&&hfm==0&&hfr==1)\
										huidu_flag=4;\
									if(hfl==1&&hfm==1&&hfr==1)\
										huidu_flag=2;\
									xunji_f(huidu_flag)

#define back						huidu;\
												left_b;\
												right_b;\
												if(hbl==1&&hbm==0&&hbr==0)\
													huidu_flag=0;\
												if(hbl==1&&hbm==1&&hbr==0)\
													huidu_flag=1;\
												if(hbl==0&&hbm==1&&hbr==0)\
													huidu_flag=2;\
												if(hbl==0&&hbm==1&&hbr==1)\
													huidu_flag=3;\
												if(hbl==0&&hbm==0&&hbr==1)\
													huidu_flag=4;\
												if(hbl==1&&hbm==1&&hbr==1)\
													huidu_flag=2;\
												xunji_b(huidu_flag)								
#define turn_right  					huidu;\
															left_f;\
															right_b;\
															TIM_SetCompare1(TIM5,800);\
															TIM_SetCompare2(TIM2,800)		
#define turn_left   					huidu;\
															left_b;\
															right_f;\
															TIM_SetCompare1(TIM5,800);\
															TIM_SetCompare2(TIM2,800)		
												
#define up 		  2000
#define down 		500

#define A1 700
#define A2 1600
#define B1 2300
#define B2 1000
#define C1 1900
#define C2 1700
#define D1 1500
#define D2 2200
#define E1 1100
#define E2 810

#define servo_360(angle) TIM_SetCompare1(TIM12,angle)
#define servo_back1(angle) TIM_SetCompare1(TIM9,angle)
#define servo_back2(angle) TIM_SetCompare1(TIM11,angle)
#define servo_A(angle)  TIM_SetCompare2(TIM3,angle)
#define servo_B(angle)  TIM_SetCompare1(TIM4,angle)
#define servo_C(angle)  TIM_SetCompare2(TIM4,angle)
#define servo_D(angle)  TIM_SetCompare3(TIM4,angle)
#define servo_E(angle)  TIM_SetCompare4(TIM4,angle)

//////////////////////////////////////////////////////////////////////////////////
//
//
//
//
//
//
//
///////////////////////////////////////////////////////////////////////////////////
										


extern double tim;
extern int numf,numb;
int hfm,hfr,hfl;
int hbm,hbr,hbl;
int hd1,hd2,hd3,hd4;
int huidu_flag,stop_flag=0;
int i,j,angle=400;
enum c{star,f5,green,white,red,black,blue,g5};
enum e{a1,b1,c1,d1,e1,a2,b2,c2,d2,e2};
double  car_angle[8]={2.0,1.5,1.0,0.5,0,(-0.5),(-1.0),(-1.5)};
int color[5];//={white,blue,red,green,black};
int servo_angle0[3]={2,4,0};
int servo_angle1[5]={2,1,4,3,0};
int servo_angle2[5]={4,0,2,3,1};



/////////////////////////////////////////////////////////////////////////////////////////
//
//
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////


void xunji_f(int w)//前进
{ 
	switch(w)
	{
		case 0:		motor_set(700,1400);	break;      //111 1 011
		case 1:		motor_set(1000,1300);	break;      //111 0 011
		case 2:		motor_set(1200,1200);	break;      //111 0 111  //正中间位置
		case 3:		motor_set(1300,1000);	break;      //110 0 111
		case 4:		motor_set(1400,700);	break;      //110 1 111
		default:  motor_set(1200,1200);	break;
	}
}

void xunji_b(int u)//后退
{
	switch(u)
	{
		case 0:		motor_set(1200,700);	break;      //111 1 011
		case 1:		motor_set(1100,900);	break;      //111 0 011
		case 2:		motor_set(1000,1000);	break;      //111 0 111  //正中间位置
		case 3:		motor_set(900,1200);	break;      //110 0 111
		case 4:		motor_set(700,1100);	break;      //110 1 111
		default:  motor_set(1000,1000);	break;
	}
}





void car_angle_change(double angle)
{
	int i;
	for(i=0;i<8;i++)
	{
		car_angle[i]-=angle;
		if(car_angle[i]>2.0) car_angle[i]=car_angle[i]-4.0;
		if(car_angle[i]<=-2.0) car_angle[i]=car_angle[i]+4.0;
	}
}

void turn(double angle)
{
		tim=0;
	  double ang=angle;
	  if(angle>0)
		{
			while(1)
			{
				turn_left;
				if(tim>angle) if(hfm==1) break;
			}
		}
		else if(angle<0)
		{
			while(1)
			{
				turn_right;
				if(tim>-angle) if(hfm==1) break;
			}
		}
		tim=0;
		while(1){stop;if(tim>0.5) break;}
		car_angle_change(ang);
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
		default:break;
	}
}


int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init(84);
	EXTIX_Init();
	Motor_GPIO_init();
	TRUCK_GPIO();
	tcs3200_init(1,1);//n=clour_disguish();
	MotorL_PWM1_Init(5000-1,1);
	MotorR_PWM2_Init(5000-1,1);
	SERVO_TIM12_Init(20000-1,84-1);
	SERVO_TIM9_Init(20000-1,168-1);
	SERVO_TIM11_Init(20000-1,168-1);
	SERVO_TIM3_Init(20000-1,84-1);
	SERVO_TIM4_Init(20000-1,84-1);
	TIM7_Int_Init(10000-1,84-1);
	servo_360(C1);
	servo_A(up);
	servo_B(up);
	servo_C(up);
	servo_D(up);
	servo_E(up);
	servo_back2(1000);
	servo_back1(1500);//1380
	delay_ms(2000);
	
  while(1){
/////////////////////////////////////////////////////////////////////		
//第一步
//	
//	
//
//
//	
//	
/////////////////////////////////////////////////////////////////////

	
//////////////////////////////////////////////////////////////////////第一次前进
  	tim=0;
		while(1)                                                
		{
			forward;
			servo(c1,up);
   		if(tim>3) {if(hd3==1) {delay_ms(1);huidu;if(hd3==1) break;}}
		}
		tim=0;
		while(1){stop;if(tim>0.1) break;}
		servo(c2,down);
		delay_ms(1000);
////////////////////////////////////////////////////////////////后退
		tim=0;
		while(1)                                               
		{
		  back;           //1.5 
			servo(c2,down);
			if(tim>0.2) {if(hd1==1){delay_ms(1);huidu;if(hd1==1)break;}}
		}
		tim=0;
		while(1){stop;if(tim>0.2) break;}	
		color[0]=clour_disguish();
/////////////////////////////////////////////////////////////////////////右转向	
		turn(car_angle[blue]);
///////////////////////////////////////////////////////////////////////////前进
		tim=0;
		while(1)                                         
		{
			forward;
			servo(e1,up);
			if(tim>0.2) {if(hd3==1) {delay_ms(1);huidu;if(hd3==1) break;}}
		}
		tim=0;
		while(1){stop;if(tim>0.3) break;}	
		servo(e2,down);
		delay_ms(1000);
///////////////////////////////////////////////////////////////////////////////////后退
		tim=0;		
		while(1)                                                
		{
			back;
			servo(e2,down);
			if(tim>0.2){if(hd1==1){delay_ms(1);huidu;if(hd1==1)break;}}
		}
		tim=0;
		while(1){stop;if(tim>0.2) break;}
		color[2]=clour_disguish();
/////////////////////////////////////////////////////////////////////////////转	
		turn(car_angle[green]);
/////////////////////////////////////////////////////////////////////////////前进
		tim=0;
		while(1)                                                
		{
			forward;
			servo(a1,up);
			if(tim>0.2) {if(hd3==1) {delay_ms(1); huidu;if(hd3==1) break;}}
		}
		tim=0;
		while(1){stop;if(tim>0.1) break;}
		servo(a2,down);
		delay_ms(1000);
///////////////////////////////////////////////////////////////////////////////////后退
		tim=0;		
		while(1)                                                
		{
			back;
			servo(a2,down);
			if(tim>0.2){if(hd1==1){delay_ms(1);huidu;if(hd1==1)break;}}
		}
		tim=0;
		while(1){stop;if(tim>0.2) break;}
		color[4]=clour_disguish();
///////////////////////////////////////////////////////
		for(i=0,j=0;i<3;i++,j=j+2)
		{
			turn(car_angle[color[j]]);
			tim=0;
			while(1)                                                
			{
				forward;
				servo(servo_angle0[i],down);
				if(tim>1.5) {if(hd3==1) {delay_ms(1);huidu;if(hd3==1) break;}}
			}
			tim=0;
			while(1){stop;if(tim>0.1) break;}
			servo(servo_angle0[i],up);
			delay_ms(1000);
			tim=0;		
			while(1)                                                
			{
				back;
				if(tim>1.5){if(hd1==1){delay_ms(1);huidu;if(hd1==1)break;}}
			}
			tim=0;
			while(1){stop;if(tim>0.1) break;}
		}
////////////////////////////////////////////////////////////////
//
//
//
//
//
//////////////////////////////////////////////////////////////////	
		turn(car_angle[f5]);
/////////////////////////////////////////////////////		
		tim=0;
		while(1)                                                
		{
			forward;
			servo(d1,up);
   		if(tim>1) {if(hd3==1) {delay_ms(1);huidu;if(hd3==1) break;}}
		}
		tim=0;
		while(1){stop;if(tim>0.2) break;}
		tim=0;
		while(1)
		{
			forward;
			if(tim>0.55) break;
		}
		tim=0;
		while(1){stop;if(tim>0.5) break;}
		servo_A(down);
		servo_B(down);
		servo_C(down);
		servo_D(down);
		servo_E(down);
		delay_ms(1000);
		tim=0;
		while(1)
		{
			back;
			servo(b2,down);
			if(tim>2){if(hd1==1){delay_ms(1);huidu;if(hd1==1)break;}}
		}		
		tim=0;
		while(1){stop;if(tim>0.2) break;}
		color[1]=clour_disguish();
////////////////////////////////////////////////////////////////////////
		if((color[0]!=2)&&(color[1]!=2)&&(color[2]!=2)&&(color[4]!=2)) color[3]=2;
		if((color[0]!=3)&&(color[1]!=3)&&(color[2]!=3)&&(color[4]!=3)) color[3]=3;
		if((color[0]!=4)&&(color[1]!=4)&&(color[2]!=4)&&(color[4]!=4)) color[3]=4;
		if((color[0]!=5)&&(color[1]!=5)&&(color[2]!=5)&&(color[4]!=5)) color[3]=5;
		if((color[0]!=6)&&(color[1]!=6)&&(color[2]!=6)&&(color[4]!=6)) color[3]=6;
////////////////////////////////////////////////	
		for(i=0;i<5;i++)
		{
			turn(car_angle[color[i]]);
			tim=0;
			while(1)                                                
			{
				forward;
				servo(servo_angle1[i],down);
				if(tim>1.1) break;
			}
			tim=0;
			while(1){stop;if(tim>0.1) break;}
			servo(servo_angle1[i],up);
			delay_ms(1000);
			tim=0;		
			while(1)                                                
			{
				back;
				if(tim>1.2){if(hd1==1){delay_ms(1);huidu;if(hd1==1)break;}}
			}
			tim=0;
			while(1){stop;if(tim>0.1) break;}
		}
//////////////////////////////////////////////////////////////
//
//
//
//
////////////////////////////////////////////////////////////////
		turn(car_angle[g5]);
/////////////////////////////////////////////////////		
		tim=0;
		while(1)                                                
		{
			forward;
			servo(d1,up);
   		if(tim>1.2) {if(hd3==1) {delay_ms(1);huidu;if(hd3==1) break;}}
		}
		tim=0;
		while(1){stop;if(tim>0.2) break;}
		tim=0;
		while(1)
		{
			forward;
			if(tim>0.55) break;
		}
		tim=0;
		while(1){stop;if(tim>0.2) break;}
		servo_A(down);
		servo_B(down);
		servo_C(down);
		servo_D(down);
		servo_E(down);
		delay_ms(1000);
		tim=0;
		while(1)
		{
			back;
			if(tim>2){if(hd1==1){delay_ms(1);huidu;if(hd1==1)break;}}
		}		
		tim=0;
		while(1){stop;if(tim>0.2) break;}
////////////////////////////////////////////////	
		for(i=0;i<5;i++)
		{
			turn(car_angle[color[i]]);
			tim=0;
			while(1)                                                
			{
				forward;
				servo(servo_angle2[i],down);
				if(tim>0.2){if(hd3==1) {delay_ms(1);huidu;if(hd3==1) break;}}
			}
			tim=0;
			while(1){stop;if(tim>1) break;}
			servo(servo_angle2[i],up);
			delay_ms(1000);
			tim=0;		
			while(1)                                                
			{
				back;
				if(tim>0.5){if(hd1==1){delay_ms(1);huidu;if(hd1==1)break;}}
			}
			tim=0;
			while(1){stop;if(tim>0.5) break;}
		}		
////////////////////////////////////////////////////
		for(i=0;i<5;i++)
		{
			delay_ms(500);
			turn(-0.5);

			if(i==1||i==2||i==3)
			{
				tim=0;
				while(1)
				{
					back;
					servo_back1(1450);
					servo_back2(1500);
					if(tim>0.5){if(hd2==1) {delay_ms(1);huidu;if(hd2==1) break;}}
				}
				tim=0;
				while(1)
				{
					back;
					servo_back1(1450);
					servo_back2(1500);
					if(tim>0.1) break;
				}
				tim=0;
				while(1){stop;if(tim>0.3) break;}
				
				servo_back2(500);
				delay_ms(2000);
				servo_back1(1650);
				delay_ms(2000);
				
				tim=0;
				while(1)
				{
					back;
					if(tim>0.5){if(hd3==1) {delay_ms(1);huidu;if(hd3==1) break;}}
				}
				tim=0;
				while(1)
				{
					back;
					if(tim>0.1)break;
				}
				tim=0;
				while(1){stop;if(tim>0.3) break;}
				
				servo_back2(1500);
				delay_ms(1000);
				servo_back1(1450);
				delay_ms(1000);
				servo_back2(500);
				delay_ms(1000);
				servo_back1(1650);
				delay_ms(1000);
				tim=0;
				while(1)
				{
					back;
					if(tim>0.5){if(hd2==1) {delay_ms(1);huidu;if(hd2==1) break;}}
				}
				tim=0;
				while(1){stop;if(tim>0.3) break;}
				servo_back2(1500);
				delay_ms(1000);
				servo_back1(1450);
				delay_ms(1000);
				servo_back2(500);
				delay_ms(1000);
				servo_back2(1500);
				delay_ms(1000);
				tim=0;
				while(1)
				{
					forward;
					if(tim>0.5){if(hd1==1&&hd2==1) break;}
				}
				while(1){stop;if(tim>0.3) break;}
			}
			else
			{
				tim=0;
				while(1)
				{
					back;
					servo_back1(1450);
					servo_back2(1500);
					if(tim>1.0){if(hd2==1) {delay_ms(1);huidu;if(hd2==1) break;}}
				}
				tim=0;
				while(1)
				{
					back;
					if(tim>0.2)break;
				}
				tim=0;
				while(1){stop;if(tim>0.3) break;}
				
				servo_back2(1500);
				delay_ms(1000);
				servo_back1(1450);
				delay_ms(1000);
				servo_back2(500);
				delay_ms(1000);
				servo_back1(1650);
				delay_ms(1000);
				tim=0;
				while(1)
				{
					back;
					if(tim>0.5){if(hd2==1) {delay_ms(1);huidu;if(hd2==1) break;}}
				}
				tim=0;
				while(1){stop;if(tim>0.3) break;}
				servo_back2(1500);
				delay_ms(1000);
				servo_back1(1450);
				delay_ms(1000);
				servo_back2(500);
				delay_ms(1000);
				servo_back2(1500);
				delay_ms(1000);
				tim=0;
				while(1)
				{
					huidu;
									left_f;
									right_f;
									if(hfl==1&&hfm==0&&hfr==0)
										huidu_flag=0;
									if(hfl==1&&hfm==1&&hfr==0)
										huidu_flag=1;
									if(hfl==0&&hfm==1&&hfr==0)
										huidu_flag=2;
									if(hfl==0&&hfm==1&&hfr==1)
										huidu_flag=3;
									if(hfl==0&&hfm==0&&hfr==1)
										huidu_flag=4;
									if(hfl==1&&hfm==1&&hfr==1)
										huidu_flag=2;
						switch(huidu_flag)
						{
							case 0:		motor_set(500,1200);	break;      //111 1 011
							case 1:		motor_set(800,1100);	break;      //111 0 011
							case 2:		motor_set(1000,1000);	break;      //111 0 111  //正中间位置
							case 3:		motor_set(1100,800);	break;      //110 0 111
							case 4:		motor_set(1200,500);	break;      //110 1 111
							default:  motor_set(1100,1000);	break;
						}
					if(tim>2.5){if(hd2==1){delay_ms(1);huidu;if(hd2==1)break;}}
				}
				while(1){stop;if(tim>0.3) break;}
			}
		}
		delay_ms(500);
		turn(car_angle[star]);
		tim=0;
		while(1)
		{
			forward;
			if(tim>2){if(hd2==1) {delay_ms(1);huidu;if(hd2==1) break;}}
		}
		while(1){stop; }
	}
}
