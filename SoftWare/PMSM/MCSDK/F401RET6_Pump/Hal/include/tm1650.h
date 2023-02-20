/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2023-02-19 15:37:42
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-02-19 15:56:50
 * @FilePath: \F401RET6_Pump\Hal\include\tm1650.h
 */
#ifndef _TM1650_H
#define _TM1650_H

#include "stdbool.h"
#include "stdint.h"

void TM1650_SetDisplay(uint8_t brightness, uint8_t mode, uint8_t state);
void TM1650_SetIndexNumber(uint8_t index, uint8_t mode, uint8_t num);
void TM1650_Clear(void);
void TM1650_SetNumber(uint16_t num);
#endif
