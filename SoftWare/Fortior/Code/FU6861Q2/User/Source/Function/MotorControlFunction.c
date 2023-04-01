/**
 * @copyright (C) COPYRIGHT 2022 Fortiortech Shenzhen
 * @file      MotorControlFunction.c
 * @author    Fortiortech  Appliction Team
 * @since     Create:2021-11-07
 * @date      Last modify:2022-07-14
 * @brief    
 */

#include <FU68xx_2.h>
#include <Myproject.h>


RPD_TypeDef             xdata   RPD_Status;
RPD_Param_TypeDef       xdata   RPDPara;
MotorTailWindTypeDef    xdata   TailWindDetect;
BEMFDetect_TypeDef      xdata   BEMFDetect;
CurrentOffset           xdata   mcCurOffset;

/** 
 * @brief      对FOC的相关寄存器进行配置,先清理寄存器，后配置，最后使能
 * @exception  初始化FOC，需要先关闭DRVIVER，对FOC寄存器配置完成后，使能FOC再打开DRVIVER,否则可能导致第一拍电流采样错误
 */
void FOC_Init(void)
{
    /* -----使能FOC ----- */
    ClrBit(DRV_CR, FOCEN);
    SetBit(DRV_CR, FOCEN);
    /* -----配置FOC寄存器 ----- */
    FOC_CR1         = 0;                                                                            // 清零 FOC_CR1
    FOC_CR2         = 0;                                                                            // 清零 FOC_CR2
    FOC_IDREF       = 0;                                                                            // 清零 Id
    FOC_IQREF       = 0;                                                                            // 清零 Iq
    FOC__THETA      = 0;                                                                            // 清零 角度
    FOC_RTHEACC     = 0;                                                                            // 清零 爬坡函数的初始加速度
    FOC__RTHESTEP   = 0;                                                                            //
    FOC__RTHECNT    = 0;                                                                            //
    FOC_THECOMP    = _Q15(0.0 / 180.0);                                                            // SMO 估算补偿角
    FOC_THECOR         = 0x04;                                                                     // 误差角度补偿
    #if (FG_Enable==1)
    FOC_KFG         = FG_Value;
    #endif
    //      SetBit(FOC_CR2, UQD);
    //    SetBit(FOC_CR2, UDD);
    /* -----电流环参数配置 ----- */
    FOC_DMAX            = DOUTMAX;
    FOC_DMIN            = DOUTMIN;
    FOC_QMAX            = QOUTMAX;
    FOC_QMIN            = QOUTMIN;
    /* -----位置估算参数配置 ----- */
    FOC_EK1             = OBS_K1T;
    FOC_EK2             = OBS_K2T;
    FOC_EK3             = OBS_K3T;
    FOC_EK4             = OBS_K4T;

    #if (EstimateAlgorithm == AO)// 自适应估算器模式使能
    {
        SetBit(FOC_CR3, ESCMS);
        SetBit(FOC_CR3, MFP_EN);
        ClrBit(FOC_CR2, ESEL);
        FOC_EKLPFMIN    = OBS_EA_KS;
    }
    #elif (EstimateAlgorithm == SMO)
    {
        ClrBit(FOC_CR2, ESEL);
        FOC_KSLIDE    = OBS_KSLIDE;
        FOC_EKLPFMIN    = OBS_EA_KS;
    }
    #elif (EstimateAlgorithm == PLL)
    {
        SetBit(FOC_CR2, ESEL);
        FOC_KSLIDE      = OBSE_PLLKP_GAIN;
        FOC_EKLPFMIN    = OBSE_PLLKI_GAIN;
    }
    #else
    {
        #error " EstimateAlgorithm  ERR"
    }
    #endif    
    
    FOC_FBASE           = OBS_FBASE;
    FOC_OMEKLPF         = SPEED_KLPF;
    FOC_EBMFK           = OBS_KLPF;
    FOC_TGLI            = PWM_TGLI_LOAD;

    SetBit(FOC_CR1, SVPWMEN);                                                                       // SVPWM模式
    //  /*正反转*/
    //  if(mcFRState.FR==1)                                                                         // 设置F/R
    //  {
    //    SetBit(DRV_CR,DRV_DDIR);
    //  }
    //  else
    //  {
    //    ClrBit(DRV_CR,DRV_DDIR);
    //  }
    #if (FRMODE==1)
    {
        SetBit(DRV_CR, DDIR);                                                                       // 反转标志位
    }
    #endif //end FRMODE
    /* -----过调制 ----- */
    #if (OverModulation == 1)
    {
        SetBit(FOC_CR1, OVMDL);                                                                     // 过调制
    }
    #endif                                                                                          //end OverModulation
    /* -----单电阻采样；需要最小采样窗,FOC_TRGDLY为0，七段式SVPWM方式 ----- */
    #if (Shunt_Resistor_Mode == Single_Resistor)
    {
        SetReg(FOC_CR1, CSM0 | CSM1, 0x00);
        FOC_TRGDLY = 9;                                                                             // 0x0c表示延迟12个clock，提前用反码形式，如0x84表示提前12个clock。
        ClrBit(FOC_CR2, F5SEG);                                                                     // 7段式
        SetReg(CMP_CR1, CMP3MOD0 | CMP3MOD1, 0x00);
        /* -----最小窗口设置，防止溢出处理----- */
        /* -----FOC_TSMIN 需要小于载波周期的1/16 ----- */
        mcFaultDect.TempTSminValue =  PWM_TS_LOAD;
        
        if (mcFaultDect.TempTSminValue < 255)
        {
            FOC_TSMIN = mcFaultDect.TempTSminValue;
        }
        else
        {
            FOC_TSMIN = 255;
        }
    }
    /* -----双电阻采样，可设置死区补偿值，在下降沿结束前开始采样Ia，配置81 ----- */
    #elif (Shunt_Resistor_Mode == Double_Resistor)                                                  
    {
        SetReg(FOC_CR1, CSM0 | CSM1, CSM0);
        FOC_TSMIN = PWM_DT_LOAD;                                                                    // 死区补偿值
        FOC_TRGDLY = 0x85;                                                                          // ADC采样的时刻，采样时刻在计数器零点附近，83为下降沿结束前3个clock采样Ia，与单电阻不同
        /* -----01为上升沿开始后第一个clock开始采样。根据实际情况调整 ----- */
        FOC_TBLO = PWM_DLOWL_TIME;                                                                  //下桥臂最小脉冲，保证采样
        SetReg(CMP_CR1, CMP3MOD0 | CMP3MOD1, 0x00);
        /* -----五段式或七段式选择 ----- */
        #if (SVPMW_Mode == SVPWM_7_Segment)
        {
            ClrBit(FOC_CR2, F5SEG);
        }
        #elif (SVPMW_Mode == SVPWM_5_Segment)
        {
            SetBit(FOC_CR2, F5SEG);
        }
        #endif
        #if (DouRes_Sample_Mode == DouRes_1_Cycle)
        {
            ClrBit(FOC_CR2, DSS);
        }
        #elif (DouRes_Sample_Mode == DouRes_2_Cycle)
        {
            SetBit(FOC_CR2, FOC_DSS);
        }
        #endif                                                                                    
    }
    /* -----三电阻采样 ----- */
    #elif (Shunt_Resistor_Mode == Three_Resistor)                                                   
    {
        SetReg(FOC_CR1, CSM0 | CSM1, CSM0 | CSM1);// 三电阻
        FOC_TSMIN  = PWM_DT_LOAD;                                                                   // 死区补偿值
        FOC_TRGDLY = 06;                                                                            // ADC采样的时刻，采样时刻在计数器零点附近，83为下降沿结束前3个clock采样Ia，与单电阻不同。
        /* -----01为上升沿开始后第一个clock开始采样。根据实际情况调整 ----- */
        SetReg(CMP_CR1, CMP3MOD0 | CMP3MOD1, CMP3MOD0 | CMP3MOD1);
        FOC_TBLO = PWM_OVERMODULE_TIME;                                                             // 过调制电流采样处理的TB脉宽
        /* -----五段式或七段式选择 ----- */
        #if (SVPMW_Mode == SVPWM_7_Segment)
        {
            ClrBit(FOC_CR2, F5SEG);
        }
        #elif (SVPMW_Mode == SVPWM_5_Segment)
        {
            SetBit(FOC_CR2, F5SEG);
        }
        #endif  
        #if (DouRes_Sample_Mode == DouRes_1_Cycle)
        {
            ClrBit(FOC_CR2, DSS);
        }
        #elif (DouRes_Sample_Mode == DouRes_2_Cycle)
        {
            SetBit(FOC_CR2, DSS);
        }
        #endif                                                                                      
    }
    #endif                                                                                          
    /* -----使能电流基准校正 ----- */
    #if (CalibENDIS == Enable)
    {
        if (mcCurOffset.OffsetFlag == 1)
        {
            #if (Shunt_Resistor_Mode == Single_Resistor)                                            // 单电阻校正
            {
                /* -----set ibus current sample offset ----- */
                SetReg(FOC_CR2, CSOC0 | CSOC1, 0x00);
                FOC_CSO = mcCurOffset.Iw_busOffset;                                                 // 写入Ibus的偏置
                
            }
            #elif (Shunt_Resistor_Mode == Double_Resistor)                                          // 双电阻校正
            {
                /* -----set ia, ib current sample offset ----- */
                SetReg(FOC_CR2, CSOC0 | CSOC1, CSOC0);
                FOC_CSO  = mcCurOffset.IuOffset;                                                    // 写入IA的偏置
            
                SetReg(FOC_CR2, CSOC0 | CSOC1, CSOC1);
                FOC_CSO  = mcCurOffset.IvOffset;                                                    // 写入IB的偏置
            
            }
            #elif (Shunt_Resistor_Mode == Three_Resistor)                                           // 三电阻校正
            {
                /* -----set ibus current sample offset ----- */
                SetReg(FOC_CR2, CSOC0 | CSOC1, CSOC0);
                FOC_CSO = mcCurOffset.IuOffset;                                                     // 写入IA的偏置
            
                SetReg(FOC_CR2, CSOC0 | CSOC1, CSOC1);
                FOC_CSO = mcCurOffset.IvOffset;                                                     // 写入IB的偏置
            
                SetReg(FOC_CR2, CSOC0 | CSOC1, 0x00);
                FOC_CSO = mcCurOffset.Iw_busOffset;                                                 // 写入IC的偏置
            }
            #endif                                                                                  //end Shunt_Resistor_Mode
        }
    }
    #endif                                                                                          //end CalibENDIS
    /*  -------------------------------------------------------------------------------------------------
        DRV_CTL：PWM来源选择
        OCS = 0, DRV_COMR
        OCS = 1, FOC/SVPWM/SPWM
        -------------------------------------------------------------------------------------------------*/
    /* -----计数器比较值来源FOC ----- */
    SetBit(DRV_CR, OCS);
}


/** 
 * @brief     预定位，开启此功能启动时候会将电机强拉到设定角度，之后再启动
 */
void Motor_Align(void)
{
    if (McStaSet.SetFlag.AlignSetFlag == 0)
    {
        McStaSet.SetFlag.AlignSetFlag = 1;
        /* -----FOC初始化----- */
        FOC_Init();
        /* -----配置预定位的电流、KP、KI----- */
        //        FOC_IDREF = ID_Align_CURRENT;
        //        FOC_IQREF = IQ_Align_CURRENT;
        //        FOC_DQKP = DQKP_Alignment;
        //        FOC_DQKI = DQKI_Alignment;
        FOC_EKP     = OBSW_KP_GAIN;
        FOC_EKI     = OBSW_KI_GAIN;
        SetBit(FOC_CR2, UQD);
        SetBit(FOC_CR2, UDD);
        #if (Align_Associated_Vol_EN == 0)
        {
            FOC__UQ = _Q15(0.0);
            FOC__UD = UD_Duty;
        }
        #else
        {
            /* -----关联电压，保证所有电压预定位力矩足够且不过大----- */
            mcFocCtrl.TempUDQValue = UD_K * (mcFocCtrl.mcDcbusFlt - UDMIN_Volt_VALUE) + UDMIN;
        
            /* -----防止UDQ定位占空比太大----- */
            if (mcFocCtrl.TempUDQValue < _Q15(0.1))
            {
                FOC__UD =  mcFocCtrl.TempUDQValue;
            }
            else
            {
                FOC__UD =  _Q15(0.1);
            }
        }
        #endif                                                                                      
        /* -----配置预定位角度----- */
        #if (AlignTestMode==1)
        {
            FOC__THETA      = Align_Theta;
        }
        #else
        {
            #if (PosCheckEnable==1)
            {
                FOC__THETA    = mcFocCtrl.mcPosCheckAngle;
            }
            #else
            {
                FOC__THETA      = Align_Theta;
            }
            #endif                                                                                  
        }
        #endif                                                                                       
        /* -----PLL或SMO----- */
        #if (EstimateAlgorithm == SMO  || EstimateAlgorithm == AO)
        {
            FOC__ETHETA   = FOC__THETA - 4096;
        }
        #elif (EstimateAlgorithm == PLL)
        {
            FOC__ETHETA   = FOC__THETA;
        }
        #endif                                                                                    
        TimeCnt = FOC__THETA;
        /* -----使能输出----- */
        DRV_CMR |= 0x3F;                                                                            // U、V、W相输出
        MOE = 1;
    }
}


/** 
 * @brief     静止启动配置函数
 */
void Motor_Open(void)
{
     #if (AlignTestMode==0)
    {
        DRV_CMR |= 0x3F;                                                                            // U、V、W相输出
        MOE = 1;
    }
    #endif
    #if (Open_Start_Mode == Open_Start)
    {
        static uint8 OpenRampCycles;                                                                // 否则定义了没调用，lint会报警告
    }
    #endif
    
    if (McStaSet.SetFlag.StartSetFlag == 0)
    {
        McStaSet.SetFlag.StartSetFlag = 1;
        /* -----启动初始角度赋值----- */
        #if (PosCheckEnable)
        {
            FOC__THETA  = mcFocCtrl.mcPosCheckAngle;                                                // 有初始位置检测，则用初始位置角
        }
        #else
        {
            FOC__THETA  = Align_Theta;                                                              // 无初始位置检测，则用预定位角
        }
        #endif
        /* -----PLL或SMO----- */
        #if (EstimateAlgorithm == SMO  || EstimateAlgorithm == AO)
        {
            FOC__ETHETA = FOC__THETA - 4915;
        }
        #elif (EstimateAlgorithm == PLL)
        {
            FOC__ETHETA = FOC__THETA;
        }
        #endif                                                                                      
        TimeCnt = FOC__ETHETA;                                                                 
        /* -----启动电流、KP、KI、FOC_EKP、FOC_EKI----- */
        FOC_IDREF = ID_Start_CURRENT;                                                               // D轴启动电流
        mcFocCtrl.mcIqref = IQ_Start_CURRENT;                                                       // Q轴启动电流
        #if (TailWind_Mode==BEMFMethod)
        {
            if (BEMFDetect.BEMFCCWFlag == 1)
            {
                mcFocCtrl.mcIqref += I_Value(0.95);                                                 // 逆风时，加大启动电流
            }
            else if (BEMFDetect.BEMFCCWFlag == 2)
            {
                mcFocCtrl.mcIqref += I_Value(0.8);                                                  // 逆风时，加大启动电流
            }
        }
        #elif (TailWind_Mode==RSDMethod)
        {
            if ((RSDDetect.RSDCCWFlag == 1) || (RSDDetect.RSDCCWTimes >= 4))
            {
                mcFocCtrl.mcIqref += I_Value(0.95);                                                 // 逆风时，加大启动电流
            }
            else if (RSDDetect.RSDCCWFlag == 2)
            {
                mcFocCtrl.mcIqref += I_Value(0.9);                                                  // 逆风时，加大启动电流
            }
        }
        #endif
        FOC_DQKP    = DQKPStart;
        FOC_DQKI    = DQKIStart;
        FOC_EKP     = OBSW_KP_GAIN;
        FOC_EKI     = OBSW_KI_GAIN;
        /* -----启动方式选择----- */
        #if (Open_Start_Mode == Omega_Start)                                                        // Omega 启动
        {
            FOC_EFREQACC    = Motor_Omega_Ramp_ACC;
            FOC_EFREQMIN    = Motor_Omega_Ramp_Min;
            FOC_EFREQHOLD   = Motor_Omega_Ramp_End;
            SetBit(FOC_CR1, EFAE);                                                                  // 估算器强制输出
            ClrBit(FOC_CR1, RFAE);                                                                  // 禁止强拉
            SetBit(FOC_CR1, ANGM);                                                                  // 估算模式
        }
        #elif (Open_Start_Mode == Open_Start)
        {
            FOC_RTHEACC     = Motor_Open_Ramp_ACC;                                                  // 爬坡函数的初始加速度
            FOC__RTHESTEP   = Motor_Open_Ramp_Min;                                                  // 0.62 degree acce speed
            RPDPara.ThetaGet = Motor_Open_Ramp_Min;
            FOC__RTHECNT    = MOTOR_OPEN_ACC_CNT;                                                   // acce time
            ClrBit(FOC_CR1, EFAE);                                                                  // 估算器强制输出
            SetBit(FOC_CR1, RFAE);                                                                  // 禁止强拉
            ClrBit(FOC_CR1, ANGM);                                                                  // 估算模式
        }
        #elif (Open_Start_Mode == Open_Omega_Start)
        {
            FOC_RTHEACC     = Motor_Open_Ramp_ACC;                                                  // 爬坡函数的初始加速度
            FOC__RTHESTEP   = Motor_Open_Ramp_Min;                                                  // 0.62 degree acce speed
            FOC__RTHECNT    = MOTOR_OPEN_ACC_CNT;                                                   // acce time
            FOC_EFREQACC    = Motor_Omega_Ramp_ACC;
            FOC_EFREQMIN    = Motor_Omega_Ramp_Min;
            FOC_EFREQHOLD   = Motor_Omega_Ramp_End;
            SetBit(FOC_CR1, EFAE);                                                                  // 估算器强制输出
            SetBit(FOC_CR1, RFAE);                                                                  // 禁止强拉
            SetBit(FOC_CR1, ANGM);                                                                  // 估算模式
        }
        #endif                                                                                     
    }
    
    /* -----不同启动方式下，切换到MCRUN状态----- */
    #if (Open_Start_Mode == Open_Start)                                                             //OPEN状态启动时拖动多次
    {
        
        mcFocCtrl.State_Count = 20;                                                              
        FOC_EKP = OBSW_KP_GAIN_RUN4;                                                                // 估算器里的PI的KP
        FOC_EKI = OBSW_KI_GAIN_RUN4;                                                                // 估算器里的PI的KI
    }
    #elif (Open_Start_Mode == Open_Omega_Start)
    {
        mcFocCtrl.State_Count = 2500;   //单位：1ms
        
    }
    #elif (Open_Start_Mode == Omega_Start)
    {
        /* -----PLL或SMO----- */
        #if (EstimateAlgorithm == SMO  || EstimateAlgorithm == AO)
        {
            mcFocCtrl.State_Count = 700;    //单位：1ms
        }
        #elif (EstimateAlgorithm == PLL)
        {
            mcFocCtrl.State_Count = 1400;    //单位：1ms
            FOC_EKP = OBSW_KP_GAIN_RUN1;                                                            // 估算器里的PI的KP
            FOC_EKI = OBSW_KI_GAIN_RUN1;                                                            // 估算器里的PI的KI
        }
        #endif                                                                                      
        
    }
    #endif                                             
		LowSpeedObserverInit();
    FOC_IQREF = mcFocCtrl.mcIqref;                                                                  // Q轴启动电流
}


/** 
 * @brief     顺风逆风参数配置函数
 */
void Motor_TailWind(void)
{
    if (mcFocCtrl.State_Count == 0)
    {
        if (McStaSet.SetFlag.TailWindSetFlag  == 0)                                                 //初始化
        {
            McStaSet.SetFlag.TailWindSetFlag = 1;
            #if (TailWind_Mode==RSDMethod)
            {
                RSDDetectInit();
            }
            #elif (TailWind_Mode==BEMFMethod)
            {
                BEMFDetectInit();
            }
            #endif
        }
        
        if (McStaSet.SetFlag.TailWindSetFlag == 1)
        {
            #if (TailWind_Mode==RSDMethod)
            {
                RSDDealwith();
            }
            #elif (TailWind_Mode==BEMFMethod)
            {
                BEMFDealwith();
            }
            #endif
        }
    }
}

/**
 * @brief    第一次上电初始化变量
 */
void MotorcontrolInit(void)
{
    /* -----电机目标方向----- */
    mcFRState.TargetFR                 = (uint8)(FRMODE);
    /* -----电流偏置校准变量----- */
    mcCurOffset.IuOffsetSum            = 16383;
    mcCurOffset.IvOffsetSum            = 16383;
    mcCurOffset.Iw_busOffsetSum        = 16383;
    /* -----LED灯响应----- */
    mcLedDisplay.Counttime             = 4999;
    /* -----速度环的响应----- */
    mcSpeedRamp.DelayPeriod           = 10;
}


/** 
 * @brief     初始化电机参数，每次电机重启均会被调用
 * @warning   需要注意填写的变量是否可以在此时刻被初始化
 */
void VariablesPreInit(void)
{
    /* -----保护----- */
    mcFaultSource = 0;
    memset(&mcFaultDect, 0, sizeof(FaultVarible));                                                  // FaultVarible变量清零
    /* -----外部控制环----- */
    memset(&mcFocCtrl, 0, sizeof(FOCCTRL));                                                         // mcFocCtrl变量清零
    /* -----顺逆风判断----- */
    #if (TailWind_Mode==RSDMethod)
    {
        RSDDetect.RSDCCWTimes    = 0;                                                               //  CCW刹车次数清零
    }
    #elif (TailWind_Mode==BEMFMethod)
    {
    }
    #elif (TailWind_Mode==FOCMethod)
    {
        memset(&TailWindDetect, 0, sizeof(MotorTailWindTypeDef));                                   //  TailWindDetect所有变量清零
    }
    #endif
    /* -----电机状态机时序变量----- */
    McStaSet.SetMode                   = 0;
    /* -----LED灯响应----- */
    memset(&mcLedDisplay, 0, sizeof(MCLedDisplay));                                                 // mcLedDisplay变量清零
    mcLedDisplay.Counttime            = 4999;
    /* -----电机功率参数初始化----- */
    Power_Currt                         = 0;
}


/** 
 * @brief     上电时，先对硬件电路的电流进行采集，写入对应的校准寄存器中。
              调试时，需观察mcCurOffset结构体中对应变量是否在范围内。采集结束后，OffsetFlag置1。
 */
void GetCurrentOffset(void)
{
    if (mcCurOffset.OffsetFlag == 0)
    {
        SetBit(ADC_CR, ADCBSY);                                                                     // 使能ADC
        
        while (ReadBit(ADC_CR, ADCBSY));
        
        #if (Shunt_Resistor_Mode == Single_Resistor)                                                // 单电阻模式，上电验证硬件电路时，需观察mcCurOffset.IbusOffset是否为4096
        {
            mcCurOffset.Iw_busOffsetSum += ((ADC4_DR & 0x0fff) << 3);
            mcCurOffset.Iw_busOffset = mcCurOffset.Iw_busOffsetSum >> 4;
            mcCurOffset.Iw_busOffsetSum -= mcCurOffset.Iw_busOffset;
        }
        #elif (Shunt_Resistor_Mode == Double_Resistor)                                              // 双电阻模式，上电验证硬件电路时，需观察mcCurOffset.IaOffset、mcCurOffset.IbOffset是否为4096
        {
            mcCurOffset.IuOffsetSum += ((ADC0_DR & 0x0fff) << 3);
            mcCurOffset.IuOffset = mcCurOffset.IuOffsetSum >> 4;
            mcCurOffset.IuOffsetSum -= mcCurOffset.IuOffset;
            mcCurOffset.IvOffsetSum += ((ADC1_DR & 0x0fff) << 3);
            mcCurOffset.IvOffset = mcCurOffset.IvOffsetSum >> 4;
            mcCurOffset.IvOffsetSum -= mcCurOffset.IvOffset;
        }
        #elif (Shunt_Resistor_Mode == Three_Resistor)                                               // 三电阻模式，上电验证硬件电路时，需观察mcCurOffset.IaOffset、mcCurOffset.IbOffset、mcCurOffset.IcOffset是否为4096
        {
            mcCurOffset.IuOffsetSum += ((ADC0_DR & 0x0fff) << 3);
            mcCurOffset.IuOffset = mcCurOffset.IuOffsetSum >> 4;
            mcCurOffset.IuOffsetSum -= mcCurOffset.IuOffset;
            mcCurOffset.IvOffsetSum += ((ADC1_DR & 0x0fff) << 3);
            mcCurOffset.IvOffset = mcCurOffset.IvOffsetSum >> 4;
            mcCurOffset.IvOffsetSum -= mcCurOffset.IvOffset;
            mcCurOffset.Iw_busOffsetSum += ((ADC4_DR & 0x0fff) << 3);
            mcCurOffset.Iw_busOffset = mcCurOffset.Iw_busOffsetSum >> 4;
            mcCurOffset.Iw_busOffsetSum -= mcCurOffset.Iw_busOffset;
        }
        #endif
        mcCurOffset.OffsetCount++;
        
        if (mcCurOffset.OffsetCount > Calib_Time)
        {
            mcCurOffset.OffsetFlag = 1;
            #if (GetCurrentOffsetEnable)
            {
              Fault_GetCurrentOffset();                                                             // 偏置电压保护
            }
            #endif
        }
    }
}

/** 
 * @brief     关闭输出，关闭FOC，电机切换到mcReady状态被调用一次
 */
void Motor_Ready(void)
{
    if (McStaSet.SetFlag.CalibFlag == 0)
    {
        McStaSet.SetFlag.CalibFlag = 1;
        MOE            = 0;                                                                         // 关闭MOE
        ClrBit(DRV_CR, FOCEN);                                                                      // 关闭FOC     
        SetBit(ADC_MASK_SYSC, CH7EN | CH4EN | CH3EN | CH2EN | CH1EN | CH0EN);                       // 开启ADC        
    }
}


/** 
 * @brief     电机初始化，对电机相关变量、PI进行初始化设置,关闭FOC所需要使用到的ADC
 * @note      关闭FOC所需要使用到的ADC，FOC模块会自动调用相应ADC 无需外部使能
 */
void Motor_Init(void)
{
    ClrBit(ADC_MASK_SYSC, CH4EN |  CH1EN | CH0EN);                                                  // 关闭软件电流采样的ADC
    VariablesPreInit();                                                                             // 电机相关变量初始化
    PI_Init();                                                                                      // PI初始化
    SpeedPIDInit();
    McStaSet.SetFlag.TailWindSetFlag = 0;
}


