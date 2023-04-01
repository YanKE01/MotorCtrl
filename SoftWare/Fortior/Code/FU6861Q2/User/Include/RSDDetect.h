/**************************** (C) COPYRIGHT 2017 Fortiortech shenzhen *****************************
* File Name          : RSDDetect.h
* Author             : Vina Peng, Fortiortech Appliction Team
* Version            : V1.0
* Date               : 10-Apr-2017
* Description        : This file contains all the common data types used for
*                      Motor Control.
***************************************************************************************************
* All Rights Reserved
**************************************************************************************************/
#ifndef __RSDDETECT_H_
#define __RSDDETECT_H_
/****************************RSD参数变量**************************/
typedef struct
{
    uint16  RSDStepTime[4];      // 一个脉冲的周期值
    uint16  RSDTimes;            // 进入RSD中断次数
    uint16  RSDPeriod;           // 1/4圈的周期值,除数不能超过16位
    int16   RSDCount;            // RSD的脉冲数
//	  uint16  TestRSDCount;            // RSD的脉冲数
    int16   RSDState;            // RSD的状态
    uint32  RSDSpeed;            // RSD的速度
    uint8   RSDDIR;              // TIM2_RSD得到的顺逆风方向
    int8    RSDFlag;             // RSD的标志
    uint8   RSDCCWFlag;          // 反转的强弱标志
    uint8   RSDCCWTimes;         // 反转刹车的次数
    uint32  RSDSpeedBase;        // RSD的速度基准
    uint16  RSDCCWSBRCnt;        // RSD反转后启动前刹车计数
    uint8   RSDStep;             // 周期值计数
    uint8   RSDBRFlag;           // RSD反转后启动前刹车标志
	  int16   RSDTheta;
	  int16   RSDTempSpeed;
}MotorRSDTypeDef;
#define   RSDSpeedBaseStep			(int32)(32767.0/4.0*(TIM2_Fre*60/Pole_Pairs/MOTOR_SPEED_BASE))

#define 	Forward 	 				(0)
#define 	Reverse						(1)
#define 	Static						(2)

extern MotorRSDTypeDef     idata    RSDDetect;//用于读寄存器的值，需Idata

#define		BaseTimerFre								(1000)			//Hz
#define		ThailWindSpeedBase					((BaseTimerFre/2)*60/Pole_Pairs)//该处除以2是因为计数器只计算了一半的角度。
#define		ThailWindSpeedBase_zhouqi		(BaseTimerFre*60/Pole_Pairs)
#define		TailWindStartMinSpeed		    (uint16)(4000.0/TailWind_Time*60.0/Pole_Pairs)		//顺风启动的最低转速

extern void Time2_RSD_Init(void);
extern void CMP_RSD_Init(void);
extern void RSDDealwith(void);
extern void RSDFRDetect(void);
extern void RSDDetectInit(void);
extern void RSDFOCCloseLoopStart(void);

/****************************end RSD参数变量*******************************/

#endif