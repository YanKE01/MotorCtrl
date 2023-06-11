#include "lcm32f037_conf.h"
#include "lcm32f037.h"
#include "lcm32f037_rcc.h"
#include "lcm32f037_uart.h"
#include "lcm32f037_gpio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lcm32f037_div.h"
#include "lcm32f037_adc.h"
#include "lcm32f037_opa.h"
#include "lcm32f037_tim.h"
#include "lcm32f037_pwr.h"
#include "lcm32f037_dac.h"
#include "lcm32f037_dma.h"
/***********************
OPA0配置正端PA9，负端通过NIN选择PA8
**********************************************/
void OPA0_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	//OPA0
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_2);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_2); //正端输入

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_2); //opa0输出到PA3 可以测量

	OPA_InitTypeDef OPA_InitStruct;
	OPA_InitStruct.OPA_Oppselect = OPA0_Oppselect_PA9;
	OPA_InitStruct.OPA_Opnselect = OPA0_Opnselect_NIN; //负端通过NIN选择
	OPA_InitStruct.OPA_Gain = OPA_Gain_10;
	OPA_InitStruct.OPA_BiasVoltage = OPA_BiasVoltage_DISEN;
	OPA_InitStruct.OPA_FeedbackRes = OPA_FeedbackRes_EN;
	OPA_InitStruct.OPA_Opoto_Gpio = OPA_OPOEX_DISEN;
	OPA_InitStruct.OPA_OppRES_short = OPA_OppRES_short_DISEN;
	OPA_InitStruct.OPA_OpnRES_short = OPA_OpnRES_short_DISEN;
	OPA_InitStruct.OPA_BiasVoltageSource = OPA_OPA_BiasVoltageSource_HALFVRH;
	OPA_NINSelect(OPA_NINselect_PA8); //通过NIN选择负端输入
	OPA_Init(OPA0, &OPA_InitStruct);

	OPA_Cmd(OPA0, ENABLE);
}
/***********************
OPA1配置正端PA6，负端选择PF1
**********************************************/
void OPA1_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	//	//OPA1
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOF, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource1, GPIO_AF_1);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_2); //正端输入

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_2); //opa1输出到PA7 可以测量

	OPA_InitTypeDef OPA_InitStruct;
	OPA_InitStruct.OPA_Oppselect = OPA1_Oppselect_PA6;
	OPA_InitStruct.OPA_Opnselect = OPA1_Opnselect_PF1;
	OPA_InitStruct.OPA_Gain = OPA_Gain_10;
	OPA_InitStruct.OPA_BiasVoltage = OPA_BiasVoltage_DISEN;
	OPA_InitStruct.OPA_FeedbackRes = OPA_FeedbackRes_EN;
	OPA_InitStruct.OPA_Opoto_Gpio = OPA_OPOEX_DISEN;
	OPA_InitStruct.OPA_OppRES_short = OPA_OppRES_short_DISEN;
	OPA_InitStruct.OPA_OpnRES_short = OPA_OpnRES_short_DISEN;
	OPA_InitStruct.OPA_BiasVoltageSource = OPA_OPA_BiasVoltageSource_HALFVRH;
	OPA_Init(OPA1, &OPA_InitStruct);
	OPA_Cmd(OPA1, ENABLE);
}
/***********************
OPA2配置正端PA5，负端选择PB7
**********************************************/
void OPA2_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	//OPA2
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_2);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_1); //正端输入

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource1, GPIO_AF_2); //opa2输出到PB1 可以测量

	OPA_InitTypeDef OPA_InitStruct;
	OPA_InitStruct.OPA_Oppselect = OPA2_Oppselect_PA5;
	OPA_InitStruct.OPA_Opnselect = OPA2_Opnselect_PB7;
	OPA_InitStruct.OPA_Gain = OPA_Gain_10;
	OPA_InitStruct.OPA_BiasVoltage = OPA_BiasVoltage_DISEN;
	OPA_InitStruct.OPA_FeedbackRes = OPA_FeedbackRes_EN;
	OPA_InitStruct.OPA_Opoto_Gpio = OPA_OPOEX_DISEN;
	OPA_InitStruct.OPA_OppRES_short = OPA_OppRES_short_DISEN;
	OPA_InitStruct.OPA_OpnRES_short = OPA_OpnRES_short_DISEN;
	OPA_InitStruct.OPA_BiasVoltageSource = OPA_OPA_BiasVoltageSource_HALFVRH;
	OPA_Init(OPA2, &OPA_InitStruct);
	OPA_Cmd(OPA2, ENABLE);
}

int main()
{
	RCC_DeInit();
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_ANACTRL, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);

	OPA0_Init(); // PA3(OUT) PA9(P)  PA8(N)

	OPA1_Init(); // PA7(OUT) PA6(P)  PF1(N)

	OPA2_Init(); // PB1(OUT) PA5(P)  PB7(N)

	while (1)
		;
}
