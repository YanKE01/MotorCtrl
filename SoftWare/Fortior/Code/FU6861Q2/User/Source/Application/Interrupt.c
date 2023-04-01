/**
 * @copyright (C) COPYRIGHT 2022 Fortiortech Shenzhen
 * @file      Interrupt.c
 * @author    Fortiortech  Appliction Team
 * @date      2022-07-13
 * @brief     This file contains interrupt function used for Motor Control.
 */
 


#include <FU68xx_2.h>
#include <Myproject.h>

uint16 xdata spidebug[4] = { 0 };
uint16 xdata Power_Currt;

/** 
 * @brief     低于预警中断
 *            开启低压检测中断后,MCU会对输入电压进行监测,当输入电压低于设定值，则会触发中断
 */
void LVW_INT(void) interrupt 0                                                                      // 硬件FO过流中断，关闭输出
{
    mcFaultSource = FaultLVW;                                                                       // 硬件过流保护
    ClrBit(LVSR, LVWIF);
}


/** 
 * @brief        比较器3硬件过流保护，该中断仅提供 故障码 赋值,用于状态机的切换。
 *               需要开启比较器CMP3  发生过流自动清除MOE功能
 * @brief        CMP0/1/2：顺逆风判断  
 */
void CMP_ISR(void) interrupt 7
{
    if (ReadBit(CMP_SR, CMP3IF))
    {
        MOE = 0;
        mcFaultSource = FaultHardOVCurrent;                                 // 硬件过流保护
        ClrBit(CMP_SR, CMP3IF);
    }
    
    #if (TailWind_Mode == BEMFMethod)
    {
        /* -----通过BEMF做顺风启动功能----- */
        BEMFDetectFunc();
    }
    #endif
}


/** 
 * @brief        FOC中断(Drv中断),每个载波周期执行一次，用于处理响应较高的程序，中断优先级第二
 */
void FOC_INT(void) interrupt 3
{
    //      GP05 = 1;
    if (ReadBit(DRV_SR, DCIF))                                                                      // 比较中断
    {
        /* -----启动除法器----- */
        APP_DIV();                                                                                  // 启动除法器，避免与过调值中的除法冲突
        //            if((mcState == mcStart)||(mcState == mcRun))
        //            if((mcState != mcAlign))
        //              {
        //                  CurrentLoop();
        //              }
				StartupState();
        #if defined (SPI_DBG_SW)                                                                    // 软件调试模式
        {
            spidebug[0] = SOFT_SPIDATA0;
            spidebug[1] = SOFT_SPIDATA1;
            spidebug[2] = SOFT_SPIDATA2;
            spidebug[3] = SOFT_SPIDATA3;
        }
        #endif
        DRV_SR = (DRV_SR | SYSTIF) & (~DCIF);
    }
    
    //      GP05 = 0;
}


/**
 * @brief    正反转检测(RSD)
 */
void TIM2_INT(void) interrupt 4
{
    if (ReadBit(TIM2_CR1, T2IR))
    {
        ClrBit(TIM2_CR1, T2IR);
    }
    
    if (ReadBit(TIM2_CR1, T2IP))
    {
        #if (TailWind_Mode == RSDMethod)
        {
            RSDFRDetect();                                                                          //RSD正反转检测
        }
        #endif
        ClrBit(TIM2_CR1, T2IP);
    }
    
    if (ReadBit(TIM2_CR1, T2IF))                                                                    //溢出中断,用于判断静止,时间为349ms。
    {
        #if (TailWind_Mode == RSDMethod)
        {
            RSDDetect.RSDState = Static;
            RSDDetect.RSDFlag  = 1;
        }
        #endif
        ClrBit(TIM2_CR1, T2IF);
    }
}


/**
 * @brief    PWM捕获 ，中断优先级第二，高于FOC中断，用于PWM调速
 */
void TIM3_INT(void) interrupt 9
{
    if (ReadBit(TIM3_CR1, T3IR))
    {
        ClrBit(TIM3_CR1, T3IR);
    }
    
    if (ReadBit(TIM3_CR1, T3IP))                                                                  //周期中断
    {
        if (mcPwmInput.PWMFlag != 1)                                                              //若正在计算占空比则不更新
        {
            mcPwmInput.PWMCompare    = TIM3__DR;
            mcPwmInput.PWMARR        = TIM3__ARR;
            mcPwmInput.PWMUpdateFlag = 1;
        }
        
        ClrBit(TIM3_CR1, T3IP);
    }
    
    if (ReadBit(TIM3_CR1, T3IF))
    {
        if (GP11)                                                                                 //PWM 100%输出
        {
            mcPwmInput.PWMCompare = 8000;
            mcPwmInput.PWMARR     = 8000;
        }
        else                                                                                      //PWM 为0%
        {
            mcPwmInput.PWMCompare = 0;
            mcPwmInput.PWMARR     = 8000;
        }
        
        mcPwmInput.PWMUpdateFlag = 1;
        ClrBit(TIM3_CR1, T3IF);
    }
}


/**
 * @brief    1ms中断，用于产生1ms定时间隔
 */
void SYStick_INT(void) interrupt 10
{

    if (ReadBit(DRV_SR, SYSTIF))                                                                    // SYS TICK中断
    {
        VariableFlag.g_1msTick = 1;
        DRV_SR = (DRV_SR | DCIF) & (~SYSTIF);                                     // 清零标志位
    }
}


/**
 * @brief     串口中断，中断优先级最低，用于接收串口信号
 */
void USART_INT(void)  interrupt 12
{
    //    if(RI == 1)
    //    {
    //        RI = 0;
    //        Uart.Uredata= UT_DR;                                                                  //读接收数据
    //        UartRecIsr();
    //    }
    //    if (TI == 1)
    //    {
    //        TI = 0;
    ////        UT_DR = 0xaa;
    //        UartSendIsr();
    //    }
}


/**
 * @brief    睡眠唤醒中断
 */
void EXTERN_INT(void) interrupt 2
{
    if (SleepSet.SleepFlag)
    {
        SleepSet.SleepFlag = 0;
        SleepSet.SleepEn   = 1;
    }
    
    ClrBit(P1_IF, P11);                                                                             // 清零P10标志位
}



