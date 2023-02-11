#ifndef _SOFT_IIC_H
#define _SOFT_IIC_H

#include "stdint.h"

#define SCL_Type SOFTIIC_SCL_GPIO_Port
#define SDA_Type SOFTIIC_SDA_GPIO_Port
#define SCL_GPIO SOFTIIC_SCL_Pin
#define SDA_GPIO SOFTIIC_SDA_Pin

#define SDA_OUT(X)                                           \
    if (X)                                                   \
        HAL_GPIO_WritePin(SDA_Type, SDA_GPIO, GPIO_PIN_SET); \
    else                                                     \
        HAL_GPIO_WritePin(SDA_Type, SDA_GPIO, GPIO_PIN_RESET);

#define SCL_OUT(X)                                           \
    if (X)                                                   \
        HAL_GPIO_WritePin(SCL_Type, SCL_GPIO, GPIO_PIN_SET); \
    else                                                     \
        HAL_GPIO_WritePin(SCL_Type, SCL_GPIO, GPIO_PIN_RESET);

#define SDA_IN HAL_GPIO_ReadPin(SDA_Type, SDA_GPIO) // 只有输入模式才能读取电平状态

void simiic_send_ch(uint8_t c);
void simiic_read_regs(uint8_t dev_add, uint8_t reg, uint8_t *dat_add, uint8_t num);
void simiic_write_reg(uint8_t dev_add, uint8_t reg, uint8_t dat);
uint8_t simiic_read_reg(uint8_t dev_add, uint8_t reg);

#endif
