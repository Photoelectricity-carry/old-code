#ifndef GYRO_DRI_H
#define GYRO_DRI_H

//陀螺仪数据类型
#define GYRO_DATA_TYPE float
	
//是否校验
#define IS_CHECKSUM	   1




#include "main.h"
#include "stdbool.h"

/*陀螺仪加速度数据结构体*/
typedef struct{
	GYRO_DATA_TYPE ax;
	GYRO_DATA_TYPE ay;
	GYRO_DATA_TYPE az;
} gyro_acc_t;

/*陀螺仪角速度数据结构体*/
typedef struct{
	GYRO_DATA_TYPE wx;
	GYRO_DATA_TYPE wy;
	GYRO_DATA_TYPE wz;
} gyro_w_t;

/*陀螺仪欧拉角数据结构体*/
typedef struct{
	GYRO_DATA_TYPE roll;
	GYRO_DATA_TYPE pitch;
	GYRO_DATA_TYPE yaw;
} gyro_angle_t;

/*陀螺仪句柄结构体*/
typedef struct {
	gyro_acc_t     acc;
	gyro_w_t       w;
	gyro_angle_t   angle;
	GYRO_DATA_TYPE temperature;
	
	bool is_data_err;
	uint8_t		   recv_buff[30 + 30];
} gyro_driver_handle_t;



//陀螺仪初始化函数
void GYRO_init(void);
//陀螺仪数据解包函数
void GYRO_decode(gyro_driver_handle_t * gyro_handler);
//串口中断数据处理函数
void gyro_usart_recv_handle(void);
//返回陀螺仪句柄结构体地址
gyro_driver_handle_t * get_gyro_handler_pointer(void);

#endif

