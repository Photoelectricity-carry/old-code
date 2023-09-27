//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其他用途
//单片机交流群：439190573
//淘宝店：https://futureworldrobot.taobao.com
//修改日期：2020/6/5
//版本：V1
//版权所有，盗版必究。
//未来世界机器人系列
//////////////////////////////////////////////////////////////////////////////////
#include "Digital.h"
	   	
/*********************************************************************
 *  函数名称：void Key_Init
 *  函数功能：端口初始化
 *  形    参：无
 *  输    出：无
 *  备    注：		需要修改
 *			   	   
 ********************************************************************/    
void Digital_Init(void)	       
{	
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);		//使能端口时钟


	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 				//设置成上拉输入
 	GPIO_Init(GPIOD, &GPIO_InitStructure);
}



