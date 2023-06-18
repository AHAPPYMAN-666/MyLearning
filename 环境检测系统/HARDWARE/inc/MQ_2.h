
#ifndef MQ2_H
#define MQ2_H

#include "stm32f10x.h"
#include "math.h"

#define CAL_PPM 20  // 校准环境中PPM值
#define RL      5   // RL阻值

extern uint16_t ADC_Value; // 全局变量，存储ADC转换结果

// 传感器初始化
void MQ2_Init(void);

// 传感器校准函数
void MQ2_PPM_Calibration(float RS);

// MQ2传感器数据处理
float MQ2_GetPPM(void);

#endif /* MQ2_H */

