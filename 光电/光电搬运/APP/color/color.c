#include "color.h"
#include "stm32f4xx.h"
#include "delay.h"
#include "exti.h"

u16 Ramount=0,Gamount=0,Bamount=0;				//���ڴ�Ŷ�ȡ��RGBֵ
u16 amount=0;									//�жϼ���
//u16 R,G,B;
_RGB RGB;
void tcs3200_init(u8 s0,u8 s1)
{

	GPIO_InitTypeDef	GPIO_InitStructure;
		
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);//ʹ��PB�˿�ʱ��
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;	//�������
    //GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;//����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	S0=s0;
	S1=s1;
 
}


/*******************************************
*
*		  ��ƽ��
*
*******************************************/
void WhiteBalance(void)
{   
	EXTIX_Init();
	S2=0;S3=0;								//��ɫͨ��
	amount=0;			 					//��ʼ����
	delay_ms(10);
	RGB.Rgena = 255/amount;   					//�����ɫ����      
	amount=0;
  //R=RGB.Rgena;
	
	S2=1;S3=1;								//��ɫͨ��
	amount=0;
   delay_ms(10);
	RGB.Ggena = 255/amount;	 					//�����ɫ����
	amount=0;
  //G=RGB.Ggena;
	
	S2=0;S3=1;								//��ɫͨ��
	amount=0;
	delay_ms(10);
	RGB.Bgena = 255/amount;	  					//�����ɫ����
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
	Ramount=(u32) RGB.Rgena*amount;	 			//ȡRֵRamount=(u32) amount*255/539;	
	if(Ramount>255) Ramount = 255;
	return Ramount;
}

u16 tcs3200_GREEN(void)					//����ɫ�˲�
{
	S2=1;S3=1;
	amount=0;
	delay_ms(10);
	S2=1;S3=0;								//�ر�ͨ�� 
	Gamount=(u32) RGB.Ggena *amount;				//ȡGֵGamount=(u32) amount*255/495;	
	if(Gamount>255) Gamount = 255;
	return Gamount;
}

u16 tcs3200_BLUE(void)						//����ɫ�˲�
{
	S2=0;S3=1;
	amount=0;
	delay_ms(10);
	S2=1;S3=0;								//�ر�ͨ�� 
	Bamount=(u32) RGB.Bgena*amount;				//ȡBֵ	Bamount=(u32) amount*255/622;	
	if(Bamount>255) Bamount = 255;
	return Bamount;
} 
//u16 clour_disguish(void)		//��ɫʶ��
//{
//	u16 tmp=3;
//	R = tcs3200_RED();
//	G = tcs3200_GREEN();
//	B = tcs3200_BLUE();
//	if(((R <= 255) &&(R > 200)) && ((G <=255) &&(G > 200)) &&((B <= 255) && (B > 200))) 			//ʶ��Ϊ��ɫ	((R < 255) &&(R > 200)) && ((G < 255) &&(G > 200)) &&((B < 255) && (B > 200))
//	{			
//		return 0;
//	}
//	 else if((R < 90) && (G < 90) && (B < 90))				//�����Ǻ�ɫ
//	{						  
//		return 1;
//	}			
//	else if(((R > 150)&&(R < 190))&&(R>G)&&(R>B)) 				//ʶ��Ϊ��ɫ		((R > 160)&&(R < 190))&&(R>G)&&(R>B)
//	{			
//		return 2;
//	}
//	else if((G<130)&&(G > 95)&&(G>R)&&(G>B)) 								//ʶ��Ϊ��ɫ
//	{			
//		return 3;
//	 }
//	else if((B<130)&&(B>90)&&(B>R)&&(B>G)) 								//ʶ��Ϊ��ɫ
//	{			
//		return 4;
//	}
//	return tmp;
//}
