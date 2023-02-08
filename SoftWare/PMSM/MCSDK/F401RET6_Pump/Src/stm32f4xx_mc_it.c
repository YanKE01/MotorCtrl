/**
  ******************************************************************************
  * @file    stm32f4xx_mc_it.c
  * @author  Motor Control SDK Team, ST Microelectronics
  * @brief   Main Interrupt Service Routines.
  *          This file provides exceptions handler and peripherals interrupt
  *          service routine related to Motor Control for the STM32F4 Family.
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
  * @ingroup STM32F4xx_IRQ_Handlers
  */

/* Includes ------------------------------------------------------------------*/
#include "mc_type.h"
#include "mc_config.h"
#include "mc_tasks.h"
#include "parameters_conversion.h"
#include "motorcontrol.h"
#include "stm32f4xx_ll_exti.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#include "mcp_config.h"
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/** @addtogroup MCSDK
  * @{
  */

/** @addtogroup STM32F4xx_IRQ_Handlers STM32F4xx IRQ Handlers
  * @{
  */

/* USER CODE BEGIN PRIVATE */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define SYSTICK_DIVIDER (SYS_TICK_FREQUENCY/1000)
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* USER CODE END PRIVATE */

/* Public prototypes of IRQ handlers called from assembly code ---------------*/
void ADC_IRQHandler(void);
void TIMx_UP_M1_IRQHandler(void);
void TIMx_BRK_M1_IRQHandler(void);

void HardFault_Handler(void);
void SysTick_Handler(void);
void EXTI4_IRQHandler (void);

/**
  * @brief  This function handles ADC1/ADC2 interrupt request.
  * @param  None
  * @retval None
  */
void ADC_IRQHandler(void)
{
  /* USER CODE BEGIN ADC_IRQn 0 */

  /* USER CODE END ADC_IRQn 0 */
  if(LL_ADC_IsActiveFlag_JEOS(ADC1))
  {
    // Clear Flags
    ADC1->SR &= ~(uint32_t)(LL_ADC_FLAG_JEOS | LL_ADC_FLAG_JSTRT);

    TSK_HighFrequencyTask();          /*GUI, this section is present only if DAC is disabled*/
  }
#ifdef ADC3
  else
  {
    // Clear Flags
    ADC3->SR &= ~(uint32_t)(LL_ADC_FLAG_JEOS | LL_ADC_FLAG_JSTRT);

    TSK_HighFrequencyTask();          /*GUI, this section is present only if DAC is disabled*/
  }
#endif
  /* USER CODE BEGIN ADC_IRQn 1 */

  /* USER CODE END ADC_IRQn 1 */
}

/**
  * @brief  This function handles first motor TIMx Update interrupt request.
  * @param  None
  * @retval None
  */
void TIMx_UP_M1_IRQHandler(void)
{
  /* USER CODE BEGIN TIMx_UP_M1_IRQn 0 */

  /* USER CODE END TIMx_UP_M1_IRQn 0 */

  LL_TIM_ClearFlag_UPDATE(PWM_Handle_M1.pParams_str->TIMx);
  R3_1_TIMx_UP_IRQHandler(&PWM_Handle_M1);
  /* USER CODE BEGIN TIMx_UP_M1_IRQn 1 */

  /* USER CODE END TIMx_UP_M1_IRQn 1 */
}

/**
  * @brief  This function handles first motor BRK interrupt.
  * @param  None
  * @retval None
  */
void TIMx_BRK_M1_IRQHandler(void)
{
  /* USER CODE BEGIN TIMx_BRK_M1_IRQn 0 */

  /* USER CODE END TIMx_BRK_M1_IRQn 0 */
  if (LL_TIM_IsActiveFlag_BRK(PWM_Handle_M1.pParams_str->TIMx))
  {
    LL_TIM_ClearFlag_BRK(PWM_Handle_M1.pParams_str->TIMx);
    R3_1_BRK_IRQHandler(&PWM_Handle_M1);
  }
  /* Systick is not executed due low priority so is necessary to call MC_Scheduler here.*/
  MC_Scheduler();

  /* USER CODE BEGIN TIMx_BRK_M1_IRQn 1 */

  /* USER CODE END TIMx_BRK_M1_IRQn 1 */
}

/**
  * @brief This function handles DMA_RX_A channel DMACH_RX_A global interrupt.
  */
void MCP_RX_IRQHandler_A(void)
{
  /* USER CODE BEGIN MCP_RX_IRQHandler_A 0 */

  /* USER CODE BEGIN MCP_RX_IRQHandler_A 0 */

  /* Buffer is ready by the HW layer to be processed */
  if (LL_DMA_IsActiveFlag_TC (DMA_RX_A, DMACH_RX_A) ){
    LL_DMA_ClearFlag_TC (DMA_RX_A, DMACH_RX_A);
    ASPEP_HWDataReceivedIT (&aspepOverUartA);
  }
  /* USER CODE BEGIN MCP_RX_IRQHandler_A 1 */

  /* USER CODE BEGIN MCP_RX_IRQHandler_A 1 */

}

/* This section is present only when serial communication is used */
/**
  * @brief  This function handles USART interrupt request.
  * @param  None
  * @retval None
  */
void USARTA_IRQHandler(void)
{
  /* USER CODE BEGIN USARTA_IRQn 0 */

  /* USER CODE END USARTA_IRQn 0 */

  if ( LL_USART_IsActiveFlag_TC (USARTA) )
  {
    /* Disable the DMA channel to prepare the next chunck of data*/
    LL_DMA_DisableStream( DMA_TX_A, DMACH_TX_A );
    LL_USART_ClearFlag_TC (USARTA);
    /* Data Sent by UART*/
    /* Need to free the buffer, and to check pending transfer*/
    ASPEP_HWDataTransmittedIT (&aspepOverUartA);
  }
  if ( (LL_USART_IsActiveFlag_ORE (USARTA) || LL_USART_IsActiveFlag_FE (USARTA) || LL_USART_IsActiveFlag_NE (USARTA))
        && LL_USART_IsEnabledIT_ERROR (USARTA) )
  { /* Stopping the debugger will generate an OverRun error*/
    LL_USART_ClearFlag_FE(USARTA);
    LL_USART_ClearFlag_ORE(USARTA);
    LL_USART_ClearFlag_NE(USARTA);
    /* We disable ERROR interrupt to avoid to trig one Overrun IT per additional byte recevied*/
    LL_USART_DisableIT_ERROR (USARTA);
    LL_USART_EnableIT_IDLE (USARTA);
  }
  if ( LL_USART_IsActiveFlag_IDLE (USARTA) && LL_USART_IsEnabledIT_IDLE (USARTA) )
  { /* Stopping the debugger will generate an OverRun error*/
    LL_USART_DisableIT_IDLE (USARTA);
    /* Once the complete unexpected data are received, we enable back the error IT*/
    LL_USART_EnableIT_ERROR (USARTA);
    /* To be sure we fetch the potential pendig data*/
    /* We disable the DMA request, Read the dummy data, endable back the DMA request */
    LL_USART_DisableDMAReq_RX (USARTA);
    LL_USART_ReceiveData8(USARTA);
    LL_USART_EnableDMAReq_RX (USARTA);
    LL_DMA_ClearFlag_TE (DMA_RX_A, DMACH_RX_A );
    ASPEP_HWDMAReset (&aspepOverUartA);
  }

  /* USER CODE BEGIN USARTA_IRQn 1 */

  /* USER CODE END USARTA_IRQn 1 */
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
 /* USER CODE BEGIN HardFault_IRQn 0 */

 /* USER CODE END HardFault_IRQn 0 */
  TSK_HardwareFaultTask();

  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {

  }
 /* USER CODE BEGIN HardFault_IRQn 1 */

 /* USER CODE END HardFault_IRQn 1 */

}

/**
  * @brief  This function handles Button IRQ on PIN PA4.
  */
void EXTI4_IRQHandler (void)
{
	/* USER CODE BEGIN START_STOP_BTN */
  if ( LL_EXTI_ReadFlag_0_31(LL_EXTI_LINE_4) )
  {
    LL_EXTI_ClearFlag_0_31 (LL_EXTI_LINE_4);
    UI_HandleStartStopButton_cb ();
  }

}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/**
  * @}
  */

/**
  * @}
  */
/******************* (C) COPYRIGHT 2019 STMicroelectronics *****END OF FILE****/
