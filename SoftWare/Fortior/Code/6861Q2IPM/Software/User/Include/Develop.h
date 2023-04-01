/* --------------------------- (C) COPYRIGHT 2020 Fortiortech ShenZhen -----------------------------
    File Name      : Develop.h
    Author         : Fortiortech  Appliction Team
    Version        : V1.0
    Date           : 2020-09-30
    Description    : This file contains Advanced Applications parameter used for Motor Control.
----------------------------------------------------------------------------------------------------
                                       All Rights Reserved
------------------------------------------------------------------------------------------------- */

/* Define to prevent recursive inclusion -------------------------------------------------------- */
#ifndef __DEVELOP_H_
#define __DEVELOP_H_

/* -----Q format define----- */

#define _Q7(A)                          (int8) ((A) * (0x7f))
#define _Q8(A)                          (int16)((A) * (0xff))
#define _Q10(A)                         (int16)((A) * (0x3ff))                                      ///< Q15 format
#define _Q11(A)                         (int16)((A) * (0x7ff))                                      ///< Q12 format
#define _Q12(A)                         (int16)((A) * (0xfff))                                      ///< Q12 format
#define _Q13(A)                         (int16)((A) * (0x1fff))                                     ///< Q12 format
#define _Q14(A)                         (int16)((A) * (0x3fff))                                     ///< Q12 format
#define _Q15(A)                         (int16)((A) * (0x7fff))                                     ///< Q15 format                                           
#define _2PI                            (3.1415926 * 2)                                             ///< 2 PI value
#define _PI                             (3.1415926)                                                 ///< 2 PI value
#define _Q16                            (65535.0)                                                   ///< Q16 format value


#define I_ValueX(Curr_Value)            (Curr_Value * HW_RSHUNT * HW_AMPGAIN / (HW_ADC_REF / 2))
#define I_Value(Curr_Value)             _Q15((Curr_Value * HW_RSHUNT * HW_AMPGAIN) / HW_ADC_REF)

#define S_Value(SpeedValue)             _Q15((SpeedValue)/MOTOR_SPEED_BASE)

#define RV                              ((RV1 + RV2 + RV3) / RV3)                                  ///< 分压比
#define HW_BOARD_VOLT_MAX               (HW_ADC_REF * RV)                                          ///< (V)  ADC可测得的最大母线电压

/* -----时间设置值----- */
#define Calib_Time                      (1000)                                                     ///< 校正次数，固定1000次，单位:次
#define Charge_Time                     (300)                                                      ///< (ms) 预充电时间，单位：ms

/* -----CPU and PWM Parameter----- */
#define MCU_CLOCK                       (24.0)                                                     ///< (MHz) 主频

/* -----采样点设置----- */
#define FOCTRGDLY                       (0x1D)

/* -----single resistor sample Parameter----- */
#define DLL_TIME                        (0.0)                                                      ///< 双电阻最小脉宽设置(us),建议值为死区时间值+0.2us以上

/* -----three resistor overmodule Parameter----- */
#define OVERMOD_TIME                    (2.0)                                                      ///< 三电阻过调制时间(us)，建议值2.0

/* -----deadtime compensation----- */
#define DT_TIME                         (0.0)                                                      ///< 死区补偿时间(us)，适用于双电阻和三电阻，建议值是1/2死区时间

/* -----min pulse----- */
#define GLI_TIME                        (0.0)                                                      ///< 桥臂窄脉宽消除(us),建议值0.5

#define OverModulation                  (0)                                                        ///< 0-禁止过调制，1-使能过调制

/* -----Current Calib:enable or disable----- */                                                        
#define CalibENDIS                      (Enable)

/* -----SVPWM mode----- */
#define SVPWM_5_Segment                 (0)                                                        ///< 五段式SVPWM
#define SVPWM_7_Segment                 (1)                                                        ///< 七段式SVPWM
#define SVPMW_Mode                      (SVPWM_7_Segment)

/* -----double resistor sample mode----- */
#define DouRes_1_Cycle                  (0)                                                        ///< 周期采样完 ia, ib
#define DouRes_2_Cycle                  (1)                                                        ///< 交替采用ia, ib, 2周期采样完成
#define DouRes_Sample_Mode              (DouRes_1_Cycle)

/* -----模式选择设置值----- */
#define IPMtest                         (0)                                                        ///< IPM测试或者MOS测试，MCU输出固定占空比
#define NormalRun                       (1)                                                        ///< 正常按电机状态机运行

#define OUTLoop_Disable                 (0)                                                        ///< 关闭外环
#define OUTLoop_Enable                  (1)                                                        ///< 使能外环

/* -----调速模式----- */
#define NONEMODE                        (0)                                                        ///< 直接给定值，不调速


/* -----估算器模式选择----- */
#define SMO                             (0)                                                        ///< SMO ,滑膜估算
#define PLL                             (1)                                                        ///< PLL ,锁相环

/* -----估算器模式选择----- */
#define OBS_KSLIDE                      _Q15(0.85)                                                 ///< SMO算法里的滑膜增益值
#define ATT_COEF                        (0.85)                                                     ///< 无需改动

#define CW                              (0)
#define CCW                             (1)

#define High_Level                      (0)                                                        ///< 驱动高电平有效
#define Low_Level                       (1)                                                        ///< 驱动低电平有效
#define UP_H_DOWN_L                     (2)                                                        ///< 上桥臂高电平有效，下桥臂低电平有效
#define UP_L_DOWN_H                     (3)                                                        ///< 上桥臂低电平有效，下桥臂高电平有效

#define Hardware_FO_Protect             (1)                                                        ///< 硬件FO过流保护使能，适用于IPM有FO保护的场合
#define Hardware_CMP_Protect            (2)                                                        ///< 硬件CMP比较过流保护使能，适用于MOS管应用场合
#define Hardware_FO_CMP_Protect         (3)                                                        ///< 硬件CMP比较和FO过流保护都使能
#define Hardware_Protect_Disable        (4)                                                        ///< 硬件过流保护禁止，用于测试

#define Compare_DAC                     (0)                                                        ///< DAC设置硬件过流值
#define Compare_Hardware                (1)                                                        ///< 硬件设置硬件过流值


#endif

