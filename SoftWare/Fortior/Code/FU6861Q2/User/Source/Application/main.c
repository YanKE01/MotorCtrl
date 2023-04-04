/**
 * @copyright (C) COPYRIGHT 2022 Fortiortech Shenzhen
 * @file      main.c
 * @author    Fortiortech  Appliction Team
 * @since     Create:2021-05-14
 * @date      Last modify:2022-07-14
 * @brief     包含主函数，软硬件初始化函数，VRER配置函数,Debug小工具
 */

#include <FU68xx_2.h>
#include <Myproject.h>
#include <SanityCheck.h>
#include "TM1650.h"
#include "MyVariable.h"
/*  ------------------------------------------------------------------------------------
    Internal Routine Prototypes
    ------------------------------------------------------------------------------------ */
void SoftwareInit(void);
void HardwareInit(void);
void DebugSet(void);
void MotorControlInit(void);

/**
 * @brief        主函数主要功能是初始化，
                     1、包括上电等待，软件初始化，硬件初始化，调试模式设置，主循环扫描。
                     2、软件初始化--初始化所有定义的变量
                     3、硬件初始化--初始化硬件设备配置
                     4、大循环运行偏置电流采集函数，电机状态机控制函数，以及环路响应函数
 */
void main(void)
{
			uint16 PowerUpCnt = 0;
		int i=0;

    /* -----上电等待电源稳定 ----- */
    for (PowerUpCnt = 0; PowerUpCnt < SystemPowerUpTime; PowerUpCnt++)
        ;

    /* -----软件参数初始化 ----- */
    SoftwareInit();
    /* -----硬件模块初始化----- */
    HardwareInit();
    /* -----调试模式设置--内部变量查询；CMP输出查询；ADC触发信号查询----- */
    //DebugSet();
    TempPower = 0; // 功率值清零
    MyVariableInit();
    SetBit(TIM234_CTRL, MDU_EN_N);

    while (1)
    {

        /* -----电流偏置的获取----- */
        GetCurrentOffset();
        /* -----主控函数，状态扫描 2.6k----- */
        MC_Control();

        if (VariableFlag.g_1msTick)
        {
            TickCycle_1ms();
            VariableFlag.g_1msTick = 0;
        }

        mcSpeedRamp.Value_UD = FOC__UD; //  FOC__ID  FOC__UD
        mcSpeedRamp.Value_UQ = FOC__UQ; //  FOC__IQ  FOC__UQ
				

    }
}

/**
 * @brief        SPI Debug调试小工具
 */
void DebugSet(void)
{
#if defined(SPI_DBG_HW) // 硬件调试模式
    Set_DBG_DMA(&HARD_SPIDATA);
#elif defined(SPI_DBG_SW) // 软件调试模式
    Set_DBG_DMA(spidebug);
#endif
#if defined(SPI_DBG_HW) && defined(SPI_DBG_SW)
#error Only one DBG mode can be selected
#endif
    /* -----Debug信号配置----- */
    SetReg(CMP_CR3, DBGSEL0 | DBGSEL1, GP01_DBG_Conf);
    SetReg(CMP_CR3, CMPSEL0 | CMPSEL1 | CMPSEL2, GP07_DBG_Conf);
}

/**
 * @brief        软件初始化，部分变量初始化，上电运行一次
 */
void SoftwareInit(void)
{
    /* -----初始化所有定义的参数变量----- */
    MotorcontrolInit();
    /* -----电机初始状态为mcReady，故障保护为无故障----- */
    mcState = mcReady;
    mcFaultSource = 0;
}

/**
 * @brief     硬件初始化，初始化需要使用的硬件设备配置，FOC必须配置的是运放电压、运放初始化、ADC初始化、Driver初始化
 *            其他的可根据实际需求加。
 */
void HardwareInit(void)
{
    /* -----为提高芯片的抗干扰能力，降低芯片功耗，请在具体项目时，将不需要用的GPIO默认都配置为输入上拉----- */
    /* -----具体配置可在GPIO_Default_Init设置----- */
    GPIO_Default_Init();
    /* -----比较器初始化，用于硬件过流比较保护----- */
    CMP3_Init();
    /* -----休眠模式初始化----- */
    //    Sleepmode_Init();
    /* -----功能IO初始化----- */
    GPIO_Init();
    /* -----运算放大器初始化----- */
    AMP_Init();
    /* -----ADC初始化----- */
    ADC_Init();
    /* -----比较器中断配置----- */
    CMP3_Inter_Init(); // 建议和比较器初始化间隔一段时间
    /* -----Driver初始化----- */
    Driver_Init();
/* -----UART初始化----- */
//    UART_Init();//未配置
/* -----SPI调试初始化----- */
#if defined(SPI_DBG_SW) | defined(SPI_DBG_HW) // 调试模式
//        SPI_Init();                                       //调试模式下，占用SPI端口的NSS(GP04),MOSI(GP05),SCK(GP06)
#endif
/* -----Timer初始化----- */
//    TIM2_Init();                                          //端口GP07 & GP10
#if (SPEED_MODE == PWMMODE)
    TIM3_Init(); // 端口GP11,采样定时器3中断作为PWM捕获中断
#endif
#if (FG_Enable == 1)
    TIM4_Init(); // 端口GP01
#endif
    TIM1ms_Init(); // 采用1ms定时器中断作为常见中断,处理故障保护等附加功能

    /*-----TM1650初始化----*/
    SetDisplay1650(1, 7, 1);
}
