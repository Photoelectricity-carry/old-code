#include "Gimbal_Task.h"

#include "main.h"

#include "led.h"
#include "INS_Task.h"
#include "pid.h"
#include "delay.h"
#include "arm_math.h"
#include "CAN_Receive.h"
#include "INS_Task.h"
#include "user_lib.h"
#include "shoot.h"

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"

//电机编码值规整 0—8191
#define ECD_Format(ecd)         \
    {                           \
        if ((ecd) > ecd_range)  \
            (ecd) -= ecd_range; \
        else if ((ecd) < 0)     \
            (ecd) += ecd_range; \
    }
		

#if INCLUDE_uxTaskGetStackHighWaterMark
uint32_t gimbal_high_water;
#endif

//底盘初始化，主要是pid初始化
static void chassis_init(chassis_move_t *chassis_move_init);
//更新数据
static void chassis_feedback_update(chassis_move_t *chassis_move_update);

static void chassis_move_angle(void);
//PID计算
static void chassis_control_loop(chassis_move_t *chassis_move_control_loop);
		


//底盘运动数据
chassis_move_t chassis_move;

// 主任务
void GIMBAL_task(void *pvParameters)
{
	  //等待陀螺仪任务更新陀螺仪数据
    vTaskDelay(GIMBAL_TASK_INIT_TIME);
	  chassis_init(&chassis_move);
	
	  while (1)
    {
			
    led_green_on();		
		//底盘数据更新
    chassis_feedback_update(&chassis_move);				
		//底盘速度	

			 
   chassis_control_loop(&chassis_move);

   CAN_CMD_CHASSIS(chassis_move.motor_chassis[0].give_current,chassis_move.motor_chassis[1].give_current,
                              chassis_move.motor_chassis[2].give_current, chassis_move.motor_chassis[3].give_current);		
			
		vTaskDelay(GIMBAL_CONTROL_TIME);

#if INCLUDE_uxTaskGetStackHighWaterMark
        gimbal_high_water = uxTaskGetStackHighWaterMark(NULL);
#endif		
		}
}
static void chassis_init(chassis_move_t *chassis_move_init)
{
	  if (chassis_move_init == NULL)
    {
        return;
    }	
	  //底盘速度环pid值
    const static fp32 motor_speed_pid[3] = {M2006_MOTOR_SPEED_PID_KP, M2006_MOTOR_SPEED_PID_KI, M2006_MOTOR_SPEED_PID_KD};
		uint8_t i;			
	  //初始化PID 运动
    for (i = 0; i < 4; i++)
    {
        chassis_move_init->motor_chassis[i].chassis_motor_measure = get_Chassis_Motor_Measure_Point(i);
        PID_Init(&chassis_move_init->motor_speed_pid[i], PID_POSITION, motor_speed_pid, M2006_MOTOR_SPEED_MAX_OUT, M2006_MOTOR_SPEED_MAX_IOUT);
    }
		chassis_feedback_update(chassis_move_init);
		
		uint8_t d = 0;
		for (d = 0; d < 4; d++)
		{
    chassis_move.ecd_count[d] = 0;
    chassis_move.angle[d] = chassis_move_init->motor_chassis[d].chassis_motor_measure->ecd * Motor_ECD_TO_ANGLE;
    chassis_move.given_current[d] = 0;
    chassis_move.move_flag = 0;
    chassis_move.set_angle[d] = chassis_move.angle[d];
    chassis_move.speed[d] = 0.0f;
    chassis_move.speed_set[d] = 0.0f;
		}			
}

static void chassis_feedback_update(chassis_move_t *chassis_move_update)
{
	  uint8_t i = 0;
		for (i = 0; i < 4; i++)
		{
				
     //更新电机速度，加速度是速度的PID微分
     chassis_move_update->motor_chassis[i].speed = chassis_move_update->motor_chassis[i].chassis_motor_measure->speed_rpm * Motor_RMP_TO_SPEED;
		
		
    //电机圈数重置， 因为输出轴旋转一圈， 电机轴旋转 36圈，将电机轴数据处理成输出轴数据，用于控制输出轴角度
    if (chassis_move_update->motor_chassis[i].chassis_motor_measure->ecd - chassis_move_update->motor_chassis[i].chassis_motor_measure->last_ecd > Half_ecd_range)
    {
        chassis_move.ecd_count[i]--;
    }
    else if (chassis_move_update->motor_chassis[i].chassis_motor_measure->ecd - chassis_move_update->motor_chassis[i].chassis_motor_measure->last_ecd < -Half_ecd_range)
    {
        chassis_move.ecd_count[i]++;
    }			

    if (chassis_move.ecd_count[i] == FULL_COUNT)
    {
        chassis_move.ecd_count[i] = -(FULL_COUNT - 1);
    }
    else if (chassis_move.ecd_count[i] == -FULL_COUNT)
    {
        chassis_move.ecd_count[i] = FULL_COUNT - 1;
    }

    //计算输出轴角度
    chassis_move.angle[i] = (chassis_move.ecd_count[i] * ecd_range + chassis_move_update->motor_chassis[i].chassis_motor_measure->ecd) * Motor_ECD_TO_ANGLE;		
		}	
		
}

static void chassis_control_loop(chassis_move_t *chassis_move_control_loop)
{
	  uint8_t i = 0;
	
	  for (i = 0; i < 4; i++)
    {
			 chassis_move_control_loop->motor_speed_pid[i].max_out = TRIGGER_BULLET_PID_MAX_OUT;
			 chassis_move_control_loop->motor_speed_pid[i].max_iout = TRIGGER_BULLET_PID_MAX_IOUT;
		}
    //计算pid
    chassis_move_angle();
		
    for (i = 0; i < 4; i++)
    {   
			  chassis_move_control_loop->motor_chassis[i].speed_set = chassis_move.speed_set[i];
        PID_Calc(&chassis_move_control_loop->motor_speed_pid[i], chassis_move_control_loop->motor_chassis[i].speed, chassis_move_control_loop->motor_chassis[i].speed_set);
    }		
     //赋值电流值
    for (i = 0; i < 4; i++)
    {
        chassis_move_control_loop->motor_chassis[i].give_current = (int16_t)(chassis_move_control_loop->motor_speed_pid[i].out);
    }
 
}


static void chassis_move_angle(void)
{
//	  uint8_t i = 0;
	
//	  //直行	
//	  for (i = 0; i < 4; i++)
//    {
//     chassis_move.speed_set[i] = T2006_SPEED;
//		}
	 chassis_move.set_angle[0] = rad_format(PI_All);
	
		if(rad_format(chassis_move.set_angle[0] - chassis_move.angle[0]) > 0.05f )
		{
		  chassis_move.speed_set[0] = T2006_SPEED;
		}
		else
		{
		 chassis_move.speed_set[0] = 0;
		}
		
}
