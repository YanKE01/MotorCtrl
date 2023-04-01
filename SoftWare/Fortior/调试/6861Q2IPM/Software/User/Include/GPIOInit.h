/* --------------------------- (C) COPYRIGHT 2020 Fortiortech ShenZhen -----------------------------
    File Name      : GPIOInit.h
    Author         : Fortiortech  Appliction Team
    Version        : V1.0
    Date           : 2020-09-30
    Description    : This file contains all the common data types used for Motor Control.
----------------------------------------------------------------------------------------------------
                                       All Rights Reserved
------------------------------------------------------------------------------------------------- */

/* Define to prevent recursive inclusion -------------------------------------------------------- */
#ifndef __G_P_I_O_INIT_H_
#define __G_P_I_O_INIT_H_

#define LEDPin			 		GP05
#define SetLEDPin				{GP05 = 1;}
#define ResetLEDPin			    {GP05 = 0;}
#define LEDPinONOFF			    {GP05 = ~GP05;}
/* Exported functions ---------------------------------------------------------------------------*/
extern void GPIO_Init(void);

#endif