#ifndef ECD_H
#define ECD_H

#include "main.h"


/*编码器结构体*/
typedef struct{
	//左编码器速度值
	int rightECD;
	//右编码器速度值
	int leftECD;
} ecd_t;


//编码器初始化
void ecd_init(void);
//读取编码器速度值
void ecd_read_speed(ecd_t * pecd);
//返回编码器结构体指针函数
ecd_t * get_ecd_pointer(void);



#endif

