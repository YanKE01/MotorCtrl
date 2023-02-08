/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2023-02-07 12:24:32
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-02-08 10:07:46
 * @FilePath: \F407IGT6_NOHALL\Ctrl\include\bldc.h
 */
#ifndef _BLDC_H
#define _BLDC_H

extern void (*switchArray[6])(void);
extern void (*ccwArray[6])(void);
extern void (*cwArray[6])(void);

void StopMotor(void);
void StartMotor(void);
void Test(void);
void UphaseH_VphaseL(void);
void UphaseH_WphaseL(void);
void VphaseH_WphaseL(void);
void VphaseH_UphaseL(void);
void WphaseH_UphaseL(void);
void WphaseH_VpahseL(void);

#endif
