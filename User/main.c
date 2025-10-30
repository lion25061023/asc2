#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"
#include "Timer.h"
#include "Motor.h"
#include "Encoder.h"
#include "Serial.h"
#include "string.h"







//mode1参数，开始pid
float target=0,actual,out;
float kp=0.3,ki=0.1,kd=0.1;
float error0,error1,error2;
//mode2 参数

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
		if (mode==0)
		{
			//判断串口输入，算target
			if (Serial_RxFlag==1)
			{
				OLED_ShowString(4,1,Serial_RxPacket);
				if (Serial_RxPacket[5]=='t' && Serial_RxPacket[6]!='-')
				{
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
				}
				else if (Serial_RxPacket[5]=='t' && Serial_RxPacket[6]=='-')
				{
					if (strlen(Serial_RxPacket)==8)
					{
						target=Serial_RxPacket[7]-48;
						target=-target;
					}
					if (strlen(Serial_RxPacket)==9)
					{
						target=(Serial_RxPacket[7]-48)*10+(Serial_RxPacket[8]-48);
						target=-target;
					}
					if (strlen(Serial_RxPacket)==10)
					{
						target=(Serial_RxPacket[7]-48)*100+(Serial_RxPacket[8]-48)*10+(Serial_RxPacket[9]-48);
						target=-target;
					}
				}
			
				Serial_RxFlag=0;
			
			}
		
	
		
		
	
		Serial_Printf("%f,%f,%f\r\n",target,actual,out);
		
		}
		else if (mode==1)
		{
			Motor_SetPWM(50);
			Moter_SetPWM_B(200);
		}
		
		
		
	
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
		
			
			
			if (mode==0)
			{
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
			
			else if (mode==1)
			{
				
			}

		}
			
		key_tick();
		
		
	
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
	}
		
}

