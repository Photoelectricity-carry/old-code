#ifndef  __ADC_H
#define __ADC_H
#include "stm32f4xx.h"

extern u16  Get_Adc(int n); 
extern u16 Get_Adc_Average(int n); 

extern void  Adc_Init(void);
#endif
