#ifndef MQ_H
#define MQ_H

#include "stm32f10x.h"

// MQ-4��������DO���Ŷ���
#define MQ4_DO_PIN GPIO_Pin_8
#define MQ4_DO_PORT GPIOA

// ��ʼ��MQ-4��������ADC����
void MQ4_ADC_Init(void);

// ��ȡMQ-4������������Ũ��ֵ
uint16_t GetMQ4Value(void);

// ��ȡMQ-4���������������״̬
int Read_MQ4_DOUT_Data(void);

#endif /* MQ_H */
