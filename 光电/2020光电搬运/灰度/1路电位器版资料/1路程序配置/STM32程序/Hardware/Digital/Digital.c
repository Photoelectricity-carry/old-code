//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ���������������;
//��Ƭ������Ⱥ��439190573
//�Ա��꣺https://futureworldrobot.taobao.com
//�޸����ڣ�2020/6/5
//�汾��V1
//��Ȩ���У�����ؾ���
//δ�����������ϵ��
//////////////////////////////////////////////////////////////////////////////////
#include "Digital.h"
	   	
/*********************************************************************
 *  �������ƣ�void Key_Init
 *  �������ܣ��˿ڳ�ʼ��
 *  ��    �Σ���
 *  ��    ������
 *  ��    ע��		��Ҫ�޸�
 *			   	   
 ********************************************************************/    
void Digital_Init(void)	       
{	
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);		//ʹ�ܶ˿�ʱ��


	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 				//���ó���������
 	GPIO_Init(GPIOD, &GPIO_InitStructure);
}



