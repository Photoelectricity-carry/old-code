/**
  ****************************(C) COPYRIGHT 2016 DJI****************************
  * @file       main.c/h
  * @brief      stm32初始化以及开始任务freeRTOS。h文件定义相关全局宏定义以及
  *             typedef 一些常用数据类型
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
#include "main.h"

#include "stm32f4xx.h"

#include "adc.h"
#include "buzzer.h"
#include "can.h"
#include "delay.h"
#include "flash.h"
#include "fric.h"
#include "laser.h"
#include "led.h"
#include "power_ctrl.h"
#include "rc.h"
#include "rng.h"
#include "sys.h"
#include "timer.h"
#include "servo.h"
#include "gray.h"
#include "tcs3200.h"
#include "exit_init.h"

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"

#include "calibrate_task.h"

#include "start_task.h"

void BSP_init(void);

//电机编码值规整 0—8191
#define ECD_Format(ecd)         \
    {                           \
        if ((ecd) > ecd_range)  \
            (ecd) -= ecd_range; \
        else if ((ecd) < 0)     \
            (ecd) += ecd_range; \
    }
		
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


int main(void)
{
    BSP_init();
	  chassis_init(&chassis_move);
	  

    led_green_on();		
		//底盘数据更新
  	 //灰度返回函数
    chassis_gary_loop();
	
 	  chassis_control_loop_1(&chassis_move);
	
}

//四个24v 输出 依次开启 间隔 709us
#define POWER_CTRL_ONE_BY_ONE_TIME 709

void BSP_init(void)
{
    //中断组 2
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    //初始化滴答时钟
    delay_init(configTICK_RATE_HZ);
    //流水灯，红绿灯初始化
    led_configuration();
	  //摩擦轮电机PWM初始化
    fric_PWM_configuration();
	  //stm32 板载温度传感器初始化
    temperature_ADC_init();
	  //蜂鸣器初始化
    // buzzer_init(30000, 90);

    //flash读取函数，把校准值放回对应参数
	  //定时器6 初始化
    TIM6_Init(60000, 90);
	
	
	  //颜色传感器初始化
	  tcs3200_init();
	  // 小舵机初始化
	  SERVO_PWM_Init();
    // 灰度初始化
    Gray_init();
    //外部中断
    EXTIX_Init_1();
    //EXTIX_Init_2();




//    cali_param_init();
	  //CAN接口初始化
    CAN1_mode_init(CAN_SJW_1tq, CAN_BS2_2tq, CAN_BS1_6tq, 5, CAN_Mode_Normal);
    CAN2_mode_init(CAN_SJW_1tq, CAN_BS2_2tq, CAN_BS1_6tq, 5, CAN_Mode_Normal);
		//24输出控制口 初始化
    power_ctrl_configuration();
    //24v 输出 依次上电
    for (uint8_t i = POWER1_CTRL_SWITCH; i < POWER4_CTRL_SWITCH + 1; i++)
    {
        power_ctrl_on(i);
        delay_us(POWER_CTRL_ONE_BY_ONE_TIME);
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
 
		
		    chassis_feedback_update(&chassis_move);

			chassis_move.speed_set[0] = -12.0f;
			chassis_move.speed_set[1] = -12.0f;	
			chassis_move.speed_set[2] = 12.0f;
			chassis_move.speed_set[3] = 12.0f;
		
		
		
		//chassis_staight_gray();

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
