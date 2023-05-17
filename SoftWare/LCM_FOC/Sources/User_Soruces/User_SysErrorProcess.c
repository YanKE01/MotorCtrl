#define EXPORT_USER_SYSERRORPROCESS_H_
#include "User_SysErrorProcess.h"
#undef EXPORT_USER_SYSERRORPROCESS_H_

#include "HY_Variable.h"

void US_vSysErrorCheck(void)
{
	s16 s16temp = 0;

	s16temp = (_IQ15mpyIQ15(UG_sCurrentAll.sCurrentAlphaBeta.s16Alpha, UG_sCurrentAll.sCurrentAlphaBeta.s16Alpha) + _IQ15mpyIQ15(UG_sCurrentAll.sCurrentAlphaBeta.s16Beta, UG_sCurrentAll.sCurrentAlphaBeta.s16Beta)) >> 6;
	s16temp = (sqrt_table[s16temp]);

	UG_sCurrentAll.sCurrentAlphaBeta.s16CurMag += _IQ15mpyIQ15((s16temp - UG_sCurrentAll.sCurrentAlphaBeta.s16CurMag), UPDS_IQ_LPF_BAND_GAIN);

	UG_sCurrentAll.sCurrentAbc.s16IAsAbs = UPDS_S32_ABS(UG_sCurrentAll.sCurrentAbc.s16As);
	UG_sCurrentAll.sCurrentAbc.s16IBsAbs = UPDS_S32_ABS(UG_sCurrentAll.sCurrentAbc.s16Bs);
	UG_sCurrentAll.sCurrentAbc.s16ICsAbs = UPDS_S32_ABS(UG_sCurrentAll.sCurrentAbc.s16Cs);

	UG_sCurrentAll.sCurrentAbc.s16IAsAbsLPF += (((s32)UG_sCurrentAll.sCurrentAbc.s16IAsAbs - UG_sCurrentAll.sCurrentAbc.s16IAsAbsLPF) >> 10);
	UG_sCurrentAll.sCurrentAbc.s16IBsAbsLPF += (((s32)UG_sCurrentAll.sCurrentAbc.s16IBsAbs - UG_sCurrentAll.sCurrentAbc.s16IBsAbsLPF) >> 10);
	UG_sCurrentAll.sCurrentAbc.s16ICsAbsLPF += (((s32)UG_sCurrentAll.sCurrentAbc.s16ICsAbs - UG_sCurrentAll.sCurrentAbc.s16ICsAbsLPF) >> 10);
	s16temp = (UG_sCurrentAll.sCurrentAbc.s16IAsAbsLPF > UG_sCurrentAll.sCurrentAbc.s16IBsAbsLPF) ? (UG_sCurrentAll.sCurrentAbc.s16IAsAbsLPF) : (UG_sCurrentAll.sCurrentAbc.s16IBsAbsLPF);
	UG_sCurrentAll.sCurrentAbc.s16IAbsMaxHalf = (((UG_sCurrentAll.sCurrentAbc.s16ICsAbsLPF > s16temp) ? (UG_sCurrentAll.sCurrentAbc.s16ICsAbsLPF) : (s16temp))) >> 2;

	if (UG_sSysStateErr.sSystemState >= UGT_E_SS_START_D)
	{
		if (UG_sCurrentAll.sCurrentAlphaBeta.s16CurMag > UG_sSystemControllers.sMotorPara.s16OverCurrent)
		{
			UG_sSysStateErr.sSysTime.OCCount++;
			if (UG_sSysStateErr.sSysTime.OCCount > UG_sSystemControllers.sMotorPara.s32OCJudgeTimeTotal)
			{
				UG_sSysStateErr.uSystemError.Bits.OverCurrent = TRUE;
				motor.fault = 1;
				UG_sSysStateErr.sSysTime.OLCount = 0;
				;
			}
		}
		else
		{
			UG_sSysStateErr.sSysTime.OCCount--;
			if (UG_sSysStateErr.sSysTime.OCCount < 0)
			{
				UG_sSysStateErr.sSysTime.OCCount = 0;
				UG_sSysStateErr.uSystemError.Bits.OverCurrent = FALSE;
			}
		}

		// Lose phase error
		if (UG_sSysStateErr.sSystemState >= UGT_E_SS_CLOSEDLOOP_J)
		{
			if ((UG_sCurrentAll.sCurrentAbc.s16IAsAbsLPF < UG_sCurrentAll.sCurrentAbc.s16IAbsMaxHalf) || (UG_sCurrentAll.sCurrentAbc.s16IBsAbsLPF < UG_sCurrentAll.sCurrentAbc.s16IAbsMaxHalf) || (UG_sCurrentAll.sCurrentAbc.s16ICsAbsLPF < UG_sCurrentAll.sCurrentAbc.s16IAbsMaxHalf))
			{
				UG_sSysStateErr.sSysTime.LosePhaseCount++;
				if (UG_sSysStateErr.sSysTime.LosePhaseCount > US_LOSEPHASE_TIME_S32)
				{
					UG_sSysStateErr.sSysTime.LosePhaseCount = 0;
					UG_sSysStateErr.uSystemError.Bits.LosePhase = TRUE;
				}
			}
			else
			{
				UG_sSysStateErr.sSysTime.LosePhaseCount--;
				if (UG_sSysStateErr.sSysTime.LosePhaseCount < 0)
				{
					UG_sSysStateErr.sSysTime.LosePhaseCount = 0;
					UG_sSysStateErr.uSystemError.Bits.LosePhase = FALSE;
				}
			}
		}
		// Over IAs
		if (UG_sCurrentAll.sCurrentAbc.s16IAsAbs > UG_sSystemControllers.sMotorPara.s16OverCurrent)
		{
			UG_sSysStateErr.sSysTime.OverIAsCount++;
			if (UG_sSysStateErr.sSysTime.OverIAsCount > UG_sSystemControllers.sMotorPara.s32OCJudgeTimeTotal)
			{
				UG_sSysStateErr.sSysTime.OverIAsCount = 0;
				UG_sSysStateErr.uSystemError.Bits.OverIAs = TRUE;
			}
		}
		else
		{
			UG_sSysStateErr.sSysTime.OverIAsCount--;
			if (UG_sSysStateErr.sSysTime.OverIAsCount < 0)
			{
				UG_sSysStateErr.sSysTime.OverIAsCount = 0;
				UG_sSysStateErr.uSystemError.Bits.OverIAs = FALSE;
			}
		}
		// Over IBs
		if (UG_sCurrentAll.sCurrentAbc.s16IBsAbs > UG_sSystemControllers.sMotorPara.s16OverCurrent)
		{
			UG_sSysStateErr.sSysTime.OverIBsCount++;
			if (UG_sSysStateErr.sSysTime.OverIBsCount > UG_sSystemControllers.sMotorPara.s32OCJudgeTimeTotal)
			{
				UG_sSysStateErr.sSysTime.OverIBsCount = 0;
				UG_sSysStateErr.uSystemError.Bits.OverIBs = TRUE;
			}
		}
		else
		{
			UG_sSysStateErr.sSysTime.OverIBsCount--;
			if (UG_sSysStateErr.sSysTime.OverIBsCount < 0)
			{
				UG_sSysStateErr.sSysTime.OverIBsCount = 0;
				UG_sSysStateErr.uSystemError.Bits.OverIBs = FALSE;
			}
		}
		// Over ICs
		if (UG_sCurrentAll.sCurrentAbc.s16ICsAbs > UG_sSystemControllers.sMotorPara.s16OverCurrent)
		{
			UG_sSysStateErr.sSysTime.OverICsCount++;
			if (UG_sSysStateErr.sSysTime.OverICsCount > UG_sSystemControllers.sMotorPara.s32OCJudgeTimeTotal)
			{
				UG_sSysStateErr.sSysTime.OverICsCount = 0;
				UG_sSysStateErr.uSystemError.Bits.OverICs = TRUE;
			}
		}
		else
		{
			UG_sSysStateErr.sSysTime.OverICsCount--;
			if (UG_sSysStateErr.sSysTime.OverICsCount < 0)
			{
				UG_sSysStateErr.sSysTime.OverICsCount = 0;
				UG_sSysStateErr.uSystemError.Bits.OverICs = FALSE;
			}
		}

		// OverVoltage && UnderVoltage
		if (UG_sVoltageAll.sVoltageAbc.s16UdcMeas > (UG_sSystemControllers.sMotorPara.s16OverVoltage))
		{
			UG_sSysStateErr.sSysTime.OVCount++;
			if (UG_sSysStateErr.sSysTime.OVCount > UG_sSystemControllers.sMotorPara.s32OVJudgeTimeTotal)
			{
				UG_sSysStateErr.uSystemError.Bits.OverVoltage = TRUE;
				motor.fault = 1;

				UG_sSysStateErr.sSysTime.OVCount = 0;
			}
		}
		else if (UG_sVoltageAll.sVoltageAbc.s16UdcMeas < (UG_sSystemControllers.sMotorPara.s16UnderVoltage))
		{
			UG_sSysStateErr.sSysTime.UVCount++;
			if (UG_sSysStateErr.sSysTime.UVCount > UG_sSystemControllers.sMotorPara.s32UVJudgeTimeTotal)
			{
				UG_sSysStateErr.uSystemError.Bits.UnderVoltage = TRUE;
				motor.fault = 1;

				UG_sSysStateErr.sSysTime.UVCount = 0;
			}
		}
		else
		{
			UG_sSysStateErr.sSysTime.UVCount--;
			UG_sSysStateErr.sSysTime.OVCount--;
			if (UG_sSysStateErr.sSysTime.OVCount < 0)
			{
				UG_sSysStateErr.sSysTime.OVCount = 0;
				UG_sSysStateErr.uSystemError.Bits.OverVoltage = FALSE;
			}
			if (UG_sSysStateErr.sSysTime.UVCount < 0)
			{
				UG_sSysStateErr.sSysTime.UVCount = 0;
				UG_sSysStateErr.uSystemError.Bits.UnderVoltage = FALSE;
			}
		}

		// Over IGBT Temperature
		//	if(UG_sADSampleAll.s16IGBTTempLPF < UG_sSystemControllers.sMotorPara.s16IPMOverTemp)
		//	{
		//		UG_sSysStateErr.sSysTime.OTIPMCount++;
		//		if(UG_sSysStateErr.sSysTime.OTIPMCount > UG_sSystemControllers.sMotorPara.s32IPMOTJudgeTimeTotal)
		//		{
		//			UG_sSysStateErr.sSysTime.OTIPMCount = 0;
		////			UG_sSysStateErr.uSystemError.Bits.OverTempIGBT = TRUE;
		//			UG_sSysStateErr.sSystemStatePre = UG_sSysStateErr.sSystemState;
		//			UG_sSysStateErr.sSystemState = UGT_E_SS_FAULT_L;
		//		}
		//	}
		//	else
		//	{
		//		UG_sSysStateErr.sSysTime.OTIPMCount--;
		//		if (UG_sSysStateErr.sSysTime.OTIPMCount < 0)
		//		{
		//			UG_sSysStateErr.sSysTime.OTIPMCount = 0;
		//			UG_sSysStateErr.uSystemError.Bits.OverTempIGBT = FALSE;
		//		}
		//	}
	}

	if (UG_sSysStateErr.sSystemState == UGT_E_SS_CLOSEDLOOP_J)
	{
		// 启动失败保护
		if (UG_sSystemControllers.sCommandAll.s32SpdUse < UG_sSystemControllers.sMotorPara.s32StartUpMinSpeed)
		{
			UG_sSysStateErr.sSysTime.StartupSwitchFailCount++;
			if (UG_sSysStateErr.sSysTime.StartupSwitchFailCount > UG_sSystemControllers.sMotorPara.s32SUMSJudgeTimeTotal)
			{
				UG_sSysStateErr.uSystemError.Bits.StartupFail = TRUE;
				motor.fault = 1;
				UG_sSysStateErr.sSysTime.StartupSwitchFailCount = 0;
			}
		}
		else
		{
			UG_sSysStateErr.sSysTime.StartupSwitchFailCount--;
			if (UG_sSysStateErr.sSysTime.StartupSwitchFailCount < 0)
			{
				UG_sSysStateErr.uSystemError.Bits.StartupFail = FALSE;
				UG_sSysStateErr.sSysTime.StartupSwitchFailCount = 0;
			}
		}

// 水泵缺水保护
#if (UPDS_NOWATER_SEL == UPDS_NOWATER_ENABLE)
		if (MDS_sNW.s32SpdDivIqGain > UG_sSystemControllers.sMotorPara.s32NoWaterGain)
		{
			UG_sSysStateErr.sSysTime.NoWaterCount++;
			if (UG_sSysStateErr.sSysTime.NoWaterCount > UG_sSystemControllers.sMotorPara.s32NoWaterJudgeTimeTotal)
			{
				UG_sSysStateErr.uSystemError.Bits.NoWater = TRUE;
				motor.fault = 1;
				UG_sSysStateErr.sSysTime.NoWaterCount = 0;
				UG_sSysStateErr.sSystemStatePre = UG_sSysStateErr.sSystemState;
				UG_sSysStateErr.sSystemState = UGT_E_SS_FAULT_L;
			}
		}
		else
		{
			UG_sSysStateErr.sSysTime.NoWaterCount--;
			if (UG_sSysStateErr.sSysTime.NoWaterCount < 0)
			{
				UG_sSysStateErr.uSystemError.Bits.NoWater = FALSE;
				UG_sSysStateErr.sSysTime.NoWaterCount = 0;
			}
		}
#endif
	}

	if (UG_sSysStateErr.sSysTime.StartupFailCount == UG_sSystemControllers.sMotorPara.u16StartUpTimes)
	{
		//		UG_sSystemControllers.u8ExtraStart = 1;
	}
	else if (UG_sSysStateErr.sSysTime.StartupFailCount >= (UG_sSystemControllers.sMotorPara.u16StartUpTimes + 1))
	{
		UG_sSysStateErr.uSystemError.Bits.StartupFailContious = TRUE;
		UG_sSysStateErr.sSysTime.StartupFailCount = 0;
	}

	if ((UG_sSysStateErr.uSystemError.Bits.OverCurrent == TRUE) && (UG_sSysStateErr.sSystemState >= UGT_E_SS_TRACK_F))
	{
		UG_sSysStateErr.sSystemStatePre = UG_sSysStateErr.sSystemState;
		UG_sSysStateErr.sSystemState = UGT_E_SS_FAULT_L;
	}

	if ((UG_sSysStateErr.uSystemError.Bits.LosePhase == TRUE) && (UG_sSysStateErr.sSystemState >= UGT_E_SS_TRACK_F))
	{
		UG_sSysStateErr.sSystemStatePre = UG_sSysStateErr.sSystemState;
		UG_sSysStateErr.sSystemState = UGT_E_SS_FAULT_L;
	}

	UG_sSysStateErr.uSystemError.Bits.OverIAsIBsICs = UG_sSysStateErr.uSystemError.Bits.OverIAs | UG_sSysStateErr.uSystemError.Bits.OverIBs | UG_sSysStateErr.uSystemError.Bits.OverICs;
	if ((UG_sSysStateErr.uSystemError.Bits.OverIAsIBsICs == TRUE) && (UG_sSysStateErr.sSystemState >= UGT_E_SS_TRACK_F))
	{
		UG_sSysStateErr.sSystemStatePre = UG_sSysStateErr.sSystemState;
		UG_sSysStateErr.sSystemState = UGT_E_SS_FAULT_L;
	}

	if (UG_sSysStateErr.uSystemError.Bits.OverVoltage == TRUE)
	{
		UG_sSysStateErr.sSystemStatePre = UG_sSysStateErr.sSystemState;
		UG_sSysStateErr.sSystemState = UGT_E_SS_FAULT_L;
	}

	if (UG_sSysStateErr.uSystemError.Bits.UnderVoltage == TRUE)
	{

		UG_sSysStateErr.sSystemStatePre = UG_sSysStateErr.sSystemState;
		UG_sSysStateErr.sSystemState = UGT_E_SS_FAULT_L;
		//			UG_sSysStateErr.uSystemError.Bits.Breaken=TRUE;
	}

	if (UG_sSysStateErr.uSystemError.Bits.StartupFailContious == TRUE)
	{
		UG_sSysStateErr.sSystemStatePre = UG_sSysStateErr.sSystemState;
		UG_sSysStateErr.sSystemState = UGT_E_SS_FAULT_L;
	}
	else if (UG_sSysStateErr.uSystemError.Bits.StartupFail == TRUE)
	{
		UG_sSysStateErr.sSystemStatePre = UG_sSysStateErr.sSystemState;
		UG_sSysStateErr.sSystemState = UGT_E_SS_FAULT_L;
	}

	//	if(UG_sVoltageAll.sVoltageAbc.s16UdcMeas < (UG_sSystemControllers.sMotorPara.s16UnderVoltageFlashWrite))
	//	{
	//		UG_sSysStateErr.sSysTime.UVFlashWriteCount ++;
	//		if (UG_sSysStateErr.sSysTime.UVFlashWriteCount > UPDS_UV_FLASHWRITE_10MS)
	//		{
	//			UG_sSysStateErr.sSystemStatePre = UG_sSysStateErr.sSystemState;
	//			UG_sSysStateErr.sSystemState 		= UGT_E_SS_WRITE_FLASH;
	//			UG_sSysStateErr.sSysTime.UVFlashWriteCount = 0;
	//		}
	//	}
	//	else
	//	{
	//		UG_sSysStateErr.sSysTime.UVFlashWriteCount --;
	//		if (UG_sSysStateErr.sSysTime.UVFlashWriteCount < 0)
	//		{
	//			UG_sSysStateErr.sSysTime.UVFlashWriteCount = 0;
	//		}
	//	}
}

// system fault process in the case FAULT
void US_vSysFaultProcess(void)
{
	SVPWM_TIM1_PWM_DISABLE_MACRO
	MDS_vTIMInit();
	if (UG_sSysStateErr.uSystemError.Bits.OverCurrent == TRUE)
	{
		UG_sSysStateErr.sSystemStatePre = UG_sSysStateErr.sSystemState;
		UG_sSysStateErr.sSystemState = UGT_E_SS_WAIT_M;
		UG_sSysStateErr.sSysTime.ReStartTime = US_RE_STARTUP_OVERCURR_TIME_S32;
		//		UG_sSysStateErr.sSystemStatePre = UG_sSysStateErr.sSystemState;
		//		UG_sSysStateErr.sSystemState = UGT_E_SS_INIT_B;
	}
	else if (UG_sSysStateErr.uSystemError.Bits.LosePhase == TRUE)
	{
		UG_sSysStateErr.sSystemStatePre = UG_sSysStateErr.sSystemState;
		UG_sSysStateErr.sSystemState = UGT_E_SS_WAIT_M;
		UG_sSysStateErr.sSysTime.ReStartTime = US_RE_STARTUP_OVERCURR_TIME_S32;
	}
	else if (UG_sSysStateErr.uSystemError.Bits.OverIAsIBsICs == TRUE)
	{
		UG_sSysStateErr.sSystemStatePre = UG_sSysStateErr.sSystemState;
		UG_sSysStateErr.sSystemState = UGT_E_SS_WAIT_M;
		UG_sSysStateErr.sSysTime.ReStartTime = US_RE_STARTUP_OVERCURR_TIME_S32;
		//		UG_sSysStateErr.sSystemStatePre = UG_sSysStateErr.sSystemState;
		//		UG_sSysStateErr.sSystemState = UGT_E_SS_INIT_B;
	}
	else if (UG_sSysStateErr.uSystemError.Bits.OverVoltage == TRUE)
	{
		UG_sSysStateErr.sSystemStatePre = UG_sSysStateErr.sSystemState;
		UG_sSysStateErr.sSystemState = UGT_E_SS_WAIT_M;
		UG_sSysStateErr.sSysTime.ReStartTime = US_RE_STARTUP_OVERVOLT_TIME_S32;
	}
	else if (UG_sSysStateErr.uSystemError.Bits.UnderVoltage == TRUE)
	{
		UG_sSysStateErr.sSystemStatePre = UG_sSysStateErr.sSystemState;
		UG_sSysStateErr.sSystemState = UGT_E_SS_WAIT_M;
		UG_sSysStateErr.sSysTime.ReStartTime = US_RE_STARTUP_UNDERVOLT_TIME_S32;
	}
	else if (UG_sSysStateErr.uSystemError.Bits.StartupFailContious == TRUE)
	{
		UG_sSysStateErr.sSystemStatePre = UG_sSysStateErr.sSystemState;
		UG_sSysStateErr.sSystemState = UGT_E_SS_WAIT_M;
		UG_sSysStateErr.sSysTime.ReStartTime = US_RE_STARTUP_TIME_LONG_S32;
	}
	else if (UG_sSysStateErr.uSystemError.Bits.StartupFail == TRUE)
	{
		UG_sSysStateErr.sSysTime.StartupFailCount++;
		UG_sSysStateErr.sSystemStatePre = UG_sSysStateErr.sSystemState;
		UG_sSysStateErr.sSystemState = UGT_E_SS_WAIT_M;
		UG_sSysStateErr.sSysTime.ReStartTime = UG_sSystemControllers.sMotorPara.s32RestartWaitTimeTotal;
	}
	else if (UG_sSysStateErr.uSystemError.Bits.NoWater == TRUE)
	{
		UG_sSysStateErr.sSystemStatePre = UG_sSysStateErr.sSystemState;
		UG_sSysStateErr.sSystemState = UGT_E_SS_WAIT_M;
		UG_sSysStateErr.sSysTime.ReStartTime = US_RE_STARTUP_NOWATER_TIME_S32;
	}
	else if (UG_sSysStateErr.uSystemError.Bits.OverTempIGBT == TRUE)
	{
		UG_sSysStateErr.sSystemStatePre = UG_sSysStateErr.sSystemState;
		UG_sSysStateErr.sSystemState = UGT_E_SS_WAIT_M;
		UG_sSysStateErr.sSysTime.ReStartTime = US_IPM_FAULT_RECOVERY_TIME_S32;
	}
	else
	{
		UG_sSysStateErr.sSystemStatePre = UG_sSysStateErr.sSystemState;
		UG_sSysStateErr.sSystemState = UGT_E_SS_INIT_B;
	}
}

void US_vHardwareOverCurCalcAMP(void)
{
	u16 u16temp = 0;
	u16temp = UG_sSystemControllers.sMotorPara.f32HardOverCurrent * UG_sSystemControllers.sMotorPara.f32Rsdc * UG_sSystemControllers.sMotorPara.f32GainRsdc * 205 + 410; //(HDOC*Rsdc*Grsdc+2)/5*1024
	if (u16temp > 1023)
		u16temp = 1023;
	DAC_SetDac_10B_Data(DAC1, DAC_Align_10B_R, u16temp); // 850/1024*4等于比较值
	DAC_SoftwareTriggerCmd(DAC1, ENABLE);
}