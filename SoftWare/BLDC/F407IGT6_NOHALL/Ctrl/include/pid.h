/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2023-02-08 13:25:26
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-02-08 14:43:32
 * @FilePath: \F407IGT6_NOHALL\Ctrl\include\pid.h
 */
#ifndef _PID_H
#define _PID_H

#include "stdint.h"

/*定义PID参数相关宏*/
#define KP 0.05000f /* P参数*/
#define KI 0.00025f /* I参数*/

/*定义位置PID参数相关宏*/
/*PID结构体*/
typedef struct
{
    float SetPoint;    /* 设定目标 */
    float ActualValue; /* 实际值 */
    float Ui;          /* 比例项 */
    float Up;          /* 积分项 */
    float Ud;          /* 微分项 */
    float Proportion;  /* 比例常数 P */
    float Integral;    /* 积分常数 I */
    float Error;       /* Error[-1] */
    float IngMin;
    float IngMax;
    float OutMin;
    float OutMax;
} PID_TypeDef;

#define LIMIT_OUT(var, max, min)               \
    {                                          \
        (var) = (var) > (max) ? (max) : (var); \
        (var) = (var) < (min) ? (min) : (var); \
    }
extern PID_TypeDef speedPid; /* 速度置PID参数结构体 */
/******************************************************************************************/
/* 外部接口函数*/
void PidInit(void);
int32_t PidOperation(PID_TypeDef *PID, float Feedback_value);

#endif
