/**
 ******************************************************************************
 * @file    lcm32f037_flash.c
 * @author  MCD Application Team
 * @version V1.0.0
 * @date    2021-05-21
 * @brief   This file provides all the flash emulation firmware functions.
 ******************************************************************************/
/**
 ******************************************************************************
 * @attention:
 *
 *
 *
 *
 ******************************************************************************/
#include "lcm32f037_flash.h"

void FLASH_SetLatency(uint32_t FLASH_Latency)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_FLASH_LATENCY(FLASH_Latency));

  /* Read the ACR register */
  tmpreg = FLASH->ACR;

  /* Sets the Latency value */
  tmpreg &= (uint32_t)(0xFFFFFFF8);
  tmpreg |= FLASH_Latency;

  /* Write the ACR register */
  FLASH->ACR = tmpreg;
}

/**
 * @brief  Checks whether the FLASH Prefetch Buffer status is set or not.
 * @param  None
 * @retval FLASH Prefetch Buffer Status (SET or RESET).
 */
FlagStatus FLASH_GetPrefetchBufferStatus(void)
{
  FlagStatus bitstatus = RESET;

  if ((FLASH->ACR & FLASH_ACR_PRFTBS) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  /* Return the new state of FLASH Prefetch Buffer Status (SET or RESET) */
  return bitstatus;
}

void FLASH_PrefetchBufferCmd(FunctionalState NewState)
{
  /* Check the parameters */
  // assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    FLASH->ACR |= FLASH_ACR_PRFTBE;
  }
  else
  {
    FLASH->ACR &= (uint32_t)(~((uint32_t)FLASH_ACR_PRFTBE));
  }
}

/**
 * @brief  Unlocks the FLASH control register and program memory access.
 * @param  None
 * @retval None
 */
void FLASH_Unlock(void)
{
  if ((FLASH->CR & FLASH_CR_LOCK) != RESET)
  {
    /* Unlocking the program memory access */
    FLASH->KEYR = FLASH_FKEY1;
    FLASH->KEYR = FLASH_FKEY2;
  }
}

/**
 * @brief  Locks the Program memory access.
 * @param  None
 * @retval None
 */
void FLASH_Lock(void)
{
  /* Set the LOCK Bit to lock the FLASH control register and program memory access */
  FLASH->CR |= FLASH_CR_LOCK;
}

/**
 * @brief  Erases a specified page in program memory.
 * @note   To correctly run this function, the FLASH_Unlock() function must be called before.
 * @note   Call the FLASH_Lock() to disable the flash memory access (recommended
 *         to protect the FLASH memory against possible unwanted operation)
 * @param  Page_Address: The page address in program memory to be erased.
 * @note   A Page is erased in the Program memory only if the address to load
 *         is the start address of a page (multiple of 1024 bytes).
 * @retval FLASH Status: The returned value can be:
 *         FLASH_ERROR_PROGRAM, FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
 */
FLASH_Status FLASH_ErasePage(uint32_t Page_Address)
{
  FLASH_Status status = FLASH_COMPLETE;

  /* Check the parameters */
  assert_param(IS_FLASH_PROGRAM_ADDRESS(Page_Address));

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

  if (status == FLASH_COMPLETE)
  {
    /* If the previous operation is completed, proceed to erase the page */
    FLASH->CR |= FLASH_CR_PER;
    FLASH->AR = Page_Address;
    FLASH->CR |= FLASH_CR_STRT;

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    /* Disable the PER Bit */
    FLASH->CR &= ~FLASH_CR_PER;
  }

  /* Return the Erase Status */
  return status;
}

/**
 * @brief  Erases all FLASH pages.
 * @note   To correctly run this function, the FLASH_Unlock() function must be called before.
 * @note   Call the FLASH_Lock() to disable the flash memory access (recommended
 *         to protect the FLASH memory against possible unwanted operation)
 * @param  None
 * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
 *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
 */
FLASH_Status FLASH_EraseAllPages(void)
{
  FLASH_Status status = FLASH_COMPLETE;

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

  if (status == FLASH_COMPLETE)
  {
    /* if the previous operation is completed, proceed to erase all pages */
    FLASH->CR |= FLASH_CR_MER;
    FLASH->CR |= FLASH_CR_STRT;

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    /* Disable the MER Bit */
    FLASH->CR &= ~FLASH_CR_MER;
  }

  /* Return the Erase Status */
  return status;
}

/**
 * @brief  Programs a word at a specified address.
 * @note   To correctly run this function, the FLASH_Unlock() function must be called before.
 * @note   Call the FLASH_Lock() to disable the flash memory access (recommended
 *         to protect the FLASH memory against possible unwanted operation)
 * @param  Address: specifies the address to be programmed.
 * @param  Data: specifies the data to be programmed.
 * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
 *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
 */
FLASH_Status FLASH_ProgramWord(uint32_t Address, uint32_t Data)
{
  FLASH_Status status = FLASH_COMPLETE;
  __IO uint32_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_FLASH_PROGRAM_ADDRESS(Address));

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

  if (status == FLASH_COMPLETE)
  {
    /* If the previous operation is completed, proceed to program the new first
    half word */
    FLASH->CR |= FLASH_CR_PG;

    *(__IO uint16_t *)Address = (uint16_t)Data;

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    if (status == FLASH_COMPLETE)
    {
      /* If the previous operation is completed, proceed to program the new second
      half word */
      tmp = Address + 2;

      *(__IO uint16_t *)tmp = Data >> 16;

      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

      /* Disable the PG Bit */
      FLASH->CR &= ~FLASH_CR_PG;
    }
    else
    {
      /* Disable the PG Bit */
      FLASH->CR &= ~FLASH_CR_PG;
    }
  }

  /* Return the Program Status */
  return status;
}

/**
 * @brief  Programs a half word at a specified address.
 * @note   To correctly run this function, the FLASH_Unlock() function must be called before.
 * @note   Call the FLASH_Lock() to disable the flash memory access (recommended
 *         to protect the FLASH memory against possible unwanted operation)
 * @param  Address: specifies the address to be programmed.
 * @param  Data: specifies the data to be programmed.
 * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
 *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
 */
FLASH_Status FLASH_ProgramHalfWord(uint32_t Address, uint16_t Data)
{
  FLASH_Status status = FLASH_COMPLETE;

  /* Check the parameters */
  assert_param(IS_FLASH_PROGRAM_ADDRESS(Address));

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

  if (status == FLASH_COMPLETE)
  {
    /* If the previous operation is completed, proceed to program the new data */
    FLASH->CR |= FLASH_CR_PG;

    *(__IO uint16_t *)Address = Data;

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    /* Disable the PG Bit */
    FLASH->CR &= ~FLASH_CR_PG;
  }

  /* Return the Program Status */
  return status;
}

/**
 * @brief  Unlocks the option bytes block access.
 * @param  None
 * @retval None
 */
void FLASH_OB_Unlock(void)
{
  if ((FLASH->CR & FLASH_CR_OPTWRE) == RESET)
  {
    /* Unlocking the option bytes block access */
    FLASH->OPTKEYR = FLASH_OPTKEY1;
    FLASH->OPTKEYR = FLASH_OPTKEY2;
  }
}

/**
 * @brief  Locks the option bytes block access.
 * @param  None
 * @retval None
 */
void FLASH_OB_Lock(void)
{
  /* Set the OPTWREN Bit to lock the option bytes block access */
  FLASH->CR &= ~FLASH_CR_OPTWRE;
}

/**
 * @brief  Launch the option byte loading.
 * @param  None
 * @retval None
 */
void FLASH_OB_Launch(void)
{
  /* Set the OBL_Launch bit to launch the option byte loading 强�?�写�?option byte 会产生systen reset�?*/
  // FLASH->CR |= FLASH_CR_OBL_LAUNCH;//�?找到相应的OBL_LAUNCH�?.�?能只用reset才能更新�?
}

/**
 * @brief  Erases the FLASH option bytes.
 * @note   To correctly run this function, the FLASH_OB_Unlock() function must be called before.
 * @note   Call the FLASH_OB_Lock() to disable the flash control register access and the option
 *         bytes (recommended to protect the FLASH memory against possible unwanted operation)
 * @note   This functions erases all option bytes except the Read protection (RDP).
 * @param  None
 * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
 *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
 */
FLASH_Status FLASH_OB_Erase(void)
{
  uint16_t rdptmp = 0;
  uint16_t rdptmp2 = 0;
  uint16_t counter = 0;
  FLASH_Status status = FLASH_COMPLETE;
  FLASH->AR = ((uint32_t)(OB_BASE));
  /* Get the actual read protection Option Byte value */
  /*if(FLASH_OB_GetRDP() != RESET)//读取保护等级，�?�果保护等级不是0，则预�?�置为L1
  {*/
  rdptmp = 0x00;
  for (counter = 0; counter < 4; counter++)
  {
    if (OB->RDP2[counter] != 0x33CC)
    {
      rdptmp2 = 1; // rdp2 �?使用
      break;
    }
  }
  if (rdptmp2)
  {
    for (counter = 0; counter < 8; counter++)
    {
      if (OB->RDP[counter] != 0x55AA)
        rdptmp |= (1 << counter);
    }
    rdptmp = rdptmp;
  }

  //}
  // printf("rdptmp=0x%x\n",rdptmp);
  // printf("rdptmp2=0x%x\n",rdptmp2);
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

  if (status == FLASH_COMPLETE)
  {
    /* If the previous operation is completed, proceed to erase the option bytes */
    FLASH->CR |= FLASH_CR_OPTER;
    FLASH->CR |= FLASH_CR_STRT;

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    if (status == FLASH_COMPLETE)
    {
      /* If the erase operation is completed, disable the OPTER Bit */
      FLASH->CR &= ~FLASH_CR_OPTER;

      /* Enable the Option Bytes Programming operation */
      FLASH->CR |= FLASH_CR_OPTPG;

      /* Restore the last read protection Option Byte value */
      if (rdptmp2 == 0)
      {
        OB->RDP2[0] = 0xcc;
        OB->RDP2[1] = 0xcc;
        OB->RDP2[2] = 0xcc;
        OB->RDP2[3] = 0xcc;
      }
      else
      {
        for (counter = 0; counter < 8; counter++)
        {
          if (rdptmp >> counter)
          {
            OB->RDP[counter] = 0xBB;
          }
          else
          {
            OB->RDP[counter] = 0xAA;
          }
        }
      }

      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

      if (status != FLASH_TIMEOUT)
      {
        /* if the program operation is completed, disable the OPTPG Bit */
        FLASH->CR &= ~FLASH_CR_OPTPG;
      }
    }
    else
    {
      if (status != FLASH_TIMEOUT)
      {
        /* Disable the OPTPG Bit */
        FLASH->CR &= ~FLASH_CR_OPTPG;
      }
    }
  }
  /* Return the erase status */
  return status;
}

FLASH_Status FLASH_OB_EnableWRP(uint32_t OB_WRP)
{ //�?一扇区�?2KB）写保护就往那一扇区对应位写1，和事实相反，不用关心�?
  uint16_t WRP0_Data = 0xFFFF, WRP1_Data = 0xFFFF;
  uint16_t WRP2_Data = 0xFFFF, WRP3_Data = 0xFFFF;

  FLASH_Status status = FLASH_COMPLETE;

  /* Check the parameters */
  assert_param(IS_OB_WRP(OB_WRP));

  OB_WRP = (uint32_t)(~OB_WRP);
  WRP0_Data = (uint16_t)(OB_WRP & OB_WRP0_WRP0);
  WRP1_Data = (uint16_t)((OB_WRP & OB_WRP0_nWRP0) >> 8);
  OB_WRP = OB_WRP >> 16;
  WRP2_Data = (uint16_t)(OB_WRP & OB_WRP0_WRP0);
  WRP3_Data = (uint16_t)((OB_WRP & OB_WRP0_nWRP0) >> 8);
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

  if (status == FLASH_COMPLETE)
  {
    FLASH->CR |= FLASH_CR_OPTPG;

    if (WRP0_Data != 0xFF)
    {
      OB->WRP[0] = WRP0_Data;

      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
    }
    if ((status == FLASH_COMPLETE) && (WRP1_Data != 0xFF))
    {
      OB->WRP[1] = WRP1_Data;

      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
    }

    if ((status == FLASH_COMPLETE) && (WRP2_Data != 0xFF))
    {
      OB->WRP[2] = WRP2_Data;

      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
    }

    if ((status == FLASH_COMPLETE) && (WRP1_Data != 0xFF))
    {
      OB->WRP[3] = WRP3_Data;

      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
    }

    if (status != FLASH_TIMEOUT)
    {
      /* if the program operation is completed, disable the OPTPG Bit */
      FLASH->CR &= ~FLASH_CR_OPTPG;
    }
  }
  /* Return the write protection operation Status */
  return status;
}

/**
 * @brief  Enables or disables the read out protection.
 * @note   To correctly run this function, the FLASH_OB_Unlock() function must be called before.
 * @note   Call the FLASH_OB_Lock() to disable the flash control register access and the option
 *         bytes (recommended to protect the FLASH memory against possible unwanted operation)
 * @param  FLASH_ReadProtection_Level: specifies the read protection level.
 *          This parameter can be:
 *             @arg OB_RDP_Level_0: No protection
 *             @arg OB_RDP_Level_1: Read protection of the memory
 *             @arg OB_RDP_Level_2: Chip protection
 * @note   When enabling OB_RDP level 2 it's no more possible to go back to level 1 or 0
 * @retval FLASH Status: The returned value can be:
 *         FLASH_ERROR_PROGRAM, FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
 */
FLASH_Status FLASH_OB_RDPConfig(uint8_t OB_RDP)
{ //保护�?一段就往那一段（8KB）写1，实际上�?往对应的option byte写入0xBB（level 1�?
  FLASH_Status status = FLASH_COMPLETE;
  uint16_t Rsb_counter;
  /* Check the parameters */
  // assert_param(IS_OB_RDP(OB_RDP));
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
  FLASH->AR = ((uint32_t)(OB_BASE));
  if (status == FLASH_COMPLETE)
  {
    FLASH->CR |= FLASH_CR_OPTER;
    FLASH->CR |= FLASH_CR_STRT;

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    if (status == FLASH_COMPLETE)
    {
      /* If the erase operation is completed, disable the OPTER Bit */
      FLASH->CR &= ~FLASH_CR_OPTER;

      /* Enable the Option Bytes Programming operation */
      FLASH->CR |= FLASH_CR_OPTPG;
      for (Rsb_counter = 0; Rsb_counter < 8; Rsb_counter++)
      {
        if (status == FLASH_COMPLETE)
        {
          if ((OB_RDP >> Rsb_counter) & 0x01)
          {
            OB->RDP[Rsb_counter] = (uint16_t)(0x33BB);
          }
          else
          {
            OB->RDP[Rsb_counter] = (uint16_t)(0x55AA);
          }
        }
        status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
      }
      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

      if (status != FLASH_TIMEOUT)
      {
        /* if the program operation is completed, disable the OPTPG Bit */
        FLASH->CR &= ~FLASH_CR_OPTPG;
      }
    }
    else
    {
      if (status != FLASH_TIMEOUT)
      {
        /* Disable the OPTER Bit */
        FLASH->CR &= ~FLASH_CR_OPTER;
      }
    }
  }
  /* Return the protection operation Status */
  return status;
}

/**
 * @brief  Programs the FLASH User Option Byte: IWDG_SW / RST_STOP / RST_STDBY.
 * @note   To correctly run this function, the FLASH_OB_Unlock() function must be called before.
 * @note   Call the FLASH_OB_Lock() to disable the flash control register access and the option
 *         bytes (recommended to protect the FLASH memory against possible unwanted operation)
 * @param  OB_IWDG: Selects the WDG mode
 *          This parameter can be one of the following values:
 *             @arg OB_IWDG_SW: Software WDG selected
 *             @arg OB_IWDG_HW: Hardware WDG selected
 * @param  OB_STOP: Reset event when entering STOP mode.
 *          This parameter can be one of the following values:
 *             @arg OB_STOP_NoRST: No reset generated when entering in STOP
 *             @arg OB_STOP_RST: Reset generated when entering in STOP
 * @param  OB_STDBY: Reset event when entering Standby mode.
 *          This parameter can be one of the following values:
 *             @arg OB_STDBY_NoRST: No reset generated when entering in STANDBY
 *             @arg OB_STDBY_RST: Reset generated when entering in STANDBY
 * @retval FLASH Status: The returned value can be:
 *         FLASH_ERROR_PROGRAM, FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
 */
FLASH_Status FLASH_OB_USERConfig(uint8_t SWD_SEL, uint8_t IWDG_SEL, uint8_t OB_BOOT_SEL, uint8_t OB_BOOT1, uint8_t OB_BOOT0)
{
  FLASH_Status status = FLASH_COMPLETE;
  uint16_t usertmp;
  /* Check the parameters */
  //  assert_param(IS_OB_IWDG_SEL(IWDG_SEL));
  //  assert_param(IS_OB_SWD_SEL(SWD_SEL));
  //  assert_param(IS_OB_BOOT_SEL(OB_BOOT_SEL));
  //  assert_param(IS_OB_BOOT1(OB_BOOT1));
  //  assert_param(IS_OB_BOOT0(OB_BOOT0));

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

  if (status == FLASH_COMPLETE)
  {
    /* Enable the Option Bytes Programming operation */
    FLASH->CR |= FLASH_CR_OPTPG;

    usertmp = (uint16_t)(SWD_SEL & IWDG_SEL & OB_BOOT_SEL & OB_BOOT1 & OB_BOOT0);
    OB->USER = usertmp;
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    if (status != FLASH_TIMEOUT)
    {
      /* If the program operation is completed, disable the OPTPG Bit */
      FLASH->CR &= ~FLASH_CR_OPTPG;
    }
  }
  /* Return the Option Byte program Status */
  return status;
}

FLASH_Status FLASH_OB_ProgramData(uint8_t DATAx, uint8_t OB_DATA)
{
  FLASH_Status status = FLASH_COMPLETE;
  assert_param(IS_OB_USER_DATA(DATAx));

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

  if (status == FLASH_COMPLETE)
  {
    /* Enable the Option Bytes Programming operation */
    FLASH->CR |= FLASH_CR_OPTPG;

    OB->DATA[DATAx] = ((uint16_t)OB_DATA);

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    if (status != FLASH_TIMEOUT)
    {
      /* If the program operation is completed, disable the OPTPG Bit */
      FLASH->CR &= ~FLASH_CR_OPTPG;
    }
  }
  /* Return the Option Byte program Status */
  return status;
}

/**
 * @brief  Enables or disables the specified FLASH interrupts.
 * @param  FLASH_IT: specifies the FLASH interrupt sources to be enabled or
 *         disabled.
 *          This parameter can be any combination of the following values:
 *             @arg FLASH_IT_EOP: FLASH end of programming Interrupt
 *             @arg FLASH_IT_ERR: FLASH Error Interrupt
 * @retval None
 */
void FLASH_ITConfig(uint32_t FLASH_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FLASH_IT(FLASH_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the interrupt sources */
    FLASH->CR |= FLASH_IT;
  }
  else
  {
    /* Disable the interrupt sources */
    FLASH->CR &= ~(uint32_t)FLASH_IT;
  }
}

/**
 * @brief  Checks whether the specified FLASH flag is set or not.
 * @param  FLASH_FLAG: specifies the FLASH flag to check.
 *          This parameter can be one of the following values:
 *             @arg FLASH_FLAG_BSY: FLASH write/erase operations in progress flag
 *             @arg FLASH_FLAG_PGERR: FLASH Programming error flag flag
 *             @arg FLASH_FLAG_WRPERR: FLASH Write protected error flag
 *             @arg FLASH_FLAG_EOP: FLASH End of Programming flag
 * @retval The new state of FLASH_FLAG (SET or RESET).
 */
FlagStatus FLASH_GetFlagStatus(uint32_t FLASH_FLAG)
{
  FlagStatus bitstatus = RESET;

  /* Check the parameters */
  assert_param(IS_FLASH_GET_FLAG(FLASH_FLAG));

  if ((FLASH->SR & FLASH_FLAG) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  /* Return the new state of FLASH_FLAG (SET or RESET) */
  return bitstatus;
}

/**
 * @brief  Returns the FLASH User Option Bytes values.
 * @param  None
 * @retval The FLASH User Option Bytes .
 */
uint8_t FLASH_OB_GetUser(void)
{
  /* Return the User Option Byte */
  return (uint8_t)(FLASH->OBR >> 8);
}

/**
 * @brief  Returns the FLASH Write Protection Option Bytes value.
 * @param  None
 * @retval The FLASH Write Protection Option Bytes value
 */
uint32_t FLASH_OB_GetWRP(void)
{
  /* Return the FLASH write protection Register value */
  return (uint32_t)(FLASH->WRPR);
}

/**************************�?间层函数*******************************************************/
FLASH_Status FLASH_WaitForLastOperation(uint32_t Timeout)
{
  FLASH_Status status = FLASH_COMPLETE;

  /* Check for the FLASH Status */
  status = FLASH_GetStatus();

  /* Wait for a FLASH operation to complete or a TIMEOUT to occur */
  while ((status == FLASH_BUSY) && (Timeout != 0x00))
  {
    status = FLASH_GetStatus();
    Timeout--;
  }

  if (Timeout == 0x00)
  {
    status = FLASH_TIMEOUT;
  }
  /* Return the operation status */
  return status;
}

FLASH_Status FLASH_GetStatus(void)
{
  FLASH_Status FLASHstatus = FLASH_COMPLETE;

  if ((FLASH->SR & FLASH_FLAG_BSY) == FLASH_FLAG_BSY)
  {
    FLASHstatus = FLASH_BUSY;
  }
  else
  {
    if ((FLASH->SR & (uint32_t)FLASH_FLAG_WRPERR) != (uint32_t)0x00)
    {
      FLASHstatus = FLASH_ERROR_WRP;
    }
    else
    {
      if ((FLASH->SR & (uint32_t)(FLASH_SR_PGERR)) != (uint32_t)0x00)
      {
        FLASHstatus = FLASH_ERROR_PROGRAM;
      }
      else
      {
        FLASHstatus = FLASH_COMPLETE;
      }
    }
  }
  /* Return the FLASH Status */
  return FLASHstatus;
}

/**
 * @brief  Clears the FLASH's pending flags.
 * @param  FLASH_FLAG: specifies the FLASH flags to clear.
 *          This parameter can be any combination of the following values:
 *             @arg FLASH_FLAG_PGERR: FLASH Programming error flag flag
 *             @arg FLASH_FLAG_WRPERR: FLASH Write protected error flag
 *             @arg FLASH_FLAG_EOP: FLASH End of Programming flag
 * @retval None
 */
void FLASH_ClearFlag(uint32_t FLASH_FLAG)
{
  /* Check the parameters */
  assert_param(IS_FLASH_CLEAR_FLAG(FLASH_FLAG));

  /* Clear the flags */
  FLASH->SR = FLASH_FLAG;
}

/**
 * @brief  Checks whether the FLASH Read out Protection Status is set or not.
 * @param  None
 * @retval FLASH ReadOut Protection Status(SET or RESET)
 */
FlagStatus FLASH_OB_GetRDP(void)
{
  FlagStatus readstatus = RESET;

  if ((uint32_t)(FLASH->RDPR & (RDPRT2 | RDPRT)) != RESET)
  {
    readstatus = SET;
  }
  else
  {
    readstatus = RESET;
  }
  return readstatus;
}

void efls_strt_per(uint32_t sec_num, uint32_t mem_type)
{
  uint32_t tmp;

  tmp = FLASH->CR;

  if (mem_type == 0)
  {
    FLASH->AR = 0x08000000 + sec_num * (1 << 9);
    tmp &= ~FLASH_CR_OPTER_Msk;
    tmp |= (1 << 1);
  }
  else if (mem_type == 1)
  {
    FLASH->AR = 0x1FFFF600 + sec_num * (1 << 9);
    tmp &= ~(1 << 1);
    tmp |= FLASH_CR_OPTER_Msk;
  }
  else // if ( mem_type == 2)
  {
    FLASH->AR = 0x1FFFF000 + sec_num * (1 << 9);
    tmp &= ~(1 << 1);
    tmp |= FLASH_CR_OPTER_Msk;
  }

  tmp &= ~FLASH_CR_MER_Msk;
  tmp |= FLASH_CR_STRT_Msk;
  FLASH->CR = tmp;
}

void ERASE_OPT()
{
  FLASH->KEYR = FLASH_FKEY1;
  FLASH->KEYR = FLASH_FKEY2;

  FLASH->OPTKEYR = FLASH_OPTKEY1;
  FLASH->OPTKEYR = FLASH_OPTKEY2;

  FLASH->SMKEYR = FLASH_SMKEYR1;
  FLASH->SMKEYR = FLASH_SMKEYR2;
  efls_strt_per(0, 1); // ERASE
}

void ERASE_SYSTEM_MERMORY()
{
  FLASH->KEYR = FLASH_FKEY1;
  FLASH->KEYR = FLASH_FKEY2;

  FLASH->OPTKEYR = FLASH_OPTKEY1;
  FLASH->OPTKEYR = FLASH_OPTKEY2;

  FLASH->SMKEYR = FLASH_SMKEYR1;
  FLASH->SMKEYR = FLASH_SMKEYR2;

  efls_strt_per(0, 2); // ERASE
  efls_strt_per(1, 2); // ERASE
  efls_strt_per(2, 2); // ERASE
}

void efls_pg(uint32_t addr, uint32_t mem_type, uint32_t data, uint32_t word_flag)
{
  uint32_t base;

  if (mem_type == 0)
    base = 0x08000000; // MAIN FLASH ADR START
  else if (mem_type == 1)
    base = 0x1FFFF600; // OPT ADR START
  else                 // if (mem_type == 2)
    base = 0X1FFFF000; // SM ADR START

  if (word_flag)
    WR_REG(base + addr, data);
  else
    WR_REGH(base + addr, data);
}

void write_opt_flash_n(unsigned int addr, unsigned int data)
{
  addr -= 0x1ffff600;
  FLASH->KEYR = FLASH_FKEY1;
  FLASH->KEYR = FLASH_FKEY2;

  FLASH->OPTKEYR = FLASH_OPTKEY1;
  FLASH->OPTKEYR = FLASH_OPTKEY2;

  FLASH->SMKEYR = FLASH_SMKEYR1;
  FLASH->SMKEYR = FLASH_SMKEYR2;

  FLASH->CR &= ~FLASH_CR_PG_Msk;
  FLASH->CR |= FLASH_CR_OPTPG_Msk; // START OPT PG

  efls_pg(addr, 1, data, 1);
}

void write_sm_flash_n(unsigned int addr, unsigned int data)
{
  addr -= 0x1ffff000;
  FLASH->KEYR = FLASH_FKEY1;
  FLASH->KEYR = FLASH_FKEY2;

  FLASH->OPTKEYR = FLASH_OPTKEY1;
  FLASH->OPTKEYR = FLASH_OPTKEY2;

  FLASH->SMKEYR = FLASH_SMKEYR1;
  FLASH->SMKEYR = FLASH_SMKEYR2;

  FLASH->CR &= ~FLASH_CR_PG_Msk;
  FLASH->CR |= FLASH_CR_OPTPG_Msk; // START OPT PG

  //	efls_strt_per (0, 2);//sec_num0 sector erase
  //  efls_strt_per (1, 2);
  //  efls_strt_per (2, 2);
  //
  //	efls_strt_optpg ();

  efls_pg(addr, 2, data, 1);
}

void opa0_trim1(uint32_t trim)
{

  ANACTRL->OPA0_CSR = (ANACTRL->OPA0_CSR & ~(0x1F << 16)) |
                      (trim << 16);
}
void opa1_trim1(uint32_t trim)
{

  ANACTRL->OPA1_CSR = (ANACTRL->OPA1_CSR & ~(0X1F << 16)) |
                      (trim << 16);
}
void opa2_trim1(uint32_t trim)
{

  ANACTRL->OPA2_CSR = (ANACTRL->OPA2_CSR & ~(0X1F << 16)) |
                      (trim << 16);
}
void rcl_trim(uint32_t trim)
{
  chipctrl_access();
  CHIPCTRL->RCL_CFG = (CHIPCTRL->RCL_CFG & ~(0X3F)) |
                      (trim << 0);
  __dekey();
}
void rch_trim(uint32_t trim)
{
  chipctrl_access();
  CHIPCTRL->RCH_CFG = (CHIPCTRL->RCH_CFG & ~(0XFF)) |
                      (trim << 0);
  __dekey();
}
void bgr_trim(uint32_t trim)
{
  chipctrl_access();
  CHIPCTRL->BGR_CFG = trim;
  __dekey();
}
void adc_trim(uint32_t trim)
{
  ADC->TRIM = trim;
}

void mco_set(uint32_t sel, uint32_t div)
{
  sysctrl_access();
  SYSCTRL->ClkEnR1 = (SYSCTRL->ClkEnR1 & ~(0X7 << 3) & ~(0X7 << 0)) | (sel << 3) | div;
  __dekey();
}
