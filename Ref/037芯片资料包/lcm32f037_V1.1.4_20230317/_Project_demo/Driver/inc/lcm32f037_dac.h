#ifndef LCM32F037_ANACTRL_H
#define LCM32F037_ANACTRL_H
#include "lcm32f037.h"

typedef struct
{
  __IO uint32_t DAC_CR;  // 0x0 * 4
  __IO uint32_t DAC_CSR; // 0x1 * 4
  __IO uint32_t DAC_DHR; // 0x2 * 4
  __IO uint32_t DAC_DOR; // 0x3 * 4
} DAC_TypeDef;

typedef struct
{
  uint32_t DAC_Trigger_Source; /*触发源选择!< Specifies the external trigger for the selected DAC channel.
                                                  This parameter can be a value of @ref DAC_trigger_selection */

  uint32_t DAC_EXTrigger_Edge; /* 触发方式选择*/

  uint32_t DAC_WaveGeneration; /*!< Specifies whether DAC channel noise waves or triangle waves
                                                  are generated, or whether no wave is generated.
                                              */

  uint32_t DAC_LFSRUnmask_TriangleAmplitude; /*!< Specifies the LFSR mask for noise wave generation or
                                                  the maximum amplitude triangle generation for the DAC channel. 
                                                  This parameter can be a value of @ref DAC_lfsrunmask_triangleamplitude 
                                                  */

  uint32_t DAC_OutputBuffer; /*!< Specifies whether the DAC channel output buffer is enabled or disabled.
                                                  This parameter can be a value of @ref DAC_output_buffer */
  uint32_t DAC_Vref_Select;  /*dac参考电压选择  */

  FunctionalState DAC_DmaMode; /* DAC dma模式使能 */

  FunctionalState DAC_DMAUDR_IE; /* DAM欠载中断使能 */

} DAC_InitTypeDef;

#define DAC_Trigger_None ((uint32_t)0x00000000)     /*!< Conversion is automatic once the DAC1_DHRxxxx register \
                                                         has been loaded, and not by external trigger */
#define DAC_Trigger_T1_TRGO ((uint32_t)0x00000008)  /*!< TIM6 TRGO selected as external conversion trigger for DAC channel1 */
#define DAC_Trigger_T3_TRGO ((uint32_t)0x00000010)  /*!< TIM3 TRGO selected as external conversion trigger for DAC channel1 */
#define DAC_Trigger_T15_TRGO ((uint32_t)0x00000018) /*!< TIM7 TRGO selected as external conversion trigger for DAC channel1, \
                                                     */
#define DAC_Trigger_T16_OC1 ((uint32_t)0x00000020)  /*!< TIM15 TRGO selected as external conversion trigger for DAC channel1 */
#define DAC_Trigger_T17_OC1 ((uint32_t)0x00000028)  /*!< TIM2 TRGO selected as external conversion trigger for DAC channel1 */
#define DAC_Trigger_Ext_IT1 ((uint32_t)0x00000030)  /*!< EXTI Line9 event selected as external conversion trigger for DAC channels */
#define DAC_Trigger_Ext_IT9 ((uint32_t)0x00000038)
#define DAC_Trigger_ACMP1_Output ((uint32_t)0x00000038)
#define DAC_Trigger_Software ((uint32_t)0x00000000)

#define DAC_EXTrigger_edge_dis ((uint32_t)0x00000000)
#define DAC_EXTrigger_Edge_Rising ((uint32_t)0x00000002)
#define DAC_EXTrigger_Edge_falling ((uint32_t)0x00000004)
#define DAC_EXTrigger_Edge_both ((uint32_t)0x00000006)

#define DAC_WaveGeneration_None (0x0UL << 6)
#define DAC_WaveGeneration_Noise (0x1UL << 6)
#define DAC_WaveGeneration_Triangle (0x2UL << 6)

#define DAC_LFSRUnmask_Bit0 ((uint32_t)0x00000000)    /*!< Unmask DAC channel LFSR bit0 for noise wave generation */
#define DAC_LFSRUnmask_Bits1_0 ((uint32_t)0x00000100) /*!< Unmask DAC channel LFSR bit[1:0] for noise wave generation */
#define DAC_LFSRUnmask_Bits2_0 ((uint32_t)0x00000200) /*!< Unmask DAC channel LFSR bit[2:0] for noise wave generation */
#define DAC_LFSRUnmask_Bits3_0 ((uint32_t)0x00000300) /*!< Unmask DAC channel LFSR bit[3:0] for noise wave generation */
#define DAC_LFSRUnmask_Bits4_0 ((uint32_t)0x00000400) /*!< Unmask DAC channel LFSR bit[4:0] for noise wave generation */
#define DAC_LFSRUnmask_Bits5_0 ((uint32_t)0x00000500) /*!< Unmask DAC channel LFSR bit[5:0] for noise wave generation */
#define DAC_LFSRUnmask_Bits6_0 ((uint32_t)0x00000600) /*!< Unmask DAC channel LFSR bit[6:0] for noise wave generation */
#define DAC_LFSRUnmask_Bits7_0 ((uint32_t)0x00000700) /*!< Unmask DAC channel LFSR bit[7:0] for noise wave generation */

#define DAC_TriangleAmplitude_1 ((uint32_t)0x00000000)   /*!< Select max triangle amplitude of 1 */
#define DAC_TriangleAmplitude_3 ((uint32_t)0x00000100)   /*!< Select max triangle amplitude of 3 */
#define DAC_TriangleAmplitude_7 ((uint32_t)0x00000200)   /*!< Select max triangle amplitude of 7 */
#define DAC_TriangleAmplitude_15 ((uint32_t)0x00000300)  /*!< Select max triangle amplitude of 15 */
#define DAC_TriangleAmplitude_31 ((uint32_t)0x00000400)  /*!< Select max triangle amplitude of 31 */
#define DAC_TriangleAmplitude_63 ((uint32_t)0x00000500)  /*!< Select max triangle amplitude of 63 */
#define DAC_TriangleAmplitude_127 ((uint32_t)0x00000600) /*!< Select max triangle amplitude of 127 */
#define DAC_TriangleAmplitude_255 ((uint32_t)0x00000700) /*!< Select max triangle amplitude of 255 */

#define DAC0_OutputBuffer_Enable (0x1UL << 4)
#define DAC1_OutputBuffer_Enable (0x1UL << 0)
#define DAC_OutputBuffer_Disable (0x0UL << 0)

#define DAC_Align_10B_R (0x0UL << 15)
#define DAC_Align_10B_L (0x1UL << 15)

#define DAC_Vref_Avdd (0x0UL << 14)
#define DAC_Vref_Pum_2v5 (0x10UL)
#define DAC_Vref_Pum_4v (0x19UL)
#define DAC_Vref_Pum (0x1UL << 14)

/***************** Bit Definition for ANACTRL_DACX_CR Register **************/
#define ANACTRL_DACX_CR_ALIGN_Pos 15
#define ANACTRL_DACX_CR_ALIGN_Msk (0x1UL << ANACTRL_DACX_CR_ALIGN_Pos)
#define ANACTRL_DACX_CR_ALIGN_R (0x0UL << ANACTRL_DACX_CR_ALIGN_Pos)
#define ANACTRL_DACX_CR_ALIGN_L (0x1UL << ANACTRL_DACX_CR_ALIGN_Pos)
#define ANACTRL_DACX_CR_VREF_SEL_Pos 14
#define ANACTRL_DACX_CR_VREF_SEL_Msk (0x1UL << ANACTRL_DACX_CR_VREF_SEL_Pos)
#define ANACTRL_DACX_CR_VREF_SEL_VDDA (0x0UL << ANACTRL_DACX_CR_VREF_SEL_Pos)
#define ANACTRL_DACX_CR_VREF_SEL_VREF (0x1UL << ANACTRL_DACX_CR_VREF_SEL_Pos)
#define ANACTRL_DACX_CR_DMAUDRIE_Pos 13
#define ANACTRL_DACX_CR_DMAUDRIE_Msk (0x1UL << ANACTRL_DACX_CR_DMAUDRIE_Pos)
#define ANACTRL_DACX_CR_DMAUDRIE_DIS (0x0UL << ANACTRL_DACX_CR_DMAUDRIE_Pos)
#define ANACTRL_DACX_CR_DMAUDRIE_EN (0x1UL << ANACTRL_DACX_CR_DMAUDRIE_Pos)
#define ANACTRL_DACX_CR_DMAEN_Pos 12
#define ANACTRL_DACX_CR_DMAEN_Msk (0x1UL << ANACTRL_DACX_CR_DMAEN_Pos)
#define ANACTRL_DACX_CR_DMAEN_DIS (0x0UL << ANACTRL_DACX_CR_DMAEN_Pos)
#define ANACTRL_DACX_CR_DMAEN_EN (0x1UL << ANACTRL_DACX_CR_DMAEN_Pos)
#define ANACTRL_DACX_CR_MAMP_Pos 8
#define ANACTRL_DACX_CR_MAMP_Msk (0xFUL << ANACTRL_DACX_CR_MAMP_Pos)
#define ANACTRL_DACX_CR_MAMP_1 (0x0UL << ANACTRL_DACX_CR_MAMP_Pos)
#define ANACTRL_DACX_CR_MAMP_3 (0x1UL << ANACTRL_DACX_CR_MAMP_Pos)
#define ANACTRL_DACX_CR_MAMP_7 (0x2UL << ANACTRL_DACX_CR_MAMP_Pos)
#define ANACTRL_DACX_CR_MAMP_15 (0x3UL << ANACTRL_DACX_CR_MAMP_Pos)
#define ANACTRL_DACX_CR_MAMP_31 (0x4UL << ANACTRL_DACX_CR_MAMP_Pos)
#define ANACTRL_DACX_CR_MAMP_63 (0x5UL << ANACTRL_DACX_CR_MAMP_Pos)
#define ANACTRL_DACX_CR_MAMP_127 (0x6UL << ANACTRL_DACX_CR_MAMP_Pos)
#define ANACTRL_DACX_CR_MAMP_255 (0x7UL << ANACTRL_DACX_CR_MAMP_Pos)
#define ANACTRL_DACX_CR_MAMP_511 (0x8UL << ANACTRL_DACX_CR_MAMP_Pos)
#define ANACTRL_DACX_CR_MAMP_1023 (0x9UL << ANACTRL_DACX_CR_MAMP_Pos)
#define ANACTRL_DACX_CR_MAMP_2047 (0xAUL << ANACTRL_DACX_CR_MAMP_Pos)
#define ANACTRL_DACX_CR_MAMP_4095 (0xBUL << ANACTRL_DACX_CR_MAMP_Pos)

#define ANACTRL_DACX_CR_WAVE_Pos 6
#define ANACTRL_DACX_CR_WAVE_Msk (0x3UL << ANACTRL_DACX_CR_WAVE_Pos)
#define ANACTRL_DACX_CR_WAVE_DIS (0x0UL << ANACTRL_DACX_CR_WAVE_Pos)
#define ANACTRL_DACX_CR_WAVE_NOISE (0x1UL << ANACTRL_DACX_CR_WAVE_Pos)
#define ANACTRL_DACX_CR_WAVE_TRIANGLE (0x2UL << ANACTRL_DACX_CR_WAVE_Pos)

#define ANACTRL_DACX_CR_TSEL_Pos 3
#define ANACTRL_DACX_CR_TSEL_Msk (0x7UL << ANACTRL_DACX_CR_TSEL_Pos)
#define ANACTRL_DACX_CR_TSEL_SWTRIG (0x0UL << ANACTRL_DACX_CR_TSEL_Pos)
#define ANACTRL_DACX_CR_TSEL_TIM1_TRGO (0x1UL << ANACTRL_DACX_CR_TSEL_Pos)
#define ANACTRL_DACX_CR_TSEL_TIM3_TRGO (0x2UL << ANACTRL_DACX_CR_TSEL_Pos)
#define ANACTRL_DACX_CR_TSEL_TIM15_TRGO (0x3UL << ANACTRL_DACX_CR_TSEL_Pos)
#define ANACTRL_DACX_CR_TSEL_TIM16_OC1 (0x4UL << ANACTRL_DACX_CR_TSEL_Pos)
#define ANACTRL_DACX_CR_TSEL_TIM17_OC1 (0x5UL << ANACTRL_DACX_CR_TSEL_Pos)
#define ANACTRL_DACX_CR_TSEL_EXTI_1 (0x6UL << ANACTRL_DACX_CR_TSEL_Pos)
#define ANACTRL_DACX_CR_TSEL_EXTI_9 (0x7UL << ANACTRL_DACX_CR_TSEL_Pos)
#define ANACTRL_DACX_CR_TEN_Pos 1
#define ANACTRL_DACX_CR_TEN_Msk (0x3UL << ANACTRL_DACX_CR_TEN_Pos)
#define ANACTRL_DACX_CR_TEN_DIS (0x0UL << ANACTRL_DACX_CR_TEN_Pos)
#define ANACTRL_DACX_CR_TEN_RISING (0x1UL << ANACTRL_DACX_CR_TEN_Pos)
#define ANACTRL_DACX_CR_TEN_FALLING (0x2UL << ANACTRL_DACX_CR_TEN_Pos)
#define ANACTRL_DACX_CR_TEN_BOTH (0x3UL << ANACTRL_DACX_CR_TEN_Pos)
#define ANACTRL_DACX_CR_EN_Pos 0
#define ANACTRL_DACX_CR_EN_Msk (0x1UL << ANACTRL_DACX_CR_EN_Pos)
#define ANACTRL_DACX_CR_EN_DIS (0x0UL << ANACTRL_DACX_CR_EN_Pos)
#define ANACTRL_DACX_CR_EN_EN (0x1UL << ANACTRL_DACX_CR_EN_Pos)

/***************** Bit Definition for ANACTRL_DACX_CSR Register **************/
#define ANACTRL_DACX_CSR_DMAUDR_Pos 8
#define ANACTRL_DACX_CSR_DMAUDR_Msk (0x1UL << ANACTRL_DACX_CSR_DMAUDR_Pos)
#define ANACTRL_DACX_CSR_SWTRIG_Pos 0
#define ANACTRL_DACX_CSR_SWTRIG_Msk (0x1UL << ANACTRL_DACX_CSR_SWTRIG_Pos)

/***************** Bit Definition for ANACTRL_DACX_DHR Register **************/
#define ANACTRL_DACX_DHR_DHR_Pos 0
#define ANACTRL_DACX_DHR_DHR_Msk (0xFFFFUL << ANACTRL_DACX_DHR_DHR_Pos)

/***************** Bit Definition for ANACTRL_DACX_DOR Register **************/
#define ANACTRL_DACX_DOR_DOR_Pos 0
#define ANACTRL_DACX_DOR_DOR_Msk (0xFFFFUL << ANACTRL_DACX_DOR_DOR_Pos)

/***************** Bit Definition for ANACTRL_KEY Register **************/
#define ANACTRL_KEY_Pos 0
#define ANACTRL_KEY_Msk (0xFFFFFFFFUL << ANACTRL_KEY_Pos)
#define ANACTRL_KEY_VALUE 0xA98BC56D

/***************** Bit Definition for ANACTRL_ANA_CSR Register **************/

#define ANACTRL_ANA_CSR_DAC8_BUF_SEL_Pos 1
#define ANACTRL_ANA_CSR_DAC8_BUF_SEL_Msk (0x7UL << ANACTRL_ANA_CSR_DAC8_BUF_SEL_Pos)
#define ANACTRL_ANA_CSR_DAC8_BUF_EN_Pos 0
#define ANACTRL_ANA_CSR_DAC8_BUF_EN_Msk (0x1UL << ANACTRL_ANA_CSR_DAC8_BUF_EN_Pos)

#define DAC_FLAG_DMAUDR ANACTRL_DACX_CSR_DMAUDR_Msk
#define DAC_IT_DMAUDR ANACTRL_DACX_CSR_DMAUDR_Msk
/***************** ANACTRL Declaration **************/
#define ANACTRL_ADDR_STR (0x40017C00)
//#define ANACTRL  ((ANACTRL_TypeDef *) (ANACTRL_ADDR_STR))
#define DAC0 ((DAC_TypeDef *)(ANACTRL_ADDR_STR + 0x40))
#define DAC1 ((DAC_TypeDef *)(ANACTRL_ADDR_STR + 0x50))

void DAC_DeInit(void);
void DAC_Init(DAC_TypeDef *dac_ptr, DAC_InitTypeDef *DAC_InitStruct);
void DAC_StructInit(DAC_InitTypeDef *DAC_InitStruct);
void DAC_Cmd(DAC_TypeDef *dac_ptr, FunctionalState NewState);
void DAC_SoftwareTriggerCmd(DAC_TypeDef *dac_ptr, FunctionalState NewState);
void DAC_WaveGenerationCmd(DAC_TypeDef *dac_ptr, uint32_t DAC_Wave, FunctionalState NewState);
void DAC_SetDac_10B_Data(DAC_TypeDef *dac_ptr, uint32_t DAC_Align, uint16_t Data);
uint16_t DAC_GetDataOutputValue_10bit(DAC_TypeDef *dac_ptr);
void DAC_DMACmd(DAC_TypeDef *dac_ptr, FunctionalState NewState);
void DAC_ITConfig(DAC_TypeDef *dac_ptr, uint32_t DAC_IT, FunctionalState NewState);

//FlagStatus DAC_GetFlagStatus(DAC_TypeDef * dac_ptr, uint32_t DAC_FLAG);
void DAC_ClearFlag(DAC_TypeDef *dac_ptr, uint32_t DAC_FLAG);
//ITStatus DAC_GetITStatus(DAC_TypeDef * dac_ptr, uint32_t DAC_IT);
void DAC_ClearITPendingBit(DAC_TypeDef *dac_ptr, uint32_t DAC_IT);

#endif // __ANACTRL_H__
