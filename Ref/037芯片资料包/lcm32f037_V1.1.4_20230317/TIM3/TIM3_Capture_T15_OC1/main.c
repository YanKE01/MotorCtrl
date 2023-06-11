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
demo给出捕获方案，捕获TIM15_OC1

配置SYSCTRL_EDU_CFGx寄存器选择输入触发源

通道1、2由于可选择复位模式，则CCRx寄存器的值即为周期时间、上升沿/下降沿时间
*********************************************************************************************/
uint16_t IC1Value1 = 0, IC1Value2 = 0;

void GPIO_Config()
{
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_0); // tim15_ch1   pA2
}

static void tim15_cfg_init()
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure;
  uint16_t TimerPeriod = 0;
  uint16_t Channel1Pulse = 0;

  TimerPeriod = 4800;
  Channel1Pulse = 2400;

  /* Time Base configuration */
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1;
  TIM_TimeBaseStructure.TIM_Period = TimerPeriod;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM15, &TIM_TimeBaseStructure);

  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //可配置强制输出模式，具体详见寄存器TIM15->CCMR1的OC1M[2:0]
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; // TIM_OCPolarity_High ;
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;

  TIM_OCInitStructure.TIM_Pulse = Channel1Pulse;
  TIM_OC1Init(TIM15, &TIM_OCInitStructure);

  TIM_CtrlPWMOutputs(TIM15, ENABLE);

  TIM_Cmd(TIM15, ENABLE);
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

  TIM3_IntputSourceCfg(TIM3_INPUT_TI1, TIM3_IntputSource_TIM15_OC1_TRIG); // 配置捕获源：TIM3 TI1捕获TIM1_OC15_TRIG

  TIM_DTS_Cfg(TIM3);
  TIM_TI1E_Set(TIM3);
  TIM_SelectInputTrigger(TIM3, TIM_TS_TI1FP1);                 //选择TIM3输入触发源：TIM经滤波定时器输入1
  TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset);              //选择从机模式：复位模式
  TIM_SelectMasterSlaveMode(TIM3, TIM_MasterSlaveMode_Enable); //开启复位模式
  TIM_ITConfig(TIM3, TIM_IT_CC1, ENABLE);                      //开启CC1中断

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
  SetSysClock(); //主频配置
  RCC_APB0PeriphClockCmd(RCC_APB0Periph_TIM3, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM15, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

  GPIO_Config();
  tim15_cfg_init();
  TIM3_CFG_CH1();
  while (1)
    ;
}

//选择通道1、2捕获
void TIM3_Handler(void)
{
  IC1Value1 = TIM3->CCR1; //周期时间
  IC1Value2 = TIM3->CCR2; //高电平时间
  TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);
}
