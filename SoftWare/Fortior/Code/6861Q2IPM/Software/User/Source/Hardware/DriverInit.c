/* --------------------------- (C) COPYRIGHT 2020 Fortiortech ShenZhen -----------------------------
    File Name      : DriverInit.c
    Author         : Fortiortech  Appliction Team
    Version        : V1.0
    Date           : 2020-09-29
    Description    : This file contains driver initial function used for Motor Control.
----------------------------------------------------------------------------------------------------  
                                       All Rights Reserved
------------------------------------------------------------------------------------------------- */
/* Includes -------------------------------------------------------------------------------------*/
#include <FU68xx_2.h>
#include <Myproject.h>

/* -------------------------------------------------------------------------------------------------
    Function Name  : Driver_Init
    Description    : Driver初始化配置
    Date           : 2020-09-29
    Parameter      : None
------------------------------------------------------------------------------------------------- */
void Driver_Init(void)
{
    /* -----配置PWM周期值和死区时间----- */    
	DRV_ARR 			= PWM_VALUE_LOAD;     										               // 载波频率的周期值
	DRV_DTR 			= PWM_LOAD_DEADTIME;			                                           // 死区时间

    /* -----
    MESEL为0，ME模块工作在BLDC模式
	MESEL为1，ME模块工作在FOC/SVPWM/SPWM模式
    ----- */ 
	SetBit(DRV_CR, MESEL);

    /* -----驱动有效电平和空闲电平----- */
	#if (PWM_Level_Mode == High_Level)
	{
		DRV_CMR = 0x003f;
		DRV_OUT = 0xC0;
	}
	#elif (PWM_Level_Mode == Low_Level)
	{
		DRV_CMR = 0x0fc0;
		DRV_OUT = 0x3F;
	}
	#elif (PWM_Level_Mode == UP_H_DOWN_L)
	{
		DRV_CMR = 0x0540;
		DRV_OUT = 0x2A;
	}
	#elif (PWM_Level_Mode == UP_L_DOWN_H)
	{
		DRV_CMR = 0x0a80;
		DRV_OUT = 0x15;
	}
    #endif
    /* -----清中断标志位，使能中断，配置比较值，设置中断优先级----- */
	ClrBit(DRV_SR, DCIF);                                                                          // 清除DRV中断标志位

    /* -----  
    DRV比较匹配中断模式
    当计数值等于DRV_COMR时，根据DCIM的设置判断是否产生中断标记
    00：不产生中断
    01：上升方向
    10：下降方向
    11：上升/下降方向
    ----- */ 
 	SetReg(DRV_SR, DCIM0 | DCIM1, DCIM1);
  
    /* -----设置DRV计数器的比较匹配值，当DRV计数值与COMR相等时，根据DRV_SR寄存器的DCIM是否产生比较匹配事件----- */
	DRV_COMR = 1;
  
	PDRV1 = 1;                                                                                     // 中断优先级设置为2，优先级低于FO硬件过流
	PDRV0 = 0;
  
  ClrBit(DRV_SR, DCIP);		                                                                   // 0--1个载波周期执行一次foc中断，1--2个载波周期执行一次foc中断

    /* -----DRV计数器使能，0-禁止，1-使能----- */
	SetBit(DRV_CR, DRVEN);

    /* -----DRV计数器比较值预装载使能，0-禁止，1-使能----- */
	ClrBit(DRV_CR, DRPE);

    /* -----Driver 输出使能，0-禁止，1-使能----- */
	SetBit(DRV_CR, DRVOE);

}


