#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lcm32f037.h"
#include "lcm32f037_uart.h"
#include "lcm32f037_gpio.h"
#include "lcm32f037_rcc.h"
#include "lcm32f037_dma.h"
/**
 ******************************************************************************
 * @function: uart1
 * @attention: TX=PA2  RX=PA3
 *
 ******************************************************************************/
#define Send_Mode 1
#define Length 8
void delay(uint32_t dly)
{
	volatile uint32_t i = 0;
	while (i++ < dly)
		;
}
uint8_t sendOffset, receiveOffset;
uint8_t sendbuff[Length] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};
uint8_t receivebuff[Length] = {0};

void UART1_Config()
{
	UART_InitTypeDef UART_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_1);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; //	PA2--UART1.Tx  PA3--UART1.Rx
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	RCC_UART0CLKConfig(RCC_UART1CLK_RCH); //选择UART0时钟源，不配置默认总线时钟
	UART_StructInit(&UART_InitStruct);
	UART_InitStruct.UART_BaudRate = 115200;
	UART_InitStruct.UART_WordLength = UART_WordLength_8b;
	UART_InitStruct.UART_StopBits = UART_StopBits_1;
	UART_InitStruct.UART_Parity = UART_Parity_No;
	UART_InitStruct.UART_HardwareFlowControl = UART_HardwareFlowControl_None;
	UART_InitStruct.UART_Mode = UART_Mode_Rx | UART_Mode_Tx;
	UART_Init(UART1, &UART_InitStruct);
	UART_ITConfig(UART1, UART_IT_TX, ENABLE); //发送中断使能
	UART_ITConfig(UART1, UART_IT_RX, ENABLE); //接收中断使能
	UART_ClearITPendingBit(UART1, UART_IT_TX);
	UART_ClearITPendingBit(UART1, UART_IT_RX);
	UART_Cmd(UART1, ENABLE);

	NVIC_ClearPendingIRQ(UART1_IRQn);
	NVIC_SetPriority(UART1_IRQn, 0);
	NVIC_EnableIRQ(UART1_IRQn);
}
unsigned char Rxtemp, FirstFrameFlag;
int main()
{
	RCC_DeInit();
	SystemInit();
	SetSysClock(); //主频配置
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART1, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	UART1_Config();

	receiveOffset = 0;
	FirstFrameFlag = 0;
	while (1)
	{
		sendOffset = 0;
		UART_SendData(UART1, sendbuff[sendOffset]); //发送第一帧，触发中断
		delay(1000);
	}
}

void UART1_Handler(void)
{
	if (UART_GetITStatus(UART1, UART_IT_TX) == SET)
	{
		UART_ClearITPendingBit(UART1, UART_IT_TX);
		sendOffset++;
		if (sendOffset < Length)
			UART_SendData(UART1, sendbuff[sendOffset]);
		else
			sendOffset = 0;
	}
	if (UART_GetITStatus(UART1, UART_IT_RX) == SET)
	{
		UART_ClearITPendingBit(UART1, UART_IT_RX);
		Rxtemp = UART_ReceiveData(UART1);
		if (Rxtemp == 0x11) //接收到帧头
			FirstFrameFlag = 1;
		if (FirstFrameFlag)
		{
			receivebuff[receiveOffset] = Rxtemp; //保存接收数据
			receiveOffset++;
			if (Rxtemp == 0x88) //接收到帧尾
				FirstFrameFlag = 0;
		}
	}
}
