/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2023-02-09 17:22:22
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-02-10 18:51:49
 * @FilePath: \F401RE_RTOS\Ctrl\include\foc.h
 */
#ifndef _FOC_H
#define _FOC_H

#include "stdint.h"

#define _SQRT3_2 0.8660254f
#define _SQRT3 1.7320508f
#define _2PI 6.28318530718f
#define _PI_2 1.57079632679f
#define _PI_3 1.0471975512f

void AngleElProcess(float *angleEl, float angleMc, uint8_t polePair);
void AntiParkOperation(float *ualpha, float *ubeta, float ud, float uq, float theta);
uint8_t JudgeSector(float ualpha, float ubeta);
void SvpwmOperation(float *tcmp1, float *tcmp2, float *tcmp3, float ualpha, float ubeta, int sector, float udc, uint16_t tpwm);
float Lpf(float x);
#endif
