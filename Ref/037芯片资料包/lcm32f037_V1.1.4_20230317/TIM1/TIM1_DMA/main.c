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
/***********
TIM1��PWM���������������ţ������ڴ�������ģ�飬����ADC��
�ɸ��������Լ�����CHx��CHxN�ĵ�ƽͬ�����
********************************************************************************8*/
uint16_t TimerPeriod = 0;
uint16_t Channel1Pulse = 0, Channel2Pulse = 0, Channel3Pulse = 0, Channel4Pulse = 0;

#define DMA_ENABLE 1
#define TIM1_CCR4_Address (0x40010040)
unsigned int tim1RawData = 400;

void GPIO_Config()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_2); // tim1_ch4   pA11

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void TIM_DMA_CFG(void)
{

	DMA_InitTypeDef DMA_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA, ENABLE);

	/*DMA1 channel1 configuration ----------------------------------------------*/
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&tim1RawData;
	;																		//��������DMA������������ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = TIM1_CCR4_Address;				//�ڴ����ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;						//�������ݴ��䷽�򣬼������Ǵ������ȡ���ݵ��ڴ滹�Ǵ��ڴ�����ݵ����裬���������Ǵ�����ADC_DR�Ĵ��������ݵ��ڴ�
	DMA_InitStructure.DMA_BufferSize = 1;									//����һ�δ����������Ĵ�С
	DMA_InitStructure.DMA_MSIZE = DMA_MSIZE_1;								//ͻ�������䳤��
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;		//���ô������ݵ�ʱ�� �����裩 ��ַ�ǲ��仹�ǵ�����
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;				//���ô������ݵ�ʱ�� ���ڴ� ����ַ�ǲ��仹�ǵ���
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word; //������������ݳ�����Ϊ�ֽڴ��䣨8bits�����ǰ��֣�16bits�������ִ��䣨32bits��
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;			//�����ڴ�����ݳ��ȣ�ͬ�ϡ�
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;							//�����Ƿ����ѭ���ɼ�
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;						//�������ȼ�
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure); //�����Ƿ��Ǵ洢�����洢��ģʽ����
	/* Enable DMA1 channel1 TC interupt*/
	DMA_ITConfig(DMA1_Channel1, DMA1_FLAG_TC1, ENABLE); //����DMA������ɺ��ж�
	DMA_RemapConfig(DMA1_Channel1, DMA_ReqNum5, DMA_REQ_TIM1_CH4);
	/* Enable DMA1 channel1 */
	DMA_Cmd(DMA1_Channel1, ENABLE);
}

static void tim1_cfg_init()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	TimerPeriod = 1000;
	Channel1Pulse = 100;
	Channel2Pulse = 200;
	Channel3Pulse = 300;
	Channel4Pulse = 400;

	/* Time Base configuration */
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = TimerPeriod;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;

	TIM_OCInitStructure.TIM_Pulse = Channel1Pulse;
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_Pulse = Channel2Pulse;
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_Pulse = Channel3Pulse;
	TIM_OC3Init(TIM1, &TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_Pulse = Channel4Pulse;
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);
	TIM_CtrlPWMOutputs(TIM1, ENABLE);

	TIM_ITConfig(TIM1, TIM_DIER_TDE | TIM_DIER_CC4DE, ENABLE); // tim dmaʹ��
	TIM_Cmd(TIM1, ENABLE);
}

int main()
{
	SystemInit();
	SetSysClock(); //��Ƶ����
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM1, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);

	NVIC_ClearPendingIRQ(DMAC_CH1_2_IRQn);
	NVIC_EnableIRQ(DMAC_CH1_2_IRQn);
	GPIO_Config(); // PWM GPIOSET
	TIM_DMA_CFG();
	tim1_cfg_init(); // TIM1 SET
	GPIO_ResetBits(GPIOA, GPIO_Pin_12);
	while (1)
		;
}

void DMAC_CH1_2_Handler(void) // 40us
{
	GPIO_SetBits(GPIOA, GPIO_Pin_12);
	tim1RawData = tim1RawData - 50;
	if (tim1RawData < 50)
		tim1RawData = 400;
	GPIO_ResetBits(GPIOA, GPIO_Pin_12);
	DMA_ClearITPendingBit(DMA1_FLAG_TC1);
}
