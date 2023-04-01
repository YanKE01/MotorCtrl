/**************************** (C) COPYRIGHT 2018 Fortiortech shenzhen *****************************
* File Name          : CRCCompute.c
* Author             : Cooper Fang, Fortiortech Appliction Team
* Version            : V1.0
* Date               : 2018-09-25
* Description        : This file contains the function used for CRC-verifying.
***************************************************************************************************
* All Rights Reserved
**************************************************************************************************/

/* Includes -------------------------------------------------------------------------------------*/
#include <FU68xx_2.h>
#include <Myproject.h>

CRCDealType CRCDeal;                                                                                // 定义一个CRC校验变量结构体

void CRC16Compute(uint8 CRCData[5])        
{
	uint8 j = 0;
	
	ClrBit(CRC_CR, CRCVAL);                                                                         // CRCVAL置0：将CRC 结果初始化为 0x0000
	SetBit(CRC_CR, CRCDINI);                                                                        // CRC结果初始化使能，1：初始化有效
	
	for( j = 0; j < 5; j++ )                                                                        // 写入待进行CRC16计算的数据
	{
		CRC_DIN = CRCData[j];
	}
	
	SetBit(CRC_CR, CRCPNT);
	CRCDeal.CRCValueHigh = CRC_DR;                                                                  // 读取计算结果高八位
	ClrBit(CRC_CR, CRCPNT);
	CRCDeal.CRCValueLow  = CRC_DR;                                                                  // 读取计算结果低八位
}