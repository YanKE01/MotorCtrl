#ifndef __ANACTRL_H__
#define __ANACTRL_H__

#include "define.h"

/******************** ANACTRL Register Struct Definition *****************/
typedef struct
{
    __IO uint32_t OPA0_CSR;         // 0x00 * 4
    __IO uint32_t OPA1_CSR;         // 0x01 * 4
    __IO uint32_t OPA2_CSR;         // 0x02 * 4
         uint32_t RESERVED0[5];
    __IO uint32_t ACMP0_CSR;        // 0x08 * 4
    __IO uint32_t ACMP1_CSR;        // 0x09 * 4
    __IO uint32_t ACMP2_CSR;        // 0x0a * 4
    __IO uint32_t ACMP3_CSR;        // 0x0b * 4
    __IO uint32_t ACMP4_CSR;        // 0x0c * 4
    __IO uint32_t ACMP5_CSR;        // 0x0d * 4
         uint32_t RESERVED1[2];
    __IO uint32_t DAC0_CR;          // 0x10 * 4
    __IO uint32_t DAC0_CSR;         // 0x11 * 4
    __IO uint32_t DAC0_DHR;         // 0x12 * 4
    __IO uint32_t DAC0_DOR;         // 0x13 * 4
    __IO uint32_t DAC1_CR;          // 0x14 * 4
    __IO uint32_t DAC1_CSR;         // 0x15 * 4
    __IO uint32_t DAC1_DHR;         // 0x16 * 4
    __IO uint32_t DAC1_DOR;         // 0x17 * 4
    __IO uint32_t DAC2_CR;          // 0x18 * 4
    __IO uint32_t DAC2_CSR;         // 0x19 * 4
    __IO uint32_t DAC2_DHR;         // 0x1a * 4
    __IO uint32_t DAC2_DOR;         // 0x1b * 4
    __IO uint32_t DAC3_CR;          // 0x1c * 4
    __IO uint32_t DAC3_CSR;         // 0x1d * 4
    __IO uint32_t DAC3_DHR;         // 0x1e * 4
    __IO uint32_t DAC3_DOR;         // 0x1f * 4
    __IO uint32_t DAC4_CR;          // 0x20 * 4
    __IO uint32_t DAC4_CSR;         // 0x21 * 4
    __IO uint32_t DAC4_DHR;         // 0x22 * 4
    __IO uint32_t DAC4_DOR;         // 0x23 * 4
    __IO uint32_t DAC5_CR;          // 0x24 * 4
    __IO uint32_t DAC5_CSR;         // 0x25 * 4
    __IO uint32_t DAC5_DHR;         // 0x26 * 4
    __IO uint32_t DAC5_DOR;         // 0x27 * 4
         uint32_t RESERVED2[8];
    __IO uint32_t DAC5_DIFF_CR1;    // 0x30 * 4
    __IO uint32_t DAC5_DIFF_CR2;    // 0x31 * 4
    __IO uint32_t DAC5_DIFF_CR3;    // 0x32 * 4
    __IO uint32_t DAC5_DIFF_CSR;    // 0x33 * 4
         uint32_t RESERVED3[10];
    __IO uint32_t ANA_CSR;          // 0x3e * 4
    #pragma anon_unions
    union {                         // 0x3f * 4
        __O uint32_t KEY;
        __I uint32_t KEY_STS; 
    };
} ANACTRL_TypeDef;

typedef struct
{
    __IO uint32_t DAC_CR;       // 0x0 * 4
    __IO uint32_t DAC_CSR;      // 0x1 * 4
    __IO uint32_t DAC_DHR;      // 0x2 * 4
    __IO uint32_t DAC_DOR;      // 0x3 * 4
} DAC_TypeDef;

typedef struct
{
  uint32_t DAC_Trigger;                      /*!< Specifies the external trigger for the selected DAC channel.
                                                  This parameter can be a value of @ref DAC_trigger_selection */

  uint32_t DAC_WaveGeneration;               /*!< Specifies whether DAC channel noise waves or triangle waves
                                                  are generated, or whether no wave is generated.
                                                  This parameter can be a value of @ref DAC_wave_generation
                                                  This parameter is only applicable for STM32F072 devices */

  uint32_t DAC_LFSRUnmask_TriangleAmplitude; /*!< Specifies the LFSR mask for noise wave generation or
                                                  the maximum amplitude triangle generation for the DAC channel. 
                                                  This parameter can be a value of @ref DAC_lfsrunmask_triangleamplitude 
                                                  This parameter is only applicable for STM32F072 devices */

  uint32_t DAC_OutputBuffer;                 /*!< Specifies whether the DAC channel output buffer is enabled or disabled.
                                                  This parameter can be a value of @ref DAC_output_buffer */
	uint32_t DAC_Vref_Sel; 
	
}DAC_InitTypeDef;


#define DAC_Trigger_None                   ((uint32_t)0x00000000) /*!< Conversion is automatic once the DAC1_DHRxxxx register 
                                                                       has been loaded, and not by external trigger */
#define DAC_Trigger_T1_TRGO                ((uint32_t)0x0000000E) /*!< TIM6 TRGO selected as external conversion trigger for DAC channel1 */
#define DAC_Trigger_T3_TRGO                ((uint32_t)0x00000016) /*!< TIM3 TRGO selected as external conversion trigger for DAC channel1 */
#define DAC_Trigger_T15_TRGO               ((uint32_t)0x0000001E) /*!< TIM7 TRGO selected as external conversion trigger for DAC channel1, 
                                                                       applicable only for STM32F072 devices */
#define DAC_Trigger_T16_OC1                ((uint32_t)0x00000026) /*!< TIM15 TRGO selected as external conversion trigger for DAC channel1 */
#define DAC_Trigger_T17_OC1                ((uint32_t)0x0000002E) /*!< TIM2 TRGO selected as external conversion trigger for DAC channel1 */
#define DAC_Trigger_Ext_IT1                ((uint32_t)0x00000036) /*!< EXTI Line9 event selected as external conversion trigger for DAC channels */
#define DAC_Trigger_Ext_IT9                ((uint32_t)0x0000003E)
#define DAC_Trigger_ACMP1_Output           ((uint32_t)0x0000003E)

#define DAC_Trigger_Ext_IT9                ((uint32_t)0x0000003E)
#define DAC_Trigger_Software               ((uint32_t)0x00000006) 

#define DAC_WaveGeneration_None            (0x0UL <<6)
#define DAC_WaveGeneration_Noise           (0x1UL <<6)
#define DAC_WaveGeneration_Triangle        (0x2UL <<6)

#define DAC_LFSRUnmask_Bit0                ((uint32_t)0x00000000) /*!< Unmask DAC channel LFSR bit0 for noise wave generation */
#define DAC_LFSRUnmask_Bits1_0             ((uint32_t)0x00000100) /*!< Unmask DAC channel LFSR bit[1:0] for noise wave generation */
#define DAC_LFSRUnmask_Bits2_0             ((uint32_t)0x00000200) /*!< Unmask DAC channel LFSR bit[2:0] for noise wave generation */
#define DAC_LFSRUnmask_Bits3_0             ((uint32_t)0x00000300) /*!< Unmask DAC channel LFSR bit[3:0] for noise wave generation */
#define DAC_LFSRUnmask_Bits4_0             ((uint32_t)0x00000400) /*!< Unmask DAC channel LFSR bit[4:0] for noise wave generation */
#define DAC_LFSRUnmask_Bits5_0             ((uint32_t)0x00000500) /*!< Unmask DAC channel LFSR bit[5:0] for noise wave generation */
#define DAC_LFSRUnmask_Bits6_0             ((uint32_t)0x00000600) /*!< Unmask DAC channel LFSR bit[6:0] for noise wave generation */
#define DAC_LFSRUnmask_Bits7_0             ((uint32_t)0x00000700) /*!< Unmask DAC channel LFSR bit[7:0] for noise wave generation */

#define DAC_TriangleAmplitude_1            ((uint32_t)0x00000000) /*!< Select max triangle amplitude of 1 */
#define DAC_TriangleAmplitude_3            ((uint32_t)0x00000100) /*!< Select max triangle amplitude of 3 */
#define DAC_TriangleAmplitude_7            ((uint32_t)0x00000200) /*!< Select max triangle amplitude of 7 */
#define DAC_TriangleAmplitude_15           ((uint32_t)0x00000300) /*!< Select max triangle amplitude of 15 */
#define DAC_TriangleAmplitude_31           ((uint32_t)0x00000400) /*!< Select max triangle amplitude of 31 */
#define DAC_TriangleAmplitude_63           ((uint32_t)0x00000500) /*!< Select max triangle amplitude of 63 */
#define DAC_TriangleAmplitude_127          ((uint32_t)0x00000600) /*!< Select max triangle amplitude of 127 */
#define DAC_TriangleAmplitude_255          ((uint32_t)0x00000700) /*!< Select max triangle amplitude of 255 */


#define DAC0_OutputBuffer_Enable            (0x1UL <<0)
#define DAC1_OutputBuffer_Enable            (0x3UL <<0)
#define DAC2_OutputBuffer_Enable            (0x5UL <<0)
#define DAC3_OutputBuffer_Enable            (0x7UL <<0)
#define DAC4_OutputBuffer_Enable            (0x9UL <<0)
#define DAC5_OutputBuffer_Enable            (0x1UL <<4)
#define DAC_OutputBuffer_Disable            (0x0UL <<0)

#define DAC_Align_8B_R                        (0x0UL <<15)
#define DAC_Align_8B_L                        (0x1UL <<15)
#define DAC_Align_12B_R                       (0x0UL <<15)
#define DAC_Align_12B_L                       (0x1UL <<15)


#define DAC_Vref_Avdd                        (0x0UL <<15)
#define DAC_Vref_Pum                         (0x1UL <<14)
/***************** Bit Definition for ANACTRL_OPA0_CSR Register **************/
//#define ANACTRL_OPA0_CSR_OPTRIMO_Pos        31
//#define ANACTRL_OPA0_CSR_OPTRIMO_Msk        (0x1UL << ANACTRL_OPA0_CSR_OPTRIMO_Pos)
//#define ANACTRL_OPA0_CSR_OPTRIMEN_Pos       30
//#define ANACTRL_OPA0_CSR_OPTRIMEN_Msk       (0x1UL << ANACTRL_OPA0_CSR_OPTRIMEN_Pos)
//#define ANACTRL_OPA0_CSR_OPPES_Pos          26
//#define ANACTRL_OPA0_CSR_OPPES_Msk          (0x3UL << ANACTRL_OPA0_CSR_OPPES_Pos)
//#define ANACTRL_OPA0_CSR_OPNES_Pos          24
//#define ANACTRL_OPA0_CSR_OPNES_Msk          (0x3UL << ANACTRL_OPA0_CSR_OPNES_Pos)
//#define ANACTRL_OPA0_CSR_OPOS_Pos           16
//#define ANACTRL_OPA0_CSR_OPOS_Msk           (0x1FUL <<ANACTRL_OPA0_CSR_OPOS_Pos)
//#define ANACTRL_OPA0_CSR_OPGS_Pos           8
//#define ANACTRL_OPA0_CSR_OPGS_Msk           (0x7UL << ANACTRL_OPA0_CSR_OPGS_Pos)
//#define ANACTRL_OPA0_CSR_OPNS_Pos           4
//#define ANACTRL_OPA0_CSR_OPNS_Msk           (0x1UL << ANACTRL_OPA0_CSR_OPNS_Pos)
//#define ANACTRL_OPA0_CSR_OPOE_Pos           3
//#define ANACTRL_OPA0_CSR_OPOE_Msk           (0x1UL << ANACTRL_OPA0_CSR_OPOE_Pos)
//#define ANACTRL_OPA0_CSR_OPOTS_Pos          2
//#define ANACTRL_OPA0_CSR_OPOTS_Msk          (0x1UL << ANACTRL_OPA0_CSR_OPOTS_Pos)
//#define ANACTRL_OPA0_CSR_OPNGD_Pos          1
//#define ANACTRL_OPA0_CSR_OPNGD_Msk          (0x1UL << ANACTRL_OPA0_CSR_OPNGD_Pos)
//#define ANACTRL_OPA0_CSR_OPEN_Pos           0
//#define ANACTRL_OPA0_CSR_OPEN_Msk           (0x1UL << ANACTRL_OPA0_CSR_OPEN_Pos)

///***************** Bit Definition for ANACTRL_OPA1_CSR Register **************/
//#define ANACTRL_OPA1_CSR_OPTRIMO_Pos        31
//#define ANACTRL_OPA1_CSR_OPTRIMO_Msk        (0x1UL << ANACTRL_OPA1_CSR_OPTRIMO_Pos)
//#define ANACTRL_OPA1_CSR_OPTRIMEN_Pos       30
//#define ANACTRL_OPA1_CSR_OPTRIMEN_Msk       (0x1UL << ANACTRL_OPA1_CSR_OPTRIMEN_Pos)
//#define ANACTRL_OPA1_CSR_OPPES_Pos          26
//#define ANACTRL_OPA1_CSR_OPPES_Msk          (0x3UL << ANACTRL_OPA1_CSR_OPPES_Pos)
//#define ANACTRL_OPA1_CSR_OPNES_Pos          24
//#define ANACTRL_OPA1_CSR_OPNES_Msk          (0x3UL << ANACTRL_OPA1_CSR_OPNES_Pos)
//#define ANACTRL_OPA1_CSR_OPOS_Pos           16
//#define ANACTRL_OPA1_CSR_OPOS_Msk           (0x1FUL<< ANACTRL_OPA1_CSR_OPOS_Pos)
//#define ANACTRL_OPA1_CSR_OPGS_Pos           8
//#define ANACTRL_OPA1_CSR_OPGS_Msk           (0x7UL << ANACTRL_OPA1_CSR_OPGS_Pos)
//#define ANACTRL_OPA1_CSR_OPPS_Pos           5
//#define ANACTRL_OPA1_CSR_OPPS_Msk           (0x1UL << ANACTRL_OPA1_CSR_OPPS_Pos)
//#define ANACTRL_OPA1_CSR_OPNS_Pos           4
//#define ANACTRL_OPA1_CSR_OPNS_Msk           (0x1UL << ANACTRL_OPA1_CSR_OPNS_Pos)
//#define ANACTRL_OPA1_CSR_OPOE_Pos           3
//#define ANACTRL_OPA1_CSR_OPOE_Msk           (0x1UL << ANACTRL_OPA1_CSR_OPOE_Pos)
//#define ANACTRL_OPA1_CSR_OPPRS_Pos          2
//#define ANACTRL_OPA1_CSR_OPPRS_Msk          (0x1UL << ANACTRL_OPA1_CSR_OPPRS_Pos)
//#define ANACTRL_OPA1_CSR_OPNRS_Pos          1
//#define ANACTRL_OPA1_CSR_OPNRS_Msk          (0x1UL << ANACTRL_OPA1_CSR_OPNRS_Pos)
//#define ANACTRL_OPA1_CSR_OPEN_Pos           0
//#define ANACTRL_OPA1_CSR_OPEN_Msk           (0x1UL << ANACTRL_OPA1_CSR_OPEN_Pos)

///***************** Bit Definition for ANACTRL_OPA2_CSR Register **************/
//#define ANACTRL_OPA2_CSR_OPTRIMO_Pos        31
//#define ANACTRL_OPA2_CSR_OPTRIMO_Msk        (0x1UL << ANACTRL_OPA2_CSR_OPTRIMO_Pos)
//#define ANACTRL_OPA2_CSR_OPTRIMEN_Pos       30
//#define ANACTRL_OPA2_CSR_OPTRIMEN_Msk       (0x1UL << ANACTRL_OPA2_CSR_OPTRIMEN_Pos)
//#define ANACTRL_OPA2_CSR_OPPES_Pos          26
//#define ANACTRL_OPA2_CSR_OPPES_Msk          (0x3UL << ANACTRL_OPA2_CSR_OPPES_Pos)
//#define ANACTRL_OPA2_CSR_OPNES_Pos          24
//#define ANACTRL_OPA2_CSR_OPNES_Msk          (0x3UL << ANACTRL_OPA2_CSR_OPNES_Pos)
//#define ANACTRL_OPA2_CSR_OPOS_Pos           16
//#define ANACTRL_OPA2_CSR_OPOS_Msk           (0x1FUL<< ANACTRL_OPA2_CSR_OPOS_Pos)
//#define ANACTRL_OPA2_CSR_OPGS_Pos           8
//#define ANACTRL_OPA2_CSR_OPGS_Msk           (0x7UL << ANACTRL_OPA2_CSR_OPGS_Pos)
//#define ANACTRL_OPA2_CSR_OPPS_Pos           5
//#define ANACTRL_OPA2_CSR_OPPS_Msk           (0x1UL << ANACTRL_OPA2_CSR_OPPS_Pos)
//#define ANACTRL_OPA2_CSR_OPNS_Pos           4
//#define ANACTRL_OPA2_CSR_OPNS_Msk           (0x1UL << ANACTRL_OPA2_CSR_OPNS_Pos)
//#define ANACTRL_OPA2_CSR_OPOE_Pos           3
//#define ANACTRL_OPA2_CSR_OPOE_Msk           (0x1UL << ANACTRL_OPA2_CSR_OPOE_Pos)
//#define ANACTRL_OPA2_CSR_OPPRS_Pos          2
//#define ANACTRL_OPA2_CSR_OPPRS_Msk          (0x1UL << ANACTRL_OPA2_CSR_OPPRS_Pos)
//#define ANACTRL_OPA2_CSR_OPNRS_Pos          1
//#define ANACTRL_OPA2_CSR_OPNRS_Msk          (0x1UL << ANACTRL_OPA2_CSR_OPNRS_Pos)
//#define ANACTRL_OPA2_CSR_OPEN_Pos           0
//#define ANACTRL_OPA2_CSR_OPEN_Msk           (0x1UL << ANACTRL_OPA2_CSR_OPEN_Pos)

/***************** Bit Definition for ANACTRL_ACMPX_CSR Register **************/
#define ANACTRL_ACMPX_CSR_CP_OUT_Pos            28
#define ANACTRL_ACMPX_CSR_CP_OUT_Msk            (0x1UL << ANACTRL_ACMPX_CSR_CP_OUT_Pos)
#define ANACTRL_ACMPX_CSR_CP_PF_Pos             16
#define ANACTRL_ACMPX_CSR_CP_PF_Msk             (0x1FUL<< ANACTRL_ACMPX_CSR_CP_PF_Pos)
#define ANACTRL_ACMPX_CSR_CP_BLANKING_Pos       12
#define ANACTRL_ACMPX_CSR_CP_BLANKING_Msk       (0x7UL<< ANACTRL_ACMPX_CSR_CP_BLANKING_Pos)
#define ANACTRL_ACMPX_CSR_CP_BLANKING_DIS       (0x0UL<< ANACTRL_ACMPX_CSR_CP_BLANKING_Pos)
#define ANACTRL_ACMPX_CSR_CP_BLANKING_TIM1_OC4  (0x1UL<< ANACTRL_ACMPX_CSR_CP_BLANKING_Pos)
#define ANACTRL_ACMPX_CSR_CP_BLANKING_TIM3_OC4  (0x2UL<< ANACTRL_ACMPX_CSR_CP_BLANKING_Pos)
#define ANACTRL_ACMPX_CSR_CP_BLANKING_TIM15_OC2 (0x3UL<< ANACTRL_ACMPX_CSR_CP_BLANKING_Pos)
#define ANACTRL_ACMPX_CSR_CP_BLANKING_TIM1_OC3  (0x4UL<< ANACTRL_ACMPX_CSR_CP_BLANKING_Pos)
#define ANACTRL_ACMPX_CSR_CP_BLANKING_TIM3_OC3  (0x5UL<< ANACTRL_ACMPX_CSR_CP_BLANKING_Pos)
#define ANACTRL_ACMPX_CSR_CP_BLANKING_TIM15_OC1 (0x6UL<< ANACTRL_ACMPX_CSR_CP_BLANKING_Pos)
#define ANACTRL_ACMPX_CSR_CP_BLANKING_TIM16_OC1 (0x7UL<< ANACTRL_ACMPX_CSR_CP_BLANKING_Pos)
#define ANACTRL_ACMPX_CSR_CP_DAC_Pos            11
#define ANACTRL_ACMPX_CSR_CP_DAC_Msk            (0x1UL << ANACTRL_ACMPX_CSR_CP_DAC_Pos)
#define ANACTRL_ACMPX_CSR_CP_DLY_Pos            9
#define ANACTRL_ACMPX_CSR_CP_DLY_Msk            (0x3UL << ANACTRL_ACMPX_CSR_CP_DLY_Pos)
#define ANACTRL_ACMPX_CSR_CP_FS_Pos             8
#define ANACTRL_ACMPX_CSR_CP_FS_Msk             (0x1UL << ANACTRL_ACMPX_CSR_CP_FS_Pos)
#define ANACTRL_ACMPX_CSR_CP_NS_Pos             6
#define ANACTRL_ACMPX_CSR_CP_NS_Msk             (0x1UL << ANACTRL_ACMPX_CSR_CP_NS_Pos)
#define ANACTRL_ACMPX_CSR_CP_PS_Pos             4
#define ANACTRL_ACMPX_CSR_CP_PS_Msk             (0x1UL << ANACTRL_ACMPX_CSR_CP_PS_Pos)
#define ANACTRL_ACMPX_CSR_CP_IS_Pos             3
#define ANACTRL_ACMPX_CSR_CP_IS_Msk             (0x1UL << ANACTRL_ACMPX_CSR_CP_IS_Pos)
#define ANACTRL_ACMPX_CSR_CP_HYSEN_Pos          2
#define ANACTRL_ACMPX_CSR_CP_HYSEN_Msk          (0x1UL << ANACTRL_ACMPX_CSR_CP_HYSEN_Pos)
#define ANACTRL_ACMPX_CSR_CP_FREN_Pos           1
#define ANACTRL_ACMPX_CSR_CP_FREN_Msk           (0x1UL << ANACTRL_ACMPX_CSR_CP_FREN_Pos)
#define ANACTRL_ACMPX_CSR_CP_EN_Pos             0
#define ANACTRL_ACMPX_CSR_CP_EN_Msk             (0x1UL << ANACTRL_ACMPX_CSR_CP_EN_Pos)

/***************** Bit Definition for ANACTRL_DACX_CR Register **************/
#define ANACTRL_DACX_CR_ALIGN_Pos               15
#define ANACTRL_DACX_CR_ALIGN_Msk               (0x1UL << ANACTRL_DACX_CR_ALIGN_Pos)
#define ANACTRL_DACX_CR_ALIGN_R                 (0x0UL << ANACTRL_DACX_CR_ALIGN_Pos)
#define ANACTRL_DACX_CR_ALIGN_L                 (0x1UL << ANACTRL_DACX_CR_ALIGN_Pos)
#define ANACTRL_DACX_CR_VREF_SEL_Pos            14
#define ANACTRL_DACX_CR_VREF_SEL_Msk            (0x1UL << ANACTRL_DACX_CR_VREF_SEL_Pos)
#define ANACTRL_DACX_CR_VREF_SEL_VDDA           (0x0UL << ANACTRL_DACX_CR_VREF_SEL_Pos)
#define ANACTRL_DACX_CR_VREF_SEL_VREF           (0x1UL << ANACTRL_DACX_CR_VREF_SEL_Pos)
#define ANACTRL_DACX_CR_DMAUDRIE_Pos            13
#define ANACTRL_DACX_CR_DMAUDRIE_Msk            (0x1UL << ANACTRL_DACX_CR_DMAUDRIE_Pos)
#define ANACTRL_DACX_CR_DMAUDRIE_DIS            (0x0UL << ANACTRL_DACX_CR_DMAUDRIE_Pos)
#define ANACTRL_DACX_CR_DMAUDRIE_EN             (0x1UL << ANACTRL_DACX_CR_DMAUDRIE_Pos)
#define ANACTRL_DACX_CR_DMAEN_Pos               12
#define ANACTRL_DACX_CR_DMAEN_Msk               (0x1UL << ANACTRL_DACX_CR_DMAEN_Pos)
#define ANACTRL_DACX_CR_DMAEN_DIS               (0x0UL << ANACTRL_DACX_CR_DMAEN_Pos)
#define ANACTRL_DACX_CR_DMAEN_EN                (0x1UL << ANACTRL_DACX_CR_DMAEN_Pos)
#define ANACTRL_DACX_CR_MAMP_Pos                8
#define ANACTRL_DACX_CR_MAMP_Msk                (0xFUL << ANACTRL_DACX_CR_MAMP_Pos)
#define ANACTRL_DACX_CR_MAMP_1                  (0x0UL << ANACTRL_DACX_CR_MAMP_Pos)
#define ANACTRL_DACX_CR_MAMP_3                  (0x1UL << ANACTRL_DACX_CR_MAMP_Pos)
#define ANACTRL_DACX_CR_MAMP_7                  (0x2UL << ANACTRL_DACX_CR_MAMP_Pos)
#define ANACTRL_DACX_CR_MAMP_15                 (0x3UL << ANACTRL_DACX_CR_MAMP_Pos)
#define ANACTRL_DACX_CR_MAMP_31                 (0x4UL << ANACTRL_DACX_CR_MAMP_Pos)
#define ANACTRL_DACX_CR_MAMP_63                 (0x5UL << ANACTRL_DACX_CR_MAMP_Pos)
#define ANACTRL_DACX_CR_MAMP_127                (0x6UL << ANACTRL_DACX_CR_MAMP_Pos)
#define ANACTRL_DACX_CR_MAMP_255                (0x7UL << ANACTRL_DACX_CR_MAMP_Pos)
#define ANACTRL_DACX_CR_MAMP_511                (0x8UL << ANACTRL_DACX_CR_MAMP_Pos)
#define ANACTRL_DACX_CR_MAMP_1023               (0x9UL << ANACTRL_DACX_CR_MAMP_Pos)
#define ANACTRL_DACX_CR_MAMP_2047               (0xAUL << ANACTRL_DACX_CR_MAMP_Pos)
#define ANACTRL_DACX_CR_MAMP_4095               (0xBUL << ANACTRL_DACX_CR_MAMP_Pos)
//#define ANACTRL_DACX_CR_MAMP_4095             (0xCUL << ANACTRL_DACX_CR_MAMP_Pos)
//#define ANACTRL_DACX_CR_MAMP_4095             (0xDUL << ANACTRL_DACX_CR_MAMP_Pos)
//#define ANACTRL_DACX_CR_MAMP_4095             (0xEUL << ANACTRL_DACX_CR_MAMP_Pos)
//#define ANACTRL_DACX_CR_MAMP_4095             (0xFUL << ANACTRL_DACX_CR_MAMP_Pos)
#define ANACTRL_DACX_CR_WAVE_Pos                6
#define ANACTRL_DACX_CR_WAVE_Msk                (0x3UL << ANACTRL_DACX_CR_WAVE_Pos)
#define ANACTRL_DACX_CR_WAVE_DIS                (0x0UL << ANACTRL_DACX_CR_WAVE_Pos)
#define ANACTRL_DACX_CR_WAVE_NOISE              (0x1UL << ANACTRL_DACX_CR_WAVE_Pos)
#define ANACTRL_DACX_CR_WAVE_TRIANGLE           (0x2UL << ANACTRL_DACX_CR_WAVE_Pos)
//#define ANACTRL_DACX_CR_WAVE_TRIANGLE         (0x3UL << ANACTRL_DACX_CR_WAVE_Pos)
#define ANACTRL_DACX_CR_TSEL_Pos                3
#define ANACTRL_DACX_CR_TSEL_Msk                (0x7UL << ANACTRL_DACX_CR_TSEL_Pos)
#define ANACTRL_DACX_CR_TSEL_SWTRIG             (0x0UL << ANACTRL_DACX_CR_TSEL_Pos)
#define ANACTRL_DACX_CR_TSEL_TIM1_TRGO          (0x1UL << ANACTRL_DACX_CR_TSEL_Pos)
#define ANACTRL_DACX_CR_TSEL_TIM3_TRGO          (0x2UL << ANACTRL_DACX_CR_TSEL_Pos)
#define ANACTRL_DACX_CR_TSEL_TIM15_TRGO         (0x3UL << ANACTRL_DACX_CR_TSEL_Pos)
#define ANACTRL_DACX_CR_TSEL_TIM16_OC1          (0x4UL << ANACTRL_DACX_CR_TSEL_Pos)
#define ANACTRL_DACX_CR_TSEL_TIM17_OC1          (0x5UL << ANACTRL_DACX_CR_TSEL_Pos)
#define ANACTRL_DACX_CR_TSEL_EXTI_1             (0x6UL << ANACTRL_DACX_CR_TSEL_Pos)
#define ANACTRL_DACX_CR_TSEL_EXTI_9             (0x7UL << ANACTRL_DACX_CR_TSEL_Pos)
#define ANACTRL_DACX_CR_TEN_Pos                 1
#define ANACTRL_DACX_CR_TEN_Msk                 (0x3UL << ANACTRL_DACX_CR_TEN_Pos)
#define ANACTRL_DACX_CR_TEN_DIS                 (0x0UL << ANACTRL_DACX_CR_TEN_Pos)
#define ANACTRL_DACX_CR_TEN_RISING              (0x1UL << ANACTRL_DACX_CR_TEN_Pos)
#define ANACTRL_DACX_CR_TEN_FALLING             (0x2UL << ANACTRL_DACX_CR_TEN_Pos)
#define ANACTRL_DACX_CR_TEN_BOTH                (0x3UL << ANACTRL_DACX_CR_TEN_Pos)
#define ANACTRL_DACX_CR_EN_Pos                  0
#define ANACTRL_DACX_CR_EN_Msk                  (0x1UL << ANACTRL_DACX_CR_EN_Pos)
#define ANACTRL_DACX_CR_EN_DIS                  (0x0UL << ANACTRL_DACX_CR_EN_Pos)
#define ANACTRL_DACX_CR_EN_EN                   (0x1UL << ANACTRL_DACX_CR_EN_Pos)

/***************** Bit Definition for ANACTRL_DACX_CSR Register **************/
#define ANACTRL_DACX_CSR_DMAUDR_Pos             8
#define ANACTRL_DACX_CSR_DMAUDR_Msk             (0x1UL << ANACTRL_DACX_CSR_DMAUDR_Pos)
#define ANACTRL_DACX_CSR_SWTRIG_Pos             0
#define ANACTRL_DACX_CSR_SWTRIG_Msk             (0x1UL << ANACTRL_DACX_CSR_SWTRIG_Pos)

/***************** Bit Definition for ANACTRL_DACX_DHR Register **************/
#define ANACTRL_DACX_DHR_DHR_Pos                0
#define ANACTRL_DACX_DHR_DHR_Msk                (0xFFFFUL << ANACTRL_DACX_DHR_DHR_Pos)

/***************** Bit Definition for ANACTRL_DACX_DOR Register **************/
#define ANACTRL_DACX_DOR_DOR_Pos                0
#define ANACTRL_DACX_DOR_DOR_Msk                (0xFFFFUL << ANACTRL_DACX_DOR_DOR_Pos)

/***************** Bit Definition for ANACTRL_DACX_DIFF_CR1 Register **************/
#define ANACTRL_DACX_DIFF_CR1_INIT_DATA_Pos     16
#define ANACTRL_DACX_DIFF_CR1_INIT_DATA_Msk     (0xFFFFUL << ANACTRL_DACX_DIFF_CR1_INIT_DATA_Pos)
#define ANACTRL_DACX_DIFF_CR1_INIT_TRIM_Pos     8
#define ANACTRL_DACX_DIFF_CR1_INIT_TRIM_Msk     (0xFFUL << ANACTRL_DACX_DIFF_CR1_INIT_TRIM_Pos)
#define ANACTRL_DACX_DIFF_CR1_TRIG_INTV_Pos     4
#define ANACTRL_DACX_DIFF_CR1_TRIG_INTV_Msk     (0x7UL << ANACTRL_DACX_DIFF_CR1_TRIG_INTV_Pos)
#define ANACTRL_DACX_DIFF_CR1_INIT_MODE_Pos     0
#define ANACTRL_DACX_DIFF_CR1_INIT_MODE_Msk     (0x3UL << ANACTRL_DACX_DIFF_CR1_INIT_MODE_Pos)
#define ANACTRL_DACX_DIFF_CR1_INIT_MODE_CPU     (0x0UL)
#define ANACTRL_DACX_DIFF_CR1_INIT_MODE_ADC_INC (0x2UL)
#define ANACTRL_DACX_DIFF_CR1_INIT_MODE_ADC_DEC (0x3UL)

/***************** Bit Definition for ANACTRL_DACX_DIFF_CR2 Register **************/
#define ANACTRL_DACX_DIFF_CR2_DAC_TH_Pos        16
#define ANACTRL_DACX_DIFF_CR2_DAC_TH_Msk        (0xFFFFUL << ANACTRL_DACX_DIFF_CR2_DAC_TH_Pos)
#define ANACTRL_DACX_DIFF_CR2_DAC_INTV_Pos      8
#define ANACTRL_DACX_DIFF_CR2_DAC_INTV_Msk      (0xFFUL << ANACTRL_DACX_DIFF_CR2_DAC_INTV_Pos)
#define ANACTRL_DACX_DIFF_CR2_DAC_TRIM_Pos      0
#define ANACTRL_DACX_DIFF_CR2_DAC_TRIM_Msk      (0xFUL << ANACTRL_DACX_DIFF_CR2_DAC_TRIM_Pos)

/***************** Bit Definition for ANACTRL_DACX_DIFF_CR3 Register **************/
#define ANACTRL_DACX_DIFF_CR3_DIFF_TH_Pos       8
#define ANACTRL_DACX_DIFF_CR3_DIFF_TH_Msk       (0xFFUL << ANACTRL_DACX_DIFF_CR3_DIFF_TH_Pos)
#define ANACTRL_DACX_DIFF_CR3_DIFF_ROUND_Pos    4
#define ANACTRL_DACX_DIFF_CR3_DIFF_ROUND_Msk    (0xFUL << ANACTRL_DACX_DIFF_CR3_DIFF_ROUND_Pos)
#define ANACTRL_DACX_DIFF_CR3_DIFF_MODE_Pos     0
#define ANACTRL_DACX_DIFF_CR3_DIFF_MODE_Msk     (0x3UL << ANACTRL_DACX_DIFF_CR3_DIFF_MODE_Pos)

/***************** Bit Definition for ANACTRL_DACX_DIFF_CSR Register **************/
#define ANACTRL_DACX_DIFF_CSR_ERR_INTR_EN_Pos   4
#define ANACTRL_DACX_DIFF_CSR_ERR_INTR_EN_Msk   (0x1UL << ANACTRL_DACX_DIFF_CSR_ERR_INTR_EN_Pos)
#define ANACTRL_DACX_DIFF_CSR_ERR_INTR_EN_OFF   (0x0UL << ANACTRL_DACX_DIFF_CSR_ERR_INTR_EN_Pos)
#define ANACTRL_DACX_DIFF_CSR_ERR_INTR_EN_ON    (0x1UL << ANACTRL_DACX_DIFF_CSR_ERR_INTR_EN_Pos)
#define ANACTRL_DACX_DIFF_CSR_ERR_INTR_Pos      1
#define ANACTRL_DACX_DIFF_CSR_ERR_INTR_Msk      (0x1UL << ANACTRL_DACX_DIFF_CSR_ERR_INTR_Pos)
#define ANACTRL_DACX_DIFF_CSR_DIFF_EN_Pos       0
#define ANACTRL_DACX_DIFF_CSR_DIFF_EN_Msk       (0x1UL << ANACTRL_DACX_DIFF_CSR_DIFF_EN_Pos)
#define ANACTRL_DACX_DIFF_CSR_DIFF_EN_OFF       (0x0UL << ANACTRL_DACX_DIFF_CSR_DIFF_EN_Pos)
#define ANACTRL_DACX_DIFF_CSR_DIFF_EN_ON        (0x1UL << ANACTRL_DACX_DIFF_CSR_DIFF_EN_Pos)

/***************** Bit Definition for ANACTRL_KEY Register **************/
#define ANACTRL_KEY_Pos                         0
#define ANACTRL_KEY_Msk                         (0xFFFFFFFFUL << ANACTRL_KEY_Pos)
#define ANACTRL_KEY_VALUE                       0xA98BC56D

/***************** Bit Definition for ANACTRL_ANA_CSR Register **************/
//#define ANACTRL_ANA_CSR_DERIV_EN_Pos            16
//#define ANACTRL_ANA_CSR_DERIV_EN_Msk            (0x1UL <<ANACTRL_ANA_CSR_DERIV_EN_Pos)
#define ANACTRL_ANA_CSR_CP0_NES_Pos             10
#define ANACTRL_ANA_CSR_CP0_NES_Msk             (0x3UL <<ANACTRL_ANA_CSR_CP0_NES_Pos)
#define ANACTRL_ANA_CSR_CP0_PES_Pos             8
#define ANACTRL_ANA_CSR_CP0_PES_Msk             (0x3UL <<ANACTRL_ANA_CSR_CP0_PES_Pos)
//#define ANACTRL_ANA_CSR_DAC12_BUF_EN_Pos        4
//#define ANACTRL_ANA_CSR_DAC12_BUF_EN_Msk        (0x1UL <<ANACTRL_ANA_CSR_DAC12_BUF_EN_Pos)
#define ANACTRL_ANA_CSR_DAC8_BUF_SEL_Pos        1
#define ANACTRL_ANA_CSR_DAC8_BUF_SEL_Msk        (0x7UL <<ANACTRL_ANA_CSR_DAC8_BUF_SEL_Pos)
#define ANACTRL_ANA_CSR_DAC8_BUF_EN_Pos         0
#define ANACTRL_ANA_CSR_DAC8_BUF_EN_Msk         (0x1UL <<ANACTRL_ANA_CSR_DAC8_BUF_EN_Pos)

#define DAC_FLAG_DMAUDR                     ANACTRL_DACX_CSR_DMAUDR_Msk
#define DAC_IT_DMAUDR                       ANACTRL_DACX_CSR_DMAUDR_Msk
/***************** ANACTRL Declaration **************/
#define ANACTRL  ((ANACTRL_TypeDef *) (ANACTRL_ADDR_STR)) 
#define DAC0 ((DAC_TypeDef *) (ANACTRL_ADDR_STR + 0x40)) 
#define DAC1 ((DAC_TypeDef *) (ANACTRL_ADDR_STR + 0x50)) 
#define DAC2 ((DAC_TypeDef *) (ANACTRL_ADDR_STR + 0x60)) 
#define DAC3 ((DAC_TypeDef *) (ANACTRL_ADDR_STR + 0x70)) 
#define DAC4 ((DAC_TypeDef *) (ANACTRL_ADDR_STR + 0x80)) 
#define DAC5 ((DAC_TypeDef *) (ANACTRL_ADDR_STR + 0x90)) 


/***************** ANACTRL Function Definition **************/
void __STATIC_INLINE anactrl_unlock()
{
    ANACTRL->KEY = ANACTRL_KEY_VALUE;
}

void __STATIC_INLINE anactrl_lock()
{
    ANACTRL->KEY = 0x0;
}

void dac_cfg (DAC_TypeDef * dac_ptr, uint32_t align, uint32_t vref_sel, uint32_t dmaudrie,
        uint32_t dmaen, uint32_t mamp, uint32_t wave, uint32_t tsel, uint32_t ten, uint32_t en);
void dac_dma_dis (DAC_TypeDef * dac_ptr);
void dac_swtrig (DAC_TypeDef * dac_ptr);
void dac_dhr_set (DAC_TypeDef * dac_ptr, uint32_t data);
void dac_dmaudr_clr (DAC_TypeDef * dac_ptr);
void dac_wave_cfg (DAC_TypeDef * dac_ptr, uint32_t mamp, uint32_t wave);
void opa0_trim(uint32_t trim);
uint32_t get_opa0_trim(void);
uint32_t get_trim_FLAG(void);
void opa1_trim(uint32_t trim);
uint32_t get_opa1_trim(void);
void opa2_trim(uint32_t trim);
uint32_t get_opa2_trim(void);
void acmp0_trim(uint32_t trim);
uint32_t get_acmp0_trim(void);
void acmp1_trim(uint32_t trim);
uint32_t get_acmp1_trim(void);
void acmp2_trim(uint32_t trim);
uint32_t get_acmp2_trim(void);
void acmp3_trim(uint32_t trim);
uint32_t get_acmp3_trim(void);
void acmp4_trim(uint32_t trim);
uint32_t get_acmp4_trim(void);
void acmp5_trim(uint32_t trim);
uint32_t get_acmp5_trim(void);
void dac5_diff_cfg(uint32_t init_data, uint32_t init_trim,  uint32_t trig_intv, uint32_t init_mode,
                   uint32_t dac_th,    uint32_t dac_intv,   uint32_t dac_trim,
                   uint32_t diff_th,   uint32_t diff_round, uint32_t diff_mode);
void dac5_diff_en(void);
void dac5_diff_dis(void);
uint32_t get_dac5_diff_err_intr(void);
void clr_dac5_diff_err_intr(void);
void dac5_diff_err_intr_en(void);
void dac5_diff_err_intr_dis(void);

void DAC_DeInit(void);
void DAC_Init(DAC_TypeDef * dac_ptr, DAC_InitTypeDef* DAC_InitStruct);
void DAC_StructInit(DAC_InitTypeDef* DAC_InitStruct);
void DAC_Cmd(DAC_TypeDef * dac_ptr, FunctionalState NewState);
void DAC_SoftwareTriggerCmd(DAC_TypeDef * dac_ptr, FunctionalState NewState);
void DAC_WaveGenerationCmd(DAC_TypeDef * dac_ptr, uint32_t DAC_Wave, FunctionalState NewState);
void DAC_SetDac_8B_Data(DAC_TypeDef * dac_ptr, uint32_t DAC_Align,uint16_t Data);
void DAC_SetDac_12B_Data(DAC_TypeDef * dac_ptr, uint32_t DAC_Align,uint16_t Data);
uint8_t DAC_GetDataOutputValue_8bit(DAC_TypeDef * dac_ptr);
uint16_t DAC_GetDataOutputValue_12bit(DAC_TypeDef * dac_ptr);
void DAC_DMACmd(DAC_TypeDef * dac_ptr, FunctionalState NewState);
void DAC_ITConfig(DAC_TypeDef * dac_ptr, uint32_t DAC_IT, FunctionalState NewState);
	
//FlagStatus DAC_GetFlagStatus(DAC_TypeDef * dac_ptr, uint32_t DAC_FLAG);	
void DAC_ClearFlag(DAC_TypeDef * dac_ptr, uint32_t DAC_FLAG);
//ITStatus DAC_GetITStatus(DAC_TypeDef * dac_ptr, uint32_t DAC_IT);
void DAC_ClearITPendingBit(DAC_TypeDef * dac_ptr, uint32_t DAC_IT);
	
#endif // __ANACTRL_H__
