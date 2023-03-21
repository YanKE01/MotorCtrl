/**
 * @copyright (C) COPYRIGHT 2022 Fortiortech Shenzhen
 * @file      SPIInit.c
 * @author    Fortiortech  Appliction Team
 * @since     Create:2021-05-14
 * @date      Last modify:2022-07-14
 * @brief    This file contains SPI initial function used for Motor Control.
 */   
    
#include <FU68xx_2.h>
#include <Myproject.h>

/**
 * @brief      SPI相关参数初始化
 */
void SPI_Init(void)
{
    ClrBit(SPI_CR1, SPIEN);                                            // 0：disable SPI; 1：enable
    /*  -------------------------------------------------------------------------------------------------
        SPI管脚配置
        1、禁止UART复用，P06配置为MISO，P05配置为MOSI
        2、禁止比较器输出复用，P07配置为SCLK
        -------------------------------------------------------------------------------------------------*/
    ClrBit(PH_SEL, UARTEN);                                             // 0,P06 as GPIO or SPI_MISO,P05 as GPIO or SPI_MOSI;1,P06 and p07 as USART
    /*  -------------------------------------------------------------------------------------------------
        1、SPI时钟相位/极性配置
        2、CPHA = 0, CPOL = 0:上升沿接收，下降沿发送，空闲电平为低
        3、CPHA = 0, CPOL = 1:上升沿发送，下降沿接收，空闲电平为高
        4、CPHA = 1, CPOL = 0:上升沿发送，下降沿接收，空闲电平为低
        5、CPHA = 1, CPOL = 1:上升沿接收，下降沿发送，空闲电平为高
        -------------------------------------------------------------------------------------------------*/
    SetReg(SPI_CR0, CPHA | CPOL, CPOL);
    /*  -------------------------------------------------------------------------------------------------
        1、SPI从方式选择配置
        2、00：3线从方式或3线主方式，NSS信号不连到端口管脚
        3、01：4线从方式或4线多主方式，NSS配置为输入
        4、1x：4线单主方式，NSS配置为输出，NSS信号输出x电平
        -------------------------------------------------------------------------------------------------*/
//    SetReg(SPI_CR1, NSSMOD0 | NSSMOD1, NSSMOD0 | NSSMOD1);//4线模拟 
		SetReg(SPI_CR1, NSSMOD0 | NSSMOD1, NSSMOD0);//单线模式 
    SetBit(SPI_CR0, SPIMS);                                             // 0:Slave, 1:Master
    /*  -------------------------------------------------------------------------------------------------
        1、SPI中断配置
        2、SPIF：SPI字节传输完成中断标志，硬件置位，软件清零
        3、WCOL：SPI写冲突中断（发送缓冲器非空时写操作），硬件置位，软件清零
        4、MODF：SPI方式错误中断（多主方式NSS被拉低，MSTEN和SPIEN被清零）硬件置位，软件清零
        5、RXOVRN：SPI接收溢出中断（SPI接收缓冲器接收溢出），硬件置位，软件清零
        -------------------------------------------------------------------------------------------------*/
    SetReg(SPI_CR1, SPIIF | WCOL | MODF | RXOVR, 0x00);                 // SPI所有中断清除
    SPIIE = 0;                                                          // SPI中断使能
    SPI_CLK = 0;                                                        // Fspi = Fcpu / (2*(SPI_CLK + 1)) = 6MHz
    SetBit(SPI_CR1, SPIEN);                                             // enable SPI
}


/** 
 * @brief        SPI传输数据
 * @param[in]    Data  传输数据，uint16格式
 * @param[in]    Channel  传输通道，取值0~3
 */
void SPI_SendData(uint16 Data, uint8 Channel)
{
    if (!ReadBit(SPI_CR0, SPIBSY))
    {
        Data = ((Data >> 4) + (0x1000));
        
        switch (Channel)
        {
            case 0:
                Data &= 0x3fff;
                break;
                
            case 1:
                Data |= 0x4000;
                break;
                
            case 2:
                Data |= 0x8000;
                break;
                
            case 3:
                Data |= 0xc000;
                break;
                
            default:
                break;
        }
        
        ClrBit(SPI_CR1, NSSMOD0);
        SPI_DR = Data >> 8;
        SPI_DR = Data;
        SetBit(SPI_CR1, NSSMOD0);
    }
}
