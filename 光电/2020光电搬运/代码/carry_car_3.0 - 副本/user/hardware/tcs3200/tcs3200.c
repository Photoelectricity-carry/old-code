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




// 白平衡
void whitebalance(void)
{
  	EXTIX_Init_1();		 //外部中断初始化
	 
	  //红色通道
    s2_low(); s3_low(); //R
		amount=0;			 //开始计数
		delay_ms(10);
		Rgena = amount;   //求出红色因子      
		amount=0;
	
	  //绿色通道
	  s2_high(); s3_high();
	  amount=0;
	  delay_ms(10);
	  Ggena = amount;	 //求出绿色因子
	  amount=0;	

    //蓝色通道
	  s2_low(); s3_high();
	  amount=0;
	  delay_ms(10);
	  Bgena = amount;	  //求出蓝色因子	
	 	amount=0;
    //关闭通道
    s2_high(); s3_low();
}



u16 tcs3200_RED(void)
{
		s2_low(); s3_low();
		amount=0;
		delay_ms(10);
		Ramount=(u32) amount*255/Rgena;	 //取R值
		if(Ramount>255) Ramount = 255;
		return Ramount;
	//	amount=0;
}

u16 tcs3200_GREEN(void)
{
	s2_high();s3_high();
	amount=0;
	delay_ms(10);
	Gamount=(u32) amount*255/Ggena;	//取G值
	if(Gamount>255) Gamount = 255;
	return Gamount;
//	amount=0;
}

u16 tcs3200_BLUE(void)
{
	s2_low();s3_high();
	amount=0;
	delay_ms(10);
	Bamount=(u32) amount*255/Bgena;//去B值
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
