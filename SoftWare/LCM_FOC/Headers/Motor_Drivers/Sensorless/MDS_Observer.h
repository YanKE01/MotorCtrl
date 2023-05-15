/******************** (C) COPYRIGHT 2021 LINGXIN Microelectronics***************
* File Name          : MDS_Observer.h
* Author             : LX Motor Lab  
* Date  						 : 2021-12-16
* Description        : Adaptive position observer
*******************************************************************************/

#ifndef SOURCE_MDS_OBSERVER_H_
#define SOURCE_MDS_OBSERVER_H_

#include "lcm32f037_lib.h"
#include "UserIncludes.h"
#include "math.h"

#if defined(EXPORT_MDS_OBSERVER_H)
  #define EXTERN
#else
  #define EXTERN extern
#endif
		

//定义各常数的标幺值（Iq24型值)
#define OB_TS_S							(UPDS_PWM_TS_S)
#define OB_THETAB						(UPDS_PI)
#define OB_TS_S2						(UPDS_PWM_TS_S2)
#define OB_SHORT_SHIFT			(14)
#define OB_SHORT_BASE				(s16)(16384)
	
#define OB_IQTS 						_IQ(UPDS_WB / UPDS_OBSERVER_FREQ)						//here in state function, TsB=2*pi*fb, qTsL=(1/fcur)/(TsB)=2*pi*fb/fcur
#define OB_IQTSPLL 					_IQ(UPDS_WB / UPDS_OBSERVER_FREQ / OB_THETAB)						  					//here in motion function, thetaB=2*pi, TsB = thetaB/(wb)=1/(fb); qTs=(1/fcur)/(TsB)=fb/fcur
#define OB_IQLD 						_IQ(UPDS_LD_REAL / UPDS_LB)														//Ld = 0.0086/0.0026757 = 3.1197(0.0086/Lb*0x01000000) (0x0000D3E1)
#define OB_IQLQ 						_IQ(UPDS_LQ_REAL / UPDS_LB)														//Lq = 0.0105/0.00266 = 3.809(0.0105/Lb*0x01000000)	 (0x03F26E98)	
#define OB_IQRS 						_IQ(UPDS_RS_REAL / UPDS_RB)							 							//Rs = 1.27/3.349 = 0.3666((1.27/Rb)*0x01000000)(0x00611340)		
#define OB_IQTS_DIV_LQ			_IQ(UPDS_TP/UPDS_LQP)
#define OB_IQTS_R_DIV_LQ		_IQ(UPDS_TP*UPDS_RSP/UPDS_LQP)
#define OB_IQTS_LD_DIV_LQ		_IQ(UPDS_TP*UPDS_LDP/UPDS_LQP)
#define OB_IQTS_PSI_DIV_LQ	_IQ(UPDS_TP*UPDS_PSIP/UPDS_LQP)
#define OB_IQTS_DIV_LD			_IQ(UPDS_TP/UPDS_LDP)
#define OB_IQTS_R_DIV_LD		_IQ(UPDS_TP*UPDS_RSP/UPDS_LDP)
#define OB_IQTS_LQ_DIV_LD		_IQ(UPDS_TP*UPDS_LQP/UPDS_LDP)		
#define OB_IQ20GAIN_Q				_IQ20(UPDS_OBS_GAIN_Q*UPDS_LQP/UPDS_TP/UPDS_PSIP)
#define OB_IQ20GAIN_D				_IQ20(UPDS_OBS_GAIN_D*UPDS_LDP/UPDS_TP/UPDS_PSIP)	
#define OB_COMP_TIME				_IQ(1.5 * UPDS_WB / UPDS_OBSERVER_FREQ / OB_THETAB)	


#define OB_IQTS2 							_IQ(UPDS_WB / UPDS_OBSERVER_FREQ2)						//here in state function, TsB=2*pi*fb, qTsL=(1/fcur)/(TsB)=2*pi*fb/fcur
#define OB_IQTSPLL2 					_IQ(UPDS_WB / UPDS_OBSERVER_FREQ2 / OB_THETAB)						  					//here in motion function, thetaB=2*pi, TsB = thetaB/(wb)=1/(fb); qTs=(1/fcur)/(TsB)=fb/fcur
#define OB_IQTS_DIV_LQ2				_IQ(UPDS_TP2/UPDS_LQP)
#define OB_IQTS_R_DIV_LQ2			_IQ(UPDS_TP2*UPDS_RSP/UPDS_LQP)
#define OB_IQTS_LD_DIV_LQ2		_IQ(UPDS_TP2*UPDS_LDP/UPDS_LQP)
#define OB_IQTS_PSI_DIV_LQ2		_IQ(UPDS_TP2*UPDS_PSIP/UPDS_LQP)
#define OB_IQTS_DIV_LD2				_IQ(UPDS_TP2/UPDS_LDP)
#define OB_IQTS_R_DIV_LD2			_IQ(UPDS_TP2*UPDS_RSP/UPDS_LDP)
#define OB_IQTS_LQ_DIV_LD2		_IQ(UPDS_TP2*UPDS_LQP/UPDS_LDP)				
#define OB_IQ20GAIN_Q2				_IQ20(UPDS_OBS_GAIN_Q*UPDS_LQP/UPDS_TP2/UPDS_PSIP)
#define OB_IQ20GAIN_D2				_IQ20(UPDS_OBS_GAIN_D*UPDS_LDP/UPDS_TP2/UPDS_PSIP)	
#define OB_COMP_TIME2					_IQ(1.5 * UPDS_WB / UPDS_OBSERVER_FREQ2 / OB_THETAB)	



#define OB_IQTS_SHORT 						(s16)(UPDS_WB / UPDS_OBSERVER_FREQ * OB_SHORT_BASE)						//here in state function, TsB=2*pi*fb, qTsL=(1/fcur)/(TsB)=2*pi*fb/fcur
#define OB_IQTSPLL_SHORT 					(s16)(UPDS_WB / UPDS_OBSERVER_FREQ / OB_THETAB *OB_SHORT_BASE)						  					//here in motion function, thetaB=2*pi, TsB = thetaB/(wb)=1/(fb); qTs=(1/fcur)/(TsB)=fb/fcur
#define OB_IQLD_SHORT 						(s16)(UPDS_LD_REAL / UPDS_LB *OB_SHORT_BASE)														//Ld = 0.0086/0.0026757 = 3.1197(0.0086/Lb*0x01000000) (0x0000D3E1)
#define OB_IQLQ_SHORT 						(s16)(UPDS_LQ_REAL / UPDS_LB *OB_SHORT_BASE)														//Lq = 0.0105/0.00266 = 3.809(0.0105/Lb*0x01000000)	 (0x03F26E98)	
#define OB_IQRS_SHORT 						(s16)(UPDS_RS_REAL / UPDS_RB *OB_SHORT_BASE)							 							//Rs = 1.27/3.349 = 0.3666((1.27/Rb)*0x01000000)(0x00611340)		
#define OB_IQTS_DIV_LQ_SHORT			(s16)(UPDS_TP/UPDS_LQP *OB_SHORT_BASE)
#define OB_IQTS_R_DIV_LQ_SHORT		(s16)(UPDS_TP*UPDS_RSP/UPDS_LQP *OB_SHORT_BASE)
#define OB_IQTS_LD_DIV_LQ_SHORT		(s16)(UPDS_TP*UPDS_LDP/UPDS_LQP *OB_SHORT_BASE)
#define OB_IQTS_PSI_DIV_LQ_SHORT	(s16)(UPDS_TP*UPDS_PSIP/UPDS_LQP *OB_SHORT_BASE)
#define OB_IQTS_DIV_LD_SHORT			(s16)(UPDS_TP/UPDS_LDP *OB_SHORT_BASE)
#define OB_IQTS_R_DIV_LD_SHORT		(s16)(UPDS_TP*UPDS_RSP/UPDS_LDP*OB_SHORT_BASE)
#define OB_IQTS_LQ_DIV_LD_SHORT		(s16)(UPDS_TP*UPDS_LQP/UPDS_LDP*OB_SHORT_BASE)			
#define OB_IQGAIN_Q_SHORT					(s16)(UPDS_OBS_GAIN_Q*UPDS_LQP/UPDS_TP/UPDS_PSIP*4096)
#define OB_IQGAIN_D_SHORT					(s16)(UPDS_OBS_GAIN_D*UPDS_LDP/UPDS_TP/UPDS_PSIP*1024)	
#define OB_COMP_TIME_SHORT				(s16)(1.5 * UPDS_WB / UPDS_OBSERVER_FREQ / OB_THETAB*OB_SHORT_BASE)	

#define OB_IQTS2_SHORT 							(s16)(UPDS_WB / UPDS_OBSERVER_FREQ2 *OB_SHORT_BASE)						//here in state function, TsB=2*pi*fb, qTsL=(1/fcur)/(TsB)=2*pi*fb/fcur
#define OB_IQTSPLL2_SHORT 					(s16)(UPDS_WB / UPDS_OBSERVER_FREQ2 / OB_THETAB *OB_SHORT_BASE)						  					//here in motion function, thetaB=2*pi, TsB = thetaB/(wb)=1/(fb); qTs=(1/fcur)/(TsB)=fb/fcur
#define OB_IQTS_DIV_LQ2_SHORT				(s16)(UPDS_TP2/UPDS_LQP *OB_SHORT_BASE)
#define OB_IQTS_R_DIV_LQ2_SHORT			(s16)(UPDS_TP2*UPDS_RSP/UPDS_LQP *OB_SHORT_BASE)
#define OB_IQTS_LD_DIV_LQ2_SHORT		(s16)(UPDS_TP2*UPDS_LDP/UPDS_LQP *OB_SHORT_BASE)
#define OB_IQTS_PSI_DIV_LQ2_SHORT		(s16)(UPDS_TP2*UPDS_PSIP/UPDS_LQP *OB_SHORT_BASE)
#define OB_IQTS_DIV_LD2_SHORT				(s16)(UPDS_TP2/UPDS_LDP *OB_SHORT_BASE)
#define OB_IQTS_R_DIV_LD2_SHORT			(s16)(UPDS_TP2*UPDS_RSP/UPDS_LDP *OB_SHORT_BASE)
#define OB_IQTS_LQ_DIV_LD2_SHORT		(s16)(UPDS_TP2*UPDS_LQP/UPDS_LDP *OB_SHORT_BASE)				
#define OB_IQGAIN_Q2_SHORT					(s16)(UPDS_OBS_GAIN_Q*UPDS_LQP/UPDS_TP2/UPDS_PSIP *4096)
#define OB_IQGAIN_D2_SHORT					(s16)(UPDS_OBS_GAIN_D*UPDS_LDP/UPDS_TP2/UPDS_PSIP *1024)	
#define OB_COMP_TIME2_SHORT					(s16)(1.5 * UPDS_WB / UPDS_OBSERVER_FREQ2 / OB_THETAB *OB_SHORT_BASE)	

#define OB_TEST 		(UPDS_OBS_GAIN_D*UPDS_LDP/UPDS_TP/UPDS_PSIP)
#define OB_TEST1 		(UPDS_OBS_GAIN_Q*UPDS_LQP/UPDS_TP/UPDS_PSIP)
#define SIGN_FUN(x)				(s32)(x>0?1:-1)

typedef struct UGT_S_PLL_STRU_
{  
	s32  s32Ref;   			// Input: reference set-point
	s32  s32Fbk;   			// Input: feedback
	s32  s32Out;   			// Output: controller output 
	s32  s32Kp;				  // Parameter: proportional loop gain
	s32  s32Ki;			    // Parameter: integral gain
	s32  s32Umax;			  // Parameter: upper saturation limit
	s32  s32Umin;			  // Parameter: lower saturation limit
	s32  s32Err;				  // Data: proportional term
	s32  s32ui;			  	// Data: integral term
	s32  s32v1;			  	// Data: pre-saturated controller output
	s32  s32i1;			  	// Data: integrator storage: ui(k-1)
	s32  s32w1;			  	// Data: saturation record: [u(k-1) - v(k-1)]
	s32	 s32PLLOut;
	u16  u16En;
} UGT_S_PLL_STRU;


typedef struct MDS_S_POS_OBSERVER_STRU_
{ 
	s32	 s32Ialphabeta[2];	
	s32	 s32Ualphabeta[2];	
	s32	 s32Idq[2];	
	s32	 s32IdqPre[2];		
	s32	 s32Udq[2];	
	s32	 s32UdqPre[2];		
	s32  s32ThetaEst;
  s32  s32SpeedEst;
	s32  s32SpeedInst;
  s32  s32GainQErr;
  s32  s32GainDErr;
	s32  s32SpeedFirst;
	s32  s32SpeedFirstPre;
	s32  s32PLLInputGain;
	s32  s32TsDivLq;
	s32	 s32TsRDivLq;
	s32	 s32TsLdDivLq;
	s32  s32TsPsiDivLq;
	s32  s32TsDivLd;
	s32  s32TsRDivLd;
	s32  s32TsLqDivLd;
	s32  s32CompTime;	
	s32  s32RestartShortTime;
	s32	 s32LdPU;
  s32  s32LqPU;	
	UGT_S_PLL_STRU sPLL;
} MDS_S_POS_OBSERVER_STRU;

typedef struct MDS_S_POS_OBSERVER_STRU_SHORT_
{ 
	s16	 s16Ialphabeta[2];	
	s16	 s16Ualphabeta[2];	
	s16	 s16Idq[2];	
	s16	 s16IdqPre[2];		
	s16	 s16Udq[2];	
	s16	 s16UdqPre[2];	
	s32  s16ThetaEst;
  s16  s16SpeedEst;
	s16  s16SpeedInst;
  s16  s16GainQErr;
  s16  s16GainDErr;
	s16  s16SpeedFirst;
	s16  s16SpeedFirstPre;
	s16  s16PLLInputGain;
	s16  s16TsDivLq;
	s16	 s16TsRDivLq;
	s16	 s16TsLdDivLq;
	s16  s16TsPsiDivLq;
	s16  s16TsDivLd;
	s16  s16TsRDivLd;
	s16  s16TsLqDivLd;
	s16  s16CompTime;	
	s32  s32RestartShortTime;
	s32	 s16LdPU;
  s32  s16LqPU;	
} MDS_S_POS_OBSERVER_SHORT_STRU;

EXTERN MDS_S_POS_OBSERVER_STRU MDS_sPosObserver;
EXTERN void MDS_vOBPosObserverInit(MDS_S_POS_OBSERVER_STRU *v);
EXTERN void MDS_vOBPosObserver(MDS_S_POS_OBSERVER_STRU *v);

EXTERN MDS_S_POS_OBSERVER_SHORT_STRU MDS_sPosObserverShort;
EXTERN void MDS_vOBPosObserverShortInit(MDS_S_POS_OBSERVER_SHORT_STRU *v);
EXTERN void MDS_vOBPosObserverShort(MDS_S_POS_OBSERVER_SHORT_STRU *v);

EXTERN void MDS_vOBPLL(UGT_S_PLL_STRU *v);
EXTERN void MDS_vOBRestarting(s16 s16alpha, s16 s16beta);
EXTERN void MDS_vCurrentControllerCalc(UGT_S_MOTORPARAMETERS_STRU *v);

EXTERN u8 MDS_vInitPosDeter(UGT_S_IPD_STRU *v, s16 s16Idc);
EXTERN void MDS_vCurLimit(s32 v);
	
#undef EXTERN	
#endif
