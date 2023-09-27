#ifndef _TCS3200_H_
#define _TCS3200_H_

#include "stm32f10x.h"
#include "io_bit.h"

extern u16 amount;
extern u16 R,G,B;
extern  float H,V,S;
extern u8 Rgena,Ggena,Bgena;
extern u16 Ramount,Gamount,Bamount;


#define S0 PAout(5)
#define S1 PAout(7)
#define S2 PAout(4)
#define S3 PAout(6)
#define OUT PAin(8)

void tcs3200_init(u8 s0,u8 s1);
void whitebalance(void);
u16 tcs3200_RED(void);
u16 tcs3200_GREEN(void);
u16 tcs3200_BLUE(void);
int  color_dat_deal(u16 R,u16 G,u16 B);
int RBG_fun(void);

#endif
