/**
 ******************************************************************************
 * @file    lcm32f037_pwr.c
 * @author  MCD Application Team
 * @version V1.0.0
 * @date    2021-05-21
 * @brief   This file provides all the pwr emulation firmware functions.
 ******************************************************************************/
/**
 ******************************************************************************
 * @attention:
 *
 *
 *
 *
 ******************************************************************************/
#include "lcm32f037_pwr.h"

/*--------------------------------------------------------------------------------------------
   WakeUpPin enable for  mcu lowpower mode
  --------------------------------------------------------------------------------------------*/
//引脚唤醒使能
void PWR_WakeUpPinCmd(uint32_t PWR_WakeUpPin, FunctionalState NewState)
{

	if (NewState != ENABLE)
	{
		chipctrl_access();
		CHIPCTRL->WKCR &= ~PWR_WakeUpPin;
		__dekey();
	}
	else
	{
		chipctrl_access();
		CHIPCTRL->WKCR |= PWR_WakeUpPin;
		__dekey();
	}
}

/*--------------------------------------------------------------------------------------------
sleepmode cmd :  mcu Working current about 400ua
  --------------------------------------------------------------------------------------------*/

void PWR_EnterSleepMode(uint32_t PWR_SLEEPEntry)
{
	assert_param(IS_PWR_SLEEP_ENTRY(PWR_SLEEPEntry));

	/* Clear SLEEPDEEP bit of Cortex-M0 System Control Register */
	SCB->SCR &= (uint32_t) ~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);

	/* Select SLEEP mode entry -------------------------------------------------*/
	if (PWR_SLEEPEntry == PWR_SLEEPEntry_WFI)
	{
		__WFI();
	}
	else
	{
		__WFE();
	}
}

/*--------------------------------------------------------------------------------------------
ur_stopmode cmd :  mcu Working current about 6ua
  --------------------------------------------------------------------------------------------*/
void PWR_EnterUR_STOPMode(uint32_t PWR_Regulator, uint32_t PWR_STOPEntry)
{
	/* Check the parameters */
	// assert_param(IS_PWR_REGULATOR(PWR_Regulator));
	// assert_param(IS_PWR_STOP_ENTRY(PWR_STOPEntry));

	// deep-sleep

	PWR_LowPowerCmd(ENABLE);			 // PUMEN
	PWR_FlashPowerDownDeepSleep(ENABLE); // FPDS
	PWR_PowerDownDeepSleep(DISABLE);	 // PDDS  standy cpu
	PWR_LowPowerDeepSleep(ENABLE);		 // LPDS  内核LDO
	PWR_UltraLowPowerDeepSleep(ENABLE);	 // ULPDS  使能超低功耗
	/* Select STOP mode entry --------------------------------------------------*/

	SCB->SCR |= ((uint32_t)SCB_SCR_SLEEPDEEP_Msk);

	if (PWR_STOPEntry == PWR_STOPEntry_WFI)
	{
		/* Request Wait For Interrupt */
		__WFI();
		SCB->SCR &= (uint32_t) ~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);
	}
	else
	{
		/* Request Wait For Event */
		__WFE();
		SCB->SCR &= (uint32_t) ~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);
	}

	/* Reset SLEEPDEEP bit of Cortex System Control Register */
}

/*--------------------------------------------------------------------------------------------
stopmode cmd :  mcu Working current about 100ua
  --------------------------------------------------------------------------------------------*/
void PWR_EnterSTOPMode(uint32_t PWR_Regulator, uint32_t PWR_STOPEntry)
{

	PWR_LowPowerCmd(ENABLE);
	PWR_FlashPowerDownDeepSleep(ENABLE);
	PWR_PowerDownDeepSleep(DISABLE);
	PWR_LowPowerDeepSleep(DISABLE);
	PWR_UltraLowPowerDeepSleep(DISABLE);

	SCB->SCR |= ((uint32_t)SCB_SCR_SLEEPDEEP_Msk);
	/* Select STOP mode entry --------------------------------------------------*/
	if (PWR_STOPEntry == PWR_STOPEntry_WFI)
	{
		/* Request Wait For Interrupt */
		__WFI();
	}
	else
	{
		/* Request Wait For Event */
		__WFE();
	}
	/* Reset SLEEPDEEP bit of Cortex System Control Register */
	SCB->SCR &= (uint32_t) ~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);
}

/*--------------------------------------------------------------------------------------------
lowpower stopmode cmd :  mcu Working current about 100ua
  --------------------------------------------------------------------------------------------*/
void PWR_EnterLowPowerSTOPMode(uint32_t PWR_Regulator, uint32_t PWR_STOPEntry)
{

	PWR_LowPowerCmd(ENABLE);
	PWR_FlashPowerDownDeepSleep(ENABLE);
	PWR_PowerDownDeepSleep(DISABLE);
	PWR_LowPowerDeepSleep(ENABLE);
	PWR_UltraLowPowerDeepSleep(DISABLE);

	SCB->SCR |= ((uint32_t)SCB_SCR_SLEEPDEEP_Msk);
	/* Select STOP mode entry --------------------------------------------------*/
	if (PWR_STOPEntry == PWR_STOPEntry_WFI)
	{
		/* Request Wait For Interrupt */
		__WFI();
	}
	else
	{
		/* Request Wait For Event */
		__WFE();
	}
	/* Reset SLEEPDEEP bit of Cortex System Control Register */
	SCB->SCR &= (uint32_t) ~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);
}

/*--------------------------------------------------------------------------------------------
standyby mode cmd :  mcu Working current about 30ua
  --------------------------------------------------------------------------------------------*/
void PWR_EnterSTANDBYMode(void)
{ /* Check the parameters */

	// deep-sleep

	PWR_LowPowerCmd(ENABLE);			 //		CHIPCTRL->CR_b.PMUEN=1;
	PWR_FlashPowerDownDeepSleep(ENABLE); //		CHIPCTRL->CR_b.FPDS=1;
	PWR_LowPowerDeepSleep(ENABLE);		 //	  CHIPCTRL->CR_b.LPDS=1;
	PWR_UltraLowPowerDeepSleep(ENABLE);	 //		CHIPCTRL->CR_b.ULPDS=1;
	PWR_PowerDownDeepSleep(ENABLE);		 //		CHIPCTRL->CR_b.PDDS=1;
	SCB->SCR |= ((uint32_t)SCB_SCR_SLEEPDEEP_Msk);

	/* Select STOP mode entry --------------------------------------------------*/
	/* Request Wait For Interrupt */
	__WFI();
	/* Reset SLEEPDEEP bit of Cortex System Control Register */
	//  SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);
}

/*--------------------------------------------------------------------------------------------
get flag for pwrlvd
  --------------------------------------------------------------------------------------------*/
FlagStatus PWR_GetFlagStatus(uint32_t PWR_FLAG)
{
	assert_param(IS_PWR_FLAG(PWR_FLAG));

	if (PWR_FLAG != PWR_LVD)
	{
		if ((PWR_FLAG & (CHIPCTRL->WKSR)) != RESET)
			return SET;
		return RESET;
	}
	else
	{
		if ((PWR_FLAG & (CHIPCTRL->STS)) != RESET)
			return SET;
		return RESET;
	}
}

/*--------------------------------------------------------------------------------------------
clear flag
  --------------------------------------------------------------------------------------------*/
void PWR_ClearFlag(uint32_t PWR_Flag)
{
	assert_param(IS_PWR_FLAG(PWR_FLAG));
	chipctrl_access();
	CHIPCTRL->WKSR |= PWR_Flag;
	__dekey();
}

/*--------------------------------------------------------------------------------------------
vrh_set
  --------------------------------------------------------------------------------------------*/
void PWR_VRHConfig(uint32_t PWR_VRHLevel)
{

	// assert(IS_VRH_LEVEL(PWR_VRHLevel));
	if (PWR_VRHLevel == PWR_VRHLevel_2v5)
	{
		chipctrl_access();
		CHIPCTRL->PWR_CFG_b.VBUF_SEL = 0;
		chipctrl_access();
		CHIPCTRL->PWR_CFG_b.VRH_SEL = PWR_VRHLevel_2v5;
	}
	else
	{
		chipctrl_access();
		CHIPCTRL->PWR_CFG_b.VBUF_SEL = 1;
		chipctrl_access();
		CHIPCTRL->PWR_CFG_b.VRH_SEL = PWR_VRHLevel_4v;
	}
	__dekey();
}

/*--------------------------------------------------------------------------------------------
LVD set level
  --------------------------------------------------------------------------------------------*/
void PWR_LVDConfig(uint32_t IE, uint32_t PWR_LVDLevel)
{
	assert_param(IS_PWR_LVDIE(IE));
	assert_param(IS_PWR_LVDLevel(PWR_LVDLevel));
	if (!IE) // if internal
	{
		chipctrl_access();
		CHIPCTRL->PWR_CFG_b.LVDES = 0;
		chipctrl_access();
		CHIPCTRL->PWR_CFG_b.LVDS = PWR_LVDLevel;
	}
	else
	{
		chipctrl_access();
		CHIPCTRL->PWR_CFG_b.LVDES = 1;
		chipctrl_access();
		CHIPCTRL->PWR_CFG_b.LVDS = PWR_LVDLevel;
	}
	__dekey();
}

/*--------------------------------------------------------------------------------------------
lvd enable
  --------------------------------------------------------------------------------------------*/
void PWR_LVDCmd(FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		chipctrl_access();
		CHIPCTRL->PWR_CFG_b.LVDEN = 1;
	}
	else
	{
		chipctrl_access();
		CHIPCTRL->PWR_CFG_b.LVDEN = 0;
	}
	__dekey();
}

/*--------------------------------------------------------------------------------------------
lvr set level
  --------------------------------------------------------------------------------------------*/
void PWR_LVRConfig(uint32_t PWR_LVRLevel)
{
	assert_param(IS_LVR_Level(PWR_LVRLevel));

	chipctrl_access();
	CHIPCTRL->PWR_CFG_b.LVRS = PWR_LVRLevel;
	__dekey();
}

/*--------------------------------------------------------------------------------------------
lvr enable
  --------------------------------------------------------------------------------------------*/
void PWR_LVRCmd(FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		chipctrl_access();
		CHIPCTRL->PWR_CFG_b.LVREN = 1;
	}
	else
	{
		chipctrl_access();
		CHIPCTRL->PWR_CFG_b.LVREN = 0;
	}
	__dekey();
}

/*--------------------------------------------------------------------------------------------
clear lvr flag
  --------------------------------------------------------------------------------------------*/
void PWR_LVRClearFlag(void)
{
	assert_param();
	chipctrl_access();
	CHIPCTRL->RST_CSR_b.LVR_FLAG = 1;
	__dekey();
}
/*--------------------------------------------------------------------------------------------
clear lvr flag
  --------------------------------------------------------------------------------------------*/
void PWR_POR_PDRClearFlag(void)
{
	assert_param();
	chipctrl_access();
	CHIPCTRL->RST_CSR_b.POR_FLAG = 1;
	__dekey();
}
/*--------------------------------------------------------------------------------------------
lvd enabled,the register cant change
  --------------------------------------------------------------------------------------------*/
void PWR_LVDRegisterLock(void)
{
	chipctrl_access();
	CHIPCTRL->PWR_CFG_b.LVREN = 1;
	__dekey();
}

/*--------------------------------------------------------------------------------------------
上电复位模块使能
  --------------------------------------------------------------------------------------------*/
void PWR_PORCmd(FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		chipctrl_access();
		CHIPCTRL->BDCR_b.POREN0 = 1;
	}
	else
	{
		chipctrl_access();
		CHIPCTRL->BDCR_b.POREN0 = 0;
	}
	__dekey();
}

/*--------------------------------------------------------------------------------------------
掉电复位模块使能
  --------------------------------------------------------------------------------------------*/
void PWR_PDRCmd(FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		chipctrl_access();
		CHIPCTRL->BDCR_b.POREN1 = 1;
	}
	else
	{
		chipctrl_access();
		CHIPCTRL->BDCR_b.POREN1 = 0;
	}
	__dekey();
}

/*--------------------------------------------------------------------------------------------
低功耗调压器LPVR 电压选择
  --------------------------------------------------------------------------------------------*/
void PWR_LPVRConfig(uint32_t PWR_VSEL)
{
	chipctrl_access();
	CHIPCTRL->LDOCR_b.VSEL = PWR_VSEL;
	__dekey();
}

/*--------------------------------------------------------------------------------------------
 LDO 输出驱动电流能力模式选择
  --------------------------------------------------------------------------------------------*/
void PWR_LDODriverLevel(uint32_t PWR_DRV)
{

	chipctrl_access();
	CHIPCTRL->LDOCR_b.DRV = PWR_DRV;
	__dekey();
}

/*--------------------------------------------------------------------------------------------
lpLDO 初始化
  --------------------------------------------------------------------------------------------*/
void PWR_LDOConfig(uint32_t IE)
{
	assert_param(IS_PWR_LDO_IE);
	if (IE != PWR_LDOExternal)
	{
		chipctrl_access();
		CHIPCTRL->LDOCR_b.DRV = 0;
	}
	else
	{
		chipctrl_access();
		CHIPCTRL->LDOCR_b.DRV = 1;
	}
	__dekey();
}

//关于低功耗模式的进入的相关配置
void PWR_UltraLowPowerDeepSleep(FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		chipctrl_access();
		CHIPCTRL->CR_b.ULPDS = 1;
	}
	else
	{
		chipctrl_access();
		CHIPCTRL->CR_b.ULPDS = 0;
	}
	__dekey();
}

/*--------------------------------------------------------------------------------------------
flash 进入深度掉电模式
  --------------------------------------------------------------------------------------------*/
void PWR_FlashPowerDownDeepSleep(FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		chipctrl_access();
		CHIPCTRL->CR_b.FPDS = 1;
	}
	else
	{
		chipctrl_access();
		CHIPCTRL->CR_b.FPDS = 0;
	}
	__dekey();
}

/*--------------------------------------------------------------------------------------------
低功耗模式使能
  --------------------------------------------------------------------------------------------*/

void PWR_LowPowerCmd(FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		chipctrl_access();
		CHIPCTRL->CR_b.PMUEN = 1;
	}
	else
	{
		chipctrl_access();
		CHIPCTRL->CR_b.PMUEN = 0;
	}
	__dekey();
}

/*--------------------------------------------------------------------------------------------
cpu深度掉电模式 使能wakeuppin
  --------------------------------------------------------------------------------------------*/
void PWR_PowerDownDeepSleep(FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		chipctrl_access();
		CHIPCTRL->WKCR_b.EWUP0 = 1;
		chipctrl_access();
		CHIPCTRL->CR_b.PDDS = 1;
	}
	else
	{
		chipctrl_access();
		CHIPCTRL->CR_b.PDDS = 0;
	}
	__dekey();
}

/*--------------------------------------------------------------------------------------------
LPDS  ENABLE
  --------------------------------------------------------------------------------------------*/
void PWR_LowPowerDeepSleep(FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		chipctrl_access();
		CHIPCTRL->CR_b.LPDS = 1;
	}
	else
	{
		chipctrl_access();
		CHIPCTRL->CR_b.LPDS = 0;
	}
	__dekey();
}

/*--------------------------------------------------------------------------------------------
LVR  LVD 使能初始化
  --------------------------------------------------------------------------------------------*/
void Power_Init()
{
	chipctrl_access();
	CHIPCTRL->PWR_CFG_b.LVREN = 0;
	chipctrl_access();
	CHIPCTRL->PWR_CFG_b.LVDEN = 0;
	__dekey();
}
