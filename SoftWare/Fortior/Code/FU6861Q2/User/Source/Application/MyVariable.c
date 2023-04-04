/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2023-04-01 20:30:06
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-04-04 20:16:43
 * @FilePath: \FU6861Q2\User\Source\Application\MyVariable.c
 */
#include "MyVariable.h"

Motor motor;
UI ui;

/**
 * @description: 变量初始化
 * @return {*}
 */
void MyVariableInit(void)
{

    /*电机相关设置*/
    motor.state = 0;                           // 默认为停止状态
    motor.maxSpeed = 3900;                     // 最大转速
    motor.minSpeed = 600;                      // 最低转速
    motor.targetSpeed = 1000;                  // 默认启动转速
    motor.speedChangeStep = 100;               // 速度默认按照100为步距调节
    motor.targetSpeedTemp = motor.targetSpeed; // 设置临时转速
    motor.currentVbus = 0;                     // 初始值为0

    /*UI*/
    ui.modePage = 0;   // 速度,电流,故障灯页面
    ui.isSetSpeed = 0; // 按下增减速成立
}