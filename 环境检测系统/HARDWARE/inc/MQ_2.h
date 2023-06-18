
#ifndef MQ2_H
#define MQ2_H

#include "stm32f10x.h"
#include "math.h"

#define CAL_PPM 20  // У׼������PPMֵ
#define RL      5   // RL��ֵ

extern uint16_t ADC_Value; // ȫ�ֱ������洢ADCת�����

// ��������ʼ��
void MQ2_Init(void);

// ������У׼����
void MQ2_PPM_Calibration(float RS);

// MQ2���������ݴ���
float MQ2_GetPPM(void);

#endif /* MQ2_H */

