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
/************
demo�������񷽰�������ACMP1_OUT

����SYSCTRL_EDU_CFGx�Ĵ���ѡ�����봥��Դ

ͨ��1��2���ڿ�ѡ��λģʽ����CCRx�Ĵ�����ֵ��Ϊ����ʱ�䡢������/�½���ʱ��
*********************************************************************************************/
uint16_t IC1Value1 = 0, IC1Value2 = 0;

void DAC1_cfg()
{
  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_2); // DAC1_OUT

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
  DAC_SetDac_10B_Data(DAC1, DAC_Align_10B_R, 0x136);
  DAC_SoftwareTriggerCmd(DAC1, ENABLE); //�������ʹ�ܣ���ʾ���� DAC ��һ�δ�������(ѡ�������������)
}
void acmp1_cfg()
{
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_6); ////out

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_1); // CP1_P_4[1]

  ACMP_InitTypeDef ACMP_InitStruct;
  ACMP_InitStruct.ACMP_P_Select = CP1_PS_CPP1EXT_INPUT; //�Ƚ�����������ѡ��
  ACMP_InitStruct.ACMP_N_Select = CP1_NS_DAC1OUT;       //�Ƚ�����������ѡ��
  ACMP_InitStruct.ACMP_Delay_time = CP_NODelay_time;    //����ӳ�����
  ACMP_InitStruct.ACMP_Blanking = CP_NOBLANKING;        //�Ƚ�������Դѡ��
  ACMP_InitStruct.ACMP_Is = CP_IS_POS;                  //�Ƚ����������
  ACMP_InitStruct.ACMP_HYSEN = DISABLE;                 //����ʹ������
  ACMP_InitStruct.ACMP_FREN = ENABLE;                   //������Ӧʹ��
  ACMP_InitStruct.ACMP_FS = DISABLE;                    //����˲�ʹ������

  ACMP_InitStruct.CMP_INTENMASK = ENABLE;              //�Ƚ��������Ƚ��ж�ʹ������
  ACMP_InitStruct.CMP_SEQ_MODE = DISABLE;              //����ģʽʹ��
  ACMP_InitStruct.TRIG_MODE = CP_TIRG_INASOFT;         //����ģʽ����������ⲿӲ������
  ACMP_InitStruct.CHNL_CNT_TIME = CHNL_CNT_TIME_64CLK; //�Ƚ���ͨ���л�ʱ������ѡ��

  ACMP1_Init(&ACMP_InitStruct);
  ACMP1_SEQ_INPUT_SELECT(DISABLE, 1, 0); //ѡ������ͨ�����Ƿ����������ˣ�����
  ACMP1_Cmd(ENABLE);
}
void TIM3_CFG_CH1()
{
  TIM_ICInitTypeDef TIM_ICInitStructure;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  TIM_TimeBaseStructure.TIM_Prescaler = 0x0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = 0xffff;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;
  TIM_ICInit(TIM3, &TIM_ICInitStructure);

  TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_IndirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;
  TIM_ICInit(TIM3, &TIM_ICInitStructure);

  TIM3_IntputSourceCfg(TIM3_INPUT_TI1, TIM3_IntputSource_ACMP1_OUTPUT); // ���ò���Դ��TIM3 TI1����ACMP1_OUTPUT

  TIM_DTS_Cfg(TIM3);
  TIM_TI1E_Set(TIM3);
  TIM_SelectInputTrigger(TIM3, TIM_TS_TI1FP1);                 //ѡ��TIM3���봥��Դ��TIM���˲���ʱ������1
  TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset);              //ѡ��ӻ�ģʽ����λģʽ
  TIM_SelectMasterSlaveMode(TIM3, TIM_MasterSlaveMode_Enable); //������λģʽ
  TIM_ITConfig(TIM3, TIM_IT_CC1, ENABLE);                      //����CC1�ж�

  /* TIM enable counter */
  TIM_Cmd(TIM3, ENABLE);

  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

int main()
{
  SystemInit();
  SetSysClock(); //��Ƶ����
  RCC_APB0PeriphClockCmd(RCC_APB0Periph_TIM3, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_ANACTRL, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);

  DAC1_cfg();  // DAC1_OUT=PA5
  acmp1_cfg(); // PA2(OUT) PA3(P) DAC1(N)

  TIM3_CFG_CH1();
  while (1)
    ;
}

//ѡ��ͨ��1��2����
void TIM3_Handler(void)
{
  IC1Value1 = TIM3->CCR1; //����ʱ��
  IC1Value2 = TIM3->CCR2; //�ߵ�ƽʱ��
  TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);
}