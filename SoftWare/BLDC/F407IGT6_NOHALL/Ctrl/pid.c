/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2023-02-08 13:24:00
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-02-08 14:52:42
 * @FilePath: \F407IGT6_NOHALL\Ctrl\pid.c
 */
#include "pid.h"
#include "variable.h"
#include "hall.h"

PID_TypeDef speedPid; /* 速度PID参数结构体 */
/**
 * @brief       初始化PID结构体成员
 * @param       无
 * @retval      无
 */
void PidInit(void)
{
    speedPid.SetPoint = 500;
    speedPid.ActualValue = 0; // pid运算值
    speedPid.Ui = 0.0;
    speedPid.Up = 0.0;
    speedPid.Error = 0.0;     // 误差
    speedPid.Proportion = KP; // 比例项输出
    speedPid.Integral = KI;   // 积分项输出
    speedPid.IngMax = 9000;
    speedPid.IngMin = -9000;
    speedPid.OutMax = 8000; // 输出限制
    speedPid.OutMin = -8000;
}

/**
 * @brief PID运算
 *
 * @param PID
 * @param Feedback_value
 * @return int32_t
 */
int32_t PidOperation(PID_TypeDef *PID, float currentVale)
{
    if (motorParameter.dir == CW && currentVale < 0)
    {
        currentVale = -currentVale;
    }

    PID->Error = (float)(PID->SetPoint - currentVale); /* 偏差值 */
    PID->Up = PID->Proportion * PID->Error;
    PID->Ui += (PID->Error * PID->Integral);
    LIMIT_OUT(PID->Ui, PID->IngMax, PID->IngMin);
    PID->ActualValue = PID->Up + PID->Ui + PID->Ud;
    LIMIT_OUT(PID->ActualValue, PID->OutMax, PID->OutMin);
    return ((int32_t)(PID->ActualValue)); /* 返回实际控制数值 */
}
