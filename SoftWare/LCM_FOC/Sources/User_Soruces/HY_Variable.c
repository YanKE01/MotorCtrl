/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2023-05-16 08:58:15
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-09-08 15:02:43
 * @FilePath: \LCM_FOC\Sources\User_Soruces\HY_Variable.c
 */
#include "HY_Variable.h"
#include "UserParaSetDefine.h"

Motor motor;
UI ui;
Strategy strategy;
Pd pd;

/**
 * @description: 系统变量初始化
 * @return {*}
 */
void HY_VariableInit(void)
{
    /*电机相关设置*/
    motor.state = 0;                           // 默认为停止状态 0:停车 1:启动
    motor.maxSpeed = 3600;                     // 最大转速
    motor.minSpeed = 700;                      // 最低转速
    motor.targetSpeed = motor.minSpeed;        // 默认启动转速
    motor.speedChangeStep = 100;               // 速度默认按照100为步距调节
    motor.targetSpeedTemp = motor.targetSpeed; // 设置临时转速
    motor.currentVbus = 0;                     // 初始值为0
    motor.fault = 0;                           // 无故障状态
    motor.targetSpeedPrev = motor.targetSpeed; // 前一个转速
    motor.minVbus = 34.0f;                     // 最低母线电压为34v
    motor.mode = 1;                            // 默认电源模式

    strategy.changeCount = 0;
    strategy.lowVbusChangeCount = 0;
    pd.error = 0;
    pd.error_last = 0;
    pd.kd = 500.0f;  // 450
    pd.kp = 800.0f; // 1300

    /*UI*/
    ui.modePage = 0;   // 速度,电流,故障灯页面
    ui.isSetSpeed = 0; // 按下增减速成立
    ui.keyValue = 0;
    ui.keyValue_Prev = 0;
}