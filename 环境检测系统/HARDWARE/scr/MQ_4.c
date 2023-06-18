#include "stm32f10x.h"
#include "stm32f10x_adc.h"
#include "MQ_4.h"

// ��ʼ��MQ-4��������ADC����
void MQ4_ADC_Init() {
    GPIO_InitTypeDef GPIO_InitStructure;
    ADC_InitTypeDef ADC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE);

    // ����GPIO����Ϊģ������ģʽ
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // ADC����
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1, &ADC_InitStructure);

    // ����ADCͨ��
    ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime_239Cycles5);

    // ʹ��ADC
    ADC_Cmd(ADC1, ENABLE);

    // У׼ADC
    ADC_ResetCalibration(ADC1);
    while (ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1));
}

// ��ȡMQ-4������������Ũ��ֵ
uint16_t GetMQ4Value(void) {
    uint16_t ADCVal;
    float Voltage;
    uint16_t ppm;

    // ����ADCת��
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);

    // �ȴ�ת�����
    while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));

    // ��ȡת�����
    ADCVal = ADC_GetConversionValue(ADC1);
    Voltage = ADCVal * 3.3 / 4096;

    // ������Ȼ���Ļ����£�ʵ��AOUT�˵ĵ�ѹΪ0.5V������⵽��Ȼ��ʱ����ѹÿ����0.1V��ʵ�ʱ�������Ũ������200ppm
    ppm = (Voltage - 0.5) / 0.1 * 200;

    return ppm;
}

// ��ȡMQ-4���������������״̬
int Read_MQ4_DOUT_Data() {
    int status;
    status = GPIO_ReadInputDataBit(MQ4_DO_PORT, MQ4_DO_PIN);
    return status;
}
