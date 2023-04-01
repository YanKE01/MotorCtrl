/* --------------------------- (C) COPYRIGHT 2020 Fortiortech ShenZhen -----------------------------
    File Name      : Customer.h
    Author         : Fortiortech  Appliction Team
    Version        : V1.0
    Date           : 2020-09-30
    Description    : This file contains all the common data types used for Motor Control.
----------------------------------------------------------------------------------------------------
                                       All Rights Reserved
------------------------------------------------------------------------------------------------- */

/* Define to prevent recursive inclusion -------------------------------------------------------- */
#ifndef __CUSTOMER_H_
#define __CUSTOMER_H_

/*****************基础参数*****************************************
1.芯片参数
2.电机参数
3.硬件参数
******************************************************************/
/*----------------------------------------------------------------------------------------------------------------------------
                                                1、芯片参数
-----------------------------------------------------
----------------------------------------------------------------------- */
/* -----载波频率设置----- */
#define PWM_FREQUENCY                  (16.0)                                                       ///< (kHz) 载波频率

/* -----死区时间设置----- */
#define PWM_DEADTIME                   (1.0)                                                       ///< (us) 死区时间

/* -----单电阻最小采样窗口设置----- */
#define MIN_WIND_TIME                  (PWM_DEADTIME +3.0)                                        ///< (us) 单电阻最小采样窗口，建议值死区时间+0.9us

/* -----正反转设置----- */
#define IRMODE                         (CW)                                                        ///< 正反转模式，正转为0，反转为1
/* ----------------------------------------------------------------------------------------------------------------------------
                                               2、电机参数
---------------------------------------------------------------------------------------------------------------------------- */
/* -----电机参数值----- */
#define     Pole_Pairs                 (3)                                            ///< 极对数
#define     RS                         (0.177)                                        ///< 电阻, ohm
#define     LD                         (0.000224)                                     ///< 电感, H
#define     LQ                         (0.000224)                                     ///< 电感, H
#define     KeVpp                      (12.8)                                         ///< (V)   反电势电压-峰峰值 */
#define     KeF                        (131.6)                                        ///< (Hz)  反电势测试时频率  */
#define     Ke                         (Pole_Pairs * KeVpp * 1000 / KeF / 207.84)     ///< 反电势系数  */
#define     Psi                        (float)(KeVpp / 2.0 / 1.732 / _2PI / KeF)

/* -----速度基准设置----- */
#define MOTOR_SPEED_BASE               (7000.0)                                                    ///< (RPM) 速度基准

/* ----------------------------------------------------------------------------------------------------------------------------
                                               3、硬件参数
---------------------------------------------------------------------------------------------------------------------------- */

/* -----硬件板子参数设置值，根据驱动芯片的类型选择，大部分芯片为High_Level----- */
#define PWM_Level_Mode                 (UP_H_DOWN_L)

/* -----电流基准的电路参数----- */
#define HW_RSHUNT                      (0.005)  //                                                 ///< (Ω)  采样电阻
#define HW_ADC_REF                     (4.5)                                                       ///< (V)  ADC参考电压
#define HW_AMPGAIN                     (10.0)                                                      ///< 运放放大倍数

/* -----母线电压采样分压电路参数----- */
#define RV1                            (20.0)                                                     ///< (kΩ) 母线电压分压电阻1
#define RV2                            (0.0)                                                      ///< (kΩ) 母线电压分压电阻2
#define RV3                            (1.0)                                                      ///< (kΩ) 母线电压分压电阻3
#define VC1                            (1.0)                                                      ///< 电压补偿系数 0.9

/*****************调试相关参数*****************************************
1.预定位相关参数配置区域
2.启动相关参数配置区域
3.运行相关参数配置区域
4.调速模式&IPM测试模式&估算器模式配置区域
5.附加功能配置区域

******************************************************************/


/* ----------------------------------------------------------------------------------------------------------------------------
                                           1. 预定位相关参数配置区域
---------------------------------------------------------------------------------------------------------------------------- */
/* -----预定位测试模式，用于验证电机输出正常，或者测试预定位力矩是否足够----- */
#define AlignTestMode                  (0)                                                         ///< 预定位测试模式

/* -----预定位时间设置值----- */
#define Align_Time                     (2500)                                                      ///< (ms) 预定位时间，单位：ms

/* -----预定位角度----- */
#define Align_First_Angle              (90.0)                                                      ///< (°) 预定位角度  45
#define Align_Second_Angle             (30.0)                                                      ///< (°) 预定位角度  0

/* -----预定位的Kp、Ki----- */
#define DQKP_Alignment                 _Q12(2.5)                                                   ///< 预定位的KP
#define DQKI_Alignment                 _Q15(0.3)                                                   ///< 预定位的KI

/* -----预定位电流----- */
#define ID_Align_CURRENT               I_Value(0.0)                                                ///< (A) D轴定位电流
#define IQ_Align_CURRENT               I_Value(5.0)                                                ///< (A) Q轴定位电流

/* ----------------------------------------------------------------------------------------------------------------------------
                                           2.启动相关参数配置区域
---------------------------------------------------------------------------------------------------------------------------- */

/*------------------------------------------------------
低速观测器开关在LowSpeedObserver.h
1.需要修改启动KPKI实现第一时间相电流峰值达到设定值
2.修改预定位时间和KPKI预定位波形平稳
3.确定RS、IS、母线电压等参数正确
4.修改启动电流可以提升启动能力
---------------------------------------------------------*/


/* -----启动电流----- */
#define ID_Start_CURRENT               I_Value(0.0)                                                ///< (A) D轴启动电流
#define IQ_Start_CURRENT               I_Value(2.0)                                               ///< (A) Q轴启动电流

/* -----运行电流----- */
#define ID_RUN_CURRENT                 I_Value(2.0)                                                ///< (A) D轴运行电流
#define IQ_RUN_CURRENT                 IQ_Start_CURRENT                                            ///< (A) Q轴运行电流

/* -----启动的ATO参数设置----- */
#define ATO_BW1                        (100.0)                                                     ///< 观测器带宽的滤波值，经典值为1.0-200.0 //220
#define ATO_BW2                        (250.0)
#define ATO_BW3                        (280.0)
#define ATO_BW4                        (100.0)
#define ATO_BW5                        (180.0)//280

/* -----启动的E_BW参数设置----- */
#define E_BW1                          (130)                                                       ///< PLL算法里的反电动势滤波值
#define E_BW2                          (140)
#define E_BW3                          (160)
#define E_BW4                          (180)
#define E_BW5                          (180)

/* -----速度带宽的滤波值----- */
#define SPD_BW                         (15.0)                                                      ///< 速度带宽的滤波值，经典值为5.0-40.0

/* -----SMO运行最小转速----- */
#define MOTOR_SPEED_SMOMIN_RPM         (10.0)                                                     ///< (RPM) SMO运行最小转速

/* -----OMEGA启动参数----- */
#define Motor_Omega_Ramp_ACC           (25.0)                                                      ///< omega启动的增量     50  //25
#define MOTOR_OMEGA_ACC_MIN            (55.0)                                                      ///< (RPM) omega启动的最小切换转速0  150
#define MOTOR_OMEGA_ACC_END            (50.0)                                                      ///< (RPM) omega启动的限制转速  300

/* -----开环切闭环转速----- */
#define MOTOR_LOOP_RPM                 (1400.0)                                                     ///< (RPM) 由mode 0到mode1切换转速，即闭环切换转速

/* -----启动电流环参数设置值----- */
#define DQKPStart                      _Q12(1.5)                                                   ///< 启动DQ轴KP //2.0
#define DQKIStart                      _Q15(0.4)                                                   ///< 启动DQ轴KI //0.01

/* -----启动速度环参数设置值----- */
#define MTPASKP                       _Q12(2.0)                                                    ///< 启动外环KP  2.0
#define MTPASKI                       _Q12(0.01)                                                   ///< 启动外环KI

/* -----启动速度环输出限幅值设置值----- */
#define MTPASOutMax_Start              (13.0)                                                  ///< (A) 外环最大限幅值  8
#define MTPASOutMin_Start              (0.0)                                                   ///< (A) 外环最小限幅值

#define MTPASOUTMAX_RUN                (22.0)
#define MTPASOUTMIN_RUN                (-22.0)                                                     ///< (A) 外环最小限幅值

/* -----启动速度环参数设置值----- */
#define SKP                            _Q12(0.5)                                                        ///< 启动外环KP  //1.0
#define SKI                            _Q12(0.01)                                                       ///< 启动外环KI

/* -----启动速度环输出限幅值设置值----- */
#define SOutMax_Start                  I_Value(20.0)                                               ///< (A) 外环最大限幅值  //32.5
#define SOutMin_Start                  I_Value(0.0)
/* -----电机运行时转速时速度环输出限幅值----- */
#define SOUTMAX_RUN                    I_Value(22.0)                                               ///< 32.5
#define SOUTMIN_RUN                    I_Value(0.0)                                                ///< (A) 外环最小限幅值


/* -----启动速度环最小目标值----- */
#define MOTOR_START_MIN_SPEED_VALUE    (1800.0)

/* -----启动速度爬坡增量----- */
#define SpeedRampStartInc              (10.0)                                                     ///< 启动速度环增量 150
#define SpeedRampStartDec              (10.0)                                                     ///< 启动速度环减量 

/* ----------------------------------------------------------------------------------------------------------------------------
                                           3.运行相关参数配置区域
---------------------------------------------------------------------------------------------------------------------------- */
/* -----外环使能----- */
/* -----(OUTLoop_Disable)----- */                                                                  ///< 关闭外环
/* -----(OUTLoop_Enable)----- */                                                                   ///< 使能外环
#define OUTLoop_Mode                   (OUTLoop_Enable)

/* -----电机运行时电流环Kp、Ki分段转速----- */
#define MOTOR_CURRENT_LOOP_PI2_MIN_SPEED (2000.0)
#define MOTOR_CURRENT_LOOP_PI3_MIN_SPEED (4000.0)

/* -----电机运行时转速小于MOTOR_CURRENT_LOOP_PI2_MIN_SPEED时电流环Kp、Ki----- */
#define DQKPRun1                       _Q12(0.5)                                                   ///< DQ轴KP  //1.0
#define DQKIRun1                       _Q15(0.01)                                                   ///< DQ轴KI  //0.01

/* -----电机运行时转速大于MOTOR_CURRENT_LOOP_PI2_MIN_SPEED且小于MOTOR_CURRENT_LOOP_PI3_MIN_SPEED时电流环Kp、Ki----- */
#define DQKPRun2                       _Q12(0.5)                                                   ///< DQ轴KP  //1.0
#define DQKIRun2                       _Q15(0.01)                                                   ///< DQ轴KI  //0.01

/* -----电机运行时转速大于MOTOR_CURRENT_LOOP_PI3_MIN_SPEED时电流环Kp、Ki----- *///2000*200=40 0 000
#define DQKPRun3                       _Q12(1.0)                                                   ///< DQ轴KP  //1.0
#define DQKIRun3                       _Q15(0.01)                                                   ///< DQ轴KI

/* -----D轴参数设置----- */
#define DOUTMAX                        _Q15(0.75)                                                   ///< D轴最大限幅值，单位：输出占空比
#define DOUTMIN                        _Q15(-0.75)                                                  ///< D轴最小限幅值，单位：输出占空比

/* -----Q轴参数设置，默认0.99即可----- */
#define QOUTMAX                        _Q15(0.99)                                                  ///< Q轴最大限幅值，单位：输出占空比
#define QOUTMIN                        _Q15(-0.50)                                                 ///< Q轴最小限幅值，单位：输出占空比

#define QOUTINC                        (5)                                                         ///< Q轴电流增大步进值,开环控制时有效 //
#define QOUTDEC                        (5)                                                         ///< Q轴电流增大步进值,开环控制时有效 //

#define QOUTCURRENT                    (1.0)                                                       ///< (A) Q轴输出电流,开环控制时有效
#define QOUTVALUE                      I_Value(QOUTCURRENT)

/* -----外环参数设置值----- */
#define SPEED_LOOP_TIME                (2)                                                         ///< (ms) 速度环调节周期 风扇速度环50，功率环5
#define SPEEDRAMPTIME                  (4.0)                                               ///< (ms) 速度环增量时间，13ms增/减一次

/* -----电机运行时速度环Kp、Ki分段转速----- */
#define MOTOR_SPEED_LOOP_PI2_MIN_SPEED (2000.0)
#define MOTOR_SPEED_LOOP_PI3_MIN_SPEED (4000.0)



/* -----电机运行时加减速的转速爬坡增量----- */
#define SpeedRampInc                   (120.0)                                                     ///< 运行速度环增量 60RPM/S //120
#define SpeedRampDec                   (120.0)                                                     ///< 运行速度环减量 60RPM/S

/* -----电机运行时最大最小转速----- */
#define MOTOR_SPEED_MIN_RPM            (2000.0)                                                    ///< (RPM) 运行最小转速 //
#define MOTOR_SPEED_MAX_RPM            (3500.0)                                                    ///< (RPM) 运行最大转速

#define MOTOR_SPEED_STOP_RPM           (1800.0)                                                    ///< (RPM) 停机转速

/* ----------------------------------------------------------------------------------------------------------------------------
                                         4.调速模式&IPM测试模式&估算器模式配置区域
---------------------------------------------------------------------------------------------------------------------------- */
/* -----调速模式----- */                                                                        ///< PWM调速
/* -----(NONEMODE)----- */                                                                         ///< 直接给定值，不调速
#define SPEED_MODE                     (NONEMODE)

/* -----IPM测试模式----- */
/* -----(IPMtest)----- */                                                                          ///< IPM测试或者MOS测试，MCU输出固定占空比
/* -----(NormalRun)----- */                                                                        ///< 正常按电机状态机运行
#define IPMState                       (IPMtest)

/* -----估算器模式选择----- */
/* -----(SMO)----- */                                                                              ///< SMO ,滑膜估算
/* -----(PLL)----- */                                                                              ///< PLL ,锁相环
#define EstimateAlgorithm              (SMO)

/* -----压缩机回油参数----- */
#define MotorReturnOilT                   (20)                                                         ///< (ms)压缩机上油时间ms
#define MotorStartSpeed                   (2000.0)                                                     ///< (rpm)压缩机上油转速
/* ----------------------------------------------------------------------------------------------------------------------------
                                          5.附加功能配置区域
---------------------------------------------------------------------------------------------------------------------------- */



//低速观测器开关需要在LowSpeedObserver.h开启
//电流解耦控制使能在DCurrentDecoupledControl.h开启
//电磁转矩最大化MTPA在MTPA.h开启
//DQCurrentKpKiCalEnable在DQCurrentKpKiCal.h开启

/* -----睡眠模式选择----- */
#define Sleep_Enable                   (0)

/*弱磁开关*/
#define MotorFiledWeakenEn             (1)
#define MotorFiledWeakenUs             _Q15(0.92)                               ///< 弱磁能到的最大饱和电压(弱磁转速上不去的时候可以调小该值)
#define MotorFiledWeakenKp             _Q12(0.5)                                ///< 弱磁控制的Kp
#define MotorFiledWeakenKi             _Q15(0.005)                              ///< 弱磁控制的Ki

/*转矩补偿开关*/
#define IQCOMPENSATEENBLE               (1)                                                         ///<转矩补偿使能标志位 
#define OBS_K3T_SPEED_END               _Q15(1200.0   / MOTOR_SPEED_BASE) //1200
#define OBS_K3T_SPEED_START             _Q15(700.0   / MOTOR_SPEED_BASE)  //700
#define IQCOMPENSATEENBLETESTENBLE     (0)                                                         ///<转矩补偿测试标志位，用于实时发送数据到串口上


//// 硬件DBG的参数首地址
#define HARD_SPIDATA                   FOC__THETA

extern uint16 xdata spidebug[4];



#endif
