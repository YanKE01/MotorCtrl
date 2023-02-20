/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2023-02-19 17:13:15
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-02-20 09:10:08
 * @FilePath: \F401RET6_Pump\Hal\74hc165d.c
 */

#include "74hc165d.h"
#include "cmsis_os.h"
#include "main.h"

void delay(void)
{
    uint16_t j = 200;
    while (j--)
    {
    }
}

uint8_t Read74HC165D(void)
{
    uint8_t data = 0;
    HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(SL_GPIO_Port, SL_Pin, GPIO_PIN_RESET);
    delay();
    HAL_GPIO_WritePin(SL_GPIO_Port, SL_Pin, GPIO_PIN_SET);

    for (uint8_t i = 0; i < 8; i++)
    {
        data = data << 1;
        if (HAL_GPIO_ReadPin(DATA_GPIO_Port, DATA_Pin) == 1)
        {
            data = data | 0x01;
        }

        HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_RESET);
        delay();
        HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_SET);
    }

    HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_RESET);

    return data;
}
