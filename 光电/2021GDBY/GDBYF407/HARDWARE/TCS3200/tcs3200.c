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
*		  ������ƽ��
*
*******************************************/
void WhiteBalance(void)
{
	S2=0;S3=0;								//��ɫͨ��
	amount=0;			 					//��ʼ����
	delay_ms(10);
	RGB.Rgena = amount;   					//�����ɫ����      
	amount=0;
  //R=RGB.Rgena;
	
	S2=1;S3=1;								//��ɫͨ��
	amount=0;
  delay_ms(10);
	RGB.Ggena = amount;	 					//�����ɫ����
	amount=0;
  //G=RGB.Ggena;
	
	S2=0;S3=1;								//��ɫͨ��
	amount=0;
	delay_ms(10);
	RGB.Bgena = amount;	  					//�����ɫ����
	amount=0;
	//B=RGB.Bgena ;
	
	S2=1;S3=0;								//�ر�ͨ��  	  
} 


/*******************************************
*
*		  RGB��ȡ
*
*******************************************/
u16 tcs3200_RED(void)						//�򿪺�ɫ�˲�
{
	S2=0;S3=0;                     //��ɫͨ��
	amount=0;
	delay_ms(10);
	S2=1;S3=0;								//�ر�ͨ�� 
	Ramount=(u32) amount*1000/200;	 			//ȡRֵRamount=(u32) amount*255/539;	445
	if(Ramount>1000) Ramount = 1000;
	return Ramount;
}

u16 tcs3200_GREEN(void)					//����ɫ�˲�
{
	S2=1;S3=1;
	amount=0;
	delay_ms(10);
	S2=1;S3=0;								//�ر�ͨ�� 
	Gamount=(u32) amount*1000/180;				//ȡGֵGamount=(u32) amount*255/495;	375
	if(Gamount>1000) Gamount = 1000;
	return Gamount;
}

u16 tcs3200_BLUE(void)						//����ɫ�˲�
{
	S2=0;S3=1;
	amount=0;
	delay_ms(10);
	S2=1;S3=0;								//�ر�ͨ�� 
	Bamount=(u32) amount*1000/210;				//ȡBֵ	Bamount=(u32) amount*255/622;	 428
	if(Bamount>1000) Bamount = 1000;
	return Bamount;
} 
u16 clour_disguish(void)		//��ɫʶ��
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
	
	if((R > 500) && (G > 500) && (B > 500)) 			//ʶ��Ϊ��ɫ3	((R < 255) &&(R > 200)) && ((G < 255) &&(G > 200)) &&((B < 255) && (B > 200))
	{			
		return 3;
	}
	 else if((R < 200) && (G < 200) && (B < 200))			//�����Ǻ�ɫ5
	{						  
		return 5;
	}			
	else if( (R>G) && (R>B)) 				//ʶ��Ϊ��ɫ4		((R > 160)&&(R < 190))&&(R>G)&&(R>B)
	{			
		return 4;
	}
	else if((G>R) && (G>B)) 				//ʶ��Ϊ��ɫ2
	{			
		return 2;
	 }
	else if((B>G) && (B>R)) 					//ʶ��Ϊ��ɫ6
	{			
		return 6;
	}
		R=0;G=0;B=0;
return tmp;
}



