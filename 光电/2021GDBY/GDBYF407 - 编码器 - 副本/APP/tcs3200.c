#include "tcs3200.h"
//S0--->PB10		S1--->PB11		S2--->PE13		S3--->PE14		OUT--->PA3

u16 Ramount=0,Gamount=0,Bamount=0;
u16 amount=0,flag=0;
u16 R=0,G=0,B=0;
_RGB RGB;
color_info_t color_info;
u16 R_t=102,G_t=91,B_t=105;              //白平衡三通道参数 55 67 54
void tcs3200_init(u8 s0,u8 s1)
{

	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);			
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);		

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
	Ramount=(u32) amount*255/R_t;	 			//取R值Ramount=(u32) amount*255/539;	445
	//if(Ramount>255) Ramount = 255;
	return Ramount;
}

u16 tcs3200_GREEN(void)					//打开绿色滤波
{
	S2=1;S3=1;
	amount=0;
	delay_ms(10);
	S2=1;S3=0;								//关闭通道 
	Gamount=(u32) amount*255/G_t;				//取G值Gamount=(u32) amount*255/495;	375
	//if(Gamount>255) Gamount = 255;
	return Gamount;
}

u16 tcs3200_BLUE(void)						//打开蓝色滤波
{
	S2=0;S3=1;
	amount=0;
	delay_ms(10);
	S2=1;S3=0;								//关闭通道 
	Bamount=(u32) amount*255/B_t;				//取B值	Bamount=(u32) amount*255/622;	 428
	//if(Bamount>255) Bamount = 255;
	return Bamount;
} 

float max,min;
int clour_disguish(void)		//颜色识别
{
  int n;
	R = tcs3200_RED();
	G = tcs3200_GREEN();
	B = tcs3200_BLUE();
	
	color_info.r=R;
	color_info.g=G;
	color_info.b=B;
	
	max=R>G?(R>B?R:B):(G>B?G:B);
	min=R<G?(R<B?R:B):(G<B?G:B);
	
	color_info.L=(float)max-((float)max+8)/17+((float)min-((float)min+8)/17);//亮度
	
	if ((float)R == max&&(float)B==min) color_info.H = 40*(float)(G-B)/(max-min);//色相
	if ((float)R == max&&(float)G==min) color_info.H = 20+40*(float)(R-B)/(max-min);
	if ((float)G == max&&(float)R==min) color_info.H = 80 + 40*(float)(B-R)/(max-min);
	if ((float)G == max&&(float)B==min) color_info.H = 40 + 40*(float)(G-R)/(max-min);
	if ((float)B == max&&(float)R==min) color_info.H = 120 + 40*(float)(B-G)/(max-min);
	if ((float)B == max&&(float)G==min) color_info.H = 160 + 40*(float)(R-G)/(max-min);
	
	if(color_info.L>1000 && R>500 && G>500 && B>500) n=3; //白
	else if(R>G && R>B) n=4;//红
	else if(B>R && B>G){if(B>R+40) n=6; //蓝
											else n=5; } //黑
	else n=2;//绿
	return n;
}


void exit_init(void)
{
	
    NVIC_InitTypeDef NVIC_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);


		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource3);

		EXTI_InitStructure.EXTI_Line = EXTI_Line3;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; 
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_InitStructure);
	 
		NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
}

void EXTI3_IRQHandler(void)
{
	amount++;
	
	EXTI_ClearITPendingBit(EXTI_Line3);
	
	
}


