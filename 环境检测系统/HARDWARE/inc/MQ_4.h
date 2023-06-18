#ifndef MQ_H
#define MQ_H

#include "stm32f10x.h"

// MQ-4传感器的DO引脚定义
#define MQ4_DO_PIN GPIO_Pin_8
#define MQ4_DO_PORT GPIOA

// 初始化MQ-4传感器的ADC设置
void MQ4_ADC_Init(void);

// 获取MQ-4传感器的气体浓度值
uint16_t GetMQ4Value(void);

// 读取MQ-4传感器的数字输出状态
int Read_MQ4_DOUT_Data(void);

#endif /* MQ_H */
