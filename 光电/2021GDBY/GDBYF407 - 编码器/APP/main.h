#ifndef MAIN_H
#define MAIN_H

typedef signed char int8_t;
typedef signed short int int16_t;
typedef signed int int32_t;
typedef signed long long int64_t;

/* exact-width unsigned integer types */
typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
typedef unsigned char bool_t;
typedef float fp32;
typedef double fp64;

//云台电机可能can发送失败的情况，尝试使用 随机延迟发送控制指令的方式解决
#define GIMBAL_MOTOR_6020_CAN_LOSE_SLOVE 0

#define SysCoreClock 180

#define RC_NVIC 4

#define CAN1_NVIC 4
#define CAN2_NVIC 4
#define TIM3_NVIC 5
#define TIM6_NVIC 4
#define SPI5_RX_NVIC 5
#define MPU_INT_NVIC 5

#define Latitude_At_ShenZhen 22.57025f


#define UP 		  2000
#define DOWN 		500

#define A1 2450
#define A2 960
#define B1 2050
#define B2 400
#define C1 1620
#define C2 2400
#define D1 1200
#define D2 1950
#define E1 780
#define E2 1500

#define servo_360(angle) TIM_SetCompare1(TIM12,angle)
#define servo_back1(angle) TIM_SetCompare1(TIM9,angle)
#define servo_back2(angle) TIM_SetCompare1(TIM11,angle)
#define servo_A(angle)  TIM_SetCompare2(TIM12,angle)
#define servo_B(angle)  TIM_SetCompare1(TIM4,angle)
#define servo_C(angle)  TIM_SetCompare2(TIM4,angle)
#define servo_D(angle)  TIM_SetCompare4(TIM4,angle)
#define servo_E(angle)  TIM_SetCompare3(TIM4,angle)

#define huidu 	hfm=GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6);\
								hfr=GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7);\
								hfl=GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8);\
								hbm=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1);\
								hbr=GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9);\
								hbl=GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10);\
								hd1=GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1);\
								hd2=GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2);\
								hd3=GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3)    

#define forward 	huidu;\
									if(hfl==0 && hfm==1 && hfr==1){left=7;right=5;}\
									else if(hfl==0 && hfm==0 && hfr==1){left=8;right=4;}\
									else if(hfl==1 && hfm==1 && hfr==0){left=5;right=7;}\
									else if(hfl==1 && hfm==0 && hfr==0){left=4;right=8;}\
									else {left=6;right=6;}\
									PID_Calc(&pid_l,encoder.speed_l,left);\
									PID_Calc(&pid_r,encoder.speed_r,right);\
									motor_speed( pid_l.out, pid_r.out)
									
#define forward0 	huidu;\
									if(hfl==0 && hfm==1 && hfr==1){left=4;right=2;}\
									else if(hfl==0 && hfm==0 && hfr==1){left=5;right=1;}\
									else if(hfl==1 && hfm==1 && hfr==0){left=2;right=4;}\
									else if(hfl==1 && hfm==0 && hfr==0){left=1;right=5;}\
									else {left=3;right=3;}\
									PID_Calc(&pid_l,encoder.speed_l,left);\
									PID_Calc(&pid_r,encoder.speed_r,right);\
									motor_speed( pid_l.out, pid_r.out)

				
#define back  		huidu;\
									if(hbl==0 && hbm==1 && hbr==1){left=-4.5;right=-5.5;}\
									else if(hbl==0 && hbm==0 && hbr==1){left=-4;right=-6;}\
									else if(hbl==1 && hbm==1 && hbr==0){left=-5.5;right=-4.5;}\
									else if(hbl==1 && hbm==0 && hbr==0){left=-6;right=-4;}\
									else {left=-5;right=-5;}\
									PID_Calc(&pid_l,encoder.speed_l,left);\
									PID_Calc(&pid_r,encoder.speed_r,right);\
									motor_speed( pid_l.out, pid_r.out)

#define stop			PID_Calc(&pid_l,encoder.speed_l,0);\
									PID_Calc(&pid_r,encoder.speed_r,0);\
									motor_speed( pid_l.out, pid_r.out)
									
#define clear			encoder.all_num_l=0;\
									encoder.all_num_r=0
									

#ifndef NULL
#define NULL 0
#endif

#ifndef PI
#define PI 3.14159265358979f
#endif

#endif
