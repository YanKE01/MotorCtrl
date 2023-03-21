/**************************** (C) COPYRIGHT 2017 Fortiortech shenzhen *****************************
* File Name          : PIOInit.h
* Author             : Vina Peng, Fortiortech Appliction Team
* Version            : V1.0
* Date               : 10-Apr-2017
* Description        : This file contains all the common data types used for
*                      Motor Control.
***************************************************************************************************
* All Rights Reserved
**************************************************************************************************/

/* Define to prevent recursive inclusion --------------------------------------------------------*/
#ifndef __PIOINIT_H_
#define __PIOINIT_H_


#define SPIncPin        GP00
#define PowerChange     GP02
#define SPDecPin        GP02
//#define FRPin						GP03
#define PIN_HEAT        GP14


#define PWMPin 					GP11

#define LEDPin			 		GP37
#define SetLEDPin				{GP37 = 1;}
#define ResetLEDPin			{GP37 = 0;}
#define LEDPinONOFF			{GP37 = ~GP37;}

#define YAOTOUPin			 		GP10
#define SetYAOTOUPin			{GP10 = 0;}
#define ResetYAOTOUPin		{GP10 = 1;}

#define FPin 				  GP07
#define SetFGPin			  {GP07 = 1;}
#define ResetFGPin		  {GP07 = 0;}
#define FPinONOFF      {GP07 = ~GP07;}

//#define RDPin 				  GP01
//#define SetRDPin			  {GP01 = 1;}
//#define ResetRDPin		  {GP01 = 0;}

/* Exported functions ---------------------------------------------------------------------------*/
extern void GPIO_Init(void);
extern void GPIO_Default_Init(void);
#endif