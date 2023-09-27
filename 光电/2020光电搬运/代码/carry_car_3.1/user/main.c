/**
  ****************************(C) COPYRIGHT 2016 DJI****************************
  * @file       main.c/h
  * @brief      stm32��ʼ���Լ���ʼ����freeRTOS��h�ļ��������ȫ�ֺ궨���Լ�
  *             typedef һЩ������������
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

//�������ֵ���� 0��8191
#define ECD_Format(ecd)         \
    {                           \
        if ((ecd) > ecd_range)  \
            (ecd) -= ecd_range; \
        else if ((ecd) < 0)     \
            (ecd) += ecd_range; \
    }
		
//���̳�ʼ������Ҫ��pid��ʼ��
static void chassis_init(chassis_move_t *chassis_move_init);
//��������
static void chassis_feedback_update(chassis_move_t *chassis_move_update);

void chassic_go_one (int d,int g);

//�����ƶ� ��ת90
static void chassis_move_right_90(void);
//�����ƶ� ��ת45
static void chassis_move_right_45(void);
//�����ƶ� ��ת135
static void chassis_move_right_135(void);
		
//�����ƶ� ��ת90
static void chassis_move_left_90(void);
//�����ƶ� ��ת45
static void chassis_move_left_45(void);
//�����ƶ� ��ת135		
static void chassis_move_left_135(void);

//ǰ��Ѳ��ģʽ
static void chassis_staight_gray(void);
//����Ѳ��ģʽ	
static void chassis_back_gray(void);

		
//PID����
static void chassis_control_loop_1(chassis_move_t *chassis_move_control_loop);


//��ȡ�Ҷ�
void chassis_gary_loop();


//�����˶�����
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
		//�������ݸ���
  	 //�Ҷȷ��غ���
    chassis_gary_loop();
	
 	  chassis_control_loop_1(&chassis_move);
	
}

//�ĸ�24v ��� ���ο��� ��� 709us
#define POWER_CTRL_ONE_BY_ONE_TIME 709

void BSP_init(void)
{
    //�ж��� 2
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    //��ʼ���δ�ʱ��
    delay_init(configTICK_RATE_HZ);
    //��ˮ�ƣ����̵Ƴ�ʼ��
    led_configuration();
	  //Ħ���ֵ��PWM��ʼ��
    fric_PWM_configuration();
	  //stm32 �����¶ȴ�������ʼ��
    temperature_ADC_init();
	  //��������ʼ��
    // buzzer_init(30000, 90);

    //flash��ȡ��������У׼ֵ�Żض�Ӧ����
	  //��ʱ��6 ��ʼ��
    TIM6_Init(60000, 90);
	
	
	  //��ɫ��������ʼ��
	  tcs3200_init();
	  // С�����ʼ��
	  SERVO_PWM_Init();
    // �Ҷȳ�ʼ��
    Gray_init();
    //�ⲿ�ж�
    EXTIX_Init_1();
    //EXTIX_Init_2();




//    cali_param_init();
	  //CAN�ӿڳ�ʼ��
    CAN1_mode_init(CAN_SJW_1tq, CAN_BS2_2tq, CAN_BS1_6tq, 5, CAN_Mode_Normal);
    CAN2_mode_init(CAN_SJW_1tq, CAN_BS2_2tq, CAN_BS1_6tq, 5, CAN_Mode_Normal);
		//24������ƿ� ��ʼ��
    power_ctrl_configuration();
    //24v ��� �����ϵ�
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
		
		
	  //�����ٶȻ�pidֵ
    const static fp32 motor_speed_pid[3] = {M2006_MOTOR_SPEED_PID_KP, M2006_MOTOR_SPEED_PID_KI, M2006_MOTOR_SPEED_PID_KD};
		uint8_t i;			
	  //��ʼ��PID �˶�
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
				
     //���µ���ٶȣ����ٶ����ٶȵ�PID΢��
     chassis_move_update->motor_chassis[i].speed = chassis_move_update->motor_chassis[i].chassis_motor_measure->speed_rpm * Motor_RMP_TO_SPEED;
		
		
    //���Ȧ�����ã� ��Ϊ�������תһȦ�� �������ת 36Ȧ������������ݴ������������ݣ����ڿ��������Ƕ�
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

    //���������Ƕ�
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
    //����pid
 
		
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
     //��ֵ����ֵ
    for (i = 0; i < 4; i++)
    {
        chassis_move_control_loop->motor_chassis[i].give_current = (int16_t)(chassis_move_control_loop->motor_speed_pid[i].out);
    }
		
		   CAN_CMD_CHASSIS(chassis_move.motor_chassis[0].give_current,chassis_move.motor_chassis[1].give_current,
                              chassis_move.motor_chassis[2].give_current, chassis_move.motor_chassis[3].give_current);	
 
}








// ǰ��Ѳ��ģʽ
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


// ����Ѳ��ģʽ
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

// ��ת90
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

// ��ת45
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

// ��ת45
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



// ��ת90
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
// ��ת45
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
// ��ת135
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


//�Ҷȼ��
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
