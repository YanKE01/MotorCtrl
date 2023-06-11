/**
  ******************************************************************************
  * @file    lcm32f037_div.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    2021-05-21
  * @brief   This file provides all the div emulation firmware functions.
  ******************************************************************************/
/**
  ******************************************************************************
  * @attention:
  * 
  * 
  * 
  * 
  ******************************************************************************/

#include "lcm32f037_div.h"

long long Fun_64_DIV_32(long long A, int B, DIV_Result *result)
{
	A_Typedef AA;
	AA.Ans64 = A;
	DIV0->DIV_CTRL = 1 << 24;
	DIV0->DIV_ALO = AA.S.LOW32;
	DIV0->DIV_AHI = AA.S.HIGH32;
	DIV0->DIV_B = B;
	result->reliable = 1;
	if (DIV0->DIV_CTRL != 0)
	{
		result->reliable = 0;
	}
	result->Q.S.LOW32 = DIV0->DIV_QUOTLO;
	result->Q.S.HIGH32 = DIV0->DIV_QUOTHI;
	result->REM = DIV0->DIV_REM;

	return (long long)result->Q.Ans64;
}
long long Fun_32_DIV_32(int A, int B, DIV_Result *result)
{
	A_Typedef AA;
	AA.Ans64 = A;
	DIV0->DIV_CTRL = 1 << 24 | 1 << 8;
	DIV0->DIV_ALO = AA.S.LOW32;
	DIV0->DIV_AHI = AA.S.HIGH32;
	DIV0->DIV_B = B;
	result->reliable = 1;
	if (DIV0->DIV_CTRL != (1U << 8))
	{
		result->reliable = 0;
	}
	result->Q.S.LOW32 = DIV0->DIV_QUOTLO;
	result->Q.S.HIGH32 = DIV0->DIV_QUOTHI;
	result->REM = DIV0->DIV_REM;

	return (long long)result->Q.Ans64;
}
