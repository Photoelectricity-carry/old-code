#include "truck.h"
#include "sys.h"
#include "delay.h"
#include "string.h"
#include <stdlib.h>

//初始化IO 串口3
//pclk1:PCLK1时钟频率(Mhz)
//bound:波特率	  
void usart3_init(u32 bound)
{  

	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);	// GPIOB时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE); //串口3时钟使能
  GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3); //GPIOB10复用为USART3
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3); //GPIOB11复用为USART3
 	USART_DeInit(USART3);  //复位串口3
	 //USART3_TX   PB10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PB10
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉	//复用推挽输出
	GPIO_Init(GPIOB, &GPIO_InitStructure); //初始化PB

	//USART3_RX	  PB11
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//浮空输入
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);  //初始化PB11
	
	USART_InitStructure.USART_BaudRate = bound;//波特率一般设置为9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  
	USART_Init(USART3, &USART_InitStructure); //初始化串口	3
  

	USART_Cmd(USART3, ENABLE);                    //使能串口 
	
	//使能接收中断
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启中断   
	
	//设置中断优先级
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//中断组选第二组
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器

}

u8 USART_RX[3] = { 0 };       //接收状态标记	  
u8 Num = 0;              //接收数据的当前位置

/*********************************************************************
 *  函数名称：Read_Data(u8 *Data)
 *  函数功能：读取串口数据并赋给数据缓存区
 *  形    参：*Data，指针
 *  输    出：无
 *  备    注：
 *			   	   
 ********************************************************************/    
void Read_Data(u16 *Data)	       
{	
	u8 y=0;
	u16 Receive_data = 0;       //数据缓存区
	
	while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
	USART_SendData(USART3, 0x57);
	while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
	
///////////////////////////数字量数值///////////////////////////////	
	
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

///////////////////////////数字量数值///////////////////////////////	

///////////////////////////偏移量数值///////////////////////////////	
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
///////////////////////////偏移量数值///////////////////////////////	

	Num = 0; 
}
/*********************************************************************
 *  函数名称：void USART3_IRQHandler
 *  函数功能：串口3中断服务函数
 *  形    参：无
 *  输    出：无
 *  备    注：无
 ********************************************************************/
void USART3_IRQHandler(void)
{
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //接收中断
	{
		USART_RX[Num++] =USART_ReceiveData(USART3);	//读取接收到的数据
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


