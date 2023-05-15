#define EXPORT_MDS_PIDREGULATOR_H
	#include "MDS_PIDRegulators.h"
#undef EXPORT_MDS_PIDREGULATOR_H

void MDS_vUdcPIRegulatorIQ24Init(UGT_S_PICONTROLLER_STRU *PI_Udc)
{
	PI_Udc->s32Kp = UPDS_UDC_KP;
	PI_Udc->s32Ki = UPDS_UDC_KI;
	PI_Udc->s32Umax = UPDS_IDC_MAX; 
	PI_Udc->s32Umin = UPDS_IDC_MIN;
	PI_Udc->s32i1	= 0;
	PI_Udc->s32ui	= 0;
	PI_Udc->s32Err	= 0;
	PI_Udc->s32v1	= 0;
	PI_Udc->s32w1	= 0;
	PI_Udc->s32Fbk	= 0;
	PI_Udc->s32Ref	= 0;
	PI_Udc->s32Out	= 0;
	PI_Udc->u16En  = FALSE;
	PI_Udc->u16LoopIndex = 1;
}


void MDS_vCurPIRegulatorIQ24Init(UGT_S_PICONTROLLER_STRU *PI_Id, UGT_S_PICONTROLLER_STRU *PI_Iq)
{

	PI_Id->s32Kp = UG_sSystemControllers.sMotorPara.s32KpDAxis;
	PI_Id->s32Ki = UG_sSystemControllers.sMotorPara.s32KiDAxis1;
	PI_Id->s32Umax = UPSD_PI_ID_MAX;
	PI_Id->s32Umin = UPSD_PI_ID_MIN;
	PI_Id->s32i1	= 0;
	PI_Id->s32ui	= 0;
	PI_Id->s32Err	= 0;
	PI_Id->s32v1	= 0;
	PI_Id->s32w1	= 0;
	PI_Id->s32Fbk	= 0;
	PI_Id->s32Ref	= 0;
	PI_Id->s32Out	= 0;
	PI_Id->u16En  = FALSE;	
	PI_Id->u16LoopIndex = 1;
	
	PI_Iq->s32Kp = UG_sSystemControllers.sMotorPara.s32KpQAxis;
	PI_Iq->s32Ki = UG_sSystemControllers.sMotorPara.s32KiQAxis1;
	PI_Iq->s32Umax = UPSD_PI_IQ_MAX;
	PI_Iq->s32Umin = UPSD_PI_IQ_MIN;
	PI_Iq->s32i1	= 0;
	PI_Iq->s32ui	= 0;
	PI_Iq->s32Err	= 0;
	PI_Iq->s32v1	= 0;
	PI_Iq->s32w1	= 0;
	PI_Iq->s32Fbk	= 0;
	PI_Iq->s32Ref	= 0;
	PI_Iq->s32Out	= 0;
	PI_Iq->u16En  = FALSE;
	PI_Iq->u16LoopIndex = 1;
	
}

void MDS_vCurPIRegulatorIQ12Init(UGT_S_PICONTROLLERIQ12_STRU *PI_Id, UGT_S_PICONTROLLERIQ12_STRU *PI_Iq)
{
	PI_Id->s16Kp = UG_sSystemControllers.sMotorPara.s16KpDAxis;
	PI_Id->s16Ki = UG_sSystemControllers.sMotorPara.s16KiDAxis1;
	PI_Id->s16Umax = UPSD_PI_ID_MAX;
	PI_Id->s16Umin = UPSD_PI_ID_MIN;
	PI_Id->s16i1	= 0;
	PI_Id->s16ui	= 0;
	PI_Id->s16Err	= 0;
	PI_Id->s16v1	= 0;
	PI_Id->s16w1	= 0;
	PI_Id->s16Fbk	= 0;
	PI_Id->s16Ref	= 0;
	PI_Id->s16Out	= 0;
	PI_Id->u16En  = FALSE;	
	PI_Id->u16LoopIndex = 1;
	
	PI_Iq->s16Kp = UG_sSystemControllers.sMotorPara.s16KpQAxis;
	PI_Iq->s16Ki = UG_sSystemControllers.sMotorPara.s16KiQAxis1;
	PI_Iq->s16Umax = UPSD_PI_IQ_MAX;
	PI_Iq->s16Umin = UPSD_PI_IQ_MIN;
	PI_Iq->s16i1	= 0;
	PI_Iq->s16ui	= 0;
	PI_Iq->s16Err	= 0;
	PI_Iq->s16v1	= 0;
	PI_Iq->s16w1	= 0;
	PI_Iq->s16Fbk	= 0;
	PI_Iq->s16Ref	= 0;
	PI_Iq->s16Out	= 0;
	PI_Iq->u16En  = FALSE;
	PI_Iq->u16LoopIndex = 1;
}

void MDS_vSpdPIRegulatorIQ24Init(UGT_S_PICONTROLLER_STRU *PI_Speed)
{	
	PI_Speed->s32Kp   = _IQ(UG_sSystemControllers.sMotorPara.f32SpdKp);
	PI_Speed->s32Ki   = _IQ(UG_sSystemControllers.sMotorPara.f32SpdKi*UPDS_SPD_LOOP_COUNT/UPDS_SYS_TICK_HZ);
	PI_Speed->s32Umax = UG_sSystemControllers.sMotorPara.s32SpdPIOutMax;
	PI_Speed->s32Umin = UG_sSystemControllers.sMotorPara.s32SpdPIOutMin;
	PI_Speed->s32i1		= 0;
	PI_Speed->s32ui		= 0;
	PI_Speed->s32Err	= 0;
	PI_Speed->s32v1		= 0;
	PI_Speed->s32w1		= 0;
	PI_Speed->s32Fbk	= 0;
	PI_Speed->s32Ref	= 0;
	PI_Speed->s32Out	= 0;
	PI_Speed->u16En		= FALSE;
	PI_Speed->u16LoopIndex = UPDS_SPD_LOOP_COUNT;		
}

/*******************************************************************************
* Function Name  : PI_Regulator
* Description    : Compute the PI output for a PI regulation.
* Input          : Pointer to the PI settings (*PI_Flux)
                   all the parameter are in Iq24 format
* Output         : s16
* Return         : None
*******************************************************************************/
//__attribute__((section("RAMCODE")))
void MDS_vPIRegulatorIQ24(UGT_S_PICONTROLLER_STRU *PI_Struct)
{
	if (PI_Struct->u16En == TRUE)
	{
		PI_Struct->s32Err = PI_Struct->s32Ref - PI_Struct->s32Fbk; 

		if(PI_Struct->s32Out == PI_Struct->s32v1)  			PI_Struct->s32ui = ((long long)(PI_Struct->s32Ki)*(PI_Struct->s32Err)>>24)+PI_Struct->s32i1;
		else																						PI_Struct->s32ui = PI_Struct->s32i1;

		if(PI_Struct->s32i1 > PI_Struct->s32Umax)				PI_Struct->s32i1 = PI_Struct->s32Umax;
		else if(PI_Struct->s32i1 < PI_Struct->s32Umin) 	PI_Struct->s32i1 = PI_Struct->s32Umin;
		else 																						PI_Struct->s32i1 = PI_Struct->s32ui;	
				
		PI_Struct->s32v1 = ((long long)(PI_Struct->s32Kp)*(PI_Struct->s32Err)>>24)+PI_Struct->s32ui;
		
		if(PI_Struct->s32v1 > PI_Struct->s32Umax)				PI_Struct->s32Out = PI_Struct->s32Umax;
		else if(PI_Struct->s32v1 < PI_Struct->s32Umin) 	PI_Struct->s32Out = PI_Struct->s32Umin;
		else 																						PI_Struct->s32Out = PI_Struct->s32v1;				
	}
	else
	{
		PI_Struct->s32ui = 0;
		PI_Struct->s32i1 = 0;
		PI_Struct->s32v1 = 0;
		PI_Struct->s32Out= 0;	
	}
}

void MDS_vPIRegulatorIQ12(UGT_S_PICONTROLLERIQ12_STRU *PI_Struct)
{
	if (PI_Struct->u16En == TRUE)
	{
		PI_Struct->s16Err = PI_Struct->s16Ref - PI_Struct->s16Fbk;

		if(PI_Struct->s16Out == PI_Struct->s16v1) PI_Struct->s16ui = ((s32)PI_Struct->s16Ki*PI_Struct->s16Err>>12)+ PI_Struct->s16i1;
		else 																			PI_Struct->s16ui = PI_Struct->s16i1;

		if(PI_Struct->s16i1 > PI_Struct->s16Umax)				PI_Struct->s16i1 = PI_Struct->s16Umax;
		else if(PI_Struct->s16i1 < PI_Struct->s16Umin) 	PI_Struct->s16i1 = PI_Struct->s16Umin;
		else 																						PI_Struct->s16i1 = PI_Struct->s16ui;			
		
		PI_Struct->s16v1 = ((s32)PI_Struct->s16Kp*PI_Struct->s16Err>>12) + PI_Struct->s16ui;
		
		if(PI_Struct->s16v1 > PI_Struct->s16Umax)				PI_Struct->s16Out = PI_Struct->s16Umax;
		else if(PI_Struct->s16v1 < PI_Struct->s16Umin) 	PI_Struct->s16Out = PI_Struct->s16Umin;
		else 																						PI_Struct->s16Out = PI_Struct->s16v1;
	}
	else
	{
		PI_Struct->s16ui = 0;
		PI_Struct->s16i1 = 0;
		PI_Struct->s16v1 = 0;
		PI_Struct->s16Out= 0;	
	}
}





