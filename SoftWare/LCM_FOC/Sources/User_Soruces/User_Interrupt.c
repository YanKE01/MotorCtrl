#define EXPORT_USER_INTERRUPT_H
	#include "User_Interrupt.h"
#undef EXPORT_USER_INTERRUPT_H

/*******************************************************************************
* Function Name  : ADC1_2_IRQHandler
* Description    : This function handles ADC1 and ADC2 global interrupts requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
//改完后完整版执行时间38us
void DMAC_CH1_2_Handler(void)
{

	UA_vADSampleAll(&UG_sADSampleAll);	
	UA_vIABCConstruct(&UG_sADSampleAll, &UG_sCurrentAll.sCurrentAbc);
	UA_vVoltageConstruct(&UG_sADSampleAll, &UG_sVoltageAll.sVoltageAbc);
	//	---------5.2us-------------------------------
	switch(UG_sSysStateErr.sSystemState)
  {
    case UGT_E_SS_IDLE_A:																	break;
    case UGT_E_SS_INIT_B:																	break;
    case UGT_E_SS_STOP_C:						MDS_vStop(); 					break;
    case UGT_E_SS_START_D:																break;
		case UGT_E_SS_PRECHARGE_E:			MDS_vPrecharge();			break;
    case UGT_E_SS_TRACK_F:					MDS_vTrack();					break;
    case UGT_E_SS_IDENTIFY_G:				MDS_vIdentify();  	  break;	
    case UGT_E_SS_ALIGNMENT_H: 			MDS_vAlignment();	   	break;
		case UGT_E_SS_OPENLOOP_I: 			MDS_vOpenloop();	   	break;
    case UGT_E_SS_CLOSEDLOOP_J:			MDS_vClosedloop();   	break;
		case UGT_E_SS_BRAKE_K:	 				MDS_vBreak();   			break;
		case UGT_E_SS_FAULT_L:	 				MDS_vFault();   			break;
		case UGT_E_SS_WAIT_M:						MDS_vWait(UG_sSysStateErr.sSysTime.ReStartTime);		break;		
    default:break;
	}

//============DAC module========================================================================
	DAC_SetDac_10B_Data(DAC0,DAC_Align_10B_R,(UG_sCurrentAll.sCurrentAbc.s16As + _IQ15(1.0))>>6);//UG_sPositionAll.PosStateObserver>>6);//
  DAC_SoftwareTriggerCmd(DAC0,ENABLE); 
//===========end DAC module======================================================================

	DMA_ClearITPendingBit(DMA1_FLAG_TC1);	
}


void SysTick_Handler(void)
{
	switch (UG_sSystemControllers.sSPD.u16LoopIndex)
	{
		case TASK10:
		{
			UG_sSystemControllers.sSPD.s32Ref = UG_sSystemControllers.sCommandAll.s32SpdCommand;
			UG_sSystemControllers.sSPD.s32Fbk = UG_sSystemControllers.sCommandAll.s32SpdUse;
			if ((UG_sSysStateErr.sSystemState != UGT_E_SS_WAIT_M)&&(UG_sSysStateErr.sSystemState >= UGT_E_SS_CLOSEDLOOP_J))
			{
				MDS_vCurLimit(UG_sSystemControllers.sSPD.s32Fbk);
				MDS_vPIRegulatorIQ24(&UG_sSystemControllers.sSPD);
				if (UG_sSystemControllers.sSPD.u16En == TRUE)
				{
					UG_sSystemControllers.sCommandAll.s32IqCommand = UG_sSystemControllers.sSPD.s32Out;
				}		
			}
			break;			
		}
		case TASK9:
		{
			if(UG_sSysStateErr.sSoftClose.u8SoftCloseEn == TRUE)
			{
				UG_sSystemControllers.sCommandAll.s32UdcCommand = UPDS_UDC_COMMAND ;
				UG_sSystemControllers.sCommandAll.s32UdcUse     = UG_sVoltageAll.sVoltageAbc.s16UdcMeas << 12;
				
				UG_sSystemControllers.sUdc.s32Ref = UG_sSystemControllers.sCommandAll.s32UdcCommand;
				UG_sSystemControllers.sUdc.s32Fbk = UG_sSystemControllers.sCommandAll.s32UdcUse;
				MDS_vPIRegulatorIQ24(&UG_sSystemControllers.sUdc);	
				
				UG_sSystemControllers.sCommandAll.s32IdCommand =UG_sSystemControllers.sUdc.s32Out;
			}			
			break;
		}
		case TASK8:
		{						
			break;
		}
		case TASK7:
		{
			if(UG_sUsartData.sUsartEvent.Bits.WriteFlashing == 0)
			{
				UU_vUartData1Prepare();
				UU_vSendDataDMA(DMA1_Channel0, (uint32_t)&UG_sUsartData.u8SendData1, UPDS_UART_SIZE);			
			}
			break;
		}
	  case TASK6:
		{
			#if (UPDS_POWER_CONTROL_SEL == UPDS_POWER_CONTROL_SOFTWARE)				
				MDS_vConstantPowerDQ(&MDS_sCP, UG_sVoltageAll.sVoltageDqCalc.s16Dr, UG_sCurrentAll.sCurrentDqUse.s16Dr, UG_sVoltageAll.sVoltageDqCalc.s16Qr, UG_sCurrentAll.sCurrentDqUse.s16Qr);
			#elif (UPDS_POWER_CONTROL_SEL == UPDS_POWER_CONTROL_HARDWARE)			
				if(UG_sSysStateErr.uControlReg.Bits.ConstCurrent == UPDS_CONCURRENT_ENABLE)
					MDS_vConstantPower(&MDS_sCP, UG_sADSampleAll.s16IdcLPFTem, UG_sSystemControllers.sMotorPara.s32NWUdcValue);
				else
					MDS_vConstantPower(&MDS_sCP, UG_sADSampleAll.s16IdcLPFTem, UG_sADSampleAll.u16UdcTem);			
			#endif

			if(UG_sSysStateErr.uControlReg.Bits.ControlMode == UGT_E_CM_POWER)
			{
				UG_sSystemControllers.sCommandAll.s32SpdCommand = MDS_sCP.PI_CP.s32Out;	
			}						
			break;
		}
		case TASK5:
		{			
			break;
		}
		case TASK4:
		{
			#if (UPDS_DCURRENT_CHOOSE == UPDS_DCURRENT_FW)			
			MDS_sFW.u32Count++;
			if((UG_sSysStateErr.sSystemState >= UGT_E_SS_CLOSEDLOOP_J)&&(MDS_sFW.u32Count>=100))
			{
				MDS_vFluxWeakening(&MDS_sFW, UG_sVoltageAll.sVoltageDqUse.s16Dr, UG_sVoltageAll.sVoltageDqUse.s16Qr);
				MDS_sFW.u32Count = 100;
			}
			#elif	(UPDS_DCURRENT_CHOOSE == UPDS_DCURRENT_MTPA)
			MDS_vMTPA(&MDS_sMTPA,UG_sSystemControllers.sCommandAll.s32IqUse);
			#endif
			break;
		}
		case TASK3:
		{	
			MDS_vNoWaterCal(&MDS_sNW,UG_sSystemControllers.sCommandAll.s32IqUse,UG_sSystemControllers.sCommandAll.s32SpdUse);			
			break;
		}
		case TASK2:
		{
			if (UG_sSysStateErr.uControlReg.Bits.SevenOrFivePWMSwitchingEn == UPDS_5_7STAGE_SWITCHING_ENABLE)
			{
				if(UG_sSystemControllers.sSPD.s32Fbk > UPDS_5STAGE_SPD_H)				UG_sVoltageAll.sSvgen.u8PWM5Stage  = 1 ;
				else if (UG_sSystemControllers.sSPD.s32Fbk < UPDS_7STAGE_SPD_H)	UG_sVoltageAll.sSvgen.u8PWM5Stage  = 0 ;
			}
			else
			{
				UG_sVoltageAll.sSvgen.u8PWM5Stage  = 0;
			}
			break;
		}
		case TASK1:
		{
			if ((UG_sSysStateErr.sSystemState != UGT_E_SS_WAIT_M)&&(UG_sSysStateErr.sSystemState >= UGT_E_SS_CLOSEDLOOP_J))
			{
				if (UG_sSysStateErr.uSystemError.Bits.OverLoad == FALSE)
				{	
					TG_sCommandRef.s32TargetValue = UG_sSystemControllers.s32Command;
				}
				else
				{
					TG_sCommandRef.s32TargetValue = UG_sSystemControllers.s32Command;
				}
				MDS_vRampGen(&TG_sCommandRef);//4us
				switch(UG_sSysStateErr.uControlReg.Bits.ControlMode)
				{
					case UGT_E_CM_VF:
						UG_sSystemControllers.sSPD.u16En = FALSE;
						UG_sSystemControllers.sID.u16En = FALSE;
						UG_sSystemControllers.sIQ.u16En = FALSE;						
						break;
					case UGT_E_CM_IF:
						if(UG_sSysStateErr.sSystemState == UGT_E_SS_CLOSEDLOOP_J)
						{
							UG_sSystemControllers.sCommandAll.s32SpdCommand = TG_sCommandRef.s32SetpointValue + MDS_sCP.PI_CP.s32Out;	
							MDS_sCP.PI_CP.s32Ref = MDS_sCP.s32PowerMax;				//限制速度环下最大输出功率						
						}
						else
						{
						UG_sSystemControllers.sCommandAll.s32IqCommand = TG_sCommandRef.s32SetpointValue;	
						UG_sSystemControllers.sCommandAll.s32IdCommand = 0;
						UG_sSystemControllers.sSPD.u16En = FALSE;		
						}							
						break;
					case UGT_E_CM_TORQUE:
						UG_sSystemControllers.sCommandAll.s32IqCommand = TG_sCommandRef.s32SetpointValue;	
						if(UG_sSystemControllers.sCommandAll.s32IqCommand>_IQ(0.2))						UG_sSystemControllers.sCommandAll.s32IqCommand=_IQ(0.2);	
						break;
					case UGT_E_CM_SPEED:
						UG_sSystemControllers.sCommandAll.s32SpdCommand = TG_sCommandRef.s32SetpointValue + MDS_sCP.PI_CP.s32Out;	
						MDS_sCP.PI_CP.s32Ref = MDS_sCP.s32PowerMax;				//限制速度环下最大输出功率
						break;
					case UGT_E_CM_POWER:
						MDS_sCP.PI_CP.s32Ref = TG_sCommandRef.s32SetpointValue;	
						if(MDS_sCP.PI_CP.s32Ref > MDS_sCP.s32PowerMax)
						{
							MDS_sCP.PI_CP.s32Ref=MDS_sCP.s32PowerMax;
						}
						break;
					case UGT_E_CM_TEST:
						break;
					default: 
						break;				
				}		
			}
			if(UG_sUsartData.sUsartEvent.Bits.WriteFlashing == 0)
			{
				UU_vUartData2Prepare();
				UU_vSendDataDMA(DMA1_Channel0, (uint32_t)&UG_sUsartData.u8SendData2, UPDS_UART_SIZE);				
			}
			break;			
		}
		default:break;
	}

	if(UPDS_FG_SEL==UPDS_FG_ENABLE)																			MDS_vFGRPM();
	
	UG_sSystemControllers.sSPD.u16LoopIndex--;
	if(UG_sSystemControllers.sSPD.u16LoopIndex == 0)UG_sSystemControllers.sSPD.u16LoopIndex = UPDS_SPD_LOOP_COUNT;
	if(UG_sSysStateErr.uControlReg.Bits.ControlMode != UGT_E_CM_TEST)
	{
		if ((UG_sSysStateErr.sSystemState != UGT_E_SS_WAIT_M)&&(UG_sSysStateErr.sSystemState != UGT_E_SS_FAULT_L)&&(UG_sSysStateErr.sSystemState >= UGT_E_SS_INIT_B))
		{
//			US_vSysErrorCheck();		
		}
	}
}
/*******************************************************************************
* Function Name  : TIM1_BRK_IRQHandler
* Description    : This function handles TIM1 Break interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UI_vTIM1BRKInterrupt(void)
{
  TIM_ClearITPendingBit(TIM1, TIM_IT_Break);
}

/*******************************************************************************
* Function Name  : TIM1_UP_IRQHandler
* Description    : This function handles TIM1 overflow and update interrupt 
*                  request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UI_vTIM1UPInterrupt(void)
{
  TIM_ClearFlag(TIM1, TIM_FLAG_Update); 	
}

void TIM1_NON_CC_Handler(void)
{
  if(TIM1->SR_b.BIF== TRUE)
	{
		TIM_ClearITPendingBit(TIM1, TIM_IT_Break);		
	}

	if(TIM1->SR_b.B2IF == TRUE)
	{
		UG_sSysStateErr.uSystemError.Bits.HardOverCurrent = TRUE;			
		UG_sSysStateErr.sSystemState = UGT_E_SS_FAULT_L;
		UG_sSysStateErr.sSystemStatePre = UG_sSysStateErr.sSystemState;
		TIM_ClearITPendingBit(TIM1, TIM_IT_Break2);		
	}
}
/*******************************************************************************
* Function Name  : UART0_Handler
* Description    : This function handles UART0 receive and send interrupt 
*                  request.
*                ：串口通信中断，上位机调试用
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
u8 guartreceivetimes=0;
void UART0_Handler(void)
{
	if (UART_GetITStatus(UART0, UART_IT_RX) == SET)
	{
		guartreceivetimes++;
		UG_sUsartData.u8ReceiveData[UG_sUsartData.u8UartRecIndex++] = UART_ReceiveData(UART0);
		if(UG_sUsartData.u8UartMode == 0)
		{
			if(UG_sUsartData.u8ReceiveData[0] == 0x11)
			{
				UG_sUsartData.u8UartMode = UART_SET;
				UG_sUsartData.u8UartRecCountNum = UPDS_UART_REC_COMMAND1_LENGTH;
				UG_sUsartData.eCommand = UGT_E_UC_COMMAND1;				
			}
			else if(UG_sUsartData.u8ReceiveData[0] == 0x22)
			{
				UG_sUsartData.u8UartMode = UART_START;
				UG_sUsartData.u8UartRecCountNum = UPDS_UART_REC_COMMAND2_LENGTH;
				UG_sUsartData.eCommand = UGT_E_UC_COMMAND2;	
			}
			else
			{
				UG_sUsartData.u8UartRecIndex=0;			
			}
		}
		
		if(UG_sUsartData.u8UartMode != 0)
		{
			if(UG_sUsartData.u8UartRecIndex == UG_sUsartData.u8UartRecCountNum)
			{
				if(UU_u8UARTRecCheck()) 
				{
					UG_sUsartData.sUsartEvent.Bits.ReceiceFinish = 1;
					if(UG_sUsartData.eCommand == UGT_E_UC_COMMAND2)
					{
						if(UG_sUsartData.u8ReceiveData[1]==0x01)
						{
							UG_sUsartData.s16UartTargetValue = (s16)UG_sUsartData.u8ReceiveData[4]*327;
						}
						else
						{
							UG_sUsartData.s16UartTargetValue = (s16)UG_sUsartData.u8ReceiveData[4]*0;
						}
						UG_sUsartData.u8ScopeSelect[0] = (UG_sUsartData.u8ReceiveData[5]>>4) & 0x0F;
						UG_sUsartData.u8ScopeSelect[1] = (UG_sUsartData.u8ReceiveData[5]) & 0x0F;
						UG_sUsartData.u8ScopeSelect[2] = (UG_sUsartData.u8ReceiveData[6]>>4) & 0x0F;
						UG_sUsartData.u8ScopeSelect[3] = (UG_sUsartData.u8ReceiveData[6]) & 0x0F;					
					}
					else if(UG_sUsartData.eCommand == UGT_E_UC_COMMAND1)
					{
						UG_sUsartData.sUsartEvent.Bits.UpdateSetPara 	= 1;
					}
				}
				else
				{
					UG_sUsartData.sUsartEvent.Bits.ReceiceFinish = 0;
				}
				UG_sUsartData.u8UartRecCountNum = 0;
				UG_sUsartData.u8UartRecIndex = 0;
				UG_sUsartData.u8UartMode = 0;	
			}

		}
		UART_ClearITPendingBit(UART0, UART_IT_RX);
	}
}


