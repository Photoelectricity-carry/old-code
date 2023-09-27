# include "gray.h"

void Gray_init(void)     
{
  GPIO_InitTypeDef  GPIO_InitStructure;   // PA0
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI,ENABLE);
	
	//GPIOA0	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ; // 灰度对应引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	//GPIOA1	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ; // 灰度对应引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	//GPIOA2
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 ; // 灰度对应引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	//GPIOA3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 ; // 灰度对应引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	//GPIOI5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; // 灰度对应引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOI, &GPIO_InitStructure);
	//GPIOI6
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 ; // 灰度对应引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOI, &GPIO_InitStructure);
	//GPIOI7	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 ; // 灰度对应引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOI, &GPIO_InitStructure);
	//GPIO2	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 ; // 灰度对应引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOI, &GPIO_InitStructure);
	//PH12
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 ; // 灰度对应引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOH, &GPIO_InitStructure);
	
	//PI0
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ; // 灰度对应引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOI, &GPIO_InitStructure);	
	
		//PH11
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 ; // 灰度对应引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOH, &GPIO_InitStructure);
		//PH10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 ; // 灰度对应引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOH, &GPIO_InitStructure);
	//PD14
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 ; // 灰度对应引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  //PD15
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 ; // 灰度对应引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOD, &GPIO_InitStructure);
//	
//	
////	  //PD12
////	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 ; // 灰度对应引脚
////  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
////  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
////  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
////  GPIO_Init(GPIOD, &GPIO_InitStructure);
//////	

//	  //PD12
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 ; // 灰度对应引脚
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
//  GPIO_Init(GPIOE, &GPIO_InitStructure);
//	
//		  //PD13
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 ; // 灰度对应引脚
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
//  GPIO_Init(GPIOD, &GPIO_InitStructure);
	
}


