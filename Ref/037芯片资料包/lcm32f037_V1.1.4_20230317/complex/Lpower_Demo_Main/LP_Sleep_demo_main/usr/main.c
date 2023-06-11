#include "lcm32f037.h"
#include "lcm32f037_rcc.h"
#include "lcm32f037_gpio.h"
#include "lcm32f037_exti.h"
#include "lcm32f037_adc.h"
#include "lcm32f037_pwr.h"
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
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
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
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOF, &GPIO_InitStruct);
}

void EXTI18_Config()
{
	EXTI_InitTypeDef EXTI_InitStruct;
	EXTI_ClearITPendingBit(EXTI_Line18);

	EXTI_InitStruct.EXTI_Line = EXTI_Line18;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStruct);
}

void System_Init()
{
	chipctrl_access();
	CHIPCTRL->PWR_CFG = 0x00040000;
	__dekey();
	sysctrl_access();
	SYSCTRL->ClkEnR0 = 0x00000000;
	__dekey();
	sysctrl_access();
	SYSCTRL->ClkEnR2 &= ~(1 << 5);
	__dekey();
}
int main()
{
	//System_Init();

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_EXTI, ENABLE);

	NVIC_EnableIRQ(EXTI4_15_IRQn);
	EXTI_Config();

	GPIOA_CONFIG();
	GPIOA3_CONFIG();
	GPIOB_CONFIG();
	GPIOF_CONFIG();

	PWR_FLG = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11);
	if (!PWR_FLG) //PA11接地，上电复位或者硬件复位后进入低功耗模式
	{
		PWR_EnterSleepMode(PWR_STOPEntry_WFI);
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
	EXTI_ClearITPendingBit(EXTI_Line9); //EXTI_Line9
}
