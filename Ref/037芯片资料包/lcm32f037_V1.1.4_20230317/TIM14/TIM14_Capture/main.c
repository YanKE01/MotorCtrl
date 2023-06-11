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
/***********
TIM14的捕获，1通道
********************************************************************************8*/
uint16_t TimerPeriod = 0;
uint16_t Channel1Pulse = 0;

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
void NVIC_Configuration()
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Enable the TIM1 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM14_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
void TIM14_CFG_CH1()
{
  TIM_ICInitTypeDef TIM_ICInitStructure;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

  /* Time Base configuration */
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = 0xffff;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInit(TIM14, &TIM_TimeBaseStructure);

  TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;
  TIM_ICInit(TIM14, &TIM_ICInitStructure);

  TIM_DTS_Cfg(TIM14);
  TIM_TI1E_Set(TIM14);
  TIM_ITConfig(TIM14, TIM_IT_CC1, ENABLE);
  TIM_Cmd(TIM14, ENABLE);
}

int main()
{
  SystemInit();
  SetSysClock(); // 主频配置
  RCC_APB0PeriphClockCmd(RCC_APB0Periph_TIM14, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  GPIO_Config();
  NVIC_Configuration();
  TIM14_CFG_CH1();

  while (1)
    ;
}
uint16_t Value, IC1Value1, IC1Value1Old;
void TIM14_Handler(void)
{
  IC1Value1 = TIM14->CCR1;
  if ((IC1Value1 > IC1Value1Old) && (IC1Value1Old != 0))
  {
    Value = IC1Value1 - IC1Value1Old;
  }
  IC1Value1Old = IC1Value1;
  TIM_ClearITPendingBit(TIM14, TIM_IT_CC1);
}
