/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2022-11-09 19:07:31
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-02-20 14:52:51
 * @FilePath: \F401RET6_Pump\Application\include\variable.h
 */
#ifndef _VARIABLE_H
#define _VARIABLE_H

#include "stdint.h"

enum ModePage
{
    SpeedPage = 0,
    CurrentPage,
    VbusPage,
};

/**
 * @brief 电机固化参数,存储至EEPROM
 *
 */
typedef struct _MotorParameter
{
    uint16_t maxSpeed;        // 最大限幅
    uint16_t minSpeed;        // 最小限幅
    uint16_t speedDuration;   // 速度调节保持时间 1000->2000, 使用speedDuration时间完成
    uint16_t speedChangeStep; // 速度调整步距

} MotorParameter;

typedef struct _Motor
{
    int targetSpeed; // 期望速度

    uint8_t isMotorStart;  // 电机启动标志位
    uint8_t motorState;    // 电机当前状态
    uint16_t motorVoltage; // 当前电机电压
    float current;         // 电流
} Motor;

typedef struct _SystemInfo
{
    uint8_t isConfig;              // 是否配置
    char developer[32];            // 开发者
    uint8_t majorVersion;          // 主版本
    uint8_t minorVersion;          // 次版本
    uint8_t pathVersion;           // 补丁版本
    char lastCompileTime[50];      // 上次的编译时间
    MotorParameter motorParameter; // 电机固化参数
} SystemInfo;

typedef struct _SystemState
{
    uint8_t keyState;     // 按键状态
    uint8_t keyStatePrev; // 按键前一时刻状态
} SystemState;

typedef struct _UI
{
    uint8_t modePage; // 当前模式设置页
} UI;

extern Motor motor;
extern SystemState systemState;
extern UI ui;

void VariableInit(void);
#endif
