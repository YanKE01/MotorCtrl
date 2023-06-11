#include "lcm32f037_conf.h"
#include "lcm32f037.h"
#include "lcm32f037_rcc.h"
#include "lcm32f037_flash.h"
#include "lcm32f037_gpio.h"
#include "lcm32f037_uart.h"
#include "lcm32f037_exti.h"
#include "lcm32f037_wt.h"
/**
 ******************************************************************************
 * @function: wt��ʱ����WT_BUZ
 * @attention:
 ******************************************************************************/
void GPIO_Config()
{

	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8; // PA8�۲�
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_0);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource4, GPIO_AF_5); // WT_BUZ   pA4
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_5); // WT_nBUZ   pA5
}

void WT_Cfg()
{
	WT_InitTypeDef WT_InitStruct;

	RCC_LSICmd(ENABLE);					  //ʹ���ڲ�RCL
	RCC_WTCLKConfig(RCC_WTCLKSource_LSI); //����WTʱ��(WTCLK),ѡ��LSI��ΪWTʱ��
	RCC_WTCLKCmd(ENABLE);				  // ʹ��WTʱ��

	WT_SetCounter(WT, 0X55); //�ݼ�����������T8ֵ

	WT_InitStruct.WT_BZOUT = WT_BZOUT_Hight;			  //����������ߵ�Ƶ��ѡ��
	WT_InitStruct.WT_Interrupt = WT_Interrupt_T8DOWN;	  // WT�ж�Դѡ��
	WT_InitStruct.WT_Outfrequency = WT_Outfrequency_1024; //���������Ƶ��ѡ��
	WT_InitStruct.WT_T8frequency = WT_T8frequency_4096;	  // T8��ʱ��ʱ��Դѡ��
	WT_InitStruct.WT_T8State = WT_T8State_Enable;		  // T8��ʱ��ʹ��
	WT_InitStruct.WT_WTState = WT_WTState_Enable;		  // WTʹ��λ
	WT_Init(WT, &WT_InitStruct);
}

void EXTI_Config()
{
	EXTI_InitTypeDef EXTI_InitStruct;

	EXTI_InitStruct.EXTI_Line = EXTI_Line17;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStruct);

	NVIC_ClearPendingIRQ(WT_IRQn);
	NVIC_EnableIRQ(WT_IRQn);
}
void OSCL_Init()
{
	OSCH_GPIO_INIT(); //����Ÿ���
	chipctrl_access();
	CHIPCTRL->BDCR_b.OSCL_EN = 1; //�����ⲿ���پ���(LSE),ʹ��������پ���
	__dekey();
	while (!(CHIPCTRL->STS & CHIPCTRL_STS_OSCL_STB_Msk)) //�ȴ����پ������
		;
}
int main()
{
	SystemInit();
	SetSysClock(); //��Ƶ����
	//	OSCL_Init();

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_EXTI, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	GPIO_Config();
	mco_set(4, 0); // PA8���OSCL

	EXTI_Config();
	WT_Cfg();
	while (1)
		;
}

void WT_Handler(void)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_12, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_12)));
	WT_ClearITPendingBit(WT_FLAG_IT);
	EXTI_ClearITPendingBit(EXTI_Line17);
}
