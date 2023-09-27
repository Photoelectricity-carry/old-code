#include "motor.h"


void MotorL_PWM1_Init(u16 arr,u16 psc)  //����
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  	//TIM5ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//ʹ��PORTFʱ��	
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //GPIOA0
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
	
	//��ʼ��TIM5 Channel1 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
	TIM_OC1Init(TIM5, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 4OC1
  TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);  //ʹ��TIM14��CCR1�ϵ�Ԥװ�ؼĴ���
	 
	
  TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable); 
  TIM_ARRPreloadConfig(TIM5,ENABLE);//ARPEʹ�� 
	
	TIM_Cmd(TIM5, ENABLE);  //ʹ��TIM5
}

void MotorR_PWM2_Init(u16 arr,u16 psc)  //����
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  	//TIM5ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//ʹ��PORTFʱ��	
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM2);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;        //����
	GPIO_Init(GPIOA,&GPIO_InitStructure);              //��ʼ��PF9
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);//��ʼ����ʱ��14
	
	//��ʼ��TIM14 Channel1 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 4OC1
  TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);  //ʹ��TIM14��CCR1�ϵ�Ԥװ�ؼĴ���
	 
	
  TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable); 
  TIM_ARRPreloadConfig(TIM2,ENABLE);//ARPEʹ�� 
	
	TIM_Cmd(TIM2, ENABLE);  //ʹ��TIM5

} 


//void encoder_tim3_init(void)    //����
//{	
//	  GPIO_InitTypeDef GPIO_InitStructure;
//    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//    TIM_ICInitTypeDef TIM_ICInitStructure;

//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
//    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

//    GPIO_StructInit(&GPIO_InitStructure); 
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;   
//    GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_AF;
//    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//    GPIO_Init(GPIOA, &GPIO_InitStructure);                      

//    GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM3);
//    GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_TIM3);

//    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
//    TIM_TimeBaseStructure.TIM_Period = 65535;
//    TIM_TimeBaseStructure.TIM_Prescaler = 0;
//    TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1; 
//    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
//    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

//    TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising ,TIM_ICPolarity_Rising);
//    TIM_ICStructInit(&TIM_ICInitStructure);
//    TIM_ICInitStructure.TIM_ICFilter = 0;
//    TIM_ICInit(TIM3, &TIM_ICInitStructure);
//    TIM_ClearFlag(TIM3, TIM_FLAG_Update);

//    TIM_SetCounter(TIM3,0);
//    TIM_Cmd(TIM3, ENABLE);
//}

//void encoder_tim4_init(void)
//{	
//	  GPIO_InitTypeDef GPIO_InitStructure;
//    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//    TIM_ICInitTypeDef TIM_ICInitStructure;
//    
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
//    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

//    GPIO_StructInit(&GPIO_InitStructure); 
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;   
//    GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_AF;
//    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//    GPIO_Init(GPIOD, &GPIO_InitStructure);                      

//    GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4);
//    GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4);

//    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
//    TIM_TimeBaseStructure.TIM_Period = 65535;
//    TIM_TimeBaseStructure.TIM_Prescaler = 0;
//    TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1; 
//    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
//    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

//    TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising ,TIM_ICPolarity_Rising);
//    TIM_ICStructInit(&TIM_ICInitStructure);
//    TIM_ICInitStructure.TIM_ICFilter = 0;
//    TIM_ICInit(TIM4, &TIM_ICInitStructure);
//    TIM_ClearFlag(TIM4, TIM_FLAG_Update);

//    TIM_SetCounter(TIM4,0);
//    TIM_Cmd(TIM4, ENABLE);
//}


void TIM7_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE);  ///ʹ��TIM3ʱ��
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM7,&TIM_TimeBaseInitStructure);//��ʼ��TIM3
	
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE); //����ʱ��3�����ж�
	TIM_Cmd(TIM7,ENABLE); //ʹ�ܶ�ʱ��3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM7_IRQn; //��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

void Motor_GPIO_init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//ʹ��GPIOFʱ��
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_7 | GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//����
  GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIO
}


double tim=0;
void TIM7_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM7,TIM_IT_Update)==SET)
    {      
			tim+=0.01;
    }
    TIM_ClearITPendingBit(TIM7,TIM_IT_Update); 
}


