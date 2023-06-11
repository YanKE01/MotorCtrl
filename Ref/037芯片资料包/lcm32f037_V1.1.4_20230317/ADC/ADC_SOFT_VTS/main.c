#include "lcm32f037_adc.h"
#include "lcm32f037_opa.h"
#include "lcm32f037_tim.h"
#include "lcm32f037_dma.h"
#include "lcm32f037_flash.h"
#include "lcm32f037_dac.h"
/*****************
demo为软件触发ADC
***********************************************************************************************/
#define DMA_ENABLE 1
#define ADC_SIZE 6
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

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_2); // tim1_ch1   pA8
}
void ADCConfiguration(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;

	ADC_InitStructure.ADC_ClkMode = ADC_ClockMode_SynClkDiv4;					  //选择转换时钟源
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;						  //精度
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;							  //转换模式0=单次;1=连续;表示触发一次转换一个通道或是一个序列
	ADC_InitStructure.ADC_AutoWatiMode = ENABLE;								  //该位由软件设置和清除来使开启 / 关闭自动延迟转换模式
	ADC_InitStructure.ADC_DMATRIG_LEVEL = FIFO_DMA_NOEMPTY;						  //软件配置触发 DMA 请求的 FIFO 水平。在 DMAEN 使能前进行配置，避免出现 DMA 在搬运时的错误。
	ADC_InitStructure.ADC_DMA = ENABLE;											  //是否允许用 DMA 控制器来自动管理转换的结果数据
	ADC_InitStructure.ADC_DiscMode = DISABLE;									  // 0=断续模式禁止;1=断续模式开启
	ADC_InitStructure.ADC_SamecMode = DISABLE;									  //采样模式选择0=连续采样;1=同时采样
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_Rising; //触发方式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_TRGO;		  //触发源
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;						  //数据对齐方式
	ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;				  // 0=向前扫描 (从 CHSEL0 到 CHSEL15);1=向后扫描( 从 CHSEL15 到 CHSEL0)
	ADC_InitStructure.ADC_Vref = ADC_Vref_Externa_Vrh4V;							  //参考电压选择
	ADC_Init(ADC, &ADC_InitStructure);

	ADC_ChannelConfig(ADC, ADC_Channel_0, 15, 7, 7); //配置通道，CONVERT，ADJUST,SMP
	ADC_ChannelConfig(ADC, ADC_Channel_1, 15, 7, 7);
	ADC_ChannelConfig(ADC, ADC_Channel_2, 15, 7, 7);
	ADC_ChannelConfig(ADC, ADC_Channel_3, 15, 7, 7);
	ADC_ChannelConfig(ADC, ADC_Channel_4, 15, 7, 7);
	ADC_ChannelConfig(ADC, ADC_Channel_5, 15, 7, 7);

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
void tim1_cfg_init()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	uint16_t TimerPeriod;
	uint16_t Channel1Pulse, Channel2Pulse, Channel3Pulse, Channel4Pulse;
	TimerPeriod = 800;	 // 16000000/20000;
	Channel1Pulse = 400; // TimerPeriod/2;
	Channel2Pulse = 400; // TimerPeriod/2;
	Channel3Pulse = 400; // TimerPeriod/2;
	Channel4Pulse = 400; // TimerPeriod/2;

	/* Time Base configuration */
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1;
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

	TIM_SelectOutputTrigger(TIM1, TIM_TRGOSource_OC4Ref); //选择TRGO输出触发源

	TIM_CtrlPWMOutputs(TIM1, ENABLE); //配置TRGO触发ADC可不需要使能，配置通道CCx触发,或通过IO观测PWM波形，必须使能；

	TIM_Cmd(TIM1, ENABLE);
}
int main()
{
	SystemInit();
	SetSysClock(); //主频配置

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_ADC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM1, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);
	NVIC_ClearPendingIRQ(DMAC_CH1_2_IRQn);
	NVIC_EnableIRQ(DMAC_CH1_2_IRQn); //使能DMA中断

	GPIOConfiguration(); // GPIO设置
	tim1_cfg_init();
	ADCConfiguration();			// ADC初始化
	ADC_StartOfConversion(ADC); // ADC 开始转换命令

	while (1)
		;
}
uint32_t datad, testCount;
int temperature;
void DMAC_CH1_2_Handler(void)
{
	DMA_ClearITPendingBit(DMA1_FLAG_TC1);
	testCount++;
	if (testCount > 10000) //搬运1000次后切通道采VTS，再切回来
	{
		testCount = 0;
		/**********************切VTS通道***********************/
		ADC_StopOfConversion(ADC);						  //停止ADC
		ADC->ISR = 0x0000000e;							  //清除ADC标志位
		ADC->CFGR1 &= 0xfffffffe;						  // DMA不使能
		ADC->EXTCFG = 0;								  //触发源:软件触发(可以不改触发源，根据需要选择)
		ADC_ChannelConfig(ADC, ADC_Channel_16, 15, 7, 7); //温度传感器: 当 ST=1，SV=0 时选用 ADC_IN16，其他通道(ADC_IN0~15，ADC_IN17)禁用
		ADC_StartOfConversion(ADC);						  // ADC开始转换命令
		datad = ADC_GetConversionValue(ADC);			  //获取温度传感器AD值
		temperature = ADC_GetVTStemperature(datad, 4000); //获取当前温度
		/**********************切回原配置***********************/
		ADC_StopOfConversion(ADC);						 //停止ADC
		ADC->ISR = 0x0000000e;							 //清除ADC标志位
		ADC->CFGR1 |= 0x01;								 // DMA使能
		ADC->EXTCFG = 0x80000001;						 //触发源:T1_TRGO上升沿
		ADC_ChannelConfig(ADC, ADC_Channel_0, 15, 7, 7); //配置通道
		ADC_ChannelConfig(ADC, ADC_Channel_1, 15, 7, 7);
		ADC_ChannelConfig(ADC, ADC_Channel_2, 15, 7, 7);
		ADC_ChannelConfig(ADC, ADC_Channel_3, 15, 7, 7);
		ADC_ChannelConfig(ADC, ADC_Channel_4, 15, 7, 7);
		ADC_ChannelConfig(ADC, ADC_Channel_5, 15, 7, 7);
		ADC_StartOfConversion(ADC); // ADC开始转换命令
	}
}