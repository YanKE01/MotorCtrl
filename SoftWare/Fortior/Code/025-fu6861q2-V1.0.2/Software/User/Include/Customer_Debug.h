/**************************** (C) COPYRIGHT 2017 Fortiortech Shenzhen ******************************
* File Name          : Customer_Debug.h
* Author             : Fortiortech Appliction Team
* Version            : V1.0
* Date               : 2017-12-27
* Description        :
****************************************************************************************************
* All Rights Reserved
***************************************************************************************************/

#ifndef __CUSTOMER_DEBUG_H__
#define __CUSTOMER_DEBUG_H__

/**************************************************************************************************///Including Header Files
#include <Myproject.h>
/**************************************************************************************************///Define Macro
/*SPI DBG模块配置--------------------------------------------------------------*/
 /*
 * 使用说明
 * 1.本模块通过SPI接口与"SPI_Monitor"硬件模块相连，"SPI_Monitor"将会把数据转换成模拟信号。
 * 2.本模块有两种工作模式：硬件DBG模式和软件DBG模式。
 * 3.硬件DBG模式：填写要发送的数据的首地址，单片机将会发送地址连续的8个字节数据。
 *   在本模式下，客户仅需要修改的以下宏定义的参数(必须是地址值)：
 *               HARD_SPIDATA
 *
 * 4.软件方式：填写想要发送的4个数据，程序会定期更新将要发送数据，然后单片机将发送这些数据。
 *   在本模式下，客户仅需要修改的以下4个宏定义的参数(可以是常数、全局变量名、XSFR的寄存器名)：
 *               SOFT_SPIDATA0
 *               SOFT_SPIDATA1
 *               SOFT_SPIDATA2
 *               SOFT_SPIDATA3
 *
 * 注意事项
 * 1.宏定义"SPI_DBG_SW"和"SPI_DBG_HW"不能同时定义，必须注释掉不需要用的一个
 *
 * 常用参数
 * FOC__ID FOC__THETA FOC__IA FOC__EALP FOC__POW ADC0_DR FOC__VBET FOC__VALP FOC_VBET FOC_EOME FOC_THETA
 *
 */

//#define SPI_DBG_SW                                                             // SPI DBG 使用软件DBG模式
//#define SPI_DBG_HW                                                             // SPI DBG使用硬件DBG模式

 //软件DBG的参数
 #define SOFT_SPIDATA0                  ReadBit(CMP_SR, CMP1OUT)*30000//FOC__THETA//ReadBit(CMP_SR, CMP0OUT)*30000//CMP0OUT*30000//160*(ADC3_DR-2048)//20*(ADC3_DR*8-16383)//PI1_EK*10//20*(ADC3_DR*8-16383)//20*(ADC3_DR*8-16383)//mcSpeedRamp.ActualValue*10 //mcFocCtrl.CtrlMode*30000
 #define SOFT_SPIDATA1                  ReadBit(CMP_SR, CMP1OUT)*30000//RSDDetect.RSDTempSpeed*2//FOC__EOME*2//RSDDetect.RSDCount*3000//mcFocCtrl.TestPin//TIM2__CNTR*3000//mcFocCtrl.TestPin*30000//RSDDetect.RSDCount*3000//mcFocCtrl.TestPin*30000//mcFocCtrl.CtrlMode*30000//mcFocCtrl.mcDcbusFlt//mcFocCtrl.mcDcbusFlt*2//mcFocCtrl.Powerlpf*10
 #define SOFT_SPIDATA2                  ReadBit(CMP_SR, CMP0OUT)*30000//PI1_UKH*10
 #define SOFT_SPIDATA3                  FOC__VALP


 // 硬件DBG的参数首地址
 #define HARD_SPIDATA                   FOC__THETA

 extern uint16 xdata spidebug[4];
/*GPIO DBG模块配置--------------------------------------------------------------*/

 // GP01 DBG信号配置
 #define GP01_DISABLE                   0x00                                    // 禁能GP01的DBG信号
 #define GP01_BEMFZero                  DBGSEL0                                 // GP01输出方波屏蔽续流结束和检测到过零点信号
 #define GP01_ADCTrigger                DBGSEL1                                 // GP01ADC trigger信号
 #define GP01_CMPSample                 DBGSEL1 | DBGSEL0                       // GP01比较器采样区间信号

 #define GP01_DBG_Conf                  (GP01_DISABLE)                          // GP01信号选择

 // GP07 DBG信号配置
 #define GP07_DISABLE                   0x00                                    // 禁能GP07的比较器信号输出
 #define GP07_CMP0                      CMPSEL0                                 // 输出CMP0
 #define GP07_CMP1                      CMPSEL1                                 // 输出CMP1
 #define GP07_CMP2                      CMPSEL1 | CMPSEL0                       // 输出CMP2
 #define GP07_CMP3                      CMPSEL2                                 // 输出CMP3
 #define GP07_CMP4                      CMPSEL2 | CMPSEL0                       // 输出CMP4
 #define CP07_CMPADC                    CMPSEL2 | CMPSEL1 | CMPSEL0             // 输出ADC结果比较信号

 #define GP07_DBG_Conf                  (GP07_CMP1)                          // GP07信号选择

#endif