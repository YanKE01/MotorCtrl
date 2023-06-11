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
/**
  ******************************************************************************
  ADC外部通道：
	PA0(AN1)=ADCIN[0];
  PA1(AN1)=ADCIN[1];
	PA2(AN2)=ADCIN[2];
	PA3(AN1)=ADCIN[3];
	PA4(AN2)=ADCIN[4];
	PA5(AN1)=ADCIN[5];
	PA6(AN1)=ADCIN[6];
	PA7(AN1)=ADCIN[7];
	PB0(AN2)=ADCIN[8];
	PB1(AN1)=ADCIN[9];
	PA8(AN1)=ADCIN[10];
	PF6(AN1)=ADCIN[11];
	PF7(AN1)=ADCIN[12];
	PB5(AN1)=ADCIN[13];
	PA9(AN1)=ADCIN[14];
	PA10(AN1)=ADCIN[15];
  ******************************************************************************/
#define DMA_ENABLE 1
#define ADC_SIZE 16UL
#define ADC1_DR_Address (0x4001A020)
unsigned int ADCConvertedRawData[ADC_SIZE] = {0};
void GPIOConfiguration(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_1); // PA0(AN1)=ADCIN[0]

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_1); // PA1(AN1)=ADCIN[1]

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_2); // PA2(AN2)=ADCIN[2]

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_1); // PA3(AN1)=ADCIN[3]

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource4, GPIO_AF_2); // PA4(AN2)=ADCIN[4]

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_1); // PA5(AN1)=ADCIN[5]

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_1); // PA6(AN1)=ADCIN[6]

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_1); // PA7(AN1)=ADCIN[7]

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource0, GPIO_AF_2); // PB0(AN2)=ADCIN[8]

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource1, GPIO_AF_1); // PB1(AN1)=ADCIN[9];

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_1); // PA8(AN1)=ADCIN[10]

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOF, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource6, GPIO_AF_1); // PF6(AN1)=ADCIN[11]

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOF, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource7, GPIO_AF_1); // PF7(AN1)=ADCIN[12]

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_1); // PB5(AN1)=ADCIN[13]

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1); // PA9(AN1)=ADCIN[14]

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1); // PA10(AN1)=ADCIN[15]
}

void ADCConfiguration(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;

	ADC_InitStructure.ADC_ClkMode = ADC_ClockMode_SynClkDiv4;					//选择转换时钟源
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;						//精度
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;							//转换模式0=单次;1=连续;表示触发一次转换一个通道或是一个序列
	ADC_InitStructure.ADC_AutoWatiMode = ENABLE;								//该位由软件设置和清除来使开启 / 关闭自动延迟转换模式
	ADC_InitStructure.ADC_DMATRIG_LEVEL = FIFO_DMA_NOEMPTY;						//软件配置触发 DMA 请求的 FIFO 水平。在 DMAEN 使能前进行配置，避免出现 DMA 在搬运时的错误。
	ADC_InitStructure.ADC_DMA = ENABLE;											//是否允许用 DMA 控制器来自动管理转换的结果数据
	ADC_InitStructure.ADC_DiscMode = DISABLE;									// 0=断续模式禁止;1=断续模式开启
	ADC_InitStructure.ADC_SamecMode = DISABLE;									//采样模式选择0=连续采样;1=同时采样
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None; //触发方式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_SoftWare;		//触发源
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;						//数据对齐方式
	ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;				// 0=向前扫描 (从 CHSEL0 到 CHSEL15);1=向后扫描( 从 CHSEL15 到 CHSEL0)
	ADC_InitStructure.ADC_Vref = ADC_Vref_Internal_3V3;							//参考电压选择
	ADC_Init(ADC, &ADC_InitStructure);

	ADC_ChannelConfig(ADC, ADC_Channel_0, 15, 7, 7); //配置通道，CONVERT，ADJUST,SMP
	ADC_ChannelConfig(ADC, ADC_Channel_1, 15, 7, 7);
	ADC_ChannelConfig(ADC, ADC_Channel_2, 15, 7, 7);
	ADC_ChannelConfig(ADC, ADC_Channel_3, 15, 7, 7);
	ADC_ChannelConfig(ADC, ADC_Channel_4, 15, 7, 7);
	ADC_ChannelConfig(ADC, ADC_Channel_5, 15, 7, 7);
	ADC_ChannelConfig(ADC, ADC_Channel_6, 15, 7, 7);
	ADC_ChannelConfig(ADC, ADC_Channel_7, 15, 7, 7);
	ADC_ChannelConfig(ADC, ADC_Channel_8, 15, 7, 7);
	ADC_ChannelConfig(ADC, ADC_Channel_9, 15, 7, 7);
	ADC_ChannelConfig(ADC, ADC_Channel_10, 15, 7, 7);
	ADC_ChannelConfig(ADC, ADC_Channel_11, 15, 7, 7);
	ADC_ChannelConfig(ADC, ADC_Channel_12, 15, 7, 7);
	ADC_ChannelConfig(ADC, ADC_Channel_13, 15, 7, 7);
	ADC_ChannelConfig(ADC, ADC_Channel_14, 15, 7, 7);
	ADC_ChannelConfig(ADC, ADC_Channel_15, 15, 7, 7);
	ADC_Cmd(ADC, ENABLE);

#if DMA_ENABLE
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA, ENABLE);
	/*DMA1 channel1 configuration ----------------------------------------------*/
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;				//用来设置DMA传输的外设基地址
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADCConvertedRawData;	//内存基地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;						//设置数据传输方向，即决定是从外设读取数据到内存还是从内存读数据到外设，这里我们是从外设ADC_DR寄存器读数据到内存
	DMA_InitStructure.DMA_BufferSize = ADC_SIZE;							//设置一次传输数据量的大小
	DMA_InitStructure.DMA_MSIZE = DMA_MSIZE_1;								//突发事务传输长度
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;		//设置传输数据的时候 （外设） 地址是不变还是递增。
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;					//设置传输数据的时候 （内存 ）地址是不变还是递增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word; //设置外设的数据长度是为字节传输（8bits）还是半字（16bits）还是字传输（32bits）
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;			//设置内存的数据长度，同上。
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;							//设置是否进行循环采集
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;						//设置优先级
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure); //设置是否是存储器到存储器模式传输
	/* Enable DMA1 channel1 TC interupt*/
	DMA_ITConfig(DMA1_Channel1, DMA1_FLAG_TC1, ENABLE); //配置DMA发送完成后中断
	DMA_RemapConfig(DMA1_Channel1, DMA_ReqNum5, DMA_REQ_ADC);
	/* Enable DMA1 channel1 */
	DMA_Cmd(DMA1_Channel1, ENABLE);
#endif
}

int main()
{
	SystemInit();
	SetSysClock(); //主频配置

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_ADC, ENABLE); //开时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);
	NVIC_ClearPendingIRQ(DMAC_CH1_2_IRQn);
	NVIC_EnableIRQ(DMAC_CH1_2_IRQn); //使能DMA中断

	GPIOConfiguration();		 // GPIO设置
	ADCConfiguration();			 // ADC初始化
	ADC_StartOfConversion(ADC1); // ADC 开始转换命令
	while (1)
		;
}

void DMAC_CH1_2_Handler(void) // 40us
{
	DMA_ClearITPendingBit(DMA1_FLAG_TC1);
}
