/* --------------------------- (C) COPYRIGHT 2020 Fortiortech ShenZhen -----------------------------
    File Name      : FU68xx_2_System.h
    Author         : Fortiortech  Appliction Team
    Version        : V1.0
    Date           : 2020-10-10
    Description    : This file contains all the common data types used for Motor Control.
----------------------------------------------------------------------------------------------------
                                       All Rights Reserved
------------------------------------------------------------------------------------------------- */

/* Define to prevent recursive inclusion -------------------------------------------------------- */
#ifndef __F_U68XX_2__SYSTEM_H_
#define __F_U68XX_2__SYSTEM_H_

#define LastSectorStartAddress          (0x3f80)

/* System Power Config---------------------------------------------------------------------------*/
#define VREF4_5			0
#define VREF5_0			1
#define VREF3_0         2
#define VREF4_0			3

/* -------------------------------------------------------------------------------------------------
    Function Name  : VREFConfig
    Description    : 参考电压VREF配置，如果使能VREF模块，则内部产生VREF输入到ADC作为ADC
                                    参考电压，如果禁止VREF模块，则由外部提供VREF输入到ADC作为ADC参考电压�?
    Date           : 2020-10-10
    Parameter      : Value--VCC低电压预警值[输入] 
                   0: VREF4_5, 参考电压VREF输出4.5V
                   1: VREF5_0, 参考电压VREF输出5.0V
                   2: VREF3_0, 参考电压VREF输出3.0V
                   3: VREF4_0, 参考电压VREF输出4.0V
                   Statue--使能控制，Disable或Enable[输入] 
------------------------------------------------------------------------------------------------- */
extern void VREFConfig(uint8 Value, bool Status);


/* -------------------------------------------------------------------------------------------------
    Function Name  : VHALFConfig
    Description    : 基准电压VHALF配置，使能VHALF工作模块，选择VREF/2作为基准
                                    电压VHALF输出，VHALF可用作运放基准电压。
    Date           : 2020-10-10
    Parameter      : Statue--使能控制，0-Disable或1-Enable[输入] 
------------------------------------------------------------------------------------------------- */
extern void VHALFConfig( bool Status);


/* WatchDog Config-------------------------------------------------------------------------------*/
/* -------------------------------------------------------------------------------------------------
    Function Name  : WatchDogConfig
    Description    : 看门狗定时函数初始化，看门狗使能和复位使能，定时配置
    Date           : 2020-10-10
    Parameter      : Value--定时时间，单位ms，最小定时时间8ms，最大定时1800ms[输入] 
                   Statue--使能控制，Disable或Enable[输入] 
------------------------------------------------------------------------------------------------- */
extern void WatchDogConfig(uint16 Value, bool Status);

/* -------------------------------------------------------------------------------------------------
    Function Name  : WatchDogRefresh
    Description    : 刷新看门狗计数器
    Date           : 2020-10-10
    Parameter      : None
------------------------------------------------------------------------------------------------- */
extern void WatchDogRefresh(void);

#endif
