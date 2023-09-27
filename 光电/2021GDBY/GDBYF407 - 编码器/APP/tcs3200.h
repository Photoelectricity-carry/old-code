#ifndef __TCS3200_H
#define __TCS3200_H
#include "stm32f4xx.h"
#include "delay.h"
#include "main.h"

extern u16 Ramount,Gamount,Bamount;			//???????RGB?
extern u16 amount;							//????,????????
extern u16 R,G,B;							//????????????
extern u16 tmp;



typedef struct   
{
	
	float Rgena;
	float Ggena;
	float Bgena;
}_RGB;//?????????,?????

typedef struct   
{
	
	float H;
	float L;
	float r;
	float g;
	float b;
}color_info_t;//?????????,?????

#define S0 PBout(10)				//TCS3200?????(s0,s1)
#define S1 PBout(11)						
#define S2 PEout(13)			//TCS3200??????(s2,s3)
#define S3 PEout(14)						
#define OUT PAin(3)				//TCS3200?????
//S0--->PA4		S1--->PA5		S2--->PA6		S3--->PA7		OUT--->PA3




void exit_init(void);
void EXTI3_IRQHandler(void);
extern void tcs3200_init(u8 s0,u8 s1); 				//TCS3200?????
void WhiteBalance(void);					//???,?????
extern u16 tcs3200_RED(void);						//???,??r??
extern u16 tcs3200_GREEN(void);					//???,??g??
extern u16 tcs3200_BLUE(void);					//???,??b??
int clour_disguish(void);		//????


#endif




