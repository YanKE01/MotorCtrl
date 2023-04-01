/**
 * @copyright (C) COPYRIGHT 2022 Fortiortech Shenzhen
 * @file      MDUInit.c
 * @author    Fortiortech  Appliction Team
 * @since     Create:2021-05-14
 * @date      Last modify:2022-07-14
 * @brief     This file contains MDU initial function used for Motor Control.
 */    
    
#include <FU68xx_2.h>
#include <Myproject.h>

/** 
 * @brief        1、32位无符号除法，返回32位无符号值
                 2、运行时间9.3us
                 3、函数在调用过程中如果被中断打断则会重复调用
                 4、应用于数据类型为XDATA
                 5、TData0(32位)/TData1(16位) = RData32(32位)
 * @param[in]    TData0 被除数(32位) 
 * @param[in]    TData1 除数(16位)
 * @return       32位商
 */
 uint32 MDU_DIV_XDATA_U32(uint8 xdata * TData0, uint8 xdata * TData1)
{
    uint32 RData32;
    uint16 * PData16;
    
    DIV0_DAH = ((*(TData0+0))<<8)+(*(TData0+1));
    DIV0_DAL = ((*(TData0+2))<<8)+(*(TData0+3));
    
    DIV0_DB = ((*(TData1+0))<<8)+(*(TData1+1));
    
    SMDU_RunBlock(0, DIV)
    
    PData16 = &RData32;
    *PData16 = DIV0_DQH;
    PData16 += 1;
    *PData16 = DIV0_DQL;
    return RData32;
}


/*  -------------------------------------------------------------------------------------------------
    Function Name  : MDU_DIV_XDATA_U16
    Description    : 1、16位无符号除法，返回16位无符号值
                     2、运行时间5.6us
                     3、函数在调用过程中如果被中断打断则会重复调用
                     4、应用于数据类型为XDATA
    Date           : 2020-08-07
    Parameter      : TData0 : [输入] -- 被除数(16位)    TData1: [输入] -- 除数(16位)
**                   RData32: [输出] -- 16位商
    ------------------------------------------------------------------------------------------------- */
//uint16 MDU_DIV_XDATA_U16(uint8 xdata * TData0, uint8 xdata * TData1)
//{
//    uint16 RData16;
//    uint16 * PData16;
//    MDU_DA3 = 0x00;
//    MDU_DA2 = 0x00;
//    MDU_DA1 = *(TData0 + 0);
//    MDU_DA0 = *(TData0 + 1);
//    MDU_DB1 = *(TData1 + 0);
//    MDU_DB0 = *(TData1 + 1);
//    SetBit(MDU_CR, DIVSTA);
//    
//    while (!ReadBit(MDU_CR, DIVDONE));                           // 等待MDU计算完成
//    
//    PData16 = &RData16;
//    *PData16 = MDU_DA01;
//    return MDU_DA01;
//}

/** 
 * @brief        1、32位无符号除法，返回32位无符号值
                 2、运行时间9.3us
                 3、函数在调用过程中如果被中断打断则会重复调用
                 4、应用于数据类型为IDATA
                 5、TData0(32位)/TData1(16位) = RData32(32位)
 * @param[in]    TData0 被除数(32位) 
 * @param[in]    TData1 除数(16位)
 * @return       32位商
 */
uint32 MDU_DIV_IDATA_U32(uint8 idata * TData0, uint8 idata * TData1)
{
    uint32 RData32;
    uint16 * PData16;
    DIV0_DAH = ((*(TData0+0))<<8)+(*(TData0+1));
    DIV0_DAL = ((*(TData0+2))<<8)+(*(TData0+3));
    
    DIV0_DB = ((*(TData1+0))<<8)+(*(TData1+1));
    
    SMDU_RunBlock(0, DIV)
    
    PData16 = &RData32;
    *PData16 = DIV0_DQH;
    PData16 += 1;
    *PData16 = DIV0_DQL;
    return RData32;
}

/*  -------------------------------------------------------------------------------------------------
    Function Name  : MDU_DIV_IDATA_U16
    Description    : 1、16位无符号除法，返回16位无符号值
                     2、运行时间4.6us
                     3、函数在调用过程中如果被中断打断则会重复调用
                     4、应用于数据类型为IDATA
    Date           : 2020-08-07
    Parameter      : TData0 : [输入] -- 被除数(16位)    TData1: [输入] -- 除数(16位)
**                   RData32: [输出] -- 16位商
    ------------------------------------------------------------------------------------------------- */

//uint16 MDU_DIV_IDATA_U16(uint8 idata * TData0, uint8 idata * TData1)
//{
//    uint16 RData16;
//    uint16 * PData16;
//    MDU_DA3 = 0x00;
//    MDU_DA2 = 0x00;
//    MDU_DA1 = *(TData0 + 0);
//    MDU_DA0 = *(TData0 + 1);
//    MDU_DB1 = *(TData1 + 0);
//    MDU_DB0 = *(TData1 + 1);
//    SetBit(MDU_CR, DIVSTA);
//    
//    while (!ReadBit(MDU_CR, DIVDONE));                          // 等待MDU计算完成
//    
//    PData16 = &RData16;
//    *PData16 = MDU_DA01;
//    return MDU_DA01;
//}

/*  -------------------------------------------------------------------------------------------------
    Function Name  : MDU_16MUL16_INT
    Description    : 有无符号乘法选，结果右移ALIGN位
    Date           : 2020-08-07
    Parameter      : ALIGN: [输入]
**                   SIGN : [输入]
    ------------------------------------------------------------------------------------------------- */
//void MDU_16MUL16_INT(uint8 ALIGN, uint8 SIGN)
//{
//    if (ALIGN == 0)
//    {
//        MDU_CR &= ~(1 << ALIGN1);
//        MDU_CR &= ~(1 << ALIGN0);                               // 00:乘法结果右移0位
//    }
//    else if (ALIGN == 8)
//    {
//        MDU_CR &= ~(1 << ALIGN1);
//        MDU_CR |= (1 << ALIGN0);                                // 01:乘法结果右移8位
//    }
//    else if (ALIGN == 12)
//    {
//        MDU_CR |= (1 << ALIGN1);
//        MDU_CR &= ~(1 << ALIGN0);                               // 10:乘法结果右移12位
//    }
//    else if (ALIGN == 15)
//    {
//        MDU_CR |= (1 << ALIGN1);
//        MDU_CR |= (1 << ALIGN0);                                // 11:乘法结果右移15位
//    }
//    else ;
//    
//    if (SIGN == 0)
//    {
//        MDU_CR &= ~(1 << MDSN);                                 // 选择无符号乘法
//    }
//    else if (SIGN == 1)
//    {
//        MDU_CR |= (1 << MDSN);                                  // 选择有符号乘法
//    }
//    else ;
//}

/** 
 * @brief        1、32位无符号乘法，返回32位无符号值
                 2、运行时间3.0-3.8us
                 3、函数在调用过程中如果被中断打断则会重复调用
                 4、应用于数据类型为XDATA
 * @param[in]    TData0 乘数0(16位) 
 * @param[in]    TData1 乘数1(16位)
 * @param[out]   Result32_t 32位乘积变量指针
 */
void MDU_MUL_XDATA_U32(uint16 TData0, uint16 TData1, uint16 xdata * Result32_t)
{

    MUL0_MA = TData0;
    MUL0_MB = TData1;                                            // 写被乘数和乘数
    SMDU_RunBlock(0, UMUL)
    *Result32_t = MUL0_MCH;
    *(Result32_t + 1) = MUL0_MCL;
}

/*  -------------------------------------------------------------------------------------------------
    Function Name  : MDU_MUL_XDATA_RIGHT_U32
    Description    : 1、16位无符号乘法，返回32位无符号值
                     2、运行时间3.0-3.8us
                     3、函数在调用过程中如果被中断打断则会重复调用
                     4、结果右移ALIGN位
                     5、应用于数据类型为XDATA
    Date           : 2020-08-07
    Parameter      : TData0 : [输入] -- 乘数0(16位)            TData1: [输入] -- 乘数1(16位)
**                   RData32: [输出] -- 32位乘积变量指针       ALIGN ：[输入] -- 乘积右移位数
    ------------------------------------------------------------------------------------------------- */
//void MDU_MUL_XDATA_RIGHT_U32(uint16 TData0, uint16 TData1, uint8 ALIGN, uint16 xdata * Result32_t)
//{
//    if (ALIGN == 8)
//    {
//        SetBit(MDU_CR, ALIGN0);
//        ClrBit(MDU_CR, ALIGN1);                                 // 01:乘法结果右移8位
//    }
//    else if (ALIGN == 12)
//    {
//        SetBit(MDU_CR, ALIGN1);                                 // 10:乘法结果右移12位
//        ClrBit(MDU_CR, ALIGN0);
//    }
//    else if (ALIGN == 15)
//    {
//        SetBit(MDU_CR, ALIGN1 | ALIGN0);                        // 11:乘法结果右移15位
//    }
//    else
//    {
//        ClrBit(MDU_CR, ALIGN1 | ALIGN0);                        // 00:乘法结果不右移
//    }
//    
//    ClrBit(MDU_CR, MDSN);                                       // 0-无符号乘法，1-有符号乘法
//    MDU_MA = TData0;
//    MDU_MB = TData1;                                            // 写被乘数和乘数
//    *(Result32_t) = MDU_MA;
//    *(Result32_t + 1) = MDU_MB;
//}

/*  -------------------------------------------------------------------------------------------------
    Function Name  : MDU_MUL_XDATA_U16
    Description    : 1、16位无符号乘法，返回16位无符号值
                     2、运行时间3.0-3.8us
                     3、函数在调用过程中如果被中断打断则会重复调用
                     4、结果右移ALIGN位
                     5、应用于数据类型为XDATA
    Date           : 2020-08-07
    Parameter      : TData0 : [输入] -- 乘数0(16位)            TData1: [输入] -- 乘数1(16位)
**                   RData32: [输出] -- 16位乘积变量指针
    ------------------------------------------------------------------------------------------------- */
//void MDU_MUL_XDATA_U16(uint16 TData0, uint16 TData1, uint16 xdata * Result16_t)
//{
//    ClrBit(MDU_CR, ALIGN1 | ALIGN0);                            // 00:乘法结果右移0位
//    ClrBit(MDU_CR, MDSN);                                       // 0-无符号乘法，1-有符号乘法
//    MDU_MA = TData0;
//    MDU_MB = TData1;                                            // 写被乘数和乘数
//    *(Result16_t) = MDU_MB;
//}

/** 
 * @brief        1、32位无符号乘法，返回32位无符号值
                 2、运行时间3.0-3.8us
                 3、函数在调用过程中如果被中断打断则会重复调用
                 4、应用于数据类型为IDATA
 * @param[in]    TData0 乘数0(16位) 
 * @param[in]    TData1 乘数1(16位)
 * @param[out]   Result32_t 32位乘积变量指针
 */

void MDU_MUL_IDATA_U32(uint16 TData0, uint16 TData1, uint16 idata * Result32_t)
{
    MUL0_MA = TData0;
    MUL0_MB = TData1;                                            // 写被乘数和乘数
    SMDU_RunBlock(0, UMUL)
    *Result32_t = MUL0_MCH;
    *(Result32_t + 1) = MUL0_MCL;
}
