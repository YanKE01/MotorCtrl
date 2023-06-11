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
/**
  ******************************************************************************
  ADC内部通道：
	OPA0O(OP0OEX)=ADCIN[11]/经PA3回环到ADCIN[3];
	OPA0O(OP1OEX)=ADCIN[12]/经PA7回环到ADCIN[7];
	OPA0O(OP2OEX)=ADCIN[2]/经PB1回环到ADCIN[9];

	DAC_OUT0:连接到外部端口PA10的模拟通道2，进而通过同时打开PA10的1通道，可以回环到ADCIN[15]
			 连接到外部端口PA4的模拟通道1，进而通过同时打开PA4的2通道，可以回环到ADCIN[4]

	DAC_OUT1:连接到外部端口PA5的模拟通道2，进而通过同时打开PA4的1通道，可以回环到ADCIN[5]

	温度传感器：当 ST=1，SV=0 时选用 ADC_IN16，其他通道(ADC_IN0~15，ADC_IN17)禁用。
	VDDA：当 ST=1，SV=1时选用 ADC_IN17(VDD)，其他通道(ADC_IN0~15，ADC_IN16)禁用。
  ******************************************************************************/
#define DMA_ENABLE 1
#define ADC_SIZE 9UL
#define ADC1_DR_Address (0x4001A020)
unsigned int ADCConvertedRawData[9] = {0};

void OPA0_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	// OPA0
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
	//	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_2);//opa0输出到PA3 可以测量
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_1 | GPIO_AF_2); //通过PA3回环使OP0O接到ADCIN[3];OP0O内部直连ADCIN[11]

	OPA_InitTypeDef OPA_InitStruct;
	OPA_InitStruct.OPA_Oppselect = OPA0_Oppselect_PA9;
	OPA_InitStruct.OPA_Opnselect = OPA0_Opnselect_PA8;
	OPA_InitStruct.OPA_Gain = OPA_Gain_10;
	OPA_InitStruct.OPA_BiasVoltage = OPA_BiasVoltage_DISEN;
	OPA_InitStruct.OPA_FeedbackRes = OPA_FeedbackRes_EN;
	OPA_InitStruct.OPA_Opoto_Gpio = OPA_OPOEX_EN;
	OPA_InitStruct.OPA_OppRES_short = OPA_OppRES_short_DISEN;
	OPA_InitStruct.OPA_OpnRES_short = OPA_OpnRES_short_DISEN;
	OPA_InitStruct.OPA_BiasVoltageSource = OPA_OPA_BiasVoltageSource_HALFVRH;
	OPA_Init(OPA0, &OPA_InitStruct);
	OPA_Cmd(OPA0, ENABLE);
}
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
	//	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_2);//opa1输出到PA7 可以测量
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_1 | GPIO_AF_2); //通过PA7回环使OP1O接到ADCIN[7];OP1O内部直连ADCIN[12]

	OPA_InitTypeDef OPA_InitStruct;
	OPA_InitStruct.OPA_Oppselect = OPA1_Oppselect_PA6;
	OPA_InitStruct.OPA_Opnselect = OPA1_Opnselect_PF1;
	OPA_InitStruct.OPA_Gain = OPA_Gain_10;
	OPA_InitStruct.OPA_BiasVoltage = OPA_BiasVoltage_DISEN;
	OPA_InitStruct.OPA_FeedbackRes = OPA_FeedbackRes_EN;
	OPA_InitStruct.OPA_Opoto_Gpio = OPA_OPOEX_EN;
	OPA_InitStruct.OPA_OppRES_short = OPA_OppRES_short_DISEN;
	OPA_InitStruct.OPA_OpnRES_short = OPA_OpnRES_short_DISEN;
	OPA_InitStruct.OPA_BiasVoltageSource = OPA_OPA_BiasVoltageSource_HALFVRH;
	OPA_Init(OPA1, &OPA_InitStruct);
	OPA_Cmd(OPA1, ENABLE);
}
void OPA2_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	// OPA2
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_2);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource0, GPIO_AF_2); //正端输入

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	//	GPIO_PinAFConfig(GPIOB,GPIO_PinSource1,GPIO_AF_2);//opa2输出到PB1 可以测量
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource1, GPIO_AF_1 | GPIO_AF_2); //通过PB1回环使OP2O接到ADCIN[9];OP0O内部直连ADCIN[2]

	OPA_InitTypeDef OPA_InitStruct;
	OPA_InitStruct.OPA_Oppselect = OPA2_Oppselect_PB0;
	OPA_InitStruct.OPA_Opnselect = OPA2_Opnselect_PB7;
	OPA_InitStruct.OPA_Gain = OPA_Gain_10;
	OPA_InitStruct.OPA_BiasVoltage = OPA_BiasVoltage_DISEN;
	OPA_InitStruct.OPA_FeedbackRes = OPA_FeedbackRes_EN;
	OPA_InitStruct.OPA_Opoto_Gpio = OPA_OPOEX_EN;
	OPA_InitStruct.OPA_OppRES_short = OPA_OppRES_short_DISEN;
	OPA_InitStruct.OPA_OpnRES_short = OPA_OpnRES_short_DISEN;
	OPA_InitStruct.OPA_BiasVoltageSource = OPA_OPA_BiasVoltageSource_HALFVRH;
	OPA_Init(OPA2, &OPA_InitStruct);
	OPA_Cmd(OPA2, ENABLE);
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
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource4, GPIO_AF_1 | GPIO_AF_2); // DAC0_OUT:回环连接到ADCIN[4]

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1 | GPIO_AF_2); // DAC0_OUT:回环连接到ADCIN[15]

	DAC_InitTypeDef DAC_InitStruct;
	DAC_InitStruct.DAC_EXTrigger_Edge = DAC_EXTrigger_edge_dis;
	DAC_InitStruct.DAC_Trigger_Source = DAC_Trigger_Software;
	DAC_InitStruct.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStruct.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
	DAC_InitStruct.DAC_OutputBuffer = DAC0_OutputBuffer_Enable;
	DAC_InitStruct.DAC_Vref_Select = DAC_Vref_Avdd;
	DAC_InitStruct.DAC_DmaMode = DISABLE;
	DAC_InitStruct.DAC_DMAUDR_IE = DISABLE;
	DAC_Init(DAC0, &DAC_InitStruct);

	DAC_Cmd(DAC0, ENABLE);
	DAC_SetDac_10B_Data(DAC0, DAC_Align_10B_R, 0x100);
	DAC_SoftwareTriggerCmd(DAC0, ENABLE); //软件触发使能；标示触发 DAC 的一次触发传输(选择软件触发条件)
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
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_1 | GPIO_AF_2); // DAC1_OUT:回环连接到ADCIN[5]

	DAC_InitTypeDef DAC_InitStruct;
	DAC_InitStruct.DAC_EXTrigger_Edge = DAC_EXTrigger_edge_dis;
	DAC_InitStruct.DAC_Trigger_Source = DAC_Trigger_Software;
	DAC_InitStruct.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStruct.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
	DAC_InitStruct.DAC_OutputBuffer = DAC1_OutputBuffer_Enable;
	DAC_InitStruct.DAC_Vref_Select = DAC_Vref_Avdd;
	DAC_InitStruct.DAC_DmaMode = DISABLE;
	DAC_InitStruct.DAC_DMAUDR_IE = DISABLE;
	DAC_Init(DAC1, &DAC_InitStruct);

	DAC_Cmd(DAC1, ENABLE);
	DAC_SetDac_10B_Data(DAC1, DAC_Align_10B_R, 0x7F);
	DAC_SoftwareTriggerCmd(DAC1, ENABLE); //软件触发使能；标示触发 DAC 的一次触发传输(选择软件触发条件)
}

void ADCConfiguration(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;

	ADC_InitStructure.ADC_ClkMode = ADC_ClockMode_sysnClk;						//选择转换时钟源
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

	/*****************OPA联动	****************/
	ADC_ChannelConfig(ADC, ADC_Channel_3, 15, 7, 7); //输出脚回环
	ADC_ChannelConfig(ADC, ADC_Channel_7, 15, 7, 7);
	ADC_ChannelConfig(ADC, ADC_Channel_9, 15, 7, 7);

	ADC_ChannelConfig(ADC, ADC_Channel_11, 15, 7, 7); //内部直连
	ADC_ChannelConfig(ADC, ADC_Channel_12, 15, 7, 7);
	ADC_ChannelConfig(ADC, ADC_Channel_2, 15, 7, 7);

	ADC_ChannelConfig(ADC, ADC_Channel_4, 15, 7, 7);  // DAC0_OUT: PA4回环
	ADC_ChannelConfig(ADC, ADC_Channel_15, 15, 7, 7); // DAC0_OUT: PA10回环
	ADC_ChannelConfig(ADC, ADC_Channel_5, 15, 7, 7);  // DAC1_OUT: PA5回环

	//	ADC_ChannelConfig(ADC,ADC_Channel_16,15,7,7); //温度传感器: 当 ST=1，SV=0 时选用 ADC_IN16，其他通道(ADC_IN0~15，ADC_IN17)禁用
	//	ADC_ChannelConfig(ADC,ADC_Channel_17,15,7,7);//VDDA：当 ST=1，SV=1时选用 ADC_IN17(VDD)，其他通道(ADC_IN0~15，ADC_IN16)禁用

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
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_ANACTRL, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);
	NVIC_ClearPendingIRQ(DMAC_CH1_2_IRQn);
	NVIC_EnableIRQ(DMAC_CH1_2_IRQn); //使能DMA中断

	OPA0_Init();
	OPA1_Init();
	OPA2_Init();
	DAC0_Config();
	DAC1_Config();

	ADCConfiguration();			 // ADC初始化
	ADC_StartOfConversion(ADC1); // ADC 开始转换命令
	while (1)
		;
}

void DMAC_CH1_2_Handler(void) // 40us
{
	DMA_ClearITPendingBit(DMA1_FLAG_TC1);
}
