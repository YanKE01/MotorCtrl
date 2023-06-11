/**
 ******************************************************************************
 * @file    lcm32f037_dma.c
 * @author  MCD Application Team
 * @version V1.0.0
 * @date    2021-05-21
 * @brief   This file provides all the dma emulation firmware functions.
 ******************************************************************************/
/**
 ******************************************************************************
 * @attention:
 *
 *
 *
 *
 ******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "lcm32f037_dma.h"

/** @addtogroup LCM32F037_StdPeriph_Driver
 * @{
 */

/** @defgroup DMA
 * @brief DMA driver modules
 * @{
 */

/**
 * @brief  DMA register for channel rest to the default value.
 * @param  DMAy_Channelx
 * @note   channel 6 and 7 reserved for other products.
 * @retval None
 */
void DMA_DeInit(DMA_Channel_TypeDef *DMAy_Channelx) /*edit end @zhang*/
{
  /* Check the parameters */
  uint32_t tmpreg;
  uint32_t ch;
  assert_param(IS_DMA_ALL_PERIPH(DMAy_Channelx));
  if (DMAy_Channelx == DMA1_Channel0)
    ch = 0;
  else if (DMAy_Channelx == DMA1_Channel1)
    ch = 1;
  else if (DMAy_Channelx == DMA1_Channel2)
    ch = 2;
  else if (DMAy_Channelx == DMA1_Channel3)
    ch = 3;
  else if (DMAy_Channelx == DMA1_Channel4)
    ch = 4;
  //  else if(DMAy_Channelx==DMA1_Channel5)ch=5;
  //  else if(DMAy_Channelx==DMA1_Channel6)ch=6;//invaild
  else
    ch = 5;                // invaild
  DMA1->DmaCfgReg |= 0x01; //开启DMA模块
  tmpreg = DMA1->ChEnReg;
  tmpreg |= 1 << (ch + 8);
  tmpreg &= ~(1 << ch);
  DMA1->ChEnReg = tmpreg; //关闭对应通道
  DMAy_Channelx->SAR = 0x00;
  DMAy_Channelx->DAR = 0x00;
  DMAy_Channelx->CTL_L = 0x00; //将1个burst对应1个signal（默认是1个burst对应4个signal），方便对应到st。
  DMAy_Channelx->CTL_H = 0x00; /*已核对*/
  DMAy_Channelx->CFG_L = 0x00; /*使用硬件握手信号*/
  DMAy_Channelx->CFG_H = 0x04; /*PROTCTL=1*/

  DMA1->RawTfr &= ~(1 << ch);
  DMA1->RawBlock &= ~(1 << ch);
  DMA1->RawSrcTran &= ~(1 << ch);
  DMA1->RawDstTran &= ~(1 << ch);
  DMA1->RawErr &= ~(1 << ch);

  DMA1->StatusTfr &= ~(1 << ch);
  DMA1->StatusBlock &= ~(1 << ch);
  DMA1->StatusSrcTran &= ~(1 << ch);
  DMA1->StatusDstTran &= ~(1 << ch);
  DMA1->StatusErr &= ~(1 << ch);

  DMA1->ClearTfr = 1 << ch;
  DMA1->ClearBlock = 1 << ch;
  DMA1->ClearSrcTran = 1 << ch;
  DMA1->ClearDstTran = 1 << ch;
  DMA1->ClearErr = 1 << ch;
}

/**
 * @brief  Initializes the DMAy Channelx according to the specified parameters
 *         in the DMA_InitStruct.
 * @param  DMA_InitStruct: pointer to a DMA_InitTypeDef structure that contains
 *         the configuration information for the specified DMA Channel.
 * @retval None
 */
void DMA_Init(DMA_Channel_TypeDef *DMAy_Channelx, DMA_InitTypeDef *DMA_InitStruct)
{
  /* Check the parameters */
  assert_param(IS_DMA_ALL_PERIPH(DMAy_Channelx));
  assert_param(IS_DMA_DIR(DMA_InitStruct->DMA_DIR));
  // assert_param(IS_DMA_BUFFER_SIZE(DMA_InitStruct->DMA_BufferSize));
  assert_param(IS_DMA_PERIPHERAL_INC_STATE(DMA_InitStruct->DMA_PeripheralInc));
  assert_param(IS_DMA_MEMORY_INC_STATE(DMA_InitStruct->DMA_MemoryInc));
  assert_param(IS_DMA_PERIPHERAL_DATA_SIZE(DMA_InitStruct->DMA_PeripheralDataSize));
  assert_param(IS_DMA_MEMORY_DATA_SIZE(DMA_InitStruct->DMA_MemoryDataSize));
  assert_param(IS_DMA_MODE(DMA_InitStruct->DMA_Mode));
  assert_param(IS_DMA_PRIORITY(DMA_InitStruct->DMA_Priority));
  assert_param(IS_DMA_M2M_STATE(DMA_InitStruct->DMA_M2M));
  assert_param(IS_DMA_MSIZE(DMA_InitStruct->DMA_MSIZE));

  if (DMA_InitStruct->DMA_DIR == DMA_DIR_PeripheralSRC)
  {
    DMAy_Channelx->SAR = DMA_InitStruct->DMA_PeripheralBaseAddr;
    DMAy_Channelx->DAR = DMA_InitStruct->DMA_MemoryBaseAddr;
    DMAy_Channelx->CTL_L_b.SRC_TR_WIDTH = DMA_InitStruct->DMA_PeripheralDataSize;
    DMAy_Channelx->CTL_L_b.DST_TR_WIDTH = DMA_InitStruct->DMA_MemoryDataSize;
    DMAy_Channelx->CTL_L_b.SINC = DMA_InitStruct->DMA_PeripheralInc;
    DMAy_Channelx->CTL_L_b.DINC = DMA_InitStruct->DMA_MemoryInc;
  }
  else
  {
    DMAy_Channelx->DAR = DMA_InitStruct->DMA_PeripheralBaseAddr;
    DMAy_Channelx->SAR = DMA_InitStruct->DMA_MemoryBaseAddr;
    DMAy_Channelx->CTL_L_b.DST_TR_WIDTH = DMA_InitStruct->DMA_PeripheralDataSize;
    DMAy_Channelx->CTL_L_b.SRC_TR_WIDTH = DMA_InitStruct->DMA_MemoryDataSize;
    DMAy_Channelx->CTL_L_b.SINC = DMA_InitStruct->DMA_MemoryInc;
    DMAy_Channelx->CTL_L_b.DINC = DMA_InitStruct->DMA_PeripheralInc;
  }
  DMAy_Channelx->CTL_H_b.BLOCK_TS = DMA_InitStruct->DMA_BufferSize; /*the max vaild value is 4095 @zhang*/
  DMAy_Channelx->CFG_L_b.RELOAD_SRC = DMA_InitStruct->DMA_Mode;
  DMAy_Channelx->CFG_L_b.RELOAD_DST = DMA_InitStruct->DMA_Mode;
  DMAy_Channelx->CFG_L_b.CH_PRIOR = DMA_InitStruct->DMA_Priority;
  DMAy_Channelx->CTL_L_b.TT_FC = DMA_InitStruct->DMA_M2M;
  DMAy_Channelx->CTL_L_b.SRC_MSIZE = DMA_InitStruct->DMA_MSIZE;
  DMAy_Channelx->CTL_L_b.DEST_MSIZE = DMA_InitStruct->DMA_MSIZE;
}

/**
 * @brief  Fills each DMA_InitStruct member with its default value.
 * @param  DMA_InitStruct: pointer to a DMA_InitTypeDef structure which will
 *         be initialized.
 * @retval None
 */
void DMA_StructInit(DMA_InitTypeDef *DMA_InitStruct)
{
  /*-------------- Reset DMA init structure parameters values ------------------*/
  /* Initialize the DMA_PeripheralBaseAddr member */
  DMA_InitStruct->DMA_PeripheralBaseAddr = 0;
  /* Initialize the DMA_MemoryBaseAddr member */
  DMA_InitStruct->DMA_MemoryBaseAddr = 0;
  /* Initialize the DMA_DIR member */
  DMA_InitStruct->DMA_DIR = DMA_DIR_PeripheralSRC;
  /* Initialize the DMA_BufferSize member */
  DMA_InitStruct->DMA_BufferSize = 0; /*这里指的是传输多少个signal transfer*/
  /* Initialize the DMA_PeripheralInc member */
  DMA_InitStruct->DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  /* Initialize the DMA_MemoryInc member */
  DMA_InitStruct->DMA_MemoryInc = DMA_MemoryInc_Enable;
  /* Initialize the DMA_PeripheralDataSize member */
  DMA_InitStruct->DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  /* Initialize the DMA_MemoryDataSize member */
  DMA_InitStruct->DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  /* Initialize the DMA_Mode member */
  DMA_InitStruct->DMA_Mode = DMA_Mode_Normal;
  /* Initialize the DMA_Priority member */
  DMA_InitStruct->DMA_Priority = DMA_Priority_Low;
  /* Initialize the DMA_M2M member */
  DMA_InitStruct->DMA_M2M = DMA_M2M_Disable;
  /* Initialize the DMA_MSIZE member */
  DMA_InitStruct->DMA_MSIZE = DMA_MSIZE_1;
}

/**
 * @brief  Enables or disables the specified DMAy Channelx.
 * @param  DMAy_Channelx: where y can be 1 to select the DMA and x can be 1 to 7
 *         for DMA1 to select the DMA Channel and 1 to 5 for DMA2 to select the DMA Channel.
 * @note   DMA1 Channel 6 and 7 are not available.
 * @note   DMA1 Channel 1 to 5 are available
 * @param  NewState: new state of the DMAy Channelx.
 *         This parameter can be: ENABLE or DISABLE.
 * @retval None
 */
void DMA_Cmd(DMA_Channel_TypeDef *DMAy_Channelx, FunctionalState NewState) /*edit end @zhang*/
{
  /* Check the parameters */
  uint32_t ch;
  uint32_t tmpreg;
  assert_param(IS_DMA_ALL_PERIPH(DMAy_Channelx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (DMAy_Channelx == DMA1_Channel0)
    ch = 0;
  else if (DMAy_Channelx == DMA1_Channel1)
    ch = 1;
  else if (DMAy_Channelx == DMA1_Channel2)
    ch = 2;
  else if (DMAy_Channelx == DMA1_Channel3)
    ch = 3;
  else if (DMAy_Channelx == DMA1_Channel4)
    ch = 4;
  //  else if(DMAy_Channelx==DMA1_Channel5)ch=5;
  //  else if(DMAy_Channelx==DMA1_Channel6)ch=6;//invaild
  else
    ch = 5; // invaild
  tmpreg = DMA1->ChEnReg;
  if (NewState != DISABLE)
  {
    /* Enable the selected DMAy Channelx */
    tmpreg |= 0x101 << ch;
  }
  else
  {
    /* Disable the selected DMAy Channelx */
    tmpreg |= 0x100 << ch;
    tmpreg &= ~(1 << ch);
  }
  DMA1->ChEnReg = tmpreg;
}

/** @defgroup DMA_Group2 Data Counter functions
 *  @brief   Data Counter functions
 * @note   This function can only be used when the DMAy_Channelx is disabled.
 * @retval None.
 */
void DMA_SetCurrDataCounter(DMA_Channel_TypeDef *DMAy_Channelx, uint16_t DataNumber) /* edit end @zhang */
{
  /* Check the parameters */
  assert_param(IS_DMA_ALL_PERIPH(DMAy_Channelx));

  /*--------------------------- DMAy Channelx CNDTR Configuration --------------*/
  /*Block Transfer Size */
  DMAy_Channelx->CTL_H = (0xFFF & DataNumber); //最大传输4096个signal transfer.
}

/**
 * @brief  Returns the number of remaining data units in the current
 *         DMAy Channelx transfer.
 * @retval 此处返回的是从源地址读取了多少个signal，而不是还有多少个signal要传输，此处有差异
 */
uint16_t DMA_GetCurrDataCounter(DMA_Channel_TypeDef *DMAy_Channelx)
{
  /* Check the parameters */
  assert_param(IS_DMA_ALL_PERIPH(DMAy_Channelx));
  /* Return the number of remaining data units for DMAy Channelx */
  return (uint16_t)((DMAy_Channelx->CTL_H) & 0xFFF);
}

/**
 * @}
 */

/**
 * @brief  Enables or disables the specified DMAy Channelx interrupts.
 * @param  NewState: new state of the specified DMA interrupts.
 *         This parameter can be: ENABLE or DISABLE.
 * @retval None
 */
void DMA_ITConfig(DMA_Channel_TypeDef *DMAy_Channelx, uint32_t DMA_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DMA_ALL_PERIPH(DMAy_Channelx));
  assert_param(IS_DMA_CONFIG_IT(DMA_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  //(void)DMAy_Channelx;
  if (NewState != DISABLE)
  {
    DMAy_Channelx->CTL_L_b.INT_EN = 1;
    /* Enable the selected DMA interrupts */
    if ((DMA_IT & 0xF0) == 0x00)
    {
      DMA1->MaskBlock = (0x101 << (DMA_IT & 0x0F));
    }
    if ((DMA_IT & 0xF0) == 0x01)
    {
      DMA1->ClearErr = 0x101 << (DMA_IT & 0x0F);
    }
  }
  else
  {
    DMAy_Channelx->CTL_L_b.INT_EN = 0;
    /* Disable the selected DMA interrupts */
    if ((DMA_IT & 0xF0) == 0x00)
    {
      DMA1->MaskBlock = (0x100 << (DMA_IT & 0x0F));
    }
    if ((DMA_IT & 0xF0) == 0x01)
    {
      DMA1->ClearErr = 0x100 << (DMA_IT & 0x0F);
    }
  }
}

/**

*/
FlagStatus DMA_GetFlagStatus(uint32_t DMAy_FLAG)
{
  /* Check the parameters */
  uint32_t tmp;
  assert_param(IS_DMA_GET_FLAG(DMAy_FLAG));
  if ((DMAy_FLAG & 0xF0) == 0x00)
  {
    tmp = (DMA1->RawBlock >> (((uint8_t)DMAy_FLAG) & 0x0F)) & 0x01;
  }
  if ((DMAy_FLAG & 0xF0) == 0x01)
  {
    tmp = (DMA1->RawErr >> (DMAy_FLAG & 0x0F)) & 0x01;
  }
  if (tmp)
    return SET;
  return RESET;
}

/**
 * @brief  Clears the DMAy Channelx's pending flags.
 * @param  DMA_FLAG: specifies the flag to clear.
 *
 * @retval None
 */
void DMA_ClearFlag(uint32_t DMAy_FLAG)
{
  /* Check the parameters */
  assert_param(IS_DMA_CLEAR_FLAG(DMAy_FLAG));
  if ((DMAy_FLAG & 0xF0) == 0x00)
  {
    DMA1->ClearBlock |= 1 << (DMAy_FLAG & 0x0F);
  }
  if ((DMAy_FLAG & 0xF0) == 0x01)
  {
    DMA1->ClearErr |= 1 << (DMAy_FLAG & 0x0F);
  }
}

/**
 * @brief  Checks whether the specified DMAy Channelx interrupt has occurred or not.
 *         interrupts relative to the same channel is set (Transfer Complete,
 *         or Transfer Error interrupts: DMAy_IT_TCx, or DMAy_IT_TEx).
 *
 * @retval The new state of DMA_IT (SET or RESET).
 */
ITStatus DMA_GetITStatus(uint32_t DMAy_IT)
{
  /* Check the parameters */
  uint32_t tmp;
  assert_param(IS_DMA_GET_FLAG(DMAy_IT));
  if ((DMAy_IT & 0xF0) == 0x00)
  {
    tmp = (DMA1->StatusBlock >> (DMAy_IT & 0x0F)) & 0x01;
  }
  if ((DMAy_IT & 0xF0) == 0x01)
  {
    tmp = (DMA1->StatusErr >> (DMAy_IT & 0x0F)) & 0x01;
  }
  if (tmp)
    return SET;
  return RESET;
}

/**
 * @brief  Clears the DMAy Channelx's interrupt pending bits.
 * @param  DMA_IT: specifies the DMA interrupt pending bit to clear.
 * @note   Clearing the Global interrupt (DMAy_IT_GLx) results in clearing all other
 *         interrupts relative to the same channel (Transfer Complete, Half-transfer
 *         Complete and Transfer Error interrupts: DMAy_IT_TCx, DMAy_IT_HTx and
 *         DMAy_IT_TEx).
 *
 * @retval None
 */
void DMA_ClearITPendingBit(uint32_t DMAy_IT)
{
  /* Check the parameters */
  assert_param(IS_DMA_CLEAR_FLAG(DMAy_IT));
  if ((DMAy_IT & 0xF0) == 0x00)
  {
    DMA1->ClearBlock = 1 << (DMAy_IT & 0x0F);
  }
  if ((DMAy_IT & 0xF0) == 0x10)
  {
    DMA1->ClearErr = 1 << (DMAy_IT & 0x0F);
  }
}

/**
* @brief  DMA请求号映射到外设
  @param  DMAy_Channelx :指定DMA使用的哪一个通道
          DMA_ReqNum :指定DMA要映射到的请求号
          DMA_Request:指定改映射连接到哪个外设
  @note   该函数只能在通道使能前调用，且必须调用。
  @retval none.
*********************/
void DMA_RemapConfig(DMA_Channel_TypeDef *DMAy_Channelx, uint32_t DMA_ReqNum, uint32_t DMA_Request)
{
  uint32_t tmpreg;
  assert_param(IS_REQ_NUM(DMA_ReqNum));
  //	assert_param(IS_DMA_REQ(DMA_Request));
  DMAy_Channelx->CFG_H_b.DEST_PER = DMA_ReqNum;
  DMAy_Channelx->CFG_H_b.SRC_PER = DMA_ReqNum;
  tmpreg = SYSCTRL->EDU_CFG0;
  // tmpreg &= 0xF << (DMA_ReqNum << 2);
  tmpreg |= DMA_Request << (DMA_ReqNum * 4);
  sysctrl_access();
  SYSCTRL->EDU_CFG0 = tmpreg;
  __dekey();
}

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT LCMicroelectronics *****END OF FILE****/
