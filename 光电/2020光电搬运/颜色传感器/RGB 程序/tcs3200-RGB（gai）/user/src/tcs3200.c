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
  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); /* 开启串口和GPIOC、GPIOD的时钟 */
	 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3	;	 /* Configure LCD1602 IO*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 	/* 配置GPIOD推免输出模式*/
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;       
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	 // 上拉输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);

	S0=s0;
	S1=s1;
}

/*******************************************
*
*		  根据rgb值判断颜色
*
*******************************************/


int  color_dat_deal(u16 R,u16 G,u16 B) //R,G,B对比
{
	R=tcs3200_RED();
	G=tcs3200_GREEN();
	B=tcs3200_BLUE();
	
	if(R<=52&&G<=52&&B<=52)
	{
		return 1;//识别颜色为黑
	}
	else if(R>=205&&G<=205&&B<=205)
	{
		return 2;//识别颜色为白
	}
	else
	{
		return 0;
	}
}

/*******************************************
*
*		  白平衡
*
*******************************************/
void whitebalance(void)
{
	EXTIX_Init();		 //外部中断初始化
	
	S2=0;S3=0;//红色通道
	amount=0;			 //开始计数
	delay_ms(10);
	Rgena = amount;   //求出红色因子      
	amount=0;
//----------------------------------
	S2=1;S3=1;//绿色通道
	amount=0;
	delay_ms(10);
	Ggena = amount;	 //求出绿色因子
	amount=0;
//----------------------------------
	S2=0;S3=1;//蓝色通道
	amount=0;
	delay_ms(10);
	Bgena = amount;	  //求出蓝色因子
	amount=0;
	S2=1;S3=0;//关闭通道  	  
}  

/*
读取颜色的返回值函数
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
	Ramount=(u32) amount*255/Rgena;	 //取R值
	if(Ramount>255) Ramount = 255;
	return Ramount;
//	amount=0;
}

u16 tcs3200_GREEN(void)
{
	S2=1;S3=1;
	amount=0;
	delay_ms(10);
	Gamount=(u32) amount*255/Ggena;	//取G值
	if(Gamount>255) Gamount = 255;
	return Gamount;
//	amount=0;
}

u16 tcs3200_BLUE(void)
{
	S2=0;S3=1;
	amount=0;
	delay_ms(10);
	Bamount=(u32) amount*255/Bgena;//去B值
	if(Bamount>255) Bamount = 255;
	return Bamount;
//	amount=0;
} 




