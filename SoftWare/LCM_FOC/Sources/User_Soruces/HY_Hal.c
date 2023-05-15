/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2023-05-15 21:07:55
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-05-16 20:06:38
 * @FilePath: \LCM_FOC\Sources\User_Soruces\HY_Hal.c
 */
#include "HY_Hal.h"
#include "HY_Display.h"
#include "lcm32f037_conf.h"
#include "lcm32f037_rcc.h"
#include "lcm32f037_gpio.h"
#include "lcm32f037_tim.h"

/**
 * @description: PA0_IIC_SDA PA1_IIC_SCL PB0_INT
 * @return {*}
 */
static void HY_GpioInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
    GPIO_Init(GPIOA, &GPIO_InitStructure); // 初始化
}

/**
 * @description: IO输出测试
 * @param {uint8_t} status
 * @return {*}
 */
void HY_GpioTest(uint8_t status)
{
    if (status == 0)
    {
        GPIO_ResetBits(GPIOA, GPIO_Pin_0);
        GPIO_ResetBits(GPIOA, GPIO_Pin_1);
    }
    else
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_0);
        GPIO_SetBits(GPIOA, GPIO_Pin_1);
    }
}

/**
 * @description: 所有驱动初始化入口
 * @return {*}
 */
void HY_HalInit(void)
{
    HY_GpioInit();

    HY_TM1650_SetDisplay(1, 7, 1);
    //HY_TM1650_Clear();
}
