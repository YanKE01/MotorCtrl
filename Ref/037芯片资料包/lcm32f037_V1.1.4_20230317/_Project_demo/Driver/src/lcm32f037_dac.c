/**
  ******************************************************************************
  * @file    lcm32f037_dac.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    2021-05-21
  * @brief   This file provides all the dac emulation firmware functions.
  ******************************************************************************/
/**
  ******************************************************************************
  * @attention:
  * 
  * 
  * 
  * 
  ******************************************************************************/
#include "lcm32f037_dac.h"
#include "lcm32f037_rcc.h"
/*--------------------------------------------------------------------------------------------
ANACTRL时钟关闭 :DAC ACMP OPA 三者公用一个时钟使能,用一次即可
  --------------------------------------------------------------------------------------------*/
void DAC_DeInit(void)
{
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_ANACTRL, ENABLE);
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_ANACTRL, DISABLE);
}

/*--------------------------------------------------------------------------------------------
DAC初始化函数
--------------------------------------------------------------------------------------------*/
void DAC_Init(DAC_TypeDef *dac_ptr, DAC_InitTypeDef *DAC_InitStruct)
{

  uint32_t tmpreg1 = 0, tmpreg2 = 0;
  CHIPCTRL->PWR_CFG &= ~(0x3 << 24);
  if (dac_ptr == DAC0)
  {
    chipctrl_access();
    CHIPCTRL->PWR_CFG &= ~(0x3 << 20); //clear bit20-21
    __dekey();
    if (DAC_InitStruct->DAC_Vref_Select == DAC_Vref_Pum_2v5)
    {
      chipctrl_access();
      CHIPCTRL->PWR_CFG |= (1 << 20); //enable DAC_vref_pmu
      __dekey();
      DAC_InitStruct->DAC_Vref_Select = DAC_Vref_Pum;
    }
    else if (DAC_InitStruct->DAC_Vref_Select == DAC_Vref_Pum_4v)
    {
      chipctrl_access();
      CHIPCTRL->PWR_CFG |= (1 << 20) | (1 << 21); //enable DAC_vref_pmu
      __dekey();
      DAC_InitStruct->DAC_Vref_Select = DAC_Vref_Pum;
    }
  }
  else if (dac_ptr == DAC1)
  {
    chipctrl_access();
    CHIPCTRL->PWR_CFG &= ~(0x3 << 22); //clear bit22-23
    __dekey();
    if (DAC_InitStruct->DAC_Vref_Select == DAC_Vref_Pum_2v5)
    {
      chipctrl_access();
      CHIPCTRL->PWR_CFG |= (1 << 22); //enable DAC_vref_pmu
      __dekey();
      DAC_InitStruct->DAC_Vref_Select = DAC_Vref_Pum;
    }
    else if (DAC_InitStruct->DAC_Vref_Select == DAC_Vref_Pum_4v)
    {
      chipctrl_access();
      CHIPCTRL->PWR_CFG |= (1 << 22) | (1 << 23); //enable DAC_vref_pmu
      __dekey();
      DAC_InitStruct->DAC_Vref_Select = DAC_Vref_Pum;
    }
  }

  /*---------------------------- DAC CR Configuration --------------------------*/
  tmpreg1 = dac_ptr->DAC_CR;
  tmpreg2 = ANACTRL->ANA_CSR;
  tmpreg1 &= ~(0x0000003e);
  //tmpreg2 &= ~(0x0000001f);
  tmpreg1 = (DAC_InitStruct->DAC_Trigger_Source | DAC_InitStruct->DAC_EXTrigger_Edge | DAC_InitStruct->DAC_WaveGeneration |
             DAC_InitStruct->DAC_LFSRUnmask_TriangleAmplitude | DAC_InitStruct->DAC_Vref_Select |
             ((DAC_InitStruct->DAC_DmaMode) << 12) | ((DAC_InitStruct->DAC_DMAUDR_IE) << 13));
  tmpreg2 |= DAC_InitStruct->DAC_OutputBuffer;

  dac_ptr->DAC_CR = tmpreg1;

  ANACTRL->ANA_CSR = tmpreg2;
}

/*--------------------------------------------------------------------------------------------
DAC结构体参数定义
--------------------------------------------------------------------------------------------*/
void DAC_StructInit(DAC_InitTypeDef *DAC_InitStruct)
{
  /*--------------- Reset DAC init structure parameters values -----------------*/
  /* Initialize the DAC_Trigger member */
  DAC_InitStruct->DAC_Trigger_Source = DAC_Trigger_None;

  DAC_InitStruct->DAC_EXTrigger_Edge = DAC_EXTrigger_edge_dis;

  /* Initialize the DAC_WaveGeneration member */
  DAC_InitStruct->DAC_WaveGeneration = DAC_WaveGeneration_None;

  /* Initialize the DAC_LFSRUnmask_TriangleAmplitude member */
  DAC_InitStruct->DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;

  /* Initialize the DAC_OutputBuffer member */
  DAC_InitStruct->DAC_OutputBuffer = DAC_OutputBuffer_Disable;

  DAC_InitStruct->DAC_Vref_Select = DAC_Vref_Avdd;

  DAC_InitStruct->DAC_DmaMode = DISABLE;

  DAC_InitStruct->DAC_DMAUDR_IE = DISABLE;
}

/*--------------------------------------------------------------------------------------------
  DAC 使能
  --------------------------------------------------------------------------------------------*/
void DAC_Cmd(DAC_TypeDef *dac_ptr, FunctionalState NewState)
{

  if (NewState != DISABLE)
  {
    /* Enable the selected DAC channel */

    dac_ptr->DAC_CR |= (0x00000001);
  }
  else
  {
    /* Disable the selected DAC channel */

    dac_ptr->DAC_CR &= (~(0x00000001));
  }
}

/*---------------------------------------------------------------------------
  DAC软件触发命令
  --------------------------------------------------------------------------*/
void DAC_SoftwareTriggerCmd(DAC_TypeDef *dac_ptr, FunctionalState NewState)
{

  if (NewState != DISABLE)
  {
    /* Enable software trigger for the selected DAC channel */

    dac_ptr->DAC_CSR |= (0x1UL << 0);
  }
  else
  {
    /* Disable software trigger for the selected DAC channel */

    dac_ptr->DAC_CSR &= ~(0x1UL << 0);
  }
}

/*---------------------------------------------------------------------------
  DAC波形设置：噪声 三角
  --------------------------------------------------------------------------*/
void DAC_WaveGenerationCmd(DAC_TypeDef *dac_ptr, uint32_t DAC_Wave, FunctionalState NewState)
{
  uint32_t wavedata;
  wavedata = DAC_Wave;
  if (NewState != DISABLE)
  {
    if (wavedata == (1 << 6))
    {
      /* Enable the selected wave generation for the selected DAC channel */

      dac_ptr->DAC_CR = (0x01 << 6);
    }
    else if (wavedata == (2 << 6))
    {

      dac_ptr->DAC_CR = (0x02 << 6);
    }
    else
    {

      dac_ptr->DAC_CR &= ~(0x03 << 6);
    }
  }
  else
  {
    /* Disable the selected wave generation for the selected DAC channel */

    dac_ptr->DAC_CR &= ~(0x03 << 6);
  }
}

/*---------------------------------------------------------------------------
  设置dac数据转换
  对齐：左对齐  右对齐
  DAC5     12bit
  DAC0-DAC4 8bit
  --------------------------------------------------------------------------*/
void DAC_SetDac_10B_Data(DAC_TypeDef *dac_ptr, uint32_t DAC_Align, uint16_t Data)
{
  uint32_t Rdata = 0;

  dac_ptr->DAC_CR |= DAC_Align;
  Rdata = ((dac_ptr->DAC_CR) >> 15) & 0x01;
  if (Rdata == 1)
  {
    dac_ptr->DAC_DHR = (Data << 6);
  }
  else
  {
    dac_ptr->DAC_DHR = Data;
  }
}

/*---------------------------------------------------------------------------
  获取数据寄存器
  对齐：左对齐  右对齐
  DAC5     12bit
  DAC0-DAC4 8bit
  --------------------------------------------------------------------------*/

uint16_t DAC_GetDataOutputValue_10bit(DAC_TypeDef *dac_ptr)
{
  uint32_t data = 0;
  uint32_t tmp = 0;
  data = ((dac_ptr->DAC_CR) >> 15) & 0x01;

  if (data == 1)
  {
    tmp = ((dac_ptr->DAC_DOR) >> 6) & 0xfff;
  }
  else
  {
    tmp = (dac_ptr->DAC_DOR) & 0xfff;
  }
  return tmp;
}

/*---------------------------------------------------------------------------
 DAC中断配置
  --------------------------------------------------------------------------*/

void DAC_ITConfig(DAC_TypeDef *dac_ptr, uint32_t DAC_IT, FunctionalState NewState)
{

  if (NewState != DISABLE)
  {
    /* Enable the selected DAC interrupts */

    dac_ptr->DAC_CR |= (0X1UL << 13);
    dac_ptr->DAC_CSR |= DAC_IT;
  }
  else
  {
    /* Disable the selected DAC interrupts */

    dac_ptr->DAC_CR &= (~(0X1UL << 13));
    dac_ptr->DAC_CSR &= (~DAC_IT);
  }
}

/*---------------------------------------------------------------------------
 DAC清除标志位
  --------------------------------------------------------------------------*/
void DAC_ClearFlag(DAC_TypeDef *dac_ptr, uint32_t DAC_FLAG)
{

  /* Clear the selected DAC flags */

  dac_ptr->DAC_CSR = DAC_FLAG;
}

/*---------------------------------------------------------------------------
 DAC清中断标志位
  --------------------------------------------------------------------------*/
void DAC_ClearITPendingBit(DAC_TypeDef *dac_ptr, uint32_t DAC_IT)
{

  /* Clear the selected DAC interrupt pending bits */

  dac_ptr->DAC_CSR = DAC_IT;
}
