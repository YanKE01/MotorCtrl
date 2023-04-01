/**
 * @copyright (C) COPYRIGHT 2022 Fortiortech Shenzhen
 * @file      FU68xx_2_DMA.c
 * @author    Fortiortech  Appliction Team
 * @since     Create:2021-05-14
 * @date      Last modify:2022-07-14
 * @brief     This file contains FU68xx_2_DMA function used for Motor Control.
 */

#include <FU68xx_2_DMA.h>
#include <FU68xx_2_MCU.h>

/* -------------------------------------------------------------------------------------------------
    Function Name  : Init_DMA
    Description    :  
*   DMA模块的配置（DMA0/1通用）
*
*   @param IEMod  DMA中断配置，可用参数如下
*                   ENIE     启用DMA中断
*                   DISIE    禁用DMA中断
*   @param ENDIAN DMA传输顺序（发送十六位数据时适用）
*                   FLSB     低8位先发（发送8位数据时必须选用该项）
*                   FMSB     高8位先发（发送8位数据时必须选用该项）
    Date           : 2020-08-07
    Parameter      : IEMod   : [输入] 
**			         FirstMod: [输入] 
------------------------------------------------------------------------------------------------- */
void Init_DMA(uint8 IEMod, uint8 FirstMod)
{
    DMA0_CR0 = IEMod | FirstMod;
}

/* -------------------------------------------------------------------------------------------------
    Function Name  : Set_DMA
    Description    : 

 *  DMA设置
 *
 *  @param   Ch         DMA通道
 *  @param   Pipe       DMA管道，可选参数如下
 *                         UART_XDATA    UART->XDATA
 *                         XDATA_UART    UART<-XDATA
 *                         I2C_XDATA     I2C ->XDATA
 *                         XDATA_I2C     I2C <-XDATA
 *                         SPI_XDATA     SPI ->XDATA
 *                         XDATA_SPI     SPI <-XDATA
 *  @param   Addr       传输首地址，可取地址范围：0x0000~0x0317
 *  @param   Len        数据包大小(1~64)
 
    Date           : 2020-08-07
    Parameter      : Ch:    [输入] 
 **       			 Pipe:  [输入] 
 **       			 Addr:  [输入] 
 **       			 Len:   [输入] 
------------------------------------------------------------------------------------------------- */
void Set_DMA(uint8 Ch, uint8 Pipe, uint16* Addr, uint8 Len)
{
    Wait_DMA(Ch);
    ClrBit(*(&DMA0_CR0 + Ch), DMAEN);

    SetReg(*(&DMA0_CR0 + Ch), DMACFG0 | DMACFG1 | DMACFG2, Pipe);

    *(&DMA0_CR1 + Ch) = ((uint16)(Len - 1) << 10) | ((uint16)Addr & 0x03ff);
}

/* -------------------------------------------------------------------------------------------------
    Function Name  : Set_DBG_DMA
    Description    : 设置DMA1的DBG模式,Addr 要DBG输出的地址
    Date           : 2020-08-07
    Parameter      : Addr: [输入/出] 
------------------------------------------------------------------------------------------------- */
void Set_DBG_DMA(uint16* Addr)
{
    ClrBit(DMA1_CR0, DMAEN);
    DMA1_CR0 = DBGEN | XDATA_SPI;
    if (!ReadBit((uint16)Addr, 0x4000)) DMA1_CR0 |= DBGSW;

    DMA1_CR1 = 0x1c00 | ((uint16)Addr & 0x03fff);

    Switch_DMA(1);
}
