#include <stm32f10x.h>
#include "uart.h"
#include <stdarg.h>     //��Ҫ�Ƕ���Uart_Print��ʵ���ַ�����ʽ�������
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "delay.h"


//�������´���,֧��printf����,������Ҫѡ��use MicroLIB
#if 1
#pragma import(__use_no_semihosting)
//��׼����Ҫ��֧�ֺ���
struct __FILE
{
    int handle;
    /* Whatever you require here. If the only file you are using is */
    /* standard output using printf() for debugging, no file handling */
    /* is required. */
};
/* FILE is typedef�� d in stdio.h. */
FILE __stdout;
//����_sys_exit()�Ա���ʹ�ð�����ģʽ
void _sys_exit(int x)
{
    x = x;
}
//�ض���fputc����
int fputc(int ch, FILE *f)
{
    while((USART1->SR & 0X40) == 0); //ѭ������,ֱ���������
    USART1->DR = (u8) ch;
    return ch;
}
#endif



void uart1_init(u32 bond)
{
  float div;
  u8 priority;
  USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
  
    //uartģ��ʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
//    //������  (USART_BRR)
//    div = ((float)clk * 1000000) / 16 / bond;
//    USART1->BRR = (u16)(div * 16);

  USART_InitStructure.USART_BaudRate = bond;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl =USART_HardwareFlowControl_None ;
  USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
  USART_Init(USART1, &USART_InitStructure);

  /*  �������ȼ�����������ռ���ȼ�2��λ����ռ���ȼ�1�������ȼ�0 */
  priority = NVIC_EncodePriority (7 - 2, 3, 3);
  /* �������ȼ� */
  NVIC_SetPriority(USART1_IRQn , priority);
  NVIC_EnableIRQ(USART1_IRQn); //NVIC_EnableIRQ()������ʹ���ⲿ�жϵ�
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
  
  USART_Cmd(USART1, ENABLE);
  
    //�˿�ʱ��ʹ�� PA��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
    //���ö˿�ģʽ
    //TX��pa9��: ����Ϊ�����������ģʽ
    //RX(pa10)������Ϊ����/��������ģʽ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void uart2_init(u32 bond)
{
  float div;
  u8 priority;
  USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
  
    //uartģ��ʱ��ʹ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
//    //������  (USART_BRR)
//    div = ((float)clk * 1000000) / 16 / bond;
//    USART1->BRR = (u16)(div * 16);

  USART_InitStructure.USART_BaudRate = bond;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl =USART_HardwareFlowControl_None ;
  USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
  USART_Init(USART2, &USART_InitStructure);

  /*  �������ȼ�����������ռ���ȼ�2��λ����ռ���ȼ�1�������ȼ�0 */
//  priority = NVIC_EncodePriority (7 - 2, 3, 3);
//  /* �������ȼ� */
//  NVIC_SetPriority(USART1_IRQn , priority);
//  NVIC_EnableIRQ(USART1_IRQn); //NVIC_EnableIRQ()������ʹ���ⲿ�жϵ�
//  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
  
  USART_Cmd(USART2, ENABLE);
  
    //�˿�ʱ��ʹ�� PA��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
    //���ö˿�ģʽ
    //TX��pa9��: ����Ϊ�����������ģʽ
    //RX(pa10)������Ϊ����/��������ģʽ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

//�����ַ���
void uart1_send_string(u8 *p)
{	
	FlagStatus Status;
  while('\0' != *p)
  {
    while( USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);
    USART_SendData(USART1, *p);
    p++;
  }
}

void uart2_send_string(u8 *p)
{	
	FlagStatus Status;
  while('\0' != *p)
  {
    while( USART_GetFlagStatus(USART2, USART_FLAG_TXE)==RESET);
    USART_SendData(USART2, *p);
    p++;
  }
}

u8 rec_buf[100];    //���ڽ��ջ�����
u8 rec_sta = 0;     //�ַ���������ɱ�ʶ�����ַ���������Ϻ�����������1
u16 rec_len = 0;
u16 len=0;
void USART1_IRQHandler(void)
{
	u8 rec_data;
	if(USART1->SR &(0X01<<5))
	{
		rec_data=USART1->DR;
		if((rec_data=='\n') &&(rec_buf[rec_len-1]=='\r')&&(rec_buf[rec_len-2]=='>'))  //�ַ����������
		{
			rec_sta=1;  
			rec_buf[rec_len-1]='\0';
      len=rec_len;
			rec_len=0;
		}
		else
		{
			rec_buf[rec_len++]=rec_data;
		}
	}
}


//#endif
