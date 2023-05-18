/**
  ******************************************************************************
  * @file    lcm32f037_e2prom.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    2021-05-21
  * @brief   This file provides all the EEPROM emulation firmware functions.
  ******************************************************************************/
/**
  ******************************************************************************
  * @attention:
  * 
  * 
  * 
  * 
  ******************************************************************************/
/** @@attention LCM32F037_EEPROM_Emulation
  * @{ flash 模拟E2功能：
	    1）首先使用2页flash空间：比如PAGE0  PAGE1;
			如果PAGE0写满数据，那么把PAGE0有效数据复制到PAGE1,如果PAGE1满了就复制数据到PAGE0
			这样循环使用：如果想增加寿命，可以多次循环；		
			2）一个PAGE=512byte；halfword+half adress =一个存储数据；每个page第一个word作为状态标志位
			所以一个page最多存储127个数据；512/4-1=127；
			
	   
  */

/* Includes ------------------------------------------------------------------*/
#include "lcm32f037_eeprom.h"
#include "lcm32f037_flash.h"
/* Virtual address defined by the user: 0xFFFF value is prohibited */
uint16_t VirtAddVarTab[NB_OF_VAR];

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Global variable used to store variable value in read sequence */
uint16_t DataVar = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static FLASH_Status EE_Format(void);
static uint16_t EE_VerifyPageFullWriteVariable(uint16_t VirtAddress, uint16_t Data);
static uint16_t EE_PageTransfer(uint16_t VirtAddress, uint16_t Data);
static uint16_t EE_FindValidPage(uint8_t Operation);

/**
  * @brief  Restore the pages to a known good state in case of page's status
  *   corruption after a power loss.
  * @param  None.
  * @retval - Flash error code: on write Flash error
  *         - FLASH_COMPLETE: on success
  */
uint16_t EE_Init(void)
{
    uint32_t PageStatus0 = 6, PageStatus1 = 6;
    uint16_t VarIdx = 0;
    uint16_t EepromStatus = 0, ReadStatus = 0;
    int16_t x = -1;
    uint16_t FlashStatus;

    /* Get Page0 status */
    PageStatus0 = (*(__IO uint32_t *)PAGE0_BASE_ADDRESS);
    /* Get Page1 status */
    PageStatus1 = (*(__IO uint32_t *)PAGE1_BASE_ADDRESS);

    /* Check for invalid header states and repair if necessary */
    switch (PageStatus0)
    {
    case ERASED:
        if (PageStatus1 == VALID_PAGE) /* Page0 erased, Page1 valid */
        {
            /* Erase Page0 */
            FlashStatus = FLASH_ErasePage(PAGE0_BASE_ADDRESS);
            /* If erase operation was failed, a Flash error code is returned */
            if (FlashStatus != FLASH_COMPLETE)
            {
                return FlashStatus;
            }
        }
        else if (PageStatus1 == RECEIVE_DATA) /* Page0 erased, Page1 receive */
        {
            /* Erase Page0 */
            FlashStatus = FLASH_ErasePage(PAGE0_BASE_ADDRESS);
            /* If erase operation was failed, a Flash error code is returned */
            if (FlashStatus != FLASH_COMPLETE)
            {
                return FlashStatus;
            }
            /* Mark Page1 as valid */
            //FlashStatus = FLASH_ProgramHalfWord(PAGE1_BASE_ADDRESS, VALID_PAGE_L);
            FlashStatus = FLASH_ProgramHalfWord(PAGE1_BASE_ADDRESS + 2, VALID_PAGE_H);

            /* If program operation was failed, a Flash error code is returned */
            if (FlashStatus != FLASH_COMPLETE)
            {
                return FlashStatus;
            }
        }
        else /* First EEPROM access (Page0&1 are erased) or invalid state -> format EEPROM */
        {
            /* Erase both Page0 and Page1 and set Page0 as valid page */
            FlashStatus = EE_Format();
            /* If erase/program operation was failed, a Flash error code is returned */
            if (FlashStatus != FLASH_COMPLETE)
            {
                return FlashStatus;
            }
        }
        break;

    case RECEIVE_DATA:                 //PAGE0在接收数据
        if (PageStatus1 == VALID_PAGE) /* Page0 receive, Page1 valid */
        {
            /* Transfer data from Page1 to Page0 */
            for (VarIdx = 0; VarIdx < NB_OF_VAR; VarIdx++)
            {
                if ((*(__IO uint16_t *)(PAGE0_BASE_ADDRESS + 6)) == VirtAddVarTab[VarIdx]) //加6的原因。每页前4字节保留。加6即有4个地址：0.2.4.6。0.2保留，4为数据，6为虚拟地址。
                {
                    x = VarIdx;
                }
                if (VarIdx != x) //地址中没有数据
                {
                    /* Read the last variables' updates */
                    ReadStatus = EE_ReadVariable(VirtAddVarTab[VarIdx], &DataVar); //读取地址VarIdx中数据，赋值给DataVar地址
                    /* In case variable corresponding to the virtual address was found */
                    if (ReadStatus != 0x1) //读取成功条件 ReadStatus==0
                    {
                        /* Transfer the variable to the Page0 */
                        EepromStatus = EE_VerifyPageFullWriteVariable(VirtAddVarTab[VarIdx], DataVar); //写数据到page0
                        /* If program operation was failed, a Flash error code is returned */
                        if (EepromStatus != FLASH_COMPLETE)
                        {
                            return EepromStatus;
                        }
                    }
                }
            }
            /* Mark Page0 as valid */
            FlashStatus = FLASH_ProgramHalfWord(PAGE0_BASE_ADDRESS + 2, VALID_PAGE_H);
            /* If program operation was failed, a Flash error code is returned */
            if (FlashStatus != FLASH_COMPLETE)
            {
                return FlashStatus;
            }
            /* Erase Page1 */
            FlashStatus = FLASH_ErasePage(PAGE1_BASE_ADDRESS);
            /* If erase operation was failed, a Flash error code is returned */
            if (FlashStatus != FLASH_COMPLETE)
            {
                return FlashStatus;
            }
        }
        else if (PageStatus1 == ERASED) /* Page0 receive, Page1 erased */
        {
            /* Erase Page1 */
            FlashStatus = FLASH_ErasePage(PAGE1_BASE_ADDRESS);
            /* If erase operation was failed, a Flash error code is returned */
            if (FlashStatus != FLASH_COMPLETE)
            {
                return FlashStatus;
            }
            /* Mark Page0 as valid */
            FlashStatus = FLASH_ProgramHalfWord(PAGE0_BASE_ADDRESS + 2, VALID_PAGE_H);
            /* If program operation was failed, a Flash error code is returned */
            if (FlashStatus != FLASH_COMPLETE)
            {
                return FlashStatus;
            }
        }
        else /* Invalid state -> format eeprom */
        {
            /* Erase both Page0 and Page1 and set Page0 as valid page */
            FlashStatus = EE_Format();
            /* If erase/program operation was failed, a Flash error code is returned */
            if (FlashStatus != FLASH_COMPLETE)
            {
                return FlashStatus;
            }
        }
        break;

    case VALID_PAGE:                   //page0为有效数据页
        if (PageStatus1 == VALID_PAGE) /* Invalid state -> format eeprom */
        {
            /* Erase both Page0 and Page1 and set Page0 as valid page */
            FlashStatus = EE_Format();
            /* If erase/program operation was failed, a Flash error code is returned */
            if (FlashStatus != FLASH_COMPLETE)
            {
                return FlashStatus;
            }
        }
        else if (PageStatus1 == ERASED) /* Page0 valid, Page1 erased */
        {
            /* Erase Page1 */
            FlashStatus = FLASH_ErasePage(PAGE1_BASE_ADDRESS);
            /* If erase operation was failed, a Flash error code is returned */
            if (FlashStatus != FLASH_COMPLETE)
            {
                return FlashStatus;
            }
        }
        else /* Page0 valid, Page1 receive */
        {
            /* Transfer data from Page0 to Page1 */
            for (VarIdx = 0; VarIdx < NB_OF_VAR; VarIdx++)
            {
                if ((*(__IO uint16_t *)(PAGE1_BASE_ADDRESS + 6)) == VirtAddVarTab[VarIdx])
                {
                    x = VarIdx;
                }
                if (VarIdx != x)
                {
                    /* Read the last variables' updates */
                    ReadStatus = EE_ReadVariable(VirtAddVarTab[VarIdx], &DataVar);
                    /* In case variable corresponding to the virtual address was found */
                    if (ReadStatus != 0x1)
                    {
                        /* Transfer the variable to the Page1 */
                        EepromStatus = EE_VerifyPageFullWriteVariable(VirtAddVarTab[VarIdx], DataVar);
                        /* If program operation was failed, a Flash error code is returned */
                        if (EepromStatus != FLASH_COMPLETE)
                        {
                            return EepromStatus;
                        }
                    }
                }
            }
            /* Mark Page1 as valid */
            FlashStatus = FLASH_ProgramHalfWord(PAGE1_BASE_ADDRESS + 2, VALID_PAGE_H);
            /* If program operation was failed, a Flash error code is returned */
            if (FlashStatus != FLASH_COMPLETE)
            {
                return FlashStatus;
            }
            /* Erase Page0 */
            FlashStatus = FLASH_ErasePage(PAGE0_BASE_ADDRESS);
            /* If erase operation was failed, a Flash error code is returned */
            if (FlashStatus != FLASH_COMPLETE)
            {
                return FlashStatus;
            }
        }
        break;

    default: /* Any other state -> format eeprom */
        /* Erase both Page0 and Page1 and set Page0 as valid page */
        FlashStatus = EE_Format();
        /* If erase/program operation was failed, a Flash error code is returned */
        if (FlashStatus != FLASH_COMPLETE)
        {
            return FlashStatus;
        }
        break;
    }

    return FLASH_COMPLETE;
}

/**
  * @brief  Returns the last stored variable data, if found, which correspond to
  *   the passed virtual address
  * @param  VirtAddress: Variable virtual address
  * @param  Data: Global variable contains the read variable value
  * @retval Success or error status:
  *           - 0: if variable was found
  *           - 1: if the variable was not found
  *           - NO_VALID_PAGE: if no valid page was found.
  */
uint16_t EE_ReadVariable(uint16_t VirtAddress, uint16_t *Data)
{
    uint16_t ValidPage = PAGE0;
    uint16_t AddressValue = 0x5555, ReadStatus = 1;
    uint32_t Address = 0x08010000, PageStartAddress = 0x08010000;

    /* Get active Page for read operation */
    ValidPage = EE_FindValidPage(READ_FROM_VALID_PAGE); //找到有效页

    /* Check if there is no valid page */
    if (ValidPage == NO_VALID_PAGE)
    {
        return NO_VALID_PAGE;
    }

    /* Get the valid Page start Address */
    PageStartAddress = (uint32_t)(EEPROM_START_ADDRESS + (uint32_t)(ValidPage * PAGE_SIZE)); //确定有效页初始地址

    /* Get the valid Page end Address */
    Address = (uint32_t)((EEPROM_START_ADDRESS - 2) + (uint32_t)((1 + ValidPage) * PAGE_SIZE)); //确定有效页结束地址

    /* Check each active page address starting from end */
    while (Address > (PageStartAddress + 2)) //地址从页最后后向前检索，搜索对应地址
    {
        /* Get the current location content to be compared with virtual address */
        AddressValue = (*(__IO uint16_t *)Address); //获得当前地址中的数据

        /* Compare the read address with the virtual address */
        if (AddressValue == VirtAddress) //地址中的数据与要搜索的地址数据对应
        {
            /* Get content of Address-2 which is variable value */
            *Data = (*(__IO uint16_t *)(Address - 2));

            /* In case variable value is read, reset ReadStatus flag */
            ReadStatus = 0;

            break;
        }
        else
        {
            /* Next address location */
            Address = Address - 4; //-4是因为半字（16位）写入，2字节数据  2字节地址
        }
    }

    /* Return ReadStatus value: (0: variable exist, 1: variable doesn't exist) */
    return ReadStatus;
}

/**
  * @brief  Writes/upadtes variable data in EEPROM.
  * @param  VirtAddress: Variable virtual address
  * @param  Data: 16 bit data to be written
  * @retval Success or error status:
  *           - FLASH_COMPLETE: on success
  *           - PAGE_FULL: if valid page is full
  *           - NO_VALID_PAGE: if no valid page was found
  *           - Flash error code: on write Flash error
  */
uint16_t EE_WriteVariable(uint16_t VirtAddress, uint16_t Data)
{
    uint16_t Status = 0;

    if (VirtAddress == 0xDDDD)
    {
        return PAGE_FULL;
    }

    /* Write the variable virtual address and value in the EEPROM */
    Status = EE_VerifyPageFullWriteVariable(VirtAddress, Data); //

    /* In case the EEPROM active page is full */
    if (Status == PAGE_FULL)
    {
        /* Perform Page transfer */
        Status = EE_PageTransfer(VirtAddress, Data);
    }

    /* Return last operation status */
    return Status;
}

uint16_t EE_WriteVariable_UsageCount(uint16_t VirtAddress, uint16_t Data)
{
    uint16_t Status = 0;

    /* Write the variable virtual address and value in the EEPROM */
    Status = EE_VerifyPageFullWriteVariable(VirtAddress, Data);

    /* In case the EEPROM active page is full */
    if (Status == PAGE_FULL)
    {
        /* Perform Page transfer */
        Status = EE_PageTransfer(VirtAddress, Data);
    }

    /* Return last operation status */
    return Status;
}

/**
  * @brief  Erases PAGE0 and PAGE1 and writes VALID_PAGE header to PAGE0
  * @param  None
  * @retval Status of the last operation (Flash write or erase) done during
  *         EEPROM formating
  */
static FLASH_Status EE_Format(void)
{
    FLASH_Status FlashStatus = FLASH_COMPLETE;

    /* Erase Page0 */
    FlashStatus = FLASH_ErasePage(PAGE0_BASE_ADDRESS);

    /* If erase operation was failed, a Flash error code is returned */
    if (FlashStatus != FLASH_COMPLETE)
    {
        return FlashStatus;
    }

    /* Set Page0 as valid page: Write VALID_PAGE at Page0 base address */
    FlashStatus = FLASH_ProgramHalfWord(PAGE0_BASE_ADDRESS, VALID_PAGE_L);
    FlashStatus = FLASH_ProgramHalfWord(PAGE0_BASE_ADDRESS + 2, VALID_PAGE_H);
    /* If program operation was failed, a Flash error code is returned */
    if (FlashStatus != FLASH_COMPLETE)
    {
        return FlashStatus;
    }

    /* Erase Page1 */
    FlashStatus = FLASH_ErasePage(PAGE1_BASE_ADDRESS);

    /* Return Page1 erase operation status */
    return FlashStatus;
}

/**
  * @brief  Find valid Page for write or read operation
  * @param  Operation: operation to achieve on the valid page.
  *   This parameter can be one of the following values:
  *     @arg READ_FROM_VALID_PAGE: read operation from valid page
  *     @arg WRITE_IN_VALID_PAGE: write operation from valid page
  * @retval Valid page number (PAGE0 or PAGE1) or NO_VALID_PAGE in case
  *   of no valid page was found
  */
static uint16_t EE_FindValidPage(uint8_t Operation)
{
    uint32_t PageStatus0 = 6, PageStatus1 = 6;

    /* Get Page0 actual status */
    PageStatus0 = (*(__IO uint32_t *)PAGE0_BASE_ADDRESS);

    /* Get Page1 actual status */
    PageStatus1 = (*(__IO uint32_t *)PAGE1_BASE_ADDRESS);

    /* Write or read operation */
    switch (Operation)
    {
    case WRITE_IN_VALID_PAGE: /* ---- Write operation ---- */
        if (PageStatus1 == VALID_PAGE)
        {
            /* Page0 receiving data */
            if (PageStatus0 == RECEIVE_DATA)
            {
                return PAGE0; /* Page0 valid */
            }
            else
            {
                return PAGE1; /* Page1 valid */
            }
        }
        else if (PageStatus0 == VALID_PAGE)
        {
            /* Page1 receiving data */
            if (PageStatus1 == RECEIVE_DATA)
            {
                return PAGE1; /* Page1 valid */
            }
            else
            {
                return PAGE0; /* Page0 valid */
            }
        }
        else
        {
            return NO_VALID_PAGE; /* No valid Page */
        }

    case READ_FROM_VALID_PAGE: /* ---- Read operation ---- */
        if (PageStatus0 == VALID_PAGE)
        {
            return PAGE0; /* Page0 valid */
        }
        else if (PageStatus1 == VALID_PAGE)
        {
            return PAGE1; /* Page1 valid */
        }
        else
        {
            return NO_VALID_PAGE; /* No valid Page */
        }

    default:
        return PAGE0; /* Page0 valid */
    }
}

/**
  * @brief  Verify if active page is full and Writes variable in EEPROM.
  * @param  VirtAddress: 16 bit virtual address of the variable
  * @param  Data: 16 bit data to be written as variable value
  * @retval Success or error status:
  *           - FLASH_COMPLETE: on success
  *           - PAGE_FULL: if valid page is full
  *           - NO_VALID_PAGE: if no valid page was found
  *           - Flash error code: on write Flash error
  */
static uint16_t EE_VerifyPageFullWriteVariable(uint16_t VirtAddress, uint16_t Data)
{
    FLASH_Status FlashStatus = FLASH_COMPLETE;
    uint16_t ValidPage = PAGE0;
    uint32_t Address = 0x08010000, PageEndAddress = 0x080107FF;

    /* Get valid Page for write operation */
    ValidPage = EE_FindValidPage(WRITE_IN_VALID_PAGE);

    /* Check if there is no valid page */
    if (ValidPage == NO_VALID_PAGE)
    {
        return NO_VALID_PAGE;
    }

    /* Get the valid Page start Address */
    Address = (uint32_t)(EEPROM_START_ADDRESS + (uint32_t)(ValidPage * PAGE_SIZE));

    /* Get the valid Page end Address */
    PageEndAddress = (uint32_t)((EEPROM_START_ADDRESS - 2) + (uint32_t)((1 + ValidPage) * PAGE_SIZE));

    /* Check each active page address starting from begining */
    while (Address < PageEndAddress)
    {
        /* Verify if Address and Address+2 contents are 0xFFFFFFFF */
        if ((*(__IO uint32_t *)Address) == 0xFFFFFFFF) //找到一个内容为空的地址
        {
            /* Set variable data */
            FlashStatus = FLASH_ProgramHalfWord(Address, Data);
            /* If program operation was failed, a Flash error code is returned */
            if (FlashStatus != FLASH_COMPLETE)
            {
                return FlashStatus;
            }
            /* Set variable virtual address */
            FlashStatus = FLASH_ProgramHalfWord(Address + 2, VirtAddress);
            /* Return program operation status */
            return FlashStatus;
        }
        else
        {
            /* Next address location */
            Address = Address + 4;
        }
    }

    /* Return PAGE_FULL in case the valid page is full */
    return PAGE_FULL;
}

/**
  * @brief  Transfers last updated variables data from the full Page to
  *   an empty one.
  * @param  VirtAddress: 16 bit virtual address of the variable
  * @param  Data: 16 bit data to be written as variable value
  * @retval Success or error status:
  *           - FLASH_COMPLETE: on success
  *           - PAGE_FULL: if valid page is full
  *           - NO_VALID_PAGE: if no valid page was found
  *           - Flash error code: on write Flash error
  */
static uint16_t EE_PageTransfer(uint16_t VirtAddress, uint16_t Data)
{
    FLASH_Status FlashStatus = FLASH_COMPLETE;
    uint32_t NewPageAddress = 0x080103FF, OldPageAddress = 0x08010000;
    uint16_t ValidPage = PAGE0, VarIdx = 0;
    uint16_t EepromStatus = 0, ReadStatus = 0;

    /* Get active Page for read operation */
    ValidPage = EE_FindValidPage(READ_FROM_VALID_PAGE);

    if (ValidPage == PAGE1) /* Page1 valid */
    {
        /* New page address where variable will be moved to */
        NewPageAddress = PAGE0_BASE_ADDRESS;

        /* Old page address where variable will be taken from */
        OldPageAddress = PAGE1_BASE_ADDRESS;
    }
    else if (ValidPage == PAGE0) /* Page0 valid */
    {
        /* New page address where variable will be moved to */
        NewPageAddress = PAGE1_BASE_ADDRESS;

        /* Old page address where variable will be taken from */
        OldPageAddress = PAGE0_BASE_ADDRESS;
    }
    else
    {
        return NO_VALID_PAGE; /* No valid Page */
    }

    /* Set the new Page status to RECEIVE_DATA status */
    FlashStatus = FLASH_ProgramHalfWord(NewPageAddress, 0xeeee); //RECEIVE_DATA 8L
    /* If program operation was failed, a Flash error code is returned */
    if (FlashStatus != FLASH_COMPLETE)
    {
        return FlashStatus;
    }

    /* Write the variable passed as parameter in the new active page */
    EepromStatus = EE_VerifyPageFullWriteVariable(VirtAddress, Data); //把当前要写入的新数据先转至空白页，后进行下面的旧数据转移
    /* If program operation was failed, a Flash error code is returned */
    if (EepromStatus != FLASH_COMPLETE)
    {
        return EepromStatus;
    }

    /* Transfer process: transfer variables from old to the new active page */
    for (VarIdx = 0; VarIdx < NB_OF_VAR; VarIdx++)
    {
        if (VirtAddVarTab[VarIdx] != VirtAddress) /* Check each variable except the one passed as parameter */ //该虚拟地址对应的新数据在上一步已经转移，所以剔除该虚拟地址的旧数据
        {
            /* Read the other last variable updates */
            ReadStatus = EE_ReadVariable(VirtAddVarTab[VarIdx], &DataVar);
            /* In case variable corresponding to the virtual address was found */
            if (ReadStatus != 0x1)
            {
                /* Transfer the variable to the new active page */
                EepromStatus = EE_VerifyPageFullWriteVariable(VirtAddVarTab[VarIdx], DataVar);
                /* If program operation was failed, a Flash error code is returned */
                if (EepromStatus != FLASH_COMPLETE)
                {
                    return EepromStatus;
                }
            }
        }
    }

    /* Erase the old Page: Set old Page status to ERASED status */
    FlashStatus = FLASH_ErasePage(OldPageAddress);
    /* If erase operation was failed, a Flash error code is returned */
    if (FlashStatus != FLASH_COMPLETE)
    {
        return FlashStatus;
    }
    /* Set new Page status to VALID_PAGE status */
    FlashStatus = FLASH_ProgramHalfWord(NewPageAddress + 2, VALID_PAGE_H);
    /* If program operation was failed, a Flash error code is returned */
    if (FlashStatus != FLASH_COMPLETE)
    {
        return FlashStatus;
    }

    /* Return last operation flash status */
    return FlashStatus;
}

/**
  * @}
  */

/************************ (C) COPYRIGHT LCMicroelectronics *****END OF FILE****/
