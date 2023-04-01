/**
 * @copyright (C) COPYRIGHT 2022 Fortiortech Shenzhen
 * @file      ADCInit.c
 * @author    Fortiortech  Appliction Team
 * @since     Create:2021-05-14
 * @date      Last modify:2022-07-14
 * @brief     This file contains ADC function function used for Motor Control
 */   
#include <FU68xx_2.h>
#include <Myproject.h>
#include <FU68xx_2_System.h>

/**
 * @brief      ADC硬件设备初始化配置，使能ADC，通道配置，采样时间配置，中断配置
 */
void ADC_Init(void)
{
    uint16 ADCVREF_DelayCnt;
    /* -----ADC参考电压配置----- */
    VREFConfig(Enable);                                                             // ADC参考电压配置
    SetBit(P3_AN, P35);                                                             //送出给P3.5的VREF电压，P3.5需外接电容
    /*  -------------------------------------------------------------------------------------------------
        ADC基本配置
        -------------------------------------------------------------------------------------------------*/
    SetBit(ADC_CR, ADCEN);                                                          // 使能ADC
    /*  -------------------------------------------------------------------------------------------------
        1、ADC参考电压选择
        2、使能VREF，用于给ADC提供内部参考基准
        3、P3.5配置模拟IO，VREFEN为1-内部参考电压提供给ADC，同时送出给P3.5的VREF电压;
        4、P3.5配置模拟IO，VREFEN为0-外部参考电压提供给ADC，需外部提供ADC参考。
        -------------------------------------------------------------------------------------------------*/
    SetBit(VREF_VHALF_CR, VREFEN);                                                  //使能VREF
    
    for (ADCVREF_DelayCnt = 0; ADCVREF_DelayCnt < 2000; ADCVREF_DelayCnt++) {};     //等待VREF稳定
    
    /*  -------------------------------------------------------------------------------------------------
        1、ADC通道配置
        2、使能相应Pin为模拟Pin，禁止数字功能
        3、使能通道MASK，连接Pin到ADC模块
        4、ADC_CH0--P20_AN--IU--固定                 ADC_CH5--P32_AN
        5、ADC_CH1--P23_AN--IV--固定                 ADC_CH6--P33_AN
        6、ADC_CH2--P24_AN--DCBUS--固定              ADC_CH7--P34_AN
        7、ADC_CH3--P25_AN--VSP                      ADC_CH8--P21_AN
        8、ADC_CH4--P27_AN--IBUS/IW--固定            ADC_CH9--P16_AN
                                                 ADC_CH10--P14_AN
                                                 ADC_CH11--P15_AN
        -------------------------------------------------------------------------------------------------*/
    SetBit(P3_AN,  P34);                                                            
    
    SetBit(P2_AN, P27 | P25 | P24 | P23 | P20);
    
    SetBit(ADC_MASK_SYSC, CH7EN | CH6EN | CH4EN | CH3EN | CH2EN | CH1EN | CH0EN);    // 使能AD
    
    /* -----ADC通道采样时钟周期设置----- */
    SetBit(ADC_MASK_SYSC, 0x3000);
    
    ADC_SYSC  = 0x33;
    
    SetReg(ADC_CR, ADCIF | ADCIE, 0x00);                                            // 清标志位和关中断
}



