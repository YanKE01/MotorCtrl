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
/**************************
3路比较器:I/O 端口、HALL、DAC 和比较器之间可实现互联；


demo为 ACMP0单通道比较，可不需要触发；
		ACMP1为多通道连续比较，软件触发；软件触发需要START，且START一次仅转换一个序列；
		ACMP2为多通道比较，硬件触发；硬件触发不需要配置START

连续模式必须要触发，连续模式若选择软件触发，
则每次START(调用函数SATRT_OFACMP0/1/2();)仅转换一个序列

主频16M，硬件触发连续模式建议不超过1.5K；主频提高，硬件触发频率也可以随之增加
***************************************/

/******************************
ACMP0配置为正端IO输入，负端为DAC0;单通道比较，非连续
************************************************************************/
void delay(uint32_t dly)
{
	volatile uint32_t i = 0;
	while (i++ < dly)
		;
}

void DAC0_cfg()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_2); //用于观测DAC0_OUT

	DAC_InitTypeDef DAC_InitStruct;
	DAC_InitStruct.DAC_Trigger_Source = DAC_Trigger_Software;
	DAC_InitStruct.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStruct.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
	DAC_InitStruct.DAC_OutputBuffer = DAC0_OutputBuffer_Enable;
	DAC_InitStruct.DAC_Vref_Select = DAC_Vref_Avdd;
	DAC_InitStruct.DAC_EXTrigger_Edge = DAC_EXTrigger_edge_dis;
	DAC_InitStruct.DAC_DmaMode = DISABLE;
	DAC_InitStruct.DAC_DMAUDR_IE = DISABLE;
	DAC_Init(DAC0, &DAC_InitStruct);

	DAC_Cmd(DAC0, ENABLE);
	DAC_SetDac_10B_Data(DAC0, DAC_Align_10B_R, 0x1FF);
	DAC_SoftwareTriggerCmd(DAC0, ENABLE); //软件触发使能；标示触发 DAC 的一次触发传输(选择软件触发条件)
}
void acmp0_cfg()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_6); ////out

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_2); // CP0_P_1[1]

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource0, GPIO_AF_1); ////CP0_N_3[2]

	ACMP_InitTypeDef ACMP_InitStruct;
	ACMP_InitStruct.ACMP_P_Select = CP0_PS_CPP0EXT_INPUT; //比较器正端输入选择
	ACMP_InitStruct.ACMP_N_Select = CP0_NS_DAC0OUT;		  //比较器负端输入选择
	ACMP_InitStruct.ACMP_Delay_time = CP_NODelay_time;	  //输出延迟配置
	ACMP_InitStruct.ACMP_Blanking = CP_NOBLANKING;		  //比较器消隐源选择
	ACMP_InitStruct.ACMP_Is = CP_IS_POS;				  //比较器输出极性
	ACMP_InitStruct.ACMP_HYSEN = DISABLE;				  //迟滞使能配置
	ACMP_InitStruct.ACMP_FREN = ENABLE;					  //快速响应使能
	ACMP_InitStruct.ACMP_FS = DISABLE;					  //输出滤波使能配置

	ACMP_InitStruct.CMP_INTENMASK = ENABLE;				 //比较器连续比较中断使能屏蔽
	ACMP_InitStruct.CMP_SEQ_MODE = DISABLE;				 //连续模式使能
	ACMP_InitStruct.TRIG_MODE = CP_TIRG_INASOFT;		 //触发模式：软件或者外部硬件触发
	ACMP_InitStruct.CHNL_CNT_TIME = CHNL_CNT_TIME_64CLK; //比较器通道切换时钟周期选择

	ACMP0_Init(&ACMP_InitStruct);
	ACMP0_SEQ_INPUT_SELECT(DISABLE, 5, 2); //选择输入通道：是否连续；正端；负端
	ACMP0_Cmd(ENABLE);
}

/******************************
ACMP1为连续比较模式，软件触发，需要START
************************************************************************/
void acmp1_cfg()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_6); ////out

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource1, GPIO_AF_1); // CP1_P_P01[0]

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_1); // CP1_P_4[1]

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource7, GPIO_AF_2); ////CP1_N_5[2]

	ACMP_InitTypeDef ACMP_InitStruct;
	ACMP_InitStruct.ACMP_P_Select = CP1_PS_CPP1EXT_INPUT; //比较器正端输入选择
	ACMP_InitStruct.ACMP_N_Select = CP1_NS_CPN1EXT_INPUT; //比较器负端输入选择
	ACMP_InitStruct.ACMP_Delay_time = CP_NODelay_time;	  //输出延迟配置
	ACMP_InitStruct.ACMP_Blanking = CP_NOBLANKING;		  //比较器消隐源选择
	ACMP_InitStruct.ACMP_Is = CP_IS_POS;				  //比较器输出极性
	ACMP_InitStruct.ACMP_HYSEN = DISABLE;				  //迟滞使能配置
	ACMP_InitStruct.ACMP_FREN = ENABLE;					  //快速响应使能
	ACMP_InitStruct.ACMP_FS = DISABLE;					  //输出滤波使能配置

	ACMP_InitStruct.CMP_INTENMASK = ENABLE;				 //比较器连续比较中断使能屏蔽
	ACMP_InitStruct.CMP_SEQ_MODE = ENABLE;				 //连续模式使能
	ACMP_InitStruct.TRIG_MODE = CP_TIRG_INASOFT;		 //触发模式：软件或者外部硬件触发
	ACMP_InitStruct.CHNL_CNT_TIME = CHNL_CNT_TIME_64CLK; //比较器通道切换时钟周期选择

	ACMP1_Init(&ACMP_InitStruct);

	ACMP1_SEQ_INPUT_SELECT(ENABLE, 18, 2);

	ACMP1_Cmd(ENABLE);
}
/******************
ACMP1为连续比较模式，硬件触发，不需要START
主频16M，硬件触发连续模式建议不超过1.5K；主频提高，硬件触发频率也可以随之增加
*****************************************/
void tim1_cfg_init()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	uint16_t TimerPeriod = 0;
	uint16_t Channel1Pulse = 0, Channel2Pulse = 0, Channel3Pulse = 0, Channel4Pulse = 0;
	TimerPeriod = 16000; // 16000000/16000;
	Channel1Pulse = TimerPeriod / 2;

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

	TIM_CtrlPWMOutputs(TIM1, ENABLE); //配置TRGO触发ADC可不需要使能，配置通道CCx触发,或通过IO观测PWM波形，必须使能；

	TIM_Cmd(TIM1, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	//配置管脚为复用模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	/* GPIOA GPIOE Clocks enable */
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_2); // TIM1_CH1
}
void acmp2_cfg()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_6); ////OUT

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource1, GPIO_AF_1); // CP2_P_6[0]

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource6, GPIO_AF_2); // CP2_P_6[1]

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_2); ////CP2_N_7[2]

	ACMP_InitTypeDef ACMP_InitStruct;
	ACMP_InitStruct.ACMP_Delay_time = CP_NODelay_time; //输出延迟配置
	ACMP_InitStruct.ACMP_Blanking = CP_NOBLANKING;	   //比较器消隐源选择
	ACMP_InitStruct.ACMP_Is = CP_IS_POS;			   //比较器输出极性
	ACMP_InitStruct.ACMP_HYSEN = DISABLE;			   //迟滞使能配置
	ACMP_InitStruct.ACMP_FREN = ENABLE;				   //快速响应使能
	ACMP_InitStruct.ACMP_FS = DISABLE;				   //输出滤波使能配置

	ACMP_InitStruct.CMP_INTENMASK = ENABLE;				 //比较器连续比较中断使能屏蔽
	ACMP_InitStruct.CMP_SEQ_MODE = ENABLE;				 //连续模式使能
	ACMP_InitStruct.TRIG_MODE = CP_TIRG_EXTEN;			 //触发模式：软件或者外部硬件触发
	ACMP_InitStruct.CHNL_CNT_TIME = CHNL_CNT_TIME_64CLK; //比较器通道切换时钟周期选择

	ACMP_InitStruct.EXTSELECT = ENABLE_EXTSELG0;			  // Two sets of trigger sources enable control bits
	ACMP_InitStruct.EXTEN_Signal_andmode = ENABLE;			  // Trigger signal logic 'or' or 'and'
	ACMP_InitStruct.CP_EXTSP = CP_EXTSP_POS;				  //触发信号极性选择
	ACMP_InitStruct.SYN_MODE = CP_SYN_MODE;					  //外部触发同步或异步
	ACMP_InitStruct.TRIG_SOURCE = TRIG_TIM1_CC1;			  //触发源选择
	ACMP_InitStruct.TRIG_DELAY_TIME = TRIG_DELAY_TIME_128CLK; //外部触发延迟时钟
	ACMP_InitStruct.EXTEN_EDGE_MODE = CP_Edge_model;		  //外部触发信号方式
	ACMP_InitStruct.EXTEN_MODE_SEL = CP_EXTEN_RISE;			  //外部触发模式选择
	ACMP2_Init(&ACMP_InitStruct);
	ACMP2_SEQ_INPUT_SELECT(ENABLE, 3, 2);
	ACMP2_Cmd(ENABLE);
}

int main()
{
	SystemInit();
	SetSysClock();//主频配置
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_ANACTRL, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM1, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);

	DAC0_cfg();	 // DAC0_OUT=PA10
	acmp0_cfg(); // PA0(OUT) PA1(P) DAC0(N)/PF0

	acmp1_cfg(); // PA2(OUT) PF1(P)  PA3(P)  PF7(N)

	tim1_cfg_init();
	acmp2_cfg(); // PA5(OUT) PB1(P) PF6(P)  PB6(N)
	while (1)
	{
		SATRT_OFACMP1(); //连续比较软件触发需要配置START，START一次，转换一个序列

		delay(1000);
	}
}
