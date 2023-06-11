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
#include "lcm32f037_dma.h"
/**************************
3路比较器，比较器输出连接到内部的扩展中断和事件控制器，每个中断都有其相应的中断线程，可以产生相应的
中断和事件，进而可以用于低功耗模式的唤醒；
***************************************/

/**************************
DAC0_OUT作为ACMP0输入，或者外部IO引脚;若选择外部输入;
触发外部扩展中断 EXTI 的 LINE19，
********************************************************/
void DAC0_cfg()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_2); //用于观测DAC0_OUT

	DAC_InitTypeDef DAC_InitStruct;
	DAC_InitStruct.DAC_Trigger_Source = DAC_Trigger_Software;
	DAC_InitStruct.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStruct.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
	DAC_InitStruct.DAC_OutputBuffer = DAC0_OutputBuffer_Enable;
	DAC_InitStruct.DAC_Vref_Select = DAC_Vref_Avdd;
	DAC_InitStruct.DAC_EXTrigger_Edge = DAC_EXTrigger_edge_dis;
	DAC_InitStruct.DAC_DmaMode = DISABLE;
	DAC_InitStruct.DAC_DMAUDR_IE = DISABLE;
	DAC_Init(DAC0, &DAC_InitStruct);

	DAC_Cmd(DAC0, ENABLE);
	DAC_SetDac_10B_Data(DAC0, DAC_Align_10B_R, 0x1FF);
	DAC_SoftwareTriggerCmd(DAC0, ENABLE); //软件触发使能；标示触发 DAC 的一次触发传输(选择软件触发条件)
}

void acmp0_cfg()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_6); ////out

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_2); //CP0_P_1[1]

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource0, GPIO_AF_1); ////CP0_N_3[2]

	ACMP_InitTypeDef ACMP_InitStruct;
	ACMP_InitStruct.ACMP_P_Select = CP0_PS_CPP0EXT_INPUT; //比较器正端输入选择
	ACMP_InitStruct.ACMP_N_Select = CP0_NS_DAC0OUT;		  //比较器负端输入选择
	ACMP_InitStruct.ACMP_Delay_time = CP_NODelay_time;	  //输出延迟配置
	ACMP_InitStruct.ACMP_Blanking = CP_NOBLANKING;		  //比较器消隐源选择
	ACMP_InitStruct.ACMP_Is = CP_IS_POS;				  //比较器输出极性
	ACMP_InitStruct.ACMP_HYSEN = DISABLE;				  //迟滞使能配置
	ACMP_InitStruct.ACMP_FREN = ENABLE;					  //快速响应使能
	ACMP_InitStruct.ACMP_FS = DISABLE;					  //输出滤波使能配置

	ACMP_InitStruct.CMP_INTENMASK = ENABLE;				 //比较器连续比较中断使能屏蔽
	ACMP_InitStruct.CMP_SEQ_MODE = DISABLE;				 //连续模式使能
	ACMP_InitStruct.TRIG_MODE = CP_TIRG_INASOFT;		 //触发模式：软件或者外部硬件触发
	ACMP_InitStruct.CHNL_CNT_TIME = CHNL_CNT_TIME_64CLK; //比较器通道切换时钟周期选择

	ACMP0_SEQ_INPUT_SELECT(DISABLE, 5, 2); //选择输入通道：是否连续；正端；负端
	ACMP0_Cmd(ENABLE);

	NVIC_ClearPendingIRQ(LCD_ACMP0_2_IRQn);
	NVIC_EnableIRQ(LCD_ACMP0_2_IRQn);
}

void EXTI_Config()
{
	EXTI_InitTypeDef EXTI_InitStruct;
	EXTI_InitStruct.EXTI_Line = EXTI_Line19;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStruct);
}
int main()
{
	SystemInit();
	SetSysClock();//主频配置
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_ANACTRL, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_EXTI, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);

	EXTI_Config();
	DAC0_cfg();
	acmp0_cfg();
	while (1)
		;
}

void LCD_ACMP0_2_Handler()
{
	EXTI_ClearITPendingBit(EXTI_Line19);
}
