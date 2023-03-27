/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2023-03-26 13:59:27
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-03-27 12:30:52
 * @FilePath: \Software\User\Include\TM1650.h
 */
#ifndef _TM1650_H
#define _TM1650_H

#include <FU68xx_2.h>
#include <Myproject.h>

void SetDisplay1650(uint8 brightness, uint8 mode, uint8 state);
void SetIndexNumber1650(uint8 index, uint8 mode, uint8 num);
void SetNumber1650(uint16 num);

#endif