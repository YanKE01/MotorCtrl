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

CRCDealType CRCDeal;                                                                                // ����һ��CRCУ������ṹ��

void CRC16Compute(uint8 CRCData[5])        
{
	uint8 j = 0;
	
	ClrBit(CRC_CR, CRCVAL);                                                                         // CRCVAL��0����CRC �����ʼ��Ϊ 0x0000
	SetBit(CRC_CR, CRCDINI);                                                                        // CRC�����ʼ��ʹ�ܣ�1����ʼ����Ч
	
	for( j = 0; j < 5; j++ )                                                                        // д�������CRC16���������
	{
		CRC_DIN = CRCData[j];
	}
	
	SetBit(CRC_CR, CRCPNT);
	CRCDeal.CRCValueHigh = CRC_DR;                                                                  // ��ȡ�������߰�λ
	ClrBit(CRC_CR, CRCPNT);
	CRCDeal.CRCValueLow  = CRC_DR;                                                                  // ��ȡ�������Ͱ�λ
}