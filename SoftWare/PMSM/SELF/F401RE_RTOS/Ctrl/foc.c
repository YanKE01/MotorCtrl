/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2023-02-09 17:22:14
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-02-09 20:01:54
 * @FilePath: \F401RE_RTOS\Ctrl\foc.c
 */
#include "foc.h"
#include "arm_math.h"
#include "stdio.h"
#include "stdio.h"
#include "tim.h"
#include "variable.h"

/**
 * @brief 机械角度归一化电角度
 *
 * @param angleEl
 * @param angleMc
 * @param polePair
 */
void AngleElProcess(float *angleEl, float angleMc, uint8_t polePair)
{

    *angleEl = angleMc * polePair; // 转换为电角度
    *angleEl = fmod(*angleEl, _2PI);

    if (*angleEl < 0)
    {
        *angleEl += _2PI;
    }
}

/**
 * @brief 反park变换
 *
 * @param ualpha
 * @param ubeta
 * @param ud
 * @param uq
 * @param theta
 */
void AntiParkOperation(float *ualpha, float *ubeta, float ud, float uq, float theta)
{
    *ualpha = ud * arm_cos_f32(theta) - uq * arm_sin_f32(theta);
    *ubeta = ud * arm_sin_f32(theta) + uq * arm_cos_f32(theta);
}

/**
 * @brief 扇区判断
 *
 * @param ualpha
 * @param ubeta
 * @return uint8_t
 */
uint8_t JudgeSector(float ualpha, float ubeta)
{
    uint8_t sector = 0;

    float uref1 = ubeta;
    float uref2 = (_SQRT3_2)*ualpha - (0.5f) * ubeta;
    float uref3 = (-_SQRT3_2) * ualpha - (0.5f) * ubeta;

    if (uref1 > 0.0f)
    {
        sector += 1;
    }

    if (uref2 > 0.0f)
    {
        sector += 2;
    }

    if (uref3 > 0.0f)
    {
        sector += 4;
    }

    return sector;
}

/**
 * @brief SVPWM
 *
 * @param tcmp1
 * @param tcmp2
 * @param tcmp3
 * @param ualpha
 * @param ubeta
 * @param sector
 * @param udc
 * @param tpwm
 */
void SvpwmOperation(float *tcmp1, float *tcmp2, float *tcmp3, float ualpha, float ubeta, int sector, float udc, uint16_t tpwm)
{
    float x = _SQRT3 * ubeta * tpwm / udc;
    float y = tpwm / udc * (1.5f * ualpha + _SQRT3_2 * ubeta);
    float z = tpwm / udc * (-1.5f * ualpha + _SQRT3_2 * ubeta);
    float t1 = 0, t2 = 0;
    float ta = 0, tb = 0, tc = 0;

    switch (sector)
    {
    case 1:
        t1 = z;
        t2 = y;
        break;
    case 2:
        t1 = y;
        t2 = -x;
        break;
    case 3:
        t1 = -z;
        t2 = x;
        break;
    case 4:
        t1 = -x;
        t2 = z;
        break;
    case 5:
        t1 = x;
        t2 = -y;
        break;
    case 6:
        t1 = -y;
        t2 = -z;
        break;

    default:
        break;
    }

    // 避免浮点运算越界
    if (t1 + t2 > tpwm)
    {
        float temp = t1 + t2;
        t1 = t1 / temp;
        t2 = t2 / temp;
    }

    // 计算CCR 7段式SVPWM
    ta = (tpwm - (t1 + t2)) / 4.0f;
    tb = ta + t1 / 2.0f;
    tc = tb + t2 / 2.0f;

    switch (sector)
    {
    case 1:
        *tcmp1 = tb;
        *tcmp2 = ta;
        *tcmp3 = tc;
        break;
    case 2:
        *tcmp1 = ta;
        *tcmp2 = tc;
        *tcmp3 = tb;
        break;
    case 3:
        *tcmp1 = ta;
        *tcmp2 = tb;
        *tcmp3 = tc;
        break;
    case 4:
        *tcmp1 = tc;
        *tcmp2 = tb;
        *tcmp3 = ta;
        break;
    case 5:
        *tcmp1 = tc;
        *tcmp2 = ta;
        *tcmp3 = tb;
        break;

    case 6:
        *tcmp1 = tb;
        *tcmp2 = tc;
        *tcmp3 = ta;
        break;
    default:
        break;
    }

    focParameter.tcmp1 = *tcmp1;
    focParameter.tcmp2 = *tcmp2;
    focParameter.tcmp3 = *tcmp3;

    TIM1->CCR1 = (uint32_t)focParameter.tcmp1;
    TIM1->CCR2 = (uint32_t)focParameter.tcmp2;
    TIM1->CCR3 = (uint32_t)focParameter.tcmp3;
}

/**
 * @brief 低通滤波
 *
 * @param x
 * @return float
 */
float Lpf(float x)
{

    static float y_vel_prev = 0;
    float y = 0.9f * y_vel_prev + 0.1f * x;

    y_vel_prev = y;

    return y;
}

