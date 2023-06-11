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
/************************
TIM6计数器功能，向上计数模式，向下计数模式，中央对齐模式
**********************************************************************/
void NVIC_Configuration()
{
  NVIC_InitTypeDef NVIC_InitStructure;

  NVIC_InitStructure.NVIC_IRQChannel = TIM6_DAC0_2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

static void tim6_cfg_init()
{
  NVIC_InitTypeDef NVIC_InitStructure;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

  TIM_TimeBaseStructure.TIM_Prescaler = 1599; //预分频系数设置位1599，即TIM_CLK=16/(1599+1)=10K;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = 1000;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);

  TIM_ARRPreloadConfig(TIM6, ENABLE);
  TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE); // TIM6 只有更新中断，DMA中断
  TIM_Cmd(TIM6, ENABLE);
}

void GPIO_Config()
{
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}
int main()
{
  SystemInit();
  SetSysClock(); //主频配置
  RCC_APB0PeriphClockCmd(RCC_APB0Periph_TIM6, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  NVIC_Configuration(); //设置NVIC参数
  tim6_cfg_init();      // TIM6 SET
  GPIO_Config();        //电平翻转观测计数
  while (1)
    ;
}

void TIM6_DAC0_2_Handler(void)
{
  GPIO_WriteBit(GPIOA, GPIO_Pin_0, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_0)));
  TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
}
