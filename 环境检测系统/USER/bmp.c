#include "stm32f10x.h" 

void bmp_Init(){
	
	GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
}

void bmp_start(){

    GPIO_SetBits(GPIOB, GPIO_Pin_12); 

}


void bmp_stop(){

   GPIO_ResetBits(GPIOB, GPIO_Pin_12);

}
