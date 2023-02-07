/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2023-02-07 10:56:18
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-02-07 12:22:40
 * @FilePath: \F407IGT6_HALL\Ctrl\hall.c
 */

#include "hall.h"
#include "main.h"
#include "gpio.h"
#include "variable.h"

/**
 * @brief 正点的电机是120度布置的 顺序是W V U
 *
 * @return uint32_t
 */
void GetHallState()
{
    motorParameter.hallState=0;
    if (HAL_GPIO_ReadPin(HALL_U_GPIO_Port, HALL_U_Pin) != GPIO_PIN_RESET)
    {
        motorParameter.hallState |= 0x01U;
    }

    if (HAL_GPIO_ReadPin(HALL_V_GPIO_Port, HALL_V_Pin) != GPIO_PIN_RESET)
    {
        motorParameter.hallState |= 0x02U;
    }

    if (HAL_GPIO_ReadPin(HALL_W_GPIO_Port, HALL_W_Pin) != GPIO_PIN_RESET)
    {
        motorParameter.hallState |= 0x04U;
    }

}


