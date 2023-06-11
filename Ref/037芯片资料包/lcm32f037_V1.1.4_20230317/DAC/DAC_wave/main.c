#include "lcm32f037_conf.h"
#include "lcm32f037.h"
#include "lcm32f037_rcc.h"
#include "lcm32f037_gpio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lcm32f037_exti.h"
#include "lcm32f037_dac.h"
#include "lcm32f037_tim.h"
/**
  ******************************************************************************
demo��������TIM1_TRGO����DAC0�������ǲ�������DAC1������������
ԭ��
   ÿ��Ӳ�������¼�֮��3��APB1ʱ�����ں��ۼ�1����������ֵ��DAC_DHRx�Ĵ�������ֵ��Ӳ��������λ��д��DAC_DORx�Ĵ�����
�ڴ���DAC_DORx�Ĵ�������ֵС��MAMP[3:0]λ�����������ʱ�����ǲ����������ۼӡ�һ���ﵽ���õ������ȣ����������ʼ�ݼ���
�ﵽ0���ٿ�ʼ�ۼӣ��ܶ���ʼ��

�������ǲ�Ƶ�ʼ��㷽ʽ=����ԴƵ��/���ǲ���������ֵ/2
  ******************************************************************************/
uint16_t TimerPeriod = 0;
uint16_t Channel1Pulse = 0, Channel2Pulse = 0, Channel3Pulse = 0, Channel4Pulse = 0;

void tim1_cfg_init()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStruct;

	TimerPeriod = 800;	 // 16000000/20000;
	Channel1Pulse = 400; // TimerPeriod/2;
	Channel2Pulse = 400; // TimerPeriod/2;
	Channel3Pulse = 400; // TimerPeriod/2;
	Channel4Pulse = 400; // TimerPeriod/2;

	/* Time Base configuration */
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = TimerPeriod;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

	/* Channel 1, 2,3 and 4 Configuration in PWM mode */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OCInitStructure.TIM_Pulse = Channel1Pulse;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;

	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);
	TIM_OC3Init(TIM1, &TIM_OCInitStructure);
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);

	/* Enables the TIM1 Preload on CC1,CC2,CC3,CC4 Register */
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);

	TIM_SelectOutputTrigger(TIM1, TIM_TRGOSource_Update); //ѡ��TRGO�������Դ

	TIM_CtrlPWMOutputs(TIM1, ENABLE); //����TRGO����ADC�ɲ���Ҫʹ�ܣ�����ͨ��CCx����,��ͨ��IO�۲�PWM���Σ�����ʹ�ܣ�

	TIM_Cmd(TIM1, ENABLE);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_2); // tim1_ch1   pA8
}
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
	DAC_InitStruct.DAC_EXTrigger_Edge = DAC_EXTrigger_Edge_Rising;
	DAC_InitStruct.DAC_Trigger_Source = DAC_Trigger_T1_TRGO;
	DAC_InitStruct.DAC_WaveGeneration = DAC_WaveGeneration_Triangle;
	DAC_InitStruct.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bits7_0;
	DAC_InitStruct.DAC_OutputBuffer = DAC0_OutputBuffer_Enable;
	DAC_InitStruct.DAC_Vref_Select = DAC_Vref_Avdd;
	DAC_InitStruct.DAC_DmaMode = DISABLE;
	DAC_InitStruct.DAC_DMAUDR_IE = DISABLE;
	DAC_Init(DAC0, &DAC_InitStruct);

	DAC_Cmd(DAC0, ENABLE);
}
/***************
demo��������TIM1_TRGO����DAC1������������
************************************************************/
void DAC1_Config()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_2); // DAC0_OUT

	DAC_InitTypeDef DAC_InitStruct;
	DAC_InitStruct.DAC_EXTrigger_Edge = DAC_EXTrigger_Edge_Rising;
	DAC_InitStruct.DAC_Trigger_Source = DAC_Trigger_T1_TRGO;
	DAC_InitStruct.DAC_WaveGeneration = DAC_WaveGeneration_Noise;
	DAC_InitStruct.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bits7_0;
	DAC_InitStruct.DAC_OutputBuffer = DAC1_OutputBuffer_Enable;
	DAC_InitStruct.DAC_Vref_Select = DAC_Vref_Avdd;
	DAC_InitStruct.DAC_DmaMode = DISABLE;
	DAC_InitStruct.DAC_DMAUDR_IE = DISABLE;
	DAC_Init(DAC1, &DAC_InitStruct);
	DAC_Cmd(DAC1, ENABLE);
}
int main()
{
	SystemInit();
	SetSysClock(); //��Ƶ����

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_ANACTRL, ENABLE); //��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM1, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	tim1_cfg_init();
	DAC0_Config();
	DAC1_Config();
	while (1)
		;
}
