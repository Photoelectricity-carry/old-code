/**************************************************************
* 文件名 ：128_64.h
* 功能：实现单片机与LCD12864之间的串口通讯
* 说明 ：引脚接线：CS接PA0脚 SID接PA1脚 SCLK接PA2脚,PSB脚接地
**************************************************************/
#ifndef _12864_H
#define _12864_H

#include<iom128v.h>
#include<macros.h>
#include<BIT.h>    

#define CS _PA0                       
#define SID _PA1                     
#define SCLK _PA2                   


#define uchar unsigned char
#define uint unsigned int


void delay_us(uint t);                //函数功能： 16M晶振，延时t微秒
void delay_ms(uint t);                //函数功能： 16M晶振，延时t毫秒
void Sendbyte(uchar byte);        //函数功能：发送1字节
uchar Receivebyte(void);            //函数功能：串口接收一个字节
                                              //仅在读取数据的时候用到
                                              //而读出的数据是一次只能读出4bit的
void Checkbusy( void );             //函数功能：检测忙
void Writecommand(uchar data);  //函数功能：写命令
void Writedata(uchar data);        //函数功能：发送数据 
void Locate_x_y(uchar x,uchar y);//函数功能：光标定位x行y列                                            
void Write_string(uchar *s);        //函数功能：写入中文串                                  
void Display_x_y_symbol(uchar x,uchar y,uint data);
                                             //函数功能：以字码的形式录
void Display_x_y_data(uchar x,uchar y,uchar *data);
                                             //函数功能：光标定位x行y列写入中文串
void LcmClearTXT();                 //文本区清RAM函数  
void Init_12864(void);              //函数功能： 液晶初始化



//自动换行编码表
unsigned char AC_TABLE[]={
0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,      //第一行汉字位置
0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,      //第二行汉字位置
0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,      //第三行汉字位置
0x98,0x99,0x9a,0x9b,0x9c,0x9d,0x9e,0x9f,      //第四行汉字位置
};



/**************************************************************
* 函数名称：delay_us()
* 函数功能：16M晶振，延时t微秒
* 入口参数：t    延时t微秒
* 出口参数：无
**************************************************************/
void delay_us(uint t)
{ 
  	uint i,j;
	 for(i=t;i>0;i--)
	 	for(j=2;j>0;j--);
} 


/**************************************************************
* 函数名称：delay_ms()
* 函数功能：16M晶振，延时t毫秒
* 入口参数：t   延时t毫秒
* 出口参数：无
**************************************************************/
void delay_ms(uint t)
{
 	 uint i,j;
	 for(i=t;i>0;i--)
	 	for(j=2800;j>0;j--);
}


/**************************************************************
* 函数名称：Sendbyte()
* 函数功能：发送1字节
* 入口参数：data   要写入的数据
* 出口参数：无
**************************************************************/
void Sendbyte(uchar data)
{ 
	uchar i=0;
	SCLK;
	delay_us(8);										//针对高频晶振
	for(i=0;i<8;i++)
		{
			if(data&0x80)
				SID=1;
			else 
				SID=0;
			SCLK=1;
			delay_us(8);								//针对高频晶振
			data<<=1;
			SCLK=0;
			delay_us(8);								//针对高频晶振
		}
}


/**************************************************************
* 函数名称：Receivebyte()
* 函数功能：串口接收一个字节,仅在读取数据的时候用到,一次只能读出4bit的数据
* 入口参数：无
* 出口参数：(0xf0&temp1)+(0x0f&temp2)
**************************************************************/
uchar Receivebyte(void)
{
     uchar i,temp1,temp2;
     temp1=temp2=0;
     for(i=0;i<8;i++)
     {
           temp1=temp1<<1;
           SCLK = 0;
           SCLK = 1;            
           SCLK = 0;
           if(SID) temp1++;
     }
     for(i=0;i<8;i++)
     {
           temp2=temp2<<1;
           SCLK = 0;
           SCLK = 1;
           SCLK = 0;
           if(SID) temp2++;
     }
     return ((0xf0&temp1)+(0x0f&temp2));
}

/**************************************************************
* 函数名称：Checkbusy()
* 函数功能：液晶检测忙
* 入口参数：无
* 出口参数：无
**************************************************************/
void Checkbusy( void )
{
     do   Sendbyte(0xfc);                           //11111,RW(1),RS(0),0
     while(0x80&Receivebyte());                  //BF(.7)=1 Busy
}

/**************************************************************
* 函数名称：Writecommand()
* 函数功能：发送的是控制指令(数据从LCD到MCU)
* 入口参数：data   要写入的命令
* 出口参数：无
**************************************************************/
void Writecommand(uchar data)
{ 
	CS=1;
	Checkbusy();
	Sendbyte(0xf8); 							     //表示发送的是控制命令
	Sendbyte(data&0xf0);
	Sendbyte((data&0x0f)<<4);
	CS=0;
}
/**************************************************************
* 函数名称：Writedata()
* 函数功能：向液晶写入数据 
* 入口参数：data   向液晶写入数据 
* 出口参数：无
**************************************************************/
void Writedata(uchar data)
{
	CS=1;
	Checkbusy();
	Sendbyte(0xfa);								    //表示发送的是数据
	Sendbyte(data&0xf0);  
	Sendbyte((data&0x0f)<<4);
	CS=0;
}

/**************************************************************
* 函数名称：Locate_x_y()
* 函数功能：光标定位x行y列
* 入口参数：X,Y   x行y列
* 出口参数：无
**************************************************************/
void Locate_x_y(uchar x,uchar y)
{
	uchar addr=0x80;
	Writecommand(0x80);
	switch(x)
	{
		case 0: addr = 0x80 + y; break;
		case 1:addr=0x90+y;break;
		case 2:addr=0x88+y;break;
		case 3:addr=0x98+y;break;
		default:break;
	}
	Writecommand(addr);
}
/**************************************************************
* 函数名称：Display_x_y_symbol()
* 函数功能：以字码的形式写入一个中文
* 入口参数：X,Y,data   X行地址，Y列地址，data是字码
* 出口参数：无
**************************************************************/
void Display_x_y_symbol(uchar x,uchar y,uint data)
{ 
	uchar i,j;
	Locate_x_y(x,y);
	j=(uchar)(data);
	i=(uchar)(data>>8);
	Writedata(i);
	Writedata(j);
}
/**************************************************************
* 函数名称：Write_string()
* 函数功能：写入串数据
* 入口参数：*s
* 出口参数：无
**************************************************************/
void Write_string(uchar *s)
{ 
	for(;*s!='\0';s++)
		{
			Writedata(*s);
		}
}
/**************************************************************
* 函数名称：Display_x_y_data()
* 函数功能：光标定位x行y列写入字符串,自动换行
* 入口参数：X,Y,data  
* 出口参数：无
**************************************************************/
void Display_x_y_data(uchar x,uchar y,uchar *data)
{
	Writecommand(AC_TABLE[8*x+y]);
	for(;*data!='\0';data++)
		{
			if(y==16)        						 //判断换行 换行后重写地址
				{            							//若不判断,则自动从第一行到第三行
					y=0;
					x++;
					if (x==4) x=0;
					Writecommand(AC_TABLE[8*x+y]);
				}
			Writedata(*data);
			y++;
		}
}

/**************************************************************
* 函数名称：LcmClearTXT()
* 函数功能：清文本区RAM数据
* 入口参数：无
* 出口参数：无
**************************************************************/
void LcmClearTXT()
{
     uchar i;
     Writecommand(0x30);                       //8BitMCU,基本指令集合
     Writecommand(0x80);                       //AC归起始位
     for(i=0;i<64;i++)
        Writedata(0x20);                           //地址归位
} 

/**************************************************************
* 函数名称：Init_12864()			
* 函数功能：初始化12864
* 入口参数：无
* 出口参数：无
**************************************************************/
void Init_12864(void)			
{
	delay_ms(50); 			                           //用延时代替读忙，以避免死机
     Writecommand(0x30);                           //8BitMCU,基本指令集合
     Writecommand(0x03);                           //AC归0,不改变DDRAM内容
     Writecommand(0x0C);                           //显示ON,游标OFF,游标位反白OFF
     Writecommand(0x01);                           //清屏,AC归0
     Writecommand(0x06);                           //写入时,游标右移动
}
#endif

