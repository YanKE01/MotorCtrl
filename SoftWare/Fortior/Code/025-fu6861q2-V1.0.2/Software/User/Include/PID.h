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
	int16 Kp;						                                     // 定义PID比例系数
	int16 Ki;						                                     // 定义PID积分系数
	int16 Err;						                                   // 定义PID当前偏差
	int16 Err_Last1;				                                 // 定义PID上次偏差
	int16 Err_Err;					                                 // 定义PID当前偏差和上次偏差之差，Err_Err=Err-Err_Last1
	int16 Out;						                                   // 定义PID输出
	int16 OutMax;					                                   // 定义PID输出最大溢出阀值
	int16 OutMin;					                                   // 定义PID输出最小溢出阀值
    
//    int16 Kp_Out;                                                     // 定义KP输出临时变量
//    int16 Ki_Out;                                                     // 定义KI输出临时变量
//    int32 PID_Out;                                                     // 定义PI输出临时变量
}PID_TypeDef;



/* Exported variables ---------------------------------------------------------------------------*/
extern PID_TypeDef xdata SpeedPID;
extern PID_TypeDef xdata CurrentPID;

/* Exported functions ---------------------------------------------------------------------------*/
//extern uint16 RampControl(Ramp_TypeDef *Ramp, uint16 Ref);
extern int16 PIDControl(PID_TypeDef *PID, int16 Ref, int16 Cur);
extern int16 PID_Control(PID_TypeDef *PID, int16 Ref, int16 Cur);

//extern uint16 PI_Control(PID_TypeDef *PID, uint16 Ref, uint16 Cur);

extern void SpeedRampInit(void);
extern void SpeedPIDInit(void);
extern void CurrentPIDInit(void);


#endif