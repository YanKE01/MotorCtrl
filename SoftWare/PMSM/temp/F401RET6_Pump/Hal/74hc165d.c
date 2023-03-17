/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2023-02-19 17:13:15
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-02-20 17:35:43
 * @FilePath: \F401RET6_Pump\Hal\74hc165d.c
 */

#include "74hc165d.h"
#include "cmsis_os.h"
#include "main.h"

extern osMutexId my74HCMutexHandle;

void delay(void)
{
    uint16_t j = 200;
    while (j--)
    {
    }
}

/**
 * @brief 读取74HC165D状态
 *
 * @return uint8_t
 */
uint8_t Read74HC165D(void)
{
    uint8_t data = 0;

    if (osMutexWait(my74HCMutexHandle, osWaitForever) == osOK)
    {
        HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(SL_GPIO_Port, SL_Pin, GPIO_PIN_RESET);
        osDelay(1);
        HAL_GPIO_WritePin(SL_GPIO_Port, SL_Pin, GPIO_PIN_SET);
        //osDelay(1);
		delay();

        for (uint8_t i = 0; i < 8; i++)
        {
            data = data << 1;

            if (HAL_GPIO_ReadPin(DATA_GPIO_Port, DATA_Pin) == 1)
            {
                data = data | 0x01;
            }

            HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_RESET);
            osDelay(1);
			//delay();
            HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_SET);
        }

        HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_RESET);

        osMutexRelease(my74HCMutexHandle);
    }

    return data;
}
