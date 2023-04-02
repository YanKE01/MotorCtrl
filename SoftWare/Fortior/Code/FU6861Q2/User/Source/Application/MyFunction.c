/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2023-03-26 13:09:19
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-04-02 13:15:32
 * @FilePath: \FU6861Q2\User\Source\Application\MyFunction.c
 */

#include "MyFunction.h"
#include "TM1650.h"
#include <FU68xx_2.h>
#include <Myproject.h>
#include "MyVariable.h"

uint8 keyValue = 0;
uint8 keyValuePrev = 0;

extern MCRAMP xdata mcSpeedRamp; ///< 控制指令爬坡结构体相关变量

void IncreaseSpeed(); // 增速
void ReduceSpeed();   // 减速
void ModeUi();        // 界面刷新
/**
 * @description: 限制转速
 * @param {int} *speed
 * @param {int} min
 * @param {int} max
 * @return {*}
 */
static void LimitSpeed(uint16 *speed, uint16 min, uint16 max)
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

/**
 * @description: 50Ms的任务
 * @return {*}
 */
void MyTask_50Ms_Entry()
{
    uint8 i = 0;
    keyValue = ScanKey1650();

    if (keyValue != keyValuePrev)
    {
        switch (keyValue)
        {
        case 0x44:
            // 启动
            GP37 = 1;
            motor.state = 1;
            break;

        case 0x47:
            // 停止
            GP37 = 0;
            motor.state = 0;
            break;
        case 0x45:
            // 菜单
            break;
        case 0x4C:
            // ACK
            ui.isSetSpeed = 0;                         // 转速设置结束
            motor.targetSpeed = motor.targetSpeedTemp; // 确认转速
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

    keyValuePrev = keyValue;
    ModeUi(); // 刷新UI
}

/***
 *   KEY1:0X44    KEY2:0X45   KEY3:0X46
 *
 *   KEY4:0X47    KEY5:0X4C   KEY6:0X4D
 *
 */
/**
 * @description: 100Ms的任务
 * @return {*}
 */
void MyTask_100Ms_Entry()
{

}

/**
 * @description: 1S的任务
 * @return {*}
 */
void MyTask_1S_Entry()
{
    static uint8 state = 0;
    state = !state;
    GP36 = state;
}

/**
 * @description: 函数运行在1ms的任务中
 * @return {*}
 */
void MyTaskLoop(void)
{
    static int count = 0;
    count++;

    if (count % 50 == 0)
    {
        MyTask_50Ms_Entry();
    }

    if (count % 100 == 0)
    {
        MyTask_100Ms_Entry();
    }

    if (count % 1000 == 0)
    {
        MyTask_1S_Entry();
        count = 0;
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

/**
 * @description: UI刷新
 * @return {*}
 */
void ModeUi()
{
    static int flashCount = 0; // UI闪烁切换

    if (ui.isSetSpeed == 0)
    {
        // 当前不在转速设置页面,正常显示转速
        SetNumber1650(motor.targetSpeed);
    }
    else
    {
        // 当前为转速设置页面 闪烁提示
        flashCount++;
        if (flashCount % 40 == 0)
        {
            flashCount = 0;
            Clear1650();
        }
        else if (flashCount % 10 == 0)
        {

            SetNumber1650(motor.targetSpeedTemp); // 显示的临时转速
        }
    }
}