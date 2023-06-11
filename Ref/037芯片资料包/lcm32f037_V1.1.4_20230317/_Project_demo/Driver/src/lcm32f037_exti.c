/**
 ******************************************************************************
 * @file    lcm32f037_exti.c
 * @author  MCD Application Team
 * @version V1.0.0
 * @date    2021-05-21
 * @brief   This file provides all the exti emulation firmware functions.
 ******************************************************************************/
/**
 ******************************************************************************
 * @attention:
 *
 *
 *
 *
 ******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "lcm32f037_exti.h"

/** @addtogroup LCM32F037_StdPeriph_Driver
 * @{
 */

/** @defgroup EXTI
 * @brief EXTI driver modules
 * @{
 */

/** @defgroup EXTI_Private_TypesDefinitions
 * @{
 */

/**
 * @}
 */

/** @defgroup EXTI_Private_Defines
 * @{
 */

#define EXTI_LINENONE ((uint32_t)0x00000) /* No interrupt selected */

/**
 * @}
 */

/** @defgroup EXTI_Private_Macros
 * @{
 */

/**
 * @}
 */

/** @defgroup EXTI_Private_Variables
 * @{
 */

/**
 * @}
 */

/** @defgroup EXTI_Private_FunctionPrototypes
 * @{
 */

/**
 * @}
 */

/** @defgroup EXTI_Private_Functions
 * @{
 */

/**
 * @brief  Deinitializes the EXTI peripheral registers to their default reset values.
 * @param  None
 * @retval None
 */
void EXTI_DeInit(void)
{
  EXTI->IMR = 0x00000000;
  EXTI->EMR = 0x00000000;
  EXTI->RTSR = 0x00000000;
  EXTI->FTSR = 0x00000000;
  EXTI->PR = 0x01FFFFFF;
}

/**
 * @brief  Initializes the EXTI peripheral according to the specified
 *         parameters in the EXTI_InitStruct.
 * @param  EXTI_InitStruct: pointer to a EXTI_InitTypeDef structure
 *         that contains the configuration information for the EXTI peripheral.
 * @retval None
 */
void EXTI_Init(EXTI_InitTypeDef *EXTI_InitStruct)
{
  uint32_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_EXTI_MODE(EXTI_InitStruct->EXTI_Mode));
  assert_param(IS_EXTI_TRIGGER(EXTI_InitStruct->EXTI_Trigger));
  assert_param(IS_EXTI_LINE(EXTI_InitStruct->EXTI_Line));
  assert_param(IS_FUNCTIONAL_STATE(EXTI_InitStruct->EXTI_LineCmd));

  tmp = (uint32_t)EXTI_BASE;

  if (EXTI_InitStruct->EXTI_LineCmd != DISABLE)
  {
    /* Clear EXTI line configuration */
    EXTI->IMR &= ~EXTI_InitStruct->EXTI_Line;
    EXTI->EMR &= ~EXTI_InitStruct->EXTI_Line;

    tmp += EXTI_InitStruct->EXTI_Mode;

    *(__IO uint32_t *)tmp |= EXTI_InitStruct->EXTI_Line;

    /* Clear Rising Falling edge configuration */
    EXTI->RTSR &= ~EXTI_InitStruct->EXTI_Line;
    EXTI->FTSR &= ~EXTI_InitStruct->EXTI_Line;

    /* Select the trigger for the selected external interrupts */
    if (EXTI_InitStruct->EXTI_Trigger == EXTI_Trigger_Rising_Falling)
    {
      /* Rising Falling edge */
      EXTI->RTSR |= EXTI_InitStruct->EXTI_Line;
      EXTI->FTSR |= EXTI_InitStruct->EXTI_Line;
    }
    else
    {
      tmp = (uint32_t)EXTI_BASE;
      tmp += EXTI_InitStruct->EXTI_Trigger;

      *(__IO uint32_t *)tmp |= EXTI_InitStruct->EXTI_Line;
    }
  }
  else
  {
    tmp += EXTI_InitStruct->EXTI_Mode;

    /* Disable the selected external lines */
    *(__IO uint32_t *)tmp &= ~EXTI_InitStruct->EXTI_Line;
  }
}

/**
 * @brief  Fills each EXTI_InitStruct member with its reset value.
 * @param  EXTI_InitStruct: pointer to a EXTI_InitTypeDef structure which will
 *         be initialized.
 * @retval None
 */
void EXTI_StructInit(EXTI_InitTypeDef *EXTI_InitStruct)
{
  EXTI_InitStruct->EXTI_Line = EXTI_LINENONE;
  EXTI_InitStruct->EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStruct->EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStruct->EXTI_LineCmd = DISABLE;
}

/**
 * @brief  Generates a Software interrupt.
 * @param  EXTI_Line: specifies the EXTI lines to be enabled or disabled.
 *   This parameter can be any combination of EXTI_Linex where x can be (0..19).
 * @retval None
 */
void EXTI_GenerateSWInterrupt(uint32_t EXTI_Line)
{
  /* Check the parameters */
  assert_param(IS_EXTI_LINE(EXTI_Line));

  EXTI->SWIER |= EXTI_Line;
}

/**
 * @brief  Checks whether the specified EXTI line flag is set or not.
 * @param  EXTI_Line: specifies the EXTI line flag to check.
 *   This parameter can be:
 *     @arg EXTI_Linex: External interrupt line x where x(0..19)
 * @retval The new state of EXTI_Line (SET or RESET).
 */
FlagStatus EXTI_GetFlagStatus(uint32_t EXTI_Line)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_GET_EXTI_LINE(EXTI_Line));

  if ((EXTI->PR & EXTI_Line) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/**
 * @brief  Clears the EXTI's line pending flags.
 * @param  EXTI_Line: specifies the EXTI lines flags to clear.
 *   This parameter can be any combination of EXTI_Linex where x can be (0..19).
 * @retval None
 */
void EXTI_ClearFlag(uint32_t EXTI_Line)
{
  /* Check the parameters */
  assert_param(IS_EXTI_LINE(EXTI_Line));

  EXTI->PR = EXTI_Line;
}

/**
 * @brief  Checks whether the specified EXTI line is asserted or not.
 * @param  EXTI_Line: specifies the EXTI line to check.
 *   This parameter can be:
 *     @arg EXTI_Linex: External interrupt line x where x(0..19)
 * @retval The new state of EXTI_Line (SET or RESET).
 */
ITStatus EXTI_GetITStatus(uint32_t EXTI_Line)
{
  ITStatus bitstatus = RESET;
  uint32_t enablestatus = 0;
  /* Check the parameters */
  assert_param(IS_GET_EXTI_LINE(EXTI_Line));

  enablestatus = EXTI->IMR & EXTI_Line;
  if (((EXTI->PR & EXTI_Line) != (uint32_t)RESET) && (enablestatus != (uint32_t)RESET))
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/**
 * @brief  Clears the EXTI's line pending bits.
 * @param  EXTI_Line: specifies the EXTI lines to clear.
 *   This parameter can be any combination of EXTI_Linex where x can be (0..19).
 * @retval None
 */
void EXTI_ClearITPendingBit(uint32_t EXTI_Line)
{
  /* Check the parameters */
  assert_param(IS_EXTI_LINE(EXTI_Line));

  EXTI->PR = EXTI_Line;
}

/*
GPIO可选连中断线上
*/
void EXTI_ConnectTo(GPIO_Typedef *GPIO, uint32_t EXTI_Line)
{
  unsigned int tmpreg = 0, tmpreg1 = 0, tmpFlag;
  unsigned char i, setValue;
  unsigned char tmpLine;
  tmpreg = SYSCTRL->EXTI_CFG0;
  tmpreg1 = SYSCTRL->EXTI_CFG1;
  if (GPIO == GPIOA)
    setValue = 0;
  if (GPIO == GPIOB)
    setValue = 1;
  if (GPIO == GPIOF)
    setValue = 5;
  tmpLine = 0;
  for (i = 0; i < 16; i++)
  {
    tmpFlag = EXTI_Line & (1 << i);
    tmpLine++;
    if (tmpFlag)
    {
      if (tmpLine <= 8)
      {
        tmpreg &= ~((7) << (4 * (tmpLine - 1)));
        tmpreg |= setValue << (4 * (tmpLine - 1));
        sysctrl_access();
        SYSCTRL->EXTI_CFG0 |= tmpreg;
        __dekey();
      }
      else
      {
        tmpreg1 &= ~((7) << (4 * (tmpLine - 9)));
        tmpreg1 |= setValue << (4 * (tmpLine - 9));
        sysctrl_access();
        SYSCTRL->EXTI_CFG1 |= tmpreg1;
        __dekey();
      }
    }
  }
}

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/******************* (C) COPYRIGHT 2011 LCMicroelectronics *****END OF FILE****/
