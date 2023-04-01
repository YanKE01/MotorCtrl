/* --------------------------- (C) COPYRIGHT 2020 Fortiortech ShenZhen -----------------------------
    File Name      : ADCInit.c
    Author         : Fortiortech  Appliction Team
    Version        : V1.0
    Date           : 2020-09-30
    Description    : This file contains .C file function used for Motor Control.
----------------------------------------------------------------------------------------------------  
                                       All Rights Reserved
------------------------------------------------------------------------------------------------- */
/* Includes -------------------------------------------------------------------------------------*/
#include <FU68xx_2.h>
#include <Myproject.h>
#include <FU68xx_2_System.h>

/* -------------------------------------------------------------------------------------------------
    Function Name  : ADC_Init
    Description    : ADC硬件设备初始化配置，使能ADC，通道配置，采样时间配置，中断配置
    Date           : 2020-09-30
    Parameter      : None
------------------------------------------------------------------------------------------------- */
void ADC_Init(void)
{
    uint16 ADCVREF_DelayCnt;
    /* -----ADC参考电压配置----- */ 
    VREFConfig(VREF4_5, Enable);								                                   // ADC参考电压配置

    /* -----ADC基本配置----- */ 
    SetBit(ADC_CR, ADCEN);		                                                                   // 使能ADC
                               
    /*-------------------------------------------------------------------------------------------------
    ADC参考电压选择
    使能VREF，用于给ADC提供内部参考基准
    P3.5配置模拟IO，VREFEN为1-内部参考电压提供给ADC，同时送出给P3.5的VREF电压;
    P3.5配置模拟IO，VREFEN为0-外部参考电压提供给ADC，需外部提供ADC参考。
    -------------------------------------------------------------------------------------------------*/
    SetBit(VREF_VHALF_CR, VREFEN);    
	//使能VREF
	SetBit(P3_AN, P35); 
    for(ADCVREF_DelayCnt=0;ADCVREF_DelayCnt<2000;ADCVREF_DelayCnt++){};		                       //等待VREF稳定

    /*-------------------------------------------------------------------------------------------------
    ADC通道配置
    1、使能相应Pin为模拟Pin，禁止数字功能
    2、使能通道MASK，连接Pin到ADC模块
    ADC_CH0--P20_AN--IU--固定                 ADC_CH5--P32_AN
    ADC_CH1--P23_AN--IV--固定                 ADC_CH6--P33_AN
    ADC_CH2--P24_AN--DCBUS--固定              ADC_CH7--P34_AN
    ADC_CH3--P25_AN--VSP                      ADC_CH8--P21_AN
    ADC_CH4--P27_AN--IBUS/IW--固定            ADC_CH9--P16_AN
                                              ADC_CH10--P14_AN
                                              ADC_CH11--P15_AN
    -------------------------------------------------------------------------------------------------*/
    SetBit(P3_AN,P32);

    SetBit(P2_AN, P27 | P24);
    SetBit(ADC_MASK_SYSC,CH5EN | CH4EN  | CH2EN);		                                           //Config P2.7 as ADC4 IBUS/IW

    /* -----ADC通道采样时钟周期设置----- */     
    SetBit(ADC_MASK_SYSC, 0x3000);
    ADC_SYSC  = 0x33;

    SetReg(ADC_CR, ADCIF|ADCIE,0x00);                                                              // 清标志位和关中断
}



