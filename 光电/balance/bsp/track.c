#include "track.h"
#include "usart.h"
#include "main.h"
#include "string.h"
#include "stdlib.h"


//循迹模块所用串口句柄
#define TRACK_hUART		huart2
//循迹模块所用串口句柄指针
#define TRACK_phUART	&TRACK_hUART


//循迹模块数据
int track_data = 0;
//循迹模块串口接收缓冲区
uint8_t track_buffer[100];

/*循迹模块初始化*/
void track_init(void){
	//开启串口接收中断
	__HAL_UART_ENABLE_IT(TRACK_phUART, UART_IT_RXNE);
	//开启串口空闲中断
	__HAL_UART_ENABLE_IT(TRACK_phUART, UART_IT_IDLE);
	
	//使能DMA传输
   HAL_UART_Receive_DMA(TRACK_phUART, track_buffer, sizeof(track_buffer));
	
	//清空缓冲区
	memset(track_buffer, 0, sizeof(track_buffer));
}

/*循迹模块串口中断处理函数*/
void track_usart_handle(void){
	//如果是空闲中断
	if (__HAL_UART_GET_FLAG(TRACK_phUART, UART_FLAG_IDLE)){
		//清除中断标志位
		 __HAL_UART_CLEAR_IDLEFLAG(TRACK_phUART);
		//停止DMA传输
		HAL_UART_DMAStop(TRACK_phUART);
		
		//数据解码
		track_deta_decode(&track_data, track_buffer);
		
		//清空缓冲区
		memset(track_buffer, 0, sizeof(track_buffer));
		//重新开启DMA传输
		HAL_UART_Receive_DMA(TRACK_phUART, track_buffer, sizeof(track_buffer));
	}
}

/*循迹模块数据解码函数*/
void track_deta_decode(int * ptrack_data, uint8_t * buffer, int len){
	
}

/*循迹模块发送指令函数*/
void track_send_cmd(char * str){
	
}

/*循迹模块数据指针*/
int * track_data_pointer(void){
	return &track_data;
}

