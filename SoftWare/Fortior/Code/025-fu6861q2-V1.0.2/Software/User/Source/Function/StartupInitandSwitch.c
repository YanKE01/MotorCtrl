/* --------------------------- (C) COPYRIGHT 2022 Fortiortech ShenZhen -----------------------------
    File Name      : StartupInitandSwitch.c
    Author         : Fortiortech  Appliction Team
    Version        : V1.0
    Date           : 2022-7-23
    Description    : This file contains StartupInitandSwitch.c function used for Motor Startup.
----------------------------------------------------------------------------------------------------
                                       All Rights Reserved
------------------------------------------------------------------------------------------------- */

#include <FU68xx_2.h>
#include <Myproject.h>

/*  -------------------------------------------------------------------------------------------------
    Function Name  : LowSpeedObserverInit
    Description    : 低速观测器参数初始化
    Date           : 2022-07-23
    Parameter      : None
    ------------------------------------------------------------------------------------------------- */
void LowSpeedObserverInit(void)
{
    memset(&LowSpeedObserver, 0, sizeof(MCLowSpeedObserver));
    FOC_EFREQACC    = 0;
    FOC_EFREQMIN    = 0;
    FOC_EFREQHOLD   = 0;
    ClrBit(FOC_CR1, RFAE);
    ClrBit(FOC_CR1, EFAE); 
    ClrBit(FOC_CR1, ANGM);
    FOC_EKLPFMIN = 32767;
    Startup.BEMFLPFK = 32767;
    LowSpeedObserver.Observer_Count = 1;
    Startup.LowSpeedObserverK1 = LowSpeedObserver_K1;
    Startup.LowSpeedObserverK2 = LowSpeedObserver_K2;
    Startup.LowSpeedObserverK3 = LowSpeedObserver_K3;
    Startup.BEMFFliterCount = BEMFFliter_Count;
    Startup.Initgain = Init_gain;
    Startup.AngleCom = Angle_Com;
    Startup.LowSpeedObserverDeltaThetaK = LowSpeedObserverDeltaTheta_K;
    Startup.ForcedSpeed1 = ForcedSpeed_1;
    Startup.ForcedSpeed2 = ForcedSpeed_2;
    Startup.ForcedSpeedLoopPeriod = ForcedSpeedLoop_Period;
    Startup.ForcedSpeedNegativeValue1 = ForcedSpeed_NegativeValue1;
    Startup.ForcedSpeedNegativeValue2 = ForcedSpeed_NegativeValue2;
    LPF1_YH = 0;
    LPF1_YL = 0;
    LPF1_K = 5000;
    LowSpeedObserver.state = 1;
}

/*  -------------------------------------------------------------------------------------------------
    Function Name  : StartupState
    Description    : 启动状态机控制
    Date           : 2022-07-23
    Parameter      : None
    ------------------------------------------------------------------------------------------------- */

void StartupState(void)
{
    switch (LowSpeedObserver.state)
        {
            case 1:
               MCLowSpeedObserverFunction();                   //44us执行时间
               if (LowSpeedObserver.LowSpeedObserverOmega_32.s16[0] > 4000)                       //转速大于设定值时开始计数
               {
                   if (LowSpeedObserver.Switch_Count < 400)
                   {
                       LowSpeedObserver.Switch_Count++;
                   }
               }
               else
               {
                   if (LowSpeedObserver.Switch_Count > 1)
                   {
                       LowSpeedObserver.Switch_Count = LowSpeedObserver.Switch_Count - 1;
                   }
               }
               if (LowSpeedObserver.Switch_Count > 200)                   //计数超过设定值时切入闭环，防止逆风误判断切入内部估算器
               {
									 memset(&LowSpeedObserver, 0, sizeof(MCLowSpeedObserver));
                   LowSpeedObserver.state = 2;
                   LowSpeedObserver.ThetaDelta = FOC__THETA - FOC__ETHETA + LowSpeedObserver.LowSpeedObserverDeltaTheta_32.s16[0];                    
                   LowSpeedObserver.Smoothswith_Count = 0;
               }  
  
               break;
            case 2:
                SetBit(FOC_CR1, ANGM);
                LowSpeedObserver.state = 3;
                break;
            case 3:
//                if (FOC_EK3 < OBS_K3T1)
//                {
//                    FOC_EK3 = FOC_EK3 + 1;
//                }
//                else
//                {
//                    FOC_EK3 = OBS_K3T1;
//                }
                if (LowSpeedObserver.Smoothswith_Count < 16)
                {
                    LowSpeedObserver.Smoothswith_Count++;
                    FOC__THETA = FOC__ETHETA + ((LowSpeedObserver.ThetaDelta >> 4)*(16 - LowSpeedObserver.Smoothswith_Count));              
                }
                if  (Startup.BEMFLPFK > OBS_EA_KS)
                {
                    Startup.BEMFLPFK = Startup.BEMFLPFK - 10;                    
                }
                else
                {
                    Startup.BEMFLPFK = OBS_EA_KS;
                }
                FOC_EKLPFMIN = Startup.BEMFLPFK;
                break;
            default:
                break;
        }
}