/**
 * @copyright (C) COPYRIGHT 2022 Fortiortech Shenzhen
 * @file      UARTInit.c
 * @author    Fortiortech  Appliction Team
 * @since     Create:2021-05-14
 * @date      Last modify:2022-07-14
 * @brief     This file contains UART initial function used for Motor Control.
 */
    
#include <FU68xx_2.h>
#include <Myproject.h>

MCUART xdata Uart;


/**
 * @brief      Uart初始化
 */
void UART_Init(void)
{
    P0_OE |= P05;
    P0_PU |= P05;
    P0_OE &= ~P06;
    P0_PU |= P06;
    SetBit(PH_SEL, UARTEN);     //使能串口
    ClrBit(PH_SEL, UARTCH);     //ClrBit(PH_SEL, UARTCH)p0[6]as UART_RXD,p0[5]as UART_TXD;SetBit(PH_SEL, UARTCH)p3[3]as UART_RXD,p3[4]as UART_TXD;
    UT_MOD1 = 0;
    UT_MOD0 = 1;                //MODE1:8bit波特率可变UART模式
    SM2 = 0;                    //禁止Mode2和Mode3多机通讯
    REN = 1;                    //使能接收
    ES0 = 0;                    //先关中断
    PUART1 = 0;                 //中断优先级时最低
    PUART0 = 0;
    UT_BAUD = 0x9b;             //  波特率=fcpu_clk/((16/(1+UT_BAUD[BAUD_SEL]))*(UT_BAUD+1))； UT_BAUD[BAUD_SEL]为UT_BAUD.15 ;default baudrate:9600-0x9b,4800-0x137;2400-0x270;1200-0x4E1
    ES0 = 1;                    //ES0 发送/接受中断使能位
    #if (0)
    {
        SetBit(PH_SEL, UARTEN); //p0[6]as UART_RXD; p0[5]as UART_TXD
        UT_MOD1 = 0;
        UT_MOD0 = 1;            //8bit波特率可变UART模式
        SM2 = 0;                //禁止Mode2和Mode3多机通讯
        REN = 1;                //使能接收
        ES0 = 0;                //先关中断
        PUART1 = 0;             //中断优先级时最低
        PUART0 = 0;
        UT_BAUD = 0x4E1;        //default baudrate:9600-0x9b,1200-0x4E1
        ES0 = 1;                //发送/接受中断使能
    }
    #endif
}



/**
 * @brief      Uart发送数据
 */
void UartTxdate(uint16 * sndBuf, int32 len)
{
    uint16 i = 0;
    
    for (i = 0; i < len; i++)
    {
        UART_SendData(*sndBuf++);
    }
}

/**
 * @brief      Uart发送数据
 */
void UART_SendData(unsigned char T_Data)
{
    UT_DR = T_Data;
    
    while (!(TI == 1));         //等待发送完成
    
    TI = 0;                     //发送完成中断标志位清零
}


/**
 * @brief      处理串口接收到的数据
 */
void UartDealResponse(void)
{
}


/**
 * @brief      串口数据处理
 */
void UartDealComm(void)
{
    uint16 j = 0;
    uint16 checkdate = 0x00;
    
    if (Uart.ResponceFlag == 1) //10ms
    {
        //         UartDealResponse();
        Uart.T_DATA[0]     = 0xaa;
        Uart.T_DATA[1]     = (int)mcState;
        Uart.T_DATA[2]     = (uint16)(((int32)mcFocCtrl.SpeedFlt * 2400) >> 19);  // actual speed/16 ,if actual speed=1000rpm/min,then TxBuf[2]=63
        Uart.T_DATA[3]     = (uint16)(((int32)mcFocCtrl.mcDcbusFlt * 626) >> 16); // DC bus feedback, 1 stand for 2V
        Uart.T_DATA[4]     = (int)mcFaultSource;//Fault state
        Uart.T_DATA[5]     = 0x00;
        Uart.T_DATA[6]     = 0x00;
        Uart.T_DATA[7]     = 0x00;
        
        for ( j = 0; j < 7; j++ )
        {
            checkdate += Uart.T_DATA[j];
        }
        
        Uart.T_DATA[8]     = checkdate;
        Uart.T_DATA[9]     = 0x55;
        UartTxdate(Uart.T_DATA, 10);
        Uart.ResponceFlag = 0;
    }
}

static uint8 uartRdata[10];
static uint8 uartRecCnt = 0;

static uint8 uartSenddata[10];
static uint8 uartSendCnt = 0;


/** 
 * @brief        Uart
 * @param[in]    ptBuf
 * @param[in]    u8Size
 * @return       sum
 */
/*  -------------------------------------------------------------------------------------------------
    Function Name  : LrcCal
    Description    : Uart
    Date           : 2020-08-08
    Parameter      : ptBuf: [输入]
**                                  u8Size: [输入]
    ------------------------------------------------------------------------------------------------- */
uint8 LrcCal(uint8 * ptBuf, uint8 u8Size)
{
    uint8 i, sum;
    sum = 0;
    
    for (i = 0; i < u8Size; i++)
    {
        sum += ptBuf[i];
    }
    
    return sum;
}


/**
 * @brief      Uart
 */
void SendConPack(void)
{
    UART_SEND * ptXy = (UART_SEND *)uartSenddata;
    ptXy->u8Start  = 0xaa;
    ptXy->u8State  = 0;
    ptXy->u16Rpm   = mcFocCtrl.SpeedFlt;
    ptXy->u16Power = mcFocCtrl.Powerlpf;
    ptXy->u8Err    = (int)mcFaultSource;
    ptXy->u8lrc    = LrcCal(uartSenddata, sizeof(UART_SEND) - 2);
    ptXy->u8End    = 0x55;
}

/**
 * @brief      Uart
 */
void UartRecIsr(void)
{
    UART_REC * ptXy = (UART_REC *)uartRdata;
    
    //    uint8 i;
    if (Uart.uartTimer >= 20)
    {
        uartRecCnt = 0;
    }
    
    Uart.uartTimer = 0;
    
    if (uartRecCnt < sizeof(uartRdata))
    {
        uartRdata[uartRecCnt++] = Uart.Uredata;
    }
    
    if (ptXy->u8Start == 0xaa)
    {
        if (uartRecCnt >= sizeof(UART_REC))
        {
            if (ptXy->u8Lrc == LrcCal(uartRdata, sizeof(UART_REC) - 2))
            {
                Uart.uartTimerCtl = 3000;
                Uart.power = ptXy->u8State;
                Uart.rpmCtrl = ptXy->u16Rpm;
                SendConPack();
                uartSendCnt = 0;
                GP36 ^= 1;
                TI = 1;
            }
        }
    }
    else
    {
        uartRecCnt = 0;
    }
}

/**
 * @brief      Uart数据传输
 */
void UartSendIsr(void)
{
    if (uartSendCnt < sizeof(UART_SEND))
    {
        UT_DR =  uartSenddata[uartSendCnt++];
    }
}
