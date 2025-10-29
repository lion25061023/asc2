#include "stm32f10x.h"                  // Device header
#include "Delay.h"

/**
  * 函    数：按键初始化
  * 参    数：无
  * 返 回 值：无
  */
void Key_Init(void)
{
	/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		//开启GPIOA的时钟
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);						
} 
uint8_t mode_flag;
void key_tick(void)
{
	static uint8_t count;
	count++;
	if (count>=50)
	{
		count=0;
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0)
		{
			mode_flag=1;
		}
		
	}
}
uint8_t key_get(void)
{
	uint8_t temp=mode_flag;
	mode_flag=0;
	
	return temp;
}

