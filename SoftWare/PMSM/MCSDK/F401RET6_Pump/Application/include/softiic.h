/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2022-12-12 17:08:56
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2022-12-21 14:16:26
 * @FilePath: \Digit_Test\MyDriver\include\softiic.h
 */
#ifndef _SOFT_IIC_H
#define _SOFT_IIC_H

#include "main.h"

#define IIC_SCL_PORT TM1650_CLK_GPIO_Port
#define IIC_SCL_PIN TM1650_CLK_Pin
#define IIC_SDA_PORT TM1650_DIO_GPIO_Port
#define IIC_SDA_PIN TM1650_DIO_Pin



uint8_t iic_checkDevice(uint8_t address);
uint8_t iic_waitAck(void);
void iic_sendByte(uint8_t ucByte);
void iic_stop(void);
void iic_start(void);
void iic_ack(void);
void iic_delay(void);



#endif
