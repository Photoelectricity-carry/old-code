#ifndef ECD_H
#define ECD_H

#include "main.h"


/*�������ṹ��*/
typedef struct{
	//��������ٶ�ֵ
	int rightECD;
	//�ұ������ٶ�ֵ
	int leftECD;
} ecd_t;


//��������ʼ��
void ecd_init(void);
//��ȡ�������ٶ�ֵ
void ecd_read_speed(ecd_t * pecd);
//���ر������ṹ��ָ�뺯��
ecd_t * get_ecd_pointer(void);



#endif

