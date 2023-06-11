#include "stdio.h"
#include "string.h"
#include "lcm32f037.h"
#include "lcm32f037_gpio.h"
#include "lcm32f037_rcc.h"
#include "lcm32f037_i2c.h"
#include "lcm32f037_uart.h"
#include "stdbool.h"
/************************************************************
FUNCTION:以24C02为例，使用硬件IIC，给出了单字节或多字节读写例程

*************************************************************************/
#define WriteLength 5
uint8_t Write_Buff[WriteLength] = {0x01, 0x02, 0x03, 0x04, 0x05};
uint8_t Read_Buff[WriteLength];

void Delay(uint16_t delay_time)
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
}
/************************
主机配置
**************************************/
void I2C0_Master()
{
	RCC_I2C0CLKConfig(RCC_I2C0CLK_APB1);
	I2C_InitTypeDef I2C_InitStruct;
	I2C_InitStruct.I2C_mode = I2C_MasterOnlyMode;				   //主机模式
	I2C_InitStruct.I2C_StopDetMaster = I2C_StopDet_MasterAlways;   //主机模式下的STOP_DET中断
	I2C_InitStruct.I2C_RxFifoFullHold = I2C_RxFifoFullHold_ENABLE; //决定I2C在RX FIFO达到RX_RX_BUFFER_DEPTH时是否hold总线
	I2C_InitStruct.I2C_TxEmptyIntr = I2C_TxEmptyIntr_ENABLE;	   //控制TX_EMPTY中断的产生方式
	I2C_InitStruct.I2C_Speed = 1000000;							   // SCL速率配置
	I2C_Init(I2C0, &I2C_InitStruct);
	I2C_ITConfig(I2C0, I2C_IT_ALL, DISABLE); //中断配置
	I2C_ClearITPendingBit(I2C0, I2C_IT_ALL); //清中断
	I2C_Cmd(I2C0, ENABLE);
}

/*************************
24C02按字节写,指定对应字节地址写入数据
******************************************************/
void AT24C02_WriteOneByte(uint8_t DeviceAddr, uint8_t byteAddr, uint8_t data)
{
	while (I2C_GetITStatus(I2C0, I2C_STATUS_ACTIVITY) == SET)
		;
	I2C_TransferHandling(I2C0, DeviceAddr); //设置7位目标地址
	while (I2C_GetITStatus(I2C0, I2C_STATUS_TFNF) == RESET)
		;
	I2C_WriteData(I2C0, byteAddr); //设置字节地址
	while (I2C_GetITStatus(I2C0, I2C_STATUS_TFNF) == RESET)
		;
	I2C_WriteData(I2C0, data); //设置传输数据，并添加STOP信号
}
/*************************
24C02多字节写
DeviceAddr：7位目标地址
byteAddr：字节地址
buff：传输数据（数组）
len：传输数据长度
(24C02一次可写入16个字节,与24C02通信,len不超过16)
******************************************************/
void AT24C02_WriteNByte(uint8_t DeviceAddr, uint8_t byteAddr, uint8_t *buff, uint8_t len)
{
	uint8_t i;
	while (I2C_GetITStatus(I2C0, I2C_STATUS_ACTIVITY) == SET)
		;
	I2C_TransferHandling(I2C0, DeviceAddr); //设置7位目标地址
	while (I2C_GetITStatus(I2C0, I2C_STATUS_TFNF) == RESET)
		;
	I2C_WriteData(I2C0, byteAddr); //设置字节地址
	while (I2C_GetITStatus(I2C0, I2C_STATUS_TFNF) == RESET)
		;
	I2C_TransferHandling(I2C0, DeviceAddr); //设置7位目标地址
	for (i = 0; i < len - 1; i++)
	{
		while (I2C_GetITStatus(I2C0, I2C_STATUS_TFNF) == RESET)
			;
		I2C_WriteData(I2C0, buff[i]); //设置传输数据
	}
	while (I2C_GetITStatus(I2C0, I2C_STATUS_TFNF) == RESET)
		;
	I2C_WriteData_Stop(I2C0, buff[len - 1]); //设置最后一个传输数据，并添加STOP信号
}
/********************************************
24C02选择性读（指定字节地址，读n个数据）
DeviceAddr：7位目标地址
byteAddr：字节地址
len：读数据长度
************************************************************/
void AT24C02_ReadNByte(uint8_t DeviceAddr, uint8_t byteAddr, uint8_t len)
{
	uint8_t i;
	while (I2C_GetITStatus(I2C0, I2C_STATUS_ACTIVITY) == SET)
		;
	I2C_TransferHandling(I2C0, DeviceAddr); //设置7位目标地址
	while (I2C_GetITStatus(I2C0, I2C_STATUS_TFNF) == RESET)
		;
	I2C_WriteData(I2C0, byteAddr); //设置字节地址
	while (I2C_GetITStatus(I2C0, I2C_STATUS_TFNF) == RESET)
		;
	I2C_TransferHandling(I2C0, DeviceAddr); //设置7位目标地址
	for (i = 0; i < len - 1; i++)
	{
		Read_Buff[i] = I2C_ReadData(I2C0);
	}
	Read_Buff[len - 1] = I2C_ReadData_Stop(I2C0); //读最后一个数据，Ncak,stop
}

uint8_t IICflag;
int main(void)
{
	uint8_t i;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C0, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART0, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	GPIO_Cfg();
	UART0_Config();
	I2C0_Master();
	IICflag = 1;
	while (1)
	{
		if (IICflag)
		{
			IICflag = 0;
			//	AT24C02_WriteOneByte(0x50,0x0B,0xAA);//按字节写
			//		AT24C02_WriteNByte(0x50, 0x0B, Write_Buff, WriteLength); //多字节写
			AT24C02_ReadNByte(0x50, 0x0B, WriteLength); //选择性读（指定字节地址，读n个数据）
			i = 0;
			while (i < WriteLength)
			{
				if (Read_Buff[i] != 0) //检测写入数据正确性
				{
					UART_SendData(UART0, Read_Buff[i]);
					Read_Buff[i] = 0;
					Delay(50);
					i++;
				}
			}
		}
	}
}
