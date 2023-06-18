#ifndef FIRE_H
#define FIRE_H

#include "stm32f10x.h"

#define FLAME_DO_PIN GPIO_Pin_11
#define FLAME_DO_PORT GPIOA

void FlameSensor_Init(void);
int ReadFlameSensorStatus(void);

#endif /* FIRE_H */
