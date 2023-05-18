/******************** (C) COPYRIGHT 2021 LINGXIN Microelectronics***************
* File Name          : MC_Globals.h
* Author             : LX Motor Lab  
* Date  						 : 2021-12-16
* Description        : Global variables define
*******************************************************************************/

#ifndef __MC_GLOBALS_H
#define __MC_GLOBALS_H


#include "lcm32f037_lib.h"
#include "UserGlobalsType.h"

#ifdef EXPORT_MDS_GLOBALS
#define EXTERN
#else
#define EXTERN extern
#endif


#ifdef EXPORT_MDS_GLOBALS

	EXTERN UGT_S_CURRENTALL_STRU 					UG_sCurrentAll;              /*Stator currents Ia,Ib,Ic*/ 
	EXTERN UGT_S_VOLTAGEALL_STRU 					UG_sVoltageAll;              /*Stator currents Ia,Ib,Ic*/ 
	EXTERN UGT_S_SYSTEMSTATE_STRU 				UG_sSysStateErr;
	EXTERN UGT_S_SYSTEMCONTROLLERs_STRU 	UG_sSystemControllers;
	EXTERN UGT_S_ADSAMPLEALL_STRU					UG_sADSampleAll;
	EXTERN UGT_S_POSITIONSPEED_STRU				UG_sPositionAll;
	EXTERN UGT_S_IPD_STRU                 UG_sIPDAll;
	EXTERN UGT_S_USARTDATA_STRU						UG_sUsartData;


#else

	EXTERN UGT_S_CURRENTALL_STRU 					UG_sCurrentAll;              /*Stator currents Ia,Ib,Ic*/ 
	EXTERN UGT_S_VOLTAGEALL_STRU 					UG_sVoltageAll;              /*Stator currents Ia,Ib,Ic*/ 
	EXTERN UGT_S_SYSTEMSTATE_STRU 				UG_sSysStateErr;
	EXTERN UGT_S_SYSTEMCONTROLLERs_STRU 	UG_sSystemControllers;
	EXTERN UGT_S_ADSAMPLEALL_STRU					UG_sADSampleAll;
	EXTERN UGT_S_POSITIONSPEED_STRU				UG_sPositionAll;
	EXTERN UGT_S_IPD_STRU                 UG_sIPDAll;
	EXTERN UGT_S_USARTDATA_STRU						UG_sUsartData;


#endif


#undef EXTERN
#endif /* __MC_GLOBALS_H */


