#include "lcm32f037_conf.h"
#include "lcm32f037.h"
#include "lcm32f037_rcc.h"
#include "lcm32f037_gpio.h"
#include "lcm32f037_opa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lcm32f037_tim.h"
#include "lcm32f037_acmp.h"
#include "lcm32f037_dac.h"
#include "lcm32f037_dma.h"

#define DMA_ENABLE 1
#define ADC_SIZE 10
#define ADC1_DR_Address (0x4001A020)
uint32_t ADCConvertedRawData[ADC_SIZE] = {0};

uint16_t TimerPeriod = 0;
uint16_t Channel1Pulse = 0, Channel2Pulse = 0, Channel3Pulse = 0, Channel4Pulse = 0;

static void tim1_cfg_init()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	TimerPeriod = 800;
	Channel1Pulse = 400;
	Channel4Pulse = 400;

	/* Time Base configuration */
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = TimerPeriod;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

	/* Channel 1, 2,3 and 4 Configuration in PWM mode */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
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

	/*配置刹车中断，需要先配置触发源，再配BDTR寄存器中的极性BKP,最后配置使能。
	或者初始化清一次SR寄存器的中断标志*/
	sysctrl_access();
	SYSCTRL->EDU_CFG4 |= (1 << 9); //刹车触发源选择 acmp1
	__dekey();

	TIM_BDTRInitTypeDef TIM_BDTRInitStruct; //设置刹车
	TIM_BDTRInitStruct.TIM_OSSRState = TIM_OSSRState_Disable;
	TIM_BDTRInitStruct.TIM_OSSIState = TIM_OSSIState_Disable;
	TIM_BDTRInitStruct.TIM_LOCKLevel = TIM_LOCKLevel_OFF;
	TIM_BDTRInitStruct.TIM_DeadTime = 0x00;
	TIM_BDTRInitStruct.TIM_Break = TIM_Break_Enable;
	TIM_BDTRInitStruct.TIM_BreakPolarity = TIM_BreakPolarity_High;
	TIM_BDTRInitStruct.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
	TIM_BDTRConfig(TIM1, &TIM_BDTRInitStruct);

	// TIM1->SR =0;//初始化清一次中断标志

	TIM_ITConfig(TIM1, TIM_DIER_BIE, ENABLE); //刹车中断BIE使能

	TIM_SelectOutputTrigger(TIM1, TIM_TRGOSource_Update); //选择输出触发源

	/* Main Output Enable */
	TIM_CtrlPWMOutputs(TIM1, ENABLE);

	TIM_Cmd(TIM1, ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_2); // tim1_ch1   OUT=pA8  PWM GPIOSET
}

void acmp1_cfg()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
	//	GPIO_InitStructure.GPIO_OType  = GPIO_OType_PP;
	//	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//	GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_2);//CP1P=PA1

	//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
	//	GPIO_InitStructure.GPIO_OType  = GPIO_OType_PP;
	//	GPIO_Init(GPIOB, &GPIO_InitStructure);
	//	GPIO_PinAFConfig(GPIOB,GPIO_PinSource0,GPIO_AF_2);//CP1N=PB0

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_6); // CP1O=PB3

	ACMP_InitTypeDef ACMP_InitStruct;

	ACMP_InitStruct.ACMP_P_Select = CP1_PS_CPP1EXT_INPUT; //第一级外部
	ACMP_InitStruct.ACMP_N_Select = CP1_NS_DAC1OUT;		  // DAC1/PB0
	ACMP_InitStruct.ACMP_Delay_time = CP_NODelay_time;	  //输出延迟配置
	ACMP_InitStruct.ACMP_Blanking = CP_NOBLANKING;		  //比较器消隐源选择
	ACMP_InitStruct.ACMP_Is = CP_IS_POS;				  //比较器输出极性
	ACMP_InitStruct.ACMP_HYSEN = DISABLE;				  //迟滞使能配置
	ACMP_InitStruct.ACMP_FREN = ENABLE;					  //快速响应使能
	ACMP_InitStruct.ACMP_FS = DISABLE;					  //输出滤波使能配置

	ACMP_InitStruct.CMP_INTENMASK = DISABLE;			 //比较器连续比较中断使能屏蔽
	ACMP_InitStruct.CMP_SEQ_MODE = DISABLE;				 //连续模式使能
	ACMP_InitStruct.TRIG_MODE = CP_TIRG_INASOFT;		 //触发模式：软件或者外部硬件触发
	ACMP_InitStruct.CHNL_CNT_TIME = CHNL_CNT_TIME_64CLK; //比较器通道切换时钟周期选择

	ACMP_InitStruct.EXTSELECT = ENABLE_EXTSELG0;			  // Two sets of trigger sources enable control bits
	ACMP_InitStruct.EXTEN_Signal_andmode = DISABLE;			  // Trigger signal logic 'or' or 'and'
	ACMP_InitStruct.CP_EXTSP = CP_EXTSP_POS;				  //触发信号极性选择
	ACMP_InitStruct.SYN_MODE = CP_SYN_MODE;					  //外部触发同步或异步
	ACMP_InitStruct.TRIG_SOURCE = TRIG_TIM1_CC1;			  //触发源选择
	ACMP_InitStruct.TRIG_DELAY_TIME = TRIG_DELAY_TIME_128CLK; //外部触发延迟时钟
	ACMP_InitStruct.EXTEN_EDGE_MODE = CP_Edge_model;		  //外部触发信号方式
	ACMP_InitStruct.EXTEN_MODE_SEL = CP_EXTEN_RISE;			  //外部触发模式选择

	ACMP_InitStruct.SYN_MODE = CP_SYN_MODE;
	ACMP1_Init(&ACMP_InitStruct);
	ACMP1_SEQ_INPUT_SELECT(DISABLE, 7, 1); // CP1P 选择OP0OUT 第二级
	ACMP1_Cmd(ENABLE);
}

void DAC1_cfg()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_2); // DAC_OUT1

	DAC_InitTypeDef DAC_InitStruct;
	DAC_InitStruct.DAC_Trigger_Source = DAC_Trigger_Software;
	DAC_InitStruct.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStruct.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
	DAC_InitStruct.DAC_OutputBuffer = DAC1_OutputBuffer_Enable;
	DAC_InitStruct.DAC_Vref_Select = DAC_Vref_Avdd;
	DAC_InitStruct.DAC_EXTrigger_Edge = DAC_EXTrigger_edge_dis;
	DAC_InitStruct.DAC_DmaMode = DISABLE;
	DAC_InitStruct.DAC_DMAUDR_IE = DISABLE;
	DAC_Init(DAC1, &DAC_InitStruct);

	DAC_Cmd(DAC1, ENABLE);
	DAC_SetDac_10B_Data(DAC1, DAC_Align_10B_R, 0x200);
	DAC_SoftwareTriggerCmd(DAC1, ENABLE);
}

void OPA0_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource4, GPIO_AF_2);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_1); //正端输入

	//	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_3 ;
	//  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	//	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	//	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	//	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	//	GPIO_Init(GPIOA, &GPIO_InitStruct);
	//	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_2);//opa0输出到PA3 可以测量

	OPA_InitTypeDef OPA_InitStruct;
	OPA_InitStruct.OPA_Oppselect = OPA0_Oppselect_PA2; // OPA0 P
	OPA_InitStruct.OPA_Opnselect = OPA0_Opnselect_PA4; // OPA0 N  外部接地
	OPA_InitStruct.OPA_Gain = OPA_Gain_2;
	OPA_InitStruct.OPA_BiasVoltage = OPA_BiasVoltage_DISEN;
	OPA_InitStruct.OPA_FeedbackRes = OPA_FeedbackRes_EN;
	OPA_InitStruct.OPA_Opoto_Gpio = OPA_OPOEX_DISEN;
	OPA_InitStruct.OPA_OppRES_short = OPA_OppRES_short_DISEN;
	OPA_InitStruct.OPA_OpnRES_short = OPA_OpnRES_short_DISEN;
	OPA_InitStruct.OPA_BiasVoltageSource = OPA_OPA_BiasVoltageSource_HALFVRH;
	OPA_Init(OPA0, &OPA_InitStruct);

	OPA_Cmd(OPA0, ENABLE);
}
void OPA1_Init()
{
	// OPA1
	GPIO_InitTypeDef GPIO_InitStruct;

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

	//	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_7 ;
	//  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	//	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	//	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	//	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	//	GPIO_Init(GPIOA, &GPIO_InitStruct);
	//	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_2);//opa1输出到PA7可以测量

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
	// OPA2
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_2);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_2); //正端输入

	//	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_1 ;
	//  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	//	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	//	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	//	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	//	GPIO_Init(GPIOB, &GPIO_InitStruct);
	//	GPIO_PinAFConfig(GPIOB,GPIO_PinSource1,GPIO_AF_2);//opa2输出到PB1 可以测量

	OPA_InitTypeDef OPA_InitStruct;
	OPA_InitStruct.OPA_Oppselect = OPA2_Oppselect_PB6;
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

static void ADC_Config(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;

	/* Configure the ADC1 in continuous mode with a resolution equal to 12 bits  */
	ADC_InitStructure.ADC_ClkMode = ADC_ClockMode_sysnClk;						  //选择转换时钟源
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
	ADC_InitStructure.ADC_Vref = ADC_Vref_Internal_3V3;							  //参考电压选择
	ADC_Init(ADC1, &ADC_InitStructure);

	ADC_ChannelConfig(ADC1, ADC_Channel_2, 25, 7, 7);
	ADC_ChannelConfig(ADC1, ADC_Channel_12, 25, 7, 7);

	ADC_Cmd(ADC1, ENABLE);

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
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;							//内存到内存使能
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);							//设置是否是存储器到存储器模式传输

	DMA_ITConfig(DMA1_Channel1, DMA1_FLAG_TC1, ENABLE); //配置DMA发送完成后中断

	DMA_RemapConfig(DMA1_Channel1, DMA_ReqNum5, DMA_REQ_ADC);

	DMA_Cmd(DMA1_Channel1, ENABLE);
#endif
}

int main()
{
	SystemInit();
	SetSysClock(); //主频配置
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM1, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_ANACTRL, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_ADC, ENABLE);

	NVIC_ClearPendingIRQ(DMAC_CH1_2_IRQn);
	NVIC_EnableIRQ(DMAC_CH1_2_IRQn);
	NVIC_ClearPendingIRQ(TIM1_NON_CC_IRQn);
	NVIC_EnableIRQ(TIM1_NON_CC_IRQn);

	// 优先级从高到底:TIM1_NON_CC_IRQn -> DMAC_CH1_2_IRQn
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_NON_CC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = DMAC_CH1_2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	OPA0_Init();	 // P=PA2; PA4接地
	DAC1_cfg();		 // OUT=PA5
	acmp1_cfg();	 // OUT=PB3
	SATRT_OFACMP1(); // only soft trigger need
	tim1_cfg_init(); // OPA0  PA2输入 PA4接地->(OPA0O=CP1P )+ (DAC)->TIM1BK

	OPA1_Init(); // P=PA6;N=PF1;OUT=PA7/ADCIN[2]
	OPA2_Init(); // P=PB6;N=PB7;OUT=PB1/ADCIN[12]
	ADC_Config();
	ADC_StartOfConversion(ADC1);

	while (1)
		;
}

void DMAC_CH1_2_Handler(void) // 40us
{
	DMA_ClearITPendingBit(DMA1_FLAG_TC1);
}

void TIM1_NON_CC_Handler(void) //刹车中断
{
	TIM_ClearITPendingBit(TIM1, TIM_IT_Break);
}
