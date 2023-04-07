/* --------------------------- (C) COPYRIGHT 2020 Fortiortech ShenZhen -----------------------------
    File Name      : MotorProtect.h
    Author         : Fortiortech  Appliction Team
    Version        : V1.0
    Date           : 2020-08-07
    Description    : This file contains all the common data parameter used for Motor Control.
----------------------------------------------------------------------------------------------------
                                       All Rights Reserved
------------------------------------------------------------------------------------------------- */

/* Define to prevent recursive inclusion --------------------------------------------------------*/
#ifndef __MOTORPROTECH_H_
#define __MOTORPROTECH_

typedef enum
{
    FaultNoSource = 0,         // 无故障
    FaultHardOVCurrent = 1,    // 硬件过流
    FaultSoftOVCurrent = 2,    // 软件过流
    FaultUnderVoltage = 3,     // 欠压保护
    FaultOverVoltage = 4,      // 过压保护
    FaultLossPhase = 5,        // 缺相保护
    FaultStall = 6,            // 堵转保护
    FaultStart = 7,            // 启动保护
    FaultOverwind = 8,         // 顺逆风失败保护
    FaultOverHeat = 9,         // 电机过热保护
    FaultOverTemperature = 10, // NTC过温保护
    FaultOverSpeed = 11,       // 堵转超速保护
    FaultLVW = 12,             // LVW
    FaultGetOffset = 13,       // 偏置电压保护
} FaultStateType;

/* Exported types -------------------------------------------------------------------------------*/
typedef struct
{
    // Current protect
    uint8 OverCurCnt; // 软件过流计数
    uint16 OverCurCntClr;
    uint16 Abs_ia; // IA的绝对值
    uint16 Abs_ib; // IB的绝对值
    uint16 Abs_ic; // IC的绝对值

    uint16 Max_ia; // IA的最大值
    uint16 Max_ib; // IB的最大值
    uint16 Max_ic; // IC的最大值

} CurrentVarible;
typedef struct
{
    uint8 StartFlag;           // 启动保护的标志位，用于判断哪个方法起作用
    uint8 StallTimes;          // 堵转保护次数
    uint8 StallFlag;           // 堵转保护的标志位，用于判断哪个方法起作用
    uint8 LossPHTimes;         // 缺相保护次数
    uint8 CurrentProtectTimes; // 过流保护次数
    uint8 TempProtectTimes;    // 过温保护次数
} ProtectVarible;
typedef struct
{
    // voltage protect
    uint16 OverVoltDetecCnt;  // 过压检测计数
    uint16 UnderVoltDetecCnt; // 欠压检测计数
    uint16 VoltRecoverCnt;    // 过压恢复计数

    // OVER Current protect recover
    uint16 CurrentRecoverCnt; // 过流保护恢复计数

    // stall protect
    uint16 StallDelayCnt;    // 堵转延迟判断计时
    uint16 StallDectEs;      // method 1，与ES相关
    uint16 StallDectESSpeed; // method 1，与ES和速度相关
    uint16 StallDectSpeed;   // method 2，与速度相关
    uint16 StallDectFocmode; // method 3，与FOC启动mode有关

    uint16 StallReCount; // 堵转保护恢复计数
    uint16 StallReTime;  // 堵转恢复时间，用于区分启动跟堵转

    // Loss Phase protect

    uint16 Lphasecnt;        // 缺相保护计时
    uint16 AOpencnt;         // A缺相计数
    uint16 BOpencnt;         // B缺相计数
    uint16 COpencnt;         // C缺相计数
    uint16 mcLossPHRecCount; // 缺相恢复计数
                             // start protect

    // OverHeat
    int16 OverHeatCnt;        // 过热保护计数
    int16 OverHeatRecoverCnt; // 过热保护恢复计数

    // NTC 过温保护
    uint16 TemperCnt;
    uint16 TemperRecover;

    // 堵转超速
    uint16 OverSpeedCnt;
    uint16 OverSpeedCntRecover;

    uint16 TempDACValue;
    uint16 TempTSminValue;

} FaultVarible;

extern FaultVarible xdata mcFaultDect;
extern CurrentVarible xdata mcCurVarible;
extern ProtectVarible xdata mcProtectTime;

/* Exported functions ---------------------------------------------------------------------------*/
extern void Fault_OverUnderVoltage(void);
extern void Fault_Overcurrent(void);
extern void Fault_Stall(void);
extern void Fault_phaseloss(void);
extern void Fault_Temperature(void);
extern void Fault_OverSpeed(void);
extern void Fault_GetCurrentOffset(void);
#endif
