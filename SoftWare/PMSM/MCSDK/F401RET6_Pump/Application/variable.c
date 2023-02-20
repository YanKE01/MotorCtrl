/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2022-11-09 19:10:45
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-02-20 11:27:16
 * @FilePath: \F401RET6_Pump\Application\variable.c
 */
#include "variable.h"
#include "string.h"

Motor motor;
SystemState systemState;
UI ui;

/**
 * @brief 关键变量初始化
 *
 */
void VariableInit()
{
    motor.targetSpeed = 1000; // 默认启动速度
    systemState.keyStatePrev = 0;
    motor.isMotorStart = 0;
    ui.modePage = 0;
}
