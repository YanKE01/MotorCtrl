/* =================================================================================
File name:        RMP_CNTL.H  
===================================================================================*/
#ifndef SOURCE_MDS_FLUXWEAKENING_H_
#define SOURCE_MDS_FLUXWEAKENING_H_

#include "lcm32f037_lib.h"
#include "UserIncludes.h"


#if defined(EXPORT_MDS_FLUXWEAKENING_H)
  #define EXTERN
#else
  #define EXTERN extern
#endif

	
typedef struct MDS_S_FW_STRU_
{ 
	s32 s32Vmax;
	s32 s32VFbk;
	s32 s32IMaxSquare;
	UGT_S_PICONTROLLER_STRU PI_FW;
	u32 u32Count;
} MDS_S_FW_STRU;	 

typedef struct MDS_S_CP_STRU_
{ 
	s32 s32PowerMax;
	s32 s32PowerFbk;
	UGT_S_PICONTROLLER_STRU PI_CP;
} MDS_S_CP_STRU;	
	
typedef struct MDS_S_NW_STRU_
{ 
	s32 s32IqUseLPF;
	s32 s32IqUseABS;
	s32 s32SpeedUse;
	s32 s32SpeedUseSquare;
	s32 s32SpdDivIqGain;
	u16 u16RunTask;	
} MDS_S_NW_STRU;	

typedef struct MDS_S_MTPA_STRU_
{ 
	s32 s32Out;
	s32 s32OutMax;
	s32 s32OutMin;	
	s32 s32IdRef;
	s32 s32Gain;
	u16 u16En;
} MDS_S_MTPA_STRU;

EXTERN MDS_S_FW_STRU MDS_sFW;
EXTERN MDS_S_CP_STRU MDS_sCP;
EXTERN MDS_S_NW_STRU MDS_sNW;
EXTERN MDS_S_MTPA_STRU MDS_sMTPA;

EXTERN void MDS_vFluxWeakeningInit(MDS_S_FW_STRU *v);
EXTERN void MDS_vFluxWeakening(MDS_S_FW_STRU *v, s32 Ud, s32 Uq);
EXTERN void MDS_vConstantPowerInit(MDS_S_CP_STRU *v);
EXTERN void MDS_vConstantPower(MDS_S_CP_STRU *v, s32 Id, s16 Udc);
EXTERN void MDS_vConstantPowerDQ(MDS_S_CP_STRU *v, s32 Ud, s32 Id, s32 Uq, s32 Iq);
EXTERN void MDS_vNoWaterCalInit(MDS_S_NW_STRU *v);
EXTERN void MDS_vNoWaterCal(MDS_S_NW_STRU *v,s32 Iq, s32 Speed);
EXTERN void MDS_vMTPAInit(MDS_S_MTPA_STRU *v);
EXTERN void MDS_vMTPA(MDS_S_MTPA_STRU *v,s32 Iq);

#undef EXTERN	
#endif
