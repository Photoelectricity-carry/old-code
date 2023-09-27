#include "stm32f10x.h"                  
#include "uart.h"
#include "stdio.h"
#include "string.h"
#include "io_bit.h"
#include "delay.h"
#include "exti.h"
#include "tcs3200.h"


 
int main(void)
{

	u8 colour;
  
  NVIC_EncodePriority(7-2,3,3);           //�˿ڳ�ʼ������
 uart1_init(9600);//������ 
//  relay_init();//�̵���
  EXTIX_Init();//�ⲿ�ж�
	tcs3200_init(1,1);//��ʼ�������ʵ�����
  whitebalance();	//��ƽ��  
			

	while(1)
  { 
		
    colour=RBG_fun();	
		printf("%d ",colour);
		delay_ms(1000);
		
  }
}

