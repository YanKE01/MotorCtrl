/**************************** (C) COPYRIGHT 2017 Fortiortech shenzhen *****************************
* File Name          : MDUInit.h
* Author             : Vina Peng, Fortiortech Appliction Team
* Version            : V1.0
* Date               : 10-Apr-2017
* Description        : This file contains all the common data types used for
*                      Motor Control.
***************************************************************************************************
* All Rights Reserved
**************************************************************************************************/

/* Define to prevent recursive inclusion --------------------------------------------------------*/

#ifndef __MDUINIT_H_
#define __MDUINIT_H_
extern void MDU_16MUL16_INT(uint8 ALIGN, uint8 SIGN);
extern void MDU_MUL_XDATA_U32(uint16 TData0, uint16 TData1, uint16 xdata *Result32_t);
extern void MDU_MUL_IDATA_U32(uint16 TData0, uint16 TData1, uint16 idata *Result32_t);
extern void MDU_MUL_XDATA_U16(uint16 TData0, uint16 TData1, uint16 xdata *Result16_t);
extern void MDU_MUL_XDATA_RIGHT_U32(uint16 TData0, uint16 TData1,uint8 ALIGN, uint16 xdata *Result32_t);
extern uint32 MDU_DIV_XDATA_U32(uint8 xdata *TData0, uint8 xdata *TData1);
extern uint32 MDU_DIV_IDATA_U32(uint8 idata *TData0, uint8 idata *TData1);
extern uint16 MDU_DIV_IDATA_U16(uint8 idata *TData0, uint8 idata *TData1);
extern uint16 MDU_DIV_XDATA_U16(uint8 xdata *TData0, uint8 xdata *TData1);
extern uint32 Div_MDU(uint32* P1, uint16* P2);

#endif