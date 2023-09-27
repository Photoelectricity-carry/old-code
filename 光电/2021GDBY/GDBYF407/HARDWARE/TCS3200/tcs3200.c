#include "tcs3200.h"
#include "stm32f4xx.h"
#include "delay.h"
#include "exit.h"
//S0--->PA4		S1--->PA5		S2--->PA6		S3--->PA7		OUT--->PA3

u16 Ramount=0,Gamount=0,Bamount=0;
u16 amount=0,flag=0;
u16 R,G,B;
_RGB RGB;
void tcs3200_init(u8 s0,u8 s1)
{

	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);			

	S0 = s0;
	S1 = s1;
	
}



/*******************************************
*
*		  调整白平衡
*
*******************************************/
void WhiteBalance(void)
{
	S2=0;S3=0;								//红色通道
	amount=0;			 					//开始计数
	delay_ms(10);
	RGB.Rgena = amount;   					//求出红色因子      
	amount=0;
  //R=RGB.Rgena;
	
	S2=1;S3=1;								//绿色通道
	amount=0;
  delay_ms(10);
	RGB.Ggena = amount;	 					//求出绿色因子
	amount=0;
  //G=RGB.Ggena;
	
	S2=0;S3=1;								//蓝色通道
	amount=0;
	delay_ms(10);
	RGB.Bgena = amount;	  					//求出蓝色因子
	amount=0;
	//B=RGB.Bgena ;
	
	S2=1;S3=0;								//关闭通道  	  
} 


/*******************************************
*
*		  RGB读取
*
*******************************************/
u16 tcs3200_RED(void)						//打开红色滤波
{
	S2=0;S3=0;                     //红色通道
	amount=0;
	delay_ms(10);
	S2=1;S3=0;								//关闭通道 
	Ramount=(u32) amount*1000/200;	 			//取R值Ramount=(u32) amount*255/539;	445
	if(Ramount>1000) Ramount = 1000;
	return Ramount;
}

u16 tcs3200_GREEN(void)					//打开绿色滤波
{
	S2=1;S3=1;
	amount=0;
	delay_ms(10);
	S2=1;S3=0;								//关闭通道 
	Gamount=(u32) amount*1000/180;				//取G值Gamount=(u32) amount*255/495;	375
	if(Gamount>1000) Gamount = 1000;
	return Gamount;
}

u16 tcs3200_BLUE(void)						//打开蓝色滤波
{
	S2=0;S3=1;
	amount=0;
	delay_ms(10);
	S2=1;S3=0;								//关闭通道 
	Bamount=(u32) amount*1000/210;				//取B值	Bamount=(u32) amount*255/622;	 428
	if(Bamount>1000) Bamount = 1000;
	return Bamount;
} 
u16 clour_disguish(void)		//颜色识别
{
	u16 tmp=0;
	int i;
	for(i=0;i<20;i++)
	{
		R += tcs3200_RED();
		G += tcs3200_GREEN();
		B += tcs3200_BLUE();
	}
	R/=20;
	G/=20;
	B/=20;
	
	if((R > 500) && (G > 500) && (B > 500)) 			//识别为白色3	((R < 255) &&(R > 200)) && ((G < 255) &&(G > 200)) &&((B < 255) && (B > 200))
	{			
		return 3;
	}
	 else if((R < 200) && (G < 200) && (B < 200))			//否则是黑色5
	{						  
		return 5;
	}			
	else if( (R>G) && (R>B)) 				//识别为红色4		((R > 160)&&(R < 190))&&(R>G)&&(R>B)
	{			
		return 4;
	}
	else if((G>R) && (G>B)) 				//识别为绿色2
	{			
		return 2;
	 }
	else if((B>G) && (B>R)) 					//识别为蓝色6
	{			
		return 6;
	}
		R=0;G=0;B=0;
return tmp;
}



