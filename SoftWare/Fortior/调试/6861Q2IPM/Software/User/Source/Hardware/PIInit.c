/* --------------------------- (C) COPYRIGHT 2020 Fortiortech ShenZhen -----------------------------
    File Name      : PIInit.c
    Author         : Fortiortech  Appliction Team
    Version        : V1.0
    Date           : 2020-09-30
    Description    : This file contains PI initial function used for Motor Control.
----------------------------------------------------------------------------------------------------  
                                       All Rights Reserved
------------------------------------------------------------------------------------------------- */
/* Includes -------------------------------------------------------------------------------------*/
#include <FU68xx_2.h>
#include <Myproject.h>
/* -------------------------------------------------------------------------------------------------
    Function Name  : PI_Init
    Description    : PI初始化配置
    Date           : 2020-09-30
    Parameter      : None
------------------------------------------------------------------------------------------------- */
void PI_Init(void)
{
    #if (MTPAENABLE)
    {
        PI1_KP = MTPASKP;
        PI1_KI = MTPASKI;
        PI1_UKMAX = MTPASOutMax_Start;
        PI1_UKMIN = MTPASOutMin_Start;
    }
    #else
    {
        PI1_KP = SKP;
        PI1_KI = SKI;
        PI1_UKMAX = SOutMax_Start;
        PI1_UKMIN = SOutMin_Start;
    }
    #endif																			
}