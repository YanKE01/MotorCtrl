/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2023-02-07 11:18:28
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-02-07 14:18:52
 * @FilePath: \F407IGT6_HALL\Variable\include\variable.h
 */
#ifndef _VARIABLE_H
#define _VARIABLE_H

#include "stdint.h"

enum Dir
{
    CW = 0, // 顺时针
    CCW,    // 逆时针
};

typedef struct
{
    /* data */
    uint32_t hallState; // 霍尔传感器状态
    uint32_t pwmDuty;   // 占空比
    uint8_t dir;        // 方向
    uint8_t isStart;    // 是否启动
} MotorParameter;

extern MotorParameter motorParameter;

void VariableInit(void);

#endif
