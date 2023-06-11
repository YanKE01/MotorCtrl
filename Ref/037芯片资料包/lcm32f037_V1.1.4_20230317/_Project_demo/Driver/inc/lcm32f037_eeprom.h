/**
  ******************************************************************************
  * @file    LCM32F037_EEPROM_Emulation/inc/eeprom.h
  * @author  MCD Application Team
  * @version V0.4.44
  * @date    29-May-2012
  * @brief   This file contains all the functions prototypes for the EEPROM
  *          emulation firmware library.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef LCM32F037_EEPROM_H
#define LCM32F037_EEPROM_H

/* Includes ------------------------------------------------------------------*/
#include "LCM32F037.h"

/* Exported constants --------------------------------------------------------*/
/* Define the size of the sectors to be used */
#define PAGE_SIZE ((uint32_t)0x0200) /* Page size = 512Byte */

/* EEPROM start address in Flash */
#define EEPROM_START_ADDRESS ((uint32_t)0x08007000) /* EEPROM emulation start address:     \
                                                       from sector2, after 40KByte of used \
                                                       Flash memory */

/* Pages 0 and 1 base and end addresses */
#define PAGE0_BASE_ADDRESS ((uint32_t)(EEPROM_START_ADDRESS + 0x0000))
#define PAGE0_END_ADDRESS ((uint32_t)(EEPROM_START_ADDRESS + (PAGE_SIZE - 1)))

#define PAGE1_BASE_ADDRESS ((uint32_t)(EEPROM_START_ADDRESS + 0x0200))
#define PAGE1_END_ADDRESS ((uint32_t)(EEPROM_START_ADDRESS + (2 * PAGE_SIZE - 1)))

/* Used Flash pages for EEPROM emulation */
#define PAGE0 ((uint16_t)0x0000)
#define PAGE1 ((uint16_t)0x0001)

/* No valid page define */
#define NO_VALID_PAGE ((uint16_t)0x00AB)

/* Page status definitions */
#define ERASED ((uint32_t)0xFFFFFFFF)       /* Page is empty */
#define RECEIVE_DATA ((uint32_t)0xFFFFEEEE) /* Page is marked to receive data */
#define VALID_PAGE ((uint32_t)0x0000EEEE)   /* Page containing valid data */

#define VALID_PAGE_H ((uint16_t)0x0000) /* Page containing valid data */
#define VALID_PAGE_L ((uint16_t)0xEEEE) /* Page containing valid data */
//#define RECEIVE_DATA_L          ((uint16_t)0xEEEE)     /* Page is marked to receive data */

/* Valid pages in read and write defines */
#define READ_FROM_VALID_PAGE ((uint8_t)0x00)
#define WRITE_IN_VALID_PAGE ((uint8_t)0x01)

/* Page full define */
#define PAGE_FULL ((uint8_t)0x80)

/* Variables' number */
#define NB_OF_VAR ((uint8_t)0x08)
extern uint16_t VirtAddVarTab[NB_OF_VAR];
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
uint16_t EE_Init(void);
uint16_t EE_ReadVariable(uint16_t VirtAddress, uint16_t *Data);
uint16_t EE_WriteVariable(uint16_t VirtAddress, uint16_t Data);

#endif /* __EEPROM_H */

/************************ (C) COPYRIGHT LCMicroelectronics *****END OF FILE****/
