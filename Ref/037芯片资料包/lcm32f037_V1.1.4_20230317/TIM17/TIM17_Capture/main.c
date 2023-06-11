#include "lcm32f037_conf.h"
#include "lcm32f037.h"
#include "lcm32f037_rcc.h"
#include "lcm32f037_gpio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lcm32f037_tim.h"
/************
demo给出捕获方案，
仅一路通道，可捕获周期数
*********************************************************************************************/
uint16_t IC1Value = 0, IC1ValueOld = 0, Value = 0;

void GPIO_Config()
{
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource4, GPIO_AF_3); // tim17_ch1   pA4
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

  TIM_DTS_Cfg(TIM17);
  TIM_TI1E_Set(TIM17);
  TIM_SelectInputTrigger(TIM17, TIM_TS_TI1FP1); //选择TIM17输入触发源：TIM经滤波定时器输入1
  TIM_ITConfig(TIM17, TIM_IT_CC1, ENABLE);      //开启CC1中断

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
  SetSysClock(); //主频配置
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM17, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  GPIO_Config();
  TIM17_CFG_CH1();
  while (1)
    ;
}

void TIM17_Handler(void)
{
  IC1Value = TIM17->CCR1;
  if ((IC1Value > IC1ValueOld) && (IC1ValueOld != 0))
  {
    Value = IC1Value - IC1ValueOld; //周期时间
  }
  IC1ValueOld = IC1Value;
  TIM_ClearITPendingBit(TIM17, TIM_IT_CC1);
}
