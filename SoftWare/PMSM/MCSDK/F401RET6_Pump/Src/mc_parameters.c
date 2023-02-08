
/**
  ******************************************************************************
  * @file    mc_parameters.c
  * @author  Motor Control SDK Team, ST Microelectronics
  * @brief   This file provides definitions of HW parameters specific to the
  *          configuration of the subsystem.
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
//cstat -MISRAC2012-Rule-21.1
#include "main.h" //cstat !MISRAC2012-Rule-21.1
//cstat +MISRAC2012-Rule-21.1
#include "parameters_conversion.h"
#include "mc_parameters.h"
#include "r3_1_f4xx_pwm_curr_fdbk.h"

/* USER CODE BEGIN Additional include */

/* USER CODE END Additional include */

#define FREQ_RATIO 1                /* Dummy value for single drive */
#define FREQ_RELATION HIGHEST_FREQ  /* Dummy value for single drive */

  /**
  * @brief  Current sensor parameters Motor 1 - three shunt - STM32F401x8
  */
R3_1_Params_t R3_1_ParamsM1 =
{
/* Current reading A/D Conversions initialization -----------------------------*/
  .ADCx = ADC1,

/* PWM generation parameters --------------------------------------------------*/
  .RepetitionCounter = REP_COUNTER,
  .hTafter            = TW_AFTER,
  .hTbefore           = TW_BEFORE_R3_1,
  .TIMx               = TIM1,
  .Tsampling                  = (uint16_t)SAMPLING_TIME,
  .Tcase2                     = (uint16_t)SAMPLING_TIME + (uint16_t)TDEAD + (uint16_t)TRISE,
  .Tcase3                     = ((uint16_t)TDEAD + (uint16_t)TNOISE + (uint16_t)SAMPLING_TIME)/2u,

/* PWM Driving signals initialization ----------------------------------------*/
  .LowSideOutputs = (LowSideOutputsFunction_t)LOW_SIDE_SIGNALS_ENABLING,
  .pwm_en_u_port = MC_NULL,
  .pwm_en_u_pin  = (uint16_t) 0,
  .pwm_en_v_port = MC_NULL,
  .pwm_en_v_pin  = (uint16_t) 0,
  .pwm_en_w_port = MC_NULL,
  .pwm_en_w_pin  = (uint16_t) 0,

  .ADCConfig = {
                ( uint32_t )( MC_ADC_CHANNEL_12<<ADC_JSQR_JSQ3_Pos ) | MC_ADC_CHANNEL_13<<ADC_JSQR_JSQ4_Pos | 1<<ADC_JSQR_JL_Pos,
                ( uint32_t )( MC_ADC_CHANNEL_10<<ADC_JSQR_JSQ3_Pos ) | MC_ADC_CHANNEL_13<<ADC_JSQR_JSQ4_Pos | 1<<ADC_JSQR_JL_Pos,
                ( uint32_t )( MC_ADC_CHANNEL_13<<ADC_JSQR_JSQ3_Pos ) | MC_ADC_CHANNEL_10<<ADC_JSQR_JSQ4_Pos | 1<<ADC_JSQR_JL_Pos,
                ( uint32_t )( MC_ADC_CHANNEL_12<<ADC_JSQR_JSQ3_Pos ) | MC_ADC_CHANNEL_10<<ADC_JSQR_JSQ4_Pos | 1<<ADC_JSQR_JL_Pos,
                ( uint32_t )( MC_ADC_CHANNEL_10<<ADC_JSQR_JSQ3_Pos ) | MC_ADC_CHANNEL_12<<ADC_JSQR_JSQ4_Pos | 1<<ADC_JSQR_JL_Pos,
                ( uint32_t )( MC_ADC_CHANNEL_13<<ADC_JSQR_JSQ3_Pos ) | MC_ADC_CHANNEL_12<<ADC_JSQR_JSQ4_Pos | 1<<ADC_JSQR_JL_Pos,
  },

  .ADCDataReg1 = {
                   &ADC1->JDR1,
                   &ADC1->JDR1,
                   &ADC1->JDR2,
                   &ADC1->JDR2,
                   &ADC1->JDR1,
                   &ADC1->JDR2,
  },
  .ADCDataReg2 = {
                   &ADC1->JDR2,
                   &ADC1->JDR2,
                   &ADC1->JDR1,
                   &ADC1->JDR1,
                   &ADC1->JDR2,
                   &ADC1->JDR1,
  },

/* Emergency input (BKIN2) signal initialization -----------------------------*/
  .EmergencyStop = DISABLE,
};

/* USER CODE BEGIN Additional parameters */

/* USER CODE END Additional parameters */

/******************* (C) COPYRIGHT 2019 STMicroelectronics *****END OF FILE****/
