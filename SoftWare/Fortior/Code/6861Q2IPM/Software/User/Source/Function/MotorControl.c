/* --------------------------- (C) COPYRIGHT 2020 Fortiortech ShenZhen -----------------------------
    File Name      : MotorControl.c
    Author         : Fortiortech  Appliction Team
    Version        : V1.0
    Date           : 2020-09-16
    Description    : This file contains XX-XX-XX function used for Motor Control.
----------------------------------------------------------------------------------------------------
                                       All Rights Reserved
------------------------------------------------------------------------------------------------- */
#include <FU68xx_2.h>
#include <Myproject.h>
/* Private variables ----------------------------------------------------------------------------*/
MotStaType mcState;
MotStaM    mcStaSet;


/* -------------------------------------------------------------------------------------------------
    Function Name  : MC_Control
    Description    : 电机状态机函数，包括初始化、预充电、顺风逆风判断、预定位、启动、运行、故障等
    Date           : 2020-09-16
    Parameter      : None
------------------------------------------------------------------------------------------------- */
void MC_Control(void)
{
    switch (mcState)
    {
        /* -----关闭输出,上电会对电流进行采集校准,当采样校准结束标志置1且启动指令置1后，才跳转到mcInit----- */
        case mcReady:
            Motor_Ready();
            
            if (mcFaultSource != FaultNoSource)
            {
                mcState = mcFault;
            }
            else if ((mcCurOffset.offsetFlag == 1) && (mcSpeedRamp.flagONOFF == 1) && (mcFocCtrl.state_Count == 0))
            {
                mcState = mcInit;
                mcCurOffset.offsetFlag             = 0;                                                    // 开始电流采集
                mcCurOffset.offsetCount            = 0;
            }
            
            break;
            
        /* -----初始化状态，进入mcCharge状态----- */
        case mcInit:
            if (mcCurOffset.offsetFlag == 1)
            {
                if (mcFaultSource != FaultNoSource)
                {
                    mcState = mcFault;
                }
                else
                {
                    Motor_Init();
                    #if (MotorFiledWeakenEn)//弱磁
                    {
                        FiledWeakenInit();
                    }
                    #endif
                    mcState               =  mcCharge;
                    mcFocCtrl.state_Count = Charge_Time;
                }
            }
            
            break;
            
        /* -----预充电状态，MCU输出固定频率占空比，预充电结束后，跳入mcAlign----- */
        case mcCharge:
            if (mcFaultSource != FaultNoSource)
            {
                mcState = mcFault;
            }
            else
            {
                Motor_Charge();
                /* -----正常按电机状态机运行 ----- */
                #if (IPMState == NormalRun)
                {
                    if ( mcFocCtrl.state_Count == 0)
                    {
                        MOE = 0;
                        mcState = mcAlign;
                        mcFocCtrl.state_Count = Align_Time;
                    }
                }
                #endif
            }
            
            break;
            
        /* -----预定位时间结束后，直接启动; AlignTestMode=1用于初始位置检测调试用 ----- */
        case mcAlign:
            if (mcFaultSource != FaultNoSource)
            {
                mcState = mcFault;
            }
            else
            {
                Motor_Align();
                #if (AlignTestMode == 1)
                {
                    while (1);
                }
                #else
                {
                    if (mcFocCtrl.state_Count == 0)
                    {
                        mcState = mcStart;
                    }
                    else
                    {
                        if ((mcFocCtrl.state_Count > (Align_Time * 0.85)))
                        {
                            mcFocCtrl.IqRef = (float)IQ_Align_CURRENT / (Align_Time * 0.15) * (Align_Time - mcFocCtrl.state_Count);
                            mcFocCtrl.IdRef = ID_Align_CURRENT;
                        }
                        else if ((mcFocCtrl.state_Count > (Align_Time * 0.5)))
                        {
                            mcFocCtrl.IdRef = ID_Align_CURRENT;
                            mcFocCtrl.IqRef = IQ_Align_CURRENT;
                        }
                        else if ((mcFocCtrl.state_Count > (Align_Time * 0.25)))
                        {
                            FOC__THETA      = AlignSecondAngle;
                        }
                        else
                        {
                            FOC__THETA      = 0;
                        }
                
                        FOC_IDREF = mcFocCtrl.IdRef;
                        FOC_IQREF = mcFocCtrl.IqRef;
                    }
                }
                #endif
            }
            
            break;
            
        /* -----配置电机启动参数，进入mcRun状态 ----- */
        case mcStart:
            if (mcFaultSource != FaultNoSource)
            {
                mcState = mcFault;
            }
            else
            { Motor_Open(); }
            
            break;
            
        /* -----运行状态，若运行状态的给定变为0，进入mcStop状态 ----- */
        case mcRun:
            if (mcFaultSource != FaultNoSource)
            {
                mcState = mcFault;
            }
            else if (mcSpeedRamp.targetValue == 0)
            {
                mcState               = mcStop;
                mcFocCtrl.state_Count = 60000;
            }
            
            break;
            
        /* -----实际转速低于Motor_Min_Speed或延时到了，关闭PWM输出 ----- */
        case mcStop:
            if (mcFaultSource != FaultNoSource)
            {
                mcState = mcFault;
            }
            else if ((mcFocCtrl.speedFlt < Motor_Min_Speed) || (mcFocCtrl.state_Count == 0))
            {
                FOC_CR1 = 0x00;
                ClrBit(DRV_CR, FOCEN);
                mcFocCtrl.state_Count = 0;
                mcState = mcReady;
            }
            else if (mcSpeedRamp.targetValue > 0)                                                                           // Stop状态时，电机在减速状态，又开机进入正常运行模式
            {
                mcState            = mcRun;
            }
            
            break;
            
        case mcFault:
            if (mcFaultSource == FaultNoSource)   //保护清零后关闭输出，软件重新运行
            {
                mcState   = mcReady;
            }
            else
            {
                DRV_CMR &= 0xFFC0;                                                                             // 六个MOS的输出关闭，不然在断电快速上电再进行预充电开始会出现电流尖峰。
                ClrBit(DRV_CR, FOCEN);  //FOC Disable
                MOE     = 0;
            }
            
            break;
    }
}

