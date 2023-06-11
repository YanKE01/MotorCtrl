/**
  ******************************************************************************
  * @file    lcm32f037_dbgmcu.h
  * @author  MCD Application Team
  * @version V0.4.44
  * @date    14-04-2021
  * @brief   This file contains all the functions prototypes for the DBGMCU firmware 
  *          library.
  ******************************************************************************
  */

#if 1

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef LCM32F037_DBGMCU_H
#define LCM32F037_DBGMCU_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "lcm32f037.h"

#define IS_DBGMCU_PERIPH(PERIPH) ((((PERIPH)&0xFFFFFFF9) == 0x00) && ((PERIPH) != 0x00))

#define DBGMCU_TIM1_STOP (1 << 0)
#define DBGMCU_TIM3_STOP (1 << 1)
#define DBGMCU_TIM6_STOP (1 << 2)
#define DBGMCU_TIM14_STOP (1 << 3)
#define DBGMCU_TIM15_STOP (1 << 4)
#define DBGMCU_TIM16_STOP (1 << 5)
#define DBGMCU_TIM17_STOP (1 << 6)
#define DBGMCU_WT_STOP (1 << 7)
#define DBGMCU_WWDG_STOP (1 << 8)
#define DBGMCU_IWDG_STOP (1 << 9)

#define IS_DBGMCU_APB1PERIPH(PERIPH) ((PERIPH == 0) || (PERIPH > 0))
#define IS_DBGMCU_APB2PERIPH(PERIPH) ((PERIPH == 0) || (PERIPH > 0))

  uint32_t DBGMCU_GetREVID(void);
  uint32_t DBGMCU_GetDEVID(void);

  void DBGMCU_Config(uint32_t DBGMCU_Periph, FunctionalState NewState);
  void DBGMCU_APB1PeriphConfig(uint32_t DBGMCU_Periph, FunctionalState NewState);
  void DBGMCU_APB2PeriphConfig(uint32_t DBGMCU_Periph, FunctionalState NewState);

#ifdef __cplusplus
}
#endif

#endif /* __LCM32F037_DBGMCU_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT LCMicroelectronics *****END OF FILE****/

#endif
