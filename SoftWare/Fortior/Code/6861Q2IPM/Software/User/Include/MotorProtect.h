/* --------------------------- (C) COPYRIGHT 2020 Fortiortech ShenZhen -----------------------------
    File Name      : MotorProtect.h
    Author         : Fortiortech  Appliction Team
    Version        : V1.0
    Date           : 2020-09-16
    Description    : This file contains XX-XX-XX parameter used for Motor Control.
----------------------------------------------------------------------------------------------------
                                       All Rights Reserved
------------------------------------------------------------------------------------------------- */

/* Define to prevent recursive inclusion -------------------------------------------------------- */
#ifndef __MOTOR_PROTECT_H_
#define __MOTOR_PROTECT_H_

extern void Fault_OverUnderVoltage(FaultVarible *h_Fault);
extern void Fault_Power(FaultVarible *h_Fault);
extern  void Fault_Overcurrent(CurrentVarible *h_Cur);
extern void Fault_OverCurrentRecover(FaultVarible *h_Fault);
extern void Fault_OverPowerRecover(FaultVarible *h_Fault);
extern void Fault_Stall(FaultVarible *h_Fault,CurrentVarible *h_Cur);
extern void Fault_phaseloss(FaultVarible *h_Fault);
extern void VariablesPreInit(void);
extern void Fault_Detection(void);
extern void FaultProcess(void);

#endif

