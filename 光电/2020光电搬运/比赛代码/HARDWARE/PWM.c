#include "pwm.h"
#include "stm32f10x_tim.h"

void TIM4_PWM_CH1_Init(u16 arr,u16 psc)                  //左车轮
{
		GPIO_InitTypeDef GPIO_InitStructure;					  
		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;            
		TIM_OCInitTypeDef TIM_OCInitStructure;		             

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);      
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);     
												 
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;                  
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;           
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;         
		GPIO_Init(GPIOB,&GPIO_InitStructure);		            

  	TIM_TimeBaseStructure.TIM_Period=arr;                  
  	TIM_TimeBaseStructure.TIM_Prescaler=psc;            
  	TIM_TimeBaseStructure.TIM_ClockDivision=0;              
  	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
  	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);          

  	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM2;           
  	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
  	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_Low;    
  	TIM_OC1Init(TIM4,&TIM_OCInitStructure);         //初始化外设  TIM4 OC1           
  	TIM_Cmd(TIM4,ENABLE);
}



void TIM4_PWM_CH3_Init(u16 arr,u16 psc)                  //右车轮
{
	  GPIO_InitTypeDef GPIO_InitStructure;					  
  	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;            
    TIM_OCInitTypeDef TIM_OCInitStructure;		             
 
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);      
 	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);     
											 
	  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;                  
	  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;           
	  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;         
	  GPIO_Init(GPIOB,&GPIO_InitStructure);		            

  	TIM_TimeBaseStructure.TIM_Period=arr;                  
  	TIM_TimeBaseStructure.TIM_Prescaler=psc;            
  	TIM_TimeBaseStructure.TIM_ClockDivision=0;              
  	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
  	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);          

  	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM2;           
  	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
  	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_Low;    
  	TIM_OC3Init(TIM4,&TIM_OCInitStructure);                    
  	TIM_Cmd(TIM4,ENABLE);
}




void TIM2_PWM_CH3_Init(u16 arr,u16 psc)                             //钩子1
	{
		GPIO_InitTypeDef GPIO_InitStructure;					 
	  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;        
  	TIM_OCInitTypeDef TIM_OCInitStructure;		         

	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);      
 	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
//    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM2, ENABLE);  //重映射
		
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;           
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;     
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz; 
		GPIO_Init(GPIOA,&GPIO_InitStructure);		       

  	TIM_TimeBaseStructure.TIM_Period=arr;                   
  	TIM_TimeBaseStructure.TIM_Prescaler=psc;               
  	TIM_TimeBaseStructure.TIM_ClockDivision=0;                
  	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
  	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);           

  	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM2;            
  	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
  	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_Low;  
 
  	TIM_OC3Init(TIM2,&TIM_OCInitStructure);  
//    TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);		
  	TIM_Cmd(TIM2,ENABLE);
	}	
	
	
	

void TIM5_PWM_CH1_Init(u16 arr,u16 psc)                           //钩子21
	{
		GPIO_InitTypeDef GPIO_InitStructure;					 
	  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;        
  	TIM_OCInitTypeDef TIM_OCInitStructure;		         

	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);      
 	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);   
//  GPIO_PinRemapConfig(GPIO_PartialRemap_TIM2, ENABLE);  //重映射
		
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;           
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;     
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz; 
		GPIO_Init(GPIOA,&GPIO_InitStructure);		       

  	TIM_TimeBaseStructure.TIM_Period=arr;                   
  	TIM_TimeBaseStructure.TIM_Prescaler=psc;               
  	TIM_TimeBaseStructure.TIM_ClockDivision=0;                
  	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
  	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);           

  	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM2;            
  	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
  	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_Low;  	
  	TIM_OC1Init(TIM5,&TIM_OCInitStructure); 
  	TIM_Cmd(TIM5,ENABLE);
	}
	
	
	

void TIM3_PWM_CH3_Init(u16 arr,u16 psc,u16 ccr3)                             //钩子31
	{
		GPIO_InitTypeDef GPIO_InitStructure;					 
	  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;        
  	TIM_OCInitTypeDef TIM_OCInitStructure;		         

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);   
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);    

		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;           
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;     
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz; 
		GPIO_Init(GPIOB,&GPIO_InitStructure);		       

  	TIM_TimeBaseStructure.TIM_Period=arr;                   
  	TIM_TimeBaseStructure.TIM_Prescaler=psc;               
  	TIM_TimeBaseStructure.TIM_ClockDivision=0;                
  	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
  	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);           

  	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM2;            
  	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
  	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_Low;   
		TIM_OCInitStructure.TIM_Pulse=ccr3;	
  	TIM_OC3Init(TIM3,&TIM_OCInitStructure);                   
  	TIM_Cmd(TIM3,ENABLE);
	}
	
	
	
	

void TIM3_PWM_CH4_Init(u16 arr,u16 psc,u16 ccr4)                             //钩子41
	{
		GPIO_InitTypeDef GPIO_InitStructure;					 
	  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;        
  	TIM_OCInitTypeDef TIM_OCInitStructure;		         

	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);   
   	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);    

		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;           
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;     
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz; 
		GPIO_Init(GPIOB,&GPIO_InitStructure);		       

  	TIM_TimeBaseStructure.TIM_Period=arr;                   
  	TIM_TimeBaseStructure.TIM_Prescaler=psc;               
  	TIM_TimeBaseStructure.TIM_ClockDivision=0;                
  	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
  	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);           

  	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM2;            
  	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
  	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_Low;  
		TIM_OCInitStructure.TIM_Pulse=ccr4;			
  	TIM_OC4Init(TIM3,&TIM_OCInitStructure);  
  	TIM_Cmd(TIM3,ENABLE);
	}
