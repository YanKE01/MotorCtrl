/**
 * @copyright (C) COPYRIGHT 2022 Fortiortech Shenzhen
 * @file      MotorControl.c
 * @author    Fortiortech  Appliction Team
 * @since     Create:2021-04-10
 * @date      Last modify:2022-07-14
 * @brief
 */

/* -----Includes ----- */
#include <FU68xx_2.h>
#include <Myproject.h>

/* -----Private variables ----- */
MotStaType xdata mcState;

MotStaM xdata McStaSet;
uint16 TimeCnt;

/**
 * @brief     电机控制状态机
 * @warning   电机的状态只能在电机状态控制中切换，禁止在其他地方切换电机状态
 */
void MC_Control(void)
{
    switch (mcState)
    {
    case mcReady: // 关闭输出,上电会对电流进行采集校准,当采样校准结束标志置1且启动指令置1后，才跳转到mcInit
        if (mcFaultSource != FaultNoSource)
        {
            mcState = mcFault;
        }
        else
        {
            Motor_Ready();

            if ((mcCurOffset.OffsetFlag == 1) && (mcSpeedRamp.FlagONOFF == 1) && (mcFocCtrl.mcDcbusFlt > UNDER_RECOVER_VALUE))
            {
                mcState = mcInit;
                mcCurOffset.OffsetFlag = 0;
                mcCurOffset.OffsetCount = 0; // 偏置电压采集计数
            }
        }

        break;

    case mcInit:
        if (mcFaultSource != FaultNoSource) // 优先检查是否有错误，若有错误则跳转至错误状态
        {
            mcState = mcFault;
        }
        else if (mcSpeedRamp.FlagONOFF == 0)
        {
            mcState = mcStop;
            mcFocCtrl.State_Count = 10;
        }
        else if (mcCurOffset.OffsetFlag == 1)
        {
            Motor_Init();
#if (TailWind_Mode == NoTailWind)
#if (PosCheckEnable == 1)
            mcState = mcPosiCheck;
            McStaSet.SetFlag.PosiCheckSetFlag = 0;
            mcFocCtrl.mcPosCheckAngle = 0xffff; // 角度赋初值
#elif (AlignEnable == 1)
            mcFocCtrl.mcPosCheckAngle = Align_Angle;
            mcState = mcAlign;
            mcFocCtrl.State_Count = Align_Time;
#else
            mcState = mcStart;
#endif
#else
            mcFocCtrl.State_Count = 100; //(ms) 顺逆风判断时间
            mcFocCtrl.Brake_Count = 100; //(ms) 低速刹车时间设置
            mcState = mcTailWind;
#endif
        }
        else
        {
        }

        break;
#if (TailWind_Mode != NoTailWind)

    case mcTailWind:
        if (mcFaultSource != FaultNoSource)
        {
            mcState = mcFault;
        }
        else if (mcSpeedRamp.FlagONOFF == 0)
        {
            mcState = mcStop;
            mcFocCtrl.State_Count = 100;
        }
        else
        {
            Motor_TailWind();

            if (mcFocCtrl.WindFlag == 1)
            {
#if (PosCheckEnable == 1)
                mcState = mcPosiCheck;
                McStaSet.SetFlag.PosiCheckSetFlag = 0;
                mcFocCtrl.mcPosCheckAngle = 0xffff; // 角度赋初值
#elif (AlignEnable == 1)
                mcFocCtrl.mcPosCheckAngle = Align_Angle;
                mcState = mcAlign;
                mcFocCtrl.State_Count = Align_Time;
#else
                mcState = mcStart;
#endif
            }
            else if (mcFocCtrl.WindFlag == 2)
            {
                mcState = mcRun;
            }
        }

        break;
#endif
#if (PosCheckEnable == 1)

    case mcPosiCheck:
        if (mcFaultSource != FaultNoSource)
        {
            mcState = mcFault;
        }
        else if (mcSpeedRamp.FlagONOFF == 0)
        {
            mcState = mcStop;
            mcFocCtrl.State_Count = 10;
        }
        else
        {
            // RPD();
        }

        break;
#endif
#if (AlignEnable == 1)

    case mcAlign: // 预定位时间结束后，直接启动; AlignTestMode=1用于初始位置检测调试用
        if (mcFaultSource != FaultNoSource)
        {
            mcState = mcFault;
        }
        else if (mcSpeedRamp.FlagONOFF == 0)
        {
            mcState = mcStop;
            mcFocCtrl.State_Count = 10;
        }
        else
        {
            Motor_Align();
#if (AlignTestMode == 1)
            {
                while (1)
                    ;
            }
#else
            {
                if (mcFocCtrl.State_Count == 0)
                {
                    mcState = mcStart;
                }
            }
#endif
        }

        break;
#endif

    case mcStart: // 配置电机启动参数，进入mcRun状态。
        if (mcFaultSource != FaultNoSource)
        {
            mcState = mcFault;
        }
        else if (mcSpeedRamp.FlagONOFF == 0)
        {
            mcState = mcStop;
            mcFocCtrl.State_Count = 10;
        }
        else
        {
            FOC_Init();
            Motor_Open();
            mcState = mcRun;
        }

        break;

    case mcRun: // 运行状态，若运行状态的给定变为0，进入mcStop状态。
        if (mcFaultSource != FaultNoSource)
        {
            mcState = mcFault;
        }
        else if (mcSpeedRamp.FlagONOFF == 0)
        {
            mcState = mcStop;
            mcFocCtrl.State_Count = 5;
        }
        else
        {
        }

        break;

    case mcStop:
        if (mcFaultSource != FaultNoSource)
        {
            mcState = mcFault;
        }
        else
        {
            //            if((mcFocCtrl.SpeedFlt < _Q15( 1000 / MOTOR_SPEED_BASE))||(mcFocCtrl.State_Count==0)) //
            if ((mcFocCtrl.Powerlpf < 0.8 * Motor_Max_Power) || (mcFocCtrl.State_Count == 0)) //
            {
#if (StopBrakeFlag == 0)
                {
                    mcState = mcReady;
                    MOE = 0;
                    FOC_CR1 = 0x00;
                    ClrBit(DRV_CR, FOCEN);
                }
#else
                {
                    if (mcFocCtrl.SpeedFlt < Motor_Stop_Speed)
                    {
                        MOE = 0;
                        FOC_CR1 = 0x00;
                        ClrBit(DRV_CR, FOCEN);
                        DRV_DR = DRV_ARR + 1;
                        DRV_CMR &= 0xFFC0;
                        DRV_CMR |= 0x015;    // 三相下桥臂通，刹车,注意有效电平
                        ClrBit(DRV_CR, OCS); // OCS = 0, DRV_COMR;OCS = 1, FOC/SVPWM/SPWM
                        MOE = 1;
                        mcState = mcBrake;
                        mcFocCtrl.State_Count = StopWaitTime;
                    }
                }
#endif
            }
            else if (mcSpeedRamp.FlagONOFF == 1)
            {
                mcState = mcRun;
                mcFocCtrl.CtrlMode = 0;
                FOC_IQREF = IQ_RUN_CURRENT;
            }
            else
            {
            }
        }

        break;

    case mcBrake:
        if (mcFocCtrl.State_Count == 0)
        {
            mcState = mcReady;
            MOE = 0;
            ClrBit(DRV_CR, FOCEN);
        }

        break;

    case mcFault:
        FaultProcess();

        if (mcFaultSource == FaultNoSource)
        {
            mcState = mcReady;
        }

        _nop_();
        break;

    default:
        mcState = mcReady;
        break;
    }
}
