/**************************** (C) COPYRIGHT 2017 Fortiortech shenzhen *****************************
* File Name          : PID.h
* Author             : Fortiortech  Market Dept
* Version            : V1.0
* Date               : 10-Apr-2017
* Description        : This file contains all the common data types used for Motor Control.
***************************************************************************************************
* All Rights Reserved
**************************************************************************************************/

/* Define to prevent recursive inclusion --------------------------------------------------------*/
#ifndef __PID_H_
#define __PID_H_

/* Exported types -------------------------------------------------------------------------------*/
typedef struct
{
	uint16 Kp;						                                     // 定义PID比例系数
	uint16 Ki;						                                     // 定义PID积分系数
	uint16 Err;						                                   // 定义PID当前偏差
	uint16 Err_Last1;				                                 // 定义PID上次偏差
	uint16 Err_Err;					                                 // 定义PID当前偏差和上次偏差之差，Err_Err=Err-Err_Last1
	uint16 Out;						                                   // 定义PID输出
	uint16 OutMax;					                                   // 定义PID输出最大溢出阀值
	uint16 OutMin;					                                   // 定义PID输出最小溢出阀值
}PID_TypeDef;

typedef struct
{
	uint16 RampInc;
	uint16 RampDec;
	uint16 RampTarget;
	uint16 RampStep;
	int16  Output;
}Ramp_TypeDef;

/* Exported variables ---------------------------------------------------------------------------*/
extern PID_TypeDef 	xdata SpeedPID;
extern Ramp_TypeDef xdata SpeedRamp;
extern PID_TypeDef 	xdata CurrentPID;

/* Exported functions ---------------------------------------------------------------------------*/
extern uint16 RampControl(Ramp_TypeDef *Ramp, uint16 Ref);
extern uint16 PIDControl(PID_TypeDef *PID, uint16 Ref, uint16 Cur);
extern uint16 PID_Control(PID_TypeDef *PID, uint16 Ref, uint16 Cur);

extern void PI_Init(void);
extern uint16 PI_Control(PID_TypeDef *PID, uint16 Ref, uint16 Cur);

extern void SpeedRampInit(void);
extern void SpeedPIDInit(void);
extern void CurrentPIDInit(void);


#endif