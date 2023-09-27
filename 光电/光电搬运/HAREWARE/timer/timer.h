#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"

extern void TIM3_PWM_Init(u16 arr,u16 psc);
extern void TIM1_PWM_Init(u16 arr,u16 psc);
extern float HF_Get_Encode_TIM4(void);
extern void TIM4_Encoder_Init(u16 arr,u16 psc);




#endif
