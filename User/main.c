#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"




int main(void)
{
	
	OLED_Init();
	OLED_ShowChar(1,1,'A');
	OLED_ShowString(2,1,"ni hao");
	OLED_ShowNum(3,1,1000,2);
	OLED_ShowSignedNum(3,1,-66,2);
	OLED_Clear();
	while (1)
	{
		
	}
}
