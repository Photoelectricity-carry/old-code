#include "tcs3200.h"
#include "exti.h"
#include "delay.h"
#include "tcs3200.h"
#include "stmflash.h"



void tcs3200_init(u8 s0,u8 s1)
{

	GPIO_InitTypeDef	GPIO_InitStructure;
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使能PB端口时钟
	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//上拉输入
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//IO口速度为50MHz
//	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//IO口速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	S0=s0;
	S1=s1;

}
/*******************************************
*
*		  白平衡
*
*******************************************/
void whitebalance(void)
{
	u16 x[3];
	EXTIX_Init();		 //外部中断初始化
	S2=0;S3=0;//红色通道
	amount=0;			 //开始计数
	delay_ms(10);
	Rgena = amount;   //求出红色因子      
	amount=0;
	x[0]=Rgena;
//	STMFLASH_Write(0x08004000,(u16*)x[0],1);
//								 0x08000000
//----------------------------------
	S2=1;S3=1;//绿色通道
	amount=0;
	delay_ms(10);
	Ggena = amount;	 //求出绿色因子
	amount=0;
	x[1]=Ggena;
//	STMFLASH_Write(0x08004100,(u16*)x1[0],1);

//----------------------------------
	S2=0;S3=1;//蓝色通道
	amount=0;
	delay_ms(10);
	Bgena = amount;	  //求出蓝色因子
	amount=0;
	x[2]=Bgena;
	STMFLASH_Write(0x08004000,(u16*)x,3);
	
	S2=1;S3=0;//关闭通道  


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

//void aj(void)
//{
//	Rgena=255;	
//	Ggena=255;
//	Bgena=255;
//}

