/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2022-11-10 11:26:25
 * @LastEditors: yanke 1435020085@qq.com
 * @LastEditTime: 2022-11-10 11:34:46
 * @FilePath: \F401RET6\MyDriver\include\version.h
 */
#ifndef _VERSION_H
#define _VERSION_H

#include "variable.h"

#define SYSTEM_INFO_ADDR 0X10

SystemInfo FirstUpadteVersionInfo(void);
void QuerySystemInfo(void);
void UpdateSystemVersion(uint8_t majorVersion,uint8_t minorVersion,uint8_t pathVersion);

#endif
