#define EXPORT_USER_DATATRANSFORM_H_
	#include "User_DataTransform.h"
#undef EXPORT_USER_DATATRANSFORM_H_

void UD_vDataTransformInit(UGT_S_DATATRANSFORM_STRU *v)
{
	v->s32SpdGain 			= (u32)(UG_sSystemControllers.sMotorPara.u16fB * 60 / UG_sSystemControllers.sMotorPara.PolePairs);
	v->s32DCBusGain 		= (u16)(UG_sSystemControllers.sMotorPara.f32UB * 10);
	v->s32PhaseCurGain 	= (u32)(UG_sSystemControllers.sMotorPara.f32IB * 1000);
	v->s32PowerGain 		= (u32)(UG_sSystemControllers.sMotorPara.f32PowerB *10);			

}

void UD_vDataTransform(UGT_S_DATATRANSFORM_STRU *v)
{
	
	v->s16SpdRpm 					= ((s64)UG_sSystemControllers.sSPD.s32Fbk*UG_sUsartData.sFlashReadDataUpdata.s32SpdGain)>>24;													//单位是rpm
	v->u16DCBusVoltage 		= ((s32)UG_sVoltageAll.sVoltageAbc.s16UdcMeas * UG_sUsartData.sFlashReadDataUpdata.s32DCBusGain)>>12;									//单位是0.1V
	v->u16PhaseCurrentMag = ((s64)UG_sCurrentAll.sCurrentAlphaBeta.s16CurMag * UG_sUsartData.sFlashReadDataUpdata.s32PhaseCurGain)>>15;					//单位是1mA
	v->s16PowerIn					= ((s64)MDS_sCP.s32PowerFbk * UG_sUsartData.sFlashReadDataUpdata.s32PowerGain)>>24;
	v->u8Temperature			= 24;
}

