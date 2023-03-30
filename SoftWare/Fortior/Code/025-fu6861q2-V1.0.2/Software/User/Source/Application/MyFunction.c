/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2023-03-26 13:09:19
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-03-30 21:02:41
 * @FilePath: \Software\User\Source\Application\MyFunction.c
 */

#include "MyFunction.h"
#include "TM1650.h"
#include <FU68xx_2.h>
#include <Myproject.h>

int count = 0;
int state = 0;

sbit FLASH_LED = P3 ^ 6;

/**
 * @description: 50Ms的任务
 * @return {*}
 */
void MyTask_50Ms_Entry()
{
}

/**
 * @description: 100Ms的任务
 * @return {*}
 */
void MyTask_100Ms_Entry()
{
}

/**
 * @description: 1S的任务
 * @return {*}
 */
void MyTask_1S_Entry()
{
	count++;
	count%=9999;
	SetNumber1650(count);
}

/**
 * @description: 函数运行在1ms的任务中
 * @return {*}
 */
void MyTaskLoop(void)
{
    static int count = 0;
    count++;

    if (count % 50 == 0)
    {
        MyTask_50Ms_Entry();
    }

    if (count % 100 == 0)
    {
        MyTask_100Ms_Entry();
    }

    if (count % 1000 == 0)
    {
        MyTask_1S_Entry();
        count = 0;
    }
}