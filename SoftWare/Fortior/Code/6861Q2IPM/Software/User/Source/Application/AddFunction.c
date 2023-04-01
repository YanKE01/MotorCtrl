/* --------------------------- (C) COPYRIGHT 2020 Fortiortech ShenZhen -----------------------------
    File Name      : AddFunction.c
    Author         : Fortiortech  Appliction Team
    Version        : V1.0
    Date           : 2020-09-16
    Description    : This file contains .C file function used for Motor Control.
----------------------------------------------------------------------------------------------------
                                       All Rights Reserved
------------------------------------------------------------------------------------------------- */


/* Includes -------------------------------------------------------------------------------------*/
#include <FU68xx_2.h>
#include <Myproject.h>

/* Private variables ---------------------------------------------------------*/
FaultStateType             mcFaultSource;
FaultVarible       idata   mcFaultDect;
CurrentVarible     idata   mcCurVarible;

OUTLOOP            xdata   speedPICtrl;
FOCCTRL            xdata   mcFocCtrl;
ADCSample          xdata   adcSampleValue;
MCLedDisplay       xdata   mcLedDisplay;
MCRAMP             xdata   mcSpeedRamp;
SLEEPMODE          xdata   sleepSet;
PWMFREQINPUTTRPE   idata   mcPWMFreqInputCtrl;

uint16             xdata   mcIbusFlt;
uint32             xdata   mcPowerlpf;
uint16             xdata   mcPower;
int16                      speedRef;
/* -------------------------------------------------------------------------------------------------
    Function Name  : PWMScan
    Description    :
    Date           : 2020-09-16
    Parameter      : None
------------------------------------------------------------------------------------------------- */
void PWMScan(void)
{
    mcPWMFreqInputCtrl.pwmINHigh = TIM3__ARR + 1;
    mcPWMFreqInputCtrl.flagPWMINHighDuty = 1;
}
/* -------------------------------------------------------------------------------------------------
    Function Name  : PWMIN_Init
    Description    : PWM检测参数初始化
    Date           : 2020-09-16
    Parameter      : None
------------------------------------------------------------------------------------------------- */
void PWMIN_Init(void)
{
    mcPWMFreqInputCtrl.pwmINHigh      = 0;
    mcPWMFreqInputCtrl.pwmINPeriod    = TIM3_Fre * CapPWMFilterNUM;
    mcPWMFreqInputCtrl.pwmINFre       = 0;
}
/* -------------------------------------------------------------------------------------------------
    Function Name  : OutLoopParameterSet
    Description    : 速度环和功率环参数初始化
    Date           : 2020-09-16
    Parameter      : None
------------------------------------------------------------------------------------------------- */
void OutLoopParameterSet(void)
{
    memset(&speedPICtrl, 0, sizeof(OUTLOOP));                                                      // SpeedControl clear
    mcFocCtrl.speedLoopTime    = SPEED_LOOP_TIME;
    mcFocCtrl.speedRampTime    = SPEEDRAMPTIME;
    mcSpeedRamp.incValue       = SPEEDRAMPSTARTINC;
    mcSpeedRamp.decValue       = SPEEDRAMPDEC;
    #if (MTPAENABLE)
    {
        speedPICtrl.extOut         = Mtpa.MtpaTx;
    }
    #else
    {
        speedPICtrl.extOut         = IQ_Start_CURRENT;
        mcFocCtrl.isRef            = speedPICtrl.extOut;
    }
    #endif
    PI1_UKH = speedPICtrl.extOut;
}

/* -------------------------------------------------------------------------------------------------
    Function Name  : Abs_F16
    Description    : 对变量取16位的绝对值
    Date           : 2020-09-16
    Parameter      : h_Fault: [输入]
------------------------------------------------------------------------------------------------- */
uint16 Abs_F16(int16 value)
{
    if (value < 0)
    {
        return (- value);
    }
    else
    {
        return (value);
    }
}

/* -------------------------------------------------------------------------------------------------
    Function Name  : Speed_response
    Description    : 速度响应函数，可根据需求加入控制环，如恒转矩控制、恒转速控制、恒功率控制
    Date           : 2020-09-16
    Parameter      : None
------------------------------------------------------------------------------------------------- */
void Speed_response(void)
{
    if ((mcState == mcRun) || (mcState == mcStop))
    {
        if (mcFocCtrl.runStateCnt < ReturnOilTime)                                                 // MotorStartHoldTime目标转速为启动转速
        {
            if (mcSpeedRamp.flagONOFF)                                                             // PWM开机
            { mcSpeedRamp.targetValue = Motor_ReturnOil_Speed; }                                    // 上油时间内维持上油转速，补偿由于主频引起的转速误差。
            
            if (++mcFocCtrl.runStateCnt > 2000)                                                    // 表明电机已经正常启动，要保证启动2S内如果电机异常能被保护。
            {
                mcFocCtrl.runStateFlag = 1;                                                        // 表明电机已经成功启动
                mcFocCtrl.softCurrentValueTemp = OverSoftCurrentValue ;                        // 运行时的软件过流值改小为启动的软件过流值的一半
                #if (MTPAENABLE)
                {
                    PI1_UKMAX = MTPASOUTMAX_RUN;
                    PI1_UKMIN = MTPASOUTMIN_RUN;
                }
                #else
                {
                    PI1_UKMAX = SOUTMAX_RUN;
                    PI1_UKMIN = SOUTMIN_RUN;
                }
                #endif
            }
            else
            {
                mcFocCtrl.runStateFlag = 0;
            }
        }
        else                                                                                       // 如果达到上油转速后，将起动速度环增量变为运行速度环增量
        {
            mcSpeedRamp.incValue    = SPEEDRAMPINC;                                                // 运行速度环增量
            
            if (mcFocCtrl.overPowerFlag == 0)
            {
                mcSpeedRamp.decValue    = SPEEDRAMPDEC;
            }
        }
        
        switch (mcFocCtrl.ctrlMode)
        {
            case 0:
            {
                if (mcFocCtrl.speedFlt > Motor_Loop_Speed)
                {
                    mcFocCtrl.ctrlMode = 1;
                    mcSpeedRamp.actualValue = Motor_Start_Min_Speed;
                    OutLoopParameterSet();
                }
            }
            break;
            
            case 1:
            {
                #if (SPEED_MODE == 1)
                {
                    mcFocCtrl.mcIqref = FOC_IQREF;
                    
                    if (FOC_IQREF < QOUTVALUE)
                    {
                        mcFocCtrl.mcIqref += QOUTINC;
                        
                        if (mcFocCtrl.mcIqref > QOUTVALUE)
                        {
                            mcFocCtrl.mcIqref = QOUTVALUE;
                        }
                        
                        FOC_IQREF = mcFocCtrl.mcIqref;
                    }
                    else if (FOC_IQREF > QOUTVALUE)
                    {
                        mcFocCtrl.mcIqref -= QOUTDEC;
                        
                        if (mcFocCtrl.mcIqref < QOUTVALUE)
                        {
                            mcFocCtrl.mcIqref = QOUTVALUE;
                        }
                        
                        FOC_IQREF = mcFocCtrl.mcIqref;
                    }
                }
                #else
                {

                
                    if (++mcFocCtrl.speedRampTime > SPEEDRAMPTIME)
                    {
                        mcFocCtrl.speedRampTime = 0;
                        mc_ramp(&mcSpeedRamp);                                                     // 外环速度爬坡或减速。每SpeedRampTime执行一次
                    }
                
                    if (++mcFocCtrl.speedLoopTime > SPEED_LOOP_TIME)                               // 外环调节周期
                    {
                        mcFocCtrl.speedLoopTime = 0;
                        #if (MTPAENABLE)
                        {
                            Mtpa.MtpaTx = HW_One_PI(mcSpeedRamp.actualValue - mcFocCtrl.speedFlt);
                        }
                        #else
                        {
                            mcFocCtrl.mcIsref = HW_One_PI(mcSpeedRamp.actualValue - mcFocCtrl.speedFlt);
                            #if (MotorFiledWeakenEn)
                            {
                                FileWeakenControl();
                                //                                mcFocCtrl.IqRef = mcFiledWeaken.WeakenRunIqRef;
                                //                                mcFocCtrl.IdRef = mcFiledWeaken.WeakenRunIdRef;
                            }
                            #else
                            {
                                mcFocCtrl.IqRef = mcFocCtrl.mcIsref;
                                mcFocCtrl.IdRef = 0;
                            }
                            #endif
                        }
                        #endif
                    }
                }
                #endif
            }
            break;
        }
    }
}
/* -------------------------------------------------------------------------------------------------
    Function Name  : LED_Display
    Description    : LED灯显示
    Date           : 2020-09-16
    Parameter      : None
------------------------------------------------------------------------------------------------- */
void LED_Display(void)
{
    switch (mcFaultSource)
    {
        case FaultNoSource:
            SetLEDPin;                                                                             // 低电平点亮，高电平灭
            break;
            
        case FaultHardOVCurrent:                                                                   // 硬件过流保护闪烁1次
            Led_OnOff(&mcLedDisplay, 1);
            break;
            
        case FaultOverVoltage:                                                                     // 过压保护闪烁2次
            Led_OnOff(&mcLedDisplay, 2);
            break;
            
        case FaultUnderVoltage:                                                                    // 欠压保护闪烁3次
            Led_OnOff(&mcLedDisplay, 3);
            break;
            
        case FaultStart:                                                                           // 启动失步闪烁4次
            Led_OnOff(&mcLedDisplay, 4);
            break;
            
        case FaultStall:                                                                           // 运行失步保护闪烁5次
            Led_OnOff(&mcLedDisplay, 5);
            break;
            
        case  FaultIbusOffset:                                                                     // 母线偏置电压错误保护闪烁6次
            Led_OnOff(&mcLedDisplay, 6);
            break;
            
        case FaultSoftOVCurrent:                                                                   // 软件过流保护闪烁7次
            Led_OnOff(&mcLedDisplay, 7);
            break;
            
        case FaultLossPhase:                                                                       // 缺相保护闪烁9次
            Led_OnOff(&mcLedDisplay, 9);
            break;
            
        case  FaultOverPower:                                                                      // 功率保护闪烁13次
            Led_OnOff(&mcLedDisplay, 10);
            break;
            
        default:
            break;
    }
}

/* -------------------------------------------------------------------------------------------------
    Function Name  : Led_OnOff
    Description    : LED灯的闪烁
    Date           : 2020-09-16
    Parameter      : hLedDisplay: [输入]
**           htime: [输入]
------------------------------------------------------------------------------------------------- */
void Led_OnOff(MCLedDisplay * hLedDisplay, uint8 htime)
{
    hLedDisplay -> counttime = 2 * htime * 400 + 1500;
    
    if (++hLedDisplay -> ledCount < hLedDisplay -> counttime)
    {
        if (hLedDisplay -> count < 400)
        {
            hLedDisplay -> count++;
        }
        else if ((hLedDisplay -> count >= 400) && (hLedDisplay -> count < 401))
        {
            hLedDisplay -> count = 0;
            LEDPinONOFF;
            hLedDisplay->ledTimCot++;
        }
        else
            ;
            
        if (hLedDisplay -> ledTimCot >= 2 * htime)
        {
            hLedDisplay -> count = 402;
            SetLEDPin;
        }
    }
    else if (hLedDisplay -> ledCount >= hLedDisplay -> counttime)
    {
        hLedDisplay -> ledCount = 0;
        hLedDisplay -> ledTimCot = 0;
        hLedDisplay -> count = 0;
    }
}
/* -------------------------------------------------------------------------------------------------
    Function Name  : mc_ramp
    Description    : 速度爬坡
    Date           : 2020-09-16
    Parameter      : hSpeedramp: [输入]
------------------------------------------------------------------------------------------------- */
void mc_ramp(MCRAMP * hSpeedramp)
{
    if (--hSpeedramp -> delayCount < 0)
    {
        hSpeedramp -> delayCount = hSpeedramp -> delayPeriod;
        
        if (hSpeedramp -> actualValue < hSpeedramp -> targetValue)
        {
            if (hSpeedramp -> actualValue + hSpeedramp -> incValue < hSpeedramp -> targetValue)
            {
                hSpeedramp -> actualValue += hSpeedramp -> incValue;
            }
            else
            {
                hSpeedramp -> actualValue = hSpeedramp -> targetValue;
            }
        }
        else
        {
            if (hSpeedramp -> actualValue - hSpeedramp -> decValue > hSpeedramp -> targetValue)
            {
                hSpeedramp -> actualValue -= hSpeedramp -> decValue;
            }
            else
            {
                hSpeedramp -> actualValue = hSpeedramp -> targetValue;
            }
        }
    }
}

/* -------------------------------------------------------------------------------------------------
    Function Name  : HW_PI_Control
    Description    : 速度环PI
    Date           : 2020-09-16
    Parameter      : PIPara: [输入]
------------------------------------------------------------------------------------------------- */
void HW_PI_Control(OUTLOOP * PIPara)
{
    PIPara -> extErr = PIPara -> extRef - PIPara -> extFed;
    PI_EK =  PIPara -> extErr;                                                                                              //填入本次EK 误差值
    SetBit(PI_LPF_CR, PISTA);                                                                                                       // Start PI
    _nop_();  _nop_();  _nop_();  _nop_();  _nop_();
    PI_UK += (((PIPara -> extKP) >> 12) + 1);
    PIPara->extOut = PI_UK;                                                                                                 // 补偿PI输出误差
}

/* -------------------------------------------------------------------------------------------------
    Function Name  : LPFFunction
    Description    : 低通滤波
    Date           : 2020-09-16
    Parameter      : Xn1: [输入]
**           Xn0: [输入]
**           K: [输入]
------------------------------------------------------------------------------------------------- */
//int16 LPFFunction(int16 Xn1, int16 Xn0, int8 K)
//{
//  LPF_K = K;
//  LPF_X = Xn1;
//  LPF_Y = Xn0;
//  SetBit(PI_LPF_CR, LPFSTA);
//  _nop_();_nop_();_nop_();_nop_();_nop_();
//  return LPF_Y;
//}

/* -------------------------------------------------------------------------------------------------
    Function Name  : Sleepmode
    Description    : 睡眠模式测试
    Date           : 2020-09-16
    Parameter      : None
------------------------------------------------------------------------------------------------- */
void Sleepmode(void)
{
    if (!mcSpeedRamp.flagONOFF)
    { sleepSet.sleepDelayCout++; }
    else
    { sleepSet.sleepDelayCout = 0; }
    
    if (sleepSet.sleepDelayCout >= 30000)                                                           // 最大65530，若要再大，需改数据类型
    {
        sleepSet.sleepDelayCout = 0;
        mcSpeedRamp.targetValue = 0;
        MOE     = 0;
        ClrBit(DRV_CR, FOCEN);  //关闭FOC
        ClrBit(AMP_CR, AMP0EN);
        ClrBit(TIM3_CR1, T3EN);                                                                    // 使能计数器，启动计数
        Sleepmode_Init();                                                                          // 使能外部中断1, P11位外部中断输入硬件
        sleepSet.sleepFlag = 1;
        SetBit(PCON, STOP);
    }
}

/* -------------------------------------------------------------------------------------------------
    Function Name  : StarRampDealwith
    Description    : 启动参数爬坡函数
    Date           : 2020-09-16
    Parameter      : None
------------------------------------------------------------------------------------------------- */
void StarRampDealwith(void)
{
    if (mcState == mcRun)
    {
        //        if(mcFocCtrl.state_Count == 1400)
        //        {
        //            #if (EstimateAlgorithm == PLL)
        //            {
        //                FOC_KSLIDE    = OBSE_PLLKP_GAIN2;
        //                FOC_EKLPFMIN  = OBSE_PLLKI_GAIN2;
        //            }
        //            #endif
        //
        //            FOC_EKP = OBSW_KP_GAIN2;                                                             // 估算器里的PI的KP
        //            FOC_EKI   = OBSW_KI_GAIN2;                                                               // 估算器里的PI的KI
        //        }
        //        else if(mcFocCtrl.state_Count == 1200)
        //        {
        //            #if (EstimateAlgorithm == PLL)
        //            {
        //                FOC_KSLIDE    = OBSE_PLLKP_GAIN3;
        //                FOC_EKLPFMIN  = OBSE_PLLKI_GAIN3;
        //            }
        //            #endif
        //
        //            FOC_EKP = OBSW_KP_GAIN3;                                                             // 估算器里的PI的KP
        //            FOC_EKI   = OBSW_KI_GAIN3;                                                               // 估算器里的PI的KI
        //        }
        //        else if(mcFocCtrl.state_Count == 1100)
        //        {
        //            #if (EstimateAlgorithm == PLL)
        //            {
        //                FOC_KSLIDE    = OBSE_PLLKP_GAIN4;
        //                FOC_EKLPFMIN  = OBSE_PLLKI_GAIN4;
        //            }
        //            #endif
        FOC_EKP = OBSW_KP_GAIN4;                                                               // 估算器里的PI的KP
        FOC_EKI = OBSW_KI_GAIN4;                                                               // 估算器里的PI的KI
        //        }
        //        else;
    }
}


/* -------------------------------------------------------------------------------------------------
    Function Name  : SW_One_PI
    Description    : 功率环PI函数
    Date           : 2020-09-16
    Parameter      : feedbackvalue: [输入]
**           referencevalue: [输入]
------------------------------------------------------------------------------------------------- */
int16 SW_One_PI(int16 feedbackvalue, int16 referencevalue, MPIDTypeDef * PID)
{
    static int16 IncTemp;
    static int32 outtemp;
    PID->err = referencevalue - feedbackvalue;
    IncTemp = PID->kp * (PID->err - PID->last_err)
        + PID->ki *  PID->err;
    outtemp = PID->lastout + IncTemp;
    PID->last_err = PID->err;
    
    if (outtemp >  PID->outMax)
    {
        outtemp =  PID->outMax;
    }
    
    if (outtemp <  PID->outMin)
    {
        outtemp =  PID->outMin;
    }
    
    PID->lastout = outtemp;
    return (int16)outtemp;
}
/* -------------------------------------------------------------------------------------------------
    Function Name  : RealPowerCal
    Description    : 计算输入功率的标幺值
    Date           : 2020-09-16
    Parameter      : None
------------------------------------------------------------------------------------------------- */
void RealPowerCal(void)
{
    static idata uint32 tempPower;
    tempPower = mcFocCtrl.mcDcbusFlt;
    tempPower = tempPower * mcFocCtrl.mcIbusFlt;
   
}

//void mcTorqueCompensationInit(void)
//{
//    memset(&mcTorqueCompensation,0, sizeof(MCTorqueCompensation));                                                            // mcFieldWeaken变量清零
//
//    mcTorqueCompensation.MotorStartHoldTime = ReturnOilTime;
//
//    mcTorqueCompensation.IqCompensateEnterSpeed = IQCOMPENSATEENTERSPEED;
//    mcTorqueCompensation.IqCompensateExitSpeed = IQCOMPENSATEEXITSPEED;
//
//    mcTorqueCompensation.IqCompensateAngleLimitMax = IQCOMPENSATEANGLELIMITMAX;
//    mcTorqueCompensation.IqCompensateAngleLimitMin = IQCOMPENSATEANGLELIMITMIN;
//
//    mcTorqueCompensation.IqCompensateAngleDelta0 = IQCOMPENSATEANGLELDELTA0;
//    mcTorqueCompensation.IqCompensateAngleDelta1 = IQCOMPENSATEANGLELDELTA1;
//    mcTorqueCompensation.IqCompensateAngleDelta2 = IQCOMPENSATEANGLELDELTA2;
//    mcTorqueCompensation.IqCompensateAngleDelta3 = IQCOMPENSATEANGLELDELTA3;
//
//    mcTorqueCompensation.IqPeakValueMax = IQPEAKVALUEMAX;
//    mcTorqueCompensation.IqPeakValueMin = IQPEAKVALUEMIN;
//
//    mcTorqueCompensation.IqPeakValueDelta0 = IQPEAKVALUEDELTA0;
//    mcTorqueCompensation.IqPeakValueDelta1 = IQPEAKVALUEDELTA1;
//    mcTorqueCompensation.IqPeakValueDelta2 = IQPEAKVALUEDELTA2;
//    mcTorqueCompensation.IqPeakValueDelta3 = IQPEAKVALUEDELTA3;
//
//    mcTorqueCompensation.IqCompensateAngleDelta = mcTorqueCompensation.IqCompensateAngleDelta0;
//    mcTorqueCompensation.IqCompensatePeakDelta = mcTorqueCompensation.IqPeakValueDelta0;
//    mcTorqueCompensation.IqCompensateInitialAngle1 = _Q15(90.0 / 180);//90
//    mcTorqueCompensation.IqCompensatePeakValueInitial = IQCOMPENSATEPEAKVALUEINITIAL;
//    mcTorqueCompensation.IqCompensatePeakValueTemp = mcTorqueCompensation.IqCompensatePeakValueInitial;//1.8

//    mcTorqueCompensation.IqCompensateAngleOrPeakValueAgainAdjustSpeedErr = IQCOMPENSATEFINISHSPEEDERR1;
//    mcTorqueCompensation.IqCompensateAngleOrPeakValueOkSpeedErr = IQCOMPENSATEFINISHSPEEDERR2;
//
//    mcTorqueCompensation.IqCompensateAngleOrPeakValueAdjustDelayTime = IQCOMPENSATEANGLEORPEAKVALUEADJUSTDELAYTIME;
//}
//void mcTorqueCompensationTest(void)
//{
//    static uint16 delay = 0;
//    int32 MachineCycleSpeedTemp = 0;
//
//    if(++delay == 477)
//    {
//        T_SPEED_DATA2[0] = mcTorqueCompensation.IqCompensateAngleDeltaChangeFlag + 0x30;
//        T_SPEED_DATA2[1] = mcTorqueCompensation.IqCompensatePeakDeltaChangeFlag + 0x30;
//    }
//    if(delay == 478)
//    {
//        UART_SendData(T_SPEED_DATA2[0]);
//    }
//    if(delay == 479)
//    {
//        UART_SendData(T_SPEED_DATA2[1]);
//    }
//    if(delay == 480)
//    {
//        UART_SendData(T_SPEED_DATA2[2]);
//    }
//    if(delay == 481)
//    {
//        UART_SendData(T_SPEED_DATA2[3]);
//    }
//    if(delay == 482)
//    {
//        UART_SendData(T_SPEED_DATA2[4]);
//    }

//    if(delay == 483)//显示在确定最大转矩区后需要调整的角度
//    {
//     //   MachineCycleSpeedTemp = (int32)mcTorqueCompensation.IqCompensateInitialAngle1 * 180;
//        if(MachineCycleSpeedTemp < 0)
//        {
//            MachineCycleSpeedTemp = -MachineCycleSpeedTemp;
//            T_SPEED_DATA1[0] = '-';
//        }else
//        {
//            T_SPEED_DATA1[0] = '+';
//        }

//        MachineCycleSpeedTemp = (MachineCycleSpeedTemp >> 15);

//        T_SPEED_DATA1[1] = (MachineCycleSpeedTemp / 100) %10 + 0x30;
//        T_SPEED_DATA1[2] = (MachineCycleSpeedTemp / 10) %10 + 0x30;
//        T_SPEED_DATA1[3] = MachineCycleSpeedTemp  %10 + 0x30;
//    }
//
//    if(delay == 484)
//    {
//        UART_SendData(T_SPEED_DATA1[0]);
//    }
//    if(delay == 485)
//    {
//        UART_SendData(T_SPEED_DATA1[1]);
//    }
//    if(delay == 486)
//    {
//        UART_SendData(T_SPEED_DATA1[2]);
//    }
//    if(delay == 487)
//    {
//        UART_SendData(T_SPEED_DATA1[3]);
//    }
//    if(delay == 488)
//    {
//        UART_SendData(T_SPEED_DATA1[4]);
//    }
//    if(delay == 489)
//    {
//        UART_SendData(T_SPEED_DATA1[5]);
//    }
//    if(delay == 490)
//    {
//        UART_SendData(T_SPEED_DATA1[6]);
//    }

//
//    if(delay == 491)//显示一个机械周期里最大转速和最小转速的差
//    {
////        MachineCycleSpeedTemp = (int32)mcTorqueCompensation.HighTorqueAndLowTorqueSpeedMaxErrFlt * MOTOR_SPEED_BASE;
////        MachineCycleSpeedTemp = MachineCycleSpeedTemp >> 15;
////
//        if(MachineCycleSpeedTemp == 0)
//        {
//            MachineCycleSpeedTemp = 0;
//        }
//        T_SPEED_DATA0[0] = MachineCycleSpeedTemp / 1000 + 0x30;
//        T_SPEED_DATA0[1] = (MachineCycleSpeedTemp / 100) %10 + 0x30;
//        T_SPEED_DATA0[2] = (MachineCycleSpeedTemp / 10) %10 + 0x30;
//        T_SPEED_DATA0[3] = MachineCycleSpeedTemp  %10 + 0x30;
//    }
//
//    if(delay == 492)
//    {
//        UART_SendData(T_SPEED_DATA0[0]);
//    }
//    if(delay == 493)
//    {
//        UART_SendData(T_SPEED_DATA0[1]);
//    }
//    if(delay == 494)
//    {
//        UART_SendData(T_SPEED_DATA0[2]);
//    }
//    if(delay == 495)
//    {
//        UART_SendData(T_SPEED_DATA0[3]);
//    }
//    if(delay == 496)
//    {
//        UART_SendData(T_SPEED_DATA0[4]);
//    }
//    if(delay == 497)
//    {
//        UART_SendData(T_SPEED_DATA0[5]);
//    }
//    if(delay == 498)
//    {
//        UART_SendData(T_SPEED_DATA0[6]);
//    }
//    if(delay == 499)
//    {
//        UART_SendData(T_SPEED_DATA0[7]);
//    }
//    if(delay == 500)
//    {
//        delay = 0;
//        UART_SendData(T_SPEED_DATA0[8]);
//    }
//}
/*---------------------------------------------------------------------------*/
/* Name     :   void Fault_Recovery(void)
/* Input    :   NO
/* Output   :   NO
/* Description: 保护恢复函数
/*---------------------------------------------------------------------------*/
uint32 FaultRecoverCnt = 0;
uint32 FaultVoltageRecoverCnt = 0;
uint8 FaultRecovertimeCnt = 0;
uint16 FaultFaultStartCnt = 0;
void Fault_Recovery(void)
{
			if((mcFaultSource == FaultStart)&&(FaultRecovertimeCnt <=2))//3次启动恢复
			{
				FaultFaultStartCnt++;
				if(FaultFaultStartCnt > 4000)
						{
								FaultRecovertimeCnt++;
								FaultFaultStartCnt = 0;
								mcFaultSource=FaultNoSource;
						}
			}
	
    // 堵转保护/失速保护/硬件过流(短路)/缺相保护状态下，故障代码保持5s后，自动清除错误标志，重新接收命令尝试运行
    if ((mcFaultSource == FaultStall) || (mcFaultSource == FaultHardOVCurrent) || (mcFaultSource == FaultLossPhase))
    {
        FaultRecoverCnt++;
        
        if (FaultRecoverCnt > 5000)
        {
            FaultRecoverCnt = 0;
            mcFaultSource = FaultNoSource;
        }
    }
    // 过欠压保护及母线电压异常，故障代码保持3s后，需等母线电压恢复正常后，才可自动清除错误标志，重新接收命令尝试运行
    else if ((mcFaultSource == FaultOverVoltage) || (mcFaultSource == FaultUnderVoltage))
    {
        FaultVoltageRecoverCnt++;
        
        if (FaultVoltageRecoverCnt >= 300)
        {
            FaultVoltageRecoverCnt = 300;
            
            if ((mcFocCtrl.mcDcbusFlt < OVER_RECOVER_VALUE) && (mcFocCtrl.mcDcbusFlt > UNDER_RECOVER_VALUE))
            {
                FaultVoltageRecoverCnt = 0;
                mcFaultSource = FaultNoSource;
            }
        }
    }
}



/*  -------------------------------------------------------------------------------------------------
    Function Name  : HW_One_PI
    Description    : PI
    Date           : 2020-08-08
    Parameter      : Xn1: [输入]
    ------------------------------------------------------------------------------------------------- */
int16 HW_One_PI(int16 Xn1)
{
    PI1_EK =  Xn1;                                                                               //填入EK
    SMDU_RunBlock(1, PI);
    return PI1_UKH;
}



/*  -------------------------------------------------------------------------------------------------
    Function Name  : LPFFunction
    Description    : 低通滤波函数
    Date           : 2020-08-08
    Parameter      : Xn1: [输入]
**                   Xn0: [输入]
**                   K: [输入]
    ------------------------------------------------------------------------------------------------- */
int16 LPFFunction(int16 Xn1, int16 Xn0, int8 K)
{
    LPF0_K = K << 8;
    LPF0_X = Xn1;
    LPF0_YH = Xn0;
    SMDU_RunBlock(0, LPF);
    return LPF0_YH;
}

/**
 * @brief        默认1ms周期服务函数，运行信号采样，调速信号处理，闭环控制，故障检测,ATO爬坡函数
 *               该函数运行于大循环中，由SYSTICK定时器间隔1ms触发运行。
 * @date         2022-07-14
 */
void TickCycle_1ms(void)
{

   SetBit(ADC_CR, ADCBSY);
        
        /* -----速度滤波、反电动势滤波----- */
        if ((mcState != mcInit) && (mcState != mcReady))
        {
            mcFocCtrl.speedFlt = LPFFunction(FOC__EOME, mcFocCtrl.speedFlt, 30);                   // 注意低通滤波器系数范围为0---127
            mcFocCtrl.esValue  = LPFFunction(FOC__ESQU, mcFocCtrl.esValue, 30);
            mcFocCtrl.udFlt  = LPFFunction(FOC__UD, mcFocCtrl.udFlt, 30);
            mcFocCtrl.uqFlt  = LPFFunction(FOC__UQ, mcFocCtrl.uqFlt, 30);
            #if (LowSpeedObserverEnable)
            LowSpeedObserver.LowSpeedObserverOmegaFlt = LPFFunction(LowSpeedObserver.LowSpeedObserverOmega, LowSpeedObserver.LowSpeedObserverOmegaFlt, 30);
            #endif
        }
        else
        {
            mcFocCtrl.speedFlt = 0;
            mcFocCtrl.esValue = 0;
            mcFocCtrl.udFlt = 0;
            mcFocCtrl.uqFlt = 0;
            LowSpeedObserver.LowSpeedObserverOmegaFlt = 0;
        }

        /* -----DCbus/Ibus的采样获取值并滤波----- */
        adcSampleValue.adcDcbus = ADC2_DR << 3;
        mcFocCtrl.mcDcbusFlt    = LPFFunction(adcSampleValue.adcDcbus, mcFocCtrl.mcDcbusFlt, 30);
        adcSampleValue.adcIbus  = ADC5_DR << 3;
        adcSampleValue.adcIbus = (adcSampleValue.adcIbus < mcCurOffset.ibusOffset) ? 0 : (adcSampleValue.adcIbus -   mcCurOffset.ibusOffset);
        mcFocCtrl.mcIbusFlt     = LPFFunction(adcSampleValue.adcIbus, mcFocCtrl.mcIbusFlt,  50);
        //              mcFocCtrl.mcIbusFlt += ((adcSampleValue.adcIbus - mcFocCtrl.mcIbusFlt)>> 3 );
        #if (MTPAENABLE)//最大转矩电流比控制
        {
            if ((mcState == mcStart) || (mcState == mcRun) || (mcState == mcStop))
            {
                MtpaControl();
                mcFocCtrl.IqRef = Mtpa.MtpaIq;
                mcFocCtrl.IdRef = Mtpa.MtpaId;
            }
        }
        #endif
        /* -----电机转速控制----- */
        Speed_response();
        FOC_IQREF = mcFocCtrl.IqRef;
        FOC_IDREF = mcFocCtrl.IdRef;

        /* -----故障保护函数功能，如过欠压保护、启动保护、缺相、堵转等----- */
        Fault_Overcurrent(&mcCurVarible); //28个us
        Fault_Detection();
        Fault_Recovery();
        /* -----LED故障指示----- */
        LED_Display();                                                                             //LED灯显示
        /* -----睡眠模式----- */
        #if (Sleep_Enable)
        {
            Sleepmode();
        }
        #endif
        /* -----电机启动爬坡函数处理----- */
        StarRampDealwith();
        
        /* -----电机状态机的时序处理----- */
        if (mcFocCtrl.state_Count > 0)
        {
            mcFocCtrl.state_Count--;
        }
        
        if (mcFocCtrl.powerLimitDelay > 0)
        {
            mcFocCtrl.powerLimitDelay--;
        }
        
        if (mcFocCtrl.powerRecoverDelay > 0)
        {
            mcFocCtrl.powerRecoverDelay--;
        }
    }      
