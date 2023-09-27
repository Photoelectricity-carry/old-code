#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"

								    
//������ʼ������
void KEY_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);  
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//ʹ��PORTA,PORTEʱ��

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB12,13
	
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10;  //��ɫ����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB12,13
}
//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//0��û���κΰ�������
//1��KEY0����
//2��KEY1����

//ע��˺�������Ӧ���ȼ�,KEY0>KEY1
u8 KEY_Scan(u8 mode)
{	 
	 u8 key_up=1;//�������ɿ���־
	if(mode) key_up=1;  //֧������		  
	if(key_up&&(KEY0==0||KEY1==0))
	{
		delay_ms(10);
		key_up=0;
		if(KEY0==0)		return KEY0_PRES;
		if(KEY1==0)		return KEY1_PRES;
	}
	else key_up=1; 	    
 	return 0;// �ް�������
}
