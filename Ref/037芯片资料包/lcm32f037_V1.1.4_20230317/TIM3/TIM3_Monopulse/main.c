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
demo配置，通道2捕获，通道1输出单脉冲；
单脉冲模式：
增计数模式：延时时间 = TIM_CCR1 - 0   脉冲宽度 =  TIM_ARR - TIM_CCR1
减计数模式：延时时间 = TIM_ARR - TIM_CCR1    脉冲宽度 = TIM_CCR1 - 0
***************************************************************************/

void GPIO_Config()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_1); // tim3_ch1   pA6

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_1); // tim3_ch2   pA7
}

static void tim3_cfg_init()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_TimeBaseStructure.TIM_Period = 2000;					//定时器周期值
	TIM_TimeBaseStructure.TIM_Prescaler = 16 - 1;				//预分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;				//时钟不分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //增计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);				//初始化定时器时基

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //可配置强制输出模式，具体详见寄存器TIM3->CCMR1的OC1M[2:0]
	TIM_OCInitStructure.TIM_Pulse = 1500;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCNPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);

	TIM_ICStructInit(&TIM_ICInitStructure);							//初始化输入捕获结构体
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;				// TIM3 CH2 配置为输入捕获模式
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;		//上升沿捕获
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //管教与寄存器直接对应
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;			//不与分频
	TIM_ICInitStructure.TIM_ICFilter = 0;							//不滤波
	TIM_ICInit(TIM3, &TIM_ICInitStructure);							//初始化TIM3 CH2

	TIM_SelectOnePulseMode(TIM3, TIM_OPMode_Single); //选择定时器为单脉冲模式
	TIM_DTS_Cfg(TIM3);
	TIM_TI2E_Set(TIM3);
	TIM_SelectInputTrigger(TIM3, TIM_TS_TI2FP2);	  //选择触发源为IC2
	TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Trigger); //选择定时器从模式为上升沿触发
	TIM_CtrlPWMOutputs(TIM3, ENABLE);

	TIM_Cmd(TIM3, ENABLE);
}

int main()
{
	SystemInit();
	SetSysClock(); //主频配置
	RCC_APB0PeriphClockCmd(RCC_APB0Periph_TIM3, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	GPIO_Config();	 // PWM GPIOSET
	tim3_cfg_init(); // TIM3 SET

	while (1)
		;
}
