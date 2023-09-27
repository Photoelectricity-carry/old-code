#include "track.h"
#include "usart.h"
#include "main.h"
#include "string.h"
#include "stdlib.h"


//ѭ��ģ�����ô��ھ��
#define TRACK_hUART		huart2
//ѭ��ģ�����ô��ھ��ָ��
#define TRACK_phUART	&TRACK_hUART


//ѭ��ģ������
int track_data = 0;
//ѭ��ģ�鴮�ڽ��ջ�����
uint8_t track_buffer[100];

/*ѭ��ģ���ʼ��*/
void track_init(void){
	//�������ڽ����ж�
	__HAL_UART_ENABLE_IT(TRACK_phUART, UART_IT_RXNE);
	//�������ڿ����ж�
	__HAL_UART_ENABLE_IT(TRACK_phUART, UART_IT_IDLE);
	
	//ʹ��DMA����
   HAL_UART_Receive_DMA(TRACK_phUART, track_buffer, sizeof(track_buffer));
	
	//��ջ�����
	memset(track_buffer, 0, sizeof(track_buffer));
}

/*ѭ��ģ�鴮���жϴ�����*/
void track_usart_handle(void){
	//����ǿ����ж�
	if (__HAL_UART_GET_FLAG(TRACK_phUART, UART_FLAG_IDLE)){
		//����жϱ�־λ
		 __HAL_UART_CLEAR_IDLEFLAG(TRACK_phUART);
		//ֹͣDMA����
		HAL_UART_DMAStop(TRACK_phUART);
		
		//���ݽ���
		track_deta_decode(&track_data, track_buffer);
		
		//��ջ�����
		memset(track_buffer, 0, sizeof(track_buffer));
		//���¿���DMA����
		HAL_UART_Receive_DMA(TRACK_phUART, track_buffer, sizeof(track_buffer));
	}
}

/*ѭ��ģ�����ݽ��뺯��*/
void track_deta_decode(int * ptrack_data, uint8_t * buffer, int len){
	
}

/*ѭ��ģ�鷢��ָ���*/
void track_send_cmd(char * str){
	
}

/*ѭ��ģ������ָ��*/
int * track_data_pointer(void){
	return &track_data;
}

