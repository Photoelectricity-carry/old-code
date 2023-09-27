#include "stm32f4xx.h"
#include "sys.h"
#include "motor.h"
#include "timer.h"
#include "delay.h"
#include "huidu.h"
#include "pid.h"


PIDtypedef *pidf;

float speed_return;
extern int flag; //ǰ��1������0




int speed1;int speed2;//����ת��


void TIM4_Encoder_Init(u16 arr,u16 psc)    //������
{
  TIM_ICInitTypeDef  TIM_ICInitStructure;
GPIO_InitTypeDef  GPIO_InitStructure;


TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
 NVIC_InitTypeDef NVIC_InitStructure;


 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);// ʹ�ܶ�ʱ��ʱ��	
 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);	//io��ʹ��ʹ�õ��Ĳ��������AB��裬
 GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4);
 GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4);
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
 GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; 	//��������	 
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
 GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	
 GPIO_Init(GPIOD, &GPIO_InitStructure);
 TIM_DeInit(TIM4); 	
 //������� ��IO���ٶ�Ϊ50MHz

 //��ʼ��TIM4��ʱ����Ԫ
    TIM_TimeBaseStructure.TIM_Period = arr;//899; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 80K
    TIM_TimeBaseStructure.TIM_Prescaler =psc;//0; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

 
 //���ö�Ӧ�Ĵ���Ϊ�������ӿ�ģʽ�Լ�������ص����벶������
  //THE MODE OF ENCODER 
    
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
  	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
  	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
  	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
  	TIM_ICInitStructure.TIM_ICFilter = 0x01;//IC1F=0000 ���������˲��� ���˲�
  	TIM_ICInit(TIM4, &TIM_ICInitStructure);
	
    TIM_ICInitStructure.TIM_Channel=TIM_Channel_2;                  
    TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Rising;	      
    TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;   
    TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1;	            
    TIM_ICInitStructure.TIM_ICFilter=0;                             
    TIM_ICInit(TIM4,&TIM_ICInitStructure);
    TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12,TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);  
							                                                          //TIM_ICPolarity_Rising�����ز��� 
	// Enable the TIM4 Update Interrupt
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	  
   TIM_ClearFlag(TIM4, TIM_FLAG_Update);
   TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);   
   TIM_SetCounter(TIM4,0);
   TIM_Cmd(TIM4, ENABLE);  //ʹ��TIM4 
  

}

u8  TIM4CH1_CAPTURE_STA=0;	//���벶��״̬		    				
u16	TIM4CH1_CAPTURE_VAL;	//���벶��ֵ
 
//��ʱ��4�жϷ������	 
void TIM4_IRQHandler(void)
{ 

 	if((TIM4CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
	{	  
		if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
		 
		{	    
			if(TIM4CH1_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
			{
				if((TIM4CH1_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
				{
					TIM4CH1_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
					TIM4CH1_CAPTURE_VAL=0XFFFF;
				}else TIM4CH1_CAPTURE_STA++;
			}	 
		}
	
 
    TIM_ClearITPendingBit(TIM4, TIM_IT_Update); //����жϱ�־λ
 
	}
}


float HF_Get_Encode_TIM4(void)
{
    float cnt;
    cnt  = (float)((uint16_t)0x7fff) - (float)((uint16_t)(TIM4->CNT)) ;
    TIM4->CNT = 0x7fff;
    return cnt;
}
void PWM1_Init(u16 arr,u16 psc)  //����
{
	
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  	//TIM5ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//ʹ��PORTFʱ��	
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM5); 

	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;        //����
	GPIO_Init(GPIOA,&GPIO_InitStructure);              //��ʼ��PF9
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);//��ʼ����ʱ��5
	
	//��ʼ��TIM14 Channel1 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
	TIM_OC1Init(TIM5, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 4OC1
     TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);  //ʹ��TIM14��CCR1�ϵ�Ԥװ�ؼĴ���
	 
	 
 TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
	TIM_OC2Init(TIM5, &TIM_OCInitStructure);
	
     TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable); 
  TIM_ARRPreloadConfig(TIM5,ENABLE);//ARPEʹ�� 
	
	TIM_Cmd(TIM5, ENABLE);  //ʹ��TIM14
 
	
}


void PWM2_Init(u16 arr,u16 psc)  //����
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  	//TIM5ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//ʹ��PORTFʱ��	
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_TIM5);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_TIM5); 

	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;        //����
	GPIO_Init(GPIOA,&GPIO_InitStructure);              //��ʼ��PF9
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);//��ʼ����ʱ��14
	
	//��ʼ��TIM14 Channel1 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
	TIM_OC3Init(TIM5, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 4OC1
     TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable);  //ʹ��TIM14��CCR1�ϵ�Ԥװ�ؼĴ���
	 
	 
 TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
	TIM_OC4Init(TIM5, &TIM_OCInitStructure);
	
     TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable); 
  TIM_ARRPreloadConfig(TIM5,ENABLE);//ARPEʹ�� 
	
	TIM_Cmd(TIM5, ENABLE);  //ʹ��TIM5
 
	
	
} 


void goStraight(int speed1,int speed2)
{
	TIM_SetCompare1(TIM5,speed1);
	TIM_SetCompare2(TIM5,0);

	TIM_SetCompare3(TIM5,speed2);
	TIM_SetCompare4(TIM5,0);
}

void retreat(int speed1,int speed2)
{
    TIM_SetCompare1(TIM5,0);
	TIM_SetCompare2(TIM5,speed1);

	TIM_SetCompare3(TIM5,0);
	TIM_SetCompare4(TIM5,speed2);
}

void turn_right(int speed1,int speed2,int n)
{   
	TIM_SetCompare1(TIM5,speed1);
	TIM_SetCompare2(TIM5,0);

	TIM_SetCompare3(TIM5,0);
	TIM_SetCompare4(TIM5,speed2);
}

void turn_left(int speed1,int speed2,int n)
{
	TIM_SetCompare1(TIM5,0);
	TIM_SetCompare2(TIM5,speed1);

	TIM_SetCompare3(TIM5,speed2);
	TIM_SetCompare4(TIM5,0);
}

void stop(int n)
{
	TIM_SetCompare1(TIM5,0);
	TIM_SetCompare2(TIM5,0);

	TIM_SetCompare3(TIM5,0);
	TIM_SetCompare4(TIM5,0);
}



//void yanxianzou(int speed1, int speed2) {
//	int a,b;
//  a=speed1,b=speed2;
// 
//   pid_return  =PID_Calc(pidf,speed_return,150);
//  if ()//�ں���
//    goStraight(speed1, speed2);
//  else if ()//ƫ��
//  { 
//    goStraight(speed1,speed2);
//  }
//  else if ()//ƫ��
//  { 
//	 ;
//     goStraight(speed1, speed2);
//  }
//  else
//    goStraight(a, b);
//}

//void yanxiantui(int speed1, int speed2) {
//  int a,b;
//  a=speed1,b=speed2;
// 
// pid_return= PID_Calc(pidf,speed_return,150);
//  if ()//�ں���
//    retreat(speed1, speed2);
//  else if ()//ƫ��
//  {
//	 
//    retreat(speed1, speed2);
//  }
//  else if ()//ƫ��
//  {
//	
//    retreat(speed1, speed2);
//  }
//  else
//    retreat(a, b);
//}

