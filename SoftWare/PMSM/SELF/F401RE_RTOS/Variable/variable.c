/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2023-02-09 17:29:44
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-02-10 18:57:14
 * @FilePath: \F401RE_RTOS\Variable\variable.c
 */
#include "variable.h"

FocParameter focParameter;
PidParameter speedPidParameter;

/**
 * @brief 关键变量初始化
 *
 */
void VariableInit(void)
{
    /*电机参数*/
    focParameter.polePair = 14;
    focParameter.udc = 48.0f;
    focParameter.tpwm = 8400; // arr*2;

    /*速度环*/
    speedPidParameter.target = 10.0f;
    speedPidParameter.kp = 0.1f;
    speedPidParameter.ki = 1.0f;
    speedPidParameter.constrain = 15.0f; // 限制输出到正负6
    speedPidParameter.t = 0.001f;       // 控制周期
    speedPidParameter.integral_prev = 0;

    /*其他参数初始化*/
    focParameter.angleEl = 0;
    focParameter.isStart = 0;
    focParameter.angleMcPrev = 0;
    focParameter.velocity = 0;
}
