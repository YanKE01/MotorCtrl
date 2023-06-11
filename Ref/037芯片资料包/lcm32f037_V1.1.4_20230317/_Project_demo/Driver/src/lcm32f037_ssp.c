/**
  ******************************************************************************
  * @file    lcm32f037_ssp.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    2021-05-21
  * @brief   This file provides all the ssp emulation firmware functions.
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
#include "lcm32f037_ssp.h"
#include "lcm32f037_gpio.h"
#include <stdio.h>

int temp, temp0, temp1, temp2;
int flag;

/*--------------------------------------------------------------------------------------------
SPI RESET
  --------------------------------------------------------------------------------------------*/
void SPI_DeInit(SPI_TypeDef *SPIx)
{
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_SSP0, ENABLE);

  RCC_APB1PeriphResetCmd(RCC_APB1Periph_SSP0, DISABLE);
}

/*--------------------------------------------------------------------------------------------
SPI参数初始化
  --------------------------------------------------------------------------------------------*/
void SPI_StructInit(SPI_InitTypeDef *SPI_InitStruct)
{
  SPI_InitStruct->SPI_Mode = SPI_Mode_Master;
  SPI_InitStruct->SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStruct->SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStruct->SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStruct->SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
  SPI_InitStruct->SPI_FirstBit = SPI_FirstBit_MSB;  //MSB is alaways.
  SPI_InitStruct->SPI_SlaveTx = SPI_SlaveTx_Enable; //control whether the spi send data only in slave mode.
}

/*--------------------------------------------------------------------------------------------
SPI参数初始化
  --------------------------------------------------------------------------------------------*/
void SPI_Init(SPI_TypeDef *SPIx, SPI_InitTypeDef *SPI_InitStruct)
{
  uint16_t tmpreg = 0x00, tmp = 0x00;
  assert_param(IS_SPI_MODE(SPI_InitStruct->SPI_Mode));
  assert_param(IS_SPI_DATA_SIZE(SPI_InitStruct->SPI_DataSize));
  assert_param(IS_SPI_CPOL(SPI_InitStruct->SPI_CPOL));
  assert_param(IS_SPI_CPHA(SPI_InitStruct->SPI_CPHA));
  assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_InitStruct->SPI_BaudRatePrescaler));
  assert_param(IS_SPI_FIRST_BIT(SPI_InitStruct->SPI_FirstBit));
  assert_param(IS_SPI_SLAVE_TX(SPI_InitStruct->SPI_SlaveTx));

  tmpreg = SPIx->SSPCR0;
  tmpreg &= 0XFFFF0000;
  tmpreg = (tmpreg | (SPI_InitStruct->SPI_BaudRatePrescaler) |
            (SPI_InitStruct->SPI_CPOL) |
            (SPI_InitStruct->SPI_CPHA) |
            (SPI_InitStruct->SPI_DataSize));
  SPIx->SSPCR0 = tmpreg;

  tmp = SPIx->SSPCR1;
  tmp &= 0XFFFFFFF0;
  tmp = ((SPI_InitStruct->SPI_SlaveTx) | (SPI_InitStruct->SPI_Mode));
  SPIx->SSPCR1 = tmp;
  SPIx->SSPCPSR = 0x02;
}

/*--------------------------------------------------------------------------------------------
   SPI使能
--------------------------------------------------------------------------------------------*/
void SPI_Cmd(SPI_TypeDef *SPIx, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    SPIx->SSPCR1 |= SSP_CR1_SSE;
  }
  else
  {
    SPIx->SSPCR1 &= ~SSP_CR1_SSE;
  }
}

/*--------------------------------------------------------------------------------------------
  帧格式设置：TI TI串行同步帧格式
--------------------------------------------------------------------------------------------*/
void SPI_TIModeCmd(SPI_TypeDef *SPIx, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    /* code */
    SPIx->SSPCR0 &= ~((uint16_t)(0x03 << 4));
    SPIx->SSPCR0 |= SSP_CR0_FRF_TI;
  }
  else
  {
    SPIx->SSPCR0 &= ~((uint16_t)(3 << 4));
    SPIx->SSPCR0 |= SSP_CR0_FRF_MT;
  }
}

/*--------------------------------------------------------------------------------------------
    帧格式设置：National microwire
--------------------------------------------------------------------------------------------*/
void SPI_NMModeCmd(SPI_TypeDef *SPIx, FunctionalState NewState)
{
  /* code */
  if (NewState != DISABLE)
  {
    /* code */
    SPIx->SSPCR0 &= ~(uint16_t)(3 << 4);
    SPIx->SSPCR0 |= SSP_CR0_FRF_NM;
  }
  else
  {
    SPIx->SSPCR0 &= ~(uint16_t)(3 << 4);
    SPIx->SSPCR0 |= SSP_CR0_FRF_MT;
  }
}

/*--------------------------------------------------------------------------------------------
   帧数据长度选择
--------------------------------------------------------------------------------------------*/
void SPI_DataSizeConfig(SPI_TypeDef *SPIx, uint16_t SPI_DataSize)
{
  assert_param(IS_SPI_DATA_SIZE(SPI_DataSize));
  SPIx->SSPCR0 &= ((uint16_t)0xFFF0);
  SPIx->SSPCR0 |= SPI_DataSize;
}

/*--------------------------------------------------------------------------------------------
   发送接收函数
--------------------------------------------------------------------------------------------*/
void SPI_SendData8(SPI_TypeDef *SPIx, uint8_t Data)
{
  SPIx->SSPDR = Data;
}
void SPI_SendData16(SPI_TypeDef *SPIx, uint16_t Data)
{
  SPIx->SSPDR = Data;
}
uint8_t SPI_ReceiveData8(SPI_TypeDef *SPIx)
{
  uint8_t temp = 0x00;
  temp = SPIx->SSPDR;
  return temp;
}
uint16_t SPI_ReceiveData16(SPI_TypeDef *SPIx)
{
  uint16_t temp = 0x00;
  temp = SPIx->SSPDR;
  return temp;
}

/*--------------------------------------------------------------------------------------------
   SPI dma使能
--------------------------------------------------------------------------------------------*/
void SPI_DMACmd(SPI_TypeDef *SPIx, uint16_t SPI_DMAReq, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    SPIx->SSPDMACR |= SPI_DMAReq;
  }
  else
  {
    SPIx->SSPDMACR |= ~SPI_DMAReq;
  }
}

/*--------------------------------------------------------------------------------------------
   SPI 中断使能函数
--------------------------------------------------------------------------------------------*/
void SPI_ITConfig(SPI_TypeDef *SPIx, uint8_t SPI_IT, FunctionalState NewState)
{
  assert_param(IS_SPI_CONFIG_IT(IT));
  if (NewState == DISABLE)
  {
    SPIx->SSPIMSC &= ~SPI_IT;
  }
  else
  {
    SPIx->SSPIMSC |= SPI_IT;
  }
}

/*--------------------------------------------------------------------------------------------
   SPI FIFO状态查询函数
--------------------------------------------------------------------------------------------*/
FlagStatus SPI_GetFlagStatus(SPI_TypeDef *SPIx, uint16_t SPI_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_GET_FLAG(SPI_FLAG));

  /* Check the status of the specified SPI flag */
  if ((SPIx->SSPSR & SPI_FLAG) != (uint16_t)RESET)
  {
    /* SPI_I2S_FLAG is set */
    bitstatus = SET;
  }
  else
  {
    /* SPI_I2S_FLAG is reset */
    bitstatus = RESET;
  }
  /* Return the SPI_I2S_FLAG status */
  return bitstatus;
}

/*--------------------------------------------------------------------------------------------
   SPI 中断标志清除函数
--------------------------------------------------------------------------------------------*/
void SPI_ClearFlag(SPI_TypeDef *SPIx, uint16_t SPI_ERROR_FLAG)
{
  SPIx->SSPICR |= SPI_ERROR_FLAG;
}

/*--------------------------------------------------------------------------------------------
查询中断标志位
--------------------------------------------------------------------------------------------*/
ITStatus SPI_GetITStatus(SPI_TypeDef *SPIx, uint8_t SPI_IT)
{
  assert_param(IS_SPI_CONFIG_IT(IT));
  if (SPIx->SSPMIS & SPI_IT)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/*--------------------------------------------------------------------------------------------
查询原始状态函数 只读
--------------------------------------------------------------------------------------------*/
ITStatus SPI_GetITRawStatus(SPI_TypeDef *SPIx, uint8_t SPI_IT)
{
  if (SPIx->SSPRIS & SPI_IT)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}
