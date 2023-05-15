#ifndef SOURCE_MDS_ONESHUNT_H_
#define SOURCE_MDS_ONESHUNT_H_

#include "lcm32f037_lib.h"
#include "UserIncludes.h"

#if defined(EXPORT_MDS_ONESHUNT_H)
  #define EXTERN
#else
  #define EXTERN extern
#endif

#define UPDS_MIN_SAMPLING_TIME_NS 4500
#define MIN_SAMPLING_TIME 350
//  (u16)((unsigned long long)UPDS_CKTIM \
//				*(unsigned long long)UPDS_MIN_SAMPLING_TIME_NS/1000000000uL)  //3us
#define SAMPLE_DELAY -15

void UG_vOne_Shunt_FirstSample();
void UG_vOne_Shunt_SecSample();

EXTERN void MDS_vOneShunt(UGT_S_PWMDUTY_STRU *v);
EXTERN void MDS_vOneShuntInit(UGT_S_PWMDUTY_STRU *v);
#endif