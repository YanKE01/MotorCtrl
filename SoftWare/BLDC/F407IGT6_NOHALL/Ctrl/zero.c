/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2023-02-07 15:47:53
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-02-08 13:14:25
 * @FilePath: \F407IGT6_NOHALL\Ctrl\zero.c
 */
#include "zero.h"
#include "variable.h"
#include "bldc.h"
#include "main.h"

SimpleOpen simpleOpen = {0, 0, 0, 0, 0};
HallLessParameter hallLessParameter = {0, 0, 0, 0, 0, 0, 0, 0, 0};
int speedCount = 0;     // 用于统计高电平次数,计算速度
int zeroStableFlag = 0; // 过零点稳定标志位

uint8_t HallLessOperation(void);

/**
 * @brief 低通滤波器
 *
 * @param valueLpf
 * @param value
 */
void Lpf(int *valueLpf, int value)
{
    static int valuePrev = 0;

    *valueLpf = (int)(0.9 * valuePrev + 0.1 * value);

    valuePrev = *valueLpf;
}

/**
 * @brief 简单六步换相,没有涉及到过零检测，只是简单的把电机固定在一项后拖动起来
 *
 */
void SimpleOpenLoopSixStepLoop()
{
    if (motorParameter.isStart == START)
    {
        switch (simpleOpen.runStep)
        {
        case 0:
            motorParameter.pwmDuty = motorParameter.maxDuty / 8;
            UphaseH_VphaseL(); // 先固定到这一项
            simpleOpen.delayCount = 0;
            simpleOpen.nextPhaseTime = 1200; // 假设值(需要调试),相与相之间切换的时间
            simpleOpen.runStep = 1;
            simpleOpen.voltageChangeCount = 0; // 用于开环调节电压
            zeroStableFlag = 0;                // 清除过零标志位
            break;

        case 1:
            // 此环节为延迟计数，以达到换向时间的要求
            simpleOpen.delayCount++;
            if (simpleOpen.delayCount >= simpleOpen.nextPhaseTime)
            {
                // 达到换向时间
                simpleOpen.delayCount = 0;
                simpleOpen.runStep = 2;
            }

            if (HallLessOperation() == 1)
            {
                simpleOpen.runStep = 3; // 直接进入过零控制
            }
            break;

        case 2:
            // 若达到换向时间，则按照顺序换相即可，同时缩短换相时间
            simpleOpen.nextPhaseTime -= simpleOpen.nextPhaseTime / 15 + 1;
            simpleOpen.voltageChangeCount++;
            SimpleOpenChangeVoltage(); // 尝试增大占空比

            if (simpleOpen.nextPhaseTime < 180)
            {
                simpleOpen.nextPhaseTime = 180;
            }

            simpleOpen.runStep = 1;

            simpleOpen.nextPhaseCount++; // 标记即将进入下一项 六步换相的顺序

            if (simpleOpen.nextPhaseCount == 6)
            {
                simpleOpen.nextPhaseCount = 0; // 新的一轮六步换相
            }
            SimpleOpenSixStepOperation();
            break;

        case 3:
            HallLessOperation();
            break;

        default:
            break;
        }
    }
    else
    {
        // 清空无感标志位
        simpleOpen.runStep = 0;
        simpleOpen.delayCount = 0;
        simpleOpen.nextPhaseCount = 0;
        simpleOpen.voltageChangeCount = 0;
    }
}

/**
 * @brief 调节电压
 *
 */
void SimpleOpenChangeVoltage()
{
    switch (simpleOpen.voltageChangeCount)
    {
    case 1:
        motorParameter.pwmDuty = motorParameter.maxDuty / 2 / 10;
        break;
    case 2:
        motorParameter.pwmDuty = motorParameter.maxDuty / 2 / 9;
        break;
    case 3:
        motorParameter.pwmDuty = motorParameter.maxDuty / 2 / 8;
        break;
    case 4:
        motorParameter.pwmDuty = motorParameter.maxDuty / 2 / 7;
        break;
    case 5:
        motorParameter.pwmDuty = motorParameter.maxDuty / 2 / 7;
        break;
    case 6:
        motorParameter.pwmDuty = motorParameter.maxDuty / 2 / 6;
        break;
    case 7:
        motorParameter.pwmDuty = motorParameter.maxDuty / 2 / 6;
        break;
    case 8:
        motorParameter.pwmDuty = motorParameter.maxDuty / 2 / 5;
        break;
    case 9:
        motorParameter.pwmDuty = motorParameter.maxDuty / 2 / 5;
        break;
    case 10:
        motorParameter.pwmDuty = motorParameter.maxDuty / 2 / 4;
        break;
    case 11:
        motorParameter.pwmDuty = motorParameter.maxDuty / 2 / 4;
        break;
    case 12:
        motorParameter.pwmDuty = motorParameter.maxDuty / 2 / 4;
        break;
    case 13:
        motorParameter.pwmDuty = motorParameter.maxDuty / 2 / 4;
        break;
    case 14:
        motorParameter.pwmDuty = motorParameter.maxDuty / 2 / 4;
        break;
    case 15:
        motorParameter.pwmDuty = motorParameter.maxDuty / 2 / 4;
        break;
    default:
        break;
    }
}

/**
 * @brief 六步换相的实现 参考正点DMF407电机开发 P477
 *
 */
void SimpleOpenSixStepOperation()
{

    if (motorParameter.dir == CCW)
    {
        switch (simpleOpen.nextPhaseCount)
        {
        case 0:
            UphaseH_VphaseL();
            break;
        case 1:
            UphaseH_WphaseL();
            break;
        case 2:
            VphaseH_WphaseL();
            break;
        case 3:
            VphaseH_UphaseL();
            break;
        case 4:
            WphaseH_UphaseL();
            break;
        case 5:
            WphaseH_VpahseL();
            break;

        default:
            break;
        }
    }
    else
    {
        switch (simpleOpen.nextPhaseCount)
        {
        case 0:
            UphaseH_VphaseL();
            break;
        case 1:
            WphaseH_VpahseL();
            break;
        case 2:
            WphaseH_UphaseL();
            break;
        case 3:
            VphaseH_UphaseL();
            break;
        case 4:
            VphaseH_WphaseL();
            break;
        case 5:
            UphaseH_WphaseL();
            break;

        default:
            break;
        }
    }
}

/**
 * @brief 反电动势跳变检测
 *
 * @param val
 * @return 0:1->0  1:0->1
 */
uint8_t UmefEdge(uint8_t val)
{
    /* 主要是检测val信号从0 - 1 在从 1 - 0的过程，即高电平所持续的过程 */
    static uint8_t oldval = 0;
    if (oldval != val)
    {
        oldval = val;

        if (val == 0)
            return 0;
        else
            return 1;
    }

    return 2;
}

/**
 * @brief 过零检测
 *
 * @return 0:不稳定过零信号  1:稳定过零信号
 */
uint8_t HallLessOperation(void)
{
    static uint8_t edgeFlag = 0; /* 过零信号稳定标志 */

    speedCount++; // 只统计1->0这段时间的高电平,其余时间会被清空

    // 存放过零状态,每次与上真实的IO状态,若8次都是1 表示检测信号为1,记为稳定
    hallLessParameter.queueState[0] = hallLessParameter.queueState[0] << 1;
    hallLessParameter.queueState[1] = hallLessParameter.queueState[1] << 1;
    hallLessParameter.queueState[2] = hallLessParameter.queueState[2] << 1;

    hallLessParameter.queueState[0] |= HAL_GPIO_ReadPin(HALL_U_GPIO_Port, HALL_U_Pin);
    hallLessParameter.queueState[1] |= HAL_GPIO_ReadPin(HALL_V_GPIO_Port, HALL_V_Pin);
    hallLessParameter.queueState[2] |= HAL_GPIO_ReadPin(HALL_W_GPIO_Port, HALL_W_Pin);

    // 判断三相是否稳定
    for (int i = 0; i < 3; i++)
    {
        if ((hallLessParameter.queueState[i] & 0XFF) == 0XFF)
        {
            hallLessParameter.queueFilterState[i] = 1;
        }
        else if ((hallLessParameter.queueState[i] & 0xFF) == 0x00)
        {
            hallLessParameter.queueFilterState[i] = 0;
        }
        else
        {
            hallLessParameter.filterFailedCount++; // 不稳定计数,后续会用作转速为0的判断
            return 0;
        }
    }

    /*速度测量*/
    hallLessParameter.filterEdge = UmefEdge(hallLessParameter.queueFilterState[0]);

    if (hallLessParameter.filterEdge == 0)
    {
        // 说明从1->0,开始统计过零时间
        if (zeroStableFlag >= 4)
        {
            if (motorParameter.dir == CCW)
            {
                // ft/(2*n*c) * 60; 其中ft为计数频率,就是周期中断的频率，n为极对数,c是记的次数
                hallLessParameter.speedRpm = (uint32_t)(((20 * 1000) / (2 * 2 * speedCount)) * 60); // 2极对
            }
            else
            {
                hallLessParameter.speedRpm = -(uint32_t)(((20 * 1000) / (2 * 2 * speedCount)) * 60); // 2极对
            }

            Lpf(&hallLessParameter.speedRpm, hallLessParameter.speedRpm);
        }
        hallLessParameter.filterDelay = speedCount / 10; // 高电平时间记为180度,滞后30度，除以6即可，可以让延迟时间更短,避免硬件问题
        hallLessParameter.filterFailedCount = 0;
        speedCount = 0;
        zeroStableFlag++;
    }

    if (hallLessParameter.filterEdge == 1)
    {
        speedCount = 0;
        hallLessParameter.filterFailedCount = 0;
    }

    if (hallLessParameter.filterEdge == 2)
    {
        // 反电动势没有变化,没有检测到过零信号
        hallLessParameter.filterFailedCount++;

        if (hallLessParameter.filterFailedCount > 15000)
        {
            // 一直没有变化，说明速度为0
            hallLessParameter.filterFailedCount = 0;
            hallLessParameter.speedRpm = 0;
        }
    }

    // 过零控制
    if (zeroStableFlag >= 4)
    {
        static int filterCount = 0;
        // 稳定的过零信号
        zeroStableFlag = 4;
        edgeFlag++; // 稳定后,旋转两圈进入控制

        if (edgeFlag >= 2)
        {
            edgeFlag = 2; // 只有第一次进入过零控制才有,进入完成直接进入
            hallLessParameter.hallLessValue = (hallLessParameter.queueFilterState[0]) | (hallLessParameter.queueFilterState[1] << 1) | (hallLessParameter.queueFilterState[2] << 2);

            if (hallLessParameter.hallLessValue <= 0 || hallLessParameter.hallLessValue > 6)
            {
                return 0;
            }

            if (hallLessParameter.hallLessValue != hallLessParameter.hallLessValuePrev)
            {
                filterCount++; // 延迟30度的时间
            }

            if (filterCount >= hallLessParameter.filterDelay)
            {
                filterCount = 0;
                if (hallLessParameter.hallLessValue != hallLessParameter.hallLessValuePrev)
                {
                    // 发生变化，即可换向
                    if (motorParameter.dir == CW)
                    {
                        cwArray[hallLessParameter.hallLessValue - 1]();
                    }
                    else
                    {
                        ccwArray[hallLessParameter.hallLessValue - 1]();
                    }
                }
                hallLessParameter.hallLessValuePrev = hallLessParameter.hallLessValue;
            }
        }

        return 1;
    }

    return 0;
}
