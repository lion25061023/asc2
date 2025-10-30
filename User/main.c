#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"
#include "Timer.h"
#include "Motor.h"
#include "Encoder.h"
#include "Serial.h"
#include "string.h"







//开始pid
float target=0,actual,out;
float kp=0.3,ki=0.1,kd=0.1;
float error0,error1,error2;

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
		//展示模式
		OLED_ShowString(1,1,"mode");
		OLED_ShowNum(1,6,mode,1);
		
		//判断串口输入，算target
		if (Serial_RxFlag==1)
		{
			OLED_ShowString(4,1,Serial_RxPacket);
			if (strlen(Serial_RxPacket)==7)
			{
				target=Serial_RxPacket[6]-48;
			}
			if (strlen(Serial_RxPacket)==8)
			{
				target=(Serial_RxPacket[6]-48)*10+(Serial_RxPacket[7]-48);
			}
			if (strlen(Serial_RxPacket)==9)
			{
				target=(Serial_RxPacket[6]-48)*100+(Serial_RxPacket[7]-48)*10+(Serial_RxPacket[8]-48);
			}
			Serial_RxFlag=0;
			
		}
		
		OLED_ShowString(2,1,"target");
		OLED_ShowNum(2,7,target,3);
		OLED_ShowString(3,1,"actual");
		OLED_ShowNum(3,7,actual,3);
		OLED_ShowString(3,11,"out");
		if (out<100 && out>-100)
		{
			OLED_ShowNum(3,14,out,2);
		}
		else{
			OLED_ShowNum(3,14,out,3);
		}
		
	
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
		
			
			
			//这里写pid
			
			actual=	Encoder_Get();
			error2=error1;
			error1=error0;
			error0=target-actual;
		
			out+=kp*(error0-error1)+ki*error0+kd*(error0-2*error1+error2);
		
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

