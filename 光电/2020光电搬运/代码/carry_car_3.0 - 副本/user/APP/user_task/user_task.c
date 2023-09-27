/**
  ****************************(C) COPYRIGHT 2016 DJI****************************
  * @file       user_task.c/h
  * @brief      һ����ͨ������������豸�޴����̵�1Hz��˸,Ȼ���ȡ��̬��
  * @note       
  * @history
  *  Version    Date            Author          Modification
  *  V1.0.0     Dec-26-2018     RM              1. ���
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
#include "fric.h"

#include "Detect_Task.h"
#include "INS_Task.h"

#define user_is_error() toe_is_error(errorListLength)

#if INCLUDE_uxTaskGetStackHighWaterMark
uint32_t UserTaskStack;
#endif

//��̬�� ��λ��
fp32 angle_degree[3] = {0.0f, 0.0f, 0.0f};
uint16_t R,G,B;

int clour_disguish(void);		//��ɫʶ��

u16 col;


void UserTask(void *pvParameters)
{
   
	
    whitebalance();	//��ƽ��  
 
    while (1)
    {    
//	    servo_on(60);
//      servo_on_1(140);
//			servo_on_2(120);

//     delay_ms(1000);
//		  servo_on(50);
//			     delay_ms(1000);

//	    servo_on(90);
//			     delay_ms(1000);

//	    servo_on(130);
//			     delay_ms(1000);

//	    servo_on(150);

//     delay_ms(1000);
//	    servo_on(140);
//     delay_ms(1000);

//				    servo_on(140);
//     delay_ms(1000);
//		 	    servo_on(140);
//     delay_ms(1000);
//		 
//		 	    servo_on(140);
//     delay_ms(1000);
//  servo_on(1);

//   servo_on_1(1);
//   delay_ms(1000);	

			



	//	delay_ms(500);
	 // col = clour_disguish();

#if INCLUDE_uxTaskGetStackHighWaterMark
        UserTaskStack = uxTaskGetStackHighWaterMark(NULL);
#endif
    }
}




int clour_disguish(void)		//��ɫʶ��
{
	R = tcs3200_RED();
	G = tcs3200_GREEN();
	B = tcs3200_BLUE();
	if(((R <= 255) &&(R > 200)) && ((G <=255) &&(G > 200)) &&((B <= 255) && (B > 200))) 			//ʶ��Ϊ��ɫ	((R < 255) &&(R > 200)) && ((G < 255) &&(G > 200)) &&((B < 255) && (B > 200))
	{			
		return 0; //��
	}
	 else if((R < 60) && (G < 60) && (B < 60))				
	{						  
		return 1; //��
	}			
	else if((R>G)&&(R>B)&&(R>140)) 				
	{			
		return 2; //��
	}
	else if((B>R)&&(B>G)&&(B>70)) 
		{								
		return 3; //��
	 }
	else if((G>R)&&(G>B)&&(G>80))
	{		
		return 4; //��
	}
	else
	{
	
			return 1; //��

	}

	
}


