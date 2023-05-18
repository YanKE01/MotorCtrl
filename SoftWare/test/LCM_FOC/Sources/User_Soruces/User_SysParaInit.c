#define EXPORT_USER_SYSPARAINIT_H_
	#include "User_SysParaInit.h"
#undef EXPORT_USER_SYSPARAINIT_H_

void US_vUserAppInit(void)
{
	US_vSystParaInit();
	TIM_Cmd(TIM1, ENABLE);
	UPDS_SYSTICK_ENABLE;
}

void US_vSystParaInitPowerup(void)
{
	UG_sSysStateErr.sSystemState 							= UGT_E_SS_INIT_B;
	UG_sSysStateErr.sSystemStatePre						= UGT_E_SS_INIT_B;
	UG_sSysStateErr.eRestart 									= UGT_E_RS_FIRST_A;	
	UG_sSystemControllers.u8CurIQMode					= UPDS_CUR_IQ;
	UG_sSystemControllers.s32StartUpSpdMax    = UPDS_STARTUP_SPD_MAX;
	UG_sSystemControllers.u8ExtraStart 				= 0;		
	UG_sSysStateErr.uSystemError.All 			 		= 0x0000;	
	UG_sSysStateErr.sSysTime.StartupFailCount = 0;

	#if (UPDS_DEBUG_MODE == UPDS_SOFTTOOL_DEBUG)
		UG_sSysStateErr.uControlReg.All 						 = UG_sSystemControllers.sMotorPara.sControlWord.All;
		UG_sSysStateErr.uControlReg.Bits.ControlMode = (UG_sSystemControllers.sMotorPara.sControlWord.All>>6)&0x000F;
		UG_sSysStateErr.uControlReg.Bits.ChipType 	 = (UG_sSystemControllers.sMotorPara.sControlWord.All>>10)&0x0003;
		UG_sSysStateErr.uControlReg.Bits.CommandType = (UG_sSystemControllers.sMotorPara.sControlWord.All>>13)&0x0003;
	#endif 

		MDS_vMotorParaCalc(&UG_sSystemControllers.sMotorPara);
//		UD_vDataTransformInit(&UG_sUsartData.sFlashReadDataUpdata);
		MDS_vCurLimitInit(&UG_sSystemControllers.sCurLimit);
//		UU_vUsartDataInit(&UG_sUsartData);
		US_vHardwareOverCurCalcAMP();	
}


void US_vSystParaInit(void)
{
	if(UG_sSysStateErr.uControlReg.Bits.ControlMode != UGT_E_CM_TEST)UP_vBreakEnable();
	SVPWM_TIM1_PWM_DISABLE_MACRO;	
	US_vSystStateInit(&UG_sSysStateErr);
	MDS_vUdcPIRegulatorIQ24Init(&UG_sSystemControllers.sUdc);
	#if (UPDS_CUR_IQ == UPDS_CUR_IQ24)
	MDS_vCurPIRegulatorIQ24Init(&UG_sSystemControllers.sID, &UG_sSystemControllers.sIQ);
	MDS_vOBPosObserverInit(&MDS_sPosObserver);
	#elif (UPDS_CUR_IQ == UPDS_CUR_IQ12)
	MDS_vCurPIRegulatorIQ12Init(&UG_sSystemControllers.sID12, &UG_sSystemControllers.sIQ12);
  MDS_vOBPosObserverShortInit(&MDS_sPosObserverShort);	
	#endif
	MDS_vSpdPIRegulatorIQ24Init(&UG_sSystemControllers.sSPD);
	MDS_vFluxWeakeningInit(&MDS_sFW);
	MDS_vConstantPowerInit(&MDS_sCP);
	MDS_vThetaInit(&TG_sThetaGen);
	MDS_vRampInit(&TG_sCommandRef,UG_sSystemControllers.sMotorPara.f32AccRate,_IQ(1.5),_IQ(-1.5));
	US_vGlobalVariablesInit();
	MDS_vTIMInit();
	MDS_vIPDInit(&UG_sIPDAll);
	UG_sSysStateErr.uSystemError.Bits.Breaken=FALSE;	
	MDS_vMTPAInit(&MDS_sMTPA);
}

void US_vSystStateInit(UGT_S_SYSTEMSTATE_STRU *v)
{
	v->sSystemState 						= UGT_E_SS_INIT_B;
	v->sSystemStatePre					= UGT_E_SS_INIT_B;
	v->sIFStartUp 							= UGT_E_IFSTARTUP_ACC_A;
	v->eAlignment								= UGT_E_ALIGNMENT_FIRST_A;
	v->sVSPCheck								= UGT_E_VSP_CLOSED_A;
	v->sSysTime.PrechargeCount 	= 0;
	v->sSysTime.OCCount 			 	= 0;
	v->sSysTime.OLCount 			 	= 0;
	v->sSysTime.OTMotorCount 	 	= 0;
	v->sSysTime.OTIPMCount 		 	= 0;
	v->sSysTime.IPMFaultCount	 	= 0;
	v->sSysTime.OverWindSpeedCount 			= 0;
	v->sSysTime.UVCount				 		 			= 0;
	v->sSysTime.ReStartTime 	 		 			= US_RE_STARTUP_TIME_S32;
	v->sSysTime.StartupSwitchFailCount 	= 0;
	v->sSysTime.StartupStartFailCount	 	= 0;
	v->sSysTime.BreakCount 							= 0;
	v->sSysTime.LosePhaseCount							= 0;
	v->sSysTime.OverIAsCount						= 0;
	v->sSysTime.OverIBsCount						= 0;	
	v->sSysTime.OverICsCount						= 0;
	v->sSysTime.RestartingCount         = 0;
	v->sSysTime.RestartingShortNum			= UG_sSystemControllers.sMotorPara.u8SoftRestartPulseCountTotal;//UPDS_SHORTTIME_US_CNT;
	v->sSysTime.RestartingIntervalNum		= UG_sSystemControllers.sMotorPara.u8SoftRestartIntervalCountTotal;//UPDS_INTERVAL_US_CNT;
	v->sSysTime.RestartingInterval2Num	= UPDS_INTERVAL_FINAL_MS_CNT;
	v->sSysTime.RestartGain             = _IQ(OB_THETAB / UPDS_WB / UPDS_RESTART_DELTA_TIME);
	v->sSysTime.RestartGainPos          = UPDS_RESTART_POS_GAIN;
	v->sSysTime.UVFlashWriteCount				= 0;
	UG_sSysStateErr.uSystemError.All 			 		= 0x0000;	
	
	v->sSoftClose.u8SoftCloseEn					= FALSE;
	v->sSoftClose.u8VSP_LOCK						= FALSE;
	v->sPWMMode.PWMMode									= UPDS_PWM_MODE1;
	v->sPWMMode.PWMModePre							= UPDS_PWM_MODE1;
	v->sPWMMode.SpeedSwitchHigh					= UPDS_PWM_SWITCH_SPEED_HIGH;
	v->sPWMMode.SpeedSwitchLow					= UPDS_PWM_SWITCH_SPEED_LOW;
	v->sRestart.u8RestartDirect 				= 0;

	v->u8IdentifySwitch									= 0;
}

void US_vGlobalVariablesInit(void)
{

	UG_sVoltageAll.sPwmDuty.u16HalfPerMax 	= UG_sSystemControllers.sMotorPara.u16PWMPerood1>>1;
	UG_sVoltageAll.sPwmDuty.u16PeriodMax 		= UG_sSystemControllers.sMotorPara.u16PWMPerood1;
	UG_sVoltageAll.sVoltageAbc.s16UdcFluctuateGain = _IQ12(1.0);
	UG_sVoltageAll.sVoltageAbc.s16UdcSamplePUGain = (s16)(UPDS_SAMPLE_AD_MAX / UG_sSystemControllers.sMotorPara.f32GainVdc / UG_sSystemControllers.sMotorPara.f32UB * 0x1000);//IQ12
	UG_sVoltageAll.sVoltageAbc.s16UxnSamplePUGain = (s16)(UPDS_SAMPLE_AD_MAX / UG_sSystemControllers.sMotorPara.f32GainVdc / UG_sSystemControllers.sMotorPara.f32UB * 0x1000);//IQ12
	UG_sVoltageAll.sDeadTimeComp.s16IqAbs = 0;
	UG_sVoltageAll.sDeadTimeComp.s16IqLPF = 0;
	UG_sVoltageAll.sDeadTimeComp.s16IqLPFGain = UPDS_IQ_LPF_BAND_GAIN;
	UG_sVoltageAll.sDeadTimeComp.u16DTCompEn 	= TRUE;
	UG_sVoltageAll.sDeadTimeComp.s32DTCompC1 = 0;
	UG_sVoltageAll.sDeadTimeComp.s32DTCompC2 = 0;
	UG_sVoltageAll.sDeadTimeComp.s32DTCompC3 = 0;
	UG_sVoltageAll.sDeadTimeComp.s16DTComp   				= UPDS_TIME_COMP;
	UG_sVoltageAll.sDeadTimeComp.s16DTCompOffset 		= 0;
	UG_sVoltageAll.sDeadTimeComp.u16DTCompBand 			= 	(u16)(0.001*0x7FFF);
	UG_sVoltageAll.sDeadTimeComp.s16DTCompOnIqAmp 	= UPDS_IQ_ON_AMP;
	UG_sVoltageAll.sDeadTimeComp.s16DTCompOffIqAmp 	= UPDS_IQ_OFF_AMP;
	UG_sVoltageAll.sPwmDuty.s32MfuncC1 = 0;
	UG_sVoltageAll.sPwmDuty.s32MfuncC2 = 0;
	UG_sVoltageAll.sPwmDuty.s32MfuncC3 = 0;
	UG_sVoltageAll.sSvgen.u8PWM5Stage  = 1;

		
	UG_sCurrentAll.sCurrentAbc.u16AsOffest = 0;
	UG_sCurrentAll.sCurrentAbc.u16BsOffest = 0;	
	UG_sCurrentAll.sCurrentAbc.u16CsOffest = 0;
	UG_sCurrentAll.sCurrentAbc.u16IdcOffest = 0;
	UG_sCurrentAll.sCurrentAlphaBeta.s16Alpha	= 0;
	UG_sCurrentAll.sCurrentAlphaBeta.s16Beta 	= 0;
	UG_sCurrentAll.sCurrentAlphaBeta.s16CurMag= 0;
	UG_sCurrentAll.sCurrentDqUse.s16Dr	= 0;
	UG_sCurrentAll.sCurrentDqUse.s16Qr	= 0;
	UG_sCurrentAll.sCurrentDqSO.s16Dr		= 0;
	UG_sCurrentAll.sCurrentDqSO.s16Qr		= 0;
	UG_sCurrentAll.sCurrentAbc.u16SampleChooseNum = UA_SAMPLE_A_B_NC;
	UG_sCurrentAll.sCurrentDqUseLPF.s16Dr = 0;
	UG_sCurrentAll.sCurrentDqUseLPF.s16Qr = 0;
	UG_sCurrentAll.s32RestartMinLimit     = UPDS_SHORT_CURRENT_MAG>>9;//_IQ15(0.02);
	
	UG_sPositionAll.PosOpenLoop = 0;
	UG_sPositionAll.u16PosUse 			= 0;
	UG_sPositionAll.PosVoltMeas = 0;
	UG_sPositionAll.PosStateObserver = 0;
	UG_sPositionAll.SpdOpenLoop = 0;
	UG_sPositionAll.SpdUse 			= 0;
	UG_sPositionAll.SpdVoltMeas = 0;
	UG_sPositionAll.SpdStateObserver = 0;
	UG_sPositionAll.SpdRestart = 0;
	UG_sPositionAll.PosRsstart[0] = 0;	
	UG_sPositionAll.PosRsstart[1] = 0;
	UG_sPositionAll.SpdUseLargeLPF = 0;
	UG_sPositionAll.PosCount[0]		=0;
	UG_sPositionAll.PosCount[1]		=0;	
	UG_sADSampleAll.s16VSPLPF = 0;
	UG_sADSampleAll.u16IAsOffest = 0;
	UG_sADSampleAll.u16IBsOffest = 0;
	UG_sADSampleAll.u16ICsOffest = 0;
	UG_sADSampleAll.u16IdcOffest = 0;	
	UG_sADSampleAll.s16IGBTTempOffest 	= 0;
	UG_sADSampleAll.u16MotorTempOffest 	= 0;
	UG_sADSampleAll.u16PFCUacOffest		 	= 0;
		
	UG_sSystemControllers.sCommandAll.s32IdCommand  	= 0;
	UG_sSystemControllers.sCommandAll.s32IqCommand  	= 0;
	UG_sSystemControllers.sCommandAll.s32SpdCommand 	= 0;
	
	UG_sSystemControllers.sCommandAll.s32IdUse 				= 0;
	UG_sSystemControllers.sCommandAll.s32IqUse 				= 0;
	UG_sSystemControllers.sCommandAll.s32SpdUse 			= 0;
	
	UG_sCurrentAll.sCurrentAlphaBeta.s32CurMag = 0;
	UG_sSysStateErr.eRestart 									 = UGT_E_RS_FIRST_A;
	
}



void MDS_vOtherInitFromUserSetting(UGT_S_MOTORPARAMETERS_STRU *v)
{
	v->u16PWMPerood1 = ((u16) (UPDS_CKTIM / (u32)(2 * v->u16PWMFre1 *(UP_PWM_PRSC+1))));
	v->u16PWMPerood2 = ((u16) (UPDS_CKTIM / (u32)(2 * v->u16PWMFre2 *(UP_PWM_PRSC+1))));
	
	UG_sVoltageAll.sPwmDuty.u16HalfPerMax 	= v->u16PWMPerood1>>1;
	UG_sVoltageAll.sPwmDuty.u16PeriodMax 		= v->u16PWMPerood1;

	v->u16Deadtime   =  (u16)((u64)UPDS_CKTIM * v->u16DeadtimeNs / 2000000000uL);
	v->u16DeadtimeComp2 = (s16)((v->u16DeadtimeNs)*v->u16PWMPerood2/30518);
	v->u16DeadtimeComp1 = (s16)((v->u16DeadtimeNs)*v->u16PWMPerood1/30518);
	
	v->s32GainQErr1			=	_IQ20(v->f32ObsGainQ * v->f32LqP /v->f32TsP1 / v->f32PsiP);
  v->s32GainDErr1			=	_IQ20(v->f32ObsGainD * v->f32LdP /v->f32TsP1 / v->f32PsiP);
	v->s32PLLInputGain1	=	_IQ(v->f32WB / v->u16PWMFre1 / OB_THETAB);//OB_IQTSPLL;
	v->s32TsDivLq1			= _IQ(v->f32TsP1 / v->f32LqP);
	v->s32TsRDivLq1			=	_IQ(v->f32TsP1 * v->f32RsP / v->f32LqP);
	v->s32TsLdDivLq1		=	_IQ(v->f32TsP1 * v->f32LdP / v->f32LqP);
	v->s32TsPsiDivLq1		=	_IQ(v->f32TsP1 * v->f32PsiP / v->f32LqP);
	v->s32TsDivLd1			= _IQ(v->f32TsP1 / v->f32LdP);
	v->s32TsRDivLd1			=	_IQ(v->f32TsP1 * v->f32RsP / v->f32LdP);
	v->s32TsLqDivLd1		=	_IQ(v->f32TsP1 * v->f32LqP / v->f32LdP);
	v->s32CompTime1			= _IQ(1.5 * v->f32WB / v->u16PWMFre1 / OB_THETAB);

	v->s32GainQErr2			=	_IQ20(v->f32ObsGainQ * v->f32LqP /v->f32TsP2 / v->f32PsiP);
  v->s32GainDErr2			=	_IQ20(v->f32ObsGainD * v->f32LdP /v->f32TsP2 / v->f32PsiP);
	v->s32PLLInputGain2	=	_IQ(v->f32WB / v->u16PWMFre2 / OB_THETAB);
	v->s32TsDivLq2			= _IQ(v->f32TsP2 / v->f32LqP);
	v->s32TsRDivLq2			=	_IQ(v->f32TsP2 * v->f32RsP / v->f32LqP);
	v->s32TsLdDivLq2		=	_IQ(v->f32TsP2 * v->f32LdP / v->f32LqP);
	v->s32TsPsiDivLq2		=	_IQ(v->f32TsP2 * v->f32PsiP / v->f32LqP);
	v->s32TsDivLd2			= _IQ(v->f32TsP2 / v->f32LdP);
	v->s32TsRDivLd2			=	_IQ(v->f32TsP2 * v->f32RsP / v->f32LdP);
	v->s32TsLqDivLd2		=	_IQ(v->f32TsP2 * v->f32LqP / v->f32LdP);
	v->s32CompTime2			= _IQ(1.5 * v->f32WB / v->u16PWMFre2 / OB_THETAB);
	
	v->s32RestartShortTime = _IQ(v->f32WB * 0.000001 * v->f32SoftRestartPulse/ OB_THETAB);
	
}

void MDS_vOBPosObserverInit(MDS_S_POS_OBSERVER_STRU *v)
{	
	v->s32Ialphabeta[0]	=	0;	
	v->s32Ialphabeta[1]	=	0;	
	v->s32Ualphabeta[0]	=	0;	
	v->s32Ualphabeta[1]	=	0;	
	v->s32Idq[0]				=	0;
	v->s32Idq[1]				=	0;		
	v->s32IdqPre[0]			=	0;	
	v->s32IdqPre[1]			=	0;		
	v->s32Udq[0]				=	0;	
	v->s32Udq[1]				=	0;	
	v->s32UdqPre[0]			=	0;	
	v->s32UdqPre[1]			=	0;
	v->s32ThetaEst			=	0;
  v->s32SpeedEst			=	0;
	v->s32SpeedEst			= 0;
	v->s32SpeedFirst		=	0;
	v->s32SpeedInst			= 0;
	v->s32SpeedFirstPre	=	0;

	v->s32GainQErr			=	UG_sSystemControllers.sMotorPara.s32GainQErr1;
  v->s32GainDErr			=	UG_sSystemControllers.sMotorPara.s32GainDErr1;;
	v->s32PLLInputGain	=	UG_sSystemControllers.sMotorPara.s32PLLInputGain1;
	v->s32TsDivLq				= UG_sSystemControllers.sMotorPara.s32TsDivLq1;
	v->s32TsRDivLq			=	UG_sSystemControllers.sMotorPara.s32TsRDivLq1;
	v->s32TsLdDivLq			=	UG_sSystemControllers.sMotorPara.s32TsLdDivLq1;
	v->s32TsPsiDivLq		=	UG_sSystemControllers.sMotorPara.s32TsPsiDivLq1;
	v->s32TsDivLd				= UG_sSystemControllers.sMotorPara.s32TsDivLd1;
	v->s32TsRDivLd			=	UG_sSystemControllers.sMotorPara.s32TsRDivLd1;
	v->s32TsLqDivLd			=	UG_sSystemControllers.sMotorPara.s32TsLqDivLd1;
	v->s32LdPU 					= UG_sSystemControllers.sMotorPara.s32LdPU;
  v->s32LqPU 					= UG_sSystemControllers.sMotorPara.s32LqPU;	
	v->s32CompTime			= UG_sSystemControllers.sMotorPara.s32CompTime1;	
	v->s32RestartShortTime = UG_sSystemControllers.sMotorPara.s32RestartShortTime;

		
}

void MDS_vOBPosObserverShortInit(MDS_S_POS_OBSERVER_SHORT_STRU *v)
{	
	v->s16Ialphabeta[0]	=	0;	
	v->s16Ialphabeta[1]	=	0;	
	v->s16Ualphabeta[0]	=	0;	
	v->s16Ualphabeta[1]	=	0;	
	v->s16Idq[0]				=	0;
	v->s16Idq[1]				=	0;		
	v->s16IdqPre[0]			=	0;	
	v->s16IdqPre[1]			=	0;		
	v->s16Udq[0]				=	0;	
	v->s16Udq[1]				=	0;	
	v->s16UdqPre[0]			=	0;	
	v->s16UdqPre[1]			=	0;
	v->s16ThetaEst			=	0;
  v->s16SpeedEst			=	0;
	v->s16SpeedEst			= 0;
  v->s16GainQErr			=	OB_IQGAIN_Q_SHORT;
  v->s16GainDErr			=	OB_IQGAIN_D_SHORT;
	v->s16SpeedFirst		=	0;
	v->s16SpeedInst			= 0;
	v->s16SpeedFirstPre	=	0;
	v->s16PLLInputGain	=	OB_IQTSPLL_SHORT;
	v->s16TsDivLq				= OB_IQTS_DIV_LQ_SHORT;
	v->s16TsRDivLq			=	OB_IQTS_R_DIV_LQ_SHORT;
	v->s16TsLdDivLq			=	OB_IQTS_LD_DIV_LQ_SHORT;
	v->s16TsPsiDivLq		=	OB_IQTS_PSI_DIV_LQ_SHORT;
	v->s16TsDivLd				= OB_IQTS_DIV_LD_SHORT;
	v->s16TsRDivLd			=	OB_IQTS_R_DIV_LD_SHORT;
	v->s16TsLqDivLd			=	OB_IQTS_LQ_DIV_LD_SHORT;
	v->s16LdPU 					= _IQ(UPDS_LDP);
  v->s16LqPU 					= _IQ(UPDS_LQP);	
	v->s16CompTime			= OB_COMP_TIME_SHORT;	
	v->s32RestartShortTime = UPDS_SHORTTIMEIQ;
		
}

void MDS_vIPDInit(UGT_S_IPD_STRU *v)
{
	v->eState 				= UGT_E_PULSE_FIRST;   	
	v->eStatePre  		= UGT_E_PULSE_FIRST;	
	v->s16Idc[0]  		= 0;   
	v->s16Idc[1]  		= 0;  
	v->s16Idc[2]  		= 0;  
	v->s16Idc[3]  		= 0;  
	v->s16Idc[4]  		= 0;  
	v->s16Idc[5]  		= 0;  	
	v->s16IdcMax			= 0;
	v->u8IdcMaxNum		= 0;
	v->u16Index				= 0; 
	v->s32InitPos 		= 0;
	v->u8PulseNum			= UG_sSystemControllers.sMotorPara.u8IPDPulseCountTotal;//UPDS_IPD_PULSE_CNT;
	v->u8IntervalNum 	= UG_sSystemControllers.sMotorPara.u8IPDIntervalCountTotal;//UPDS_IPD_INTERVAL_CNT;
	v->u8En						= UG_sSysStateErr.uControlReg.Bits.IPDEn;
	v->u8IPDFinish		= 0;
	v->u8MotorDirection = UG_sSysStateErr.uControlReg.Bits.MotorDirection;//UPDS_MOTOR_DIRECTION;
}

void MDS_vMotorParaReadFromFlash(UGT_S_MOTORPARAMETERS_STRU *v, u16 *w)
{
	v->sControlWord.All 	= (*(volatile u16 *)(w+0));
	v->f32Rs 							= (*(volatile u16 *)(w+1))/1000.0;
	v->f32Ld 							= (*(volatile u16 *)(w+2))/1000000.0;
	v->f32Lq 							= (*(volatile u16 *)(w+3))/1000000.0;	
	if(v->sControlWord.Bits.LowOrHighVoltage == 0)
	{
		v->f32PsiPM 				= (*(volatile u16 *)(w+4))/1000000.0;
	}
	else
	{
		v->f32PsiPM 				= (*(volatile u16 *)(w+4))/1000.0;
	}
	v->PolePairs 					= (*(volatile u16 *)(w+5));
	v->f32J								= (*(volatile u16 *)(w+6))/1000000.0;
	v->f32RatedCurrent 		= (*(volatile u16 *)(w+7))/1000.0;
	v->f32RatedSpeed   		= (*(volatile u16 *)(w+8))*10;	
	v->f32Rsp							= (*(volatile u16 *)(w+9))/1000.0;
	v->f32GainRsp					= (*(volatile u16 *)(w+10))/1000.0;
	v->f32GainVdc					= (*(volatile u16 *)(w+11))/100000.0;
	v->f32Rsdc						= (*(volatile u16 *)(w+12))/1000.0;
	v->f32GainRsdc				= (*(volatile u16 *)(w+13))/1000.0;
	v->f32Udc							= (*(volatile u16 *)(w+14))/10.0;
	v->u16DeadtimeNs			= (*(volatile u16 *)(w+15));	
	v->f32AccRate					= (*(volatile u16 *)(w+16))/10.0;
	v->f32StartCurPU			= (*(volatile u16 *)(w+17))/1000.0;
	v->u16PWMFre2					= (*(volatile u16 *)(w+18));
	v->f32BandWidth				= (*(volatile u16 *)(w+19));
	v->f32SpdKp						= (*(volatile u16 *)(w+20))/1000.0;
	v->f32SpdKi						= (*(volatile u16 *)(w+21))/10.0;
	v->f32SpeedPowerLimit = (*(volatile u16 *)(w+22));
	v->f32PowerKp					= (*(volatile u16 *)(w+23))/1000.0;
	v->f32PowerKi					= (*(volatile u16 *)(w+24))/10.0;
	v->f32FluxWeakenKp				= (*(volatile u16 *)(w+25))/1000.0;
	v->f32FluxWeakenKi				= (*(volatile u16 *)(w+26))/10.0;
	v->f32FluxWeakenOutMax		= (*(volatile u16 *)(w+27))/1000.0;
	v->f32ObsGainQ						= (*(volatile u16 *)(w+28))/10000.0;
	v->f32ObsGainD						= (*(volatile u16 *)(w+29))/10000.0;
	v->f32IPDPulseTime    		= (*(volatile u16 *)(w+30));	
	v->f32IPDIntervalTime    	= (*(volatile u16 *)(w+31))/1000.0;	
	v->f32SoftRestartPulse 		= (*(volatile u16 *)(w+32));	
	v->f32SoftRestartInterval = (*(volatile u16 *)(w+33));				
	v->f32HardOverCurrent			= (*(volatile u16 *)(w+34))/1000.0;
	v->f32SoftOverCurrent			= (*(volatile u16 *)(w+35))/1000.0;
	v->f32SoftOCJudgeTime 		= (*(volatile u16 *)(w+36))/10.0;
	v->f32OverVoltage					= (*(volatile u16 *)(w+37))/10.0;
	v->f32OVJudgeTime					= (*(volatile u16 *)(w+38));
	v->f32UnderVoltage				= (*(volatile u16 *)(w+39))/10.0;
	v->f32UVJudgeTime					= (*(volatile u16 *)(w+40));
	v->s16OverMotorTemp				= (*(volatile u16 *)(w+41));
	v->u16MotorOTJudgeTime		= (*(volatile u16 *)(w+42));	
	v->s16IPMOverTemp					= (*(volatile u16 *)(w+43));
	v->u16IPMOTJudgeTime  		= (*(volatile u16 *)(w+44));
	v->f32StartUpMinSpeed 		= (*(volatile u16 *)(w+45));
	v->f32SUMSJudgeTime				= (*(volatile u16 *)(w+46))/10.0;
	v->f32RestartWaitTime 		= (*(volatile u16 *)(w+47))/10.0;
	v->u16StartUpTimes 				= (*(volatile u16 *)(w+48));
	
	if(v->sControlWord.Bits.LowOrHighVoltage == 0)
	{
		if(v->u16DeadtimeNs<200)v->u16DeadtimeNs=200;
		else if(v->u16DeadtimeNs>4000)v->u16DeadtimeNs=4000;
	}
	else
	{
		if(v->u16DeadtimeNs<1000)v->u16DeadtimeNs=1000;
		else if(v->u16DeadtimeNs>5000)v->u16DeadtimeNs=5000;
	}	
		
	if(v->sControlWord.Bits.PWMFreqSwitchingEn == 1)	
	{
			v->u16PWMFre1 = v->u16PWMFre2>>1;
	}
	else 
	{
			v->u16PWMFre1 = v->u16PWMFre2;
	}
	
}

void MDS_vMotorParaReadFromHfile(UGT_S_MOTORPARAMETERS_STRU *v)
{
		UG_sSysStateErr.uControlReg.Bits.MotorDirection							= UPDS_MOTOR_DIRECTION;
		UG_sSysStateErr.uControlReg.Bits.LowOrHighVoltage					  = UPDS_MOTOR_VOLTAGE;
		UG_sSysStateErr.uControlReg.Bits.LowOrHighSpeed							= UPDS_MOTOR_SPEED;
		UG_sSysStateErr.uControlReg.Bits.SevenOrFivePWMSwitchingEn	= UPDS_5_7STAGE_SWITCHING_SEL;
		UG_sSysStateErr.uControlReg.Bits.PWMFreqSwitchingEn					= UPDS_UPDS_PWM_SWITCHING_SEL;	
		UG_sSysStateErr.uControlReg.Bits.IPDEn											= UPDS_IPD_SEL;
		UG_sSysStateErr.uControlReg.Bits.ControlMode 								= UPDS_CONTROL_MODE;
		UG_sSysStateErr.uControlReg.Bits.ChipType										= UPDS_CHIP_TYPE_SEL;
		UG_sSysStateErr.uControlReg.Bits.FlyingRestartMethod				= UPDS_RESTART_METHOD;
		UG_sSysStateErr.uControlReg.Bits.CommandType                = UPDS_COMMAND_TYPE;	
		UG_sSysStateErr.uControlReg.Bits.ConstCurrent               = UPDS_CONCURRENT_SEL;	
	
	
		v->f32Rs 		 				= UPDS_RS_REAL;//+UPDS_SAMPLE_CURR_R_REAL;//+UPDS_SAMPLE_DCBUS_R_REAL+;
		v->f32Ld		 				= UPDS_LD_REAL;
		v->f32Lq		 				= UPDS_LQ_REAL;
		v->f32PsiPM  				= UPDS_PSI_REAL;
		v->PolePairs 				= UPDS_PAIRS;
		v->f32J			 				= UPDS_MOTOR_J;
		v->f32RatedCurrent 	= UPDS_RATED_CURRENT;
		v->f32RatedSpeed    = UPDS_RATED_SPEED;
		
		v->f32Rsp					  = UPDS_SAMPLE_CURR_R_REAL;
		v->f32GainRsp			  = UPDS_SAMPLE_CURR_OP_REAL;
		v->f32GainVdc			  = UPDS_SAMPLE_VOLT_OP_GAIN;
		v->f32Rsdc				  = UPDS_SAMPLE_DCBUS_R_REAL;
		v->f32GainRsdc		  = UPDS_SAMPLE_DCBUS_OP_REAL;
		v->f32Udc						= UPDS_UDC_REAL;
		v->u16DeadtimeNs		= UPDS_DEADTIME_NS;
		
		v->f32AccRate				= UPDS_COMMAND_TIME_IQ1_S;
		v->f32StartCurPU		= UPDS_INJECT_D_CURRENT_A_PU;
		if(UG_sSysStateErr.uControlReg.Bits.PWMFreqSwitchingEn == 1)	
		{
			v->u16PWMFre1 = UPDS_PWM_FREQ;
		}
		else 
		{
			v->u16PWMFre1 = UPDS_PWM_FREQ2;
		}
		v->u16PWMFre2       = UPDS_PWM_FREQ2;			
		
		v->f32BandWidth     = UPDS_CURRENT_LOOP_BW_HZ;
		
		v->f32SpdKp					= UPSD_PI_SPEED_KP;
		v->f32SpdKi					= UPSD_PI_SPEED_KI;
		v->f32SpeedPowerLimit 		= UPSD_POWER_MAX;
		v->f32SoftRestartPulse 		= UPDS_SHORTTIME_US;
		v->f32SoftRestartInterval = UPDS_INTERVAL_US;
		v->f32IPDPulseTime  = UPDS_IPD_PULSE_US;
		v->f32IPDIntervalTime 		= UPDS_IPD_INTERVAL_US;
		v->f32PowerKp				= UPDS_CP_KP;
		v->f32PowerKi				= UPDS_CP_KI;
		v->f32FluxWeakenKp	= UPDS_FW_KP;
		v->f32FluxWeakenKi	= UPDS_FW_KI;
		v->f32FluxWeakenOutMax = UPDS_FW_IDREF_MAX;
		v->f32ObsGainD			= UPDS_OBS_GAIN_D;
		v->f32ObsGainQ			= UPDS_OBS_GAIN_Q;	
		
		v->f32HardOverCurrent = UPDS_HARDOVERCURRENT_A;
		v->f32SoftOverCurrent = UPDS_OVERCURRENT_A;
		v->f32SoftOCJudgeTime = UPDS_OVERCURRENT_A_TIME_MS;
		v->f32OverVoltage			=	UPDS_OVERVOLTAGE_V;
		v->f32OVJudgeTime			= UPDS_OVERVOLTAGE_V_TIME_MS;
		v->f32UnderVoltage   	= UPDS_UNDERVOLTAGE_V;
		v->f32UVJudgeTime     = UPDS_UNDERVOLTAGE_V_TIME_MS;
		v->s16OverMotorTemp  	= UPDS_MOTOROVERTEMPERATURE_DEGREE;
		v->u16MotorOTJudgeTime= UPDS_MOTOROVERTEMPERATURE_TIME_S;
		v->s16IPMOverTemp     = UPDS_IGBTOVERTEMPERATURE_DEGREE;
		v->u16IPMOTJudgeTime  = UPDS_IGBTOVERTEMPERATURE_TIME_S;	
		v->f32StartUpMinSpeed = UPDS_STARTUP_FAIL_SPEED;
		v->f32SUMSJudgeTime   = UPDS_STARTUP_FAIL_TIME_S;
		v->f32RestartWaitTime = UPDS_RE_STARTUP_TIME_S;
		v->u16StartUpTimes    = UPDS_STARTUP_FAIL_MAX;		
}

void MDS_vMotorParaCalc(UGT_S_MOTORPARAMETERS_STRU *v)
{
	v->u16PWMPerood1 = ((u16) (UPDS_CKTIM / (u32)(2 * v->u16PWMFre1 *(UP_PWM_PRSC+1))));
	v->u16PWMPerood2 = ((u16) (UPDS_CKTIM / (u32)(2 * v->u16PWMFre2 *(UP_PWM_PRSC+1))));	
	v->u16fB    = v->f32RatedSpeed*v->PolePairs/60.0;
	v->f32UB 		= (v->f32Udc / UPDS_SQRT3);
	v->f32IB 		= (UPDS_SAMPLE_AD_MAX / 2.0 / v->f32Rsp / v->f32GainRsp);
	v->f32RB 		= v->f32UB/v->f32IB;
	v->f32WB 		= (UPDS_2PI * v->u16fB);
	v->f32LB 		= v->f32RB/v->f32WB;
	v->f32TB 		= 1.0f/v->f32WB;
	v->f32PsiB 	= v->f32UB/v->f32WB;
	#if (UPDS_POWER_CONTROL_SEL == UPDS_POWER_CONTROL_SOFTWARE)	
	v->f32PowerB = 	 v->f32UB * v->f32IB;
	#elif (UPDS_POWER_CONTROL_SEL == UPDS_POWER_CONTROL_HARDWARE)
	v->f32PowerB = 	(UPDS_SAMPLE_AD_MAX/UG_sSystemControllers.sMotorPara.f32GainVdc)*(UPDS_SAMPLE_AD_MAX/(2.0*UG_sSystemControllers.sMotorPara.f32GainRsdc*UG_sSystemControllers.sMotorPara.f32Rsdc));
	#endif	
	
	v->f32RsP 	= v->f32Rs/v->f32RB;
	v->f32LdP 	= v->f32Ld/v->f32LB;
	v->f32LqP 	= v->f32Lq/v->f32LB;
	v->f32PsiP 	= v->f32PsiPM / v->f32PsiB;
	v->f32TsCurrentPI1 	= 1.0/v->u16PWMFre1;
	v->f32TsCurrentPI2 	= 1.0/v->u16PWMFre2;
	v->f32TsP1 					= v->f32TsCurrentPI1/v->f32TB;
	v->f32TsP2 					= v->f32TsCurrentPI2/v->f32TB;
	v->f32StartCurPU		= v->f32StartCurPU*v->f32RatedCurrent/v->f32IB ;	

	v->s32RsPU    = _IQ(v->f32RsP);
	v->s32LdPU		= _IQ(v->f32LdP);
	v->s32LqPU    = _IQ(v->f32LqP);
	v->s32PsiPU		= _IQ(v->f32PsiP);
	v->s32TsPU1   = _IQ(v->f32TsP1);	
	v->s32TsPU2   = _IQ(v->f32TsP2);
	v->s32StartCurPU		= _IQ(v->f32StartCurPU);
	if(v->s32StartCurPU > _IQ(0.5))			v->s32StartCurPU=_IQ(0.5);
	else if(v->s32StartCurPU < _IQ(0))	v->s32StartCurPU=_IQ(0);	
	
	v->u16DeadtimeComp2 = (s16)((v->u16DeadtimeNs)*v->u16PWMPerood2/30518);
	v->u16DeadtimeComp1 = (s16)((v->u16DeadtimeNs)*v->u16PWMPerood1/30518);	
	
	
	v->s32OCJudgeTimeTotal = v->f32SoftOCJudgeTime*UPDS_ERROR_EMERGENCY/1000;
	v->s32OVJudgeTimeTotal = v->f32OVJudgeTime*UPDS_ERROR_EMERGENCY/1000;
	v->s32UVJudgeTimeTotal = v->f32UVJudgeTime*UPDS_ERROR_EMERGENCY/1000;

	v->s32MotorOTJudgeTimeTotal	= v->u16MotorOTJudgeTime*UPDS_ERROR_NOT_EMERGENCY;
	v->s32IPMOTJudgeTimeTotal		= v->u16IPMOTJudgeTime*UPDS_ERROR_NOT_EMERGENCY;	
	v->s32SUMSJudgeTimeTotal 		= v->f32SUMSJudgeTime*UPDS_ERROR_NOT_EMERGENCY;
	v->s32RestartWaitTimeTotal  = v->f32RestartWaitTime*UPDS_ERROR_NOT_EMERGENCY;
	v->s32StartUpMinSpeed 			= _IQ(v->f32StartUpMinSpeed*v->PolePairs/60.0/v->u16fB);

	v->s32NoWaterGain						=	UPDS_IQDIVSPD_GAIN*0x7FFF;
	v->s32NoWaterJudgeTimeTotal	=	UPDS_NOWATER_JUDGETIME;

	v->s32SpdPIOutMax 					= _IQ(v->f32RatedCurrent / v->f32IB);
	v->s32SpdPIOutMin						= -v->s32SpdPIOutMax;
	v->s16OverCurrent 					= (s16)(v->f32SoftOverCurrent / v->f32IB * S16_MAX);
	v->s16OverVoltage 					= (s16)(v->f32OverVoltage / v->f32Udc * UPDS_SQRT3 * 0x1000);
	v->s16UnderVoltage 					= (s16)(v->f32UnderVoltage / v->f32Udc * UPDS_SQRT3 * 0x1000);	
	v->s16UnderVoltageFlashWrite 		= v->s16UnderVoltage>>1;
	v->u8IPDPulseCountTotal			= v->f32IPDPulseTime*v->u16PWMFre1*0.000001;
	v->u8IPDIntervalCountTotal	= v->f32IPDIntervalTime*v->u16PWMFre1*0.000001;

	v->u8SoftRestartPulseCountTotal    = v->f32SoftRestartPulse*v->u16PWMFre1*0.000001;
	v->u8SoftRestartIntervalCountTotal = v->f32SoftRestartInterval*v->u16PWMFre1*0.000001;
  MDS_vCurrentControllerCalc(v);
	
}

void MDS_vTIMInit(void)
{
	TIM1->ARR = UG_sSystemControllers.sMotorPara.u16PWMPerood1;
	UG_sVoltageAll.sPwmDuty.u16HalfPerMax 		= UG_sSystemControllers.sMotorPara.u16PWMPerood1>>1;
	UG_sVoltageAll.sPwmDuty.u16PeriodMax 			= UG_sSystemControllers.sMotorPara.u16PWMPerood1;
	UG_sVoltageAll.sDeadTimeComp.s16DTComp   	= UG_sSystemControllers.sMotorPara.u16DeadtimeComp1;
}

void MDS_vCurLimitInit(UGT_S_CURRENT_LIMIT_STRU *v)
{
	v->s32SpdFbkWL = UPDS_CUR_LIMLT_SPD_WL;
	v->s32SpdFbkWH = UPDS_CUR_LIMLT_SPD_WH;
	v->s32CurLimitMin   = UPDS_CUR_LIMLT_MIN;
	v->s32CurLimitSlope = (((s64)_IQ(1)-v->s32CurLimitMin)<<24)/(v->s32SpdFbkWH - v->s32SpdFbkWL);
	v->u8CurLimitEn			= UPDS_CUR_LIMLT_EN_SEL;
	if(v->s32CurLimitSlope<_IQ(1.0))v->s32CurLimitSlope=_IQ(1.0);
	else if(v->s32CurLimitSlope>_IQ(10.0))v->s32CurLimitSlope=_IQ(10.0);
	v->s32CurLimitGain = _IQ(1.0);
}



