#include "gouzi.h"
#include "pwm.h"
#include "delay.h"
#include "speed.h"
u16 i;
u16 next_state[4],next_state1[4];
u16 last_state[4]={149,149,149,149},last_state1[4]={149,149,149,149};
void  gouzi1(u16 x)
{
	int distance1[2]={0}; 
	u16 max=0;
	u8 i=0;
	u8 j=0;
	
	
	next_state1[2]=x;
  distance1[0]=next_state1[2]-last_state1[2];
	distance1[1]=next_state1[3]-last_state1[3];
	
	
	for(i=0;i<2;i++)
	{
		if(distance1[i]<0)
		{
			distance1[i]=-distance1[i];
		}
	}
	
	if(distance1[0] < distance1[1])
	{
		max=distance1[1];
	}
	else
	{
		max=distance1[0];
	}
	
	for(i=0;i<max+1;i++)
	{
		for(j=2;j<4;j++)
		{
			if(last_state1[j]<next_state1[j])
			{
				last_state1[j]++;
			}
			else if(last_state1[j]>next_state1[j])
			{
				last_state1[j]--;
			}
		}
			TIM_SetCompare3(TIM2,last_state1[2]);  //<150    ×ó
			delay_ms(15,0);
	}
}

void  gouzi21(u16 y)
{
	int distance[2]={0}; 
	u16 max=0;
	u8 i=0;
	u8 j=0;
	
	next_state[3]=y;
	
	distance[0]=next_state[2]-last_state[2];
	distance[1]=next_state[3]-last_state[3];
	
	
	for(i=0;i<2;i++)
	{
		if(distance[i]<0)
		{
			distance[i]=-distance[i];
		}
	}
	
	if(distance[0] < distance[1])
	{
		max=distance[1];
	}
	else
	{
		max=distance[0];
	}
	
	for(i=0;i<max+1;i++)
	{
		for(j=2;j<4;j++)
		{
			if(last_state[j]<next_state[j])
			{
				last_state[j]++;
			}
			else if(last_state[j]>next_state[j])
			{
				last_state[j]--;
			}
		}
			TIM_SetCompare1(TIM5,last_state[3]);  //<150    ÏÂ
			delay_ms(15,0);
	}
}

void  gouzi31(u16 x)
{
	TIM3_PWM_CH3_Init(19999,71,x);	//b7
}

void  gouzi41(u16 x)
{
	TIM3_PWM_CH4_Init(19999,71,x);
}

	