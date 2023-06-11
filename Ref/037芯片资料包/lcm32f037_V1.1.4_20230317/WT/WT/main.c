#include "lcm32f037_conf.h"
#include "lcm32f037.h"
#include "lcm32f037_rcc.h"
#include "lcm32f037_flash.h"
#include "lcm32f037_gpio.h"
#include "lcm32f037_uart.h"
#include "lcm32f037_exti.h"
#include "lcm32f037_wt.h"
/**
 ******************************************************************************
 * @function: wt定时器、WT_BUZ
 * @attention:
 ******************************************************************************/
void GPIO_Config()
{

	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8; // PA8观测
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_0);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource4, GPIO_AF_5); // WT_BUZ   pA4
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_5); // WT_nBUZ   pA5
}

void WT_Cfg()
{
	WT_InitTypeDef WT_InitStruct;

	RCC_LSICmd(ENABLE);					  //使能内部RCL
	RCC_WTCLKConfig(RCC_WTCLKSource_LSI); //设置WT时钟(WTCLK),选择LSI作为WT时钟
	RCC_WTCLKCmd(ENABLE);				  // 使能WT时钟

	WT_SetCounter(WT, 0X55); //递减计数，设置T8值

	WT_InitStruct.WT_BZOUT = WT_BZOUT_Hight;			  //蜂鸣器输出高低频率选择
	WT_InitStruct.WT_Interrupt = WT_Interrupt_T8DOWN;	  // WT中断源选择
	WT_InitStruct.WT_Outfrequency = WT_Outfrequency_1024; //蜂鸣器输出频率选择
	WT_InitStruct.WT_T8frequency = WT_T8frequency_4096;	  // T8定时器时钟源选择
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
void OSCL_Init()
{
	OSCH_GPIO_INIT(); //晶振脚复用
	chipctrl_access();
	CHIPCTRL->BDCR_b.OSCL_EN = 1; //设置外部低速晶振(LSE),使用外设低速晶振
	__dekey();
	while (!(CHIPCTRL->STS & CHIPCTRL_STS_OSCL_STB_Msk)) //等待低速晶振就绪
		;
}
int main()
{
	SystemInit();
	SetSysClock(); //主频配置
	//	OSCL_Init();

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_EXTI, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	GPIO_Config();
	mco_set(4, 0); // PA8输出OSCL

	EXTI_Config();
	WT_Cfg();
	while (1)
		;
}

void WT_Handler(void)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_12, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_12)));
	WT_ClearITPendingBit(WT_FLAG_IT);
	EXTI_ClearITPendingBit(EXTI_Line17);
}
