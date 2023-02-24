/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2023-02-19 15:59:04
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-02-19 16:01:36
 * @FilePath: \F401RET6_Pump\Hal\hal.c
 */
#include "hal.h"
#include "main.h"

/**
 * @brief 硬件外设初始化
 * 
 */
void HalInit(void)
{
	HAL_Delay(500);
    TM1650_SetDisplay(1, 7, 1);
    TM1650_Clear();
}
