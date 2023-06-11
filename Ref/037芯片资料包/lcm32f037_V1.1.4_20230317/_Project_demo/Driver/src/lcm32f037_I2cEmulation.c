/**
 ******************************************************************************
 * @file    lcm32f037_I2cEmulation.c
 * @author  MCD Application Team
 * @version V1.0.0
 * @date    2021-05-21
 * @brief   This file provides all the i2ce emulation firmware functions.
 ******************************************************************************/
/**
 ******************************************************************************
 * @attention:
 *
 *
 *
 *
 ******************************************************************************/
#include "LCM32F037.h"
#include "LCM32F037_gpio.h"
#include "lcm32f037_i2c.h"

#define AT24C01 127
#define AT24C02 255
#define AT24C04 511
#define AT24C08 1023
#define AT24C16 2047
#define AT24C32 4095
#define AT24C64 8191
#define AT24C128 16383
#define AT24C256 32767

#define IIC_SCL_H GPIO_SetBits(GPIOA, GPIO_Pin_9)
#define IIC_SCL_L GPIO_ResetBits(GPIOA, GPIO_Pin_9)
#define IIC_SDA_H GPIO_SetBits(GPIOA, GPIO_Pin_10)
#define IIC_SDA_L GPIO_ResetBits(GPIOA, GPIO_Pin_10)
#define READ_SDA GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_10)
#define SDA_IN()   \
	{    \
		GPIOA->MODER &= 0xFFCFFFFF; \
	}
#define SDA_OUT()  \
	{    \
		GPIOA->MODER |= 0x00100000; \
	}
void delay_us(int i)
{
	while (i--)
		;
}
/**************
when CLK is high,DATA change form high to low
**************************************************/
void IIC_Start(void)
{
	SDA_OUT(); // sda�����
	IIC_SCL_H;
	IIC_SDA_H;
	delay_us(5);
	IIC_SDA_L;
	delay_us(5);
}
/**************
when CLK is high DATA change form low to high
**************************************************/
void IIC_Stop(void)
{
	SDA_OUT(); // sda�����
	IIC_SDA_L;
	IIC_SCL_L;
	delay_us(5);
	IIC_SCL_H;
	IIC_SDA_H; //����I2C���߽����ź�
	delay_us(5);
}
/**************
�ȴ�Ӧ���źŵ���
����ֵ��1:����Ӧ��ʧ��;   0:����Ӧ��ɹ�
**************************************************/
uint8_t IIC_Wait_Ack(void)
{
	uint8_t ucErrTime = 0;
	SDA_IN(); // SDA����Ϊ����
	IIC_SDA_H;
	delay_us(5);
	IIC_SCL_H;
	delay_us(5);
	while (READ_SDA)
	{
		ucErrTime++;
		if (ucErrTime > 250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL_L; //ʱ�����0
	return 0;
}
/**************
����ACKӦ��
**************************************************/
void IIC_Ack(void)
{
	IIC_SCL_L;
	SDA_OUT();
	IIC_SDA_L;
	delay_us(5);
	IIC_SCL_H;
	delay_us(5);
	IIC_SCL_L;
}
/**************
������ACKӦ��
**************************************************/
void IIC_NAck(void)
{
	IIC_SCL_L;
	SDA_OUT();
	IIC_SDA_H;
	delay_us(5);
	IIC_SCL_H;
	delay_us(5);
	IIC_SCL_L;
}

void IIC_Send_Byte(uint8_t txd)
{
	uint8_t t = 0;
	SDA_OUT();
	IIC_SCL_L; //����ʱ�ӿ�ʼ���ݴ���
	for (t = 0; t < 8; t++)
	{
		if (txd & 0x80)
			IIC_SDA_H;
		else
			IIC_SDA_L;
		txd <<= 1;
		delay_us(5);
		IIC_SCL_H;
		delay_us(5);
		IIC_SCL_L;
		delay_us(5);
	}
}
/********************
��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK
*******************************************/
uint8_t IIC_Read_Byte(uint8_t ack)
{
	uint8_t receive = 0;
	uint8_t i = 0;
	SDA_IN(); // SDA����Ϊ����
	for (i = 0; i < 8; i++)
	{
		IIC_SCL_L;
		delay_us(5);
		IIC_SCL_H;
		receive <<= 1;
		if (READ_SDA)
			receive++;
		delay_us(5);
	}
	if (!ack)
		IIC_NAck(); //����nACK
	else
		IIC_Ack(); //����ACK
	return receive;
}
void IIC_Init(void)
{
	IIC_SCL_H;
	IIC_SDA_H;
	delay_us(5000);
}
/***************
��AT24CXXָ����ַ����һ������
 ReadAddr:��ʼ�����ĵ�ַ
����ֵ  :����������
**************************************/
uint8_t AT24CXX_ReadOneByte(uint16_t ReadAddr)
{
	uint8_t temp = 0;
	IIC_Start();
	if (AT24C02 > AT24C16)
	{
		IIC_Send_Byte(0XA0); //����д����
		IIC_Wait_Ack();
		IIC_Send_Byte(ReadAddr >> 8); //���͸ߵ�ַ
		IIC_Wait_Ack();
	}
	else
		IIC_Send_Byte(0XA0 + ((ReadAddr / 256) << 1)); //����������ַ0XA0,д����

	IIC_Wait_Ack();
	IIC_Send_Byte(ReadAddr % 256); //���͵͵�ַ
	IIC_Wait_Ack();
	IIC_Start();
	IIC_Send_Byte(0XA1); //�������ģʽ
	IIC_Wait_Ack();
	temp = IIC_Read_Byte(0);
	IIC_Stop(); //����һ��ֹͣ����
	return temp;
}
/****************************
��AT24CXXָ����ַд��һ������
WriteAddr  :д�����ݵ�Ŀ�ĵ�ַ
DataToWrite:Ҫд�������
****************************************/
void AT24CXX_WriteOneByte(uint16_t WriteAddr, uint8_t DataToWrite)
{
	IIC_Start();
	if (AT24C02 > AT24C16)
	{
		IIC_Send_Byte(0XA0); //����д����
		IIC_Wait_Ack();
		IIC_Send_Byte(WriteAddr >> 8); //���͸ߵ�ַ
	}
	else
	{
		IIC_Send_Byte(0XA0 + ((WriteAddr / 256) << 1)); //����������ַ0XA0,д����
	}
	IIC_Wait_Ack();
	IIC_Send_Byte(WriteAddr % 256); //���͵͵�ַ
	IIC_Wait_Ack();
	IIC_Send_Byte(DataToWrite); //�����ֽ�
	IIC_Wait_Ack();
	IIC_Stop(); //����һ��ֹͣ����
	delay_us(1000);
}
/************************************************
��AT24CXX�����ָ����ַ��ʼд�볤��ΪLen������
�ú�������д��16bit����32bit������.
WriteAddr  :��ʼд��ĵ�ַ
DataToWrite:���������׵�ַ
Len   :Ҫд�����ݵĳ���2,4
***********************************************/
void AT24CXX_WriteLenByte(uint16_t WriteAddr, uint32_t DataToWrite, uint8_t Len)
{
	uint8_t t;
	for (t = 0; t < Len; t++)
	{
		AT24CXX_WriteOneByte(WriteAddr + t, (DataToWrite >> (8 * t)) & 0xff);
	}
}
/****************************************************
��AT24CXX�����ָ����ַ��ʼ��������ΪLen������
�ú������ڶ���16bit����32bit������.
ReadAddr   :��ʼ�����ĵ�ַ
����ֵ:����
Len   :Ҫ�������ݵĳ���2,4
*************************************/
uint32_t AT24CXX_ReadLenByte(uint16_t ReadAddr, uint8_t Len)
{
	uint8_t t;
	uint32_t temp = 0;
	for (t = 0; t < Len; t++)
	{
		temp <<= 8;
		temp += AT24CXX_ReadOneByte(ReadAddr + Len - t - 1);
	}
	return temp;
}
/***************************************
���AT24CXX�Ƿ�����
��������24XX�����һ����ַ(255)���洢��־��.
���������24Cϵ��,�����ַҪ�޸�
����1:���ʧ��
����0:���ɹ�
***********************************/
uint8_t AT24CXX_Check(void)
{
	uint8_t temp;
	temp = AT24CXX_ReadOneByte(255); //����ÿ�ο�����дAT24CXX
	if (temp == 0X55)
		return 0;
	else //�ų���һ�γ�ʼ�������
	{
		AT24CXX_WriteOneByte(255, 0X55);
		temp = AT24CXX_ReadOneByte(255);
		if (temp == 0X55)
			return 0;
	}
	return 1;
}
/****************************************
��AT24CXX�����ָ����ַ��ʼ����ָ������������
ReadAddr :��ʼ�����ĵ�ַ ��24c02Ϊ0~255
pBuffer  :���������׵�ַ
NumToRead:Ҫ�������ݵĸ���
************************************/
void AT24CXX_Read(uint16_t ReadAddr, uint8_t *pBuffer, uint16_t NumToRead)
{
	while (NumToRead)
	{
		*pBuffer++ = AT24CXX_ReadOneByte(ReadAddr++);
		NumToRead--;
	}
}
/*************************************
��AT24CXX�����ָ����ַ��ʼд��ָ������������
WriteAddr :��ʼд��ĵ�ַ ��24c02Ϊ0~255
pBuffer   :���������׵�ַ
NumToWrite:Ҫд�����ݵĸ���
*******************************************/
void AT24CXX_Write(uint16_t WriteAddr, uint8_t *pBuffer, uint16_t NumToWrite)
{
	while (NumToWrite--)
	{
		AT24CXX_WriteOneByte(WriteAddr, *pBuffer);
		WriteAddr++;
		pBuffer++;
	}
}
