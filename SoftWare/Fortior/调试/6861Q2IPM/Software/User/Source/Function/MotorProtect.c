/* --------------------------- (C) COPYRIGHT 2020 Fortiortech ShenZhen -----------------------------
    File Name      : MotorProtect.c
    Author         : Fortiortech  Appliction Team
    Version        : V1.0
    Date           : 2020-09-16
    Description    : This file contains .C file function used for Motor Control.
----------------------------------------------------------------------------------------------------
                                       All Rights Reserved
------------------------------------------------------------------------------------------------- */
#include <FU68xx_2.h>
#include <Myproject.h>

/* -------------------------------------------------------------------------------------------------
    Function Name  : FaultProcess
    Description    : 保护处理函数，关闭FOC输出，同时将状态变为mcFault
    Date           : 2020-09-16
    Parameter      : None
------------------------------------------------------------------------------------------------- */
void FaultProcess(void)
{
    DRV_CMR &= 0xFFC0;                                                                             // 六个MOS的输出关闭，不然在断电快速上电再进行预充电开始会出现电流尖峰。
    MOE     = 0;
    ClrBit(DRV_CR, FOCEN);                                                                         // 关闭FOC
}


/* -------------------------------------------------------------------------------------------------
    Function Name  : Fault_OverUnderVoltage
    Description    : 过压欠压保护函数：程序每5ms判断一次，母线电压大于过压保护值时，计数器加一，计数器值超过10次，判断为过压保护，关闭输出;反之，计数器慢慢减
                     同理，欠压保护。
                     电机过欠压保护状态下，母线电压恢复到欠压恢复值以上，过压恢复值以下时，计数器加一，超过100次后，恢复。根据档位信息来决定恢复到哪个状态。
    Date           : 2020-09-16
    Parameter      : h_Fault: [输入/出]
------------------------------------------------------------------------------------------------- */
void Fault_OverUnderVoltage(FaultVarible * h_Fault)
{
    /* -----过压保护----- */
    if (mcFaultSource == FaultNoSource)
    {
        if (mcFocCtrl.mcDcbusFlt > OVER_PROTECT_VALUE)                                             // 母线电压大于过压保护值时，计数，超过20次，判断为过压保护，关闭输出;反之，计数器慢慢减
        {
            h_Fault -> overVoltDetecCnt ++;
            
            if (h_Fault -> overVoltDetecCnt > 10)                                                  // 检测50ms
            {
                mcFaultSource = FaultOverVoltage;
                FaultProcess();
            }
        }
        else
        {
            h_Fault -> overVoltDetecCnt = 0;
        }
        
        /* -----欠压保护----- */
        if (mcFocCtrl.mcDcbusFlt < UNDER_PROTECT_VALUE)
        {
            h_Fault -> underVoltDetecCnt ++;
            
            if (h_Fault -> underVoltDetecCnt > 10)                                                 // 检测50ms
            {
                mcFaultSource = FaultUnderVoltage;
                FaultProcess();
            }
        }
        else
        {
            h_Fault -> underVoltDetecCnt = 0;
        }
    }
}

/* -------------------------------------------------------------------------------------------------
    Function Name  : Fault_Overcurrent
    Description    : 电机运行或者启动时，当三相中某一相最大值大于OverCurrentValue，则OverCurCnt加1。
                     连续累加3次，判断为软件过流保护。执行时间约600us。
    Date           : 2020-09-16
    Parameter      : h_Cur: [输入/出]
------------------------------------------------------------------------------------------------- */
void Fault_Overcurrent(CurrentVarible * h_Cur)
{
    if ((mcState == mcRun) || (mcState == mcStart))                                                // check over current in rum and open mode
    {
        h_Cur -> abs_ia = Abs_F16(FOC__IA);
        h_Cur -> abs_ib = Abs_F16(FOC__IB);
        h_Cur -> abs_ic = Abs_F16(FOC__IC);
        
        if (h_Cur -> abs_ia > h_Cur -> max_ia)                                                     // 此部分既用于软件过流保护，又用于缺相保护
        {
            h_Cur -> max_ia = h_Cur -> abs_ia;
        }
        
        if (h_Cur -> abs_ib > h_Cur -> max_ib)
        {
            h_Cur -> max_ib = h_Cur -> abs_ib;
        }
        
        if (h_Cur -> abs_ic > h_Cur -> max_ic)
        {
            h_Cur -> max_ic = h_Cur -> abs_ic;
        }
        
        if ((h_Cur -> max_ia >= mcFocCtrl.softCurrentValueTemp) || (h_Cur -> max_ib >= mcFocCtrl.softCurrentValueTemp) || (h_Cur -> max_ic >= mcFocCtrl.softCurrentValueTemp))
        {
            h_Cur -> overCurCnt++;
            
            if (h_Cur -> overCurCnt >= 3)
            {
                h_Cur -> max_ia = 0;
                h_Cur -> max_ib = 0;
                h_Cur -> max_ic = 0;
                h_Cur -> overCurCnt = 0;
                mcFaultSource = FaultSoftOVCurrent;
                FaultProcess();
            }
        }
        else
        {
            if (h_Cur -> overCurCnt > 0)
            {
                h_Cur -> overCurCnt --;
            }
        }
    }
}

/* -------------------------------------------------------------------------------------------------
    Function Name  : Fault_Start
    Description    : 启动保护函数，电机运行状态下，电机在前5s估算转速达到堵转保护值或者5s后反电动势值太低(此方法未验证)
                     或4s内还在CtrlMode状态，即速度低于MOTOR_LOOP_RPM，程序判断为启动失败，电机停机。
                     当程序判断为启动失败后，若重启次数少于或等于5次，程序立即进入校准状态，等待重启。
    Date           : 2020-09-16
    Parameter      : h_Fault: [输入/出]
------------------------------------------------------------------------------------------------- */
void Fault_Start(FaultVarible * h_Fault)
{
    if (mcState == mcRun)
    {
        /* -----5s内速度大于最大速度，同时反电动势值低于一定值----- */
        if (h_Fault -> startSpeedCnt <= 1000)
        {
            h_Fault -> startSpeedCnt ++;
            
            if ((mcFocCtrl.speedFlt > Motor_Max_Speed) && (mcFocCtrl.esValue < StartProtect1EsValue))
            {
                if (h_Fault -> startSpeedAndESCnt ++ >= 50)
                {
                    mcFaultSource = FaultStart;
                    FaultProcess();
                }
            }
            else
            {
                if (h_Fault -> startSpeedAndESCnt > 0)
                {
                    h_Fault -> startSpeedAndESCnt --;
                }
            }
        }
        
        /* -----前6s，等待1.5s后，开始判断Es，如果超过一定次数，则失败----- */
        if (h_Fault -> startEsCnt <= 1200)
        {
            h_Fault -> startEsCnt ++;
            
            if (++h_Fault -> startDelay >= 300)
            {
                h_Fault -> startDelay = 300;
                
                if (mcFocCtrl.esValue < StartProtect2EsValue)
                {
                    if (++h_Fault -> startESCount >= 50)                                             //50次Es小于设定值，启动失败
                    {
                        mcFaultSource = FaultStart;
                        FaultProcess();
                    }
                }
                else
                {
                    if (h_Fault -> startESCount > 0)
                    { h_Fault -> startESCount --; }
                }
            }
            
            #if (LowSpeedObserverEnable)//低速观测器启动保护
            {
                if (LowSpeedObserver.LowSpeedObserverToAoObserverFlag == 0)        //
                {
                    h_Fault -> startSMOCnt++;
                    
                    if (h_Fault -> startSMOCnt >= 30)//30*5 =150，150ms
                    {
                        h_Fault -> startSMOCnt = 0;
                        mcFaultSource = FaultStart;
                        FaultProcess();
                    }
                }
            }
            #endif
        }
        else
        {
            h_Fault -> startESCount = 0;
        }
    }
}


/* -------------------------------------------------------------------------------------------------
    Function Name  : Fault_Stall
    Description    : 堵转保护函数，有三种保护方式，
                     第一种，
                     第二种，电机运行状态下，延迟5s判断，估算速度绝对值超过堵转速度连续70次；
                     第三种，电机运行状态下，当U,V两相电流绝对值大于堵转电流保护值连续20次；
                     当以上三种的任何一种保护触发时，电机停机，程序判断为堵转保护；
                     当堵转保护状态下，U相采集值低于堵转恢复值时，若堵转次数小于或等于堵转重启次数8次，
                     程序延迟mcStallRecover重新启动，进行校准状态。
    Date           : 2020-09-16
    Parameter      : h_Fault: [输入/出]
**           h_Cur: [输入/出]
------------------------------------------------------------------------------------------------- */
void Fault_Stall(FaultVarible * h_Fault, CurrentVarible * h_Cur)
{
    if (mcState == mcRun)
    {
        if (h_Fault -> stallDelayCnt <= 1000)                                                      // 启动后延时5s判断是否堵转保护
        {
            h_Fault -> stallDelayCnt ++;
        }
        else
        {
            /* -----当反电动势太小 或当 转速太大但反电动势却很小时进入保护----- */
            if ((mcFocCtrl.esValue < StallProtect1EsValue)
                || ((FOC__EOME > StallProtec2tSpeedValue)
                    && (mcFocCtrl.esValue < StallProtec2tEsValue)))
            {
                if (++h_Fault -> stallDectEs >= 70)                                                  // 判断满足条件达到设置次数，保护动作
                {
                    mcFaultSource = FaultStall;
                    FaultProcess();
                }
            }
            else
            {
                if ( h_Fault -> stallDectEs > 0)
                { h_Fault -> stallDectEs --; }
            }
            
            /* -----判断速度低于堵转最小值或者超过堵转最大值----- */
            if ((mcFocCtrl.speedFlt < StallProtec3MinSpeed)
                || (mcFocCtrl.speedFlt > StallProtec3MaxSpeed))
            {
                if (++h_Fault -> stallDectSpeed >= 70)      // 判断满足条件达到设置次数，保护动作
                {
                    mcFaultSource = FaultStall;
                    FaultProcess();
                }
            }
            else
            {
                if (h_Fault -> stallDectSpeed > 0)
                { h_Fault -> stallDectSpeed --; }
            }
        }
    }
}


/* -------------------------------------------------------------------------------------------------
    Function Name  : Fault_phaseloss
    Description    : 缺相保护函数，当电机运行状态下，300ms取三相电流的最大值，
                     1.5s判断各相电流最大值，若存在两相电流值大于一定值，而第三相电流值却非常小，则判断为缺相保护，电机停机；
    Date           : 2020-09-16
    Parameter      : h_Fault: [输入/出]
------------------------------------------------------------------------------------------------- */

void Fault_phaseloss(FaultVarible * h_Fault)
{
    static uint8 phaselosstime = 60;//缺相保护时间 //60*5=300ms  300ms判断一次
    
    if ((mcState == mcRun) || (mcState == mcStart))
    {
        #if (LowSpeedObserverEnable)//避免低速观测器启动保护优先于缺相保护触发
        {
            if (LowSpeedObserver.LowSpeedObserverToAoObserverFlag == 0) //低速观测器未启动完成
            { phaselosstime = 10; }
            else
            {
                phaselosstime = 60;
            }
        }
        #endif
        
        if (++h_Fault -> lphasecnt > phaselosstime)
        {
            h_Fault -> lphasecnt = 0;
            
            if (((mcCurVarible.max_ia > (mcCurVarible.max_ib * 2)) || (mcCurVarible.max_ia > (mcCurVarible.max_ic * 2))) && (mcCurVarible.max_ia > PhaseLossCurrentValue1))
            {
                h_Fault -> aOpencnt ++;
            }
            else
            {
                if (h_Fault -> aOpencnt > 0)
                { h_Fault -> aOpencnt --; }
            }
            
            if (((mcCurVarible.max_ib > (mcCurVarible.max_ia * 2)) || (mcCurVarible.max_ib > (mcCurVarible.max_ic * 2))) && (mcCurVarible.max_ib > PhaseLossCurrentValue1))
            {
                h_Fault -> bOpencnt ++;
            }
            else
            {
                if (h_Fault -> bOpencnt > 0)
                { h_Fault -> bOpencnt --; }
            }
            
            if (((mcCurVarible.max_ic > (mcCurVarible.max_ia * 2)) || (mcCurVarible.max_ic > (mcCurVarible.max_ib * 2))) && (mcCurVarible.max_ic > PhaseLossCurrentValue1))
            {
                h_Fault -> cOpencnt ++;
            }
            else
            {
                if (h_Fault -> cOpencnt > 0)
                { h_Fault -> cOpencnt --; }
            }
            
            if (((mcCurVarible.max_ia < PhaseLossCurrentValue2) && (mcCurVarible.max_ib < PhaseLossCurrentValue2) && (mcCurVarible.max_ic < PhaseLossCurrentValue2)) && (mcFocCtrl.esValue > 5000)) //解决缺三相或两相不报缺相保护的情况。
            {
                if (h_Fault -> abcOpencnt++ > 10)
                {
                    mcFaultSource = FaultLossPhase;
                    FaultProcess();
                }
            }
            else
            {
                h_Fault->abcOpencnt = 0;
            }
            
            mcCurVarible.max_ia = 0;
            mcCurVarible.max_ib = 0;
            mcCurVarible.max_ic = 0;
            
            if (h_Fault -> aOpencnt > 1 || h_Fault->bOpencnt > 1 || h_Fault -> cOpencnt > 1)
            {
                mcFaultSource = FaultLossPhase;
                FaultProcess();
            }
        }
    }
}


/* -------------------------------------------------------------------------------------------------
    Function Name  : Fault_Detection
    Description    : 保护函数，因保护的时间响应不会很高，采用分段处理，每5个定时器中断执行一次对应的保护
                     常见保护有过欠压、过温、堵转、启动、缺相等保护，调试时，可根据需求，一个个的调试加入。
    Date           : 2020-09-16
    Parameter      : None
------------------------------------------------------------------------------------------------- */
void Fault_Detection(void)
{
    if (++mcFaultDect.segment >= 5)
    {
        mcFaultDect.segment = 0;
    }
    
    if (mcFaultDect.segment == 0)
    {
    }
    else if (mcFaultDect.segment == 1)
    {
        #if (VoltageProtectEnable == 1)                                                            // 过压保护使能
        {
            Fault_OverUnderVoltage(&mcFaultDect);
        }
        #endif
    }
    else if (mcFaultDect.segment == 2)
    {
        #if (StartProtectEnable == 1)                                                              // 启动失步保护使能
        {
            Fault_Start(&mcFaultDect);
        }
        #endif
    }
    else if (mcFaultDect.segment == 3)
    {
        #if (StallProtectEnable == 1)                                                              // 运行失步保护使能
        {
            Fault_Stall(&mcFaultDect, &mcCurVarible);
        }
        #endif
    }
    else if (mcFaultDect.segment == 4)
    {
        #if (PhaseLossProtectEnable == 1)                                                          // 缺相保护使能
        {
            Fault_phaseloss(&mcFaultDect);
        }
        #endif
    }
}
