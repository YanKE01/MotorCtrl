#include "lcm32f037_conf.h"
#include "lcm32f037.h"
#include "lcm32f037_rcc.h"
#include "lcm32f037_gpio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lcm32f037_tim.h"
/************************
TIM16���������ܣ����ϼ���ģʽ�����¼���ģʽ���������ģʽ
**********************************************************************/
static void tim16_cfg_init()
{
  NVIC_InitTypeDef NVIC_InitStructure;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

  TIM_TimeBaseStructure.TIM_Prescaler = 1599; //Ԥ��Ƶϵ������λ1599����TIM_CLK=16/(1599+1)=10K;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = 1000;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM16, &TIM_TimeBaseStructure);

  TIM_ARRPreloadConfig(TIM16, ENABLE);
  TIM_ITConfig(TIM16, TIM_IT_Update, ENABLE);
  TIM_Cmd(TIM16, ENABLE);

  NVIC_InitStructure.NVIC_IRQChannel = TIM16_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
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
  SetSysClock(); //��Ƶ����
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM16, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  tim16_cfg_init(); // TIM16 SET
  GPIO_Config();    //��ƽ��ת�۲����
  while (1)
    ;
}

void TIM16_Handler(void)
{
  GPIO_WriteBit(GPIOA, GPIO_Pin_0, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_0)));
  TIM_ClearITPendingBit(TIM16, TIM_IT_Update);
}
