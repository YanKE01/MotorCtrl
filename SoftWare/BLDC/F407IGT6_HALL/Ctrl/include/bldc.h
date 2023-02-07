/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2023-02-07 12:24:32
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-02-07 13:50:01
 * @FilePath: \F407IGT6_HALL\Ctrl\include\bldc.h
 */
#ifndef _BLDC_H
#define _BLDC_H

extern void (*switchArray[6])(void);

void StopMotor(void);
void StartMotor(void);
void StartInit(void);

#endif
