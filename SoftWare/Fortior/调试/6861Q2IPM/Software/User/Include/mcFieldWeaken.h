/* --------------------------- (C) COPYRIGHT 2021 Fortiortech ShenZhen -----------------------------
    File Name      : MotorFiledWeaken.h
    Author         : Fortiortech  Appliction Team
    Version        : V1.0
    Date           : 2021-12-08
    Description    : This file contains motor filed weaken parameter used for Motor Control.
----------------------------------------------------------------------------------------------------
                                       All Rights Reserved
------------------------------------------------------------------------------------------------- */

/* Define to prevent recursive inclusion -------------------------------------------------------- */
#ifndef __MOTOR_FILED_WEAKEN_H_
#define __MOTOR_FILED_WEAKEN_H_

typedef struct
{
    int16   WeakenRunUq;
    int16   WeakenRunUd;
    uint16  WeakenUsRef;
    uint16  WeakenUsFed;
    int16   ThetaOutmin;
    int16   ThetaOutmax;
    int16   WeakenTheta;
}FieldWeakeningTypeDef;

extern void FiledWeakenInit(void);
extern void FileWeakenControl(void);

#endif

