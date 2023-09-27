#ifndef TCS_H
#define TCS_H
#include "main.h"
#include "stm32f4xx.h"

extern u16 amount;

extern void tcs3200_init(void);
extern void whitebalance(void);

extern void s0_high(void);
extern void s1_high(void);
extern void s2_high(void);
extern void s3_high(void);
extern void s0_low(void);
extern void s1_low(void);
extern void s2_low(void);
extern void s3_low(void);

extern u16 tcs3200_RED(void);
extern u16 tcs3200_GREEN(void);
extern u16 tcs3200_BLUE(void);
#endif
