#include "oled.h"
#include "stm32f10x.h" 
#include "OLED_Show.h"


void OLEDShowConnecting(){

				OLED_ShowChinese(0,0,10,16,1); 	//正
		    OLED_ShowChinese(18,0,11,16,1);	//在
				OLED_ShowChinese(36,0,12,16,1); //连
				OLED_ShowChinese(54,0,13,16,1);	//接
				OLED_ShowChinese(72,0,14,16,1); //服
				OLED_ShowChinese(90,0,15,16,1);	//务
				OLED_ShowChinese(108,0,16,16,1);	//器
	
}

void OLEDShowData(){

				OLED_ShowChinese(0,0,0,16,1); //温 
				OLED_ShowChinese(18,0,1,16,1);//度
				OLED_ShowString(36,0,":",16,1);
				OLED_ShowChinese(0,16,2,16,1);//湿
				OLED_ShowChinese(18,16,1,16,1);//度	
				OLED_ShowString(36,16,":",16,1); 
				OLED_ShowChinese(0,34,17,16,1); 	//烟
		    OLED_ShowChinese(18,34,18,16,1);	//雾
				OLED_ShowChinese(36,34,19,16,1); //浓
				OLED_ShowChinese(54,34,20,16,1);	//度
				OLED_ShowString(72,34,":",16,1);
}
