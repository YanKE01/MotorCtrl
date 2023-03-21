/**
 * @copyright (C) COPYRIGHT 2022 Fortiortech Shenzhen
 * @file      EXTIInit.c
 * @author    Fortiortech  Appliction Team
 * @since     Create:2021-05-14
 * @date      Last modify:2022-07-14
 * @brief     This file contains EXTI init function used for Motor Control.
 */ 
#include <FU68xx_2.h>
#include <Myproject.h>

/**
 * @brief      外部中断配置
 */
void EXTI_Init(void)
{
    /* -----EXTI Input Pin 配置----- */
    ClrBit(P0_OE, P00);                     // config P00 as input，配置P0.0为硬件过流FO端口
    ClrBit(P0_PU, P00);                     // 0:disable pull up, 1:enable P10 pull up
    /*  -------------------------------------------------------------------------------------------------
        1、外部中断模式配置
        2、IT01/IT00 = 00: 上升沿产生中断
        3、IT01/IT00 = 01: 下降沿产生中断
        4、IT01/IT00 = 1x: 上升/下降沿产生中断
        -------------------------------------------------------------------------------------------------*/
    IF0  = 0;                               // clear P00 interrupt flag
    IT01 = 0;
    IT00 = 1;                               // 00: rising edge interrupt，01: failing edge interrupt，1x: edge-change mode interrupt
    /*  -------------------------------------------------------------------------------------------------
        1、外部中断优先级配置及芯片中断总使能
        2、PX01/PX00，中断优先级控制值从0-3依次表示优先级从最低到最高，共4级优化级控制
        3、EX0，外部中断0使能
        4、EA,芯片中断总使能
        5、外部中断是否有滤波的配置，决定于选择硬件保护触发信号源，外部中断0或者比较器3中断
        6、若选择了比较器3中断，则外部中断无法进行滤波配置
        -------------------------------------------------------------------------------------------------*/
    PX01 = 1;
    PX00 = 1;                               // 中断优先级别3，中断优先级最高,
    EX0 = 1;                                // 使能外部中断0, POO位外部中断输入硬件
    EA = 1;                                 // 使能全局中断
}


/**
 * @brief      睡眠模式初始化
 */
void Sleepmode_Init(void)
{
    ClrBit(P1_OE, P11);                     // config   P11 as input
    ClrBit(P1_PU, P11);                     // diasable P11 Pull Up
    // ClrBit(P1_AN, P11);                  // diasable P11 analog function
    ClrBit(P1_IF, P11);                     // clear        P11 interrupt flag
    ClrBit(P1_IE, P11);                     // config   P11 as the source of EXTI1
    IT11 = 1;
    IT10 = 0;                               // 00: posedge mode interrupt，01: negedge mode interrupt，1x: edge-change mode interrupt
    PX11 = 0;
    PX10 = 0;                               // 中断优先级别0，中断优先级最高
    EX1 = 1;                                // 使能外部中断1, P11位外部中断输入硬件
    EA = 1;                                 // 使能全局中断
}
