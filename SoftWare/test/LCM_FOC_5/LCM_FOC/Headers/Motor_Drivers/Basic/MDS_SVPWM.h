/******************** (C) COPYRIGHT 2021 LINGXIN Microelectronics***************
* File Name          : MDS_SVPWM.h
* Author             : LX Motor Lab  
* Date  						 : 2021-12-16
* Description        : space vector pulse width modulation
*******************************************************************************/
#ifndef SOURCE_MDS_SVPWM_H_
#define SOURCE_MDS_SVPWM_H_

#include "lcm32f037_lib.h"
#include "UserIncludes.h"

#if defined(EXPORT_MDS_SVPWM_H)
  #define EXTERN
#else
  #define EXTERN extern
#endif
	
#define SVPWM_TIM1_PWM_DISABLE_MACRO 		{TIM1->EGR |= 0x0080;}
#define	SVPWM_TIM1_PWM_ENABLE_MACRO  		{TIM1->EGR &= ~0x0080; TIM1->BDTR |= 1<<15;} 
#define SVPWM_TIM1_PWM_MODE_ENABLE			{TIM1->CCER |=(0x0005);TIM1->CCER |=(0x0005<<4);TIM1->CCER |=(0x0005<<8);}
#define SVPWM_TIM1_PWMH_LOW_PWML_ENABLE {TIM1->CCER |=(0x0001<<2);TIM1->CCER &=~(0x0001);TIM1->CCER |=(0x0001<<6);TIM1->CCER &=~(0x0001<<4);TIM1->CCER |=(0x0001<<10);TIM1->CCER &=~(0x0001<<8);}
#define SVWPM_ABC_HIGH_ACTIVE						{TIM1->CCER = 0x1555;}
	
#define BLDC_PWM_AH_BL_CO			{TIM1->CCER = 0x10C3;}		
#define BLDC_PWM_BH_CL_AO			{TIM1->CCER = 0x1C30;}	
#define BLDC_PWM_AH_CL_BO			{TIM1->CCER = 0x1C03;}	
#define BLDC_PWM_CH_AL_BO			{TIM1->CCER = 0x130C;}	
#define BLDC_PWM_CH_BL_AO			{TIM1->CCER = 0x13C0;}	
#define BLDC_PWM_BH_AL_CO			{TIM1->CCER = 0x103C;}
#define BLDC_PWM_ALL_CO				{TIM1->CCER = 0x1000;}


//static const u16 UPDS_HallToPhase60[8] =
//{
//    0x1000, //notez this should be a error state CCER all OFF000
//    0x10C3, //  C.   B-   A+ 001
//    0x1C30, //  C-   B+   A. 010
//    0x1C03, //  C-   B.   A+ 011
//    0x130C, //  C+   B.   A- 100
//    0x13C0, //  C+   B-   A. 101
//    0x103C, //  C.   B+   A- 110
//    0x1000 //notez this should be a error state111
//};	
	
#define SQRT3_DIV_2_IQ15			(s32)(28377)      // 28377=sqrt(3)/2

EXTERN void MDS_vFOC(void);	
EXTERN void MDS_vSVPWM(UGT_S_SVGEN_STRU *Svgen_Input);
EXTERN void MDS_vPWMUpdate(UGT_S_PWMDUTY_STRU *PWM_Duty_Input, vu16 *CurrSampleMode);
EXTERN void MDS_vDeadTimeComp(UGT_S_DEADTIMECOMP_STRU *DT_Input, UGT_S_CURRABC_STRU *Curr_Input, s16 Iq);	

#undef EXTERN
#endif //__MC_CLARKE_PARK_H
	
