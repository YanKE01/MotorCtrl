/**************************** (C) COPYRIGHT 2015 Fortiortech shenzhen *****************************
* File Name          : FU68xx_I2C.h
* Author             : Fortiortech  Application Dept
* Version            : V1.0
* Date               : 01/07/2015
* Description        : This file contains all the common data types used for
*                      Motor Control.
***************************************************************************************************
* All Rights Reserved
**************************************************************************************************/ 

/* Define to prevent recursive inclusion --------------------------------------------------------*/

#ifndef __I2C_H_
#define __I2C_H_

#define WC24C02   0xA0

#define RC24C02   0xA1

#define WC24C02_PAGESIZE  8

#define WC24C02_MAXSIZE   256


sbit SCL  = P1^4;			//I2Cʱ�����Ŷ���
sbit SDA  = P1^6;			//I2C�������Ŷ���

//#define	SlaveAddress 0xD0   //IICд��ʱ�ĵ�ַ�ֽ����ݣ�+1Ϊ��ȡ

//********������ʼ����******************************
//extern void I2C_riteBit(unsigned char reg, unsigned char bitNum, unsigned char bitData);
//extern int16 Single_ReadI2C(uint8 REG_Address);					//��ȡI2C����
//extern void Single_WriteI2C(unsigned char REG_Address,unsigned char REG_data);	    //��I2Cд������

extern uint8 xdata RXdata[2];

extern void  Delay2us(void);
extern bool  I2C_Start(void);
extern void  I2C_Stop(void);
extern void  I2C_SendACK();
extern void  I2C_SendNoACK();
extern bool  I2C_RecvACK(void);
extern void  I2C_SendByte(unsigned char dat);
extern unsigned char I2C_RecvByte(void);
extern unsigned char Single_ReadI2C(unsigned char REG_Address);						//��ȡI2C����
extern bool Page_WriteI2C(unsigned char Wrire_Address,unsigned char *Write_data,unsigned char n);
extern bool  Single_WriteI2C(unsigned char REG_Address,unsigned char REG_data);	    //��I2Cд������
extern signed int Single_ReadI2C_2Byte(unsigned char REG_Address);	
extern bool I2C_BufferRead(unsigned char Read_Address,unsigned char *Read_data,unsigned char n) ;
#endif