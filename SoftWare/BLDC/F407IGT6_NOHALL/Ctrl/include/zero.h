/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2023-02-07 15:48:02
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-02-07 21:34:48
 * @FilePath: \F407IGT6_NOHALL\Ctrl\include\zero.h
 */
#ifndef _ZERO_H
#define _ZERO_H

#include "stdint.h"

typedef struct
{
    /* data */
    int runStep;
    int delayCount;         // 延迟计数
    int nextPhaseTime;      // 切换到下一项的时间
    int nextPhaseCount;     // 换向计数
    int voltageChangeCount; // 改变电压计数
} SimpleOpen;

typedef struct
{
    /* data */
    uint8_t hallLessState[3];     // 三相反电动式状态
    uint16_t queueState[3];       // 三相滤波
    uint16_t queueFilterState[3]; // 三相滤波后的状态
    uint16_t filterEdge;          // 滤波后边沿检测
    int speedRpm;             // 电机转速
    uint16_t filterFailedCount;   // 不稳定计数
    uint16_t filterDelay;         // 延迟换向的时间
    uint8_t hallLessValue;        // 三相反电势状态组合值
    uint8_t hallLessValuePrev;    // 三相反电势状态组合值,前一时刻
} HallLessParameter;

void SimpleOpenLoopSixStepLoop(void);
void SimpleOpenChangeVoltage(void);
void SimpleOpenSixStepOperation(void);
#endif
