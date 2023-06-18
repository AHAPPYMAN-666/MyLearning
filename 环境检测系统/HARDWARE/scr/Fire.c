#include "stm32f10x.h"

#define Flame_DO_PIN GPIO_Pin_11
#define Flame_DO_PORT GPIOA

void FlameSensor_Init() {
    GPIO_InitTypeDef GPIO_InitStructure;

    // ʹ�� GPIOA ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    // ���� Flame_DO_PIN Ϊ����ģʽ
    GPIO_InitStructure.GPIO_Pin = Flame_DO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // ��������ģʽ
    GPIO_Init(Flame_DO_PORT, &GPIO_InitStructure);
}

int ReadFlameSensorStatus() {
    int status;
    status = GPIO_ReadInputDataBit(Flame_DO_PORT, Flame_DO_PIN);
    return status;
}
