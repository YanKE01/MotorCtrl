/**
 ******************************************************************************
 * @file    lcm32f037_gpio.c
 * @author  MCD Application Team
 * @version V1.0.0
 * @date    2021-05-21
 * @brief
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
#include "lcm32f037_gpio.h"
#include "lcm32f037_rcc.h"

/** @addtogroup LCM32F037_StdPeriph_Driver
 * @{
 */

/** @defgroup GPIO
 * @brief GPIO driver modules
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup GPIO_Private_Functions
 * @{
 */

/** @defgroup GPIO_Group1 Initialization and Configuration
 *  @brief   Initialization and Configuration
 *
@verbatim
 ===============================================================================
                    ##### Initialization and Configuration #####
 ===============================================================================
@endverbatim
  * @{
  */

/**
 * @brief  Deinitializes the GPIOx peripheral registers to their default reset
 *         values.
 * @param  GPIOx: where x can be (A, B,  F) to select the GPIO peripheral.
 * @retval None
 */
void GPIO_DeInit(GPIO_TypeDef *GPIOx) //@zhang end
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

  if (GPIOx == GPIOA)
  {
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOA, ENABLE);
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOA, DISABLE);
  }
  else if (GPIOx == GPIOB)
  {
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOB, ENABLE);
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOB, DISABLE);
  }
  else
  {
    if (GPIOx == GPIOF)
    {
      RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOF, ENABLE);
      RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOF, DISABLE);
    }
  }
}
/*--------------------------------------------------------------------------------------------
reset引脚PF2作为普通GPIO使用
--------------------------------------------------------------------------------------------*/
void GPIO_ResetPinConfig(uint32_t NewState)
{
  if (NewState != DISABLE)
  {
    chipctrl_access();
    CHIPCTRL->BDCR_b.RET_CFG = 0; // PF2作为通用GPIO
    __dekey();
  }
  else
  {
    chipctrl_access();
    CHIPCTRL->BDCR_b.RET_CFG = 1; // PF2作为复位引脚
    __dekey();
  }
}
/**
 * @brief  Initializes the GPIOx peripheral according to the specified
 *         parameters in the GPIO_InitStruct.
 * @param  GPIOx: where x can be (A, B, C, D or F) to select the GPIO peripheral.
 * @param  GPIO_InitStruct: pointer to a GPIO_InitTypeDef structure that contains
 *         the configuration information for the specified GPIO peripheral.
 * @note   The configured pins can be: GPIO_Pin_0 to GPIO_Pin_15 for GPIOA, GPIOB and GPIOC,
 *         GPIO_Pin_0 to GPIO_Pin_2 for GPIOD, GPIO_Pin_0 to GPIO_Pin_3 for GPIOF.
 * @retval None
 */
void GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_InitStruct)
{
  uint32_t pinpos = 0x00, pos = 0x00 /*, currentpin = 0x00*/;
  uint32_t tmpreg;
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_InitStruct->GPIO_Pin));
  assert_param(IS_GPIO_MODE(GPIO_InitStruct->GPIO_Mode)); // 数值完全对应
  assert_param(IS_GPIO_PUPD(GPIO_InitStruct->GPIO_PuPd));
  assert_param(IS_GPIO_OTYPE(GPIO_InitStruct->GPIO_OType));
  if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_OUT)
  {
    GPIO_InitStruct->GPIO_PuPd = GPIO_PuPd_NOPULL; // 输出模式无上下拉
  }
  /*-------------------------- Configure the port pins -----------------------*/
  pinpos = GPIO_InitStruct->GPIO_Pin; // 取出有多少位要配置
  for (pos = 0; pos < 16; pos++)      // 模式配置
  {
    if ((pinpos >> pos) & 0x01)
    {
      tmpreg = GPIOx->MODER;
      tmpreg &= ~(0x03 << (pos * 2));
      tmpreg |= (GPIO_InitStruct->GPIO_Mode) << pos * 2;
      GPIOx->MODER = tmpreg;
    }
  }
  for (pos = 0; pos < 16; pos++) // 翻转斜率
  {
    if ((pinpos >> pos) & 0x01)
    {
      if (GPIO_InitStruct->GPIO_Speed == GPIO_Speed_Fast) /*GPIO_Speed_Level_2*/
      {

        GPIOx->SR_BSRR = 1 << (pos + 16);
      }
      else // GPIO_Speed_Slow /*GPIO_Speed_Level_1*/
      {
        GPIOx->SR_BSRR = 1 << pos;
      }
    }
  }
  for (pos = 0; pos < 16; pos++) // 电阻上拉下拉
  {
    if ((pinpos >> pos) & 0x01)
    {
      if ((GPIO_InitStruct->GPIO_PuPd) == GPIO_PuPd_UP)
      {
        GPIOx->PD_BSRR = 1 << (pos + 16);
        GPIOx->PU_BSRR = 1 << pos;
      }
      else if ((GPIO_InitStruct->GPIO_PuPd) == GPIO_PuPd_DOWN)
      {
        GPIOx->PU_BSRR = 1 << (pos + 16);
        GPIOx->PD_BSRR = 1 << pos;
      }
      else if ((GPIO_InitStruct->GPIO_PuPd) == GPIO_PuPd_UPDOWN)
      {
        GPIOx->PU_BSRR = 1 << pos;
        GPIOx->PD_BSRR = 1 << pos;
      }
      else // 如果没有选定确认的 PULL 则给默认为 NOPULL
      {
        GPIOx->PU_BSRR = 1 << (pos + 16);
        GPIOx->PD_BSRR = 1 << (pos + 16);
      }
    }
  }
  // if((GPIOx->MODER==GPIO_Mode_OUT)||(GPIOx->MODER==GPIO_Mode_IN))

  for (pos = 0; pos < 16; pos++) // 输出类型
  {
    if ((pinpos >> pos) & 0x01)
    {
      if (GPIO_InitStruct->GPIO_OType == GPIO_OType_PP)
      {
        GPIOx->OD_BSRR = (1 << (pos + 16)); // open drain disable
        GPIOx->OS_BSRR = (1 << (pos + 16));
      }
      else if (GPIO_InitStruct->GPIO_OType == GPIO_OType_OD)
      {
        GPIOx->OD_BSRR = (1 << pos); // open drain enable
      }
      else
      {
        GPIOx->OS_BSRR = (1 << pos); // open sources output enable
      }
    }
  }
}

/**
 * @brief  Fills each GPIO_InitStruct member with its default value.
 * @param  GPIO_InitStruct: pointer to a GPIO_InitTypeDef structure which will
 *         be initialized.
 * @retval None
 */
void GPIO_StructInit(GPIO_InitTypeDef *GPIO_InitStruct)
{
  /* Reset GPIO init structure parameters values */
  /* Reset GPIO init structure parameters values */
  GPIO_InitStruct->GPIO_Pin = GPIO_Pin_All;
  GPIO_InitStruct->GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStruct->GPIO_Speed = GPIO_Speed_Level_2;
  GPIO_InitStruct->GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct->GPIO_PuPd = GPIO_PuPd_NOPULL;
}

/**   已经修@zhang
 * @brief  Locks GPIO Pins configuration registers.
 * @note   Each lock bit freezes a specific configuration register (control and alternate function
 *			registers)
 * @note   The configuration of the locked GPIO pins can no longer be modified
 *         until the next device reset.
 * @param  GPIOx: where x can be (A or B F) to select the GPIO peripheral.
 * @param  GPIO_Pin: specifies the port bit to be written.
 *          This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
 * @retval None
 */
void GPIO_PinLockConfig(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  uint32_t tmp_1 = 0x00010000;
  uint32_t tmp_0 = 0x00000000;
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  tmp_1 |= GPIO_Pin;
  tmp_0 |= GPIO_Pin;
  /* Set LCKK bit */
  GPIOx->LCKR = tmp_1;
  /* Reset LCKK bit */
  GPIOx->LCKR = tmp_0;
  /* Set LCKK bit */
  GPIOx->LCKR = tmp_1;
  /* Read LCKK bit */
  tmp_1 = GPIOx->LCKR;
  /* Read LCKK bit */
  if (!((GPIOx->LCKR >> 16) & 0x01))
  {
    while (1)
      ; // 如果锁定失败将停在这里
  };
}

/**
 * @}
 */

/** @defgroup GPIO_Group2 GPIO Read and Write
 *  @brief   GPIO Read and Write
 *
@verbatim
 ===============================================================================
                      ##### GPIO Read and Write #####
 ===============================================================================

@endverbatim
  * @{
  */

/**   已修改@zhang
 * @brief  Reads the specified input port pin.
 * @param  GPIOx: where x can be (A, B, F) to select the GPIO peripheral.
 * @param  GPIO_Pin: specifies the port bit to read.
 * @note
 * @retval The input port pin value.
 */
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  uint8_t bitstatus = 0x00;

  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GET_GPIO_PIN(GPIO_Pin));

  if (GPIOx->IDR & GPIO_Pin)
  {
    bitstatus = (uint8_t)Bit_SET;
  }
  else
  {
    bitstatus = (uint8_t)Bit_RESET;
  }
  return bitstatus;
}

/**    已修改@zhaeng0102
 * @brief  Reads the specified input port pin.
 * @param  GPIOx: where x can be (A, B, F) to select the GPIO peripheral.
 * @retval The input port pin value.
 */
uint16_t GPIO_ReadInputData(GPIO_TypeDef *GPIOx)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

  return ((uint16_t)GPIOx->IDR);
}

/**   已修改@zhaeng0102
 * @brief  Reads the specified output data port bit.
 * @param  GPIOx: where x can be (A, B,  F) to select the GPIO peripheral.
 * @param  GPIO_Pin: Specifies the port bit to read.
 * @note
 * @retval The output port pin value.
 */
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  uint8_t bitstatus = 0x00;

  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GET_GPIO_PIN(GPIO_Pin));

  if ((GPIOx->ODR & GPIO_Pin) != (uint32_t)Bit_RESET)
  {
    bitstatus = (uint8_t)Bit_SET;
  }
  else
  {
    bitstatus = (uint8_t)Bit_RESET;
  }
  return bitstatus;
}

/**   已修改@zhang
 * @brief  Reads the specified GPIO output data port.
 * @param  GPIOx: where x can be (A, B,  F) to select the GPIO peripheral.
 * @retval GPIO output data port value.
 */
uint16_t GPIO_ReadOutputData(GPIO_TypeDef *GPIOx)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

  return ((uint16_t)GPIOx->ODR);
}

/**     已修改@zhang
 * @brief  Sets the selected data port bits.
 * @param  GPIOx: where x can be (A, B, F) to select the GPIO peripheral.
 * @param  GPIO_Pin: specifies the port bits to be written.
 * @note
 * @retval None
 */
void GPIO_SetBits(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  GPIOx->BSRR = GPIO_Pin;
}

/**  已修改@zhang
 * @brief  Clears the selected data port bits.
 * @param  GPIOx: where x can be (A, B, F) to select the GPIO peripheral.
 * @param  GPIO_Pin: specifies the port bits to be written.
 * @note
 * @retval None
 */
void GPIO_ResetBits(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  GPIOx->BSRR = GPIO_Pin << 16;
}

/**          已修改@zhang
 * @brief  Sets or clears the selected data port bit.
 * @param  GPIOx: where x can be (A, B, C, D or F) to select the GPIO peripheral.
 * @param  GPIO_Pin: specifies the port bit to be written.
 * @param  BitVal: specifies the value to be written to the selected bit.
 *          This parameter can be one of the BitAction enumeration values:
 *            @arg Bit_RESET: to clear the port pin
 *            @arg Bit_SET: to set the port pin
 * @note   The GPIO_Pin parameter can be GPIO_Pin_x where x can be: (0..15) for GPIOA,
 *         GPIOB or GPIOC,(0..2) for GPIOD and(0..3) for GPIOF.
 * @retval None
 */
void GPIO_WriteBit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, BitAction BitVal)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GET_GPIO_PIN(GPIO_Pin));
  assert_param(IS_GPIO_BIT_ACTION(BitVal));

  if (BitVal != Bit_RESET)
  {
    GPIOx->BSRR = GPIO_Pin;
  }
  else
  {
    GPIOx->BSRR = GPIO_Pin << 16;
  }
}

/**  修改完成@zhang
 * @brief  Writes data to the specified GPIO data port.
 * @param  GPIOx: where x can be (A, B, F) to select the GPIO peripheral.
 * @param  PortVal: specifies the value to be written to the port output data register.
 * @retval None
 */
void GPIO_Write(GPIO_TypeDef *GPIOx, uint16_t PortVal)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

  GPIOx->ODR = PortVal;
}

/**
 * @}
 */

/** @defgroup GPIO_Group3 GPIO Alternate functions configuration functions
 *  @brief   GPIO Alternate functions configuration functions
 *
@verbatim
 ===============================================================================
          ##### GPIO Alternate functions configuration functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**   已修改@zhang
 * @brief  Writes data to the specified GPIO data port.
 * @param  GPIOx: where x can be (A  B  F) to select the GPIO peripheral.
 * @param  GPIO_PinSource: specifies the pin for the Alternate function.
 *          This parameter can be GPIO_PinSourcex where x can be (0..15).
 * @param  GPIO_AF: selects the pin to used as Alternate function.
 *          This parameter can be one of the following value:
 *            @arg GPIO_AF_0
 *            @arg GPIO_AF_1
 *            @arg GPIO_AF_2
 *            @arg GPIO_AF_3
 *            @arg GPIO_AF_4
 *            @arg GPIO_AF_5
 *            @arg GPIO_AF_6
 *            @arg GPIO_AF_7
 * @note   The pin should already been configured in Alternate Function mode(AF)
 *         using GPIO_InitStruct->GPIO_Mode = GPIO_Mode_AF
 * @note   Refer to the Alternate function mapping table in the device datasheet
 *         for the detailed mapping of the system and peripherals'alternate
 *         function I/O pins.
 * @retval None
 */
void GPIO_PinAFConfig(GPIO_TypeDef *GPIOx, uint16_t GPIO_PinSource, uint8_t GPIO_AF)
{
  uint32_t tmp_1 = 0x00;
  uint32_t tmp_2 = 0x00;

  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN_SOURCE(GPIO_PinSource));
  assert_param(IS_GPIO_AF(GPIO_AF));
  tmp_1 = GPIOx->AFRL;
  tmp_2 = GPIOx->AFRH;

  if (GPIO_PinSource < 8)
  {
    tmp_1 &= ~(0x0F << (GPIO_PinSource * 4));
    tmp_1 |= (GPIO_AF << (GPIO_PinSource * 4));
  }
  else
  {
    tmp_2 &= ~(0x0F << ((GPIO_PinSource - 8) * 4));
    tmp_2 |= (GPIO_AF << ((GPIO_PinSource - 8) * 4));
  }
  GPIOx->AFRL = tmp_1;
  GPIOx->AFRH = tmp_2;
}

/**  已添加@zhang
  @brief GPIO drive capability configuration.
  @param  GPIO_Drive:
            @arg GPIO_Drive_Level_strong: strong current output.
            @arg GPIO_Drive_Level_weak：thin	current output.
*/
void GPIO_DriveConfig(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint16_t GPIO_Drive)
{
  uint32_t tmppreg;
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));
  assert_param(IS_GPIO_LEVEL(GPIO_Drive));
  tmppreg = GPIOx->DR_BSRR;
  if (GPIO_Drive == GPIO_Drive_Level_strong)
  {

    tmppreg &= ~GPIO_Pin;
    tmppreg |= (GPIO_Pin << 16);
  }
  else // GPIO_Drive_Level_weak
  {
    tmppreg |= (GPIO_Pin);
  }
  GPIOx->DR_BSRR = tmppreg;
}

/**   已添加@zhang
  @brief GPIO bit toggle
*/
void GPIO_BitToggle(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));
  GPIOx->BTGLR = GPIO_Pin;
}

/**  已添加@zhang
  @brief cmos input enable/disable
*/
void GPIO_InputCMOSCmd(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, FunctionalState NewState)
{
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));
  if (NewState != DISABLE) // enable cmos buffer input
  {
    GPIOx->CS_BSRR = GPIO_Pin;
  }
  else // enable digital buffer input( default ).
  {
    GPIOx->CS_BSRR = GPIO_Pin << 16;
  }
}

/**  已添加@zhang
  @brief Set to ana quickly
*/
void gpio_ana_mode_set(GPIO_TypeDef *gpio_ptr, uint32_t port_num, uint32_t ae1, uint32_t ae2)
{
  // set ana mode
  gpio_ptr->MODER |= 0x3 << (port_num << 1);
  // set ana enable
  if (port_num < 8)
    gpio_ptr->AFRL = (gpio_ptr->AFRL & ~(0xf << (port_num << 2))) |
                     ((ae1 | (ae2 << 1)) << (port_num << 2));
  else
    gpio_ptr->AFRH = (gpio_ptr->AFRH & ~(0xf << ((port_num - 8) << 2))) |
                     ((ae1 | (ae2 << 1)) << ((port_num - 8) << 2));
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

/**
 * @}
 */

/************************ (C) COPYRIGHT LCMicroelectronics *****END OF FILE****/
