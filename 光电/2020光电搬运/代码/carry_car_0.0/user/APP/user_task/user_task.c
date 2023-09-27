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

#include "led.h"
#include "buzzer.h"

#include "Detect_Task.h"
#include "INS_Task.h"
#include "CAN_Receive.h"

#define user_is_error() toe_is_error(errorListLength)

#if INCLUDE_uxTaskGetStackHighWaterMark
uint32_t UserTaskStack;
#endif

//姿态角 单位度
fp32 angle_degree[3] = {0.0f, 0.0f, 0.0f};
cap_measure_t get_vot;
void UserTask(void *pvParameters)
{
    const volatile fp32 *angle;
    //获取姿态角指针
    angle = get_INS_angle_point();
 
    while (1)
    {    
			
			
			uint16_t  tempower = 8000;
			uint8_t  sendbuf1[8];
			sendbuf1[0]=tempower>>8;//1f  前面
			sendbuf1[1]=tempower;//40   后面
		 //8000  16 	00001f40
			CAN_CMD_cap(sendbuf1[1],sendbuf1[0]);
			
			uint16_t  vot = get_vot.capvot; 
      if(vot < 13)
		  {
			 uint16_t  tempower = 13000;
			 uint8_t  sendbuf1[8];
			 sendbuf1[0]=tempower>>8;//1f  前面
			 sendbuf1[1]=tempower;//40   后面
		  //8000  16 	00001f40
			 CAN_CMD_cap(sendbuf1[1],sendbuf1[0]);			
		  	//buzzer_init(30000, 90);
			}
			
        //系统延时
        vTaskDelay(100);
#if INCLUDE_uxTaskGetStackHighWaterMark
        UserTaskStack = uxTaskGetStackHighWaterMark(NULL);
#endif
    }
}
