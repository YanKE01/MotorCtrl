/**
  ******************************************************************************
  * @file    lcm32f037_wt.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    2021-05-25
  * @brief   This file provides all the WT emulation firmware functions.
  ******************************************************************************/
/**
  ******************************************************************************
  * @attention:
  * 
  * 
  * 
  * 
  ******************************************************************************/
#include "lcm32f037.h"
#include "lcm32f037_rcc.h"
#include "lcm32f037_wt.h"
#include "lcm32f037_gpio.h"
#include <stdio.h>

/*--------------------------------------------------------------------------------------------
WT参数初始化
  --------------------------------------------------------------------------------------------*/
void WT_StructInit(WT_InitTypeDef *WT_InitStruct)
{
  WT_InitStruct->WT_BZOUT = WT_BZOUT_Hight;              //蜂鸣器输出高低频率选择位
  WT_InitStruct->WT_WTState = WT_WTState_Enable;         // WT 使能位
  WT_InitStruct->WT_Outfrequency = WT_Outfrequency_1024; //蜂鸣器输出频率选择位
  WT_InitStruct->WT_T8State = WT_T8State_Enable;         //T8 使能位
  WT_InitStruct->WT_T8frequency = WT_T8frequency_4096;   //T8 时钟源选择位
  WT_InitStruct->WT_Interrupt = WT_Interrupt_2HZ;        // WT 中断源选择位
}

/*--------------------------------------------------------------------------------------------
WT参数初始化
  --------------------------------------------------------------------------------------------*/
void WT_Init(WT_TypeDef *WTx, WT_InitTypeDef *WT_InitStruct)
{
  uint16_t tmpreg = 0x00;
  assert_param(IS_WT_BZOUT(WT_InitStruct->WT_BZOUT));
  assert_param(IS_WT_WTState(WT_InitStruct->WT_WTState));
  assert_param(IS_WT_Outfrequency(WT_InitStruct->WT_Outfrequency));
  assert_param(IS_WT_T8State(WT_InitStruct->WT_T8State));
  assert_param(IS_WT_T8frequency(WT_InitStruct->WT_T8frequency));
  assert_param(IS_WT_Interrupt(WT_InitStruct->WT_Interrupt));
  tmpreg = WT->WTCON;
  tmpreg &= 0X0000;
  tmpreg = (tmpreg | (WT_InitStruct->WT_BZOUT) |
            (WT_InitStruct->WT_WTState) |
            (WT_InitStruct->WT_Outfrequency) |
            (WT_InitStruct->WT_T8State) |
            (WT_InitStruct->WT_T8frequency) |
            (WT_InitStruct->WT_Interrupt));
  WT->WTCON = tmpreg;
}

/*--------------------------------------------------------------------------------------------
设置定时器初值
--------------------------------------------------------------------------------------------*/
void WT_SetCounter(WT_TypeDef *WTx, uint16_t Counter)
{
  WT->T8 = Counter;
}
/*--------------------------------------
清WT中断
---------------------------------------------------------*/
void WT_ClearITPendingBit(uint32_t WT_Line)
{
  WT->WTCON &= 0xFFFFFFBF;
}
/************************ (C) COPYRIGHT LCMicroelectronics *****END OF FILE******************/
