#ifndef __TRUCK_H
#define __TRUCK_H
#include "stm32f4xx.h"
#include "sys.h" 


extern u8 USART_RX[3];         		//����״̬���	

//����3��ʼ��
void Usart3_Init(void);
void Read_Data(u16 *Data);
void usart3_init(u32 bound);
void motor_set(int speed_l_set,int speed_r_set);

void TRUCK_GPIO(void);



#endif
