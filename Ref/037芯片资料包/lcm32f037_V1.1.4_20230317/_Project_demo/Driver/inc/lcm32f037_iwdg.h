/**
  ******************************************************************************
  * @file    lcm32f037_iwdg.h
  * @author  MCD Application Team
  * @version V0.4.44
  * @date    14-04-2021
  * @brief   This file contains all the functions prototypes for the IWDG 
  *          firmware library.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2020 LCMicroelectronics</center></h2>
  *
  * Licensed under MCD-LC Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.lnchip.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef LCM32F037_IWDG_H
#define LCM32F037_IWDG_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "lcm32f037.h"

  /** @addtogroup LCM32F037_StdPeriph_Driver
  * @{
  */

  /** @addtogroup IWDG
  * @{
  */

  /* Exported types ------------------------------------------------------------*/
  /* Exported constants --------------------------------------------------------*/

  /** @defgroup IWDG_Exported_Constants
  * @{
  */

  /** @defgroup IWDG_WriteAccess
  * @{
  */

#define IWDG_WriteAccess_Enable ((uint16_t)0x5555)
#define IWDG_WriteAccess_Disable ((uint16_t)0x0000)
#define IS_IWDG_WRITE_ACCESS(ACCESS) (((ACCESS) == IWDG_WriteAccess_Enable) || \
                                      ((ACCESS) == IWDG_WriteAccess_Disable))
  /**
  * @}
  */

  /** @defgroup IWDG_prescaler 
  * @{
  */

#define IWDG_Prescaler_4 ((uint8_t)0x00)
#define IWDG_Prescaler_8 ((uint8_t)0x01)
#define IWDG_Prescaler_16 ((uint8_t)0x02)
#define IWDG_Prescaler_32 ((uint8_t)0x03)
#define IWDG_Prescaler_64 ((uint8_t)0x04)
#define IWDG_Prescaler_128 ((uint8_t)0x05)
#define IWDG_Prescaler_256 ((uint8_t)0x06)
#define IS_IWDG_PRESCALER(PRESCALER) (((PRESCALER) == IWDG_Prescaler_4) ||   \
                                      ((PRESCALER) == IWDG_Prescaler_8) ||   \
                                      ((PRESCALER) == IWDG_Prescaler_16) ||  \
                                      ((PRESCALER) == IWDG_Prescaler_32) ||  \
                                      ((PRESCALER) == IWDG_Prescaler_64) ||  \
                                      ((PRESCALER) == IWDG_Prescaler_128) || \
                                      ((PRESCALER) == IWDG_Prescaler_256))
  /**
  * @}
  */

  /** @defgroup IWDG_Flag 
  * @{
  */

#define IWDG_SR_PVU 1UL
#define IWDG_SR_RVU 2UL
#define IWDG_SR_WVU 4UL
#define IWDG_FLAG_PVU IWDG_SR_PVU
#define IWDG_FLAG_RVU IWDG_SR_RVU
#define IWDG_FLAG_WVU IWDG_SR_WVU
#define IS_IWDG_FLAG(FLAG) (((FLAG) == IWDG_FLAG_PVU) || \
                            ((FLAG) == IWDG_FLAG_RVU) || \
                            ((FLAG) == IWDG_FLAG_WVU))

#define IS_IWDG_RELOAD(RELOAD) ((RELOAD) <= 0xFFF)

#define IS_IWDG_WINDOW_VALUE(VALUE) ((VALUE) <= 0xFFF)
/**
  * @}
  */

/**
  * @}
  */
/* =========================================================================================================================== */
/* ================                                           IWDG                                            ================ */
/* =========================================================================================================================== */

/* ==========================================================  KR  =========================================================== */
#define IWDG_KR_KEY_Pos (0UL)    /*!< KEY (Bit 0)                                           */
#define IWDG_KR_KEY_Msk (0xffUL) /*!< KEY (Bitfield-Mask: 0xffff)                           */
/* ==========================================================  PR  =========================================================== */
#define IWDG_PR_PR_Pos (0UL)   /*!< PR (Bit 0)                                            */
#define IWDG_PR_PR_Msk (0x7UL) /*!< PR (Bitfield-Mask: 0x07)                              */
/* ==========================================================  RLR  ========================================================== */
#define IWDG_RLR_RL_Pos (0UL)     /*!< RL (Bit 0)                                            */
#define IWDG_RLR_RL_Msk (0xfffUL) /*!< RL (Bitfield-Mask: 0xfff)                             */
/* ==========================================================  SR  =========================================================== */
#define IWDG_SR_WVU_Pos (2UL)   /*!< WVU (Bit 2)                                           */
#define IWDG_SR_WVU_Msk (0x4UL) /*!< WVU (Bitfield-Mask: 0x01)                             */
#define IWDG_SR_RVU_Pos (1UL)   /*!< RVU (Bit 1)                                           */
#define IWDG_SR_RVU_Msk (0x2UL) /*!< RVU (Bitfield-Mask: 0x01)                             */
#define IWDG_SR_PVU_Pos (0UL)   /*!< PVU (Bit 0)                                           */
#define IWDG_SR_PVU_Msk (0x1UL) /*!< PVU (Bitfield-Mask: 0x01)                             */
/* =========================================================  WINTR  ========================================================= */
#define IWDG_WINTR_WIN_Pos (0UL)     /*!< WIN (Bit 0)                                           */
#define IWDG_WINTR_WIN_Msk (0xfffUL) /*!< WIN (Bitfield-Mask: 0xfff)                            */

  /* Exported macro ------------------------------------------------------------*/
  /* Exported functions ------------------------------------------------------- */

  /* Prescaler and Counter configuration functions ******************************/
  void IWDG_WriteAccessCmd(uint16_t IWDG_WriteAccess);
  void IWDG_SetPrescaler(uint8_t IWDG_Prescaler);
  void IWDG_SetReload(uint16_t Reload);
  void IWDG_ReloadCounter(void);
  void IWDG_SetWindowValue(uint16_t WindowValue);

  /* IWDG activation function ***************************************************/
  void IWDG_Enable(void);

  /* Flag management function ***************************************************/
  FlagStatus IWDG_GetFlagStatus(uint16_t IWDG_FLAG);

#ifdef __cplusplus
}
#endif

#endif /* __LCM32F037_IWDG_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT LCMicroelectronics *****END OF FILE****/
