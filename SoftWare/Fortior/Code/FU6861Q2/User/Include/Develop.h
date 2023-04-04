/**
 * @copyright (C) COPYRIGHT 2022 Fortiortech Shenzhen
 * @file      Develop.h
 * @author    Fortiortech  Appliction Team
 * @date      2022-07-13
 * @brief      This file contains Advanced Applications parameter used for Motor Control.
 */
 
/* -----Define to prevent recursive inclusion----- */
#ifndef __DEVELOP_H_
#define __DEVELOP_H_

/* -----Q 格式定义 ----- */
#define _Q7(A)                          (int8) ((A) * (0x7f))
#define _Q8(A)                          (int16)((A) * (0xff))                                                            ///< Q8 format
#define _Q10(A)                         (int16)((A) * (0x3ff))                                                           ///< Q15 format
#define _Q11(A)                         (int16)((A) * (0x7ff))                                                           ///< Q12 format
#define _Q12(A)                         (int16)((A) * (0xfff))                                                           ///< Q12 format
#define _Q13(A)                         (int16)((A) * (0x1fff))                                                          ///< Q12 format
#define _Q14(A)                         (int16)((A) * (0x3fff))                                                          ///< Q15 format
#define _Q15(A)                         (int16)((A) * (0x7fff))                                                          ///< Q15 format
#define _2PI                            (3.1415926 * 2)                                                                  ///< 2 PI value
#define _Q16                            (65535.0)                                                                        ///< Q16 format value

/* -----Private define----- */
#define SystemPowerUpTime               (50000)                                                                          ///< 上电等待时间，cpu计数时钟

#define I_ValueX(Curr_Value)            ((Curr_Value) * (HW_RSHUNT) * (HW_AMPGAIN) / (HW_ADC_REF))
#define I_Value(Curr_Value)             _Q15(I_ValueX(Curr_Value))

/* -----芯片参数值----- */
#define MCU_CLOCK                      (24.0)                                                                           ///< (MHz) 主频

#define RV                             ((RV1  + RV2) / RV2)                                                             ///< 分压比
#define HW_BOARD_VOLT_MAX              (HW_ADC_REF * RV)                                                                ///< (V)  ADC可测得的最大母线电压

/* -----时间设置值----- */
#define Calib_Time                     (1000)                                                                           ///< 校正次数，固定1000次，单位:次
#define Charge_Time                    (20)                                                                             ///< (ms) 预充电时间，单位：ms

/* -----正常运行时估算算法的参数设置值----- */
#define OBS_KSLIDE                     _Q15(0.85)                                                                       ///< SMO算法里的滑膜增益值
#define E_BW_Wind                      (600.0)                                                                          ///< PLL算法里的反电动势滤波值
#define E_BW                           (400.0)                                                                          ///< PLL算法里的反电动势滤波值

/* -----逆风判断时的估算算法设置值----- */
#define TailWind_Time                  (100)                                                                            ///< (ms) 顺逆风检测时间
#define ATO_BW_Wind                    (120.0)                                                                          ///< 逆风判断观测器带宽的滤波值，经典值为8.0-100.0
#define SPD_BW_Wind                    (10.0)                                                                           ///< 逆风判断速度带宽的滤波值，经典值为5.0-40.0

/* -----逆风顺风状态下的KP、KI----- */
#define DQKP_TailWind                  _Q12(0.8)                                                                        ///<_Q12(1.0)-PLL ,   _Q12(1.5)   -smo
#define DQKI_TailWind                  _Q15(0.01)                                                                       ///<_Q15(0.08)-PLL  ,_Q15(0.2)-smo

/* -----芯片参数值----- */
#define PWM_CYCLE                       (1000.0 / PWM_FREQUENCY)                                                        ///< 周期us
#define SAMP_FREQ                       (PWM_FREQUENCY * 1000)                                                          ///< 采样频率(HZ)
#define TPWM_VALUE                      (1.0 / SAMP_FREQ)                                                               ///< 载波周期(S)
#define PWM_VALUE_LOAD                  (uint16)(MCU_CLOCK * 500 / PWM_FREQUENCY)                                       ///< PWM 定时器重载值

/* -----初始位置检查参数----- */
#define PosCheckEnable                 (0)                                                                              ///< 初始位置使能,目前程序中没添加此功能 20220616
#define AlignEnable                    (0)                                                                              ///< 预定位使能

/* -----脉冲注入时间长于2ms 或 低于2ms----- */
#define InjectTime                     (Short_Inject)
#define RPD_Time                       (3)                                                                              ///< (ms) 每次RPD的时间
#define RPD_CurValue                   (6.5)                                                                            ///< (A)  RPD过流值
#define DAC_RPDCurValue                _Q7(I_ValueX(RPD_CurValue * 2))

#define ATT_COEF                       (0.85)                                                                           ///< 无需改动


#define   UDMAX_Volt_VALUE    			_Q15(Under_Protect_Voltage/HW_BOARD_VOLT_MAX)
#define   UDMIN_Volt_VALUE    			_Q15(Over_Protect_Voltage/HW_BOARD_VOLT_MAX)
#define   UD_K		                  ((float)(UDMAX-UDMIN)/(float)(UDMAX_Volt_VALUE-UDMIN_Volt_VALUE))                 ///<2498

/* -----过温保护值设置----- */
#define   Tempera_Value(NTC_Value) 		_Q15((5.0*NTC_Value/(10.0+NTC_Value))/HW_ADC_REF)								///< 10K上拉电阻时，NTC阻值对应Q15的AD值 

/* -----双电阻最小脉宽设置----- */
#define DLL_TIME                        (1.0)                                                                           ///< 双电阻最小脉宽设置(us),建议值为死区时间值+0.2us以上

/* -----三电阻过调制时间----- */
#define OVERMOD_TIME                    (2.0)                                                                           ///< 三电阻过调制时间(us)，建议值2.0

/* -----死区补偿时间----- */
#define DT_TIME                         (0.0)                                                                           ///< 死区补偿时间(us)，适用于双电阻和三电阻，建议值是1/2死区时间

/* -----*桥臂窄脉宽消除----- */
#define GLI_TIME                        (0.0)                                                                           ///< 桥臂窄脉宽消除(us),建议值0.5

/* -----死区参数----- */
#define PWM_LOAD_DEADTIME               (PWM_DEADTIME * MCU_CLOCK)                                                      ///< 死区设置值
#define PWM_OVERMODULE_TIME             (OVERMOD_TIME * MCU_CLOCK / 2)                                                  ///< 过调制时间
#define PWM_DLOWL_TIME                  (DLL_TIME * MCU_CLOCK / 2)                                                      ///<下桥臂最小时间

/* -----单电阻采样参数----- */
#define PWM_TS_LOAD                     (uint16)(_Q16 / PWM_CYCLE * MIN_WIND_TIME / 16)                                 ///< 单电阻采样设置值
#define PWM_DT_LOAD                     (uint16)(_Q16 / PWM_CYCLE * DT_TIME / 16)                                       ///< 死区补偿值

#define PWM_TGLI_LOAD                   (uint16)(_Q16 / PWM_CYCLE * (GLI_TIME) / 16)                                    ///< 最小脉冲

/* -----电流基准的电路参数----- */
#define HW_BOARD_CURR_MAX               (HW_ADC_REF / 2 / HW_AMPGAIN / HW_RSHUNT)                                       ///< 最大采样电流,2.702A
#define HW_BOARD_CURR_MIN               (-HW_BOARD_CURR_MAX)                                                            ///< 最小采样电流,-2.702A
#define HW_BOARD_CURR_BASE              (HW_BOARD_CURR_MAX * 2)                                                         ///< 电流基准///<5.4A
#define VC1                             (1.0)                                                                           ///< 电压补偿系数

/* -----母线电压采样分压电路参数----- */
#define HW_BOARD_VOLTAGE_BASE           (HW_BOARD_VOLT_MAX / 1.732)                                                     ///< 电压基准
#define HW_BOARD_VOLTAGE_VC             ((RV1 + RV2 * VC1) / (RV2 * VC1))
#define HW_BOARD_VOLTAGE_BASE_Start     (HW_ADC_REF * HW_BOARD_VOLTAGE_VC / 1.732)                                      ///< 电压基准

/* -----硬件过流保护DAC值----- */
#if ((AMP0_VHALF == Enable)||(HW_AMP_MODE == AMP_PGA_DUAL))      
    #define DAC_OvercurrentValue        ((uint8)_Q8(I_ValueX(OverHardcurrentValue))+0x7F)
#else
    #define DAC_OvercurrentValue        ((uint8)_Q8(I_ValueX(OverHardcurrentValue)))
#endif

#define Align_Theta                     _Q15((float)Align_Angle / 180.0)
#define BEMF_Theta                      _Q15((float)0.0 / 180.0)

#define BASE_FREQ                       ((MOTOR_SPEED_BASE / 60) * Pole_Pairs)                                          ///< 基准频率
#define FG_Value						(TIM4_Fre/BASE_FREQ/ FG_K)	

/* -----保护参数值----- */
#define GetCurrentOffsetValueLow     (16383-GetCurrentOffsetValue)                                                      ///<  偏置电压差值低点 
#define GetCurrentOffsetValueHigh    (16383+GetCurrentOffsetValue)                                                      ///<  偏置电压差值高点 
/* -----电压保护值----- */
#define OVER_PROTECT_VALUE              _Q15(Over_Protect_Voltage  / HW_BOARD_VOLT_MAX)
#define UNDER_PROTECT_VALUE             _Q15(Under_Protect_Voltage / HW_BOARD_VOLT_MAX)
#define OVER_RECOVER_VALUE              _Q15(Over_Recover_Vlotage  / HW_BOARD_VOLT_MAX)
#define UNDER_RECOVER_VALUE             _Q15(Under_Recover_Vlotage / HW_BOARD_VOLT_MAX)

#define Motor_Open_Ramp_ACC             _Q15(MOTOR_OPEN_ACC     / MOTOR_SPEED_BASE)
#define Motor_Open_Ramp_Min             _Q15(MOTOR_OPEN_ACC_MIN / MOTOR_SPEED_BASE)

#define Motor_Omega_Ramp_Min            _Q15(MOTOR_OMEGA_ACC_MIN / MOTOR_SPEED_BASE)
#define Motor_Omega_Ramp_End            _Q15(MOTOR_OMEGA_ACC_END / MOTOR_SPEED_BASE)

#define Motor_Loop_Speed                _Q15(MOTOR_LOOP_RPM / MOTOR_SPEED_BASE)

#define Motor_Max_Speed                 _Q15(MOTOR_SPEED_MAX_RPM   / MOTOR_SPEED_BASE)
#define Motor_Min_Speed                 _Q15(MOTOR_SPEED_MIN_RPM   / MOTOR_SPEED_BASE)
#define Motor_Limit_Speed               _Q15(MOTOR_SPEED_LIMIT_RPM / MOTOR_SPEED_BASE)
#define Motor_Stop_Speed                _Q15(MOTOR_SPEED_STOP_RPM  / MOTOR_SPEED_BASE)
#define MOTOR_Onoff_Speed                _Q15(MOTOR_ONOFF_RPM  / MOTOR_SPEED_BASE)
#define Motor_Stall_Speed               _Q15(Stall_DectSpeed / MOTOR_SPEED_BASE)

#define Motor_Stall_Min_Speed           _Q15(MOTOR_SPEED_STAL_MIN_RPM / MOTOR_SPEED_BASE)
#define Motor_Stall_Max_Speed           _Q15(MOTOR_SPEED_STAL_MAX_RPM / MOTOR_SPEED_BASE)

#define Motor_RD_Speed                  _Q15(MOTOR_SPEED_RD_RPM    / MOTOR_SPEED_BASE)
#define Motor_RDPT_Speed                _Q15(MOTOR_SPEED_RDPT_RPM  / MOTOR_SPEED_BASE)
#define Motor_RDRCV_Speed               _Q15(MOTOR_SPEED_RDRCV_RPM / MOTOR_SPEED_BASE)


#define Motor_Over_Speed                 _Q15(MOTOR_SPEED_OVER_RPM   / MOTOR_SPEED_BASE)
#define Motor_Over_RecoverSpeed                 _Q15(MOTOR_SPEED_OVER_RecoverRPM   / MOTOR_SPEED_BASE)

#define SPEED_K                         ((float)(Motor_Max_Speed-Motor_Min_Speed)/(float)(MAXPWMDuty-MINPWMDuty))
#define POWER_K                         ((float)(Motor_Max_Power-Motor_Min_Power)/(float)(MAXPWMDuty-MINPWMDuty))
#define CURRENT_K                         ((float)(Motor_Max_Current-Motor_Min_Current)/(float)(MAXPWMDuty-MINPWMDuty))

#define MAX_BEMF_VOLTAGE                ((MOTOR_SPEED_BASE*Ke)/(1000.0))
#define MAX_OMEG_RAD_SEC                ((float)(_2PI*BASE_FREQ))

/* -----估算器模式选择----- */
#define SMO                            (0)                                      ///< SMO ,滑膜估算
#define PLL                            (1)                                      ///< PLL ,锁相环
#define AO                             (2)                                      ///< AO，自适应估算器

//自适应估算器模式使能
#if (EstimateAlgorithm == AO)
    #define OBS_K1T                         _Q11((1.0*3.0/(125.0*1.0))*(LQ/TPWM_VALUE)*(HW_BOARD_CURR_BASE/HW_BOARD_VOLTAGE_BASE))
    #define OBS_K2T                         _Q11(0.8*RS*HW_BOARD_CURR_BASE/HW_BOARD_VOLTAGE_BASE)
    //#define OBS_K2T_SMO                     _Q11(1.0*RS*HW_BOARD_CURR_BASE/HW_BOARD_VOLTAGE_BASE)
    #define OBS_K2T_Actual                  OBS_K2T
    #define OBS_K3T                         _Q8(2.5)
    #define OBS_K4T                         _Q15(((LD-LQ)*TPWM_VALUE*MAX_OMEG_RAD_SEC)/(LD+RS*TPWM_VALUE))
#else
    #define OBS_K1T                         _Q15(LD/(LD+RS*TPWM_VALUE))
    #define OBS_K2T                         _Q13((TPWM_VALUE/(LD+RS*TPWM_VALUE))*(HW_BOARD_VOLTAGE_BASE_Start/HW_BOARD_CURR_BASE))
    #define OBS_K2T_SMO                     _Q13((TPWM_VALUE/(LD+RS*TPWM_VALUE))*1.4*(HW_BOARD_VOLTAGE_BASE_Start/HW_BOARD_CURR_BASE))
    #define OBS_K2T_Actual                  _Q13((TPWM_VALUE/(LD+RS*TPWM_VALUE))*(HW_BOARD_VOLTAGE_BASE/HW_BOARD_CURR_BASE))
    #define OBS_K3T                         _Q15((TPWM_VALUE/(LD+RS*TPWM_VALUE))*(MAX_BEMF_VOLTAGE/HW_BOARD_CURR_BASE))
    #define OBS_K4T                         _Q15(((LD-LQ)*TPWM_VALUE*MAX_OMEG_RAD_SEC)/(LD+RS*TPWM_VALUE))
#endif

#define OBSW_KP_GAIN                    _Q12(2*_2PI*ATT_COEF*ATO_BW/BASE_FREQ)
#define OBSW_KI_GAIN                    _Q15(_2PI*ATO_BW*ATO_BW*TPWM_VALUE/BASE_FREQ)

#define OBSW_KP_GAIN_RUN                _Q12(2*_2PI*ATT_COEF*ATO_BW_RUN/BASE_FREQ)
#define OBSW_KI_GAIN_RUN                _Q15(_2PI*ATO_BW_RUN*ATO_BW_RUN*TPWM_VALUE/BASE_FREQ)

#define OBSW_KP_GAIN_RUN1               _Q12(2*_2PI*ATT_COEF*ATO_BW_RUN1/BASE_FREQ)
#define OBSW_KI_GAIN_RUN1               _Q15(_2PI*ATO_BW_RUN1*ATO_BW_RUN1*TPWM_VALUE/BASE_FREQ)

#define OBSW_KP_GAIN_RUN2               _Q12(2*_2PI*ATT_COEF*ATO_BW_RUN2/BASE_FREQ)
#define OBSW_KI_GAIN_RUN2               _Q15(_2PI*ATO_BW_RUN2*ATO_BW_RUN2*TPWM_VALUE/BASE_FREQ)

#define OBSW_KP_GAIN_RUN3               _Q12(2*_2PI*ATT_COEF*ATO_BW_RUN3/BASE_FREQ)
#define OBSW_KI_GAIN_RUN3               _Q15(_2PI*ATO_BW_RUN3*ATO_BW_RUN3*TPWM_VALUE/BASE_FREQ)

#define OBSW_KP_GAIN_RUN4               _Q12(2*_2PI*ATT_COEF*ATO_BW_RUN4/BASE_FREQ)
#define OBSW_KI_GAIN_RUN4               _Q15(_2PI*ATO_BW_RUN4*ATO_BW_RUN4*TPWM_VALUE/BASE_FREQ)

#define OBS_FBASE                       BASE_FREQ*TPWM_VALUE*32768                                                       
#define OBS_KLPF                        _Q15(_2PI*BASE_FREQ*TPWM_VALUE)                                                  
#define SPEED_KLPF                      _Q15(_2PI*SPD_BW*TPWM_VALUE)                                                    
#define OBS_EA_KS                       _Q15((2*MOTOR_SPEED_SMOMIN_RPM*_2PI*BASE_FREQ*TPWM_VALUE)/MOTOR_SPEED_BASE)     

#define OBSE_PLLKP_GAIN_WIND            _Q11(((2*ATT_COEF*_2PI*E_BW_Wind*LD - RS)*HW_BOARD_CURR_BASE)/HW_BOARD_VOLTAGE_BASE)
#define OBSE_PLLKI_GAIN_WIND            _Q11((_2PI*E_BW_Wind*_2PI*E_BW_Wind*LD*TPWM_VALUE*HW_BOARD_CURR_BASE)/HW_BOARD_VOLTAGE_BASE)

#define OBSE_PLLKP_GAIN                 _Q11(((2*ATT_COEF*_2PI*E_BW*LD - RS)*HW_BOARD_CURR_BASE)/HW_BOARD_VOLTAGE_BASE)
#define OBSE_PLLKI_GAIN                 _Q11((_2PI*E_BW*_2PI*E_BW*LD*TPWM_VALUE*HW_BOARD_CURR_BASE)/HW_BOARD_VOLTAGE_BASE)


/* ADC参考电压配置 */
#define VREF3_0                         (0xA0)                                 ///< 3.0V
#define VREF4_0                         (0xB0)                                 ///< 4.0V
#define VREF4_5                         (0xC0)                                 ///< 4.5V
#define VREF5_0                         (0xD0)                                 ///< 5.0V


#if (HW_ADC_VREF==VREF5_0)
 #define HW_ADC_REF                     (5.0)                                   ///< (V)  ADC参考电压
#elif (HW_ADC_VREF==VREF4_5)
 #define HW_ADC_REF                     (4.5)                                   ///< (V)  ADC参考电压
#elif (HW_ADC_VREF==VREF4_0)
 #define HW_ADC_REF                     (4.0)                                   ///< (V)  ADC参考电压
#elif (HW_ADC_VREF==VREF3_0)
 #define HW_ADC_REF                     (3.0)                                   ///< (V)  ADC参考电压
#endif

/* -----逆风判断时的估算算法设置值----- */
#define SPEED_KLPF_WIND                 _Q15(_2PI*SPD_BW_Wind*TPWM_VALUE)                                         ///< 2PI*SPD_BW_Wind*Tpwm
#define OBSW_KP_GAIN_WIND               _Q12(2*_2PI*ATT_COEF*ATO_BW_Wind/BASE_FREQ)
///<#define   OBSW_KI_GAIN_WIND           _Q15(_2PI*0.5*ATO_BW_Wind*ATO_BW_Wind*TPWM_VALUE/BASE_FREQ)             ///<---SMO
#define OBSW_KI_GAIN_WIND               _Q15(_2PI*ATO_BW_Wind*ATO_BW_Wind*TPWM_VALUE/BASE_FREQ)                   ///<---PLL


/* -----open 算法启动参数----- */
#define MOTOR_OPEN_ACC                 (200)                                    ///< 强拖启动的增量(每载波周期加一次)
#define MOTOR_OPEN_ACC_MIN             (0)                                      ///< 强拖启动的初始速度
#define MOTOR_OPEN_ACC_CNT             (100)                                    ///< 强拖启动的执行次数(MOTOR_OPEN_ACC_CNT*256)


/* -----电流基准校正使能----- */
#define CalibDisable                    (0)                                                                             
#define CalibEnable                     (1)                                                                             
#define CalibENDIS                      (CalibEnable)

/* -----SVPWM 模式选择----- */
#define SVPWM_5_Segment                 (0)                                     ///< 五段式SVPWM
#define SVPWM_7_Segment                 (1)                                     ///< 七段式SVPWM
#define SVPMW_Mode                      (SVPWM_7_Segment)

/* -----double resistor sample mode----- */
#define DouRes_1_Cycle                  (0)                                     ///< 1 周期采样完 ia, ib
#define DouRes_2_Cycle                  (1)                                     ///< 交替采用ia, ib, 2周期采样完成
#define DouRes_Sample_Mode              (DouRes_1_Cycle)

/* -----驱动有效电平，根据驱动芯片的类型选择，大部分芯片为High_Level----- */
#define High_Level                      (0)                                     ///< 驱动高电平有效
#define Low_Level                       (1)                                     ///< 驱动低电平有效
#define UP_H_DOWN_L                     (2)                                     ///< 上桥臂高电平有效，下桥臂低电平有效
#define UP_L_DOWN_H                     (3)                                     ///< 上桥臂低电平有效，下桥臂高电平有效

/* 运放模式选择 */
#define AMP_NOMAL                       (0xA0)                                  ///< 外部放大
#define AMP_PGA_DUAL                    (0xB0)                                  ///< 内部PGA 双端差分输入

/* 内部PGA放大倍数选择 */
#define AMP2x                           (2)
#define AMP4x                           (4)
#define AMP8x                           (8)
#define AMP16x                          (16)

/* -----脉冲注入时间长于2ms 或 低于2ms----- */
#define Long_Inject                     (0)                                     ///< 脉冲注入时间长于2ms,若时间长于4ms，则要修改定时器分频
#define Short_Inject                    (1)                                     ///< 脉冲注入时间低于2ms

/* -----调速模式----- */
#define PWMMODE                        (0)                                      ///< PWM调速
#define SREFMODE                       (1)                                      ///< 模拟调速
#define NONEMODE                       (2)                                      ///< 直接给定值，不调速
#define KEYMODE                        (3)                                      ///< 按键调速模式
#define ONOFFTEST                      (4)                                      ///< 按键调速模式


/* -----顺逆风判断设置----- */
#define NoTailWind                     (0)                                      ///< 无逆风顺风判断
#define RSDMethod                      (1)                                      ///< RSD比较器方法
#define BEMFMethod                     (2)                                      ///< BEMF方法

/* -----开环启动模式选择----- */
#define Open_Start                     (0)                                      ///< 开环强拖启动
#define Omega_Start                    (1)                                      ///< Omega启动
#define Open_Omega_Start               (2)                                      ///< 先开环启，后Omega启动

/* -----电流采样模式----- */
#define Single_Resistor                (0)                                      ///< 单电阻电流采样模式
#define Double_Resistor                (1)                                      ///< 双电阻电流采样模式
#define Three_Resistor                 (2)                                      ///< 三电阻电流采样模式

/* -----硬件过流保护----- */
#define Hardware_FO_Protect            (1)                                      ///< 硬件FO过流保护使能，适用于IPM有FO保护的场合
#define Hardware_CMP_Protect           (2)                                      ///< 硬件CMP比较过流保护使能，适用于MOS管应用场合
#define Hardware_FO_CMP_Protect        (3)                                      ///< 硬件CMP比较和FO过流保护都使能
#define Hardware_Protect_Disable       (4)                                      ///< 硬件过流保护禁止，用于测试

/* -----硬件过流保护比较值来源----- */
#define Compare_DAC                    (0)                                      ///< DAC设置硬件过流值
#define Compare_Hardware               (1)                                      ///< 硬件设置硬件过流值

/* -----外环使能----- */
#define OUTLoop_Disable                (0)                                      ///< 关闭外环
#define OUTLoop_Enable                 (1)                                      ///< 使能外环

/* -----正PWMduty or 负PWMduty Choose----- */
#define PosiPWMDUTY			           (0)										///< 正PWMduty
#define NegaPWMDUTY				       (1)										///< 负PWMduty



#endif