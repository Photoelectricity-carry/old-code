#include "turn.h"
#include "speed.h"
#include "direction.h"
#include "delay.h"
void Turn45(u8 direction,u16 time)
{
	if(direction==0)  //��ת
	{
	  Direction(0,1); 
	  Speed(1950,1800);
	  delay_ms(time,0);
	  Speed(500,500);
	  delay_ms(100,0);
	}
	if(direction==1)   //��ת
	{
	  Direction(1,0);
	  Speed(1900,2150);
	  delay_ms(time,0);
	  Speed(500,500);
	  delay_ms(100,0);
	}
}

void Turn90(u8 direction,u16 time)
{
	if(direction==0)  //��ת
	{
	  Direction(0,0); 
	  Speed(2950,3000);
	  delay_ms(time,0);
		delay_ms(time,0);
	  Speed(500,800);
	  delay_ms(100,0);
	}
	if(direction==1)   //��ת
	{
	  Direction(1,1);
	  Speed(2950,3000);
	  delay_ms(time,0);
		delay_ms(time,0);
	  Speed(500,500);
	  delay_ms(100,0);
	}
}
void Turn135(u8 direction,u16 time)
{
	if(direction==0)  //��ת
	{
	  Direction(0,0); 
	  Speed(2950,3000);
	  delay_ms(time,0);
		delay_ms(time,0);
	  Speed(500,800);
	  delay_ms(100,0);
	}
	if(direction==1)   //��ת
	{
	  Direction(1,1);
	  Speed(2950,3000);
	  delay_ms(time,0);
		delay_ms(time,0);
	  Speed(500,500);
	  delay_ms(100,0);
	}
}

void Turn180(u8 direction,u16 time)
{
	if(direction==0)  //��ת
	{
	  Direction(0,0); 
	  Speed(2950,3000);
	  delay_ms(time,0);
		delay_ms(time,0);
	  Speed(500,800);
	  delay_ms(100,0);
	}
	if(direction==1)   //��ת
	{
	  Direction(1,1);
	  Speed(2950,3000);
	  delay_ms(time,0);
		delay_ms(time,0);
	  Speed(500,500);
	  delay_ms(100,0);
	}
}

void Turn_weizhuan(u8 direction)
{
	if(direction==1)  //��ת
	{
	  Direction(0,0); 
	  Speed(2950,3000);

	}
	if(direction==0)   //��ת
	{
	 Direction(1,1);
	 Speed(2950,3000);
	}
}

