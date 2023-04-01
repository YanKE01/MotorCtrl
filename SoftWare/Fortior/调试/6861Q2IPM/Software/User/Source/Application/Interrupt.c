/* --------------------------- (C) COPYRIGHT 2020 Fortiortech ShenZhen -----------------------------
    File Name      : Interrupt.c
    Author         : Fortiortech  Appliction Team
    Version        : V1.0
    Date           : 2020-09-27
    Description    : This file contains .C file function used for Motor Control.
----------------------------------------------------------------------------------------------------
                                       All Rights Reserved
------------------------------------------------------------------------------------------------- */
/* Includes -------------------------------------------------------------------------------------*/
#include <FU68xx_2.h>
#include <Myproject.h>
uint16 xdata spidebug[4] = { 0 };
extern uint8 data g_1mTick;                   ///< 1ms滴答信号，每隔1ms在SYSTICK定时器被置1，需在大循环使用处清零

/* -------------------------------------------------------------------------------------------------
    Function Name  : CMP_ISR
    Description    : 硬件比较器过流保护，关断输出，中断优先级最高
    Date           : 2020-09-27
    Parameter      : None
------------------------------------------------------------------------------------------------- */
void CMP_ISR(void) interrupt 7
{
    if (ReadBit(CMP_SR, CMP3IF))
    {
        mcFaultSource = FaultHardOVCurrent;                                                        // 硬件过流保护
        ClrBit(CMP_SR, CMP3IF);
    }
}
/* -------------------------------------------------------------------------------------------------
    Function Name  : TIM3_INT
    Description    : Capture PWM ，中断优先级第二，高于FOC中断，用于PWM调速
    Date           : 2020-09-27
    Parameter      : None
------------------------------------------------------------------------------------------------- */
//void TIM3_INT(void) interrupt 9
//{
//    if(ReadBit(TIM3_CR1, T3IP))
//    {
//        ClrBit(TIM3_CR1, T3IP);
//        PWMScan();
//    }
//    if(ReadBit(TIM3_CR1, T3IF))
//    {
//        ClrBit(TIM3_CR1, T3IF);

//        ClrBit(TIM3_CR1, T3EN);

//        TIM3__ARR = 0;
//        TIM3__DR = CapPWMFilterNUM;

//        mcPWMFreqInputCtrl.pwmINHigh = 0;
//        mcPWMFreqInputCtrl.pwmINFre = 0;

//        SetBit(TIM3_CR1, T3EN);

//        mcPWMFreqInputCtrl.flagPWMINHighDuty = 1;
//    }
//}
/* -------------------------------------------------------------------------------------------------
    Function Name  : FOC_INT
    Description    : FOC中断(Drv中断),每个载波周期执行一次，用于处理响应较高的程序，中断优先级第二。DCEN开了就会产生中断。
    Date           : 2020-09-27
    Parameter      : None
------------------------------------------------------------------------------------------------- */
void FOC_INT(void) interrupt 3
{
    if (ReadBit(DRV_SR, DCIF))
    {
        
        #if (LowSpeedObserverEnable)
        {
            if ((mcState == mcRun)&&(LowSpeedObserver.LowSpeedObserverToAoObserverFlag == 0))
            {
                LowSpeedObserverFunction();

            }
        }
        #endif
        #if (CurrentDecoupledControlEnable)
        {
            if (LowSpeedObserver.LowSpeedObserverToAoObserverFlag)
            {
                mcCurrentDecoupledControl.Omega = mcFocCtrl.speedFlt;//Q15格式
            }
            else
            {
                mcCurrentDecoupledControl.Omega = LowSpeedObserver.LowSpeedObserverOmegaFlt;//Q15格式
            }
            
            CurrentDecoupledControlFunction();
        }
        #endif
        mcTorqueCompensation.MotorTargetSpeed = mcSpeedRamp.actualValue;
        #if (IQCOMPENSATEENBLE)
        {
            if (mcState == mcRun || mcState == mcStop)
            {
                if ((mcTorqueCompensation.MotorTargetSpeed < mcTorqueCompensation.TorqueCompensateEnterSpeedValue) && (mcFocCtrl.runStateCnt == ReturnOilTime) ) //回油时间到后再进行补偿判断
                {
                    mcTorqueCompensation.TorqueCompensatePeakKValueRef = TorqueCompensatePeakKEnd;
                    
                    if (mcSpeedRamp.actualValue > OBS_K3T_SPEED_END)
                    {
                        mcTorqueCompensation.TorqueCompensatePeakKValueRef = TorqueCompensatePeakKEnd;
                    }
                    else if (mcSpeedRamp.actualValue > OBS_K3T_SPEED_START)
                    {
                        MuiltS1_H_MDU_0((mcSpeedRamp.actualValue - OBS_K3T_SPEED_START), TorqueCompensatePeakK_K, mcTorqueCompensation.TorqueCompensatePeakKValueRef); //将目标转速转换为机械角度增量
                        mcTorqueCompensation.TorqueCompensatePeakKValueRef = TorqueCompensatePeakKStart + (mcTorqueCompensation.TorqueCompensatePeakKValueRef << 3);
                    }
                    else
                    {
                        mcTorqueCompensation.TorqueCompensatePeakKValueRef = TorqueCompensatePeakKStart;
                    }
                }
                else if (mcTorqueCompensation.MotorTargetSpeed > mcTorqueCompensation.TorqueCompensateExitSpeedValue)
                {
                    mcTorqueCompensation.TorqueCompensatePeakKValueRef = 0;
                }
                
                if ( mcSpeedRamp.actualValue <   _Q15(2500.0   / MOTOR_SPEED_BASE)  )
                { MCTorqueCompensationFunction(); }
            }
        }
        #endif
        #if (EstimateAlgorithm == PLL)
        {
            mcFocCtrl.speedEOME = FOC__EOME;
            mcFocCtrl.theta = FOC__ETHETA;
            
            if (mcFocCtrl.runStateCnt > 500)
            {
                if ((mcFocCtrl.theta < 910) && (mcFocCtrl.theta > -910))
                {
                    ClrBit(FOC_CR2, ESEL);
                    FOC_KSLIDE    = OBS_KSLIDE;
                    FOC_EKLPFMIN    = OBS_EA_KS;
                }
            }
        }
        #endif

        /********************SPI配置****************************/
        spidebug[0] = FOC__IC << 2; // FOC_IQREF<<2;//   FOC_IQREF<<2;//  MachineCycleSpeedTemp_read <<10;//   mcTorqueCompensation.TorqueCompensateIqCurrentValue;//mcTorqueCompensation.IqCompensateValue;//mcTorqueCompensation.HighTorqueAndLowTorqueSpeedMaxErr<<6;//FOC_IQREF<<2;// mcFocCtrl.iqRef<<2;//mcTorqueCompensation.IqCompensateAngleValue;//      mcTorqueCompensation.IqCompensatePeakValue<<3;//mcFocCtrl.iqRef<<3;
        spidebug[1] = mcFocCtrl.IqRef << 2; //  FOC__IQ<<2;     mcTorqueCompensation.TorqueCompensateInitTheta;//  FOC__EOME<<6;//mcTorqueCompensation.IqCompensateValue<<2;//  mcTorqueCompensation.IqCompensateInitialAngle1;//mcTorqueCompensation.HighTorqueAndLowTorqueSpeedMaxErr<<6;//mcTorqueCompensation.ElectricalCycleCnt<<10;//   mcTorqueCompensation.IqCompensatePeakValue<<3;//mcHall.TargetTheta;
        spidebug[2] = FOC__THETA;
        spidebug[3] = FOC__IA << 2;
        DRV_SR = (DRV_SR | SYSTIF) & ~(DCIF);
    }
}


/* -------------------------------------------------------------------------------------------------
    Function Name  : TIM_1MS_INT
    Description    : 1ms定时器中断（SYS TICK中断），滴答定时器，默认用于产生1ms定时间隔；在TickCycle_1ms函数中用于处理附加功能，如控制环路响应、各种保护等。中断优先级低于FO中断和FOC中断。
    Date           : 2020-09-27
    Parameter      : None
------------------------------------------------------------------------------------------------- */
void TIM_1MS_INT(void) interrupt 10
{
	
    if (ReadBit(DRV_SR, SYSTIF))
    {
        g_1mTick = 1;
        DRV_SR = (DRV_SR | DCIF) & ~(SYSTIF);    // 清零标志位
    }
}

/* -------------------------------------------------------------------------------------------------
    Function Name  : EXTERN_INT
    Description    : 睡眠唤醒
    Date           : 2020-09-27
    Parameter      : None
------------------------------------------------------------------------------------------------- */
void EXTERN_INT(void) interrupt 2
{
    if (ReadBit(P1_IF, P11))
    {
        if (sleepSet.sleepFlag)
        {
            sleepSet.sleepFlag = 0;
            sleepSet.sleepUpdata = 1;
            EX1 = 0;
        }
        
        ClrBit(P1_IF, P11);                                                                            // 清零P10标志位
    }
}
