/* --------------------------- (C) COPYRIGHT 2020 Fortiortech ShenZhen -----------------------------
    File Name      : TimerInit.h
    Author         : Fortiortech  Appliction Team
    Version        : V1.0
    Date           : 2020-09-30
    Description    : This file contains all the common data types used for Motor Control.
----------------------------------------------------------------------------------------------------
                                       All Rights Reserved
------------------------------------------------------------------------------------------------- */

/* Define to prevent recursive inclusion -------------------------------------------------------- */
#ifndef __TIMER_INIT_H_
#define __TIMER_INIT_H_

#define TIM0_Fre                       (24000000.0)                                                // TIM0计数频率24MHz
#define TIM2_Fre                       (187500.0)                                                  // TIM2计数频率187.5KHz
#define TIM3_Fre                       (187500.0)                                                  // TIM3计数频率187500Hz

/* Exported types -------------------------------------------------------------------------------*/

/* Exported variables ---------------------------------------------------------------------------*/

/* Exported functions ---------------------------------------------------------------------------*/
extern void TIM0_Init(void);
extern void TIM1_Init(void);
extern void TIM2_Init(void);
extern void TIM3_Init(void);
extern void TIM4_Init(void);
extern void TIM1ms_Init(void);

#endif