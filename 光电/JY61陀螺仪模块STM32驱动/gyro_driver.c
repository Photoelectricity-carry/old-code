#include "gyro_driver.h"
#include "usart.h"
#include "string.h"


//���������õĴ��ھ��
#define GRYO_UART  huart1
//���������õĴ��ھ��ָ��
#define pGYRO_UART &huart1

//���������ݰ�ͷ
#define GYRO_DATA_HEAD       0x55
//�����Ǽ��ٶ����ݰ�ͷ
#define GYRO_ACC_DATA_HEAD	 0x51
//�����ǽ��ٶ����ݰ�ͷ
#define GYRO_W_DATA_HEAD	 0x52
//������ŷ�������ݰ�ͷ
#define GYRO_ANGLE_DATA_HEAD 0x53

//���������ݰ���Ի���ַ
#define GYRO_DATA_BASE		 0
//���������ݰ���ַƫ����
#define GYRO_DATA_DELTA		 11

//�����Ǽ��ٶȰ�����ַ
#define GYRO_ACC_DATA_BASE	 (GYRO_DATA_BASE + 0*GYRO_DATA_DELTA)
//�����ǽ��ٶȰ�����ַ
#define GYRO_W_DATA_BASE	 (GYRO_DATA_BASE + 1*GYRO_DATA_DELTA)
//������ŷ���ǰ�����ַ
#define GYRO_ANGLE_DATA_BASE (GYRO_DATA_BASE + 2*GYRO_DATA_DELTA)


gyro_driver_handle_t gyro_dirver_handler = {0};


//���������ݽ������
static void GYRO_decode(gyro_driver_handle_t * gyro_handler);
//���ٶ�����ƴ�Ӵ�����
static GYRO_DATA_TYPE acc_data_montage(uint8_t data_high, uint8_t data_low);
//���ٶ�����ƴ�Ӵ�����
static GYRO_DATA_TYPE w_data_montage(uint8_t data_high, uint8_t data_low);
//ŷ��������ƴ�Ӵ�����
static GYRO_DATA_TYPE angle_data_montage(uint8_t data_high, uint8_t data_low);
//�¶�����ƴ�Ӵ�����
static GYRO_DATA_TYPE temperature_data_montage(uint8_t data_high, uint8_t data_low);



/*�����ǳ�ʼ������*/
void GYRO_init(void){
	//�������ڽ����ж�
	__HAL_UART_ENABLE_IT(pGYRO_UART, UART_IT_RXNE);
	//�������ڿ����ж�
	__HAL_UART_ENABLE_IT(pGYRO_UART, UART_IT_IDLE);
	
	//ʹ��DMA����
   HAL_UART_Receive_DMA(pGYRO_UART, gyro_dirver_handler.recv_buff, 60);
}

/*���ٶ�����ƴ�Ӵ�����*/
static GYRO_DATA_TYPE acc_data_montage(uint8_t data_high, uint8_t data_low){
	GYRO_DATA_TYPE data = (short)(data_high << 8 | data_low);
	data = data / 32768.0 * 16;
	
	return data;
}

/*���ٶ�����ƴ�Ӵ�����*/
static GYRO_DATA_TYPE w_data_montage(uint8_t data_high, uint8_t data_low){
	GYRO_DATA_TYPE data = (short)(data_high << 8 | data_low);
	data = data / 32768.0 * 2000.0;
	
	return data;
}

/*ŷ��������ƴ�Ӵ�����*/
static GYRO_DATA_TYPE angle_data_montage(uint8_t data_high, uint8_t data_low){
	GYRO_DATA_TYPE data = (short)(data_high << 8 | data_low);
	data = data / 32768.0 * 180.0;
	
	return data;
}



/*�¶�����ƴ�Ӵ�����*/
static GYRO_DATA_TYPE temperature_data_montage(uint8_t data_high, uint8_t data_low){
	GYRO_DATA_TYPE data = (short)(data_high << 8 | data_low);
	data = data / 340.0 + 36.53;
	
	return data;
}

/*���������ݽ������*/
static void GYRO_decode(gyro_driver_handle_t * gyro_handler){
	/*������ٶ����ݰ�*/
	//��֤֡ͷ
	if (gyro_handler->recv_buff[GYRO_ACC_DATA_BASE] == GYRO_DATA_HEAD){
		//��֤���ٶ�֡��ʶ��
		if (gyro_handler->recv_buff[GYRO_ACC_DATA_BASE+1] == GYRO_ACC_DATA_HEAD){
			//����x���ٶ�
			gyro_handler->acc.ax 
			= acc_data_montage(gyro_handler->recv_buff[GYRO_ACC_DATA_BASE+3], gyro_handler->recv_buff[GYRO_ACC_DATA_BASE+2]);
			
			//����y���ٶ�
			gyro_handler->acc.ay
			= acc_data_montage(gyro_handler->recv_buff[GYRO_ACC_DATA_BASE+5], gyro_handler->recv_buff[GYRO_ACC_DATA_BASE+4]);
			
			//����z���ٶ�
			gyro_handler->acc.az
			= acc_data_montage(gyro_handler->recv_buff[GYRO_ACC_DATA_BASE+7], gyro_handler->recv_buff[GYRO_ACC_DATA_BASE+6]);
		}
	}
	
	/*������ٶ����ݰ�*/
	//��֤֡ͷ
	if (gyro_handler->recv_buff[GYRO_W_DATA_BASE] == GYRO_DATA_HEAD){
		//��֤���ٶȱ�ʶ��
		if (gyro_handler->recv_buff[GYRO_W_DATA_BASE+1] == GYRO_W_DATA_HEAD){
			//����x���ٶ�
			gyro_handler->w.wx 
			= w_data_montage(gyro_handler->recv_buff[GYRO_W_DATA_BASE+3], gyro_handler->recv_buff[GYRO_W_DATA_BASE+2]);
			
			//����y���ٶ�
			gyro_handler->w.wy
			= w_data_montage(gyro_handler->recv_buff[GYRO_W_DATA_BASE+5], gyro_handler->recv_buff[GYRO_W_DATA_BASE+4]);
			
			//����z���ٶ�
			gyro_handler->w.wz
			= w_data_montage(gyro_handler->recv_buff[GYRO_W_DATA_BASE+7], gyro_handler->recv_buff[GYRO_W_DATA_BASE+6]);
		}
	}
	
	/*����ŷ�������ݰ�*/
	//��֤֡ͷ
	if (gyro_handler->recv_buff[GYRO_ANGLE_DATA_BASE] == GYRO_DATA_HEAD){
		//��֤ŷ���Ǳ�ʶ��
		if (gyro_handler->recv_buff[GYRO_ANGLE_DATA_BASE+1] == GYRO_ANGLE_DATA_HEAD){
			//����roll
			gyro_handler->angle.roll 
			= angle_data_montage(gyro_handler->recv_buff[GYRO_ANGLE_DATA_BASE+3], gyro_handler->recv_buff[GYRO_ANGLE_DATA_BASE+2]);
			
			//����pitch
			gyro_handler->angle.pitch
			= angle_data_montage(gyro_handler->recv_buff[GYRO_ANGLE_DATA_BASE+5], gyro_handler->recv_buff[GYRO_ANGLE_DATA_BASE+4]);
			
			//����yaw
			gyro_handler->angle.yaw 
			= angle_data_montage(gyro_handler->recv_buff[GYRO_ANGLE_DATA_BASE+7], gyro_handler->recv_buff[GYRO_ANGLE_DATA_BASE+6]);
			
			//�����¶�
			gyro_handler->temperature 
			= temperature_data_montage(gyro_handler->recv_buff[GYRO_ANGLE_DATA_BASE+9], gyro_handler->recv_buff[GYRO_ANGLE_DATA_BASE+8]);
		}
	}
}


/*�����ж����ݴ�����*/
void usart_recv_handle(void){
	if (__HAL_UART_GET_FLAG(pGYRO_UART, UART_FLAG_IDLE)){
		//����жϱ�־λ
		 __HAL_UART_CLEAR_IDLEFLAG(pGYRO_UART);
		//ֹͣDMA����
		HAL_UART_DMAStop(pGYRO_UART);
		
		//���ݽ��
		GYRO_decode(&gyro_dirver_handler);
		
		//��ջ�����
		memset(gyro_dirver_handler.recv_buff, 0, sizeof(gyro_dirver_handler.recv_buff));
		//���¿���DMA����
		HAL_UART_Receive_DMA(&huart1, gyro_dirver_handler.recv_buff, 60);
	}
}


/*���������Ǿ���ṹ���ַ����*/
gyro_driver_handle_t * get_gyro_handler_pointer(void){
	return &gyro_dirver_handler;
}
