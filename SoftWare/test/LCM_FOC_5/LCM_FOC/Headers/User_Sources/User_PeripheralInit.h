#ifndef SOURCE_USER_PERIPHERALINIT_H_
#define SOURCE_USER_PERIPHERALINIT_H_

#include "lcm32f037_lib.h"
#include "UserIncludes.h"

#if defined(EXPORT_USER_PERIPHERALINIT_H_)
  #define EXTERN
#else
  #define EXTERN extern
#endif
	
/****	 Pattern type is center aligned  ****/
#define UP_PWM_PRSC ((u8)0)
			/* Resolution: 1Hz */                            
#define UP_PWM_PERIOD 	((u16) (UPDS_CKTIM / (u32)(2 * UPDS_PWM_FREQ *(UP_PWM_PRSC+1)))) 	
#define UP_PWM_PERIOD2 	((u16) (UPDS_CKTIM / (u32)(2 * UPDS_PWM_FREQ2 *(UP_PWM_PRSC+1)))) 	
////////////////////////////// Deadtime Value /////////////////////////////////
#define UP_DEADTIME  (u16)((unsigned long long)UPDS_CKTIM/2 \
				*(unsigned long long)UPDS_DEADTIME_NS/1000000000uL) 

#define UP_DA_PWM_PERIOD ((u16) (UPDS_CKTIM / (u32)(2 * UPDS_DA_PWM_FREQ *(UP_PWM_PRSC+1)))) 				
				/*********************** CURRENT REGULATION PARAMETERS ************************/

/****	ADC IRQ-HANDLER frequency, related to PWM  ****/
#define UP_REP_RATE (1)  // (N.b): Internal current loop is performed every 
                      //             (REP_RATE + 1)/(2*PWM_FREQ) seconds.
                      // REP_RATE has to be an odd number in case of three-shunt
                      // current reading; this limitation doesn't apply to ICS
	
EXTERN 	vu32  ADCConvertedRawData[ADC_SIZE];
EXTERN	TIM_TimeBaseInitTypeDef  	TIM_TimeBaseStructure;
EXTERN	TIM_OCInitTypeDef  				TIM_OCInitStructure;
EXTERN	TIM_BDTRInitTypeDef				TIM_BDTRInitStructure;	


EXTERN void UP_vDeviceInit(void);
EXTERN void UP_vGPIOConfiguration(void);
EXTERN void UP_vADCConfiguration(void);
EXTERN void UP_vOpa0_config(void);
EXTERN void UP_vOpa1_config(void);
EXTERN void UP_vOpa2_config(void);
EXTERN void	UP_vOPA012Config(void);
EXTERN void UP_vTimerConfiguration(void);
EXTERN void UP_vUART_Config(void);
EXTERN void UP_vDAC1_5_Config(void);
EXTERN void UP_vACMPconfiguration(void);
EXTERN void UP_vPeriphClockCmdInit(void);
EXTERN void UP_vBreakEnable(void);
EXTERN void UP_vBreakDisable(void);



	
	
#undef EXTERN
#endif
