/*
 * @Author: Yanke@zjut.edu.cn
 * @Date: 2022-11-10 09:52:43
 * @LastEditors: yanke 1435020085@qq.com
 * @LastEditTime: 2022-11-10 11:03:01
 * @FilePath: \F401RET6\MyDriver\at24cxx.c
 */
#include "at24cxx.h"
#include "main.h"
#include "cmsis_os.h"

extern I2C_HandleTypeDef hi2c1;

/**
 * @brief 判断是否查询到AT24CXX
 *
 * @return true
 * @return false
 */
bool At24cxx_IsConnected(void)
{
  if (HAL_I2C_IsDeviceReady(&hi2c1, _EEPROM_ADDRESS, 2, 100) == HAL_OK)
  {
    return true;
  }

  return false;
}

/**
 * @brief 写一个字节
 *
 * @param writeAddr
 * @param dataToWrite
 * @return int
 */
int At24cxx_WriteOneByte(uint16_t writeAddr, uint8_t dataToWrite)
{
  if (HAL_I2C_Mem_Write(&hi2c1, _EEPROM_ADDRESS, writeAddr, I2C_MEMADD_SIZE_16BIT, &dataToWrite, 1, 100) == HAL_OK)
  {
    return 0;
  }

  return -1;
}

/**
 * @brief 读一个字节
 *
 * @param readAddr
 * @param data
 * @return int
 */
uint8_t At24cxx_ReadOneByte(uint16_t readAddr)
{
	uint8_t data;
  if (HAL_I2C_Mem_Read(&hi2c1, _EEPROM_ADDRESS, readAddr, I2C_MEMADD_SIZE_16BIT, &data, 1, 100) == HAL_OK)
  {
    return data;
  }

  return 0;
}

/**
 * @brief 写数据
 *
 * @param writeAddr
 * @param pBuffer
 * @param numToWrite
 * @return int
 */
int At24cxx_Write(uint32_t writeAddr, uint8_t *pBuffer, uint16_t numToWrite)
{
  uint16_t i = 0;
  if (writeAddr + numToWrite > AT24C256_MAX_MEM_ADDRESS)
  {
    // 超过写入范围
    return -1;
  }

  // 循环写入
  while (1)
  {
    if (At24cxx_WriteOneByte(writeAddr, pBuffer[i]) < 0)
    {
      HAL_Delay(5);
    }
    else
    {
      writeAddr++;
      i++;
    }

    if (i == numToWrite)
    {
      break;
    }
  }
  return 0;
}


/**
 * @brief 读数据
 * 
 * @param readAddr 
 * @param pBuffer 
 * @param numToRead 
 * @return int 
 */
int At24cxx_Read(uint32_t readAddr, uint8_t *pBuffer, uint16_t numToRead)
{
  if (readAddr + numToRead > AT24C256_MAX_MEM_ADDRESS)
  {
    return -1;
  }

  while (numToRead)
  {
    *pBuffer++=At24cxx_ReadOneByte(readAddr++);
    numToRead--;
  }

  return 0;
}





