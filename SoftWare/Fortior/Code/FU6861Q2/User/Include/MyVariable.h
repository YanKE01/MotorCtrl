/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2023-04-01 20:30:33
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-04-04 20:50:45
 * @FilePath: \FU6861Q2\User\Include\MyVariable.h
 */
#ifndef _MY_VARIABLE_H
#define _MY_VARIABLE_H

#include <FU68xx_2.h>
#include <Myproject.h>

typedef struct _Motor
{
    /* data */
    uint8 state;            // 电机运行状态 0:停止 1:启动
    uint16 minSpeed;        // 最低转速
    uint16 maxSpeed;        // 最高转速
    uint16 targetSpeed;     // 目标转速,需要限制在最低与最高转速
    uint16 targetSpeedTemp; // 临时转速
    uint16 speedChangeStep; // 速度调节步距
    uint16 currentVbus;     // 当前总线电压
} Motor;

typedef struct _UI
{
    uint8 modePage;   // 当前模式设置页
    uint8 isSetSpeed; // 当前是否处于设置速度状态
} UI;

enum ModePage
{
    SpeedPage = 0,
    VbusPage,
    CurrentPage,
};

extern Motor motor;
extern UI ui;

void MyVariableInit(void);

#endif