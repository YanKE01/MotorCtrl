#include "lcm32f037.h"
#include "lcm32f037_rcc.h"
#include "lcm32f037_gpio.h"
#include "lcm32f037_exti.h"
#include "lcm32f037_adc.h"
#include "lcm32f037_pwr.h"
/**
 ******************************************************************************
 * @function:  u-stop : 3ua
 * @attention:
 *
 *
 *
 ******************************************************************************/
uint8_t PWR_FLG;

void delay(uint32_t dly)
{
	volatile uint32_t i = 0;
	while (i++ < dly)
		;
}
void EXTI_Config()
{
	EXTI_InitTypeDef EXTI_InitStruct;

	EXTI_InitStruct.EXTI_Line = EXTI_Line9;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStruct);
}

void GPIOA_CONFIG()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_10 | GPIO_Pin_12 | GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}
void GPIOA3_CONFIG()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}
void GPIOA9_Exti()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}
void GPIOA11_GND()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}
void GPIOB_CONFIG()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void GPIOF_CONFIG()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOF, &GPIO_InitStruct);
}
void GPIOF3_CONFIG()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOF, &GPIO_InitStruct);
}
void GPIO_VBG_OUT()
{
	gpio_ana_mode_set(GPIOA, 0, 0, 1);
	chipctrl_access();
	CHIPCTRL->PWR_CFG = 0x00080000;
}
int main()
{
	SystemInit();
	SetSysClock(); //主频配置
	chipctrl_access();
	CHIPCTRL->PWR_CFG = 0x00000000;
	__dekey();
	sysctrl_access();
	SYSCTRL->ClkEnR0 = 0x00000000;
	__dekey();
	sysctrl_access();
	SYSCTRL->ClkEnR2 &= ~(1 << 5);
	__dekey();

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_EXTI, ENABLE);

	NVIC_EnableIRQ(EXTI4_15_IRQn);
	EXTI_Config();

	GPIOB_CONFIG();
	GPIOF_CONFIG();
	GPIOF3_CONFIG();
	GPIOA3_CONFIG();
	GPIOA9_Exti();
	GPIOA_CONFIG();
	GPIOA11_GND();

	PWR_FLG = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11);

	if (!PWR_FLG) // PA11接地，上电复位或者硬件复位后进入低功耗模式
	{
		//		GPIO_PinAFConfig(GPIOA,GPIO_PinSource13,GPIO_AF_2);
		//		GPIO_PinAFConfig(GPIOA,GPIO_PinSource14,GPIO_AF_2);
		PWR_LPVRConfig(PWR_VSEL_1V1);
		PWR_EnterUR_STOPMode(0, PWR_STOPEntry_WFI);
	}
	while (1)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_3);
		delay(1000);
		GPIO_ResetBits(GPIOA, GPIO_Pin_3);
		delay(1000);
	}
}
void EXTI4_15_Handler()
{
	EXTI_ClearITPendingBit(EXTI_Line9); // EXTI_Line9
}
