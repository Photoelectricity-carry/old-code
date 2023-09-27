#include "tcs3200.h"
#include "exit_init.h"
#include "stm32f4xx.h"
#include "main.h"
#include "delay.h"

u16 Rgena,Ggena,Bgena;
u16 Ramount,Gamount,Bamount;

u16 amount;

void tcs3200_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF | RCC_AHB1Periph_GPIOE, ENABLE); //

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	  s0_high();
	  s1_high();
}




// ��ƽ��
void whitebalance(void)
{
  	EXTIX_Init_1();		 //�ⲿ�жϳ�ʼ��
	 
	  //��ɫͨ��
    s2_low(); s3_low(); //R
		amount=0;			 //��ʼ����
		delay_ms(10);
		Rgena = amount;   //�����ɫ����      
		amount=0;
	
	  //��ɫͨ��
	  s2_high(); s3_high();
	  amount=0;
	  delay_ms(10);
	  Ggena = amount;	 //�����ɫ����
	  amount=0;	

    //��ɫͨ��
	  s2_low(); s3_high();
	  amount=0;
	  delay_ms(10);
	  Bgena = amount;	  //�����ɫ����	
	 	amount=0;
    //�ر�ͨ��
    s2_high(); s3_low();
}



u16 tcs3200_RED(void)
{
		s2_low(); s3_low();
		amount=0;
		delay_ms(10);
		Ramount=(u32) amount*255/Rgena;	 //ȡRֵ
		if(Ramount>255) Ramount = 255;
		return Ramount;
	//	amount=0;
}

u16 tcs3200_GREEN(void)
{
	s2_high();s3_high();
	amount=0;
	delay_ms(10);
	Gamount=(u32) amount*255/Ggena;	//ȡGֵ
	if(Gamount>255) Gamount = 255;
	return Gamount;
//	amount=0;
}

u16 tcs3200_BLUE(void)
{
	s2_low();s3_high();
	amount=0;
	delay_ms(10);
	Bamount=(u32) amount*255/Bgena;//ȥBֵ
	if(Bamount>255) Bamount = 255;
	return Bamount;
//	amount=0;
} 

void s0_low(void)
{
	  GPIO_ResetBits(GPIOE, GPIO_Pin_4);
}
void s0_high(void)
{
	  GPIO_SetBits(GPIOE, GPIO_Pin_4);
}


void s1_low(void)
{
	  GPIO_ResetBits(GPIOE, GPIO_Pin_5);
}
void s1_high(void)
{
	  GPIO_SetBits(GPIOE, GPIO_Pin_5);
}


void s2_low(void)
{
	  GPIO_ResetBits(GPIOE, GPIO_Pin_6);
}
void s2_high(void)
{
	  GPIO_SetBits(GPIOE, GPIO_Pin_6);
}


void s3_low(void)
{
	  GPIO_ResetBits(GPIOE, GPIO_Pin_12);
}
void s3_high(void)
{
	  GPIO_SetBits(GPIOE, GPIO_Pin_12);
}
