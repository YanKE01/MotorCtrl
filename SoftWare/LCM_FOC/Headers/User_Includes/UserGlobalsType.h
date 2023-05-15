/******************** (C) COPYRIGHT 2021 LINGXIN Microelectronics***************
* File Name          : MC_GlobalsType.h
* Author             : LX Motor Lab  
* Date  						 : 2021-12-16
* Description        : Global variables
*******************************************************************************/
#ifndef __MC_TYPE_H
#define __MC_TYPE_H

#include "lcm32f037_lib.h"
#include "UserIncludes.h"

/* Includes ------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
typedef enum UGT_E_SS_TASK_
{
	TASK1		= 1,
	TASK2		= 2, 	
	TASK3		= 3,
	TASK4 	= 4, 
	TASK5		= 5,
	TASK6		= 6, 	
	TASK7		=	7, 
	TASK8		=	8,
	TASK9		= 9, 
	TASK10	= 10, 
} UGT_E_SS_TASK;

typedef struct UGT_S_CURRABC_STRU_
{
  s16 s16As;
  s16 s16Bs;
	s16 s16Cs;
	s16 s16Idc;
	s16 s16IdcLPF;
	u16 u16AsOffest;
	u16 u16BsOffest;
	u16 u16CsOffest;
	u16 u16IdcOffest;
	u16 u16IdcLPFOffest;
	u16 u16SampleChooseNum;
	u16 u16SampleErr;
	s32 s32IAsBsCsSum;
	s16 s16IAsAbs;
	s16 s16IBsAbs;
	s16 s16ICsAbs;
	s16 s16IAsAbsLPF;
	s16 s16IBsAbsLPF;
	s16 s16ICsAbsLPF;	
	s16 s16IAbsMaxHalf;
} UGT_S_CURRABC_STRU;

typedef struct UGT_S_CURRALBE_STRU_
{
  s16 s16Alpha;
  s16 s16Beta;
	s16 s16CurMag;
	s32 s32CurMag;
} UGT_S_CURRALBE_STRU;

typedef struct UGT_S_CURRDQ_STRU_
{
  s16 s16Dr;
  s16 s16Qr;
} UGT_S_CURRDQ_STRU;

typedef struct UGT_S_CURRALBE_RESTART_STRU_
{
  s16 s16Alpha[2];
  s16 s16Beta[2];
} UGT_S_CURRALBE_RESTART_STRU;

typedef struct UGT_S_VOLTABC_STRU_
{
  s16 s16UdcMeas;
	s16 s16UdcSamplePUGain;
	s16 s16UxnSamplePUGain;
	s16 s16UdcFluctuateGain;
	s16 s16MfuncV1;  		// Input: Modulation voltage phase A (pu)
	s16 s16MfuncV2;			// Input: Modulation voltage phase B (pu)	
	s16 s16MfuncV3;			// Input: Modulation voltage phase C (pu) 
	s16 s16UAsCalc;
  s16 s16UBsCalc;
	s16 s16UCsCalc;
	s16 s16UAsMeas;
  s16 s16UBsMeas;
	s16 s16UCsMeas;
	s16 s16UsnMeas;
	s16 s16Tem;
} UGT_S_VOLTABC_STRU;

typedef struct UGT_S_ADSAMPLEALL_STRU_
{
  s16 s16IAsTem;
  s16 s16IBsTem;
	s16 s16ICsTem;
	s16 s16IdcTem;
	s16 s16IdcLPFTem;
	u16 u16IAsOffest;
	u16 u16IBsOffest;
	u16 u16ICsOffest;
	u16 u16IdcOffest;
	u16 u16IdcLPFOffest;	
	s16 s16UAnTem;
  s16 s16UBnTem;
	s16 s16UCnTem;
	u16 u16UdcTem;
	s16 s16VSPTem;
	s16 s16VSPLPF;
  s16 s16IGBTTemp;
	s16 s16IGBTTempLPF;
	u16 u16MotorTemp;
	u16 u16PFCUac;
	u16 u16VSPOffest;
  u16 s16IGBTTempOffest;
	u16 u16MotorTempOffest;
	u16 u16PFCUacOffest;
} UGT_S_ADSAMPLEALL_STRU;

typedef struct UGT_S_VOLTALBE_STRU_
{
  s16 s16Alpha;
  s16 s16Beta;
} UGT_S_VOLTALBE_STRU;

typedef struct UGT_S_VOLTDQ_STRU_
{
  s32 s16Dr;
  s32 s16Qr;
} UGT_S_VOLTDQ_STRU;

typedef struct UGT_S_VOLTDQ_RCCOMP_STRU_
{
  s32 s32DrComp[50];
  s32 s32QrComp[50];
	s32 s32DrCompUse;
	s32 s32QrCompUse;
	s32 s32IdErrUse;
	s32 s32IqErrUse;
	u16 u16Count;
} UGT_S_VOLTDQ_RCCOMP_STRU;

typedef struct UGT_S_SVGEN_STRU_	
{ 
	_iq  s16Ualpha; 	// Input: reference alpha-axis phase voltage 
	_iq  s16Ubeta;		// Input: reference beta-axis phase voltage 
	_iq  s32Ta;				// Output: reference phase-a switching function		
	_iq  s32Tb;				// Output: reference phase-b switching function 
	_iq  s32Tc;				// Output: reference phase-c switching function
	_iq  s32tmp1;			// Variable: temp variable
	_iq  s32tmp2;			// Variable: temp variable
	_iq  s32tmp3;			// Variable: temp variable
	u16  u16VecSector;		// Space vector sector
	u8	 u8PWM5Stage;
} UGT_S_SVGEN_STRU;

typedef struct UGT_S_PWMDUTY_STRU_	
{ 
		u16 u16PeriodMax;   // Parameter: PWM Half-Period in CPU clock cycles (Q0)
		u16 u16HalfPerMax;	// Parameter: Half of PeriodMax (Q0)
		u16 u16Deadband;    // Parameter: PWM deadband in CPU clock cycles (Q0) 
		_iq s32MfuncC1;        // Input: EPWM1 A&B Duty cycle ratio (Q24)
		_iq s32MfuncC2;        // Input: EPWM2 A&B Duty cycle ratio (Q24)
		_iq s32MfuncC3;        // Input: EPWM3 A&B Duty cycle ratio (Q24)
} UGT_S_PWMDUTY_STRU;

typedef struct UGT_S_DEADTIMECOMP_STRU_	
{ 
	s32 s32DTMfunC1;
	s32 s32DTMfunC2;
	s32 s32DTMfunC3;
	s32 s32DTCompC1;
	s32 s32DTCompC2;
	s32 s32DTCompC3;
	u16 u16DTCompBand;          //(0.02); 0x001E //IQ15
	s16 s16DTCompOffset;        //编译时变量改变，上一拍值保存下
	s16 s16IqLPF;
	s16 s16IqLPFGain;
	s16 s16IqAbs;
	s16 s16DTComp;      				//0x216; 
	u16 u16DTCompEn; 
	s16 s16DTCompOnIqAmp;
	s16 s16DTCompOffIqAmp;
} UGT_S_DEADTIMECOMP_STRU;

typedef struct UGT_S_TRIG_STRU_
{
  s16 s16Cos;
  s16 s16Sin;
} UGT_S_TRIG_STRU;


typedef struct UGT_S_PICONTROLLER_STRU_
{  
	s32  s32Ref;   			// Input: reference set-point
	s32  s32Fbk;   			// Input: feedback
	s32  s32Out;   			// Output: controller output 
	s32  s32Kp;				  // Parameter: proportional loop gain
	s32  s32Ki;			    // Parameter: integral gain
	s32  s32Umax;			  // Parameter: upper saturation limit
	s32  s32Umin;			  // Parameter: lower saturation limit
	s32  s32Err;				  // Data: proportional term
	s32  s32ui;			  	// Data: integral term
	s32  s32v1;			  	// Data: pre-saturated controller output
	s32  s32i1;			  	// Data: integrator storage: ui(k-1)
	s32  s32w1;			  	// Data: saturation record: [u(k-1) - v(k-1)]
	u16  u16En;
	u16	 u16LoopIndex;
} UGT_S_PICONTROLLER_STRU;

typedef struct UGT_S_PICONTROLLERIQ12_STRU_
{  
	s16  s16Ref;   			// Input: reference set-point
	s16  s16Fbk;   			// Input: feedback
	s16  s16Out;   			// Output: controller output 
	s16  s16Kp;				  // _IQ8
	s16  s16Ki;			    // _IQ12
	s16  s16Umax;			  // Parameter: upper saturation limit
	s16  s16Umin;			  // Parameter: lower saturation limit
	s16  s16Err;				  // Data: proportional term
	s16  s16ui;			  	// Data: integral term
	s16  s16v1;			  	// Data: pre-saturated controller output
	s16  s16i1;			  	// Data: integrator storage: ui(k-1)
	s16  s16w1;			  	// Data: saturation record: [u(k-1) - v(k-1)]
	u16  u16En;
	u16	 u16LoopIndex;
} UGT_S_PICONTROLLERIQ12_STRU;

typedef struct UGT_S_COMMAND_STRU_
{
	s32  	s32UdcCommand;  
	s32  	s32SpdCommand;
	s32  	s32IdCommand;
	s32  	s32IqCommand;
	s32 	s32UdcUse;	
	s32 	s32SpdUse;
	s32 	s32IdUse;
	s32 	s32IqUse;
} UGT_S_COMMAND_STRU;
									
typedef enum UGT_E_SS_ENUM_
{
	UGT_E_SS_IDLE_A				= 0,
	UGT_E_SS_INIT_B				= 1,
	UGT_E_SS_STOP_C				= 2, 	
	UGT_E_SS_START_D			= 3,
	UGT_E_SS_PRECHARGE_E 	= 4, 
	UGT_E_SS_TRACK_F			= 5,
	UGT_E_SS_IDENTIFY_G		= 6, 	
	UGT_E_SS_ALIGNMENT_H	=	7, 
	UGT_E_SS_OPENLOOP_I		=	8,
	UGT_E_SS_CLOSEDLOOP_J	= 9, 
	UGT_E_SS_BRAKE_K			= 10, 
	UGT_E_SS_FAULT_L			= 11,
	UGT_E_SS_WAIT_M				= 12,
	UGT_E_SS_WRITE_FLASH	= 13
	
} UGT_E_SS_ENUM;



typedef enum UGT_E_RESTART_ENUM_
{
	UGT_E_RS_FIRST_A			= 0,
	UGT_E_RS_INTERVAL_B		= 1,
	UGT_E_RS_SECOND_C			= 2, 
	UGT_E_RS_INTERVAL_D		= 3,
	UGT_E_RS_END_E				= 4,
} UGT_E_RESTART_ENUM;


typedef enum UGT_E_CONTROL_MODE_ENUM_
{
	UGT_E_CM_VF						= 0,
	UGT_E_CM_IF						= 1,
	UGT_E_CM_TORQUE				= 2, 
	UGT_E_CM_SPEED				= 3,
	UGT_E_CM_POWER				= 4,
	UGT_E_CM_TEST					= 5,
} UGT_E_CONTROL_MODE_ENUM;

typedef enum UGT_E_DEBUG_MODE_ENUM_
{	
	UGT_E_DM_SOFTTOOL		= 0, 
	UGT_E_DM_VSP				= 1,
	UGT_E_DM_PWM				= 2,
	UGT_E_DM_SOFTKEIL		= 3,
} UGT_E_DEBUG_MODE_ENUM;

typedef enum UGT_E_RESTART_METHOD_ENUM_
{
	UGT_E_FLYING_RESTART_SOFTWARE				= 0,
	UGT_E_FLYING_RESTART_HARDWARE				= 1,
} UGT_E_RESTART_METHOD_ENUM;

typedef enum UGT_E_CHIP_ENUM_
{
	UGT_E_037_24PIN				= 0,
	UGT_E_037_32PIN				= 1,
} UGT_E_CHIP_ENUM;

typedef enum UGT_E_SSE_ENUM_
{
	UGT_E_SSE_OK 	= 0, 
	UGT_E_SSE_OC 	= 1,
	UGT_E_SSE_OL 	=	2,
	UGT_E_SSE_OV 	= 3,
	UGT_E_SSE_UV 	= 4,
	UGT_E_SSE_OS 	= 5,
	UGT_E_SSE_US	=	6,
	UGT_E_SSE_OTIPM 	= 7,
	UGT_E_SSE_OTMOTER = 8,
	UGT_E_SSE_SWITCH = 9,
	UGT_E_SSE_OW = 10				/*wind speed is lagre*/
} UGT_E_SSE_ENUM;


typedef enum UGT_E_UART_COMMAND_ENUM_
{
	UGT_E_UC_COMMAND1			= 0,
	UGT_E_UC_COMMAND2			= 1,
} UGT_E_UART_COMMAND_ENUM;

typedef struct UGT_S_SSE_BITS_
{      
   u16 OverVoltage:		1;       	// 过压 
   u16 UnderVoltage:	1;        // 欠压 
	 u16 OverCurrent:		1;   			// 软件过流
	 u16 HardOverCurrent:	1;      // 硬件过流
	 u16 OverTempMotor:	1;        // 电机过温 
	 u16 OverTempIGBT:	1;				// IPM过温
	 u16 StartupFail:		1;				// 启动失败
	 u16 StartupFailContious: 1;	// 连续启动失败
	 u16 OverLoad:			1;       	// 软件过载，降额运行
	 u16 OverWindSpeed:	1;				// 超速
	 u16 LosePhase:			1;
	 u16 OverIAs:				1;
	 u16 OverIBs:				1;
	 u16 OverICs:				1;
	 u16 OverIAsIBsICs: 1;
	 u16 NoWater: 			1;
	 u16 Breaken: 			1;	

}UGT_S_SSE_BITS;

typedef struct UGT_S_CR_BITS_
{      
   u16 MotorDirection:						1;   			// 电机转动正方向
   u16 LowOrHighVoltage:					1;       	// 欠压或过压
   u16 LowOrHighSpeed:						1;       	// 低速或高速 
   u16 SevenOrFivePWMSwitchingEn:	1;        // 七五段式切换使能
   u16 PWMFreqSwitchingEn:				1;      	// 频率切换
	 u16 IPDEn:											1;
	 u16 ControlMode:							4;
	 u16 ChipType:								2;
	 u16 FlyingRestartMethod:			1;
	 u16 CommandType:							2;
	 //UGT_E_CONTROL_MODE_ENUM 		ControlMode:							4;
	 //UGT_E_CHIP_ENUM				 		ChipType:									2;
	 //UGT_E_RESTART_METHOD_ENUM 	FlyingRestartMethod:			1;
	 //UGT_E_DEBUG_MODE_ENUM	 		CommandType:							2;
	 u16 ReceivedDataType:          											1;
	 u16 ConstCurrent:						1;
}UGT_S_CR_BITS;

typedef struct UGT_S_PWMMODE_BITS_
{      
   u8  PWMMode;
	 u8  PWMModePre;
	 s32 SpeedSwitchLow;
	 s32 SpeedSwitchHigh;
}UGT_S_PWMMODE_BITS;

typedef struct UGT_S_RESRART_
{      
	u8  u8RestartDirect;
	UGT_E_RESTART_METHOD_ENUM	eRestartMethod;
}UGT_S_RESRART;

typedef union UGT_U_SSE_ALL_
{
	u16 						All;
	UGT_S_SSE_BITS 	Bits; 	
}UGT_U_SSE_ALL;

typedef union UGT_U_CR_ALL_
{
	u16 						All;
	UGT_S_CR_BITS 	Bits; 	
}UGT_U_CR_ALL;

typedef struct UGT_S_SSE_TIMECOUNT_
{      
   s32 OCCount;		
   s32 OLCount;
   s32 OVCount;  
   s32 UVCount;	
   s32 OTIPMCount;
	 s32 IPMFaultCount;	
   s32 OTMotorCount;
	 u8  StartupFailCount;
	 s32 StartupSwitchFailCount;
	 s32 StartupStartFailCount;
	 s32 NoWaterCount;	
	
	 u32 ReStartTime;	
	 s32 OverWindSpeedCount;
	 s32 PrechargeCount;
	 s32 BreakCount;
	 s32 LosePhaseCount;
	 s32 OverIAsCount;
	 s32 OverIBsCount;
	 s32 OverICsCount;
	 s32 RestartingCount;
	 s32 RestartingShortNum;
	 s32 RestartingIntervalNum;
	 s32 RestartingInterval2Num;
	 s32 RestartGain;
	 s32 RestartGainPos;
	 s32 UVFlashWriteCount;
	 u16 SoftClosedCount;	 
}UGT_S_SSE_TIMECOUNT;

typedef struct UGT_S_SSE_SOFTCLOSE_
{      
	s16 	s16SystemSwitch;	
	u8 		u8VSP_LOCK;
	u8 		u8SoftCloseEn;
	u8 		u8SoftCloseLastEn;  	
}UGT_S_SSE_SOFTCLOSE;
	
typedef enum UGT_E_AlIGNMENT_ENUM_
{
	UGT_E_ALIGNMENT_FIRST_A			= 0,
	UGT_E_ALIGNMENT_SECOND_B		= 1,
} UGT_E_AlIGNMENT_ENUM;

typedef enum UGT_E_IFSTARTUP_ENUM_
{
	UGT_E_IFSTARTUP_ACC_A				= 0,
	UGT_E_IFSTARTUP_CONTIUE_B		= 1,
	UGT_E_IFSTARTUP_SWITCH_C		= 2,
	UGT_E_IFSTARTUP_CLOSED_D		= 4
} UGT_E_IFSTARTUP_ENUM;

typedef enum UGT_E_VSPCHECK_ENUM_
{
	UGT_E_VSP_CLOSED_A			= 0,
	UGT_E_VSP_OPEN_B				= 1
} UGT_E_VSPCHECK_ENUM;

typedef enum UGT_E_DIRECTION_ENUM_
{
	UGT_E_FORWARD 	= 0, 
	UGT_E_BACKWARD 	= 1
} UGT_E_DIRECTION_ENUM;

typedef struct UGT_S_MOTORPARAMETERS_STRU_
{
	UGT_U_CR_ALL sControlWord;
	f32 f32Rs;
	f32 f32Ld;
	f32 f32Lq;
	f32 f32PsiPM;
	u8  PolePairs;
	f32 f32J;
	f32 f32RatedCurrent;
	f32 f32RatedSpeed;

	f32 f32Rsp;
	f32 f32GainRsp;	
	f32 f32GainVdc;
	f32 f32Rsdc;
	f32 f32GainRsdc;	
	f32 f32Udc;
	u16 u16DeadtimeNs;

	u16 u16fB;
	f32 f32AccRate;
	f32 f32StartCurPU;
	u16 u16PWMFre2;
	f32 f32BandWidth;	
	
	f32 f32SpdKp;
	f32 f32SpdKi;
	f32 f32PowerKp;
	f32 f32PowerKi;
	f32 f32SpeedPowerLimit;
	f32 f32FluxWeakenKp;
	f32 f32FluxWeakenKi;
	f32 f32FluxWeakenOutMax;
	f32 f32ObsGainD;
	f32 f32ObsGainQ;
	f32 f32IPDPulseTime;
	f32 f32IPDIntervalTime;
	f32 f32SoftRestartPulse;
	f32 f32SoftRestartInterval;	
	
	f32 f32HardOverCurrent;
	f32 f32SoftOverCurrent;
	f32 f32SoftOCJudgeTime;
	f32 f32OverVoltage;
	f32 f32OVJudgeTime;
	f32 f32UnderVoltage;
	f32 f32UVJudgeTime;
	s16 s16OverMotorTemp;
	u16 u16MotorOTJudgeTime;
	s16 s16IPMOverTemp;
	u16 u16IPMOTJudgeTime;
	f32 f32StartUpMinSpeed;
	f32 f32SUMSJudgeTime;
	f32 f32RestartWaitTime;
	u16 u16StartUpTimes;
	

	f32 f32WB;
	f32 f32UB;
	f32 f32IB;
	f32 f32RB;
	f32 f32LB;
	f32 f32TB;
	f32 f32PsiB;	
	f32 f32TsCurrentPI1;
	f32 f32TsCurrentPI2;
	f32 f32PowerB;
	
	f32 f32LdP;
  f32 f32LqP;
	f32 f32RsP;
	f32 f32PsiP;
	f32 f32TsP1;
	f32 f32TsP2;
	
	s32 s32LdPU;
  s32 s32LqPU;
	s32 s32RsPU;
	s32 s32PsiPU;
	s32 s32TsPU1;	
	s32 s32TsPU2;
	
	u16 u16PWMPerood1;
	u16 u16PWMPerood2;
	u16 u16Deadtime;
	u16 u16DeadtimeComp1;
	u16 u16DeadtimeComp2;	
	
	u16 u16PWMFre1;
	
	s32 s32KpDAxis;
	s32 s32KpQAxis;
	s32 s32KiDAxis1;
	s32 s32KiQAxis1;
	s32 s32KiDAxis2;
	s32 s32KiQAxis2;
	s32 s32StartCurPU;
		
	s16 s16KpDAxis;
	s16 s16KpQAxis;
	s16 s16KiDAxis1;
	s16 s16KiQAxis1;
	s16 s16KiDAxis2;
	s16 s16KiQAxis2;
	
	s32 s32GainQErr1;
  s32 s32GainDErr1;
	s32 s32PLLInputGain1;
	s32 s32TsDivLq1;
	s32 s32TsRDivLq1;
	s32 s32TsLdDivLq1;
	s32 s32TsPsiDivLq1;
	s32 s32TsDivLd1;
	s32 s32TsRDivLd1;
	s32 s32TsLqDivLd1;
	s32 s32CompTime1;	
	
	s32 s32GainQErr2;
  s32 s32GainDErr2;
	s32 s32PLLInputGain2;
	s32 s32TsDivLq2;
	s32 s32TsRDivLq2;
	s32 s32TsLdDivLq2;
	s32 s32TsPsiDivLq2;
	s32 s32TsDivLd2;
	s32 s32TsRDivLd2;
	s32 s32TsLqDivLd2;
	s32 s32CompTime2;	
	
	s32 s32RestartShortTime;
  s32 s32SpdPIOutMax;
	s32 s32SpdPIOutMin;

	
	s16 s16OverCurrent;
	s16 s16OverVoltage;
	s16 s16UnderVoltage;
	s16 s16UnderVoltageFlashWrite;
	s32 s32OCJudgeTimeTotal;
	s32 s32OVJudgeTimeTotal;
	s32 s32UVJudgeTimeTotal;
	s32 s32MotorOTJudgeTimeTotal;
	s32 s32IPMOTJudgeTimeTotal;
	s32 s32SUMSJudgeTimeTotal;
	s32 s32RestartWaitTimeTotal;
	s32 s32StartUpMinSpeed;
	
	s32 s32NoWaterGain;
	s32 s32NoWaterJudgeTimeTotal;
	s32 s32NWUdcValue;
	
	u8 u8IPDPulseCountTotal;
	u8 u8IPDIntervalCountTotal;	
	u8 u8SoftRestartPulseCountTotal;
	u8 u8SoftRestartIntervalCountTotal;	
	
}UGT_S_MOTORPARAMETERS_STRU;

typedef struct UGT_S_CURRENTALL_STRU_
{
  UGT_S_CURRABC_STRU 	sCurrentAbc;
	UGT_S_CURRALBE_STRU sCurrentAlphaBeta;
	UGT_S_CURRDQ_STRU		sCurrentDqUse;
	UGT_S_CURRDQ_STRU		sCurrentDqUseLPF;
	UGT_S_CURRDQ_STRU		sCurrentDqSO;
	s32 								s32RestartMinLimit; 
} UGT_S_CURRENTALL_STRU;

typedef struct UGT_S_VOLTAGEALL_STRU_
{
  UGT_S_VOLTABC_STRU 			sVoltageAbc;	
	UGT_S_VOLTALBE_STRU 		sVoltageAlphaBetaMeas;
	UGT_S_VOLTALBE_STRU 		sVoltageAlphaBetaCalc;
	UGT_S_VOLTALBE_STRU 		sVoltageAlphaBetaUse;	
	UGT_S_VOLTDQ_STRU				sVoltageDqMeas;
	UGT_S_VOLTDQ_STRU				sVoltageDqCalc;
	UGT_S_VOLTDQ_STRU				sVoltageDqUse;

	UGT_S_SVGEN_STRU    		sSvgen;
	UGT_S_DEADTIMECOMP_STRU sDeadTimeComp;
	UGT_S_PWMDUTY_STRU  		sPwmDuty;
} UGT_S_VOLTAGEALL_STRU;

typedef struct UGT_S_SYSTEMSTATE_STRU_ 
{
  UGT_E_SS_ENUM 				sSystemState;
	UGT_E_SS_ENUM 				sSystemStatePre;
	UGT_U_SSE_ALL					uSystemError;
	UGT_E_RESTART_ENUM 		eRestart;
	UGT_E_IFSTARTUP_ENUM 	sIFStartUp;
	UGT_E_AlIGNMENT_ENUM 	eAlignment;
	UGT_E_VSPCHECK_ENUM  	sVSPCheck;
	UGT_S_SSE_TIMECOUNT  	sSysTime;
	UGT_S_SSE_SOFTCLOSE  	sSoftClose;
	UGT_S_PWMMODE_BITS	 	sPWMMode;
	UGT_S_RESRART				 	sRestart;
	UGT_U_CR_ALL					uControlReg;
	u8                    u8IdentifySwitch;
} UGT_S_SYSTEMSTATE_STRU; 

typedef struct UGT_S_CURRENT_LIMIT_STRU_
{
	s32 s32SpdFbkWL;
	s32 s32SpdFbkWH;
	s32 s32CurLimitMin;
	s32 s32CurLimitSlope;
	s32 s32CurLimitGain;
	u8  u8CurLimitEn;
} UGT_S_CURRENT_LIMIT_STRU;

typedef struct UGT_S_SYSTEMCONTROLLERs_STRU_
{
	UGT_S_PICONTROLLER_STRU 		sID;
	UGT_S_PICONTROLLER_STRU 		sIQ;
	UGT_S_PICONTROLLERIQ12_STRU sID12;
	UGT_S_PICONTROLLERIQ12_STRU sIQ12;
	UGT_S_PICONTROLLER_STRU 		sSPD;
	UGT_S_PICONTROLLER_STRU 		sUdc;
	UGT_S_COMMAND_STRU 					sCommandAll;
	UGT_S_MOTORPARAMETERS_STRU 	sMotorPara;
	u8 	u8CurIQMode;
	s32 s32StartUpSpdMax;
	s32 s32Command;
	UGT_S_CURRENT_LIMIT_STRU		sCurLimit;
	u8  u8ExtraStart;

}UGT_S_SYSTEMCONTROLLERs_STRU;

typedef struct UGT_S_POSITIONSPEED_STRU_
{
	UGT_S_TRIG_STRU sSinCosSO;
	UGT_S_TRIG_STRU sSinCosOL;
	UGT_S_TRIG_STRU sSinCosVM;
	UGT_S_TRIG_STRU sSinCosUse;
	UGT_S_TRIG_STRU sSinCosUseComp;
	u16 PosStateObserver;
	s32 SpdStateObserver;
	u16 PosOpenLoop;
	s32 SpdOpenLoop;
	u16 PosVoltMeas;
	s32 SpdVoltMeas;
	u16 u16PosUse;
	u16 u16PosUseComp;
	s32 SpdUse;
	s32 SpdUseLargeLPF;
	u16 PosRsstart[2];
	s32 SpdRestart;	
	u16 PosCount[2];
	u16 PosCountIndex;	
}UGT_S_POSITIONSPEED_STRU;



typedef struct UGT_S_USARTSTATE_STRU_
{
	 u16 NoEvevt:				1;        // 2:0    Character length control        
   u16 SendFinish:		1;   			// 3      ADDR/IDLE Mode control
   u16 ReceiceFinish:	1;       	// 4      Loop Back enable
	 u16 WriteFlash:    1;
	 u16 WriteFlashing: 1;
	 u16 UpdateSetPara:	1;
	 u16 Reserved:			10;
}UGT_S_USARTSTATE_STRU;

typedef union UGT_S_USARTSTATE_ALL_
{
	u16 										All;
	UGT_S_USARTSTATE_STRU 	Bits; 	
}UGT_S_USARTSTATE_ALL;

typedef struct UGT_S_DATATRANSFORM_STRU_
{
	s16 s16SpdRpm;
	u16 u16DCBusVoltage;
	u8  u8Temperature;
	u16 u16PhaseCurrentMag;
	s16 s16PowerIn;
	s32 s32SpdGain;
	s32 s32DCBusGain;
	s32 s32TempGain;
	s32 s32PhaseCurGain;
	s32 s32PowerGain;
}UGT_S_DATATRANSFORM_STRU;

typedef struct UGT_S_USARTDATA_STRU_
{
	u16 u16ReceiveLength;
	u8 u8SendData1[UPDS_UART_SIZE];
	u8 u8SendData2[UPDS_UART_SIZE];
	u8 u8ReceiveData[UPDS_UART_REC_COMMAND1_LENGTH];
	u16 u16FlashReadData[UPDS_UART_REC_COMMAND1_HALFWOED_LENGTH];
	s16 s16Scope[4];
	u8  u8ScopeSelect[4];
	UGT_S_DATATRANSFORM_STRU	sFlashReadDataUpdata;
	u8 u8UartMode;
	UGT_E_UART_COMMAND_ENUM	eCommand;
	FLASH_Status sFlashWriteStatus;
	u8  u8UartRecIndex;
	u8  u8UartRecCountNum;
	s16 s16UartTargetValue;
	UGT_S_USARTSTATE_ALL sUsartEvent;
}UGT_S_USARTDATA_STRU;



typedef enum UGT_E_IPD_ENUM_
{
	UGT_E_PULSE_FIRST 					= 0,    //	
	UGT_E_PULSE_SECOND  				= 1,	 	//
	UGT_E_PULSE_THIRD       		= 2,    //
	UGT_E_PULSE_FOURTH        	= 3,    //
	UGT_E_PULSE_FIVTH       		= 4,    //
	UGT_E_PULSE_SIXTH						= 5, 		//
	UGT_E_PULSE_INTERVAL				= 6,		//
  UGT_E_PULSE_END							= 7,		//
	UGT_E_PULSE_ZERO						= 8,	
}UGT_E_IPD_ENUM;

typedef struct UGT_S_IPD_STRU_
{  
	UGT_E_IPD_ENUM  eState;   	// Input: Stationary alfa-axis stator voltage
	UGT_E_IPD_ENUM  eStatePre; 
	s16  s16Idc[6];   	// Variable: Stationary alfa-axis back EMF 
	s16  s16IdcMax;
	u8   u8IdcMaxNum;
	u16  u16Index;      // Output: Stationary alfa-axis sliding control 
	s32  s32InitPos;
	u8   u8PulseNum;
	u8   u8IntervalNum;
	u8   u8En;
	u8   u8IPDFinish;
	u8   u8MotorDirection;
} UGT_S_IPD_STRU;



#endif /* __MC_TYPE_H */


