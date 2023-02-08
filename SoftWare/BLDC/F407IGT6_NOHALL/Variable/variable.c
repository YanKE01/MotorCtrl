/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2023-02-07 11:18:28
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-02-08 10:53:25
 * @FilePath: \F407IGT6_NOHALL\Variable\variable.c
 */
#include "variable.h"

MotorParameter motorParameter;

void VariableInit(void)
{
    motorParameter.dir = CCW; // 默认顺时针
    motorParameter.hallState = 0;
    motorParameter.pwmDuty = 0;
    motorParameter.isStart = 0;
    motorParameter.maxDuty = 8000;
    motorParameter.isStart = STOP;
}
