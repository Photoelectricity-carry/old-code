#ifndef TRACK_H
#define TRACK_H

#include "main.h"

//循迹模块初始化
void track_init(void);
//循迹模块串口中断处理函数
void track_usart_handle(void);
//循迹模块数据解码函数
void track_deta_decode(int * ptrack_data, uint8_t * buff, int len);
//循迹模块发送指令函数
void track_send_cmd(char * str);
//循迹模块数据指针
int * track_data_pointer(void);

#endif

