#include "timer.h"
#include "stm32f4xx.h"

void TIM3_PWM_Init(u16 arr,u16 psc)   //TIM3 舵机
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//使能定时器3时钟
 	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA |RCC_AHB1Periph_GPIOB ,ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6|GPIO_Pin_7,GPIO_AF_TIM3);
    GPIO_PinAFConfig(GPIOB,GPIO_PinSource0|GPIO_Pin_1,GPIO_AF_TIM3);
	
	
   //设置该引脚为复用输出功能,输出TIM3 CH2的PWM脉冲波形	GPIOB.5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; //TIM_CH 1-2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;  //复用推挽输出
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; //TIM_CH 3-4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;  //复用推挽输出
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
 
   //初始化TIM3
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
 	TIM_OCInitStructure.TIM_Pulse = 0;//初始占空比为0
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM2 OC1
	 TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM2在CCR1上的预装载寄存器
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
 	TIM_OCInitStructure.TIM_Pulse = 0;//初始占空比为0
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM2 OC2
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM2在CCR2上的预装载寄存器
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
 	TIM_OCInitStructure.TIM_Pulse = 0;//初始占空比为0
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM2 OC3
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM2在CCR3上的预装载寄存器
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
 	TIM_OCInitStructure.TIM_Pulse = 0;//初始占空比为0
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM2 OC4
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM2在CCR4上的预装载寄存器
	
 
   TIM_ARRPreloadConfig(TIM3, ENABLE); //使能TIMx在ARR上的预装载寄存器
	
 	TIM_Cmd(TIM3, ENABLE);  //使能TIM3
	
}








void TIM1_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure; 
	/*配置TIM1*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure; 
	
		/*开时钟PWM的时钟与GPIO的时钟*/ 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource8,GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource11,GPIO_AF_TIM1);
	/* PA8设置为功能脚(PWM) */ 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;  //复用推挽输出
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure); 


	
 TIM_DeInit(TIM1); //重设为缺省值 
/*TIM1时钟配置*/ 
TIM_TimeBaseStructure.TIM_Prescaler = psc; //预分频(时钟分频)72M/4000=18K	
TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数
TIM_TimeBaseStructure.TIM_Period = arr; //装载值?18k/144=125hz 就是说向上加的144便满了 
TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置了时钟分割?不懂得不管	
TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0; //周期计数器值?不懂得不管	
TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure); //初始化TIMx的时间基数单位	


    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
 	TIM_OCInitStructure.TIM_Pulse = 0;//初始占空比为0
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM2 OC1
	 TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //使能TIM2在CCR1上的预装载寄存器
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
 	TIM_OCInitStructure.TIM_Pulse = 0;//初始占空比为0
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM2 OC2
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);  //使能TIM2在CCR2上的预装载寄存器
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
 	TIM_OCInitStructure.TIM_Pulse = 0;//初始占空比为0
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC3Init(TIM1, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM2 OC3
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);  //使能TIM2在CCR3上的预装载寄存器
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
 	TIM_OCInitStructure.TIM_Pulse = 0;//初始占空比为0
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM2 OC4
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);  //使能TIM2在CCR4上的预装载寄存器
	
 
   TIM_ARRPreloadConfig(TIM1, ENABLE); //使能TIMx在ARR上的预装载寄存器
	
 	TIM_Cmd(TIM1, ENABLE);  //使能TIM3
}
//TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //PWM模式2
//TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //正向通道有效 PA8
//TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable; //反向通道也有效 PB13
//TIM_OCInitStructure.TIM_Pulse = 0; //占空时间 144 中有40的时间为高，互补的输出正好相反
//TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性
//TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low; //互补端的极性
//TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset; //空闲状态下的非工作状态?不管
//TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset; //先不管

//  
//	TIM_OC1Init(TIM1,&TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM2 OC1
//	TIM_OC2Init(TIM1, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM2 OC2
//	TIM_OC3Init(TIM1, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM2 OC3
//	TIM_OC4Init(TIM1, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM2 OC4
//	
//  TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //使能TIM2在CCR1上的预装载寄存器
//	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);  //使能TIM2在CCR2上的预装载寄存器
//	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);  //使能TIM2在CCR3上的预装载寄存器
//	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);  //使能TIM2在CCR4上的预装载寄存器

//TIM_ARRPreloadConfig(TIM1, ENABLE); //使能TIMx在ARR上的预装载寄存器
//	
//TIM_Cmd(TIM1,ENABLE);	

//TIM_CtrlPWMOutputs(TIM1,ENABLE);

//}

