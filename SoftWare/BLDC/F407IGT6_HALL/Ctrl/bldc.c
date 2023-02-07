/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2023-02-07 12:24:27
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-02-07 14:00:41
 * @FilePath: \F407IGT6_HALL\Ctrl\bldc.c
 */
#include "bldc.h"
#include "main.h"
#include "gpio.h"
#include "tim.h"
#include "variable.h"
#include "hall.h"
#include "stdio.h"

void StopMotor(void)
{
    HAL_GPIO_WritePin(SHUTDOWN_GPIO_Port, SHUTDOWN_Pin, GPIO_PIN_RESET); // 关闭半桥驱动
    // 关闭PWM输出
    HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
    HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
    HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_3);

    // 清空CCR
    TIM1->CCR1 = 0;
    TIM1->CCR2 = 0;
    TIM1->CCR3 = 0;
    // 关闭下桥臂
    HAL_GPIO_WritePin(U_LOW_GPIO_Port, U_LOW_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(V_LOW_GPIO_Port, V_LOW_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(W_LOW_GPIO_Port, W_LOW_Pin, GPIO_PIN_RESET);
    motorParameter.isStart = 0;
}

/**
 * @brief 启动电机
 *
 */
void StartMotor(void)
{
    HAL_GPIO_WritePin(SHUTDOWN_GPIO_Port, SHUTDOWN_Pin, GPIO_PIN_SET); // 打开半桥驱动
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
    motorParameter.isStart = 1;
}

/**
 * @brief U相上桥臂与V项下桥臂导通
 *
 */
void UphaseH_VphaseL(void)
{
    TIM1->CCR1 = motorParameter.pwmDuty;
    TIM1->CCR2 = 0;
    TIM1->CCR3 = 0;

    HAL_GPIO_WritePin(U_LOW_GPIO_Port, U_LOW_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(V_LOW_GPIO_Port, V_LOW_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(W_LOW_GPIO_Port, W_LOW_Pin, GPIO_PIN_RESET);
}

/**
 * @brief U相上桥臂与W相下桥臂
 *
 */
void UphaseH_WphaseL(void)
{
    TIM1->CCR1 = motorParameter.pwmDuty;
    TIM1->CCR2 = 0;
    TIM1->CCR3 = 0;

    HAL_GPIO_WritePin(U_LOW_GPIO_Port, U_LOW_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(V_LOW_GPIO_Port, V_LOW_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(W_LOW_GPIO_Port, W_LOW_Pin, GPIO_PIN_SET);
}

/**
 * @brief V相上桥臂与W相下桥臂
 *
 */
void VphaseH_WphaseL(void)
{
    TIM1->CCR1 = 0;
    TIM1->CCR2 = motorParameter.pwmDuty;
    TIM1->CCR3 = 0;

    HAL_GPIO_WritePin(U_LOW_GPIO_Port, U_LOW_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(V_LOW_GPIO_Port, V_LOW_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(W_LOW_GPIO_Port, W_LOW_Pin, GPIO_PIN_SET);
}

/**
 * @brief V相上桥臂与U相下桥臂
 *
 */
void VphaseH_UphaseL(void)
{
    TIM1->CCR1 = 0;
    TIM1->CCR2 = motorParameter.pwmDuty;
    TIM1->CCR3 = 0;

    HAL_GPIO_WritePin(U_LOW_GPIO_Port, U_LOW_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(V_LOW_GPIO_Port, V_LOW_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(W_LOW_GPIO_Port, W_LOW_Pin, GPIO_PIN_RESET);
}

/**
 * @brief W相上桥臂U相下桥臂
 *
 */
void WphaseH_UphaseL(void)
{
    TIM1->CCR1 = 0;
    TIM1->CCR2 = 0;
    TIM1->CCR3 = motorParameter.pwmDuty;

    HAL_GPIO_WritePin(U_LOW_GPIO_Port, U_LOW_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(V_LOW_GPIO_Port, V_LOW_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(W_LOW_GPIO_Port, W_LOW_Pin, GPIO_PIN_RESET);
}

/**
 * @brief W相上桥臂与V相下桥臂
 *
 */
void WphaseH_VpahseL(void)
{
    TIM1->CCR1 = 0;
    TIM1->CCR2 = 0;
    TIM1->CCR3 = motorParameter.pwmDuty;

    HAL_GPIO_WritePin(U_LOW_GPIO_Port, U_LOW_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(V_LOW_GPIO_Port, V_LOW_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(W_LOW_GPIO_Port, W_LOW_Pin, GPIO_PIN_RESET);
}


void (*switchArray[6])(void) = {&UphaseH_WphaseL, &VphaseH_UphaseL, &VphaseH_WphaseL, &WphaseH_VpahseL, &UphaseH_VphaseL, &WphaseH_UphaseL};
