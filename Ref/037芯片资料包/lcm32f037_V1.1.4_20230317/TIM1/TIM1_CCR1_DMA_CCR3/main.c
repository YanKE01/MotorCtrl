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
TIM1_DMA 将CCR1的数据通过DMA搬运到CCR3
********************************************************************************8*/

#define TIM1_CCR1_Address (0x40010034)
#define TIM1_CCR2_Address (0x40010038)
#define TIM1_CCR3_Address (0x4001003C)
#define TIM1_CCR4_Address (0x40010040)

void GPIO_Config()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_2); // tim1_ch1   pA8
}
//使用DMA将CCR1数据到CCR3
void TIM_DMA_CFG(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA, ENABLE);
	/*DMA1 channel1 configuration ----------------------------------------------*/
	DMA_DeInit(DMA1_Channel0);
	DMA_InitStructure.DMA_PeripheralBaseAddr = TIM1_CCR1_Address;			//用来设置DMA传输的外设基地址
	DMA_InitStructure.DMA_MemoryBaseAddr = TIM1_CCR3_Address;				//内存基地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;						//设置数据传输方向，即决定是从外设读取数据到内存还是从内存读数据到外设，这里我们是从外设ADC_DR寄存器读数据到内存
	DMA_InitStructure.DMA_BufferSize = 1;									//设置一次传输数据量的大小
	DMA_InitStructure.DMA_MSIZE = DMA_MSIZE_1;								//突发事务传输长度
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;		//设置传输数据的时候 （外设） 地址是不变还是递增。
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;				//设置传输数据的时候 （内存 ）地址是不变还是递增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word; //设置外设的数据长度是为字节传输（8bits）还是半字（16bits）还是字传输（32bits）
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;			//设置内存的数据长度，同上。
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;							//设置是否进行循环采集
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;						//设置优先级
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel0, &DMA_InitStructure); //设置是否是存储器到存储器模式传输
	/* Enable DMA1 channel1 TC interupt*/
	DMA_ITConfig(DMA1_Channel0, DMA1_FLAG_TC0, ENABLE); //配置DMA发送完成后中断
	DMA_RemapConfig(DMA1_Channel0, DMA_ReqNum4, DMA_REQ_TIM1_CH1);
	/* Enable DMA1 channel1 */
	DMA_Cmd(DMA1_Channel0, ENABLE);

	NVIC_ClearPendingIRQ(DMAC_CH0_IRQn);
	NVIC_EnableIRQ(DMAC_CH0_IRQn);
}

static void tim1_cfg_init()
{
	uint16_t TimerPeriod = 0;
	uint16_t Channel1Pulse = 0;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	TimerPeriod = 1000;
	Channel1Pulse = 400;

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

	TIM_ITConfig(TIM1, TIM_DIER_TDE | TIM_DIER_CC1DE, ENABLE);			  // tim DMA使能
	TIM_DMAConfig(TIM1, TIM_DMABase_CCR1, TIM_DMABurstLength_2Transfers); // tim DMA配置
	TIM_Cmd(TIM1, ENABLE);
}

int main()
{
	SystemInit();
	SetSysClock(); //主频配置
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM1, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	GPIO_Config(); // PWM GPIOSET
	TIM_DMA_CFG();
	tim1_cfg_init(); // TIM1 SET
	while (1)
		;
}

void DMAC_CH0_Handler(void)
{
	DMA_ClearITPendingBit(DMA1_FLAG_TC1);
}
