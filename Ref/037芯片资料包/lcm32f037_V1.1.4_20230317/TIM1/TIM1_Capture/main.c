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
demo给出两种捕获通道组合，
通道1、2由于可选择复位模式，则CCRx寄存器的值即为周期时间、上升沿/下降沿时间
通道3、4没有复位模式，即需要通过计算得出周期时间、上升沿/下降沿时间
*********************************************************************************************/
uint16_t IC1Value1 = 0, IC1Value2 = 0;
uint16_t IC3Value1 = 0, IC3Value1Old = 0, IC3Value2 = 0, Value3 = 0, Value4 = 0;

void GPIO_Config()
{
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_2); // tim1_ch1  PA8

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_3); // tim1_ch3  PA10
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

  TIM_DTS_Cfg(TIM1);
  TIM_TI1E_Set(TIM1);
  TIM_SelectInputTrigger(TIM1, TIM_TS_TI1FP1);                 //选择TIM1输入触发源：TIM经滤波定时器输入1
  TIM_SelectSlaveMode(TIM1, TIM_SlaveMode_Reset);              //选择从机模式：复位模式
  TIM_SelectMasterSlaveMode(TIM1, TIM_MasterSlaveMode_Enable); //开启复位模式
  TIM_ITConfig(TIM1, TIM_IT_CC1, ENABLE);                      //开启CC1中断

  /* TIM enable counter */
  TIM_Cmd(TIM1, ENABLE);
}

void TIM1_CFG_CH3()
{
  TIM_ICInitTypeDef TIM_ICInitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

  TIM_TimeBaseStructure.TIM_Prescaler = 0x0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = 0xffff;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

  TIM_ICInitStructure.TIM_Channel = TIM_Channel_3;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;
  TIM_ICInit(TIM1, &TIM_ICInitStructure);

  TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_IndirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;
  TIM_ICInit(TIM1, &TIM_ICInitStructure);

  TIM_DTS_Cfg(TIM1);
  TIM_TI3E_Set(TIM1);
  TIM_ITConfig(TIM1, TIM_IT_CC3, ENABLE); //开启CC3中断
  TIM_Cmd(TIM1, ENABLE);                  // TIM enable counter
}

int main()
{
  SystemInit();
  SetSysClock(); //主频配置
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM1, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  NVIC_Configuration(); //设置NVIC参数
  GPIO_Config();        // PWM GPIOSET

  //	TIM1_CFG_CH1(); //TIM1 SET

  TIM1_CFG_CH3(); // TIM1 SET
  while (1)
    ;
}

//选择通道1、2捕获
// void TIM1_CC_Handler(void)
//{
//	IC1Value1 = TIM1->CCR1; //周期时间
//  IC1Value2 = TIM1->CCR2; //高电平时间
//  TIM_ClearITPendingBit(TIM1, TIM_IT_CC1);
//}

//选择通道3、4捕获
void TIM1_CC_Handler(void)
{
  IC3Value1 = TIM1->CCR3;
  IC3Value2 = TIM1->CCR4;
  if ((IC3Value1 > IC3Value1Old) && (IC3Value1Old != 0))
  {
    Value4 = IC3Value1 - IC3Value1Old; //周期时间
  }
  if ((IC3Value1 > IC3Value2) && (IC3Value2 != 0))
  {
    Value3 = IC3Value1 - IC3Value2; //低电平时间
  }
  IC3Value1Old = IC3Value1;
  TIM_ClearITPendingBit(TIM1, TIM_IT_CC3);
}
