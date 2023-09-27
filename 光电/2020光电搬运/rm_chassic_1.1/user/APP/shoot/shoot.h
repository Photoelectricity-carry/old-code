#ifndef SHOOT_H
#define SHOOT_H
#include "main.h"
#include "CAN_Receive.h"
#include "remote_control.h"
#include "user_lib.h"
#include "Gimbal_Task.h"
//射击发射开关通道数据
#define Shoot_RC_Channel    1
//云台模式使用的开关通道
#define GIMBAL_ModeChannel  1

#define SHOOT_CONTROL_TIME  GIMBAL_CONTROL_TIME

//遥控器射击开关打下档一段时间后 连续发射子弹 用于清单
#define RC_S_LONG_TIME 2000

#define SHOOT_FRIC_PWM_ADD_VALUE    100.0f
//鼠标长按判断
#define PRESS_LONG_TIME 400
//射击摩擦轮激光打开 关闭
#define SHOOT_ON_KEYBOARD KEY_PRESSED_OFFSET_Q
#define SHOOT_OFF_KEYBOARD KEY_PRESSED_OFFSET_E


//拨弹速度
#define TRIGGER_SPEED 7.0f //-12.0f
#define Ready_Trigger_Speed 6.0f

//电机rmp 变化成 旋转速度的比例
#define Motor_RMP_TO_SPEED 0.00290888208665721596153948461415f
#define Motor_ECD_TO_ANGLE 0.000021305288720633905968306772076277f
#define FULL_COUNT 18

//拨弹轮电机PID
#define TRIGGER_ANGLE_PID_KP 800.0f
#define TRIGGER_ANGLE_PID_KI 0.0f
#define TRIGGER_ANGLE_PID_KD 0.0f

#define TRIGGER_READY_PID_MAX_OUT 5000.0f
#define TRIGGER_READY_PID_MAX_IOUT 2500.0f

#define TRIGGER_BULLET_PID_MAX_OUT 15000.0f
#define TRIGGER_BULLET_PID_MAX_IOUT 5000.0f

#define PI_Four 0.78539816339744830961566084581988f
#define PI_Three 1.0466666666666f
#define PI_Ten 0.314f

#define SWITCH_TRIGGER_ON 0

typedef struct
{
  ramp_function_source_t fric1_ramp;
  ramp_function_source_t fric2_ramp;
  const motor_measure_t *shoot_motor_measure;
	fp32 speed;
	fp32 speed_set;
	fp32 angle;
	int8_t ecd_count;
	fp32 set_angle;
  int16_t given_current;
	
	bool_t press_l;
	bool_t press_r;
	bool_t last_press_l;
	bool_t last_press_r;
	uint16_t press_l_time;
	uint16_t press_r_time;
	uint16_t rc_s_time;
	
	uint32_t run_time;
	uint32_t cmd_time;
	bool_t move_flag;
	bool_t key;
	int16_t BulletShootCnt;
	int16_t last_butter_count;
} Shoot_Motor_t;

typedef enum
{
    SHOOT_STOP = 0,
    SHOOT_READY,
    SHOOT_BULLET,
	  SHOOT_DONE,
} shoot_mode_e;

//由于射击和云台使用同一个can的id故也射击任务在云台任务中执行
extern void shoot_init(void);
extern int16_t shoot_control_loop(void);

#endif
