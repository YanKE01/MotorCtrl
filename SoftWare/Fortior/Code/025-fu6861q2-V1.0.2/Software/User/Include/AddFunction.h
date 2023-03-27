/**************************** (C) COPYRIGHT 2017 Fortiortech shenzhen *****************************
 * File Name          : AddFunction.h
 * Author             : Vina Peng, Fortiortech Appliction Team
 * Version            : V1.0
 * Date               : 10-Apr-2017
 * Description        : This file contains all the common data types used for
 *                      Motor Control.
 ***************************************************************************************************
 * All Rights Reserved
 **************************************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef __AddFuntion_H_
#define __AddFuntion_H_

typedef struct
{
    uint16 ADCDcbus; // 母线电压
    uint16 ADCVref;  // ADC参考
} ADCSample;
typedef struct
{
    uint16 ON_Count;    // 运行时间计数
    uint16 OFF_Count;   // 停止时间计数
    uint32 ONOFF_Times; // 启停次数
    uint8 ONOFF_Flag;   // 启停测试中启动标志位
} ONVarible;
typedef struct
{
    uint16 LedCount;  // 闪灯周期计数
    uint8 LedTimCot;  // 闪灯次数计数
    uint16 Counttime; // 闪灯周期
    uint16 Count;     // 电平翻转计数
} MCLedDisplay;
typedef struct
{
    uint16 mcDcbusFlt;   // 母线电压
    uint16 CtrlMode;     // 控制模式
    uint16 CurrentPower; // 当前功率
    uint16 PowerCal;
    uint16 mcADCCurrentbus;
    int16 Powerlpf;         // 功率滤波后的值
    int16 mcIqref;          // Q轴给定电流
    uint16 mcPosCheckAngle; // 位置检测的角度
    int16 SpeedFlt;         // 当前速度滤波后的值
    int32 SQUSysSpeed;      // 速度的平方和
    int16 SpeedFlag;
    uint16 EsValue;        // 当前FOC_ESQU滤波后的值
    uint16 SQUSpeedDIVEs;  // 速度平方和除以ESQU的值
    uint16 Smo_EK2;        // EK2的调试值
    uint16 RunStateCnt;    // 运行状态计数
    uint16 TorqueLoopTime; // 转矩环时间
    uint16 State_Count;    // 电机各个状态的时间计数
    uint8 Brake_Count;
    uint8 Brake_Flag;

    uint16 mcADCTemperature;

    int16 AngleCompensation; // 角度补偿
    uint16 TempUDQValue;

    uint8 RSDDIVFlag; // RSD除法执行标志位
    uint8 WindFlag;

} FOCCTRL;

typedef struct
{
    uint32 SleepDelayCout;
    int32 SleepFlag;
    uint8 SleepEn;
} SLEEPMODE;

typedef struct
{
    int16 TargetValue;
    int16 ActualValue;

    int16 DelayCount;
    int16 DelayPeriod;
    int8 FlagONOFF;
    int16 Value_UD;
    int16 Value_UQ;

    uint8 MotorOnFilter;
    uint8 MotorOffFilter;

} MCRAMP;
typedef union
{
    uint32 PWMCompareAMP; // 比较值标幺化的值
    uint16 PWMCompareUpdate[2];
} PWMD;
typedef struct
{
    uint16 PWMCompare;       // 比较值
    uint16 PWMARR;           // 周期值
    uint16 PWMCompareOld;    // 上一次的比较值
    uint16 PWMCompareUpdate; // 使用共同体，将比较值乘以32768
    uint16 PWMARROld;        // 上一次的周期值
    uint16 PWMFlag;          // PWM标志位，置1期间不更新duty
    uint16 PWMARRUpdate;     // 计算中的周期值
    uint32 PWMDuty;          // PWM占空比，Q15格式
    int16 PWMUpdateFlag;     // PWM新的duty更新
    uint32 PWMVSum;          // PWM的总和
    uint16 PWMcnt;           // PWM求平均技术
    uint8 PWMDivFlag;        // PWM的除法标志位
    uint8 PWMfilterL;        // 低电平滤波次数
    uint8 PWMfilterH;        // 高电平滤波次数

} PWMINPUTCAL;

typedef struct
{
    uint8 FR;     // 当前给定的转子方向
    uint8 FlagFR; // 反向的标志位
    uint8 FRStatus;
    uint8 TargetFR; // 设置的目标方向
    uint16 OldTargetSpeed;
} MotorFRTypeDef;

// 标志位定义
typedef struct
{
    uint8 g_1msTick : 1; // 1ms中断标志位

} Flag_VARIABLE;

/* Exported variables ---------------------------------------------------------------------------*/
extern PWMINPUTCAL idata mcPwmInput;

extern Flag_VARIABLE xdata VariableFlag;
extern ONVarible xdata ONOFFTest;
extern FaultStateType xdata mcFaultSource;
extern ADCSample xdata AdcSampleValue;
extern FOCCTRL xdata mcFocCtrl;
extern MCLedDisplay xdata mcLedDisplay;
extern MCRAMP xdata mcSpeedRamp;
extern int16 xdata VSP;
extern MotorFRTypeDef xdata mcFRState;
extern SLEEPMODE xdata SleepSet;
extern int16 Motor_Loop_Speed1;

extern uint32 TempPower;

///* Exported functions ---------------------------------------------------------------------------*/
// extern void Fault_OverUnderVoltage(FaultVarible *h_Fault);
// extern  void Fault_Overcurrent(CurrentVarible *h_Cur);
// extern void Fault_OverCurrentRecover(FaultVarible *h_Fault);
// extern void Fault_Stall(FaultVarible *h_Fault);
// extern void Fault_phaseloss(FaultVarible *h_Fault);
// extern void Fault_Temperature(FaultVarible *h_Fault);
// extern void Fault_OverSpeed(FaultVarible *h_Fault);

extern void VariablesPreInit(void);
extern void Fault_Detection(void);
extern int16 KLPF_VALUE(int16 INVlaue, int16 OutLastValue);
extern void Led_OnOff(uint8 htime);
extern void Speed_response(void);
extern void mc_ramp();
extern void VSPSample(void);
extern void HW_Speed_PI(void);
extern int16 HW_Genal_PI(int16 Xn1, int16 Yn0, int16 Xn2);
extern int16 HW_One_PI(int16 Xn1);
extern int16 SoftLPF(int16 Xn1, int16 Xn0, int16 K);
extern void Sleepmode(void);
extern void LED_Display(void);
extern void FaultProcess(void);
extern void SpeedRegulation(void);
extern int16 LPFFunction(int16 Xn1, int16 Xn0, int8 K);
extern uint32 Abs_F32(int32 value);
extern uint16 Abs_F16(int16 value);
extern void StarRampDealwith(void);
extern void ONOFF_Starttest();
extern void MULDIV_test(void);
extern void APP_DIV(void);
extern void CurrentLoop(void);

extern void TailWindSpeedDetect(void);

extern void PWMInputCapture(void);
extern void RDOutput(void);

extern void Weak_Control(void);
extern void TickCycle_1ms(void);

#endif