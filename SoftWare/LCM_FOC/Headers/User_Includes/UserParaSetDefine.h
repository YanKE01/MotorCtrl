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

//====================ϵͳָ��=============================
// ���ת������
#define UPDS_POSITIVE_DIRECTION (0) // ������CW
#define UPDS_NEGATIVE_DIRECTION (1) // ������CCW
#define UPDS_MOTOR_DIRECTION (UPDS_POSITIVE_DIRECTION)

// �����ѹ
#define UPDS_MOTOR_LOW_VOLTAGE (0)  // ��ѹ������LV
#define UPDS_MOTOR_HIGH_VOLTAGE (1) // ��ѹ������HV
#define UPDS_MOTOR_VOLTAGE (UPDS_MOTOR_LOW_VOLTAGE)

// ���ת��
#define UPDS_MOTOR_LOW_SPEED (0)  // ����ת�٣���Ƶ��С��1000Hz���ŷ��������ҵ�����
#define UPDS_MOTOR_HIGH_SPEED (1) // ��ת�ٵ������Ƶ�ʴ���1000Hz����������ɨ�ػ���
#define UPDS_MOTOR_SPEED (UPDS_MOTOR_LOW_SPEED)

// �����ʽSVPWM�л�ʹ��,������ߵ��ƶȣ������ת�٣����ǻ������Դ�ĵ���г��������
#define UPDS_5_7STAGE_SWITCHING_DISABLE (0) // �����ʽSVPWM�л��ر�
#define UPDS_5_7STAGE_SWITCHING_ENABLE (1)  // �����ʽSVPWM�л�ʹ��
#define UPDS_5_7STAGE_SWITCHING_SEL (UPDS_5_7STAGE_SWITCHING_ENABLE)

// PWMƵ���л�ʹ�ܣ�ʹ�ܿ�����������ɹ���
#define UPDS_PWM_SWITCHING_DISABLE (0) // �ر�PWM�л�
#define UPDS_PWM_SWITCHING_ENABLE (1)  // ʹ��PWM�л�
#define UPDS_UPDS_PWM_SWITCHING_SEL (UPDS_PWM_SWITCHING_ENABLE)

// IPD, ��ʼλ�ñ�ʶ������������ת��6����ע�뷽��
#define UPDS_IPD_DISABLE (0) // ��ʼλ�ñ�ʶ�ر�
#define UPDS_IPD_ENABLE (1)  // ��ʼλ�ñ�ʶʹ��
#define UPDS_IPD_SEL (UPDS_IPD_DISABLE)

// ����ģʽ
#define UPDS_VF_MODE (0)    // VF������һ�����Ӳ����
#define UPDS_IF_MODE (1)    // IF�ջ������Ե�������Ƿ���ȷ��
#define UPDS_TOQRE_MODE (2) // ת�رջ�ģʽ
#define UPDS_SPEED_MODE (3) // �ٶȱջ�ģʽ
#define UPDS_POWER_MODE (4) // ���ʱջ�ģʽ
#define UPDS_TEST (5)       // VF����ģʽ�����������ж�
#define UPDS_CONTROL_MODE (UPDS_SPEED_MODE)

// оƬѡ��24SSOP �� 32SSOP
#define UPDS_LCM037_24PIN (0) // 24Pin037
#define UPDS_LCM037_32PIN (1) // 32Pin037
#define UPDS_CHIP_TYPE_SEL (UPDS_LCM037_32PIN)

// ������Ͷ����ѡ��
#define UPDS_RESTART_SOFTWARE (0) // �������
#define UPDS_RESTART_HARDWARE (1) // Ӳ������
#define UPDS_RESTART_METHOD (UPDS_RESTART_SOFTWARE)

// �������������Ͷ,һ�㲻�Ķ����͵�е����С���²���������ʱ����PWM����Ϊ��λ
#define UPDS_SHORTTIME_US (500.000000f)  // ע���������ʱ��
#define UPDS_INTERVAL_US (800.000000f)   // ��һ��������ʱ����
#define UPDS_INTERVAL_FINAL_MS (0.5)     // �ڶ���������ʱ����
#define UPDS_SHORT_CURRENT_MAG _IQ(0.02) // �������ڸ�ֵ����Ϊ��ת��
#define UPDS_STARTUP_SPD_MAX _IQ(0.5)    // ������Ͷ��������ٶȣ����ڴ��ٶȣ��ȴ����٣����ڴ��ٶȣ���������

// ָ������
#define UPDS_COMMAND_SOFTTOOL (0) // ���LCM_MotorControl��λ��ʹ�ã�ͨ����λ��������ָ��
#define UPDS_COMMAND_VSP (1)      // ��ťADC���
#define UPDS_COMMAND_PWM (2)      // PWMռ�ձ�
#define UPDS_COMMAND_KEIL (3)     // Keil�����ֱ�Ӹ���
#define UPDS_COMMAND_TYPE (UPDS_COMMAND_KEIL)

//====================�����������=======================
#define UPDS_MOTOR_J (0.000100f)        // ���ϵͳת����������ʱû�ã�������Ĭ��ֵ
#define UPDS_RS_REAL (0.1159076f)       // ��������裬ŷķ
#define UPDS_LD_REAL (0.0002850f)       // d���У�H
#define UPDS_LQ_REAL (0.0004590f)       // q���У�H
#define UPDS_PSI_REAL (0.018379f)       // �����������ֵ��V/(rad/s)
#define UPDS_PAIRS (3u)                 // ������
#define UPDS_RATED_CURRENT (28.000000f) // �������A   <=2*IN
#define UPDS_RATED_SPEED (3600.000000f) // �ת�٣�rpm

//====================Ӳ������===========================
#define UPDS_SAMPLE_CURR_R_REAL (0.01000f)    // �������������
#define UPDS_SAMPLE_CURR_OP_REAL (6.000000f)  // ����������˷ŷŴ���
#define UPDS_SAMPLE_VOLT_OP_GAIN (0.040000f)  // ĸ�ߵ�ѹ��������
#define UPDS_SAMPLE_DCBUS_R_REAL (0.0100f)    // ĸ�ߵ�������������ֵ
#define UPDS_SAMPLE_DCBUS_OP_REAL (6.000000f) // ĸ�ߵ��������Ŵ���
#define UPDS_UDC_REAL (48.000000)             // ֱ��ĸ�ߵ�ѹ
#define UPDS_DEADTIME_NS ((u16)1500)          // ����ʱ��,��λns��0~3500ns

//=====================���Ʋ���==========================
#define UPDS_COMMAND_TIME_IQ1_S (1.000000f)     // ָ���0-1PU������ʱ��
#define UPDS_INJECT_D_CURRENT_A_PU (0.000000f)  // ����������������ǿ����������0-0.5, �ɿ���������������Ҷ�����ʵ����󣨱��ۣ�
#define UPDS_PWM_FREQ2 ((u16)16000)             // �ڶ�Ƶ�ʣ����������ã���λ��Hz��fpwm2,//PWM����Ƶ�ʣ����жϣ���Ƶ���л�ʹ�ܺ������á�������PWM2����
#define UPDS_PWM_FREQ ((u16)UPDS_PWM_FREQ2 / 2) // ��һƵ�ʣ����������ã���λ��Hz��fpwm1
#define UPDS_CURRENT_LOOP_BW_HZ (200.000000f)   // ����������Hz��,����������ܹ��󣬷��������������������

// �ٶȻ�PI����
#define UPSD_PI_SPEED_KP (0.100000f) // ����
#define UPSD_PI_SPEED_KI (2.000000f) // ����
#define UPSD_POWER_MAX (800.000000f) // �ٶȻ�����������������ֵ

// ���ʻ�PI����
#define UPDS_CP_KP (1.000000f)  // ����
#define UPDS_CP_KI (10.000000f) // ����

// ���ſ���
#define UPDS_FW_KP (0.200000f)        // ����
#define UPDS_FW_KI (10.000000f)       // ����
#define UPDS_FW_IDREF_MAX (5.000000f) // ����id���ֵ

// �۲�������1��2
#define UPDS_OBS_GAIN_Q (0.010000f) // �۲�������1
#define UPDS_OBS_GAIN_D (2.000000f) // �۲�������2

// ��ʹ�ܳ�ʼλ�ü�⣨IPD����6����ע���ź�����
#define UPDS_IPD_PULSE_US (125.000000f)
#define UPDS_IPD_INTERVAL_US (100.000000f)

//=====================��������=======================
#define UPDS_HARDOVERCURRENT_A (45.000000f) // Ӳ������������Idc����˷ź󵽱Ƚ���������Ӳ����������

#define UPDS_OVERCURRENT_A (33.300000f)        // �������������ӵ���ģֵ��Mag(Is)��A
#define UPDS_OVERCURRENT_A_TIME_MS (1.000000f) // ����������������ʱ�䣬ms

#define UPDS_OVERVOLTAGE_V (55.000000f)          // ĸ�߹�ѹ������V
#define UPDS_OVERVOLTAGE_V_TIME_MS (100.000000f) // ����ĸ�߹�ѹ����ʱ�䣬ms

#define UPDS_UNDERVOLTAGE_V (36.000000f)          // ĸ��Ƿѹ������V
#define UPDS_UNDERVOLTAGE_V_TIME_MS (100.000000f) // ����ĸ��Ƿѹ����ʱ�䣬ms

#define UPDS_MOTOROVERTEMPERATURE_DEGREE (150.000000f) // ������±���ֵ
#define UPDS_MOTOROVERTEMPERATURE_TIME_S (10.000000f)  // ������±���ʱ�䣬s

#define UPDS_IGBTOVERTEMPERATURE_DEGREE (600 * 0x08) // ����ģ����±���ֵ85��C
#define UPDS_IGBTOVERTEMPERATURE_TIME_S (1.000000f)  // ����ģ����±���ʱ��

// ����ʧ�ܱ���
#define UPDS_STARTUP_FAIL_SPEED (200.000000f) // ����ʧ���ٶ�����ֵ
#define UPDS_STARTUP_FAIL_TIME_S (5.000000f)  // ����ʧ�ܱ���ʱ�䣬�����ʱ���ڣ�ת�ٱ������UPDS_STARTUP_FAIL_SPEED����ת��
#define UPDS_RE_STARTUP_TIME_S (5.000000f)    // ����ʧ�ܺ������������ʱ�䣬s
#define UPDS_STARTUP_FAIL_MAX (u8)(5)         // ��������

//==========================ˮ��========================
#define UPDS_IQDIVSPD_GAIN (20.000000f) // ȱˮ����ֵ
#define UPDS_NOWATER_TIME_S (30.0000f)  // ����ȱˮ����ʱ��  unit��s
// �����λ�ж�
// 48v
#define UPDS_NWONE_VOLLOW_V (30.0f)                     // unit��V
#define UPDS_NWONE_VOLHIGH_V (55.0f)                    // unit��V
#define UPDS_NWONE_CUR_A (8.0f)                         // unit��A
#define UPDS_UNDERVOLTAGE_NWONE_V (UPDS_NWONE_VOLLOW_V) // ĸ��Ƿѹ������V
// 60V
#define UPDS_NWTWO_VOLLOW_V (56.0f)            // unit��V
#define UPDS_NWTWO_VOLHIGH_V (66.0f)           // unit��V
#define UPDS_NWTWO_CUR_A (7.0f)                // unit��A
#define UPDS_UNDERVOLTAGE_NWTWO_V (44.000000f) // ĸ��Ƿѹ������V
// 72V
#define UPDS_NWTHREE_VOLLOW_V (67.0f)            // unit��V
#define UPDS_NWTHREE_VOLHIGH_V (96.0f)           // unit��V
#define UPDS_NWTHREE_CUR_A (6.0f)                // unit��A
#define UPDS_UNDERVOLTAGE_NWTHREE_V (54.000000f) // ĸ��Ƿѹ������V

#endif
