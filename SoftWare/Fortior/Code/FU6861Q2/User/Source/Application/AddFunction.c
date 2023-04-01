/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2023-03-20 21:07:44
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-04-01 21:38:57
 * @FilePath: \Software\User\Source\Application\AddFunction.c
 */
/**
 * @copyright (C) COPYRIGHT 2022 Fortiortech Shenzhen
 * @file      AddFunction.c
 * @author    Fortiortech  Appliction Team
 * @since     Create:2022-07-13
 * @date      Last modify:2022-07-14
 * @brief     This file contains main function used for Motor Control.
 */

/* -----Includes----- */
#include <FU68xx_2.h>
#include <Myproject.h>
#include "MyFunction.h"
#include "MyVariable.h"
/* -----Private variables----- */
PWMINPUTCAL idata mcPwmInput;       ///< PWM捕获结构体变量
MotorRSDTypeDef idata RSDDetect;    ///< RSD顺逆风检测结构体变量
FaultStateType xdata mcFaultSource; ///< 错误信息结构体变量
FOCCTRL xdata mcFocCtrl;            ///< FOC电机控制相关结构体变量
ADCSample xdata AdcSampleValue;     ///< ADC相关结构体变量
ONVarible xdata ONOFFTest;          ///< ONOFF启停测试小工具结构体变量
MCLedDisplay xdata mcLedDisplay;    ///< LED灯控制结构体变量
MCRAMP xdata mcSpeedRamp;           ///< 控制指令爬坡结构体相关变量
SLEEPMODE xdata SleepSet;           ///< 睡眠模式控制结构体变量
MotorFRTypeDef xdata mcFRState;     ///< 方向控制结构体变量
KeyScanParam_TypeDef xdata KS;      ///< 按键控制结构体变量
Flag_VARIABLE xdata VariableFlag;   ///< 标志位控制结构体变量
int16 xdata VSP;
int16 Motor_Loop_Speed1;
uint16 PI_Count = 0;
uint32 TempPower;

const int16 PowerGiven[10] = {0, 500, 1000, 2200, 2900, 4300, 5900, 7300, 7900, 8550};

/**
 * @brief     滤波
 * @param[in]   INVlaue
 * @param[out]	OutLastValue
 */
int16 KLPF_VALUE(int16 INVlaue, int16 OutLastValue)
{
    int16 Result = 0;
    MDU_MA = (INVlaue - OutLastValue);
    MDU_MB = (int16)480; // 写被乘数和乘数
    Result = MDU_MB;
    Result += OutLastValue;
    return (Result);
}

/**
  @brief        保护处理函数，关闭FOC输出
 */
void FaultProcess(void)
{
    MOE = 0;
    ClrBit(DRV_CR, FOCEN);
}

/**
    @brief        对变量取16位的绝对值
    @param[in]    value
    @return       绝对值
*/
uint16 Abs_F16(int16 value)
{
    if (value < 0)
    {
        return (-value);
    }
    else
    {
        return (value);
    }
}

/**
    @brief        对变量取32位的绝对值
    @param[in]    value
    @return       绝对值
*/
uint32 Abs_F32(int32 value)
{
    if (value < 0)
    {
        return (-value);
    }
    else
    {
        return (value);
    }
}
/**
    @brief        除法归类，将所有用到除法的地方，放在同一个中断，以避免中断串扰
*/
void APP_DIV(void)
{
    uint32 idata Temp32 = 0;

    if (mcPwmInput.PWMDivFlag == 1) // 启动除法器，避免与过调值中的除法冲突
    {
        MDU_MUL_IDATA_U32(mcPwmInput.PWMCompareUpdate, 32767, &Temp32);
        mcPwmInput.PWMDuty = MDU_DIV_IDATA_U32(&Temp32, &mcPwmInput.PWMARRUpdate);
        mcPwmInput.PWMDivFlag = 0;
    }

//    if( mcFocCtrl.ESDIVFlag==1)                                                           //启动除法器，避免与过调值中的除法冲突
//    {
//       mcFocCtrl.SQUSpeedDIVEs = MDU_DIV_XDATA_U32(&mcFocCtrl.SQUSysSpeed,&mcFocCtrl.EsValue);
//       mcFocCtrl.ESDIVFlag=0;
//    }
#if (TailWind_Mode == RSDMethod)
    {
        //        if(mcFocCtrl.RSDDIVFlag==1)                                                           //启动除法器，避免与过调值中的除法冲突
        //        {
        ////           RSDDetect.RSDSpeed  = MDU_DIV_IDATA_U32(&RSDDetect.RSDSpeedBase, &RSDDetect.RSDPeriod); //Q格式的速度,此处除法器与过调值不冲突
        //           mcFocCtrl.RSDDIVFlag=0;
        //        }
    }
#endif
}

/**
 * @brief    软件电流环
 */
void CurrentLoop(void)
{
    PI2_EK = FOC_IDREF - FOC__ID; // 填入EK
    SMDU_RunBlock(2, PI);
    FOC__UD = PI2_UKH;
    PI3_EK = FOC_IQREF - FOC__IQ;
    SMDU_RunBlock(3, PI);
    FOC__UQ = PI3_UKH;
}

/**
 * @brief    输入PWM处理
 */
void PWMInputCapture(void)
{
    uint16 MotorControlVSP;

    if (mcPwmInput.PWMUpdateFlag == 1) // 有新的duty更新
    {
        if ((Abs_F32(mcPwmInput.PWMCompare - mcPwmInput.PWMCompareOld) < 50) // 两次比较值相近，减少读错率
            && (Abs_F32(mcPwmInput.PWMARROld - mcPwmInput.PWMARR) < 50)      // 两次周期值相近，减少读错率
            //        &&((100<mcPwmInput.PWMARR)&&(mcPwmInput.PWMARR<6000))                     // 周期值在一定范围内才认为有效，即一定频率范围
            && (mcPwmInput.PWMDivFlag == 0))
        {
            mcPwmInput.PWMFlag = 1;                              // PWMFlag置1期间，不读取TIM3__DR和TIM3__ARR;，防止出错
            mcPwmInput.PWMCompareUpdate = mcPwmInput.PWMCompare; // 对其乘以32768
            mcPwmInput.PWMARRUpdate = mcPwmInput.PWMARR;
            mcPwmInput.PWMFlag = 0;
            mcPwmInput.PWMDivFlag = 1; // 启动除法
#if (PWMDUTY_Choose == NegaPWMDUTY)    // 速度随PWM增大而增大
            {
                MotorControlVSP = 32767 - mcPwmInput.PWMDuty;
            }
#elif (PWMDUTY_Choose == PosiPWMDUTY) // 速度随PWM增大而减小
            {
                MotorControlVSP = mcPwmInput.PWMDuty;
            }
#endif

            if ((MotorControlVSP > ONPWMDuty) && (MotorControlVSP <= (OFFPWMDutyHigh)))
            {
                mcSpeedRamp.MotorOffFilter = MotorOffFilterTime;

                if (mcSpeedRamp.MotorOnFilter == 0)
                {
                    mcSpeedRamp.MotorOnFilter = MotorOnFilterTime;
                    mcSpeedRamp.FlagONOFF = 1;
                }
            }
            else if ((MotorControlVSP < OFFPWMDuty) || (MotorControlVSP > OFFPWMDutyHigh))
            {
                mcSpeedRamp.MotorOnFilter = MotorOnFilterTime;

                if (mcSpeedRamp.MotorOffFilter == 0)
                {
                    mcSpeedRamp.MotorOffFilter = MotorOffFilterTime;
                    mcSpeedRamp.FlagONOFF = 0;
                }
            }

            /* -----转速曲线计算----- */
            if (mcSpeedRamp.FlagONOFF == 1)
            {
#if (Motor_Control_Mode == SPEED_LOOP_CONTROL)
                {
                    if (MotorControlVSP <= MINPWMDuty)
                    {
                        mcSpeedRamp.TargetValue = Motor_Min_Speed;
                    }
                    else if (MotorControlVSP < MAXPWMDuty)
                    {
                        mcSpeedRamp.TargetValue = Motor_Min_Speed + SPEED_K * (MotorControlVSP - MINPWMDuty);
                    }
                    else
                    {
                        mcSpeedRamp.TargetValue = Motor_Max_Speed;
                    }
                }
#elif (Motor_Control_Mode == POWER_LOOP_CONTROL)
                {
                    if (MotorControlVSP <= MINPWMDuty)
                    {
                        mcSpeedRamp.TargetValue = Motor_Min_Power;
                    }
                    else if (MotorControlVSP < MAXPWMDuty)
                    {
                        mcSpeedRamp.TargetValue = Motor_Min_Power + POWER_K * (MotorControlVSP - MINPWMDuty);
                    }
                    else
                    {
                        mcSpeedRamp.TargetValue = Motor_Max_Power;
                    }
                }
#elif (Motor_Control_Mode == CURRENT_LOOP_CONTROL)
                {
                    if (MotorControlVSP <= MINPWMDuty)
                    {
                        mcSpeedRamp.TargetValue = Motor_Min_Current;
                    }
                    else if (MotorControlVSP < MAXPWMDuty)
                    {
                        mcSpeedRamp.TargetValue = Motor_Min_Current + POWER_K * (MotorControlVSP - MINPWMDuty);
                    }
                    else
                    {
                        mcSpeedRamp.TargetValue = Motor_Max_Current;
                    }
                }
#endif
            }
            else
            {
                mcSpeedRamp.TargetValue = 0;
            }
        }

        mcPwmInput.PWMCompareOld = mcPwmInput.PWMCompare; // 将此次比较值赋值给上次比较值
        mcPwmInput.PWMARROld = mcPwmInput.PWMARR;         // 将此次周期值赋值给上次周期值
        mcPwmInput.PWMUpdateFlag = 0;
    }
}

/**
 * @brief    启动测试
 */
void ONOFF_Starttest()
{
    if (ONOFFTest.ONOFF_Flag == 1)
    {
        ONOFFTest.ON_Count++;

        if (ONOFFTest.ON_Count > StartON_Time)
        {
            ONOFFTest.ON_Count = 0;
            ONOFFTest.ONOFF_Times++;
            ONOFFTest.ONOFF_Flag = 0;
            mcSpeedRamp.FlagONOFF = 0;
            mcSpeedRamp.TargetValue = 0;
        }
    }
    else
    {
        if (mcState != mcFault)
        {
            ONOFFTest.OFF_Count++;

            if (ONOFFTest.OFF_Count > StartOFF_Time)
            {
                ONOFFTest.OFF_Count = 0;
                ONOFFTest.ONOFF_Flag = 1;
                mcSpeedRamp.FlagONOFF = 1;
#if (Motor_Control_Mode == SPEED_LOOP_CONTROL)
                {
                    mcSpeedRamp.TargetValue = MOTOR_Onoff_Speed;
                }
#elif (Motor_Control_Mode == POWER_LOOP_CONTROL)
                {
                    mcSpeedRamp.TargetValue = Motor_ONOFF_Power;
                }
#elif (Motor_Control_Mode == CURRENT_LOOP_CONTROL)
                {
                    mcSpeedRamp.TargetValue = Motor_ONOFF_Current;
                }
#endif
            }
        }
    }
}

/**
 * @brief        外部闭环控制函数，示例代码提供 电流环，速度环，功率环，可根据需要自行修改
 *               建议使用默认1ms周期运行
 */
void Speed_response(void)
{
    if ((mcState == mcRun) || (mcState == mcStop))
    {
        switch (mcFocCtrl.CtrlMode)
        {
        case 0:
        {
            if (mcFocCtrl.SpeedFlt > Motor_Loop_Speed)
            {
                mcFocCtrl.CtrlMode = 1;
                FOC_DQKP = DQKP;
                FOC_DQKI = DQKI;
                mcFocCtrl.mcIqref = FOC_IQREF;
#if (Motor_Control_Mode == CURRENT_LOOP_CONTROL)
                {
                    mcSpeedRamp.ActualValue = mcFocCtrl.mcIqref;
                }
#elif (Motor_Control_Mode == SPEED_LOOP_CONTROL)
                {
                    mcSpeedRamp.ActualValue = FOC__EOME;
                }
#elif (Motor_Control_Mode == POWER_LOOP_CONTROL)
                {
                    mcSpeedRamp.ActualValue = mcFocCtrl.Powerlpf;
                }
#endif
                mcFocCtrl.TorqueLoopTime = SPEED_LOOP_TIME;
                PI1_UKH = mcFocCtrl.mcIqref;
                //                    FOC_IQREF = IQ_RUN_CURRENT;
                //                                      PI1_UKH = IQ_RUN_CURRENT;
                //                    mcSpeedRamp.ActualValue = mcFocCtrl.Powerlpf;
            }
        }
        break;

        case 1:
        {
            mcFocCtrl.TorqueLoopTime++;

            if (mcFocCtrl.TorqueLoopTime >= SPEED_LOOP_TIME)
            {
                mcFocCtrl.TorqueLoopTime = 0;
                mc_ramp();
#if (Motor_Control_Mode == CURRENT_LOOP_CONTROL)
                {
                    mcFocCtrl.mcIqref = mcSpeedRamp.ActualValue;
                    FOC_IQREF = mcFocCtrl.mcIqref;
                }
#elif (Motor_Control_Mode == SPEED_LOOP_CONTROL)
                {
                    FOC_IQREF = HW_One_PI(mcSpeedRamp.ActualValue - mcFocCtrl.SpeedFlt); // COMPESATE是作为补偿
                }
#elif (Motor_Control_Mode == POWER_LOOP_CONTROL)
                {
#if (OverSpeedLimitEnable) // 限速
                    {
                        FOC_QMAX = PIDControl(&SpeedPID, Motor_Limit_Speed, mcFocCtrl.SpeedFlt);
                    }
#endif
                    //                            FOC_IQREF = PIDControl(&SpeedPID,mcSpeedRamp.ActualValue,mcFocCtrl.Powerlpf);
                    // 注意！！！下面这句代码调用的时候 32位乘法器的结果右移12位 与PWM计算不需要有边移有冲突
                    //                            FOC_IQREF = PID_Control(&SpeedPID,mcSpeedRamp.ActualValue,mcFocCtrl.Powerlpf);
                    FOC_IQREF = HW_One_PI(mcSpeedRamp.ActualValue - mcFocCtrl.Powerlpf); // 加这句话为什么ActualValue值会变
                }
#endif

                if (FOC_EK2 < OBS_K2T_Actual - 10)
                {
                    mcFocCtrl.Smo_EK2 = FOC_EK2;
                    mcFocCtrl.Smo_EK2 += 10;
                    FOC_EK2 = mcFocCtrl.Smo_EK2;
                }
                else if (FOC_EK2 > OBS_K2T_Actual + 10)
                {
                    mcFocCtrl.Smo_EK2 = FOC_EK2;
                    mcFocCtrl.Smo_EK2 -= 10;
                    FOC_EK2 = mcFocCtrl.Smo_EK2;
                }
                else
                {
                    FOC_EK2 = OBS_K2T_Actual;
                }
            }
        }
        break;
        }
    }

    if (mcState == mcRun)
    {
        if (mcFocCtrl.RunStateCnt < 15000) // 15s的延迟，用于清RSDCCWFlag,BEMFCCWFlag
        {
            mcFocCtrl.RunStateCnt++;
        }
        else
        {
            BEMFDetect.BEMFCCWFlag = 0;
            RSDDetect.RSDCCWFlag = 0;
        }
    }
}

/**
 * @brief        软件低通滤波
 * @param[in]    Xn1
 * @param[in]    Xn0
 * @param[in]    K
 * @return       滤波结果
 */
int16 SoftLPF(int16 Xn1, int16 Xn0, int16 K)
{
    int16 Temp16 = 0;
    int32 Temp32 = 0;
    Temp32 = (((int32)Xn1 - (int32)Xn0) * (int32)K) >> 15;
    Temp16 = Xn0 + (int16)Temp32;
    return Temp16;
}

/**
 * @brief    LED灯显示
 */
void LED_Display(void)
{
    switch (mcFaultSource)
    {
    case FaultNoSource:
        ResetLEDPin;
        break;

    case FaultHardOVCurrent:
        Led_OnOff(1);
        break;

    case FaultSoftOVCurrent:
        Led_OnOff(2);
        break;

    case FaultUnderVoltage:
        Led_OnOff(3);
        break;

    case FaultOverVoltage:
        Led_OnOff(4);
        break;

    case FaultLossPhase:
        Led_OnOff(5);
        break;

    case FaultStall:
        Led_OnOff(6);
        break;

    case FaultStart:
        Led_OnOff(7);
        break;

    case FaultOverwind:
        Led_OnOff(8);
        break;

    case FaultOverHeat:
        Led_OnOff(9);
        break;

    default:
        break;
    }
}

/**
 * @brief        LED灯的闪烁
 * @param[in]    htime：闪烁时间
 */
void Led_OnOff(uint8 htime)
{
    mcLedDisplay.LedCount++;
    // if (mcLedDisplay.LedCount < mcLedDisplay.Counttime)
    mcLedDisplay.Count++;

    if (mcLedDisplay.Count < (htime << 10))
    {
        if ((mcLedDisplay.Count & 0x03ff) < 0x01ff)
        {
            SetLEDPin;
        }
        else
        {
            ResetLEDPin;
        }
    }
    else if (mcLedDisplay.Count < ((htime << 10) + 2000))
    {
        SetLEDPin;
    }
    else
    {
        mcLedDisplay.LedCount = 0;
        mcLedDisplay.LedTimCot = 0;
        mcLedDisplay.Count = 0;
    }
}

/**
 * @brief    爬坡函数，实际值ActualValue慢慢趋于目标值TargetValue
 */
void mc_ramp()
{
    if (--mcSpeedRamp.DelayCount < 0)
    {
        mcSpeedRamp.DelayCount = mcSpeedRamp.DelayPeriod;

        if (mcSpeedRamp.ActualValue < mcSpeedRamp.TargetValue)
        {
            if (mcSpeedRamp.ActualValue + Motor_Inc < mcSpeedRamp.TargetValue)
            {
                mcSpeedRamp.ActualValue += Motor_Inc;
            }
            else
            {
                mcSpeedRamp.ActualValue = mcSpeedRamp.TargetValue;
            }
        }
        else
        {
            if (mcSpeedRamp.ActualValue - Motor_Dec > mcSpeedRamp.TargetValue)
            {
                mcSpeedRamp.ActualValue -= Motor_Dec;
            }
            else
            {
                mcSpeedRamp.ActualValue = mcSpeedRamp.TargetValue;
            }
        }
    }
}

/*  -------------------------------------------------------------------------------------------------
    Function Name  : HW_Speed_PI
    Description    : 速度PI函数
    Date           : 2020-08-08
    Parameter      : None
    ------------------------------------------------------------------------------------------------- */
// void HW_Speed_PI(void)
//{
//     //      PI_EK =  mcSpeedRamp.ActualValue- mcFocCtrl.Powerlpf;                               //给定转速与实际转速之差，可区分恒功率或恒转速，或恒电压
//     PI_EK =  mcSpeedRamp.ActualValue - FOC__EOME;                                               //给定转速与实际转速之差，直接减FOC__EOME有风险
//     PI_LPF_CR |= 0x02;                                                                          // Start PI
//     _nop_();  _nop_();  _nop_();  _nop_();  _nop_();
//     //    mcFocCtrl.mcIqref= PI_UK;//可区分限功率与不限功率
//     //      FOC_IQREF =mcFocCtrl.mcIqref;
//     PI_UK += (SKP / 4096 + 1);
//     FOC_IQREF = PI_UK;
// }

/*  -------------------------------------------------------------------------------------------------
    Function Name  : HW_Genal_PI
    Description    : PI
    Date           : 2020-08-08
    Parameter      : Xn1: [输入]
**                   Yn0: [输入]
**                   Xn2: [输入]
    ------------------------------------------------------------------------------------------------- */
// int16 HW_Genal_PI(int16 Xn1, int16 Yn0, int16 Xn2)
//{
//     PI_KP = SKP;
//     PI_KI = SKI;
//     PI_UKMAX = SOUTMAX;
//     PI_UKMIN = SOUTMIN;
//     PI_EK =  Xn1;                                                                               //初始化E(K-1)
//     PI_LPF_CR |= 0x02;                                                                          // Start PI
//     _nop_();  _nop_();  _nop_();  _nop_();  _nop_();
//     PI_UK =  Yn0;                                                                               //初始化U(K-1)
//     PI_EK =  Xn2;                                                                               //填入EK
//     PI_LPF_CR |= 0x02;                                                                          // Start PI
//     _nop_();  _nop_();  _nop_();  _nop_();  _nop_();
//     PI_UK += (SKP / 4096 + 1);
//     return PI_UK;
// }

/**
 * @brief        PI运算函数
 * @param[in]    Xn1
 * @return       PI运行结果
 */
int16 HW_One_PI(int16 Xn1)
{
    PI1_EK = Xn1; // 填入EK
    SMDU_RunBlock(1, PI);
    return PI1_UKH;
}

/**
 * @brief        低通滤波函数
 * @param[in]    Xn1
 * @param[in]    Xn0
 * @param[in]    K
 * @return       滤波输出值
 */
int16 LPFFunction(int16 Xn1, int16 Xn0, int8 K)
{
    LPF0_K = K << 8;
    LPF0_X = Xn1;
    LPF0_YH = Xn0;
    SMDU_RunBlock(0, LPF);
    return LPF0_YH;
}

/**
 * @brief    VSP采样
 */
void VSPSample(void)
{
    /* -----VREF的采样获取值并滤波----- */
    AdcSampleValue.ADCVref = (ADC7_DR << 3);            // 采集对应端口
    VSP = LPFFunction(AdcSampleValue.ADCVref, VSP, 10); // 低通滤波

    //    if((VSP > ONPWMDuty)&&(VSP <= OFFPWMDutyHigh))    lint认为右边永远成立                //在ONPWMDuty-OFFPWMDutyHigh之间，电机有转速运行
    if (VSP > ONPWMDuty)
    {
        mcSpeedRamp.FlagONOFF = 1;
    }
    //    else if((VSP < OFFPWMDuty)||(VSP > OFFPWMDutyHigh))                                   //电机停机 lint认为右边永远不成立
    else if ((VSP < OFFPWMDuty)) // 电机停机
    {
        mcSpeedRamp.FlagONOFF = 0;
    }

    /* -----转速曲线计算----- */
    if (mcSpeedRamp.FlagONOFF == 1) //
    {
#if (Motor_Control_Mode == SPEED_LOOP_CONTROL)
        {
            if (VSP <= MINPWMDuty)
            {
                mcSpeedRamp.TargetValue = Motor_Min_Speed;
            }
            else if (VSP < MAXPWMDuty)
            {
                mcSpeedRamp.TargetValue = Motor_Min_Speed + SPEED_K * (VSP - MINPWMDuty);
            }
            else
            {
                mcSpeedRamp.TargetValue = Motor_Max_Speed;
            }
        }
#elif (Motor_Control_Mode == POWER_LOOP_CONTROL)
        {
            if (VSP <= MINPWMDuty)
            {
                mcSpeedRamp.TargetValue = Motor_Min_Power;
            }
            else if (VSP < MAXPWMDuty)
            {
                mcSpeedRamp.TargetValue = Motor_Min_Power + POWER_K * (VSP - MINPWMDuty);
            }
            else
            {
                mcSpeedRamp.TargetValue = Motor_Max_Power;
            }
        }
#elif (Motor_Control_Mode == CURRENT_LOOP_CONTROL)
        {
            if (VSP <= MINPWMDuty)
            {
                mcSpeedRamp.TargetValue = Motor_Min_Current;
            }
            else if (VSP < MAXPWMDuty)
            {
                mcSpeedRamp.TargetValue = Motor_Min_Current + POWER_K * (VSP - MINPWMDuty);
            }
            else
            {
                mcSpeedRamp.TargetValue = Motor_Max_Current;
            }
        }
#endif
    }
    else
    {
        mcSpeedRamp.TargetValue = 0;
    }
}

/**
 * @brief    按键调速
 */
void KeyScan(void)
{
    if (Key0 == 0)
    {
        KS.Key0InitCnt = 0;

        if (KS.Key0PressCnt < 50)
        {
            KS.Key0PressCnt++;
        }
        else
        {
            KS.Key0PressCnt = 0;
            KS.FlagKey0Press = 1;
            KS.FlagKey1Press = 0;
        }
    }
    else
    {
        KS.Key0PressCnt = 0;

        if (KS.Key0InitCnt < 50)
        {
            KS.Key0InitCnt++;
        }
        else
        {
            KS.Key0InitCnt = 0;
            KS.FlagKey0Press = 0;
            KS.FlagKey1Press = 1;
        }
    }

    if (mcSpeedRamp.FlagONOFF)
    {
        if (KS.FlagKey1Press)
        {
//          KS.Key0PressCnt  = 0;
//          KS.Key0InitCnt   = 0;
#if (Motor_Control_Mode == SPEED_LOOP_CONTROL)
            {
                mcSpeedRamp.TargetValue = Motor_Min_Speed;
            }
#elif (Motor_Control_Mode == POWER_LOOP_CONTROL)
            {
                mcSpeedRamp.TargetValue = Motor_Min_Power;
            }
#elif (Motor_Control_Mode == CURRENT_LOOP_CONTROL)
            {
                mcSpeedRamp.TargetValue = Motor_Min_Current;
            }
#endif
        }

        if (KS.FlagKey0Press)
        {
//          KS.Key0PressCnt  = 0;
//          KS.Key0InitCnt   = 0;
#if (Motor_Control_Mode == SPEED_LOOP_CONTROL)
            {
                mcSpeedRamp.TargetValue = Motor_Max_Speed;
            }
#elif (Motor_Control_Mode == POWER_LOOP_CONTROL)
            {
                mcSpeedRamp.TargetValue = Motor_Max_Power;
            }
#elif (Motor_Control_Mode == CURRENT_LOOP_CONTROL)
            {
                mcSpeedRamp.TargetValue = Motor_Max_Current;
            }
#endif
        }
    }
}

/**
 * @brief    睡眠模式
 */
void Sleepmode(void)
{
    SleepSet.SleepDelayCout++;

    if (SleepSet.SleepDelayCout >= 20000) // 最大65530，若要再大，需改数据类型
    {
        //        FOC_EFREQMIN  = -Motor_Omega_Ramp_Min;
        //        FOC_EFREQHOLD = -Motor_Omega_Ramp_End;
        mcSpeedRamp.TargetValue = 0;
        MOE = 0;
        ClrBit(DRV_CR, FOCEN);
        SleepSet.SleepDelayCout = 0;
        SleepSet.SleepFlag = 1;
        SetBit(P1_IE, P11); // config P11 as the source of EXTI1
        SetBit(PCON, STOP);
    }
}

/**
 * @brief    ATO_BW爬坡切换函数，根据时间切换ATO，使其慢慢变大
 */
void StarRampDealwith(void)
{
    //    int temp=0;
    if ((mcState == mcRun))
    {
        //            if(FOC_IQREF<mcFocCtrl.mcIqref)
        //            {
        //                temp=FOC_IQREF;
        //                temp+=20;
        //                FOC_IQREF = temp;
        //            }
        if (mcFocCtrl.State_Count == 670) // 2300
        {
            FOC_EKP = OBSW_KP_GAIN_RUN; // 估算器里的PI的KP
            FOC_EKI = OBSW_KI_GAIN_RUN; // 估算器里的PI的KI
            //              GP07 = 1;
        }
        else if (mcFocCtrl.State_Count == 620) // 2000
        {
            FOC_EKP = OBSW_KP_GAIN_RUN1; // 估算器里的PI的KP
            FOC_EKI = OBSW_KI_GAIN_RUN1; // 估算器里的PI的KI
            //              GP07 = 0;
        }
        else if (mcFocCtrl.State_Count == 580) // 1600
        {
            FOC_EKP = OBSW_KP_GAIN_RUN2; // 估算器里的PI的KP
            FOC_EKI = OBSW_KI_GAIN_RUN2; // 估算器里的PI的KI
            //              GP07 = 1;
        }
        else if (mcFocCtrl.State_Count == 520) // 1200
        {
            FOC_EKP = OBSW_KP_GAIN_RUN3; // 估算器里的PI的KP
            FOC_EKI = OBSW_KI_GAIN_RUN3; // 估算器里的PI的KI
            //              GP07 = 0;
        }
        else if (mcFocCtrl.State_Count == 480)
        {
            FOC_EKP = OBSW_KP_GAIN_RUN4; // 估算器里的PI的KP
            FOC_EKI = OBSW_KI_GAIN_RUN4; // 估算器里的PI的KI
            //              GP07 = 1;
        }
        else
            ;
    }
}

/**
 * @brief    弱磁控制函数
 */
void Weak_Control(void)
{
    if (FOC__UQ > _Q15(0.7))
    {
        if (FOC_IDREF > WEAK_MAX)
        {
            FOC_IDREF -= 1;
        }
        else
        {
            FOC_IDREF = WEAK_MAX;
        }
    }
    else
    {
        FOC_IDREF = WEAK_MIN;
    }
}

/**
 * @brief    默认1ms周期服务函数，运行信号采样，调速信号处理，闭环控制，故障检测,ATO爬坡函数
 *           该函数运行于大循环中，由SYSTICK定时器间隔1ms触发运行。
 */
void TickCycle_1ms(void)
{
    SetBit(ADC_CR, ADCBSY); // 使能ADC的DCBUS采样
    /* -----母线电流采样----- */
    Power_Currt = (ADC3_DR << 3);

    if (Power_Currt > mcCurOffset.Iw_busOffset)
    {
        Power_Currt = Power_Currt - mcCurOffset.Iw_busOffset;
    }
    else
    {
        Power_Currt = 0;
    }

    /* -----母线电流滤波----- */
    mcFocCtrl.mcADCCurrentbus = LPFFunction(Power_Currt, mcFocCtrl.mcADCCurrentbus, 32);

    /* -----输出功率滤波----- */
    if (mcState == mcRun)
    {
        mcFocCtrl.CurrentPower = FOC__POW << 3;
        mcFocCtrl.Powerlpf = LPFFunction(mcFocCtrl.CurrentPower, mcFocCtrl.Powerlpf, 10); // 注意低通滤波器系数范围为0---127
    }

    /* -----速度滤波、反电动势滤波----- */
    if ((mcState != mcInit) && (mcState != mcReady))
    {
        mcFocCtrl.SpeedFlt = LPFFunction(FOC__EOME, mcFocCtrl.SpeedFlt, 10); // 注意低通滤波器系数范围为0---127
        mcFocCtrl.EsValue = LPFFunction(FOC__ESQU, mcFocCtrl.EsValue, 10);
    }
    else
    {
        mcFocCtrl.SpeedFlt = 0;
    }

    /* -----母线电压的采样并滤波----- */
    AdcSampleValue.ADCDcbus = ADC2_DR;
    //        mcFocCtrl.mcDcbusFlt    = AdcSampleValue.ADCDcbus << 3;
    mcFocCtrl.mcDcbusFlt = LPFFunction((ADC2_DR << 3), mcFocCtrl.mcDcbusFlt, 80);
    /* -----功率计算----- */
    //        MDU_MUL_XDATA_U32(mcFocCtrl.mcADCCurrentbus, mcFocCtrl.mcDcbusFlt, &TempPower);
    //        mcFocCtrl.PowerCal = (uint16)(TempPower >> 11);
    //        mcFocCtrl.Powerlpf =  mcFocCtrl.PowerCal;
    /* -----环路响应，如速度环、转矩环、功率环等----- */
    Speed_response();
/* -----弱磁功能配置----- */
#if (WEAK_MAGNETIC_EN)
    {
        Weak_Control();
    }
#endif
    /* -----温度的采样并滤波----- */
    mcFocCtrl.mcADCTemperature = LPFFunction((ADC7_DR << 3), mcFocCtrl.mcADCTemperature, 10);
    /* -----故障保护函数功能，如过欠压保护、启动保护、缺相、堵转等----- */
    Fault_Detection();
//        Fault_Overcurrent(&mcCurVarible);
/* -----LED灯显示----- */
/* -----通过LED灯闪烁的次数反馈错误状态----- */
//        LED_Display();
/* -----启停测试的时候不通过调速方式给开关信号----- */
/* -----电机调速模式----- */
#if (SPEED_MODE == PWMMODE) // PWM调速模式
    {
        /* -----PWM捕获处理----- */
        PWMInputCapture();
    }
#elif (SPEED_MODE == SREFMODE)
    {
        /* -----模拟调速----- */
        VSPSample();
    }
#elif (SPEED_MODE == NONEMODE) // 直接上电运行模式
    {
        mcSpeedRamp.FlagONOFF = motor.state; // 手动设置为0
#if (Motor_Control_Mode == SPEED_LOOP_CONTROL)
        {
            mcSpeedRamp.TargetValue = _Q15(motor.targetSpeed / MOTOR_SPEED_BASE); // 用户设置转速
        }
#elif (Motor_Control_Mode == POWER_LOOP_CONTROL)
        {
            mcSpeedRamp.TargetValue = Motor_Min_Power;
        }
#elif (Motor_Control_Mode == CURRENT_LOOP_CONTROL)
        {
            mcSpeedRamp.TargetValue = Motor_Min_Current;
        }
#endif
    }
#elif (SPEED_MODE == KEYMODE)
    {
        /* -----按键调速----- */
        mcSpeedRamp.FlagONOFF = 1;
        KeyScan();
    }
#elif (SPEED_MODE == ONOFFTEST)
    {
        if (mcFaultSource == FaultNoSource)
        {
            ONOFF_Starttest();
        }
    }
#endif

    /* -----睡眠模式----- */
    //        Sleepmode();

    /* -----电机状态机的时序处理----- */
    if (mcFocCtrl.State_Count > 0)
    {
        mcFocCtrl.State_Count--;
    }

    if (BEMFDetect.BEMFTimeCount > 0)
    {
        BEMFDetect.BEMFTimeCount--;
    }

    if (RSDDetect.RSDCCWSBRCnt > 0)
    {
        RSDDetect.RSDCCWSBRCnt--;
    }

    if (mcFocCtrl.Brake_Count > 0)
    {
        mcFocCtrl.Brake_Count--;
    }

    if (mcSpeedRamp.MotorOnFilter > 0)
    {
        mcSpeedRamp.MotorOnFilter--;
    }

    if (mcSpeedRamp.MotorOffFilter > 0)
    {
        mcSpeedRamp.MotorOffFilter--;
    }

    /* -----电机启动爬坡函数处理----- */
    StarRampDealwith();

    /* -----自定义函数入口 ------*/
    MyTaskLoop();
}
