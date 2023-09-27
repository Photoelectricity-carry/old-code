#ifndef _UART_H_
#define _UART_H_
#include "stm32f10x.h"


extern u8 rec_buf[100];
extern u8 rec_sta;
extern u16 rec_len;
extern u16 len;

void uart1_init(u32 bond);
void uart2_init(u32 bond);
void uart1_send_string(u8 *p);
void uart2_send_string(u8 *p);
void clear_buf(u8 buf[100]);
u8 hex_to_asc(u8 hex);
u32 get_ten(u8 i);
float get_zero_ten(u8 i);
float asc_to_ten(void);
float asc_to_8808alcd1_ten(void);

#endif




