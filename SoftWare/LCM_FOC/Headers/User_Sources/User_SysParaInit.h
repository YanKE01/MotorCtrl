#ifndef SOURCE_USER_SYSPARAINIT_H_
#define SOURCE_USER_SYSPARAINIT_H_

#include "lcm32f037_lib.h"
#include "UserIncludes.h"

#if defined(EXPORT_USER_SYSPARAINIT_H_)
  #define EXTERN
#else
  #define EXTERN extern
#endif
EXTERN void US_vUserAppInit(void);	
EXTERN void US_vSystParaInitPowerup(void);
EXTERN void US_vSystParaInit(void);	
EXTERN void US_vSystStateInit(UGT_S_SYSTEMSTATE_STRU *v);	
EXTERN void US_vGlobalVariablesInit(void);
EXTERN void MDS_vMotorParaCalc(UGT_S_MOTORPARAMETERS_STRU *v);
EXTERN void MDS_vOtherInitFromUserSetting(UGT_S_MOTORPARAMETERS_STRU *v);
EXTERN void MDS_vIPDInit(UGT_S_IPD_STRU *v);
EXTERN void MDS_vMotorParaReadFromFlash(UGT_S_MOTORPARAMETERS_STRU *v, u16 *w);
EXTERN void MDS_vMotorParaReadFromHfile(UGT_S_MOTORPARAMETERS_STRU *v);	
EXTERN void MDS_vTIMInit(void);
EXTERN void MDS_vCurLimitInit(UGT_S_CURRENT_LIMIT_STRU *v);
	
#undef EXTERN
#endif
	