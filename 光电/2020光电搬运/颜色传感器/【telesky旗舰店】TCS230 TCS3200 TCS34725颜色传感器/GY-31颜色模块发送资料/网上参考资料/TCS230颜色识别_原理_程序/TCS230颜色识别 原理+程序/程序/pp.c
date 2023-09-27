#include<iom128v.h>
#include<macros.h>
#include<BIT.h>
#include"LCD12864.c"
#define uint unsigned int
#define uchar unsigned char
#pragma interrupt_handler timer0:iv_TIMER0_OVF
#pragma interrupt_handler int0:iv_INT0
#define PSB _PA3
#define REST _PA4
#define LED_B _PG1
#define S2 _PE0
#define S3 _PE1
#define buzzer _PG0
uchar table0[]="颜色识别";
uchar table1[]="红色: ";
uchar table2[]="绿色: ";
uchar table3[]="蓝色: ";
uint  red,gree,blue,time_count,int_count;
uchar red_value,gree_value;
void delay(uint tt)
{
    uchar j;
	for(;tt>0;tt--)
	    for(j=100;j>0;j--);
}
void timer_Init()
{
    TCCR0=0x07;
    TCNT0=0x64;
  //  TIMSK|=BIT(0);
}
void interrupt0_Init()
{
   // EIMSK|=BIT(0);
    EICRA=0x02;
    DDR_PD0=0;
  //  _PD0=1;
}
void PORT_INIT()
{
    DDR_PA0=1;
	DDR_PA1=1;
	DDR_PA2=1;
	DDR_PA3=1;
	DDR_PA4=1;
	
	DDRC=0xff;
	
	DDR_PE0=1;
	DDR_PE1=1;
	
	DDR_PG0=1;
	DDR_PG1=1;
	
	PSB=0;
	REST=1;
	LED_B=1;
}
void color_Recognition()
{
    S2=1;
	S3=1;
	EIMSK|=BIT(0);
	TIMSK|=BIT(0);
}
void main()
{
	PORT_INIT();
    timer_Init();
	interrupt0_Init();
	LCD_12864_Init();
	SREG|=BIT(7);
 //	PutStr(0,2,table0);
	PutStr(1,1,table1);
	PutStr(2,1,table2);
	PutStr(3,1,table3);
	delay(5000);
	buzzer=1;
	delay(200);
	buzzer=0;
	color_Recognition();
	while(1);
}
void timer0()
{ 
    uchar ge,shi,bai,qian;
	float temp;
    TIMSK&=~BIT(0);
	time_count++;
	TCNT0=0x64;
	if(time_count==1)
	   {
          bai=int_count/100;
	      shi=int_count%100/10;
	      ge=int_count%10;
	      Write_command_12864(0x95);
	      Write_data_12864(0x30+bai);
	      Write_data_12864(0x30+shi);
	      Write_data_12864(0x30+ge);
	      red=int_count;
		  S2=1;
		  S3=1;
	   }
	 if(time_count==2)
	   {
	      bai=int_count/100;
	      shi=int_count%100/10;
	      ge=int_count%10; 
		  Write_command_12864(0x8d);
	      Write_data_12864(0x30+bai);
	      Write_data_12864(0x30+shi);
	      Write_data_12864(0x30+ge); 
		  gree=int_count;
		  S2=0;
		  S3=1;   
	   }
	 if(time_count==3)
	   {
	      bai=int_count/100;
	      shi=int_count%100/10;
	      ge=int_count%10; 	
		  Write_command_12864(0x9d);
	      Write_data_12864(0x30+bai);
	      Write_data_12864(0x30+shi);
	      Write_data_12864(0x30+ge); 
		  blue=int_count;
		  S2=0;
		  S3=0;       
	   }
	 if(time_count==40)
	   {
	      time_count=0;	
		  temp=(float)red/blue;
		  red_value=temp*1000;
		  temp=(float)gree/blue;
		  gree_value=temp*1000;
		  
		  qian=red_value/1000;
		  bai=red_value%1000/100;
		  shi=red_value%100/10;
		  ge=red_value%10;
		  Write_command_12864(0x81);  
		  Write_data_12864(0x30+qian);
		  Write_data_12864(0x30+bai);
		  Write_data_12864(0x30+shi);
		  Write_data_12864(0x30+ge);
		  
		  qian=gree_value/1000;
		  bai=gree_value%1000/100;
		  shi=gree_value%100/10;
		  ge=gree_value%10;
		  Write_command_12864(0x85);  
		  Write_data_12864(0x30+qian);
		  Write_data_12864(0x30+bai);
		  Write_data_12864(0x30+shi);
		  Write_data_12864(0x30+ge);
	   }
	 int_count=0; 
	 TIMSK|=BIT(0); 
}
void int0()
{
     int_count++;
}