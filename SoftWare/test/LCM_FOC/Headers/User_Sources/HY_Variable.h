/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2023-05-16 08:59:03
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-06-09 17:22:19
 * @FilePath: \LCM_FOC\Headers\User_Sources\HY_Variable.h
 */
#ifndef _HY_VARIABLE_H
#define _HY_VARIABLE_H

#include "lcm32f037.h"

typedef struct _Motor
{
  /* data */
  uint8_t state;            // 电机运行状态 0:停止 1:启动
  uint8_t fault;            // 电机故障状态 用户状态，需手动置位清零
  uint16_t minSpeed;        // 最低转速
  uint16_t maxSpeed;        // 最高转速
  uint16_t targetSpeed;     // 目标转速,需要限制在最低与最高转速
  uint16_t targetSpeedTemp; // 临时转速
  uint16_t speedChangeStep; // 速度调节步距
  uint16_t currentVbus;     // 当前总线电压
  float busCurrent;         // 当前母线电流

} Motor;

typedef struct _UI
{
  uint8_t modePage;   // 当前模式设置页
  uint8_t isSetSpeed; // 当前是否处于设置速度状态
  uint8_t keyValue;
  uint8_t keyValue_Prev;
} UI;


typedef struct _MMPTADC
{
  uint32_t a7_Value;   
  uint32_t b0_Value;   
  uint32_t b1_Value;   

} MPPTADC;

enum ModePage
{
  SpeedPage = 0,
  VbusPage,
  CurrentPage,
};

extern Motor motor;
extern UI ui;
extern MPPTADC mpptAdc;
void HY_VariableInit(void);

#endif
