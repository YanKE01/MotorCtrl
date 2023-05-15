/******************** (C) COPYRIGHT 2021 LINGXIN Microelectronics***************
 * File Name          : UserParaSetDefine.h
 * Author             : LX Motor Lab
 * Date  						 : 2022-08-01
 * Version            : v3.7
 * Description        : Users set all control parameters in this h file
 *******************************************************************************/
#ifndef __USERPARASETDEFINE_H_INCLUDED__
#define __USERPARASETDEFINE_H_INCLUDED__

#include "lcm32f037_lib.h"
#include "UserIncludes.h"

//====================系统指令=============================
// 电机转动方向
#define UPDS_POSITIVE_DIRECTION (0) // 正方向CW
#define UPDS_NEGATIVE_DIRECTION (1) // 反方向CCW
#define UPDS_MOTOR_DIRECTION (UPDS_POSITIVE_DIRECTION)

// 电机电压
#define UPDS_MOTOR_LOW_VOLTAGE (0)  // 低压控制器LV
#define UPDS_MOTOR_HIGH_VOLTAGE (1) // 高压控制器HV
#define UPDS_MOTOR_VOLTAGE (UPDS_MOTOR_LOW_VOLTAGE)

// 电机转速
#define UPDS_MOTOR_LOW_SPEED (0)  // 常规转速，电频率小于1000Hz，伺服电机，工业风机等
#define UPDS_MOTOR_HIGH_SPEED (1) // 高转速电机，电频率大于1000Hz，吸尘器、扫地机等
#define UPDS_MOTOR_SPEED (UPDS_MOTOR_LOW_SPEED)

// 七五段式SVPWM切换使能,可以提高调制度，即提高转速，但是会引入稍大的电流谐波和噪声
#define UPDS_5_7STAGE_SWITCHING_DISABLE (0) // 七五段式SVPWM切换关闭
#define UPDS_5_7STAGE_SWITCHING_ENABLE (1)  // 七五段式SVPWM切换使能
#define UPDS_5_7STAGE_SWITCHING_SEL (UPDS_5_7STAGE_SWITCHING_ENABLE)

// PWM频率切换使能，使能可以提高启动成功率
#define UPDS_PWM_SWITCHING_DISABLE (0) // 关闭PWM切换
#define UPDS_PWM_SWITCHING_ENABLE (1)  // 使能PWM切换
#define UPDS_UPDS_PWM_SWITCHING_SEL (UPDS_PWM_SWITCHING_ENABLE)

// IPD, 初始位置辨识，减少启动反转，6脉冲注入方法
#define UPDS_IPD_DISABLE (0) // 初始位置辨识关闭
#define UPDS_IPD_ENABLE (1)  // 初始位置辨识使能
#define UPDS_IPD_SEL (UPDS_IPD_DISABLE)

// 控制模式
#define UPDS_VF_MODE (0)    // VF开环，一般测试硬件用
#define UPDS_IF_MODE (1)    // IF闭环，测试电流检测是否正确用
#define UPDS_TOQRE_MODE (2) // 转矩闭环模式
#define UPDS_SPEED_MODE (3) // 速度闭环模式
#define UPDS_POWER_MODE (4) // 功率闭环模式
#define UPDS_TEST (5)       // VF测试模式，不做故障判断
#define UPDS_CONTROL_MODE (UPDS_SPEED_MODE)

// 芯片选择，24SSOP 和 32SSOP
#define UPDS_LCM037_24PIN (0) // 24Pin037
#define UPDS_LCM037_32PIN (1) // 32Pin037
#define UPDS_CHIP_TYPE_SEL (UPDS_LCM037_32PIN)

// 带速重投方法选择
#define UPDS_RESTART_SOFTWARE (0) // 软件方法
#define UPDS_RESTART_HARDWARE (1) // 硬件方法
#define UPDS_RESTART_METHOD (UPDS_RESTART_SOFTWARE)

// 软件方法带速重投,一般不改动，低电感电机减小以下参数，以下时间以PWM周期为单位
#define UPDS_SHORTTIME_US (500.000000f)  // 注入脉冲电流时间
#define UPDS_INTERVAL_US (800.000000f)   // 第一个脉冲后的时间间隔
#define UPDS_INTERVAL_FINAL_MS (0.5)     // 第二个脉冲后的时间间隔
#define UPDS_SHORT_CURRENT_MAG _IQ(0.02) // 电流低于改值，认为低转速
#define UPDS_STARTUP_SPD_MAX _IQ(0.5)    // 带速重投最大切入速度，高于此速度，等待减速；低于此速度，立即切入

// 指令类型
#define UPDS_COMMAND_SOFTTOOL (0) // 配合LCM_MotorControl上位机使用，通过上位机发控制指令
#define UPDS_COMMAND_VSP (1)      // 旋钮ADC检测
#define UPDS_COMMAND_PWM (2)      // PWM占空比
#define UPDS_COMMAND_KEIL (3)     // Keil软件中直接给定
#define UPDS_COMMAND_TYPE (UPDS_COMMAND_KEIL)

//====================电机参数设置=======================
#define UPDS_MOTOR_J (0.000100f)        // 电机系统转动惯量，暂时没用，可以用默认值
#define UPDS_RS_REAL (0.1159076f)       // 定子相电阻，欧姆
#define UPDS_LD_REAL (0.0002850f)       // d轴电感，H
#define UPDS_LQ_REAL (0.0004590f)       // q轴电感，H
#define UPDS_PSI_REAL (0.018379f)       // 永磁体磁链幅值，V/(rad/s)
#define UPDS_PAIRS (3u)                 // 极对数
#define UPDS_RATED_CURRENT (28.000000f) // 额定电流，A   <=2*IN
#define UPDS_RATED_SPEED (3600.000000f) // 额定转速，rpm

//====================硬件参数===========================
#define UPDS_SAMPLE_CURR_R_REAL (0.01000f)    // 相电流采样电阻
#define UPDS_SAMPLE_CURR_OP_REAL (6.000000f)  // 相电流采样运放放大倍数
#define UPDS_SAMPLE_VOLT_OP_GAIN (0.040000f)  // 母线电压采样增益
#define UPDS_SAMPLE_DCBUS_R_REAL (0.0100f)    // 母线电流采样电阻阻值
#define UPDS_SAMPLE_DCBUS_OP_REAL (6.000000f) // 母线电流采样放大倍数
#define UPDS_UDC_REAL (48.000000)             // 直流母线电压
#define UPDS_DEADTIME_NS ((u16)1500)          // 死区时间,单位ns，0~3500ns

//=====================控制参数==========================
#define UPDS_COMMAND_TIME_IQ1_S (1.000000f)     // 指令从0-1PU，所需时间
#define UPDS_INJECT_D_CURRENT_A_PU (0.000000f)  // 启动电流参数，增强启动能力，0-0.5, 可靠启动参数，大扇叶可是适当增大（标幺）
#define UPDS_PWM_FREQ2 ((u16)16000)             // 第二频率，高速运行用，单位：Hz，fpwm2,//PWM开关频率（主中断），频率切换使能后起作用。否则按照PWM2配置
#define UPDS_PWM_FREQ ((u16)UPDS_PWM_FREQ2 / 2) // 第一频率，低速运行用，单位：Hz，fpwm1
#define UPDS_CURRENT_LOOP_BW_HZ (200.000000f)   // 电流环带宽（Hz）,这个参数不能过大，否则容易引起电流不正弦

// 速度环PI参数
#define UPSD_PI_SPEED_KP (0.100000f) // 比例
#define UPSD_PI_SPEED_KI (2.000000f) // 积分
#define UPSD_POWER_MAX (800.000000f) // 速度环控制是输出功率最大值

// 功率环PI参数
#define UPDS_CP_KP (1.000000f)  // 比例
#define UPDS_CP_KI (10.000000f) // 积分

// 弱磁控制
#define UPDS_FW_KP (0.200000f)        // 比例
#define UPDS_FW_KI (10.000000f)       // 积分
#define UPDS_FW_IDREF_MAX (5.000000f) // 限制id最大值

// 观测器参数1，2
#define UPDS_OBS_GAIN_Q (0.010000f) // 观测器增益1
#define UPDS_OBS_GAIN_D (2.000000f) // 观测器增益2

// 若使能初始位置检测（IPD），6脉冲注入信号设置
#define UPDS_IPD_PULSE_US (125.000000f)
#define UPDS_IPD_INTERVAL_US (100.000000f)

//=====================保护参数=======================
#define UPDS_HARDOVERCURRENT_A (45.000000f) // 硬件过流保护，Idc检测运放后到比较器，进行硬件过流保护

#define UPDS_OVERCURRENT_A (33.300000f)        // 过流保护，定子电流模值，Mag(Is)，A
#define UPDS_OVERCURRENT_A_TIME_MS (1.000000f) // 触发过流保护所需时间，ms

#define UPDS_OVERVOLTAGE_V (55.000000f)          // 母线过压保护，V
#define UPDS_OVERVOLTAGE_V_TIME_MS (100.000000f) // 触发母线过压保护时间，ms

#define UPDS_UNDERVOLTAGE_V (36.000000f)          // 母线欠压保护，V
#define UPDS_UNDERVOLTAGE_V_TIME_MS (100.000000f) // 触发母线欠压保护时间，ms

#define UPDS_MOTOROVERTEMPERATURE_DEGREE (150.000000f) // 电机过温保护值
#define UPDS_MOTOROVERTEMPERATURE_TIME_S (10.000000f)  // 电机过温保护时间，s

#define UPDS_IGBTOVERTEMPERATURE_DEGREE (600 * 0x08) // 功率模块过温保护值85°C
#define UPDS_IGBTOVERTEMPERATURE_TIME_S (1.000000f)  // 功率模块过温保护时间

// 启动失败保护
#define UPDS_STARTUP_FAIL_SPEED (200.000000f) // 启动失败速度上限值
#define UPDS_STARTUP_FAIL_TIME_S (5.000000f)  // 启动失败保护时间，在这个时间内，转速必须大于UPDS_STARTUP_FAIL_SPEED设置转速
#define UPDS_RE_STARTUP_TIME_S (5.000000f)    // 启动失败后，重新启动间隔时间，s
#define UPDS_STARTUP_FAIL_MAX (u8)(5)         // 重启次数

//==========================水泵========================
#define UPDS_IQDIVSPD_GAIN (20.000000f) // 缺水保护值
#define UPDS_NOWATER_TIME_S (30.0000f)  // 触发缺水保护时间  unit：s
// 电机档位判断
// 48v
#define UPDS_NWONE_VOLLOW_V (30.0f)                     // unit；V
#define UPDS_NWONE_VOLHIGH_V (55.0f)                    // unit；V
#define UPDS_NWONE_CUR_A (8.0f)                         // unit：A
#define UPDS_UNDERVOLTAGE_NWONE_V (UPDS_NWONE_VOLLOW_V) // 母线欠压保护，V
// 60V
#define UPDS_NWTWO_VOLLOW_V (56.0f)            // unit：V
#define UPDS_NWTWO_VOLHIGH_V (66.0f)           // unit：V
#define UPDS_NWTWO_CUR_A (7.0f)                // unit：A
#define UPDS_UNDERVOLTAGE_NWTWO_V (44.000000f) // 母线欠压保护，V
// 72V
#define UPDS_NWTHREE_VOLLOW_V (67.0f)            // unit：V
#define UPDS_NWTHREE_VOLHIGH_V (96.0f)           // unit：V
#define UPDS_NWTHREE_CUR_A (6.0f)                // unit：A
#define UPDS_UNDERVOLTAGE_NWTHREE_V (54.000000f) // 母线欠压保护，V

#endif
