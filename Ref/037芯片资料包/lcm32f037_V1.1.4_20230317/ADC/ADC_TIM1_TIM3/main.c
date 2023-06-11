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
#include "lcm32f037_dma.h"
#include "lcm32f037_flash.h"
#include "lcm32f037_dac.h"
/*****************
demoΪTIM1��TIM3��������������TIM1��ɲ�����������ƼĴ���BDTR������Ҫ����PWMOUTλ��TIM3���ã�

TRGO����Ϊ�¼��ź�����������񣬻���PWM���������ΪTRGO�źŴ�������ģ�顣
TIMɲ��ʱ��PWM���������������ͨ����Ϊ������ɲ��ʱADC��������
�����������ʹ��TRGO�ź���ΪADC����Դ
***********************************************************************************************/
uint16_t TimerPeriod = 0;
uint16_t Channel1Pulse = 0, Channel2Pulse = 0, Channel3Pulse = 0, Channel4Pulse = 0;
uint32_t datad;

void GPIOConfiguration(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_1); // PA0=ADCIN[0]

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_2); // tim1_ch1   pA8

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_1); // tim3_ch1   pA6
}

void tim1_cfg_init()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

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
}

void tim3_cfg_init()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

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
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	/* Channel 1, 2,3 and 4 Configuration in PWM mode */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OCInitStructure.TIM_Pulse = Channel1Pulse;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;

	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);

	/* Enables the TIM1 Preload on CC1,CC2,CC3,CC4 Register */
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);

	TIM_SelectOutputTrigger(TIM3, TIM_TRGOSource_Update); //ѡ��TRGO�������Դ

	TIM_Cmd(TIM3, ENABLE);
}

void ADCConfiguration(void)
{
	ADC_InitTypeDef ADC_InitStructure;

	ADC_InitStructure.ADC_ClkMode = ADC_ClockMode_sysnClk;						  //ѡ��ת��ʱ��Դ
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;						  //����
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;							  //ת��ģʽ0=����;1=����;��ʾ����һ��ת��һ��ͨ������һ������
	ADC_InitStructure.ADC_AutoWatiMode = ENABLE;								  //��λ��������ú������ʹ���� / �ر��Զ��ӳ�ת��ģʽ
	ADC_InitStructure.ADC_DMATRIG_LEVEL = FIFO_DMA_NOEMPTY;						  //������ô��� DMA ����� FIFO ˮƽ���� DMAEN ʹ��ǰ�������ã�������� DMA �ڰ���ʱ�Ĵ���
	ADC_InitStructure.ADC_DMA = DISABLE;										  //�Ƿ������� DMA ���������Զ�����ת���Ľ������
	ADC_InitStructure.ADC_DiscMode = DISABLE;									  // 0=����ģʽ��ֹ;1=����ģʽ����
	ADC_InitStructure.ADC_SamecMode = DISABLE;									  //����ģʽѡ��0=��������;1=ͬʱ����
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_Rising; //������ʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T3_CC4;		  //����Դ
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;						  //���ݶ��뷽ʽ
	ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;				  // 0=��ǰɨ�� (�� CHSEL0 �� CHSEL15);1=���ɨ��( �� CHSEL15 �� CHSEL0)
	ADC_InitStructure.ADC_Vref = ADC_Vref_Internal_3V3;							  //�ο���ѹѡ��
	ADC_Init(ADC, &ADC_InitStructure);

	ADC_ChannelConfig(ADC, ADC_Channel_0, 15, 7, 7); //����ͨ����CONVERT��ADJUST,SMP
	ADC_Cmd(ADC, ENABLE);
}

int main()
{
	SystemInit();
	SetSysClock(); //��Ƶ����

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_ADC, ENABLE); //��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM1, ENABLE);
	RCC_APB0PeriphClockCmd(RCC_APB0Periph_TIM3, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	tim1_cfg_init();
	tim3_cfg_init();

	GPIOConfiguration(); // GPIO����
	ADCConfiguration();	 // ADC��ʼ��

	ADC_StartOfConversion(ADC1); // ADC ��ʼת������
	while (1)
	{
		datad = ADC_GetConversionValue(ADC1);
	}
}
