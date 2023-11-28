/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2023-05-15 22:57:24
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-10-11 09:10:50
 * @FilePath: \LCM_FOC\Sources\User_Soruces\HY_Application.c
 */
#include "HY_Application.h"
#include "UserParaSetDefine.h"
#include "HY_Variable.h"
#include "HY_Hal.h"
#include "HY_Display.h"
#include "HY_Display2.h"

#define LIMIT(x, min, max) ((x) < (min) ? (min) : ((x) > (max) ? (max) : (x)))

uint16_t speed_array[20] = {0};
uint16_t speed_count = 0;

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
 * @brief UI界面切换
 *
 */
void ModeUiPageProcess()
{
    HY_TM1638_Clear();
    ui.modePage++;
    ui.modePage %= 2;
}

/**
 * @brief MPPT速度控制
 *
 */
void MpptControl()
{
    int i, j, k, w;
    int sum = 0;

    for (i = 0; i < 5; i++)
    {
        motor.vbusArray[i] = (1.0 * ADCConvertedRawData[0] / 4096.0) * 4.1 * 25.0 + 1.0;
    }

    for (i = 0; i < 5 - 1; i++)
    {
        for (j = 0; j < 5 - i - 1; j++)
        {
            if (motor.vbusArray[j] > motor.vbusArray[j + 1])
            {
                float temp = motor.vbusArray[j];
                motor.vbusArray[j] = motor.vbusArray[j + 1];
                motor.vbusArray[j + 1] = temp;
            }
        }
    }

    motor.currentVbus = (motor.vbusArray[1] + motor.vbusArray[2] + motor.vbusArray[3]) / 3.0;

    if (motor.fault == 0 && motor.state == 1)
    {
        // 无故障且启动
        pd.error = motor.currentVbus - motor.minVbus;

        motor.targetSpeed = (uint16_t)(1.0 * 1000 + pd.kp * pd.error + pd.kd * (pd.error - pd.error_last));

        if (motor.targetSpeed < motor.minSpeed)
        {
            motor.targetSpeed = motor.minSpeed;
        }

        if (motor.targetSpeed > motor.maxSpeed)
        {
            motor.targetSpeed = motor.maxSpeed;
        }
        pd.error_last = pd.error;

        speed_array[speed_count++] = motor.targetSpeed;

        if (speed_count == 20)
        {
            speed_count = 0;

            for (k = 0; k < 20 - 1; k++)
            {
                for (w = 0; w < 20 - k - 1; w++)
                {
                    if (speed_array[w] < speed_array[w + 1])
                    {
                        int temp_speed = speed_array[w];
                        speed_array[w] = speed_array[w + 1];
                        speed_array[w + 1] = temp_speed;
                    }
                }
            }
            sum = 0;
            for (k = 9; k < 13; k++)
            {
                sum += speed_array[k];
            }
            motor.mpptSpeed = (uint16_t)(sum / 4.0);
            motor.targetSpeedTemp = motor.mpptSpeed;
        }
    }
}

/**
 * @brief UI刷新
 *
 */
void ModeUi()
{
    static int flashCount = 0; // UI闪烁切换
    static int faultCount = 0;
    static int showCount = 0;
    if (UG_sSysStateErr.uSystemError.All == 0x00 && motor.fault == 0)
    {
        // 无故障状态下,且不在转速设置页面
        if (ui.isSetSpeed == 0)
        {
            if (showCount++ == 20)
            {
                showCount = 0;
                switch (ui.modePage)
                {
                case VbusPage:
                    HY_TM1638_SetNumAuto((uint16_t)(motor.currentVbus)); // 显示当前电压
                    HY_TM1638_SetLedState(RPM, 0);
                    HY_TM1638_SetLedState(V, 1);
                    break;
                case SpeedPage:
                    /* code */
                    if (motor.mode)
                    {
                        HY_TM1638_SetNumAuto(motor.mpptSpeed); // 显示MPPT速度
                    }
                    else
                    {
                        HY_TM1638_SetNumAuto(motor.targetSpeed); // 显示电源模式下的速度
                    }
                    HY_TM1638_SetLedState(RPM, 1);
                    HY_TM1638_SetLedState(V, 0);
                    break;
                case CurrentPage:
                    // HY_TM1638_SetNumAuto(motor.busCurrent); // 显示母线电压
                    break;
                default:
                    break;
                }
            }
        }
        else
        {
            // 当前为转速设置页面 闪烁提示
            flashCount++;
            if (flashCount % 20 == 0)
            {
                flashCount = 0;
                HY_TM1638_Clear();
            }
            else if (flashCount % 10 == 0)
            {
                HY_TM1638_SetNumAuto(motor.targetSpeedTemp); // 显示的临时转速
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
            HY_TM1638_Clear();
        }
        else if (faultCount % 15 == 0)
        {
            HY_TM1638_SetFault(UG_sSysStateErr);
        }

        motor.state = 0; // 发生错误后，电机应该处于停机状态
    }
}

/****************************任务*************************************/

/**
 * @brief 50MS定时任务
 *
 */
static void HY_Task_50MS_Entry()
{
    ui.keyValue = HY_TM1638_ScanKey();
    if (ui.keyValue != ui.keyValue_Prev)
    {
        switch (ui.keyValue)
        {
        case 1:
            // SET 切换MPPT模式和恒速模式
            if (UG_sSysStateErr.uSystemError.All == 0x00)
            {
                motor.mode = !motor.mode; // 仅无故障支持切换
            }
            break;
        case 2:
            // ENTER
            ui.isSetSpeed = 0;                         // 设置转速结束
            motor.targetSpeed = motor.targetSpeedTemp; // 确认转速
            motor.fault = 0;
            break;
        case 3:
            // UP
            IncreaseSpeed();
            break;
        case 4:
            // DOWN
            ReduceSpeed();
            break;
        case 5:
            // SWITCH
            ModeUiPageProcess();
            break;
        case 6:
            // ONOFF
            if (UG_sSysStateErr.uSystemError.All == 0x00)
            {
                motor.state = !motor.state;
            }
            else
            {
                motor.state = 0;
            }
            break;
        default:
            break;
        }
    }

    ui.keyValue_Prev = ui.keyValue;

    if (motor.mode)
    {
        // MPPT模式
        MpptControl();
        HY_TM1638_SetLedState(MPPT, 1);
    }
    else
    {
        HY_TM1638_SetLedState(MPPT, 0);
    }

    ModeUi();
}

/**
 * @brief 100MS定时任务
 *
 */
static void HY_Task_100MS_Entry()
{
}

/**
 * @brief 1S定时任务
 *
 */
static void HY_Task_1S_Entry()
{
    motor.currentVbus = (1.0 * ADCConvertedRawData[0] / 4096.0) * 4.1 * 25.0 + 1.0; // 采集当前母线电压，ADC基准为4.0V，但是校准是在4.1V下进行，1.0为手动偏移母线压降
    motor.busCurrent = 1.0 * UG_sADSampleAll.s16IdcLPFTem / 4096.0 * UPDS_IB;       // 采集当前母线电流

    if (motor.fault)
    {
        strategy.faultCount++;
        motor.targetSpeed = motor.minSpeed;
        motor.state = 0;

        if (strategy.faultCount == 30)
        {
            // 解锁错误
            motor.fault = 0;
            UG_sSysStateErr.uSystemError.All = 0X00;
            motor.state = 0;
            strategy.faultCount = 0;
            HY_TM1638_Clear();
        }
    }
}

/**
 * @brief LOOP函数以1KHZ运行
 *
 */
void HY_TaskLoop()
{
    static int count = 0;
    static uint8_t flag = 0;
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
