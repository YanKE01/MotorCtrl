/**************************** (C) COPYRIGHT 2017 Fortiortech shenzhen *****************************
* File Name          : FOCTailDect.h
* Author             : Vina Peng, Fortiortech Appliction Team
* Version            : V1.0
* Date               : 2017-12-26
* Description        : This file contains all the common data types used for
*                      Motor Control.
***************************************************************************************************
* All Rights Reserved
**************************************************************************************************/
#ifndef __FOCTAILDETECT_H_
#define __FOCTAILDETECT_H_


/****************************FOC TaildWind参数变量**************************/

/*********************顺风检测启动初始化参数******************/
typedef struct
{
    uint16 TailWindSpeed;                                   // 顺逆风速度
    uint8  MotorDir;                                        // 电机方向
    uint8  AngleState;                                      // 角度状态
    uint8  MotorTailWindState;                              // 电机顺逆风状态
    uint8  SpeedStoreNum;                                   // 速度计算的次数
    uint16 SpeedCountTimer;                                 // 速度检测计时
    uint8  SpeedTimerClearStatus;                           // 速度检测计时的清零标志位
    uint32 TempThailWindSpeedBase;                          // 顺逆风速度基准
    uint8  SpeedOverFlowStatus;                             // 转速溢出标志
    uint8  ShakeTimes;                                      // 1和3状态来回抖动的次数
    uint8  PLLFlag;                                         // pll逆风的标志位;
    int16  PLLDetectCnt;                                    // PLL逆风刹车后静止速度计数
    int16  PLLTheta;                                        // PLL估算的角度
    int16  PLLSpeed;                                        // PLL估算的速度
    uint8  AntiFlag;                                        // 不同转速的反转标志
	uint8  ThetaStep;
}MotorTailWindTypeDef;


#define NormalTailWind                  (0)
#define BrakeTailWind                   (1)

#define CW                              (0)
#define CCW                             (1)

#define BaseTimerFre                    (1000)          //Hz
#define ThailWindSpeedBase              ((BaseTimerFre/2)*60/Pole_Pairs)//没必要除以2
//#define TailWindStartMinSpeed           (uint16)(1000.0/TailWind_Time*60.0/Pole_Pairs)      //顺风启动的最低转速



extern MotorTailWindTypeDef xdata  TailWindDetect;
extern void TailWindDetectInit(void);
extern void FOCTailWindTimeLimit(void);
//extern void TailWindSpeedDetect(void);
//extern void FOCCloseLoopStart(void);
extern void FOCTailWindDealwith(void);
extern void PLL_TailWindDealwith(void);
extern void SMO_TailWindDealwith(void);
#endif