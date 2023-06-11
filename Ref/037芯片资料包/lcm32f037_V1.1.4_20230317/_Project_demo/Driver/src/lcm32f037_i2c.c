/**
 ******************************************************************************
 * @file    lcm32f037_iic.c
 * @author  MCD Application Team
 * @version V1.0.0
 * @date    2021-05-21
 * @brief   This file provides all the iic emulation firmware functions.
 ******************************************************************************/

#include "lcm32f037_i2c.h"
#include "lcm32f037.h"
#include "lcm32f037_rcc.h"
/*************************************
 *  config as a i2c slave
 *************************************/

void I2C_DeInit(I2C_TypeDef *I2Cx)
{
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C0, ENABLE);

  RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C0, DISABLE);
}

/*--------------------------------------------------------------------------------------------
   I2C 收到 General Call 是否返回 ACK/NACK；仅在从机模式下有效
  --------------------------------------------------------------------------------------------*/
void SlaveAckGeneralCall(I2C_TypeDef *I2Cx, bool status)
{
  if (status == TRUE)
  {
    I2Cx->ACKGENERALCALL |= I2C_ACK_GEN_CALL_Msk;
  }
  if (status == FALSE)
  {
    I2Cx->ACKGENERALCALL &= ~I2C_ACK_GEN_CALL_Msk;
  }
}

/*--------------------------------------------------------------------------------------------
//产生General Call 广播,产生后要手动清除
--------------------------------------------------------------------------------------------*/
void I2C_GenerateGeneralCall(I2C_TypeDef *I2Cx)
{
  I2Cx->TAR |= I2C_TAR_SPECIAL_ON;    // special set
  I2Cx->TAR &= ~I2C_TAR_GC_START_Msk; // GC_OR_START reset
}

/*--------------------------------------------------------------------------------------------
//清除 General Call 广播
--------------------------------------------------------------------------------------------*/
void I2C_ClearGeneralCall(I2C_TypeDef *I2Cx)
{
  I2Cx->TAR &= ~I2C_TAR_SPECIAL_ON;
}

/*--------------------------------------------------------------------------------------------
//产生Start Byte，没说必须要手动清除
--------------------------------------------------------------------------------------------*/
void I2C_GenerateStartByte(I2C_TypeDef *I2Cx)
{
  I2Cx->TAR |= I2C_TAR_SPECIAL_ON;  // special set
  I2Cx->TAR |= I2C_TAR_GC_START_ON; // GC_OR_START set
}

/*--------------------------------------------------------------------------------------------
//明确数据收发的波特率，SCL时钟;
--------------------------------------------------------------------------------------------*/
void I2C_SetFrequent(I2C_TypeDef *I2Cx, int sclClock)
{
  uint32_t tmpreg = 0;
  uint32_t freq, LCNT, HCNT, SPKLEN;
  RCC_ClocksTypeDef RCC_Clocks;
  SpeedSelectType Mode;
  tmpreg = I2Cx->CON;
  tmpreg &= 0xFFFFFFF9;
  if (sclClock <= 100000)
  {
    Mode = STANDARD_MODE;

    tmpreg |= I2C_SPEED_STANDARD_MODE;
  }
  else if (sclClock <= 400000)
  {
    Mode = FAST_MODE;
    tmpreg |= I2C_SPEED_FAST_MODE;
  }
  else if (sclClock <= 1000000)
  {
    Mode = HIGH_SPEED;
    tmpreg |= I2C_SPEED_FAST_MODE;
  }
  I2Cx->CON = tmpreg;
  RCC_GetClockFreq(&RCC_Clocks);
  freq = RCC_Clocks.I2C0_Frequency;
  SPKLEN = I2Cx->FSSPKLEN;
  LCNT = (freq - 2 * sclClock) / (2 * sclClock);
  HCNT = (LCNT - SPKLEN - 6);
  if ((HCNT + SPKLEN + 7 > 17) && (LCNT + 1 > 16))
  {
    if (Mode == STANDARD_MODE)
    {
      I2Cx->SSLCNT = LCNT;
      I2Cx->SSHCNT = HCNT;
    }
    else if (Mode == FAST_MODE)
    {
      I2Cx->FSLCNT = LCNT - 1;
      I2Cx->FSHCNT = HCNT - 1;
    }
    else if (Mode == HIGH_SPEED)
    {
      I2Cx->FSLCNT = LCNT - 2;
      I2Cx->FSHCNT = HCNT - 2;
    }
  }
}
/*********************************************
 *threshold value of TX_FIFO to raise the interrupt
控制 TX_EMPTY 中断触发的阈值设定。范围 0~7
 * *******************************************/
void I2C_TxFifoITthreshold(uint32_t TxFifoValue)
{
  assert_param(IS_I2C_TX_FIFO_IT(TxFifoValue));
  I2C0->TXTL = TxFifoValue;
}
/*********************************************
 *threshold value of RX_FIFO to raise the interrupt
控制 RX_FULL 中断触发的阈值设定。范围 0~7
 * *******************************************/
void I2C_RxFifoITthreshold(uint32_t RxFifoValue)
{
  assert_param(IS_I2C_RX_FIFO_IT(RxFifoValue));
  I2C0->RXTL = RxFifoValue;
}

//=========================================================================
/** 设置目标地址 master mode
 * @brief  Handles I2Cx communication when starting transfer or during transfer (TC or TCR flag are set).
 */
void I2C_TransferHandling(I2C_TypeDef *I2Cx, uint32_t Address)
{
  uint32_t tmpreg = 0;
  tmpreg = I2Cx->TAR;
  tmpreg &= (uint32_t)0xFFFFEC00;
  tmpreg |= Address;
  if (tmpreg & 0x00000300)
    tmpreg |= I2C_TAR_10ADDR_MAS; //主机设置10位通信地址
  else
    tmpreg &= ~I2C_TAR_10ADDR_MAS; //主机设置7位通信地址
  I2Cx->TAR = tmpreg;
}
/****************************************
设置从机地址
config the Slaver Address when working in I2C slave mode.
 **********************************************************************************/
void I2C_SlaveAddressConfig(I2C_TypeDef *I2Cx, uint32_t Address)
{
  I2Cx->SAR = Address & ((uint32_t)0x000003FF); // 从机设置地址。
}

/**************************************************
 * I2C使能
 * ****************************************************/
void I2C_Cmd(I2C_TypeDef *I2Cx, FunctionalState NewState)
{

  if (NewState != DISABLE)
  {
    /* Enable the selected I2C peripheral */
    I2Cx->ENABLE |= (I2C_ENABLE_ON);
  }
  else
  {
    /* Disable the selected I2C peripheral */
    I2Cx->ENABLE &= (~I2C_ENABLE_ON);
  }
}

void I2C_StructInit(I2C_InitTypeDef *I2C_InitStruct)
{
  /*---------------- Reset I2C init structure parameters values --------------*/
  I2C_InitStruct->I2C_mode = I2C_MasterOnlyMode;                  //主机模式
  I2C_InitStruct->I2C_StopDetMaster = I2C_StopDet_MasterAlways;   //主机模式下的STOP_DET中断
  I2C_InitStruct->I2C_RxFifoFullHold = I2C_RxFifoFullHold_ENABLE; //决定I2C在RX FIFO达到RX_RX_BUFFER_DEPTH时是否hold总线
  I2C_InitStruct->I2C_TxEmptyIntr = I2C_TxEmptyIntr_ENABLE;       //控制TX_EMPTY中断的产生方式
  I2C_InitStruct->I2C_Speed = 400000;                             // SCL速率配置
}

//使用结构体初始化I2C==============完成====================================
void I2C_Init(I2C_TypeDef *I2Cx, I2C_InitTypeDef *I2C_InitStruct)
{
  uint32_t tmpreg = 0;
  tmpreg = I2Cx->CON;
  tmpreg &= 0xFFFFF830;
  I2Cx->ENABLE &= (~I2C_ENABLE_ON);
  if (I2C_InitStruct->I2C_mode & 0x01)
  {
    tmpreg |= (I2C_InitStruct->I2C_mode) | (I2C_InitStruct->I2C_TxEmptyIntr) |
              (I2C_InitStruct->I2C_RxFifoFullHold) | (I2C_InitStruct->I2C_StopDetMaster);
  }
  else
  {
    tmpreg |= (I2C_InitStruct->I2C_mode) | (I2C_InitStruct->I2C_SlaveAddressedLength) |
              (I2C_InitStruct->I2C_StopDetSlave) | (I2C_InitStruct->I2C_TxEmptyIntr) |
              (I2C_InitStruct->I2C_RxFifoFullHold);
  }
  I2Cx->CON = tmpreg;
  if (I2C_InitStruct->I2C_mode & 0x01)
  {
    I2C_SetFrequent(I2Cx, I2C_InitStruct->I2C_Speed);
  }
}

/************************************************************
 * I2C registers management functions
 * @brief  Reads the specified I2C register and returns its value.
 * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
 * @param  I2C_Register: specifies the register to read.
 *********************************************************************/
uint32_t I2C_ReadRegister(I2C_TypeDef *I2Cx, uint8_t I2C_Register)
{
  __IO uint32_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_REGISTER(I2C_Register));

  tmp = (uint32_t)I2Cx;
  tmp += I2C_Register;

  /* Return the selected register value */
  return (*(__IO uint32_t *)tmp);
}
/******************************************************
 * 主机写（发送）
 * master write(send)
 * *******************************************/
void I2C_WriteData(I2C_TypeDef *I2Cx, uint8_t Data)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  uint32_t tmpPreg;
  tmpPreg = Data;
  tmpPreg &= ~(1 << 8); //写
  I2Cx->DATACMD |= tmpPreg;
}
/******************************************************
 * 主机写（发送）最后一帧后加STOP
 * master send the last frame and send STOP sign
 * *******************************************/
void I2C_WriteData_Stop(I2C_TypeDef *I2Cx, uint8_t Data)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  uint32_t tmpPreg;
  tmpPreg = Data;
  tmpPreg &= ~(1 << 8); //写
  tmpPreg |= (1 << 9);  // STOP
  I2Cx->DATACMD |= tmpPreg;
}
/******************************************************
 * 主机读
 * master read
 * *******************************************/
uint8_t I2C_ReadData(I2C_TypeDef *I2Cx)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  uint8_t tempData;
  I2Cx->DATACMD |= I2C_DATA_CMD_CMD_Msk; //读
  while (I2C_GetITStatus(I2C0, I2C_STATUS_RFNF) == RESET)
    ;
  tempData = ((uint8_t)(I2Cx->DATACMD & 0xff));
  return tempData;
}
/******************************************************
 * 主机读最后一帧后加STOP
 * master read the last frame and send STOP sign
 * *******************************************/
uint8_t I2C_ReadData_Stop(I2C_TypeDef *I2Cx)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  uint8_t tempData;
  uint32_t tmpPreg;
  tmpPreg |= I2C_DATA_CMD_CMD_Msk | (1 << 9); //读+STOP
  I2Cx->DATACMD |= tmpPreg;
  while (I2C_GetITStatus(I2C0, I2C_STATUS_RFNF) == RESET)
    ;
  tempData = ((uint8_t)(I2Cx->DATACMD & 0xff));
  return tempData;
}

/******************************************************
 * 从机接收
 * *******************************************/
uint32_t I2C_ReceiveData(I2C_TypeDef *I2Cx)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  uint32_t tempData;
  tempData = I2Cx->DATACMD & 0x08ff;
  return tempData;
}

/******************************************************
 * 从机发送
 * *******************************************/
void I2C_SendData(I2C_TypeDef *I2Cx, uint8_t Data)
{
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  I2Cx->DATACMD |= Data;
}
//===DMA请求使能=======已结束======================================================
void I2C_DMACmd(I2C_TypeDef *I2Cx, uint32_t I2C_DMAReq, FunctionalState NewState)
{
  assert_param(IS_I2C_DMAReq(I2C_DMAReq));
  if (I2C_DMAReq == I2C_DMAReq_Rx)
  {
    (NewState != DISABLE) ? (I2Cx->DMACR |= I2C_DMAReq_Rx) : (I2Cx->DMACR &= ~I2C_DMAReq_Rx);
  }
  else
  {
    (NewState != DISABLE) ? (I2Cx->DMACR |= I2C_DMAReq_Tx) : (I2Cx->DMACR &= ~I2C_DMAReq_Tx);
  }
}
/*********************************************
 *threshold value of TX_DMA to raise the interrupt
控制 TX_EMPTY 中断触发的阈值设定。范围 0~7
 * *******************************************/
void I2C_TxDMAITthreshold(uint32_t TxDMAValue)
{
  assert_param(IS_I2C_TX_DMA_IT(TxDMAValue));
  I2C0->DMATDLR = TxDMAValue;
}
/*********************************************
 *threshold value of RX_FIFO to raise the interrupt
控制 RX_FULL 中断触发的阈值设定。范围 0~7
 * *******************************************/
void I2C_RxDMAITthreshold(uint32_t RxDMAValue)
{
  assert_param(IS_I2C_RX_DMA_IT(RxDMAValue));
  I2C0->DMARDLR = RxDMAValue;
}

/*************************************
 *  I2C 中断原始状态
 * ************************************************************************/
FlagStatus I2C_GetFlagStatus(I2C_TypeDef *I2Cx, uint32_t I2C_FLAG)
{
  assert_param(IS_I2C_GET_FLAG(I2C_FLAG));
  unsigned int tmpreg = 0;
  FlagStatus bitstatus = RESET;
  tmpreg = I2Cx->RAWINTRSTAT;
  tmpreg &= I2C_FLAG;
  if (tmpreg != 0)
  {
    /* I2C_FLAG is set */
    bitstatus = SET;
  }
  else
  {
    /* I2C_FLAG is reset */
    bitstatus = RESET;
  }
  return bitstatus;
}
/**************************************
//获取状态标志位：set or reset
****************************************************/
FlagStatus I2C_GetITStatus(I2C_TypeDef *I2Cx, uint32_t I2C_STATUS)
{
  assert_param(IS_I2C_GET_STATUS(I2C_STATUS));
  unsigned int tmpreg = 0;
  FlagStatus bitstatus = RESET;
  tmpreg = I2Cx->STATUS;
  tmpreg &= I2C_STATUS;
  if (tmpreg != 0)
  {
    /* I2C_FLAG is set */
    bitstatus = SET;
  }
  else
  {
    /* I2C_FLAG is reset */
    bitstatus = RESET;
  }
  return bitstatus;
}

//=============================已结束=====================================
//解除中断悬挂
void I2C_ClearITPendingBit(I2C_TypeDef *I2Cx, uint32_t I2C_IT)
{
  assert_param(IS_I2C_GET_IT(I2C_IT));
  /* Clear the selected flag */
  switch (I2C_IT)
  {
  //当master txfifo为空时，启用时钟延伸   #13
  case I2C_IT_MST_ON_HOLD:;
    break; // auto clear by hardware
  // slave接收到restart信号进入中断使能   #12
  case I2C_IT_RESTART_DET:
    I2Cx->CLRRESTARTDET;
    break;
  //从机进入响应广播地址进入中断   #11
  case I2C_IT_GEN_CALL:
    I2Cx->CLRGENCALL;
    break;
  // I2C接口是否产生了start或者restart信号，master和slaver都适用    #10
  case I2C_IT_START_DET:
    I2Cx->CLRSTARTDET;
    break;
  // i2c接口上是否产生了stop信号#9
  case I2C_IT_STOP_DET:
    I2Cx->CLRSTOP_DET;
    break;
  // i2c active 标志中断#8
  case I2C_IT_ACTIVITY:
    I2Cx->CLRACTIVITY;
    break;
  //*从机*发送1byte，主机未应答（slave类型中断）   #7
  case I2C_IT_RX_DONE:
    I2Cx->CLRRXDONE;
    break;
  //发送不能继续产生中断,master slave都适用#6
  case I2C_IT_TX_ABRT:
    I2Cx->CLRTXABRT;
    break;
  //从机准备发送数据前，拉低时钟直到写入数据后清除中断（从机模式中断） #5
  case I2C_IT_RD_REQ:
    I2Cx->CLRRDREQ;
    break;
  // Txfifo empty intr #4
  case I2C_IT_TX_EMPTY:;
    break;
  // Txfifo 溢出中断   #3
  case I2C_IT_TX_OVER:
    I2Cx->CLRTXOVER;
    break;
  // Rxfifo 满中断#2
  case I2C_IT_RX_FULL:;
    break;
  // RXfifo上溢中断    #1
  case I2C_IT_RX_OVER:
    I2Cx->CLRRXOVER;
    break;
  // rxfifo 被读空后接着读，产生下溢中断#0
  case I2C_IT_RX_UNDER:
    I2Cx->CLRRXUNDER;
    break;
  case I2C_IT_ALL:
    I2Cx->CLRINTR;
    break;
  default:
    printf("error has occur");
  }
}

/**********************************
 * Enables or disables the specified  interrupts.
 * ********************************************/
void I2C_ITConfig(I2C_TypeDef *I2Cx, uint32_t I2C_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_GET_IT(I2C_IT));

  I2Cx->INTRMASK = 0x00000000;
  if (NewState != DISABLE)
  {
    /* Enable the selected I2C interrupts */
    I2Cx->INTRMASK |= I2C_IT;
  }
  else
  {
    /* Disable the selected I2C interrupts */
    I2Cx->INTRMASK &= ~I2C_IT;
  }
}

//====================待===处=====理=====内======容=================
