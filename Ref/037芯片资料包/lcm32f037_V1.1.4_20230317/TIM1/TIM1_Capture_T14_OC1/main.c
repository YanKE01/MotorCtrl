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
demo�������񷽰�������TIM14_OC1

����SYSCTRL_EDU_CFGx�Ĵ���ѡ�����봥��Դ

ͨ��1��2���ڿ�ѡ��λģʽ����CCRx�Ĵ�����ֵ��Ϊ����ʱ�䡢������/�½���ʱ��
*********************************************************************************************/
uint16_t IC1Value1 = 0, IC1Value2 = 0;

void GPIO_Config()
{
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource4, GPIO_AF_4); // tim14_ch1   pA4
}

static void tim14_cfg_init()
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure;
  uint16_t TimerPeriod = 0;
  uint16_t Channel1Pulse = 0;

  TimerPeriod = 9600;
  Channel1Pulse = 4800;

  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = TimerPeriod;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM14, &TIM_TimeBaseStructure);

  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //������ǿ�����ģʽ����������Ĵ���TIM14->CCMR14��OC1M[2:0]
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; // TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;

  TIM_OCInitStructure.TIM_Pulse = Channel1Pulse;
  TIM_OC1Init(TIM14, &TIM_OCInitStructure);

  TIM_Cmd(TIM14, ENABLE);
}

void NVIC_Configuration()
{
  NVIC_InitTypeDef NVIC_InitStructure;

  NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void TIM1_CFG_CH1()
{
  TIM_ICInitTypeDef TIM_ICInitStructure;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

  /* Time Base configuration */
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = 0xffff;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

  TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;
  TIM_ICInit(TIM1, &TIM_ICInitStructure);

  TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_IndirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;
  TIM_ICInit(TIM1, &TIM_ICInitStructure);

  TIM1_IntputSourceCfg(TIM1_INPUT_TI1, TIM1_IntputSource_TIM14_OC1_TRIG); // ���ò���Դ��TIM1 TI1����TIM14_OC1_TRIG

  TIM_DTS_Cfg(TIM1);
  TIM_TI1E_Set(TIM1);
  TIM_SelectInputTrigger(TIM1, TIM_TS_TI1FP1);                 //ѡ��TIM1���봥��Դ��TIM���˲���ʱ������1
  TIM_SelectSlaveMode(TIM1, TIM_SlaveMode_Reset);              //ѡ��ӻ�ģʽ����λģʽ
  TIM_SelectMasterSlaveMode(TIM1, TIM_MasterSlaveMode_Enable); //������λģʽ
  TIM_ITConfig(TIM1, TIM_IT_CC1, ENABLE);                      //����CC1�ж�

  /* TIM enable counter */
  TIM_Cmd(TIM1, ENABLE);
}
int main()
{
  SystemInit();
  SetSysClock(); //��Ƶ����
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM1, ENABLE);
  RCC_APB0PeriphClockCmd(RCC_APB0Periph_TIM14, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

  NVIC_Configuration(); //����NVIC����
  GPIO_Config();        // PWM GPIOSET
  tim14_cfg_init();     // TIM14 SET
  TIM1_CFG_CH1();       // TIM1 SET
  while (1)
    ;
}

//ѡ��ͨ��1��2����
void TIM1_CC_Handler(void)
{
  IC1Value1 = TIM1->CCR1; //����ʱ��
  IC1Value2 = TIM1->CCR2; //�ߵ�ƽʱ��
  TIM_ClearITPendingBit(TIM1, TIM_IT_CC1);
}
