/**
  ******************************************************************************
  * @file    lcm32f037_uart.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    2021-05-21
  * @brief   This file provides all the uart emulation firmware functions.
  ******************************************************************************/
/**
  ******************************************************************************
  * @attention:
  * 
  * 
  * 
  * 
  ******************************************************************************/
#include "LCM32F037.h"
#include "lcm32f037_uart.h"
#include "lcm32f037_rcc.h"

/*--------------------------------------------------------------------------------------------
串口时钟使能：LCM32F037 包含UART0  UART1  
--------------------------------------------------------------------------------------------*/
void UART_DeInit(UART_TypeDef *UARTx)
{

  if (UARTx == UART0)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART0, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART0, DISABLE);
  }
  else
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART1, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART1, DISABLE);
  }
}

/*--------------------------------------------------------------------------------------------
串口波特率设置
--------------------------------------------------------------------------------------------*/
void UART_BaudRateConfig(UART_TypeDef *UARTx, uint32_t baud)
{

  uint32_t freq;
  RCC_ClocksTypeDef RCC_Clocks;

  uint32_t baud16;
  uint16_t div_int;
  uint32_t div_frac;

  RCC_GetClockFreq(&RCC_Clocks);
  if (UARTx == UART0)
    freq = RCC_Clocks.UART0_Frequency;
  else if (UARTx == UART1)
    freq = RCC_Clocks.UART1_Frequency;
#ifdef FPGA_K7
  freq = 30000000;
#endif

  baud16 = baud * 16;
  div_int = freq / baud16;
  div_frac = freq - baud16 * div_int;
  div_frac = (div_frac * 64 + baud16 / 2) / baud16;
  UARTx->IBRD = div_int;
  //temp=UARTx->IBRD;
  UARTx->FBRD = div_frac;
}

/*--------------------------------------------------------------------------------------------
串口初始化
--------------------------------------------------------------------------------------------*/
void UART_Init(UART_TypeDef *UARTx, UART_InitTypeDef *UART_InitStruct)
{
  volatile uint32_t tmpreg = 0;
  UART_BaudRateConfig(UARTx, (UART_InitStruct->UART_BaudRate));
  //frame config
  tmpreg = ((UART_InitStruct->UART_WordLength) | (UART_InitStruct->UART_StopBits) | (UART_InitStruct->UART_Parity));
  UARTx->LCR |= tmpreg;

  tmpreg = UARTx->CR;
  tmpreg &= 0xffff07ff;
  tmpreg = UART_InitStruct->UART_HardwareFlowControl;
  UARTx->CR |= tmpreg;

  tmpreg = UART_InitStruct->UART_Mode;
  if (tmpreg == (UART_Mode_Rx | UART_Mode_Tx))
  {
    UARTx->CR |= UART_Mode_Rx;
    UARTx->CR |= UART_Mode_Tx;
  }
  else if (tmpreg == UART_Mode_Tx)
  {
    UARTx->CR |= UART_Mode_Tx;
    UARTx->CR &= ~UART_Mode_Rx;
  }
  else //receive only
  {
    UARTx->CR |= UART_Mode_Rx;
    UARTx->CR &= ~UART_Mode_Tx;
  }
}

/*--------------------------------------------------------------------------------------------
串口结构参数定义
--------------------------------------------------------------------------------------------*/
void UART_StructInit(UART_InitTypeDef *UART_InitStruct)
{
  /* UART_InitStruct members default value */
  UART_InitStruct->UART_BaudRate = 115200;
  UART_InitStruct->UART_WordLength = UART_WordLength_8b;
  UART_InitStruct->UART_StopBits = UART_StopBits_1;
  UART_InitStruct->UART_Parity = UART_Parity_No;
  UART_InitStruct->UART_Mode = UART_Mode_Rx | UART_Mode_Tx;
  UART_InitStruct->UART_HardwareFlowControl = UART_HardwareFlowControl_None;
}

/*--------------------------------------------------------------------------------------------
串口使能
--------------------------------------------------------------------------------------------*/
void UART_Cmd(UART_TypeDef *UARTx, FunctionalState NewState)
{
  if (NewState != DISABLE)
    UARTx->CR |= UARTEN_ON;
  else
    UARTx->CR &= UARTEN_OFF;
} /*EditStatus:end*/

/*--------------------------------------------------------------------------------------------
接受发送过程中关闭uart 接受或发送完当前字节
--------------------------------------------------------------------------------------------*/
void UART_DirectionModeCmd(UART_TypeDef *UARTx, uint32_t UART_DirectionMode, FunctionalState NewState)
{
  /* Check the parameters */
  //assert_param(IS_UART_DIRECTION(UART_DirectionMode));
  //assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != ENABLE)
  {
    UARTx->CR &= ~UART_DirectionMode;
  }
  else
  {
    UARTx->CR |= UART_DirectionMode;
  }
}

/*--------------------------------------------------------------------------------------------
串口发送函数
--------------------------------------------------------------------------------------------*/
/* Data transfers functions ***************************************************/
void UART_SendData(UART_TypeDef *UARTx, uint8_t Data)
{
  UARTx->DR = Data;
}

/*--------------------------------------------------------------------------------------------
串口接受函数
--------------------------------------------------------------------------------------------*/
uint16_t UART_ReceiveData(UART_TypeDef *UARTx)
{
  uint32_t tmpreg = 0;
  tmpreg = UARTx->DR;
  return (uint16_t)(tmpreg & 0xff);
}
void UART_SendBreak(UART_TypeDef *UARTx)
{
  /* set and cleared by software */
  UARTx->LCR |= UARTLCR_BRK;
}

/*--------------------------------------------------------------------------------------------
串口fifo深度选择
--------------------------------------------------------------------------------------------*/
void UART_FIFOLevelConfig(UART_TypeDef *UARTx, uint32_t RXIFLSelect, uint32_t TXIFLSelect)
{
  //assert_param(IS_UART_FIFO_SELECT(FIFOSelect));
  //assert_param(IS_UART_FIFO(FIFOSelect));
  uint32_t tmpreg = 0;
  tmpreg = UARTx->IFLS;
	tmpreg&=0xFFFFFFC0;
  tmpreg |=RXIFLSelect ;
  tmpreg |=TXIFLSelect;
  UARTx->IFLS = tmpreg;
} /*EditStatus:end&&check*/

/* IrDA mode functions ********************************************************/
void UART_IrDACmd(UART_TypeDef *UARTx, FunctionalState NewState)
{
  if (NewState != ENABLE)
    UARTx->CR &= UART_SIREN_OFF;
  else
    UARTx->CR |= UART_SIREN_ON;
}; /*  (EditStatus:end)*/

/*--------------------------------------------------------------------------------------------
串口DMA使能
--------------------------------------------------------------------------------------------*/
/* DMA transfers management functions *****************************************/
void UART_DMACmd(UART_TypeDef *UARTx, uint32_t UART_DMAReq, FunctionalState NewState)
{
  if (UART_DMAReq == UART_DMAReq_Rx)
  {
    (NewState != DISABLE) ? (UARTx->DMACR |= UART_DMAReq_Rx) : (UARTx->DMACR &= ~UART_DMAReq_Rx);
  }
  else
  {
    (NewState != DISABLE) ? (UARTx->DMACR |= UART_DMAReq_Tx) : (UARTx->DMACR &= ~UART_DMAReq_Tx);
  }
} /*EditStatus:end*/

/*--------------------------------------------------------------------------------------------
串口中断使能
--------------------------------------------------------------------------------------------*/
/* Interrupts and flags management functions **********************************/
void UART_ITConfig(UART_TypeDef *UARTx, uint32_t UART_IT, FunctionalState NewState)
{
  //assert_param(IS_UART_IT(UART_IT));
  if (NewState == ENABLE)
  {
    UARTx->IMSC |= UART_IT;
  }
  else
  {
    UARTx->IMSC &= ~UART_IT;
  }
}

/*--------------------------------------------------------------------------------------------
串口运行标志位读取
--------------------------------------------------------------------------------------------*/
FlagStatus UART_GetFlagStatus(UART_TypeDef *UARTx, uint32_t UART_FLAG)
{
  //  uint32_t temp;
  //  temp=UARTx->FR;
  assert_param(IS_UART_STATUSFLAG(UART_FLAG));
  if (UART_FLAG > (uint32_t)0X800)
  {
    if (UARTx->RSR & (UART_FLAG >> 12))
      return SET;
    else
      return RESET;
  }
  else
  {
    if (UARTx->FR & UART_FLAG)
      return SET;
    else
      return RESET;
  }
}

/*--------------------------------------------------------------------------------------------
屏蔽中断状态位读取
--------------------------------------------------------------------------------------------*/
ITStatus UART_GetITStatus(UART_TypeDef *UARTx, uint32_t UART_IT)
{
  if (UARTx->MIS & UART_IT)
    return SET;
  else
    return RESET;
}

/*--------------------------------------------------------------------------------------------
原始中断状态读取
--------------------------------------------------------------------------------------------*/
ITStatus UART_GetRawITStatus(UART_TypeDef *UARTx, uint32_t UART_IT)
{
  if (UARTx->RIS & UART_IT)
    return SET;
  else
    return RESET;
}

/*--------------------------------------------------------------------------------------------
清中断标志
--------------------------------------------------------------------------------------------*/
void UART_ClearITPendingBit(UART_TypeDef *UARTx, uint32_t UART_IT)
{
  UARTx->ICR |= UART_IT;
}

/*--------------------------------------------------------------------------------------------
串口fifo使能
--------------------------------------------------------------------------------------------*/
void UART_FIFOEnable(UART_TypeDef *UARTx, uint32_t NewState)
{
  if (NewState != DISABLE)
    UARTx->LCR |= 0X10;
  else //default
    UARTx->LCR &= 0XEF;
}
