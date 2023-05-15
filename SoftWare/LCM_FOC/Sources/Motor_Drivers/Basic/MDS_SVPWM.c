
#define EXPORT_MDS_SVPWM_H
	#include "MDS_SVPWM.h"
#undef EXPORT_MDS_SVPWM_H

//__attribute__((section("RAMCODE")))
void MDS_vFOC(void)
{
	s32 temp;
	#if (UPDS_CUR_IQ == UPDS_CUR_IQ24)
	UG_sSystemControllers.sID.s32Ref = UG_sSystemControllers.sCommandAll.s32IdCommand + MDS_sFW.PI_FW.s32Out;
	UG_sSystemControllers.sID.s32Fbk = UG_sSystemControllers.sCommandAll.s32IdUse;
	MDS_vPIRegulatorIQ24(&UG_sSystemControllers.sID);
	
	UG_sSystemControllers.sIQ.s32Ref = UG_sSystemControllers.sCommandAll.s32IqCommand;
	UG_sSystemControllers.sIQ.s32Fbk = UG_sSystemControllers.sCommandAll.s32IqUse;
	MDS_vPIRegulatorIQ24(&UG_sSystemControllers.sIQ);
	
	UG_sVoltageAll.sVoltageDqUse.s16Dr = UG_sSystemControllers.sID.s32Out >> 9;
	UG_sVoltageAll.sVoltageDqUse.s16Qr = UG_sSystemControllers.sIQ.s32Out >> 9;
	#elif (UPDS_CUR_IQ == UPDS_CUR_IQ12)
	UG_sSystemControllers.sID12.s16Ref = UG_sSystemControllers.sCommandAll.s32IdCommand>>10;
	UG_sSystemControllers.sID12.s16Fbk = UG_sSystemControllers.sCommandAll.s32IdUse>>10;
	MDS_vPIRegulatorIQ12(&UG_sSystemControllers.sID12);
	
	UG_sSystemControllers.sIQ12.s16Ref = UG_sSystemControllers.sCommandAll.s32IqCommand>>10;
	UG_sSystemControllers.sIQ12.s16Fbk = UG_sSystemControllers.sCommandAll.s32IqUse>>10;
	MDS_vPIRegulatorIQ12(&UG_sSystemControllers.sIQ12);
	
	UG_sVoltageAll.sVoltageDqUse.s16Dr = UG_sSystemControllers.sID12.s16Out << 1;
	UG_sVoltageAll.sVoltageDqUse.s16Qr = UG_sSystemControllers.sIQ12.s16Out << 1;	
	#endif
	
	if(UG_sSysStateErr.sSoftClose.u8SoftCloseEn == FALSE)
	{
		UG_sVoltageAll.sVoltageDqUse.s16Dr = ((s32)UG_sVoltageAll.sVoltageDqUse.s16Dr * UG_sVoltageAll.sVoltageAbc.s16UdcFluctuateGain) >>12;
		UG_sVoltageAll.sVoltageDqUse.s16Qr = ((s32)UG_sVoltageAll.sVoltageDqUse.s16Qr * UG_sVoltageAll.sVoltageAbc.s16UdcFluctuateGain) >>12;
		if (UG_sVoltageAll.sVoltageDqUse.s16Dr > _IQ15(0.95)) 		UG_sVoltageAll.sVoltageDqUse.s16Dr 		= _IQ15(0.95);
		else if (UG_sVoltageAll.sVoltageDqUse.s16Dr < _IQ15(-0.95)) UG_sVoltageAll.sVoltageDqUse.s16Dr 	= _IQ15(-0.95);
		if (UG_sVoltageAll.sVoltageDqUse.s16Qr > _IQ15(0.95)) 		UG_sVoltageAll.sVoltageDqUse.s16Qr 		= _IQ15(0.95);
		else if (UG_sVoltageAll.sVoltageDqUse.s16Qr < _IQ15(-0.95)) UG_sVoltageAll.sVoltageDqUse.s16Qr 	= _IQ15(-0.95);		
	}
 
	if(UG_sSysStateErr.uControlReg.Bits.ControlMode == UGT_E_CM_VF)
	{	
		UG_sVoltageAll.sVoltageDqUse.s16Dr = _IQ(0.0)>>9;
  	UG_sVoltageAll.sVoltageDqUse.s16Qr = _IQ(0.15)>>9;	
	}
	MDS_vVoltRevParkCircleLimit(&UG_sVoltageAll.sVoltageDqUse);
	if(UG_sSysStateErr.sSystemState>=UGT_E_SS_CLOSEDLOOP_J)	
	{
	#if (UPDS_CUR_IQ == UPDS_CUR_IQ24)			
	temp = MDS_sPosObserver.s32ThetaEst + _IQmpy(MDS_sPosObserver.s32SpeedEst,MDS_sPosObserver.s32CompTime);
	if (temp >= 0x02000000)		temp -= 0x02000000;						
	else if (temp < 0)	temp += 0x02000000;		
	UG_sPositionAll.u16PosUseComp = temp>>9;
	#elif (UPDS_CUR_IQ == UPDS_CUR_IQ12)
	temp = MDS_sPosObserverShort.s16ThetaEst + ((s32)MDS_sPosObserverShort.s16SpeedEst*MDS_sPosObserverShort.s16CompTime>>OB_SHORT_SHIFT);
	if (temp >= 32768)		temp -= 32768;						
	else if (temp < 0)	temp += 32768;		
	UG_sPositionAll.u16PosUseComp = temp<<1;
	#endif	
	}
	else
	{
		UG_sPositionAll.u16PosUseComp =UG_sPositionAll.u16PosUse;
	}
  MDS_vTrigFunctions(&UG_sPositionAll.sSinCosUseComp, UG_sPositionAll.u16PosUseComp);
	UG_sVoltageAll.sVoltageAlphaBetaUse.s16Alpha = _IQ15mpyIQ12(UG_sVoltageAll.sVoltageDqUse.s16Dr, UG_sPositionAll.sSinCosUseComp.s16Cos) - _IQ15mpyIQ12(UG_sVoltageAll.sVoltageDqUse.s16Qr, UG_sPositionAll.sSinCosUseComp.s16Sin);
	UG_sVoltageAll.sVoltageAlphaBetaUse.s16Beta  = _IQ15mpyIQ12(UG_sVoltageAll.sVoltageDqUse.s16Dr, UG_sPositionAll.sSinCosUseComp.s16Sin) + _IQ15mpyIQ12(UG_sVoltageAll.sVoltageDqUse.s16Qr, UG_sPositionAll.sSinCosUseComp.s16Cos);
	
	
	UG_sVoltageAll.sSvgen.s16Ualpha = UG_sVoltageAll.sVoltageAlphaBetaUse.s16Alpha;
	UG_sVoltageAll.sSvgen.s16Ubeta  = UG_sVoltageAll.sVoltageAlphaBetaUse.s16Beta;
	
	MDS_vSVPWM(&UG_sVoltageAll.sSvgen);

	UG_sVoltageAll.sDeadTimeComp.s32DTMfunC1 = UG_sVoltageAll.sSvgen.s32Ta;
	UG_sVoltageAll.sDeadTimeComp.s32DTMfunC2 = UG_sVoltageAll.sSvgen.s32Tb;
	UG_sVoltageAll.sDeadTimeComp.s32DTMfunC3 = UG_sVoltageAll.sSvgen.s32Tc;
	
	MDS_vDeadTimeComp(&UG_sVoltageAll.sDeadTimeComp, &UG_sCurrentAll.sCurrentAbc,UG_sCurrentAll.sCurrentDqUse.s16Qr);
	
	UG_sVoltageAll.sPwmDuty.s32MfuncC1 = UG_sVoltageAll.sDeadTimeComp.s32DTMfunC1;
  UG_sVoltageAll.sPwmDuty.s32MfuncC2 = UG_sVoltageAll.sDeadTimeComp.s32DTMfunC2;
	UG_sVoltageAll.sPwmDuty.s32MfuncC3 = UG_sVoltageAll.sDeadTimeComp.s32DTMfunC3;	
	
	MDS_vPWMUpdate(&UG_sVoltageAll.sPwmDuty, &UG_sCurrentAll.sCurrentAbc.u16SampleChooseNum);
	
	UG_sVoltageAll.sVoltageAbc.s16MfuncV1 = UG_sVoltageAll.sPwmDuty.s32MfuncC1;
	UG_sVoltageAll.sVoltageAbc.s16MfuncV2 = UG_sVoltageAll.sPwmDuty.s32MfuncC2;
	UG_sVoltageAll.sVoltageAbc.s16MfuncV3 = UG_sVoltageAll.sPwmDuty.s32MfuncC3;
	

}

//__attribute__((section("RAMCODE")))
void MDS_vPWMUpdate(UGT_S_PWMDUTY_STRU *PWM_Duty_Input, vu16 *CurrSampleMode)
{
	vu16 u16SampleMode = 0;
		
	if(UG_sSysStateErr.uControlReg.Bits.MotorDirection == UPDS_POSITIVE_DIRECTION)
	{		
		TIM1->CCR1 = UG_sVoltageAll.sPwmDuty.u16HalfPerMax -((UG_sVoltageAll.sPwmDuty.u16HalfPerMax*UG_sVoltageAll.sPwmDuty.s32MfuncC1)>>15);
		TIM1->CCR2 = UG_sVoltageAll.sPwmDuty.u16HalfPerMax -((UG_sVoltageAll.sPwmDuty.u16HalfPerMax*UG_sVoltageAll.sPwmDuty.s32MfuncC2)>>15);
		TIM1->CCR3 = UG_sVoltageAll.sPwmDuty.u16HalfPerMax -((UG_sVoltageAll.sPwmDuty.u16HalfPerMax*UG_sVoltageAll.sPwmDuty.s32MfuncC3)>>15);
		UG_sCurrentAll.sCurrentAbc.u16SampleChooseNum = UA_SAMPLE_A_B_NC;//u16SampleMode;//
	}
	else if(UG_sSysStateErr.uControlReg.Bits.MotorDirection == UPDS_NEGATIVE_DIRECTION)	
	{
		TIM1->CCR3 = UG_sVoltageAll.sPwmDuty.u16HalfPerMax -((UG_sVoltageAll.sPwmDuty.u16HalfPerMax*UG_sVoltageAll.sPwmDuty.s32MfuncC1)>>15);
		TIM1->CCR2 = UG_sVoltageAll.sPwmDuty.u16HalfPerMax -((UG_sVoltageAll.sPwmDuty.u16HalfPerMax*UG_sVoltageAll.sPwmDuty.s32MfuncC2)>>15);
		TIM1->CCR1 = UG_sVoltageAll.sPwmDuty.u16HalfPerMax -((UG_sVoltageAll.sPwmDuty.u16HalfPerMax*UG_sVoltageAll.sPwmDuty.s32MfuncC3)>>15);	
		UG_sCurrentAll.sCurrentAbc.u16SampleChooseNum = UA_SAMPLE_NA_B_C;//u16SampleMode;//
	}
}



