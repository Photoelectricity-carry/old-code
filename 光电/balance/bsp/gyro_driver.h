#ifndef GYRO_DRI_H
#define GYRO_DRI_H

//��������������
#define GYRO_DATA_TYPE float
	
//�Ƿ�У��
#define IS_CHECKSUM	   1




#include "main.h"
#include "stdbool.h"

/*�����Ǽ��ٶ����ݽṹ��*/
typedef struct{
	GYRO_DATA_TYPE ax;
	GYRO_DATA_TYPE ay;
	GYRO_DATA_TYPE az;
} gyro_acc_t;

/*�����ǽ��ٶ����ݽṹ��*/
typedef struct{
	GYRO_DATA_TYPE wx;
	GYRO_DATA_TYPE wy;
	GYRO_DATA_TYPE wz;
} gyro_w_t;

/*������ŷ�������ݽṹ��*/
typedef struct{
	GYRO_DATA_TYPE roll;
	GYRO_DATA_TYPE pitch;
	GYRO_DATA_TYPE yaw;
} gyro_angle_t;

/*�����Ǿ���ṹ��*/
typedef struct {
	gyro_acc_t     acc;
	gyro_w_t       w;
	gyro_angle_t   angle;
	GYRO_DATA_TYPE temperature;
	
	bool is_data_err;
	uint8_t		   recv_buff[30 + 30];
} gyro_driver_handle_t;



//�����ǳ�ʼ������
void GYRO_init(void);
//���������ݽ������
void GYRO_decode(gyro_driver_handle_t * gyro_handler);
//�����ж����ݴ�����
void gyro_usart_recv_handle(void);
//���������Ǿ���ṹ���ַ
gyro_driver_handle_t * get_gyro_handler_pointer(void);

#endif

