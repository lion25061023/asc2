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


//开始pid
float target=300.0,actual,out;
float kp=0.5,ki=0.1,kd=0;
float error0,error1,errorint;

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
		
		
		
		OLED_ShowNum(2,1,pwm,5);
		OLED_ShowNum(3,1,actual,5);
		Serial_Printf("%f,%f,%f\r\n",target,actual,out);
		
		
		
	
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
			
			
			//这里写pid
			actual=speed;
			error1=error0;
			error0=target-actual;
			errorint+=error0;
			out=kp*error0+ki*errorint+kd*(error0-error1);
		
			if (out>100)
			{
				out=100;
			}
			if (out<-100)
			{
				out=-100;
			}
			Motor_SetPWM(out);
			
			
		}

		key_tick();
		
		
	
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
	}
		
}

