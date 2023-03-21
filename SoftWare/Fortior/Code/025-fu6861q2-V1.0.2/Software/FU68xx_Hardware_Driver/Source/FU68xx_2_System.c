/**
 * @copyright (C) COPYRIGHT 2022 Fortiortech Shenzhen
 * @file      FU68xx_2_System.c
 * @author    Fortiortech  Appliction Team
 * @since     Create:2021-05-14
 * @date      Last modify:2022-07-14
 * @brief     This file contains system function used for Motor Control.
 */
#include <FU68xx_2.h>
#include <Myproject.h>

/** 
 * @brief        参考电压配置
 */
void VREFConfig(uint8 Status)
{
    #if (HW_ADC_VREF==VREF3_0)
    {
        SetBit(VREF_VHALF_CR, VRVSEL1);             //00-->4.5V   01-->VDD5
        ClrBit(VREF_VHALF_CR, VRVSEL0);             //10-->3.0V   11-->4.0V
    }
    #elif (HW_ADC_VREF==VREF4_0)
    {
        SetBit(VREF_VHALF_CR, VRVSEL1);             //00-->4.5V   01-->VDD5
        SetBit(VREF_VHALF_CR, VRVSEL0);             //10-->3.0V   11-->4.0V
    }
    #elif (HW_ADC_VREF==VREF4_5)
    {
        ClrBit(VREF_VHALF_CR, VRVSEL1);             //00-->4.5V   01-->VDD5
        ClrBit(VREF_VHALF_CR, VRVSEL0);             //10-->3.0V   11-->4.0V
    }
    #else
    {
        ClrBit(VREF_VHALF_CR, VRVSEL1);             //00-->4.5V   01-->VDD5
        SetBit(VREF_VHALF_CR, VRVSEL0);             //10-->3.0V   11-->4.0V
    }
    #endif

    SetReg(VREF_VHALF_CR, VREFEN, (Status ? VREFEN : 0x00));
}


/** 
 * @brief        基准电压VHALF配置
 */
void VHALFConfig(uint8 Status)
{
    SetReg(VREF_VHALF_CR, VHALFEN, (Status ? VHALFEN : 0x00));
}

/** 
 * @brief        看门狗配置
 * @param[in]    Value : [输入] -- 定时时间，单位ms，最小定时时间8ms，最大定时1800ms
 * @param[in]    Status: [输入] -- 使能控制，Disable或Enable
 */
/* -------------------------------------------------------------------------------------------------
    Function Name  : WatchDogConfig
    Description    : 1、看门狗定时函数初始化，看门狗使能和复位使能，定时配置
    Date           : 2020-08-07
    Parameter      : Value : [输入] -- 定时时间，单位ms，最小定时时间8ms，最大定时1800ms
**			         Status: [输入] -- 使能控制，Disable或Enable
------------------------------------------------------------------------------------------------- */
void WatchDogConfig(uint16 Value, uint8 Status)
{
    SetReg(CCFG1, WDTEN, (Status ? WDTEN : 0x00));
    WDT_REL = ((uint16)(65532-(uint32)Value*32768/1000) >> 8);
    ClrBit(WDT_CR, WDTF);
    SetBit(WDT_CR, WDTRF);
}


/** 
 * @brief        刷新看门狗计数器
 */
void WatchDogRefresh(void)
{
    SetBit(WDT_CR, WDTRF);
}


/** 
 * @brief        1、扇区自擦除: 指定将要擦除的Flash扇区，每个扇区128Byte，共128个扇区
                 2、扇区0~127对应Flash地址0x0000~0x3fff，通过指定Flash地址来指定要擦除
                 3、的Flash地址所在扇区。一次只能擦除一个扇区，自擦除数据为任意值，一定
                 4、要在解锁后才给DPTR赋值。
 * @param[in]    FlashAddress: [输入] -Flash自擦除扇区内任意地址
 * @return        [输出] 0--Flash自擦除成功，1--Flash自擦除失败
 */
uint8 Flash_Sector_Erase(uint8 xdata *FlashAddress)
{
    bool TempEA;
    uint16 TempFlashAddress;

    TempEA = EA;
    EA = 0;
    TempFlashAddress = FlashAddress;

    if(TempFlashAddress < 0x3f80)                   // 不擦除最后一个扇区
    {
        FLA_CR = 0x03;                          //使能自擦除
        FLA_KEY = 0x5a;
        FLA_KEY = 0x1f;                         //flash预编程解锁
        _nop_();
        *FlashAddress = 0xff;                   //写任意数据
        FLA_CR = 0x08;                          //开始预编程，完成后Flash再次上锁
    }

    EA = TempEA;

    if(ReadBit(FLA_CR, FLAERR))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


/** This file contains system  function used for Motor Control.
 * @brief        1、Flash自烧写: 对扇区预编程和自擦除后，可以对扇区内的地址进行Flash烧写，
                 2、一次烧写一个byte,一定要在解锁后才给DPTR赋值
 * @param[in]    FlashAddress: [输入] -- Flash烧写地址
 * @param[in]    FlashData   : [输入] -- Flash烧写数据
 * @return       [输出] 0--Flash写成功，1--Flash写失败
 */
uint8 Flash_Sector_Write(uint8 xdata *FlashAddress, uint8 FlashData)
{
    bool TempEA;
    uint16 TempFlashAddress;
    
    TempEA = EA;
    EA = 0;
    TempFlashAddress = FlashAddress;

    if(TempFlashAddress < 0x3f80)         // 不编程最后一个扇区
    {
        FLA_CR = 0x01;              // 使能Flash编程
        FLA_KEY = 0x5a;
        FLA_KEY = 0x1f;             // flash预编程解锁
        _nop_();
        *FlashAddress = FlashData;  // 写编程数据
        FLA_CR = 0x08;              // 开始预编程，完成后Flash再次上锁
    }

    EA = TempEA;

    if(ReadBit(FLA_CR, FLAERR))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
