/**
  ******************************************************************************
  * @file    lcm32f037_exti.h
  * @author  MCD Application Team
  * @version V0.4.44
  * @date    14-04-2021
  * @brief   This file contains all the functions prototypes for the EXTI firmware
  *          library.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, LCMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2020 LCMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef LCM32F037_EXTI_H
#define LCM32F037_EXTI_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "lcm32f037.h"

  /** @addtogroup LCM32F037_StdPeriph_Driver
  * @{
  */

  /** @addtogroup EXTI
  * @{
  */

  /** @defgroup EXTI_Exported_Types
  * @{
  */

  /** 
  * @brief  EXTI mode enumeration  
  */

  typedef enum
  {
    EXTI_Mode_Interrupt = 0x00,
    EXTI_Mode_Event = 0x04
  } EXTIMode_TypeDef;

#define IS_EXTI_MODE(MODE) (((MODE) == EXTI_Mode_Interrupt) || ((MODE) == EXTI_Mode_Event))

  /** 
  * @brief  EXTI Trigger enumeration  
  */

  typedef enum
  {
    EXTI_Trigger_Rising = 0x08,
    EXTI_Trigger_Falling = 0x0C,
    EXTI_Trigger_Rising_Falling = 0x10
  } EXTITrigger_TypeDef;

#define IS_EXTI_TRIGGER(TRIGGER) (((TRIGGER) == EXTI_Trigger_Rising) ||  \
                                  ((TRIGGER) == EXTI_Trigger_Falling) || \
                                  ((TRIGGER) == EXTI_Trigger_Rising_Falling))
  /** 
  * @brief  EXTI Init Structure definition  
  */

  typedef struct
  {
    uint32_t EXTI_Line; /*!< Specifies the EXTI lines to be enabled or disabled.
                                         This parameter can be any combination of @ref EXTI_Lines */

    EXTIMode_TypeDef EXTI_Mode; /*!< Specifies the mode for the EXTI lines.
                                         This parameter can be a value of @ref EXTIMode_TypeDef */

    EXTITrigger_TypeDef EXTI_Trigger; /*!< Specifies the trigger signal active edge for the EXTI lines.
                                         This parameter can be a value of @ref EXTIMode_TypeDef */

    FunctionalState EXTI_LineCmd; /*!< Specifies the new state of the selected EXTI lines.
                                         This parameter can be set either to ENABLE or DISABLE */
  } EXTI_InitTypeDef;

  /**
  * @}
  */

  /** @defgroup EXTI_Exported_Constants
  * @{
  */

  /** @defgroup EXTI_Lines 
  * @{
  */

#define EXTI_Line0 ((uint32_t)0x00001)    /*!< External interrupt line 0 */
#define EXTI_Line1 ((uint32_t)0x00002)    /*!< External interrupt line 1 */
#define EXTI_Line2 ((uint32_t)0x00004)    /*!< External interrupt line 2 */
#define EXTI_Line3 ((uint32_t)0x00008)    /*!< External interrupt line 3 */
#define EXTI_Line4 ((uint32_t)0x00010)    /*!< External interrupt line 4 */
#define EXTI_Line5 ((uint32_t)0x00020)    /*!< External interrupt line 5 */
#define EXTI_Line6 ((uint32_t)0x00040)    /*!< External interrupt line 6 */
#define EXTI_Line7 ((uint32_t)0x00080)    /*!< External interrupt line 7 */
#define EXTI_Line8 ((uint32_t)0x00100)    /*!< External interrupt line 8 */
#define EXTI_Line9 ((uint32_t)0x00200)    /*!< External interrupt line 9 */
#define EXTI_Line10 ((uint32_t)0x00400)   /*!< External interrupt line 10 */
#define EXTI_Line11 ((uint32_t)0x00800)   /*!< External interrupt line 11 */
#define EXTI_Line12 ((uint32_t)0x01000)   /*!< External interrupt line 12 */
#define EXTI_Line13 ((uint32_t)0x02000)   /*!< External interrupt line 13 */
#define EXTI_Line14 ((uint32_t)0x04000)   /*!< External interrupt line 14 */
#define EXTI_Line15 ((uint32_t)0x08000)   /*!< External interrupt line 15 */
#define EXTI_Line16 ((uint32_t)0x10000)   /*!< External interrupt line 16  */
#define EXTI_Line17 ((uint32_t)0x20000)   /*!< External interrupt line 17  */
#define EXTI_Line18 ((uint32_t)0x40000)   /*!< External interrupt line 18 */
#define EXTI_Line19 ((uint32_t)0x80000)   /*!< External interrupt line 19  */
#define EXTI_Line20 ((uint32_t)0x100000)  /*!< External interrupt line 20  */
#define EXTI_Line21 ((uint32_t)0x200000)  /*!< External interrupt line 21  */
#define EXTI_Line22 ((uint32_t)0x400000)  /*!< External interrupt line 22 */
#define EXTI_Line23 ((uint32_t)0x800000)  /*!< External interrupt line 23  */
#define EXTI_Line24 ((uint32_t)0x1000000) /*!< External interrupt line 24  */

#define IS_EXTI_LINE(LINE) ((((LINE) & (uint32_t)0xFFF00000) == 0x00) && ((LINE) != (uint16_t)0x00))
#define IS_GET_EXTI_LINE(LINE) (((LINE) == EXTI_Line0) || ((LINE) == EXTI_Line1) ||   \
                                ((LINE) == EXTI_Line2) || ((LINE) == EXTI_Line3) ||   \
                                ((LINE) == EXTI_Line4) || ((LINE) == EXTI_Line5) ||   \
                                ((LINE) == EXTI_Line6) || ((LINE) == EXTI_Line7) ||   \
                                ((LINE) == EXTI_Line8) || ((LINE) == EXTI_Line9) ||   \
                                ((LINE) == EXTI_Line10) || ((LINE) == EXTI_Line11) || \
                                ((LINE) == EXTI_Line12) || ((LINE) == EXTI_Line13) || \
                                ((LINE) == EXTI_Line14) || ((LINE) == EXTI_Line15) || \
                                ((LINE) == EXTI_Line16) || ((LINE) == EXTI_Line17) || \
                                ((LINE) == EXTI_Line18) || ((LINE) == EXTI_Line19) || \
                                ((LINE) == EXTI_Line20) || ((LINE) == EXTI_Line21) || \
                                ((LINE) == EXTI_Line22) || ((LINE) == EXTI_Line23) || \
                                (LINE) == EXTI_Line24)

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup EXTI_Exported_Macros
  * @{
  */

/**
  * @}
  */
/* =========================================================================================================================== */
/* ================                                           EXTI                                            ================ */
/* =========================================================================================================================== */

/* ==========================================================  IMR  ========================================================== */
#define EXTI_IMR_MR24_Pos (24UL)        /*!< MR24 (Bit 24)                                         */
#define EXTI_IMR_MR24_Msk (0x1000000UL) /*!< MR24 (Bitfield-Mask: 0x01)                            */
#define EXTI_IMR_MR23_Pos (23UL)        /*!< MR23 (Bit 23)                                         */
#define EXTI_IMR_MR23_Msk (0x800000UL)  /*!< MR23 (Bitfield-Mask: 0x01)                            */
#define EXTI_IMR_MR22_Pos (22UL)        /*!< MR22 (Bit 22)                                         */
#define EXTI_IMR_MR22_Msk (0x400000UL)  /*!< MR22 (Bitfield-Mask: 0x01)                            */
#define EXTI_IMR_MR21_Pos (21UL)        /*!< MR21 (Bit 21)                                         */
#define EXTI_IMR_MR21_Msk (0x200000UL)  /*!< MR21 (Bitfield-Mask: 0x01)                            */
#define EXTI_IMR_MR20_Pos (20UL)        /*!< MR20 (Bit 20)                                         */
#define EXTI_IMR_MR20_Msk (0x100000UL)  /*!< MR20 (Bitfield-Mask: 0x01)                            */
#define EXTI_IMR_MR19_Pos (19UL)        /*!< MR19 (Bit 19)                                         */
#define EXTI_IMR_MR19_Msk (0x80000UL)   /*!< MR19 (Bitfield-Mask: 0x01)                            */
#define EXTI_IMR_MR18_Pos (18UL)        /*!< MR18 (Bit 18)                                         */
#define EXTI_IMR_MR18_Msk (0x40000UL)   /*!< MR18 (Bitfield-Mask: 0x01)                            */
#define EXTI_IMR_MR17_Pos (17UL)        /*!< MR17 (Bit 17)                                         */
#define EXTI_IMR_MR17_Msk (0x20000UL)   /*!< MR17 (Bitfield-Mask: 0x01)                            */
#define EXTI_IMR_MR16_Pos (16UL)        /*!< MR16 (Bit 16)                                         */
#define EXTI_IMR_MR16_Msk (0x10000UL)   /*!< MR16 (Bitfield-Mask: 0x01)                            */
#define EXTI_IMR_MR15_Pos (15UL)        /*!< MR15 (Bit 15)                                         */
#define EXTI_IMR_MR15_Msk (0x8000UL)    /*!< MR15 (Bitfield-Mask: 0x01)                            */
#define EXTI_IMR_MR14_Pos (14UL)        /*!< MR14 (Bit 14)                                         */
#define EXTI_IMR_MR14_Msk (0x4000UL)    /*!< MR14 (Bitfield-Mask: 0x01)                            */
#define EXTI_IMR_MR13_Pos (13UL)        /*!< MR13 (Bit 13)                                         */
#define EXTI_IMR_MR13_Msk (0x2000UL)    /*!< MR13 (Bitfield-Mask: 0x01)                            */
#define EXTI_IMR_MR12_Pos (12UL)        /*!< MR12 (Bit 12)                                         */
#define EXTI_IMR_MR12_Msk (0x1000UL)    /*!< MR12 (Bitfield-Mask: 0x01)                            */
#define EXTI_IMR_MR11_Pos (11UL)        /*!< MR11 (Bit 11)                                         */
#define EXTI_IMR_MR11_Msk (0x800UL)     /*!< MR11 (Bitfield-Mask: 0x01)                            */
#define EXTI_IMR_MR10_Pos (10UL)        /*!< MR10 (Bit 10)                                         */
#define EXTI_IMR_MR10_Msk (0x400UL)     /*!< MR10 (Bitfield-Mask: 0x01)                            */
#define EXTI_IMR_MR9_Pos (9UL)          /*!< MR9 (Bit 9)                                           */
#define EXTI_IMR_MR9_Msk (0x200UL)      /*!< MR9 (Bitfield-Mask: 0x01)                             */
#define EXTI_IMR_MR8_Pos (8UL)          /*!< MR8 (Bit 8)                                           */
#define EXTI_IMR_MR8_Msk (0x100UL)      /*!< MR8 (Bitfield-Mask: 0x01)                             */
#define EXTI_IMR_MR7_Pos (7UL)          /*!< MR7 (Bit 7)                                           */
#define EXTI_IMR_MR7_Msk (0x80UL)       /*!< MR7 (Bitfield-Mask: 0x01)                             */
#define EXTI_IMR_MR6_Pos (6UL)          /*!< MR6 (Bit 6)                                           */
#define EXTI_IMR_MR6_Msk (0x40UL)       /*!< MR6 (Bitfield-Mask: 0x01)                             */
#define EXTI_IMR_MR5_Pos (5UL)          /*!< MR5 (Bit 5)                                           */
#define EXTI_IMR_MR5_Msk (0x20UL)       /*!< MR5 (Bitfield-Mask: 0x01)                             */
#define EXTI_IMR_MR4_Pos (4UL)          /*!< MR4 (Bit 4)                                           */
#define EXTI_IMR_MR4_Msk (0x10UL)       /*!< MR4 (Bitfield-Mask: 0x01)                             */
#define EXTI_IMR_MR3_Pos (3UL)          /*!< MR3 (Bit 3)                                           */
#define EXTI_IMR_MR3_Msk (0x8UL)        /*!< MR3 (Bitfield-Mask: 0x01)                             */
#define EXTI_IMR_MR2_Pos (2UL)          /*!< MR2 (Bit 2)                                           */
#define EXTI_IMR_MR2_Msk (0x4UL)        /*!< MR2 (Bitfield-Mask: 0x01)                             */
#define EXTI_IMR_MR1_Pos (1UL)          /*!< MR1 (Bit 1)                                           */
#define EXTI_IMR_MR1_Msk (0x2UL)        /*!< MR1 (Bitfield-Mask: 0x01)                             */
#define EXTI_IMR_MR0_Pos (0UL)          /*!< MR0 (Bit 0)                                           */
#define EXTI_IMR_MR0_Msk (0x1UL)        /*!< MR0 (Bitfield-Mask: 0x01)                             */
/* ==========================================================  EMR  ========================================================== */
#define EXTI_EMR_MR24_Pos (24UL)        /*!< MR24 (Bit 24)                                         */
#define EXTI_EMR_MR24_Msk (0x1000000UL) /*!< MR24 (Bitfield-Mask: 0x01)                            */
#define EXTI_EMR_MR23_Pos (23UL)        /*!< MR23 (Bit 23)                                         */
#define EXTI_EMR_MR23_Msk (0x800000UL)  /*!< MR23 (Bitfield-Mask: 0x01)                            */
#define EXTI_EMR_MR22_Pos (22UL)        /*!< MR22 (Bit 22)                                         */
#define EXTI_EMR_MR22_Msk (0x400000UL)  /*!< MR22 (Bitfield-Mask: 0x01)                            */
#define EXTI_EMR_MR21_Pos (21UL)        /*!< MR21 (Bit 21)                                         */
#define EXTI_EMR_MR21_Msk (0x200000UL)  /*!< MR21 (Bitfield-Mask: 0x01)                            */
#define EXTI_EMR_MR20_Pos (20UL)        /*!< MR20 (Bit 20)                                         */
#define EXTI_EMR_MR20_Msk (0x100000UL)  /*!< MR20 (Bitfield-Mask: 0x01)                            */
#define EXTI_EMR_MR19_Pos (19UL)        /*!< MR19 (Bit 19)                                         */
#define EXTI_EMR_MR19_Msk (0x80000UL)   /*!< MR19 (Bitfield-Mask: 0x01)                            */
#define EXTI_EMR_MR18_Pos (18UL)        /*!< MR18 (Bit 18)                                         */
#define EXTI_EMR_MR18_Msk (0x40000UL)   /*!< MR18 (Bitfield-Mask: 0x01)                            */
#define EXTI_EMR_MR17_Pos (17UL)        /*!< MR17 (Bit 17)                                         */
#define EXTI_EMR_MR17_Msk (0x20000UL)   /*!< MR17 (Bitfield-Mask: 0x01)                            */
#define EXTI_EMR_MR16_Pos (16UL)        /*!< MR16 (Bit 16)                                         */
#define EXTI_EMR_MR16_Msk (0x10000UL)   /*!< MR16 (Bitfield-Mask: 0x01)                            */
#define EXTI_EMR_MR15_Pos (15UL)        /*!< MR15 (Bit 15)                                         */
#define EXTI_EMR_MR15_Msk (0x8000UL)    /*!< MR15 (Bitfield-Mask: 0x01)                            */
#define EXTI_EMR_MR14_Pos (14UL)        /*!< MR14 (Bit 14)                                         */
#define EXTI_EMR_MR14_Msk (0x4000UL)    /*!< MR14 (Bitfield-Mask: 0x01)                            */
#define EXTI_EMR_MR13_Pos (13UL)        /*!< MR13 (Bit 13)                                         */
#define EXTI_EMR_MR13_Msk (0x2000UL)    /*!< MR13 (Bitfield-Mask: 0x01)                            */
#define EXTI_EMR_MR12_Pos (12UL)        /*!< MR12 (Bit 12)                                         */
#define EXTI_EMR_MR12_Msk (0x1000UL)    /*!< MR12 (Bitfield-Mask: 0x01)                            */
#define EXTI_EMR_MR11_Pos (11UL)        /*!< MR11 (Bit 11)                                         */
#define EXTI_EMR_MR11_Msk (0x800UL)     /*!< MR11 (Bitfield-Mask: 0x01)                            */
#define EXTI_EMR_MR10_Pos (10UL)        /*!< MR10 (Bit 10)                                         */
#define EXTI_EMR_MR10_Msk (0x400UL)     /*!< MR10 (Bitfield-Mask: 0x01)                            */
#define EXTI_EMR_MR9_Pos (9UL)          /*!< MR9 (Bit 9)                                           */
#define EXTI_EMR_MR9_Msk (0x200UL)      /*!< MR9 (Bitfield-Mask: 0x01)                             */
#define EXTI_EMR_MR8_Pos (8UL)          /*!< MR8 (Bit 8)                                           */
#define EXTI_EMR_MR8_Msk (0x100UL)      /*!< MR8 (Bitfield-Mask: 0x01)                             */
#define EXTI_EMR_MR7_Pos (7UL)          /*!< MR7 (Bit 7)                                           */
#define EXTI_EMR_MR7_Msk (0x80UL)       /*!< MR7 (Bitfield-Mask: 0x01)                             */
#define EXTI_EMR_MR6_Pos (6UL)          /*!< MR6 (Bit 6)                                           */
#define EXTI_EMR_MR6_Msk (0x40UL)       /*!< MR6 (Bitfield-Mask: 0x01)                             */
#define EXTI_EMR_MR5_Pos (5UL)          /*!< MR5 (Bit 5)                                           */
#define EXTI_EMR_MR5_Msk (0x20UL)       /*!< MR5 (Bitfield-Mask: 0x01)                             */
#define EXTI_EMR_MR4_Pos (4UL)          /*!< MR4 (Bit 4)                                           */
#define EXTI_EMR_MR4_Msk (0x10UL)       /*!< MR4 (Bitfield-Mask: 0x01)                             */
#define EXTI_EMR_MR3_Pos (3UL)          /*!< MR3 (Bit 3)                                           */
#define EXTI_EMR_MR3_Msk (0x8UL)        /*!< MR3 (Bitfield-Mask: 0x01)                             */
#define EXTI_EMR_MR2_Pos (2UL)          /*!< MR2 (Bit 2)                                           */
#define EXTI_EMR_MR2_Msk (0x4UL)        /*!< MR2 (Bitfield-Mask: 0x01)                             */
#define EXTI_EMR_MR1_Pos (1UL)          /*!< MR1 (Bit 1)                                           */
#define EXTI_EMR_MR1_Msk (0x2UL)        /*!< MR1 (Bitfield-Mask: 0x01)                             */
#define EXTI_EMR_MR0_Pos (0UL)          /*!< MR0 (Bit 0)                                           */
#define EXTI_EMR_MR0_Msk (0x1UL)        /*!< MR0 (Bitfield-Mask: 0x01)                             */
/* =========================================================  RTSR  ========================================================== */
#define EXTI_RTSR_TR24_Pos (24UL)        /*!< TR24 (Bit 24)                                         */
#define EXTI_RTSR_TR24_Msk (0x1000000UL) /*!< TR24 (Bitfield-Mask: 0x01)                            */
#define EXTI_RTSR_TR23_Pos (23UL)        /*!< TR23 (Bit 23)                                         */
#define EXTI_RTSR_TR23_Msk (0x800000UL)  /*!< TR23 (Bitfield-Mask: 0x01)                            */
#define EXTI_RTSR_TR22_Pos (22UL)        /*!< TR22 (Bit 22)                                         */
#define EXTI_RTSR_TR22_Msk (0x400000UL)  /*!< TR22 (Bitfield-Mask: 0x01)                            */
#define EXTI_RTSR_TR21_Pos (21UL)        /*!< TR21 (Bit 21)                                         */
#define EXTI_RTSR_TR21_Msk (0x200000UL)  /*!< TR21 (Bitfield-Mask: 0x01)                            */
#define EXTI_RTSR_TR20_Pos (20UL)        /*!< TR20 (Bit 20)                                         */
#define EXTI_RTSR_TR20_Msk (0x100000UL)  /*!< TR20 (Bitfield-Mask: 0x01)                            */
#define EXTI_RTSR_TR19_Pos (19UL)        /*!< TR19 (Bit 19)                                         */
#define EXTI_RTSR_TR19_Msk (0x80000UL)   /*!< TR19 (Bitfield-Mask: 0x01)                            */
#define EXTI_RTSR_TR18_Pos (18UL)        /*!< TR18 (Bit 18)                                         */
#define EXTI_RTSR_TR18_Msk (0x40000UL)   /*!< TR18 (Bitfield-Mask: 0x01)                            */
#define EXTI_RTSR_TR17_Pos (17UL)        /*!< TR17 (Bit 17)                                         */
#define EXTI_RTSR_TR17_Msk (0x20000UL)   /*!< TR17 (Bitfield-Mask: 0x01)                            */
#define EXTI_RTSR_TR16_Pos (16UL)        /*!< TR16 (Bit 16)                                         */
#define EXTI_RTSR_TR16_Msk (0x10000UL)   /*!< TR16 (Bitfield-Mask: 0x01)                            */
#define EXTI_RTSR_TR15_Pos (15UL)        /*!< TR15 (Bit 15)                                         */
#define EXTI_RTSR_TR15_Msk (0x8000UL)    /*!< TR15 (Bitfield-Mask: 0x01)                            */
#define EXTI_RTSR_TR14_Pos (14UL)        /*!< TR14 (Bit 14)                                         */
#define EXTI_RTSR_TR14_Msk (0x4000UL)    /*!< TR14 (Bitfield-Mask: 0x01)                            */
#define EXTI_RTSR_TR13_Pos (13UL)        /*!< TR13 (Bit 13)                                         */
#define EXTI_RTSR_TR13_Msk (0x2000UL)    /*!< TR13 (Bitfield-Mask: 0x01)                            */
#define EXTI_RTSR_TR12_Pos (12UL)        /*!< TR12 (Bit 12)                                         */
#define EXTI_RTSR_TR12_Msk (0x1000UL)    /*!< TR12 (Bitfield-Mask: 0x01)                            */
#define EXTI_RTSR_TR11_Pos (11UL)        /*!< TR11 (Bit 11)                                         */
#define EXTI_RTSR_TR11_Msk (0x800UL)     /*!< TR11 (Bitfield-Mask: 0x01)                            */
#define EXTI_RTSR_TR10_Pos (10UL)        /*!< TR10 (Bit 10)                                         */
#define EXTI_RTSR_TR10_Msk (0x400UL)     /*!< TR10 (Bitfield-Mask: 0x01)                            */
#define EXTI_RTSR_TR9_Pos (9UL)          /*!< TR9 (Bit 9)                                           */
#define EXTI_RTSR_TR9_Msk (0x200UL)      /*!< TR9 (Bitfield-Mask: 0x01)                             */
#define EXTI_RTSR_TR8_Pos (8UL)          /*!< TR8 (Bit 8)                                           */
#define EXTI_RTSR_TR8_Msk (0x100UL)      /*!< TR8 (Bitfield-Mask: 0x01)                             */
#define EXTI_RTSR_TR7_Pos (7UL)          /*!< TR7 (Bit 7)                                           */
#define EXTI_RTSR_TR7_Msk (0x80UL)       /*!< TR7 (Bitfield-Mask: 0x01)                             */
#define EXTI_RTSR_TR6_Pos (6UL)          /*!< TR6 (Bit 6)                                           */
#define EXTI_RTSR_TR6_Msk (0x40UL)       /*!< TR6 (Bitfield-Mask: 0x01)                             */
#define EXTI_RTSR_TR5_Pos (5UL)          /*!< TR5 (Bit 5)                                           */
#define EXTI_RTSR_TR5_Msk (0x20UL)       /*!< TR5 (Bitfield-Mask: 0x01)                             */
#define EXTI_RTSR_TR4_Pos (4UL)          /*!< TR4 (Bit 4)                                           */
#define EXTI_RTSR_TR4_Msk (0x10UL)       /*!< TR4 (Bitfield-Mask: 0x01)                             */
#define EXTI_RTSR_TR3_Pos (3UL)          /*!< TR3 (Bit 3)                                           */
#define EXTI_RTSR_TR3_Msk (0x8UL)        /*!< TR3 (Bitfield-Mask: 0x01)                             */
#define EXTI_RTSR_TR2_Pos (2UL)          /*!< TR2 (Bit 2)                                           */
#define EXTI_RTSR_TR2_Msk (0x4UL)        /*!< TR2 (Bitfield-Mask: 0x01)                             */
#define EXTI_RTSR_TR1_Pos (1UL)          /*!< TR1 (Bit 1)                                           */
#define EXTI_RTSR_TR1_Msk (0x2UL)        /*!< TR1 (Bitfield-Mask: 0x01)                             */
#define EXTI_RTSR_TR0_Pos (0UL)          /*!< TR0 (Bit 0)                                           */
#define EXTI_RTSR_TR0_Msk (0x1UL)        /*!< TR0 (Bitfield-Mask: 0x01)                             */
/* =========================================================  FTSR  ========================================================== */
#define EXTI_FTSR_TR24_Pos (24UL)        /*!< TR24 (Bit 24)                                         */
#define EXTI_FTSR_TR24_Msk (0x1000000UL) /*!< TR24 (Bitfield-Mask: 0x01)                            */
#define EXTI_FTSR_TR23_Pos (23UL)        /*!< TR23 (Bit 23)                                         */
#define EXTI_FTSR_TR23_Msk (0x800000UL)  /*!< TR23 (Bitfield-Mask: 0x01)                            */
#define EXTI_FTSR_TR22_Pos (22UL)        /*!< TR22 (Bit 22)                                         */
#define EXTI_FTSR_TR22_Msk (0x400000UL)  /*!< TR22 (Bitfield-Mask: 0x01)                            */
#define EXTI_FTSR_TR21_Pos (21UL)        /*!< TR21 (Bit 21)                                         */
#define EXTI_FTSR_TR21_Msk (0x200000UL)  /*!< TR21 (Bitfield-Mask: 0x01)                            */
#define EXTI_FTSR_TR20_Pos (20UL)        /*!< TR20 (Bit 20)                                         */
#define EXTI_FTSR_TR20_Msk (0x100000UL)  /*!< TR20 (Bitfield-Mask: 0x01)                            */
#define EXTI_FTSR_TR19_Pos (19UL)        /*!< TR19 (Bit 19)                                         */
#define EXTI_FTSR_TR19_Msk (0x80000UL)   /*!< TR19 (Bitfield-Mask: 0x01)                            */
#define EXTI_FTSR_TR18_Pos (18UL)        /*!< TR18 (Bit 18)                                         */
#define EXTI_FTSR_TR18_Msk (0x40000UL)   /*!< TR18 (Bitfield-Mask: 0x01)                            */
#define EXTI_FTSR_TR17_Pos (17UL)        /*!< TR17 (Bit 17)                                         */
#define EXTI_FTSR_TR17_Msk (0x20000UL)   /*!< TR17 (Bitfield-Mask: 0x01)                            */
#define EXTI_FTSR_TR16_Pos (16UL)        /*!< TR16 (Bit 16)                                         */
#define EXTI_FTSR_TR16_Msk (0x10000UL)   /*!< TR16 (Bitfield-Mask: 0x01)                            */
#define EXTI_FTSR_TR15_Pos (15UL)        /*!< TR15 (Bit 15)                                         */
#define EXTI_FTSR_TR15_Msk (0x8000UL)    /*!< TR15 (Bitfield-Mask: 0x01)                            */
#define EXTI_FTSR_TR14_Pos (14UL)        /*!< TR14 (Bit 14)                                         */
#define EXTI_FTSR_TR14_Msk (0x4000UL)    /*!< TR14 (Bitfield-Mask: 0x01)                            */
#define EXTI_FTSR_TR13_Pos (13UL)        /*!< TR13 (Bit 13)                                         */
#define EXTI_FTSR_TR13_Msk (0x2000UL)    /*!< TR13 (Bitfield-Mask: 0x01)                            */
#define EXTI_FTSR_TR12_Pos (12UL)        /*!< TR12 (Bit 12)                                         */
#define EXTI_FTSR_TR12_Msk (0x1000UL)    /*!< TR12 (Bitfield-Mask: 0x01)                            */
#define EXTI_FTSR_TR11_Pos (11UL)        /*!< TR11 (Bit 11)                                         */
#define EXTI_FTSR_TR11_Msk (0x800UL)     /*!< TR11 (Bitfield-Mask: 0x01)                            */
#define EXTI_FTSR_TR10_Pos (10UL)        /*!< TR10 (Bit 10)                                         */
#define EXTI_FTSR_TR10_Msk (0x400UL)     /*!< TR10 (Bitfield-Mask: 0x01)                            */
#define EXTI_FTSR_TR9_Pos (9UL)          /*!< TR9 (Bit 9)                                           */
#define EXTI_FTSR_TR9_Msk (0x200UL)      /*!< TR9 (Bitfield-Mask: 0x01)                             */
#define EXTI_FTSR_TR8_Pos (8UL)          /*!< TR8 (Bit 8)                                           */
#define EXTI_FTSR_TR8_Msk (0x100UL)      /*!< TR8 (Bitfield-Mask: 0x01)                             */
#define EXTI_FTSR_TR7_Pos (7UL)          /*!< TR7 (Bit 7)                                           */
#define EXTI_FTSR_TR7_Msk (0x80UL)       /*!< TR7 (Bitfield-Mask: 0x01)                             */
#define EXTI_FTSR_TR6_Pos (6UL)          /*!< TR6 (Bit 6)                                           */
#define EXTI_FTSR_TR6_Msk (0x40UL)       /*!< TR6 (Bitfield-Mask: 0x01)                             */
#define EXTI_FTSR_TR5_Pos (5UL)          /*!< TR5 (Bit 5)                                           */
#define EXTI_FTSR_TR5_Msk (0x20UL)       /*!< TR5 (Bitfield-Mask: 0x01)                             */
#define EXTI_FTSR_TR4_Pos (4UL)          /*!< TR4 (Bit 4)                                           */
#define EXTI_FTSR_TR4_Msk (0x10UL)       /*!< TR4 (Bitfield-Mask: 0x01)                             */
#define EXTI_FTSR_TR3_Pos (3UL)          /*!< TR3 (Bit 3)                                           */
#define EXTI_FTSR_TR3_Msk (0x8UL)        /*!< TR3 (Bitfield-Mask: 0x01)                             */
#define EXTI_FTSR_TR2_Pos (2UL)          /*!< TR2 (Bit 2)                                           */
#define EXTI_FTSR_TR2_Msk (0x4UL)        /*!< TR2 (Bitfield-Mask: 0x01)                             */
#define EXTI_FTSR_TR1_Pos (1UL)          /*!< TR1 (Bit 1)                                           */
#define EXTI_FTSR_TR1_Msk (0x2UL)        /*!< TR1 (Bitfield-Mask: 0x01)                             */
#define EXTI_FTSR_TR0_Pos (0UL)          /*!< TR0 (Bit 0)                                           */
#define EXTI_FTSR_TR0_Msk (0x1UL)        /*!< TR0 (Bitfield-Mask: 0x01)                             */
/* =========================================================  SWIER  ========================================================= */
#define EXTI_SWIER_SWIER24_Pos (24UL)        /*!< SWIER24 (Bit 24)                                      */
#define EXTI_SWIER_SWIER24_Msk (0x1000000UL) /*!< SWIER24 (Bitfield-Mask: 0x01)                         */
#define EXTI_SWIER_SWIER23_Pos (23UL)        /*!< SWIER23 (Bit 23)                                      */
#define EXTI_SWIER_SWIER23_Msk (0x800000UL)  /*!< SWIER23 (Bitfield-Mask: 0x01)                         */
#define EXTI_SWIER_SWIER22_Pos (22UL)        /*!< SWIER22 (Bit 22)                                      */
#define EXTI_SWIER_SWIER22_Msk (0x400000UL)  /*!< SWIER22 (Bitfield-Mask: 0x01)                         */
#define EXTI_SWIER_SWIER21_Pos (21UL)        /*!< SWIER21 (Bit 21)                                      */
#define EXTI_SWIER_SWIER21_Msk (0x200000UL)  /*!< SWIER21 (Bitfield-Mask: 0x01)                         */
#define EXTI_SWIER_SWIER20_Pos (20UL)        /*!< SWIER20 (Bit 20)                                      */
#define EXTI_SWIER_SWIER20_Msk (0x100000UL)  /*!< SWIER20 (Bitfield-Mask: 0x01)                         */
#define EXTI_SWIER_SWIER19_Pos (19UL)        /*!< SWIER19 (Bit 19)                                      */
#define EXTI_SWIER_SWIER19_Msk (0x80000UL)   /*!< SWIER19 (Bitfield-Mask: 0x01)                         */
#define EXTI_SWIER_SWIER18_Pos (18UL)        /*!< SWIER18 (Bit 18)                                      */
#define EXTI_SWIER_SWIER18_Msk (0x40000UL)   /*!< SWIER18 (Bitfield-Mask: 0x01)                         */
#define EXTI_SWIER_SWIER17_Pos (17UL)        /*!< SWIER17 (Bit 17)                                      */
#define EXTI_SWIER_SWIER17_Msk (0x20000UL)   /*!< SWIER17 (Bitfield-Mask: 0x01)                         */
#define EXTI_SWIER_SWIER16_Pos (16UL)        /*!< SWIER16 (Bit 16)                                      */
#define EXTI_SWIER_SWIER16_Msk (0x10000UL)   /*!< SWIER16 (Bitfield-Mask: 0x01)                         */
#define EXTI_SWIER_SWIER15_Pos (15UL)        /*!< SWIER15 (Bit 15)                                      */
#define EXTI_SWIER_SWIER15_Msk (0x8000UL)    /*!< SWIER15 (Bitfield-Mask: 0x01)                         */
#define EXTI_SWIER_SWIER14_Pos (14UL)        /*!< SWIER14 (Bit 14)                                      */
#define EXTI_SWIER_SWIER14_Msk (0x4000UL)    /*!< SWIER14 (Bitfield-Mask: 0x01)                         */
#define EXTI_SWIER_SWIER13_Pos (13UL)        /*!< SWIER13 (Bit 13)                                      */
#define EXTI_SWIER_SWIER13_Msk (0x2000UL)    /*!< SWIER13 (Bitfield-Mask: 0x01)                         */
#define EXTI_SWIER_SWIER12_Pos (12UL)        /*!< SWIER12 (Bit 12)                                      */
#define EXTI_SWIER_SWIER12_Msk (0x1000UL)    /*!< SWIER12 (Bitfield-Mask: 0x01)                         */
#define EXTI_SWIER_SWIER11_Pos (11UL)        /*!< SWIER11 (Bit 11)                                      */
#define EXTI_SWIER_SWIER11_Msk (0x800UL)     /*!< SWIER11 (Bitfield-Mask: 0x01)                         */
#define EXTI_SWIER_SWIER10_Pos (10UL)        /*!< SWIER10 (Bit 10)                                      */
#define EXTI_SWIER_SWIER10_Msk (0x400UL)     /*!< SWIER10 (Bitfield-Mask: 0x01)                         */
#define EXTI_SWIER_SWIER9_Pos (9UL)          /*!< SWIER9 (Bit 9)                                        */
#define EXTI_SWIER_SWIER9_Msk (0x200UL)      /*!< SWIER9 (Bitfield-Mask: 0x01)                          */
#define EXTI_SWIER_SWIER8_Pos (8UL)          /*!< SWIER8 (Bit 8)                                        */
#define EXTI_SWIER_SWIER8_Msk (0x100UL)      /*!< SWIER8 (Bitfield-Mask: 0x01)                          */
#define EXTI_SWIER_SWIER7_Pos (7UL)          /*!< SWIER7 (Bit 7)                                        */
#define EXTI_SWIER_SWIER7_Msk (0x80UL)       /*!< SWIER7 (Bitfield-Mask: 0x01)                          */
#define EXTI_SWIER_SWIER6_Pos (6UL)          /*!< SWIER6 (Bit 6)                                        */
#define EXTI_SWIER_SWIER6_Msk (0x40UL)       /*!< SWIER6 (Bitfield-Mask: 0x01)                          */
#define EXTI_SWIER_SWIER5_Pos (5UL)          /*!< SWIER5 (Bit 5)                                        */
#define EXTI_SWIER_SWIER5_Msk (0x20UL)       /*!< SWIER5 (Bitfield-Mask: 0x01)                          */
#define EXTI_SWIER_SWIER4_Pos (4UL)          /*!< SWIER4 (Bit 4)                                        */
#define EXTI_SWIER_SWIER4_Msk (0x10UL)       /*!< SWIER4 (Bitfield-Mask: 0x01)                          */
#define EXTI_SWIER_SWIER3_Pos (3UL)          /*!< SWIER3 (Bit 3)                                        */
#define EXTI_SWIER_SWIER3_Msk (0x8UL)        /*!< SWIER3 (Bitfield-Mask: 0x01)                          */
#define EXTI_SWIER_SWIER2_Pos (2UL)          /*!< SWIER2 (Bit 2)                                        */
#define EXTI_SWIER_SWIER2_Msk (0x4UL)        /*!< SWIER2 (Bitfield-Mask: 0x01)                          */
#define EXTI_SWIER_SWIER1_Pos (1UL)          /*!< SWIER1 (Bit 1)                                        */
#define EXTI_SWIER_SWIER1_Msk (0x2UL)        /*!< SWIER1 (Bitfield-Mask: 0x01)                          */
#define EXTI_SWIER_SWIER0_Pos (0UL)          /*!< SWIER0 (Bit 0)                                        */
#define EXTI_SWIER_SWIER0_Msk (0x1UL)        /*!< SWIER0 (Bitfield-Mask: 0x01)                          */
/* ==========================================================  PR  =========================================================== */
#define EXTI_PR_PR24_Pos (24UL)        /*!< PR24 (Bit 24)                                         */
#define EXTI_PR_PR24_Msk (0x1000000UL) /*!< PR24 (Bitfield-Mask: 0x01)                            */
#define EXTI_PR_PR23_Pos (23UL)        /*!< PR23 (Bit 23)                                         */
#define EXTI_PR_PR23_Msk (0x800000UL)  /*!< PR23 (Bitfield-Mask: 0x01)                            */
#define EXTI_PR_PR22_Pos (22UL)        /*!< PR22 (Bit 22)                                         */
#define EXTI_PR_PR22_Msk (0x400000UL)  /*!< PR22 (Bitfield-Mask: 0x01)                            */
#define EXTI_PR_PR21_Pos (21UL)        /*!< PR21 (Bit 21)                                         */
#define EXTI_PR_PR21_Msk (0x200000UL)  /*!< PR21 (Bitfield-Mask: 0x01)                            */
#define EXTI_PR_PR20_Pos (20UL)        /*!< PR20 (Bit 20)                                         */
#define EXTI_PR_PR20_Msk (0x100000UL)  /*!< PR20 (Bitfield-Mask: 0x01)                            */
#define EXTI_PR_PR19_Pos (19UL)        /*!< PR19 (Bit 19)                                         */
#define EXTI_PR_PR19_Msk (0x80000UL)   /*!< PR19 (Bitfield-Mask: 0x01)                            */
#define EXTI_PR_PR18_Pos (18UL)        /*!< PR18 (Bit 18)                                         */
#define EXTI_PR_PR18_Msk (0x40000UL)   /*!< PR18 (Bitfield-Mask: 0x01)                            */
#define EXTI_PR_PR17_Pos (17UL)        /*!< PR17 (Bit 17)                                         */
#define EXTI_PR_PR17_Msk (0x20000UL)   /*!< PR17 (Bitfield-Mask: 0x01)                            */
#define EXTI_PR_PR16_Pos (16UL)        /*!< PR16 (Bit 16)                                         */
#define EXTI_PR_PR16_Msk (0x10000UL)   /*!< PR16 (Bitfield-Mask: 0x01)                            */
#define EXTI_PR_PR15_Pos (15UL)        /*!< PR15 (Bit 15)                                         */
#define EXTI_PR_PR15_Msk (0x8000UL)    /*!< PR15 (Bitfield-Mask: 0x01)                            */
#define EXTI_PR_PR14_Pos (14UL)        /*!< PR14 (Bit 14)                                         */
#define EXTI_PR_PR14_Msk (0x4000UL)    /*!< PR14 (Bitfield-Mask: 0x01)                            */
#define EXTI_PR_PR13_Pos (13UL)        /*!< PR13 (Bit 13)                                         */
#define EXTI_PR_PR13_Msk (0x2000UL)    /*!< PR13 (Bitfield-Mask: 0x01)                            */
#define EXTI_PR_PR12_Pos (12UL)        /*!< PR12 (Bit 12)                                         */
#define EXTI_PR_PR12_Msk (0x1000UL)    /*!< PR12 (Bitfield-Mask: 0x01)                            */
#define EXTI_PR_PR11_Pos (11UL)        /*!< PR11 (Bit 11)                                         */
#define EXTI_PR_PR11_Msk (0x800UL)     /*!< PR11 (Bitfield-Mask: 0x01)                            */
#define EXTI_PR_PR10_Pos (10UL)        /*!< PR10 (Bit 10)                                         */
#define EXTI_PR_PR10_Msk (0x400UL)     /*!< PR10 (Bitfield-Mask: 0x01)                            */
#define EXTI_PR_PR9_Pos (9UL)          /*!< PR9 (Bit 9)                                           */
#define EXTI_PR_PR9_Msk (0x200UL)      /*!< PR9 (Bitfield-Mask: 0x01)                             */
#define EXTI_PR_PR8_Pos (8UL)          /*!< PR8 (Bit 8)                                           */
#define EXTI_PR_PR8_Msk (0x100UL)      /*!< PR8 (Bitfield-Mask: 0x01)                             */
#define EXTI_PR_PR7_Pos (7UL)          /*!< PR7 (Bit 7)                                           */
#define EXTI_PR_PR7_Msk (0x80UL)       /*!< PR7 (Bitfield-Mask: 0x01)                             */
#define EXTI_PR_PR6_Pos (6UL)          /*!< PR6 (Bit 6)                                           */
#define EXTI_PR_PR6_Msk (0x40UL)       /*!< PR6 (Bitfield-Mask: 0x01)                             */
#define EXTI_PR_PR5_Pos (5UL)          /*!< PR5 (Bit 5)                                           */
#define EXTI_PR_PR5_Msk (0x20UL)       /*!< PR5 (Bitfield-Mask: 0x01)                             */
#define EXTI_PR_PR4_Pos (4UL)          /*!< PR4 (Bit 4)                                           */
#define EXTI_PR_PR4_Msk (0x10UL)       /*!< PR4 (Bitfield-Mask: 0x01)                             */
#define EXTI_PR_PR3_Pos (3UL)          /*!< PR3 (Bit 3)                                           */
#define EXTI_PR_PR3_Msk (0x8UL)        /*!< PR3 (Bitfield-Mask: 0x01)                             */
#define EXTI_PR_PR2_Pos (2UL)          /*!< PR2 (Bit 2)                                           */
#define EXTI_PR_PR2_Msk (0x4UL)        /*!< PR2 (Bitfield-Mask: 0x01)                             */
#define EXTI_PR_PR1_Pos (1UL)          /*!< PR1 (Bit 1)                                           */
#define EXTI_PR_PR1_Msk (0x2UL)        /*!< PR1 (Bitfield-Mask: 0x01)                             */
#define EXTI_PR_PR0_Pos (0UL)          /*!< PR0 (Bit 0)                                           */
#define EXTI_PR_PR0_Msk (0x1UL)        /*!< PR0 (Bitfield-Mask: 0x01)                             */
/* ==========================================================  FR  =========================================================== */
#define EXTI_FR_FR15_Pos (30UL)         /*!< FR15 (Bit 30)                                         */
#define EXTI_FR_FR15_Msk (0xc0000000UL) /*!< FR15 (Bitfield-Mask: 0x03)                            */
#define EXTI_FR_FR14_Pos (28UL)         /*!< FR14 (Bit 28)                                         */
#define EXTI_FR_FR14_Msk (0x30000000UL) /*!< FR14 (Bitfield-Mask: 0x03)                            */
#define EXTI_FR_FR13_Pos (26UL)         /*!< FR13 (Bit 26)                                         */
#define EXTI_FR_FR13_Msk (0xc000000UL)  /*!< FR13 (Bitfield-Mask: 0x03)                            */
#define EXTI_FR_FR12_Pos (24UL)         /*!< FR12 (Bit 24)                                         */
#define EXTI_FR_FR12_Msk (0x3000000UL)  /*!< FR12 (Bitfield-Mask: 0x03)                            */
#define EXTI_FR_FR11_Pos (22UL)         /*!< FR11 (Bit 22)                                         */
#define EXTI_FR_FR11_Msk (0xc00000UL)   /*!< FR11 (Bitfield-Mask: 0x03)                            */
#define EXTI_FR_FR10_Pos (20UL)         /*!< FR10 (Bit 20)                                         */
#define EXTI_FR_FR10_Msk (0x300000UL)   /*!< FR10 (Bitfield-Mask: 0x03)                            */
#define EXTI_FR_FR9_Pos (18UL)          /*!< FR9 (Bit 18)                                          */
#define EXTI_FR_FR9_Msk (0xc0000UL)     /*!< FR9 (Bitfield-Mask: 0x03)                             */
#define EXTI_FR_FR8_Pos (16UL)          /*!< FR8 (Bit 16)                                          */
#define EXTI_FR_FR8_Msk (0x30000UL)     /*!< FR8 (Bitfield-Mask: 0x03)                             */
#define EXTI_FR_FR7_Pos (14UL)          /*!< FR7 (Bit 14)                                          */
#define EXTI_FR_FR7_Msk (0xc000UL)      /*!< FR7 (Bitfield-Mask: 0x03)                             */
#define EXTI_FR_FR6_Pos (12UL)          /*!< FR6 (Bit 12)                                          */
#define EXTI_FR_FR6_Msk (0x3000UL)      /*!< FR6 (Bitfield-Mask: 0x03)                             */
#define EXTI_FR_FR5_Pos (10UL)          /*!< FR5 (Bit 10)                                          */
#define EXTI_FR_FR5_Msk (0xc00UL)       /*!< FR5 (Bitfield-Mask: 0x03)                             */
#define EXTI_FR_FR4_Pos (8UL)           /*!< FR4 (Bit 8)                                           */
#define EXTI_FR_FR4_Msk (0x300UL)       /*!< FR4 (Bitfield-Mask: 0x03)                             */
#define EXTI_FR_FR3_Pos (6UL)           /*!< FR3 (Bit 6)                                           */
#define EXTI_FR_FR3_Msk (0xc0UL)        /*!< FR3 (Bitfield-Mask: 0x03)                             */
#define EXTI_FR_FR2_Pos (4UL)           /*!< FR2 (Bit 4)                                           */
#define EXTI_FR_FR2_Msk (0x30UL)        /*!< FR2 (Bitfield-Mask: 0x03)                             */
#define EXTI_FR_FR1_Pos (2UL)           /*!< FR1 (Bit 2)                                           */
#define EXTI_FR_FR1_Msk (0xcUL)         /*!< FR1 (Bitfield-Mask: 0x03)                             */
#define EXTI_FR_FR0_Pos (0UL)           /*!< FR0 (Bit 0)                                           */
#define EXTI_FR_FR0_Msk (0x3UL)         /*!< FR0 (Bitfield-Mask: 0x03)                             */
/* ==========================================================  CR  =========================================================== */
#define EXTI_CR_PSC_Pos (28UL)         /*!< PSC (Bit 28)                                          */
#define EXTI_CR_PSC_Msk (0x70000000UL) /*!< PSC (Bitfield-Mask: 0x07)                             */
#define EXTI_CR_LR24_Pos (24UL)        /*!< LR24 (Bit 24)                                         */
#define EXTI_CR_LR24_Msk (0x1000000UL) /*!< LR24 (Bitfield-Mask: 0x01)                            */
#define EXTI_CR_LR23_Pos (23UL)        /*!< LR23 (Bit 23)                                         */
#define EXTI_CR_LR23_Msk (0x800000UL)  /*!< LR23 (Bitfield-Mask: 0x01)                            */
#define EXTI_CR_LR22_Pos (22UL)        /*!< LR22 (Bit 22)                                         */
#define EXTI_CR_LR22_Msk (0x400000UL)  /*!< LR22 (Bitfield-Mask: 0x01)                            */
#define EXTI_CR_LR21_Pos (21UL)        /*!< LR21 (Bit 21)                                         */
#define EXTI_CR_LR21_Msk (0x200000UL)  /*!< LR21 (Bitfield-Mask: 0x01)                            */
#define EXTI_CR_LR20_Pos (20UL)        /*!< LR20 (Bit 20)                                         */
#define EXTI_CR_LR20_Msk (0x100000UL)  /*!< LR20 (Bitfield-Mask: 0x01)                            */
#define EXTI_CR_LR19_Pos (19UL)        /*!< LR19 (Bit 19)                                         */
#define EXTI_CR_LR19_Msk (0x80000UL)   /*!< LR19 (Bitfield-Mask: 0x01)                            */
#define EXTI_CR_LR18_Pos (18UL)        /*!< LR18 (Bit 18)                                         */
#define EXTI_CR_LR18_Msk (0x40000UL)   /*!< LR18 (Bitfield-Mask: 0x01)                            */
#define EXTI_CR_LR17_Pos (17UL)        /*!< LR17 (Bit 17)                                         */
#define EXTI_CR_LR17_Msk (0x20000UL)   /*!< LR17 (Bitfield-Mask: 0x01)                            */
#define EXTI_CR_LR16_Pos (16UL)        /*!< LR16 (Bit 16)                                         */
#define EXTI_CR_LR16_Msk (0x10000UL)   /*!< LR16 (Bitfield-Mask: 0x01)                            */
#define EXTI_CR_LR15_Pos (15UL)        /*!< LR15 (Bit 15)                                         */
#define EXTI_CR_LR15_Msk (0x8000UL)    /*!< LR15 (Bitfield-Mask: 0x01)                            */
#define EXTI_CR_LR14_Pos (14UL)        /*!< LR14 (Bit 14)                                         */
#define EXTI_CR_LR14_Msk (0x4000UL)    /*!< LR14 (Bitfield-Mask: 0x01)                            */
#define EXTI_CR_LR13_Pos (13UL)        /*!< LR13 (Bit 13)                                         */
#define EXTI_CR_LR13_Msk (0x2000UL)    /*!< LR13 (Bitfield-Mask: 0x01)                            */
#define EXTI_CR_LR12_Pos (12UL)        /*!< LR12 (Bit 12)                                         */
#define EXTI_CR_LR12_Msk (0x1000UL)    /*!< LR12 (Bitfield-Mask: 0x01)                            */
#define EXTI_CR_LR11_Pos (11UL)        /*!< LR11 (Bit 11)                                         */
#define EXTI_CR_LR11_Msk (0x800UL)     /*!< LR11 (Bitfield-Mask: 0x01)                            */
#define EXTI_CR_LR10_Pos (10UL)        /*!< LR10 (Bit 10)                                         */
#define EXTI_CR_LR10_Msk (0x400UL)     /*!< LR10 (Bitfield-Mask: 0x01)                            */
#define EXTI_CR_LR9_Pos (9UL)          /*!< LR9 (Bit 9)                                           */
#define EXTI_CR_LR9_Msk (0x200UL)      /*!< LR9 (Bitfield-Mask: 0x01)                             */
#define EXTI_CR_LR8_Pos (8UL)          /*!< LR8 (Bit 8)                                           */
#define EXTI_CR_LR8_Msk (0x100UL)      /*!< LR8 (Bitfield-Mask: 0x01)                             */
#define EXTI_CR_LR7_Pos (7UL)          /*!< LR7 (Bit 7)                                           */
#define EXTI_CR_LR7_Msk (0x80UL)       /*!< LR7 (Bitfield-Mask: 0x01)                             */
#define EXTI_CR_LR6_Pos (6UL)          /*!< LR6 (Bit 6)                                           */
#define EXTI_CR_LR6_Msk (0x40UL)       /*!< LR6 (Bitfield-Mask: 0x01)                             */
#define EXTI_CR_LR5_Pos (5UL)          /*!< LR5 (Bit 5)                                           */
#define EXTI_CR_LR5_Msk (0x20UL)       /*!< LR5 (Bitfield-Mask: 0x01)                             */
#define EXTI_CR_LR4_Pos (4UL)          /*!< LR4 (Bit 4)                                           */
#define EXTI_CR_LR4_Msk (0x10UL)       /*!< LR4 (Bitfield-Mask: 0x01)                             */
#define EXTI_CR_LR3_Pos (3UL)          /*!< LR3 (Bit 3)                                           */
#define EXTI_CR_LR3_Msk (0x8UL)        /*!< LR3 (Bitfield-Mask: 0x01)                             */
#define EXTI_CR_LR2_Pos (2UL)          /*!< LR2 (Bit 2)                                           */
#define EXTI_CR_LR2_Msk (0x4UL)        /*!< LR2 (Bitfield-Mask: 0x01)                             */
#define EXTI_CR_LR1_Pos (1UL)          /*!< LR1 (Bit 1)                                           */
#define EXTI_CR_LR1_Msk (0x2UL)        /*!< LR1 (Bitfield-Mask: 0x01)                             */
#define EXTI_CR_LR0_Pos (0UL)          /*!< LR0 (Bit 0)                                           */
#define EXTI_CR_LR0_Msk (0x1UL)        /*!< LR0 (Bitfield-Mask: 0x01)                             */
  /** @defgroup EXTI_Exported_Functions
  * @{
  */

  void EXTI_DeInit(void);
  void EXTI_Init(EXTI_InitTypeDef *EXTI_InitStruct);
  void EXTI_StructInit(EXTI_InitTypeDef *EXTI_InitStruct);
  void EXTI_GenerateSWInterrupt(uint32_t EXTI_Line);
  FlagStatus EXTI_GetFlagStatus(uint32_t EXTI_Line);
  void EXTI_ClearFlag(uint32_t EXTI_Line);
  ITStatus EXTI_GetITStatus(uint32_t EXTI_Line);
  void EXTI_ClearITPendingBit(uint32_t EXTI_Line);

  //connect exti interrupt line to GPIOA,GPIOB,GPIOC or GPIOD
  void EXTI_ConnectTo(GPIO_Typedef *GPIO, uint32_t EXTI_Line);

#ifdef __cplusplus
}
#endif

#endif /* __LCM32F037_EXTI_H */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2020 LCMicroelectronics *****END OF FILE****/
