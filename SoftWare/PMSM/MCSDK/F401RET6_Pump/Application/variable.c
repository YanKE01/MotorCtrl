/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2022-11-09 19:10:45
 * @LastEditors: yanke 1435020085@qq.com
 * @LastEditTime: 2022-11-10 11:27:42
 * @FilePath: \F401RET6\MyDriver\variable.c
 */
#include "variable.h"
#include "string.h"
Motor motor;

/**
 * @brief 关键变量初始化
 *
 */
void VariableInit()
{
    motor.state = 0;              // 电机状态为停止状态
    motor.targetSpeedIndex = 0;   // 初始索引为0
    motor.lastTargetSpeed = 1500; // 上次设置的电机值
    motor.targetSpeed[0] = 2000;
    motor.targetSpeed[1] = 1500;
    motor.targetSpeed[2] = 1000;
	motor.targetSpeed[3] = 600;
}

