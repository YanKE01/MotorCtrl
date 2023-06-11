#ifndef SOURCE_USER_NVIC_H_
#define SOURCE_USER_NVIC_H_

#include "lcm32f037_lib.h"
#include "UserIncludes.h"

#if defined(EXPORT_USER_NVIC_H)
  #define EXTERN
#else
  #define EXTERN extern
#endif
	
	
#define ADC_PRE_EMPTION_PRIORITY 0
#define ADC_SUB_PRIORITY 0

#define BRK_PRE_EMPTION_PRIORITY 0
#define BRK_SUB_PRIORITY 0

#define TIM1_UP_PRE_EMPTION_PRIORITY 1
#define TIM1_UP_SUB_PRIORITY 0

#define USART3_PRE_EMPTION_PRIORITY 3
#define USART3_SUB_PRIORITY 0

#define DMA1_PRE_EMPTION_PRIORITY 2
#define DMA1_SUB_PRIORITY 0

#define LOW_SIDE_POLARITY  TIM_OCIdleState_Reset

#define PWM2_MODE 0
#define PWM1_MODE 1
	
	
	
	
	
	
	
EXTERN void User_vNVICConfiguration(void);
EXTERN void User_vNVICFlashOrRam(void);
EXTERN void User_vUsart3IRQHandler(void);
	
#undef EXTERN
#endif
