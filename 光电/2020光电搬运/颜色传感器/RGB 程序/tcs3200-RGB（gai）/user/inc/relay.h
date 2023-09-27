#ifndef _RELAY_H_
#define _RELAY_H_

#include "stm32f10x.h"
#include "io_bit.h"

#define SENSOR_POWER_SWITCH          PCout(10)   //程控电源给Sensor板供电开关
#define CURRENT_SWITCH               PCout(11)   //测试电流切换开关
#define HUB_BLUETOOTH_SWITCH         PCout(12)   //Hub板蓝牙控制开关
#define HUB_POWER_SWITCH             PDout(2)    //Hub板供电开关
#define BUCHANG_POWER_SWITCH         PBout(3)    //Sensor板供电补偿开关

void relay_init(void);
void Close_All_Relay(void);
void TEST_CURR_SW(u8 model);

#endif

