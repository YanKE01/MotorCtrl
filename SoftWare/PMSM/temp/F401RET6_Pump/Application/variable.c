/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2022-11-09 19:10:45
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-02-21 19:30:14
 * @FilePath: \F401RET6_Pump\Application\variable.c
 */
#include "variable.h"
#include "string.h"

Motor motor;
SystemState systemState;
UI ui;
extern SystemInfo systemInfo;

/**
 * @brief 关键变量初始化
 *
 */
void VariableInit()
{
    motor.targetSpeed = 1000;                                // 默认启动速度
    motor.targetSpeedTemp = motor.targetSpeed;               // 设置临时速度
    motor.isMotorRun = 0;                                    // 电机尚未启动过
    motor.isMotorStart = 0;                                  // 上电默认用户没有按下启动按键
    motor.maxStartup = systemInfo.motorParameter.maxStartUp; // 最大容忍启动失败次数
    motor.motorRunAfterFault = 0;
    motor.motorCurrentFaultCode = 0;
    systemState.keyStatePrev = 0;
    ui.modePage = 0;
    ui.isSetSpeed = 0;
}
