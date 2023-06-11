#include "lcm32f037_conf.h"
#include "lcm32f037.h"
#include "lcm32f037_rcc.h"
#include "lcm32f037_gpio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lcm32f037_iwdg.h"

void delay(uint32_t dly)
{
	volatile uint32_t i = 0;
	while (i++ < dly)
		;
}

void GPIO_Config()
{
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}

int main()
{
	SystemInit();
	SetSysClock(); // 主频配置
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	GPIO_Config();

	GPIO_SetBits(GPIOA, GPIO_Pin_11);
	delay(50000);
	GPIO_ResetBits(GPIOA, GPIO_Pin_11);
	delay(50000); // 复位指示脉冲
	/*------------IWDG-----------*/

	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable); // 解除IWDG写保护
	IWDG_SetPrescaler(IWDG_Prescaler_16);		  // 分频系数  rcl32k作为来源
	IWDG_SetReload(0xBBB);
	while (IWDG->SR)
		;
	IWDG_Enable();
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Disable); // 恢复IWDG写保护

	while (1)
	{
		IWDG_ReloadCounter(); // 喂狗
		delay(50000);
	}
}
