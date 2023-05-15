/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2023-05-16 10:11:00
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-05-16 16:39:20
 * @FilePath: \LCM_FOC\Headers\User_Sources\HY_SoftIIC.h
 */
#ifndef _HY_SOFT_IIC_H
#define _HY_SOFT_IIC_H

#include "lcm32f037_conf.h"
#include "lcm32f037_gpio.h"

#define IIC_SCL_0() GPIO_ResetBits(GPIOA, GPIO_Pin_1);
#define IIC_SCL_1() GPIO_SetBits(GPIOA, GPIO_Pin_1);
#define IIC_SDA_0() GPIO_ResetBits(GPIOA, GPIO_Pin_0);
#define IIC_SDA_1() GPIO_SetBits(GPIOA, GPIO_Pin_0);
#define IIC_SDA_READ() GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)

uint8_t iic_checkDevice(uint8_t address);
uint8_t iic_waitAck(void);
void iic_sendByte(uint8_t ucByte);
void iic_stop(void);
void iic_start(void);
void iic_ack(void);
void iic_delay(void);
uint8_t iic_readByte();

void sda_input();

#endif
