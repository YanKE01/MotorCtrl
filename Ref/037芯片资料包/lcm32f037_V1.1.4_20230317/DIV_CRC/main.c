#include "stdio.h"
#include "string.h"
#include "lcm32f037.h"
#include "lcm32f037_gpio.h"
#include "lcm32f037_uart.h"
#include "lcm32f037_rcc.h"
#include "lcm32f037_crc.h"
#include "stdbool.h"
#include "lcm32f037_div.h"
/*****************************
支持64/32的有符号操作,32个周期完成；向下支持32/32的有符号除法。将数据写入除数寄存器DIV_B
后开始计算，待32个周期后读取计算结果。

硬件CRC
***************************************/
DIV_Result result0, result1;
long long Temp11, Temp21, Temp31, Temp41;
uint32_t uwCRCValue = 0;
#define length 8
uint32_t testBuff[length] = {0};
void CRC_Init()
{
	Crc_initial_config_32(CRC0);
}

uint32_t CRC_CalcBlockCRC(uint32_t pBuffer[], uint32_t BufferLength)
{
	uint32_t index = 0;
	uint32_t temp;
	CRC0->CRC_RESULT = 0XFFFFFFFF;
	for (index = 0; index < BufferLength; index++)
	{
		CRC0->CRC_DATA = pBuffer[index];
		while (CRC0->CRC_CTRL & MULT_CTRL_CRC_VALID_ON)
			;
	}
	temp = CRC0->CRC_RESULT;
	return temp;
}

void GPIO_INIT() // IO初始化
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
void delay(uint32_t dly)
{
	volatile uint32_t i = 0;
	while (i++ < dly)
		;
}
int main()
{
	uint16_t i;
	SystemInit();
	SetSysClock();
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DIV, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	GPIO_INIT();
	CRC_Init();
	for (i = 0; i < length; i++)
	{
		testBuff[i] = i;
	}
	while (1)
	{
		{ // DIV
			Temp11 = Fun_64_DIV_32(-8, 2, &result0);
			Temp21 = Fun_32_DIV_32(0x7FFFFFFD, 0x07, &result1);
			Temp31 = Fun_64_DIV_32(0xFFFFFFFFFFFFFFAF, 0x03, &result0);
			Temp41 = Fun_32_DIV_32(0xFFFFFFFD, 0x07, &result1);
		}
		{ // CRC
			CRC0->CRC_CTRL = CRC_GPS_CRC32 | CRC_LM_MSB | CRC_BYTE_4 | CRC_CTRL_OVERFLOW_EN | CRC_CRTL_CORDIC_EN | CRC_RESET_CRC_EN | CRC_RESET_OFF | CRC_SWAP_11;
			uwCRCValue = CRC_CalcBlockCRC(testBuff, (uint32_t)length);
		}
		{
			GPIO_SetBits(GPIOA, GPIO_Pin_0);
			delay(100);
			GPIO_ResetBits(GPIOA, GPIO_Pin_0);
			delay(100);
		}
	}
}
