/* --------------------------- (C) COPYRIGHT 2020 Fortiortech ShenZhen -----------------------------
    File Name      : AMPInit.c
    Author         : Fortiortech  Appliction Team
    Version        : V1.0
    Date           : 2020-09-29
    Description    : This file contains AMP initial function used for Motor Control.
----------------------------------------------------------------------------------------------------  
                                       All Rights Reserved
------------------------------------------------------------------------------------------------- */
/* Includes -------------------------------------------------------------------------------------*/
#include <FU68xx_2.h>
#include <Myproject.h>

/* -------------------------------------------------------------------------------------------------
    Function Name  : AMP_Init
    Description    : AMP初始化配置,使能运放电压VHALF，配置运放的电流采样正向输入，反向输入和输出，包括I_BUS,I_U,I_V
	                并使能对应的运放。
    Date           : 2020-09-29
    Parameter      : None
------------------------------------------------------------------------------------------------- */
void AMP_Init(void)
{
    /* -----使能VHALF电压----- */    
	SetBit(VREF_VHALF_CR, VHALFEN);												                   // 使能VHALF

    /* -----AMP管脚配置----- */  
 	SetBit(P2_AN, P27);            
	SetBit(P3_AN, P30|P31);                                                                        // AMP0--I_BUS   

    /* -----运放使能----- */
    SetBit(AMP_CR, AMP0EN);
}