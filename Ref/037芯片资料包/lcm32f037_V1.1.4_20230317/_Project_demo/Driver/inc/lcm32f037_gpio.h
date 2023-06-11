/**
 ******************************************************************************
 * @file    lcm32f037_gpio.h
 * @author  MCD Application Team
 * @version V0.4.44
 * @date    14-04-2021
 * @brief   This file contains all the functions prototypes for the GPIO
 *          firmware library.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT 2020 LCMicroelectronics</center></h2>
 *
 *
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *        http://www.lnchip.com/software_license_agreement_liberty_v2
 *
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef LCM32F037_GPIO_H
#define LCM32F037_GPIO_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "lcm32f037.h"

/** @addtogroup LCM32F037_StdPeriph_Driver
 * @{
 */

/** @addtogroup GPIO
 * @{
 */
/* Exported types ------------------------------------------------------------*/
/* retain @{*/
#define IS_GPIO_ALL_PERIPH(PERIPH) (((PERIPH) == GPIOA) || \
                                    ((PERIPH) == GPIOB) || \
                                    ((PERIPH) == GPIOC) || \
                                    ((PERIPH) == GPIOD) || \
                                    ((PERIPH) == GPIOF))
  /*retain @}*/

  /** @defgroup Configuration_Mode_enumeration
   * @{
   */
  typedef enum
  {
    GPIO_Mode_IN = 0x00,  /*!< GPIO Input Mode              */
    GPIO_Mode_OUT = 0x01, /*!< GPIO Output Mode             */
    GPIO_Mode_AF = 0x02,  /*!< GPIO Alternate function Mode */
    GPIO_Mode_AN = 0x03   /*!< GPIO Analog In/Out Mode      */
  } GPIOMode_TypeDef;

#define IS_GPIO_MODE(MODE) (((MODE) == GPIO_Mode_IN) || ((MODE) == GPIO_Mode_OUT) || \
                            ((MODE) == GPIO_Mode_AF) || ((MODE) == GPIO_Mode_AN))
  /**
   * @}
   */

  /** @defgroup Output_type_enumeration
   * @{
   */
  typedef enum
  {
    GPIO_OType_PP = 0x00,
    GPIO_OType_OD = 0x01
  } GPIOOType_TypeDef;

#define IS_GPIO_OTYPE(OTYPE) (((OTYPE) == GPIO_OType_PP) || ((OTYPE) == GPIO_OType_OD))

  /**
   * @}
   */

  /** @defgroup Output_Maximum_frequency_enumeration
   * @{
   */
  typedef enum
  {
    GPIO_Speed_Level_1 = 0x01, /*!< I/O output speed: Low 2 MHz */
    GPIO_Speed_Level_2 = 0x00  /*!< I/O output speed: Medium 10 MHz */
  } GPIOSpeed_TypeDef;
#define GPIO_Speed_Slow GPIO_Speed_Level_1
#define GPIO_Speed_Fast GPIO_Speed_Level_2
#define IS_GPIO_SPEED(SPEED) (((SPEED) == GPIO_Speed_Level_1) || ((SPEED) == GPIO_Speed_Level_2))
  /**
   * @}
   */

  /** @defgroup Configuration_Pull-Up_Pull-Down_enumeration
   * @{
   */
  typedef enum
  {
    GPIO_PuPd_NOPULL = 0x00,
    GPIO_PuPd_UP = 0x01,
    GPIO_PuPd_DOWN = 0x02,
    GPIO_PuPd_UPDOWN = 0x03
  } GPIOPuPd_TypeDef;

#define IS_GPIO_PUPD(PUPD) (((PUPD) == GPIO_PuPd_NOPULL) || ((PUPD) == GPIO_PuPd_UP) || \
                            ((PUPD) == GPIO_PuPd_DOWN)||(PUPD) == GPIO_PuPd_UPDOWN))
  /**
   * @}
   */

  /** @defgroup Bit_SET_and_Bit_RESET_enumeration
   * @{
   */
  typedef enum
  {
    Bit_RESET = 0,
    Bit_SET
  } BitAction;

#define IS_GPIO_BIT_ACTION(ACTION) (((ACTION) == Bit_RESET) || ((ACTION) == Bit_SET))
  /**
   * @}
   */

  /**
   * @brief  GPIO Init structure definition
   */
  typedef struct
  {
    uint32_t GPIO_Pin; /*!< Specifies the GPIO pins to be configured.
                                       This parameter can be any value of @ref GPIO_pins_define */

    GPIOMode_TypeDef GPIO_Mode; /*!< Specifies the operating mode for the selected pins.
                                       This parameter can be a value of @ref GPIOMode_TypeDef   */

    GPIOSpeed_TypeDef GPIO_Speed; /*!< Specifies the speed for the selected pins.
                                       This parameter can be a value of @ref GPIOSpeed_TypeDef  */

    GPIOOType_TypeDef GPIO_OType; /*!< Specifies the operating output type for the selected pins.
                                       This parameter can be a value of @ref GPIOOType_TypeDef  */

    GPIOPuPd_TypeDef GPIO_PuPd; /*!< Specifies the operating Pull-up/Pull down for the selected pins.
                                       This parameter can be a value of @ref GPIOPuPd_TypeDef   */
  } GPIO_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup GPIO_Exported_Constants
 * @{
 */

/** @defgroup GPIO_pins_define
 * @{
 */
#define GPIO_Pin_0 ((uint32_t)0x0001)   /*!< Pin 0 selected    */
#define GPIO_Pin_1 ((uint32_t)0x0002)   /*!< Pin 1 selected    */
#define GPIO_Pin_2 ((uint32_t)0x0004)   /*!< Pin 2 selected    */
#define GPIO_Pin_3 ((uint32_t)0x0008)   /*!< Pin 3 selected    */
#define GPIO_Pin_4 ((uint32_t)0x0010)   /*!< Pin 4 selected    */
#define GPIO_Pin_5 ((uint32_t)0x0020)   /*!< Pin 5 selected    */
#define GPIO_Pin_6 ((uint32_t)0x0040)   /*!< Pin 6 selected    */
#define GPIO_Pin_7 ((uint32_t)0x0080)   /*!< Pin 7 selected    */
#define GPIO_Pin_8 ((uint32_t)0x0100)   /*!< Pin 8 selected    */
#define GPIO_Pin_9 ((uint32_t)0x0200)   /*!< Pin 9 selected    */
#define GPIO_Pin_10 ((uint32_t)0x0400)  /*!< Pin 10 selected   */
#define GPIO_Pin_11 ((uint32_t)0x0800)  /*!< Pin 11 selected   */
#define GPIO_Pin_12 ((uint32_t)0x1000)  /*!< Pin 12 selected   */
#define GPIO_Pin_13 ((uint32_t)0x2000)  /*!< Pin 13 selected   */
#define GPIO_Pin_14 ((uint32_t)0x4000)  /*!< Pin 14 selected   */
#define GPIO_Pin_15 ((uint32_t)0x8000)  /*!< Pin 15 selected   */
#define GPIO_Pin_All ((uint32_t)0xFFFF) /*!< All pins selected */

#define IS_GPIO_PIN(PIN) ((PIN) != (uint16_t)0x00)

#define IS_GET_GPIO_PIN(PIN) (((PIN) == GPIO_Pin_0) ||  \
                              ((PIN) == GPIO_Pin_1) ||  \
                              ((PIN) == GPIO_Pin_2) ||  \
                              ((PIN) == GPIO_Pin_3) ||  \
                              ((PIN) == GPIO_Pin_4) ||  \
                              ((PIN) == GPIO_Pin_5) ||  \
                              ((PIN) == GPIO_Pin_6) ||  \
                              ((PIN) == GPIO_Pin_7) ||  \
                              ((PIN) == GPIO_Pin_8) ||  \
                              ((PIN) == GPIO_Pin_9) ||  \
                              ((PIN) == GPIO_Pin_10) || \
                              ((PIN) == GPIO_Pin_11) || \
                              ((PIN) == GPIO_Pin_12) || \
                              ((PIN) == GPIO_Pin_13) || \
                              ((PIN) == GPIO_Pin_14) || \
                              ((PIN) == GPIO_Pin_15))

/**
 * @}
 */

/** @defgroup GPIO_Pin_sources
 * @{
 */
#define GPIO_PinSource0 ((uint8_t)0x00)
#define GPIO_PinSource1 ((uint8_t)0x01)
#define GPIO_PinSource2 ((uint8_t)0x02)
#define GPIO_PinSource3 ((uint8_t)0x03)
#define GPIO_PinSource4 ((uint8_t)0x04)
#define GPIO_PinSource5 ((uint8_t)0x05)
#define GPIO_PinSource6 ((uint8_t)0x06)
#define GPIO_PinSource7 ((uint8_t)0x07)
#define GPIO_PinSource8 ((uint8_t)0x08)
#define GPIO_PinSource9 ((uint8_t)0x09)
#define GPIO_PinSource10 ((uint8_t)0x0A)
#define GPIO_PinSource11 ((uint8_t)0x0B)
#define GPIO_PinSource12 ((uint8_t)0x0C)
#define GPIO_PinSource13 ((uint8_t)0x0D)
#define GPIO_PinSource14 ((uint8_t)0x0E)
#define GPIO_PinSource15 ((uint8_t)0x0F)

#define IS_GPIO_PIN_SOURCE(PINSOURCE) (((PINSOURCE) == GPIO_PinSource0) ||  \
                                       ((PINSOURCE) == GPIO_PinSource1) ||  \
                                       ((PINSOURCE) == GPIO_PinSource2) ||  \
                                       ((PINSOURCE) == GPIO_PinSource3) ||  \
                                       ((PINSOURCE) == GPIO_PinSource4) ||  \
                                       ((PINSOURCE) == GPIO_PinSource5) ||  \
                                       ((PINSOURCE) == GPIO_PinSource6) ||  \
                                       ((PINSOURCE) == GPIO_PinSource7) ||  \
                                       ((PINSOURCE) == GPIO_PinSource8) ||  \
                                       ((PINSOURCE) == GPIO_PinSource9) ||  \
                                       ((PINSOURCE) == GPIO_PinSource10) || \
                                       ((PINSOURCE) == GPIO_PinSource11) || \
                                       ((PINSOURCE) == GPIO_PinSource12) || \
                                       ((PINSOURCE) == GPIO_PinSource13) || \
                                       ((PINSOURCE) == GPIO_PinSource14) || \
                                       ((PINSOURCE) == GPIO_PinSource15))
/**
 * @}
 */

/** @defgroup GPIO_Alternate_function_selection_define
 * @{
 */

/**
 * @brief  AF 0 selection
 */
#define GPIO_AF_0 ((uint8_t)0x00) /* WKUP, EVENTOUT, TIM15, TIM17,     \
                                     MCO, SWDAT, SWCLK, TIM14, USART1, \
                                     CEC, IR_OUT,  */
/**
 * @brief  AF 1 selection
 */
#define GPIO_AF_1 ((uint8_t)0x01) /* , CEC, TIM3, USART1, IR_OUT, \
                                     EVENTOUT, , TIM15 */
/**
 * @brief  AF 2 selection
 */
#define GPIO_AF_2 ((uint8_t)0x02) /* TIM2, TIM1, EVENTOUT, TIM16, TIM17 */
/**
 * @brief  AF 3 selection
 */
#define GPIO_AF_3 ((uint8_t)0x03) /* TS, , TIM15, EVENTOUT */

/**
 * @brief  AF 4 selection
 */
#define GPIO_AF_4 ((uint8_t)0x04) /* TIM14,  */
/**
 * @brief  AF 5 selection
 */
#define GPIO_AF_5 ((uint8_t)0x05) /* TIM16, TIM17 */

/**
 * @brief  AF 6 selection
 */
#define GPIO_AF_6 ((uint8_t)0x06) /* EVENTOUT */
/**
 * @brief  AF 7 selection
 */
#define GPIO_AF_7 ((uint8_t)0x07) /* COMP1 OUT and COMP2 OUT */

#define IS_GPIO_AF(AF) (((AF) == GPIO_AF_0) || ((AF) == GPIO_AF_1) || \
                        ((AF) == GPIO_AF_2) || ((AF) == GPIO_AF_3) || \
                        ((AF) == GPIO_AF_4) || ((AF) == GPIO_AF_5) || \
                        ((AF) == GPIO_AF_6) || ((AF) == GPIO_AF_7))

  /**
   * @}
   */

#define GPIO_Drive_Level_strong ((uint32_t)0x000000000) /*big current   强*/
#define GPIO_Drive_Level_weak ((uint32_t)0x000000001)   /*small current 弱 */

#define IS_GPIO_LEVEL(GPIO_Drive) (((GPIO_Drive) == GPIO_Drive_Level_weak) || ((GPIO_Drive) == GPIO_Drive_Level_strong))

/**
 * @}
 */
/* =========================================================================================================================== */
/* ================                                           GPIOF                                           ================ */
/* =========================================================================================================================== */

/* =========================================================  MODER  ========================================================= */
#define GPIOF_MODER_MODER15_Pos (30UL)         /*!< MODER15 (Bit 30)                                      */
#define GPIOF_MODER_MODER15_Msk (0xc0000000UL) /*!< MODER15 (Bitfield-Mask: 0x03)                         */
#define GPIOF_MODER_MODER14_Pos (28UL)         /*!< MODER14 (Bit 28)                                      */
#define GPIOF_MODER_MODER14_Msk (0x30000000UL) /*!< MODER14 (Bitfield-Mask: 0x03)                         */
#define GPIOF_MODER_MODER13_Pos (26UL)         /*!< MODER13 (Bit 26)                                      */
#define GPIOF_MODER_MODER13_Msk (0xc000000UL)  /*!< MODER13 (Bitfield-Mask: 0x03)                         */
#define GPIOF_MODER_MODER12_Pos (24UL)         /*!< MODER12 (Bit 24)                                      */
#define GPIOF_MODER_MODER12_Msk (0x3000000UL)  /*!< MODER12 (Bitfield-Mask: 0x03)                         */
#define GPIOF_MODER_MODER11_Pos (22UL)         /*!< MODER11 (Bit 22)                                      */
#define GPIOF_MODER_MODER11_Msk (0xc00000UL)   /*!< MODER11 (Bitfield-Mask: 0x03)                         */
#define GPIOF_MODER_MODER10_Pos (20UL)         /*!< MODER10 (Bit 20)                                      */
#define GPIOF_MODER_MODER10_Msk (0x300000UL)   /*!< MODER10 (Bitfield-Mask: 0x03)                         */
#define GPIOF_MODER_MODER9_Pos (18UL)          /*!< MODER9 (Bit 18)                                       */
#define GPIOF_MODER_MODER9_Msk (0xc0000UL)     /*!< MODER9 (Bitfield-Mask: 0x03)                          */
#define GPIOF_MODER_MODER8_Pos (16UL)          /*!< MODER8 (Bit 16)                                       */
#define GPIOF_MODER_MODER8_Msk (0x30000UL)     /*!< MODER8 (Bitfield-Mask: 0x03)                          */
#define GPIOF_MODER_MODER7_Pos (14UL)          /*!< MODER7 (Bit 14)                                       */
#define GPIOF_MODER_MODER7_Msk (0xc000UL)      /*!< MODER7 (Bitfield-Mask: 0x03)                          */
#define GPIOF_MODER_MODER6_Pos (12UL)          /*!< MODER6 (Bit 12)                                       */
#define GPIOF_MODER_MODER6_Msk (0x3000UL)      /*!< MODER6 (Bitfield-Mask: 0x03)                          */
#define GPIOF_MODER_MODER5_Pos (10UL)          /*!< MODER5 (Bit 10)                                       */
#define GPIOF_MODER_MODER5_Msk (0xc00UL)       /*!< MODER5 (Bitfield-Mask: 0x03)                          */
#define GPIOF_MODER_MODER4_Pos (8UL)           /*!< MODER4 (Bit 8)                                        */
#define GPIOF_MODER_MODER4_Msk (0x300UL)       /*!< MODER4 (Bitfield-Mask: 0x03)                          */
#define GPIOF_MODER_MODER3_Pos (6UL)           /*!< MODER3 (Bit 6)                                        */
#define GPIOF_MODER_MODER3_Msk (0xc0UL)        /*!< MODER3 (Bitfield-Mask: 0x03)                          */
#define GPIOF_MODER_MODER2_Pos (4UL)           /*!< MODER2 (Bit 4)                                        */
#define GPIOF_MODER_MODER2_Msk (0x30UL)        /*!< MODER2 (Bitfield-Mask: 0x03)                          */
#define GPIOF_MODER_MODER1_Pos (2UL)           /*!< MODER1 (Bit 2)                                        */
#define GPIOF_MODER_MODER1_Msk (0xcUL)         /*!< MODER1 (Bitfield-Mask: 0x03)                          */
#define GPIOF_MODER_MODER0_Pos (0UL)           /*!< MODER0 (Bit 0)                                        */
#define GPIOF_MODER_MODER0_Msk (0x3UL)         /*!< MODER0 (Bitfield-Mask: 0x03)                          */
/* ==========================================================  OD  =========================================================== */
#define GPIOF_OD_OD15_Pos (15UL)     /*!< OD15 (Bit 15)                                         */
#define GPIOF_OD_OD15_Msk (0x8000UL) /*!< OD15 (Bitfield-Mask: 0x01)                            */
#define GPIOF_OD_OD14_Pos (14UL)     /*!< OD14 (Bit 14)                                         */
#define GPIOF_OD_OD14_Msk (0x4000UL) /*!< OD14 (Bitfield-Mask: 0x01)                            */
#define GPIOF_OD_OD13_Pos (13UL)     /*!< OD13 (Bit 13)                                         */
#define GPIOF_OD_OD13_Msk (0x2000UL) /*!< OD13 (Bitfield-Mask: 0x01)                            */
#define GPIOF_OD_OD12_Pos (12UL)     /*!< OD12 (Bit 12)                                         */
#define GPIOF_OD_OD12_Msk (0x1000UL) /*!< OD12 (Bitfield-Mask: 0x01)                            */
#define GPIOF_OD_OD11_Pos (11UL)     /*!< OD11 (Bit 11)                                         */
#define GPIOF_OD_OD11_Msk (0x800UL)  /*!< OD11 (Bitfield-Mask: 0x01)                            */
#define GPIOF_OD_OD10_Pos (10UL)     /*!< OD10 (Bit 10)                                         */
#define GPIOF_OD_OD10_Msk (0x400UL)  /*!< OD10 (Bitfield-Mask: 0x01)                            */
#define GPIOF_OD_OD9_Pos (9UL)       /*!< OD9 (Bit 9)                                           */
#define GPIOF_OD_OD9_Msk (0x200UL)   /*!< OD9 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OD_OD8_Pos (8UL)       /*!< OD8 (Bit 8)                                           */
#define GPIOF_OD_OD8_Msk (0x100UL)   /*!< OD8 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OD_OD7_Pos (7UL)       /*!< OD7 (Bit 7)                                           */
#define GPIOF_OD_OD7_Msk (0x80UL)    /*!< OD7 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OD_OD6_Pos (6UL)       /*!< OD6 (Bit 6)                                           */
#define GPIOF_OD_OD6_Msk (0x40UL)    /*!< OD6 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OD_OD5_Pos (5UL)       /*!< OD5 (Bit 5)                                           */
#define GPIOF_OD_OD5_Msk (0x20UL)    /*!< OD5 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OD_OD4_Pos (4UL)       /*!< OD4 (Bit 4)                                           */
#define GPIOF_OD_OD4_Msk (0x10UL)    /*!< OD4 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OD_OD3_Pos (3UL)       /*!< OD3 (Bit 3)                                           */
#define GPIOF_OD_OD3_Msk (0x8UL)     /*!< OD3 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OD_OD2_Pos (2UL)       /*!< OD2 (Bit 2)                                           */
#define GPIOF_OD_OD2_Msk (0x4UL)     /*!< OD2 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OD_OD1_Pos (1UL)       /*!< OD1 (Bit 1)                                           */
#define GPIOF_OD_OD1_Msk (0x2UL)     /*!< OD1 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OD_OD0_Pos (0UL)       /*!< OD0 (Bit 0)                                           */
#define GPIOF_OD_OD0_Msk (0x1UL)     /*!< OD0 (Bitfield-Mask: 0x01)                             */
/* ========================================================  OD_BSRR  ======================================================== */
#define GPIOF_OD_BSRR_BR15_Pos (31UL)         /*!< BR15 (Bit 31)                                         */
#define GPIOF_OD_BSRR_BR15_Msk (0x80000000UL) /*!< BR15 (Bitfield-Mask: 0x01)                            */
#define GPIOF_OD_BSRR_BR14_Pos (30UL)         /*!< BR14 (Bit 30)                                         */
#define GPIOF_OD_BSRR_BR14_Msk (0x40000000UL) /*!< BR14 (Bitfield-Mask: 0x01)                            */
#define GPIOF_OD_BSRR_BR13_Pos (29UL)         /*!< BR13 (Bit 29)                                         */
#define GPIOF_OD_BSRR_BR13_Msk (0x20000000UL) /*!< BR13 (Bitfield-Mask: 0x01)                            */
#define GPIOF_OD_BSRR_BR12_Pos (28UL)         /*!< BR12 (Bit 28)                                         */
#define GPIOF_OD_BSRR_BR12_Msk (0x10000000UL) /*!< BR12 (Bitfield-Mask: 0x01)                            */
#define GPIOF_OD_BSRR_BR11_Pos (27UL)         /*!< BR11 (Bit 27)                                         */
#define GPIOF_OD_BSRR_BR11_Msk (0x8000000UL)  /*!< BR11 (Bitfield-Mask: 0x01)                            */
#define GPIOF_OD_BSRR_BR10_Pos (26UL)         /*!< BR10 (Bit 26)                                         */
#define GPIOF_OD_BSRR_BR10_Msk (0x4000000UL)  /*!< BR10 (Bitfield-Mask: 0x01)                            */
#define GPIOF_OD_BSRR_BR9_Pos (25UL)          /*!< BR9 (Bit 25)                                          */
#define GPIOF_OD_BSRR_BR9_Msk (0x2000000UL)   /*!< BR9 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OD_BSRR_BR8_Pos (24UL)          /*!< BR8 (Bit 24)                                          */
#define GPIOF_OD_BSRR_BR8_Msk (0x1000000UL)   /*!< BR8 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OD_BSRR_BR7_Pos (23UL)          /*!< BR7 (Bit 23)                                          */
#define GPIOF_OD_BSRR_BR7_Msk (0x800000UL)    /*!< BR7 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OD_BSRR_BR6_Pos (22UL)          /*!< BR6 (Bit 22)                                          */
#define GPIOF_OD_BSRR_BR6_Msk (0x400000UL)    /*!< BR6 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OD_BSRR_BR5_Pos (21UL)          /*!< BR5 (Bit 21)                                          */
#define GPIOF_OD_BSRR_BR5_Msk (0x200000UL)    /*!< BR5 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OD_BSRR_BR4_Pos (20UL)          /*!< BR4 (Bit 20)                                          */
#define GPIOF_OD_BSRR_BR4_Msk (0x100000UL)    /*!< BR4 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OD_BSRR_BR3_Pos (19UL)          /*!< BR3 (Bit 19)                                          */
#define GPIOF_OD_BSRR_BR3_Msk (0x80000UL)     /*!< BR3 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OD_BSRR_BR2_Pos (18UL)          /*!< BR2 (Bit 18)                                          */
#define GPIOF_OD_BSRR_BR2_Msk (0x40000UL)     /*!< BR2 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OD_BSRR_BR1_Pos (17UL)          /*!< BR1 (Bit 17)                                          */
#define GPIOF_OD_BSRR_BR1_Msk (0x20000UL)     /*!< BR1 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OD_BSRR_BR0_Pos (16UL)          /*!< BR0 (Bit 16)                                          */
#define GPIOF_OD_BSRR_BR0_Msk (0x10000UL)     /*!< BR0 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OD_BSRR_BS15_Pos (15UL)         /*!< BS15 (Bit 15)                                         */
#define GPIOF_OD_BSRR_BS15_Msk (0x8000UL)     /*!< BS15 (Bitfield-Mask: 0x01)                            */
#define GPIOF_OD_BSRR_BS14_Pos (14UL)         /*!< BS14 (Bit 14)                                         */
#define GPIOF_OD_BSRR_BS14_Msk (0x4000UL)     /*!< BS14 (Bitfield-Mask: 0x01)                            */
#define GPIOF_OD_BSRR_BS13_Pos (13UL)         /*!< BS13 (Bit 13)                                         */
#define GPIOF_OD_BSRR_BS13_Msk (0x2000UL)     /*!< BS13 (Bitfield-Mask: 0x01)                            */
#define GPIOF_OD_BSRR_BS12_Pos (12UL)         /*!< BS12 (Bit 12)                                         */
#define GPIOF_OD_BSRR_BS12_Msk (0x1000UL)     /*!< BS12 (Bitfield-Mask: 0x01)                            */
#define GPIOF_OD_BSRR_BS11_Pos (11UL)         /*!< BS11 (Bit 11)                                         */
#define GPIOF_OD_BSRR_BS11_Msk (0x800UL)      /*!< BS11 (Bitfield-Mask: 0x01)                            */
#define GPIOF_OD_BSRR_BS10_Pos (10UL)         /*!< BS10 (Bit 10)                                         */
#define GPIOF_OD_BSRR_BS10_Msk (0x400UL)      /*!< BS10 (Bitfield-Mask: 0x01)                            */
#define GPIOF_OD_BSRR_BS9_Pos (9UL)           /*!< BS9 (Bit 9)                                           */
#define GPIOF_OD_BSRR_BS9_Msk (0x200UL)       /*!< BS9 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OD_BSRR_BS8_Pos (8UL)           /*!< BS8 (Bit 8)                                           */
#define GPIOF_OD_BSRR_BS8_Msk (0x100UL)       /*!< BS8 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OD_BSRR_BS7_Pos (7UL)           /*!< BS7 (Bit 7)                                           */
#define GPIOF_OD_BSRR_BS7_Msk (0x80UL)        /*!< BS7 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OD_BSRR_BS6_Pos (6UL)           /*!< BS6 (Bit 6)                                           */
#define GPIOF_OD_BSRR_BS6_Msk (0x40UL)        /*!< BS6 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OD_BSRR_BS5_Pos (5UL)           /*!< BS5 (Bit 5)                                           */
#define GPIOF_OD_BSRR_BS5_Msk (0x20UL)        /*!< BS5 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OD_BSRR_BS4_Pos (4UL)           /*!< BS4 (Bit 4)                                           */
#define GPIOF_OD_BSRR_BS4_Msk (0x10UL)        /*!< BS4 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OD_BSRR_BS3_Pos (3UL)           /*!< BS3 (Bit 3)                                           */
#define GPIOF_OD_BSRR_BS3_Msk (0x8UL)         /*!< BS3 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OD_BSRR_BS2_Pos (2UL)           /*!< BS2 (Bit 2)                                           */
#define GPIOF_OD_BSRR_BS2_Msk (0x4UL)         /*!< BS2 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OD_BSRR_BS1_Pos (1UL)           /*!< BS1 (Bit 1)                                           */
#define GPIOF_OD_BSRR_BS1_Msk (0x2UL)         /*!< BS1 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OD_BSRR_BS0_Pos (0UL)           /*!< BS0 (Bit 0)                                           */
#define GPIOF_OD_BSRR_BS0_Msk (0x1UL)         /*!< BS0 (Bitfield-Mask: 0x01)                             */
/* ==========================================================  SR  =========================================================== */
#define GPIOF_SR_SR15_Pos (15UL)     /*!< SR15 (Bit 15)                                         */
#define GPIOF_SR_SR15_Msk (0x8000UL) /*!< SR15 (Bitfield-Mask: 0x01)                            */
#define GPIOF_SR_SR14_Pos (14UL)     /*!< SR14 (Bit 14)                                         */
#define GPIOF_SR_SR14_Msk (0x4000UL) /*!< SR14 (Bitfield-Mask: 0x01)                            */
#define GPIOF_SR_SR13_Pos (13UL)     /*!< SR13 (Bit 13)                                         */
#define GPIOF_SR_SR13_Msk (0x2000UL) /*!< SR13 (Bitfield-Mask: 0x01)                            */
#define GPIOF_SR_SR12_Pos (12UL)     /*!< SR12 (Bit 12)                                         */
#define GPIOF_SR_SR12_Msk (0x1000UL) /*!< SR12 (Bitfield-Mask: 0x01)                            */
#define GPIOF_SR_SR11_Pos (11UL)     /*!< SR11 (Bit 11)                                         */
#define GPIOF_SR_SR11_Msk (0x800UL)  /*!< SR11 (Bitfield-Mask: 0x01)                            */
#define GPIOF_SR_SR10_Pos (10UL)     /*!< SR10 (Bit 10)                                         */
#define GPIOF_SR_SR10_Msk (0x400UL)  /*!< SR10 (Bitfield-Mask: 0x01)                            */
#define GPIOF_SR_SR9_Pos (9UL)       /*!< SR9 (Bit 9)                                           */
#define GPIOF_SR_SR9_Msk (0x200UL)   /*!< SR9 (Bitfield-Mask: 0x01)                             */
#define GPIOF_SR_SR8_Pos (8UL)       /*!< SR8 (Bit 8)                                           */
#define GPIOF_SR_SR8_Msk (0x100UL)   /*!< SR8 (Bitfield-Mask: 0x01)                             */
#define GPIOF_SR_SR7_Pos (7UL)       /*!< SR7 (Bit 7)                                           */
#define GPIOF_SR_SR7_Msk (0x80UL)    /*!< SR7 (Bitfield-Mask: 0x01)                             */
#define GPIOF_SR_SR6_Pos (6UL)       /*!< SR6 (Bit 6)                                           */
#define GPIOF_SR_SR6_Msk (0x40UL)    /*!< SR6 (Bitfield-Mask: 0x01)                             */
#define GPIOF_SR_SR5_Pos (5UL)       /*!< SR5 (Bit 5)                                           */
#define GPIOF_SR_SR5_Msk (0x20UL)    /*!< SR5 (Bitfield-Mask: 0x01)                             */
#define GPIOF_SR_SR4_Pos (4UL)       /*!< SR4 (Bit 4)                                           */
#define GPIOF_SR_SR4_Msk (0x10UL)    /*!< SR4 (Bitfield-Mask: 0x01)                             */
#define GPIOF_SR_SR3_Pos (3UL)       /*!< SR3 (Bit 3)                                           */
#define GPIOF_SR_SR3_Msk (0x8UL)     /*!< SR3 (Bitfield-Mask: 0x01)                             */
#define GPIOF_SR_SR2_Pos (2UL)       /*!< SR2 (Bit 2)                                           */
#define GPIOF_SR_SR2_Msk (0x4UL)     /*!< SR2 (Bitfield-Mask: 0x01)                             */
#define GPIOF_SR_SR1_Pos (1UL)       /*!< SR1 (Bit 1)                                           */
#define GPIOF_SR_SR1_Msk (0x2UL)     /*!< SR1 (Bitfield-Mask: 0x01)                             */
#define GPIOF_SR_SR0_Pos (0UL)       /*!< SR0 (Bit 0)                                           */
#define GPIOF_SR_SR0_Msk (0x1UL)     /*!< SR0 (Bitfield-Mask: 0x01)                             */
/* ========================================================  SR_BSRR  ======================================================== */
#define GPIOF_SR_BSRR_BR15_Pos (31UL)         /*!< BR15 (Bit 31)                                         */
#define GPIOF_SR_BSRR_BR15_Msk (0x80000000UL) /*!< BR15 (Bitfield-Mask: 0x01)                            */
#define GPIOF_SR_BSRR_BR14_Pos (30UL)         /*!< BR14 (Bit 30)                                         */
#define GPIOF_SR_BSRR_BR14_Msk (0x40000000UL) /*!< BR14 (Bitfield-Mask: 0x01)                            */
#define GPIOF_SR_BSRR_BR13_Pos (29UL)         /*!< BR13 (Bit 29)                                         */
#define GPIOF_SR_BSRR_BR13_Msk (0x20000000UL) /*!< BR13 (Bitfield-Mask: 0x01)                            */
#define GPIOF_SR_BSRR_BR12_Pos (28UL)         /*!< BR12 (Bit 28)                                         */
#define GPIOF_SR_BSRR_BR12_Msk (0x10000000UL) /*!< BR12 (Bitfield-Mask: 0x01)                            */
#define GPIOF_SR_BSRR_BR11_Pos (27UL)         /*!< BR11 (Bit 27)                                         */
#define GPIOF_SR_BSRR_BR11_Msk (0x8000000UL)  /*!< BR11 (Bitfield-Mask: 0x01)                            */
#define GPIOF_SR_BSRR_BR10_Pos (26UL)         /*!< BR10 (Bit 26)                                         */
#define GPIOF_SR_BSRR_BR10_Msk (0x4000000UL)  /*!< BR10 (Bitfield-Mask: 0x01)                            */
#define GPIOF_SR_BSRR_BR9_Pos (25UL)          /*!< BR9 (Bit 25)                                          */
#define GPIOF_SR_BSRR_BR9_Msk (0x2000000UL)   /*!< BR9 (Bitfield-Mask: 0x01)                             */
#define GPIOF_SR_BSRR_BR8_Pos (24UL)          /*!< BR8 (Bit 24)                                          */
#define GPIOF_SR_BSRR_BR8_Msk (0x1000000UL)   /*!< BR8 (Bitfield-Mask: 0x01)                             */
#define GPIOF_SR_BSRR_BR7_Pos (23UL)          /*!< BR7 (Bit 23)                                          */
#define GPIOF_SR_BSRR_BR7_Msk (0x800000UL)    /*!< BR7 (Bitfield-Mask: 0x01)                             */
#define GPIOF_SR_BSRR_BR6_Pos (22UL)          /*!< BR6 (Bit 22)                                          */
#define GPIOF_SR_BSRR_BR6_Msk (0x400000UL)    /*!< BR6 (Bitfield-Mask: 0x01)                             */
#define GPIOF_SR_BSRR_BR5_Pos (21UL)          /*!< BR5 (Bit 21)                                          */
#define GPIOF_SR_BSRR_BR5_Msk (0x200000UL)    /*!< BR5 (Bitfield-Mask: 0x01)                             */
#define GPIOF_SR_BSRR_BR4_Pos (20UL)          /*!< BR4 (Bit 20)                                          */
#define GPIOF_SR_BSRR_BR4_Msk (0x100000UL)    /*!< BR4 (Bitfield-Mask: 0x01)                             */
#define GPIOF_SR_BSRR_BR3_Pos (19UL)          /*!< BR3 (Bit 19)                                          */
#define GPIOF_SR_BSRR_BR3_Msk (0x80000UL)     /*!< BR3 (Bitfield-Mask: 0x01)                             */
#define GPIOF_SR_BSRR_BR2_Pos (18UL)          /*!< BR2 (Bit 18)                                          */
#define GPIOF_SR_BSRR_BR2_Msk (0x40000UL)     /*!< BR2 (Bitfield-Mask: 0x01)                             */
#define GPIOF_SR_BSRR_BR1_Pos (17UL)          /*!< BR1 (Bit 17)                                          */
#define GPIOF_SR_BSRR_BR1_Msk (0x20000UL)     /*!< BR1 (Bitfield-Mask: 0x01)                             */
#define GPIOF_SR_BSRR_BR0_Pos (16UL)          /*!< BR0 (Bit 16)                                          */
#define GPIOF_SR_BSRR_BR0_Msk (0x10000UL)     /*!< BR0 (Bitfield-Mask: 0x01)                             */
#define GPIOF_SR_BSRR_BS15_Pos (15UL)         /*!< BS15 (Bit 15)                                         */
#define GPIOF_SR_BSRR_BS15_Msk (0x8000UL)     /*!< BS15 (Bitfield-Mask: 0x01)                            */
#define GPIOF_SR_BSRR_BS14_Pos (14UL)         /*!< BS14 (Bit 14)                                         */
#define GPIOF_SR_BSRR_BS14_Msk (0x4000UL)     /*!< BS14 (Bitfield-Mask: 0x01)                            */
#define GPIOF_SR_BSRR_BS13_Pos (13UL)         /*!< BS13 (Bit 13)                                         */
#define GPIOF_SR_BSRR_BS13_Msk (0x2000UL)     /*!< BS13 (Bitfield-Mask: 0x01)                            */
#define GPIOF_SR_BSRR_BS12_Pos (12UL)         /*!< BS12 (Bit 12)                                         */
#define GPIOF_SR_BSRR_BS12_Msk (0x1000UL)     /*!< BS12 (Bitfield-Mask: 0x01)                            */
#define GPIOF_SR_BSRR_BS11_Pos (11UL)         /*!< BS11 (Bit 11)                                         */
#define GPIOF_SR_BSRR_BS11_Msk (0x800UL)      /*!< BS11 (Bitfield-Mask: 0x01)                            */
#define GPIOF_SR_BSRR_BS10_Pos (10UL)         /*!< BS10 (Bit 10)                                         */
#define GPIOF_SR_BSRR_BS10_Msk (0x400UL)      /*!< BS10 (Bitfield-Mask: 0x01)                            */
#define GPIOF_SR_BSRR_BS9_Pos (9UL)           /*!< BS9 (Bit 9)                                           */
#define GPIOF_SR_BSRR_BS9_Msk (0x200UL)       /*!< BS9 (Bitfield-Mask: 0x01)                             */
#define GPIOF_SR_BSRR_BS8_Pos (8UL)           /*!< BS8 (Bit 8)                                           */
#define GPIOF_SR_BSRR_BS8_Msk (0x100UL)       /*!< BS8 (Bitfield-Mask: 0x01)                             */
#define GPIOF_SR_BSRR_BS7_Pos (7UL)           /*!< BS7 (Bit 7)                                           */
#define GPIOF_SR_BSRR_BS7_Msk (0x80UL)        /*!< BS7 (Bitfield-Mask: 0x01)                             */
#define GPIOF_SR_BSRR_BS6_Pos (6UL)           /*!< BS6 (Bit 6)                                           */
#define GPIOF_SR_BSRR_BS6_Msk (0x40UL)        /*!< BS6 (Bitfield-Mask: 0x01)                             */
#define GPIOF_SR_BSRR_BS5_Pos (5UL)           /*!< BS5 (Bit 5)                                           */
#define GPIOF_SR_BSRR_BS5_Msk (0x20UL)        /*!< BS5 (Bitfield-Mask: 0x01)                             */
#define GPIOF_SR_BSRR_BS4_Pos (4UL)           /*!< BS4 (Bit 4)                                           */
#define GPIOF_SR_BSRR_BS4_Msk (0x10UL)        /*!< BS4 (Bitfield-Mask: 0x01)                             */
#define GPIOF_SR_BSRR_BS3_Pos (3UL)           /*!< BS3 (Bit 3)                                           */
#define GPIOF_SR_BSRR_BS3_Msk (0x8UL)         /*!< BS3 (Bitfield-Mask: 0x01)                             */
#define GPIOF_SR_BSRR_BS2_Pos (2UL)           /*!< BS2 (Bit 2)                                           */
#define GPIOF_SR_BSRR_BS2_Msk (0x4UL)         /*!< BS2 (Bitfield-Mask: 0x01)                             */
#define GPIOF_SR_BSRR_BS1_Pos (1UL)           /*!< BS1 (Bit 1)                                           */
#define GPIOF_SR_BSRR_BS1_Msk (0x2UL)         /*!< BS1 (Bitfield-Mask: 0x01)                             */
#define GPIOF_SR_BSRR_BS0_Pos (0UL)           /*!< BS0 (Bit 0)                                           */
#define GPIOF_SR_BSRR_BS0_Msk (0x1UL)         /*!< BS0 (Bitfield-Mask: 0x01)                             */
/* ==========================================================  PU  =========================================================== */
#define GPIOF_PU_PU15_Pos (15UL)     /*!< PU15 (Bit 15)                                         */
#define GPIOF_PU_PU15_Msk (0x8000UL) /*!< PU15 (Bitfield-Mask: 0x01)                            */
#define GPIOF_PU_PU14_Pos (14UL)     /*!< PU14 (Bit 14)                                         */
#define GPIOF_PU_PU14_Msk (0x4000UL) /*!< PU14 (Bitfield-Mask: 0x01)                            */
#define GPIOF_PU_PU13_Pos (13UL)     /*!< PU13 (Bit 13)                                         */
#define GPIOF_PU_PU13_Msk (0x2000UL) /*!< PU13 (Bitfield-Mask: 0x01)                            */
#define GPIOF_PU_PU12_Pos (12UL)     /*!< PU12 (Bit 12)                                         */
#define GPIOF_PU_PU12_Msk (0x1000UL) /*!< PU12 (Bitfield-Mask: 0x01)                            */
#define GPIOF_PU_PU11_Pos (11UL)     /*!< PU11 (Bit 11)                                         */
#define GPIOF_PU_PU11_Msk (0x800UL)  /*!< PU11 (Bitfield-Mask: 0x01)                            */
#define GPIOF_PU_PU10_Pos (10UL)     /*!< PU10 (Bit 10)                                         */
#define GPIOF_PU_PU10_Msk (0x400UL)  /*!< PU10 (Bitfield-Mask: 0x01)                            */
#define GPIOF_PU_PU9_Pos (9UL)       /*!< PU9 (Bit 9)                                           */
#define GPIOF_PU_PU9_Msk (0x200UL)   /*!< PU9 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PU_PU8_Pos (8UL)       /*!< PU8 (Bit 8)                                           */
#define GPIOF_PU_PU8_Msk (0x100UL)   /*!< PU8 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PU_PU7_Pos (7UL)       /*!< PU7 (Bit 7)                                           */
#define GPIOF_PU_PU7_Msk (0x80UL)    /*!< PU7 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PU_PU6_Pos (6UL)       /*!< PU6 (Bit 6)                                           */
#define GPIOF_PU_PU6_Msk (0x40UL)    /*!< PU6 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PU_PU5_Pos (5UL)       /*!< PU5 (Bit 5)                                           */
#define GPIOF_PU_PU5_Msk (0x20UL)    /*!< PU5 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PU_PU4_Pos (4UL)       /*!< PU4 (Bit 4)                                           */
#define GPIOF_PU_PU4_Msk (0x10UL)    /*!< PU4 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PU_PU3_Pos (3UL)       /*!< PU3 (Bit 3)                                           */
#define GPIOF_PU_PU3_Msk (0x8UL)     /*!< PU3 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PU_PU2_Pos (2UL)       /*!< PU2 (Bit 2)                                           */
#define GPIOF_PU_PU2_Msk (0x4UL)     /*!< PU2 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PU_PU1_Pos (1UL)       /*!< PU1 (Bit 1)                                           */
#define GPIOF_PU_PU1_Msk (0x2UL)     /*!< PU1 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PU_PU0_Pos (0UL)       /*!< PU0 (Bit 0)                                           */
#define GPIOF_PU_PU0_Msk (0x1UL)     /*!< PU0 (Bitfield-Mask: 0x01)                             */
/* ========================================================  PU_BSRR  ======================================================== */
#define GPIOF_PU_BSRR_BR15_Pos (31UL)         /*!< BR15 (Bit 31)                                         */
#define GPIOF_PU_BSRR_BR15_Msk (0x80000000UL) /*!< BR15 (Bitfield-Mask: 0x01)                            */
#define GPIOF_PU_BSRR_BR14_Pos (30UL)         /*!< BR14 (Bit 30)                                         */
#define GPIOF_PU_BSRR_BR14_Msk (0x40000000UL) /*!< BR14 (Bitfield-Mask: 0x01)                            */
#define GPIOF_PU_BSRR_BR13_Pos (29UL)         /*!< BR13 (Bit 29)                                         */
#define GPIOF_PU_BSRR_BR13_Msk (0x20000000UL) /*!< BR13 (Bitfield-Mask: 0x01)                            */
#define GPIOF_PU_BSRR_BR12_Pos (28UL)         /*!< BR12 (Bit 28)                                         */
#define GPIOF_PU_BSRR_BR12_Msk (0x10000000UL) /*!< BR12 (Bitfield-Mask: 0x01)                            */
#define GPIOF_PU_BSRR_BR11_Pos (27UL)         /*!< BR11 (Bit 27)                                         */
#define GPIOF_PU_BSRR_BR11_Msk (0x8000000UL)  /*!< BR11 (Bitfield-Mask: 0x01)                            */
#define GPIOF_PU_BSRR_BR10_Pos (26UL)         /*!< BR10 (Bit 26)                                         */
#define GPIOF_PU_BSRR_BR10_Msk (0x4000000UL)  /*!< BR10 (Bitfield-Mask: 0x01)                            */
#define GPIOF_PU_BSRR_BR9_Pos (25UL)          /*!< BR9 (Bit 25)                                          */
#define GPIOF_PU_BSRR_BR9_Msk (0x2000000UL)   /*!< BR9 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PU_BSRR_BR8_Pos (24UL)          /*!< BR8 (Bit 24)                                          */
#define GPIOF_PU_BSRR_BR8_Msk (0x1000000UL)   /*!< BR8 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PU_BSRR_BR7_Pos (23UL)          /*!< BR7 (Bit 23)                                          */
#define GPIOF_PU_BSRR_BR7_Msk (0x800000UL)    /*!< BR7 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PU_BSRR_BR6_Pos (22UL)          /*!< BR6 (Bit 22)                                          */
#define GPIOF_PU_BSRR_BR6_Msk (0x400000UL)    /*!< BR6 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PU_BSRR_BR5_Pos (21UL)          /*!< BR5 (Bit 21)                                          */
#define GPIOF_PU_BSRR_BR5_Msk (0x200000UL)    /*!< BR5 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PU_BSRR_BR4_Pos (20UL)          /*!< BR4 (Bit 20)                                          */
#define GPIOF_PU_BSRR_BR4_Msk (0x100000UL)    /*!< BR4 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PU_BSRR_BR3_Pos (19UL)          /*!< BR3 (Bit 19)                                          */
#define GPIOF_PU_BSRR_BR3_Msk (0x80000UL)     /*!< BR3 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PU_BSRR_BR2_Pos (18UL)          /*!< BR2 (Bit 18)                                          */
#define GPIOF_PU_BSRR_BR2_Msk (0x40000UL)     /*!< BR2 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PU_BSRR_BR1_Pos (17UL)          /*!< BR1 (Bit 17)                                          */
#define GPIOF_PU_BSRR_BR1_Msk (0x20000UL)     /*!< BR1 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PU_BSRR_BR0_Pos (16UL)          /*!< BR0 (Bit 16)                                          */
#define GPIOF_PU_BSRR_BR0_Msk (0x10000UL)     /*!< BR0 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PU_BSRR_BS15_Pos (15UL)         /*!< BS15 (Bit 15)                                         */
#define GPIOF_PU_BSRR_BS15_Msk (0x8000UL)     /*!< BS15 (Bitfield-Mask: 0x01)                            */
#define GPIOF_PU_BSRR_BS14_Pos (14UL)         /*!< BS14 (Bit 14)                                         */
#define GPIOF_PU_BSRR_BS14_Msk (0x4000UL)     /*!< BS14 (Bitfield-Mask: 0x01)                            */
#define GPIOF_PU_BSRR_BS13_Pos (13UL)         /*!< BS13 (Bit 13)                                         */
#define GPIOF_PU_BSRR_BS13_Msk (0x2000UL)     /*!< BS13 (Bitfield-Mask: 0x01)                            */
#define GPIOF_PU_BSRR_BS12_Pos (12UL)         /*!< BS12 (Bit 12)                                         */
#define GPIOF_PU_BSRR_BS12_Msk (0x1000UL)     /*!< BS12 (Bitfield-Mask: 0x01)                            */
#define GPIOF_PU_BSRR_BS11_Pos (11UL)         /*!< BS11 (Bit 11)                                         */
#define GPIOF_PU_BSRR_BS11_Msk (0x800UL)      /*!< BS11 (Bitfield-Mask: 0x01)                            */
#define GPIOF_PU_BSRR_BS10_Pos (10UL)         /*!< BS10 (Bit 10)                                         */
#define GPIOF_PU_BSRR_BS10_Msk (0x400UL)      /*!< BS10 (Bitfield-Mask: 0x01)                            */
#define GPIOF_PU_BSRR_BS9_Pos (9UL)           /*!< BS9 (Bit 9)                                           */
#define GPIOF_PU_BSRR_BS9_Msk (0x200UL)       /*!< BS9 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PU_BSRR_BS8_Pos (8UL)           /*!< BS8 (Bit 8)                                           */
#define GPIOF_PU_BSRR_BS8_Msk (0x100UL)       /*!< BS8 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PU_BSRR_BS7_Pos (7UL)           /*!< BS7 (Bit 7)                                           */
#define GPIOF_PU_BSRR_BS7_Msk (0x80UL)        /*!< BS7 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PU_BSRR_BS6_Pos (6UL)           /*!< BS6 (Bit 6)                                           */
#define GPIOF_PU_BSRR_BS6_Msk (0x40UL)        /*!< BS6 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PU_BSRR_BS5_Pos (5UL)           /*!< BS5 (Bit 5)                                           */
#define GPIOF_PU_BSRR_BS5_Msk (0x20UL)        /*!< BS5 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PU_BSRR_BS4_Pos (4UL)           /*!< BS4 (Bit 4)                                           */
#define GPIOF_PU_BSRR_BS4_Msk (0x10UL)        /*!< BS4 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PU_BSRR_BS3_Pos (3UL)           /*!< BS3 (Bit 3)                                           */
#define GPIOF_PU_BSRR_BS3_Msk (0x8UL)         /*!< BS3 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PU_BSRR_BS2_Pos (2UL)           /*!< BS2 (Bit 2)                                           */
#define GPIOF_PU_BSRR_BS2_Msk (0x4UL)         /*!< BS2 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PU_BSRR_BS1_Pos (1UL)           /*!< BS1 (Bit 1)                                           */
#define GPIOF_PU_BSRR_BS1_Msk (0x2UL)         /*!< BS1 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PU_BSRR_BS0_Pos (0UL)           /*!< BS0 (Bit 0)                                           */
#define GPIOF_PU_BSRR_BS0_Msk (0x1UL)         /*!< BS0 (Bitfield-Mask: 0x01)                             */
/* ==========================================================  PD  =========================================================== */
#define GPIOF_PD_PD15_Pos (15UL)     /*!< PD15 (Bit 15)                                         */
#define GPIOF_PD_PD15_Msk (0x8000UL) /*!< PD15 (Bitfield-Mask: 0x01)                            */
#define GPIOF_PD_PD14_Pos (14UL)     /*!< PD14 (Bit 14)                                         */
#define GPIOF_PD_PD14_Msk (0x4000UL) /*!< PD14 (Bitfield-Mask: 0x01)                            */
#define GPIOF_PD_PD13_Pos (13UL)     /*!< PD13 (Bit 13)                                         */
#define GPIOF_PD_PD13_Msk (0x2000UL) /*!< PD13 (Bitfield-Mask: 0x01)                            */
#define GPIOF_PD_PD12_Pos (12UL)     /*!< PD12 (Bit 12)                                         */
#define GPIOF_PD_PD12_Msk (0x1000UL) /*!< PD12 (Bitfield-Mask: 0x01)                            */
#define GPIOF_PD_PD11_Pos (11UL)     /*!< PD11 (Bit 11)                                         */
#define GPIOF_PD_PD11_Msk (0x800UL)  /*!< PD11 (Bitfield-Mask: 0x01)                            */
#define GPIOF_PD_PD10_Pos (10UL)     /*!< PD10 (Bit 10)                                         */
#define GPIOF_PD_PD10_Msk (0x400UL)  /*!< PD10 (Bitfield-Mask: 0x01)                            */
#define GPIOF_PD_PD9_Pos (9UL)       /*!< PD9 (Bit 9)                                           */
#define GPIOF_PD_PD9_Msk (0x200UL)   /*!< PD9 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PD_PD8_Pos (8UL)       /*!< PD8 (Bit 8)                                           */
#define GPIOF_PD_PD8_Msk (0x100UL)   /*!< PD8 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PD_PD7_Pos (7UL)       /*!< PD7 (Bit 7)                                           */
#define GPIOF_PD_PD7_Msk (0x80UL)    /*!< PD7 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PD_PD6_Pos (6UL)       /*!< PD6 (Bit 6)                                           */
#define GPIOF_PD_PD6_Msk (0x40UL)    /*!< PD6 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PD_PD5_Pos (5UL)       /*!< PD5 (Bit 5)                                           */
#define GPIOF_PD_PD5_Msk (0x20UL)    /*!< PD5 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PD_PD4_Pos (4UL)       /*!< PD4 (Bit 4)                                           */
#define GPIOF_PD_PD4_Msk (0x10UL)    /*!< PD4 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PD_PD3_Pos (3UL)       /*!< PD3 (Bit 3)                                           */
#define GPIOF_PD_PD3_Msk (0x8UL)     /*!< PD3 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PD_PD2_Pos (2UL)       /*!< PD2 (Bit 2)                                           */
#define GPIOF_PD_PD2_Msk (0x4UL)     /*!< PD2 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PD_PD1_Pos (1UL)       /*!< PD1 (Bit 1)                                           */
#define GPIOF_PD_PD1_Msk (0x2UL)     /*!< PD1 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PD_PD0_Pos (0UL)       /*!< PD0 (Bit 0)                                           */
#define GPIOF_PD_PD0_Msk (0x1UL)     /*!< PD0 (Bitfield-Mask: 0x01)                             */
/* ========================================================  PD_BSRR  ======================================================== */
#define GPIOF_PD_BSRR_BR15_Pos (31UL)         /*!< BR15 (Bit 31)                                         */
#define GPIOF_PD_BSRR_BR15_Msk (0x80000000UL) /*!< BR15 (Bitfield-Mask: 0x01)                            */
#define GPIOF_PD_BSRR_BR14_Pos (30UL)         /*!< BR14 (Bit 30)                                         */
#define GPIOF_PD_BSRR_BR14_Msk (0x40000000UL) /*!< BR14 (Bitfield-Mask: 0x01)                            */
#define GPIOF_PD_BSRR_BR13_Pos (29UL)         /*!< BR13 (Bit 29)                                         */
#define GPIOF_PD_BSRR_BR13_Msk (0x20000000UL) /*!< BR13 (Bitfield-Mask: 0x01)                            */
#define GPIOF_PD_BSRR_BR12_Pos (28UL)         /*!< BR12 (Bit 28)                                         */
#define GPIOF_PD_BSRR_BR12_Msk (0x10000000UL) /*!< BR12 (Bitfield-Mask: 0x01)                            */
#define GPIOF_PD_BSRR_BR11_Pos (27UL)         /*!< BR11 (Bit 27)                                         */
#define GPIOF_PD_BSRR_BR11_Msk (0x8000000UL)  /*!< BR11 (Bitfield-Mask: 0x01)                            */
#define GPIOF_PD_BSRR_BR10_Pos (26UL)         /*!< BR10 (Bit 26)                                         */
#define GPIOF_PD_BSRR_BR10_Msk (0x4000000UL)  /*!< BR10 (Bitfield-Mask: 0x01)                            */
#define GPIOF_PD_BSRR_BR9_Pos (25UL)          /*!< BR9 (Bit 25)                                          */
#define GPIOF_PD_BSRR_BR9_Msk (0x2000000UL)   /*!< BR9 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PD_BSRR_BR8_Pos (24UL)          /*!< BR8 (Bit 24)                                          */
#define GPIOF_PD_BSRR_BR8_Msk (0x1000000UL)   /*!< BR8 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PD_BSRR_BR7_Pos (23UL)          /*!< BR7 (Bit 23)                                          */
#define GPIOF_PD_BSRR_BR7_Msk (0x800000UL)    /*!< BR7 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PD_BSRR_BR6_Pos (22UL)          /*!< BR6 (Bit 22)                                          */
#define GPIOF_PD_BSRR_BR6_Msk (0x400000UL)    /*!< BR6 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PD_BSRR_BR5_Pos (21UL)          /*!< BR5 (Bit 21)                                          */
#define GPIOF_PD_BSRR_BR5_Msk (0x200000UL)    /*!< BR5 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PD_BSRR_BR4_Pos (20UL)          /*!< BR4 (Bit 20)                                          */
#define GPIOF_PD_BSRR_BR4_Msk (0x100000UL)    /*!< BR4 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PD_BSRR_BR3_Pos (19UL)          /*!< BR3 (Bit 19)                                          */
#define GPIOF_PD_BSRR_BR3_Msk (0x80000UL)     /*!< BR3 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PD_BSRR_BR2_Pos (18UL)          /*!< BR2 (Bit 18)                                          */
#define GPIOF_PD_BSRR_BR2_Msk (0x40000UL)     /*!< BR2 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PD_BSRR_BR1_Pos (17UL)          /*!< BR1 (Bit 17)                                          */
#define GPIOF_PD_BSRR_BR1_Msk (0x20000UL)     /*!< BR1 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PD_BSRR_BR0_Pos (16UL)          /*!< BR0 (Bit 16)                                          */
#define GPIOF_PD_BSRR_BR0_Msk (0x10000UL)     /*!< BR0 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PD_BSRR_BS15_Pos (15UL)         /*!< BS15 (Bit 15)                                         */
#define GPIOF_PD_BSRR_BS15_Msk (0x8000UL)     /*!< BS15 (Bitfield-Mask: 0x01)                            */
#define GPIOF_PD_BSRR_BS14_Pos (14UL)         /*!< BS14 (Bit 14)                                         */
#define GPIOF_PD_BSRR_BS14_Msk (0x4000UL)     /*!< BS14 (Bitfield-Mask: 0x01)                            */
#define GPIOF_PD_BSRR_BS13_Pos (13UL)         /*!< BS13 (Bit 13)                                         */
#define GPIOF_PD_BSRR_BS13_Msk (0x2000UL)     /*!< BS13 (Bitfield-Mask: 0x01)                            */
#define GPIOF_PD_BSRR_BS12_Pos (12UL)         /*!< BS12 (Bit 12)                                         */
#define GPIOF_PD_BSRR_BS12_Msk (0x1000UL)     /*!< BS12 (Bitfield-Mask: 0x01)                            */
#define GPIOF_PD_BSRR_BS11_Pos (11UL)         /*!< BS11 (Bit 11)                                         */
#define GPIOF_PD_BSRR_BS11_Msk (0x800UL)      /*!< BS11 (Bitfield-Mask: 0x01)                            */
#define GPIOF_PD_BSRR_BS10_Pos (10UL)         /*!< BS10 (Bit 10)                                         */
#define GPIOF_PD_BSRR_BS10_Msk (0x400UL)      /*!< BS10 (Bitfield-Mask: 0x01)                            */
#define GPIOF_PD_BSRR_BS9_Pos (9UL)           /*!< BS9 (Bit 9)                                           */
#define GPIOF_PD_BSRR_BS9_Msk (0x200UL)       /*!< BS9 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PD_BSRR_BS8_Pos (8UL)           /*!< BS8 (Bit 8)                                           */
#define GPIOF_PD_BSRR_BS8_Msk (0x100UL)       /*!< BS8 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PD_BSRR_BS7_Pos (7UL)           /*!< BS7 (Bit 7)                                           */
#define GPIOF_PD_BSRR_BS7_Msk (0x80UL)        /*!< BS7 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PD_BSRR_BS6_Pos (6UL)           /*!< BS6 (Bit 6)                                           */
#define GPIOF_PD_BSRR_BS6_Msk (0x40UL)        /*!< BS6 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PD_BSRR_BS5_Pos (5UL)           /*!< BS5 (Bit 5)                                           */
#define GPIOF_PD_BSRR_BS5_Msk (0x20UL)        /*!< BS5 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PD_BSRR_BS4_Pos (4UL)           /*!< BS4 (Bit 4)                                           */
#define GPIOF_PD_BSRR_BS4_Msk (0x10UL)        /*!< BS4 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PD_BSRR_BS3_Pos (3UL)           /*!< BS3 (Bit 3)                                           */
#define GPIOF_PD_BSRR_BS3_Msk (0x8UL)         /*!< BS3 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PD_BSRR_BS2_Pos (2UL)           /*!< BS2 (Bit 2)                                           */
#define GPIOF_PD_BSRR_BS2_Msk (0x4UL)         /*!< BS2 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PD_BSRR_BS1_Pos (1UL)           /*!< BS1 (Bit 1)                                           */
#define GPIOF_PD_BSRR_BS1_Msk (0x2UL)         /*!< BS1 (Bitfield-Mask: 0x01)                             */
#define GPIOF_PD_BSRR_BS0_Pos (0UL)           /*!< BS0 (Bit 0)                                           */
#define GPIOF_PD_BSRR_BS0_Msk (0x1UL)         /*!< BS0 (Bitfield-Mask: 0x01)                             */
/* ==========================================================  IDR  ========================================================== */
#define GPIOF_IDR_IDR15_Pos (15UL)     /*!< IDR15 (Bit 15)                                        */
#define GPIOF_IDR_IDR15_Msk (0x8000UL) /*!< IDR15 (Bitfield-Mask: 0x01)                           */
#define GPIOF_IDR_IDR14_Pos (14UL)     /*!< IDR14 (Bit 14)                                        */
#define GPIOF_IDR_IDR14_Msk (0x4000UL) /*!< IDR14 (Bitfield-Mask: 0x01)                           */
#define GPIOF_IDR_IDR13_Pos (13UL)     /*!< IDR13 (Bit 13)                                        */
#define GPIOF_IDR_IDR13_Msk (0x2000UL) /*!< IDR13 (Bitfield-Mask: 0x01)                           */
#define GPIOF_IDR_IDR12_Pos (12UL)     /*!< IDR12 (Bit 12)                                        */
#define GPIOF_IDR_IDR12_Msk (0x1000UL) /*!< IDR12 (Bitfield-Mask: 0x01)                           */
#define GPIOF_IDR_IDR11_Pos (11UL)     /*!< IDR11 (Bit 11)                                        */
#define GPIOF_IDR_IDR11_Msk (0x800UL)  /*!< IDR11 (Bitfield-Mask: 0x01)                           */
#define GPIOF_IDR_IDR10_Pos (10UL)     /*!< IDR10 (Bit 10)                                        */
#define GPIOF_IDR_IDR10_Msk (0x400UL)  /*!< IDR10 (Bitfield-Mask: 0x01)                           */
#define GPIOF_IDR_IDR9_Pos (9UL)       /*!< IDR9 (Bit 9)                                          */
#define GPIOF_IDR_IDR9_Msk (0x200UL)   /*!< IDR9 (Bitfield-Mask: 0x01)                            */
#define GPIOF_IDR_IDR8_Pos (8UL)       /*!< IDR8 (Bit 8)                                          */
#define GPIOF_IDR_IDR8_Msk (0x100UL)   /*!< IDR8 (Bitfield-Mask: 0x01)                            */
#define GPIOF_IDR_IDR7_Pos (7UL)       /*!< IDR7 (Bit 7)                                          */
#define GPIOF_IDR_IDR7_Msk (0x80UL)    /*!< IDR7 (Bitfield-Mask: 0x01)                            */
#define GPIOF_IDR_IDR6_Pos (6UL)       /*!< IDR6 (Bit 6)                                          */
#define GPIOF_IDR_IDR6_Msk (0x40UL)    /*!< IDR6 (Bitfield-Mask: 0x01)                            */
#define GPIOF_IDR_IDR5_Pos (5UL)       /*!< IDR5 (Bit 5)                                          */
#define GPIOF_IDR_IDR5_Msk (0x20UL)    /*!< IDR5 (Bitfield-Mask: 0x01)                            */
#define GPIOF_IDR_IDR4_Pos (4UL)       /*!< IDR4 (Bit 4)                                          */
#define GPIOF_IDR_IDR4_Msk (0x10UL)    /*!< IDR4 (Bitfield-Mask: 0x01)                            */
#define GPIOF_IDR_IDR3_Pos (3UL)       /*!< IDR3 (Bit 3)                                          */
#define GPIOF_IDR_IDR3_Msk (0x8UL)     /*!< IDR3 (Bitfield-Mask: 0x01)                            */
#define GPIOF_IDR_IDR2_Pos (2UL)       /*!< IDR2 (Bit 2)                                          */
#define GPIOF_IDR_IDR2_Msk (0x4UL)     /*!< IDR2 (Bitfield-Mask: 0x01)                            */
#define GPIOF_IDR_IDR1_Pos (1UL)       /*!< IDR1 (Bit 1)                                          */
#define GPIOF_IDR_IDR1_Msk (0x2UL)     /*!< IDR1 (Bitfield-Mask: 0x01)                            */
#define GPIOF_IDR_IDR0_Pos (0UL)       /*!< IDR0 (Bit 0)                                          */
#define GPIOF_IDR_IDR0_Msk (0x1UL)     /*!< IDR0 (Bitfield-Mask: 0x01)                            */
/* ==========================================================  ODR  ========================================================== */
#define GPIOF_ODR_ODR15_Pos (15UL)     /*!< ODR15 (Bit 15)                                        */
#define GPIOF_ODR_ODR15_Msk (0x8000UL) /*!< ODR15 (Bitfield-Mask: 0x01)                           */
#define GPIOF_ODR_ODR14_Pos (14UL)     /*!< ODR14 (Bit 14)                                        */
#define GPIOF_ODR_ODR14_Msk (0x4000UL) /*!< ODR14 (Bitfield-Mask: 0x01)                           */
#define GPIOF_ODR_ODR13_Pos (13UL)     /*!< ODR13 (Bit 13)                                        */
#define GPIOF_ODR_ODR13_Msk (0x2000UL) /*!< ODR13 (Bitfield-Mask: 0x01)                           */
#define GPIOF_ODR_ODR12_Pos (12UL)     /*!< ODR12 (Bit 12)                                        */
#define GPIOF_ODR_ODR12_Msk (0x1000UL) /*!< ODR12 (Bitfield-Mask: 0x01)                           */
#define GPIOF_ODR_ODR11_Pos (11UL)     /*!< ODR11 (Bit 11)                                        */
#define GPIOF_ODR_ODR11_Msk (0x800UL)  /*!< ODR11 (Bitfield-Mask: 0x01)                           */
#define GPIOF_ODR_ODR10_Pos (10UL)     /*!< ODR10 (Bit 10)                                        */
#define GPIOF_ODR_ODR10_Msk (0x400UL)  /*!< ODR10 (Bitfield-Mask: 0x01)                           */
#define GPIOF_ODR_ODR9_Pos (9UL)       /*!< ODR9 (Bit 9)                                          */
#define GPIOF_ODR_ODR9_Msk (0x200UL)   /*!< ODR9 (Bitfield-Mask: 0x01)                            */
#define GPIOF_ODR_ODR8_Pos (8UL)       /*!< ODR8 (Bit 8)                                          */
#define GPIOF_ODR_ODR8_Msk (0x100UL)   /*!< ODR8 (Bitfield-Mask: 0x01)                            */
#define GPIOF_ODR_ODR7_Pos (7UL)       /*!< ODR7 (Bit 7)                                          */
#define GPIOF_ODR_ODR7_Msk (0x80UL)    /*!< ODR7 (Bitfield-Mask: 0x01)                            */
#define GPIOF_ODR_ODR6_Pos (6UL)       /*!< ODR6 (Bit 6)                                          */
#define GPIOF_ODR_ODR6_Msk (0x40UL)    /*!< ODR6 (Bitfield-Mask: 0x01)                            */
#define GPIOF_ODR_ODR5_Pos (5UL)       /*!< ODR5 (Bit 5)                                          */
#define GPIOF_ODR_ODR5_Msk (0x20UL)    /*!< ODR5 (Bitfield-Mask: 0x01)                            */
#define GPIOF_ODR_ODR4_Pos (4UL)       /*!< ODR4 (Bit 4)                                          */
#define GPIOF_ODR_ODR4_Msk (0x10UL)    /*!< ODR4 (Bitfield-Mask: 0x01)                            */
#define GPIOF_ODR_ODR3_Pos (3UL)       /*!< ODR3 (Bit 3)                                          */
#define GPIOF_ODR_ODR3_Msk (0x8UL)     /*!< ODR3 (Bitfield-Mask: 0x01)                            */
#define GPIOF_ODR_ODR2_Pos (2UL)       /*!< ODR2 (Bit 2)                                          */
#define GPIOF_ODR_ODR2_Msk (0x4UL)     /*!< ODR2 (Bitfield-Mask: 0x01)                            */
#define GPIOF_ODR_ODR1_Pos (1UL)       /*!< ODR1 (Bit 1)                                          */
#define GPIOF_ODR_ODR1_Msk (0x2UL)     /*!< ODR1 (Bitfield-Mask: 0x01)                            */
#define GPIOF_ODR_ODR0_Pos (0UL)       /*!< ODR0 (Bit 0)                                          */
#define GPIOF_ODR_ODR0_Msk (0x1UL)     /*!< ODR0 (Bitfield-Mask: 0x01)                            */
/* =========================================================  BSRR  ========================================================== */
#define GPIOF_BSRR_BR15_Pos (31UL)         /*!< BR15 (Bit 31)                                         */
#define GPIOF_BSRR_BR15_Msk (0x80000000UL) /*!< BR15 (Bitfield-Mask: 0x01)                            */
#define GPIOF_BSRR_BR14_Pos (30UL)         /*!< BR14 (Bit 30)                                         */
#define GPIOF_BSRR_BR14_Msk (0x40000000UL) /*!< BR14 (Bitfield-Mask: 0x01)                            */
#define GPIOF_BSRR_BR13_Pos (29UL)         /*!< BR13 (Bit 29)                                         */
#define GPIOF_BSRR_BR13_Msk (0x20000000UL) /*!< BR13 (Bitfield-Mask: 0x01)                            */
#define GPIOF_BSRR_BR12_Pos (28UL)         /*!< BR12 (Bit 28)                                         */
#define GPIOF_BSRR_BR12_Msk (0x10000000UL) /*!< BR12 (Bitfield-Mask: 0x01)                            */
#define GPIOF_BSRR_BR11_Pos (27UL)         /*!< BR11 (Bit 27)                                         */
#define GPIOF_BSRR_BR11_Msk (0x8000000UL)  /*!< BR11 (Bitfield-Mask: 0x01)                            */
#define GPIOF_BSRR_BR10_Pos (26UL)         /*!< BR10 (Bit 26)                                         */
#define GPIOF_BSRR_BR10_Msk (0x4000000UL)  /*!< BR10 (Bitfield-Mask: 0x01)                            */
#define GPIOF_BSRR_BR9_Pos (25UL)          /*!< BR9 (Bit 25)                                          */
#define GPIOF_BSRR_BR9_Msk (0x2000000UL)   /*!< BR9 (Bitfield-Mask: 0x01)                             */
#define GPIOF_BSRR_BR8_Pos (24UL)          /*!< BR8 (Bit 24)                                          */
#define GPIOF_BSRR_BR8_Msk (0x1000000UL)   /*!< BR8 (Bitfield-Mask: 0x01)                             */
#define GPIOF_BSRR_BR7_Pos (23UL)          /*!< BR7 (Bit 23)                                          */
#define GPIOF_BSRR_BR7_Msk (0x800000UL)    /*!< BR7 (Bitfield-Mask: 0x01)                             */
#define GPIOF_BSRR_BR6_Pos (22UL)          /*!< BR6 (Bit 22)                                          */
#define GPIOF_BSRR_BR6_Msk (0x400000UL)    /*!< BR6 (Bitfield-Mask: 0x01)                             */
#define GPIOF_BSRR_BR5_Pos (21UL)          /*!< BR5 (Bit 21)                                          */
#define GPIOF_BSRR_BR5_Msk (0x200000UL)    /*!< BR5 (Bitfield-Mask: 0x01)                             */
#define GPIOF_BSRR_BR4_Pos (20UL)          /*!< BR4 (Bit 20)                                          */
#define GPIOF_BSRR_BR4_Msk (0x100000UL)    /*!< BR4 (Bitfield-Mask: 0x01)                             */
#define GPIOF_BSRR_BR3_Pos (19UL)          /*!< BR3 (Bit 19)                                          */
#define GPIOF_BSRR_BR3_Msk (0x80000UL)     /*!< BR3 (Bitfield-Mask: 0x01)                             */
#define GPIOF_BSRR_BR2_Pos (18UL)          /*!< BR2 (Bit 18)                                          */
#define GPIOF_BSRR_BR2_Msk (0x40000UL)     /*!< BR2 (Bitfield-Mask: 0x01)                             */
#define GPIOF_BSRR_BR1_Pos (17UL)          /*!< BR1 (Bit 17)                                          */
#define GPIOF_BSRR_BR1_Msk (0x20000UL)     /*!< BR1 (Bitfield-Mask: 0x01)                             */
#define GPIOF_BSRR_BR0_Pos (16UL)          /*!< BR0 (Bit 16)                                          */
#define GPIOF_BSRR_BR0_Msk (0x10000UL)     /*!< BR0 (Bitfield-Mask: 0x01)                             */
#define GPIOF_BSRR_BS15_Pos (15UL)         /*!< BS15 (Bit 15)                                         */
#define GPIOF_BSRR_BS15_Msk (0x8000UL)     /*!< BS15 (Bitfield-Mask: 0x01)                            */
#define GPIOF_BSRR_BS14_Pos (14UL)         /*!< BS14 (Bit 14)                                         */
#define GPIOF_BSRR_BS14_Msk (0x4000UL)     /*!< BS14 (Bitfield-Mask: 0x01)                            */
#define GPIOF_BSRR_BS13_Pos (13UL)         /*!< BS13 (Bit 13)                                         */
#define GPIOF_BSRR_BS13_Msk (0x2000UL)     /*!< BS13 (Bitfield-Mask: 0x01)                            */
#define GPIOF_BSRR_BS12_Pos (12UL)         /*!< BS12 (Bit 12)                                         */
#define GPIOF_BSRR_BS12_Msk (0x1000UL)     /*!< BS12 (Bitfield-Mask: 0x01)                            */
#define GPIOF_BSRR_BS11_Pos (11UL)         /*!< BS11 (Bit 11)                                         */
#define GPIOF_BSRR_BS11_Msk (0x800UL)      /*!< BS11 (Bitfield-Mask: 0x01)                            */
#define GPIOF_BSRR_BS10_Pos (10UL)         /*!< BS10 (Bit 10)                                         */
#define GPIOF_BSRR_BS10_Msk (0x400UL)      /*!< BS10 (Bitfield-Mask: 0x01)                            */
#define GPIOF_BSRR_BS9_Pos (9UL)           /*!< BS9 (Bit 9)                                           */
#define GPIOF_BSRR_BS9_Msk (0x200UL)       /*!< BS9 (Bitfield-Mask: 0x01)                             */
#define GPIOF_BSRR_BS8_Pos (8UL)           /*!< BS8 (Bit 8)                                           */
#define GPIOF_BSRR_BS8_Msk (0x100UL)       /*!< BS8 (Bitfield-Mask: 0x01)                             */
#define GPIOF_BSRR_BS7_Pos (7UL)           /*!< BS7 (Bit 7)                                           */
#define GPIOF_BSRR_BS7_Msk (0x80UL)        /*!< BS7 (Bitfield-Mask: 0x01)                             */
#define GPIOF_BSRR_BS6_Pos (6UL)           /*!< BS6 (Bit 6)                                           */
#define GPIOF_BSRR_BS6_Msk (0x40UL)        /*!< BS6 (Bitfield-Mask: 0x01)                             */
#define GPIOF_BSRR_BS5_Pos (5UL)           /*!< BS5 (Bit 5)                                           */
#define GPIOF_BSRR_BS5_Msk (0x20UL)        /*!< BS5 (Bitfield-Mask: 0x01)                             */
#define GPIOF_BSRR_BS4_Pos (4UL)           /*!< BS4 (Bit 4)                                           */
#define GPIOF_BSRR_BS4_Msk (0x10UL)        /*!< BS4 (Bitfield-Mask: 0x01)                             */
#define GPIOF_BSRR_BS3_Pos (3UL)           /*!< BS3 (Bit 3)                                           */
#define GPIOF_BSRR_BS3_Msk (0x8UL)         /*!< BS3 (Bitfield-Mask: 0x01)                             */
#define GPIOF_BSRR_BS2_Pos (2UL)           /*!< BS2 (Bit 2)                                           */
#define GPIOF_BSRR_BS2_Msk (0x4UL)         /*!< BS2 (Bitfield-Mask: 0x01)                             */
#define GPIOF_BSRR_BS1_Pos (1UL)           /*!< BS1 (Bit 1)                                           */
#define GPIOF_BSRR_BS1_Msk (0x2UL)         /*!< BS1 (Bitfield-Mask: 0x01)                             */
#define GPIOF_BSRR_BS0_Pos (0UL)           /*!< BS0 (Bit 0)                                           */
#define GPIOF_BSRR_BS0_Msk (0x1UL)         /*!< BS0 (Bitfield-Mask: 0x01)                             */
/* =========================================================  LCKR  ========================================================== */
#define GPIOF_LCKR_LCKK_Pos (16UL)      /*!< LCKK (Bit 16)                                         */
#define GPIOF_LCKR_LCKK_Msk (0x10000UL) /*!< LCKK (Bitfield-Mask: 0x01)                            */
#define GPIOF_LCKR_LCK15_Pos (15UL)     /*!< LCK15 (Bit 15)                                        */
#define GPIOF_LCKR_LCK15_Msk (0x8000UL) /*!< LCK15 (Bitfield-Mask: 0x01)                           */
#define GPIOF_LCKR_LCK14_Pos (14UL)     /*!< LCK14 (Bit 14)                                        */
#define GPIOF_LCKR_LCK14_Msk (0x4000UL) /*!< LCK14 (Bitfield-Mask: 0x01)                           */
#define GPIOF_LCKR_LCK13_Pos (13UL)     /*!< LCK13 (Bit 13)                                        */
#define GPIOF_LCKR_LCK13_Msk (0x2000UL) /*!< LCK13 (Bitfield-Mask: 0x01)                           */
#define GPIOF_LCKR_LCK12_Pos (12UL)     /*!< LCK12 (Bit 12)                                        */
#define GPIOF_LCKR_LCK12_Msk (0x1000UL) /*!< LCK12 (Bitfield-Mask: 0x01)                           */
#define GPIOF_LCKR_LCK11_Pos (11UL)     /*!< LCK11 (Bit 11)                                        */
#define GPIOF_LCKR_LCK11_Msk (0x800UL)  /*!< LCK11 (Bitfield-Mask: 0x01)                           */
#define GPIOF_LCKR_LCK10_Pos (10UL)     /*!< LCK10 (Bit 10)                                        */
#define GPIOF_LCKR_LCK10_Msk (0x400UL)  /*!< LCK10 (Bitfield-Mask: 0x01)                           */
#define GPIOF_LCKR_LCK9_Pos (9UL)       /*!< LCK9 (Bit 9)                                          */
#define GPIOF_LCKR_LCK9_Msk (0x200UL)   /*!< LCK9 (Bitfield-Mask: 0x01)                            */
#define GPIOF_LCKR_LCK8_Pos (8UL)       /*!< LCK8 (Bit 8)                                          */
#define GPIOF_LCKR_LCK8_Msk (0x100UL)   /*!< LCK8 (Bitfield-Mask: 0x01)                            */
#define GPIOF_LCKR_LCK7_Pos (7UL)       /*!< LCK7 (Bit 7)                                          */
#define GPIOF_LCKR_LCK7_Msk (0x80UL)    /*!< LCK7 (Bitfield-Mask: 0x01)                            */
#define GPIOF_LCKR_LCK6_Pos (6UL)       /*!< LCK6 (Bit 6)                                          */
#define GPIOF_LCKR_LCK6_Msk (0x40UL)    /*!< LCK6 (Bitfield-Mask: 0x01)                            */
#define GPIOF_LCKR_LCK5_Pos (5UL)       /*!< LCK5 (Bit 5)                                          */
#define GPIOF_LCKR_LCK5_Msk (0x20UL)    /*!< LCK5 (Bitfield-Mask: 0x01)                            */
#define GPIOF_LCKR_LCK4_Pos (4UL)       /*!< LCK4 (Bit 4)                                          */
#define GPIOF_LCKR_LCK4_Msk (0x10UL)    /*!< LCK4 (Bitfield-Mask: 0x01)                            */
#define GPIOF_LCKR_LCK3_Pos (3UL)       /*!< LCK3 (Bit 3)                                          */
#define GPIOF_LCKR_LCK3_Msk (0x8UL)     /*!< LCK3 (Bitfield-Mask: 0x01)                            */
#define GPIOF_LCKR_LCK2_Pos (2UL)       /*!< LCK2 (Bit 2)                                          */
#define GPIOF_LCKR_LCK2_Msk (0x4UL)     /*!< LCK2 (Bitfield-Mask: 0x01)                            */
#define GPIOF_LCKR_LCK1_Pos (1UL)       /*!< LCK1 (Bit 1)                                          */
#define GPIOF_LCKR_LCK1_Msk (0x2UL)     /*!< LCK1 (Bitfield-Mask: 0x01)                            */
#define GPIOF_LCKR_LCK0_Pos (0UL)       /*!< LCK0 (Bit 0)                                          */
#define GPIOF_LCKR_LCK0_Msk (0x1UL)     /*!< LCK0 (Bitfield-Mask: 0x01)                            */
/* =========================================================  AFRL  ========================================================== */
#define GPIOF_AFRL_AFR7_Pos (28UL)         /*!< AFR7 (Bit 28)                                         */
#define GPIOF_AFRL_AFR7_Msk (0xf0000000UL) /*!< AFR7 (Bitfield-Mask: 0x0f)                            */
#define GPIOF_AFRL_AFR6_Pos (24UL)         /*!< AFR6 (Bit 24)                                         */
#define GPIOF_AFRL_AFR6_Msk (0xf000000UL)  /*!< AFR6 (Bitfield-Mask: 0x0f)                            */
#define GPIOF_AFRL_AFR5_Pos (20UL)         /*!< AFR5 (Bit 20)                                         */
#define GPIOF_AFRL_AFR5_Msk (0xf00000UL)   /*!< AFR5 (Bitfield-Mask: 0x0f)                            */
#define GPIOF_AFRL_AFR4_Pos (16UL)         /*!< AFR4 (Bit 16)                                         */
#define GPIOF_AFRL_AFR4_Msk (0xf0000UL)    /*!< AFR4 (Bitfield-Mask: 0x0f)                            */
#define GPIOF_AFRL_AFR3_Pos (12UL)         /*!< AFR3 (Bit 12)                                         */
#define GPIOF_AFRL_AFR3_Msk (0xf000UL)     /*!< AFR3 (Bitfield-Mask: 0x0f)                            */
#define GPIOF_AFRL_AFR2_Pos (8UL)          /*!< AFR2 (Bit 8)                                          */
#define GPIOF_AFRL_AFR2_Msk (0xf00UL)      /*!< AFR2 (Bitfield-Mask: 0x0f)                            */
#define GPIOF_AFRL_AFR1_Pos (4UL)          /*!< AFR1 (Bit 4)                                          */
#define GPIOF_AFRL_AFR1_Msk (0xf0UL)       /*!< AFR1 (Bitfield-Mask: 0x0f)                            */
#define GPIOF_AFRL_AFR0_Pos (0UL)          /*!< AFR0 (Bit 0)                                          */
#define GPIOF_AFRL_AFR0_Msk (0xfUL)        /*!< AFR0 (Bitfield-Mask: 0x0f)                            */
/* =========================================================  AFRH  ========================================================== */
#define GPIOF_AFRH_AFR15_Pos (28UL)         /*!< AFR15 (Bit 28)                                        */
#define GPIOF_AFRH_AFR15_Msk (0xf0000000UL) /*!< AFR15 (Bitfield-Mask: 0x0f)                           */
#define GPIOF_AFRH_AFR14_Pos (24UL)         /*!< AFR14 (Bit 24)                                        */
#define GPIOF_AFRH_AFR14_Msk (0xf000000UL)  /*!< AFR14 (Bitfield-Mask: 0x0f)                           */
#define GPIOF_AFRH_AFR13_Pos (20UL)         /*!< AFR13 (Bit 20)                                        */
#define GPIOF_AFRH_AFR13_Msk (0xf00000UL)   /*!< AFR13 (Bitfield-Mask: 0x0f)                           */
#define GPIOF_AFRH_AFR12_Pos (16UL)         /*!< AFR12 (Bit 16)                                        */
#define GPIOF_AFRH_AFR12_Msk (0xf0000UL)    /*!< AFR12 (Bitfield-Mask: 0x0f)                           */
#define GPIOF_AFRH_AFR11_Pos (12UL)         /*!< AFR11 (Bit 12)                                        */
#define GPIOF_AFRH_AFR11_Msk (0xf000UL)     /*!< AFR11 (Bitfield-Mask: 0x0f)                           */
#define GPIOF_AFRH_AFR10_Pos (8UL)          /*!< AFR10 (Bit 8)                                         */
#define GPIOF_AFRH_AFR10_Msk (0xf00UL)      /*!< AFR10 (Bitfield-Mask: 0x0f)                           */
#define GPIOF_AFRH_AFR9_Pos (4UL)           /*!< AFR9 (Bit 4)                                          */
#define GPIOF_AFRH_AFR9_Msk (0xf0UL)        /*!< AFR9 (Bitfield-Mask: 0x0f)                            */
#define GPIOF_AFRH_AFR8_Pos (0UL)           /*!< AFR8 (Bit 0)                                          */
#define GPIOF_AFRH_AFR8_Msk (0xfUL)         /*!< AFR8 (Bitfield-Mask: 0x0f)                            */
/* =========================================================  BTGLR  ========================================================= */
#define GPIOF_BTGLR_BTGL15_Pos (15UL)     /*!< BTGL15 (Bit 15)                                       */
#define GPIOF_BTGLR_BTGL15_Msk (0x8000UL) /*!< BTGL15 (Bitfield-Mask: 0x01)                          */
#define GPIOF_BTGLR_BTGL14_Pos (14UL)     /*!< BTGL14 (Bit 14)                                       */
#define GPIOF_BTGLR_BTGL14_Msk (0x4000UL) /*!< BTGL14 (Bitfield-Mask: 0x01)                          */
#define GPIOF_BTGLR_BTGL13_Pos (13UL)     /*!< BTGL13 (Bit 13)                                       */
#define GPIOF_BTGLR_BTGL13_Msk (0x2000UL) /*!< BTGL13 (Bitfield-Mask: 0x01)                          */
#define GPIOF_BTGLR_BTGL12_Pos (12UL)     /*!< BTGL12 (Bit 12)                                       */
#define GPIOF_BTGLR_BTGL12_Msk (0x1000UL) /*!< BTGL12 (Bitfield-Mask: 0x01)                          */
#define GPIOF_BTGLR_BTGL11_Pos (11UL)     /*!< BTGL11 (Bit 11)                                       */
#define GPIOF_BTGLR_BTGL11_Msk (0x800UL)  /*!< BTGL11 (Bitfield-Mask: 0x01)                          */
#define GPIOF_BTGLR_BTGL10_Pos (10UL)     /*!< BTGL10 (Bit 10)                                       */
#define GPIOF_BTGLR_BTGL10_Msk (0x400UL)  /*!< BTGL10 (Bitfield-Mask: 0x01)                          */
#define GPIOF_BTGLR_BTGL9_Pos (9UL)       /*!< BTGL9 (Bit 9)                                         */
#define GPIOF_BTGLR_BTGL9_Msk (0x200UL)   /*!< BTGL9 (Bitfield-Mask: 0x01)                           */
#define GPIOF_BTGLR_BTGL8_Pos (8UL)       /*!< BTGL8 (Bit 8)                                         */
#define GPIOF_BTGLR_BTGL8_Msk (0x100UL)   /*!< BTGL8 (Bitfield-Mask: 0x01)                           */
#define GPIOF_BTGLR_BTGL7_Pos (7UL)       /*!< BTGL7 (Bit 7)                                         */
#define GPIOF_BTGLR_BTGL7_Msk (0x80UL)    /*!< BTGL7 (Bitfield-Mask: 0x01)                           */
#define GPIOF_BTGLR_BTGL6_Pos (6UL)       /*!< BTGL6 (Bit 6)                                         */
#define GPIOF_BTGLR_BTGL6_Msk (0x40UL)    /*!< BTGL6 (Bitfield-Mask: 0x01)                           */
#define GPIOF_BTGLR_BTGL5_Pos (5UL)       /*!< BTGL5 (Bit 5)                                         */
#define GPIOF_BTGLR_BTGL5_Msk (0x20UL)    /*!< BTGL5 (Bitfield-Mask: 0x01)                           */
#define GPIOF_BTGLR_BTGL4_Pos (4UL)       /*!< BTGL4 (Bit 4)                                         */
#define GPIOF_BTGLR_BTGL4_Msk (0x10UL)    /*!< BTGL4 (Bitfield-Mask: 0x01)                           */
#define GPIOF_BTGLR_BTGL3_Pos (3UL)       /*!< BTGL3 (Bit 3)                                         */
#define GPIOF_BTGLR_BTGL3_Msk (0x8UL)     /*!< BTGL3 (Bitfield-Mask: 0x01)                           */
#define GPIOF_BTGLR_BTGL2_Pos (2UL)       /*!< BTGL2 (Bit 2)                                         */
#define GPIOF_BTGLR_BTGL2_Msk (0x4UL)     /*!< BTGL2 (Bitfield-Mask: 0x01)                           */
#define GPIOF_BTGLR_BTGL1_Pos (1UL)       /*!< BTGL1 (Bit 1)                                         */
#define GPIOF_BTGLR_BTGL1_Msk (0x2UL)     /*!< BTGL1 (Bitfield-Mask: 0x01)                           */
#define GPIOF_BTGLR_BTGL0_Pos (0UL)       /*!< BTGL0 (Bit 0)                                         */
#define GPIOF_BTGLR_BTGL0_Msk (0x1UL)     /*!< BTGL0 (Bitfield-Mask: 0x01)                           */
/* ========================================================  DR_BSRR  ======================================================== */
#define GPIOF_DR_BSRR_BR15_Pos (31UL)         /*!< BR15 (Bit 31)                                         */
#define GPIOF_DR_BSRR_BR15_Msk (0x80000000UL) /*!< BR15 (Bitfield-Mask: 0x01)                            */
#define GPIOF_DR_BSRR_BR14_Pos (30UL)         /*!< BR14 (Bit 30)                                         */
#define GPIOF_DR_BSRR_BR14_Msk (0x40000000UL) /*!< BR14 (Bitfield-Mask: 0x01)                            */
#define GPIOF_DR_BSRR_BR13_Pos (29UL)         /*!< BR13 (Bit 29)                                         */
#define GPIOF_DR_BSRR_BR13_Msk (0x20000000UL) /*!< BR13 (Bitfield-Mask: 0x01)                            */
#define GPIOF_DR_BSRR_BR12_Pos (28UL)         /*!< BR12 (Bit 28)                                         */
#define GPIOF_DR_BSRR_BR12_Msk (0x10000000UL) /*!< BR12 (Bitfield-Mask: 0x01)                            */
#define GPIOF_DR_BSRR_BR11_Pos (27UL)         /*!< BR11 (Bit 27)                                         */
#define GPIOF_DR_BSRR_BR11_Msk (0x8000000UL)  /*!< BR11 (Bitfield-Mask: 0x01)                            */
#define GPIOF_DR_BSRR_BR10_Pos (26UL)         /*!< BR10 (Bit 26)                                         */
#define GPIOF_DR_BSRR_BR10_Msk (0x4000000UL)  /*!< BR10 (Bitfield-Mask: 0x01)                            */
#define GPIOF_DR_BSRR_BR9_Pos (25UL)          /*!< BR9 (Bit 25)                                          */
#define GPIOF_DR_BSRR_BR9_Msk (0x2000000UL)   /*!< BR9 (Bitfield-Mask: 0x01)                             */
#define GPIOF_DR_BSRR_BR8_Pos (24UL)          /*!< BR8 (Bit 24)                                          */
#define GPIOF_DR_BSRR_BR8_Msk (0x1000000UL)   /*!< BR8 (Bitfield-Mask: 0x01)                             */
#define GPIOF_DR_BSRR_BR7_Pos (23UL)          /*!< BR7 (Bit 23)                                          */
#define GPIOF_DR_BSRR_BR7_Msk (0x800000UL)    /*!< BR7 (Bitfield-Mask: 0x01)                             */
#define GPIOF_DR_BSRR_BR6_Pos (22UL)          /*!< BR6 (Bit 22)                                          */
#define GPIOF_DR_BSRR_BR6_Msk (0x400000UL)    /*!< BR6 (Bitfield-Mask: 0x01)                             */
#define GPIOF_DR_BSRR_BR5_Pos (21UL)          /*!< BR5 (Bit 21)                                          */
#define GPIOF_DR_BSRR_BR5_Msk (0x200000UL)    /*!< BR5 (Bitfield-Mask: 0x01)                             */
#define GPIOF_DR_BSRR_BR4_Pos (20UL)          /*!< BR4 (Bit 20)                                          */
#define GPIOF_DR_BSRR_BR4_Msk (0x100000UL)    /*!< BR4 (Bitfield-Mask: 0x01)                             */
#define GPIOF_DR_BSRR_BR3_Pos (19UL)          /*!< BR3 (Bit 19)                                          */
#define GPIOF_DR_BSRR_BR3_Msk (0x80000UL)     /*!< BR3 (Bitfield-Mask: 0x01)                             */
#define GPIOF_DR_BSRR_BR2_Pos (18UL)          /*!< BR2 (Bit 18)                                          */
#define GPIOF_DR_BSRR_BR2_Msk (0x40000UL)     /*!< BR2 (Bitfield-Mask: 0x01)                             */
#define GPIOF_DR_BSRR_BR1_Pos (17UL)          /*!< BR1 (Bit 17)                                          */
#define GPIOF_DR_BSRR_BR1_Msk (0x20000UL)     /*!< BR1 (Bitfield-Mask: 0x01)                             */
#define GPIOF_DR_BSRR_BR0_Pos (16UL)          /*!< BR0 (Bit 16)                                          */
#define GPIOF_DR_BSRR_BR0_Msk (0x10000UL)     /*!< BR0 (Bitfield-Mask: 0x01)                             */
#define GPIOF_DR_BSRR_BS15_Pos (15UL)         /*!< BS15 (Bit 15)                                         */
#define GPIOF_DR_BSRR_BS15_Msk (0x8000UL)     /*!< BS15 (Bitfield-Mask: 0x01)                            */
#define GPIOF_DR_BSRR_BS14_Pos (14UL)         /*!< BS14 (Bit 14)                                         */
#define GPIOF_DR_BSRR_BS14_Msk (0x4000UL)     /*!< BS14 (Bitfield-Mask: 0x01)                            */
#define GPIOF_DR_BSRR_BS13_Pos (13UL)         /*!< BS13 (Bit 13)                                         */
#define GPIOF_DR_BSRR_BS13_Msk (0x2000UL)     /*!< BS13 (Bitfield-Mask: 0x01)                            */
#define GPIOF_DR_BSRR_BS12_Pos (12UL)         /*!< BS12 (Bit 12)                                         */
#define GPIOF_DR_BSRR_BS12_Msk (0x1000UL)     /*!< BS12 (Bitfield-Mask: 0x01)                            */
#define GPIOF_DR_BSRR_BS11_Pos (11UL)         /*!< BS11 (Bit 11)                                         */
#define GPIOF_DR_BSRR_BS11_Msk (0x800UL)      /*!< BS11 (Bitfield-Mask: 0x01)                            */
#define GPIOF_DR_BSRR_BS10_Pos (10UL)         /*!< BS10 (Bit 10)                                         */
#define GPIOF_DR_BSRR_BS10_Msk (0x400UL)      /*!< BS10 (Bitfield-Mask: 0x01)                            */
#define GPIOF_DR_BSRR_BS9_Pos (9UL)           /*!< BS9 (Bit 9)                                           */
#define GPIOF_DR_BSRR_BS9_Msk (0x200UL)       /*!< BS9 (Bitfield-Mask: 0x01)                             */
#define GPIOF_DR_BSRR_BS8_Pos (8UL)           /*!< BS8 (Bit 8)                                           */
#define GPIOF_DR_BSRR_BS8_Msk (0x100UL)       /*!< BS8 (Bitfield-Mask: 0x01)                             */
#define GPIOF_DR_BSRR_BS7_Pos (7UL)           /*!< BS7 (Bit 7)                                           */
#define GPIOF_DR_BSRR_BS7_Msk (0x80UL)        /*!< BS7 (Bitfield-Mask: 0x01)                             */
#define GPIOF_DR_BSRR_BS6_Pos (6UL)           /*!< BS6 (Bit 6)                                           */
#define GPIOF_DR_BSRR_BS6_Msk (0x40UL)        /*!< BS6 (Bitfield-Mask: 0x01)                             */
#define GPIOF_DR_BSRR_BS5_Pos (5UL)           /*!< BS5 (Bit 5)                                           */
#define GPIOF_DR_BSRR_BS5_Msk (0x20UL)        /*!< BS5 (Bitfield-Mask: 0x01)                             */
#define GPIOF_DR_BSRR_BS4_Pos (4UL)           /*!< BS4 (Bit 4)                                           */
#define GPIOF_DR_BSRR_BS4_Msk (0x10UL)        /*!< BS4 (Bitfield-Mask: 0x01)                             */
#define GPIOF_DR_BSRR_BS3_Pos (3UL)           /*!< BS3 (Bit 3)                                           */
#define GPIOF_DR_BSRR_BS3_Msk (0x8UL)         /*!< BS3 (Bitfield-Mask: 0x01)                             */
#define GPIOF_DR_BSRR_BS2_Pos (2UL)           /*!< BS2 (Bit 2)                                           */
#define GPIOF_DR_BSRR_BS2_Msk (0x4UL)         /*!< BS2 (Bitfield-Mask: 0x01)                             */
#define GPIOF_DR_BSRR_BS1_Pos (1UL)           /*!< BS1 (Bit 1)                                           */
#define GPIOF_DR_BSRR_BS1_Msk (0x2UL)         /*!< BS1 (Bitfield-Mask: 0x01)                             */
#define GPIOF_DR_BSRR_BS0_Pos (0UL)           /*!< BS0 (Bit 0)                                           */
#define GPIOF_DR_BSRR_BS0_Msk (0x1UL)         /*!< BS0 (Bitfield-Mask: 0x01)                             */
/* ==========================================================  DR  =========================================================== */
#define GPIOF_DR_DR15_Pos (15UL)     /*!< DR15 (Bit 15)                                         */
#define GPIOF_DR_DR15_Msk (0x8000UL) /*!< DR15 (Bitfield-Mask: 0x01)                            */
#define GPIOF_DR_DR14_Pos (14UL)     /*!< DR14 (Bit 14)                                         */
#define GPIOF_DR_DR14_Msk (0x4000UL) /*!< DR14 (Bitfield-Mask: 0x01)                            */
#define GPIOF_DR_DR13_Pos (13UL)     /*!< DR13 (Bit 13)                                         */
#define GPIOF_DR_DR13_Msk (0x2000UL) /*!< DR13 (Bitfield-Mask: 0x01)                            */
#define GPIOF_DR_DR12_Pos (12UL)     /*!< DR12 (Bit 12)                                         */
#define GPIOF_DR_DR12_Msk (0x1000UL) /*!< DR12 (Bitfield-Mask: 0x01)                            */
#define GPIOF_DR_DR11_Pos (11UL)     /*!< DR11 (Bit 11)                                         */
#define GPIOF_DR_DR11_Msk (0x800UL)  /*!< DR11 (Bitfield-Mask: 0x01)                            */
#define GPIOF_DR_DR10_Pos (10UL)     /*!< DR10 (Bit 10)                                         */
#define GPIOF_DR_DR10_Msk (0x400UL)  /*!< DR10 (Bitfield-Mask: 0x01)                            */
#define GPIOF_DR_DR9_Pos (9UL)       /*!< DR9 (Bit 9)                                           */
#define GPIOF_DR_DR9_Msk (0x200UL)   /*!< DR9 (Bitfield-Mask: 0x01)                             */
#define GPIOF_DR_DR8_Pos (8UL)       /*!< DR8 (Bit 8)                                           */
#define GPIOF_DR_DR8_Msk (0x100UL)   /*!< DR8 (Bitfield-Mask: 0x01)                             */
#define GPIOF_DR_DR7_Pos (7UL)       /*!< DR7 (Bit 7)                                           */
#define GPIOF_DR_DR7_Msk (0x80UL)    /*!< DR7 (Bitfield-Mask: 0x01)                             */
#define GPIOF_DR_DR6_Pos (6UL)       /*!< DR6 (Bit 6)                                           */
#define GPIOF_DR_DR6_Msk (0x40UL)    /*!< DR6 (Bitfield-Mask: 0x01)                             */
#define GPIOF_DR_DR5_Pos (5UL)       /*!< DR5 (Bit 5)                                           */
#define GPIOF_DR_DR5_Msk (0x20UL)    /*!< DR5 (Bitfield-Mask: 0x01)                             */
#define GPIOF_DR_DR4_Pos (4UL)       /*!< DR4 (Bit 4)                                           */
#define GPIOF_DR_DR4_Msk (0x10UL)    /*!< DR4 (Bitfield-Mask: 0x01)                             */
#define GPIOF_DR_DR3_Pos (3UL)       /*!< DR3 (Bit 3)                                           */
#define GPIOF_DR_DR3_Msk (0x8UL)     /*!< DR3 (Bitfield-Mask: 0x01)                             */
#define GPIOF_DR_DR2_Pos (2UL)       /*!< DR2 (Bit 2)                                           */
#define GPIOF_DR_DR2_Msk (0x4UL)     /*!< DR2 (Bitfield-Mask: 0x01)                             */
#define GPIOF_DR_DR1_Pos (1UL)       /*!< DR1 (Bit 1)                                           */
#define GPIOF_DR_DR1_Msk (0x2UL)     /*!< DR1 (Bitfield-Mask: 0x01)                             */
#define GPIOF_DR_DR0_Pos (0UL)       /*!< DR0 (Bit 0)                                           */
#define GPIOF_DR_DR0_Msk (0x1UL)     /*!< DR0 (Bitfield-Mask: 0x01)                             */
/* ========================================================  CS_BSRR  ======================================================== */
#define GPIOF_CS_BSRR_BR15_Pos (31UL)         /*!< BR15 (Bit 31)                                         */
#define GPIOF_CS_BSRR_BR15_Msk (0x80000000UL) /*!< BR15 (Bitfield-Mask: 0x01)                            */
#define GPIOF_CS_BSRR_BR14_Pos (30UL)         /*!< BR14 (Bit 30)                                         */
#define GPIOF_CS_BSRR_BR14_Msk (0x40000000UL) /*!< BR14 (Bitfield-Mask: 0x01)                            */
#define GPIOF_CS_BSRR_BR13_Pos (29UL)         /*!< BR13 (Bit 29)                                         */
#define GPIOF_CS_BSRR_BR13_Msk (0x20000000UL) /*!< BR13 (Bitfield-Mask: 0x01)                            */
#define GPIOF_CS_BSRR_BR12_Pos (28UL)         /*!< BR12 (Bit 28)                                         */
#define GPIOF_CS_BSRR_BR12_Msk (0x10000000UL) /*!< BR12 (Bitfield-Mask: 0x01)                            */
#define GPIOF_CS_BSRR_BR11_Pos (27UL)         /*!< BR11 (Bit 27)                                         */
#define GPIOF_CS_BSRR_BR11_Msk (0x8000000UL)  /*!< BR11 (Bitfield-Mask: 0x01)                            */
#define GPIOF_CS_BSRR_BR10_Pos (26UL)         /*!< BR10 (Bit 26)                                         */
#define GPIOF_CS_BSRR_BR10_Msk (0x4000000UL)  /*!< BR10 (Bitfield-Mask: 0x01)                            */
#define GPIOF_CS_BSRR_BR9_Pos (25UL)          /*!< BR9 (Bit 25)                                          */
#define GPIOF_CS_BSRR_BR9_Msk (0x2000000UL)   /*!< BR9 (Bitfield-Mask: 0x01)                             */
#define GPIOF_CS_BSRR_BR8_Pos (24UL)          /*!< BR8 (Bit 24)                                          */
#define GPIOF_CS_BSRR_BR8_Msk (0x1000000UL)   /*!< BR8 (Bitfield-Mask: 0x01)                             */
#define GPIOF_CS_BSRR_BR7_Pos (23UL)          /*!< BR7 (Bit 23)                                          */
#define GPIOF_CS_BSRR_BR7_Msk (0x800000UL)    /*!< BR7 (Bitfield-Mask: 0x01)                             */
#define GPIOF_CS_BSRR_BR6_Pos (22UL)          /*!< BR6 (Bit 22)                                          */
#define GPIOF_CS_BSRR_BR6_Msk (0x400000UL)    /*!< BR6 (Bitfield-Mask: 0x01)                             */
#define GPIOF_CS_BSRR_BR5_Pos (21UL)          /*!< BR5 (Bit 21)                                          */
#define GPIOF_CS_BSRR_BR5_Msk (0x200000UL)    /*!< BR5 (Bitfield-Mask: 0x01)                             */
#define GPIOF_CS_BSRR_BR4_Pos (20UL)          /*!< BR4 (Bit 20)                                          */
#define GPIOF_CS_BSRR_BR4_Msk (0x100000UL)    /*!< BR4 (Bitfield-Mask: 0x01)                             */
#define GPIOF_CS_BSRR_BR3_Pos (19UL)          /*!< BR3 (Bit 19)                                          */
#define GPIOF_CS_BSRR_BR3_Msk (0x80000UL)     /*!< BR3 (Bitfield-Mask: 0x01)                             */
#define GPIOF_CS_BSRR_BR2_Pos (18UL)          /*!< BR2 (Bit 18)                                          */
#define GPIOF_CS_BSRR_BR2_Msk (0x40000UL)     /*!< BR2 (Bitfield-Mask: 0x01)                             */
#define GPIOF_CS_BSRR_BR1_Pos (17UL)          /*!< BR1 (Bit 17)                                          */
#define GPIOF_CS_BSRR_BR1_Msk (0x20000UL)     /*!< BR1 (Bitfield-Mask: 0x01)                             */
#define GPIOF_CS_BSRR_BR0_Pos (16UL)          /*!< BR0 (Bit 16)                                          */
#define GPIOF_CS_BSRR_BR0_Msk (0x10000UL)     /*!< BR0 (Bitfield-Mask: 0x01)                             */
#define GPIOF_CS_BSRR_BS15_Pos (15UL)         /*!< BS15 (Bit 15)                                         */
#define GPIOF_CS_BSRR_BS15_Msk (0x8000UL)     /*!< BS15 (Bitfield-Mask: 0x01)                            */
#define GPIOF_CS_BSRR_BS14_Pos (14UL)         /*!< BS14 (Bit 14)                                         */
#define GPIOF_CS_BSRR_BS14_Msk (0x4000UL)     /*!< BS14 (Bitfield-Mask: 0x01)                            */
#define GPIOF_CS_BSRR_BS13_Pos (13UL)         /*!< BS13 (Bit 13)                                         */
#define GPIOF_CS_BSRR_BS13_Msk (0x2000UL)     /*!< BS13 (Bitfield-Mask: 0x01)                            */
#define GPIOF_CS_BSRR_BS12_Pos (12UL)         /*!< BS12 (Bit 12)                                         */
#define GPIOF_CS_BSRR_BS12_Msk (0x1000UL)     /*!< BS12 (Bitfield-Mask: 0x01)                            */
#define GPIOF_CS_BSRR_BS11_Pos (11UL)         /*!< BS11 (Bit 11)                                         */
#define GPIOF_CS_BSRR_BS11_Msk (0x800UL)      /*!< BS11 (Bitfield-Mask: 0x01)                            */
#define GPIOF_CS_BSRR_BS10_Pos (10UL)         /*!< BS10 (Bit 10)                                         */
#define GPIOF_CS_BSRR_BS10_Msk (0x400UL)      /*!< BS10 (Bitfield-Mask: 0x01)                            */
#define GPIOF_CS_BSRR_BS9_Pos (9UL)           /*!< BS9 (Bit 9)                                           */
#define GPIOF_CS_BSRR_BS9_Msk (0x200UL)       /*!< BS9 (Bitfield-Mask: 0x01)                             */
#define GPIOF_CS_BSRR_BS8_Pos (8UL)           /*!< BS8 (Bit 8)                                           */
#define GPIOF_CS_BSRR_BS8_Msk (0x100UL)       /*!< BS8 (Bitfield-Mask: 0x01)                             */
#define GPIOF_CS_BSRR_BS7_Pos (7UL)           /*!< BS7 (Bit 7)                                           */
#define GPIOF_CS_BSRR_BS7_Msk (0x80UL)        /*!< BS7 (Bitfield-Mask: 0x01)                             */
#define GPIOF_CS_BSRR_BS6_Pos (6UL)           /*!< BS6 (Bit 6)                                           */
#define GPIOF_CS_BSRR_BS6_Msk (0x40UL)        /*!< BS6 (Bitfield-Mask: 0x01)                             */
#define GPIOF_CS_BSRR_BS5_Pos (5UL)           /*!< BS5 (Bit 5)                                           */
#define GPIOF_CS_BSRR_BS5_Msk (0x20UL)        /*!< BS5 (Bitfield-Mask: 0x01)                             */
#define GPIOF_CS_BSRR_BS4_Pos (4UL)           /*!< BS4 (Bit 4)                                           */
#define GPIOF_CS_BSRR_BS4_Msk (0x10UL)        /*!< BS4 (Bitfield-Mask: 0x01)                             */
#define GPIOF_CS_BSRR_BS3_Pos (3UL)           /*!< BS3 (Bit 3)                                           */
#define GPIOF_CS_BSRR_BS3_Msk (0x8UL)         /*!< BS3 (Bitfield-Mask: 0x01)                             */
#define GPIOF_CS_BSRR_BS2_Pos (2UL)           /*!< BS2 (Bit 2)                                           */
#define GPIOF_CS_BSRR_BS2_Msk (0x4UL)         /*!< BS2 (Bitfield-Mask: 0x01)                             */
#define GPIOF_CS_BSRR_BS1_Pos (1UL)           /*!< BS1 (Bit 1)                                           */
#define GPIOF_CS_BSRR_BS1_Msk (0x2UL)         /*!< BS1 (Bitfield-Mask: 0x01)                             */
#define GPIOF_CS_BSRR_BS0_Pos (0UL)           /*!< BS0 (Bit 0)                                           */
#define GPIOF_CS_BSRR_BS0_Msk (0x1UL)         /*!< BS0 (Bitfield-Mask: 0x01)                             */
/* ==========================================================  CS  =========================================================== */
#define GPIOF_CS_CS15_Pos (15UL)     /*!< CS15 (Bit 15)                                         */
#define GPIOF_CS_CS15_Msk (0x8000UL) /*!< CS15 (Bitfield-Mask: 0x01)                            */
#define GPIOF_CS_CS14_Pos (14UL)     /*!< CS14 (Bit 14)                                         */
#define GPIOF_CS_CS14_Msk (0x4000UL) /*!< CS14 (Bitfield-Mask: 0x01)                            */
#define GPIOF_CS_CS13_Pos (13UL)     /*!< CS13 (Bit 13)                                         */
#define GPIOF_CS_CS13_Msk (0x2000UL) /*!< CS13 (Bitfield-Mask: 0x01)                            */
#define GPIOF_CS_CS12_Pos (12UL)     /*!< CS12 (Bit 12)                                         */
#define GPIOF_CS_CS12_Msk (0x1000UL) /*!< CS12 (Bitfield-Mask: 0x01)                            */
#define GPIOF_CS_CS11_Pos (11UL)     /*!< CS11 (Bit 11)                                         */
#define GPIOF_CS_CS11_Msk (0x800UL)  /*!< CS11 (Bitfield-Mask: 0x01)                            */
#define GPIOF_CS_CS10_Pos (10UL)     /*!< CS10 (Bit 10)                                         */
#define GPIOF_CS_CS10_Msk (0x400UL)  /*!< CS10 (Bitfield-Mask: 0x01)                            */
#define GPIOF_CS_CS9_Pos (9UL)       /*!< CS9 (Bit 9)                                           */
#define GPIOF_CS_CS9_Msk (0x200UL)   /*!< CS9 (Bitfield-Mask: 0x01)                             */
#define GPIOF_CS_CS8_Pos (8UL)       /*!< CS8 (Bit 8)                                           */
#define GPIOF_CS_CS8_Msk (0x100UL)   /*!< CS8 (Bitfield-Mask: 0x01)                             */
#define GPIOF_CS_CS7_Pos (7UL)       /*!< CS7 (Bit 7)                                           */
#define GPIOF_CS_CS7_Msk (0x80UL)    /*!< CS7 (Bitfield-Mask: 0x01)                             */
#define GPIOF_CS_CS6_Pos (6UL)       /*!< CS6 (Bit 6)                                           */
#define GPIOF_CS_CS6_Msk (0x40UL)    /*!< CS6 (Bitfield-Mask: 0x01)                             */
#define GPIOF_CS_CS5_Pos (5UL)       /*!< CS5 (Bit 5)                                           */
#define GPIOF_CS_CS5_Msk (0x20UL)    /*!< CS5 (Bitfield-Mask: 0x01)                             */
#define GPIOF_CS_CS4_Pos (4UL)       /*!< CS4 (Bit 4)                                           */
#define GPIOF_CS_CS4_Msk (0x10UL)    /*!< CS4 (Bitfield-Mask: 0x01)                             */
#define GPIOF_CS_CS3_Pos (3UL)       /*!< CS3 (Bit 3)                                           */
#define GPIOF_CS_CS3_Msk (0x8UL)     /*!< CS3 (Bitfield-Mask: 0x01)                             */
#define GPIOF_CS_CS2_Pos (2UL)       /*!< CS2 (Bit 2)                                           */
#define GPIOF_CS_CS2_Msk (0x4UL)     /*!< CS2 (Bitfield-Mask: 0x01)                             */
#define GPIOF_CS_CS1_Pos (1UL)       /*!< CS1 (Bit 1)                                           */
#define GPIOF_CS_CS1_Msk (0x2UL)     /*!< CS1 (Bitfield-Mask: 0x01)                             */
#define GPIOF_CS_CS0_Pos (0UL)       /*!< CS0 (Bit 0)                                           */
#define GPIOF_CS_CS0_Msk (0x1UL)     /*!< CS0 (Bitfield-Mask: 0x01)                             */
/* ========================================================  OS_BSRR  ======================================================== */
#define GPIOF_OS_BSRR_BR15_Pos (31UL)         /*!< BR15 (Bit 31)                                         */
#define GPIOF_OS_BSRR_BR15_Msk (0x80000000UL) /*!< BR15 (Bitfield-Mask: 0x01)                            */
#define GPIOF_OS_BSRR_BR14_Pos (30UL)         /*!< BR14 (Bit 30)                                         */
#define GPIOF_OS_BSRR_BR14_Msk (0x40000000UL) /*!< BR14 (Bitfield-Mask: 0x01)                            */
#define GPIOF_OS_BSRR_BR13_Pos (29UL)         /*!< BR13 (Bit 29)                                         */
#define GPIOF_OS_BSRR_BR13_Msk (0x20000000UL) /*!< BR13 (Bitfield-Mask: 0x01)                            */
#define GPIOF_OS_BSRR_BR12_Pos (28UL)         /*!< BR12 (Bit 28)                                         */
#define GPIOF_OS_BSRR_BR12_Msk (0x10000000UL) /*!< BR12 (Bitfield-Mask: 0x01)                            */
#define GPIOF_OS_BSRR_BR11_Pos (27UL)         /*!< BR11 (Bit 27)                                         */
#define GPIOF_OS_BSRR_BR11_Msk (0x8000000UL)  /*!< BR11 (Bitfield-Mask: 0x01)                            */
#define GPIOF_OS_BSRR_BR10_Pos (26UL)         /*!< BR10 (Bit 26)                                         */
#define GPIOF_OS_BSRR_BR10_Msk (0x4000000UL)  /*!< BR10 (Bitfield-Mask: 0x01)                            */
#define GPIOF_OS_BSRR_BR9_Pos (25UL)          /*!< BR9 (Bit 25)                                          */
#define GPIOF_OS_BSRR_BR9_Msk (0x2000000UL)   /*!< BR9 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OS_BSRR_BR8_Pos (24UL)          /*!< BR8 (Bit 24)                                          */
#define GPIOF_OS_BSRR_BR8_Msk (0x1000000UL)   /*!< BR8 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OS_BSRR_BR7_Pos (23UL)          /*!< BR7 (Bit 23)                                          */
#define GPIOF_OS_BSRR_BR7_Msk (0x800000UL)    /*!< BR7 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OS_BSRR_BR6_Pos (22UL)          /*!< BR6 (Bit 22)                                          */
#define GPIOF_OS_BSRR_BR6_Msk (0x400000UL)    /*!< BR6 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OS_BSRR_BR5_Pos (21UL)          /*!< BR5 (Bit 21)                                          */
#define GPIOF_OS_BSRR_BR5_Msk (0x200000UL)    /*!< BR5 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OS_BSRR_BR4_Pos (20UL)          /*!< BR4 (Bit 20)                                          */
#define GPIOF_OS_BSRR_BR4_Msk (0x100000UL)    /*!< BR4 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OS_BSRR_BR3_Pos (19UL)          /*!< BR3 (Bit 19)                                          */
#define GPIOF_OS_BSRR_BR3_Msk (0x80000UL)     /*!< BR3 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OS_BSRR_BR2_Pos (18UL)          /*!< BR2 (Bit 18)                                          */
#define GPIOF_OS_BSRR_BR2_Msk (0x40000UL)     /*!< BR2 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OS_BSRR_BR1_Pos (17UL)          /*!< BR1 (Bit 17)                                          */
#define GPIOF_OS_BSRR_BR1_Msk (0x20000UL)     /*!< BR1 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OS_BSRR_BR0_Pos (16UL)          /*!< BR0 (Bit 16)                                          */
#define GPIOF_OS_BSRR_BR0_Msk (0x10000UL)     /*!< BR0 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OS_BSRR_BS15_Pos (15UL)         /*!< BS15 (Bit 15)                                         */
#define GPIOF_OS_BSRR_BS15_Msk (0x8000UL)     /*!< BS15 (Bitfield-Mask: 0x01)                            */
#define GPIOF_OS_BSRR_BS14_Pos (14UL)         /*!< BS14 (Bit 14)                                         */
#define GPIOF_OS_BSRR_BS14_Msk (0x4000UL)     /*!< BS14 (Bitfield-Mask: 0x01)                            */
#define GPIOF_OS_BSRR_BS13_Pos (13UL)         /*!< BS13 (Bit 13)                                         */
#define GPIOF_OS_BSRR_BS13_Msk (0x2000UL)     /*!< BS13 (Bitfield-Mask: 0x01)                            */
#define GPIOF_OS_BSRR_BS12_Pos (12UL)         /*!< BS12 (Bit 12)                                         */
#define GPIOF_OS_BSRR_BS12_Msk (0x1000UL)     /*!< BS12 (Bitfield-Mask: 0x01)                            */
#define GPIOF_OS_BSRR_BS11_Pos (11UL)         /*!< BS11 (Bit 11)                                         */
#define GPIOF_OS_BSRR_BS11_Msk (0x800UL)      /*!< BS11 (Bitfield-Mask: 0x01)                            */
#define GPIOF_OS_BSRR_BS10_Pos (10UL)         /*!< BS10 (Bit 10)                                         */
#define GPIOF_OS_BSRR_BS10_Msk (0x400UL)      /*!< BS10 (Bitfield-Mask: 0x01)                            */
#define GPIOF_OS_BSRR_BS9_Pos (9UL)           /*!< BS9 (Bit 9)                                           */
#define GPIOF_OS_BSRR_BS9_Msk (0x200UL)       /*!< BS9 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OS_BSRR_BS8_Pos (8UL)           /*!< BS8 (Bit 8)                                           */
#define GPIOF_OS_BSRR_BS8_Msk (0x100UL)       /*!< BS8 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OS_BSRR_BS7_Pos (7UL)           /*!< BS7 (Bit 7)                                           */
#define GPIOF_OS_BSRR_BS7_Msk (0x80UL)        /*!< BS7 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OS_BSRR_BS6_Pos (6UL)           /*!< BS6 (Bit 6)                                           */
#define GPIOF_OS_BSRR_BS6_Msk (0x40UL)        /*!< BS6 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OS_BSRR_BS5_Pos (5UL)           /*!< BS5 (Bit 5)                                           */
#define GPIOF_OS_BSRR_BS5_Msk (0x20UL)        /*!< BS5 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OS_BSRR_BS4_Pos (4UL)           /*!< BS4 (Bit 4)                                           */
#define GPIOF_OS_BSRR_BS4_Msk (0x10UL)        /*!< BS4 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OS_BSRR_BS3_Pos (3UL)           /*!< BS3 (Bit 3)                                           */
#define GPIOF_OS_BSRR_BS3_Msk (0x8UL)         /*!< BS3 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OS_BSRR_BS2_Pos (2UL)           /*!< BS2 (Bit 2)                                           */
#define GPIOF_OS_BSRR_BS2_Msk (0x4UL)         /*!< BS2 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OS_BSRR_BS1_Pos (1UL)           /*!< BS1 (Bit 1)                                           */
#define GPIOF_OS_BSRR_BS1_Msk (0x2UL)         /*!< BS1 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OS_BSRR_BS0_Pos (0UL)           /*!< BS0 (Bit 0)                                           */
#define GPIOF_OS_BSRR_BS0_Msk (0x1UL)         /*!< BS0 (Bitfield-Mask: 0x01)                             */
/* ==========================================================  OS  =========================================================== */
#define GPIOF_OS_OS15_Pos (15UL)     /*!< OS15 (Bit 15)                                         */
#define GPIOF_OS_OS15_Msk (0x8000UL) /*!< OS15 (Bitfield-Mask: 0x01)                            */
#define GPIOF_OS_OS14_Pos (14UL)     /*!< OS14 (Bit 14)                                         */
#define GPIOF_OS_OS14_Msk (0x4000UL) /*!< OS14 (Bitfield-Mask: 0x01)                            */
#define GPIOF_OS_OS13_Pos (13UL)     /*!< OS13 (Bit 13)                                         */
#define GPIOF_OS_OS13_Msk (0x2000UL) /*!< OS13 (Bitfield-Mask: 0x01)                            */
#define GPIOF_OS_OS12_Pos (12UL)     /*!< OS12 (Bit 12)                                         */
#define GPIOF_OS_OS12_Msk (0x1000UL) /*!< OS12 (Bitfield-Mask: 0x01)                            */
#define GPIOF_OS_OS11_Pos (11UL)     /*!< OS11 (Bit 11)                                         */
#define GPIOF_OS_OS11_Msk (0x800UL)  /*!< OS11 (Bitfield-Mask: 0x01)                            */
#define GPIOF_OS_OS10_Pos (10UL)     /*!< OS10 (Bit 10)                                         */
#define GPIOF_OS_OS10_Msk (0x400UL)  /*!< OS10 (Bitfield-Mask: 0x01)                            */
#define GPIOF_OS_OS9_Pos (9UL)       /*!< OS9 (Bit 9)                                           */
#define GPIOF_OS_OS9_Msk (0x200UL)   /*!< OS9 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OS_OS8_Pos (8UL)       /*!< OS8 (Bit 8)                                           */
#define GPIOF_OS_OS8_Msk (0x100UL)   /*!< OS8 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OS_OS7_Pos (7UL)       /*!< OS7 (Bit 7)                                           */
#define GPIOF_OS_OS7_Msk (0x80UL)    /*!< OS7 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OS_OS6_Pos (6UL)       /*!< OS6 (Bit 6)                                           */
#define GPIOF_OS_OS6_Msk (0x40UL)    /*!< OS6 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OS_OS5_Pos (5UL)       /*!< OS5 (Bit 5)                                           */
#define GPIOF_OS_OS5_Msk (0x20UL)    /*!< OS5 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OS_OS4_Pos (4UL)       /*!< OS4 (Bit 4)                                           */
#define GPIOF_OS_OS4_Msk (0x10UL)    /*!< OS4 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OS_OS3_Pos (3UL)       /*!< OS3 (Bit 3)                                           */
#define GPIOF_OS_OS3_Msk (0x8UL)     /*!< OS3 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OS_OS2_Pos (2UL)       /*!< OS2 (Bit 2)                                           */
#define GPIOF_OS_OS2_Msk (0x4UL)     /*!< OS2 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OS_OS1_Pos (1UL)       /*!< OS1 (Bit 1)                                           */
#define GPIOF_OS_OS1_Msk (0x2UL)     /*!< OS1 (Bitfield-Mask: 0x01)                             */
#define GPIOF_OS_OS0_Pos (0UL)       /*!< OS0 (Bit 0)                                           */
#define GPIOF_OS_OS0_Msk (0x1UL)     /*!< OS0 (Bitfield-Mask: 0x01)                             */
  /* Exported macro ------------------------------------------------------------*/
  /* Exported functions ------------------------------------------------------- */
  /* Function used to set the GPIO configuration to the default reset state *****/
  void GPIO_DeInit(GPIO_TypeDef *GPIOx);
  /* Function used to set the RST pin configuration to the GPIO  *****/
  void GPIO_ResetPinConfig(uint32_t NewState);
  /* Initialization and Configuration functions *********************************/
  void GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_InitStruct);
  void GPIO_StructInit(GPIO_InitTypeDef *GPIO_InitStruct);
  void GPIO_PinLockConfig(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

  /* GPIO Read and Write functions **********************************************/
  uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
  uint16_t GPIO_ReadInputData(GPIO_TypeDef *GPIOx);
  uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
  uint16_t GPIO_ReadOutputData(GPIO_TypeDef *GPIOx);
  void GPIO_SetBits(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
  void GPIO_ResetBits(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
  void GPIO_WriteBit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, BitAction BitVal);
  void GPIO_Write(GPIO_TypeDef *GPIOx, uint16_t PortVal);

  /* GPIO Alternate functions configuration functions ***************************/
  void GPIO_PinAFConfig(GPIO_TypeDef *GPIOx, uint16_t GPIO_PinSource, uint8_t GPIO_AF);

  /*GPIO drive level Configuration*/
  void GPIO_DriveConfig(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint16_t GPIO_Drive); //新增

  /*GPIO bit toggle*/
  void GPIO_BitToggle(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin); //新增
  /*digital input or cmos input when gpio mode is input mode*/
  void GPIO_InputCMOSCmd(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, FunctionalState NewState); //新增
  /*added for legacy support*/
  void gpio_ana_mode_set(GPIO_TypeDef *gpio_ptr, uint32_t port_num, uint32_t ae1, uint32_t ae2);
  void gpio_out_mode_set(GPIO_TypeDef *GPIOx, uint32_t port_num);
#ifdef __cplusplus
}
#endif

#endif /* __LCM32F037_GPIO_H */
/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT LCMicroelectronics *****END OF FILE****/
