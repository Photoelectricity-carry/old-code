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

void UserTask(void *pvParameters)
{
   
	
    whitebalance();	//白平衡  
 
    while (1)
    {    
			
			
			
			R = tcs3200_RED();
			G = tcs3200_GREEN();
			B = tcs3200_BLUE();
//    servo_on(1);  // 0
//		delay_ms(500);
//    servo_on(90);  // 90
//		delay_ms(500);
//    servo_on(180);   //180
//  	delay_ms(1000);			

#if INCLUDE_uxTaskGetStackHighWaterMark
        UserTaskStack = uxTaskGetStackHighWaterMark(NULL);
#endif
    }
}
