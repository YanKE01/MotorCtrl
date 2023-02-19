/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2022-11-09 19:07:31
 * @LastEditors: yanke 1435020085@qq.com
 * @LastEditTime: 2022-11-21 17:36:31
 * @FilePath: \F401RET6\MyDriver\include\variable.h
 */
#ifndef _VARIABLE_H
#define _VARIABLE_H

#include "stdint.h"

typedef struct _Motor
{
    int16_t targetSpeed[4];
    int16_t lastTargetSpeed;
    uint8_t targetSpeedIndex;
    uint8_t state; // 电机状态 0停止 1启动
} Motor;

typedef struct _SystemInfo
{
    uint8_t isConfig;         // 是否配置
    char developer[32];       // 开发者
    uint8_t majorVersion;     // 主版本
    uint8_t minorVersion;     // 次版本
    uint8_t pathVersion;      // 补丁版本
    char lastCompileTime[50]; // 上次的编译时间

} SystemInfo;

extern Motor motor;

void VariableInit(void);
#endif
