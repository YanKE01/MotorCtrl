/**************************** (C) COPYRIGHT 2017 Fortiortech shenzhen *****************************
* File Name          : KeyScan.h
* Author             : Vina Peng, Fortiortech Appliction Team
* Version            : V1.0
* Date               : 01/04/2017
* Description        : This file contains all the common data types used for
*                      Motor Control.
***************************************************************************************************
* All Rights Reserved
**************************************************************************************************/

/* Define to prevent recursive inclusion --------------------------------------------------------*/
#ifndef __KEYSCAN_H_
#define __KEYSCAN_H_

#define Key0 	          PowerChange
#define Key1 	          BrakePin

/* Exported types -------------------------------------------------------------------------------*/
typedef struct
{
	uint8 Key0Value;
	uint8 Key0TempValue;
	uint8 FlagKey0Press;
	uint8 KeyDownFlag;
	
	int16 Key0PressCnt;
	int16 Key0InitCnt;

	uint8 Key1Value;
	uint8 Key1TempValue;
	uint8 FlagKey1Press;
	int16 Key1PressCnt;
	int16 Key1InitCnt;

} KeyScanParam_TypeDef;

/* Exported variables ---------------------------------------------------------------------------*/
extern KeyScanParam_TypeDef KS;

/* Exported functions ---------------------------------------------------------------------------*/
extern void KeyInit(void);
extern uint8 KeyValue(void);
extern void KeyScan(void);

#endif

