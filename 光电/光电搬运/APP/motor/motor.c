#include "stm32f4xx.h"
#include "sys.h"
#include "motor.h"
#include "timer.h"
#include "delay.h"
#include "huidu.h"
#include "pid.h"


PIDtypedef *pidf;

float speed_return;
extern int flag; //前进1，后退0




int speed1;int speed2;//轮子转速


void TIM4_Encoder_Init(u16 arr,u16 psc)    //编码器
{
  TIM_ICInitTypeDef  TIM_ICInitStructure;
GPIO_InitTypeDef  GPIO_InitStructure;


TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
 NVIC_InitTypeDef NVIC_InitStructure;


 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);// 使能定时器时钟	
 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);	//io口使能使用到的捕获编码器AB相借，
 GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4);
 GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4);
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
 GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; 	//浮空输入	 
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
 GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	
 GPIO_Init(GPIOD, &GPIO_InitStructure);
 TIM_DeInit(TIM4); 	
 //推挽输出 ，IO口速度为50MHz

 //初始化TIM4的时机单元
    TIM_TimeBaseStructure.TIM_Period = arr;//899; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 80K
    TIM_TimeBaseStructure.TIM_Prescaler =psc;//0; //设置用来作为TIMx时钟频率除数的预分频值  不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

 
 //配置对应寄存器为编码器接口模式以及配置相关的输入捕获配置
  //THE MODE OF ENCODER 
    
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	选择输入端 IC1映射到TI1上
  	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
  	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
  	TIM_ICInitStructure.TIM_ICFilter = 0x01;//IC1F=0000 配置输入滤波器 不滤波
  	TIM_ICInit(TIM4, &TIM_ICInitStructure);
	
    TIM_ICInitStructure.TIM_Channel=TIM_Channel_2;                  
    TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Rising;	      
    TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;   
    TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1;	            
    TIM_ICInitStructure.TIM_ICFilter=0;                             
    TIM_ICInit(TIM4,&TIM_ICInitStructure);
    TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12,TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);  
							                                                          //TIM_ICPolarity_Rising上升沿捕获 
	// Enable the TIM4 Update Interrupt
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	  
   TIM_ClearFlag(TIM4, TIM_FLAG_Update);
   TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);   
   TIM_SetCounter(TIM4,0);
   TIM_Cmd(TIM4, ENABLE);  //使能TIM4 
  

}

u8  TIM4CH1_CAPTURE_STA=0;	//输入捕获状态		    				
u16	TIM4CH1_CAPTURE_VAL;	//输入捕获值
 
//定时器4中断服务程序	 
void TIM4_IRQHandler(void)
{ 

 	if((TIM4CH1_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{	  
		if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
		 
		{	    
			if(TIM4CH1_CAPTURE_STA&0X40)//已经捕获到高电平了
			{
				if((TIM4CH1_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
				{
					TIM4CH1_CAPTURE_STA|=0X80;//标记成功捕获了一次
					TIM4CH1_CAPTURE_VAL=0XFFFF;
				}else TIM4CH1_CAPTURE_STA++;
			}	 
		}
	
 
    TIM_ClearITPendingBit(TIM4, TIM_IT_Update); //清除中断标志位
 
	}
}


float HF_Get_Encode_TIM4(void)
{
    float cnt;
    cnt  = (float)((uint16_t)0x7fff) - (float)((uint16_t)(TIM4->CNT)) ;
    TIM4->CNT = 0x7fff;
    return cnt;
}
void PWM1_Init(u16 arr,u16 psc)  //左轮
{
	
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  	//TIM5时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//使能PORTF时钟	
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM5); 

	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;        //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure);              //初始化PF9
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=arr;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);//初始化定时器5
	
	//初始化TIM14 Channel1 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性低
	TIM_OC1Init(TIM5, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1
     TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);  //使能TIM14在CCR1上的预装载寄存器
	 
	 
 TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性低
	TIM_OC2Init(TIM5, &TIM_OCInitStructure);
	
     TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable); 
  TIM_ARRPreloadConfig(TIM5,ENABLE);//ARPE使能 
	
	TIM_Cmd(TIM5, ENABLE);  //使能TIM14
 
	
}


void PWM2_Init(u16 arr,u16 psc)  //右轮
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  	//TIM5时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//使能PORTF时钟	
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_TIM5);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_TIM5); 

	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;        //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure);              //初始化PF9
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=arr;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);//初始化定时器14
	
	//初始化TIM14 Channel1 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性低
	TIM_OC3Init(TIM5, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1
     TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable);  //使能TIM14在CCR1上的预装载寄存器
	 
	 
 TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性低
	TIM_OC4Init(TIM5, &TIM_OCInitStructure);
	
     TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable); 
  TIM_ARRPreloadConfig(TIM5,ENABLE);//ARPE使能 
	
	TIM_Cmd(TIM5, ENABLE);  //使能TIM5
 
	
	
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
//  if ()//在黑线
//    goStraight(speed1, speed2);
//  else if ()//偏右
//  { 
//    goStraight(speed1,speed2);
//  }
//  else if ()//偏左
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
//  if ()//在黑线
//    retreat(speed1, speed2);
//  else if ()//偏左
//  {
//	 
//    retreat(speed1, speed2);
//  }
//  else if ()//偏右
//  {
//	
//    retreat(speed1, speed2);
//  }
//  else
//    retreat(a, b);
//}

