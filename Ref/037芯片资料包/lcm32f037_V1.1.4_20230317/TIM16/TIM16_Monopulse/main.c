#include "lcm32f037_conf.h"
#include "lcm32f037.h"
#include "lcm32f037_rcc.h"
#include "lcm32f037_uart.h"
#include "lcm32f037_gpio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lcm32f037_div.h"
#include "lcm32f037_tim.h"
#include "lcm32f037_acmp.h"
#include "lcm32f037_dac.h"
#include "lcm32f037_exti.h"
/***********
单脉冲表示只有一个周期的PWM；产生一个周期的PWM后计数停止，可手动打开，或使用TI2触发
demo配置，通道1输出单脉冲；
单脉冲模式：
增计数模式：延时时间 = TIM_CCR1 - 0   脉冲宽度 =  TIM_ARR - TIM_CCR1
减计数模式：延时时间 = TIM_ARR - TIM_CCR1    脉冲宽度 = TIM_CCR1 - 0
***************************************************************************/
void delay(uint32_t dly)
{
	volatile uint32_t i = 0;
	while (i++ < dly)
		;
}
void GPIO_Config()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_3); // tim16_ch1   pA0
}

static void tim16_cfg_init()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_TimeBaseStructure.TIM_Period = 2000;					//定时器周期值
	TIM_TimeBaseStructure.TIM_Prescaler = 16 - 1;				//预分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;				//时钟不分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //增计数模式
	TIM_TimeBaseInit(TIM16, &TIM_TimeBaseStructure);			//初始化定时器时基

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_Pulse = 1500;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	TIM_OC1Init(TIM16, &TIM_OCInitStructure);

	TIM_SelectOnePulseMode(TIM16, TIM_OPMode_Single); //选择定时器为单脉冲模式
	TIM_CtrlPWMOutputs(TIM16, ENABLE);
	TIM_Cmd(TIM16, ENABLE);
}

int main()
{
	SystemInit();
	SetSysClock(); //主频配置
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM16, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	GPIO_Config(); // PWM GPIOSET
	tim16_cfg_init();

	while (1)
	{
		delay(100);
		TIM_Cmd(TIM16, ENABLE); //产生一个周期的PWM后计数停止，需要手动打开
	}
}
