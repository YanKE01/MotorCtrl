#include "stdio.h"
#include "string.h"
#include "lcm32f037.h"
#include "lcm32f037_gpio.h"
#include "lcm32f037_rcc.h"
#include "lcm32f037_i2c.h"
#include "lcm32f037_uart.h"
#include "stdbool.h"
/************************************************************
FUNCTION:
*************************************************************************/
#define WriteLength 10
uint8_t Receive_Buff[WriteLength] = {0};
uint8_t Send_Buff[WriteLength] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A};
uint8_t ReceiveOffset, SendOffset;
void Delay(uint32_t delay_time)
{
	while (delay_time--)
		;
}
/************************
串口打印读数据观测
**************************************/
void UART0_Config()
{
	UART_InitTypeDef UART_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_UART0CLKConfig(RCC_UART0CLK_RCH); //选择UART0时钟源，不配置默认总线时钟

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource0, GPIO_AF_4);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource1, GPIO_AF_5);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; //	PB0--UART0.Tx  PB1--UART0.Rx
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	UART_StructInit(&UART_InitStruct);
	UART_InitStruct.UART_BaudRate = 921600;
	UART_InitStruct.UART_WordLength = UART_WordLength_8b;
	UART_InitStruct.UART_StopBits = UART_StopBits_1;
	UART_InitStruct.UART_Parity = UART_Parity_No;
	UART_InitStruct.UART_HardwareFlowControl = UART_HardwareFlowControl_None;
	UART_InitStruct.UART_Mode = UART_Mode_Rx | UART_Mode_Tx;
	UART_Init(UART0, &UART_InitStruct);
	UART_FIFOEnable(UART0, ENABLE);
	UART_Cmd(UART0, ENABLE);
}
/************************
IIC  IO初始化
**************************************/
void GPIO_Cfg()
{
	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_I2C0CLKConfig(RCC_I2C0CLK_RCH);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; // I2C0:PA9_SCL  PA10_SDA
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_4);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_4);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}

/************************
从机配置
**************************************/
void I2C0_Slave()
{
	I2C_InitTypeDef I2C_InitStruct;
	I2C_InitStruct.I2C_mode = I2C_SlaveOnlyMode;							 //从机模式
	I2C_InitStruct.I2C_StopDetSlave = I2C_StopDet_SlaveActive;				 //从机模式下，当寻址匹配时产生STOP_DET中断
	I2C_InitStruct.I2C_RxFifoFullHold = I2C_RxFifoFullHold_ENABLE;			 //决定I2C在RX FIFO达到RX_RX_BUFFER_DEPTH时是否hold总线
	I2C_InitStruct.I2C_TxEmptyIntr = I2C_TxEmptyIntr_ENABLE;				 //控制TX_EMPTY中断的产生方式
	I2C_InitStruct.I2C_SlaveAddressedLength = I2C_SlaveAddressedLength_7bit; //地址长度
	I2C_Init(I2C0, &I2C_InitStruct);
	I2C_SlaveAddressConfig(I2C0, 0x05);											 //设置地址
	I2C_RxFifoITthreshold(I2C_RX_FIFO_IT_0);									 //控制RX_FULL中断触发的阈值设定。范围 0~7,超过阈值触发中断
	I2C_TxFifoITthreshold(I2C_TX_FIFO_IT_0);									 //控制TX_FULL中断触发的阈值设定。范围 0~7,超过阈值触发中断
	I2C_ITConfig(I2C0, I2C_IT_RX_FULL | I2C_IT_RD_REQ | I2C_IT_RX_DONE, ENABLE); //中断配置
	I2C_ClearITPendingBit(I2C0, I2C_IT_ALL);									 //清中断
	I2C_Cmd(I2C0, ENABLE);
}

int main(void)
{
	uint8_t i;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C0, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART0, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

	NVIC_ClearPendingIRQ(I2C0_IRQn);
	NVIC_SetPriority(I2C0_IRQn, 0);
	NVIC_EnableIRQ(I2C0_IRQn);

	GPIO_Cfg();
	UART0_Config();
	I2C0_Slave();
	ReceiveOffset = 0;
	SendOffset = 0;
	while (1)
	{
		i = 0;
		while (i < WriteLength)
		{
			if (Receive_Buff[i] != 0) //检测接收数据正确性
			{
				UART_SendData(UART0, Receive_Buff[i]);
				Receive_Buff[i] = 0;
				Delay(50);
				i++;
			}
		}
		UART_SendData(UART0, ReceiveOffset);
		ReceiveOffset = 0;
	}
}

void I2C0_Handler()
{
	/*****************从机接收******************/
	uint32_t tempData;
	if (I2C_GetFlagStatus(I2C0, I2C_FLAG_RX_FULL) == SET) //接收数据,当buffer低于阈值时，该位自动清0
	{
		tempData = I2C_ReceiveData(I2C0);
		if ((tempData >> 11) == TRUE) //判断第一帧
		{
			ReceiveOffset = 0;
			Receive_Buff[ReceiveOffset] = tempData;
		}
		else
		{
			ReceiveOffset++;
			Receive_Buff[ReceiveOffset] = tempData;
		}
	}
	/*****************从机发送******************/
	if (I2C_GetFlagStatus(I2C0, I2C_FLAG_RD_REQ) == SET)
	{
		I2C_ClearITPendingBit(I2C0, I2C_FLAG_RD_REQ);
		I2C_SendData(I2C0, Send_Buff[SendOffset]);
		SendOffset++;
	}
	if (I2C_GetFlagStatus(I2C0, I2C_FLAG_RX_DONE) == SET) //判断最后一帧没有回应ACK，表示发送完成
	{
		I2C_ClearITPendingBit(I2C0, I2C_FLAG_RX_DONE);
		SendOffset = 0;
	}
}
