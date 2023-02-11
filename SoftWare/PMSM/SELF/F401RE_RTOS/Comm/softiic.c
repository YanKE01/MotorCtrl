/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2023-02-05 18:33:00
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-02-10 18:34:58
 * @FilePath: \F401RE_RTOS\Comm\softiic.c
 */
#include "softiic.h"
#include "gpio.h"
#include "main.h"
#include "stdint.h"

static GPIO_InitTypeDef GPIO_InitStruct;

#define ack 1    // 主应答
#define no_ack 0 // 从应答

/**
 * @brief SDA配置为输出模式
 *
 */
void simiic_sda_out(void)
{
    GPIO_InitStruct.Pin = SDA_GPIO;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(SDA_Type, &GPIO_InitStruct);
}

/**
 * @brief SDA配置为输入模式
 *
 */
void simiic_sda_in(void)
{
    GPIO_InitStruct.Pin = SDA_GPIO;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(SDA_Type, &GPIO_InitStruct);
}

void simiic_delay(void)
{
    uint16_t j = 200;
    while (j--)
    {
    }
}

/**
 * @brief 软件IIC起始信号 SCL:HIGH SDA:HIGH->LOW
 *
 */
void simiic_start(void)
{
    SDA_OUT(1);
    SCL_OUT(1);
    simiic_delay();
    SDA_OUT(0);
    simiic_delay();
    SCL_OUT(0);
}

/**
 * @brief 软件IIC停止信号 SCL:HIGH SDA:LOW->HIGH
 *
 */
void simiic_stop(void)
{
    SDA_OUT(0);
    SCL_OUT(0);
    simiic_delay();
    SCL_OUT(1);
    simiic_delay();
    SDA_OUT(1);
    simiic_delay();
}

/**
 * @brief 从机需要在第9个CLK将SDA拉低
 *
 */
int simiic_waitAck(void)
{
    SCL_OUT(0);
    simiic_sda_in();
    simiic_delay();

    SCL_OUT(1);
    simiic_delay(); // 第9个CLK

    if (SDA_IN)
    {
        // 通讯失败
        simiic_sda_out();
        SCL_OUT(0);
        return 0;
    }

    simiic_sda_out();
    SCL_OUT(0);
    simiic_delay();
    return 1;
}

/**
 * @brief 发送字节，高位先行.SCL为高电平期间，保持数据稳定
 *
 * @param c
 */
void simiic_send_ch(uint8_t c)
{
    uint8_t i = 8;
    while (i--)
    {
        if (c & 0x80)
        {
            SDA_OUT(1);
        }
        else
        {
            SDA_OUT(0);
        }
        c <<= 1;
        simiic_delay();
        SCL_OUT(1); // 高电平期间保持数据稳定
        simiic_delay();
        SCL_OUT(0);
    }
    simiic_waitAck();
}

/**
 * @brief 主应答
 *
 * @param ack_dat
 */
void simiic_sendack(uint8_t ack_dat)
{
    SCL_OUT(0);
    simiic_delay();
    if (ack_dat)
    {
        SDA_OUT(0);
    }
    else
    {
        SDA_OUT(1);
    }

    SCL_OUT(1);
    simiic_delay();
    SCL_OUT(0);
    simiic_delay();
}

/**
 * @brief 读取数据
 *
 * @param ack_x
 * @return uint8_t
 */
uint8_t simiic_read_ch(uint8_t ack_x)
{
    uint8_t i;
    uint8_t c;
    c = 0;
    SCL_OUT(0);
    simiic_delay();
    SDA_OUT(1);
    simiic_sda_in(); // 输入模式
    for (i = 0; i < 8; i++)
    {
        simiic_delay();
        SCL_OUT(0); // 置时钟线为低，准备接收数据位
        simiic_delay();
        SCL_OUT(1); // 置时钟线为高，使数据线上数据有效
        simiic_delay();
        c <<= 1;
        if (SDA_IN)
        {
            c += 1; // 读数据位，将接收的数据存c
        }
    }
    simiic_sda_out();
    SCL_OUT(0);
    simiic_delay();
    simiic_sendack(ack_x);

    return c;
}

/**
 * @brief 软件IIC写寄存器
 *
 * @param dev_add
 * @param reg
 * @param dat
 */
void simiic_write_reg(uint8_t dev_add, uint8_t reg, uint8_t dat)
{
    simiic_start();
    simiic_send_ch((dev_add << 1) | 0x00); // 发送器件地址加写位
    simiic_send_ch(reg);                   // 发送从机寄存器地址
    simiic_send_ch(dat);                   // 发送从机寄存器地址
    simiic_stop();
}

/**
 * @brief 读寄存器
 *
 * @param dev_add
 * @param reg
 * @return uint8_t
 */
uint8_t simiic_read_reg(uint8_t dev_add, uint8_t reg)
{
    uint8_t dat;
    simiic_start();
    simiic_send_ch((dev_add << 1) | 0x00); // 发送器件地址加写位
    simiic_send_ch(reg);                   // 发送从机寄存器地址

    simiic_start();
    simiic_send_ch((dev_add << 1) | 0x01); // 发送器件地址加读位
    dat = simiic_read_ch(no_ack);          // 读取数据
    simiic_stop();

    return dat;
}

void simiic_read_regs(uint8_t dev_add, uint8_t reg, uint8_t *dat_add, uint8_t num)
{
    simiic_start();
    simiic_send_ch((dev_add << 1) | 0x00); // 发送器件地址加写位
    simiic_send_ch(reg);                   // 发送从机寄存器地址

    simiic_start();
    simiic_send_ch((dev_add << 1) | 0x01); // 发送器件地址加读位
    while (--num)
    {
        *dat_add = simiic_read_ch(ack); // 读取数据
        dat_add++;
    }
    *dat_add = simiic_read_ch(no_ack); // 读取数据
    simiic_stop();
}
