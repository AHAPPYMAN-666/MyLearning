#include "stm32f10x.h"
#include "math.h"
#include "OLED.h"

#define ADC_RESOLUTION 4095.0f  // ADC�ֱ���
#define RL 5.0f  // MQ-2��������RL��ֵ


ADC_InitTypeDef ADC_InitStructure;

// ��ʼ��ADC
void ADC_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  // ʹ��ADC1��GPIOAʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOA, ENABLE);

  // ����GPIOA.0Ϊģ������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  // ADC����
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel = 1;
  ADC_Init(ADC1, &ADC_InitStructure);

  // ����ADCͨ��0�Ĳ���ʱ��
  ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5);

  // ʹ��ADC
  ADC_Cmd(ADC1, ENABLE);

  // ����ADCУ׼
  ADC_ResetCalibration(ADC1);
  while (ADC_GetResetCalibrationStatus(ADC1));
  ADC_StartCalibration(ADC1);
  while (ADC_GetCalibrationStatus(ADC1));
}


// ��ȡMQ-2������������Ũ��
float MQ2_GetSmokeDensity(void)
{
  uint16_t ADC_Value;
  float Vout, Rs, Ro, SmokeDensity;

  // ����ADCת��
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);

  // �ȴ�ת�����
  while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);

  // ��ȡADCֵ
  ADC_Value = ADC_GetConversionValue(ADC1);

  // �����ѹ���ֵ
  Vout = (float)ADC_Value / ADC_RESOLUTION * 3.3f;
 
  // ���㴫������ֵ
  Rs = (3.3f - Vout) / Vout * RL;
	 OLED_ShowFloat(4,2,Rs,5);

  // �ڽྻ�����е���ֵ
  Ro = Rs / pow(20 / 613.9f, 1 / -2.074f);  // ����Ϊ10K��

  // ��������Ũ��
  SmokeDensity = 613.9f * pow(Rs/Ro, -2.074f);

  return SmokeDensity;
}

