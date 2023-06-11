#include "lcm32f037_conf.h"
#include "lcm32f037.h"
#include "lcm32f037_rcc.h"
#include "lcm32f037_gpio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*******************************
推挽强驱
********************************/

void GPIO_INIT() // IO初始化
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_Init(GPIOA, &GPIO_InitStructure);									   //初始化
	GPIO_DriveConfig(GPIOA, GPIO_Pin_0 | GPIO_Pin_1, GPIO_Drive_Level_strong); //强驱模式
	GPIO_DriveConfig(GPIOA, GPIO_Pin_2, GPIO_Drive_Level_strong);			   //强驱模式
}

int main()
{
	SystemInit();
	SetSysClock(); //主频配置
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	GPIO_INIT();
	while (1)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_0);
		GPIO_SetBits(GPIOA, GPIO_Pin_1);
		GPIO_SetBits(GPIOA, GPIO_Pin_2);
	}
}
