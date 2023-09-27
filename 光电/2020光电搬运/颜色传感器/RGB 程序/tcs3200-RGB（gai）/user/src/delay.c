#include "stm32f10x.h"                  // Device header


void delay_us(u16 nus)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	TIM4->PSC =72-1;
	if(nus>1)
	{
		TIM4->ARR =nus-1;
	}
	else
	{
		TIM4->ARR=1;
	}
	TIM4->EGR |=0X01;
	TIM4->SR &=~(0X01);
	TIM4->CR1 |=0X01<<0;
	while(!(TIM4->SR&(0x01)));  //等待时间到
	TIM4->CR1 &=~(0X01<<0);   //关定时器
}

void delay_ms(u16 nms)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	TIM4->PSC =7200-1;
	TIM4->ARR =10*nms-1;
	TIM4->EGR |=0X01;
	TIM4->SR &=~(0X01);
	TIM4->CR1 |=0X01<<0;
	while(!(TIM4->SR&(0x01)));  //等待时间到
	TIM4->CR1 &=~(0X01<<0);   //关定时器
}

