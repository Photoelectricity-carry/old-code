#include "TCS3200.h"
#include "exit.h"
#include "delay.h"


u16 Ramount=0,Gamount=0,Bamount=0;				//���ڴ�Ŷ�ȡ��RGBֵ
u16 amount=0;									//�жϼ���
u16 R,G,B;
_RGB RGB;

/*******************************************
*
*		TCS3200��ʼ��  
*
*******************************************/
  void TCS3200_Init(u8 s0,u8 s1)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 
	//S0--->PA9		S1--->PA10		S2--->PA11		S3--->PA12
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(GPIOA, &GPIO_InitStructure);			

	S0=s0;
	S1=s1;
	EO=0;	
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
	delay_ms(10,0);
	RGB.Rgena = amount;   					//�����ɫ����      
	amount=0;
  //R=RGB.Rgena;
	
	S2=1;S3=1;								//��ɫͨ��
	amount=0;
  delay_ms(10,0);
	RGB.Ggena = amount;	 					//�����ɫ����
	amount=0;
  //G=RGB.Ggena;
	
	S2=0;S3=1;								//��ɫͨ��
	amount=0;
	delay_ms(10,0);
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
	delay_ms(10,0);
	S2=1;S3=0;								//�ر�ͨ�� 
	Ramount=(u32) amount*255/863;	 			//ȡRֵRamount=(u32) amount*255/539;	
	if(Ramount>255) Ramount = 255;
	return Ramount;
}

u16 tcs3200_GREEN(void)					//����ɫ�˲�
{
	S2=1;S3=1;
	amount=0;
	delay_ms(10,0);
	S2=1;S3=0;								//�ر�ͨ�� 
	Gamount=(u32) amount*255/865;				//ȡGֵGamount=(u32) amount*255/495;	
	if(Gamount>255) Gamount = 255;
	return Gamount;
}

u16 tcs3200_BLUE(void)						//����ɫ�˲�
{
	S2=0;S3=1;
	amount=0;
	delay_ms(10,0);
	S2=1;S3=0;								//�ر�ͨ�� 
	Bamount=(u32) amount*255/1243;				//ȡBֵ	Bamount=(u32) amount*255/622;	
	if(Bamount>255) Bamount = 255;
	return Bamount;
} 
u16 clour_disguish(void)		//��ɫʶ��
{
	u16 tmp=0;
	R = tcs3200_RED();
	G = tcs3200_GREEN();
	B = tcs3200_BLUE();
	if(((R <= 255) &&(R > 200)) && ((G <=255) &&(G > 200)) &&((B <= 255) && (B > 200))) 			//ʶ��Ϊ��ɫ	((R < 255) &&(R > 200)) && ((G < 255) &&(G > 200)) &&((B < 255) && (B > 200))
	{			
		return 0;
	}
	 else if((R < 90) && (G < 90) && (B < 90))				//�����Ǻ�ɫ
	{						  
		return 1;
	}			
	else if((R<199)&&(R>120)&&(R>G)&&(R>B)) 				//ʶ��Ϊ��ɫ		((R > 160)&&(R < 190))&&(R>G)&&(R>B)
	{			
		return 2;
	}
	else if((G<130)&&(G> 90)&&(G>R)&&(G>B)) 								//ʶ��Ϊ��ɫ
	{			
		return 3;
	 }
	else if((B<135)&&(B>90)&&(B>R)&&(B>G)) 								//ʶ��Ϊ��ɫ
	{			
		return 4;
	}
return tmp;
}
