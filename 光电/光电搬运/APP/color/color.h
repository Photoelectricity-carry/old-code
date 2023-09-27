#ifndef __COLOR_H
#define __COLOR_H
#include "sys.h"



extern u16 amount;


extern u16 Ramount,Gamount,Bamount;
typedef struct   
{
	
	float Rgena;
	float Ggena;
	float Bgena;
}_RGB;									   //用于在调整白平衡后，存放标准值

#define S0 PDout(4)
#define S1 PDout(5)
#define S2 PDout(6)
#define S3 PDout(7)
#define OUT PEin(2)


extern void tcs3200_init(u8 s0,u8 s1);  //
extern void WhiteBalance(void);

extern u16 tcs3200_RED(void);
extern u16 tcs3200_GREEN(void);
extern u16 tcs3200_BLUE(void);

#endif
