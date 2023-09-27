#ifndef _RELAY_H_
#define _RELAY_H_

#include "stm32f10x.h"
#include "io_bit.h"

#define SENSOR_POWER_SWITCH          PCout(10)   //�̿ص�Դ��Sensor�幩�翪��
#define CURRENT_SWITCH               PCout(11)   //���Ե����л�����
#define HUB_BLUETOOTH_SWITCH         PCout(12)   //Hub���������ƿ���
#define HUB_POWER_SWITCH             PDout(2)    //Hub�幩�翪��
#define BUCHANG_POWER_SWITCH         PBout(3)    //Sensor�幩�粹������

void relay_init(void);
void Close_All_Relay(void);
void TEST_CURR_SW(u8 model);

#endif

