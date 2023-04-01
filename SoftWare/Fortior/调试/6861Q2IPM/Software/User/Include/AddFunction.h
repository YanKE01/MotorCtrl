/* --------------------------- (C) COPYRIGHT 2020 Fortiortech ShenZhen -----------------------------
    File Name      : AddFunction.h
    Author         : Fortiortech  Appliction Team
    Version        : V1.0
    Date           : 2020-09-30
    Description    : This file contains  function used for Motor Control.
----------------------------------------------------------------------------------------------------
                                       All Rights Reserved
------------------------------------------------------------------------------------------------- */

/* Define to prevent recursive inclusion -------------------------------------------------------- */
#ifndef __ADD_FUNCTION_H_
#define __ADD_FUNCTION_H_

/* Exported types -------------------------------------------------------------------------------*/
typedef struct
{
    uint8	  overCurCnt;          	                                                               // 软件过流计数

    uint16    abs_ia;				                                                               // IA的绝对值
    uint16    abs_ib;				                                                               // IB的绝对值
    uint16    abs_ic;				                                                               // IC的绝对值

    uint16    max_ia;				                                                               // IA的最大值
    uint16    max_ib;				                                                               // IB的最大值
    uint16    max_ic;				                                                               // IC的最大值
}CurrentVarible;




typedef struct
{
    uint8     segment;                                                                             // 分段执行

    uint8     overVoltDetecCnt;                                                                    // 过压检测计数
    uint8 	  underVoltDetecCnt;                                                                   // 欠压检测计数
    uint16    voltRecoverCnt;	                                                                   // 过压恢复计数

    uint16 	  overPowerDetecCnt;                                                                   // 过功率检测次数

    uint16    currentRecoverCnt;                                                                   // 过流保护恢复计数
    uint16    overCurrentRecoverTime;

    uint16    stallDelayCnt;                                                                       // 堵转延迟判断计时
    uint8     stallDectEs;                                                                         // method 1，与ES相关
    uint16    stallDectSpeed;                                                                      // method 2，与速度相关
    uint16    mcStallDeCurrent;                                                                    // 堵转电流检测次数
    uint16    stallReCount;	                                                                       // 堵转保护恢复计数

    uint8     lphasecnt;                                                                           // 缺相保护计时
    uint8     aOpencnt ;                                                                           // A缺相计数
    uint8     bOpencnt ;                                                                           // B缺相计数
    uint8     cOpencnt ;                                                                           // C缺相计数

    uint8     abcOpencnt ;                                                                         // A缺相计数

    uint16    mcLossPHRecCount;                                                                    // 缺相恢复计数
    uint16    mcLossPHRecoverDelayTimes;

    uint8     startSpeedAndESCnt;
    uint8     startESCount;                                                                        // 启动保护判断ES的计数
    uint16    startEsCnt;                                                                          // 启动保护判断ES的计时
    uint16    startDelay;                                                                          // 启动保护判断ES的延迟
    uint16    startFocmode;                                                                        // 启动保护判断FOCMODE状态的计时
    uint16    startSpeedCnt;                                                                       // 启动保护判断速度和ES的计时
    uint16    startRecoverDelayCnt;                                                                // 启动保护恢复延时计数
    uint16    startRecoverDelayTimes;
		uint16    startSMOCnt;

}FaultVarible;

typedef enum
{
    FaultNoSource				= 0,                                                               // 无故障
    FaultHardOVCurrent          = 1,	                                                           // 硬件过流
    FaultSoftOVCurrent	        = 2,                                                               // 软件过流
    FaultUnderVoltage	        = 3,	                                                           // 欠压保护
    FaultOverVoltage            = 4,                                                               // 过压保护
    FaultLossPhase   		    = 5,                                                               // 缺相保护
    FaultStall 			        = 6,                                                               // 堵转保护
    FaultStart       	        = 7,                                                               // 启动保护
    FaultOverwind 	            = 8,	                                                           // 顺逆风失败保护
    FaultOverPower   		    = 9,                                                               // 功率保护
    FaultEepromReadData         = 10,                                                              // EEPROM读取错误
    FaultIbusOffset             = 11,
} FaultStateType;

typedef struct
{
    uint16    adcDcbus;                                                                            // 母线电压
    uint16    adcIbus;                                                                             // 母线电流	
    uint16	  adcVref;                                                                             // ADC参考
} ADCSample;

typedef struct
{
    uint16    ledCount;                                                                            // 闪灯周期计数
    uint8     ledTimCot;                                                                           // 闪灯次数计数
    uint16    counttime;                                                                           // 闪灯周期
    uint16    count;                                                                               // 电平翻转计数
}MCLedDisplay;
typedef struct
{
    uint16    mcDcbusFlt;                                                                          // 母线电压
    uint16    mcIbusFlt;                                                                           // 母线电流
    uint8     ctrlMode;                                                                            // 控制模式
    int16     powerlpf;                                                                            // 功率滤波后的值
    uint16    power;
    float     realPower;

    int16     mcIqref;                                                                             // Q轴给定电流
    int16     speedEOME;                                                                           // 当前速度值
    int16     focThetaTemp;
    int16     theta;
    int16     speedFlt;                                                                            // 当前速度滤波后的值
    uint16    esValue;                                                                             // 当前FOC_ESQU滤波后的值
    uint16    smo_EK2;                                                                             // EK2的调试值
    
    int16	  uqFlt;										                                       // UQ滤波后的值
    int16	  udFlt;										                                       // UD滤波后的值

    int16     isRef;                                                                              
    int16     ipRef;                                                                               // 功率闭环PI计算结果
    
    int16     iqRef;                                                                               // Q 轴参考电流
    int16     idRef;                                                                               // D 轴参考电流

    uint16    dqCurrentKp;
    uint16    dqCurrentKi;

    uint16    runStateCnt;                                                                         // 运行状态计数
    uint8     runStateFlag;                                                                        // 电机运行状态标志
    uint16    speedRampTime;						                                               // 速度环增量时间
    uint16    speedLoopTime;                                                                       // 速度环时间
    uint8     chargeStep;                                                                          // 预充电的步骤
    uint16    state_Count;	                                                                       // 电机各个状态的时间计数

    int16     ek3Ref;
    int16     ek2Ref;

    int16     overPowerFlag;                                                                       // 过功率标志
    int16     overPowerRecoverFlag;                                                                // 过功率恢复标志
    uint16    powerRecoverDelay;                                                                   //降功率恢复时间
    uint16    powerLimitDelay;
    uint16    speedRecoverCount;
    
    uint16    softCurrentValueTemp;
       
   // uint16    mcIsref;
    int16     mcIsref;
     int16   mcIdref ; 
//         int16   mciqref ; 

	  int16  IqRef;                  		   // Q 轴参考电流
		 int16  IdRef;    
}FOCCTRL;


typedef struct
{
	uint16    sleepDelayCout;
	int8      sleepFlag;
    uint8     sleepEn;
    uint8     sleepUpdata;
}SLEEPMODE;


typedef struct
{
    int16     targetValue;
    int16     targetValueOld;
    int16     actualValue;
    int16     incValue;
    int16     decValue;
    int16     delayCount;
    int16     delayPeriod;
    int8      flagONOFF;
}MCRAMP;

typedef struct
{
    int16	  extRef;																			
    int16	  extFed;																	
    int16	  extKP;          															
    int16	  extKI;         																
    int16	  extErr;      																		
    int16	  extOut;    																		
    int16	  extOutMax;    																	
    int16	  extOutMin;    																
} OUTLOOP;

typedef struct
{
    int16     err;		 
    int16     last_err; 		
    int16     prev_err;	

    int16     outMax;
    int16     outMin;  

    float     kp;		 
    float     ki;		   

    int16     lastout;		   
} MPIDTypeDef;

#define CapPWMFilterNUM										(1)					                   //频率控制模式时PWM捕获周期数

/* Exported types -------------------------------------------------------------------------------*/
typedef struct
{
	uint16    pwmINHigh;
	uint32    pwmINPeriod;
	uint16    pwmINHighDuty;
	uint16    pwmINFre;

  uint16    pwmINTime;
	uint16    pwmSpeedRef;
  uint8     flagPWMINHighDuty;
} PWMFREQINPUTTRPE;

/* Exported variables ---------------------------------------------------------------------------*/
extern FaultVarible     idata 	  mcFaultDect;
extern CurrentVarible   idata     mcCurVarible;
extern FaultStateType	xdata	  mcFaultSource;
extern ADCSample        xdata     adcSampleValue;
extern FOCCTRL          xdata 	  mcFocCtrl;
extern MCLedDisplay     xdata     mcLedDisplay;
extern MCRAMP           xdata     mcSpeedRamp;
extern SLEEPMODE        xdata     sleepSet;
extern OUTLOOP		    xdata     speedPICtrl;
extern uint16           xdata     mcIbusFlt;
extern uint32           xdata     mcPowerlpf;
extern uint16           xdata     mcPower;
extern PWMFREQINPUTTRPE idata     mcPWMFreqInputCtrl;
/* Exported functions ---------------------------------------------------------------------------*/
extern void Fault_OverUnderVoltage(FaultVarible *h_Fault);
extern void Fault_Power(FaultVarible *h_Fault);
extern void Fault_Overcurrent(CurrentVarible *h_Cur);
extern void Fault_OverCurrentRecover(FaultVarible *h_Fault);
extern void Fault_OverPowerRecover(FaultVarible *h_Fault);
extern void Fault_Stall(FaultVarible *h_Fault,CurrentVarible *h_Cur);
extern void Fault_phaseloss(FaultVarible *h_Fault);
extern void VariablesPreInit(void);
extern void Fault_Detection(void);
extern void FaultProcess(void);
//extern int16 LPFFunction(int16 Xn1, int16 Xn0, int8 K);
extern void Led_OnOff(MCLedDisplay *hLedDisplay,uint8 htime);
extern void Speed_response(void);
extern void mc_ramp(MCRAMP *hSpeedramp);
extern  int16 HW_One_PI(int16 Xn1);
extern void Sleepmode(void);
extern void LED_Display(void);
extern int16 LPFFunction(int16 Xn1, int16 Xn0, int8 K);
extern uint16 Abs_F16(int16 value);
extern void StarRampDealwith(void);
extern void APP_DIV(void);
extern void HW_PI_Control(OUTLOOP *PIPara);

extern void OutLoopParameterSet(void);
extern void	ONOFFControl(void);
extern void RealPowerCal(void);
extern int16 SW_One_PI(int16 feedbackvalue, int16 referencevalue , MPIDTypeDef * PID);
extern void PWMIN_Init(void);
extern void PWMScan(void);
extern void Fault_Recovery(void);
extern void   TickCycle_1ms(void);
//extern void mcTorqueCompensationTest(void);
//extern void mcTorqueCompensationInit(void);
#endif