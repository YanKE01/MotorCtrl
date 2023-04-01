/* --------------------------- (C) COPYRIGHT 2020 Fortiortech ShenZhen -----------------------------
    File Name      : UARTInit.h
    Author         : Fortiortech  Appliction Team
    Version        : V1.0
    Date           : 2020-09-30
    Description    : This file contains all the common data types used for Motor Control.
----------------------------------------------------------------------------------------------------
                                       All Rights Reserved
------------------------------------------------------------------------------------------------- */

/* Define to prevent recursive inclusion -------------------------------------------------------- */
#ifndef __U_A_R_T_INIT_H_
#define __U_A_R_T_INIT_H_

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
}MCUART;

extern MCUART Uart;
extern void UART_Init(void);
extern void UART_SendData(uint8 T_Data);
extern void SPI_Init(void);

#endif