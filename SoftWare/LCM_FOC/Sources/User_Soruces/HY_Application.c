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

#define LIMIT(x, min, max) ((x) < (min) ? (min) : ((x) > (max) ? (max) : (x)))

uint8_t keyValue = 0;
uint8_t keyValuePrev = 0;
uint32_t pb0_adc = 0;
uint32_t pb1_adc = 0;
int count = 0;
uint8_t isFirstStart = 0; // 是否为第一次尝试启动
int faultCount = 0;       // 故障计数
float test_speed = 0.0f;
float vbus_array[5] = {0};
uint16_t max_speed = 0;
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
 * @description: UI界面切换
 * @return {*}
 */
void ModeUiPageProcess()
{
    HY_TM1650_Clear();
    ui.modePage++;
    ui.modePage %= 2;
}

void speed_ctrl()
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
            max_speed = (uint16_t)(sum / 4.0);
        }
    }
}
/**
 * @description: UI刷新
 * @return {*}
 */
void ModeUi()
{
    static int flashCount = 0; // UI闪烁切换
    static int faultCount = 0;
    static int showCount = 0;
    if (UG_sSysStateErr.uSystemError.All == 0x00 && motor.fault == 0)
    {
        // 无故障状态下,且不再转速设置页面
        if (ui.isSetSpeed == 0)
        {
            if (showCount++ == 20)
            {
                showCount = 0;
                switch (ui.modePage)
                {
                case VbusPage:
                    HY_TM1650_SetNumber((uint16_t)motor.currentVbus); // 显示当前电压
                    break;
                case SpeedPage:
                    /* code */
                    HY_TM1650_SetNumber(max_speed); // 显示速度
                    break;
                case CurrentPage:
                    HY_TM1650_SetFloat(motor.busCurrent); // 显示母线电压
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
            UG_sSysStateErr.uSystemError.All = 0X00;
            break;
        case 0x46:
            // 增速
            // IncreaseSpeed();
            break;
        case 0x4D:
            // 减速
            // ReduceSpeed();
            break;
        default:
            break;
        }
    }
    ModeUi();

    keyValuePrev = keyValue;
    speed_ctrl();
}

/**
 * @brief 母线电压滤波
 *
 */
static void HY_Task_100MS_Entry()
{

    // if (strategy.changeCount++ == 1)
    // {
    //     // 2s调整一次
    //     if (!motor.fault && motor.state == 1)
    //     {
    //         // 只有母线电压大于34V，没有故障,尝试增加转速
    //         if (motor.currentVbus > 36.0f)
    //         {
    //             if (strategy.lowVbusChangeCount > 0)
    //             {
    //                 strategy.lowVbusChangeCount--;
    //             }
    //             else
    //             {
    //                 motor.targetSpeed += 10;
    //             }
    //         }
    //         else
    //         {
    //             motor.targetSpeed -= 200;
    //             strategy.lowVbusChangeCount = 100;
    //         }
    //     }
    //     strategy.changeCount = 0;
    // }
}

/**
 * @description: 1s任务
 * @return {*}
 */
static void HY_Task_1S_Entry()
{
    // motor.currentVbus = (1.0 * ADCConvertedRawData[0] / 4096.0) * 4.1 * 25.0 + 1.0; // 采集当前母线电压，ADC基准为4.0V，但是校准是在4.1V下进行，1.0为手动偏移母线压降
    motor.busCurrent = 1.0 * UG_sADSampleAll.s16IdcLPFTem / 4096.0 * UPDS_IB; // 采集当前母线电流
    pb0_adc = ADCConvertedRawData[7];
    pb1_adc = ADCConvertedRawData[5];

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
            motor.state = 1;
            // strategy.faultCount = 0;
            // strategy.changeCount = 0;
            // strategy.lowVbusChangeCount = 0;
        }
    }

    // ModeUi();

    // test_speed = (-6.9683f * motor.currentVbus * motor.currentVbus * motor.currentVbus + 801.88f * motor.currentVbus * motor.currentVbus - 30926.0f * motor.currentVbus + 401727.0f);

    // if (count++ == 10)
    // {
    //     test_speed += 50;
    //     count = 0;

    //     if (test_speed < motor.minSpeed)
    //     {
    //         test_speed = motor.minSpeed;
    //     }

    //     if (test_speed > motor.maxSpeed)
    //     {
    //         test_speed = motor.maxSpeed;
    //     }

    //     motor.targetSpeed = test_speed;
    // }

    //    if (motor.fault)
    //    {
    //        motor.state = 0;                         // 存在故障，设置为不启动
    //        motor.fault = 0;                         // 手动清空
    //        UG_sSysStateErr.uSystemError.All = 0X00; // 清空所有故障
    //
    //
    //        faultCount++;
    //        count = 0;
    //        isFirstStart = 0; // 设置为首次启动
    //
    //
    //				motor.maxSpeed = (motor.targetSpeedPrev-2*motor.speedChangeStep > motor.minSpeed?motor.targetSpeedPrev-2*motor.speedChangeStep:motor.minSpeed);//预留加速空间

    //        if (faultCount == 60)
    //        {
    //            // 当前启动失败已经累计到10s中，恢复默认的初始启动
    //            faultCount = 0;   // 清空计数
    //            isFirstStart = 0; // 设置为第一次启动
    //            count = 0;
    //            // 多次启动失败，恢复到默认状态
    //            motor.targetSpeedPrev = motor.minSpeed;
    //            motor.targetSpeed = motor.minSpeed;
    //						motor.maxSpeed = (uint16_t)(UPDS_RATED_SPEED);
    //        }
    //        return;
    //    }

    //    count++; // 只有在无故障的时候才有可能++

    //    switch (count)
    //    {
    //    case 2:
    //        if (!motor.fault && !isFirstStart)
    //        {
    //            motor.state = 1;                           // 第一次尝试启动
    //            isFirstStart = 1;                          // 首次启动标志位成立
    //            motor.targetSpeed = motor.minSpeed; // 掉电后就是min，没掉电就是上一次跑起来的速度
    //        }
    //        break;
    //    case 3:
    //        if (!motor.fault)
    //        {
    //            motor.targetSpeedPrev = motor.targetSpeed; // 保留上一次速度
    //            if (motor.targetSpeed < motor.maxSpeed)
    //            {
    //                motor.targetSpeed += motor.speedChangeStep; // 尝试加速
    //            }else{
    //								motor.targetSpeed = motor.maxSpeed; // 限制最大速度
    //						}

    //            count = 0; // 等待下一轮加速
    //        }
    //        break;
    //    default:
    //        break;
    //    }
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
