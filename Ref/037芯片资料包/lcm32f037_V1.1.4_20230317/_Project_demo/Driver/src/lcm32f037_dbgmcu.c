/**
  ******************************************************************************
  * @file    lcm32f037_dbgmcu.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    2021-05-21
  * @brief   This file provides all the dbgmcu emulation firmware functions.
  ******************************************************************************/
/**
  ******************************************************************************
  * @attention:
  * 
  * 
  * 
  * 
  ******************************************************************************/
#if 1

#include "lcm32f037_dbgmcu.h"

#define IDCODE_DEVID_MASK ((uint32_t)0x00000FFF)

uint32_t DBGMCU_GetREVID(void)
{
  return 0;
}

/**
  * @brief  Returns the device identifier.
  * @param  None
  * @retval Device identifier
  */
uint32_t DBGMCU_GetDEVID(void)
{
  return 0;
}

/**
  * @}
  */

/** @defgroup DBGMCU_Group2 Peripherals Configuration functions
 *  @brief   Peripherals Configuration
 *
@verbatim
  ==============================================================================
               ##### Peripherals Configuration functions #####
  ==============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Configures low power mode behavior when the MCU is in Debug mode.
  * @param  DBGMCU_Periph: specifies the low power mode.
  *         This parameter can be any combination of the following values:
  *             @arg DBGMCU_STOP: Keep debugger connection during STOP mode
  *             @arg DBGMCU_STANDBY: Keep debugger connection during STANDBY mode
  * @param  NewState: new state of the specified low power mode in Debug mode.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DBGMCU_Config(uint32_t DBGMCU_Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DBGMCU_PERIPH(DBGMCU_Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    //DBGMCU->CR |= DBGMCU_Periph;
  }
  else
  {
    //DBGMCU->CR &= ~DBGMCU_Periph;
  }
}

/**
  * @brief  Configures APB1 peripheral behavior when the MCU is in Debug mode.
  * @param  DBGMCU_Periph: specifies the APB1 peripheral.
  *         This parameter can be any combination of the following values:
  *             @arg DBGMCU_TIM2_STOP: TIM2 counter stopped when Core is halted
  *             @arg DBGMCU_TIM3_STOP: TIM3 counter stopped when Core is halted
  *             @arg DBGMCU_TIM6_STOP: TIM6 counter stopped when Core is halted
  *             @arg DBGMCU_TIM14_STOP: TIM14 counter stopped when Core is halted
  *                  when Core is halted.
  *             @arg DBGMCU_WWDG_STOP: Debug WWDG stopped when Core is halted
  *             @arg DBGMCU_IWDG_STOP: Debug IWDG stopped when Core is halted

  *                  when Core is halted
  * @param  NewState: new state of the specified APB1 peripheral in Debug mode.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DBGMCU_APB1PeriphConfig(uint32_t DBGMCU_Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DBGMCU_APB1PERIPH(DBGMCU_Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    sysctrl_access();
    SYSCTRL->DBG_CFG |= DBGMCU_Periph;
    __dekey();
  }
  else
  {
    sysctrl_access();
    SYSCTRL->DBG_CFG &= ~DBGMCU_Periph;
    __dekey();
  }
}

/**
  * @brief  Configures APB2 peripheral behavior when the MCU is in Debug mode.
  * @param  DBGMCU_Periph: specifies the APB2 peripheral.
  *         This parameter can be any combination of the following values:
  *             @arg DBGMCU_TIM1_STOP: TIM1 counter stopped when Core is halted
  *             @arg DBGMCU_TIM15_STOP: TIM15 counter stopped when Core is halted
  *             @arg DBGMCU_TIM16_STOP: TIM16 counter stopped when Core is halted
  *             @arg DBGMCU_TIM17_STOP: TIM17 counter stopped when Core is halted
  * @param  NewState: new state of the specified APB2 peripheral in Debug mode.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DBGMCU_APB2PeriphConfig(uint32_t DBGMCU_Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DBGMCU_APB2PERIPH(DBGMCU_Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    sysctrl_access();
    SYSCTRL->DBG_CFG |= DBGMCU_Periph;
    __dekey();
  }
  else
  {
    sysctrl_access();
    SYSCTRL->DBG_CFG &= ~DBGMCU_Periph;
    __dekey();
  }
}

/************************ (C) COPYRIGHT LCMicroelectronics *****END OF FILE****/

#endif
