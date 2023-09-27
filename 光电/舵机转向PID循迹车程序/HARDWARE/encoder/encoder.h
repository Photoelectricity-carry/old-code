#ifndef __ENCODER_H_
#define __ENCODER_H_

#include "sys.h"

#define ENCODER_TIM_PERIOD (u16)(65535)   //不可大于65535 因为F103的定时器是16位的。


/***********************编码器参数定义**************************/

#define ACircleLeftEncode 1060	//一圈1060
#define ACircleRightEncode 1060	//一圈1060
#define ACircleEncoder ACircleLeftEncode 


/*************************外部变量声明**************************/

extern int Encode_Left;			//定义左轮编码器读取值变量，更改会导致错误
extern int Encode_Right;		//定义右轮编码器读取值变量，更改会导致错误
extern int Encode_Left_ALL;		//定义左轮编码器累加值
extern int Encode_Right_ALL;	//定义右轮编码器累加值
extern int	Encode_Speed;		//定义通过编码器获取的小车前进速度
extern int	Encode_Spin_Speed;	//通过编码器获取的小车旋转速度

/*************************外部函数声明**************************/
extern void Encoder_Init(void);		//编码器初始化函数
extern int Read_Encoder(u8 TIMX);   //读编码器的值



#endif





