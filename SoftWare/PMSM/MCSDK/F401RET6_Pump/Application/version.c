/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2022-11-10 11:26:16
 * @LastEditors: yanke 1435020085@qq.com
 * @LastEditTime: 2022-11-21 17:37:50
 * @FilePath: \F401RET6\MyDriver\version.c
 * @other: 本文件用于获取配置在EEPROM的数据
 */
#include "version.h"
#include "string.h"
#include "stdio.h"
#include "at24cxx.h"

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
    strcpy(info.developer, "Yanke");

    return info;
}

/**
 * @brief 查询系统信息
 *
 */
void QuerySystemInfo()
{
    SystemInfo info;
    At24cxx_Read(SYSTEM_INFO_ADDR, (uint8_t *)&info, sizeof(SystemInfo));

    if (info.isConfig == 0)
    {
        printf("Not Found System Info\n");
        info = FirstUpadteVersionInfo();
        At24cxx_Write(SYSTEM_INFO_ADDR, (uint8_t *)&info, sizeof(SystemInfo));
        return;
    }

    printf("Developer:%s,Version:%d/%d/%d,Complie Time:%s\n", info.developer, info.majorVersion, info.minorVersion, info.pathVersion, info.lastCompileTime);
}

void UpdateSystemVersion(uint8_t majorVersion, uint8_t minorVersion, uint8_t pathVersion)
{
    SystemInfo info = {
        .isConfig = 1,
        .majorVersion = majorVersion,
        .minorVersion = minorVersion,
        .pathVersion = pathVersion,
    };
    strcpy(info.developer, "Yanke");
    sprintf(info.lastCompileTime, "%s,%s", __DATE__, __TIME__);

    At24cxx_Write(SYSTEM_INFO_ADDR, (uint8_t *)&info, sizeof(SystemInfo));
}
