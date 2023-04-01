/**************************** (C) COPYRIGHT 2017 Fortiortech shenzhen *****************************
* File Name          : AddFunction.c
* Author             : Fortiortech  Appliction Team
* Version            : V1.0
* Date               : 10-Apr-2017
* Description        : This file contains MDU initial function used for Motor Control.
***************************************************************************************************
* All Rights Reserved
**************************************************************************************************/


/* Includes -------------------------------------------------------------------------------------*/
#include <FU68xx_2.h>
#include <Myproject.h>

/*-------------------------------------------------------------------------------------------------
    Function Name : uint32 MDU_DIV_XDATA_U32(uint8 xdata *TData0, uint8 xdata *TData1)
    Description   : 32位无符号除法，返回32位无符号值，运行时间9.3us，函数在调用过程中如果
                  被中断打断则会重复调用
    Input         : TData0-被除数(32位)，TData1-除数(16位)，商是32位的，应用于数据类型为XDATA
  Output                :   RData32-32位商
-------------------------------------------------------------------------------------------------*/
uint32 MDU_DIV_XDATA_U32(uint8 xdata * TData0, uint8 xdata * TData1)
{
    uint32 RData32;
    uint16 * PData16;
    MDU_DA3 = *TData0;
    MDU_DA2 = *(TData0 + 1);
    MDU_DA1 = *(TData0 + 2);
    MDU_DA0 = *(TData0 + 3);
    MDU_DB1 = *(TData1 + 0);
    MDU_DB0 = *(TData1 + 1);
    SetBit(MDU_CR, DIVSTA);
    
    while (!ReadBit(MDU_CR, DIVDONE));                           // 等待MDU计算完成
    
    PData16 = &RData32;
    *PData16 = MDU_DA23;
    PData16 += 1;
    *PData16 = MDU_DA01;
    return RData32;
}

/*  -------------------------------------------------------------------------------------------------
    Function Name  : MDU_MUL_XDATA_U32
    Description    : 1、16位无符号乘法，返回32位无符号值
                     2、运行时间3.0-3.8us
                     3、函数在调用过程中如果被中断打断则会重复调用
                     4、应用于数据类型为XDATA
    Date           : 2020-08-07
    Parameter      : TData0 : [输入] -- 乘数0(16位)       TData1: [输入] -- 乘数1(16位)
**                   RData32: [输出] -- 32位乘积变量指针
    ------------------------------------------------------------------------------------------------- */
void MDU_MUL_XDATA_U32(uint16 TData0, uint16 TData1, uint16 xdata * Result32_t)
{
    MUL0_MA = TData0;
    MUL0_MB = TData1;                                            // 写被乘数和乘数
    SMDU_RunBlock(0, SMUL)
    *Result32_t = MUL0_MCH;
    *(Result32_t + 1) = MUL0_MCL;
}
/*-------------------------------------------------------------------------------------------------
    Function Name : uint16 MDU_DIV_XDATA_U16(uint8 xdata *TData0, uint8 xdata *TData1)
    Description   : 16位无符号除法，返回16位无符号值，运行时间5.6us，函数在调用过程中如果
                  被中断打断则会重复调用
    Input         : TData0-被除数(16位)，TData1-除数(16位)，商是16位的，应用于数据类型为XDATA
  Output                :   RData16-16位商
-------------------------------------------------------------------------------------------------*/

uint16 MDU_DIV_XDATA_U16(uint8 xdata * TData0, uint8 xdata * TData1)
{
    uint16 RData16;
    uint16 * PData16;
    MDU_DA3 = 0x00;
    MDU_DA2 = 0x00;
    MDU_DA1 = *(TData0 + 0);
    MDU_DA0 = *(TData0 + 1);
    MDU_DB1 = *(TData1 + 0);
    MDU_DB0 = *(TData1 + 1);
    SetBit(MDU_CR, DIVSTA);
    
    while (!ReadBit(MDU_CR, DIVDONE));                           // 等待MDU计算完成
    
    PData16 = &RData16;
    *PData16 = MDU_DA01;
    return MDU_DA01;
}
/*-------------------------------------------------------------------------------------------------
    Function Name : uint32 MDU_DIV_IDATA_U32(uint8 xdata *TData0, uint8 xdata *TData1)
    Description   : 32位无符号除法，返回32位无符号值，运行时间8us，函数在调用过程中如果
                  被中断打断则会重复调用
    Input         : TData0-被除数(32位)，TData1-除数(16位)，商是32位的，应用于数据类型为IDATA
  Output                :   RData32-32位商
-------------------------------------------------------------------------------------------------*/
uint32 MDU_DIV_IDATA_U32(uint8 idata * TData0, uint8 idata * TData1) //
{
    uint32 RData32;
    uint16 * PData16;
    MDU_DA3 = *TData0;
    MDU_DA2 = *(TData0 + 1);
    MDU_DA1 = *(TData0 + 2);
    MDU_DA0 = *(TData0 + 3);
    MDU_DB1 = *(TData1 + 0);
    MDU_DB0 = *(TData1 + 1);
    SetBit(MDU_CR, DIVSTA);
    
    while (!ReadBit(MDU_CR, DIVDONE));                           // 等待MDU计算完成
    
    PData16 = &RData32;
    *PData16 = MDU_DA23;
    PData16 += 1;
    *PData16 = MDU_DA01;
    return RData32;
}


/*-------------------------------------------------------------------------------------------------
    Function Name : uint16 MDU_DIV_XDATA_U16(uint8 xdata *TData0, uint8 xdata *TData1)
    Description   : 16位无符号除法，返回16位无符号值，运行时间4.6us，函数在调用过程中如果
                  被中断打断则会重复调用
    Input         : TData0-被除数(16位)，TData1-除数(16位)，商是16位的，应用于数据类型为IDATA
  Output                :   RData16-16位商
-------------------------------------------------------------------------------------------------*/

uint16 MDU_DIV_IDATA_U16(uint8 idata * TData0, uint8 idata * TData1)
{
    uint16 RData16;
    uint16 * PData16;
    MDU_DA3 = 0x00;
    MDU_DA2 = 0x00;
    MDU_DA1 = *(TData0 + 0);
    MDU_DA0 = *(TData0 + 1);
    MDU_DB1 = *(TData1 + 0);
    MDU_DB0 = *(TData1 + 1);
    SetBit(MDU_CR, DIVSTA);
    
    while (!ReadBit(MDU_CR, DIVDONE));                           // 等待MDU计算完成
    
    PData16 = &RData16;
    *PData16 = MDU_DA01;
    return MDU_DA01;
}

/*---------------------------------------------------------------------------*/
/* Name     :   void MDU_16MUL16_INT(uint8 ALIGN, uint8 SIGN)
/* Input    :   NO
/* Output   :   NO
/* Description: Inital MDU parameter
/*---------------------------------------------------------------------------*/
void MDU_16MUL16_INT(uint8 ALIGN, uint8 SIGN)
{
    if (ALIGN == 0)
    {
        MDU_CR &= ~(1 << ALIGN1);
        MDU_CR &= ~(1 << ALIGN0);           /*00:乘法结果右移0位*/
    }
    else if (ALIGN == 8)
    {
        MDU_CR &= ~(1 << ALIGN1);
        MDU_CR |= (1 << ALIGN0);                /*01:乘法结果右移8位*/
    }
    else if (ALIGN == 12)
    {
        MDU_CR |= (1 << ALIGN1);
        MDU_CR &= ~(1 << ALIGN0);               /*10:乘法结果右移12位*/
    }
    else if (ALIGN == 15)
    {
        MDU_CR |= (1 << ALIGN1);
        MDU_CR |= (1 << ALIGN0);                /*11:乘法结果右移15位*/
    }
    else ;
    
    if (SIGN == 0)
    {
        MDU_CR &= ~(1 << MDSN);                 /*选择无符号乘法*/
    }
    else if (SIGN == 1)
    {
        MDU_CR |= (1 << MDSN);                      /*选择有符号乘法*/
    }
    else ;
}
/*-------------------------------------------------------------------------------------------------
    Function Name : void MDU_MUL_U32(uint16 TData0, uint16 TData1, uint16 xdata *Result32_t)
    Description   : 16位无符号乘法，返回32位无符号值，运行时间3.0-3.8us，函数在调用过程中如果
                  被中断打断则会重复调用
    Input         : TData0-乘数0; TData1-乘数1; Result32_t-32bi乘积变量指针
-------------------------------------------------------------------------------------------------*/
////void MDU_MUL_XDATA_U32(uint16 TData0, uint16 TData1, uint16 xdata *Result32_t)
////{

////    ClrBit(MDU_CR, ALIGN1);
////    ClrBit(MDU_CR, ALIGN0);                                  // 00:乘法结果右移0位
////    SetBit(MDU_CR, MDSN);                                            // 0-无符号乘法，1-有符号乘法

////    MDU_MA = TData0;
////    MDU_MB = TData1;                                                         // 写被乘数和乘数

////    *Result32_t = MDU_MA;
////    *(Result32_t+1) = MDU_MB;
////}
/*-------------------------------------------------------------------------------------------------
    Function Name : void MDU_MUL_XDATA_RIGHT_U16(uint16 TData0, uint16 TData1, uint16 xdata *Result16_t)
    Description   : 16位无符号乘法，返回32位无符号值，运行时间3.0-3.8us，函数在调用过程中如果
                  被中断打断则会重复调用,右移15位
    Input         : TData0-乘数0; TData1-乘数1; Result32_t-32bit乘积变量指针，ALIGN右移的位数
-------------------------------------------------------------------------------------------------*/
void MDU_MUL_XDATA_RIGHT_32(int16 TData0, int16 TData1, uint8 ALIGN, int16 xdata * Result32_t)
{
    if (ALIGN == 8)
    {
        SetBit(MDU_CR, ALIGN0);
        ClrBit(MDU_CR, ALIGN1);                                // 01:乘法结果右移8位
    }
    else if (ALIGN == 12)
    {
        SetBit(MDU_CR, ALIGN1);                                // 10:乘法结果右移12位
        ClrBit(MDU_CR, ALIGN0);
    }
    else if (ALIGN == 15)
    {
        SetBit(MDU_CR, ALIGN1 | ALIGN0);                          // 11:乘法结果右移15位
    }
    else
    {
        ClrBit(MDU_CR, ALIGN1 | ALIGN0);                  // 00:乘法结果不右移
    }
    
    SetBit(MDU_CR, MDSN);                                            // 0-无符号乘法，1-有符号乘法
    MDU_MA = TData0;
    MDU_MB = TData1;                                                   // 写被乘数和乘数
    *(Result32_t) = MDU_MA;
    *(Result32_t + 1) = MDU_MB;
}
/*-------------------------------------------------------------------------------------------------
    Function Name : void MDU_MUL_U16(uint16 TData0, uint16 TData1, uint16 xdata *Result16_t)
    Description   : 16位无符号乘法，返回16位无符号值，运行时间3.0-3.8us，函数在调用过程中如果
                  被中断打断则会重复调用
    Input         : TData0-乘数0; TData1-乘数1; Result16_t-16bi乘积变量指针
-------------------------------------------------------------------------------------------------*/
void MDU_MUL_XDATA_16(int16 TData0, int16 TData1, int16 xdata * Result16_t)
{
    //  ClrBit(MDU_CR, ALIGN1|ALIGN0);                     // 00:乘法结果右移0位
    SetBit(MDU_CR, ALIGN1 | ALIGN0);                         // 11:乘法结果右移15位
    //  SetBit(MDU_CR, ALIGN1);                                             // 10:乘法结果右移12位
    //  ClrBit(MDU_CR, ALIGN0);
    SetBit(MDU_CR, MDSN);                                                       // 0-无符号乘法，1-有符号乘法
    MDU_MA = TData0;
    MDU_MB = TData1;                                                            // 写被乘数和乘数
    *(Result16_t) = MDU_MB;
}

/*-------------------------------------------------------------------------------------------------
    Function Name : void MDU_MUL_IDATA_U32(uint16 TData0, uint16 TData1, uint16 idata *Result32_t)
    Description   : 16位无符号乘法，返回32位无符号值，运行时间3.0-3.8us，函数在调用过程中如果
                  被中断打断则会重复调用
    Input         : TData0-乘数0; TData1-乘数1; Result32_t-32bi乘积变量指针
-------------------------------------------------------------------------------------------------*/
void MDU_MUL_IDATA_U32(uint16 TData0, uint16 TData1, uint16 idata * Result32_t)
{
    ClrBit(MDU_CR, ALIGN1 | ALIGN0);                               // 00:乘法结果右移0位
    SetBit(MDU_CR, MDSN);                                                  // 0-无符号乘法，1-有符号乘法
    MDU_MA = TData0;
    MDU_MB = TData1;                                                         // 写被乘数和乘数
    *Result32_t = MDU_MA;
    *(Result32_t + 1) = MDU_MB;
}