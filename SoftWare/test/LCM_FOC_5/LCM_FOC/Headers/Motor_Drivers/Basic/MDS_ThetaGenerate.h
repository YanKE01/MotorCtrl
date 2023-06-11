/******************** (C) COPYRIGHT 2021 LINGXIN Microelectronics***************
* File Name          : MDS_ThetaGenerate.h
* Author             : LX Motor Lab  
* Date  						 : 2021-12-16
* Description        : Ramp and theta generation
*******************************************************************************/
#ifndef SOURCE_MDS_THETAGENERATE_H_
#define SOURCE_MDS_THETAGENERATE_H_

#include "lcm32f037_lib.h"
#include "UserIncludes.h"
//#include "UserParaSetDefine.h"


#if defined(EXPORT_MDS_THETAGENERATE_H)
  #define EXTERN
#else
  #define EXTERN extern
#endif

 
typedef struct MDS_sTHETA_STRU_
{ 
	s16  s16Freq; 		// Input: Ramp frequency (pu) 	
	s16  s16StepAngleMax;	// Parameter: Maximum step angle (pu)	Base_frequency= 200Hz, Base_frequency/PWM_Frequency, 200*65536/16000=820(IQ15),200*65536/8000=1640(IQ15)
	s32  s32Angle;		// Variable: Step angle (pu)	
	u16  u16AngleOut; //	
	s16  s16Gain;			// Input: Ramp gain (pu)
	s16  s16Out;  	 	// Output: Ramp signal (pu) 	
	s16  s16Offset;		// Input: Ramp offset (pu) 				 
 } MDS_sTHETA_STRU;	 
										
typedef struct MDS_sRAMPIQ24_STRU_
{ 
	s32 s32TargetValue; 		// Input: Target input (pu)
	s32 s32RampLowLimit;		// Parameter: Minimum limit (pu)				  
	s32 s32RampHighLimit;	// Parameter: Maximum limit (pu)
	s32 s32SetpointValue;	// Output: Target output (pu)				 
	u16 u16EqualFlag;		// Output: Flag output (Q0) - independently with global Q
	s32 s32Tmp;					// Variable: Temp variable
	s32 s32StepPosInc;
} MDS_sRAMPIQ24_STRU;	
         
#define MDS_IQ_ALIGNMENT_AMPL_IQ24	_IQ24(UPDS_IQ_ALIGNMENT_AMPL/UPDS_IB)
#define MDS_IQ_ALIGNMENT_AMPL_STEP	(s32)(MDS_IQ_ALIGNMENT_AMPL_IQ24/UPDS_IQ_ALIGNMENT_TIME/UPDS_CURR_FREQ)
#define MDS_IQ_ALIGNMENT_TIME_U32		(u32)(UPDS_IQ_ALIGNMENT_TIME*UPDS_CURR_FREQ)
#define MDS_IQ_ALIGNMENT_THETA_STEP	(u32)((f32)(0x4000)/UPDS_CURR_FREQ)
	
#define MDS_IQ_STARTUP_AMPL_IQ24		_IQ24(UPDS_IQ_STARTUP_AMPL/UPDS_IB)
#define MDS_SPD_STARTUP_FINA_IQ24		_IQ24(UPDS_SPD_STARTUP_FINA*UPDS_PAIRS/60/UPDS_FB)
#define MDS_SPD_STARTUP_FINA_STEP		(s32)(MDS_SPD_STARTUP_FINA_IQ24/UPDS_IQ_STARTUP_TIME/UPDS_CURR_FREQ)  	
#define MDS_SPD_FINA_TIME_COUNT			(u32)(UPDS_SPD_FINA_TIME*UPDS_CURR_FREQ) 

#define MDS_SPD_CLOSEDLOOP_INIT_IQ24	_IQ24(UPDS_SPD_CLOSEDLOOP_INIT*UPDS_PAIRS/60/UPDS_FB)
#define MDS_STARTUP_FAIL_SPEED_IQ24		_IQ24(UPDS_STARTUP_FAIL_SPEED*UPDS_PAIRS/60/UPDS_FB)
	

#define MDS_IQ_SWITCH_AMPL_STEP			(s32)(MDS_IQ_STARTUP_AMPL_IQ24/UPDS_IQ_SWITCH_TIME_MS/UPDS_CURR_FREQ*1000)
#define MDS_IQ_SWITCH_MIN_IQ24			_IQ24(UPDS_IQ_SWITCH_MIN/UPDS_IB)
#define MDS_THETSAERR_SWITCH_MIN    (u16)(UPDS_THETAERR_SWITCH_MIN/360.0*0xFFFF)	
#define MDS_THETSAERR_SWITCH_MAX    (u16)(UPDS_THETAERR_SWITCH_MAX/360.0*0xFFFF)	
#define MDS_THETSAERR_160DEG    		(u16)(160/360.0*0xFFFF)	

#define MDS_IQ_SWITCH_AMPL_MIN_IQ24 _IQ24(UPDS_IQ_SWITCH_MIN/UPDS_IB)

#define MDS_THETA_STEP							(u16)(UPDS_FB*0xFFFF/UPDS_CURR_FREQ)		

//with initional speed
#define MDS_STARTUP_SPD_LIMIT_MIN_IQ24    		_IQ24(UPDS_STARTUP_SPD_LIMIT_MIN*UPDS_PAIRS/60/UPDS_FB)
#define MDS_STARTUP_SPD_LIMIT_MID_IQ24    		_IQ24(UPDS_STARTUP_SPD_LIMIT_MID*UPDS_PAIRS/60/UPDS_FB)
#define MDS_STARTUP_SPD_LIMIT_NEG_MIN_IQ24    _IQ24(UPDS_SRATRUP_SPD_LIMIT_NEG_MIN*UPDS_PAIRS/60/UPDS_FB)
#define MDS_STARTUP_SPD_LIMIT_NEG_MID_IQ24    _IQ24(UPDS_SRATRUP_SPD_LIMIT_NEG_MID*UPDS_PAIRS/60/UPDS_FB)
	
EXTERN MDS_sTHETA_STRU 			TG_sThetaGen;
EXTERN MDS_sRAMPIQ24_STRU		TG_sCommandRef;

EXTERN void MDS_vThetaInit(MDS_sTHETA_STRU *w);
EXTERN void MDS_vRampInit(MDS_sRAMPIQ24_STRU *v, f32 f32Time, s32 _iq24max, s32 _iq24min);
EXTERN void MDS_vThetaGen(MDS_sTHETA_STRU *v);
EXTERN void MDS_vRampGen(MDS_sRAMPIQ24_STRU *v);

#undef EXTERN	
#endif
