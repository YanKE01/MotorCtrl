#ifndef SOURCE_USER_INTERRUPT_H_
#define SOURCE_USER_INTERRUPT_H_

#include "lcm32f037_lib.h"
#include "UserIncludes.h"

#if defined(EXPORT_USER_INTERRUPT_H)
  #define EXTERN
#else
  #define EXTERN extern
#endif
	
EXTERN void DMAC_CH1_2_Handler(void);
EXTERN void SysTick_Handler(void);
EXTERN void TIM1_NON_CC_Handler(void);//±È½ÏÆ÷ÖÐ¶Ï
EXTERN void UI_vADC12Interrupt(void);	
EXTERN void UI_vTIM1BRKInterrupt(void);
EXTERN void UI_vTIM1UPInterrupt(void);
	
#undef EXTERN
#endif
	