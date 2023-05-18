#define EXPORT_MDS_THETAGENERATE_H
	#include "MDS_ThetaGenerate.h"
#undef EXPORT_MDS_THETAGENERATE_H


void MDS_vThetaInit(MDS_sTHETA_STRU *v)
{
	v->s16Freq 					= 0; 		// Input: Ramp frequency (pu) 	
	v->s16StepAngleMax	= MDS_THETA_STEP;	// Parameter: Maximum step angle (pu)	Base_frequency= 200Hz, Base_frequency/PWM_Frequency, 200*65536/16000=820(IQ15),200*65536/8000=1640(IQ15)
	v->s32Angle		= 0xC000;		// Variable: Step angle (pu)	
	v->u16AngleOut= 0xC000; 	//	
	v->s16Gain		= 0x7FFF;		// Input: Ramp gain (pu)
	v->s16Out			= 0;  	 		// Output: Ramp signal (pu) 	
	v->s16Offset	= 0x7FFF;		// Input: Ramp offset (pu)
}

void MDS_vRampInit(MDS_sRAMPIQ24_STRU *v, f32 f32Time, s32 _iq24max, s32 _iq24min)
{

	v->s32TargetValue		= 0; 										
	v->s32RampLowLimit	= _iq24min;					  
	v->s32RampHighLimit	= _iq24max;									
	v->s32SetpointValue	= 0;													 
	v->s32StepPosInc		= (s32)(16777216.0/UPDS_SYS_TICK_TASK_HZ/f32Time);
	v->u16EqualFlag			= 0;									
	v->s32Tmp						= 0;									
	
}

void MDS_vRampGen(MDS_sRAMPIQ24_STRU *v)
{
																
	v->s32Tmp = v->s32TargetValue - v->s32SetpointValue;
  if(v->s32Tmp < 0)	v->s32Tmp = -v->s32Tmp;
							
	if (v->s32Tmp >= v->s32StepPosInc)		
	{																										
		v->u16EqualFlag = 0;																										
		if (v->s32TargetValue >= v->s32SetpointValue)
		{
			v->s32SetpointValue += v->s32StepPosInc;					
		}										
		else		
		{
			v->s32SetpointValue -= v->s32StepPosInc;				
		}					
																													
		if (v->s32SetpointValue > v->s32RampHighLimit)	
		{
			v->s32SetpointValue = v->s32RampHighLimit;				
		}									
		else if (v->s32SetpointValue < v->s32RampLowLimit)
		{
			v->s32SetpointValue = v->s32RampLowLimit;					
		}																																																															
	}																										
	else 
	{
		v->u16EqualFlag = 1;	
		v->s32SetpointValue = v->s32TargetValue;	
	}
}

/*------------------------------------------------------------------------------
	RAMP(Sawtooh) Generator Macro Definition
------------------------------------------------------------------------------*/                                               
void MDS_vThetaGen(MDS_sTHETA_STRU *v)
{
																						
/* Compute the angle rate */								
	v->s32Angle += (((s32)v->s16StepAngleMax * v->s16Freq)>>15);		
																														
/* Saturate the angle rate within (0,2) */									
	if (v->s32Angle > 0xFFFF)							
		v->s32Angle -= 0xFFFF;							
	else if (v->s32Angle < 0x0000)					
		v->s32Angle += 0xFFFF;							
																			
		v->u16AngleOut = (u16)v->s32Angle;	
}
