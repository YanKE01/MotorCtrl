/**
  ******************************************************************************
  * @file    lcm32f037_wwdg.h
  * @author  MCD Application Team
  * @version V0.4.44
  * @date    14-04-2021
  * @brief   This file contains all the functions prototypes for the WWDG 
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
#ifndef LCM32F037_WWDG_H
#define LCM32F037_WWDG_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "lcm32f037.h"

  /** @addtogroup LCM32F037_StdPeriph_Driver
  * @{
  */

  /** @addtogroup WWDG
  * @{
  */
  /* Exported types ------------------------------------------------------------*/
  /* Exported constants --------------------------------------------------------*/

  /** @defgroup WWDG_Exported_Constants
  * @{
  */

  /** @defgroup WWDG_Prescaler 
  * @{
  */

#define WWDG_CFR_EWI ((uint16_t)0x0200)
#define WWDG_CR_WDGA ((uint8_t)0x80) /*!< Activation bit */

#define WWDG_Prescaler_1 ((uint32_t)0x00000000)
#define WWDG_Prescaler_2 ((uint32_t)0x00000080)
#define WWDG_Prescaler_4 ((uint32_t)0x00000100)
#define WWDG_Prescaler_8 ((uint32_t)0x00000180)
#define IS_WWDG_PRESCALER(PRESCALER) (((PRESCALER) == WWDG_Prescaler_1) || \
                                      ((PRESCALER) == WWDG_Prescaler_2) || \
                                      ((PRESCALER) == WWDG_Prescaler_4) || \
                                      ((PRESCALER) == WWDG_Prescaler_8))
#define IS_WWDG_WINDOW_VALUE(VALUE) ((VALUE) <= 0x7F)
#define IS_WWDG_COUNTER(COUNTER) (((COUNTER) >= 0x40) && ((COUNTER) <= 0x7F))

/**
  * @}
  */

/**
  * @}
  */
/* =========================================================================================================================== */
/* ================                                           WWDG                                            ================ */
/* =========================================================================================================================== */

/* ==========================================================  CR  =========================================================== */
#define WWDG_CR_WDGEN_Pos (8UL)     /*!< WDGEN (Bit 8)                                         */
#define WWDG_CR_WDGEN_Msk (0x100UL) /*!< WDGEN (Bitfield-Mask: 0x01)                           */
#define WWDG_CR_WDGA_Pos (7UL)      /*!< WDGA (Bit 7)                                          */
#define WWDG_CR_WDGA_Msk (0x80UL)   /*!< WDGA (Bitfield-Mask: 0x01)                            */
#define WWDG_CR_T_Pos (0UL)         /*!< T (Bit 0)                                             */
#define WWDG_CR_T_Msk (0x7fUL)      /*!< T (Bitfield-Mask: 0x7f)                               */
/* ==========================================================  CFR  ========================================================== */
#define WWDG_CFR_EWI_Pos (9UL)       /*!< EWI (Bit 9)                                           */
#define WWDG_CFR_EWI_Msk (0x200UL)   /*!< EWI (Bitfield-Mask: 0x01)                             */
#define WWDG_CFR_WDGTB_Pos (7UL)     /*!< WDGTB (Bit 7)                                         */
#define WWDG_CFR_WDGTB_Msk (0x180UL) /*!< WDGTB (Bitfield-Mask: 0x03)                           */
#define WWDG_CFR_W_Pos (0UL)         /*!< W (Bit 0)                                             */
#define WWDG_CFR_W_Msk (0x7fUL)      /*!< W (Bitfield-Mask: 0x7f)                               */
/* ==========================================================  SR  =========================================================== */
#define WWDG_SR_EWIF_Pos (0UL)   /*!< EWIF (Bit 0)                                          */
#define WWDG_SR_EWIF_Msk (0x1UL) /*!< EWIF (Bitfield-Mask: 0x01)                            */
  /* Exported macro ------------------------------------------------------------*/
  /* Exported functions ------------------------------------------------------- */
  /*  Function used to set the WWDG configuration to the default reset state ****/
  void WWDG_DeInit(void);

  /* Prescaler, Refresh window and Counter configuration functions **************/
  void WWDG_SetPrescaler(uint32_t WWDG_Prescaler);
  void WWDG_SetWindowValue(uint8_t WindowValue);
  void WWDG_EnableIT(void);
  void WWDG_SetCounter(uint8_t Counter);

  /* WWDG activation functions **************************************************/
  void WWDG_Enable(uint8_t Counter);

  /* Interrupts and flags management functions **********************************/
  FlagStatus WWDG_GetFlagStatus(void);
  void WWDG_ClearFlag(void);

#ifdef __cplusplus
}
#endif

#endif /* __LCM32F037_WWDG_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT LCMicroelectronics *****END OF FILE****/
