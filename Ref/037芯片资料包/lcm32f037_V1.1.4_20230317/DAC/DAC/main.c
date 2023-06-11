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
DAC0��DAC1Ϊ10λ���ȣ�
PA4(AN1)=DAC0_OUT;
PA10(AN2)=DAC0_OUT;

PA5(AN2)=DAC1_OUT;
  ******************************************************************************/

/*********************
	DAC0�������
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
	DAC_InitStruct.DAC_EXTrigger_Edge = DAC_EXTrigger_edge_dis;			   //��������
	DAC_InitStruct.DAC_Trigger_Source = DAC_Trigger_Software;			   //������ʽ
	DAC_InitStruct.DAC_WaveGeneration = DAC_WaveGeneration_None;		   //�����������ã��ޣ����ǲ���������
	DAC_InitStruct.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0; //�������η�ֵ
	DAC_InitStruct.DAC_OutputBuffer = DAC0_OutputBuffer_Enable;			   // DAC������ʹ�ܿ���
	DAC_InitStruct.DAC_Vref_Select = DAC_Vref_Avdd;						   //�ο�Դ����
	DAC_InitStruct.DAC_DmaMode = DISABLE;								   // DAC DMA ʹ��λ
	DAC_InitStruct.DAC_DMAUDR_IE = DISABLE;								   // DAC DMAǷ���ж�ʹ������
	DAC_Init(DAC0, &DAC_InitStruct);

	DAC_Cmd(DAC0, ENABLE);
	DAC_SetDac_10B_Data(DAC0, DAC_Align_10B_R, 0x1D1);
	DAC_SoftwareTriggerCmd(DAC0, ENABLE); //�������ʹ�ܣ���ʾ���� DAC ��һ�δ�������(ѡ�������������)
}

/**********************
�ⲿ�ж��߳� 1����DAC1
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
	SetSysClock(); //��Ƶ����
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
