#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#define up 1
#define down 0

/**
  * 函    数：按键初始化
  * 参    数：无
  * 返 回 值：无
  */
uint8_t mode;
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
uint16_t current;
uint16_t previous;
void key_tick(void)
{
	static uint8_t count;
	count++;
	if (count>=10)
	{
		count=0;
		previous=current;
		current=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
		if (current==up && previous==down)
		{
			mode=!mode;
		}
	
			
		
		
	}
}


