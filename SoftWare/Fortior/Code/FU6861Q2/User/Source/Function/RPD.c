///******************** (C) COPYRIGHT 2017 Fortiortech shenzhen******************
//* File Name          : RPD.c
//* Author             : Vina Peng,Fortiortech  Appliction Team
//* Version            : V1.0
//* Date               : 10-Apr-2017
//* Description        : This file contains init position detection used for
//*                      Motor Control.
//********************************************************************************
//* All Rights Reserved
//*
//*******************************************************************************/
//#include <FU68xx_2.h>
//#include <Myproject.h>

///* Private define -------------------------------------------------------------------------------*/

//RPD_TypeDef RPD_Status;
//RPD_Param_TypeDef RPDPara;



//void RPD_Init(void)
//{
//  RPD_Status=RPD_0;
////    RPDPara.insertFlag=0;
//  RPDPara.DetectCount[0] = 0;
//  RPDPara.DetectCount[1] = 0;
//  RPDPara.DetectCount[2] = 0;
//  RPDPara.DetectCount[3] = 0;
//  RPDPara.DetectCount[4] = 0;
//  RPDPara.DetectCount[5] = 0;
//  RPDPara.DetectCount[6] = 0;
//  RPDPara.DetectCount[7] = 0;
//  RPDPara.InsetCount[0] = 0;
//  RPDPara.InsetCount[1] = 0;
//  RPDPara.InsetCount[2] = 0;
//  RPDPara.InsetCount[3] = 0;
//  RPDPara.InsetCount[4] = 0;
//  RPDPara.InsetCount[5] = 0;
//  RPDPara.InsetCount[6] = 0;
//  RPDPara.InsetCount[7] = 0;
//  RPDPara.U_Offset   = (mcCurOffset.IuOffset-16383)>>6;
//  RPDPara.V_Offset   = (mcCurOffset.IvOffset-16383)>>6;
//  RPDPara.W_Offset   = (mcCurOffset.Iw_busOffset-16383)>>6;
//  RPDPara.injectmin=0;
//  RPDPara.injectmid=0;
//  RPDPara.ThetaGet =0xFF;
//  RPDPara.injecttimes=0;

//}

///*---------------------------------------------------------------------------*/
///* Name       :   void Time2_RPD_Init(void)
///* Input  :   NO
///* Output :   NO
///* Description:   RPD对应Time2的初始化
///*---------------------------------------------------------------------------*/
//void Time2_RPD_Init(void)
//{
//  /*-------------------------------------------------------------------------------------------------
//  先停止计数，配置完寄存器后，最后启动计数
//-------------------------------------------------------------------------------------------------*/
//  ClrBit(TIM2_CR1, T2EN);                                    // 0，停止计数；1,使能计数

///*-------------------------------------------------------------------------------------------------
//  时钟分频设置(TIM2_PSC)
//  000:cpuclk(24MHz)           001:cpuclk/2^1(12MHz)   010:cpuclk/2^2(6MHz)    011:cpuclk/2^3(3MHz)
//  100:cpuclk/2^4(1.5MHz)  101:cpuclk/2^5(750KHz)  110:cpuclk/2^6(375KHz)  111:cpuclk/2^7(187.5KHz)
//-------------------------------------------------------------------------------------------------*/
//      #if (InjectTime == Short_Inject)
//      {
//          SetReg(TIM2_CR0, T2PSC0 | T2PSC1 | T2PSC2, 0x00);
//      }
//      #elif (InjectTime == Long_Inject)
//      {
//          SetReg(TIM2_CR0, T2PSC0 | T2PSC1 | T2PSC2, T2PSC0);
//      }
//      #endif

//  /*-------------------------------------------------------------------------------------------------
//  /模式选择
//  TIM2_MOD1，TIM2_MOD0
//  00--输入Timer模式；01--输出模式
//  10--输入Count模式；11--QEP或者RSD模式
//-------------------------------------------------------------------------------------------------*/
//  SetReg(TIM2_CR0, T2MOD0 | T2MOD1, T2MOD0);

//  SetBit(TIM2_CR1, T2FE);                                    // 滤波使能
///*-------------------------------------------------------------------------------------------------
//  清除中断标志位
//  不配置中断
//-------------------------------------------------------------------------------------------------*/
//  ClrBit(TIM2_CR1, T2IR | T2IP | T2IF);


//  ClrBit(TIM2_CR0, T2IRE | T2CES);                     // QEP&RSD方向改变事件
//  ClrBit(TIM2_CR1, T2IPE | T2IFE);                             // 清零上升沿检测中断

///*-------------------------------------------------------------------------------------------------
//  配置周期值、比较值、计数值
//  禁止PWM周期检测中断使能
//  使能计数器上溢中断使能
//-------------------------------------------------------------------------------------------------*/
//  TIM2__CNTR = 0;
//  TIM2__ARR = 0xFFFF;

//}
//void RPD (void)
//{
//  if(mcFocCtrl.State_Count == 0)                         // RPD每拍执行时间
//   {
//    if(McStaSet.SetFlag.PosiCheckSetFlag  ==0)// 初始化RPD配置
//    {
//      McStaSet.SetFlag.PosiCheckSetFlag =1;
//      RPD_Init();                         // RPD变量初始化
//      Time2_RPD_Init();                   // RPD的Time2初始化
//      SetBit(PI_LPF_CR, T2RPD);               // 使能RPD,即当比较器3产生中断，对应的Time2的计数器的数据会保存，关闭MOE，停止TIM2计数
//      MOE = 0;                              // 关闭MOE
//      DRV_DR = DRV_ARR+1;
//      ClrBit(DRV_CR, OCS);                  // 计数器比较值来源，0-方波；1-FOC,SVPWM,SPWM
//      SetBit(DAC_CR, DACEN);              // 使能DAC
//      SetBit(DAC_CR, DACMOD);             // 0: 正常模式，DAC输出电压范围为0到VREF。1: 半电压转换模式，DAC输出电压范围为VHALF到VREF。
//      #if (Shunt_Resistor_Mode != Three_Resistor)
//      {
//        //DAC_DR = DAC_RPDCurValue;
//              DAC_DR = 200;
//      }
//      #endif
//      }
//          MOE = 0;                            // 关闭MOE
//      ClrBit(TIM2_CR1, T2EN);               // 关闭TIM2
//      TIM2__CNTR=0;                       // TIM2计数值清零
//        RPD_Inject();                         // RPD注入的时序及角度判断
//    if(RPD_Status!=RPD_7)                 //???
//      {
//          MOE = 1;                              // 打开MOE
//          SetBit(TIM2_CR1, T2EN);               // 启动TIM2,确保每拍使能的时间相同
//      }
//      else
//      {
//        DRV_CMR &= 0xFFC0;
//            mcFocCtrl.mcPosCheckAngle=_Q15((float)RPDPara.ThetaGet/180.0);
//              mcState = mcAlign;
//              mcFocCtrl.State_Count = Align_Time;
//        /******************************
//        0: 正常模式，DAC输出电压范围为0到VREF，适用于硬件过流保护
//        1: 半电压转换模式，DAC输出电压范围为VHALF到VREF
//        ****************************/
//        ClrBit(DAC_CR, DACMOD );
//        /**********设置DAC过流值*****************/
//        DAC_DR = DAC_OvercurrentValue;
//      }

//  mcFocCtrl.State_Count=RPD_Time;           // RPD每拍执行时间
//  }
//}

