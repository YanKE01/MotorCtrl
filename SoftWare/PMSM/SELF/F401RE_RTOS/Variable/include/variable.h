/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2023-02-09 17:29:59
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-02-10 18:55:40
 * @FilePath: \F401RE_RTOS\Variable\include\variable.h
 */
#ifndef _VARIABLE_H
#define _VARIABLE_H

#include "stdint.h"

typedef struct
{
    /* data */
    uint8_t sector;   // 扇区
    uint8_t polePair; // 极对数
    uint8_t isStart;  // 是否启动
    float udc;        // 母线电压
    float tpwm;       // pwm周期 arr*2
    float tcmp1;      // CCR1
    float tcmp2;      // CCR2
    float tcmp3;      // CCR3
    float angleMc;    // 机械角度
    float angleEl;    // 电角度
    float ualpha;
    float ubeta;
    float angleMcPrev; // 前一时刻机械角度
    float velocity;    // 速度
    float velocityLpf; // 速度-低通滤波

} FocParameter;

typedef struct
{
    float error;
    float kp;
    float ki;
    float proportional;
    float integral;
    float output;
    float integral_prev;
    float constrain;
    float t; // 控制周期
    float target;
} PidParameter;

extern FocParameter focParameter;
extern PidParameter speedPidParameter;

void VariableInit(void);

#endif
