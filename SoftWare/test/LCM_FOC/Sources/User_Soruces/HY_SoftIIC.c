/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2023-05-16 10:10:40
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-05-17 14:34:29
 * @FilePath: \LCM_FOC\Sources\User_Soruces\HY_SoftIIC.c
 */
#include "HY_SoftIIC.h"
#include "lcm32f037_gpio.h"
#include "lcm32f037_rcc.h"

// SCL:PA0 SDA:PA1

/**
 * @description: 软件延时
 * @return {*}
 */
void iic_delay(void)
{
    uint16_t j = 500; //500
    while (j--)
    {
    }
}

/**
 * @description: sda设置为输出
 * @return {*}
 */
void sda_ouput()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType 	= GPIO_OType_OD;
		GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_NOPULL;		
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
    GPIO_Init(GPIOA, &GPIO_InitStructure); // 初始化
}
/**
 * @description: sda设置为输入
 * @return {*}
 */
void sda_input()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
    GPIO_Init(GPIOA, &GPIO_InitStructure); // 初始化
}

/**
 * @description: iic起始
 * @return {*}
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

/**
 * @description: iic终止
 * @return {*}
 */
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

/**
 * @description: 发送1个byte
 * @param {uint8_t} ucByte
 * @return {*}
 */
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
 * @description: 读取1个byte
 * @return {*}
 */
uint8_t iic_readByte()
{
    uint8_t i, rekey=0;
    sda_input();

    for (i = 0; i < 8; i++)
    {
        IIC_SCL_0();
        iic_delay();
        IIC_SCL_1();
        rekey = rekey << 1;

        if (IIC_SDA_READ())
        {
            rekey++;
        }
    }

    return rekey;
}

/**
 * @description: 等待回应
 * @return {*}
 */
uint8_t iic_waitAck(void)
{
    uint8_t timeout = 0;
    IIC_SCL_1();
    iic_delay();
    IIC_SCL_0();
    while ((IIC_SDA_READ()) && (timeout <= 10))
    {
        timeout++;
    }
    iic_delay();
    IIC_SCL_0();

    return 0;
}

/**
 * @description: 产生应答
 * @return {*}
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