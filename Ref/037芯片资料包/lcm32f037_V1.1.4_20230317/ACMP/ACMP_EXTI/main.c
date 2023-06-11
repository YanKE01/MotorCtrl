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
3·�Ƚ������Ƚ���������ӵ��ڲ�����չ�жϺ��¼���������ÿ���ж϶�������Ӧ���ж��̣߳����Բ�����Ӧ��
�жϺ��¼��������������ڵ͹���ģʽ�Ļ��ѣ�
***************************************/

/**************************
DAC0_OUT��ΪACMP0���룬�����ⲿIO����;��ѡ���ⲿ����;
�����ⲿ��չ�ж� EXTI �� LINE19��
********************************************************/
void DAC0_cfg()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_2); //���ڹ۲�DAC0_OUT

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
	DAC_SoftwareTriggerCmd(DAC0, ENABLE); //�������ʹ�ܣ���ʾ���� DAC ��һ�δ�������(ѡ�������������)
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
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_2); //CP0_P_1[1]

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource0, GPIO_AF_1); ////CP0_N_3[2]

	ACMP_InitTypeDef ACMP_InitStruct;
	ACMP_InitStruct.ACMP_P_Select = CP0_PS_CPP0EXT_INPUT; //�Ƚ�����������ѡ��
	ACMP_InitStruct.ACMP_N_Select = CP0_NS_DAC0OUT;		  //�Ƚ�����������ѡ��
	ACMP_InitStruct.ACMP_Delay_time = CP_NODelay_time;	  //����ӳ�����
	ACMP_InitStruct.ACMP_Blanking = CP_NOBLANKING;		  //�Ƚ�������Դѡ��
	ACMP_InitStruct.ACMP_Is = CP_IS_POS;				  //�Ƚ����������
	ACMP_InitStruct.ACMP_HYSEN = DISABLE;				  //����ʹ������
	ACMP_InitStruct.ACMP_FREN = ENABLE;					  //������Ӧʹ��
	ACMP_InitStruct.ACMP_FS = DISABLE;					  //����˲�ʹ������

	ACMP_InitStruct.CMP_INTENMASK = ENABLE;				 //�Ƚ��������Ƚ��ж�ʹ������
	ACMP_InitStruct.CMP_SEQ_MODE = DISABLE;				 //����ģʽʹ��
	ACMP_InitStruct.TRIG_MODE = CP_TIRG_INASOFT;		 //����ģʽ����������ⲿӲ������
	ACMP_InitStruct.CHNL_CNT_TIME = CHNL_CNT_TIME_64CLK; //�Ƚ���ͨ���л�ʱ������ѡ��

	ACMP0_SEQ_INPUT_SELECT(DISABLE, 5, 2); //ѡ������ͨ�����Ƿ����������ˣ�����
	ACMP0_Cmd(ENABLE);

	NVIC_ClearPendingIRQ(LCD_ACMP0_2_IRQn);
	NVIC_EnableIRQ(LCD_ACMP0_2_IRQn);
}

void EXTI_Config()
{
	EXTI_InitTypeDef EXTI_InitStruct;
	EXTI_InitStruct.EXTI_Line = EXTI_Line19;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStruct);
}
int main()
{
	SystemInit();
	SetSysClock();//��Ƶ����
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_ANACTRL, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_EXTI, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);

	EXTI_Config();
	DAC0_cfg();
	acmp0_cfg();
	while (1)
		;
}

void LCD_ACMP0_2_Handler()
{
	EXTI_ClearITPendingBit(EXTI_Line19);
}
