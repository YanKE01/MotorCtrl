/**************************** (C) COPYRIGHT 2017 Fortiortech shenzhen *****************************
* File Name          : TimerInit.h
* Author             : Vina Peng, Fortiortech Appliction Team
* Version            : V1.0
* Date               : 10-Apr-2017
* Description        : This file contains all the common data types used for
*                      Motor Control.
***************************************************************************************************
* All Rights Reserved
**************************************************************************************************/

/* Define to prevent recursive inclusion --------------------------------------------------------*/
#ifndef __TIMERINIT_H_
#define __TIMERINIT_H_
#define TIM0_Fre                       (24000000.0)                              // TIM0计数频率24MHz
#define TIM2_Fre                       (1500000.0)                                // TIM2计数频率187.5KHz
#define TIM4_Fre                       (12000000.0)                                // TIM4计数频率

/* Exported types -------------------------------------------------------------------------------*/

/* Exported functions ---------------------------------------------------------------------------*/
extern void TIM0_Init(void);
extern void TIM1_Init(void);
extern void TIM2_Init(void);
extern void TIM3_Init(void);
extern void TIM4_Init(void);
extern void TIM1ms_Init(void);
extern void PWMIN_Init(void);


#endif