#ifndef MAIN_H
#define MAIN_H

typedef signed char int8_t;
typedef signed short int int16_t;
typedef signed int int32_t;
typedef signed long long int64_t;

/* exact-width unsigned integer types */
typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
typedef unsigned char bool_t;
typedef float fp32;
typedef double fp64;

#include "CAN_Receive.h"
#include "pid.h"
#include "user_lib.h"

#define SysCoreClock 180

#define RC_NVIC 4

#define CAN1_NVIC 4
#define CAN2_NVIC 4
#define TIM3_NVIC 5
#define TIM6_NVIC 4
#define SPI5_RX_NVIC 5
#define MPU_INT_NVIC 5

#define Latitude_At_ShenZhen 22.57025f

#ifndef NULL
#define NULL 0
#endif

#ifndef PI
#define PI 3.14159265358979f
#endif




//电机码盘值最大以及中值
#define Half_ecd_range 4096
#define ecd_range 8191

//任务初始化 空闲一段时间
#define GIMBAL_TASK_INIT_TIME 201
//云台控制周期
#define GIMBAL_CONTROL_TIME 1

//底盘电机速度环PID
#define M2006_MOTOR_SPEED_PID_KP 900.0f
#define M2006_MOTOR_SPEED_PID_KI 0.0f
#define M2006_MOTOR_SPEED_PID_KD 0.0f
#define M2006_MOTOR_SPEED_MAX_OUT 5000.0f
#define M2006_MOTOR_SPEED_MAX_IOUT 2500.0f

#define TRIGGER_BULLET_PID_MAX_OUT 15000.0f
#define TRIGGER_BULLET_PID_MAX_IOUT 5000.0f

//电机rmp 变化成 旋转速度的比例
#define Motor_RMP_TO_SPEED 0.00290888208665721596153948461415f
#define Motor_ECD_TO_ANGLE 0.000021305288720633905968306772076277f
#define FULL_COUNT 360

//速度
#define T2006_SPEED_left  8.0f
#define T2006_SPEED_right -8.0f

#define PI_Four 0.78539816339744830961566084581988f
#define PI_Three 1.0466666666666f
#define PI_Ten 0.314f


#define PI_All 22.4247778f
#define PI_LEFT -4.5f

#define PI_LEFT_45 -2.25f
#define PI_RIGHT_45 2.55f

#define PI_RIGHT_135 7.85f
#define PI_LEFT_135 -6.75f


#define right_45    1
#define right_90    2
#define right_135   3
#define left_45     4
#define left_90     5
#define left_135    6

#define PI_RIGHT 5.5f

typedef enum
{
  CHASSIS_VECTOR_FOLLOW_GIMBAL_YAW,   //底盘跟随云台
  CHASSIS_VECTOR_FOLLOW_CHASSIS_YAW,  //底盘自主
  CHASSIS_VECTOR_NO_FOLLOW_YAW,       //底盘不跟随
  CHASSIS_VECTOR_RAW,									//底盘原始控制
	CHASSIS_VECTOR_SPIN,								//小陀螺
} chassis_mode_e;

typedef struct
{
  const motor_measure_t *chassis_motor_measure;
  fp32 accel;
  fp32 speed;
  fp32 speed_set;
  int16_t give_current;
} Chassis_Motor_t;


typedef struct
{
  chassis_mode_e chassis_mode;               //底盘控制状态机
	chassis_mode_e last_chassis_mode;          //底盘上次控制状态机
	Chassis_Motor_t motor_chassis[4];          //底盘电机数据
	PidTypeDef motor_speed_pid[4];             //底盘电机速度pid
	fp32 angle[4];
	int16_t ecd_count[4];
  int16_t given_current[4];
  fp32 set_angle[4];
	fp32 speed[4];
	fp32 speed_set[4];	
	
	bool_t move_flag;
	
	
} chassis_move_t;




#endif /* __MAIN_H */
