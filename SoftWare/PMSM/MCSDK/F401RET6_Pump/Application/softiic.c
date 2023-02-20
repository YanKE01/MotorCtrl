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
 * @brief �����ʱ
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
 * @brief sda����Ϊ���ģʽ
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
 * @brief iic��ʼ
 * @other SCL�ߣ�SDA��->��
 *
 */
void iic_start()
{
    sda_ouput();
    IIC_SDA_1();
    IIC_SCL_1();
    iic_delay();
    IIC_SDA_0(); // ��SCL�ߵ�ƽʱ��SDA����һ�������ر�ʾI2C���������ź�
    iic_delay();
    IIC_SCL_0(); // ǯסI2C���ߣ�׼�����ͻ��������
}

void iic_stop()
{
    sda_ouput();
    IIC_SCL_0();
    IIC_SDA_0();
    IIC_SCL_1();
    iic_delay();
    IIC_SDA_1(); // ��SCL�ߵ�ƽʱ��SDA����һ�������ر�ʾI2C����ֹͣ�ź�
    iic_delay();
}

void iic_sendByte(uint8_t ucByte)
{
    uint8_t i;

    sda_ouput(); // SDA�����ģʽ

    IIC_SCL_0(); // ����ʱ�ӿ�ʼ���ݴ���

    // ÿһλ���� SCL�ڸߵ�ƽ��ʱ��SDA���ݱ����ȶ�
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
        ucByte <<= 1; // �Ӹ�λ����λ
        iic_delay();
        IIC_SCL_1();
        iic_delay();
        IIC_SCL_0();
        iic_delay();
    }
}

/**
 * @brief �ȴ��ӻ���Ӧ�����ͱ�ʾ��ȷ��Ӧ
 *
 * @return uint8_t
 */
uint8_t iic_waitAck(void)
{
    uint8_t result = 0;

    sda_input(); // SDA������ģʽ

    IIC_SDA_1(); // CPU�ͷ�SDA����
    iic_delay();
    IIC_SCL_1(); // CPU����SCL = 1, ��ʱ�����᷵��ACKӦ��
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
 * @brief ����Ӧ���ź�
 *
 */
void iic_ack()
{
    sda_ouput(); // SDA�����ģʽ

    IIC_SDA_0(); // CPU����SDA = 0
    iic_delay();
    IIC_SCL_1(); // CPU����1��ʱ��
    iic_delay();
    IIC_SCL_0();
    iic_delay();
    IIC_SDA_1(); // CPU�ͷ�SDA����
}

/**
 * @brief ���ӻ��Ƿ��Ӧ
 *
 * @param address
 * @return uint8_t
 */
uint8_t iic_checkDevice(uint8_t address)
{
    uint8_t ucAck;

    iic_stop();            // ��ʼ��I2C
    iic_start();           // ���������ź�
    iic_sendByte(address); // �豸��I2C���ߵ�ַ+��д����bit��0 = w�� 1 = r)
    ucAck = iic_waitAck(); // ����豸��ACKӦ��
    iic_stop();            // ����ֹͣ�ź�

    return ucAck;
}
