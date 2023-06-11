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

	/*����ɲ���жϣ���Ҫ�����ô���Դ������BDTR�Ĵ����еļ���BKP,�������ʹ�ܡ�
	���߳�ʼ����һ��SR�Ĵ������жϱ�־*/
	sysctrl_access();
	SYSCTRL->EDU_CFG4 |= (1 << 9); //ɲ������Դѡ�� acmp1
	__dekey();

	TIM_BDTRInitTypeDef TIM_BDTRInitStruct; //����ɲ��
	TIM_BDTRInitStruct.TIM_OSSRState = TIM_OSSRState_Disable;
	TIM_BDTRInitStruct.TIM_OSSIState = TIM_OSSIState_Disable;
	TIM_BDTRInitStruct.TIM_LOCKLevel = TIM_LOCKLevel_OFF;
	TIM_BDTRInitStruct.TIM_DeadTime = 0x00;
	TIM_BDTRInitStruct.TIM_Break = TIM_Break_Enable;
	TIM_BDTRInitStruct.TIM_BreakPolarity = TIM_BreakPolarity_High;
	TIM_BDTRInitStruct.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
	TIM_BDTRConfig(TIM1, &TIM_BDTRInitStruct);

	// TIM1->SR =0;//��ʼ����һ���жϱ�־

	TIM_ITConfig(TIM1, TIM_DIER_BIE, ENABLE); //ɲ���ж�BIEʹ��

	TIM_SelectOutputTrigger(TIM1, TIM_TRGOSource_Update); //ѡ���������Դ

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

	ACMP_InitStruct.ACMP_P_Select = CP1_PS_CPP1EXT_INPUT; //��һ���ⲿ
	ACMP_InitStruct.ACMP_N_Select = CP1_NS_DAC1OUT;		  // DAC1/PB0
	ACMP_InitStruct.ACMP_Delay_time = CP_NODelay_time;	  //����ӳ�����
	ACMP_InitStruct.ACMP_Blanking = CP_NOBLANKING;		  //�Ƚ�������Դѡ��
	ACMP_InitStruct.ACMP_Is = CP_IS_POS;				  //�Ƚ����������
	ACMP_InitStruct.ACMP_HYSEN = DISABLE;				  //����ʹ������
	ACMP_InitStruct.ACMP_FREN = ENABLE;					  //������Ӧʹ��
	ACMP_InitStruct.ACMP_FS = DISABLE;					  //����˲�ʹ������

	ACMP_InitStruct.CMP_INTENMASK = DISABLE;			 //�Ƚ��������Ƚ��ж�ʹ������
	ACMP_InitStruct.CMP_SEQ_MODE = DISABLE;				 //����ģʽʹ��
	ACMP_InitStruct.TRIG_MODE = CP_TIRG_INASOFT;		 //����ģʽ����������ⲿӲ������
	ACMP_InitStruct.CHNL_CNT_TIME = CHNL_CNT_TIME_64CLK; //�Ƚ���ͨ���л�ʱ������ѡ��

	ACMP_InitStruct.EXTSELECT = ENABLE_EXTSELG0;			  // Two sets of trigger sources enable control bits
	ACMP_InitStruct.EXTEN_Signal_andmode = DISABLE;			  // Trigger signal logic 'or' or 'and'
	ACMP_InitStruct.CP_EXTSP = CP_EXTSP_POS;				  //�����źż���ѡ��
	ACMP_InitStruct.SYN_MODE = CP_SYN_MODE;					  //�ⲿ����ͬ�����첽
	ACMP_InitStruct.TRIG_SOURCE = TRIG_TIM1_CC1;			  //����Դѡ��
	ACMP_InitStruct.TRIG_DELAY_TIME = TRIG_DELAY_TIME_128CLK; //�ⲿ�����ӳ�ʱ��
	ACMP_InitStruct.EXTEN_EDGE_MODE = CP_Edge_model;		  //�ⲿ�����źŷ�ʽ
	ACMP_InitStruct.EXTEN_MODE_SEL = CP_EXTEN_RISE;			  //�ⲿ����ģʽѡ��

	ACMP_InitStruct.SYN_MODE = CP_SYN_MODE;
	ACMP1_Init(&ACMP_InitStruct);
	ACMP1_SEQ_INPUT_SELECT(DISABLE, 7, 1); // CP1P ѡ��OP0OUT �ڶ���
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
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_1); //��������

	//	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_3 ;
	//  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	//	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	//	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	//	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	//	GPIO_Init(GPIOA, &GPIO_InitStruct);
	//	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_2);//opa0�����PA3 ���Բ���

	OPA_InitTypeDef OPA_InitStruct;
	OPA_InitStruct.OPA_Oppselect = OPA0_Oppselect_PA2; // OPA0 P
	OPA_InitStruct.OPA_Opnselect = OPA0_Opnselect_PA4; // OPA0 N  �ⲿ�ӵ�
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
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_2); //��������

	//	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_7 ;
	//  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	//	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	//	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	//	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	//	GPIO_Init(GPIOA, &GPIO_InitStruct);
	//	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_2);//opa1�����PA7���Բ���

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
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_2); //��������

	//	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_1 ;
	//  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	//	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	//	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	//	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	//	GPIO_Init(GPIOB, &GPIO_InitStruct);
	//	GPIO_PinAFConfig(GPIOB,GPIO_PinSource1,GPIO_AF_2);//opa2�����PB1 ���Բ���

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
	ADC_InitStructure.ADC_ClkMode = ADC_ClockMode_sysnClk;						  //ѡ��ת��ʱ��Դ
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;						  //����
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;							  //ת��ģʽ0=����;1=����;��ʾ����һ��ת��һ��ͨ������һ������
	ADC_InitStructure.ADC_AutoWatiMode = ENABLE;								  //��λ��������ú������ʹ���� / �ر��Զ��ӳ�ת��ģʽ
	ADC_InitStructure.ADC_DMATRIG_LEVEL = FIFO_DMA_NOEMPTY;						  //������ô��� DMA ����� FIFO ˮƽ���� DMAEN ʹ��ǰ�������ã�������� DMA �ڰ���ʱ�Ĵ���
	ADC_InitStructure.ADC_DMA = ENABLE;											  //�Ƿ������� DMA ���������Զ�����ת���Ľ������
	ADC_InitStructure.ADC_DiscMode = DISABLE;									  // 0=����ģʽ��ֹ;1=����ģʽ����
	ADC_InitStructure.ADC_SamecMode = DISABLE;									  //����ģʽѡ��0=��������;1=ͬʱ����
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_Rising; //������ʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_TRGO;		  //����Դ
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;						  //���ݶ��뷽ʽ
	ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;				  // 0=��ǰɨ�� (�� CHSEL0 �� CHSEL15);1=���ɨ��( �� CHSEL15 �� CHSEL0)
	ADC_InitStructure.ADC_Vref = ADC_Vref_Internal_3V3;							  //�ο���ѹѡ��
	ADC_Init(ADC1, &ADC_InitStructure);

	ADC_ChannelConfig(ADC1, ADC_Channel_2, 25, 7, 7);
	ADC_ChannelConfig(ADC1, ADC_Channel_12, 25, 7, 7);

	ADC_Cmd(ADC1, ENABLE);

#if DMA_ENABLE
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA, ENABLE);

	/*DMA1 channel1 configuration ----------------------------------------------*/
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;				//��������DMA������������ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADCConvertedRawData;	//�ڴ����ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;						//�������ݴ��䷽�򣬼������Ǵ������ȡ���ݵ��ڴ滹�Ǵ��ڴ�����ݵ����裬���������Ǵ�����ADC_DR�Ĵ��������ݵ��ڴ�
	DMA_InitStructure.DMA_BufferSize = ADC_SIZE;							//����һ�δ����������Ĵ�С
	DMA_InitStructure.DMA_MSIZE = DMA_MSIZE_1;								//ͻ�������䳤��
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;		//���ô������ݵ�ʱ�� �����裩 ��ַ�ǲ��仹�ǵ�����
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;					//���ô������ݵ�ʱ�� ���ڴ� ����ַ�ǲ��仹�ǵ���
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word; //������������ݳ�����Ϊ�ֽڴ��䣨8bits�����ǰ��֣�16bits�������ִ��䣨32bits��
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;			//�����ڴ�����ݳ��ȣ�ͬ�ϡ�
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;							//�����Ƿ����ѭ���ɼ�
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;						//�������ȼ�
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;							//�ڴ浽�ڴ�ʹ��
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);							//�����Ƿ��Ǵ洢�����洢��ģʽ����

	DMA_ITConfig(DMA1_Channel1, DMA1_FLAG_TC1, ENABLE); //����DMA������ɺ��ж�

	DMA_RemapConfig(DMA1_Channel1, DMA_ReqNum5, DMA_REQ_ADC);

	DMA_Cmd(DMA1_Channel1, ENABLE);
#endif
}

int main()
{
	SystemInit();
	SetSysClock(); //��Ƶ����
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

	// ���ȼ��Ӹߵ���:TIM1_NON_CC_IRQn -> DMAC_CH1_2_IRQn
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_NON_CC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = DMAC_CH1_2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	OPA0_Init();	 // P=PA2; PA4�ӵ�
	DAC1_cfg();		 // OUT=PA5
	acmp1_cfg();	 // OUT=PB3
	SATRT_OFACMP1(); // only soft trigger need
	tim1_cfg_init(); // OPA0  PA2���� PA4�ӵ�->(OPA0O=CP1P )+ (DAC)->TIM1BK

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

void TIM1_NON_CC_Handler(void) //ɲ���ж�
{
	TIM_ClearITPendingBit(TIM1, TIM_IT_Break);
}
