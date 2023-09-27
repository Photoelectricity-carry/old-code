#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "tcs3200.h"
#include "exti.h"
#include "uart.h"

u8 Rgena,Ggena,Bgena;
u16 Ramount,Gamount,Bamount;
u16 amount;
u16 R=0x00,G=0x00,B=0x00;


void tcs3200_init(u8 s0,u8 s1)
{
	GPIO_InitTypeDef GPIO_InitStructure;  
  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); /* �������ں�GPIOC��GPIOD��ʱ�� */
	 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3	;	 /* Configure LCD1602 IO*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 	/* ����GPIOD�������ģʽ*/
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;       
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	 // ��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);

	S0=s0;
	S1=s1;
}

/*******************************************
*
*		  ����rgbֵ�ж���ɫ
*
*******************************************/


int  color_dat_deal(u16 R,u16 G,u16 B) //R,G,B�Ա�
{
	R=tcs3200_RED();
	G=tcs3200_GREEN();
	B=tcs3200_BLUE();
	
	if(R<=52&&G<=52&&B<=52)
	{
		return 1;//ʶ����ɫΪ��
	}
	else if(R>=205&&G<=205&&B<=205)
	{
		return 2;//ʶ����ɫΪ��
	}
	else
	{
		return 0;
	}
}

/*******************************************
*
*		  ��ƽ��
*
*******************************************/
void whitebalance(void)
{
	EXTIX_Init();		 //�ⲿ�жϳ�ʼ��
	
	S2=0;S3=0;//��ɫͨ��
	amount=0;			 //��ʼ����
	delay_ms(10);
	Rgena = amount;   //�����ɫ����      
	amount=0;
//----------------------------------
	S2=1;S3=1;//��ɫͨ��
	amount=0;
	delay_ms(10);
	Ggena = amount;	 //�����ɫ����
	amount=0;
//----------------------------------
	S2=0;S3=1;//��ɫͨ��
	amount=0;
	delay_ms(10);
	Bgena = amount;	  //�����ɫ����
	amount=0;
	S2=1;S3=0;//�ر�ͨ��  	  
}  

/*
��ȡ��ɫ�ķ���ֵ����
*/
int RBG_fun(void)
{
		
		u8 colour;
		colour=color_dat_deal(R,G,B);
		return colour;

}


u16 tcs3200_RED(void)
{
	S2=0;S3=0;
	amount=0;
	delay_ms(10);
	Ramount=(u32) amount*255/Rgena;	 //ȡRֵ
	if(Ramount>255) Ramount = 255;
	return Ramount;
//	amount=0;
}

u16 tcs3200_GREEN(void)
{
	S2=1;S3=1;
	amount=0;
	delay_ms(10);
	Gamount=(u32) amount*255/Ggena;	//ȡGֵ
	if(Gamount>255) Gamount = 255;
	return Gamount;
//	amount=0;
}

u16 tcs3200_BLUE(void)
{
	S2=0;S3=1;
	amount=0;
	delay_ms(10);
	Bamount=(u32) amount*255/Bgena;//ȥBֵ
	if(Bamount>255) Bamount = 255;
	return Bamount;
//	amount=0;
} 




