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
  ADC�ڲ�ͨ����
	OPA0O(OP0OEX)=ADCIN[11]/��PA3�ػ���ADCIN[3];
	OPA0O(OP1OEX)=ADCIN[12]/��PA7�ػ���ADCIN[7];
	OPA0O(OP2OEX)=ADCIN[2]/��PB1�ػ���ADCIN[9];

	DAC_OUT0:���ӵ��ⲿ�˿�PA10��ģ��ͨ��2������ͨ��ͬʱ��PA10��1ͨ�������Իػ���ADCIN[15]
			 ���ӵ��ⲿ�˿�PA4��ģ��ͨ��1������ͨ��ͬʱ��PA4��2ͨ�������Իػ���ADCIN[4]

	DAC_OUT1:���ӵ��ⲿ�˿�PA5��ģ��ͨ��2������ͨ��ͬʱ��PA4��1ͨ�������Իػ���ADCIN[5]

	�¶ȴ��������� ST=1��SV=0 ʱѡ�� ADC_IN16������ͨ��(ADC_IN0~15��ADC_IN17)���á�
	VDDA���� ST=1��SV=1ʱѡ�� ADC_IN17(VDD)������ͨ��(ADC_IN0~15��ADC_IN16)���á�
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
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_2); //��������

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	//	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_2);//opa0�����PA3 ���Բ���
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_1 | GPIO_AF_2); //ͨ��PA3�ػ�ʹOP0O�ӵ�ADCIN[3];OP0O�ڲ�ֱ��ADCIN[11]

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
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_2); //��������

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	//	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_2);//opa1�����PA7 ���Բ���
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_1 | GPIO_AF_2); //ͨ��PA7�ػ�ʹOP1O�ӵ�ADCIN[7];OP1O�ڲ�ֱ��ADCIN[12]

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
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource0, GPIO_AF_2); //��������

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	//	GPIO_PinAFConfig(GPIOB,GPIO_PinSource1,GPIO_AF_2);//opa2�����PB1 ���Բ���
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource1, GPIO_AF_1 | GPIO_AF_2); //ͨ��PB1�ػ�ʹOP2O�ӵ�ADCIN[9];OP0O�ڲ�ֱ��ADCIN[2]

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
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource4, GPIO_AF_1 | GPIO_AF_2); // DAC0_OUT:�ػ����ӵ�ADCIN[4]

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1 | GPIO_AF_2); // DAC0_OUT:�ػ����ӵ�ADCIN[15]

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
	DAC_SoftwareTriggerCmd(DAC0, ENABLE); //�������ʹ�ܣ���ʾ���� DAC ��һ�δ�������(ѡ�������������)
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
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_1 | GPIO_AF_2); // DAC1_OUT:�ػ����ӵ�ADCIN[5]

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
	DAC_SoftwareTriggerCmd(DAC1, ENABLE); //�������ʹ�ܣ���ʾ���� DAC ��һ�δ�������(ѡ�������������)
}

void ADCConfiguration(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;

	ADC_InitStructure.ADC_ClkMode = ADC_ClockMode_sysnClk;						//ѡ��ת��ʱ��Դ
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;						//����
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;							//ת��ģʽ0=����;1=����;��ʾ����һ��ת��һ��ͨ������һ������
	ADC_InitStructure.ADC_AutoWatiMode = ENABLE;								//��λ��������ú������ʹ���� / �ر��Զ��ӳ�ת��ģʽ
	ADC_InitStructure.ADC_DMATRIG_LEVEL = FIFO_DMA_NOEMPTY;						//������ô��� DMA ����� FIFO ˮƽ���� DMAEN ʹ��ǰ�������ã�������� DMA �ڰ���ʱ�Ĵ���
	ADC_InitStructure.ADC_DMA = ENABLE;											//�Ƿ������� DMA ���������Զ�����ת���Ľ������
	ADC_InitStructure.ADC_DiscMode = DISABLE;									// 0=����ģʽ��ֹ;1=����ģʽ����
	ADC_InitStructure.ADC_SamecMode = DISABLE;									//����ģʽѡ��0=��������;1=ͬʱ����
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None; //������ʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_SoftWare;		//����Դ
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;						//���ݶ��뷽ʽ
	ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;				// 0=��ǰɨ�� (�� CHSEL0 �� CHSEL15);1=���ɨ��( �� CHSEL15 �� CHSEL0)
	ADC_InitStructure.ADC_Vref = ADC_Vref_Internal_3V3;							//�ο���ѹѡ��
	ADC_Init(ADC, &ADC_InitStructure);

	/*****************OPA����	****************/
	ADC_ChannelConfig(ADC, ADC_Channel_3, 15, 7, 7); //����Żػ�
	ADC_ChannelConfig(ADC, ADC_Channel_7, 15, 7, 7);
	ADC_ChannelConfig(ADC, ADC_Channel_9, 15, 7, 7);

	ADC_ChannelConfig(ADC, ADC_Channel_11, 15, 7, 7); //�ڲ�ֱ��
	ADC_ChannelConfig(ADC, ADC_Channel_12, 15, 7, 7);
	ADC_ChannelConfig(ADC, ADC_Channel_2, 15, 7, 7);

	ADC_ChannelConfig(ADC, ADC_Channel_4, 15, 7, 7);  // DAC0_OUT: PA4�ػ�
	ADC_ChannelConfig(ADC, ADC_Channel_15, 15, 7, 7); // DAC0_OUT: PA10�ػ�
	ADC_ChannelConfig(ADC, ADC_Channel_5, 15, 7, 7);  // DAC1_OUT: PA5�ػ�

	//	ADC_ChannelConfig(ADC,ADC_Channel_16,15,7,7); //�¶ȴ�����: �� ST=1��SV=0 ʱѡ�� ADC_IN16������ͨ��(ADC_IN0~15��ADC_IN17)����
	//	ADC_ChannelConfig(ADC,ADC_Channel_17,15,7,7);//VDDA���� ST=1��SV=1ʱѡ�� ADC_IN17(VDD)������ͨ��(ADC_IN0~15��ADC_IN16)����

	ADC_Cmd(ADC, ENABLE);

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
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure); //�����Ƿ��Ǵ洢�����洢��ģʽ����
	/* Enable DMA1 channel1 TC interupt*/
	DMA_ITConfig(DMA1_Channel1, DMA1_FLAG_TC1, ENABLE); //����DMA������ɺ��ж�
	DMA_RemapConfig(DMA1_Channel1, DMA_ReqNum5, DMA_REQ_ADC);
	/* Enable DMA1 channel1 */
	DMA_Cmd(DMA1_Channel1, ENABLE);
#endif
}

int main()
{
	SystemInit();
	SetSysClock(); //��Ƶ����

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_ADC, ENABLE); //��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_ANACTRL, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);
	NVIC_ClearPendingIRQ(DMAC_CH1_2_IRQn);
	NVIC_EnableIRQ(DMAC_CH1_2_IRQn); //ʹ��DMA�ж�

	OPA0_Init();
	OPA1_Init();
	OPA2_Init();
	DAC0_Config();
	DAC1_Config();

	ADCConfiguration();			 // ADC��ʼ��
	ADC_StartOfConversion(ADC1); // ADC ��ʼת������
	while (1)
		;
}

void DMAC_CH1_2_Handler(void) // 40us
{
	DMA_ClearITPendingBit(DMA1_FLAG_TC1);
}
