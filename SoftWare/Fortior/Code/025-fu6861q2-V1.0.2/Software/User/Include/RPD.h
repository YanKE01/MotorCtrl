/**************************** (C) COPYRIGHT 2017 Fortiortech shenzhen *****************************
* File Name          : RPD.h
* Author             : Vina Peng, Fortiortech Appliction Team
* Version            : V1.0
* Date               : 10-Apr-2017
* Description        : This file contains all the common data types used for
*                      Motor Control.
***************************************************************************************************
* All Rights Reserved
**************************************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef __RPD_H_
#define __RPD_H_

typedef enum
{
    RPD_0				= 0,
    RPD_1				= 1,
    RPD_2               = 2,
    RPD_3		        = 3,
    RPD_4	            = 4,
    RPD_5				= 5,
    RPD_6			    = 6,
    RPD_7			    = 7,
}RPD_TypeDef;

typedef struct
{
//	uint16 insertFlag;
    uint16 DetectCount[8];  // RPD检测时间
    uint16 InsetCount[8];   // RPD检测处理
    uint8  injectmin;       // 检测注入的最小值
    uint8  injectmid;       // 检测注入的中间值
    uint16 ThetaGet;        // RPD的角度获取
    uint8  injecttimes;     // RPD注入次数
    int16  U_Offset;        // U相基准偏差
    int16  V_Offset;        // V相基准偏差
    int16  W_Offset;        // W相基准偏差


} RPD_Param_TypeDef;
extern RPD_TypeDef RPD_Status;
extern RPD_Param_TypeDef RPDPara;

extern void RPD (void);
extern void Time2_RPD_Init(void);


#endif