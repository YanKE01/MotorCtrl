/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2023-05-16 08:59:03
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-09-08 15:23:33
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
  float currentVbus;        // 当前总线电压
  uint16_t targetSpeedPrev; // 目标转速的前一个转速
  float busCurrent;         // 当前母线电流
  float minVbus;            // 最低母线电压
  float vbusArray[5];       // 母线电压数组

} Motor;

typedef struct _UI
{
  uint8_t modePage;   // 当前模式设置页
  uint8_t isSetSpeed; // 当前是否处于设置速度状态
  uint8_t keyValue;
  uint8_t keyValue_Prev;
} UI;

typedef struct _Strategy
{
  int changeCount;
  int lowVbusChangeCount; // 低于母线电压的调整
  int faultCount;         // 失败统计
} Strategy;

typedef struct PD
{
  /* data */
  float error;
  float error_last;
  float kp;
  float kd;
}Pd;


enum ModePage
{
  VbusPage=0,
  SpeedPage,
  CurrentPage,
};

extern Motor motor;
extern UI ui;
extern Strategy strategy;
extern Pd pd;

void HY_VariableInit(void);

#endif
