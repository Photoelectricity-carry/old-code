#ifndef __TCS3200_H
#define __TCS3200_H
#include "sys.h"

extern u16 amount;

extern u16 Rgena,Ggena,Bgena;
extern u16 Ramount,Gamount,Bamount;


#define S0 PBout(10)
#define S1 PBout(12)
#define S2 PBout(14)
#define S3 PBout(13)
#define OUT PBin(15)

void tcs3200_init(u8 s0,u8 s1);  //
void whitebalance(void);
void aj(void);

u16 tcs3200_RED(void);
u16 tcs3200_GREEN(void);
u16 tcs3200_BLUE(void);

#endif

