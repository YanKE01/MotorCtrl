/* --------------------------- (C) COPYRIGHT 2021 Fortiortech -------- -----------------------------
    File Name      : SanityCheck.h
    Author         : Fortiortech  Appliction Team
    Version        : V1.1
    Date           : 2021-12-02
    Description    : This file contains .H file function used for check Customer.h set.
----------------------------------------------------------------------------------------------------
                                       All Rights Reserved
------------------------------------------------------------------------------------------------- */
#ifndef __SANITYCHECK_H_
#define __SANITYCHECK_H_
#include <Customer.h>
#include <Develop.h>
     #if (PosCheckEnable==1)
      #error "data 20220616,RPD Program has not been added"
     #endif
//     #if ((AO_Enable==1) &&(EstimateAlgorithm == PLL))
//      #error "AO_Enable must match `EstimateAlgorithm = SMO`"
//     #endif

//#if (DBG_MODE == DBG_UART)
//    #error "data 20220622, UART debug Program has not been added"
//#endif





    /* 驱动电平配置检查 */
    #if (PWM_Level_Mode != High_Level && PWM_Level_Mode != Low_Level && PWM_Level_Mode != UP_H_DOWN_L && PWM_Level_Mode != UP_L_DOWN_H)
        #error " PWM_Level_Mode err.[Set: High_Level,Low_Level,UP_H_DOWN_L,UP_L_DOWN_H]"
    #endif

    /* VREF参考电压配置检查 */
//    #if (HW_ADC_VREF == VREF3_0 || HW_ADC_VREF == VREF4_0 || HW_ADC_VREF == VREF4_5)
//        #if (VREF_OUT_EN == 0)
//          #error " VREF err.[Enable P3.5 AN function]"
//        #endif
//    #elif (HW_ADC_VREF == VREF5_0)

//    #else
//        #error " VREF error.[VREF can only be VREF3_0  VREF4_0  VREF4_5  VREF5_0] "  
//    #endif

    /*  运放配置检查 */
//    #if (HW_AMP_MODE == AMP_PGA_DUAL)
//        #if (HW_AMPGAIN != AMP2x && HW_AMPGAIN != AMP4x && HW_AMPGAIN != AMP8x && HW_AMPGAIN != AMP16x)
//            #error " Amp gain error.[Internal PGA gain can only be AMP2x  AMP4x  AMP8x  AMP16x] "  
//        #endif
//    #elif (HW_AMP_MODE == AMP_NOMAL)
//    #else
//        #error "Amp mode error.[Set: AMP_NOMAL or AMP_PGA_DUAL]"
//    #endif
    
    /*  采样模式配置检查 */
    #if (Shunt_Resistor_Mode != Single_Resistor && Shunt_Resistor_Mode != Double_Resistor && Shunt_Resistor_Mode != Three_Resistor )
        #error " Shunt_Resistor_Mode error.[Set: Single_Resistor / Double_Resistor / Three_Resistor] "  
    #endif
 
    /*  顺逆风设置 */
    #if (TailWind_Mode != NoTailWind && TailWind_Mode != RSDMethod && TailWind_Mode != BEMFMethod )
        #error " TailWind_Mode error.[Set: NoTailWind / RSDMethod / BEMFMethod / FOCMethod] "  
    #endif
    

    /*  硬件过流值检测 */
//    #if (DAC_OverCurrentValue  > 0xff)
//        #error " DAC_OverCurrentValue error.[data overflow] "  
//    #endif



 
#endif