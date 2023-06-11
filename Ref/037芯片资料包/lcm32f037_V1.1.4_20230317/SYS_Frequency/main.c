#include "lcm32f037_conf.h"
#include "lcm32f037.h"
#include "lcm32f037_rcc.h"
#include "lcm32f037_gpio.h"
/*******************************
高频配置方式
********************************/

void GPIO_INIT() // IO初始化
{
	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_0);
}
/*72M以上主频配置方式根据实际需要选择下述两种方式其一;
72M一下主频配仅调用SystemInit()即可
主频宏定义选择方式照旧*/
int main()
{
	SystemInit();
	SetSysClock(); //主频配置
	GPIO_INIT();
	RCC_MCOConfig(RCC_MCOSource_SYSCLK, RCC_MCOPrescaler_8); //主频观测,8分频
	while (1)
		;
}
