#define EXPORT_MDS_MOTORCONTROL_H
	#include "MDS_MotorControl.h"
#undef EXPORT_MDS_MOTORCONTROL_H

/********************************************************************************************
  * @brief      MotorControlFSM.    
********************************************************************************************/
void MDS_vMotorControlState(void)
{
  switch(UG_sSysStateErr.sSystemState)
  {
    case UGT_E_SS_IDLE_A: 					while(MDS_vIdle   		() == 0);	    break;
    case UGT_E_SS_INIT_B:   				while(MDS_vInit     	() == 0);	  	break;
    case UGT_E_SS_STOP_C:    				break;
    case UGT_E_SS_START_D:  				while(MDS_vStart			() == 0); 		break;
		case UGT_E_SS_PRECHARGE_E: 	 		break;
    case UGT_E_SS_TRACK_F: 			 		break;
    case UGT_E_SS_IDENTIFY_G:     	break;	
    case UGT_E_SS_ALIGNMENT_H: 		  break;
		case UGT_E_SS_OPENLOOP_I: 	   	break;
    case UGT_E_SS_CLOSEDLOOP_J:	   	break;
		case UGT_E_SS_BRAKE_K:	 		   	break;
		case UGT_E_SS_FAULT_L:	 		   	break;
		case UGT_E_SS_WAIT_M:						break;	
		case UGT_E_SS_WRITE_FLASH:			while(MDS_vWriteFlash	() == 0); 		break;
    default:                        break;
  }
}

/********************************************************************************************
  * @brief      FSM_Init.
********************************************************************************************/
u8 MDS_vIdle(void)
{   
	UG_sSysStateErr.sSystemStatePre = UG_sSysStateErr.sSystemState;
	UG_sSysStateErr.sSystemState 		= UGT_E_SS_INIT_B;	
  return 1;
}


/********************************************************************************************
  * @brief      FSM_Init.
********************************************************************************************/
u8 MDS_vInit(void)
{   
	US_vSystParaInit();
	UG_sSysStateErr.sSystemStatePre = UG_sSysStateErr.sSystemState;
	UG_sSysStateErr.sSystemState 		= UGT_E_SS_STOP_C;	
	
	return 1;
}

/********************************************************************************************
  * @brief      FSM_Stop.
********************************************************************************************/
u8 MDS_vStop(void)
{  
	SVPWM_TIM1_PWM_DISABLE_MACRO;
	if(UA_u8CurrSampleOffest(&UG_sADSampleAll, &UG_sCurrentAll.sCurrentAbc, &UG_sVoltageAll.sVoltageAbc)==TRUE)
	{
		UG_sSysStateErr.sSystemStatePre = UG_sSysStateErr.sSystemState;	
		UG_sSysStateErr.sSystemState 		= UGT_E_SS_START_D;
	}
	
	return 1;
}

/********************************************************************************************
  * @brief      FSM_Prepare.
********************************************************************************************/
u8 MDS_vStart(void)
{ 
	GPIO_InitTypeDef GPIO_InitStructure;
	if(UG_sSysStateErr.uControlReg.Bits.ControlMode != UGT_E_CM_TEST)
	{	
		if ((UG_sSysStateErr.sVSPCheck == UGT_E_VSP_OPEN_B)&&(UG_sVoltageAll.sVoltageAbc.s16UdcMeas > (UG_sSystemControllers.sMotorPara.s16UnderVoltage))&&(UG_sVoltageAll.sVoltageAbc.s16UdcMeas < (UG_sSystemControllers.sMotorPara.s16OverVoltage)))
		{			
			UG_sSysStateErr.sSystemStatePre = UG_sSysStateErr.sSystemState;
			UG_sSysStateErr.sSystemState = UGT_E_SS_TRACK_F;
			SVPWM_TIM1_PWM_DISABLE_MACRO
			#if (UPDS_CUR_IQ == UPDS_CUR_IQ24)
			{		
				UG_sSystemControllers.sID.u16En		=	0;
				UG_sSystemControllers.sIQ.u16En		=	0;
			}
			#elif (UPDS_CUR_IQ == UPDS_CUR_IQ12)
			{
				UG_sSystemControllers.sID12.u16En	=	0;
				UG_sSystemControllers.sIQ12.u16En	=	0;	
			}
			#endif
			UG_sSystemControllers.sSPD.u16En	=	0;	
			MDS_sCP.PI_CP.u16En 							= 0;
			TIM1->CCER |=(0x0111<<2);
			TIM1->CCER &=~(0x0111);
	//		TIM1->CCER |=(0x0888);//CC1NP:改为低电平有效
			TIM1->CCER &=(~0x0888); //CC1NP:改为低电平有效
			UG_sVoltageAll.sPwmDuty.s32MfuncC1 = _IQ15(0.0);
			UG_sVoltageAll.sPwmDuty.s32MfuncC2 = _IQ15(0.0);
			UG_sVoltageAll.sPwmDuty.s32MfuncC3 = _IQ15(0.0);
			TIM1->CCR1 = UG_sVoltageAll.sPwmDuty.u16PeriodMax-((UG_sVoltageAll.sPwmDuty.u16PeriodMax*UG_sVoltageAll.sPwmDuty.s32MfuncC1)>>15);
			TIM1->CCR2 = UG_sVoltageAll.sPwmDuty.u16PeriodMax-((UG_sVoltageAll.sPwmDuty.u16PeriodMax*UG_sVoltageAll.sPwmDuty.s32MfuncC2)>>15);
			TIM1->CCR3 = UG_sVoltageAll.sPwmDuty.u16PeriodMax-((UG_sVoltageAll.sPwmDuty.u16PeriodMax*UG_sVoltageAll.sPwmDuty.s32MfuncC3)>>15);			
		}
	}	
	else
	{
			UG_sSysStateErr.sSystemStatePre = UG_sSysStateErr.sSystemState;
			UG_sSysStateErr.sSystemState = UGT_E_SS_IDENTIFY_G;
	}
	return 1;
}

/********************************************************************************************
  * @brief      FSM_Precharge.
********************************************************************************************/
u8 MDS_vPrecharge(void)
{ 	
}

/********************************************************************************************
  * @brief      FSM_Track.
********************************************************************************************/
u8 MDS_vTrack(void)
{   
	MDS_vCurrClarke(&UG_sCurrentAll.sCurrentAbc, &UG_sCurrentAll.sCurrentAlphaBeta);
	MDS_vOBRestarting(UG_sCurrentAll.sCurrentAlphaBeta.s16Alpha, UG_sCurrentAll.sCurrentAlphaBeta.s16Beta);	
  return 1;
}


/********************************************************************************************
  * @brief      FSM_Alignment.
********************************************************************************************/
u8 MDS_vIdentify(void)
{
	u8 u8ControlModePre;
	NVIC_InitTypeDef NVIC_InitStructure;
	if(UG_sSysStateErr.uControlReg.Bits.IPDEn == UPDS_IPD_DISABLE)
	{
		UG_sSysStateErr.u8IdentifySwitch = 1;
	}
	else if(UG_sSysStateErr.uControlReg.Bits.IPDEn == UPDS_IPD_ENABLE)	
	{
	  if(UG_sSysStateErr.sRestart.u8RestartDirect == 1)
		{
			TIM1->CCR1 = UG_sVoltageAll.sPwmDuty.u16PeriodMax;
			TIM1->CCR2 = UG_sVoltageAll.sPwmDuty.u16PeriodMax;
			TIM1->CCR3 = UG_sVoltageAll.sPwmDuty.u16PeriodMax;	
			UG_sIPDAll.u8IPDFinish = MDS_vInitPosDeter(&UG_sIPDAll, UG_sADSampleAll.s16IdcTem);
			if(UG_sIPDAll.u8IPDFinish == 1)
			{
				#if (UPDS_CUR_IQ == UPDS_CUR_IQ24)
				MDS_sPosObserver.s32ThetaEst 		 	= UG_sIPDAll.s32InitPos;
				UG_sPositionAll.PosStateObserver 	= UG_sIPDAll.s32InitPos>>9;					
				#elif (UPDS_CUR_IQ == UPDS_CUR_IQ12)
				MDS_sPosObserverShort.s16ThetaEst = UG_sIPDAll.s32InitPos>>10;//_IQ24->IQ14
				UG_sPositionAll.PosStateObserver  = UG_sIPDAll.s32InitPos>>9;				
				#endif
				TG_sThetaGen.s32Angle = UG_sIPDAll.s32InitPos>>9;
				UG_sSysStateErr.u8IdentifySwitch = 1;
			}		
		}
		else
		{
			UG_sSysStateErr.u8IdentifySwitch = 1;
	
		}
	}

		
	if(UG_sSysStateErr.u8IdentifySwitch == 1)
	{
		UG_sSysStateErr.u8IdentifySwitch=0;
		UG_sSysStateErr.sSystemStatePre = UG_sSysStateErr.sSystemState;
		u8ControlModePre=UG_sSysStateErr.uControlReg.Bits.ControlMode;
		if(UG_sSystemControllers.u8ExtraStart == 1)UG_sSysStateErr.uControlReg.Bits.ControlMode = UGT_E_CM_IF;
		switch(UG_sSysStateErr.uControlReg.Bits.ControlMode )
		{
			case UGT_E_CM_VF:
				#if (UPDS_CUR_IQ == UPDS_CUR_IQ24)
				UG_sSystemControllers.sID.u16En 	= FALSE;
				UG_sSystemControllers.sIQ.u16En 	= FALSE;		
				#elif (UPDS_CUR_IQ == UPDS_CUR_IQ12)
				UG_sSystemControllers.sID12.u16En = FALSE;
				UG_sSystemControllers.sIQ12.u16En = FALSE;	
				#endif	
				UG_sSystemControllers.sSPD.u16En 	= FALSE;
				MDS_sCP.PI_CP.u16En 							= FALSE;	
				UG_sSysStateErr.sSystemState = UGT_E_SS_OPENLOOP_I;				
				break;
			case UGT_E_CM_IF:
				#if (UPDS_CUR_IQ == UPDS_CUR_IQ24)
				UG_sSystemControllers.sID.u16En 	= TRUE;
				UG_sSystemControllers.sIQ.u16En 	= TRUE;		
				#elif (UPDS_CUR_IQ == UPDS_CUR_IQ12)
				UG_sSystemControllers.sID12.u16En = TRUE;
				UG_sSystemControllers.sIQ12.u16En = TRUE;	
				#endif
				if(UG_sSysStateErr.sRestart.u8RestartDirect == 1)
				{
					UG_sSysStateErr.sSystemState = UGT_E_SS_OPENLOOP_I;	
					UG_sSystemControllers.sSPD.u16En 	= FALSE;
					MDS_sCP.PI_CP.u16En 							= FALSE;	
				}					
				else 	
				{
					UG_sSysStateErr.sSystemState = UGT_E_SS_CLOSEDLOOP_J;	
					UG_sSystemControllers.sSPD.u16En 	= TRUE;
					MDS_sCP.PI_CP.u16En 							= TRUE;						
				}
			break;
			case UGT_E_CM_TORQUE:
				#if (UPDS_CUR_IQ == UPDS_CUR_IQ24)
				UG_sSystemControllers.sID.u16En 	= TRUE;
				UG_sSystemControllers.sIQ.u16En 	= TRUE;		
				#elif (UPDS_CUR_IQ == UPDS_CUR_IQ12)
				UG_sSystemControllers.sID12.u16En = TRUE;
				UG_sSystemControllers.sIQ12.u16En = TRUE;	
				#endif
				UG_sSystemControllers.sSPD.u16En 	= FALSE;
				MDS_sCP.PI_CP.u16En 							= FALSE;		
				UG_sSysStateErr.sSystemState = UGT_E_SS_CLOSEDLOOP_J;	
				break;
			case UGT_E_CM_SPEED:

			case UGT_E_CM_POWER:
				#if (UPDS_CUR_IQ == UPDS_CUR_IQ24)
				UG_sSystemControllers.sID.u16En 	= TRUE;
				UG_sSystemControllers.sIQ.u16En 	= TRUE;	
				#elif (UPDS_CUR_IQ == UPDS_CUR_IQ12)
				UG_sSystemControllers.sID12.u16En = TRUE;
				UG_sSystemControllers.sIQ12.u16En = TRUE;		
				#endif
				UG_sSystemControllers.sSPD.u16En 	= TRUE;
				MDS_sCP.PI_CP.u16En 							= TRUE;
			
				#if (UPDS_DCURRENT_CHOOSE == UPDS_DCURRENT_FW)			
				MDS_sFW.PI_FW.u16En								= TRUE;	
				#elif	(UPDS_DCURRENT_CHOOSE == UPDS_DCURRENT_MTPA)
				MDS_sMTPA.u16En										=	TRUE;
				#endif		
			
				if(UG_sSysStateErr.uControlReg.Bits.ConstCurrent == UPDS_CONCURRENT_ENABLE) 	MDS_vUdcSwitchCheck();
			
				UG_sSysStateErr.sSystemState = UGT_E_SS_CLOSEDLOOP_J;		
				break;
			case UGT_E_CM_TEST:
				UG_sSysStateErr.sSystemState = UGT_E_SS_CLOSEDLOOP_J;
				break;
			default: 
				break;				
		}	
		if(UG_sSystemControllers.u8ExtraStart == 1)
		{
			UG_sSysStateErr.uControlReg.Bits.ControlMode = u8ControlModePre;
			UG_sSystemControllers.u8ExtraStart = 0;			
		}

		SATRT_OFACMP1(); 													//only soft trigger need		
		TIM_ClearITPendingBit(TIM1, TIM_IT_Break);		
		TIM_ITConfig(TIM1, TIM_IT_Break,ENABLE);	//使能指定的TIM中断
		SVPWM_TIM1_PWM_ENABLE_MACRO;
		SVWPM_ABC_HIGH_ACTIVE;	
	}	
  return 1;
}


/********************************************************************************************
  * @brief      FSM_OpenLoop.
********************************************************************************************/
u8 MDS_vAlignment(void)
{  

  return 1;
}

/********************************************************************************************
  * @brief      FSM_OpenLoop.
********************************************************************************************/
u8 MDS_vOpenloop(void)
{  
	static u32 u32OpenLoopIndex = 0;
	static s16 s16PosErr=0x7FFF;
	
	TG_sThetaGen.s16Freq = _IQ15(0.1);//(s16)(UG_sSystemControllers.sCommandAll.s32SpdCommand >> 9);
	MDS_vThetaGen(&TG_sThetaGen);
	UG_sPositionAll.PosOpenLoop = TG_sThetaGen.u16AngleOut;		//270 Degrees
	UG_sPositionAll.u16PosUse = UG_sPositionAll.PosOpenLoop;
	
	s16PosErr = UG_sPositionAll.PosStateObserver - UG_sPositionAll.PosOpenLoop; 
	if(s16PosErr < -MDS_THETSAERR_160DEG)s16PosErr += 0xFFFF;
	else if(s16PosErr > MDS_THETSAERR_160DEG)s16PosErr -= 0xFFFF;
	
	switch (UG_sSysStateErr.sIFStartUp)
	{
		case UGT_E_IFSTARTUP_ACC_A:
			if (UG_sSystemControllers.sCommandAll.s32IqCommand < MDS_IQ_STARTUP_AMPL_IQ24)
			{
				UG_sSystemControllers.sCommandAll.s32IqCommand += MDS_IQ_ALIGNMENT_AMPL_STEP;	
			}		
			if(UG_sSystemControllers.sCommandAll.s32SpdCommand < MDS_SPD_STARTUP_FINA_IQ24)
			{
				UG_sSystemControllers.sCommandAll.s32SpdCommand += MDS_SPD_STARTUP_FINA_STEP;
			}
			else
			{
				UG_sSystemControllers.sCommandAll.s32SpdCommand = MDS_SPD_STARTUP_FINA_IQ24;
				if(UG_sSysStateErr.uControlReg.Bits.ControlMode != UGT_E_CM_VF)
				{	
					UG_sSysStateErr.sIFStartUp = UGT_E_IFSTARTUP_CLOSED_D;					
				}
			}
			break;
			
		case UGT_E_IFSTARTUP_CONTIUE_B:
//			if (u32OpenLoopIndex == MDS_SPD_FINA_TIME_COUNT)
//			{
////				UG_sSysStateErr.sIFStartUp = UGT_E_IFSTARTUP_SWITCH_C;
//				u32OpenLoopIndex = 0;
//			}
//			u32OpenLoopIndex++;		
			break;
			
		case UGT_E_IFSTARTUP_SWITCH_C:		
			UG_sSystemControllers.sCommandAll.s32IqCommand -= MDS_IQ_SWITCH_AMPL_STEP;
//			if((UG_sSystemControllers.sCommandAll.s32IqCommand < UPDS_IQ_SWITCH_MIN)||(s16PosErr < MDS_THETSAERR_SWITCH_MIN))
//			{
//				UG_sSysStateErr.sIFStartUp = UGT_E_IFSTARTUP_CLOSED_D;
////				GPIO_ResetBits(GPIOC,GPIO_Pin_13);
//			
//			}
//			else if(s16PosErr > MDS_THETSAERR_SWITCH_MAX)
//			{
////				UG_sSysStateErr.sSystemState = UGT_E_SS_FAULT_L; 				
//			}	
			if((UG_sSystemControllers.sCommandAll.s32IqCommand < MDS_IQ_SWITCH_MIN_IQ24))
			{
				UG_sSysStateErr.sIFStartUp = UGT_E_IFSTARTUP_CLOSED_D;			
			}
			break;
			
		case UGT_E_IFSTARTUP_CLOSED_D:	

			UG_sPositionAll.u16PosUse = UG_sPositionAll.PosStateObserver;	
			UG_sPositionAll.SpdUse = UG_sPositionAll.SpdStateObserver;
			UG_sSystemControllers.sID.s32i1 = UG_sVoltageAll.sVoltageDqCalc.s16Dr << 9;
			UG_sSystemControllers.sIQ.s32i1 = UG_sVoltageAll.sVoltageDqCalc.s16Qr << 9;
			UG_sSystemControllers.sSPD.s32i1 = UG_sCurrentAll.sCurrentDqSO.s16Qr << 9;
			UG_sSystemControllers.sCommandAll.s32SpdCommand =  UG_sPositionAll.SpdStateObserver;
			UG_sSystemControllers.sCommandAll.s32SpdUse = UG_sSystemControllers.sCommandAll.s32SpdCommand;
			UG_sSystemControllers.sSPD.u16En = TRUE;
			TG_sCommandRef.s32SetpointValue   = UG_sSystemControllers.sCommandAll.s32SpdCommand; //_IQ24->IQ5
			UG_sSysStateErr.sSystemStatePre = UG_sSysStateErr.sSystemState;
			UG_sCurrentAll.sCurrentDqUseLPF.s16Dr = UG_sCurrentAll.sCurrentDqSO.s16Dr;
			UG_sCurrentAll.sCurrentDqUseLPF.s16Qr = UG_sCurrentAll.sCurrentDqSO.s16Qr;		
			UG_sSysStateErr.sSystemState = UGT_E_SS_CLOSEDLOOP_J;
			break;
		
		default: break;
	
	}
	MDS_vTrigFunctions(&UG_sPositionAll.sSinCosUse, UG_sPositionAll.u16PosUse);	
	MDS_vCurrClarke(&UG_sCurrentAll.sCurrentAbc, &UG_sCurrentAll.sCurrentAlphaBeta);	
	MDS_vCurrPark(&UG_sCurrentAll.sCurrentAlphaBeta, UG_sPositionAll.sSinCosUse, &UG_sCurrentAll.sCurrentDqUse);
	
	
	MDS_vTrigFunctions(&UG_sPositionAll.sSinCosSO, UG_sPositionAll.PosStateObserver);
	MDS_vCurrPark(&UG_sCurrentAll.sCurrentAlphaBeta, UG_sPositionAll.sSinCosSO, &UG_sCurrentAll.sCurrentDqSO);
	MDS_vVoltClarke(&UG_sVoltageAll);
	MDS_vVoltPark(&UG_sVoltageAll.sVoltageAlphaBetaCalc, UG_sPositionAll.sSinCosSO, &UG_sVoltageAll.sVoltageDqCalc);
	//MDS_vVoltPark(&UG_sVoltageAll.sVoltageAlphaBetaUse, UG_sPositionAll.sSinCosSO, &UG_sVoltageAll.sVoltageDqCalc);
	//------16.4us----------
	MDS_sPosObserver.s32Idq[0] = UG_sCurrentAll.sCurrentDqSO.s16Dr << 9;
	MDS_sPosObserver.s32Idq[1] = UG_sCurrentAll.sCurrentDqSO.s16Qr << 9;
	MDS_sPosObserver.s32Udq[0] = UG_sVoltageAll.sVoltageDqCalc.s16Dr << 9;
	MDS_sPosObserver.s32Udq[1] = UG_sVoltageAll.sVoltageDqCalc.s16Qr << 9;
	MDS_vOBPosObserver(&MDS_sPosObserver);
	
	UG_sPositionAll.PosStateObserver = MDS_sPosObserver.s32ThetaEst>>9;
	UG_sPositionAll.SpdStateObserver = MDS_sPosObserver.s32SpeedEst;
	
	UG_sCurrentAll.sCurrentDqUseLPF.s16Dr += ((UG_sCurrentAll.sCurrentDqUse.s16Dr - UG_sCurrentAll.sCurrentDqUseLPF.s16Dr)>>1);
	UG_sCurrentAll.sCurrentDqUseLPF.s16Qr += ((UG_sCurrentAll.sCurrentDqUse.s16Qr - UG_sCurrentAll.sCurrentDqUseLPF.s16Qr)>>1);
	UG_sSystemControllers.sCommandAll.s32IdUse  = UG_sCurrentAll.sCurrentDqUseLPF.s16Dr << 9;
	UG_sSystemControllers.sCommandAll.s32IqUse  = UG_sCurrentAll.sCurrentDqUseLPF.s16Qr << 9;
	UG_sSystemControllers.sCommandAll.s32SpdUse = UG_sPositionAll.SpdStateObserver;

	MDS_vFOC();

  return 1;
}

/********************************************************************************************
  * @brief      FSM_CloseLoop.
********************************************************************************************/

u8 MDS_vClosedloop(void)
{ 
	static u32 index=0;
	
	UG_sPositionAll.u16PosUse = UG_sPositionAll.PosStateObserver;
  MDS_vTrigFunctions(&UG_sPositionAll.sSinCosUse, UG_sPositionAll.u16PosUse);

	MDS_vCurrClarke(&UG_sCurrentAll.sCurrentAbc, &UG_sCurrentAll.sCurrentAlphaBeta);	
	MDS_vCurrPark(&UG_sCurrentAll.sCurrentAlphaBeta, UG_sPositionAll.sSinCosUse, &UG_sCurrentAll.sCurrentDqUse);
	MDS_vVoltClarke(&UG_sVoltageAll);
	MDS_vVoltPark(&UG_sVoltageAll.sVoltageAlphaBetaCalc, UG_sPositionAll.sSinCosUse, &UG_sVoltageAll.sVoltageDqCalc);
	#if(UPDS_UABC_MEAS_SEL == UPDS_UABC_MEAS_ENABLE)	
	MDS_vVoltMeasClarke(&UG_sVoltageAll);
	MDS_vVoltPark(&UG_sVoltageAll.sVoltageAlphaBetaMeas, UG_sPositionAll.sSinCosUse, &UG_sVoltageAll.sVoltageDqMeas);
	#endif		

	#if (UPDS_CUR_IQ == UPDS_CUR_IQ24)	
	MDS_sPosObserver.s32Idq[0] = UG_sCurrentAll.sCurrentDqUse.s16Dr 	<< 9;//UG_sCurrentAll.sCurrentDqSO.s16Dr << 9;
	MDS_sPosObserver.s32Idq[1] = UG_sCurrentAll.sCurrentDqUse.s16Qr 	<< 9;
	MDS_sPosObserver.s32Udq[0] = UG_sVoltageAll.sVoltageDqCalc.s16Dr 	<< 9;//UG_sVoltageAll.sVoltageDqMeas.s16Dr << 12;//UG_sSystemControllers.sID.s32Out;
	MDS_sPosObserver.s32Udq[1] = UG_sVoltageAll.sVoltageDqCalc.s16Qr 	<< 9;//UG_sVoltageAll.sVoltageDqMeas.s16Qr << 12;//UG_sSystemControllers.sIQ.s32Out;
	MDS_vOBPosObserver(&MDS_sPosObserver);
	UG_sPositionAll.PosStateObserver = MDS_sPosObserver.s32ThetaEst>>9;
	UG_sPositionAll.SpdStateObserver = MDS_sPosObserver.s32SpeedEst;
	#elif (UPDS_CUR_IQ == UPDS_CUR_IQ12)	
	MDS_sPosObserverShort.s16Idq[0] = UG_sCurrentAll.sCurrentDqUse.s16Dr >>1;
	MDS_sPosObserverShort.s16Idq[1] = UG_sCurrentAll.sCurrentDqUse.s16Qr >>1;
	MDS_sPosObserverShort.s16Udq[0] = UG_sVoltageAll.sVoltageDqCalc.s16Dr >>1;//UG_sSystemControllers.sID.s32Out;//UG_sVoltageAll.sVoltageDqCalc.s16Dr << 9;////((s64)(UG_sSystemControllers.sID.s32Out)*UG_sVoltageAll.sVoltageAbc.s16UdcFluctuateGain)>>12;//UG_sSystemControllers.sID.s32Out;//UG_sVoltageAll.sVoltageDqCalc.s16Dr << 9;//
	MDS_sPosObserverShort.s16Udq[1] = UG_sVoltageAll.sVoltageDqCalc.s16Qr >>1;//UG_sSystemControllers.sIQ.s32Out;//UG_sVoltageAll.sVoltageDqCalc.s16Qr << 9;//((s64)(UG_sSystemControllers.sIQ.s32Out)*UG_sVoltageAll.sVoltageAbc.s16UdcFluctuateGain)>>12;//UG_sSystemControllers.sIQ.s32Out;//UG_sVoltageAll.sVoltageDqCalc.s16Qr << 9;//((s64)(UG_sSystemControllers.sIQ.s32Out)*UG_sVoltageAll.sVoltageAbc.s16UdcFluctuateGain)>>12;//
	MDS_vOBPosObserverShort(&MDS_sPosObserverShort);	
	UG_sPositionAll.PosStateObserver = (s32)MDS_sPosObserverShort.s16ThetaEst<<1;
	UG_sPositionAll.SpdStateObserver = (s32)MDS_sPosObserverShort.s16SpeedEst<<10;
	#endif

	UG_sCurrentAll.sCurrentDqUseLPF.s16Dr += ((UG_sCurrentAll.sCurrentDqUse.s16Dr - UG_sCurrentAll.sCurrentDqUseLPF.s16Dr)>>1);
	UG_sCurrentAll.sCurrentDqUseLPF.s16Qr += ((UG_sCurrentAll.sCurrentDqUse.s16Qr - UG_sCurrentAll.sCurrentDqUseLPF.s16Qr)>>1);
	UG_sSystemControllers.sCommandAll.s32IdUse = UG_sCurrentAll.sCurrentDqUseLPF.s16Dr << 9;
	UG_sSystemControllers.sCommandAll.s32IqUse = UG_sCurrentAll.sCurrentDqUseLPF.s16Qr << 9;
	UG_sSystemControllers.sCommandAll.s32SpdUse = UG_sPositionAll.SpdStateObserver;
	UG_sPositionAll.SpdUseLargeLPF += (UG_sPositionAll.SpdStateObserver - UG_sPositionAll.SpdUseLargeLPF)>>1;
	if(UG_sSysStateErr.sSoftClose.u8SoftCloseEn == FALSE)
	{
		
		if((UG_sSystemControllers.sCommandAll.s32SpdUse<_IQ(0.1))&&(UG_sSystemControllers.sCommandAll.s32SpdUse>_IQ(-0.1)))
		{
			if(UG_sSystemControllers.sCommandAll.s32IdCommand < UG_sSystemControllers.sMotorPara.s32StartCurPU)
				UG_sSystemControllers.sCommandAll.s32IdCommand += (UPDS_SOFTCLOSE_IQ_DEACC_MS_IQ<<2);
			else
				UG_sSystemControllers.sCommandAll.s32IdCommand = UG_sSystemControllers.sMotorPara.s32StartCurPU;
		}
		else
		{
			if(UG_sSystemControllers.sCommandAll.s32IdCommand > 0)
				UG_sSystemControllers.sCommandAll.s32IdCommand -= UPDS_SOFTCLOSE_IQ_DEACC_MS_IQ;
			else
			{
				#if (UPDS_DCURRENT_CHOOSE == UPDS_DCURRENT_FW)
				UG_sSystemControllers.sCommandAll.s32IdCommand = MDS_sFW.PI_FW.s32Out;
				#elif	(UPDS_DCURRENT_CHOOSE == UPDS_DCURRENT_MTPA)
				UG_sSystemControllers.sCommandAll.s32IdCommand = MDS_sMTPA.s32IdRef;
				#elif	(UPDS_DCURRENT_CHOOSE == UPDS_DCURRENT_ZERO)
				UG_sSystemControllers.sCommandAll.s32IdCommand = 0;	
				#endif			
			}				
		}
		
		if(UG_sSysStateErr.sPWMMode.PWMModePre != UG_sSysStateErr.sPWMMode.PWMMode)
		{
			MDS_vPWMSwitchNextPeriod();
			if (UG_sSystemControllers.sSPD.u16LoopIndex == UPDS_SPD_LOOP_COUNT)UG_sSystemControllers.sSPD.u16LoopIndex-=2;
		}
		
		if(UPDS_S32_ABS(UG_sPositionAll.SpdUseLargeLPF) > UG_sSysStateErr.sPWMMode.SpeedSwitchHigh)
		{
			UG_sSysStateErr.sPWMMode.PWMModePre = UG_sSysStateErr.sPWMMode.PWMMode;
			UG_sSysStateErr.sPWMMode.PWMMode 		= UPDS_PWM_MODE2;
		}
		else if(UPDS_S32_ABS(UG_sPositionAll.SpdUseLargeLPF) < UG_sSysStateErr.sPWMMode.SpeedSwitchLow)
		{
			UG_sSysStateErr.sPWMMode.PWMModePre = UG_sSysStateErr.sPWMMode.PWMMode;
			UG_sSysStateErr.sPWMMode.PWMMode 		= UPDS_PWM_MODE1;
		}
		
		if(UG_sSysStateErr.sPWMMode.PWMModePre != UG_sSysStateErr.sPWMMode.PWMMode)
		{
			MDS_vPWMSwitchImmediate();
			if (UG_sSystemControllers.sSPD.u16LoopIndex == UPDS_SPD_LOOP_COUNT)UG_sSystemControllers.sSPD.u16LoopIndex-=2;
		}
		
	}
	else
	{
		if(UG_sSysStateErr.sSoftClose.u8SoftCloseLastEn ==FALSE)
		{
			UG_sSystemControllers.sCommandAll.s32SpdCommand = 0;
			UG_sSystemControllers.sCommandAll.s32IqCommand -= UPDS_SOFTCLOSE_IQ_DEACC_MS_IQ;
			if(UG_sSystemControllers.sCommandAll.s32IqCommand < _IQ(0.0))UG_sSystemControllers.sCommandAll.s32IqCommand = _IQ(0.0);
		}
		else
		{
			UG_sSystemControllers.sCommandAll.s32IdCommand -= _IQ(0.0001);
			if(UG_sSystemControllers.sCommandAll.s32IdCommand < _IQ(0.0))UG_sSystemControllers.sCommandAll.s32IdCommand = _IQ(0.0);
			UG_sSystemControllers.sCommandAll.s32IqCommand -= UPDS_SOFTCLOSE_IQ_DEACC_MS_IQ;
			if(UG_sSystemControllers.sCommandAll.s32IqCommand < _IQ(0.0))UG_sSystemControllers.sCommandAll.s32IqCommand = _IQ(0.0);
		}					
	}
	
	MDS_vFOC();	
	
	return 1;
}

/********************************************************************************************
  * @brief      FSM_Identify.
********************************************************************************************/
u8 MDS_vBreak(void)
{
	UG_sSysStateErr.sSysTime.SoftClosedCount++;	
	if(UG_sSysStateErr.sSysTime.SoftClosedCount <= 10000)
	{	
	  SVPWM_TIM1_PWMH_LOW_PWML_ENABLE
	}
	else 
	{
		UG_sSysStateErr.sSystemStatePre = UG_sSysStateErr.sSystemState;  
		UG_sSysStateErr.sSystemState = UGT_E_SS_FAULT_L;
	}

	
	return 1;
}

/********************************************************************************************
  * @brief      FSM_Fault.
********************************************************************************************/
u8 MDS_vFault(void)
{
	if (UG_sSysStateErr.sSystemState > UGT_E_SS_INIT_B)	US_vSysFaultProcess();	  
	return 1;
}

u32 lg_u32WaitCount = 0;
u8 MDS_vWait(u32 WaitTime)
{
//	static 
	if(lg_u32WaitCount >= WaitTime)
	{
		UG_sSysStateErr.sSystemStatePre = UG_sSysStateErr.sSystemState;
		UG_sSysStateErr.sSystemState = UGT_E_SS_INIT_B;	
		lg_u32WaitCount = 0;
		return 1;
	}
	else
	{
		lg_u32WaitCount++;
		return 0;
	}
}

void MDS_vVSPCheck(void)
{
	static s32 s32VSPIndex=0;
	if ((UG_sSysStateErr.sSoftClose.s16SystemSwitch > UPDS_SYSTEM_START) && (UG_sSysStateErr.sSoftClose.u8VSP_LOCK == FALSE)&&(UG_sSysStateErr.uSystemError.Bits.Breaken == FALSE))
	{
		UG_sSysStateErr.sVSPCheck = UGT_E_VSP_OPEN_B;
	}
	else if ((UG_sSysStateErr.sSoftClose.s16SystemSwitch < UPDS_SYSTEM_OFF)||(UG_sSysStateErr.uSystemError.Bits.Breaken == TRUE)||(UG_sSysStateErr.sSoftClose.u8VSP_LOCK == TRUE))
	{
		UG_sSysStateErr.sVSPCheck = UGT_E_VSP_CLOSED_A;
		if(UG_sSysStateErr.sSystemState >= UGT_E_SS_PRECHARGE_E)
		{
			if((UG_sSysStateErr.sSystemState == UGT_E_SS_CLOSEDLOOP_J)||(UG_sSysStateErr.sSystemState == UGT_E_SS_OPENLOOP_I))
			{
				if(UG_sSysStateErr.uControlReg.Bits.ControlMode != UGT_E_CM_VF)
				{
					UG_sSystemControllers.sCommandAll.s32IqCommand = UG_sSystemControllers.sSPD.s32Out;
					UG_sSystemControllers.sSPD.u16En = FALSE;
					MDS_sCP.PI_CP.u16En = FALSE;					
					UG_sSystemControllers.sUdc.u16En = TRUE;					
					UG_sSysStateErr.sSoftClose.u8VSP_LOCK = TRUE;
					UG_sSysStateErr.sSoftClose.u8SoftCloseEn = TRUE;

					if (UG_sSystemControllers.sCommandAll.s32SpdUse < _IQ(0.05))
					{
						s32VSPIndex++;
						if(s32VSPIndex>100)
						{
							UG_sSysStateErr.sSoftClose.u8SoftCloseLastEn = TRUE;							
							UG_sSysStateErr.sSoftClose.u8VSP_LOCK = FALSE;
							UG_sSysStateErr.uSystemError.Bits.Breaken=FALSE;
							UG_sSysStateErr.sSoftClose.u8SoftCloseEn = FALSE;
							UG_sSysStateErr.sSystemStatePre = UG_sSysStateErr.sSystemState;					
							UG_sSysStateErr.sSystemState = UGT_E_SS_FAULT_L; 
							UG_sSysStateErr.sSysTime.SoftClosedCount = 0;														
							s32VSPIndex=0;								
						}		
					}	
					else
					{
						s32VSPIndex--;
						if(s32VSPIndex < -100)s32VSPIndex=0;
					}	
				}	
				else	
				{
					UG_sSysStateErr.sSoftClose.u8VSP_LOCK = FALSE;
					UG_sSysStateErr.sSoftClose.u8SoftCloseEn = FALSE;
					UG_sSysStateErr.sSystemStatePre = UG_sSysStateErr.sSystemState;					
					UG_sSysStateErr.sSystemState = UGT_E_SS_BRAKE_K; 				
				}					
			}		
		}
	}
}


void MDS_vPWMSwitchNextPeriod(void)
{
	if(UG_sSysStateErr.sPWMMode.PWMMode == UPDS_PWM_MODE1)
	{
		#if (UPDS_CUR_IQ == UPDS_CUR_IQ24)
		MDS_sPosObserver.s32GainQErr			=	UG_sSystemControllers.sMotorPara.s32GainQErr1;
		MDS_sPosObserver.s32GainDErr			=	UG_sSystemControllers.sMotorPara.s32GainDErr1;
		MDS_sPosObserver.s32PLLInputGain	=	UG_sSystemControllers.sMotorPara.s32PLLInputGain1;
		MDS_sPosObserver.s32TsDivLq				= UG_sSystemControllers.sMotorPara.s32TsDivLq1;
		MDS_sPosObserver.s32TsRDivLq			=	UG_sSystemControllers.sMotorPara.s32TsRDivLq1;
		MDS_sPosObserver.s32TsLdDivLq			=	UG_sSystemControllers.sMotorPara.s32TsLdDivLq1;
		MDS_sPosObserver.s32TsPsiDivLq		=	UG_sSystemControllers.sMotorPara.s32TsPsiDivLq1;
		MDS_sPosObserver.s32TsDivLd				= UG_sSystemControllers.sMotorPara.s32TsDivLd1;
		MDS_sPosObserver.s32TsRDivLd			=	UG_sSystemControllers.sMotorPara.s32TsRDivLd1;
		MDS_sPosObserver.s32TsLqDivLd			=	UG_sSystemControllers.sMotorPara.s32TsLqDivLd1;
		MDS_sPosObserver.s32CompTime			= UG_sSystemControllers.sMotorPara.s32CompTime1;	
		UG_sSystemControllers.sID.s32Ki   = UG_sSystemControllers.sMotorPara.s32KiDAxis1;
		UG_sSystemControllers.sIQ.s32Ki   = UG_sSystemControllers.sMotorPara.s32KiQAxis1;		
		#elif (UPDS_CUR_IQ == UPDS_CUR_IQ12)
		MDS_sPosObserverShort.s16GainQErr			=	OB_IQGAIN_Q_SHORT;
		MDS_sPosObserverShort.s16GainDErr			=	OB_IQGAIN_D_SHORT;
		MDS_sPosObserverShort.s16PLLInputGain	=	OB_IQTSPLL_SHORT;
		MDS_sPosObserverShort.s16TsDivLq			= OB_IQTS_DIV_LQ_SHORT;
		MDS_sPosObserverShort.s16TsRDivLq			=	OB_IQTS_R_DIV_LQ_SHORT;
		MDS_sPosObserverShort.s16TsLdDivLq		=	OB_IQTS_LD_DIV_LQ_SHORT;
		MDS_sPosObserverShort.s16TsPsiDivLq		=	OB_IQTS_PSI_DIV_LQ_SHORT;
		MDS_sPosObserverShort.s16TsDivLd			= OB_IQTS_DIV_LD_SHORT;
		MDS_sPosObserverShort.s16TsRDivLd			=	OB_IQTS_R_DIV_LD_SHORT;
		MDS_sPosObserverShort.s16TsLqDivLd		=	OB_IQTS_LQ_DIV_LD_SHORT;	
		MDS_sPosObserverShort.s16CompTime			= OB_COMP_TIME_SHORT;		
		UG_sSystemControllers.sID12.s16Ki   = UG_sSystemControllers.sMotorPara.s16KiDAxis1;
		UG_sSystemControllers.sIQ12.s16Ki   = UG_sSystemControllers.sMotorPara.s16KiQAxis1;
		#endif
	}
	else if(UG_sSysStateErr.sPWMMode.PWMMode == UPDS_PWM_MODE2)
	{
		#if (UPDS_CUR_IQ == UPDS_CUR_IQ24)
		MDS_sPosObserver.s32GainQErr			=	UG_sSystemControllers.sMotorPara.s32GainQErr2;
		MDS_sPosObserver.s32GainDErr			=	UG_sSystemControllers.sMotorPara.s32GainDErr2;
		MDS_sPosObserver.s32PLLInputGain	=	UG_sSystemControllers.sMotorPara.s32PLLInputGain2;
		MDS_sPosObserver.s32TsDivLq				= UG_sSystemControllers.sMotorPara.s32TsDivLq2;
		MDS_sPosObserver.s32TsRDivLq			=	UG_sSystemControllers.sMotorPara.s32TsRDivLq2;
		MDS_sPosObserver.s32TsLdDivLq			=	UG_sSystemControllers.sMotorPara.s32TsLdDivLq2;
		MDS_sPosObserver.s32TsPsiDivLq		=	UG_sSystemControllers.sMotorPara.s32TsPsiDivLq2;
		MDS_sPosObserver.s32TsDivLd				= UG_sSystemControllers.sMotorPara.s32TsDivLd2;
		MDS_sPosObserver.s32TsRDivLd			=	UG_sSystemControllers.sMotorPara.s32TsRDivLd2;
		MDS_sPosObserver.s32TsLqDivLd			=	UG_sSystemControllers.sMotorPara.s32TsLqDivLd2;
		MDS_sPosObserver.s32CompTime			= UG_sSystemControllers.sMotorPara.s32CompTime2;	
		UG_sSystemControllers.sID.s32Ki   = UG_sSystemControllers.sMotorPara.s32KiDAxis2;
		UG_sSystemControllers.sIQ.s32Ki   = UG_sSystemControllers.sMotorPara.s32KiQAxis2;		
		#elif (UPDS_CUR_IQ == UPDS_CUR_IQ12)
		MDS_sPosObserverShort.s16GainQErr			=	OB_IQGAIN_Q2_SHORT;
		MDS_sPosObserverShort.s16GainDErr			=	OB_IQGAIN_D2_SHORT;
		MDS_sPosObserverShort.s16PLLInputGain	=	OB_IQTSPLL2_SHORT;
		MDS_sPosObserverShort.s16TsDivLq			= OB_IQTS_DIV_LQ2_SHORT;
		MDS_sPosObserverShort.s16TsRDivLq			=	OB_IQTS_R_DIV_LQ2_SHORT;
		MDS_sPosObserverShort.s16TsLdDivLq		=	OB_IQTS_LD_DIV_LQ2_SHORT;
		MDS_sPosObserverShort.s16TsPsiDivLq		=	OB_IQTS_PSI_DIV_LQ2_SHORT;
		MDS_sPosObserverShort.s16TsDivLd			= OB_IQTS_DIV_LD2_SHORT;
		MDS_sPosObserverShort.s16TsRDivLd			=	OB_IQTS_R_DIV_LD2_SHORT;
		MDS_sPosObserverShort.s16TsLqDivLd		=	OB_IQTS_LQ_DIV_LD2_SHORT;	
		MDS_sPosObserverShort.s16CompTime			= OB_COMP_TIME2_SHORT;		
		UG_sSystemControllers.sID12.s16Ki   	= UG_sSystemControllers.sMotorPara.s16KiDAxis2;
		UG_sSystemControllers.sIQ12.s16Ki   	= UG_sSystemControllers.sMotorPara.s16KiQAxis2;
		#endif
		
	}
}

//1.3us
void MDS_vPWMSwitchImmediate(void)
{
	if(UG_sSysStateErr.sPWMMode.PWMMode == UPDS_PWM_MODE1)
	{
		TIM1->CCR4_b.CCR4 = 10;		
		TIM1->ARR = UG_sSystemControllers.sMotorPara.u16PWMPerood1;
		UG_sVoltageAll.sPwmDuty.u16HalfPerMax 		= UG_sSystemControllers.sMotorPara.u16PWMPerood1>>1;
		UG_sVoltageAll.sPwmDuty.u16PeriodMax 			= UG_sSystemControllers.sMotorPara.u16PWMPerood1;
		UG_sVoltageAll.sDeadTimeComp.s16DTComp   	= UG_sSystemControllers.sMotorPara.u16DeadtimeComp1;	
	}
	else if(UG_sSysStateErr.sPWMMode.PWMMode == UPDS_PWM_MODE2)
	{
		TIM1->CCR4_b.CCR4 = 10;
		TIM1->ARR = UG_sSystemControllers.sMotorPara.u16PWMPerood2;
		UG_sVoltageAll.sPwmDuty.u16HalfPerMax 		= UG_sSystemControllers.sMotorPara.u16PWMPerood2>>1;
		UG_sVoltageAll.sPwmDuty.u16PeriodMax 			= UG_sSystemControllers.sMotorPara.u16PWMPerood2;
		UG_sVoltageAll.sDeadTimeComp.s16DTComp   	= UG_sSystemControllers.sMotorPara.u16DeadtimeComp2;	
	}
}

void MDS_vMotorAppCommand(void)
{
  switch(UG_sSysStateErr.uControlReg.Bits.CommandType)
	{
		case UPDS_COMMAND_SOFTTOOL:
		{
			UG_sSystemControllers.s32Command 					 = ((s32)UG_sUsartData.s16UartTargetValue << 9);
			UG_sSysStateErr.sSoftClose.s16SystemSwitch = UG_sUsartData.s16UartTargetValue;	
			break;		
		}
		case 	UPDS_COMMAND_VSP:
		{
			UG_sSystemControllers.s32Command 						= ((s32)UG_sADSampleAll.s16VSPLPF << 9);
			UG_sSysStateErr.sSoftClose.s16SystemSwitch 	= UG_sADSampleAll.s16VSPLPF;			
			break;
		}
		case UPDS_COMMAND_PWM:
		{
			UG_sSysStateErr.sSoftClose.s16SystemSwitch 	= UG_sADSampleAll.s16VSPLPF;	
			break;		
		}
		case UPDS_COMMAND_KEIL:
		{
			UG_sSystemControllers.s32Command 						= UPDS_KEILVALUE<<9;
			UG_sSysStateErr.sSoftClose.s16SystemSwitch 	= UG_sADSampleAll.s16VSPLPF;//0;//starup			
			break;		
		}
		default: break;
	}
}
//28ms
u8 MDS_vWriteFlash(void)
{  
	if(UG_sUsartData.sUsartEvent.Bits.WriteFlash == 1)
	{
		PA1_SET;
		TIM_Cmd(TIM1, DISABLE);
		UPDS_SYSTICK_DISABLE;
		UG_sUsartData.sUsartEvent.Bits.WriteFlashing = 1;
		UU_vUartDataFlashWrite(FLASH_START_PAGE_ADDRESS, HALF_WRITE);		
		US_vSystParaInitPowerup();
		MDS_vOtherInitFromUserSetting(&UG_sSystemControllers.sMotorPara);
		UP_vOPA012Config();
		UP_vTimerConfiguration();			
		UG_sUsartData.sUsartEvent.Bits.WriteFlashing = 0;
		UG_sUsartData.sUsartEvent.Bits.WriteFlash = 0;
		TIM_Cmd(TIM1, ENABLE);
		UPDS_SYSTICK_ENABLE;
		PA1_RESET;
	}

	UG_sSysStateErr.sSystemStatePre = UG_sSysStateErr.sSystemState;
	UG_sSysStateErr.sSystemState 		= UGT_E_SS_IDLE_A;	
	return 1;
}

void MDS_vUdcSwitchCheck(void)
{
	if(UG_sVoltageAll.sVoltageAbc.s16UdcMeas < UPDS_NWONE_VOLHIGH_IQ12)	
	{
		UG_sSystemControllers.sMotorPara.s32NWUdcValue 		= UPDS_NWONE_UDCVALUE;
		UG_sSystemControllers.sMotorPara.f32UnderVoltage	=	UPDS_UNDERVOLTAGE_NWONE_V;
		MDS_sNW.u16RunTask	=	1;
	}
	else if ((UG_sVoltageAll.sVoltageAbc.s16UdcMeas > UPDS_NWTWO_VOLLOW_IQ12)&&(UG_sVoltageAll.sVoltageAbc.s16UdcMeas < UPDS_NWTWO_VOLHIGH_IQ12))
	{
		UG_sSystemControllers.sMotorPara.s32NWUdcValue 		= UPDS_NWTWO_UDCVALUE;
		UG_sSystemControllers.sMotorPara.f32UnderVoltage	=	UPDS_UNDERVOLTAGE_NWTWO_V;
		MDS_sNW.u16RunTask	=	2;
	}
	else if(UG_sVoltageAll.sVoltageAbc.s16UdcMeas > UPDS_NWTHREE_VOLLOW_IQ12)	
	{
		UG_sSystemControllers.sMotorPara.s32NWUdcValue 		= UPDS_NWTHREE_UDCVALUE;
		UG_sSystemControllers.sMotorPara.f32UnderVoltage	=	UPDS_UNDERVOLTAGE_NWTHREE_V;
		MDS_sNW.u16RunTask	=	3;
	}
	UG_sSystemControllers.sMotorPara.s16UnderVoltage 		= (s16)(UG_sSystemControllers.sMotorPara.f32UnderVoltage / UG_sSystemControllers.sMotorPara.f32Udc * UPDS_SQRT3 * 0x1000);			
}	

void MDS_vFGRPM(void)
{
	UG_sPositionAll.PosCount[1]= UG_sPositionAll.u16PosUse;
	if(((UG_sPositionAll.PosCount[1]-UG_sPositionAll.PosCount[0])>0x7FFF)||(UG_sPositionAll.PosCount[0]-UG_sPositionAll.PosCount[1]>0x7FFF)){}
	else
	{
		if((UG_sPositionAll.PosCount[0]<0x7FFF)&&(UG_sPositionAll.PosCount[1]>=0x7FFF))
		{
			UG_sPositionAll.PosCountIndex++;
			if(UG_sPositionAll.PosCountIndex==(UPDS_PAIRS+1))UG_sPositionAll.PosCountIndex=1;
		}
		else if((UG_sPositionAll.PosCount[0]>=0x7FFF)&&(UG_sPositionAll.PosCount[1]<0x7FFF))
		{
			UG_sPositionAll.PosCountIndex--;
			if(UG_sPositionAll.PosCountIndex==0)UG_sPositionAll.PosCountIndex=1;	
		}
	}
	UG_sPositionAll.PosCount[0]= UG_sPositionAll.PosCount[1];
	if(UG_sPositionAll.PosCountIndex==(UPDS_PAIRS>>1))GPIO_ResetBits(GPIOA, GPIO_Pin_2 ); 
	else if(UG_sPositionAll.PosCountIndex==UPDS_PAIRS)GPIO_SetBits(GPIOA, GPIO_Pin_2 ); 
}