/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2023-01-26 21:26:25
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-02-10 18:34:30
 * @FilePath: \F401RE_RTOS\Hal\as5600.c
 */
#include "stm32f4xx_hal.h"
#include "as5600.h"
#include "stm32f4xx_hal_i2c.h"
// #include "i2c.h"
#include "softiic.h"
#include "stdint.h"

#define abs(x) ((x) > 0 ? (x) : -(x))

const uint8_t AS5600_RAW_ADDR = 0x36;           /*AS5600原始7位地址*/
const uint8_t AS5600_RAW_ANGLE_REGISTER = 0x0C; /*AS5600原始角度寄存器*/
const uint16_t AS5600_RESOLUTION = 4096;        /*AS5600分辨率*/
const float _2PI = 6.283f;

/**
 * @brief 获取原始角度数据 0~360
 *
 * @return 错误返回-1
 */
int16_t GetRawAngle(void)
{
    uint8_t high, low = 0;

    high = simiic_read_reg(AS5600_RAW_ADDR, 0x0C);
    low = simiic_read_reg(AS5600_RAW_ADDR, 0X0D);

    return (int16_t)(high << 8 | low);
}

/**
 * @brief 返回角度(弧度制) 具有圈数保留功能
 *
 * @return float
 */
float GetAngle(void)
{
    static float full_rotation_count = 0.0f; // 统计转过圈数
    static float angle_prev = 0.0f;

    float angle = GetRawAngle();
    float error = angle - angle_prev;

    if (abs(error) > 0.8f * AS5600_RESOLUTION)
    {
        full_rotation_count += (error > 0 ? -_2PI : _2PI); // 统计圈数
    }

    angle_prev = angle;

    return -1.0f * (full_rotation_count + (angle / (float)AS5600_RESOLUTION * _2PI));
}
