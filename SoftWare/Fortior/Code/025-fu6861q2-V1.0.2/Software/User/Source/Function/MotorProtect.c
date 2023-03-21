/*  --------------------------- (C) COPYRIGHT 2020 Fortiortech ShenZhen -----------------------------
    File Name      : MotorProtect.c
    Author         : Fortiortech  Appliction Team
    Version        : V1.0
    Date           : 2020-08-19
    Description    : This file contains MotorProtect function used for Motor Control.
    ----------------------------------------------------------------------------------------------------
                                       All Rights Reserved
    ------------------------------------------------------------------------------------------------- */

#include <FU68xx_2.h>
#include <Myproject.h>

FaultVarible          xdata   mcFaultDect;

CurrentVarible        xdata   mcCurVarible;
ProtectVarible        xdata   mcProtectTime;

/**
 * @brief      电机过热保护
 */   
void Fault_OverHeat(FaultVarible * h_Fault)
{
    if (mcFaultSource != FaultNoSource )
    {
        return;
    }
    
    if (PIN_HEAT == 0)
    {
        if (mcFaultDect.OverHeatCnt > 20)
        {
            mcFaultDect.OverHeatCnt = 0;
            mcFaultSource = FaultOverHeat;
        }
        else
        {
            mcFaultDect.OverHeatCnt++;
        }
    }
    else
    {
        if (mcFaultDect.OverHeatCnt > 0)
        {
            mcFaultDect.OverHeatCnt--;
        }
    }
}


/**
 * @brief      过压欠压检测
 */   
void Fault_OverUnderVoltage(void)
{
    /* -----过压保护----- */
    if (mcFaultSource == FaultNoSource)                                                     // 程序无其他保护下
    {
        if (mcFocCtrl.mcDcbusFlt > OVER_PROTECT_VALUE)                                      // 母线电压大于过压保护值时，计数，超过20次，判断为过压保护，关闭输出;反之，计数器慢慢减
        {
            mcFaultDect.OverVoltDetecCnt++;
            
            if (mcFaultDect.OverVoltDetecCnt > 500)                                          // 不可以太短 顺风的时候电压过冲导致过压
            {
                mcFaultDect.OverVoltDetecCnt = 0;
                mcFaultSource = FaultOverVoltage;
            }
        }
        else
        {
            if (mcFaultDect.OverVoltDetecCnt > 0)
            {
                mcFaultDect.OverVoltDetecCnt--;
            }
        }
        
        /* -----欠压保护----- */
        if (mcFocCtrl.mcDcbusFlt < UNDER_PROTECT_VALUE)
        {
            mcFaultDect.UnderVoltDetecCnt++;
            
            if (mcFaultDect.UnderVoltDetecCnt > 10)
            {
                mcFaultDect.UnderVoltDetecCnt = 0;
                mcFaultSource = FaultUnderVoltage;
            }
        }
        else
        {
            if (mcFaultDect.UnderVoltDetecCnt > 0)
            {
                mcFaultDect.UnderVoltDetecCnt--;
            }
        }
    }
}


/**
 * @brief      1、软件过流保护
 */ 
void Fault_Overcurrent(void)
{
    if ((mcState == mcRun) || (mcState == mcStart))                                         
    {
        mcCurVarible.Abs_ia = Abs_F16(FOC__IA);
        mcCurVarible.Abs_ib = Abs_F16(FOC__IB);
        mcCurVarible.Abs_ic = Abs_F16(FOC__IC);
        
        if (mcCurVarible.Abs_ia > mcCurVarible.Max_ia)                    // 此部分既用于软件过流保护，又用于缺相保护
        {
            mcCurVarible.Max_ia = mcCurVarible.Abs_ia;
        }
        
        if (mcCurVarible.Abs_ib > mcCurVarible.Max_ib)
        {
            mcCurVarible.Max_ib = mcCurVarible.Abs_ib;
        }
        
        if (mcCurVarible.Abs_ic > mcCurVarible.Max_ic)
        {
            mcCurVarible.Max_ic = mcCurVarible.Abs_ic;
        }
        
        if ((mcCurVarible.Max_ia >= OverSoftCurrentValue) || (mcCurVarible.Max_ib >= OverSoftCurrentValue) || (mcCurVarible.Max_ic >= OverSoftCurrentValue))
        {
            mcCurVarible.OverCurCnt++;
            mcCurVarible.Max_ia = 0;                                       //最大值会在缺相保护每500ms清零
            mcCurVarible.Max_ib = 0;
            mcCurVarible.Max_ic = 0;
            mcCurVarible.OverCurCntClr = 0;
            
            if (mcCurVarible.OverCurCnt >= OverSoftCurrentTime)
            {
                mcCurVarible.OverCurCnt = 0;
                mcFaultSource = FaultSoftOVCurrent;
            }
        }
        else
        {
            if (++mcCurVarible.OverCurCntClr > OverSoftCurrentClrTime)        //ms，到达时间计数值清零
            {
                mcCurVarible.OverCurCnt = 0;
                mcCurVarible.OverCurCntClr = 0;
            }
        }
    }
}


/**
 * @brief      偏置电压检测
 */
void Fault_GetCurrentOffset(void)
{
    if (mcCurOffset.OffsetFlag == 1)
    {
        #if (AMP0_VHALF == Enable)                                         //有加VHALF偏置，理论值为16383
        {
            #if (Shunt_Resistor_Mode == Single_Resistor)                   //单电阻模式
            {
                if ((mcCurOffset.Iw_busOffset < GetCurrentOffsetValueLow) || (mcCurOffset.Iw_busOffset > GetCurrentOffsetValueHigh))
                {
                    mcFaultSource = FaultGetOffset;
                }
            }
            #elif (Shunt_Resistor_Mode == Double_Resistor)                 //双电阻模式
            {
                if ((mcCurOffset.IuOffset < GetCurrentOffsetValueLow) || (mcCurOffset.IuOffset > GetCurrentOffsetValueHigh)
                    || (mcCurOffset.IvOffset < GetCurrentOffsetValueLow) || (mcCurOffset.IvOffset > GetCurrentOffsetValueHigh))
                {
                    mcFaultSource = FaultGetOffset;
                }
            }
            #elif (Shunt_Resistor_Mode == Three_Resistor)                  //三电阻模式
            {
                if ((mcCurOffset.IuOffset < GetCurrentOffsetValueLow) || (mcCurOffset.IuOffset > GetCurrentOffsetValueHigh)
                    || (mcCurOffset.IvOffset < GetCurrentOffsetValueLow) || (mcCurOffset.IvOffset > GetCurrentOffsetValueHigh)
                    || (mcCurOffset.Iw_busOffset < GetCurrentOffsetValueLow) || (mcCurOffset.Iw_busOffset > GetCurrentOffsetValueHigh))
                {
                    mcFaultSource = FaultGetOffset;
                }
            }
            #endif
        }
        #else                                                              //没加VHALF偏置,理论值在0
        {
            #if (Shunt_Resistor_Mode == Single_Resistor)                   //单电阻模式
            {
                if (mcCurOffset.Iw_busOffset > GetCurrentOffsetValue)
                {
                    mcFaultSource = FaultGetOffset;
                }
        
            }
            #elif (Shunt_Resistor_Mode == Double_Resistor)                 //双电阻模式
            {
                if ((mcCurOffset.IuOffset > GetCurrentOffsetValue) || (mcCurOffset.IvOffset > GetCurrentOffsetValue))
                {
                    mcFaultSource = FaultGetOffset;
                }
            }
            #elif (Shunt_Resistor_Mode == Three_Resistor)                  //三电阻模式
            {
                if ((mcCurOffset.IuOffset > GetCurrentOffsetValue) || (mcCurOffset.IvOffset > GetCurrentOffsetValue) || (mcCurOffset.Iw_busOffset > GetCurrentOffsetValue))
                {
                    mcFaultSource = FaultGetOffset;
                }
            }
            #endif
        }
        #endif
    }
}


/**
 * @brief      电机堵转检测
 */
void Fault_Stall(void)
{
    if (mcState == mcRun)
    {
        if (mcFaultDect.StallDelayCnt < 15000)
        {
            mcFaultDect.StallDelayCnt ++;
        }
        else
        {
        }
        
        /* -----方法1，在2s后判断反电动势太小 或  当反电动势太小，转速太大 ----- */
        if (((mcFocCtrl.EsValue < Stall_DectEsValue1)  && (mcFaultDect.StallDelayCnt > Stall_Delay_DectTime))
            || (((FOC__EOME > Motor_Stall_Speed) && (mcFocCtrl.EsValue < Stall_DectEsValue2))))
        {
            mcFaultDect.StallDectEs++;
            
            if (mcFaultDect.StallDectEs >= Stall_Protect_Time)
            {
                mcFaultDect.StallDectEs = 0;
                mcFaultSource = FaultStall;
                mcProtectTime.StallFlag  =  1;
            }
        }
        else
        {
            if ( mcFaultDect.StallDectEs > 0)
            {
                mcFaultDect.StallDectEs--;
            }
        }
        
        /* -----方法 2，判断速度低于堵转最小值或者超过堵转最大值 ----- */
        if (((mcFocCtrl.SpeedFlt < Motor_Stall_Min_Speed) && (mcFaultDect.StallDelayCnt > Stall_Delay_DectTime)) || (mcFocCtrl.SpeedFlt > Motor_Stall_Max_Speed))
        {
            mcFaultDect.StallDectSpeed++;
            
            if (mcFaultDect.StallDectSpeed >= Stall_Protect_Time)
            {
                mcFaultDect.StallDectSpeed = 0;
                mcFaultSource = FaultStall;
                mcProtectTime.StallFlag = 2;
            }
        }
        else
        {
            if (mcFaultDect.StallDectSpeed > 0)
            {
                mcFaultDect.StallDectSpeed--;
            }
        }
        
        /* -----方法3，长时间在CtrlMode=0状态 ----- */
        if (mcFocCtrl.CtrlMode == 0)                                                        //
        {
            mcFaultDect.StallDectFocmode++;
            
            if (mcFaultDect.StallDectFocmode >= FOCMode_DectTime)
            {
                mcFaultDect.StallDectFocmode = 0;
                mcFaultSource = FaultStall;
                mcProtectTime.StallFlag = 3;
            }
        }
        
        //区分启动跟堵转
        if (mcProtectTime.StallFlag != 0)
        {
            if (mcFaultDect.StallDelayCnt < St_DisTime)
            { mcFaultDect.StallReTime = StartRecoverDelayTime; }        //启动恢复时间
            else
            { mcFaultDect.StallReTime = StallRecoverDelayTime; }        //堵转恢复时间
        }
        else
        {
        }
    }
}


/**
 * @brief      电机缺相检测
 */
void Fault_phaseloss(void)
{
    if (mcState == mcRun)
    {
        mcFaultDect.Lphasecnt++;
        
        if (mcFaultDect.Lphasecnt > 500)            //500ms检查一次
        {
            mcFaultDect.Lphasecnt = 0;
            
            if (((mcCurVarible.Max_ia > (mcCurVarible.Max_ib * PhaseLossTimes)) || (mcCurVarible.Max_ia > (mcCurVarible.Max_ic * PhaseLossTimes))) && (mcCurVarible.Max_ia > PhaseLossCurrentValue))
            {
                mcFaultDect.AOpencnt++;
            }
            else
            {
                if (mcFaultDect.AOpencnt > 0)
                {
                    mcFaultDect.AOpencnt --;
                }
            }
            
            if (((mcCurVarible.Max_ib > (mcCurVarible.Max_ia * PhaseLossTimes)) || (mcCurVarible.Max_ib > (mcCurVarible.Max_ic * PhaseLossTimes))) && (mcCurVarible.Max_ib > PhaseLossCurrentValue))
            {
                mcFaultDect.BOpencnt++;
            }
            else
            {
                if (mcFaultDect.BOpencnt > 0)
                {
                    mcFaultDect.BOpencnt --;
                }
            }
            
            if (((mcCurVarible.Max_ic > (mcCurVarible.Max_ia * PhaseLossTimes)) || (mcCurVarible.Max_ic > (mcCurVarible.Max_ib * PhaseLossTimes))) && (mcCurVarible.Max_ic > PhaseLossCurrentValue))
            {
                mcFaultDect.COpencnt++;
            }
            else
            {
                if (mcFaultDect.COpencnt > 0)
                {
                    mcFaultDect.COpencnt --;
                }
            }
            
            mcCurVarible.Max_ia = 0;
            mcCurVarible.Max_ib = 0;
            mcCurVarible.Max_ic = 0;
            
            if (mcFaultDect.AOpencnt > 1 || mcFaultDect.BOpencnt > 1 || mcFaultDect.COpencnt > 1)
            {
                mcFaultSource = FaultLossPhase;
            }
        }
    }
}


/**
 * @brief      过温检测
 */
void Fault_Temperature(void)
{
    if (mcFocCtrl.mcADCTemperature < OVER_Temperature)
    {
        mcFaultDect.TemperCnt++;
        
        if (mcFaultDect.TemperCnt > TemperatureProtectTime)
        {
            mcFaultDect.TemperCnt = 0;
            mcFaultDect.TemperRecover = 0;
            mcFaultSource = FaultOverTemperature;
        }
    }
    else
    {
        mcFaultDect.TemperCnt = 0;
    }
}


/**
 * @brief      电机超速检测
 */
void Fault_OverSpeed(void)
{
    if (mcState == mcRun)
    {
        if (mcFocCtrl.SpeedFlt > Motor_Over_Speed)
        {
            mcFaultDect.OverSpeedCnt++;
            
            if (mcFaultDect.OverSpeedCnt > OVER_SpeedDetectTime)                                              
            {
                mcFaultDect.OverSpeedCnt = 0;
                mcFaultDect.OverSpeedCntRecover = 0;
                mcFaultSource = FaultOverSpeed;
            }
        }
        else
        {
            mcFaultDect.OverSpeedCnt = 0;
        }
    }
}


/**
 * @brief      保护清零，错误保护恢复
 */
void Fault_Recovery(void)
{
    if (mcState == mcFault)
    {
        #if (CurrentRecoverEnable)
        {
            /* -----过流保护恢复----- */
            if (((mcFaultSource == FaultSoftOVCurrent) || (mcFaultSource == FaultHardOVCurrent)) && (mcProtectTime.CurrentProtectTimes < OverCurrentRecoverTime))
            {
                mcFaultDect.CurrentRecoverCnt++;
                
                if (mcFaultDect.CurrentRecoverCnt >= OverCurrentRecoverDelayTime)
                {
                    mcFaultDect.CurrentRecoverCnt = 0;
                    mcProtectTime.CurrentProtectTimes++;
                    mcFaultSource = FaultNoSource;
                }
            }
        }
        #endif
        #if (VoltageRecoverEn)
        {
            /* -----过压欠压保护恢复----- */
            if (((mcFaultSource == FaultUnderVoltage) || (mcFaultSource == FaultOverVoltage) || (mcFaultSource == FaultLVW)))
            {
                if ((mcFocCtrl.mcDcbusFlt < OVER_RECOVER_VALUE) && (mcFocCtrl.mcDcbusFlt > UNDER_RECOVER_VALUE))
                {
                    mcFaultDect.VoltRecoverCnt++;
                    
                    if (mcFaultDect.VoltRecoverCnt > VoltageRecoverDelayTime)
                    {
                        mcFaultSource = FaultNoSource;
                        mcFaultDect.VoltRecoverCnt = 0;
                    }
                }
                else
                {
                    mcFaultDect.VoltRecoverCnt = 0;
                }
            }
        }
        #endif
        #if (SPEED_MODE != ONOFFTEST)
        {
            #if (StallRecoverEn)
            {
                /* -----堵转保护恢复 ----- */
                if ((mcFaultSource == FaultStall) && (mcProtectTime.StallTimes < StallRecoverTime))
                {
                    mcFaultDect.StallReCount++;
                    
                    if (mcFaultDect.StallReCount >= mcFaultDect.StallReTime)
                    {
                        mcFaultDect.StallReCount = 0;
                        mcProtectTime.StallTimes++;
                        mcFaultSource = FaultNoSource;
                    }
                }
                else
                {
                    mcFaultDect.StallReCount = 0;
                }
            }
            #endif
        }
        #endif
        #if (SPEED_MODE != ONOFFTEST)
        {
            #if (PhaseRecoverEn)
            {
                /* -----缺相保护恢复 ----- */
                if ((mcFaultSource == FaultLossPhase) && (mcProtectTime.LossPHTimes < PhaseRecoverTime))
                {
                    mcFaultDect.mcLossPHRecCount++;
                    
                    if (mcFaultDect.mcLossPHRecCount >= PhaseRecoverDelayTime)
                    {
                        mcFaultDect.AOpencnt = 0;
                        mcFaultDect.BOpencnt = 0;
                        mcFaultDect.COpencnt = 0;
                        mcProtectTime.LossPHTimes++;
                        mcFaultSource = FaultNoSource;
                    }
                }
                else
                {
                    mcFaultDect.mcLossPHRecCount = 0;
                }
            }
            #endif
        }
        #endif
        #if (TempRecoverEn)
        {
            /* -----过温保护恢复 ----- */
            if ((mcFaultSource == FaultOverTemperature) && (mcFocCtrl.mcADCTemperature > UNDER_Temperature) && (mcProtectTime.TempProtectTimes < TempRecoverTime))
            {
                mcFaultDect.TemperRecover++;
                
                if (mcFaultDect.TemperRecover > TempRecoverDelayTime)
                {
                    mcFaultDect.TemperRecover = 0;
                    mcProtectTime.TempProtectTimes++;
                    mcFaultSource = FaultNoSource;
                }
            }
            else
            {
                mcFaultDect.TemperRecover = 0;
            }
        }
        #endif
    }
}


/** 
 * @brief     故障检测，扫描周期默认为1ms
 * @warning   所有故障检测只进行故障码赋值，禁止在状态机以外地方进行电机状态跳转
 */
void Fault_Detection(void)
{
    Fault_Overcurrent();               // 软件过流保护

    #if (VoltageProtectEnable)
    {
        Fault_OverUnderVoltage();      // 电压保护
    }
    #endif
    #if (StallProtectEnable)
    {
        Fault_Stall();                 // 堵转保护
    }
    #endif
    #if (PhaseLossProtectEnable)
    {
        Fault_phaseloss();             // 缺相保护
    }
    #endif
    #if (TemperatureProtectEnable)
    {
        Fault_Temperature();           // 温度保护
    }
    #endif
    #if (OverSpeedProtectEnable)
    {
        Fault_OverSpeed();             // 超速保护
    }
    #endif
    Fault_Recovery();                  // 保护恢复
}
