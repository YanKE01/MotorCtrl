/*****************************************************
**  @brief div moudle driver
**	@author zhang
**	@data 2020-10-13
**	@function  A/B = Q......Rem
*******************************************************/

#ifndef LCM32F037_DIV_H
#define LCM32F037_DIV_H
#include "lcm32f037.h"
#include <stdint.h>
#include <core_cm0.h>
typedef struct
{
	__IO uint32_t DIV_CTRL;
	__IO uint32_t DIV_ALO;
	__IO uint32_t DIV_AHI;
	__IO uint32_t DIV_B;
	__IO uint32_t DIV_QUOTLO;
	__IO uint32_t DIV_QUOTHI;
	__IO uint32_t DIV_REM;
} DIV_TypeDef;

typedef union
{
	struct
	{
		uint32_t LOW32;
		uint32_t HIGH32;
	} S;
	uint64_t Ans64;
} A_Typedef;

#define DIV0 ((DIV_TypeDef *)(0x48010000 + (4UL << 12)))
#define DIVx DIV0
typedef struct
{
	A_Typedef Q;
	__IO uint32_t REM;
	__IO uint32_t reliable;
} DIV_Result;

#define LCM_DIV(A, B) 		{DIV0->DIV_CTRL = 0x01000100; DIV0->DIV_ALO = (s32)A;	DIV0->DIV_B 	= (s32)B;}
#define LCM_DIV_RESULT 		(DIV0->DIV_QUOTLO)
	//void DIV_fun2(uint64_t A, uint32_t B, DIV_Result *result);
//void DIV_fun1(uint32_t A, uint32_t B, DIV_Result *result);
long long Fun_32_DIV_32(int A, int B, DIV_Result *result);
//long long Fun_64_DIV_32(long long A, int B, DIV_Result *result);
#endif
