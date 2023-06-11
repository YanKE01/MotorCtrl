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
demo�������ֲ���ͨ����ϣ�
ͨ��1��2���ڿ�ѡ��λģʽ����CCRx�Ĵ�����ֵ��Ϊ����ʱ�䡢������/�½���ʱ��
ͨ��3��4û�и�λģʽ������Ҫͨ������ó�����ʱ�䡢������/�½���ʱ��
*********************************************************************************************/
uint16_t IC1Value1 = 0, IC1Value2 = 0;
uint16_t IC3Value1 = 0, IC3Value1Old = 0, IC3Value2 = 0, Value3 = 0, Value4 = 0;

void GPIO_Config()
{
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_1); // tim3_ch1  PA6

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource0, GPIO_AF_1); // tim3_ch3  PB0
}
void NVIC_Configuration()
{
  NVIC_InitTypeDef NVIC_InitStructure;

  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
void TIM3_CFG_CH1()
{
  TIM_ICInitTypeDef TIM_ICInitStructure;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

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

  TIM_DTS_Cfg(TIM3);
  TIM_TI1E_Set(TIM3);
  TIM_SelectInputTrigger(TIM3, TIM_TS_TI1FP1);                 //ѡ��TIM3���봥��Դ��TIM���˲���ʱ������1
  TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset);              //ѡ��ӻ�ģʽ����λģʽ
  TIM_SelectMasterSlaveMode(TIM3, TIM_MasterSlaveMode_Enable); //������λģʽ
  TIM_ITConfig(TIM3, TIM_IT_CC1, ENABLE);                      //����CC1�ж�

  /* TIM enable counter */
  TIM_Cmd(TIM3, ENABLE);
}

void TIM3_CFG_CH3()
{
  TIM_ICInitTypeDef TIM_ICInitStructure;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

  TIM_TimeBaseStructure.TIM_Prescaler = 0x0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = 0xffff;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  TIM_ICInitStructure.TIM_Channel = TIM_Channel_3;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;
  TIM_ICInit(TIM3, &TIM_ICInitStructure);

  TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_IndirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;
  TIM_ICInit(TIM3, &TIM_ICInitStructure);

  TIM_DTS_Cfg(TIM3);
  TIM_TI3E_Set(TIM3);
  TIM_ITConfig(TIM3, TIM_IT_CC3, ENABLE); //����CC3�ж�
  TIM_Cmd(TIM3, ENABLE);                  // TIM enable counter
}

int main()
{
  SystemInit();
  SetSysClock(); //��Ƶ����
  RCC_APB0PeriphClockCmd(RCC_APB0Periph_TIM3, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
  NVIC_Configuration(); //����NVIC����
  GPIO_Config();        // PWM GPIOSET

  TIM3_CFG_CH1(); // TIM3 SET

  // TIM3_CFG_CH3(); //TIM3 SET
  while (1)
    ;
}
//ѡ��ͨ��1��2����
void TIM3_Handler(void)
{
  IC1Value1 = TIM3->CCR1; //����ʱ��
  IC1Value2 = TIM3->CCR2; //�ߵ�ƽʱ��
  TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);
}

//ѡ��ͨ��3��4����
// void TIM3_Handler(void)
// {
//   IC3Value1 = TIM3->CCR3;
//   IC3Value2 = TIM3->CCR4;
//   if ((IC3Value1 > IC3Value1Old) && (IC3Value1Old != 0))
//   {
//     Value4 = IC3Value1 - IC3Value1Old; //����ʱ��
//   }
//   if ((IC3Value1 > IC3Value2) && (IC3Value2 != 0))
//   {
//     Value3 = IC3Value1 - IC3Value2; //�͵�ƽʱ��
//   }
//   IC3Value1Old = IC3Value1;
//   TIM_ClearITPendingBit(TIM3, TIM_IT_CC3);
// }
