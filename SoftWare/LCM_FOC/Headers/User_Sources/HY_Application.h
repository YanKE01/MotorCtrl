/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2023-05-15 22:57:55
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-05-16 11:24:27
 * @FilePath: \LCM_FOC\Headers\User_Sources\HY_Application.h
 */
#ifndef _HY_APPLICATION_H
#define _HY_APPLICATION_H

#include "lcm32f037_type.h"
#include "lcm32f037.h"


s32 HY_SetPumpMechanicalSpeed(uint16_t target);
void HY_TaskLoop(void);

#endif
