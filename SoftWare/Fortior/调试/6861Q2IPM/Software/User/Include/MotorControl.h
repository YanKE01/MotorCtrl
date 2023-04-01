/* --------------------------- (C) COPYRIGHT 2020 Fortiortech ShenZhen -----------------------------
    File Name      : MotorControl.h
    Author         : Fortiortech  Appliction Team
    Version        : V1.0
    Date           : 2020-09-30
    Description    : This file contains motor contorl parameter used for Motor Control.
----------------------------------------------------------------------------------------------------
                                       All Rights Reserved
------------------------------------------------------------------------------------------------- */

/* Define to prevent recursive inclusion -------------------------------------------------------- */
#ifndef __MOTOR_CONTROL_H_
#define __MOTOR_CONTROL_H_

/* Exported types -------------------------------------------------------------------------------*/

typedef enum
{
    mcReady     = 0,
    mcInit      = 1,
    mcCharge    = 2,
    mcTailWind  = 3,
    mcPosiCheck = 4,
    mcAlign     = 5,
    mcStart     = 6,
    mcRun       = 7,
    mcStop      = 8,
    mcFault     = 9,
    mcPllTect   = 10,
    mcBrake     = 11
}MotStaType;

typedef union
{
    uint8 setMode;                      // 整个配置模式使能位
    struct
    {
        uint8 calibFlag        :1;      // 电流校准的标志位
        uint8 chargeSetFlag    :1;      // 预充电配置标志位
        uint8 alignSetFlag     :1;      // 预定位配置标志位
        uint8 startSetFlag     :1;      // 启动配置标志位
    } setFlag;
}MotStaM;




/* Exported variables ---------------------------------------------------------------------------*/
extern MotStaType mcState;
extern MotStaM mcStaSet;
/* Exported functions ---------------------------------------------------------------------------*/
extern void MC_Control(void);

#endif

