/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2023-03-20 21:07:44
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-04-01 19:22:16
 * @FilePath: \Software\User\Source\Hardware\GPIO.c
 */
/**
 * @copyright (C) COPYRIGHT 2022 Fortiortech Shenzhen
 * @file      GPIOInit.c
 * @author    Fortiortech  Appliction Team
 * @since     Create:2021-05-14
 * @date      Last modify:2022-07-14
 * @brief     This file contains GPIO initial function used for Motor Control.
 */

#include <FU68xx_2.h>
#include <Myproject.h>

/**
 * @brief      为提高芯片的抗干扰能力，降低芯片功耗，请在具体项目时，将不需要用的GPIO默认都配置为输入上拉。
 */
void GPIO_Default_Init(void)
{
    P2_OE = 0;
    P2_PU = P22 | P26; // 需确认这些端口能接受上拉
    P3_OE = 0;
    P3_PU = P30 | P31 | P32 | P33 | P34 | P35 | P36 | P37; // 需确认这些端口能接受上拉
    P0_OE = 0;
    P0_PU = P00 | P01 | P02 | P03 | P04 | P05 | P06 | P07; // 需确认这些端口能接受上拉
    P1_OE = 0;
    P1_PU = P10 | P11 | P12 | P17; // 需确认这些端口能接受上拉
    P4_OE = 0;
    P4_PU = P40 | P41; // 使用步进电机时，P40，P41不能配置输入上拉，上拉会导致直通
}

/**
 * @brief      GPIO初始化配置,可将I/O口配置成输入或输出模式，上拉还是不上拉，模拟输出还是数字输出
 */ 
void GPIO_Init(void)
{
    // P1_OE = P15 ;
    // P3_OE = P36 | P37;
    // P0_OE = P07 | P04| P05;
    // P0_PU = P04 | P01| P05;
    // GP36 = 0;
    // GP37 = 0;
    // //LED灯IO口初始化
    // P4_OE = P42;
    // GP42  = 0;
    // //测试口
    // GP04 = 0;
    // GP11 = 1;

    P1_OE = P15;
    P3_OE = P36 | P37;
    P0_OE = P07;
    //P0_PU = P01;

    // LED灯IO口初始化
    P4_OE = P42;
    GP42 = 0;


    // TM1650 IO
    P0_OE = P00 | P01;
}
