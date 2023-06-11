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
#include "lcm32f037_pwr.h"
/*********
��LVDΪ����Դ����ɲ���ж�,
����ͨ����Դ����ͬһ��·�����˹���Ϊ����·����������ɺ�ɲ��ʹ�ܼ��ɣ�����Ҫ���ü���
*********************************************************************/
uint16_t TimerPeriod = 0;
uint16_t Channel1Pulse = 0;

void GPIO_Config()
{
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_2); // tim1_ch1   pA8
}

static void tim1_cfg_init()
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure;

  TimerPeriod = 800;
  Channel1Pulse = 400;

  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = TimerPeriod;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM_OCInitStructure.TIM_Pulse = Channel1Pulse;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;

  TIM_OCInitStructure.TIM_Pulse = Channel1Pulse;
  TIM_OC1Init(TIM1, &TIM_OCInitStructure);

  PWR_LVDConfig(PWR_LVDInternal, PWR_LVDInternal_3V6); // ����ڲ���ѹ�����õ�ѹ��
  PWR_LVDCmd(ENABLE);
  chipctrl_access();
  CHIPCTRL->CTRL_b.LVD_LOCK = 1; // 1�� LVD ������� TIM1/15/16/17 �� Break ��������
  __dekey();

  TIM_BDTRInitTypeDef TIM_BDTRInitStruct; // ����ɲ��
  TIM_BDTRInitStruct.TIM_OSSRState = TIM_OSSRState_Disable;
  TIM_BDTRInitStruct.TIM_OSSIState = TIM_OSSIState_Disable;
  TIM_BDTRInitStruct.TIM_LOCKLevel = TIM_LOCKLevel_OFF;
  TIM_BDTRInitStruct.TIM_DeadTime = 0x00;
  TIM_BDTRInitStruct.TIM_Break = TIM_Break_Enable;
  TIM_BDTRInitStruct.TIM_BreakPolarity = TIM_BreakPolarity_High; // �ߵ�ƽ����ɲ��
  TIM_BDTRInitStruct.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
  TIM_BDTRConfig(TIM1, &TIM_BDTRInitStruct);

  // TIM1->SR =0;//��ʼ����һ���жϱ�־

  TIM_ITConfig(TIM1, TIM_DIER_BIE, ENABLE); // ɲ���ж�BIEʹ��

  TIM_CtrlPWMOutputs(TIM1, ENABLE);

  TIM_Cmd(TIM1, ENABLE);
}

int main()
{

  SystemInit();
  SetSysClock(); // ��Ƶ����
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM1, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

  GPIO_Config();   // PWM GPIOSET
  tim1_cfg_init(); // TIM1 SET

  while (1)
    ;
}
void TIM1_NON_CC_Handler(void) // ɲ���ж�
{
  TIM_ClearITPendingBit(TIM1, TIM_IT_Break);
}
