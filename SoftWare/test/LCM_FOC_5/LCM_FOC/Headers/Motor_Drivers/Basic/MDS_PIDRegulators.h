/******************** (C) COPYRIGHT 2021 LINGXIN Microelectronics***************
* File Name          : MDS_PIDRegulators.h
* Author             : LX Motor Lab  
* Date  						 : 2021-12-16
* Description        : PID
*******************************************************************************/
 
#ifndef SOURCE_MDS_PIDREGULATORS_H_
#define SOURCE_MDS_PIDREGULATORS_H_


#include "lcm32f037_lib.h"
#include "UserParaSetDefine.h"


#if defined(EXPORT_MDS_PIDREGULATOR_H)
  #define EXTERN
#else
  #define EXTERN extern
#endif

EXTERN void MDS_vUdcPIRegulatorIQ24Init(UGT_S_PICONTROLLER_STRU *PI_Udc);
EXTERN void MDS_vCurPIRegulatorIQ24Init(UGT_S_PICONTROLLER_STRU *PI_Id, UGT_S_PICONTROLLER_STRU *PI_Iq);
EXTERN void MDS_vCurPIRegulatorIQ12Init(UGT_S_PICONTROLLERIQ12_STRU *PI_Id, UGT_S_PICONTROLLERIQ12_STRU *PI_Iq);
EXTERN void MDS_vSpdPIRegulatorIQ24Init(UGT_S_PICONTROLLER_STRU *PI_Speed);
EXTERN void MDS_vPIRegulatorIQ24(UGT_S_PICONTROLLER_STRU *PI_Struct);
EXTERN void MDS_vPIRegulatorIQ12(UGT_S_PICONTROLLERIQ12_STRU *PI_Struct);


#undef EXTERN
#endif 

