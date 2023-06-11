/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2023-05-15 22:57:24
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-05-18 11:20:22
 * @FilePath: \LCM_FOC\Sources\User_Soruces\HY_Application.c
 */
#include "HY_Application.h"
#include "UserParaSetDefine.h"
#include "HY_Variable.h"
#include "HY_Hal.h"
#include "HY_Display.h"

#define LIMIT(x, min, max) ((x) < (min) ? (min) : ((x) > (max) ? (max) : (x)))

uint8_t keyValue = 0;
uint8_t keyValuePrev = 0;

/**
 * @description: 速度限幅，传址
 * @param {uint16_t} *speed
 * @param {uint16_t} min
 * @param {uint16_t} max
 * @return {*}
 */
static void LimitSpeed(uint16_t *speed, uint16_t min, uint16_t max)
{
    if (*speed > max)
    {
        *speed = max;
    }

    if (*speed < min)
    {
        *speed = min;
    }
}

/****************************状态设置*************************************/
/**
 * @description: 设置水泵机械转速
 * @param {uint16_t} target
 * @return {*}
 */
s32 HY_SetPumpMechanicalSpeed(uint16_t target)
{
    double ratio = 0.0f;
    // 判断是否超过限制
    target = LIMIT(target, motor.minSpeed, motor.maxSpeed);

    ratio = 1.0 * target / UPDS_RATED_SPEED;
    return (s32)(((u32)(ratio * 0x7FFF)) << 9);
}

/**
 * @description: 设置电机状态 0:停止 1:启动
 * @param {uint8_t} start_or_stop
 * @return {*}
 */
void HY_SetPumpState(uint8_t start_or_stop)
{
    switch (start_or_stop)
    {
    case 0:
        // 停止状态
        motor.state = 0;
        break;
    case 1:
        // 启动状态
        motor.state = 1;
        break;
    default:
        break;
    }
}

/**
 * @description: 增速
 * @return {*}
 */
void IncreaseSpeed()
{
    if (ui.modePage == SpeedPage)
    {
        // 只允许在速度设置页设置转速
        ui.isSetSpeed = 1; // ACK后置为0
        motor.targetSpeedTemp += motor.speedChangeStep;
        LimitSpeed(&motor.targetSpeedTemp, motor.minSpeed, motor.maxSpeed);
    }
}

/**
 * @description: 减速
 * @return {*}
 */
void ReduceSpeed()
{
    if (ui.modePage == SpeedPage)
    {
        // 只允许在速度设置页设置转速
        ui.isSetSpeed = 1; // ACK后置为0
        motor.targetSpeedTemp -= motor.speedChangeStep;
        LimitSpeed(&motor.targetSpeedTemp, motor.minSpeed, motor.maxSpeed);
    }
}

/****************************UI*************************************/

/**
 * @description: UI界面切换
 * @return {*}
 */
void ModeUiPageProcess()
{
    HY_TM1650_Clear();
    ui.modePage++;
    ui.modePage %= 3;
}

/**
 * @description: UI刷新
 * @return {*}
 */
void ModeUi()
{
    static int flashCount = 0; // UI闪烁切换
    static int faultCount = 0;
    if (UG_sSysStateErr.uSystemError.All == 0x00 && motor.fault == 0)
    {
        // 无故障状态下,且不再转速设置页面
        if (ui.isSetSpeed == 0)
        {
            switch (ui.modePage)
            {
            case SpeedPage:
                /* code */
                HY_TM1650_SetNumber(motor.targetSpeed); // 显示速度
                break;
            case VbusPage:
                HY_TM1650_SetNumber(motor.currentVbus); // 显示当前电压
                break;
            case CurrentPage:
                HY_TM1650_SetFloat(motor.busCurrent); // 显示母线电压
                break;
            default:
                break;
            }
        }
        else
        {
            // 当前为转速设置页面 闪烁提示
            flashCount++;
            if (flashCount % 20 == 0)
            {
                flashCount = 0;

                HY_TM1650_Clear();
                HY_TM1650_SetDisplay(1, 7, 1);
            }
            else if (flashCount % 10 == 0)
            {
                HY_TM1650_SetNumber(motor.targetSpeedTemp); // 显示的临时转速
            }
        }
    }
    else
    {
        // 有故障状态 UG_sSysStateErr.uSystemError.All底层会自动处理，如果此时恢复到正常的话，错误标志位就会消失，或许考虑一个临时的来暂存一下
        faultCount++;
        if (faultCount % 20 == 0)
        {
            faultCount = 0;

            HY_TM1650_Clear();
            HY_TM1650_SetDisplay(1, 7, 1);
        }
        else if (faultCount % 15 == 0)
        {
            HY_TM1650_ShowFault(UG_sSysStateErr); // 显示故障
        }

        motor.state = 0; // 发生错误后，电机应该处于停机状态
    }
}

/****************************任务*************************************/
int key_test = 0;
/**
 * @description: 50MS任务
 * @return {*}
 */
static void HY_Task_50MS_Entry()
{
    keyValue = HY_TM1650_ScanKey();

    if (keyValue != keyValuePrev)
    {
        switch (keyValue)
        {
        case 0x44:
            if (UG_sSysStateErr.uSystemError.All == 0x00)
            {
                // 无故障启动
                motor.state = 1;
            }
            break;

        case 0x47:
            // 停止
            motor.state = 0;
            ui.modePage = 0; // 恢复到转速设置页
            break;
        case 0x45:
            // 菜单
            ModeUiPageProcess();
            break;
        case 0x4C:
            // ACK
            ui.isSetSpeed = 0;                         // 转速设置结束
            motor.targetSpeed = motor.targetSpeedTemp; // 确认转速
            motor.fault = 0;                           // 手动置0，区分 UG_sSysStateErr.uSystemError.All
            // UG_sSysStateErr.uSystemError.Bits.HardOverCurrent = 0;
            // UG_sSysStateErr.uSystemError.Bits.LosePhase = 0;
            UG_sSysStateErr.uSystemError.All=0X00;
            break;
        case 0x46:
            // 增速
            IncreaseSpeed();
            break;
        case 0x4D:
            // 减速
            ReduceSpeed();
            break;
        default:
            break;
        }
    }
    ModeUi();

    keyValuePrev = keyValue;
}

/**
 * @description: 100MS任务
 * @return {*}
 */
static void HY_Task_100MS_Entry()
{
}

/**
 * @description: 1s任务
 * @return {*}
 */
static void HY_Task_1S_Entry()
{
    motor.currentVbus = (uint16_t)((1.0 * ADCConvertedRawData[2] / 4096.0) * 4.1 * 25.0 + 1.0); // 采集当前母线电压，ADC基准为4.0V，但是校准是在4.1V下进行，1.0为手动偏移母线压降
    //motor.busCurrent = 1.0 * UG_sADSampleAll.s16IdcLPFTem / 4096.0 * UPDS_IB;                   // 采集当前母线电流
    mpptAdc.a7_Value=ADCConvertedRawData[0];
    mpptAdc.b0_Value=ADCConvertedRawData[7];
    mpptAdc.b1_Value=ADCConvertedRawData[5];
}

/**
 * @description: 函数运行在1kz频率下
 * @return {*}
 */
void HY_TaskLoop()
{
    static int count = 0;
    count++;

    if (count % 50 == 0)
    {
        HY_Task_50MS_Entry();
    }

    if (count % 100 == 0)
    {
        HY_Task_100MS_Entry();
    }

    if (count % 1000 == 0)
    {
        HY_Task_1S_Entry();
        count = 0;
    }
}
