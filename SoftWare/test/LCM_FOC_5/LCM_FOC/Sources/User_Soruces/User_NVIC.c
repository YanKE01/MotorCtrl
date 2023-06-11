#define EXPORT_USER_NVIC_H
	#include "User_NVIC.h"
#undef EXPORT_USER_NVIC_H


void User_vNVICConfiguration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_ClearPendingIRQ(DMAC_CH1_2_IRQn);
	NVIC_EnableIRQ(DMAC_CH1_2_IRQn);
	NVIC_ClearPendingIRQ(TIM1_NON_CC_IRQn);
	NVIC_EnableIRQ(TIM1_NON_CC_IRQn);
 
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_NON_CC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = DMAC_CH1_2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = SysTick_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_ClearPendingIRQ(UART0_IRQn);
	NVIC_InitStructure.NVIC_IRQChannel = UART0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}

