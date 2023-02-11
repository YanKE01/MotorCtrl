/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2023-02-10 18:57:38
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-02-10 18:58:31
 * @FilePath: \F401RE_RTOS\Ctrl\pid.c
 */
#include "pid.h"
#include "variable.h"

#define _constrain(amt, low, high) ((amt) < (low) ? (low) : ((amt) > (high) ? (high) : (amt)))

void VelocityPidOperation(float target, float current)
{
    speedPidParameter.error = (target - current);

    speedPidParameter.proportional = speedPidParameter.kp * speedPidParameter.error;
    speedPidParameter.integral = speedPidParameter.integral_prev + speedPidParameter.ki * speedPidParameter.error * speedPidParameter.t; // 控制周期0.001s

    speedPidParameter.output = speedPidParameter.proportional + speedPidParameter.integral;

    // 限幅
    speedPidParameter.output = _constrain(speedPidParameter.output, -speedPidParameter.constrain, speedPidParameter.constrain);

    // 存储上一次
    speedPidParameter.integral_prev = speedPidParameter.integral;
}
