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
demo给出捕获方案，捕获ACMP1_OUT

配置SYSCTRL_EDU_CFGx寄存器选择输入触发源

通道1、2由于可选择复位模式，则CCRx寄存器的值即为周期时间、上升沿/下降沿时间
*********************************************************************************************/
uint16_t IC1Value1 = 0, IC1Value2 = 0;

void DAC1_cfg()
{
  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_2); // DAC1_OUT

  DAC_InitTypeDef DAC_InitStruct;
  DAC_InitStruct.DAC_EXTrigger_Edge = DAC_EXTrigger_edge_dis;
  DAC_InitStruct.DAC_Trigger_Source = DAC_Trigger_Software;
  DAC_InitStruct.DAC_WaveGeneration = DAC_WaveGeneration_None;
  DAC_InitStruct.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
  DAC_InitStruct.DAC_OutputBuffer = DAC1_OutputBuffer_Enable;
  DAC_InitStruct.DAC_Vref_Select = DAC_Vref_Avdd;
  DAC_InitStruct.DAC_DmaMode = DISABLE;
  DAC_InitStruct.DAC_DMAUDR_IE = DISABLE;
  DAC_Init(DAC1, &DAC_InitStruct);

  DAC_Cmd(DAC1, ENABLE);
  DAC_SetDac_10B_Data(DAC1, DAC_Align_10B_R, 0x136);
  DAC_SoftwareTriggerCmd(DAC1, ENABLE); //软件触发使能；标示触发 DAC 的一次触发传输(选择软件触发条件)
}
void acmp1_cfg()
{
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_6); ////out

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_1); // CP1_P_4[1]

  ACMP_InitTypeDef ACMP_InitStruct;
  ACMP_InitStruct.ACMP_P_Select = CP1_PS_CPP1EXT_INPUT; //比较器正端输入选择
  ACMP_InitStruct.ACMP_N_Select = CP1_NS_DAC1OUT;       //比较器负端输入选择
  ACMP_InitStruct.ACMP_Delay_time = CP_NODelay_time;    //输出延迟配置
  ACMP_InitStruct.ACMP_Blanking = CP_NOBLANKING;        //比较器消隐源选择
  ACMP_InitStruct.ACMP_Is = CP_IS_POS;                  //比较器输出极性
  ACMP_InitStruct.ACMP_HYSEN = DISABLE;                 //迟滞使能配置
  ACMP_InitStruct.ACMP_FREN = ENABLE;                   //快速响应使能
  ACMP_InitStruct.ACMP_FS = DISABLE;                    //输出滤波使能配置

  ACMP_InitStruct.CMP_INTENMASK = ENABLE;              //比较器连续比较中断使能屏蔽
  ACMP_InitStruct.CMP_SEQ_MODE = DISABLE;              //连续模式使能
  ACMP_InitStruct.TRIG_MODE = CP_TIRG_INASOFT;         //触发模式：软件或者外部硬件触发
  ACMP_InitStruct.CHNL_CNT_TIME = CHNL_CNT_TIME_64CLK; //比较器通道切换时钟周期选择

  ACMP1_Init(&ACMP_InitStruct);
  ACMP1_SEQ_INPUT_SELECT(DISABLE, 1, 0); //选择输入通道：是否连续；正端；负端
  ACMP1_Cmd(ENABLE);
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

  TIM3_IntputSourceCfg(TIM3_INPUT_TI1, TIM3_IntputSource_ACMP1_OUTPUT); // 配置捕获源：TIM3 TI1捕获ACMP1_OUTPUT

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
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_ANACTRL, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);

  DAC1_cfg();  // DAC1_OUT=PA5
  acmp1_cfg(); // PA2(OUT) PA3(P) DAC1(N)

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