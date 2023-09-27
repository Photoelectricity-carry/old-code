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
#include "servo.h"
#include "gray.h"

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

void chassic_go_one (int d,int g);

//定向移动 右转90
static void chassis_move_right_90(void);
//定向移动 右转45
static void chassis_move_right_45(void);
//定向移动 右转135
static void chassis_move_right_135(void);
		
//定向移动 左转90
static void chassis_move_left_90(void);
//定向移动 左转45
static void chassis_move_left_45(void);
//定向移动 左转135		
static void chassis_move_left_135(void);

//前进巡线模式
static void chassis_staight_gray(void);
//后退巡线模式	
static void chassis_back_gray(void);

		
//PID计算
static void chassis_control_loop_1(chassis_move_t *chassis_move_control_loop);
//读取灰度
void chassis_gary_loop();


//底盘运动数据
chassis_move_t chassis_move;

int16_t count;
int16_t c=0;
int16_t falg1 = 0,falg2 = 0,falg3 = 0,falg4 = 0;
int16_t key[8];
int16_t w = 1;


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
  	 //灰度返回函数
    chassis_gary_loop();
    //底盘控制函数
			
			
 	 // chassis_control_loop_1(&chassis_move);
  
	
			
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

static void chassis_control_loop_1(chassis_move_t *chassis_move_control_loop)
{
	  uint8_t i = 0;
	
	  for (i = 0; i < 4; i++)
    {
			 chassis_move_control_loop->motor_speed_pid[i].max_out = TRIGGER_BULLET_PID_MAX_OUT;
			 chassis_move_control_loop->motor_speed_pid[i].max_iout = TRIGGER_BULLET_PID_MAX_IOUT;
		}
    //计算pid

		chassis_staight_gray();

		//chassis_move_left_135();
		
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
		
		   CAN_CMD_CHASSIS(chassis_move.motor_chassis[0].give_current,chassis_move.motor_chassis[1].give_current,
                              chassis_move.motor_chassis[2].give_current, chassis_move.motor_chassis[3].give_current);	
 
}








// 前进巡线模式
static void chassis_staight_gray(void)
{
	
		  chassis_move.speed_set[0] = 12.0f;
			chassis_move.speed_set[1] = 12.0f;	
			chassis_move.speed_set[2] = -12.0f;
			chassis_move.speed_set[3] = -12.0f;
	 
			if(key[0] == 1 && key[1] == 0)
			{		
			   chassis_move.speed_set[0] = 8.0f;
				 chassis_move.speed_set[1] = 8.0f;	
				 chassis_move.speed_set[2] = -12.0f;
				 chassis_move.speed_set[3] = -12.0f;		
			}
			if(key[1] == 1 && key[0] == 0)
			{			
			   chassis_move.speed_set[0] = 12.0f;
				 chassis_move.speed_set[1] = 12.0f;	
				 chassis_move.speed_set[2] = -8.0f;
  			 chassis_move.speed_set[3] = -8.0f;
			}
	
			if(  key[4] == 1 && key[3] == 1)				
			{
				 chassis_move.speed_set[0] = 0.0f;
				 chassis_move.speed_set[1] = 0.0f;	
				 chassis_move.speed_set[2] = 0.0f;
  			 chassis_move.speed_set[3] = 0.0f;	
			
			}
	  
}


// 倒退巡线模式
static void chassis_back_gray(void)
{
	
		  chassis_move.speed_set[0] = -12.0f;
			chassis_move.speed_set[1] = -12.0f;	
			chassis_move.speed_set[2] = 12.0f;
			chassis_move.speed_set[3] = 12.0f;
	 
			if(key[1] == 1 && key[0] == 0)
			{		
			   chassis_move.speed_set[0] = -12.0f;
				 chassis_move.speed_set[1] = -12.0f;	
				 chassis_move.speed_set[2] = 8.0f;
				 chassis_move.speed_set[3] = 8.0f;	
			}
			if(key[0] == 1 && key[1] == 0)
			{			
			   chassis_move.speed_set[0] = -8.0f;
				 chassis_move.speed_set[1] = -8.0f;	
				 chassis_move.speed_set[2] = 12.0f;
				 chassis_move.speed_set[3] = 12.0f;
			}
	
			if(  key[2] == 1 && key[5] == 1)				
			{
				 chassis_move.speed_set[0] = 0.0f;
				 chassis_move.speed_set[1] = 0.0f;	
				 chassis_move.speed_set[2] = 0.0f;
  			 chassis_move.speed_set[3] = 0.0f;	
			
			}
	  
}

// 右转90
static void chassis_move_right_90(void)
{
	  chassis_move.set_angle[0] = rad_format(PI_RIGHT);
		if(rad_format(chassis_move.set_angle[0] - chassis_move.angle[0]) > 0.05f)
		{
				 chassis_move.speed_set[0] = 12.0f;
				 chassis_move.speed_set[1] = 12.0f;	
				 chassis_move.speed_set[2] = 12.0f;
				 chassis_move.speed_set[3] = 12.0f;			
		}
		else
		{
		 chassis_move.speed_set[0] = 0;
		 chassis_move.speed_set[1] = 0;	
		 chassis_move.speed_set[2] = 0;
		 chassis_move.speed_set[3] = 0;	
		}
}

// 右转45
static void chassis_move_right_45(void)
{
	  chassis_move.set_angle[0] = rad_format(PI_RIGHT_45);
		if(rad_format(chassis_move.set_angle[0] - chassis_move.angle[0]) > 0.05f)
		{
				 chassis_move.speed_set[0] = 12.0f;
				 chassis_move.speed_set[1] = 12.0f;	
				 chassis_move.speed_set[2] = 12.0f;
				 chassis_move.speed_set[3] = 12.0f;			
		}
		else
		{
		 chassis_move.speed_set[0] = 0;
		 chassis_move.speed_set[1] = 0;	
		 chassis_move.speed_set[2] = 0;
		 chassis_move.speed_set[3] = 0;	
		}
}

// 右转45
static void chassis_move_right_135(void)
{
	  chassis_move.set_angle[0] = rad_format(PI_RIGHT_135);
		if(rad_format(chassis_move.set_angle[0] - chassis_move.angle[0]) > 0.05f)
		{
				 chassis_move.speed_set[0] = 12.0f;
				 chassis_move.speed_set[1] = 12.0f;	
				 chassis_move.speed_set[2] = 12.0f;
				 chassis_move.speed_set[3] = 12.0f;			
		}
		else
		{
		 chassis_move.speed_set[0] = 0;
		 chassis_move.speed_set[1] = 0;	
		 chassis_move.speed_set[2] = 0;
		 chassis_move.speed_set[3] = 0;	
		}
}



// 左转90
static void chassis_move_left_90(void)
{
	  chassis_move.set_angle[1] = rad_format(PI_LEFT);
		if(rad_format(chassis_move.set_angle[1] - chassis_move.angle[1]) < 0.05f)
		{
				 chassis_move.speed_set[0] = -12.0f;
				 chassis_move.speed_set[1] = -12.0f;	
				 chassis_move.speed_set[2] = -12.0f;
				 chassis_move.speed_set[3] = -12.0f;
		}
		else
		{
		 chassis_move.speed_set[0] = 0;
		 chassis_move.speed_set[1] = 0;	
		 chassis_move.speed_set[2] = 0;
		 chassis_move.speed_set[3] = 0;	
		}
}
// 左转45
static void chassis_move_left_45(void)
{
	  chassis_move.set_angle[1] = rad_format(PI_LEFT_45);
		if(rad_format(chassis_move.set_angle[1] - chassis_move.angle[1]) < 0.05f)
		{
				 chassis_move.speed_set[0] = -12.0f;
				 chassis_move.speed_set[1] = -12.0f;	
				 chassis_move.speed_set[2] = -12.0f;
				 chassis_move.speed_set[3] = -12.0f;
		}
		else
		{
		 chassis_move.speed_set[0] = 0;
		 chassis_move.speed_set[1] = 0;	
		 chassis_move.speed_set[2] = 0;
		 chassis_move.speed_set[3] = 0;	
		}
}
// 左转135
static void chassis_move_left_135(void)
{
	  chassis_move.set_angle[1] = rad_format(PI_LEFT_135);
		if(rad_format(chassis_move.set_angle[1] - chassis_move.angle[1]) < 0.05f)
		{
				 chassis_move.speed_set[0] = -12.0f;
				 chassis_move.speed_set[1] = -12.0f;	
				 chassis_move.speed_set[2] = -12.0f;
				 chassis_move.speed_set[3] = -12.0f;
		}
		else
		{
		 chassis_move.speed_set[0] = 0;
		 chassis_move.speed_set[1] = 0;	
		 chassis_move.speed_set[2] = 0;
		 chassis_move.speed_set[3] = 0;	
		}
}








//灰度检测
void chassis_gary_loop()
{
    key[0]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0);   //PA0
    key[1]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1);   //PA1
    key[2]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2);   //PA2
    key[3]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3);   //PA3
    key[4]=GPIO_ReadInputDataBit(GPIOI,GPIO_Pin_5);   //PI5
    key[5]=GPIO_ReadInputDataBit(GPIOI,GPIO_Pin_6);   //PI6
    key[6]=GPIO_ReadInputDataBit(GPIOI,GPIO_Pin_7);   //PI7
    key[7]=GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_12);   //PD12
}
