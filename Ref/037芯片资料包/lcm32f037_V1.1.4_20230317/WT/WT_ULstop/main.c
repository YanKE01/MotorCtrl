#include "lcm32f037_conf.h"
#include "lcm32f037.h"
#include "lcm32f037_rcc.h"
#include "lcm32f037_flash.h"
#include "lcm32f037_gpio.h"
#include "lcm32f037_uart.h"
#include "lcm32f037_exti.h"
#include "lcm32f037_wt.h"
#include "lcm32f037_pwr.h"
/**
 ******************************************************************************
 * @function: wt定时器、WT_BUZ
 * @attention:
 ******************************************************************************/
void delay(uint32_t dly)
{
	volatile uint32_t i = 0;
	while (i++ < dly)
		;
}

void GPIO_Config()
{
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11; // PA11
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; // PA0/PA1观测用
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = 0x97FC;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOF, &GPIO_InitStruct);
}

void WT_Cfg()
{
	WT_InitTypeDef WT_InitStruct;

	RCC_LSICmd(ENABLE);					  //使能内部RCL
	RCC_WTCLKConfig(RCC_WTCLKSource_LSI); //设置WT时钟(WTCLK),选择LSI作为WT时钟
	RCC_WTCLKCmd(ENABLE);				  // 使能WT时钟

	WT_SetCounter(WT, 0XBF); //递减计数，设置T8值

	WT_InitStruct.WT_BZOUT = WT_BZOUT_Hight;			  //蜂鸣器输出高低频率选择
	WT_InitStruct.WT_Interrupt = WT_Interrupt_T8DOWN;	  // WT中断源选择
	WT_InitStruct.WT_Outfrequency = WT_Outfrequency_1024; //蜂鸣器输出频率选择
	WT_InitStruct.WT_T8frequency = WT_T8frequency_64;	  // T8定时器时钟源选择
	WT_InitStruct.WT_T8State = WT_T8State_Enable;		  // T8定时器使能
	WT_InitStruct.WT_WTState = WT_WTState_Enable;		  // WT使能位
	WT_Init(WT, &WT_InitStruct);
}

void EXTI_Config()
{
	EXTI_InitTypeDef EXTI_InitStruct;

	EXTI_InitStruct.EXTI_Line = EXTI_Line17;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStruct);

	NVIC_ClearPendingIRQ(WT_IRQn);
	NVIC_EnableIRQ(WT_IRQn);
}
uint8_t PWR_FLG;
int main()
{
	SystemInit();
	SetSysClock(); //主频配置

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_EXTI, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);

	GPIO_Config();
	EXTI_Config();
	WT_Cfg();
	PWR_FLG = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11);
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	if (PWR_FLG == 0) // PA11接地，上电复位或者硬件复位后进入低功耗模式
	{
		PWR_LPVRConfig(PWR_VSEL_1V);
		PWR_EnterUR_STOPMode(0, PWR_STOPEntry_WFI);
	}
	while (1)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_0);
		delay(1000);
		GPIO_ResetBits(GPIOA, GPIO_Pin_0);
		delay(1000);
	}
}

void WT_Handler(void)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_1, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_1)));
	WT_ClearITPendingBit(WT_FLAG_IT);
	EXTI_ClearITPendingBit(EXTI_Line17);
}
