/**************************** (C) COPYRIGHT 2017 Fortiortech shenzhen *****************************
* File Name          : UARTInit.h
* Author             : Vina Peng, Fortiortech Appliction Team
* Version            : V1.0
* Date               : 10-Apr-2017
* Description        : This file contains all the common data types used for
*                      Motor Control.
***************************************************************************************************
* All Rights Reserved
**************************************************************************************************/
#ifndef __UARTINIT_H_
#define __UARTINIT_H_

typedef struct
{
    uint16   R_DATA[10];//={0,0,0,0,0,0,0,0,0,0};
    uint16   T_DATA[10];//={0,0,0,0,0,0,0,0,0,0};
    uint16   Uredata;
    uint16   UARxCnt;
    uint16   RxFSM;
    uint16   UsaRxLen;
    uint16   flagUsaRxComm;
    uint32   CheckDate;
    uint16   ResponceCount;
    uint8    ResponceFlag;

	uint16  uartTimer;
	uint16  uartTimerCtl; //���ƶ�ʱ�������ö�ʱ������0ʱ��ʹ�ô��ڿ���
	uint8   power;  //���ڿ��Ƶ����Ϣ
	uint16  rpmCtrl;//���ڿ��Ƶ��ת��
}MCUART;



typedef struct{
    uint8 u8Start;
    uint8 u8State;
    uint16 u16Rpm;
    uint8 u8Nom;
    uint8 u8Lrc;
    uint8 u8End;
}UART_REC;

typedef struct{
    uint8 u8Start;
    uint8 u8State;
    uint16 u16Rpm;
    uint16 u16Power;
    uint8 u8Err;
    uint8 u8Nom;
    uint8 u8lrc;
    uint8 u8End;
}UART_SEND;

extern MCUART Uart;
extern void UART_Init(void);
extern void UART_SendData(uint8 T_Data);
extern void UartDealResponse(void);
extern void UartDealComm(void);

//extern void UartSendIsr();
//extern void  UartRecIsr();

#endif