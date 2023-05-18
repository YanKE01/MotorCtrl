#define EXPORT_MDS_CALCVOLTAGE_H
	#include "MDS_CalcVoltage.h"
#undef EXPORT_MDS_CALCVOLTAGE_H

void MDS_vVoltageCalc(UGT_S_VOLTABC_STRU *v)
{	
  v->s16Tem 	  	= ((s32)(v->s16UdcMeas)*(s32)ONE_SIXTH)>>16;																
  v->s16UAsCalc   = ((s32)(v->s16Tem)*(((s32)(v->s16MfuncV1)<<1)-v->s16MfuncV2-v->s16MfuncV3))>>12;	//	IQ12*IQ15=IQ15>>12+15-15=12)		
  v->s16UBsCalc   = ((s32)(v->s16Tem)*(((s32)(v->s16MfuncV2)<<1)-v->s16MfuncV1-v->s16MfuncV3))>>12;	//			
	v->s16UCsCalc   = ((s32)(v->s16Tem)*(((s32)(v->s16MfuncV3)<<1)-v->s16MfuncV1-v->s16MfuncV2))>>12;	//		
}


