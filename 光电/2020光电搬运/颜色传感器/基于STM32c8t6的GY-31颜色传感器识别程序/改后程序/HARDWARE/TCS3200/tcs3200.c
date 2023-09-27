#include "tcs3200.h"
#include "exti.h"
#include "delay.h"
#include "tcs3200.h"
#include "stmflash.h"



void tcs3200_init(u8 s0,u8 s1)
{

	GPIO_InitTypeDef	GPIO_InitStructure;
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//ʹ��PB�˿�ʱ��
	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//��������
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//IO���ٶ�Ϊ50MHz
//	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	S0=s0;
	S1=s1;

}
/*******************************************
*
*		  ��ƽ��
*
*******************************************/
void whitebalance(void)
{
	u16 x[3];
	EXTIX_Init();		 //�ⲿ�жϳ�ʼ��
	S2=0;S3=0;//��ɫͨ��
	amount=0;			 //��ʼ����
	delay_ms(10);
	Rgena = amount;   //�����ɫ����      
	amount=0;
	x[0]=Rgena;
//	STMFLASH_Write(0x08004000,(u16*)x[0],1);
//								 0x08000000
//----------------------------------
	S2=1;S3=1;//��ɫͨ��
	amount=0;
	delay_ms(10);
	Ggena = amount;	 //�����ɫ����
	amount=0;
	x[1]=Ggena;
//	STMFLASH_Write(0x08004100,(u16*)x1[0],1);

//----------------------------------
	S2=0;S3=1;//��ɫͨ��
	amount=0;
	delay_ms(10);
	Bgena = amount;	  //�����ɫ����
	amount=0;
	x[2]=Bgena;
	STMFLASH_Write(0x08004000,(u16*)x,3);
	
	S2=1;S3=0;//�ر�ͨ��  


}  

u16 tcs3200_RED(void)
{
	S2=0;S3=0;
	amount=0;
	delay_ms(10);
	Ramount=(u32) amount*255/Rgena;	 //ȡRֵ
	if(Ramount>255) Ramount = 255;
	return Ramount;
//	amount=0;
}

u16 tcs3200_GREEN(void)
{
	S2=1;S3=1;
	amount=0;
	delay_ms(10);
	Gamount=(u32) amount*255/Ggena;	//ȡGֵ
	if(Gamount>255) Gamount = 255;
	return Gamount;
//	amount=0;
}

u16 tcs3200_BLUE(void)
{
	S2=0;S3=1;
	amount=0;
	delay_ms(10);
	Bamount=(u32) amount*255/Bgena;//ȥBֵ
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

