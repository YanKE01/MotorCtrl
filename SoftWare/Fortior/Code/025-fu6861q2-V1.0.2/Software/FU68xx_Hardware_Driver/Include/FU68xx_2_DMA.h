/**
  ******************************************************************************
  * @file    FU68xx_2_DMA.h
  * @author  Fortiortech MCU Team
  * @version V1.0
  * @date    10-Apr-2017
  ******************************************************************************
  * @attention
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT FU6812,FU6861.
  ******************************************************************************
  */
#ifndef __FU68XX_2_DMA_H__
#define __FU68XX_2_DMA_H__

#include <FU68xx_2_MCU.h>

/*************************************************************************************///Defined CMD(Don't touch)
// DMA管道参数表
 #define UART_XDATA      0x00                            // DMA管道--UART->XDATA
 #define XDATA_UART      (DMACFG0)                       // DMA管道--UART<-XDATA
 #define I2C_XDATA       (DMACFG1)                       // DMA管道--I2C ->XDATA
 #define XDATA_I2C       (DMACFG0 | DMACFG1)             // DMA管道--I2C <-XDATA
 #define SPI_XDATA       (DMACFG2)                       // DMA管道--SPI ->XDATA
 #define XDATA_SPI       (DMACFG2 | DMACFG0)             // DMA管道--SPI <-XDATA

// DMA模块参数配置表
 #define ENIE DMAIE                                      // 使能DMA中断
 #define DISIE 0x00                                      // 禁能DMA中断
 #define FLSB 0x00                                       // DMA先发低8位
 #define FHSB ENDIAN                                     // DMA先发高8位
/*************************************************************************************///Config
/*************************************************************************************///External Function
#define Wait_DMA(a)       while (ReadBit(*(&DMA0_CR0 + a), DMABSY))
#define Switch_DMA(a)     SetBit(*(&DMA0_CR0 + a), DMAEN | DMABSY)

extern void Init_DMA(uint8 IEMod, uint8 FirstMod);
extern void Set_DMA(uint8 Ch, uint8 Pipe, uint16* Addr, uint8 Len);
extern void Set_DBG_DMA(uint16* Addr);

#endif