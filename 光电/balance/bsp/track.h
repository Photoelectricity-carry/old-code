#ifndef TRACK_H
#define TRACK_H

#include "main.h"

//ѭ��ģ���ʼ��
void track_init(void);
//ѭ��ģ�鴮���жϴ�����
void track_usart_handle(void);
//ѭ��ģ�����ݽ��뺯��
void track_deta_decode(int * ptrack_data, uint8_t * buff, int len);
//ѭ��ģ�鷢��ָ���
void track_send_cmd(char * str);
//ѭ��ģ������ָ��
int * track_data_pointer(void);

#endif

