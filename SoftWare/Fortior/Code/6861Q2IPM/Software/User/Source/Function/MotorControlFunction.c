/* --------------------------- (C) COPYRIGHT 2020 Fortiortech ShenZhen -----------------------------
    File Name      : MotorControlFunction.c
    Author         : Fortiortech  Appliction Team
    Version        : V1.0
    Date           : 2020-09-16
    Description    : This file contains .C file function used for Motor Control.
----------------------------------------------------------------------------------------------------  
                                       All Rights Reserved
------------------------------------------------------------------------------------------------- */
#include <FU68xx_2.h>
#include <Myproject.h>

CurrentOffset xdata mcCurOffset;
StartTimeCnt Time;
/* -------------------------------------------------------------------------------------------------
    Function Name  : FOC_Init
    Description    : mcInit状态下，对FOC的相关寄存器进行配置,先清理寄存器，后配置，最后使能
    Date           : 2020-09-16
    Parameter      : None
------------------------------------------------------------------------------------------------- */
void FOC_Init(void)
{
	ClrBit(DRV_CR, DRVOE);
	ClrBit(DRV_CR, OCS);
    ClrBit(DRV_CR, DRVEN);
	/*使能FOC*/
	ClrBit(DRV_CR, FOCEN);
	SetBit(DRV_CR, FOCEN);
	/*配置FOC寄存器*/
	FOC_CR1 			= 0;																	   // 清零 FOC_CR1
	FOC_CR2 			= 0;																	   // 清零 FOC_CR2
	FOC_IDREF 		    = 0;																	   // 清零 Id
	FOC_IQREF 		    = 0;																	   // 清零 Iq

	FOC__THETA 		    = 0;																	   // 清零 角度
	FOC_RTHEACC 	    = 0;																	   // 清零 爬坡函数的初始加速度
	FOC__RTHESTEP 	    = 0;																		
	FOC__RTHECNT 	    = 0;																			
	FOC__THECOMP 	    = _Q15(0.0 / 180.0);												       // SMO 估算补偿角
	FOC__THECOR 		= 0x02;																	   // 误差角度补偿

	
			  //自适应估算器模式使能 
		SetBit(FOC_CR3, ESCMS); 
    SetBit(FOC_CR3, MFP_EN); 
	
	
	/*电流环参数配置*/
	FOC_DMAX 			= DOUTMAX;
	FOC_DMIN 			= DOUTMIN;
	
	FOC_QMAX 			= QOUTMAX;
	FOC_QMIN 			= QOUTMIN;

	/*位置估算参数配置*/
	FOC_EK1 			= OBS_K1T;
	FOC_EK2 			= OBS_K2T;
	FOC_EK3 			= OBS_K3T;
	FOC_EK4 			= OBS_K4T;
	FOC_FBASE 		    = OBS_FBASE;
	FOC_OMEKLPF 	    = SPEED_KLPF;
	FOC_EBMFK 		    = OBS_KLPF;

    FOC_TGLI            = PWM_TGLI_LOAD;

	/*********PLL或SMO**********/
	#if (EstimateAlgorithm == SMO)
	{
        ClrBit(FOC_CR2, ESEL);
        FOC_KSLIDE      = OBS_KSLIDE;
        FOC_EKLPFMIN	= OBS_EA_KS;
	}
	#elif (EstimateAlgorithm == PLL)
	{
        SetBit(FOC_CR2, ESEL);
        FOC_KSLIDE      = OBSE_PLLKP_GAIN1;
        FOC_EKLPFMIN	= OBSE_PLLKI_GAIN1;
	}
    #endif
    
	SetBit(FOC_CR1, SVPWMEN);															           // SVPWM模式

    #if (IRMODE)                                                                               // 设置F/R
    {
        SetBit(DRV_CR,DDIR);
    }
    #else
    {
        ClrBit(DRV_CR,DDIR);
    }
    #endif
	#if (OverModulation)
	{
        SetBit(FOC_CR1,OVMDL);													                   // 过调制
	}
	#endif
    /* -----单电阻采样；需要最小采样窗,FOC_TRGDLY为0，七段式SVPWM方式----- */
    SetReg(FOC_CR1, CSM0 | CSM1, 0x00);
    FOC_TSMIN = PWM_TS_LOAD;									                                   // 最小采样窗口
    FOC_TRGDLY = FOCTRGDLY;          					                                           // 采样时刻在中点，一般考虑开关噪声影响，会设置延迟，0x0c表示延迟12个clock，提前用反码形式，如0x84表示提前12个clock。
    ClrBit(FOC_CR2,F5SEG);															               // 7段式
    SetReg(CMP_CR1, CMP3MOD0 | CMP3MOD1, 0x00);
	
	/* 使能电流基准校正	*/
	#if (CalibENDIS == Enable)
    {
        if(mcCurOffset.offsetFlag)
        {
            SetReg(FOC_CR2, CSOC0 | CSOC1, 0x00);
            FOC_CSO = mcCurOffset.ibusOffset;	                                                   // 写入Ibus的偏置
        }
    }
	#endif	//end CalibENDIS
	/*-------------------------------------------------------------------------------------------------
	DRV_CTL：PWM来源选择
	OCS = 0, DRV_COMR
	OCS = 1, FOC/SVPWM/SPWM
	-------------------------------------------------------------------------------------------------*/
	/*计数器比较值来源FOC*/
	SetBit(DRV_CR, OCS);
	SetBit(DRV_CR, DRVOE);
    SetBit(DRV_CR, DRVEN);
}

/* -------------------------------------------------------------------------------------------------
    Function Name  : Motor_Charge
    Description    : 预充电，当一直处于预充电状态下，不接电机，可用于验证IPM或者Mos。
                     预充电分三步，第一步是对U相进行预充电，第二步是对U,V两相进行预充电;第三步是对U、V、W三相进行预充电。
    Date           : 2020-09-16
    Parameter      : None
------------------------------------------------------------------------------------------------- */
void Motor_Charge(void)
{
    if(mcStaSet.setFlag.chargeSetFlag == 0)
    {
        mcStaSet.setFlag.chargeSetFlag = 1;
        #if (PWM_Level_Mode == Low_Level)	                                                       //用于测试6536
        {
            SetBit(P1_OE, P10);
            GP10 = 1;
        }
        #endif
        #if (IPMState == IPMtest)
        {
            DRV_DR = 0.7 * DRV_ARR;						                                           // IPM 70% duty
        }
        #elif (IPMState == NormalRun)		                                                       // 正常按电机状态机运行
        {
            DRV_DR = 0.1 * DRV_ARR;				                                                   //下桥臂10% duty
        }
        #endif
        /*-------------------------------------------------------------------------------------------------
        DRV_CTL：PWM来源选择
        OCS = 0, DRV_COMR
        OCS = 1, FOC/SVPWM/SPWM
        -------------------------------------------------------------------------------------------------*/
        ClrBit(DRV_CR, OCS);
        mcFocCtrl.chargeStep = 0;
    }
		 
    if((mcFocCtrl.state_Count < Charge_Time) && (mcFocCtrl.chargeStep == 0))
    {
        mcFocCtrl.chargeStep = 1;
        #if (IPMState == IPMtest)  
        {
            DRV_CMR |= 0x03;                                                                       // U相输出
        }
        #elif (IPMState == NormalRun)		                                                       // 正常按电机状态机运行
        {
            DRV_CMR |= 0x01;                                                                       // U相下桥臂通
        }
        #endif
        MOE = 1;
    }
    if(( mcFocCtrl.state_Count <= (Charge_Time << 1) / 3) && (mcFocCtrl.chargeStep == 1))
    {
        mcFocCtrl.chargeStep = 2;
        #if (IPMState == IPMtest)
        {
            DRV_CMR |= 0x0F;                                                                       // U、V相输出
        }
        #elif (IPMState == NormalRun)		                                                       // 正常按电机状态机运行
        {
            DRV_CMR |= 0x04;                                                                       // V相下桥臂导通
        }
        #endif
    }
    if((mcFocCtrl.state_Count <= Charge_Time / 3) && (mcFocCtrl.chargeStep == 2))
    {
        mcFocCtrl.chargeStep = 3;
        #if (IPMState == IPMtest)
        {
            DRV_CMR |= 0x3F;                                                                       // U、V、W相输出
        }
        #elif (IPMState == NormalRun)		                                                       // 正常按电机状态机运行
        {
            DRV_CMR |= 0x10;                                                                       // W相下桥臂导通
        }
        #endif
    }
}

/* -------------------------------------------------------------------------------------------------
    Function Name  : Motor_Align
    Description    : 预定位函数，当无逆风判断时，采用预定位固定初始位置;当有逆风判断时，采用预定位刹车
    Date           : 2020-09-16
    Parameter      : None
------------------------------------------------------------------------------------------------- */
void Motor_Align(void)
{
    if(mcStaSet.setFlag.alignSetFlag == 0)
    {
        mcStaSet.setFlag.alignSetFlag = 1;

        /* -----FOC初始化----- */
        FOC_Init();
        
        /* -----配置预定位的电流、KP、KI----- */
        FOC_IDREF = 0;
        FOC_IQREF = 0;

        #if (DQCurrentKpKiCalEnable)
        {
            DQCurrentKpKiCal();                        
        }
        #else
        {
            FOC_DKP = DQKP_Alignment;
            FOC_DKI = DQKI_Alignment;
            
            FOC_QKP = DQKP_Alignment;
            FOC_QKI = DQKI_Alignment;

        }
        #endif

        /* -----配置预定位角度----- */
        #if (AlignTestMode)
        {
            FOC__THETA		= AlignFirstAngle;
        }
        #else
        {
            FOC__THETA		= AlignFirstAngle; 
        }
        #endif	
        
        /* -----PLL或SMO----- */
        #if (EstimateAlgorithm == SMO)
        {
            FOC__ETHETA 	= FOC__THETA - 4096;
        }
        #elif (EstimateAlgorithm == PLL)
        {
            FOC__ETHETA 	= FOC__THETA;
        }
        #endif
        /* -----使能输出----- */
        DRV_CMR |= 0x3F;                         
        MOE = 1;
    }
}


/* -------------------------------------------------------------------------------------------------
    Function Name  : Motor_Open
    Description    : 开环启动的参数配置
    Date           : 2020-09-16
    Parameter      : None
------------------------------------------------------------------------------------------------- */
void Motor_Open(void)
{
    if(mcStaSet.setFlag.startSetFlag == 0)
    {
        /* -----FOC初始化----- */
        FOC_Init();

        /* -----启动初始角度赋值----- */
        FOC__THETA		              = AlignSecondAngle;              // 无初始位置检测，则用预定位角
        /* -----PLL或SMO----- */
        #if (EstimateAlgorithm == SMO)
        {
            FOC__ETHETA 	          = FOC__THETA - 4915;
        }
        #elif (EstimateAlgorithm == PLL)
        {
            FOC__ETHETA 	          = FOC__THETA;
            FOC_KSLIDE                = OBSE_PLLKP_GAIN1;
            FOC_EKLPFMIN              = OBSE_PLLKI_GAIN1;
        }
        #endif
        mcFocCtrl.IdRef = ID_Start_CURRENT;                                                              // D轴启动电流
        mcFocCtrl.IqRef = IQ_Start_CURRENT;		                                               // Q轴启动电流
        FOC_IDREF = mcFocCtrl.IdRef;
        FOC_IQREF = mcFocCtrl.IqRef;
        #if (DQCurrentKpKiCalEnable == 0)
        {
            FOC_DKP = DQKPStart;
            FOC_DKI = DQKIStart;
            
            FOC_QKP = DQKPStart;
            FOC_QKI = DQKIStart;

        }
        #endif


        FOC_EKP 	= OBSW_KP_GAIN1;
        FOC_EKI 	= OBSW_KI_GAIN1;

        FOC_EFREQACC 	= Motor_Omega_Ramp_ACC;
        FOC_EFREQMIN 	= Motor_Omega_Ramp_Min;
        FOC_EFREQHOLD   = Motor_Omega_Ramp_End;

        
        #if (LowSpeedObserverEnable)
        {
            SetReg(FOC_CR1 , EFAE | RFAE | ANGM , 0);
        }
        #else
        {
            SetReg(FOC_CR1 , EFAE | RFAE | ANGM , EFAE | ANGM);            
        }
        #endif

        mcStaSet.setFlag.startSetFlag = 1;
    }

    mcFocCtrl.state_Count = 1500;
    
    mcState = mcRun;
}

/* -------------------------------------------------------------------------------------------------
    Function Name  : MotorcontrolInit
    Description    : 控制变量初始化清零,包括保护参数的初始化、电机状态初始化
    Date           : 2020-09-16
    Parameter      : None
------------------------------------------------------------------------------------------------- */
void MotorcontrolInit(void)
{
    /* -----保护----- */
    memset(&mcFaultDect , 0 , sizeof(FaultVarible));											   // FaultVarible变量清零
    /* -----过流保护----- */
    memset(&mcCurVarible , 0 , sizeof(CurrentVarible));											   // 电流保护的变量清零
    /* -----电机状态机时序变量----- */
    mcStaSet.setMode                   = 0;
    /* -----外部控制环----- */
    memset(&mcFocCtrl , 0 , sizeof(FOCCTRL));													   // mcFocCtrl变量清零
    /* -----ADC采样滤波值----- */
    memset(&adcSampleValue , 0 , sizeof(ADCSample));											   // ADCSample变量清零
    /* -----电流偏置校准变量----- */
    memset(&mcCurOffset , 0 , sizeof(CurrentOffset));											   // mcCurOffset变量清零
    mcCurOffset.ibusOffsetSum          = 16383;    
    /* -----速度环的响应----- */
    memset(&mcSpeedRamp , 0 , sizeof(MCRAMP));												       // mcSpeedRamp变量清零
    /* -----PWM调速变量----- */
    memset(&mcPWMFreqInputCtrl , 0 , sizeof(PWMFREQINPUTTRPE));									   // 清零PWM 调频调速变量PWMINCtl
    /* -----睡眠模式----- */
    #if (Sleep_Enable)
    {
        memset(&sleepSet , 0 , sizeof(SLEEPMODE));		                                  	       // 睡眠模式清零
    }
    #endif
    Time.start_CNT                     = 0;
    
   // mcTorqueCompensationInit();
}

/* -------------------------------------------------------------------------------------------------
    Function Name  : VariablesPreInit
    Description    : 初始化电机参数
    Date           : 2020-09-16
    Parameter      : None
------------------------------------------------------------------------------------------------- */
void VariablesPreInit(void)
{
    /* -----保护----- */
	mcFaultSource = 0;
	memset(&mcFaultDect , 0 , sizeof(FaultVarible));											   // FaultVarible变量清零
    /* -----外部控制环----- */
	memset(&mcFocCtrl , 0 , sizeof(FOCCTRL));													   // mcFocCtrl变量清零
    /* -----电机状态机时序变量----- */
    mcStaSet.setMode                   = 0;
    /* -----LED灯响应----- */
	memset(&mcLedDisplay , 0 , sizeof(MCLedDisplay));											   // mcLedDisplay变量清零		
	#if (MotorFiledWeakenEn)//弱磁
		{
			FiledWeakenInit();
		}
	#endif
	#if (MTPAENABLE)//MTPA
		{
			MtpaInit(MTPAPsi , MTPALD , MTPALQ , HW_BOARD_CURR_BASE , MotorStartMtpaTx);
		}
	#endif
	#if (LowSpeedObserverEnable)//低速观测器
		{  
			memset(&LowSpeedObserver , 0 , sizeof(MCLowSpeedObserver));
			LowSpeedObserver.LowSpeedObserverToAoObserverSpeed = LowSpeedObserverToAoObserverSpeed_Q15;
			LowSpeedObserver.LowSpeedObserverToAoObserverEnable = 1;
			LowSpeedObserverInit(RS , LowSpeedObserverLD , LowSpeedObserverLQ , HW_BOARD_VOLTAGE_BASE , MAX_BEMF_VOLTAGE , HW_BOARD_CURR_BASE , MAX_OMEG_RAD_SEC , TPWM_VALUE , LowSpeedObserverGain1 , LowSpeedObserverGain2);
    }
	#endif
	#if (DQCurrentKpKiCalEnable)//DQ
		{
			DQCurrentKpKiCalInit(DQCURRENT_KP_KI_CAL_LD , DQCURRENT_KP_KI_CAL_LQ , TPWM_VALUE , HW_BOARD_VOLTAGE_BASE , HW_BOARD_CURR_BASE , h);
		}
	#endif
	#if (CurrentDecoupledControlEnable)//电流解耦
		{
			CurrentDecoupledControlFunctionInit(CURRENT_DECOUPLED_CONTROL_LD , CURRENT_DECOUPLED_CONTROL_LQ  , HW_BOARD_VOLTAGE_BASE , HW_BOARD_CURR_BASE , MAX_OMEG_RAD_SEC);
		}
	#endif
}

/* -------------------------------------------------------------------------------------------------
    Function Name  : GetCurrentOffset
    Description    : 上电时，先对硬件电路的电流进行采集，写入对应的校准寄存器中。
					 调试时，需观察mcCurOffset结构体中对应变量是否在范围内。采集结束后，OffsetFlag置1。
    Date           : 2020-09-16
    Parameter      : None
------------------------------------------------------------------------------------------------- */
void GetCurrentOffset(void)
{
    if(mcCurOffset.offsetFlag == 0)
    {      
        SetBit(ADC_CR , ADCBSY);		                           
        while(ReadBit(ADC_CR , ADCBSY));

        mcCurOffset.ibusOffsetSum += ((ADC4_DR & 0x0fff) << 3);
        mcCurOffset.ibusOffset = mcCurOffset.ibusOffsetSum >> 4;
        mcCurOffset.ibusOffsetSum -= mcCurOffset.ibusOffset;

        if(++mcCurOffset.offsetCount > Calib_Time)
        {
            mcCurOffset.offsetFlag = 1;
            
            #if (CurOffsetProtectEnable)
            {
                if((mcCurOffset.ibusOffset > 17000) || (mcCurOffset.ibusOffset < 15000))       //偏置电压不在正常范围内。
                {
                    mcState = mcFault;
                    mcFaultSource = FaultIbusOffset;                                               //进入偏置电压错误保护。
                }
            }
            #endif
        }
    }
}


/* -------------------------------------------------------------------------------------------------
    Function Name  : Motor_Ready
    Description    : 上电时，关闭输出，先对硬件电路的电流进行采集，在FOC_Init中写入对应的校准寄存器中。
                     调试时，需观察mcCurOffset结构体中对应变量是否在范围内。
    Date           : 2020-09-16
    Parameter      : None
------------------------------------------------------------------------------------------------- */
void Motor_Ready(void)
{
    if(mcStaSet.setFlag.calibFlag == 0)
    {
        mcStaSet.setFlag.calibFlag         = 1;
        ClrBit(DRV_CR , FOCEN);                                                                    // 关闭FOC
        MOE			                       = 0;                                                    // 关闭MOE
        SetBit(ADC_MASK_SYSC, CH5EN | CH4EN  | CH2EN);                                             // 开启ADC
        mcCurOffset.offsetFlag             = 0;                                                    // 开始电流采集
        mcCurOffset.offsetCount            = 0;                                                    // 开始电流采集
        mcCurOffset.ibusOffsetSum          = 16383;        
    }
}

/* -------------------------------------------------------------------------------------------------
    Function Name  : Motor_Init
    Description    : 对电机相关变量、PI进行初始化设置
    Date           : 2020-09-16
    Parameter      : None
------------------------------------------------------------------------------------------------- */
void Motor_Init(void)
{
    ClrBit(ADC_MASK_SYSC , CH4EN);                                                                 // 关闭软件电流采样的ADC
    VariablesPreInit();                                                                            // 电机相关变量初始化
    PI_Init();
		#if (IQCOMPENSATEENBLE)
		{
			MCTorqueCompensationCodeInit();
		}
		#endif
    mcFocCtrl.softCurrentValueTemp                = OverSoftCurrentValue;	                                                                           // PI初始化
    

}
