/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2023-03-26 13:59:03
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-03-27 20:40:36
 * @FilePath: \Software\User\Source\Hardware\TM1650.c
 */
#include "TM1650.h"

sbit CLK = P0 ^ 4;
sbit DIO = P0 ^ 5;

static uint8 s_7number[11] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x00}; // 7段显示方式0~9 第10位为不显示位
static uint8 s_8number[11] = {0xBF, 0x86, 0xDB, 0xCF, 0xE6, 0xED, 0xFD, 0x87, 0xFF, 0xEF, 0x00}; // 8段显示方式0~9

/**
 * @description: 微秒延迟
 * @param {int} i
 * @return {*}
 */
void Delay_us(int i)
{
    for (; i > 0; i--)
    {
        _nop_();
        _nop_();
        _nop_();
        _nop_();
        _nop_();
    }
}

/**
 * @description: 管脚测试
 * @param {uint8} state
 * @return {*}
 */
void TM1650_IOTest(uint8 state)
{
    CLK = state;
    DIO = state;
}

/**
 * @description: TM1650的起始
 * @return {*}
 */
void Start1650(void)
{
    CLK = 1;
    DIO = 1;
    Delay_us(5);
    DIO = 0;
}

/**
 * @description: TM1650的停止
 * @return {*}
 */
void Stop1650(void)
{
    CLK = 1;
    DIO = 0;
    Delay_us(5);
    DIO = 1;
}

/**
 * @description: TM1650写一个byte
 * @param {uint8_t} oneByte
 * @return {*}
 */
void WriteByte1650(uint8 oneByte)
{
    uint8 i = 0;
    CLK = 0;
    Delay_us(1);

    for (i = 0; i < 8; i++)
    {
        if (oneByte & 0x80)
        {
            DIO = 1;
        }
        else
        {
            DIO = 0;
        }

        oneByte <<= 1;
        // 高电平期间稳定
        CLK = 0;
        Delay_us(5);
        CLK = 1;
        Delay_us(5);
        CLK = 0;
    }
}

/**
 * @description: ACK信号
 * @return {*}
 */
void Ask1650()
{
    uint8 timeout = 0;
    CLK = 1;
    Delay_us(5);
    CLK = 0;
    while ((DIO) && (timeout <= 100))
    {
        timeout++;
    }
    Delay_us(5);
    CLK = 0;
}

/**
 * @description: 设置数码管
 * @param {uchar} add
 * @param {uchar} dat
 * @return {*}
 */
void Set1650(uint8 add, uint8 dat)
{

    Start1650();
    WriteByte1650(add); // 第一个显存地址
    Ask1650();
    WriteByte1650(dat);
    Ask1650();
    Stop1650();
}

/**
 * @description: 设置显示模式
 * @param {uint8} brightness
 * @param {uint8} mode
 * @param {uint8} state
 * @return {*}
 */
void SetDisplay1650(uint8 brightness, uint8 mode, uint8 state)
{
    if (state)
    {
        if (mode == 7) // 7段显示方式
        {
            Set1650(0x48, brightness * 16 + 1 * 4 + 1);
        }
        else if (mode == 8) // 8段显示方式
        {
            Set1650(0x48, brightness * 16 + 1);
        }
    }
    else
    {
        Set1650(0x48, 0x00); // 关闭显示
    }
}

/**
 * @description: 在对应的INDEX显示数字
 * @param {uint8} index
 * @param {uint8} mode
 * @param {uint8} num
 * @return {*}
 */
void SetIndexNumber1650(uint8 index, uint8 mode, uint8 num)
{
    uint8 indexAddr = 0;
    uint8 numValue = 0;

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

    Set1650(indexAddr, numValue);
}

/**
 * @description: 清空TM1650
 * @return {*}
 */
void Clear1650(void)
{
    uint8 j = 0;
    for (j = 0; j < 4; j++)
    {
        SetIndexNumber1650(j, 7, 10);
    }
}

/**
 * @description: 4位数码管直接显示数字
 * @param {uint16_t} num
 * @return {*}
 */
void SetNumber1650(uint16 num)
{
    uint8 index = 3;
    Clear1650();
    if (num > 9999)
    {
        return;
    }

    // 拆分位数
    while (num)
    {
        SetIndexNumber1650(index, 7, num % 10);
        index--;
        num /= 10;
    }
}
