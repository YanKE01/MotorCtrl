/**
 * @copyright (C) COPYRIGHT 2022 Fortiortech Shenzhen
 * @file      AMPInit.c
 * @author    Fortiortech  Appliction Team
 * @since     Create:2021-05-14
 * @date      Last modify:2022-07-14
 * @brief     This file contains AMP initial function used for Motor Control.
 */ 
 
#include <FU68xx_2.h>
#include <Myproject.h>

/**
 * @brief      AMP初始化配置
 */
void AMP_Init(void)
{
    /* -----使能VHALF电压----- */
    SetBit(VREF_VHALF_CR, VHALFEN);                         // 使能VHALF
     
    /* -----运放使能----- */
    #if (Shunt_Resistor_Mode == Single_Resistor)            // 单电阻电流采样
    {
        #if (HW_AMP_MODE == AMP_NOMAL) //外部放大
        {
            SetBit(P3_AN, P31);             //AMP0 Pin设置为模拟模式  +
            SetBit(P3_AN, P30);             //AMP0 Pin设置为模拟模式  -
            SetBit(P2_AN, P27);             //AMP0 Pin设置为模拟模式  O
            SetBit(AMP_CR, AMP0EN);         //使能AMP0 
            ClrBit(CMP_AMP, AMP0_GAIN2);
            ClrBit(CMP_AMP, AMP0_GAIN1);
            ClrBit(CMP_AMP, AMP0_GAIN0);
        }
        #else       // 内部PGA双端差分输入
        {
            SetBit(P3_AN, P31);             //AMP0 Pin设置为模拟模式  +
            SetBit(P3_AN, P30);             //AMP0 Pin设置为模拟模式  -
            SetBit(P2_AN, P27);             //AMP0 Pin设置为模拟模式  O
            
            ClrBit(AMP_CR0, AMP0M_GND);     // 禁止运放反向输入端内部接地
            SetBit(AMP_CR0, AMP0EN);        // 使能AMP0 
            
            #if (HW_AMPGAIN == AMP2x)
            {
                ClrBit(CMP_AMP, AMP0_GAIN2);
                ClrBit(CMP_AMP, AMP0_GAIN1);
                SetBit(CMP_AMP, AMP0_GAIN0);
            }
            #elif (HW_AMPGAIN == AMP4x)
            {
                ClrBit(CMP_AMP, AMP0_GAIN2);
                SetBit(CMP_AMP, AMP0_GAIN1);
                ClrBit(CMP_AMP, AMP0_GAIN0);
            }
            #elif (HW_AMPGAIN == AMP8x)
            {
                ClrBit(CMP_AMP, AMP0_GAIN2);
                SetBit(CMP_AMP, AMP0_GAIN1);
                SetBit(CMP_AMP, AMP0_GAIN0);
            }
            #elif (HW_AMPGAIN == AMP16x)
            {
                SetBit(CMP_AMP, AMP0_GAIN2);
                ClrBit(CMP_AMP, AMP0_GAIN1);
                ClrBit(CMP_AMP, AMP0_GAIN0);
            }
            #endif
        }
        #endif      
        
        
        
       
    }
    #else                                                   // 双/三电阻电流采样
    {
        SetBit(P1_AN, P16);             //AMP1 Pin设置为模拟模式  +
        SetBit(P1_AN, P17);             //AMP1 Pin设置为模拟模式  -
        SetBit(P2_AN, P20);             //AMP1 Pin设置为模拟模式  O

        SetBit(P2_AN, P21);             //AMP2 Pin设置为模拟模式  +
        SetBit(P2_AN, P22);             //AMP2 Pin设置为模拟模式  -
        SetBit(P2_AN, P23);             //AMP2 Pin设置为模拟模式  O
        ClrBit(P2_OE, P23);             //P23_OE需要强制为0，禁止DA1输出至PAD

        SetBit(P3_AN, P31);             //AMP0 Pin设置为模拟模式  +
        SetBit(P3_AN, P30);             //AMP0 Pin设置为模拟模式  -
        SetBit(P2_AN, P27);             //AMP0 Pin设置为模拟模式  O
        
        ClrBit(TSD_ADJ, AMP0M_GND);     // 禁止运放0反向输入端内部接地
        ClrBit(TSD_ADJ, AMP12M_GND);    // 禁止运放1,2反向输入端内部接地
        SetBit(AMP_CR, AMP0EN);         //使能AMP0  
        SetBit(AMP_CR, AMP1EN);         //使能AMP1  
        SetBit(AMP_CR, AMP2EN);         //使能AMP2  
        
        #if (HW_AMP_MODE == AMP_NOMAL)  //外部放大
        {
            ClrBit(CMP_AMP, AMP0_GAIN2);
            ClrBit(CMP_AMP, AMP0_GAIN1);
            ClrBit(CMP_AMP, AMP0_GAIN0);
    
            ClrBit(CMP_AMP, AMP_PH_GAIN2);
            ClrBit(CMP_AMP, AMP_PH_GAIN1);
            ClrBit(CMP_AMP, AMP_PH_GAIN0);
        }
        #else
        {
            #if (HW_AMPGAIN == AMP2x)
            {
                ClrBit(CMP_AMP, AMP0_GAIN2);
                ClrBit(CMP_AMP, AMP0_GAIN1);
                SetBit(CMP_AMP, AMP0_GAIN0);
    
                ClrBit(CMP_AMP, AMP_PH_GAIN2);
                ClrBit(CMP_AMP, AMP_PH_GAIN1);
                SetBit(CMP_AMP, AMP_PH_GAIN0);
            }
            #elif (HW_AMPGAIN == AMP4x)
            {
                ClrBit(CMP_AMP, AMP0_GAIN2);
                SetBit(CMP_AMP, AMP0_GAIN1);
                ClrBit(CMP_AMP, AMP0_GAIN0);
    
                ClrBit(CMP_AMP, AMP_PH_GAIN2);
                SetBit(CMP_AMP, AMP_PH_GAIN1);
                ClrBit(CMP_AMP, AMP_PH_GAIN0);
            }
            #elif (HW_AMPGAIN == AMP8x)
            {
                ClrBit(CMP_AMP, AMP0_GAIN2);
                SetBit(CMP_AMP, AMP0_GAIN1);
                SetBit(CMP_AMP, AMP0_GAIN0);
    
                ClrBit(CMP_AMP, AMP_PH_GAIN2);
                SetBit(CMP_AMP, AMP_PH_GAIN1);
                SetBit(CMP_AMP, AMP_PH_GAIN0);
            }
            #elif (HW_AMPGAIN == AMP16x)
            {
                SetBit(CMP_AMP, AMP0_GAIN2);
                ClrBit(CMP_AMP, AMP0_GAIN1);
                ClrBit(CMP_AMP, AMP0_GAIN0);
    
                SetBit(CMP_AMP, AMP_PH_GAIN2);
                ClrBit(CMP_AMP, AMP_PH_GAIN1);
                ClrBit(CMP_AMP, AMP_PH_GAIN0);
            }
            #endif
        }
        #endif     
    }
    #endif
}
