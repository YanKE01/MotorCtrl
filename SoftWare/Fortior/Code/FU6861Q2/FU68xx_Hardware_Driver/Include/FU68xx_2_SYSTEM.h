/**************************** (C) COPYRIGHT 2017 Fortiortech shenzhen *****************************
* File Name          : FU6812_19_SYSTEM.h
* Author             : Vina Peng, Fortiortech Appliction Team
* Version            : V1.0
* Date               : 10-Apr-2017
* Description        : This file contains all the common data types used for
*                      Motor Control.
***************************************************************************************************
* All Rights Reserved
**************************************************************************************************/

/* Define to prevent recursive inclusion --------------------------------------------------------*/
#ifndef __FU6812_19_SYSTEM_H_
#define __FU6812_19_SYSTEM_H_

/* Includes -------------------------------------------------------------------------------------*/
// #include <absacc.h>

/* System Clock Config---------------------------------------------------------------------------*/

#define InternalFastClock    0
#define ExternalFastClock    1

/*-------------------------------------------------------------------------------------------------
	Function Name :	InternalFastClockConfig(Status)
	Description   :	内部快时钟配置，强制使能内部快时钟晶振电路，切换系统时钟为内部快时钟
	Input         :	Statue--使能控制，Disable或Enable
  Output				:	None
-------------------------------------------------------------------------------------------------*/
extern void InternalFastClockConfig(uint8 Status);


/*-------------------------------------------------------------------------------------------------
	Function Name :	SystemFastClockConfig(Mode)
	Description   :	系统快时钟在线切换，外部快时钟默认为无源晶体模式。
	Input         :	Mode--系统快时钟模式，InternalFastClock或ExternalFastClock
  Output				:	None
-------------------------------------------------------------------------------------------------*/
extern void SystemFastClockConfig(uint8 Mode);


/*-------------------------------------------------------------------------------------------------
	Function Name :	ExternalSlowClockConfig(Status)
	Description   :	外部慢时钟配置，使能外部慢时钟晶振电路
	Input         :	Statue--使能控制，Disable或Enable
  Output				:	None
-------------------------------------------------------------------------------------------------*/
extern void ExternalSlowClockConfig(uint8 Status);


/* System Power Config---------------------------------------------------------------------------*/
//#define VREF4_5			0
//#define VREF5_0			1
//#define VREF3_0         2
//#define VREF4_0			3


/*-------------------------------------------------------------------------------------------------
	Function Name :	LVDPowerDownDetectConfig(Status)
	Description   :	掉电检测使能，检测到VCC电压低于设定值后触发预警或者VDD5电压低于设定
	                值后触发复位。
	Input         :	Statue--使能控制，1--Disable或0--Enable
  Output				:	None
-------------------------------------------------------------------------------------------------*/
extern void LVDPowerDownDetectConfig(uint8 Status);


/*-------------------------------------------------------------------------------------------------
	Function Name :	LVDPowerDownWarnIEConfig(Status)
	Description   :	掉电低压预警中断使能，检测到VCC电压低于设定值后触发预警，如果低压预
                  警中断则响应中断。
	Input         :	Statue--使能控制，Disable或Enable
  Output				:	None
-------------------------------------------------------------------------------------------------*/
extern void LVDPowerDownWarnIEConfig(uint8 Status);


/*-------------------------------------------------------------------------------------------------
	Function Name :	VREFConfig(Value, Status)
	Description   :	参考电压VREF配置，如果使能VREF模块，则内部产生VREF输入到ADC作为ADC
									参考电压，如果禁止VREF模块，则由外部提供VREF输入到ADC作为ADC参考电压。
	Input         :	Value--VCC低电压预警值
                  0: VREF3_0, 参考电压VREF输出为3.0V
									1: VREF4_0, 参考电压VREF输出为4.0V
									2: VREF4_5, 参考电压VREF输出为4.5V
									3: VREF5_0, 参考电压VREF输出为5.0V
                  Statue--使能控制，Disable或Enable。
  Output				:	None
-------------------------------------------------------------------------------------------------*/
extern void VREFConfig(uint8 Status);


/*-------------------------------------------------------------------------------------------------
	Function Name :	VHALFConfig(Mode, Status)
	Description   :	基准电压VHALF配置，使能VHALF工作模块，选择VREF/2作为基准
									电压VHALF输出，VHALF可用作运放基准电压。
	Input         : Statue--使能控制，Disable或Enable。
  Output				:	None
-------------------------------------------------------------------------------------------------*/
extern void VHALFConfig( uint8 Status);


/* WatchDog Config-------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------
	Function Name ：void WatchDogRefresh(void
	Description   ：看门狗定时函数初始化，看门狗使能和复位使能，定时配置
	Input         ：Value--定时时间，单位ms，最小定时时间8ms，最大定时1800ms
                  Statue--使能控制，Disable或Enable
  Output				：None
-------------------------------------------------------------------------------------------------*/
extern void WatchDogConfig(uint16 Value, uint8 Status);

/*-------------------------------------------------------------------------------------------------
	Function Name ：WatchDogRefresh(Value ,Status)
	Description   ：刷新看门狗计数器
	Input         ：None
  Output				：None
-------------------------------------------------------------------------------------------------*/
extern void WatchDogRefresh(void);



/* Flash Program Config--------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------
	Function Name :	uint8 Flash_Sector_Erase(uint8 xdata *FlashAddress)
	Description   :	扇区自擦除: 指定将要擦除的Flash扇区，每个扇区128Byte，共128个扇区，
									扇区0~127对应Flash地址0x0000~0x3fff，通过指定Flash地址来指定要擦除
									的Flash地址所在扇区。一次只能擦除一个扇区，自擦除数据为任意值，一定
									要在解锁后才给DPTR赋值。
	Input         :	FlashAddress--Flash自擦除扇区内任意地址
  Output				:	0--Flash自擦除成功，1--Flash自擦除失败
-------------------------------------------------------------------------------------------------*/
extern uint8 Flash_Sector_Erase(uint8 xdata *FlashAddress);

/*-------------------------------------------------------------------------------------------------
	Function Name :	uint8 Flash_Sector_Write(uint8 xdata *FlashAddress, uint8 FlashData)
	Description   :	Flash自烧写: 对扇区预编程和自擦除后，可以对扇区内的地址进行Flash烧写，
                  一次烧写一个byte,一定要在解锁后才给DPTR赋值
	Input         :	FlashAddress--Flash烧写地址
									FlashData--Flash烧写数据
  Output				:	0--Flash自烧写成功，1--Flash自烧写失败
-------------------------------------------------------------------------------------------------*/
extern uint8 Flash_Sector_Write(uint8 xdata *FlashAddress, uint8 FlashData);


#endif
