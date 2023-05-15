/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2023-05-16 09:56:54
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-05-16 14:26:43
 * @FilePath: \LCM_FOC\Headers\User_Sources\HY_Display.h
 */
#ifndef _HY_DISPLAY_H
#define _HY_DISPLAY_H

#include "lcm32f037.h"
#include "lcm32f037_conf.h"

void HY_TM1650_SetDisplay(uint8_t brightness, uint8_t mode, uint8_t state);
void HY_TM1650_SetIndexNumber(uint8_t index, uint8_t mode, uint8_t num);
void HY_TM1650_Clear(void);
void HY_TM1650_SetNumber(uint16_t num);
void HY_TM1650_SetFloat(float num);
void HY_TM1650_SetIndexLetter(uint8_t index, char letter);
void HY_TM1650_ShowFaultCode(uint16_t state);
uint8_t HY_TM1650_ScanKey();

#endif
