/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2023-05-16 08:58:15
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-05-16 12:50:53
 * @FilePath: \LCM_FOC\Sources\User_Soruces\HY_Variable.c
 */
#include "HY_Variable.h"
#include "UserParaSetDefine.h"

Motor motor;
UI ui;
/**
 * @description: 系统变量初始化
 * @return {*}
 */
void HY_VariableInit(void)
{
    /*电机相关设置*/
    motor.state = 0;                               // 默认为停止状态 0:停车 1:启动
    motor.maxSpeed = (uint16_t)(UPDS_RATED_SPEED); // 最大转速
    motor.minSpeed = 700;                          // 最低转速
    motor.targetSpeed = 3600;                      // 默认启动转速
    motor.speedChangeStep = 100;                   // 速度默认按照100为步距调节
    motor.targetSpeedTemp = motor.targetSpeed;     // 设置临时转速
    motor.currentVbus = 0;                         // 初始值为0
    motor.fault = 0;                               // 无故障状态

    /*UI*/
    ui.modePage = 0;   // 速度,电流,故障灯页面
    ui.isSetSpeed = 0; // 按下增减速成立
}