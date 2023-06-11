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
/*********
���ⲿIO��Ϊ����Դ����ɲ���жϣ�
�û��ɸ����Լ���Ҫ����SYSCTRL->EDU_CFG6�Ĵ���ѡ��ɲ������Դ
*********************************************************************/
uint16_t TimerPeriod = 0;
uint16_t Channel1Pulse = 0;

void GPIO_Config()
{
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_0); // tim15_ch1   pA2

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1); // tim15_bkin    pa9
}

static void tim15_cfg_init()
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

  TIM_TimeBaseInit(TIM15, &TIM_TimeBaseStructure);

  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM_OCInitStructure.TIM_Pulse = Channel1Pulse;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;

  TIM_OCInitStructure.TIM_Pulse = Channel1Pulse;
  TIM_OC1Init(TIM15, &TIM_OCInitStructure);

  /*����ɲ���жϣ���Ҫ�����ô���Դ������BDTR�Ĵ����еļ���BKP,�������ʹ��BKE��
  ���߳�ʼ����һ��SR�Ĵ������жϱ�־*/
  sysctrl_access();
  SYSCTRL->EDU_CFG6 |= (1 << 14); //ɲ������Դѡ�� �ⲿIO�ڣ�PA9
  __dekey();

  TIM_BDTRInitTypeDef TIM_BDTRInitStruct; //����ɲ��
  TIM_BDTRInitStruct.TIM_OSSRState = TIM_OSSRState_Disable;
  TIM_BDTRInitStruct.TIM_OSSIState = TIM_OSSIState_Disable;
  TIM_BDTRInitStruct.TIM_LOCKLevel = TIM_LOCKLevel_OFF;
  TIM_BDTRInitStruct.TIM_DeadTime = 0x00;
  TIM_BDTRInitStruct.TIM_Break = TIM_Break_Enable;
  TIM_BDTRInitStruct.TIM_BreakPolarity = TIM_BreakPolarity_High; //�ߵ�ƽ����ɲ��
  TIM_BDTRInitStruct.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
  TIM_BDTRConfig(TIM15, &TIM_BDTRInitStruct);

  // TIM15->SR =0;//��ʼ����һ���жϱ�־

  TIM_ITConfig(TIM15, TIM_DIER_BIE, ENABLE); //ɲ���ж�BIEʹ��

  TIM_CtrlPWMOutputs(TIM15, ENABLE);

  TIM_Cmd(TIM15, ENABLE);
}

int main()
{

  SystemInit();
  SetSysClock(); //��Ƶ����
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM15, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

  GPIO_Config();    // PWM GPIOSET
  tim15_cfg_init(); // TIM15 SET

  while (1)
    ;
}
void TIM15_Handler(void) //ɲ���ж�
{
  TIM_ClearITPendingBit(TIM15, TIM_IT_Break);
}
