#include "stdio.h"
#include "string.h"
#include "lcm32f037.h"
#include "lcm32f037_gpio.h"
#include "lcm32f037_rcc.h"
#include "lcm32f037_i2c.h"
#include "lcm32f037_uart.h"
#include "stdbool.h"
#include "lcm32f037_flash.h"
/************************************************************
FUNCTION:
*************************************************************************/
#define WriteLength 10
uint8_t Write_Buff[WriteLength] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA};
uint8_t Read_Buff[WriteLength] = {0};

void Delay(uint16_t delay_time)
{
	while (delay_time--)
		;
}
/************************
���ڴ�ӡ�����ݹ۲�
**************************************/
void UART0_Config()
{
	UART_InitTypeDef UART_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_UART0CLKConfig(RCC_UART0CLK_RCH); //ѡ��UART0ʱ��Դ��������Ĭ������ʱ��

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
IIC  IO��ʼ��
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

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_0); //�۲�mco���
}

/************************
��������
**************************************/
void I2C0_Master()
{
	RCC_I2C0CLKConfig(RCC_I2C0CLK_APB1);
	I2C_InitTypeDef I2C_InitStruct;
	I2C_InitStruct.I2C_mode = I2C_MasterOnlyMode;				   //����ģʽ
	I2C_InitStruct.I2C_StopDetMaster = I2C_StopDet_MasterAlways;   //����ģʽ�µ�STOP_DET�ж�
	I2C_InitStruct.I2C_RxFifoFullHold = I2C_RxFifoFullHold_ENABLE; //����I2C��RX FIFO�ﵽRX_RX_BUFFER_DEPTHʱ�Ƿ�hold����
	I2C_InitStruct.I2C_TxEmptyIntr = I2C_TxEmptyIntr_ENABLE;	   //����TX_EMPTY�жϵĲ�����ʽ
	I2C_InitStruct.I2C_Speed = 100000;							   // SCL��������
	I2C_Init(I2C0, &I2C_InitStruct);
	
	I2C_ITConfig(I2C0, I2C_IT_ALL, DISABLE); //�ж�����
	I2C_ClearITPendingBit(I2C0, I2C_IT_ALL); //���ж�
	I2C_Cmd(I2C0, ENABLE);
}
/********************************************
���ֽڶ�
DeviceAddr��7λĿ���ַ
*buff:д�������ַ
len�������ݳ���
************************************************************/
void Master_WriteNByte(uint32_t DeviceAddr, uint8_t *buff, uint8_t len)
{
	uint8_t i;
	while (I2C_GetITStatus(I2C0, I2C_STATUS_ACTIVITY) == SET)
		;
	I2C_TransferHandling(I2C0, DeviceAddr); //����7λĿ���ַ
	for (i = 0; i < len - 1; i++)
	{
		while (I2C_GetITStatus(I2C0, I2C_STATUS_TFNF) == RESET)
			;
		I2C_WriteData(I2C0, buff[i]); //���ô�������
	}
	while (I2C_GetITStatus(I2C0, I2C_STATUS_TFNF) == RESET)
		;
	I2C_WriteData_Stop(I2C0, buff[len - 1]); //�������һ���������ݣ������STOP�ź�
}
/********************************************
���ֽڶ�
DeviceAddr��7λĿ���ַ
len�������ݳ���
************************************************************/
void Master_ReadNByte(uint32_t DeviceAddr, uint8_t len)
{
	uint8_t i;
	while (I2C_GetITStatus(I2C0, I2C_STATUS_ACTIVITY) == SET)
		;
	I2C_TransferHandling(I2C0, DeviceAddr); //����7λĿ���ַ
	for (i = 0; i < len - 1; i++)
	{
		while (I2C_GetITStatus(I2C0, I2C_STATUS_TFNF) == RESET)
			;
		Read_Buff[i] = I2C_ReadData(I2C0); //������
	}
	while (I2C_GetITStatus(I2C0, I2C_STATUS_TFNF) == RESET)
		;
	Read_Buff[len - 1] = I2C_ReadData_Stop(I2C0); //�����һ�����ݣ�Ncak,stop
}

int main(void)
{
	uint8_t i;
	SystemInit();
	SetSysClock(); //��Ƶ����
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C0, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART0, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	GPIO_Cfg();
	UART0_Config();
	I2C0_Master();
	mco_set(3, 0);
	while (1)
	{

#if 0
		Master_WriteNByte(0x05, Write_Buff, WriteLength); //���ֽ�д
#else

		Master_ReadNByte(0x05, WriteLength); //���ֽڶ�
		i = 0;
		while (i < WriteLength)
		{
			if (Read_Buff[i] != 0) //������������ȷ��
			{
				UART_SendData(UART0, Read_Buff[i]);
				Read_Buff[i] = 0;
				Delay(50);
				i++;
			}
		}
#endif
		Delay(10000);
	}
}
