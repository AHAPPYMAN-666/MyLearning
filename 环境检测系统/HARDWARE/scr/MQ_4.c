#include "stm32f10x.h"
#include "stm32f10x_adc.h"
#include "MQ_4.h"

// 初始化MQ-4传感器的ADC设置
void MQ4_ADC_Init() {
    GPIO_InitTypeDef GPIO_InitStructure;
    ADC_InitTypeDef ADC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE);

    // 配置GPIO引脚为模拟输入模式
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // ADC配置
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1, &ADC_InitStructure);

    // 配置ADC通道
    ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime_239Cycles5);

    // 使能ADC
    ADC_Cmd(ADC1, ENABLE);

    // 校准ADC
    ADC_ResetCalibration(ADC1);
    while (ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1));
}

// 获取MQ-4传感器的气体浓度值
uint16_t GetMQ4Value(void) {
    uint16_t ADCVal;
    float Voltage;
    uint16_t ppm;

    // 启动ADC转换
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);

    // 等待转换完成
    while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));

    // 获取转换结果
    ADCVal = ADC_GetConversionValue(ADC1);
    Voltage = ADCVal * 3.3 / 4096;

    // 在无天然气的环境下，实测AOUT端的电压为0.5V，当检测到天然气时，电压每升高0.1V，实际被测气体浓度增加200ppm
    ppm = (Voltage - 0.5) / 0.1 * 200;

    return ppm;
}

// 读取MQ-4传感器的数字输出状态
int Read_MQ4_DOUT_Data() {
    int status;
    status = GPIO_ReadInputDataBit(MQ4_DO_PORT, MQ4_DO_PIN);
    return status;
}
