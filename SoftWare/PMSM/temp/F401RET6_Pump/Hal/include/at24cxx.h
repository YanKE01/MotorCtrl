/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2022-11-10 09:52:43
 * @LastEditors: yanke 1435020085@qq.com
 * @LastEditTime: 2022-11-10 11:03:46
 * @FilePath: \F401RET6\MyDriver\include\at24cxx.h
 */
#ifndef _AT24CXX_H
#define _AT24CXX_H

#include <stdbool.h>
#include <stdint.h>

#define _EEPROM_ADDRESS 0xA0
#define AT24C256_PAGE_BYTE 64
#define AT24C256_MAX_MEM_ADDRESS 32768

bool At24cxx_IsConnected(void);
int At24cxx_WriteOneByte(uint16_t writeAddr, uint8_t dataToWrite);
uint8_t At24cxx_ReadOneByte(uint16_t readAddr);
int At24cxx_Write(uint32_t writeAddr, uint8_t *pBuffer, uint16_t numToWrite);
int At24cxx_Read(uint32_t readAddr, uint8_t *pBuffer, uint16_t numToRead);

#endif
