/**
 * @copyright (C) COPYRIGHT 2022 Fortiortech Shenzhen
 * @file      Customer.h
 * @author    Fortiortech  Appliction Team
 * @date      2022-07-13
 * @brief     This file contains protect parameter used for Motor Contro.
 */
 
/* Define to prevent recursive inclusion --------------------------------------------------------*/
#ifndef __PROTECT_H_
#define __PROTECT_H_
                           
/* -------------------------------------保护使能设置---------------------------------------------------- */
#define VoltageProtectEnable           (1)                                      ///< 电压保护，0,不使能；1，使能
#define StallProtectEnable             (0)                                      ///< 堵转保护，0,不使能；1，使能
#define PhaseLossProtectEnable         (1)                                      ///< 缺相保护，0,不使能；1，使能
#define GetCurrentOffsetEnable         (0)                                      ///< 偏置电压保护，0,不使能；1，使能
#define TemperatureProtectEnable	   (0)									    ///< 温度保护使能
#define OverSpeedProtectEnable		   (0)	                                    ///< 超速保护使能

/* -------------------------------------保护参数值---------------------------------------------------- */
/* -----硬件过流保护比较值来源----- */
#define Compare_Mode                   (Compare_DAC)                            ///< 硬件过流值的来源
#define OverHardcurrentValue           (80.0)                                   ///< (A) DAC模式下的硬件过流值 Imax = VHALF / HW_RSHUNT / HW_AMPGAIN    
//YK 2023年4月1日13:11:36 OverHardcurrentValue=40 给小了在高转速下容易报过流故障
/* -----软件过流保护----- */
#define OverSoftCurrentValue           I_Value(40.0)                            ///< (A) 软件过流值 
#define OverSoftCurrentTime            (10)                                     ///< 软件过流检测次数，初步设定值10
#define OverSoftCurrentClrTime         (1000)                                   ///<(ms) 每隔 OverSoftCurrentClrTime 检测次数清零，初步设定值1000

/* -----偏置电压保护----- */
 #define GetCurrentOffsetValue          _Q14(0.05)                              ///< (%) 偏置电压保护误差范围，超过该范围保护   

/* -----过欠压保护----- */
#define Over_Protect_Voltage           (55.5)                                   ///< (V) 直流电压过压保护值 
#define Over_Recover_Vlotage           (54.5)                                   ///< (V) 直流电压过压保护恢复值
#define Under_Protect_Voltage          (42.5)                                   ///< (V) 直流电压欠压保护值 
#define Under_Recover_Vlotage          (43.5)                                   ///< (V) 直流电压欠压保护恢复值 

/* -----堵转保护----- */
#define Stall_Protect_Time              (50)                                    ///< (ms) 堵转保护时间

#define Stall_Delay_DectTime            (500)                                   ///< (ms) 延时检测反电动势时间，结合Stall_DectEsValue1一起配置
#define Stall_DectEsValue1              (10)                                    ///< 反电动势判断值

#define Stall_DectSpeed                 (50000)                                 ///< (RPM) 堵转检测转速，结合Stall_DectEsValue2一起配置
#define Stall_DectEsValue2              (80)                                    ///< 反电动势判断值  

#define MOTOR_SPEED_STAL_MAX_RPM        (90000.0)                               ///< (RPM) 堵转保护最大转速
#define MOTOR_SPEED_STAL_MIN_RPM        (2000.0)                                ///< (RPM) 堵转保护最小转速

#define FOCMode_DectTime                (3000)                                  ///< (ms) 判断处在mode0的持续时间

/* -----缺相保护----- */
#define PhaseLossCurrentValue           I_Value(1.8)                            ///< (A) 缺相电流值 1.8
#define PhaseLossTimes                 (1.2)                                      ///< 缺相时电流倍数 3

/* -----NTC过温保护----- */
#define TemperatureProtectTime 			(100)									///< (ms) 温度保护检测时间
#define OVER_Temperature 		        Tempera_Value(1.0)						///< 过温保护阈值，根据NTC曲线设定，10K上拉电阻，80℃
#define UNDER_Temperature          		Tempera_Value(2.23)						///< 过温保护恢复阈值，根据NTC曲线设定，10K上拉电阻，70℃

/* -----堵入风口超速保护----- */ 
#define	 MOTOR_SPEED_OVER_RPM		    (110000)                                ///< (RPM) 超速保护速度
#define	 OVER_SpeedDetectTime			(3000)                                  ///< (ms) 超速保护检测时间

/* -----堵入风口限速功能----- */
#define  OverSpeedLimitEnable			(0)	                                    ///< 限速功能，0，不使能，1使能
#define  MOTOR_SPEED_LIMIT_RPM          (60000.0)                               ///< (RPM) 限速保护最大速度


/* -------------------------------------保护重启参数值---------------------------------------------------- */
/* -----过流恢复----- */
#define CurrentRecoverEnable             (1)                                    ///< 过流保护使能位, 0，不使能；1，使能
#define OverCurrentRecoverTime           (5)                                    ///< (ms) 重启次数,设定值<255 达到重启次数后不再重启，设定值>=255，一直重启
#define OverCurrentRecoverDelayTime      (1000)                                 ///< (ms) 重启延迟时间

/* -----过欠压恢复----- */
#define VoltageRecoverEn                  (1)                                   ///< 过欠压恢复使能：  0,不使能；1，使能
#define VoltageRecoverDelayTime           (200)                                 ///< (ms) 重启延迟时间

/* -----堵转恢复----- */
#define StallRecoverEn                    (1)                                   ///< 堵转保护恢复使能： 0,不使能；1，使能
#define StallRecoverTime                  (5)                                   ///< 重启次数,设定值<255 达到重启次数后不再重启，设定值>=255，一直重启
#define St_DisTime                        (500)                                 ///< (ms) < St_DisTime 为启动保护重启，≥ St_DisTime 为堵转保护重启，用于区分启动跟堵转保护，设定值<15000
#define StartRecoverDelayTime             (100)                                 ///< (ms) 启动重启延迟时间
#define StallRecoverDelayTime             (1000)                                ///< (ms) 堵转重启延迟时间

/* -----缺相恢复----- */
#define PhaseRecoverEn                    (1)                                   ///< 缺相恢复使能：     0,不使能；1，使能
#define PhaseRecoverTime                  (5)                                   ///< 重启次数,设定值<255 达到重启次数后不再重启，设定值>=255，一直重启
#define PhaseRecoverDelayTime             (1000)                                ///< (ms) 重启延迟时间

/* -----过温恢复----- */
#define TempRecoverEn                     (1)                                   ///< 过温恢复使能：     0,不使能；1，使能
#define TempRecoverTime                   (5)                                   ///< 重启次数,设定值<255 达到重启次数后不再重启，设定值>=255，一直重启
#define TempRecoverDelayTime              (1000)                                ///< (ms) 重启延迟时间



#endif
