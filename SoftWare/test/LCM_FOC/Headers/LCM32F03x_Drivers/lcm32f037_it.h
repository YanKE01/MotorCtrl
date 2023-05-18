/**
  ******************************************************************************
  * @file    ADC_DMA/LCM32f037_it.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    23-March-2012
  * @brief   This file contains the headers of the interrupt handlers.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 LCMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LCM32F037_IT_H
#define __LCM32F037_IT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "lcm32f037_lib.h"
#include "UserIncludes.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void NMI_Handler(void);
void HardFault_Handler(void);
void SVC_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void TIM1_BRK_UP_TRG_COM_IRQHandler(void);
void TIM2_IRQHandler(void);
void TIM16_IRQHandler(void);
void EXTI0_1_IRQHandler(void);
void EXTI2_3_IRQHandler(void);
void EXTI4_15_IRQHandler(void);
#ifdef USE_USART1
void USART1_IRQHandler(void);
#endif
#ifdef USE_USART2
void USART2_IRQHandler(void);
#endif
void DMA1_Channel1_IRQHandler(void);
#ifdef __cplusplus
}
#endif

#define UARTBUF_SIZE_TX   512        /*** Must be a power of 2 (2,4,8,16,32,64,128,256,512,...) ***/
#define UARTBUF_SIZE_RX   128	       /*** Must be a power of 2 (2,4,8,16,32,64,128,256,512,...) ***/
#define UARTBUF_SIZE_FREE 200
extern void DLYMS_TIM16(int ms);
struct buf_st_tx
{
    unsigned int in;                                // Next In Index
    unsigned int out;                               // Next Out Index
    char buf [UARTBUF_SIZE_TX];                            // Buffer
};

struct buf_st_rx
{
    unsigned int in;                                // Next In Index
    unsigned int out;                               // Next Out Index
    char buf [UARTBUF_SIZE_RX];                     // Buffer
};

extern struct buf_st_tx tbuf;
extern struct buf_st_rx rbuf;

extern u8 HALL_ABC_b;

#endif 

/************************ (C) COPYRIGHT LCMicroelectronics *****END OF FILE****/
