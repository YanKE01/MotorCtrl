/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2022-11-10 11:26:16
 * @LastEditors: LINKEEE 1435020085@qq.com
 * @LastEditTime: 2023-02-21 19:58:18
 * @FilePath: \F401RET6_Pump\Application\version.c
 * @other: 本文件用于获取配置在EEPROM的数据
 */
#include "version.h"
#include "string.h"
#include "stdio.h"
#include "at24cxx.h"

SystemInfo systemInfo;

/**
 * @brief 上电首次写入数据
 *
 * @return SystemInfo
 */
SystemInfo FirstUpadteVersionInfo()
{
    SystemInfo info;
    info.isConfig = 1;
    info.majorVersion = 0;
    info.minorVersion = 1;
    info.pathVersion = 1;
    info.motorParameter.minSpeed = 600;        // 最小600转速
    info.motorParameter.maxSpeed = 3000;       // 最大 3000rpm转速
    info.motorParameter.speedDuration = 2000;  // 速度调节时长 2000ms
    info.motorParameter.speedChangeStep = 100; // 每次按100转速来调节
    info.motorParameter.maxStartUp = 5;        // 最大启动次数为5
    strcpy(info.developer, "Yanke");

    return info;
}

/**
 * @brief 查询系统信息
 *
 */
void QuerySystemInfo()
{
    // SystemInfo info;
    At24cxx_Read(SYSTEM_INFO_ADDR, (uint8_t *)&systemInfo, sizeof(SystemInfo));

    if (systemInfo.isConfig == 0)
    {
        printf("Not Found System Info\n");
        systemInfo = FirstUpadteVersionInfo();
        At24cxx_Write(SYSTEM_INFO_ADDR, (uint8_t *)&systemInfo, sizeof(SystemInfo));
        return;
    }

    printf("Developer:%s,Version:%d/%d/%d,Complie Time:%s\n", systemInfo.developer, systemInfo.majorVersion, systemInfo.minorVersion, systemInfo.pathVersion, systemInfo.lastCompileTime);
    printf("  MinSpeed:%d,MaxSpeed:%d,Duration:%d,Step:%d\n", systemInfo.motorParameter.minSpeed, systemInfo.motorParameter.maxSpeed, systemInfo.motorParameter.speedDuration, systemInfo.motorParameter.speedChangeStep);
}

/**
 * @brief 修改系统版本 下次生效
 *
 * @param majorVersion
 * @param minorVersion
 * @param pathVersion
 */
void UpdateSystemVersion(uint8_t majorVersion, uint8_t minorVersion, uint8_t pathVersion)
{
    SystemInfo info = {
        .isConfig = 1,
        .majorVersion = majorVersion,
        .minorVersion = minorVersion,
        .pathVersion = pathVersion,
        .motorParameter.minSpeed = 600,        // 最小600转速
        .motorParameter.maxSpeed = 3000,       // 最大 3000rpm转速
        .motorParameter.speedDuration = 2000,  // 速度调节时长 2000ms
        .motorParameter.speedChangeStep = 100, // 每次按100转速来调节
        .motorParameter.maxStartUp = 5,        // 最大启动次数为5
    };
    strcpy(info.developer, "Yanke");
    sprintf(info.lastCompileTime, "%s,%s", __DATE__, __TIME__);

    At24cxx_Write(SYSTEM_INFO_ADDR, (uint8_t *)&info, sizeof(SystemInfo));
}
