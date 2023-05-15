
#define EXPORT_MDS_FLUXWEAKENING_H
	#include "MDS_FluxWeakeningPowerControl.h"
#undef EXPORT_MDS_FLUXWEAKENING_H


void MDS_vFluxWeakeningInit(MDS_S_FW_STRU *v)
{
	v->s32VFbk = 0;
	v->s32Vmax = _IQ(0.7);
	v->s32IMaxSquare  = _IQmpy(UG_sSystemControllers.sMotorPara.s32SpdPIOutMax, UG_sSystemControllers.sMotorPara.s32SpdPIOutMax);
	v->PI_FW.u16En 		= 0;
	v->PI_FW.s32Umax 	= 0;
	v->PI_FW.s32Umin 	= -_IQ(UG_sSystemControllers.sMotorPara.f32FluxWeakenOutMax / UG_sSystemControllers.sMotorPara.f32IB);
	v->PI_FW.s32Kp		= _IQ(UG_sSystemControllers.sMotorPara.f32FluxWeakenKp);
	v->PI_FW.s32Ki		= _IQ(UG_sSystemControllers.sMotorPara.f32FluxWeakenKi/UPDS_SYS_TASK_HZ);
	v->PI_FW.s32Err 	= 0;
	v->PI_FW.s32i1 		= 0;
	v->PI_FW.s32Out 	= 0;
	v->PI_FW.s32Ref 	= 0;
	v->PI_FW.s32Fbk 	= 0;
	v->PI_FW.s32ui 		= 0;
	v->PI_FW.s32v1 		= 0;
	v->PI_FW.s32w1 		= 0;
	v->u32Count 			= 0;
}

void MDS_vConstantPowerInit(MDS_S_CP_STRU *v)
{
	v->s32PowerFbk 	= 0;
	v->s32PowerMax 	= _IQ(UG_sSystemControllers.sMotorPara.f32SpeedPowerLimit/UG_sSystemControllers.sMotorPara.f32PowerB);
	v->PI_CP.u16En 	= 0;
	if(UG_sSysStateErr.uControlReg.Bits.ControlMode == UGT_E_CM_POWER)
	{	
		v->PI_CP.s32Umax = _IQ(1.0);
	}
	else//其他模式限功率
	{
		v->PI_CP.s32Umax = 0;	
	}
	v->PI_CP.s32Umin = _IQ(-1.0);
	v->PI_CP.s32Kp 	= _IQ(UG_sSystemControllers.sMotorPara.f32PowerKp);
	v->PI_CP.s32Ki 	= _IQ(UG_sSystemControllers.sMotorPara.f32PowerKi/UPDS_SYS_TASK_HZ);
	v->PI_CP.s32Err = 0;
	v->PI_CP.s32i1 	= 0;
	v->PI_CP.s32Out = 0;
	v->PI_CP.s32Ref = 0;
	v->PI_CP.s32Fbk = 0;
	v->PI_CP.s32ui 	= 0;
	v->PI_CP.s32v1 	= 0;
	v->PI_CP.s32w1 	= 0;
}

void MDS_vFluxWeakening(MDS_S_FW_STRU *v, s32 Ud, s32 Uq)
{
//	v->s32VFbk = _IQmpy(Ud,Ud) + _IQmpy(Uq,Uq);
	u32 temp = 0;
	s32 s32temp=0;
//	v->s32VFbk = ((Ud*Ud)>>6) + ((Uq*Uq)>>6);
	temp = ((Ud*Ud+Uq*Uq)>>21)&0x000001FF;
	v->s32VFbk = sqrt_table[temp]<<9;
	v->PI_FW.s32Fbk = v->s32VFbk;
	v->PI_FW.s32Ref = v->s32Vmax;	
	MDS_vPIRegulatorIQ24(&v->PI_FW);
	s32temp=((v->s32IMaxSquare -  (((s64)v->PI_FW.s32Out*v->PI_FW.s32Out)>>24))>>15);
	if(s32temp<0)s32temp=0;
	temp = s32temp&0x000001FF;
	UG_sSystemControllers.sSPD.s32Umax = sqrt_table[temp]<<9;
	UG_sSystemControllers.sSPD.s32Umin = -UG_sSystemControllers.sSPD.s32Umax;
}


#if (UPDS_POWER_CONTROL_SEL == UPDS_POWER_CONTROL_SOFTWARE)			
void MDS_vConstantPowerDQ(MDS_S_CP_STRU *v, s32 Ud, s32 Id, s32 Uq, s32 Iq)
{
	v->s32PowerFbk += ((_IQmpy(((Id*Ud + Uq*Iq)>>6),_IQ(1.5))-v->s32PowerFbk)>>1);
	v->PI_CP.s32Fbk = v->s32PowerFbk;
	v->PI_CP.s32Ref = v->s32PowerMax;	
	MDS_vPIRegulatorIQ24(&v->PI_CP);
}
#elif (UPDS_POWER_CONTROL_SEL == UPDS_POWER_CONTROL_HARDWARE)			
void MDS_vConstantPower(MDS_S_CP_STRU *v, s32 Id, s16 Udc)
{
	v->s32PowerFbk += ((((s32)Id*Udc)-v->s32PowerFbk)>>1);//_IQ12*IQ12=IQ24
	v->PI_CP.s32Fbk = v->s32PowerFbk;
//	v->PI_CP.s32Ref = v->s32PowerMax;	
	MDS_vPIRegulatorIQ24(&v->PI_CP);
}
#endif

void MDS_vNoWaterCalInit(MDS_S_NW_STRU *v)
{
	v->s32IqUseLPF			=	0;
	v->s32IqUseABS			=	0;
	v->s32SpdDivIqGain	=	0;
	v->s32SpeedUse			=	0;
	v->s32SpeedUseSquare=	0;
}

void MDS_vNoWaterCal(MDS_S_NW_STRU *v,s32 Iq, s32 Speed)
{
	u64 u64temp;
	
	v->s32IqUseABS       = UPDS_S32_ABS(Iq);//IQ24	
	v->s32IqUseLPF			 += (((v->s32IqUseABS) - v->s32IqUseLPF)>>5);//IQ24	
	v->s32SpeedUse  		 = (Speed)>>9;//IQ15
	v->s32SpeedUseSquare = (v->s32SpeedUse)*(v->s32SpeedUse);//IQ30
	if(Speed>_IQ(0.2))  u64temp =  (u64)(v->s32SpeedUseSquare)/((v->s32IqUseLPF)>>9);//IQ15
	
	if(u64temp>_IQ15(100.0))  v->s32SpdDivIqGain = _IQ15(100.0);
	else v->s32SpdDivIqGain = u64temp;
}

void MDS_vMTPAInit(MDS_S_MTPA_STRU *v)
{
	v->s32Gain  = _IQ15(UPDS_PHIDIVL);
	v->s32IdRef = 0;
	v->s32Out   = 0;
	v->s32OutMax=	_IQ15(UPDS_MTPAMAX);
	v->s32OutMin=	_IQ15(UPDS_MTPAMIN);
	v->u16En		=	FALSE;
}

void MDS_vMTPA(MDS_S_MTPA_STRU *v,s32 Iq)
{
	s32 iqtemp,temp,temp1,temp2;
	
	iqtemp = Iq>>9;
	
	if(v->u16En==TRUE)
	{
		temp = ((v->s32Gain * v->s32Gain + iqtemp*iqtemp)>>21)&0x000001FF;
		temp1 = sqrt_table[temp];
		temp2 = v->s32Gain - temp1;
	}
	
	if(temp2>v->s32OutMax) v->s32Out = v->s32OutMax;
	else if(temp2<v->s32OutMin) v->s32Out = v->s32OutMin;
	else v->s32Out = temp2;
	
	v->s32IdRef = (v->s32Out)<<9;		
}