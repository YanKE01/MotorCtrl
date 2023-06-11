#ifndef LCM32F037_WT_H
#define LCM32F037_WT_H
#include "stdint.h"
#include "lcm32f037.h"

typedef struct
{
  uint16_t WT_BZOUT; //蜂鸣器输出高低频率选择位

  uint16_t WT_WTState; // WT 使能位

  uint16_t WT_Outfrequency; //蜂鸣器输出频率选择位

  uint16_t WT_T8State; //T8 使能位

  uint16_t WT_T8frequency; //T8 时钟源选择位

  uint16_t WT_Interrupt; // WT 中断源选择位

} WT_InitTypeDef;

/** @defgroup WT_BZOUT
  * @{
  */

#define WT_BZOUT_Hight ((uint16_t)0x0000)
#define WT_BZOUT_Low ((uint16_t)0x0100)
#define IS_WT_BZOUT(MODE) (((MODE) == WT_BZOUT_Hight) || \
                           ((MODE) == WT_BZOUT_Low))

/** @defgroup WT_WTState_State 
  * @{
  */

#define WT_WTState_Enable ((uint16_t)0x0080)
#define WT_WTState_Disable ((uint16_t)0x0000)
#define IS_WT_WTState(STATE) (((STATE) == WT_WTState_Enable) || \
                              ((STATE) == WT_WTState_Disable))

/** @defgroup WT_Outfrequency
  * @{
  */

#define WT_Outfrequency_1024 ((uint16_t)0x0000)
#define WT_Outfrequency_2048 ((uint16_t)0x0010)
#define WT_Outfrequency_4096 ((uint16_t)0x0020)
#define WT_Outfrequency_8192 ((uint16_t)0x0030)
#define IS_WT_Outfrequency(Outfrequency) (((Outfrequency) == WT_Outfrequency_1024) || \
                                          ((Outfrequency) == WT_Outfrequency_2048) || \
                                          ((Outfrequency) == WT_Outfrequency_4096) || \
                                          ((Outfrequency) == WT_Outfrequency_8192))

/** @defgroup WT_T8State 
  * @{
  */

#define WT_T8State_Disable ((uint16_t)0x0000)
#define WT_T8State_Enable ((uint16_t)0x0008)
#define IS_WT_T8State(STATE) (((STATE) == WT_T8State_Enable) || \
                              ((STATE) == WT_T8State_Disable))

/** @defgroup WT_T8frequency
  * @{
  */

#define WT_T8frequency_4096 ((uint16_t)0x0000)
#define WT_T8frequency_64 ((uint16_t)0x0002)
#define WT_T8frequency_1 ((uint16_t)0x0004)
#define WT_T8frequency_1_60 ((uint16_t)0x0006)
#define IS_WT_T8frequency(frequency) (((frequency) == WT_T8frequency_4096) || \
                                      ((frequency) == WT_T8frequency_64) ||   \
                                      ((frequency) == WT_T8frequency_1) ||    \
                                      ((frequency) == WT_T8frequency_1_60))

/** @defgroup WT_Interrupt 
  * @{
  */

#define WT_Interrupt_2HZ ((uint16_t)0x0000)
#define WT_Interrupt_T8DOWN ((uint16_t)0x0001)
#define IS_WT_Interrupt(Interrupt) (((Interrupt) == WT_Interrupt_2HZ) || \
                                    ((Interrupt) == WT_Interrupt_T8DOWN))
#define WT_FLAG_IT 1
/* =========================================================================================================================== */
/* ================                                           WT                                            ================ */
/* =========================================================================================================================== */

/* ==========================================================  WTCON  ========================================================== */

#define WT_WTCON_BZLS_Pos (8UL)     /*!< WTCON (Bit 8)             														 */
#define WT_WTCON_BZLS_Msk (0x100UL) /*!< WTCON (Bitfield-Mask: 0x01)          											    */
#define WT_WTCON_WTEN_Pos (7UL)     /*!< WTCON (Bit 7)             															*/
#define WT_WTCON_WTEN_Msk (0x80UL)  /*!< WTCON (Bitfield-Mask: 0x01)          											    */
#define WT_WTCON_WTF_Pos (6UL)      /*!< WTCON (Bit 6)             															*/
#define WT_WTCON_WTF_Msk (0x40UL)   /*!< WTCON (Bitfield-Mask: 0x01)          											    */
#define WT_WTCON_BUZS_Pos (4UL)     /*!< WTCON (Bit 4)             															*/
#define WT_WTCON_BUZS_Msk (0x30UL)  /*!< WTCON (Bitfield-Mask: 0x03)          											    */
#define WT_WTCON_TR8_Pos (3UL)      /*!< WTCON (Bit 3)             															*/
#define WT_WTCON_TR8_Msk (0x8UL)    /*!< WTCON (Bitfield-Mask: 0x01)          											      */
#define WT_WTCON_T8CKS_Pos (1UL)    /*!< WTCON (Bit 1)             															*/
#define WT_WTCON_T8CKS_Msk (0x6UL)  /*!< WTCON (Bitfield-Mask: 0x03)          											      */
#define WT_WTCON_WTINTS_Pos (0UL)   /*!< WTCON (Bit 0)             															*/
#define WT_WTCON_WTINTS_Msk (0x1UL) /*!< WTCON (Bitfield-Mask: 0x01)          											      */

/* ==========================================================  T8  ========================================================== */
#define WT_T8_Pos (0UL)    /*!< T8 (Bit 0)                                           */
#define WT_T8_Msk (0xffUL) /*!< T8 (Bitfield-Mask: 0xff)                             */

void WT_StructInit(WT_InitTypeDef *WT_InitStruct);
void WT_Init(WT_TypeDef *WTx, WT_InitTypeDef *WT_InitStruct);
void WT_SetCounter(WT_TypeDef *WTx, uint16_t Counter);
void WT_ClearITPendingBit(uint32_t WT_Line);
#endif
