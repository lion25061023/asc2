#include "stm32f10x.h"                  // Device header

void Encoder_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructurea;
	GPIO_InitStructurea.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructurea.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructurea.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructurea);
	
	GPIO_InitTypeDef GPIO_InitStructureb;
	GPIO_InitStructureb.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructureb.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructureb.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructureb);
		
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1;		//ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 1 - 1;		//PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);
	
	TIM_ICInitTypeDef TIM_ICInitStructurea;
	TIM_ICStructInit(&TIM_ICInitStructurea);
	TIM_ICInitStructurea.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructurea.TIM_ICFilter = 0xF;
	TIM_ICInit(TIM3, &TIM_ICInitStructurea);
	TIM_ICInitStructurea.TIM_Channel = TIM_Channel_2;
	TIM_ICInitStructurea.TIM_ICFilter = 0xF;
	TIM_ICInit(TIM3, &TIM_ICInitStructurea);
	
	TIM_ICInitTypeDef TIM_ICInitStructureb;
	TIM_ICStructInit(&TIM_ICInitStructureb);
	TIM_ICInitStructureb.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructureb.TIM_ICFilter = 0xF;
	TIM_ICInit(TIM4, &TIM_ICInitStructureb);
	TIM_ICInitStructureb.TIM_Channel = TIM_Channel_2;
	TIM_ICInitStructureb.TIM_ICFilter = 0xF;
	TIM_ICInit(TIM4, &TIM_ICInitStructureb);
	
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	
	TIM_Cmd(TIM3, ENABLE);
	TIM_Cmd(TIM4, ENABLE);
}

int16_t Encoder_Get(void)
{
	int16_t Temp;
	Temp = TIM_GetCounter(TIM3);
	TIM_SetCounter(TIM3, 0);
	return Temp;
}


int16_t Encoder_Get_B(void)
{
	int16_t Temp;
	Temp = TIM_GetCounter(TIM4);
	TIM_SetCounter(TIM4, 0);
	return Temp;
}

