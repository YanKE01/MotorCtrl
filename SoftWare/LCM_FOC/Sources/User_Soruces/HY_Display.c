/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2023-05-16 09:56:38
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-05-17 14:44:09
 * @FilePath: \LCM_FOC\Sources\User_Soruces\HY_Display.c
 */
#include "HY_Display.h"
#include "HY_Variable.h"
#include "HY_SoftIIC.h"

static uint8_t s_7number[11] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x00}; // 7段显示方式0~9 第10位为不显示位
static uint8_t s_8number[11] = {0xBF, 0x86, 0xDB, 0xCF, 0xE6, 0xED, 0xFD, 0x87, 0xFF, 0xEF, 0x00}; // 8段显示方式0~9

void HY_TM1650_SetIndexNumber(uint8_t index, uint8_t mode, uint8_t num);

/**
 * @description: TM1650写
 * @param {uint8_t} addr
 * @param {uint8_t} data
 * @return {*}
 */
void HY_TM1650_Write(uint8_t addr, uint8_t data)
{
    iic_start();        // 发送起始信号
    iic_sendByte(addr); // 写地址
    iic_waitAck();      // 等待应答
    iic_sendByte(data); // 写入数据
    iic_ack();          // 发送应答
    iic_stop();         // 发送停止信号
}

/**
 * @description: TM1650读取
 * @param {uint8_t} addr
 * @return {*}
 */
uint8_t HY_TM1650_Read(uint8_t addr)
{
    uint8_t rekey = 0;
    iic_start();        // 发送起始信号
    iic_sendByte(addr); // 写地址
    iic_waitAck();      // 等待应答
    rekey = iic_readByte();
    iic_waitAck(); // 发送应答
    iic_stop();    // 发送停止信号
    return rekey;
}

/**
 * @description: TM1650设置显示
 * @param {uint8_t} brightness
 * @param {uint8_t} mode
 * @param {uint8_t} state
 * @return {*}
 */
void HY_TM1650_SetDisplay(uint8_t brightness, uint8_t mode, uint8_t state)
{
    if (state)
    {
        if (mode == 7) // 7段显示方式
        {
            HY_TM1650_Write(0x48, brightness * 16 + 1 * 4 + 1);
        }
        else if (mode == 8) // 8段显示方式
        {
            HY_TM1650_Write(0x48, brightness * 16 + 1);
        }
    }
    else
    {
        HY_TM1650_Write(0x48, 0x00); // 关闭显示
    }
}

/**
 * @description: TM1650清空显存
 * @return {*}
 */
void HY_TM1650_Clear(void)
{
    uint8_t j = 0;
    for (j = 0; j < 4; j++)
    {
        HY_TM1650_SetIndexNumber(j, 7, 10);
    }
}

/**
 * @description: TM1650单独设置数字
 * @param {uint8_t} index
 * @param {uint8_t} mode
 * @param {uint8_t} num
 * @return {*}
 */
void HY_TM1650_SetIndexNumber(uint8_t index, uint8_t mode, uint8_t num)
{
    uint8_t indexAddr = 0;
    uint8_t numValue = 0;

    if (mode == 7) // 7段显示方式
    {
        numValue = s_7number[num];
    }
    else if (mode == 8) // 8段显示方式
    {
        numValue = s_8number[num];
    }

    if (index == 0)
    {
        indexAddr = 0x68;
    }
    else if (index == 1)
    {
        indexAddr = 0x6A;
    }
    else if (index == 2)
    {
        indexAddr = 0x6C;
    }
    else if (index == 3)
    {
        indexAddr = 0x6E;
    }

    HY_TM1650_Write(indexAddr, numValue);
}

/**
 * @description: TM1650设置数字
 * @param {uint16_t} num
 * @return {*}
 */
void HY_TM1650_SetNumber(uint16_t num)
{
    uint8_t index = 3;
    // HY_TM1650_Clear();

    if (num > 9999)
    {
        return;
    }

    // 拆分位数
    while (num)
    {
        HY_TM1650_SetIndexNumber(index, 7, num % 10);
        index--;
        num /= 10;
    }
}

/**
 * @description: TM1650设置字符
 * @param {uint8_t} index
 * @param {char} letter
 * @return {*}
 */
void HY_TM1650_SetIndexLetter(uint8_t index, char letter)
{
    uint8_t indexAddr = 0;

    if (index == 0)
    {
        indexAddr = 0x68;
    }
    else if (index == 1)
    {
        indexAddr = 0x6A;
    }
    else if (index == 2)
    {
        indexAddr = 0x6C;
    }
    else if (index == 3)
    {
        indexAddr = 0x6E;
    }

    if (letter == 'P')
    {
        HY_TM1650_Write(indexAddr, 0X73);
    }
    else if (letter == 'F')
    {
        HY_TM1650_Write(indexAddr, 0X71);
    }
    else if (letter == '.')
    {
        HY_TM1650_Write(indexAddr, 0X80);
    }
    else if (letter == 'E')
    {
        HY_TM1650_Write(indexAddr, 0X79);
    }
}

/**
 * @description: TM1650设置浮点
 * @param {float} num
 * @return {*}
 */
void HY_TM1650_SetFloat(float num)
{

    int integer = (int)(num);
    int decimal = (int)((num - integer) * 10); // 只保留一位小数
    uint8_t index = 2;

    // HY_TM1650_Clear();

    if (integer > 999)
    {
        return; // 超出范围，不显示
    }

    // 显示整数部分需要判断是否为0
    if (integer != 0)
    {
        // 显示整数
        while (integer)
        {
            if (index != 2)
            {
                HY_TM1650_SetIndexNumber(index, 7, integer % 10);
            }
            else
            {
                // 最后一位，追加小数点
                HY_TM1650_Write(0x6C, s_7number[integer % 10] | 0x80);
            }

            index--;
            integer /= 10;
        }
    }
    else
    {
        // HY_TM1650_SetIndexNumber(2, 7, 0);
        HY_TM1650_Write(0x6C, s_7number[0] | 0x80);
    }

    HY_TM1650_SetIndexNumber(3, 7, decimal); // 显示小数
}

/**
 * @description: 按键扫描
 * @return {*}
 */
uint8_t HY_TM1650_ScanKey()
{
    return HY_TM1650_Read(0x49);
}

/**
 * @description: 显示故障码
 * @return {*}
 */
void HY_TM1650_ShowFault(UGT_S_SYSTEMSTATE_STRU fault)
{
    if (fault.uSystemError.Bits.OverVoltage)
    {
        // 过压为E01
        HY_TM1650_SetIndexLetter(0, 'E');
        HY_TM1650_SetNumber(1);
    }
    else if (fault.uSystemError.Bits.UnderVoltage)
    {
        // 欠压E02
        HY_TM1650_SetIndexLetter(0, 'E');
        HY_TM1650_SetNumber(2);
    }
    else if (fault.uSystemError.Bits.StartupFailContious)
    {
        // 连续驱动失败E03
        HY_TM1650_SetIndexLetter(0, 'E');
        HY_TM1650_SetNumber(3);
    }
    else if (fault.uSystemError.Bits.HardOverCurrent)
    {
        // 硬件过流E04
        HY_TM1650_SetIndexLetter(0, 'E');
        HY_TM1650_SetNumber(4);
    }
    else
    {
        // 说明底层已经检测到错误消失了，可以解锁用户错误标志位
        motor.fault = 0;
    }
}