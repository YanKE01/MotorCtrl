/**
 * @copyright (C) COPYRIGHT 2022 Fortiortech Shenzhen
 * @file      CMPInit.c
 * @author    Fortiortech  Appliction Team
 * @since     Create:2021-05-14
 * @date      Last modify:2022-07-14
 * @brief     This file contains driver initial function used for Motor Control.
 */ 
 
#include <FU68xx_2.h>
#include <Myproject.h>

/**
 * @brief      Driver初始化配置
 */
void Driver_Init(void)
{
    /* -----配置PWM周期值和死区时间----- */
    DRV_ARR             = PWM_VALUE_LOAD;                                           // 载波频率的周期值
    DRV_DTR             = PWM_LOAD_DEADTIME;                                        // 死区时间
    /*  -------------------------------------------------------------------------------------------------
        1、配置ME模块工作模式
        2、MESEL为0，ME模块工作在BLDC模式
        3、MESEL为1，ME模块工作在FOC/SVPWM/SPWM模式
        -------------------------------------------------------------------------------------------------*/
    SetBit(DRV_CR, MESEL);
    /* -----驱动有效电平和空闲电平----- */
    #if (PWM_Level_Mode == High_Level)
    {
        DRV_CMR &= 0x003f;
        DRV_OUT &= 0xC0;
    }
    #elif (PWM_Level_Mode == Low_Level)
    {
        DRV_CMR |= 0x0fc0;
        DRV_OUT = 0x3F;
    }
    #elif (PWM_Level_Mode == UP_H_DOWN_L)
    {
        DRV_CMR = 0x0540;
        DRV_OUT = 0x2A;
    }
    #elif (PWM_Level_Mode == UP_L_DOWN_H)
    {
        DRV_CMR &= 0x0a80;
        DRV_OUT = 0x15;
    }
    #endif //end PWM_Level_Mode
    /* -----清中断标志位，使能中断，配置比较值，设置中断优先级----- */
    ClrBit(DRV_SR, DCIF);                                                           // 清除DRV中断标志位
    /*  -------------------------------------------------------------------------------------------------
        1、配置DRV比较匹配中断模式
        2、当计数值等于DRV_COMR时，根据DCIM的设置判断是否产生中断标记
        3、00：不产生中断
        4、01：上升方向
        5、10：下降方向
        6、11：上下沿
        -------------------------------------------------------------------------------------------------*/
    SetReg(DRV_SR, DCIM0 | DCIM1, DCIM1);
    /* -----设置DRV计数器的比较匹配值，当DRV计数值与COMR相等时，根据DRV_SR寄存器的DCIM是否产生比较匹配事件----- */
    DRV_COMR = (PWM_VALUE_LOAD >> 1);
    /* -----中断优先级配置，优先级低于FO硬件过流----- */
    PDRV1 = 1;
    PDRV0 = 1;
    /* -----配置1个/2个载波周期执行一次FOC终端，0--1个，1-2个----- */
    SetBit(DRV_SR, DCIP);
    /* -----DRV计数器使能，0-禁止，1-使能----- */
    SetBit(DRV_CR, DRVEN);
    /* -----DRV计数器比较值预装载使能，0-禁止，1-使能----- */
    ClrBit(DRV_CR, DRPE);
    /* -----Driver 输出使能，0-禁止，1-使能----- */
    SetBit(DRV_CR, DRVOE);
}


