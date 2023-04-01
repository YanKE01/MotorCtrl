/* --------------------------- (C) COPYRIGHT 2020 Fortiortech ShenZhen -----------------------------
    File Name      : Parameter.h
    Author         : Fortiortech  Appliction Team
    Version        : V1.0
    Date           : 2020-09-30
    Description    : This file contains all FOC debug  parameter used for Motor Control.
----------------------------------------------------------------------------------------------------
                                       All Rights Reserved
------------------------------------------------------------------------------------------------- */

/* Define to prevent recursive inclusion -------------------------------------------------------- */
#ifndef __PARAMETER_H_
#define __PARAMETER_H_

/* -----Private define----- */
#define SystemPowerUpTime               (10000)                                                    // 上电等待时间，cpu计数时钟

/* -----CPU and PWM Parameter----- */
#define PWM_CYCLE                       (1000.0 / PWM_FREQUENCY)                                   // 周期us
#define SAMP_FREQ                       (PWM_FREQUENCY * 1000)                                     // 采样频率(HZ)
#define TPWM_VALUE                      (1.0 / SAMP_FREQ)                                          // 载波周期(S)
#define PWM_VALUE_LOAD                  (uint16)(MCU_CLOCK * 500 / PWM_FREQUENCY)                  // PWM 定时器重载值

/* -----deadtime Parameter----- */
#define PWM_LOAD_DEADTIME               (PWM_DEADTIME * MCU_CLOCK)                                 // 死区设置值
#define PWM_OVERMODULE_TIME             (OVERMOD_TIME * MCU_CLOCK / 2)                             // 过调制时间
#define PWM_DLOWL_TIME                  (DLL_TIME * MCU_CLOCK / 2)                                 // 下桥臂最小时间

/* -----single resistor sample Parameter----- */
#define PWM_TS_LOAD                     (uint16)(_Q16 / PWM_CYCLE * MIN_WIND_TIME / 16)            // 单电阻采样设置值
#define PWM_DT_LOAD                     (uint16)(_Q16 / PWM_CYCLE * DT_TIME / 16)                  // 死区补偿值
#define PWM_TGLI_LOAD                   (0)                                                        // 最小脉冲

/* -----hardware current sample Parameter----- */
#define HW_BOARD_CURR_MAX               (HW_ADC_REF / 2 / HW_AMPGAIN / HW_RSHUNT)                  // 最大采样电流
#define HW_BOARD_CURR_MIN               (-HW_BOARD_CURR_MAX)                                       // 最小采样电流
#define HW_BOARD_CURR_BASE              (HW_BOARD_CURR_MAX * 2)                                    // 电流基准

/* -----hardware voltage sample Parameter----- */
#define HW_BOARD_VOLTAGE_BASE           (HW_BOARD_VOLT_MAX / 1.732)                                // 电压基准
#define HW_BOARD_VOLTAGE_VC             ((RV1 + RV2 + RV3 * VC1) / (RV3 * VC1))
#define HW_BOARD_VOLTAGE_BASE_Start     (HW_ADC_REF * HW_BOARD_VOLTAGE_VC / 1.732)                 // 电压基准

/* -----硬件过流保护DAC值----- */
#define DAC_OvercurrentValue            _Q7(I_ValueX(OverHardcurrentValue))+0x7F				   // HALF到VCC需加7F 

#define AlignFirstAngle                 _Q15((float)Align_First_Angle / 180.0)                     // (°) 预定位角度
#define AlignSecondAngle                _Q15((float)Align_Second_Angle / 180.0)                    // (°) 预定位角度

/* -----protect value----- */
#define OVER_PROTECT_VALUE              _Q15(Over_Protect_Voltage  / HW_BOARD_VOLT_MAX)
#define UNDER_PROTECT_VALUE             _Q15(Under_Protect_Voltage / HW_BOARD_VOLT_MAX)
#define OVER_RECOVER_VALUE              _Q15(Over_Recover_Vlotage  / HW_BOARD_VOLT_MAX)
#define UNDER_RECOVER_VALUE             _Q15(Under_Recover_Vlotage / HW_BOARD_VOLT_MAX)

/* -----motor speed set value----- */
#define Motor_Omega_Ramp_Min            _Q15(MOTOR_OMEGA_ACC_MIN / MOTOR_SPEED_BASE)
#define Motor_Omega_Ramp_End            _Q15(MOTOR_OMEGA_ACC_END / MOTOR_SPEED_BASE)

#define Motor_Loop_Speed                _Q15(MOTOR_LOOP_RPM / MOTOR_SPEED_BASE)

#define Motor_Start_Min_Speed           _Q15(MOTOR_START_MIN_SPEED_VALUE / MOTOR_SPEED_BASE)

#define Motor_Max_Speed                 _Q15(MOTOR_SPEED_MAX_RPM   / MOTOR_SPEED_BASE)
#define Motor_Min_Speed                 _Q15(MOTOR_SPEED_MIN_RPM   / MOTOR_SPEED_BASE)
#define Motor_Stop_Speed                _Q15(MOTOR_SPEED_STOP_RPM  / MOTOR_SPEED_BASE)

#define StallProtec2tSpeedValue         _Q15(MOTOR_SPEED_STAL2_RPM / MOTOR_SPEED_BASE)
#define StallProtec3MinSpeed            _Q15(MOTOR_SPEED_STAL3_MIN_RPM / MOTOR_SPEED_BASE)
#define StallProtec3MaxSpeed            _Q15(MOTOR_SPEED_STAL3_MAX_RPM / MOTOR_SPEED_BASE)

#define Motor_Speed_Loop_PI2_Min_Speed  _Q15(MOTOR_SPEED_LOOP_PI2_MIN_SPEED / MOTOR_SPEED_BASE)
#define Motor_Speed_Loop_PI3_Min_Speed  _Q15(MOTOR_SPEED_LOOP_PI3_MIN_SPEED / MOTOR_SPEED_BASE)

#define Motor_Current_Loop_PI2_Min_Speed _Q15(MOTOR_CURRENT_LOOP_PI2_MIN_SPEED / MOTOR_SPEED_BASE)
#define Motor_Current_Loop_PI3_Min_Speed _Q15(MOTOR_CURRENT_LOOP_PI3_MIN_SPEED / MOTOR_SPEED_BASE)

#define Motor_ReturnOil_Speed           _Q15(MotorStartSpeed / MOTOR_SPEED_BASE)
#define ReturnOilTime                   (uint16)(MotorReturnOilT*1000)

/* -----外环增量----- */
#define SPEEDRAMPINC                	(S_Value(SpeedRampInc))/(1000/SPEEDRAMPTIME)			   // 运行加速度
#define SPEEDRAMPDEC                	(S_Value(SpeedRampDec))/(1000/SPEEDRAMPTIME)			   // 运行减速度

#define OVERPOWERSPEEDRAMPDEC           (S_Value(OverPowerSpeedRampDec))/(1000/SPEEDRAMPTIME)      // 运行减速度

#define SPEEDRAMPSTARTINC           	(S_Value(SpeedRampStartInc))/(1000/SPEEDRAMPTIME)		   // 启动加速度
#define SPEEDRAMPSTARTDEC           	(S_Value(SpeedRampStartDec))/(1000/SPEEDRAMPTIME)		   // 启动减速度

/* -----功率转换系数----- */
#define PowerLimitK                    ((float)HW_BOARD_VOLT_MAX *  (float)HW_ADC_REF) / (float)HW_AMPGAIN / (float)HW_RSHUNT / (float)MOTOR_POWER_BASE/32767.0
#define P_Value(Pow_Val)                _Q15((float)(Pow_Val)/MOTOR_POWER_BASE)

/* -----obsever parameter set value----- */
#define MAX_BEMF_VOLTAGE                ((MOTOR_SPEED_BASE*Ke)/(1000.0))
#define MAX_OMEG_RAD_SEC                ((float)(_2PI*BASE_FREQ))
//#define OBS_K1T                         _Q15(LD/(LD+RS*TPWM_VALUE))
//#define OBS_K2T                         _Q13((TPWM_VALUE/(LD+RS*TPWM_VALUE))*(HW_BOARD_VOLTAGE_BASE_Start/HW_BOARD_CURR_BASE))
#define OBS_K2T_SMO                     _Q13((TPWM_VALUE/(LD+RS*TPWM_VALUE))*1.4*(HW_BOARD_VOLTAGE_BASE_Start/HW_BOARD_CURR_BASE))
//#define OBS_K2T_Actual                  _Q13((TPWM_VALUE/(LD+RS*TPWM_VALUE))*(HW_BOARD_VOLTAGE_BASE/HW_BOARD_CURR_BASE))
//#define OBS_K3T                         _Q15((TPWM_VALUE/(LD+RS*TPWM_VALUE))*(MAX_BEMF_VOLTAGE/HW_BOARD_CURR_BASE))
//#define OBS_K4T                         _Q15(((LD-LQ)*TPWM_VALUE*MAX_OMEG_RAD_SEC)/(LD+RS*TPWM_VALUE))





#define OBS_K1T                         _Q11((1.0*3.0/(125.0*1.0))*(LQ/TPWM_VALUE)*(HW_BOARD_CURR_BASE/HW_BOARD_VOLTAGE_BASE))
#define OBS_K2T                         _Q11(RS*HW_BOARD_CURR_BASE/HW_BOARD_VOLTAGE_BASE)
//#define OBS_K2T_SMO                     _Q11(1.0*RS*HW_BOARD_CURR_BASE/HW_BOARD_VOLTAGE_BASE)
#define OBS_K2T_Actual                  OBS_K2T
#define OBS_K3T                         _Q8(2.5)
#define OBS_K4T                         _Q15(((LD-LQ)*TPWM_VALUE*MAX_OMEG_RAD_SEC)/(LD+RS*TPWM_VALUE))






#define BASE_FREQ                       ((MOTOR_SPEED_BASE / 60) * Pole_Pairs)                     // 基准频率
#define OBS_FBASE                       BASE_FREQ*TPWM_VALUE*32768                                 // Fbase*Tpwm*32768
#define OBS_KLPF                        _Q15(_2PI*BASE_FREQ*TPWM_VALUE)                            // 2PI*Fbase*Tpwm
#define SPEED_KLPF                      _Q15(_2PI*SPD_BW*TPWM_VALUE)                               // 2PI*SPD_BW*Tpwm
#define OBS_EA_KS                       _Q15((2*MOTOR_SPEED_SMOMIN_RPM*_2PI*BASE_FREQ*TPWM_VALUE)/MOTOR_SPEED_BASE)     // SMO的最小速度

#define OBSW_KP_GAIN1                   _Q12(2*_2PI*ATT_COEF*ATO_BW1/BASE_FREQ)
#define OBSW_KI_GAIN1                   _Q15(_2PI*ATO_BW1*ATO_BW1*TPWM_VALUE/BASE_FREQ)

#define OBSW_KP_GAIN2                   _Q12(2*_2PI*ATT_COEF*ATO_BW2/BASE_FREQ)
#define OBSW_KI_GAIN2                   _Q15(_2PI*ATO_BW2*ATO_BW2*TPWM_VALUE/BASE_FREQ)

#define OBSW_KP_GAIN3                   _Q12(2*_2PI*ATT_COEF*ATO_BW3/BASE_FREQ)
#define OBSW_KI_GAIN3                   _Q15(_2PI*ATO_BW3*ATO_BW3*TPWM_VALUE/BASE_FREQ)

#define OBSW_KP_GAIN4                   _Q12(2*_2PI*ATT_COEF*ATO_BW4/BASE_FREQ)
#define OBSW_KI_GAIN4                   _Q15(_2PI*ATO_BW4*ATO_BW4*TPWM_VALUE/BASE_FREQ)


#define OBSE_PLLKP_GAIN1                _Q11(((2*ATT_COEF*_2PI*E_BW1*LD - RS)*HW_BOARD_CURR_BASE)/HW_BOARD_VOLTAGE_BASE)
#define OBSE_PLLKI_GAIN1                _Q11((_2PI*E_BW1*_2PI*E_BW1*LD*TPWM_VALUE*HW_BOARD_CURR_BASE)/HW_BOARD_VOLTAGE_BASE)

#define OBSE_PLLKP_GAIN2                _Q11(((2*ATT_COEF*_2PI*E_BW2*LD - RS)*HW_BOARD_CURR_BASE)/HW_BOARD_VOLTAGE_BASE)
#define OBSE_PLLKI_GAIN2                _Q11((_2PI*E_BW2*_2PI*E_BW2*LD*TPWM_VALUE*HW_BOARD_CURR_BASE)/HW_BOARD_VOLTAGE_BASE)

#define OBSE_PLLKP_GAIN3                _Q11(((2*ATT_COEF*_2PI*E_BW3*LD - RS)*HW_BOARD_CURR_BASE)/HW_BOARD_VOLTAGE_BASE)
#define OBSE_PLLKI_GAIN3                _Q11((_2PI*E_BW3*_2PI*E_BW3*LD*TPWM_VALUE*HW_BOARD_CURR_BASE)/HW_BOARD_VOLTAGE_BASE)

#define OBSE_PLLKP_GAIN4                _Q11(((2*ATT_COEF*_2PI*E_BW4*LD - RS)*HW_BOARD_CURR_BASE)/HW_BOARD_VOLTAGE_BASE)
#define OBSE_PLLKI_GAIN4                _Q11((_2PI*E_BW4*_2PI*E_BW4*LD*TPWM_VALUE*HW_BOARD_CURR_BASE)/HW_BOARD_VOLTAGE_BASE)

#define OBS_K3T_SPEED9                  OBS_K3T * 1.0		
#define OBS_K3T_SPEED8                  OBS_K3T * 1.0 
#define OBS_K3T_SPEED7                  OBS_K3T * 0.80 
#define OBS_K3T_SPEED6                  OBS_K3T * 0.75
#define OBS_K3T_SPEED5                  OBS_K3T * 0.70 
#define OBS_K3T_SPEED4                  OBS_K3T * 0.50 
#define OBS_K3T_SPEED3                  OBS_K3T * 0.50 
#define OBS_K3T_SPEED2                  OBS_K3T * 0.50 
#define OBS_K3T_SPEED1                  OBS_K3T * 0.50 

/* -----SVPWM mode----- */
#define SVPWM_5_Segment                 (0)                                                        // 五段式SVPWM
#define SVPWM_7_Segment                 (1)                                                        // 七段式SVPWM
#define SVPMW_Mode                      (SVPWM_7_Segment)

/* -----double resistor sample mode----- */
#define DouRes_1_Cycle                  (0)                                                        // 周期采样完 ia, ib
#define DouRes_2_Cycle                  (1)                                                        // 交替采用ia, ib, 2周期采样完成
#define DouRes_Sample_Mode              (DouRes_1_Cycle)

#endif