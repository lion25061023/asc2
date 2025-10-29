#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"
#include "Timer.h"
#include "Motor.h"
#include "Encoder.h"
#include "Serial.h"

uint8_t get_flag;
uint8_t mode;
int16_t pwm=50;
int16_t speed;
int main(void)
{
	
	OLED_Init();
	Key_Init();
	Motor_Init();
	Encoder_Init();
	Serial_Init();
	Timer_Init();
	
	
	
	while (1)
	{
		
		OLED_ShowString(1,1,"mode");
		get_flag=key_get();
		if (get_flag)
		{
			OLED_ShowNum(1,6,mode,1);
			mode=!mode;
			
		}
		Motor_SetPWM(pwm);
		OLED_ShowNum(2,1,pwm,5);
		OLED_ShowNum(3,1,speed,5);
		
		
		
	
	}
}
void TIM1_UP_IRQHandler(void)
{
	static uint16_t count;
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) == SET)
	{
		count++;
		//40s进行一次测速，该值需要时间==实践调整
		if (count>=40)
		{
			count=0;
			speed=Encoder_Get();
			
			
		}

		key_tick();
		
		
	
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
	}
		
}

