

#ifndef SOURCE_MDS_RSIDENT_H_
#define SOURCE_MDS_RSIDENT_H_

#include "lcm32f037_lib.h"
#include "UserIncludes.h"

#if defined(EXPORT_MDS_RSIDENT_H)
  #define EXTERN
#else
  #define EXTERN extern
#endif
	
	


#define RSLPF_HZ 				(f32)(0.1)						//here in state function, TsB=2*pi*fb, qTsL=(1/fcur)/(TsB)=2*pi*fb/fcur
#define RS_PERIOD				(f32)(1.0)
#define RS_IDMAG				_IQ(0.05)
#define RS_IDMAG_INV		_IQ(1.0/0.05/2.0)	


typedef enum UGT_E_RI_ENUM_
{
	UGT_E_RI_STAGE1				= 0,
	UGT_E_RI_STAGE2				= 1,
	UGT_E_RI_CALC					= 2,
	UGT_E_RI_NONE					= 3,
} UGT_E_RI_ENUM;	

typedef struct UGT_S_RS_IDENT_STRU_
{  
	s32  s32RsEst;   			// Input: reference set-point
	s32  s32RsEstPre;   			// Input: feedback
	s32  s32IdMag;   			// Output: controller output 
	s32  s32IdLPF1;				  // Parameter: proportional loop gain
	s32  s32IdLPF2;			    // Parameter: integral gain
	s32  s32IqLPF1;			  // Parameter: upper saturation limit
	s32  s32IqLPF2;			  // Parameter: lower saturation limit
	s32  s32UdLPF1;				  // Data: proportional term
	s32  s32UdLPF2;			  	// Data: integral term
	s32  s32RsLPFGain;			  	// Data: pre-saturated controller output
	u32  u32Count;
	u32  u32CountMax;
	u32  u32CountMaxHalf;	
	u8  u16En;
	f32 f32RsEst;
	UGT_E_RI_ENUM eState;
} UGT_S_RS_IDENT_STRU;



EXTERN void MDS_vRsIdentInit(UGT_S_RS_IDENT_STRU *v);
EXTERN void MDS_vRsIdentExecute(UGT_S_RS_IDENT_STRU *v);


EXTERN UGT_S_RS_IDENT_STRU MDS_sRsIdent;
	
#undef EXTERN	
#endif
