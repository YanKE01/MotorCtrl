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

��һ·ͨ�����ɲ���������
*********************************************************************************************/
uint16_t IC1Value = 0, IC1ValueOld = 0, Value = 0;

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
void TIM17_CFG_CH1()
{
  NVIC_InitTypeDef NVIC_InitStructure;
  TIM_ICInitTypeDef TIM_ICInitStructure;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

  /* Time Base configuration */
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = 0xffff;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInit(TIM17, &TIM_TimeBaseStructure);

  TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;
  TIM_ICInit(TIM17, &TIM_ICInitStructure);

  TIM17_IntputSourceCfg(TIM17_INPUT_TI1, TIM17_IntputSource_ACMP1_OUTPUT); // ���ò���Դ��TIM17 TI1����ACMP1_OUTPUT

  TIM_DTS_Cfg(TIM17);
  TIM_TI1E_Set(TIM17);
  TIM_SelectInputTrigger(TIM17, TIM_TS_TI1FP1); //ѡ��TIM17���봥��Դ��TIM���˲���ʱ������1
  TIM_ITConfig(TIM17, TIM_IT_CC1, ENABLE);      //����CC1�ж�

  /* TIM enable counter */
  TIM_Cmd(TIM17, ENABLE);

  NVIC_InitStructure.NVIC_IRQChannel = TIM17_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
int main()
{
  SystemInit();
  SetSysClock(); //��Ƶ����
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM17, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_ANACTRL, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);

  DAC1_cfg();  // DAC1_OUT=PA5
  acmp1_cfg(); // PA2(OUT) PA3(P) DAC1(N)

  TIM17_CFG_CH1();
  while (1)
    ;
}

void TIM17_Handler(void)
{
  IC1Value = TIM17->CCR1;
  if ((IC1Value > IC1ValueOld) && (IC1ValueOld != 0))
  {
    Value = IC1Value - IC1ValueOld; //����ʱ��
  }
  IC1ValueOld = IC1Value;
  TIM_ClearITPendingBit(TIM17, TIM_IT_CC1);
}