#include "lcm32f037_adc.h"
#include "lcm32f037_opa.h"
#include "lcm32f037_tim.h"
#include "lcm32f037_dma.h"
#include "lcm32f037_flash.h"
#include "lcm32f037_dac.h"
/*****************
demo为ADC模拟看门狗例程
***********************************************************************************************/
void delay(uint32_t dly)
{
	volatile uint32_t i = 0;
	while (i++ < dly)
		;
}
void GPIOConfiguration(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_1); // PA0=ADCIN[0]
}
void ADCConfiguration(void)
{
	ADC_InitTypeDef ADC_InitStructure;

	ADC_InitStructure.ADC_ClkMode = ADC_ClockMode_sysnClk;						//选择转换时钟源
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;						//精度
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;							//转换模式0=单次;1=连续;表示触发一次转换一个通道或是一个序列
	ADC_InitStructure.ADC_AutoWatiMode = ENABLE;								//该位由软件设置和清除来使开启 / 关闭自动延迟转换模式
	ADC_InitStructure.ADC_DMATRIG_LEVEL = FIFO_DMA_NOEMPTY;						//软件配置触发 DMA 请求的 FIFO 水平。在 DMAEN 使能前进行配置，避免出现 DMA 在搬运时的错误。
	ADC_InitStructure.ADC_DMA = DISABLE;										//是否允许用 DMA 控制器来自动管理转换的结果数据
	ADC_InitStructure.ADC_DiscMode = DISABLE;									// 0=断续模式禁止;1=断续模式开启
	ADC_InitStructure.ADC_SamecMode = DISABLE;									//采样模式选择0=连续采样;1=同时采样
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None; //触发方式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_SoftWare;		//触发源
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;						//数据对齐方式
	ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;				// 0=向前扫描 (从 CHSEL0 到 CHSEL15);1=向后扫描( 从 CHSEL15 到 CHSEL0)
	ADC_InitStructure.ADC_Vref = ADC_Vref_Internal_3V3;							//参考电压选择
	ADC_Init(ADC, &ADC_InitStructure);

	ADC_ChannelConfig(ADC, ADC_Channel_0, 15, 7, 7); //配置通道，CONVERT，ADJUST,SMP
	ADC_Cmd(ADC, ENABLE);
}
void ADC_WDG(void)
{
	ADC_AnalogWatchdogSingleChannelCmd(ADC, ENABLE);						  //在单一通道上使能模拟看门狗
	ADC_AnalogWatchdogSingleChannelConfig(ADC, ADC_AnalogWatchdog_Channel_0); //配置通道0
	ADC_AnalogWatchdogThresholdsConfig(ADC, 2048, 1024);					  //配置模拟看门狗的高、低阀值
	ADC_ITConfig(ADC, ADC_IT_AWD, ENABLE);									  // AWD中断配置
	ADC_AnalogWatchdogCmd(ADC, ENABLE);

	NVIC_ClearPendingIRQ(ADC_IRQn);
	NVIC_SetPriority(ADC_IRQn, 0);
	NVIC_EnableIRQ(ADC_IRQn);
}
uint32_t datad[16] = {0};
uint8_t i;
int main()
{
	SystemInit();
	SetSysClock(); //主频配置

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_ADC, ENABLE); //开时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	GPIOConfiguration(); // GPIO设置
	ADCConfiguration();	 // ADC初始化

	ADC_WDG();					 // ADC模拟看门狗初始化
	ADC_StartOfConversion(ADC1); // ADC 开始转换命令
	while (1)
	{
		for (i = 0; i < 16; i++)
		{
			datad[i] = ADC_GetConversionValue(ADC1);
		}
		delay(10);
	}
}
void ADC_Handler()
{
	ADC_ClearFlag(ADC, ADC_IT_AWD);
}
