/*******************************************
* 文件名： 
* 功能： 
* 说明： 
/********************************************/
#include <iom128v.h>
#include <macros.h>
#include "12864.h"

//颜色识别器色光滤波器选择：红色(S2,S3=0,0)，蓝色(S2,S3=0,1)，绿色(S2,S3=1,1)
#define S2 _PC7
#define S3 _PC6

//变量、常量定义
volatile uchar red=0,blue=0,green=0,flag=0,i=0,j=0,data[5]={0};
volatile uint counter=0;

//中断定义
#pragma interrupt_handler interrupt_int2:4 
#pragma interrupt_handler interrupt_timer1:15

/*******************************************
* 函数名称: int2_init()
* 函数功能: 外部中断2初始化
* 入口参数: 无
* 出口参数: 无
/********************************************/
void int2_init() 
{
   DDRD &= ~BIT(2);//中断引脚设置为输入
   PORTD |= BIT(2); //设置输出口上拉
   EICRA = 0X20; //下降沿触发
}

/*******************************************
* 函数名称: timer1_init()
* 函数功能: 定时器1初始化
* 入口参数: 无
* 出口参数: 无
/********************************************/
void timer1_init()
{
    TCCR1B = 0X02;// 设置分频数为8
	TCNT1H = 0x63;// 设置计数初值, 定时20ms
    TCNT1L = 0xC0;
}
/*******************************************
* 函数名称: port_init()
* 函数功能: 端口初始化
* 入口参数: 无
* 出口参数: 无
/********************************************/
void port_init()
{
   DDRA = 0XFF;//PORTA3~0为液晶数据线
   DDRC = 0XFF;//控制S2与S3  
}

/*******************************************
* 函数名称:  main()
/********************************************/
void main(void)
{   
   port_init();
   int2_init();
   timer1_init();
   Init_12864();  
   LcmClearTXT(); //文本区清RAM函数
   Display_x_y_data(0,0,"颜色识别：");
   Display_x_y_data(1,0,"红色成分：");
   Display_x_y_data(2,0,"蓝色成分：");
   Display_x_y_data(3,0,"绿色成分：");
   S2=0;//先检测红色(S2,S3=0,0)
   S3=0;
   SEI();
   EIMSK |= BIT(2); //打开外部中断
   TIMSK |=  BIT(2);//打开溢出中断
   while(1);  
}

 /*******************************************
* 函数名称:  interrupt_int2()  
* 函数功能: 
* 入口参数: 无
* 出口参数: 无
/********************************************/
void interrupt_int2()  
{  
	counter++;
}

/*******************************************
* 函数名称: interrupt_timer1()
* 函数功能: 
* 入口参数: 无
* 出口参数: 无
/********************************************/
void interrupt_timer1()
{
    CLI();//关总中断
    TCCR1B = 0X00;//定时器停止工作
	TIMSK &= ~ BIT(2);//关闭溢出中断
	EIMSK &= ~BIT(2); //关闭外部中断      	
	flag++;//实现先检测红色,再检测蓝色,然后检测绿色,循环检测
	if(flag==1)
	{   		 
		 red=counter;
		 data[0]=counter/100+0x30;		 
		 counter=counter%100;
		 data[1]=counter/10+0x30;
		 counter=counter%10;
		 data[2]=counter+0x30;		
   		 Locate_x_y(1,5);	
   		 for(i=0;i<3;i++)	    
	     		 Writedata(data[i]);    		
		S2=0;//下次检测蓝色(S2,S3=0,1)
		S3=1;		
	}
	else if(flag==2)
	{
   		 blue=counter;
		 data[0]=counter/100+0x30;		 
		 counter=counter%100;
		 data[1]=counter/10+0x30;
		 counter=counter%10;
		 data[2]=counter+0x30;		
   		 Locate_x_y(2,5);	
   		 for(i=0;i<3;i++)	    
	     		 Writedata(data[i]);    			
		S2=1;//下次检测绿色(S2,S3=1,1)
		S3=1;
	}
    else if(flag==3)
	{
   		 green=counter;
		 data[0]=counter/100+0x30;		 
		 counter=counter%100;
		 data[1]=counter/10+0x30;
		 counter=counter%10;
		 data[2]=counter+0x30;	
   		 Locate_x_y(3,5);	
   		 for(i=0;i<3;i++)	    
	     		 Writedata(data[i]);   				 
		S2=0;//下次检测红色(S2,S3=0,0)
		S3=0;
	}
	else if(flag==4) 
	{      
	     flag=0;		 
		 if((red+5)>(blue+green))		 
		     Display_x_y_data(0,5,"红色");
		 else if((blue+8>red)&&(blue+2>green))
		     Display_x_y_data(0,5,"蓝色");		
		 else if((green-3<red)&&(green-15>blue))
		     Display_x_y_data(0,5,"黄色");	  	
		 else if((green+5>red)&&(green>blue))
		     Display_x_y_data(0,5,"绿色");		   
		/*else if((blue>red)&&(green>blue))
		     Display_x_y_data(0,5,"白色");*/
		 else
		     Display_x_y_data(0,5,"未知");		 
	}
	//delay_ms(200); 
	counter = 0;//清零外中断计数标志		
	TCCR1B = 0X02;// 设置分频数为8
	TCNT1H = 0x63;//重新装入初值
    TCNT1L = 0xC0;
	TIMSK |=  BIT(2);//打开溢出中断
	EIMSK |= BIT(2); //打开外部中断		
	SEI();//开总中断
}