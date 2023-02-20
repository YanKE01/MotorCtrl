/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2022-12-12 17:08:41
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2022-12-12 18:37:23
 * @FilePath: \Digit_Test\MyDriver\softiic.c
 */
#include "softiic.h"
#include "stdint.h"
#include "stm32f4xx_hal_gpio.h"

#define IIC_SCL_0() HAL_GPIO_WritePin(IIC_SCL_PORT, IIC_SCL_PIN, GPIO_PIN_RESET)
#define IIC_SCL_1() HAL_GPIO_WritePin(IIC_SCL_PORT, IIC_SCL_PIN, GPIO_PIN_SET)
#define IIC_SDA_0() HAL_GPIO_WritePin(IIC_SDA_PORT, IIC_SDA_PIN, GPIO_PIN_RESET)
#define IIC_SDA_1() HAL_GPIO_WritePin(IIC_SDA_PORT, IIC_SDA_PIN, GPIO_PIN_SET)
#define IIC_SDA_READ() HAL_GPIO_ReadPin(IIC_SDA_PORT, IIC_SDA_PIN)

/**
 * @brief 软件延时
 *
 */
void iic_delay(void)
{
    uint16_t j = 200;
    while (j--)
    {
    }
}

/**
 * @brief sda设置为输出模式
 *
 */
void sda_ouput()
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.Pin = IIC_SDA_PIN;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_OD;
    HAL_GPIO_Init(IIC_SDA_PORT, &GPIO_InitStructure);
}

void sda_input()
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.Pin = IIC_SDA_PIN;
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
    HAL_GPIO_Init(IIC_SDA_PORT, &GPIO_InitStructure);
}

/**
 * @brief iic起始
 * @other SCL高，SDA高->低
 *
 */
void iic_start()
{
    sda_ouput();
    IIC_SDA_1();
    IIC_SCL_1();
    iic_delay();
    IIC_SDA_0(); // 当SCL高电平时，SDA出现一个下跳沿表示I2C总线启动信号
    iic_delay();
    IIC_SCL_0(); // 钳住I2C总线，准备发送或接收数据
}

void iic_stop()
{
    sda_ouput();
    IIC_SCL_0();
    IIC_SDA_0();
    IIC_SCL_1();
    iic_delay();
    IIC_SDA_1(); // 当SCL高电平时，SDA出现一个上跳沿表示I2C总线停止信号
    iic_delay();
}

void iic_sendByte(uint8_t ucByte)
{
    uint8_t i;

    sda_ouput(); // SDA线输出模式

    IIC_SCL_0(); // 拉低时钟开始数据传输

    // 每一位发送 SCL在高电平的时候，SDA数据保持稳定
    for (i = 0; i < 8; i++)
    {
        if (ucByte & 0x80)
        {
            IIC_SDA_1();
        }
        else
        {
            IIC_SDA_0();
        }
        ucByte <<= 1; // 从高位到低位
        iic_delay();
        IIC_SCL_1();
        iic_delay();
        IIC_SCL_0();
        iic_delay();
    }
}

/**
 * @brief 等待从机回应，拉低表示正确回应
 *
 * @return uint8_t
 */
uint8_t iic_waitAck(void)
{
    uint8_t result = 0;

    sda_input(); // SDA线输入模式

    IIC_SDA_1(); // CPU释放SDA总线
    iic_delay();
    IIC_SCL_1(); // CPU驱动SCL = 1, 此时器件会返回ACK应答
    iic_delay();
    if (IIC_SDA_READ())
    {
        result = 1;
    }
    else
    {
        result = 0;
    }
    IIC_SCL_0();
    iic_delay();

    return result;
}

/**
 * @brief 产生应答信号
 *
 */
void iic_ack()
{
    sda_ouput(); // SDA线输出模式

    IIC_SDA_0(); // CPU驱动SDA = 0
    iic_delay();
    IIC_SCL_1(); // CPU产生1个时钟
    iic_delay();
    IIC_SCL_0();
    iic_delay();
    IIC_SDA_1(); // CPU释放SDA总线
}

/**
 * @brief 检查从机是否回应
 *
 * @param address
 * @return uint8_t
 */
uint8_t iic_checkDevice(uint8_t address)
{
    uint8_t ucAck;

    iic_stop();            // 初始化I2C
    iic_start();           // 发送启动信号
    iic_sendByte(address); // 设备的I2C总线地址+读写控制bit（0 = w， 1 = r)
    ucAck = iic_waitAck(); // 检测设备的ACK应答
    iic_stop();            // 发送停止信号

    return ucAck;
}
