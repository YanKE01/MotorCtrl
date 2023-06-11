/******************** (C) COPYRIGHT 2021 LINGXIN Microelectronics***************
* File Name          : MDS_CalcVoltage.h
* Author             : LX Motor Lab  
* Date  						 : 2021-12-16
* Description        : voltages transformation and calculation
*******************************************************************************/
#ifndef SOURCE_MDS_CALCVOLTAGE_H_
#define SOURCE_MDS_CALCVOLTAGE_H_

/* Includes ------------------------------------------------------------------*/
#include "lcm32f037_lib.h"
#include "UserParaSetDefine.h"


#if defined(EXPORT_MDS_CALCVOLTAGE_H)
  #define EXTERN
#else
  #define EXTERN extern
#endif

typedef struct MDS_S_CV_STRU_
{ 
	s16  s16DcBusVolt;		// Input: DC-bus voltage (pu)
	s16  s16MfuncV1;  		// Input: Modulation voltage phase A (pu)
	s16  s16MfuncV2;			// Input: Modulation voltage phase B (pu)	
	s16  s16MfuncV3;			// Input: Modulation voltage phase C (pu) 
	s16  s16VAs;			// Output: Phase voltage phase A (pu)
	s16  s16VBs;			// Output: Phase voltage phase B (pu) 
	s16  s16VCs;			// Output: Phase voltage phase C (pu) 
	s16  s16VAlpha;			// Output: Stationary d-axis phase voltage (pu)
	s16  s16VBeta;  			// Output: Stationary q-axis phase voltage (pu)
	s16  s16temp;				// Variable: temp variable
} MDS_S_CV_STRU;	                   

#define ONE_THIRD  (u16)(0.3333*0xFFFF) //IQ16
#define TWO_THIRD  (u16)(0.6666*0xFFFF)
#define INV_SQRT3  (u16)(0.5773*0xFFFF)
#define ONE_SIXTH  (u16)(0.1666*0xFFFF)



EXTERN void MDS_vVoltageCalc(UGT_S_VOLTABC_STRU *v);


#undef EXTERN
#endif // __VOLT_CAL_H__
