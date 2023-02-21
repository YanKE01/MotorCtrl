/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2023-02-19 20:48:08
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-02-21 19:59:50
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
void UserAppliactionLoop(void)
{
    motor.motorState = MC_GetSTMStateMotor1(); // 获取当前电机状态
    motor.current = MC_GetIabMotor1().a;       // 获取A轴电流
    systemState.keyState = Read74HC165D();     // 读取当前按键状态
    PanelKeyProcess();                         // 处理按键
    GetVbusVoltage();                          // 获取当前电机电压状态
    ModeUi();                                  // 刷新MODE UI
    MotorCtrl();                               // 电机运行

    systemState.keyStatePrev = systemState.keyState; // 刷新按键状态

    // 以下代码用于区分在正常情况下 手动按下停止时的故障与异常停止
    if (motor.isMotorRun > 0 && motor.isMotorStart == 0)
    {
        // 运行起来后,手动按下停止,正常停止
        motor.motorCurrentFaultCode = 0;
        motor.isMotorRun--;
        motor.maxStartup = systemInfo.motorParameter.maxStartUp;
    }
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
            if (motor.motorCurrentFaultCode == 0 && motor.maxStartup != 0)
            {
                motor.isMotorStart = 1;
            }
            break;

        case 0x37:
            printf("Stop Motor\n");
            motor.isMotorStart = 0;
            motor.maxStartup = systemInfo.motorParameter.maxStartUp;
            motor.motorRunAfterFault = 0;
            motor.motorCurrentFaultCode = 0;
            break;

        case 0x3D:
            printf("Mode\n");
            ModePageProcess();
            break;

        case 0x2F:
            printf("Set\n");
            ui.isSetSpeed = 0;
            motor.targetSpeed = motor.targetSpeedTemp; // 确认转速
            if (motor.maxStartup == 0 || motor.motorRunAfterFault == 1 || motor.motorCurrentFaultCode != 0)
            {
                // 手动ACK
                MC_AcknowledgeFaultMotor1(); // 关闭错误
                motor.maxStartup = systemInfo.motorParameter.maxStartUp;
                motor.isMotorRun = 0;
                motor.motorRunAfterFault = 0;
                motor.motorCurrentFaultCode = 0;
                motor.isMotorStart = 0;
            }
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
 * @other 电机初始启动次数超过容忍值,显示04错误码
 * @other 电机运转过程中,出现错误,显示对应的错误码
 * @other 电机运转过程中,正常,显示对应的数值
 *
 */
void ModeUi(void)
{
    static int flashCount = 0;

    // 容忍的启动次数内,并且没有发生故障
    if (motor.maxStartup > 0 && motor.motorRunAfterFault != 1 && motor.motorCurrentFaultCode == 0)
    {
        // 当前状态下,电机并没有出现异常, 显示转速、电流、电压
        if (ui.isSetSpeed == 0)
        {
            // 当前状态下,用户并未处于设置速度状态,故正常显示即可
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
        else
        {
            // 当前状态下 用户处于设置速度状态,仅显示临时速度,并按规律闪烁
            flashCount++;
            if (flashCount % 10 == 0)
            {
                TM1650_Clear();
                flashCount = 0;
            }
            else if (flashCount % 5 == 0)
            {
                TM1650_SetNumber(motor.targetSpeedTemp); // 设置速度状态显示的未确认的速度
            }
        }
    }
    else
    {
        if (motor.motorCurrentFaultCode || motor.maxStartup == 0)
        {
            TM1650_ShowFaultCode(motor.motorCurrentFaultCode);
        }
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
    if (ui.isSetSpeed == 0)
    {
        ui.modePage++;
        ui.modePage %= 3;
    }
    else
    {
        ui.isSetSpeed = 0;
        ui.modePage = SpeedPage; // 直接回到显示速度的页面
        motor.targetSpeedTemp = motor.targetSpeed;
    }
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
        ui.isSetSpeed = 1; // 当前为设置速度模式
        motor.targetSpeedTemp += systemInfo.motorParameter.speedChangeStep;
        LimitSpeed(&motor.targetSpeedTemp, systemInfo.motorParameter.minSpeed, systemInfo.motorParameter.maxSpeed);
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
        ui.isSetSpeed = 1; // 当前为设置速度模式
        motor.targetSpeedTemp -= systemInfo.motorParameter.speedChangeStep;
        LimitSpeed((int *)&motor.targetSpeedTemp, systemInfo.motorParameter.minSpeed, systemInfo.motorParameter.maxSpeed);
    }
}

/**
 * @brief 电机控制
 *
 */
void MotorCtrl()
{
    switch (motor.motorState)
    {
    case FAULT_OVER:
        printf("Motor Fault Over\n");
        // 启动失败 均会报改错误
        if (motor.maxStartup >= 1 && motor.isMotorStart == 1)
        {
            // 只有在容忍次数范围内,且按下启动状态,自动ACK故障
            if (motor.maxStartup >= 2)
            {
                MC_AcknowledgeFaultMotor1(); // 关闭错误 实际好像会多一次，所以实际做的时候少一次ACK
            }
            motor.maxStartup--;
        }
        else
        {
            // 电机停机
            Mci[M1].State = STOP; // 正常运行状态下 关闭电机
        }
        break;
    case FAULT_NOW:
        // 主要用于判断掉电压 过电压 以及其他错误
        motor.motorCurrentFaultCode = MC_GetCurrentFaultsMotor1(); // mc_type.h
        Mci[M1].State = STOP;                                      // 正常运行状态下 关闭电机
        motor.isMotorStart = 0;                                    // 取消用户启动
        motor.maxStartup = 0;                                      // 取消尝试驱动

        break;
    case IDLE:
        if (motor.isMotorStart)
        {
            MC_ProgramSpeedRampMotor1(motor.targetSpeed, 10); // 设置初始转速
            Mci[M1].DirectCommand = MCI_START;                // 设置电机状态为启动
        }
        break;

    case RUN:
        if (!motor.isMotorStart)
        {
            Mci[M1].State = STOP; // 正常运行状态下  按下停止键关闭电机
        }

        if (motor.isMotorRun < 20)
        {
            motor.isMotorRun++; // 次数达到20次,表示电机已进入正常运转模式
        }

        motor.motorCurrentFaultCode = 0; // 正常运行状态下,清除故障码

        // 更新电机转速
        MC_ProgramSpeedRampMotor1_F(motor.targetSpeed, systemInfo.motorParameter.speedDuration);

        break;

    case STOP:
        motor.motorCurrentFaultCode = 0;
        break;

    default:
        break;
    }
}
