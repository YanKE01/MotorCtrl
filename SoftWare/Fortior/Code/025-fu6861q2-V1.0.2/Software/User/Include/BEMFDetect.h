/**************************** (C) COPYRIGHT 2017 Fortiortech shenzhen *****************************
* File Name          : BEMFDetect.h
* Author             : Vina Peng, Fortiortech Appliction Team
* Version            : V1.0
* Date               : 10-Apr-2017
* Description        : This file contains all the common data types used for
*                      Motor Control.
***************************************************************************************************
* All Rights Reserved
**************************************************************************************************/
#ifndef __BEMFDETECT_H_
#define __BEMFDETECT_H_


/****************************BEMF参数变量**************************/
//定义使用BEMF启动时ATO_BW值
#define 	ATO_BW_BEMF_START								100.0

#define 	OBSW_KP_GAIN_BEMF_START					_Q12(2*_2PI*ATT_COEF*ATO_BW_BEMF_START/BASE_FREQ)
#define 	OBSW_KI_GAIN_BEMF_START					_Q12(_2PI*ATO_BW_BEMF_START*ATO_BW_BEMF_START*TPWM_VALUE/BASE_FREQ)

//定义使用BEMF启动时DKI QKI值
#define 	DKI_BEMF_START									_Q12(1.0)
#define 	QKI_BEMF_START									_Q12(1.0)

//定义使用BEMF启动最低转速,ROM
#define		BEMFMotorStartSpeed							_Q15(2000.0/MOTOR_SPEED_BASE)
#define		BEMFMotorStartSpeedHigh		  		_Q15(110000.0/MOTOR_SPEED_BASE)

//定义使用BEMF检测时间,ms
#define		BEMF_START_DETECT_TIME					(1000)    // 单位1ms，速度快的电机，时间可以缩短到5

//定义使用BEMF启动检测延时,ms
#define		BEMF_START_DELAY_TIME						(50) // 单位1ms速度快的电机，时间可以缩短到2

#define TempBEMFSpeedBase								(int32)(32767.0/8.0*(TIM2_Fre*60/Pole_Pairs/MOTOR_SPEED_BASE))
#define TempBEMFSpeedBase1								(int32)(32767.0/6.0/8.0*(TIM2_Fre*60/Pole_Pairs/MOTOR_SPEED_BASE))


typedef struct
{
	uint16	BEMFSpeed;          //反电动势检测的速度
	uint32	BEMFSpeedBase;      //反电动势检测的速度基准
	uint8 	BEMFStatus;         //反电动势的状态，6拍的状态
	uint8		FRStatus;	          //正反转
	uint16	PeriodTime;	        //转一圈的周期计数值/8,因除数只能是16位的
	uint16	MC_StepTime[6];     //转一拍的计数值数组
	uint16	StepTime;           //单拍的计数值
	uint16  BEMFTimeCount;      //反电动势检测时间
	uint8		FirstCycle;         //反电动势检测第一个周期
	uint8		BEMFStep;           //拍的计数
	uint8		BEMFSpeedInitStatus;//速度初始化状态
	uint8		FlagSpeedCal;	      //速度计算标志
	uint8		BEMFStartStatus;    //强制启动标志位
	uint8   BEMFCCWFlag;        //反转的强弱标志
}BEMFDetect_TypeDef;


extern BEMFDetect_TypeDef BEMFDetect;

extern void BEMFSpeedDetect(void);
extern void CMP_BMEF_Init(void);
extern void Time2_BMEF_Init(void);
extern uint8 CWCCWDetect(uint8 HallStatus);
extern uint8 GetBEMFStatus(void);
extern void BEMFDetectInit(void);
extern void BEMFDetectFunc(void);
extern void BEMFSpeedCal(void);
extern void BEMFDealwith(void);
extern void BEMFFOCCloseLoopStart(void);

#endif