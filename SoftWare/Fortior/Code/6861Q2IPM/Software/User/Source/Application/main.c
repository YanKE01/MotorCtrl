/* --------------------------- (C) COPYRIGHT 2020 Fortiortech ShenZhen -----------------------------
    File Name      : main.c
    Author         : Fortiortech  Appliction Team
    Version        : V1.0
    Date           : 2020-09-29
    Description    : This file contains .C file function used for Motor Control.
----------------------------------------------------------------------------------------------------  
                                       All Rights Reserved
------------------------------------------------------------------------------------------------- */
/* Includes -------------------------------------------------------------------------------------*/
#include <FU68xx_2.h>
#include <Myproject.h>

/* Private typedef ------------------------------------------------------------------------------*/
/* Private define -------------------------------------------------------------------------------*/
/* Private macro --------------------------------------------------------------------------------*/
/* Private variables ----------------------------------------------------------------------------*/
/* Private function prototypes ------------------------------------------------------------------*/
/* Private functions ----------------------------------------------------------------------------*/
void SoftwareInit(void);
void HardwareInit(void);
void MotorControlInit(void);

/*  ----------------------------------------------------------------------------------------------*/
/*  Function Name  : DebugSet
/*  Description    : 调试模式配置
/*  Date           : 2020-04-14
/*  Parameter      : None
/*  ----------------------------------------------------------------------------------------------*/
void DebugSet(void)
{
//    #if (SPI_DBG_HW)      // 硬件调试模式
//    Set_DBG_DMA(&HARD_SPIDATA);
//    #elif (SPI_DBG_SW)    // 软件调试模式
//    Set_DBG_DMA(spidebug);
//    #endif
////    #if  ((SPI_DBG_HW) && (SPI_DBG_SW))
////    #error Only one DBG mode can be selected
////    #endif
//    SetReg(CMP_CR3, DBGSEL0 | DBGSEL1,  GP01_DBG_Conf);
//    SetReg(CMP_CR3, CMPSEL0 | CMPSEL1 | CMPSEL2, GP07_DBG_Conf);
}


/* -------------------------------------------------------------------------------------------------
    Function Name  : main
    Description    : 主函数主要功能是初始化，包括上电等待，软件初始化，硬件初始化，调试模式设置，主循环扫描。
                                    软件初始化--初始化所有定义的变量
                                    硬件初始化--初始化硬件设备配置
                                    调试模式设置--调试模式
    Date           : 2020-09-29
    Parameter      : None
------------------------------------------------------------------------------------------------- */
uint8 data g_1mTick = 0;  ///< 1ms滴答信号，每隔1ms在SYSTICK定时器被置1，需在大循环使用处清零


void main(void)
{
    uint16 PowerUpCnt = 0;
    for(PowerUpCnt = 0;PowerUpCnt < SystemPowerUpTime;PowerUpCnt++){};

    /* -----Software Init----- */
    SoftwareInit();	

    /* -----Hardware Init----- */
    HardwareInit();
	  //DebugSet();	
    /* -----PWM Init----- */        
	  PWMIN_Init();
        
  SetBit(TIM234_CTRL, MDU_EN_N);
	//		GP04 = 0;

    while(1)
    {

			#if (Sleep_Enable)
        {
            if(sleepSet.sleepUpdata)
            {
              sleepSet.sleepUpdata = 0;
              /* -----Software Init----- */             
              SoftwareInit();
              /* -----Hardware Init----- */
              HardwareInit();
              /* -----PWM Init----- */			
              PWMIN_Init();
            }
        }
        #endif

        /* -----运放偏置电压采样----- */
        GetCurrentOffset(); 
     																							   // 电流偏置的获取
        /* -----电机状态机控制----- */
		MC_Control();            																   // 主控函数，状态扫描
        
        if(mcState == mcRun || mcState == mcStop)
        {
            /* -----计算标幺后的功率----- */
            RealPowerCal();
        }
        #if (SPEED_MODE == NONEMODE)											                   // 直接上电运行模式
        {  
           mcSpeedRamp.flagONOFF   = 1;
           mcSpeedRamp.targetValue =   _Q15(2000 / MOTOR_SPEED_BASE);//低于1500容易失步//1400
        }
        #endif
                /* -----1ms处理函数----- */
        if (g_1mTick)
        {
            
            TickCycle_1ms();
            g_1mTick = 0;
           
        }
		
    }
}
/* -------------------------------------------------------------------------------------------------
    Function Name  : SoftwareInit
    Description    : 参数初始化
    Date           : 2020-09-29
    Parameter      : None
------------------------------------------------------------------------------------------------- */
void SoftwareInit(void)
{
    /* -----初始化所有定义的参数变量----- */
    MotorcontrolInit();
    /* -----电机初始状态为mcReady，故障保护为无故障----- */    
    mcState = mcReady;
    mcFaultSource = 0;
}

/* -------------------------------------------------------------------------------------------------
    Function Name  : HardwareInit
    Description    : 硬件初始化，初始化需要使用的硬件设备配置，FOC必须配置的是运放电压、运放初始化、ADC初始化、Driver初始化
                                    TIM4初始化，其他的可根据实际需求加。
    Date           : 2020-09-29
    Parameter      : None
------------------------------------------------------------------------------------------------- */
void HardwareInit(void)
{
    /* -----比较器初始化，用于硬件过流比较保护----- */
    CMP3_Init();
    
	#if (Sleep_Enable)
	{
      Sleepmode_Init();
    }
    #endif
    
    /* -----功能IO初始化----- */
    GPIO_Init();
    
    /* -----运算放大器初始化----- */
    AMP_Init();
    
    /* -----ADC初始化----- */    
    ADC_Init();
    
    /* -----比较器中断配置----- */
    CMP3_Inter_Init();                         													   // 建议和比较器初始化间隔一段时间
    
    /* -----Driver初始化----- */
    Driver_Init();
    
//		SPI_Init();  
//    /* -----Timer初始化----- */
    TIM3_Init();																																//端口GP11,采样定时器3中断作为PWM捕获中断
    TIM1ms_Init();																															//采用1ms定时器中断作为常见中断,处理故障保护等附加功能
 }
