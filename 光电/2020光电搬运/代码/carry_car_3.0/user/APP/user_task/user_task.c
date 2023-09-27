/**
  ****************************(C) COPYRIGHT 2016 DJI****************************
  * @file       user_task.c/h
  * @brief      一个普通心跳程序，如果设备无错误，绿灯1Hz闪烁,然后获取姿态角
  * @note       
  * @history
  *  Version    Date            Author          Modification
  *  V1.0.0     Dec-26-2018     RM              1. 完成
  *
  @verbatim
  ==============================================================================

  ==============================================================================
  @endverbatim
  ****************************(C) COPYRIGHT 2016 DJI****************************
  */

#include "User_Task.h"
#include "main.h"

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "servo.h"
#include "delay.h"
#include "tcs3200.h"
#include "exit_init.h"

#include "led.h"

#include "Detect_Task.h"
#include "INS_Task.h"

#define user_is_error() toe_is_error(errorListLength)

#if INCLUDE_uxTaskGetStackHighWaterMark
uint32_t UserTaskStack;
#endif

//姿态角 单位度
fp32 angle_degree[3] = {0.0f, 0.0f, 0.0f};
uint16_t R,G,B;

int clour_disguish(void);		//颜色识别

u16 col;


void UserTask(void *pvParameters)
{
   
	
    whitebalance();	//白平衡  
 
    while (1)
    {    
			
			
	  col = clour_disguish();

#if INCLUDE_uxTaskGetStackHighWaterMark
        UserTaskStack = uxTaskGetStackHighWaterMark(NULL);
#endif
    }
}




int clour_disguish(void)		//颜色识别
{
	R = tcs3200_RED();
	G = tcs3200_GREEN();
	B = tcs3200_BLUE();
	if(((R <= 255) &&(R > 200)) && ((G <=255) &&(G > 200)) &&((B <= 255) && (B > 200))) 			//识别为白色	((R < 255) &&(R > 200)) && ((G < 255) &&(G > 200)) &&((B < 255) && (B > 200))
	{			
		return 0; //白
	}
	 else if((R < 65) && (G < 65) && (B < 65))				
	{						  
		return 1; //黑
	}			
	else if((R>G)&&(R>B)&&(R>150)) 				
	{			
		return 2; //红
	}
	else if((B>R)&&(B>G)) 
		{								
		return 3; //蓝
	 }
	else if((G>R)&&(G>B)&&(G>60))
	{		
		return 4; //绿
	}
	else
	{
	return 9;
	}
	
}


