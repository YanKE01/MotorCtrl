/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2023-02-03 21:19:04
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-02-10 17:04:22
 * @FilePath: \F401RE_RTOS\Hal\btn.c
 */
#include "btn.h"
#include "stdint.h"
#include "main.h"
#include "stdio.h"
#include "hal.h"
#include "multi_button.h"
#include "variable.h"

static struct button btnSwitch;

/**
 * @brief 读取PA4状态
 *
 * @return uint8_t
 */
static uint8_t ReadPA4()
{
    return (uint8_t)HAL_GPIO_ReadPin(START_STOP_GPIO_Port, START_STOP_Pin);
}

/**
 * @brief PA4回调函数
 *
 * @param btn
 */
void BtnPA4_Cb(void *btn)
{

    uint32_t btn_event_val = get_button_event((struct button *)btn);

    switch (btn_event_val)
    {
    case PRESS_DOWN:
        /* code */
        focParameter.isStart = !focParameter.isStart; // 切换状态
        if (focParameter.isStart)
        {
            printf("Motor state: start\n");
            HAL_GPIO_WritePin(STATE_LED_GPIO_Port, STATE_LED_Pin, GPIO_PIN_SET);
            PwmStart();
        }
        else
        {
            printf("Motor state: stop\n");
            HAL_GPIO_WritePin(STATE_LED_GPIO_Port, STATE_LED_Pin, GPIO_PIN_RESET);

            PwmStop();
        }
        break;

    default:
        break;
    }
}

/**
 * @brief 按键初始化
 *
 */
void BtnInit()
{
    button_init(&btnSwitch, ReadPA4, 0);
    button_attach(&btnSwitch, PRESS_DOWN, BtnPA4_Cb);
    button_start(&btnSwitch);
}
