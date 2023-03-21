/**
 * @copyright (C) COPYRIGHT 2022 Fortiortech Shenzhen
 * @file      PIInit.c
 * @author    Fortiortech  Appliction Team
 * @since     Create:2021-05-14
 * @date      Last modify:2022-07-14
 * @brief     This file contains PI initial function used for Motor Control.
 */       
    
#include <FU68xx_2.h>
#include <Myproject.h>

/**
 * @brief      PI初始化
 */
void PI_Init(void)
{
    PI1_KP = SKP;
    PI1_KI = SKI;
    PI1_UKMAX = SOUTMAX;
    PI1_UKMIN = SOUTMIN;
	
    PI2_KP = DQKP;
    PI2_KI = DQKI;
    PI2_UKMAX = DOUTMAX;
    PI2_UKMIN = DOUTMIN;
	
    PI3_KP = DQKP;
    PI3_KI = DQKI;
    PI3_UKMAX = QOUTMAX;
    PI3_UKMIN = QOUTMIN;
	
	PI1_UKH = 0;
    PI2_UKH = 0;
    PI3_UKH = 0;
}
