#ifndef __TCS3200_H
#define __TCS3200_H	 
#include "sys.h"

#define __LED_H	 
#include "sys.h"

extern u16 Ramount,Gamount,Bamount;			//用于存放读取的RGB值
extern u16 amount;							//中断计数，记录每次的频率值
extern u16 R,G,B;							//用于存放通过不同滤波的值
extern u16 tmp;

typedef struct   
{
	
	u16 Rgena;
	u16 Ggena;
	u16 Bgena;
}_RGB;									   //用于在调整白平衡后，存放标准值

extern _RGB RGB;

#define S0 PAout(9)							//TCS3200控制比例端（s0，s1）
#define S1 PAout(10)						
#define S2 PAout(11)						//TCS3200滤波器选择端（s2，s3）
#define S3 PAout(12)						
#define EO PAout(13)						//TCS3200工作使能端
#define OUT PAin(8)						//TCS3200数据输出端

void TCS3200_Init(u8 s0,u8 s1);				//TCS3200初始化函数
void WhiteBalance(void);					//无滤波，调整白平衡
u16 tcs3200_RED(void);						//红滤波，测出r的值
u16 tcs3200_GREEN(void);					//绿滤波，测出g的值
u16 tcs3200_BLUE(void);					//蓝滤波，测出b的值
u16 clour_disguish(void);		//颜色识别


//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
#define LED0 PBout(5)// PB5
#define LED1 PEout(5)// PE5	

void LED_Init(void);//初始化

		 				    
#endif
