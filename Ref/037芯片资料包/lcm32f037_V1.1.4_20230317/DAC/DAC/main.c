#include "lcm32f037_conf.h"
#include "lcm32f037.h"
#include "lcm32f037_rcc.h"
#include "lcm32f037_gpio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lcm32f037_exti.h"
#include "lcm32f037_dac.h"
/**
  ******************************************************************************
DAC0、DAC1为10位精度，
PA4(AN1)=DAC0_OUT;
PA10(AN2)=DAC0_OUT;

PA5(AN2)=DAC1_OUT;
  ******************************************************************************/

/*********************
	DAC0软件触发
	***********************************************************/
void DAC0_Config()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource4, GPIO_AF_1); // DAC0_OUT

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_2); // DAC0_OUT

	DAC_InitTypeDef DAC_InitStruct;
	DAC_InitStruct.DAC_EXTrigger_Edge = DAC_EXTrigger_edge_dis;			   //触发边沿
	DAC_InitStruct.DAC_Trigger_Source = DAC_Trigger_Software;			   //触发方式
	DAC_InitStruct.DAC_WaveGeneration = DAC_WaveGeneration_None;		   //产生波形配置：无；三角波；噪声波
	DAC_InitStruct.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0; //产生波形幅值
	DAC_InitStruct.DAC_OutputBuffer = DAC0_OutputBuffer_Enable;			   // DAC驱动管使能控制
	DAC_InitStruct.DAC_Vref_Select = DAC_Vref_Avdd;						   //参考源配置
	DAC_InitStruct.DAC_DmaMode = DISABLE;								   // DAC DMA 使能位
	DAC_InitStruct.DAC_DMAUDR_IE = DISABLE;								   // DAC DMA欠载中断使能配置
	DAC_Init(DAC0, &DAC_InitStruct);

	DAC_Cmd(DAC0, ENABLE);
	DAC_SetDac_10B_Data(DAC0, DAC_Align_10B_R, 0x1D1);
	DAC_SoftwareTriggerCmd(DAC0, ENABLE); //软件触发使能；标示触发 DAC 的一次触发传输(选择软件触发条件)
}

/**********************
外部中断线程 1触发DAC1
*********************************************************************/
void DAC_Trigger_GPIO_INIT()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void EXTI_Config()
{
	EXTI_InitTypeDef EXTI_InitStruct;

	EXTI_ConnectTo(GPIOA, EXTI_Line1);

	EXTI_InitStruct.EXTI_Line = EXTI_Line1;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStruct);
	NVIC_ClearPendingIRQ(EXTI0_1_IRQn);
	NVIC_EnableIRQ(EXTI0_1_IRQn);
}
void DAC1_Config()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_2); // DAC1_OUT

	DAC_InitTypeDef DAC_InitStruct;
	DAC_InitStruct.DAC_EXTrigger_Edge = DAC_EXTrigger_Edge_Rising;
	DAC_InitStruct.DAC_Trigger_Source = DAC_Trigger_Ext_IT1;
	DAC_InitStruct.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStruct.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
	DAC_InitStruct.DAC_OutputBuffer = DAC1_OutputBuffer_Enable;
	DAC_InitStruct.DAC_Vref_Select = DAC_Vref_Avdd;
	DAC_InitStruct.DAC_DmaMode = DISABLE;
	DAC_InitStruct.DAC_DMAUDR_IE = DISABLE;
	DAC_Init(DAC1, &DAC_InitStruct);

	DAC_Cmd(DAC1, ENABLE);
	DAC_SetDac_10B_Data(DAC1, DAC_Align_10B_R, 0x136);
}

int main()
{
	SystemInit();
	SetSysClock(); //主频配置
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_EXTI, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_ANACTRL, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	DAC0_Config();

	DAC_Trigger_GPIO_INIT();
	EXTI_Config();
	DAC1_Config();

	while (1)
		;
}
void EXTI0_1_Handler()
{
	EXTI_ClearITPendingBit(EXTI_Line1);
}
