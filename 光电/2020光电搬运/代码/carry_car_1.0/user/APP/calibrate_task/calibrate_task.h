#ifndef CALIBRATE_TASK_H
#define CALIBRATE_TASK_H
#include "main.h"

#define CALIBRATE_CONTROL_TIME 1 //У׼���������е����� Ϊ1ms
#define RC_CALI_VALUE_HOLE 600        //ң������˻����ڰ� ��ֵ�ж��� ң����ҡ������� 660 ֻҪ����630 ����Ϊ�����
#define CALIBRATE_END_TIME 20000 //ң����У׼ʱ��20s ����20s��Ҫ���²���
#define RC_CMD_LONG_TIME 2000 //ң����ʹ��У׼��ʱ�䣬�������ڰ˵�ʱ��

#define CALI_FUNC_CMD_ON 1   //У׼������ʹ��У׼
#define CALI_FUNC_CMD_INIT 0 //У׼����������flash�е�У׼����
#define CALIED_FLAG 0x55       //�������Ѿ�У׼��
#define GYRO_CALIBRATE_TIME 20000 //������У׼��ʱ�� 20s
#define gyro_cali_disable_control() RC_unable()                 //������У׼ʱ�����ң����
//����������У׼ֵ
#define gyro_set_cali(cali_scale, cali_offset) INS_set_cali_gyro((cali_scale), (cali_offset))
//������У׼����
#define gyro_cali_fun(cali_scale, cali_offset, time_count) INS_cali_gyro((cali_scale), (cali_offset), (time_count))


#define GYRO_CONST_MAX_TEMP 45.0f //�����ǿ��ƺ��� �������¶�
#define FIRMWARE_VERSION 12345 //��ͷ�е�Ӳ���汾�� Ŀǰ����д��

#define SELF_ID 0              //��ͷ�е�ID

#define FLASH_USER_ADDR ADDR_FLASH_SECTOR_23 //Ҫд��flash������Ŀǰ�����һ�飬
#define CALI_SENSOR_HEAD_LEGHT 1 //У׼�ṹ��ı�ͷ Ϊcali_sensor_t��ǰ�� �꿴 cali_sensor_t������ ��С 1 ����һ��32λ����

#define cali_get_mcu_temperature() get_temprate() //��ȡstm32�ϵ��¶� ��ΪIMUУ׼�Ļ����¶�


#define cali_flash_read(address, buf, len) flash_read((address), (buf), (len))                  //flash ��ȡ����
#define cali_flash_write(address, buf, len) flash_write_single_address((address), (buf), (len)) //flash д�뺯��

#define get_remote_ctrl_point_cali() get_remote_control_point() //��ȡң�����Ľṹ��ָ��

//У׼�豸��
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

//У׼�豸ǰ����ͨ��flash_buf���ӵ���Ӧ��У׼�豸������ַ
typedef __packed struct
{
    uint8_t name[3];
    uint8_t cali_done;
    uint8_t flash_len : 7;
    uint8_t cali_cmd : 1;
    uint32_t *flash_buf;
    bool_t (*cali_hook)(uint32_t *point, bool_t cmd);
} cali_sensor_t;

//ͷ�豸��У׼����
typedef __packed struct
{
    uint8_t self_id;
    int8_t temperate;
    uint16_t firmware_version;
    fp32 latitude;
} head_cali_t;
//��̨�豸��У׼����
typedef struct
{
    uint16_t yaw_offset;
    uint16_t pitch_offset;
    fp32 yaw_max_angle;
    fp32 yaw_min_angle;
    fp32 pitch_max_angle;
    fp32 pitch_min_angle;
} gimbal_cali_t;
//�����ǣ����ٶȼƣ�������ͨ��У׼����
typedef struct
{
    fp32 offset[3]; //x,y,z
    fp32 scale[3];  //x,y,z
} imu_cali_t;

//��ʼ�����Լ���ȡflashУ׼ֵ
extern void cali_param_init(void);
//����mpu6500���Ƶ��¶�
extern int8_t get_control_temperate(void);
extern void calibrate_task(void *pvParameters);
#endif
