#include "oled.h"
#include "stm32f10x.h" 
#include "OLED_Show.h"


void OLEDShowConnecting(){

				OLED_ShowChinese(0,0,10,16,1); 	//��
		    OLED_ShowChinese(18,0,11,16,1);	//��
				OLED_ShowChinese(36,0,12,16,1); //��
				OLED_ShowChinese(54,0,13,16,1);	//��
				OLED_ShowChinese(72,0,14,16,1); //��
				OLED_ShowChinese(90,0,15,16,1);	//��
				OLED_ShowChinese(108,0,16,16,1);	//��
	
}

void OLEDShowData(){

				OLED_ShowChinese(0,0,0,16,1); //�� 
				OLED_ShowChinese(18,0,1,16,1);//��
				OLED_ShowString(36,0,":",16,1);
				OLED_ShowChinese(0,16,2,16,1);//ʪ
				OLED_ShowChinese(18,16,1,16,1);//��	
				OLED_ShowString(36,16,":",16,1); 
				OLED_ShowChinese(0,34,17,16,1); 	//��
		    OLED_ShowChinese(18,34,18,16,1);	//��
				OLED_ShowChinese(36,34,19,16,1); //Ũ
				OLED_ShowChinese(54,34,20,16,1);	//��
				OLED_ShowString(72,34,":",16,1);
}
