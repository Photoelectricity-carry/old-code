#ifndef CALIBRATE_TASK_H
#define CALIBRATE_TASK_H
#include "main.h"

#define CALIBRATE_CONTROL_TIME 1 //校准任务函数运行的周期 为1ms
#define RC_CALI_VALUE_HOLE 600        //遥控器外八或者内八 阈值判定， 遥控器摇杆最大是 660 只要大于630 就认为到最大
#define CALIBRATE_END_TIME 20000 //遥控器校准时长20s 超过20s需要重新操作
#define RC_CMD_LONG_TIME 2000 //遥控器使能校准的时间，即保持内八的时间

#define CALI_FUNC_CMD_ON 1   //校准函数，使能校准
#define CALI_FUNC_CMD_INIT 0 //校准函数，传递flash中的校准参数
#define CALIED_FLAG 0x55       //代表标记已经校准完
#define GYRO_CALIBRATE_TIME 20000 //陀螺仪校准的时间 20s
#define gyro_cali_disable_control() RC_unable()                 //陀螺仪校准时候掉线遥控器
//设置陀螺仪校准值
#define gyro_set_cali(cali_scale, cali_offset) INS_set_cali_gyro((cali_scale), (cali_offset))
//陀螺仪校准函数
#define gyro_cali_fun(cali_scale, cali_offset, time_count) INS_cali_gyro((cali_scale), (cali_offset), (time_count))


#define GYRO_CONST_MAX_TEMP 45.0f //陀螺仪控制恒温 最大控制温度
#define FIRMWARE_VERSION 12345 //表头中的硬件版本号 目前随意写的

#define SELF_ID 0              //表头中的ID

#define FLASH_USER_ADDR ADDR_FLASH_SECTOR_23 //要写入flash扇区，目前是最后一块，
#define CALI_SENSOR_HEAD_LEGHT 1 //校准结构体的表头 为cali_sensor_t的前部 详看 cali_sensor_t的描述 大小 1 代表一个32位数据

#define cali_get_mcu_temperature() get_temprate() //获取stm32上的温度 作为IMU校准的环境温度


#define cali_flash_read(address, buf, len) flash_read((address), (buf), (len))                  //flash 读取函数
#define cali_flash_write(address, buf, len) flash_write_single_address((address), (buf), (len)) //flash 写入函数

#define get_remote_ctrl_point_cali() get_remote_control_point() //获取遥控器的结构体指针

//校准设备名
typedef enum
{
    CALI_HEAD,
    CALI_GIMBAL,
    CALI_GYRO,
    CALI_ACC,
    CALI_MAG,
    CALI_LIST_LENGHT,
    //add more...
} cali_id_e;

//校准设备前部，通过flash_buf链接到对应的校准设备变量地址
typedef __packed struct
{
    uint8_t name[3];
    uint8_t cali_done;
    uint8_t flash_len : 7;
    uint8_t cali_cmd : 1;
    uint32_t *flash_buf;
    bool_t (*cali_hook)(uint32_t *point, bool_t cmd);
} cali_sensor_t;

//头设备的校准数据
typedef __packed struct
{
    uint8_t self_id;
    int8_t temperate;
    uint16_t firmware_version;
    fp32 latitude;
} head_cali_t;
//云台设备的校准数据
typedef struct
{
    uint16_t yaw_offset;
    uint16_t pitch_offset;
    fp32 yaw_max_angle;
    fp32 yaw_min_angle;
    fp32 pitch_max_angle;
    fp32 pitch_min_angle;
} gimbal_cali_t;
//陀螺仪，加速度计，磁力计通用校准数据
typedef struct
{
    fp32 offset[3]; //x,y,z
    fp32 scale[3];  //x,y,z
} imu_cali_t;

//初始化，以及读取flash校准值
extern void cali_param_init(void);
//返回mpu6500控制的温度
extern int8_t get_control_temperate(void);
extern void calibrate_task(void *pvParameters);
#endif
