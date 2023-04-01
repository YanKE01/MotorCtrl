/**************************** (C) COPYRIGHT 2017 Fortiortech shenzhen *****************************
* File Name          : SPIInit.h
* Author             : Fortiortech Appliction Team
* Version            : V1.0
* Date               : 10-Apr-2017
* Description        : This file contains all the common data types used for
*                      Motor Control.
***************************************************************************************************
* All Rights Reserved
**************************************************************************************************/

/* Define to prevent recursive inclusion --------------------------------------------------------*/
#ifndef __SPIINIT_H_
#define __SPIINIT_H_

/* Exported functions ---------------------------------------------------------------------------*/
extern void SPI_Init(void);
extern void SPI_SendData(uint16 Data, uint8 Channel);



#endif