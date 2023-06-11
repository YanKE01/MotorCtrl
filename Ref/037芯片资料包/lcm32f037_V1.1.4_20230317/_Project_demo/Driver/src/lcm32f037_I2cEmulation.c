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
	SDA_OUT(); // sda线输出
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
	SDA_OUT(); // sda线输出
	IIC_SDA_L;
	IIC_SCL_L;
	delay_us(5);
	IIC_SCL_H;
	IIC_SDA_H; //发送I2C总线结束信号
	delay_us(5);
}
/**************
等待应答信号到来
返回值：1:接收应答失败;   0:接收应答成功
**************************************************/
uint8_t IIC_Wait_Ack(void)
{
	uint8_t ucErrTime = 0;
	SDA_IN(); // SDA设置为输入
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
	IIC_SCL_L; //时钟输出0
	return 0;
}
/**************
产生ACK应答
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
不产生ACK应答
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
	IIC_SCL_L; //拉低时钟开始数据传输
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
读1个字节，ack=1时，发送ACK，ack=0，发送nACK
*******************************************/
uint8_t IIC_Read_Byte(uint8_t ack)
{
	uint8_t receive = 0;
	uint8_t i = 0;
	SDA_IN(); // SDA设置为输入
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
		IIC_NAck(); //发送nACK
	else
		IIC_Ack(); //发送ACK
	return receive;
}
void IIC_Init(void)
{
	IIC_SCL_H;
	IIC_SDA_H;
	delay_us(5000);
}
/***************
在AT24CXX指定地址读出一个数据
 ReadAddr:开始读数的地址
返回值  :读到的数据
**************************************/
uint8_t AT24CXX_ReadOneByte(uint16_t ReadAddr)
{
	uint8_t temp = 0;
	IIC_Start();
	if (AT24C02 > AT24C16)
	{
		IIC_Send_Byte(0XA0); //发送写命令
		IIC_Wait_Ack();
		IIC_Send_Byte(ReadAddr >> 8); //发送高地址
		IIC_Wait_Ack();
	}
	else
		IIC_Send_Byte(0XA0 + ((ReadAddr / 256) << 1)); //发送器件地址0XA0,写数据

	IIC_Wait_Ack();
	IIC_Send_Byte(ReadAddr % 256); //发送低地址
	IIC_Wait_Ack();
	IIC_Start();
	IIC_Send_Byte(0XA1); //进入接收模式
	IIC_Wait_Ack();
	temp = IIC_Read_Byte(0);
	IIC_Stop(); //产生一个停止条件
	return temp;
}
/****************************
在AT24CXX指定地址写入一个数据
WriteAddr  :写入数据的目的地址
DataToWrite:要写入的数据
****************************************/
void AT24CXX_WriteOneByte(uint16_t WriteAddr, uint8_t DataToWrite)
{
	IIC_Start();
	if (AT24C02 > AT24C16)
	{
		IIC_Send_Byte(0XA0); //发送写命令
		IIC_Wait_Ack();
		IIC_Send_Byte(WriteAddr >> 8); //发送高地址
	}
	else
	{
		IIC_Send_Byte(0XA0 + ((WriteAddr / 256) << 1)); //发送器件地址0XA0,写数据
	}
	IIC_Wait_Ack();
	IIC_Send_Byte(WriteAddr % 256); //发送低地址
	IIC_Wait_Ack();
	IIC_Send_Byte(DataToWrite); //发送字节
	IIC_Wait_Ack();
	IIC_Stop(); //产生一个停止条件
	delay_us(1000);
}
/************************************************
在AT24CXX里面的指定地址开始写入长度为Len的数据
该函数用于写入16bit或者32bit的数据.
WriteAddr  :开始写入的地址
DataToWrite:数据数组首地址
Len   :要写入数据的长度2,4
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
在AT24CXX里面的指定地址开始读出长度为Len的数据
该函数用于读出16bit或者32bit的数据.
ReadAddr   :开始读出的地址
返回值:数据
Len   :要读出数据的长度2,4
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
检查AT24CXX是否正常
这里用了24XX的最后一个地址(255)来存储标志字.
如果用其他24C系列,这个地址要修改
返回1:检测失败
返回0:检测成功
***********************************/
uint8_t AT24CXX_Check(void)
{
	uint8_t temp;
	temp = AT24CXX_ReadOneByte(255); //避免每次开机都写AT24CXX
	if (temp == 0X55)
		return 0;
	else //排除第一次初始化的情况
	{
		AT24CXX_WriteOneByte(255, 0X55);
		temp = AT24CXX_ReadOneByte(255);
		if (temp == 0X55)
			return 0;
	}
	return 1;
}
/****************************************
在AT24CXX里面的指定地址开始读出指定个数的数据
ReadAddr :开始读出的地址 对24c02为0~255
pBuffer  :数据数组首地址
NumToRead:要读出数据的个数
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
在AT24CXX里面的指定地址开始写入指定个数的数据
WriteAddr :开始写入的地址 对24c02为0~255
pBuffer   :数据数组首地址
NumToWrite:要写入数据的个数
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
