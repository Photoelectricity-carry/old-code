#include "color.h"
#include "stm32f4xx.h"
#include "delay.h"
#include "exti.h"

u16 Ramount=0,Gamount=0,Bamount=0;				//用于存放读取的RGB值
u16 amount=0;									//中断计数
//u16 R,G,B;
_RGB RGB;
void tcs3200_init(u8 s0,u8 s1)
{

	GPIO_InitTypeDef	GPIO_InitStructure;
		
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);//使能PB端口时钟
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;	//推挽输出
    //GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;//不带上下拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//IO口速度为50MHz
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	S0=s0;
	S1=s1;
 
}


/*******************************************
*
*		  白平衡
*
*******************************************/
void WhiteBalance(void)
{   
	EXTIX_Init();
	S2=0;S3=0;								//红色通道
	amount=0;			 					//开始计数
	delay_ms(10);
	RGB.Rgena = 255/amount;   					//求出红色因子      
	amount=0;
  //R=RGB.Rgena;
	
	S2=1;S3=1;								//绿色通道
	amount=0;
   delay_ms(10);
	RGB.Ggena = 255/amount;	 					//求出绿色因子
	amount=0;
  //G=RGB.Ggena;
	
	S2=0;S3=1;								//蓝色通道
	amount=0;
	delay_ms(10);
	RGB.Bgena = 255/amount;	  					//求出蓝色因子
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
	Ramount=(u32) RGB.Rgena*amount;	 			//取R值Ramount=(u32) amount*255/539;	
	if(Ramount>255) Ramount = 255;
	return Ramount;
}

u16 tcs3200_GREEN(void)					//打开绿色滤波
{
	S2=1;S3=1;
	amount=0;
	delay_ms(10);
	S2=1;S3=0;								//关闭通道 
	Gamount=(u32) RGB.Ggena *amount;				//取G值Gamount=(u32) amount*255/495;	
	if(Gamount>255) Gamount = 255;
	return Gamount;
}

u16 tcs3200_BLUE(void)						//打开蓝色滤波
{
	S2=0;S3=1;
	amount=0;
	delay_ms(10);
	S2=1;S3=0;								//关闭通道 
	Bamount=(u32) RGB.Bgena*amount;				//取B值	Bamount=(u32) amount*255/622;	
	if(Bamount>255) Bamount = 255;
	return Bamount;
} 
//u16 clour_disguish(void)		//颜色识别
//{
//	u16 tmp=3;
//	R = tcs3200_RED();
//	G = tcs3200_GREEN();
//	B = tcs3200_BLUE();
//	if(((R <= 255) &&(R > 200)) && ((G <=255) &&(G > 200)) &&((B <= 255) && (B > 200))) 			//识别为白色	((R < 255) &&(R > 200)) && ((G < 255) &&(G > 200)) &&((B < 255) && (B > 200))
//	{			
//		return 0;
//	}
//	 else if((R < 90) && (G < 90) && (B < 90))				//否则是黑色
//	{						  
//		return 1;
//	}			
//	else if(((R > 150)&&(R < 190))&&(R>G)&&(R>B)) 				//识别为红色		((R > 160)&&(R < 190))&&(R>G)&&(R>B)
//	{			
//		return 2;
//	}
//	else if((G<130)&&(G > 95)&&(G>R)&&(G>B)) 								//识别为绿色
//	{			
//		return 3;
//	 }
//	else if((B<130)&&(B>90)&&(B>R)&&(B>G)) 								//识别为蓝色
//	{			
//		return 4;
//	}
//	return tmp;
//}
