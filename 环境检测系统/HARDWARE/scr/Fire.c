#include "stm32f10x.h"

#define Flame_DO_PIN GPIO_Pin_11
#define Flame_DO_PORT GPIOA

void FlameSensor_Init() {
    GPIO_InitTypeDef GPIO_InitStructure;

    // 使能 GPIOA 时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    // 配置 Flame_DO_PIN 为输入模式
    GPIO_InitStructure.GPIO_Pin = Flame_DO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // 上拉输入模式
    GPIO_Init(Flame_DO_PORT, &GPIO_InitStructure);
}

int ReadFlameSensorStatus() {
    int status;
    status = GPIO_ReadInputDataBit(Flame_DO_PORT, Flame_DO_PIN);
    return status;
}
