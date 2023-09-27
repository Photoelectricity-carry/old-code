#include "jiguang.h"
#include "sys.h"
#include "motor.h"
#include "delay.h"
///////////////////////////////////////////激光传感器
 #define Llflash  GPIO_Pin_9
 #define L2flash  GPIO_Pin_10
 #define Rlflash  GPIO_Pin_11
 #define R2flash  GPIO_Pin_12

//int  L1Return = 0;
//int  L2Return = 0;
//int  R1Return = 0;
//int  R2Return= 0;


//void L1Count(int n, int speed1, int speed2,int x)//前进or后退 左灯1数线
//{ 
// int count = 0;

//  L1Return = 0;
//  int flag;
//  while (count < n)
//  {
//   
//    flag = 0;
//    if(count==n)
//		  {
//			   flag = 1;
//		   }
//    while (flag == 0)
//    {
//		if(x==1)
//		{
//			yanxianzou(speed1, speed2);
//            L1Return = GPIO_ReadInputDataBit(GPIOC,Llflash);
//		}
//		if(x==0)
//		{
//			yanxiantui(speed1, speed2);
//            L1Return = GPIO_ReadInputDataBit(GPIOC,Llflash);
//		}
//      while (L1Return)
//      { //在黑色区域
//		   count++;
//         delay_ms(20);
//		  
//      }
//      }
//    }
//   stop(200);
//  }

//  
//  
//void L2Count(int n, int speed1, int speed2,int x)//前进or后退 左灯2数线
//{ 
//  int count = 0;
// 
//  L2Return = 0;
//  int flag;
//  while (count < n)
//  {
//   
//    flag = 0;
//    if(count==n)
//		  {
//			   flag = 1;
//		   }
//    while (flag == 0)
//    {
//		if(x==1)
//		{
//			yanxianzou(speed1, speed2);
//            L2Return = GPIO_ReadInputDataBit(GPIOC,L2flash);
//		}
//		if(x==0)
//		{
//			yanxiantui(speed1, speed2);
//            L2Return = GPIO_ReadInputDataBit(GPIOC,L2flash);
//		}
//      while (L2Return)
//      { //在黑色区域
//		   count++;
//         delay_ms(20);
//		  
//      }
//      }
//    }
//   stop(200);
//  }
//void R1Count(int n, int speed1, int speed2,int x)//前进or后退 右灯1数线
//{ 
//  int count = 0;
// 
//  R1Return = 0;
//  int flag;
//  while (count < n)
//  {
//   
//    flag = 0;
//    if(count==n)
//		  {
//			   flag = 1;
//		   }
//    while (flag == 0)
//    {
//		if(x==1)
//		{
//			yanxianzou(speed1, speed2);
//            R1Return = GPIO_ReadInputDataBit(GPIOC,Rlflash);
//		}
//		if(x==0)
//		{
//			yanxiantui(speed1, speed2);
//            R1Return = GPIO_ReadInputDataBit(GPIOC,Rlflash);
//		}
//      while (R1Return)
//      { //在黑色区域
//		   count++;
//         delay_ms(20);
//		  
//      }
//      }
//    }
//   stop(200);
//  }



// void R2Count(int n, int speed1, int speed2,int x)//前进or后退 右灯2数线
//{ 
//  int count = 0;
// 
//  R2Return = 0;
//  int flag;
//  while (count < n)
//  {
//   
//    flag = 0;
//    if(count==n)
//		  {
//			   flag = 1;
//		   }
//    while (flag == 0)
//    {
//		if(x==1)
//		{
//			yanxianzou(speed1, speed2);
//            R2Return = GPIO_ReadInputDataBit(GPIOC,R2flash);
//		}
//		if(x==0)
//		{
//			yanxiantui(speed1, speed2);
//            R2Return = GPIO_ReadInputDataBit(GPIOC,R2flash);
//		}
//      while (R2Return)
//      { //在黑色区域
//		   count++;
//         delay_ms(20);
//		  
//      }
//      }
//    }
//   stop(200);
//  }



//  
//  void R1CountRL(int n, int speed1, int speed2,int y,int angel)//左转or右转 右灯1数线 1右转，0左转
//{ 
//  int count = 0;
// 
//  R1Return = 0;
//  int flag;
//  while (count < n)
//  {
//   
//    flag = 0;
//	   if(count==n)
//		  {
//			   flag = 1;
//		   }
//    while (flag == 0)
//    {
//		if(y==1)
//		{
//			turn_right(speed1, speed2,angel);
//            R1Return = GPIO_ReadInputDataBit(GPIOC,Rlflash);
//		}
//		if(y==0)
//		{
//			turn_left(speed1, speed2,angel);
//            R1Return = GPIO_ReadInputDataBit(GPIOC,Rlflash);
//		}
//      while (R1Return)
//      { //在黑色区域
//       count++;
//      delay_ms(20);
//      }
//    
//        count++;
//      }
//    }
//   stop(200);
//  }

//  
//  void L1CountRL(int n, int speed1, int speed2,int y,int angel)//左转or右转 左灯1数线 1右转，0左转
//{ 
//  int count = 0;
// 
//  L1Return = 0;
//  int flag;
//  while (count < n)
//  {
//   
//    flag = 0;
//	   if(count==n)
//		  {
//			   flag = 1;
//		   }
//    while (flag == 0)
//    {
//		if(y==1)
//		{
//			turn_right(speed1, speed2,angel);
//            L1Return = GPIO_ReadInputDataBit(GPIOC,Llflash);
//		}
//		if(y==0)
//		{
//			turn_left(speed1, speed2,angel);
//            L1Return = GPIO_ReadInputDataBit(GPIOC,Llflash);
//		}
//      while (L1Return)
//      { //在黑色区域
//       count++;
//      delay_ms(20);
//      }
//    
//        count++;
//      }
//    }
//   stop(200);
//  }
