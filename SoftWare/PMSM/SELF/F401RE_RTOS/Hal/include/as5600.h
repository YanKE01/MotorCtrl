/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2023-01-26 21:26:38
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-02-03 17:42:29
 * @FilePath: \PMSM_FOC\Hal\include\as5600.h
 */
#ifndef _AS5600_H
#define _AS5600_H

#include "stdint.h"

HAL_StatusTypeDef FindAs5600Device(void);
int16_t GetRawAngle(void);
float GetAngle(void);

#endif
