#include "motor.h"
#include "main.h"

void encoder_tim3_init(void)
{
	// GPIO�ڳ�ʼ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;  // GPIO�ڵ�����ģʽ���ú���Ҫ������ȷ�Ļ������������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_TIM3);    
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_TIM3);
	
	// ��ʱ��������ģʽ��ʼ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	TIM_DeInit(TIM3);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_Period = 65535;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // ��������Լ����ã���ʹ��Ĭ��ֵ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising ,TIM_ICPolarity_Rising); // ���������˱�����ģʽ
	
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 10; // ��������Լ����ã���ʹ��Ĭ��ֵ
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	
	TIM_SetCounter(TIM3, 0);
	TIM_Cmd(TIM3, ENABLE);
}

void encoder_tim1_init(void)
{
	// GPIO�ڳ�ʼ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;  // GPIO�ڵ�����ģʽ���ú���Ҫ������ȷ�Ļ������������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_TIM1);    
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_TIM1);
	
	// ��ʱ��������ģʽ��ʼ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	
	TIM_DeInit(TIM1);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_Period = 65535;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // ��������Լ����ã���ʹ��Ĭ��ֵ
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
	
	TIM_EncoderInterfaceConfig(TIM1, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising ,TIM_ICPolarity_Rising); // ���������˱�����ģʽ
	
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 10; // ��������Լ����ã���ʹ��Ĭ��ֵ
	TIM_ICInit(TIM1, &TIM_ICInitStructure);
	
	TIM_SetCounter(TIM1, 0);
	TIM_Cmd(TIM1, ENABLE);
}

void MotorL_PWM_Init(u16 arr,u16 psc)  //����
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

void MotorR_PWM_Init(u16 arr,u16 psc)  //����
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

void Motor_GPIO_init(void)
{
	 GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//ʹ��GPIOFʱ��
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//����
  GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIO
}

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

EcoderTypeDef encoder;


//int read_encoder_l(void)
//{
//	encoder.encoder_num_l = (int)((int16_t)(TIM3->CNT));
//	encoder.all_num_l += (int)((int16_t)(TIM3->CNT)); // ����������Ҫע����������
////	TIM_SetCounter(TIM3, 0);
//	return encoder.all_num_l;
//}

//int read_encoder_r(void)
//{
//	encoder.encoder_num_r = (int)((int16_t)(TIM1->CNT));
//	encoder.all_num_r += (int)((int16_t)(TIM1->CNT)); // ����������Ҫע����������
////	TIM_SetCounter(TIM3, 0);
//	return encoder.all_num_r;
//}

double time=0;
void TIM7_IRQHandler(void)
{
  if(TIM_GetITStatus(TIM7,TIM_IT_Update)==SET)
  {
		encoder.encoder_num_l = (int)((int16_t)(TIM3->CNT));
	  encoder.all_num_l += (int)((int16_t)(TIM3->CNT));
		encoder.encoder_num_r = (int)((int16_t)(TIM1->CNT));
	  encoder.all_num_r += (int)((int16_t)(TIM1->CNT)); 
		encoder.speed_l=encoder.encoder_num_l/1320.0f*(2.0f*PI*7.0f)*10;
		encoder.speed_r=encoder.encoder_num_r/1320.0f*(2.0f*PI*7.0f)*10;
		TIM1->CNT=0;
		TIM3->CNT=0;
		time+=0.01;
	}
  TIM_ClearITPendingBit(TIM7,TIM_IT_Update); 
}

void motor_speed(double left,double right)
{
	if(left>=0){
		GPIO_SetBits(GPIOE,GPIO_Pin_10);
		GPIO_ResetBits(GPIOE,GPIO_Pin_9);
		TIM_SetCompare1(TIM5,left);
	}
	if(left<0){
		left=-left;
		GPIO_SetBits(GPIOE,GPIO_Pin_9);
		GPIO_ResetBits(GPIOE,GPIO_Pin_10);
		TIM_SetCompare1(TIM5,left);
	}
	if(right>=0){
		GPIO_SetBits(GPIOE,GPIO_Pin_12);
		GPIO_ResetBits(GPIOE,GPIO_Pin_11);
		TIM_SetCompare2(TIM2,right);
	}
	if(right<0){
		right=-right;
		GPIO_SetBits(GPIOE,GPIO_Pin_11);
		GPIO_ResetBits(GPIOE,GPIO_Pin_12);
		TIM_SetCompare2(TIM2,right);
	}
}
