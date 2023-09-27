#ifndef __TCS3200_H
#define __TCS3200_H	 
#include "sys.h"

#define __LED_H	 
#include "sys.h"

extern u16 Ramount,Gamount,Bamount;			//���ڴ�Ŷ�ȡ��RGBֵ
extern u16 amount;							//�жϼ�������¼ÿ�ε�Ƶ��ֵ
extern u16 R,G,B;							//���ڴ��ͨ����ͬ�˲���ֵ
extern u16 tmp;

typedef struct   
{
	
	u16 Rgena;
	u16 Ggena;
	u16 Bgena;
}_RGB;									   //�����ڵ�����ƽ��󣬴�ű�׼ֵ

extern _RGB RGB;

#define S0 PAout(9)							//TCS3200���Ʊ����ˣ�s0��s1��
#define S1 PAout(10)						
#define S2 PAout(11)						//TCS3200�˲���ѡ��ˣ�s2��s3��
#define S3 PAout(12)						
#define EO PAout(13)						//TCS3200����ʹ�ܶ�
#define OUT PAin(8)						//TCS3200���������

void TCS3200_Init(u8 s0,u8 s1);				//TCS3200��ʼ������
void WhiteBalance(void);					//���˲���������ƽ��
u16 tcs3200_RED(void);						//���˲������r��ֵ
u16 tcs3200_GREEN(void);					//���˲������g��ֵ
u16 tcs3200_BLUE(void);					//���˲������b��ֵ
u16 clour_disguish(void);		//��ɫʶ��


//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
#define LED0 PBout(5)// PB5
#define LED1 PEout(5)// PE5	

void LED_Init(void);//��ʼ��

		 				    
#endif
