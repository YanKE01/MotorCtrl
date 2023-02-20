/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2023-02-19 20:48:08
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-02-20 21:28:22
 * @FilePath: \F401RET6_Pump\Application\system.c
 */
#include "system.h"
#include "variable.h"
#include "mc_api.h"
#include "hal.h"
#include "stdio.h"
#include "main.h"
#include "bus_voltage_sensor.h"

extern SystemInfo systemInfo;

void PanelKeyProcess(void); // 显示面板按键处理
void ModeUi(void);          // 模式UI界面
void GetVbusVoltage(void);  // 获取系统电压
void ModePageProcess(void); // UI页面处理
void IncreaseSpeed(void);   // 增速
void DecreaseSpeed(void);   // 减速
void MotorCtrl(void);
/**
 * @brief 速度限幅
 *
 * @param speed
 * @param min
 * @param max
 */
static inline void LimitSpeed(int *speed, int min, int max)
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
 * @brief 查询系统状态
 *
 */
void QuerySystemState(void)
{
    motor.motorState = MC_GetSTMStateMotor1(); // 获取当前电机状态
    motor.current = MC_GetIabMotor1().a;       // 获取A轴电流
    systemState.keyState = Read74HC165D();     // 读取当前按键状态
    PanelKeyProcess();                         // 处理按键
    GetVbusVoltage();                          // 获取当前电机电压状态
    ModeUi();                                  // 刷新MODE UI
    MotorCtrl();                               // 电机运行

    systemState.keyStatePrev = systemState.keyState; // 刷新按键状态
}

/**
 * @brief 处理面板按键
 *
 */
void PanelKeyProcess(void)
{
    if (systemState.keyState != systemState.keyStatePrev)
    {
        switch (systemState.keyState)
        {
        case 0x3E:
            printf("Statr Motor\n");
            motor.isMotorStart = 1;
            break;

        case 0x37:
            printf("Stop Motor\n");
            motor.isMotorStart = 0;
            break;

        case 0x3D:
            printf("Mode\n");
            ModePageProcess();
            break;

        case 0x2F:
            printf("Set\n");
            break;
        case 0x3B:
            printf("Add Speed\n");
            IncreaseSpeed();
            break;
        case 0x1F:
            printf("Sub Speed\n");
            DecreaseSpeed();
            break;
        default:
            break;
        }
    }
}

/**
 * @brief UI绘制
 *
 */
void ModeUi(void)
{
    // 显示转速、电流、电压

    switch (ui.modePage)
    {
    case SpeedPage:
        // 显示转速
        TM1650_SetNumber(motor.targetSpeed);
        break;

    case CurrentPage:
        // 显示电流
        TM1650_SetNumber(2);
        break;

    case VbusPage:
        // 显示电机电压
        TM1650_SetNumber(motor.motorVoltage);
        break;
    default:
        break;
    }
}

/**
 * @brief 获取总线电压
 *
 */
void GetVbusVoltage()
{
    BusVoltageSensor_Handle_t *BusVoltageSensor[NBR_OF_MOTORS] = {&BusVoltageSensor_M1._Super};
    motor.motorVoltage = VBS_GetAvBusVoltage_V(BusVoltageSensor[0]);
}

/**
 * @brief 模式页面处理
 *
 */
void ModePageProcess(void)
{
    ui.modePage++;
    ui.modePage %= 3;
}

/**
 * @brief 增加速度
 *
 */
void IncreaseSpeed()
{
    // 判断当前UI也是否为设置页
    if (ui.modePage == SpeedPage)
    {
        // 设置
        motor.targetSpeed += systemInfo.motorParameter.speedChangeStep;
        LimitSpeed(&motor.targetSpeed, systemInfo.motorParameter.minSpeed, systemInfo.motorParameter.maxSpeed);
    }
}

/**
 * @brief 减少速度
 *
 */
void DecreaseSpeed()
{
    if (ui.modePage == SpeedPage)
    {
        motor.targetSpeed -= systemInfo.motorParameter.speedChangeStep;
        LimitSpeed((int *)&motor.targetSpeed, systemInfo.motorParameter.minSpeed, systemInfo.motorParameter.maxSpeed);
    }
}

void MotorCtrl()
{
    switch (motor.motorState)
    {
    case FAULT_OVER:
        printf("Motor Fault Over\n");
        // MC_StopMotor1(); // 关闭电机
        MC_AcknowledgeFaultMotor1(); // 关闭错误
        break;
    case IDLE:
        if (motor.isMotorStart)
        {
            MC_ProgramSpeedRampMotor1(motor.targetSpeed, 10); // 设置初始转速
            Mci[M1].DirectCommand = MCI_START;                 // 设置电机状态为启动
            // MC_StartMotor1();                                  // 在启动状态+空闲下启动电机
        }
        break;

    case RUN:
        if (!motor.isMotorStart)
        {
            Mci[M1].State = STOP;
            ; // 正常运行状态下 关闭电机
        }

        // 更新电机转速
        MC_ProgramSpeedRampMotor1_F(motor.targetSpeed, systemInfo.motorParameter.speedDuration);

        break;
    default:
        break;
    }

    // if (motor.isMotorStart)
    // {
    //     if (motor.motorState == IDLE)
    //     {
    //         Mci[M1].DirectCommand = MCI_START;
    //     }
    //     else if (motor.motorState == FAULT_OVER)
    //     {
    //         Mci[M1].DirectCommand = OFFSET_CALIB;
    //     }
    // }
    // else
    // {
    //     Mci[M1].State = STOP;
    // }
}
