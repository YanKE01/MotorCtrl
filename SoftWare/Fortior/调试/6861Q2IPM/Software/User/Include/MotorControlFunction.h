/* --------------------------- (C) COPYRIGHT 2020 Fortiortech ShenZhen -----------------------------
    File Name      : MotorControlFunction.h
    Author         : Fortiortech  Appliction Team
    Version        : V1.0
    Date           : 2020-09-30
    Description    : This file contains motor contorl parameter used for Motor Control.
----------------------------------------------------------------------------------------------------
                                       All Rights Reserved
------------------------------------------------------------------------------------------------- */

/* Define to prevent recursive inclusion -------------------------------------------------------- */
#ifndef __MOTOR_CONTROL_FUNCTION_H_
#define __MOTOR_CONTROL_FUNCTION_H_

typedef struct
{                                                                    // Iw或Ibus的偏置电压总和
  int16   ibusOffset;                                                                              // Ibus的偏置电压
  int32   ibusOffsetSum;                                                                           // Ibus的偏置电压总和
  int16   offsetCount;                                                                             // 偏置电压采集计数
  int8    offsetFlag;                                                                              // 偏置电压结束标志位
}CurrentOffset;
typedef struct 
{
    unsigned char  wAdcVref;
    unsigned char  wPwmDeadTime;                                                                   // 死区时间
	unsigned char  wMinWindTime;                                                                   // 采样窗口时间
	unsigned char  wFocTrgdly;                                                                     // 采样点延迟时间
    unsigned char  wPwmLevelMode;                                                                  // 预驱有效电平
    unsigned char  wShuntResistorMode;                                                             // 采样电阻模式
    unsigned char  wIPMState;                                                                      // IPM模式
    unsigned char  wFr;                                                                            // 电机转向

    unsigned char  wEstimateAlgorithm;                                                             // 估算器模式
    unsigned char  wTailWindMode;                                                                  // 顺逆风模式
    unsigned short wTailWindTime;                                                                  // 顺逆风检测时间
    unsigned short wTailWindSpeedKlpf;                                                             // 顺逆风期间检测转速滤波系数
    unsigned short wTailWindOBSWindKp;
    unsigned short wTailWindOBSWindKi;
    unsigned short wTailWindOBSWindCCWKp;
    unsigned short wTailWindOBSWindCCWKi;

    unsigned short wAlignFirstAngle;                                                               // 第一次预定位角度
	unsigned short wAlignSecondAngle;                                                              // 第二次预定位角度
	unsigned short wAlignCurr;                                                                     // 预定位电流
	unsigned short wAlignTime;                                                                     // 预定位时间
	unsigned short wAlignDQKP;                                                                     // 预定位电流环Kp
    unsigned short wAlignDQKI;                                                                     // 预定位电流环Ki

    unsigned short wStartCurr;                                                                     // 启动Q轴电流
	unsigned short wStartDQKP;                                                                     // 启动DQ轴电流KP
    unsigned short wStartDQKI;                                                                     // 启动DQ轴电流KI

    unsigned char  wOmegaAcc;
    unsigned short wOmegaMin;
    unsigned short wOmegaEnd;

    unsigned short wOBSKp1;
    unsigned short wOBSKi1;
    unsigned short wOBSKp2;
    unsigned short wOBSKi2;
    unsigned short wOBSKp3;
    unsigned short wOBSKi3;
    unsigned short wOBSKp4;
    unsigned short wOBSKi4;
    unsigned short wOBSKp5;
    unsigned short wOBSKi5;
    unsigned short wOBSKp6;
    unsigned short wOBSKi6;
    unsigned short wOBSKp7;
    unsigned short wOBSKi7;

	unsigned short wOBSPLLKp1;
    unsigned short wOBSPLLKi1;
    unsigned short wOBSPLLKp2;
    unsigned short wOBSPLLKi2;
    unsigned short wOBSPLLKp3;
    unsigned short wOBSPLLKi3;
    unsigned short wOBSPLLKp4;
    unsigned short wOBSPLLKi4;
    unsigned short wOBSPLLKp5;
    unsigned short wOBSPLLKi5;
    unsigned short wOBSPLLKp6;
    unsigned short wOBSPLLKi6;
    unsigned short wOBSPLLKp7;
    unsigned short wOBSPLLKi7;    
    
    unsigned char  wOutLoopMode;
    short          wIqref;
    unsigned char  wIqrefInc;
    unsigned char  wIqrefDec;    
    short          wOutLoopTargetValue;
    
    unsigned short wMotorCurrentLoopPI2MinSpeed;
    unsigned short wMotorCurrentLoopPI3MinSpeed;
    unsigned short wRunDQKP1;
    unsigned short wRunDQKI1;
    unsigned short wRunDQKP2;
    unsigned short wRunDQKI2;
    unsigned short wRunDQKP3;
    unsigned short wRunDQKI3;    
    short wDoutMax;
    short wDoutMin;
    short wQoutMax;
    short wQoutMin;
    
    unsigned short wMotorSpeedLoopPI2MinSpeed;
    unsigned short wMotorSpeedLoopPI3MinSpeed;
    unsigned short wOutLoopRunKP1;
    unsigned short wOutLoopRunKI1;
    unsigned short wOutLoopRunKP2;
    unsigned short wOutLoopRunKI2;
    unsigned short wOutLoopRunKP3;
    unsigned short wOutLoopRunKI3;
    unsigned short wSoutmaxRun;
    unsigned short wSoutminRun;

    unsigned char  wCurOffsetProtectEnable;
    unsigned char  wCurrentProtectRecoverEnable;
    unsigned char  wDACOverHardcurrentValue;
    unsigned short wDACOverSoftcurrentValue;
    
    unsigned char  wVoltageProtectEnable;
    unsigned char  wVoltageProtectRecoverEnable;
    unsigned short wOverVoltageProtectValue;
    unsigned short wUnderVoltageProtectValue;
    unsigned short wOverVoltageRecoverValue;
    unsigned short wUnderVoltageRecoverValue;

    unsigned char  wOverPowerProtectEnable;
    unsigned char  wOverPowerProtectRecoverEnable;
    unsigned char  wPowerLimitEnable;
    unsigned short wMotorPowerLimitValue;
    unsigned char  wPowerLimitRecoverTime;
    
    unsigned char  wStartProtectEnable;
    unsigned char  wStartProtectRecoverEnable;
    unsigned short wStartProtect1EsValue;
    unsigned short wStartProtect2EsValue;

    unsigned char  wStallProtectEnable;
    unsigned char  wStallProtectRecoverEnable;
    unsigned short wStallProtect1EsValue;
    unsigned short wStallProtect2SpeedValue;
    unsigned short wStallProtect2EsValue;
    unsigned short wStallProtect3MinSpeedValue;
    unsigned short wStallProtect3MaxSpeedValue;
    unsigned short wStallProtect4CurrentValue;

    unsigned char  wPhaseLossProtectEnable;
    unsigned char  wPhaseLossProtectRecoverEnable;
    unsigned short wPhaseLossCurrentValue1;
    unsigned short wPhaseLossCurrentValue2;
    
    unsigned char  wSpeedLimitEnable;
    short          wSpeedLimitValue;

    unsigned short wMotorMinShieldSpeedValue1;                                                     // 电机最小屏蔽转速1
    unsigned short wMotorMaxShieldSpeedValue1;                                                     // 电机最大屏蔽转速1
    unsigned short wMotorMinShieldSpeedValue2;                                                     // 电机最小屏蔽转速2
    unsigned short wMotorMaxShieldSpeedValue2;                                                     // 电机最大屏蔽转速2

    unsigned char  wOverPowerSpeedRampDec;

    unsigned short wOBSKslide;
    unsigned short wSpeedKlpf;
    unsigned short wOBSFbase;
    unsigned short wOBSKlpf;
    unsigned short wOBSKs; 
    
    short wOBSK1;
    short wOBSK2;
    short wOBSK2SMO;    
    short wOBSK2Actual;	
    short wOBSK3;
    short wOBSK4;
    
    unsigned char  wSpeedMode;
	unsigned short wMotorMaxSpeed;                                                                 // 最大转速
	unsigned short wMotorMinSpeed;                                                                 // 最小转速
    
    unsigned char  wPwmOnFre;                                                                      // 开机频率
	unsigned char  wPwmOffLowFre;                                                                  // 关机最小频率
	unsigned short wPwmOffHightFre;                                                                // 关机最大频率
    
    unsigned short wMotorLoopSpeed;                                                                // 速度环起作用转速
    unsigned short wMotorStartMinSpeedValue;                                                       // 最小速度环目标转速
	unsigned short wMotorReturnOilSpeed;                                                           // 回油转速
    unsigned short wMotorReturnOilTime;                                                            // 回油时间

    unsigned short wSpeedLoopStartKP;
	unsigned short wSpeedLoopStartKI;
    unsigned short wSoutmaxStart;
    unsigned short wSoutminStart;    
    unsigned char  wSpeedRampStartInc;

    unsigned char  wSpeedRampInc;
	unsigned char  wSpeedRampDec;

	unsigned char  wFiledWeakenCompEnable;
}STypeProPara;

typedef struct
{
	uint16  start_CNT;
}StartTimeCnt;

extern CurrentOffset xdata mcCurOffset;
extern FaultVarible  idata mcFaultDect;
extern StartTimeCnt Time;	

extern void GetCurrentOffset(void);
extern void Motor_Ready (void);
extern void Motor_Init (void);
extern void FOC_Init(void);
extern void Motor_Charge(void);
extern void Motor_Open(void);
extern void Motor_Align(void);
extern void MotorcontrolInit(void);
extern void VariablesPreInit(void);

#endif

