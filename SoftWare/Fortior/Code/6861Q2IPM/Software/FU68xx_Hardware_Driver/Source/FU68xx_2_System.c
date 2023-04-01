/* --------------------------- (C) COPYRIGHT 2020 Fortiortech ShenZhen -----------------------------
    File Name      : FU68xx_2_System.c
    Author         : Fortiortech  Appliction Team
    Version        : V1.0
    Date           : 2020-09-30
    Description    : This file contains the system function used for Motor Control.
----------------------------------------------------------------------------------------------------  
                                       All Rights Reserved
------------------------------------------------------------------------------------------------- */
#include <FU68xx_2.h>
#include <FU68xx_2_System.h>
/* -------------------------------------------------------------------------------------------------
    Function Name  : VREFConfig
    Description    : 参考电压VREF配置，如果使能VREF模块，则内部产生VREF输入到ADC作为ADC
                                    参考电压，如果禁止VREF模块，则由外部提供VREF输入到ADC作为ADC参考电压。
    Date           : 2020-09-30
    Parameter      : Value--VCC低电压预警值[输入] 
                   0: VREF4_5, 参考电压VREF输出为4.5V
                   1: VREF5_0, 参考电压VREF输出为5.0V
                   2: VREF3_0, 参考电压VREF输出为3.0V
                   3: VREF4_0, 参考电压VREF输出为4.0V
                   Statue--使能控制，Disable或Enable[输入] 
------------------------------------------------------------------------------------------------- */
void VREFConfig(uint8 Value, bool Status)
{
    switch(Value)
    {
        case 0: ClrBit(VREF_VHALF_CR, VRVSEL0 | VRVSEL1);          break;
        case 1: SetReg(VREF_VHALF_CR, VRVSEL0 | VRVSEL1, VRVSEL0); break;
        case 2: SetReg(VREF_VHALF_CR, VRVSEL0 | VRVSEL1, VRVSEL1); break;
        case 3: SetBit(VREF_VHALF_CR, VRVSEL0 | VRVSEL1);          break;
    }

    SetReg(VREF_VHALF_CR, VREFEN, (Status ? VREFEN : 0x00));
}

/* -------------------------------------------------------------------------------------------------
    Function Name  : VHALFConfig
    Description    : 基准电压VHALF配置，使能VHALF工作模块，选择VREF/2作为基准
                                    电压VHALF输出，VHALF可用作运放基准电压。
    Date           : 2020-09-30
    Parameter      : Statue--使能控制，0-Disable或1-Enable[输入] 
------------------------------------------------------------------------------------------------- */
void VHALFConfig(bool Status)
{
    SetReg(VREF_VHALF_CR, VHALFEN, (Status ? VHALFEN : 0x00));
}

/* -------------------------------------------------------------------------------------------------
    Function Name  : WatchDogConfig
    Description    : 看门狗定时函数初始化，看门狗使能和复位使能，定时配置
    Date           : 2020-09-30
    Parameter      : Value--定时时间，单位ms，最小定时时间8ms，最大定时1800ms[输入] 
                   Statue--使能控制，Disable或Enable[输入] 
------------------------------------------------------------------------------------------------- */
void WatchDogConfig(uint16 Value, bool Status)
{
    SetReg(CCFG1, WDTEN, (Status ? WDTEN : 0x00));
    WDT_REL = ((uint16)(65532-(uint32)Value*32768/1000) >> 8);
    ClrBit(WDT_CR, WDTF);
    SetBit(WDT_CR, WDTRF);
}

/* -------------------------------------------------------------------------------------------------
    Function Name  : WatchDogRefresh
    Description    : 刷新看门狗计数器
    Date           : 2020-09-30
    Parameter      : None
------------------------------------------------------------------------------------------------- */
void WatchDogRefresh(void)
{
    SetBit(WDT_CR, WDTRF);
}
