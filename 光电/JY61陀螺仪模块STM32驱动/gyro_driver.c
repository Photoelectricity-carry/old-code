#include "gyro_driver.h"
#include "usart.h"
#include "string.h"


//陀螺仪所用的串口句柄
#define GRYO_UART  huart1
//陀螺仪所用的串口句柄指针
#define pGYRO_UART &huart1

//陀螺仪数据包头
#define GYRO_DATA_HEAD       0x55
//陀螺仪加速度数据包头
#define GYRO_ACC_DATA_HEAD	 0x51
//陀螺仪角速度数据包头
#define GYRO_W_DATA_HEAD	 0x52
//陀螺仪欧拉角数据包头
#define GYRO_ANGLE_DATA_HEAD 0x53

//陀螺仪数据包相对基地址
#define GYRO_DATA_BASE		 0
//陀螺仪数据包地址偏移量
#define GYRO_DATA_DELTA		 11

//陀螺仪加速度包基地址
#define GYRO_ACC_DATA_BASE	 (GYRO_DATA_BASE + 0*GYRO_DATA_DELTA)
//陀螺仪角速度包基地址
#define GYRO_W_DATA_BASE	 (GYRO_DATA_BASE + 1*GYRO_DATA_DELTA)
//陀螺仪欧拉角包基地址
#define GYRO_ANGLE_DATA_BASE (GYRO_DATA_BASE + 2*GYRO_DATA_DELTA)


gyro_driver_handle_t gyro_dirver_handler = {0};


//陀螺仪数据解包函数
static void GYRO_decode(gyro_driver_handle_t * gyro_handler);
//加速度数据拼接处理函数
static GYRO_DATA_TYPE acc_data_montage(uint8_t data_high, uint8_t data_low);
//角速度数据拼接处理函数
static GYRO_DATA_TYPE w_data_montage(uint8_t data_high, uint8_t data_low);
//欧拉角数据拼接处理函数
static GYRO_DATA_TYPE angle_data_montage(uint8_t data_high, uint8_t data_low);
//温度数据拼接处理函数
static GYRO_DATA_TYPE temperature_data_montage(uint8_t data_high, uint8_t data_low);



/*陀螺仪初始化函数*/
void GYRO_init(void){
	//开启串口接收中断
	__HAL_UART_ENABLE_IT(pGYRO_UART, UART_IT_RXNE);
	//开启串口空闲中断
	__HAL_UART_ENABLE_IT(pGYRO_UART, UART_IT_IDLE);
	
	//使能DMA传输
   HAL_UART_Receive_DMA(pGYRO_UART, gyro_dirver_handler.recv_buff, 60);
}

/*加速度数据拼接处理函数*/
static GYRO_DATA_TYPE acc_data_montage(uint8_t data_high, uint8_t data_low){
	GYRO_DATA_TYPE data = (short)(data_high << 8 | data_low);
	data = data / 32768.0 * 16;
	
	return data;
}

/*角速度数据拼接处理函数*/
static GYRO_DATA_TYPE w_data_montage(uint8_t data_high, uint8_t data_low){
	GYRO_DATA_TYPE data = (short)(data_high << 8 | data_low);
	data = data / 32768.0 * 2000.0;
	
	return data;
}

/*欧拉角数据拼接处理函数*/
static GYRO_DATA_TYPE angle_data_montage(uint8_t data_high, uint8_t data_low){
	GYRO_DATA_TYPE data = (short)(data_high << 8 | data_low);
	data = data / 32768.0 * 180.0;
	
	return data;
}



/*温度数据拼接处理函数*/
static GYRO_DATA_TYPE temperature_data_montage(uint8_t data_high, uint8_t data_low){
	GYRO_DATA_TYPE data = (short)(data_high << 8 | data_low);
	data = data / 340.0 + 36.53;
	
	return data;
}

/*陀螺仪数据解包函数*/
static void GYRO_decode(gyro_driver_handle_t * gyro_handler){
	/*解算加速度数据包*/
	//验证帧头
	if (gyro_handler->recv_buff[GYRO_ACC_DATA_BASE] == GYRO_DATA_HEAD){
		//验证加速度帧标识符
		if (gyro_handler->recv_buff[GYRO_ACC_DATA_BASE+1] == GYRO_ACC_DATA_HEAD){
			//解算x加速度
			gyro_handler->acc.ax 
			= acc_data_montage(gyro_handler->recv_buff[GYRO_ACC_DATA_BASE+3], gyro_handler->recv_buff[GYRO_ACC_DATA_BASE+2]);
			
			//解算y加速度
			gyro_handler->acc.ay
			= acc_data_montage(gyro_handler->recv_buff[GYRO_ACC_DATA_BASE+5], gyro_handler->recv_buff[GYRO_ACC_DATA_BASE+4]);
			
			//解算z加速度
			gyro_handler->acc.az
			= acc_data_montage(gyro_handler->recv_buff[GYRO_ACC_DATA_BASE+7], gyro_handler->recv_buff[GYRO_ACC_DATA_BASE+6]);
		}
	}
	
	/*解算角速度数据包*/
	//验证帧头
	if (gyro_handler->recv_buff[GYRO_W_DATA_BASE] == GYRO_DATA_HEAD){
		//验证角速度标识符
		if (gyro_handler->recv_buff[GYRO_W_DATA_BASE+1] == GYRO_W_DATA_HEAD){
			//解算x角速度
			gyro_handler->w.wx 
			= w_data_montage(gyro_handler->recv_buff[GYRO_W_DATA_BASE+3], gyro_handler->recv_buff[GYRO_W_DATA_BASE+2]);
			
			//解算y角速度
			gyro_handler->w.wy
			= w_data_montage(gyro_handler->recv_buff[GYRO_W_DATA_BASE+5], gyro_handler->recv_buff[GYRO_W_DATA_BASE+4]);
			
			//解算z角速度
			gyro_handler->w.wz
			= w_data_montage(gyro_handler->recv_buff[GYRO_W_DATA_BASE+7], gyro_handler->recv_buff[GYRO_W_DATA_BASE+6]);
		}
	}
	
	/*解算欧拉角数据包*/
	//验证帧头
	if (gyro_handler->recv_buff[GYRO_ANGLE_DATA_BASE] == GYRO_DATA_HEAD){
		//验证欧拉角标识符
		if (gyro_handler->recv_buff[GYRO_ANGLE_DATA_BASE+1] == GYRO_ANGLE_DATA_HEAD){
			//解算roll
			gyro_handler->angle.roll 
			= angle_data_montage(gyro_handler->recv_buff[GYRO_ANGLE_DATA_BASE+3], gyro_handler->recv_buff[GYRO_ANGLE_DATA_BASE+2]);
			
			//解算pitch
			gyro_handler->angle.pitch
			= angle_data_montage(gyro_handler->recv_buff[GYRO_ANGLE_DATA_BASE+5], gyro_handler->recv_buff[GYRO_ANGLE_DATA_BASE+4]);
			
			//解算yaw
			gyro_handler->angle.yaw 
			= angle_data_montage(gyro_handler->recv_buff[GYRO_ANGLE_DATA_BASE+7], gyro_handler->recv_buff[GYRO_ANGLE_DATA_BASE+6]);
			
			//解算温度
			gyro_handler->temperature 
			= temperature_data_montage(gyro_handler->recv_buff[GYRO_ANGLE_DATA_BASE+9], gyro_handler->recv_buff[GYRO_ANGLE_DATA_BASE+8]);
		}
	}
}


/*串口中断数据处理函数*/
void usart_recv_handle(void){
	if (__HAL_UART_GET_FLAG(pGYRO_UART, UART_FLAG_IDLE)){
		//清除中断标志位
		 __HAL_UART_CLEAR_IDLEFLAG(pGYRO_UART);
		//停止DMA传输
		HAL_UART_DMAStop(pGYRO_UART);
		
		//数据解包
		GYRO_decode(&gyro_dirver_handler);
		
		//清空缓冲区
		memset(gyro_dirver_handler.recv_buff, 0, sizeof(gyro_dirver_handler.recv_buff));
		//重新开启DMA传输
		HAL_UART_Receive_DMA(&huart1, gyro_dirver_handler.recv_buff, 60);
	}
}


/*返回陀螺仪句柄结构体地址函数*/
gyro_driver_handle_t * get_gyro_handler_pointer(void){
	return &gyro_dirver_handler;
}
