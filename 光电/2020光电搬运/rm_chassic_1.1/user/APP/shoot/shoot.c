#include "Shoot.h"
#include "CAN_Receive.h"
#include "gimbal_behaviour.h"
#include "Detect_Task.h"
#include "pid.h"
#include "laser.h"
#include "fric.h"
#include "arm_math.h"
#include "user_lib.h"

#include "stm32f4xx.h"

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"


#define shoot_fric1_on(pwm) fric1_on((pwm)) //摩擦轮1pwm宏定义
#define shoot_fric2_on(pwm) fric2_on((pwm)) //摩擦轮2pwm宏定义
#define shoot_fric_off() fric_off()         //关闭两个摩擦轮


static void Shoot_Feedback_Update(void);

const RC_ctrl_t *shoot_rc; //遥控器指针
Shoot_Motor_t trigger_motor;          //射击数据
static PidTypeDef trigger_motor_pid;         //电机PID

shoot_mode_e shoot_mode = SHOOT_STOP; //射击状态机

static void Shoot_Set_Mode(void);
static void shoot_bullet_control(void);
	
void shoot_init(void)
{
	
	  static const fp32 Trigger_speed_pid[3] = {TRIGGER_ANGLE_PID_KP, TRIGGER_ANGLE_PID_KI, TRIGGER_ANGLE_PID_KD};
    //遥控器指针
    shoot_rc = get_remote_control_point();	
    //电机指针
    trigger_motor.shoot_motor_measure = get_Trigger_Motor_Measure_Point();
    //初始化PID
    PID_Init(&trigger_motor_pid, PID_POSITION, Trigger_speed_pid, TRIGGER_READY_PID_MAX_OUT, TRIGGER_READY_PID_MAX_IOUT);
    //更新数据
    Shoot_Feedback_Update();
    ramp_init(&trigger_motor.fric1_ramp, SHOOT_CONTROL_TIME * 0.001f, Fric_UP, Fric_OFF);
    ramp_init(&trigger_motor.fric2_ramp, SHOOT_CONTROL_TIME * 0.001f, Fric_UP, Fric_OFF);

    trigger_motor.ecd_count = 0;
    trigger_motor.angle = trigger_motor.shoot_motor_measure->ecd * Motor_ECD_TO_ANGLE;
    trigger_motor.given_current = 0;
    trigger_motor.move_flag = 0;
    trigger_motor.set_angle = trigger_motor.angle;
    trigger_motor.speed = 0.0f;
    trigger_motor.speed_set = 0.0f;
    trigger_motor.BulletShootCnt = 0;	
}

static void Shoot_Feedback_Update(void)
{
    static fp32 speed_fliter_1 = 0.0f;
    static fp32 speed_fliter_2 = 0.0f;
    static fp32 speed_fliter_3 = 0.0f;

    //拨弹轮电机速度滤波一下
    static const fp32 fliter_num[3] = {1.725709860247969f, -0.75594777109163436f, 0.030237910843665373f};

    //二阶低通滤波
    speed_fliter_1 = speed_fliter_2;
    speed_fliter_2 = speed_fliter_3;
    speed_fliter_3 = speed_fliter_2 * fliter_num[0] + speed_fliter_1 * fliter_num[1] + (trigger_motor.shoot_motor_measure->speed_rpm * Motor_RMP_TO_SPEED) * fliter_num[2];
    trigger_motor.speed = speed_fliter_3;

    //电机圈数重置， 因为输出轴旋转一圈， 电机轴旋转 36圈，将电机轴数据处理成输出轴数据，用于控制输出轴角度
    if (trigger_motor.shoot_motor_measure->ecd - trigger_motor.shoot_motor_measure->last_ecd > Half_ecd_range)
    {
        trigger_motor.ecd_count--;
    }
    else if (trigger_motor.shoot_motor_measure->ecd - trigger_motor.shoot_motor_measure->last_ecd < -Half_ecd_range)
    {
        trigger_motor.ecd_count++;
    }

    if (trigger_motor.ecd_count == FULL_COUNT)
    {
        trigger_motor.ecd_count = -(FULL_COUNT - 1);
    }
    else if (trigger_motor.ecd_count == -FULL_COUNT)
    {
        trigger_motor.ecd_count = FULL_COUNT - 1;
    }	
    //计算输出轴角度
    trigger_motor.angle = (trigger_motor.ecd_count * ecd_range + trigger_motor.shoot_motor_measure->ecd) * Motor_ECD_TO_ANGLE;
 	
    //射击开关下档时间计时
    if (shoot_mode != SHOOT_STOP && switch_is_down(shoot_rc->rc.s[Shoot_RC_Channel]))
    {
        if (trigger_motor.rc_s_time < RC_S_LONG_TIME)
        {
            trigger_motor.rc_s_time++;
        }
    }
    else
    {
        trigger_motor.rc_s_time = 0;
    }	
}

static void Shoot_Set_Mode(void)
{

	  static int8_t last_s = RC_SW_UP;
	  //上拨判断， 一次开启，再次关闭
    if ((switch_is_up(shoot_rc->rc.s[Shoot_RC_Channel]) && !switch_is_up(last_s) && shoot_mode == SHOOT_STOP))
    {
        shoot_mode = SHOOT_READY;
    }
    else if ((switch_is_up(shoot_rc->rc.s[Shoot_RC_Channel]) && !switch_is_up(last_s) && shoot_mode != SHOOT_STOP) || (shoot_rc->key.v & SHOOT_OFF_KEYBOARD))
    {
        shoot_mode = SHOOT_STOP;
    } 
    //处于中档， 可以使用键盘开启摩擦轮
    if (switch_is_mid(shoot_rc->rc.s[Shoot_RC_Channel]) && (shoot_rc->key.v & SHOOT_ON_KEYBOARD) && shoot_mode == SHOOT_STOP)
    {
        shoot_mode = SHOOT_READY;
    }
    //处于中档， 可以使用键盘关闭摩擦轮
    else if (switch_is_mid(shoot_rc->rc.s[Shoot_RC_Channel]) && (shoot_rc->key.v & SHOOT_OFF_KEYBOARD) && shoot_mode == SHOOT_READY)
    {
        shoot_mode = SHOOT_STOP;
    }

    //如果云台状态是 无力状态，就关闭射击
    if (gimbal_cmd_to_shoot_stop())
    {
        shoot_mode = SHOOT_STOP;
    }
		
	  if (shoot_mode == SHOOT_READY)
    {
        //下拨一次或者鼠标按下一次，进入射击状态
        if ((switch_is_down(shoot_rc->rc.s[Shoot_RC_Channel]) && !switch_is_down(last_s)) || (trigger_motor.press_l && trigger_motor.last_press_l == 0) || (trigger_motor.press_r && trigger_motor.last_press_r == 0))
        {
            shoot_mode = SHOOT_BULLET;
            trigger_motor.last_butter_count = trigger_motor.BulletShootCnt;
        }
        //鼠标长按一直进入射击状态 保持连发
        if ((trigger_motor.press_l_time == PRESS_LONG_TIME) || (trigger_motor.press_r_time == PRESS_LONG_TIME) || (trigger_motor.rc_s_time == RC_S_LONG_TIME))
        {
            if (shoot_mode != SHOOT_DONE && trigger_motor.key == SWITCH_TRIGGER_ON)
            {
                shoot_mode = SHOOT_BULLET;
            }
        }
    }
	  last_s = shoot_rc->rc.s[Shoot_RC_Channel];
		
}


int tempaaa;
int16_t shoot_control_loop(void)
{
    int16_t shoot_CAN_Set_Current; 
    static uint16_t fric_pwm1 = Fric_OFF;
    static uint16_t fric_pwm2 = Fric_OFF;
	
    Shoot_Set_Mode();        //设置状态机
    Shoot_Feedback_Update(); //更新数据
	
    //发射状态控制
    if (shoot_mode == SHOOT_BULLET|| trigger_motor.move_flag == 1 )
    {
			  tempaaa++;
        trigger_motor_pid.max_out = TRIGGER_BULLET_PID_MAX_OUT;
        trigger_motor_pid.max_iout = TRIGGER_BULLET_PID_MAX_IOUT;
        shoot_bullet_control();
    }
		else if(trigger_motor.press_l_time == PRESS_LONG_TIME)
		{
			 trigger_motor.speed_set=TRIGGER_SPEED;
	  }
		else
		{
			  trigger_motor.speed_set = 0;
		}
		
		if (shoot_mode == SHOOT_STOP)
    {
        trigger_motor.fric1_ramp.out = Fric_OFF;
        trigger_motor.fric2_ramp.out = Fric_OFF;
        trigger_motor.speed_set = 0;
    }
		else
		{
			  trigger_motor.fric1_ramp.max_value = Fric_UP;
        trigger_motor.fric2_ramp.max_value = Fric_UP;
			  shoot_mode = SHOOT_READY;
			
				         //摩擦轮需要一个个斜波开启，不能同时直接开启，否则可能电机不转
        ramp_calc(&trigger_motor.fric1_ramp, SHOOT_FRIC_PWM_ADD_VALUE);

        if(trigger_motor.fric1_ramp.out == trigger_motor.fric1_ramp.max_value)
        {
            ramp_calc(&trigger_motor.fric2_ramp, SHOOT_FRIC_PWM_ADD_VALUE);
        }
		}
		
		

		PID_Calc(&trigger_motor_pid, trigger_motor.speed, trigger_motor.speed_set);
    trigger_motor.given_current = (int16_t)(trigger_motor_pid.out);
    shoot_CAN_Set_Current = trigger_motor.given_current;
		
		if(shoot_rc->key.v & KEY_PRESSED_OFFSET_C)
		{
			trigger_motor.fric1_ramp.out=Fric_DOWN;
			trigger_motor.fric2_ramp.out=Fric_DOWN;
		}
	  fric_pwm1 = (uint16_t)(trigger_motor.fric1_ramp.out);
    fric_pwm2 = (uint16_t)(trigger_motor.fric2_ramp.out);

		
    shoot_fric1_on(fric_pwm1);
    shoot_fric2_on(fric_pwm2);
		
		
		
    return shoot_CAN_Set_Current;}


/**
  * @brief          射击控制，控制拨弹电机角度，完成一次发射
  * @author         RM
  * @param[in]      void
  * @retval         void
  */


static void shoot_bullet_control(void)
{
    //每次拨动 1/4PI的角度
    if (trigger_motor.move_flag == 0 && shoot_mode == SHOOT_BULLET)
    {
        trigger_motor.set_angle = rad_format(trigger_motor.set_angle + PI_Four);
        trigger_motor.cmd_time = xTaskGetTickCount();
        trigger_motor.move_flag = 1;
    }

    //到达角度判断
    if (rad_format(trigger_motor.set_angle - trigger_motor.angle) > 0.05f)
    {
        //没到达一直设置旋转速度
        trigger_motor.speed_set = TRIGGER_SPEED;
        trigger_motor.run_time = xTaskGetTickCount();
    }
    else
    {
        trigger_motor.move_flag = 0;
			 
    }
}

