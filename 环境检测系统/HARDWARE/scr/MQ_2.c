#include "stm32f10x.h"
#include "math.h"
#include "OLED.h"

#define ADC_RESOLUTION 4095.0f  // ADC分辨率
#define RL 5.0f  // MQ-2传感器的RL阻值


ADC_InitTypeDef ADC_InitStructure;

// 初始化ADC
void ADC_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  // 使能ADC1和GPIOA时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOA, ENABLE);

  // 配置GPIOA.0为模拟输入
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  // ADC配置
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel = 1;
  ADC_Init(ADC1, &ADC_InitStructure);

  // 配置ADC通道0的采样时间
  ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5);

  // 使能ADC
  ADC_Cmd(ADC1, ENABLE);

  // 开启ADC校准
  ADC_ResetCalibration(ADC1);
  while (ADC_GetResetCalibrationStatus(ADC1));
  ADC_StartCalibration(ADC1);
  while (ADC_GetCalibrationStatus(ADC1));
}


// 获取MQ-2传感器的烟雾浓度
float MQ2_GetSmokeDensity(void)
{
  uint16_t ADC_Value;
  float Vout, Rs, Ro, SmokeDensity;

  // 启动ADC转换
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);

  // 等待转换完成
  while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);

  // 读取ADC值
  ADC_Value = ADC_GetConversionValue(ADC1);

  // 计算电压输出值
  Vout = (float)ADC_Value / ADC_RESOLUTION * 3.3f;
 
  // 计算传感器阻值
  Rs = (3.3f - Vout) / Vout * RL;
	 OLED_ShowFloat(4,2,Rs,5);

  // 在洁净空气中的阻值
  Ro = Rs / pow(20 / 613.9f, 1 / -2.074f);  // 假设为10KΩ

  // 计算烟雾浓度
  SmokeDensity = 613.9f * pow(Rs/Ro, -2.074f);

  return SmokeDensity;
}

