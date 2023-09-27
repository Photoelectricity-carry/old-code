#include "truck.h"
#include "sys.h"
#include "delay.h"
#include "string.h"
#include <stdlib.h>

//��ʼ��IO ����3
//pclk1:PCLK1ʱ��Ƶ��(Mhz)
//bound:������	  
void usart3_init(u32 bound)
{  

	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);	// GPIOBʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE); //����3ʱ��ʹ��
  GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3); //GPIOB10����ΪUSART3
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3); //GPIOB11����ΪUSART3
 	USART_DeInit(USART3);  //��λ����3
	 //USART3_TX   PB10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PB10
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����	//�����������
	GPIO_Init(GPIOB, &GPIO_InitStructure); //��ʼ��PB

	//USART3_RX	  PB11
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//��������
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);  //��ʼ��PB11
	
	USART_InitStructure.USART_BaudRate = bound;//������һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  
	USART_Init(USART3, &USART_InitStructure); //��ʼ������	3
  

	USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ��� 
	
	//ʹ�ܽ����ж�
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�����ж�   
	
	//�����ж����ȼ�
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�ж���ѡ�ڶ���
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���

}

u8 USART_RX[3] = { 0 };       //����״̬���	  
u8 Num = 0;              //�������ݵĵ�ǰλ��

/*********************************************************************
 *  �������ƣ�Read_Data(u8 *Data)
 *  �������ܣ���ȡ�������ݲ��������ݻ�����
 *  ��    �Σ�*Data��ָ��
 *  ��    ������
 *  ��    ע��
 *			   	   
 ********************************************************************/    
void Read_Data(u16 *Data)	       
{	
	u8 y=0;
	u16 Receive_data = 0;       //���ݻ�����
	
	while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
	USART_SendData(USART3, 0x57);
	while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
	
///////////////////////////��������ֵ///////////////////////////////	
	
//	while(Num != 1)
//	{
//		
//		Delay_ms(1);
//		if(y>5)
//		{
//			y=0;
//			break;
//		}
//		y++;
//	}
//	*Data = USART_RX_STA[0];

///////////////////////////��������ֵ///////////////////////////////	

///////////////////////////ƫ������ֵ///////////////////////////////	
//	
	while(Num != 3)
	{
		
		delay_ms(1);
		if(y>10)
		{
			y=0;
			break;
		}
		y++;
	}
	Receive_data = USART_RX[1];
	Receive_data <<= 8;
	Receive_data |= USART_RX[2];

	*Data = USART_RX[0];
	*(Data+1) = Receive_data;
//	
///////////////////////////ƫ������ֵ///////////////////////////////	

	Num = 0; 
}
/*********************************************************************
 *  �������ƣ�void USART3_IRQHandler
 *  �������ܣ�����3�жϷ�����
 *  ��    �Σ���
 *  ��    ������
 *  ��    ע����
 ********************************************************************/
void USART3_IRQHandler(void)
{
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //�����ж�
	{
		USART_RX[Num++] =USART_ReceiveData(USART3);	//��ȡ���յ�������
	} 	
}






void TRUCK_GPIO()
{
		GPIO_InitTypeDef  GPIO_InitStructure;	
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);	 
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |GPIO_Pin_11 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;		
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;	 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
		GPIO_Init(GPIOC, &GPIO_InitStructure);					


}

#define speed_max 2000

void motor_set(int speed_l_set,int speed_r_set)
{
	if(speed_l_set>speed_max)
		speed_l_set=speed_max;
	if(speed_r_set>speed_max)
		speed_r_set=speed_max;
	TIM_SetCompare1(TIM5,speed_l_set);
	TIM_SetCompare2(TIM2,speed_r_set);
	
}


