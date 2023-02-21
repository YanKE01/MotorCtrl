/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2022-11-09 19:07:31
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-02-21 19:55:57
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

enum ErrorCode
{
    OverCurrentError = 0,
    OverVoltageError,
    UnderVoltageError,
    StartUpError,
    OtherError,
};

/**
 * @brief 电机固化参数,存储至EEPROM
 *
 */
typedef struct _MotorParameter
{
    uint8_t maxStartUp;       // 最大启动次数
    uint16_t maxSpeed;        // 最大限幅
    uint16_t minSpeed;        // 最小限幅
    uint16_t speedDuration;   // 速度调节保持时间 1000->2000, 使用speedDuration时间完成
    uint16_t speedChangeStep; // 速度调整步距

} MotorParameter;

typedef struct _Motor
{

    uint8_t isMotorStart;           // 电机启动标志位 自定义层面,用于设置启动
    uint8_t isMotorRun;             // 电机是否处于运行状态 用于后面运行过程中的意外错误
    uint8_t motorState;             // 电机当前状态
    int8_t maxStartup;              // 最大启动次数
    uint8_t motorRunAfterFault;     // 电机运转后出现错误
    uint16_t motorVoltage;          // 当前电机电压
    uint16_t motorCurrentFaultCode; // 电机当前错误代码
    int targetSpeed;                // 期望速度
    int targetSpeedTemp;            // 临时期望速度,用于暂时设定转速
    float current;                  // 当前电机电流

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
    uint8_t modePage;   // 当前模式设置页
    uint8_t isSetSpeed; // 当前是否处于设置速度状态
} UI;

extern Motor motor;
extern SystemState systemState;
extern UI ui;

void VariableInit(void);
#endif
