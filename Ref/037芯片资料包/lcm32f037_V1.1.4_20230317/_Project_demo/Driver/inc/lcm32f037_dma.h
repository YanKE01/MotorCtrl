/**
 ******************************************************************************
 * @file    lcm32f037_dma.h
 * @author  MCD Application Team
 * @version V0.4.44
 * @date    14-04-2021
 * @brief   This file contains all the functions prototypes for the DMA firmware
 *          library.
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef LCM32F037_DMA_H
#define LCM32F037_DMA_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "lcm32f037.h"
#define DMA_ReqNum_0 0UL
#define DMA_ReqNum_1 1UL
#define DMA_ReqNum_2 2UL
#define DMA_ReqNum_3 3UL
#define DMA_ReqNum_4 4UL
#define DMA_ReqNum_5 5UL
#define DMA_ReqNum_6 6UL
#define DMA_ReqNum_7 7UL
#define IS_REQ_NUM(DMA_ReqNum) ((DMA_ReqNum == DMA_ReqNum_0) || \
                                (DMA_ReqNum == DMA_ReqNum_1) || \
                                (DMA_ReqNum == DMA_ReqNum_2) || \
                                (DMA_ReqNum == DMA_ReqNum_3) || \
                                (DMA_ReqNum == DMA_ReqNum_4) || \
                                (DMA_ReqNum == DMA_ReqNum_5) || \
                                (DMA_ReqNum == DMA_ReqNum_6) || \
                                (DMA_ReqNum == DMA_ReqNum_7))
  /** @addtogroup LCM32F037_StdPeriph_Driver
   * @{
   */

  /** @addtogroup DMA
   * @{
   */
  /* Exported types ------------------------------------------------------------*/

  /**
   * @brief  DMA Init structures definition
   */
  typedef struct
  {
    uint32_t DMA_PeripheralBaseAddr; /*!< Specifies the peripheral base address for DMAy Channelx.              */

    uint32_t DMA_MemoryBaseAddr; /*!< Specifies the memory base address for DMAy Channelx.                  */

    uint32_t DMA_DIR; /*!< Specifies if the peripheral is the source or destination.
                                        This parameter can be a value of @ref DMA_data_transfer_direction     */

    uint32_t DMA_BufferSize; /*!< Specifies the buffer size, in data unit, of the specified Channel.
                                        The data unit is equal to the configuration set in DMA_PeripheralDataSize
                                        or DMA_MemoryDataSize members depending in the transfer direction     */

    uint32_t DMA_PeripheralInc; /*!< Specifies whether the Peripheral address register is incremented or not.
                                        This parameter can be a value of @ref DMA_peripheral_incremented_mode */

    uint32_t DMA_MemoryInc; /*!< Specifies whether the memory address register is incremented or not.
                                        This parameter can be a value of @ref DMA_memory_incremented_mode     */

    uint32_t DMA_PeripheralDataSize; /*!< Specifies the Peripheral data width.
                                        This parameter can be a value of @ref DMA_peripheral_data_size        */

    uint32_t DMA_MemoryDataSize; /*!< Specifies the Memory data width.
                                        This parameter can be a value of @ref DMA_memory_data_size            */

    uint32_t DMA_Mode; /*!< Specifies the operation mode of the DMAy Channelx.
                                        This parameter can be a value of @ref DMA_circular_normal_mode
                                        @note: The circular buffer mode cannot be used if the memory-to-memory
                                              data transfer is configured on the selected Channel */

    uint32_t DMA_Priority; /*!< Specifies the software priority for the DMAy Channelx.
                                        This parameter can be a value of @ref DMA_priority_level              */

    uint32_t DMA_M2M;   /*!< Specifies if the DMAy Channelx will be used in memory-to-memory transfer.
                                          This parameter can be a value of @ref DMA_memory_to_memory            */
    uint32_t DMA_MSIZE; /*!< SRC_MSIZE and DEST_MSIZE   */
  } DMA_InitTypeDef;

  /* Exported constants --------------------------------------------------------*/

  /** @defgroup DMA_Exported_Constants
   * @{
   */

#define IS_DMA_ALL_PERIPH(PERIPH) (((PERIPH) == DMA1_Channel1) || \
                                   ((PERIPH) == DMA1_Channel2) || \
                                   ((PERIPH) == DMA1_Channel3) || \
                                   ((PERIPH) == DMA1_Channel4) || \
                                   ((PERIPH) == DMA1_Channel5) || \
                                   ((PERIPH) == DMA1_Channel0))

  /** @defgroup DMA_data_transfer_direction
   * @{
   */

#define DMA_DIR_PeripheralSRC (0) /*P2M*/
#define DMA_DIR_PeripheralDST (1) /*M2P*/

#define IS_DMA_DIR(DIR) (((DIR) == DMA_DIR_PeripheralSRC) || \
                         ((DIR) == DMA_DIR_PeripheralDST))
  /**
   * @}
   */

  /** @defgroup DMA_peripheral_incremented_mode
   * @{
   */

#define DMA_PeripheralInc_Disable (3) /*P指针指向-固定-位置*/
#define DMA_PeripheralInc_Enable (0)  /*P指针递增*/

#define IS_DMA_PERIPHERAL_INC_STATE(STATE) (((STATE) == DMA_PeripheralInc_Disable) || \
                                            ((STATE) == DMA_PeripheralInc_Enable))
  /**
   * @}
   */

  /** @defgroup DMA_memory_incremented_mode
   * @{
   */

#define DMA_MemoryInc_Disable (3) /*M指针指向固定位置*/
#define DMA_MemoryInc_Enable (0)  /*M指针递增*/

#define IS_DMA_MEMORY_INC_STATE(STATE) (((STATE) == DMA_MemoryInc_Disable) || \
                                        ((STATE) == DMA_MemoryInc_Enable))
  /**
   * @}
   */

  /** @defgroup DMA_peripheral_data_size
   * @{
   */

#define DMA_PeripheralDataSize_Byte (0x0)     /*每次从*P读取8bits*/
#define DMA_PeripheralDataSize_HalfWord (0x1) /*每次从*P读取16bits*/
#define DMA_PeripheralDataSize_Word (0x2)     /*每次从*P读取32bits*/

#define IS_DMA_PERIPHERAL_DATA_SIZE(SIZE) (((SIZE) == DMA_PeripheralDataSize_Byte) ||     \
                                           ((SIZE) == DMA_PeripheralDataSize_HalfWord) || \
                                           ((SIZE) == DMA_PeripheralDataSize_Word))
  /**
   * @}
   */

  /** @defgroup DMA_memory_data_size
   * @{
   */

#define DMA_MemoryDataSize_Byte (0x0)     /*每次从*M读取8bits*/
#define DMA_MemoryDataSize_HalfWord (0x1) /*每次从*M读取16bits*/
#define DMA_MemoryDataSize_Word (0x2)     /*每次从*M读取32bits*/

#define IS_DMA_MEMORY_DATA_SIZE(SIZE) (((SIZE) == DMA_MemoryDataSize_Byte) ||     \
                                       ((SIZE) == DMA_MemoryDataSize_HalfWord) || \
                                       ((SIZE) == DMA_MemoryDataSize_Word))
  /**
   * @}
   */

  /** @defgroup DMA_circular_normal_mode
   * @{
   */

#define DMA_Mode_Normal (0)   /*一次性*/
#define DMA_Mode_Circular (1) /*有重载*/

#define IS_DMA_MODE(MODE) (((MODE) == DMA_Mode_Normal) || ((MODE) == DMA_Mode_Circular))
  /**
   * @}
   */

  /** @defgroup DMA_priority_level
   * @{
   */

#define DMA_Priority_VeryHigh (3) /*通道优先级*/
#define DMA_Priority_High (2)
#define DMA_Priority_Medium (1)
#define DMA_Priority_Low (0)

#define IS_DMA_PRIORITY(PRIORITY) (((PRIORITY) == DMA_Priority_VeryHigh) || \
                                   ((PRIORITY) == DMA_Priority_High) ||     \
                                   ((PRIORITY) == DMA_Priority_Medium) ||   \
                                   ((PRIORITY) == DMA_Priority_Low))
  /**
   * @}
   */

  /** @defgroup DMA_memory_to_memory
   * @{
   */

#define DMA_M2M_Disable (2) /*Peripheral to Memory transfer which DW_ahb_dmac is flow controler.*/
#define DMA_M2M_Enable (0)  /*需要软件握手*/

#define IS_DMA_M2M_STATE(STATE) (((STATE) == DMA_M2M_Disable) || ((STATE) == DMA_M2M_Enable))

#define DMA_MSIZE_1 (0)
#define DMA_MSIZE_4 (1)
#define DMA_MSIZE_8 (2)

#define IS_DMA_MSIZE(MSIZE) (((MSIZE) == DMA_MSIZE_1) || ((STATE) == DMA_MSIZE_4) || ((STATE) == DMA_MSIZE_8))

/**
 * @}
 */

/** @defgroup DMA_Remap_Config
 * @{
 */
#define DMAx_CHANNEL1_RMP 0x00000000
#define DMAx_CHANNEL2_RMP 0x10000000
#define DMAx_CHANNEL3_RMP 0x20000000
#define DMAx_CHANNEL4_RMP 0x30000000
#define DMAx_CHANNEL5_RMP 0x40000000
#define DMAx_CHANNEL6_RMP 0x50000000
#define DMAx_CHANNEL7_RMP 0x60000000

#define IS_DMA_ALL_LIST(LIST) ((LIST) == DMA1)

  /** @defgroup DMA_interrupts_definition
   * @{
   */

#define DMA_IT_TC (0) /*传输完成*/
#define DMA_IT_HT (1) /*传输完成一半*/
#define DMA_IT_TE (2) /*传输中出现错误*/

#define DMA1_FLAG_TC0 (0x00)
#define DMA1_FLAG_TE0 (0x10)
#define DMA1_FLAG_TC1 (0x01)
#define DMA1_FLAG_TE1 (0x11)
#define DMA1_FLAG_TC2 (0x02)
#define DMA1_FLAG_TE2 (0x12)
#define DMA1_FLAG_TC3 (0x03)
#define DMA1_FLAG_TE3 (0x13)
#define DMA1_FLAG_TC4 (0x04)
#define DMA1_FLAG_TE4 (0x14)
#define DMA1_FLAG_TC5 (0x05)
#define DMA1_FLAG_TE5 (0x15)

#define DMA1_IT_TC0 DMA1_FLAG_TC0
#define DMA1_IT_TE0 DMA1_FLAG_TE0
#define DMA1_IT_TC1 DMA1_FLAG_TC1
#define DMA1_IT_TE1 DMA1_FLAG_TE1
#define DMA1_IT_TC2 DMA1_FLAG_TC2
#define DMA1_IT_TE2 DMA1_FLAG_TE2
#define DMA1_IT_TC3 DMA1_FLAG_TC3
#define DMA1_IT_TE3 DMA1_FLAG_TE3
#define DMA1_IT_TC4 DMA1_FLAG_TC4
#define DMA1_IT_TE4 DMA1_FLAG_TE4
#define DMA1_IT_TC5 DMA1_FLAG_TC5
#define DMA1_IT_TE5 DMA1_FLAG_TE5

#define IS_DMA_CONFIG_IT(IT) ((IT == DMA1_IT_TC0) || \
                              (IT == DMA1_IT_TE0) || \
                              (IT == DMA1_IT_TC1) || \
                              (IT == DMA1_IT_TE1) || \
                              (IT == DMA1_IT_TC2) || \
                              (IT == DMA1_IT_TE2) || \
                              (IT == DMA1_IT_TC3) || \
                              (IT == DMA1_IT_TE3) || \
                              (IT == DMA1_IT_TC4) || \
                              (IT == DMA1_IT_TE4) || \
                              (IT == DMA1_IT_TC5) || \
                              (IT == DMA1_IT_TE5))

#define IS_DMA_CLEAR_FLAG(IT) ((IT == DMA1_IT_TC0) || \
                               (IT == DMA1_IT_TE0) || \
                               (IT == DMA1_IT_TC1) || \
                               (IT == DMA1_IT_TE1) || \
                               (IT == DMA1_IT_TC2) || \
                               (IT == DMA1_IT_TE2) || \
                               (IT == DMA1_IT_TC3) || \
                               (IT == DMA1_IT_TE3) || \
                               (IT == DMA1_IT_TC4) || \
                               (IT == DMA1_IT_TE4) || \
                               (IT == DMA1_IT_TC5) || \
                               (IT == DMA1_IT_TE5))

#define IS_DMA_GET_FLAG(DMAy_IT) ((DMAy_IT == DMA1_IT_TC0) || \
                                  (DMAy_IT == DMA1_IT_TE0) || \
                                  (DMAy_IT == DMA1_IT_TC1) || \
                                  (DMAy_IT == DMA1_IT_TE1) || \
                                  (DMAy_IT == DMA1_IT_TC2) || \
                                  (DMAy_IT == DMA1_IT_TE2) || \
                                  (DMAy_IT == DMA1_IT_TC3) || \
                                  (DMAy_IT == DMA1_IT_TE3) || \
                                  (DMAy_IT == DMA1_IT_TC4) || \
                                  (DMAy_IT == DMA1_IT_TE4) || \
                                  (DMAy_IT == DMA1_IT_TC5) || \
                                  (DMAy_IT == DMA1_IT_TE5))

#define IS_DMA_BUFFER_SIZE(SIZE) (((SIZE) >= 0x1) && ((SIZE) < 0x0xFFF))

/* REQ7,REQ6,REQ5,REQ4   */
#define DMA_REQ_TIM1_CH1 (0x00UL)
#define DMA_REQ_TIM1_CH2 (0x01UL)
#define DMA_REQ_TIM1_CH3 (0x02UL)
#define DMA_REQ_TIM1_UP (0x02UL)
#define DMA_REQ_TIM1_CH4 (0x03UL)
#define DMA_REQ_TIM1_TRIG (0x03UL)
#define DMA_REQ_TIM1_COM (0x03UL)
#define DMA_REQ_ADC (0x04UL)
#define DMA_REQ_TIM3_CH1 (0x05UL)
#define DMA_REQ_TIM3_TRIG (0x05UL)
#define DMA_REQ_TIM3_CH2 (0x06UL)
#define DMA_REQ_TIM3_CH3 (0x06UL)
#define DMA_REQ_TIM3_CH4 (0x07UL)
#define DMA_REQ_TIM3_UP (0x07UL)
#define DMA_REQ_TIM6 (0x08UL)
#define DMA_REQ_TIM15 (0x09UL)
#define DMA_REQ_TIM16 (10UL)
#define DMA_REQ_TIM17 (11UL)
#define DMA_REQ_DAC1 (14UL)
#define DMA_REQ_DAC0 (15UL)

/* REQ3,REQ2,REQ1,REQ0  */
#define DMA_REQ_UART0_TX (0x00UL)
#define DMA_REQ_UART0_RX (0x01UL)
#define DMA_REQ_UART1_TX (0x02UL)
#define DMA_REQ_UART1_RX (0x03UL)
#define DMA_REQ_I2C0_TX (0x04UL)
#define DMA_REQ_I2C0_RX (0x05UL)
#define DMA_REQ_SSP0_TX (0x06UL)
#define DMA_REQ_SSP0_RX (0x07UL)
#define DMA_REQ_SSP2_TX (14UL)
#define DMA_REQ_SSP2_RX (15UL)

#define DMA_ReqNum0 (0)
#define DMA_ReqNum1 (1)
#define DMA_ReqNum2 (2)
#define DMA_ReqNum3 (3)
#define DMA_ReqNum4 (4)
#define DMA_ReqNum5 (5)
#define DMA_ReqNum6 (6)
#define DMA_RqeNUM7 (7)
#define IS_DMAREQNUM(DMA_ReqNum) \
  ((DMA_ReqNum >= 0) && (DMA_ReqNum < 8))
#define IS_DMA_REQ(DMA_Request) \
  ((DMA_Request >= 0x00) && (DMA_Request <= 0x0F))

/**
 * @}
 */

/* =========================================================================================================================== */
/* ================                                           DMAC                                            ================ */
/* =========================================================================================================================== */

/* =========================================================  SAR0  ========================================================== */
#define DMAC_SAR0_SAR_Pos (0UL)          /*!< SAR (Bit 0)                                           */
#define DMAC_SAR0_SAR_Msk (0xffffffffUL) /*!< SAR (Bitfield-Mask: 0xffffffff)                       */
/* =========================================================  DAR0  ========================================================== */
#define DMAC_DAR0_DAR_Pos (0UL)          /*!< DAR (Bit 0)                                           */
#define DMAC_DAR0_DAR_Msk (0xffffffffUL) /*!< DAR (Bitfield-Mask: 0xffffffff)                       */
/* =========================================================  LLP0  ========================================================== */
#define DMAC_LLP0_LOC_Pos (2UL)          /*!< LOC (Bit 2)                                           */
#define DMAC_LLP0_LOC_Msk (0xfffffffcUL) /*!< LOC (Bitfield-Mask: 0x3fffffff)                       */
#define DMAC_LLP0_LMS_Pos (0UL)          /*!< LMS (Bit 0)                                           */
#define DMAC_LLP0_LMS_Msk (0x3UL)        /*!< LMS (Bitfield-Mask: 0x03)                             */
/* ========================================================  CTL0_L  ========================================================= */
#define DMAC_CTL0_L_LLP_SRC_EN_Pos (28UL)          /*!< LLP_SRC_EN (Bit 28)                                   */
#define DMAC_CTL0_L_LLP_SRC_EN_Msk (0x10000000UL)  /*!< LLP_SRC_EN (Bitfield-Mask: 0x01)                      */
#define DMAC_CTL0_L_LLP_DST_EN_Pos (27UL)          /*!< LLP_DST_EN (Bit 27)                                   */
#define DMAC_CTL0_L_LLP_DST_EN_Msk (0x8000000UL)   /*!< LLP_DST_EN (Bitfield-Mask: 0x01)                      */
#define DMAC_CTL0_L_SMS_Pos (25UL)                 /*!< SMS (Bit 25)                                          */
#define DMAC_CTL0_L_SMS_Msk (0x6000000UL)          /*!< SMS (Bitfield-Mask: 0x03)                             */
#define DMAC_CTL0_L_DMS_Pos (23UL)                 /*!< DMS (Bit 23)                                          */
#define DMAC_CTL0_L_DMS_Msk (0x1800000UL)          /*!< DMS (Bitfield-Mask: 0x03)                             */
#define DMAC_CTL0_L_TT_FC_Pos (20UL)               /*!< TT_FC (Bit 20)                                        */
#define DMAC_CTL0_L_TT_FC_Msk (0x700000UL)         /*!< TT_FC (Bitfield-Mask: 0x07)                           */
#define DMAC_CTL0_L_DST_SCATTER_EN_Pos (18UL)      /*!< DST_SCATTER_EN (Bit 18)                               */
#define DMAC_CTL0_L_DST_SCATTER_EN_Msk (0x40000UL) /*!< DST_SCATTER_EN (Bitfield-Mask: 0x01)                  */
#define DMAC_CTL0_L_SRC_GATHER_EN_Pos (17UL)       /*!< SRC_GATHER_EN (Bit 17)                                */
#define DMAC_CTL0_L_SRC_GATHER_EN_Msk (0x20000UL)  /*!< SRC_GATHER_EN (Bitfield-Mask: 0x01)                   */
#define DMAC_CTL0_L_SRC_MSIZE_Pos (14UL)           /*!< SRC_MSIZE (Bit 14)                                    */
#define DMAC_CTL0_L_SRC_MSIZE_Msk (0x1c000UL)      /*!< SRC_MSIZE (Bitfield-Mask: 0x07)                       */
#define DMAC_CTL0_L_DEST_MSIZE_Pos (11UL)          /*!< DEST_MSIZE (Bit 11)                                   */
#define DMAC_CTL0_L_DEST_MSIZE_Msk (0x3800UL)      /*!< DEST_MSIZE (Bitfield-Mask: 0x07)                      */
#define DMAC_CTL0_L_SINC_Pos (9UL)                 /*!< SINC (Bit 9)                                          */
#define DMAC_CTL0_L_SINC_Msk (0x600UL)             /*!< SINC (Bitfield-Mask: 0x03)                            */
#define DMAC_CTL0_L_DINC_Pos (7UL)                 /*!< DINC (Bit 7)                                          */
#define DMAC_CTL0_L_DINC_Msk (0x180UL)             /*!< DINC (Bitfield-Mask: 0x03)                            */
#define DMAC_CTL0_L_SRC_TR_WIDTH_Pos (4UL)         /*!< SRC_TR_WIDTH (Bit 4)                                  */
#define DMAC_CTL0_L_SRC_TR_WIDTH_Msk (0x70UL)      /*!< SRC_TR_WIDTH (Bitfield-Mask: 0x07)                    */
#define DMAC_CTL0_L_DST_TR_WIDTH_Pos (1UL)         /*!< DST_TR_WIDTH (Bit 1)                                  */
#define DMAC_CTL0_L_DST_TR_WIDTH_Msk (0xeUL)       /*!< DST_TR_WIDTH (Bitfield-Mask: 0x07)                    */
#define DMAC_CTL0_L_INT_EN_Pos (0UL)               /*!< INT_EN (Bit 0)                                        */
#define DMAC_CTL0_L_INT_EN_Msk (0x1UL)             /*!< INT_EN (Bitfield-Mask: 0x01)                          */
/* ========================================================  CTL0_H  ========================================================= */
#define DMAC_CTL0_H_DONE_Pos (12UL)        /*!< DONE (Bit 12)                                         */
#define DMAC_CTL0_H_DONE_Msk (0x1000UL)    /*!< DONE (Bitfield-Mask: 0x01)                            */
#define DMAC_CTL0_H_BLOCK_TS_Pos (0UL)     /*!< BLOCK_TS (Bit 0)                                      */
#define DMAC_CTL0_H_BLOCK_TS_Msk (0xfffUL) /*!< BLOCK_TS (Bitfield-Mask: 0xfff)                       */
/* ========================================================  SSTAT0  ========================================================= */
#define DMAC_SSTAT0_SSTAT_Pos (0UL)          /*!< SSTAT (Bit 0)                                         */
#define DMAC_SSTAT0_SSTAT_Msk (0xffffffffUL) /*!< SSTAT (Bitfield-Mask: 0xffffffff)                     */
/* ========================================================  DSTAT0  ========================================================= */
#define DMAC_DSTAT0_DSTAT_Pos (0UL)          /*!< DSTAT (Bit 0)                                         */
#define DMAC_DSTAT0_DSTAT_Msk (0xffffffffUL) /*!< DSTAT (Bitfield-Mask: 0xffffffff)                     */
/* =======================================================  SSTATAR0  ======================================================== */
#define DMAC_SSTATAR0_SSTATAR_Pos (0UL)          /*!< SSTATAR (Bit 0)                                       */
#define DMAC_SSTATAR0_SSTATAR_Msk (0xffffffffUL) /*!< SSTATAR (Bitfield-Mask: 0xffffffff)                   */
/* =======================================================  DSTATAR0  ======================================================== */
#define DMAC_DSTATAR0_DSTATAR_Pos (0UL)          /*!< DSTATAR (Bit 0)                                       */
#define DMAC_DSTATAR0_DSTATAR_Msk (0xffffffffUL) /*!< DSTATAR (Bitfield-Mask: 0xffffffff)                   */
/* ========================================================  CFG0_L  ========================================================= */
#define DMAC_CFG0_L_RELOAD_DST_Pos (31UL)         /*!< RELOAD_DST (Bit 31)                                   */
#define DMAC_CFG0_L_RELOAD_DST_Msk (0x80000000UL) /*!< RELOAD_DST (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG0_L_RELOAD_SRC_Pos (30UL)         /*!< RELOAD_SRC (Bit 30)                                   */
#define DMAC_CFG0_L_RELOAD_SRC_Msk (0x40000000UL) /*!< RELOAD_SRC (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG0_L_MAX_ABRST_Pos (20UL)          /*!< MAX_ABRST (Bit 20)                                    */
#define DMAC_CFG0_L_MAX_ABRST_Msk (0x3ff00000UL)  /*!< MAX_ABRST (Bitfield-Mask: 0x3ff)                      */
#define DMAC_CFG0_L_SRC_HS_POL_Pos (19UL)         /*!< SRC_HS_POL (Bit 19)                                   */
#define DMAC_CFG0_L_SRC_HS_POL_Msk (0x80000UL)    /*!< SRC_HS_POL (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG0_L_DST_HS_POL_Pos (18UL)         /*!< DST_HS_POL (Bit 18)                                   */
#define DMAC_CFG0_L_DST_HS_POL_Msk (0x40000UL)    /*!< DST_HS_POL (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG0_L_LOCK_B_Pos (17UL)             /*!< LOCK_B (Bit 17)                                       */
#define DMAC_CFG0_L_LOCK_B_Msk (0x20000UL)        /*!< LOCK_B (Bitfield-Mask: 0x01)                          */
#define DMAC_CFG0_L_LOCK_CH_Pos (16UL)            /*!< LOCK_CH (Bit 16)                                      */
#define DMAC_CFG0_L_LOCK_CH_Msk (0x10000UL)       /*!< LOCK_CH (Bitfield-Mask: 0x01)                         */
#define DMAC_CFG0_L_LOCK_B_L_Pos (14UL)           /*!< LOCK_B_L (Bit 14)                                     */
#define DMAC_CFG0_L_LOCK_B_L_Msk (0xc000UL)       /*!< LOCK_B_L (Bitfield-Mask: 0x03)                        */
#define DMAC_CFG0_L_LOCK_CH_L_Pos (12UL)          /*!< LOCK_CH_L (Bit 12)                                    */
#define DMAC_CFG0_L_LOCK_CH_L_Msk (0x3000UL)      /*!< LOCK_CH_L (Bitfield-Mask: 0x03)                       */
#define DMAC_CFG0_L_HS_SEL_SRC_Pos (11UL)         /*!< HS_SEL_SRC (Bit 11)                                   */
#define DMAC_CFG0_L_HS_SEL_SRC_Msk (0x800UL)      /*!< HS_SEL_SRC (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG0_L_HS_SEL_DST_Pos (10UL)         /*!< HS_SEL_DST (Bit 10)                                   */
#define DMAC_CFG0_L_HS_SEL_DST_Msk (0x400UL)      /*!< HS_SEL_DST (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG0_L_FIFO_EMPTY_Pos (9UL)          /*!< FIFO_EMPTY (Bit 9)                                    */
#define DMAC_CFG0_L_FIFO_EMPTY_Msk (0x200UL)      /*!< FIFO_EMPTY (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG0_L_CH_SUSP_Pos (8UL)             /*!< CH_SUSP (Bit 8)                                       */
#define DMAC_CFG0_L_CH_SUSP_Msk (0x100UL)         /*!< CH_SUSP (Bitfield-Mask: 0x01)                         */
#define DMAC_CFG0_L_CH_PRIOR_Pos (5UL)            /*!< CH_PRIOR (Bit 5)                                      */
#define DMAC_CFG0_L_CH_PRIOR_Msk (0xe0UL)         /*!< CH_PRIOR (Bitfield-Mask: 0x07)                        */
/* ========================================================  CFG0_H  ========================================================= */
#define DMAC_CFG0_H_DEST_PER_Pos (11UL)     /*!< DEST_PER (Bit 11)                                     */
#define DMAC_CFG0_H_DEST_PER_Msk (0x7800UL) /*!< DEST_PER (Bitfield-Mask: 0x0f)                        */
#define DMAC_CFG0_H_SRC_PER_Pos (7UL)       /*!< SRC_PER (Bit 7)                                       */
#define DMAC_CFG0_H_SRC_PER_Msk (0x780UL)   /*!< SRC_PER (Bitfield-Mask: 0x0f)                         */
#define DMAC_CFG0_H_SS_UPD_EN_Pos (6UL)     /*!< SS_UPD_EN (Bit 6)                                     */
#define DMAC_CFG0_H_SS_UPD_EN_Msk (0x40UL)  /*!< SS_UPD_EN (Bitfield-Mask: 0x01)                       */
#define DMAC_CFG0_H_DS_UPD_EN_Pos (5UL)     /*!< DS_UPD_EN (Bit 5)                                     */
#define DMAC_CFG0_H_DS_UPD_EN_Msk (0x20UL)  /*!< DS_UPD_EN (Bitfield-Mask: 0x01)                       */
#define DMAC_CFG0_H_PROTCTL_Pos (2UL)       /*!< PROTCTL (Bit 2)                                       */
#define DMAC_CFG0_H_PROTCTL_Msk (0x1cUL)    /*!< PROTCTL (Bitfield-Mask: 0x07)                         */
#define DMAC_CFG0_H_FIFO_MODE_Pos (1UL)     /*!< FIFO_MODE (Bit 1)                                     */
#define DMAC_CFG0_H_FIFO_MODE_Msk (0x2UL)   /*!< FIFO_MODE (Bitfield-Mask: 0x01)                       */
#define DMAC_CFG0_H_FCMODE_Pos (0UL)        /*!< FCMODE (Bit 0)                                        */
#define DMAC_CFG0_H_FCMODE_Msk (0x1UL)      /*!< FCMODE (Bitfield-Mask: 0x01)                          */
/* =========================================================  SGR0  ========================================================== */
#define DMAC_SGR0_SGC_Pos (20UL)         /*!< SGC (Bit 20)                                          */
#define DMAC_SGR0_SGC_Msk (0xfff00000UL) /*!< SGC (Bitfield-Mask: 0xfff)                            */
#define DMAC_SGR0_SGI_Pos (0UL)          /*!< SGI (Bit 0)                                           */
#define DMAC_SGR0_SGI_Msk (0xfffffUL)    /*!< SGI (Bitfield-Mask: 0xfffff)                          */
/* =========================================================  DSR0  ========================================================== */
#define DMAC_DSR0_DSC_Pos (20UL)         /*!< DSC (Bit 20)                                          */
#define DMAC_DSR0_DSC_Msk (0xfff00000UL) /*!< DSC (Bitfield-Mask: 0xfff)                            */
#define DMAC_DSR0_DSI_Pos (0UL)          /*!< DSI (Bit 0)                                           */
#define DMAC_DSR0_DSI_Msk (0xfffffUL)    /*!< DSI (Bitfield-Mask: 0xfffff)                          */
/* =========================================================  SAR1  ========================================================== */
#define DMAC_SAR1_SAR_Pos (0UL)          /*!< SAR (Bit 0)                                           */
#define DMAC_SAR1_SAR_Msk (0xffffffffUL) /*!< SAR (Bitfield-Mask: 0xffffffff)                       */
/* =========================================================  SAR2  ========================================================== */
#define DMAC_SAR2_SAR_Pos (0UL)          /*!< SAR (Bit 0)                                           */
#define DMAC_SAR2_SAR_Msk (0xffffffffUL) /*!< SAR (Bitfield-Mask: 0xffffffff)                       */
/* =========================================================  SAR3  ========================================================== */
#define DMAC_SAR3_SAR_Pos (0UL)          /*!< SAR (Bit 0)                                           */
#define DMAC_SAR3_SAR_Msk (0xffffffffUL) /*!< SAR (Bitfield-Mask: 0xffffffff)                       */
/* =========================================================  SAR4  ========================================================== */
#define DMAC_SAR4_SAR_Pos (0UL)          /*!< SAR (Bit 0)                                           */
#define DMAC_SAR4_SAR_Msk (0xffffffffUL) /*!< SAR (Bitfield-Mask: 0xffffffff)                       */
/* =========================================================  SAR5  ========================================================== */
#define DMAC_SAR5_SAR_Pos (0UL)          /*!< SAR (Bit 0)                                           */
#define DMAC_SAR5_SAR_Msk (0xffffffffUL) /*!< SAR (Bitfield-Mask: 0xffffffff)                       */
/* =========================================================  SAR6  ========================================================== */
#define DMAC_SAR6_SAR_Pos (0UL)          /*!< SAR (Bit 0)                                           */
#define DMAC_SAR6_SAR_Msk (0xffffffffUL) /*!< SAR (Bitfield-Mask: 0xffffffff)                       */
/* =========================================================  SAR7  ========================================================== */
#define DMAC_SAR7_SAR_Pos (0UL)          /*!< SAR (Bit 0)                                           */
#define DMAC_SAR7_SAR_Msk (0xffffffffUL) /*!< SAR (Bitfield-Mask: 0xffffffff)                       */
/* =========================================================  DAR1  ========================================================== */
#define DMAC_DAR1_DAR_Pos (0UL)          /*!< DAR (Bit 0)                                           */
#define DMAC_DAR1_DAR_Msk (0xffffffffUL) /*!< DAR (Bitfield-Mask: 0xffffffff)                       */
/* =========================================================  DAR2  ========================================================== */
#define DMAC_DAR2_DAR_Pos (0UL)          /*!< DAR (Bit 0)                                           */
#define DMAC_DAR2_DAR_Msk (0xffffffffUL) /*!< DAR (Bitfield-Mask: 0xffffffff)                       */
/* =========================================================  DAR3  ========================================================== */
#define DMAC_DAR3_DAR_Pos (0UL)          /*!< DAR (Bit 0)                                           */
#define DMAC_DAR3_DAR_Msk (0xffffffffUL) /*!< DAR (Bitfield-Mask: 0xffffffff)                       */
/* =========================================================  DAR4  ========================================================== */
#define DMAC_DAR4_DAR_Pos (0UL)          /*!< DAR (Bit 0)                                           */
#define DMAC_DAR4_DAR_Msk (0xffffffffUL) /*!< DAR (Bitfield-Mask: 0xffffffff)                       */
/* =========================================================  DAR5  ========================================================== */
#define DMAC_DAR5_DAR_Pos (0UL)          /*!< DAR (Bit 0)                                           */
#define DMAC_DAR5_DAR_Msk (0xffffffffUL) /*!< DAR (Bitfield-Mask: 0xffffffff)                       */
/* =========================================================  DAR6  ========================================================== */
#define DMAC_DAR6_DAR_Pos (0UL)          /*!< DAR (Bit 0)                                           */
#define DMAC_DAR6_DAR_Msk (0xffffffffUL) /*!< DAR (Bitfield-Mask: 0xffffffff)                       */
/* =========================================================  DAR7  ========================================================== */
#define DMAC_DAR7_DAR_Pos (0UL)          /*!< DAR (Bit 0)                                           */
#define DMAC_DAR7_DAR_Msk (0xffffffffUL) /*!< DAR (Bitfield-Mask: 0xffffffff)                       */
/* =========================================================  LLP1  ========================================================== */
#define DMAC_LLP1_LOC_Pos (2UL)          /*!< LOC (Bit 2)                                           */
#define DMAC_LLP1_LOC_Msk (0xfffffffcUL) /*!< LOC (Bitfield-Mask: 0x3fffffff)                       */
#define DMAC_LLP1_LMS_Pos (0UL)          /*!< LMS (Bit 0)                                           */
#define DMAC_LLP1_LMS_Msk (0x3UL)        /*!< LMS (Bitfield-Mask: 0x03)                             */
/* =========================================================  LLP2  ========================================================== */
#define DMAC_LLP2_LOC_Pos (2UL)          /*!< LOC (Bit 2)                                           */
#define DMAC_LLP2_LOC_Msk (0xfffffffcUL) /*!< LOC (Bitfield-Mask: 0x3fffffff)                       */
#define DMAC_LLP2_LMS_Pos (0UL)          /*!< LMS (Bit 0)                                           */
#define DMAC_LLP2_LMS_Msk (0x3UL)        /*!< LMS (Bitfield-Mask: 0x03)                             */
/* =========================================================  LLP3  ========================================================== */
#define DMAC_LLP3_LOC_Pos (2UL)          /*!< LOC (Bit 2)                                           */
#define DMAC_LLP3_LOC_Msk (0xfffffffcUL) /*!< LOC (Bitfield-Mask: 0x3fffffff)                       */
#define DMAC_LLP3_LMS_Pos (0UL)          /*!< LMS (Bit 0)                                           */
#define DMAC_LLP3_LMS_Msk (0x3UL)        /*!< LMS (Bitfield-Mask: 0x03)                             */
/* =========================================================  LLP4  ========================================================== */
#define DMAC_LLP4_LOC_Pos (2UL)          /*!< LOC (Bit 2)                                           */
#define DMAC_LLP4_LOC_Msk (0xfffffffcUL) /*!< LOC (Bitfield-Mask: 0x3fffffff)                       */
#define DMAC_LLP4_LMS_Pos (0UL)          /*!< LMS (Bit 0)                                           */
#define DMAC_LLP4_LMS_Msk (0x3UL)        /*!< LMS (Bitfield-Mask: 0x03)                             */
/* =========================================================  LLP5  ========================================================== */
#define DMAC_LLP5_LOC_Pos (2UL)          /*!< LOC (Bit 2)                                           */
#define DMAC_LLP5_LOC_Msk (0xfffffffcUL) /*!< LOC (Bitfield-Mask: 0x3fffffff)                       */
#define DMAC_LLP5_LMS_Pos (0UL)          /*!< LMS (Bit 0)                                           */
#define DMAC_LLP5_LMS_Msk (0x3UL)        /*!< LMS (Bitfield-Mask: 0x03)                             */
/* =========================================================  LLP6  ========================================================== */
#define DMAC_LLP6_LOC_Pos (2UL)          /*!< LOC (Bit 2)                                           */
#define DMAC_LLP6_LOC_Msk (0xfffffffcUL) /*!< LOC (Bitfield-Mask: 0x3fffffff)                       */
#define DMAC_LLP6_LMS_Pos (0UL)          /*!< LMS (Bit 0)                                           */
#define DMAC_LLP6_LMS_Msk (0x3UL)        /*!< LMS (Bitfield-Mask: 0x03)                             */
/* =========================================================  LLP7  ========================================================== */
#define DMAC_LLP7_LOC_Pos (2UL)          /*!< LOC (Bit 2)                                           */
#define DMAC_LLP7_LOC_Msk (0xfffffffcUL) /*!< LOC (Bitfield-Mask: 0x3fffffff)                       */
#define DMAC_LLP7_LMS_Pos (0UL)          /*!< LMS (Bit 0)                                           */
#define DMAC_LLP7_LMS_Msk (0x3UL)        /*!< LMS (Bitfield-Mask: 0x03)                             */
/* ========================================================  CTL1_L  ========================================================= */
#define DMAC_CTL1_L_LLP_SRC_EN_Pos (28UL)          /*!< LLP_SRC_EN (Bit 28)                                   */
#define DMAC_CTL1_L_LLP_SRC_EN_Msk (0x10000000UL)  /*!< LLP_SRC_EN (Bitfield-Mask: 0x01)                      */
#define DMAC_CTL1_L_LLP_DST_EN_Pos (27UL)          /*!< LLP_DST_EN (Bit 27)                                   */
#define DMAC_CTL1_L_LLP_DST_EN_Msk (0x8000000UL)   /*!< LLP_DST_EN (Bitfield-Mask: 0x01)                      */
#define DMAC_CTL1_L_SMS_Pos (25UL)                 /*!< SMS (Bit 25)                                          */
#define DMAC_CTL1_L_SMS_Msk (0x6000000UL)          /*!< SMS (Bitfield-Mask: 0x03)                             */
#define DMAC_CTL1_L_DMS_Pos (23UL)                 /*!< DMS (Bit 23)                                          */
#define DMAC_CTL1_L_DMS_Msk (0x1800000UL)          /*!< DMS (Bitfield-Mask: 0x03)                             */
#define DMAC_CTL1_L_TT_FC_Pos (20UL)               /*!< TT_FC (Bit 20)                                        */
#define DMAC_CTL1_L_TT_FC_Msk (0x700000UL)         /*!< TT_FC (Bitfield-Mask: 0x07)                           */
#define DMAC_CTL1_L_DST_SCATTER_EN_Pos (18UL)      /*!< DST_SCATTER_EN (Bit 18)                               */
#define DMAC_CTL1_L_DST_SCATTER_EN_Msk (0x40000UL) /*!< DST_SCATTER_EN (Bitfield-Mask: 0x01)                  */
#define DMAC_CTL1_L_SRC_GATHER_EN_Pos (17UL)       /*!< SRC_GATHER_EN (Bit 17)                                */
#define DMAC_CTL1_L_SRC_GATHER_EN_Msk (0x20000UL)  /*!< SRC_GATHER_EN (Bitfield-Mask: 0x01)                   */
#define DMAC_CTL1_L_SRC_MSIZE_Pos (14UL)           /*!< SRC_MSIZE (Bit 14)                                    */
#define DMAC_CTL1_L_SRC_MSIZE_Msk (0x1c000UL)      /*!< SRC_MSIZE (Bitfield-Mask: 0x07)                       */
#define DMAC_CTL1_L_DEST_MSIZE_Pos (11UL)          /*!< DEST_MSIZE (Bit 11)                                   */
#define DMAC_CTL1_L_DEST_MSIZE_Msk (0x3800UL)      /*!< DEST_MSIZE (Bitfield-Mask: 0x07)                      */
#define DMAC_CTL1_L_SINC_Pos (9UL)                 /*!< SINC (Bit 9)                                          */
#define DMAC_CTL1_L_SINC_Msk (0x600UL)             /*!< SINC (Bitfield-Mask: 0x03)                            */
#define DMAC_CTL1_L_DINC_Pos (7UL)                 /*!< DINC (Bit 7)                                          */
#define DMAC_CTL1_L_DINC_Msk (0x180UL)             /*!< DINC (Bitfield-Mask: 0x03)                            */
#define DMAC_CTL1_L_SRC_TR_WIDTH_Pos (4UL)         /*!< SRC_TR_WIDTH (Bit 4)                                  */
#define DMAC_CTL1_L_SRC_TR_WIDTH_Msk (0x70UL)      /*!< SRC_TR_WIDTH (Bitfield-Mask: 0x07)                    */
#define DMAC_CTL1_L_DST_TR_WIDTH_Pos (1UL)         /*!< DST_TR_WIDTH (Bit 1)                                  */
#define DMAC_CTL1_L_DST_TR_WIDTH_Msk (0xeUL)       /*!< DST_TR_WIDTH (Bitfield-Mask: 0x07)                    */
#define DMAC_CTL1_L_INT_EN_Pos (0UL)               /*!< INT_EN (Bit 0)                                        */
#define DMAC_CTL1_L_INT_EN_Msk (0x1UL)             /*!< INT_EN (Bitfield-Mask: 0x01)                          */
/* ========================================================  CTL2_L  ========================================================= */
#define DMAC_CTL2_L_LLP_SRC_EN_Pos (28UL)          /*!< LLP_SRC_EN (Bit 28)                                   */
#define DMAC_CTL2_L_LLP_SRC_EN_Msk (0x10000000UL)  /*!< LLP_SRC_EN (Bitfield-Mask: 0x01)                      */
#define DMAC_CTL2_L_LLP_DST_EN_Pos (27UL)          /*!< LLP_DST_EN (Bit 27)                                   */
#define DMAC_CTL2_L_LLP_DST_EN_Msk (0x8000000UL)   /*!< LLP_DST_EN (Bitfield-Mask: 0x01)                      */
#define DMAC_CTL2_L_SMS_Pos (25UL)                 /*!< SMS (Bit 25)                                          */
#define DMAC_CTL2_L_SMS_Msk (0x6000000UL)          /*!< SMS (Bitfield-Mask: 0x03)                             */
#define DMAC_CTL2_L_DMS_Pos (23UL)                 /*!< DMS (Bit 23)                                          */
#define DMAC_CTL2_L_DMS_Msk (0x1800000UL)          /*!< DMS (Bitfield-Mask: 0x03)                             */
#define DMAC_CTL2_L_TT_FC_Pos (20UL)               /*!< TT_FC (Bit 20)                                        */
#define DMAC_CTL2_L_TT_FC_Msk (0x700000UL)         /*!< TT_FC (Bitfield-Mask: 0x07)                           */
#define DMAC_CTL2_L_DST_SCATTER_EN_Pos (18UL)      /*!< DST_SCATTER_EN (Bit 18)                               */
#define DMAC_CTL2_L_DST_SCATTER_EN_Msk (0x40000UL) /*!< DST_SCATTER_EN (Bitfield-Mask: 0x01)                  */
#define DMAC_CTL2_L_SRC_GATHER_EN_Pos (17UL)       /*!< SRC_GATHER_EN (Bit 17)                                */
#define DMAC_CTL2_L_SRC_GATHER_EN_Msk (0x20000UL)  /*!< SRC_GATHER_EN (Bitfield-Mask: 0x01)                   */
#define DMAC_CTL2_L_SRC_MSIZE_Pos (14UL)           /*!< SRC_MSIZE (Bit 14)                                    */
#define DMAC_CTL2_L_SRC_MSIZE_Msk (0x1c000UL)      /*!< SRC_MSIZE (Bitfield-Mask: 0x07)                       */
#define DMAC_CTL2_L_DEST_MSIZE_Pos (11UL)          /*!< DEST_MSIZE (Bit 11)                                   */
#define DMAC_CTL2_L_DEST_MSIZE_Msk (0x3800UL)      /*!< DEST_MSIZE (Bitfield-Mask: 0x07)                      */
#define DMAC_CTL2_L_SINC_Pos (9UL)                 /*!< SINC (Bit 9)                                          */
#define DMAC_CTL2_L_SINC_Msk (0x600UL)             /*!< SINC (Bitfield-Mask: 0x03)                            */
#define DMAC_CTL2_L_DINC_Pos (7UL)                 /*!< DINC (Bit 7)                                          */
#define DMAC_CTL2_L_DINC_Msk (0x180UL)             /*!< DINC (Bitfield-Mask: 0x03)                            */
#define DMAC_CTL2_L_SRC_TR_WIDTH_Pos (4UL)         /*!< SRC_TR_WIDTH (Bit 4)                                  */
#define DMAC_CTL2_L_SRC_TR_WIDTH_Msk (0x70UL)      /*!< SRC_TR_WIDTH (Bitfield-Mask: 0x07)                    */
#define DMAC_CTL2_L_DST_TR_WIDTH_Pos (1UL)         /*!< DST_TR_WIDTH (Bit 1)                                  */
#define DMAC_CTL2_L_DST_TR_WIDTH_Msk (0xeUL)       /*!< DST_TR_WIDTH (Bitfield-Mask: 0x07)                    */
#define DMAC_CTL2_L_INT_EN_Pos (0UL)               /*!< INT_EN (Bit 0)                                        */
#define DMAC_CTL2_L_INT_EN_Msk (0x1UL)             /*!< INT_EN (Bitfield-Mask: 0x01)                          */
/* ========================================================  CTL3_L  ========================================================= */
#define DMAC_CTL3_L_LLP_SRC_EN_Pos (28UL)          /*!< LLP_SRC_EN (Bit 28)                                   */
#define DMAC_CTL3_L_LLP_SRC_EN_Msk (0x10000000UL)  /*!< LLP_SRC_EN (Bitfield-Mask: 0x01)                      */
#define DMAC_CTL3_L_LLP_DST_EN_Pos (27UL)          /*!< LLP_DST_EN (Bit 27)                                   */
#define DMAC_CTL3_L_LLP_DST_EN_Msk (0x8000000UL)   /*!< LLP_DST_EN (Bitfield-Mask: 0x01)                      */
#define DMAC_CTL3_L_SMS_Pos (25UL)                 /*!< SMS (Bit 25)                                          */
#define DMAC_CTL3_L_SMS_Msk (0x6000000UL)          /*!< SMS (Bitfield-Mask: 0x03)                             */
#define DMAC_CTL3_L_DMS_Pos (23UL)                 /*!< DMS (Bit 23)                                          */
#define DMAC_CTL3_L_DMS_Msk (0x1800000UL)          /*!< DMS (Bitfield-Mask: 0x03)                             */
#define DMAC_CTL3_L_TT_FC_Pos (20UL)               /*!< TT_FC (Bit 20)                                        */
#define DMAC_CTL3_L_TT_FC_Msk (0x700000UL)         /*!< TT_FC (Bitfield-Mask: 0x07)                           */
#define DMAC_CTL3_L_DST_SCATTER_EN_Pos (18UL)      /*!< DST_SCATTER_EN (Bit 18)                               */
#define DMAC_CTL3_L_DST_SCATTER_EN_Msk (0x40000UL) /*!< DST_SCATTER_EN (Bitfield-Mask: 0x01)                  */
#define DMAC_CTL3_L_SRC_GATHER_EN_Pos (17UL)       /*!< SRC_GATHER_EN (Bit 17)                                */
#define DMAC_CTL3_L_SRC_GATHER_EN_Msk (0x20000UL)  /*!< SRC_GATHER_EN (Bitfield-Mask: 0x01)                   */
#define DMAC_CTL3_L_SRC_MSIZE_Pos (14UL)           /*!< SRC_MSIZE (Bit 14)                                    */
#define DMAC_CTL3_L_SRC_MSIZE_Msk (0x1c000UL)      /*!< SRC_MSIZE (Bitfield-Mask: 0x07)                       */
#define DMAC_CTL3_L_DEST_MSIZE_Pos (11UL)          /*!< DEST_MSIZE (Bit 11)                                   */
#define DMAC_CTL3_L_DEST_MSIZE_Msk (0x3800UL)      /*!< DEST_MSIZE (Bitfield-Mask: 0x07)                      */
#define DMAC_CTL3_L_SINC_Pos (9UL)                 /*!< SINC (Bit 9)                                          */
#define DMAC_CTL3_L_SINC_Msk (0x600UL)             /*!< SINC (Bitfield-Mask: 0x03)                            */
#define DMAC_CTL3_L_DINC_Pos (7UL)                 /*!< DINC (Bit 7)                                          */
#define DMAC_CTL3_L_DINC_Msk (0x180UL)             /*!< DINC (Bitfield-Mask: 0x03)                            */
#define DMAC_CTL3_L_SRC_TR_WIDTH_Pos (4UL)         /*!< SRC_TR_WIDTH (Bit 4)                                  */
#define DMAC_CTL3_L_SRC_TR_WIDTH_Msk (0x70UL)      /*!< SRC_TR_WIDTH (Bitfield-Mask: 0x07)                    */
#define DMAC_CTL3_L_DST_TR_WIDTH_Pos (1UL)         /*!< DST_TR_WIDTH (Bit 1)                                  */
#define DMAC_CTL3_L_DST_TR_WIDTH_Msk (0xeUL)       /*!< DST_TR_WIDTH (Bitfield-Mask: 0x07)                    */
#define DMAC_CTL3_L_INT_EN_Pos (0UL)               /*!< INT_EN (Bit 0)                                        */
#define DMAC_CTL3_L_INT_EN_Msk (0x1UL)             /*!< INT_EN (Bitfield-Mask: 0x01)                          */
/* ========================================================  CTL4_L  ========================================================= */
#define DMAC_CTL4_L_LLP_SRC_EN_Pos (28UL)          /*!< LLP_SRC_EN (Bit 28)                                   */
#define DMAC_CTL4_L_LLP_SRC_EN_Msk (0x10000000UL)  /*!< LLP_SRC_EN (Bitfield-Mask: 0x01)                      */
#define DMAC_CTL4_L_LLP_DST_EN_Pos (27UL)          /*!< LLP_DST_EN (Bit 27)                                   */
#define DMAC_CTL4_L_LLP_DST_EN_Msk (0x8000000UL)   /*!< LLP_DST_EN (Bitfield-Mask: 0x01)                      */
#define DMAC_CTL4_L_SMS_Pos (25UL)                 /*!< SMS (Bit 25)                                          */
#define DMAC_CTL4_L_SMS_Msk (0x6000000UL)          /*!< SMS (Bitfield-Mask: 0x03)                             */
#define DMAC_CTL4_L_DMS_Pos (23UL)                 /*!< DMS (Bit 23)                                          */
#define DMAC_CTL4_L_DMS_Msk (0x1800000UL)          /*!< DMS (Bitfield-Mask: 0x03)                             */
#define DMAC_CTL4_L_TT_FC_Pos (20UL)               /*!< TT_FC (Bit 20)                                        */
#define DMAC_CTL4_L_TT_FC_Msk (0x700000UL)         /*!< TT_FC (Bitfield-Mask: 0x07)                           */
#define DMAC_CTL4_L_DST_SCATTER_EN_Pos (18UL)      /*!< DST_SCATTER_EN (Bit 18)                               */
#define DMAC_CTL4_L_DST_SCATTER_EN_Msk (0x40000UL) /*!< DST_SCATTER_EN (Bitfield-Mask: 0x01)                  */
#define DMAC_CTL4_L_SRC_GATHER_EN_Pos (17UL)       /*!< SRC_GATHER_EN (Bit 17)                                */
#define DMAC_CTL4_L_SRC_GATHER_EN_Msk (0x20000UL)  /*!< SRC_GATHER_EN (Bitfield-Mask: 0x01)                   */
#define DMAC_CTL4_L_SRC_MSIZE_Pos (14UL)           /*!< SRC_MSIZE (Bit 14)                                    */
#define DMAC_CTL4_L_SRC_MSIZE_Msk (0x1c000UL)      /*!< SRC_MSIZE (Bitfield-Mask: 0x07)                       */
#define DMAC_CTL4_L_DEST_MSIZE_Pos (11UL)          /*!< DEST_MSIZE (Bit 11)                                   */
#define DMAC_CTL4_L_DEST_MSIZE_Msk (0x3800UL)      /*!< DEST_MSIZE (Bitfield-Mask: 0x07)                      */
#define DMAC_CTL4_L_SINC_Pos (9UL)                 /*!< SINC (Bit 9)                                          */
#define DMAC_CTL4_L_SINC_Msk (0x600UL)             /*!< SINC (Bitfield-Mask: 0x03)                            */
#define DMAC_CTL4_L_DINC_Pos (7UL)                 /*!< DINC (Bit 7)                                          */
#define DMAC_CTL4_L_DINC_Msk (0x180UL)             /*!< DINC (Bitfield-Mask: 0x03)                            */
#define DMAC_CTL4_L_SRC_TR_WIDTH_Pos (4UL)         /*!< SRC_TR_WIDTH (Bit 4)                                  */
#define DMAC_CTL4_L_SRC_TR_WIDTH_Msk (0x70UL)      /*!< SRC_TR_WIDTH (Bitfield-Mask: 0x07)                    */
#define DMAC_CTL4_L_DST_TR_WIDTH_Pos (1UL)         /*!< DST_TR_WIDTH (Bit 1)                                  */
#define DMAC_CTL4_L_DST_TR_WIDTH_Msk (0xeUL)       /*!< DST_TR_WIDTH (Bitfield-Mask: 0x07)                    */
#define DMAC_CTL4_L_INT_EN_Pos (0UL)               /*!< INT_EN (Bit 0)                                        */
#define DMAC_CTL4_L_INT_EN_Msk (0x1UL)             /*!< INT_EN (Bitfield-Mask: 0x01)                          */
/* ========================================================  CTL5_L  ========================================================= */
#define DMAC_CTL5_L_LLP_SRC_EN_Pos (28UL)          /*!< LLP_SRC_EN (Bit 28)                                   */
#define DMAC_CTL5_L_LLP_SRC_EN_Msk (0x10000000UL)  /*!< LLP_SRC_EN (Bitfield-Mask: 0x01)                      */
#define DMAC_CTL5_L_LLP_DST_EN_Pos (27UL)          /*!< LLP_DST_EN (Bit 27)                                   */
#define DMAC_CTL5_L_LLP_DST_EN_Msk (0x8000000UL)   /*!< LLP_DST_EN (Bitfield-Mask: 0x01)                      */
#define DMAC_CTL5_L_SMS_Pos (25UL)                 /*!< SMS (Bit 25)                                          */
#define DMAC_CTL5_L_SMS_Msk (0x6000000UL)          /*!< SMS (Bitfield-Mask: 0x03)                             */
#define DMAC_CTL5_L_DMS_Pos (23UL)                 /*!< DMS (Bit 23)                                          */
#define DMAC_CTL5_L_DMS_Msk (0x1800000UL)          /*!< DMS (Bitfield-Mask: 0x03)                             */
#define DMAC_CTL5_L_TT_FC_Pos (20UL)               /*!< TT_FC (Bit 20)                                        */
#define DMAC_CTL5_L_TT_FC_Msk (0x700000UL)         /*!< TT_FC (Bitfield-Mask: 0x07)                           */
#define DMAC_CTL5_L_DST_SCATTER_EN_Pos (18UL)      /*!< DST_SCATTER_EN (Bit 18)                               */
#define DMAC_CTL5_L_DST_SCATTER_EN_Msk (0x40000UL) /*!< DST_SCATTER_EN (Bitfield-Mask: 0x01)                  */
#define DMAC_CTL5_L_SRC_GATHER_EN_Pos (17UL)       /*!< SRC_GATHER_EN (Bit 17)                                */
#define DMAC_CTL5_L_SRC_GATHER_EN_Msk (0x20000UL)  /*!< SRC_GATHER_EN (Bitfield-Mask: 0x01)                   */
#define DMAC_CTL5_L_SRC_MSIZE_Pos (14UL)           /*!< SRC_MSIZE (Bit 14)                                    */
#define DMAC_CTL5_L_SRC_MSIZE_Msk (0x1c000UL)      /*!< SRC_MSIZE (Bitfield-Mask: 0x07)                       */
#define DMAC_CTL5_L_DEST_MSIZE_Pos (11UL)          /*!< DEST_MSIZE (Bit 11)                                   */
#define DMAC_CTL5_L_DEST_MSIZE_Msk (0x3800UL)      /*!< DEST_MSIZE (Bitfield-Mask: 0x07)                      */
#define DMAC_CTL5_L_SINC_Pos (9UL)                 /*!< SINC (Bit 9)                                          */
#define DMAC_CTL5_L_SINC_Msk (0x600UL)             /*!< SINC (Bitfield-Mask: 0x03)                            */
#define DMAC_CTL5_L_DINC_Pos (7UL)                 /*!< DINC (Bit 7)                                          */
#define DMAC_CTL5_L_DINC_Msk (0x180UL)             /*!< DINC (Bitfield-Mask: 0x03)                            */
#define DMAC_CTL5_L_SRC_TR_WIDTH_Pos (4UL)         /*!< SRC_TR_WIDTH (Bit 4)                                  */
#define DMAC_CTL5_L_SRC_TR_WIDTH_Msk (0x70UL)      /*!< SRC_TR_WIDTH (Bitfield-Mask: 0x07)                    */
#define DMAC_CTL5_L_DST_TR_WIDTH_Pos (1UL)         /*!< DST_TR_WIDTH (Bit 1)                                  */
#define DMAC_CTL5_L_DST_TR_WIDTH_Msk (0xeUL)       /*!< DST_TR_WIDTH (Bitfield-Mask: 0x07)                    */
#define DMAC_CTL5_L_INT_EN_Pos (0UL)               /*!< INT_EN (Bit 0)                                        */
#define DMAC_CTL5_L_INT_EN_Msk (0x1UL)             /*!< INT_EN (Bitfield-Mask: 0x01)                          */
/* ========================================================  CTL6_L  ========================================================= */
#define DMAC_CTL6_L_LLP_SRC_EN_Pos (28UL)          /*!< LLP_SRC_EN (Bit 28)                                   */
#define DMAC_CTL6_L_LLP_SRC_EN_Msk (0x10000000UL)  /*!< LLP_SRC_EN (Bitfield-Mask: 0x01)                      */
#define DMAC_CTL6_L_LLP_DST_EN_Pos (27UL)          /*!< LLP_DST_EN (Bit 27)                                   */
#define DMAC_CTL6_L_LLP_DST_EN_Msk (0x8000000UL)   /*!< LLP_DST_EN (Bitfield-Mask: 0x01)                      */
#define DMAC_CTL6_L_SMS_Pos (25UL)                 /*!< SMS (Bit 25)                                          */
#define DMAC_CTL6_L_SMS_Msk (0x6000000UL)          /*!< SMS (Bitfield-Mask: 0x03)                             */
#define DMAC_CTL6_L_DMS_Pos (23UL)                 /*!< DMS (Bit 23)                                          */
#define DMAC_CTL6_L_DMS_Msk (0x1800000UL)          /*!< DMS (Bitfield-Mask: 0x03)                             */
#define DMAC_CTL6_L_TT_FC_Pos (20UL)               /*!< TT_FC (Bit 20)                                        */
#define DMAC_CTL6_L_TT_FC_Msk (0x700000UL)         /*!< TT_FC (Bitfield-Mask: 0x07)                           */
#define DMAC_CTL6_L_DST_SCATTER_EN_Pos (18UL)      /*!< DST_SCATTER_EN (Bit 18)                               */
#define DMAC_CTL6_L_DST_SCATTER_EN_Msk (0x40000UL) /*!< DST_SCATTER_EN (Bitfield-Mask: 0x01)                  */
#define DMAC_CTL6_L_SRC_GATHER_EN_Pos (17UL)       /*!< SRC_GATHER_EN (Bit 17)                                */
#define DMAC_CTL6_L_SRC_GATHER_EN_Msk (0x20000UL)  /*!< SRC_GATHER_EN (Bitfield-Mask: 0x01)                   */
#define DMAC_CTL6_L_SRC_MSIZE_Pos (14UL)           /*!< SRC_MSIZE (Bit 14)                                    */
#define DMAC_CTL6_L_SRC_MSIZE_Msk (0x1c000UL)      /*!< SRC_MSIZE (Bitfield-Mask: 0x07)                       */
#define DMAC_CTL6_L_DEST_MSIZE_Pos (11UL)          /*!< DEST_MSIZE (Bit 11)                                   */
#define DMAC_CTL6_L_DEST_MSIZE_Msk (0x3800UL)      /*!< DEST_MSIZE (Bitfield-Mask: 0x07)                      */
#define DMAC_CTL6_L_SINC_Pos (9UL)                 /*!< SINC (Bit 9)                                          */
#define DMAC_CTL6_L_SINC_Msk (0x600UL)             /*!< SINC (Bitfield-Mask: 0x03)                            */
#define DMAC_CTL6_L_DINC_Pos (7UL)                 /*!< DINC (Bit 7)                                          */
#define DMAC_CTL6_L_DINC_Msk (0x180UL)             /*!< DINC (Bitfield-Mask: 0x03)                            */
#define DMAC_CTL6_L_SRC_TR_WIDTH_Pos (4UL)         /*!< SRC_TR_WIDTH (Bit 4)                                  */
#define DMAC_CTL6_L_SRC_TR_WIDTH_Msk (0x70UL)      /*!< SRC_TR_WIDTH (Bitfield-Mask: 0x07)                    */
#define DMAC_CTL6_L_DST_TR_WIDTH_Pos (1UL)         /*!< DST_TR_WIDTH (Bit 1)                                  */
#define DMAC_CTL6_L_DST_TR_WIDTH_Msk (0xeUL)       /*!< DST_TR_WIDTH (Bitfield-Mask: 0x07)                    */
#define DMAC_CTL6_L_INT_EN_Pos (0UL)               /*!< INT_EN (Bit 0)                                        */
#define DMAC_CTL6_L_INT_EN_Msk (0x1UL)             /*!< INT_EN (Bitfield-Mask: 0x01)                          */
/* ========================================================  CTL7_L  ========================================================= */
#define DMAC_CTL7_L_LLP_SRC_EN_Pos (28UL)          /*!< LLP_SRC_EN (Bit 28)                                   */
#define DMAC_CTL7_L_LLP_SRC_EN_Msk (0x10000000UL)  /*!< LLP_SRC_EN (Bitfield-Mask: 0x01)                      */
#define DMAC_CTL7_L_LLP_DST_EN_Pos (27UL)          /*!< LLP_DST_EN (Bit 27)                                   */
#define DMAC_CTL7_L_LLP_DST_EN_Msk (0x8000000UL)   /*!< LLP_DST_EN (Bitfield-Mask: 0x01)                      */
#define DMAC_CTL7_L_SMS_Pos (25UL)                 /*!< SMS (Bit 25)                                          */
#define DMAC_CTL7_L_SMS_Msk (0x6000000UL)          /*!< SMS (Bitfield-Mask: 0x03)                             */
#define DMAC_CTL7_L_DMS_Pos (23UL)                 /*!< DMS (Bit 23)                                          */
#define DMAC_CTL7_L_DMS_Msk (0x1800000UL)          /*!< DMS (Bitfield-Mask: 0x03)                             */
#define DMAC_CTL7_L_TT_FC_Pos (20UL)               /*!< TT_FC (Bit 20)                                        */
#define DMAC_CTL7_L_TT_FC_Msk (0x700000UL)         /*!< TT_FC (Bitfield-Mask: 0x07)                           */
#define DMAC_CTL7_L_DST_SCATTER_EN_Pos (18UL)      /*!< DST_SCATTER_EN (Bit 18)                               */
#define DMAC_CTL7_L_DST_SCATTER_EN_Msk (0x40000UL) /*!< DST_SCATTER_EN (Bitfield-Mask: 0x01)                  */
#define DMAC_CTL7_L_SRC_GATHER_EN_Pos (17UL)       /*!< SRC_GATHER_EN (Bit 17)                                */
#define DMAC_CTL7_L_SRC_GATHER_EN_Msk (0x20000UL)  /*!< SRC_GATHER_EN (Bitfield-Mask: 0x01)                   */
#define DMAC_CTL7_L_SRC_MSIZE_Pos (14UL)           /*!< SRC_MSIZE (Bit 14)                                    */
#define DMAC_CTL7_L_SRC_MSIZE_Msk (0x1c000UL)      /*!< SRC_MSIZE (Bitfield-Mask: 0x07)                       */
#define DMAC_CTL7_L_DEST_MSIZE_Pos (11UL)          /*!< DEST_MSIZE (Bit 11)                                   */
#define DMAC_CTL7_L_DEST_MSIZE_Msk (0x3800UL)      /*!< DEST_MSIZE (Bitfield-Mask: 0x07)                      */
#define DMAC_CTL7_L_SINC_Pos (9UL)                 /*!< SINC (Bit 9)                                          */
#define DMAC_CTL7_L_SINC_Msk (0x600UL)             /*!< SINC (Bitfield-Mask: 0x03)                            */
#define DMAC_CTL7_L_DINC_Pos (7UL)                 /*!< DINC (Bit 7)                                          */
#define DMAC_CTL7_L_DINC_Msk (0x180UL)             /*!< DINC (Bitfield-Mask: 0x03)                            */
#define DMAC_CTL7_L_SRC_TR_WIDTH_Pos (4UL)         /*!< SRC_TR_WIDTH (Bit 4)                                  */
#define DMAC_CTL7_L_SRC_TR_WIDTH_Msk (0x70UL)      /*!< SRC_TR_WIDTH (Bitfield-Mask: 0x07)                    */
#define DMAC_CTL7_L_DST_TR_WIDTH_Pos (1UL)         /*!< DST_TR_WIDTH (Bit 1)                                  */
#define DMAC_CTL7_L_DST_TR_WIDTH_Msk (0xeUL)       /*!< DST_TR_WIDTH (Bitfield-Mask: 0x07)                    */
#define DMAC_CTL7_L_INT_EN_Pos (0UL)               /*!< INT_EN (Bit 0)                                        */
#define DMAC_CTL7_L_INT_EN_Msk (0x1UL)             /*!< INT_EN (Bitfield-Mask: 0x01)                          */
/* ========================================================  CTL1_H  ========================================================= */
#define DMAC_CTL1_H_DONE_Pos (12UL)        /*!< DONE (Bit 12)                                         */
#define DMAC_CTL1_H_DONE_Msk (0x1000UL)    /*!< DONE (Bitfield-Mask: 0x01)                            */
#define DMAC_CTL1_H_BLOCK_TS_Pos (0UL)     /*!< BLOCK_TS (Bit 0)                                      */
#define DMAC_CTL1_H_BLOCK_TS_Msk (0xfffUL) /*!< BLOCK_TS (Bitfield-Mask: 0xfff)                       */
/* ========================================================  CTL2_H  ========================================================= */
#define DMAC_CTL2_H_DONE_Pos (12UL)        /*!< DONE (Bit 12)                                         */
#define DMAC_CTL2_H_DONE_Msk (0x1000UL)    /*!< DONE (Bitfield-Mask: 0x01)                            */
#define DMAC_CTL2_H_BLOCK_TS_Pos (0UL)     /*!< BLOCK_TS (Bit 0)                                      */
#define DMAC_CTL2_H_BLOCK_TS_Msk (0xfffUL) /*!< BLOCK_TS (Bitfield-Mask: 0xfff)                       */
/* ========================================================  CTL3_H  ========================================================= */
#define DMAC_CTL3_H_DONE_Pos (12UL)        /*!< DONE (Bit 12)                                         */
#define DMAC_CTL3_H_DONE_Msk (0x1000UL)    /*!< DONE (Bitfield-Mask: 0x01)                            */
#define DMAC_CTL3_H_BLOCK_TS_Pos (0UL)     /*!< BLOCK_TS (Bit 0)                                      */
#define DMAC_CTL3_H_BLOCK_TS_Msk (0xfffUL) /*!< BLOCK_TS (Bitfield-Mask: 0xfff)                       */
/* ========================================================  CTL4_H  ========================================================= */
#define DMAC_CTL4_H_DONE_Pos (12UL)        /*!< DONE (Bit 12)                                         */
#define DMAC_CTL4_H_DONE_Msk (0x1000UL)    /*!< DONE (Bitfield-Mask: 0x01)                            */
#define DMAC_CTL4_H_BLOCK_TS_Pos (0UL)     /*!< BLOCK_TS (Bit 0)                                      */
#define DMAC_CTL4_H_BLOCK_TS_Msk (0xfffUL) /*!< BLOCK_TS (Bitfield-Mask: 0xfff)                       */
/* ========================================================  CTL5_H  ========================================================= */
#define DMAC_CTL5_H_DONE_Pos (12UL)        /*!< DONE (Bit 12)                                         */
#define DMAC_CTL5_H_DONE_Msk (0x1000UL)    /*!< DONE (Bitfield-Mask: 0x01)                            */
#define DMAC_CTL5_H_BLOCK_TS_Pos (0UL)     /*!< BLOCK_TS (Bit 0)                                      */
#define DMAC_CTL5_H_BLOCK_TS_Msk (0xfffUL) /*!< BLOCK_TS (Bitfield-Mask: 0xfff)                       */
/* ========================================================  CTL6_H  ========================================================= */
#define DMAC_CTL6_H_DONE_Pos (12UL)        /*!< DONE (Bit 12)                                         */
#define DMAC_CTL6_H_DONE_Msk (0x1000UL)    /*!< DONE (Bitfield-Mask: 0x01)                            */
#define DMAC_CTL6_H_BLOCK_TS_Pos (0UL)     /*!< BLOCK_TS (Bit 0)                                      */
#define DMAC_CTL6_H_BLOCK_TS_Msk (0xfffUL) /*!< BLOCK_TS (Bitfield-Mask: 0xfff)                       */
/* ========================================================  CTL7_H  ========================================================= */
#define DMAC_CTL7_H_DONE_Pos (12UL)        /*!< DONE (Bit 12)                                         */
#define DMAC_CTL7_H_DONE_Msk (0x1000UL)    /*!< DONE (Bitfield-Mask: 0x01)                            */
#define DMAC_CTL7_H_BLOCK_TS_Pos (0UL)     /*!< BLOCK_TS (Bit 0)                                      */
#define DMAC_CTL7_H_BLOCK_TS_Msk (0xfffUL) /*!< BLOCK_TS (Bitfield-Mask: 0xfff)                       */
/* ========================================================  SSTAT1  ========================================================= */
#define DMAC_SSTAT1_SSTAT_Pos (0UL)          /*!< SSTAT (Bit 0)                                         */
#define DMAC_SSTAT1_SSTAT_Msk (0xffffffffUL) /*!< SSTAT (Bitfield-Mask: 0xffffffff)                     */
/* ========================================================  SSTAT2  ========================================================= */
#define DMAC_SSTAT2_SSTAT_Pos (0UL)          /*!< SSTAT (Bit 0)                                         */
#define DMAC_SSTAT2_SSTAT_Msk (0xffffffffUL) /*!< SSTAT (Bitfield-Mask: 0xffffffff)                     */
/* ========================================================  SSTAT3  ========================================================= */
#define DMAC_SSTAT3_SSTAT_Pos (0UL)          /*!< SSTAT (Bit 0)                                         */
#define DMAC_SSTAT3_SSTAT_Msk (0xffffffffUL) /*!< SSTAT (Bitfield-Mask: 0xffffffff)                     */
/* ========================================================  SSTAT4  ========================================================= */
#define DMAC_SSTAT4_SSTAT_Pos (0UL)          /*!< SSTAT (Bit 0)                                         */
#define DMAC_SSTAT4_SSTAT_Msk (0xffffffffUL) /*!< SSTAT (Bitfield-Mask: 0xffffffff)                     */
/* ========================================================  SSTAT5  ========================================================= */
#define DMAC_SSTAT5_SSTAT_Pos (0UL)          /*!< SSTAT (Bit 0)                                         */
#define DMAC_SSTAT5_SSTAT_Msk (0xffffffffUL) /*!< SSTAT (Bitfield-Mask: 0xffffffff)                     */
/* ========================================================  SSTAT6  ========================================================= */
#define DMAC_SSTAT6_SSTAT_Pos (0UL)          /*!< SSTAT (Bit 0)                                         */
#define DMAC_SSTAT6_SSTAT_Msk (0xffffffffUL) /*!< SSTAT (Bitfield-Mask: 0xffffffff)                     */
/* ========================================================  SSTAT7  ========================================================= */
#define DMAC_SSTAT7_SSTAT_Pos (0UL)          /*!< SSTAT (Bit 0)                                         */
#define DMAC_SSTAT7_SSTAT_Msk (0xffffffffUL) /*!< SSTAT (Bitfield-Mask: 0xffffffff)                     */
/* ========================================================  DSTAT1  ========================================================= */
#define DMAC_DSTAT1_DSTAT_Pos (0UL)          /*!< DSTAT (Bit 0)                                         */
#define DMAC_DSTAT1_DSTAT_Msk (0xffffffffUL) /*!< DSTAT (Bitfield-Mask: 0xffffffff)                     */
/* ========================================================  DSTAT2  ========================================================= */
#define DMAC_DSTAT2_DSTAT_Pos (0UL)          /*!< DSTAT (Bit 0)                                         */
#define DMAC_DSTAT2_DSTAT_Msk (0xffffffffUL) /*!< DSTAT (Bitfield-Mask: 0xffffffff)                     */
/* ========================================================  DSTAT3  ========================================================= */
#define DMAC_DSTAT3_DSTAT_Pos (0UL)          /*!< DSTAT (Bit 0)                                         */
#define DMAC_DSTAT3_DSTAT_Msk (0xffffffffUL) /*!< DSTAT (Bitfield-Mask: 0xffffffff)                     */
/* ========================================================  DSTAT4  ========================================================= */
#define DMAC_DSTAT4_DSTAT_Pos (0UL)          /*!< DSTAT (Bit 0)                                         */
#define DMAC_DSTAT4_DSTAT_Msk (0xffffffffUL) /*!< DSTAT (Bitfield-Mask: 0xffffffff)                     */
/* ========================================================  DSTAT5  ========================================================= */
#define DMAC_DSTAT5_DSTAT_Pos (0UL)          /*!< DSTAT (Bit 0)                                         */
#define DMAC_DSTAT5_DSTAT_Msk (0xffffffffUL) /*!< DSTAT (Bitfield-Mask: 0xffffffff)                     */
/* ========================================================  DSTAT6  ========================================================= */
#define DMAC_DSTAT6_DSTAT_Pos (0UL)          /*!< DSTAT (Bit 0)                                         */
#define DMAC_DSTAT6_DSTAT_Msk (0xffffffffUL) /*!< DSTAT (Bitfield-Mask: 0xffffffff)                     */
/* ========================================================  DSTAT7  ========================================================= */
#define DMAC_DSTAT7_DSTAT_Pos (0UL)          /*!< DSTAT (Bit 0)                                         */
#define DMAC_DSTAT7_DSTAT_Msk (0xffffffffUL) /*!< DSTAT (Bitfield-Mask: 0xffffffff)                     */
/* =======================================================  SSTATAR1  ======================================================== */
#define DMAC_SSTATAR1_SSTATAR_Pos (0UL)          /*!< SSTATAR (Bit 0)                                       */
#define DMAC_SSTATAR1_SSTATAR_Msk (0xffffffffUL) /*!< SSTATAR (Bitfield-Mask: 0xffffffff)                   */
/* =======================================================  SSTATAR2  ======================================================== */
#define DMAC_SSTATAR2_SSTATAR_Pos (0UL)          /*!< SSTATAR (Bit 0)                                       */
#define DMAC_SSTATAR2_SSTATAR_Msk (0xffffffffUL) /*!< SSTATAR (Bitfield-Mask: 0xffffffff)                   */
/* =======================================================  SSTATAR3  ======================================================== */
#define DMAC_SSTATAR3_SSTATAR_Pos (0UL)          /*!< SSTATAR (Bit 0)                                       */
#define DMAC_SSTATAR3_SSTATAR_Msk (0xffffffffUL) /*!< SSTATAR (Bitfield-Mask: 0xffffffff)                   */
/* =======================================================  SSTATAR4  ======================================================== */
#define DMAC_SSTATAR4_SSTATAR_Pos (0UL)          /*!< SSTATAR (Bit 0)                                       */
#define DMAC_SSTATAR4_SSTATAR_Msk (0xffffffffUL) /*!< SSTATAR (Bitfield-Mask: 0xffffffff)                   */
/* =======================================================  SSTATAR5  ======================================================== */
#define DMAC_SSTATAR5_SSTATAR_Pos (0UL)          /*!< SSTATAR (Bit 0)                                       */
#define DMAC_SSTATAR5_SSTATAR_Msk (0xffffffffUL) /*!< SSTATAR (Bitfield-Mask: 0xffffffff)                   */
/* =======================================================  SSTATAR6  ======================================================== */
#define DMAC_SSTATAR6_SSTATAR_Pos (0UL)          /*!< SSTATAR (Bit 0)                                       */
#define DMAC_SSTATAR6_SSTATAR_Msk (0xffffffffUL) /*!< SSTATAR (Bitfield-Mask: 0xffffffff)                   */
/* =======================================================  SSTATAR7  ======================================================== */
#define DMAC_SSTATAR7_SSTATAR_Pos (0UL)          /*!< SSTATAR (Bit 0)                                       */
#define DMAC_SSTATAR7_SSTATAR_Msk (0xffffffffUL) /*!< SSTATAR (Bitfield-Mask: 0xffffffff)                   */
/* =======================================================  DSTATAR1  ======================================================== */
#define DMAC_DSTATAR1_DSTATAR_Pos (0UL)          /*!< DSTATAR (Bit 0)                                       */
#define DMAC_DSTATAR1_DSTATAR_Msk (0xffffffffUL) /*!< DSTATAR (Bitfield-Mask: 0xffffffff)                   */
/* =======================================================  DSTATAR2  ======================================================== */
#define DMAC_DSTATAR2_DSTATAR_Pos (0UL)          /*!< DSTATAR (Bit 0)                                       */
#define DMAC_DSTATAR2_DSTATAR_Msk (0xffffffffUL) /*!< DSTATAR (Bitfield-Mask: 0xffffffff)                   */
/* =======================================================  DSTATAR3  ======================================================== */
#define DMAC_DSTATAR3_DSTATAR_Pos (0UL)          /*!< DSTATAR (Bit 0)                                       */
#define DMAC_DSTATAR3_DSTATAR_Msk (0xffffffffUL) /*!< DSTATAR (Bitfield-Mask: 0xffffffff)                   */
/* =======================================================  DSTATAR4  ======================================================== */
#define DMAC_DSTATAR4_DSTATAR_Pos (0UL)          /*!< DSTATAR (Bit 0)                                       */
#define DMAC_DSTATAR4_DSTATAR_Msk (0xffffffffUL) /*!< DSTATAR (Bitfield-Mask: 0xffffffff)                   */
/* =======================================================  DSTATAR5  ======================================================== */
#define DMAC_DSTATAR5_DSTATAR_Pos (0UL)          /*!< DSTATAR (Bit 0)                                       */
#define DMAC_DSTATAR5_DSTATAR_Msk (0xffffffffUL) /*!< DSTATAR (Bitfield-Mask: 0xffffffff)                   */
/* =======================================================  DSTATAR6  ======================================================== */
#define DMAC_DSTATAR6_DSTATAR_Pos (0UL)          /*!< DSTATAR (Bit 0)                                       */
#define DMAC_DSTATAR6_DSTATAR_Msk (0xffffffffUL) /*!< DSTATAR (Bitfield-Mask: 0xffffffff)                   */
/* =======================================================  DSTATAR7  ======================================================== */
#define DMAC_DSTATAR7_DSTATAR_Pos (0UL)          /*!< DSTATAR (Bit 0)                                       */
#define DMAC_DSTATAR7_DSTATAR_Msk (0xffffffffUL) /*!< DSTATAR (Bitfield-Mask: 0xffffffff)                   */
/* ========================================================  CFG1_L  ========================================================= */
#define DMAC_CFG1_L_RELOAD_DST_Pos (31UL)         /*!< RELOAD_DST (Bit 31)                                   */
#define DMAC_CFG1_L_RELOAD_DST_Msk (0x80000000UL) /*!< RELOAD_DST (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG1_L_RELOAD_SRC_Pos (30UL)         /*!< RELOAD_SRC (Bit 30)                                   */
#define DMAC_CFG1_L_RELOAD_SRC_Msk (0x40000000UL) /*!< RELOAD_SRC (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG1_L_MAX_ABRST_Pos (20UL)          /*!< MAX_ABRST (Bit 20)                                    */
#define DMAC_CFG1_L_MAX_ABRST_Msk (0x3ff00000UL)  /*!< MAX_ABRST (Bitfield-Mask: 0x3ff)                      */
#define DMAC_CFG1_L_SRC_HS_POL_Pos (19UL)         /*!< SRC_HS_POL (Bit 19)                                   */
#define DMAC_CFG1_L_SRC_HS_POL_Msk (0x80000UL)    /*!< SRC_HS_POL (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG1_L_DST_HS_POL_Pos (18UL)         /*!< DST_HS_POL (Bit 18)                                   */
#define DMAC_CFG1_L_DST_HS_POL_Msk (0x40000UL)    /*!< DST_HS_POL (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG1_L_LOCK_B_Pos (17UL)             /*!< LOCK_B (Bit 17)                                       */
#define DMAC_CFG1_L_LOCK_B_Msk (0x20000UL)        /*!< LOCK_B (Bitfield-Mask: 0x01)                          */
#define DMAC_CFG1_L_LOCK_CH_Pos (16UL)            /*!< LOCK_CH (Bit 16)                                      */
#define DMAC_CFG1_L_LOCK_CH_Msk (0x10000UL)       /*!< LOCK_CH (Bitfield-Mask: 0x01)                         */
#define DMAC_CFG1_L_LOCK_B_L_Pos (14UL)           /*!< LOCK_B_L (Bit 14)                                     */
#define DMAC_CFG1_L_LOCK_B_L_Msk (0xc000UL)       /*!< LOCK_B_L (Bitfield-Mask: 0x03)                        */
#define DMAC_CFG1_L_LOCK_CH_L_Pos (12UL)          /*!< LOCK_CH_L (Bit 12)                                    */
#define DMAC_CFG1_L_LOCK_CH_L_Msk (0x3000UL)      /*!< LOCK_CH_L (Bitfield-Mask: 0x03)                       */
#define DMAC_CFG1_L_HS_SEL_SRC_Pos (11UL)         /*!< HS_SEL_SRC (Bit 11)                                   */
#define DMAC_CFG1_L_HS_SEL_SRC_Msk (0x800UL)      /*!< HS_SEL_SRC (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG1_L_HS_SEL_DST_Pos (10UL)         /*!< HS_SEL_DST (Bit 10)                                   */
#define DMAC_CFG1_L_HS_SEL_DST_Msk (0x400UL)      /*!< HS_SEL_DST (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG1_L_FIFO_EMPTY_Pos (9UL)          /*!< FIFO_EMPTY (Bit 9)                                    */
#define DMAC_CFG1_L_FIFO_EMPTY_Msk (0x200UL)      /*!< FIFO_EMPTY (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG1_L_CH_SUSP_Pos (8UL)             /*!< CH_SUSP (Bit 8)                                       */
#define DMAC_CFG1_L_CH_SUSP_Msk (0x100UL)         /*!< CH_SUSP (Bitfield-Mask: 0x01)                         */
#define DMAC_CFG1_L_CH_PRIOR_Pos (5UL)            /*!< CH_PRIOR (Bit 5)                                      */
#define DMAC_CFG1_L_CH_PRIOR_Msk (0xe0UL)         /*!< CH_PRIOR (Bitfield-Mask: 0x07)                        */
/* ========================================================  CFG2_L  ========================================================= */
#define DMAC_CFG2_L_RELOAD_DST_Pos (31UL)         /*!< RELOAD_DST (Bit 31)                                   */
#define DMAC_CFG2_L_RELOAD_DST_Msk (0x80000000UL) /*!< RELOAD_DST (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG2_L_RELOAD_SRC_Pos (30UL)         /*!< RELOAD_SRC (Bit 30)                                   */
#define DMAC_CFG2_L_RELOAD_SRC_Msk (0x40000000UL) /*!< RELOAD_SRC (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG2_L_MAX_ABRST_Pos (20UL)          /*!< MAX_ABRST (Bit 20)                                    */
#define DMAC_CFG2_L_MAX_ABRST_Msk (0x3ff00000UL)  /*!< MAX_ABRST (Bitfield-Mask: 0x3ff)                      */
#define DMAC_CFG2_L_SRC_HS_POL_Pos (19UL)         /*!< SRC_HS_POL (Bit 19)                                   */
#define DMAC_CFG2_L_SRC_HS_POL_Msk (0x80000UL)    /*!< SRC_HS_POL (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG2_L_DST_HS_POL_Pos (18UL)         /*!< DST_HS_POL (Bit 18)                                   */
#define DMAC_CFG2_L_DST_HS_POL_Msk (0x40000UL)    /*!< DST_HS_POL (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG2_L_LOCK_B_Pos (17UL)             /*!< LOCK_B (Bit 17)                                       */
#define DMAC_CFG2_L_LOCK_B_Msk (0x20000UL)        /*!< LOCK_B (Bitfield-Mask: 0x01)                          */
#define DMAC_CFG2_L_LOCK_CH_Pos (16UL)            /*!< LOCK_CH (Bit 16)                                      */
#define DMAC_CFG2_L_LOCK_CH_Msk (0x10000UL)       /*!< LOCK_CH (Bitfield-Mask: 0x01)                         */
#define DMAC_CFG2_L_LOCK_B_L_Pos (14UL)           /*!< LOCK_B_L (Bit 14)                                     */
#define DMAC_CFG2_L_LOCK_B_L_Msk (0xc000UL)       /*!< LOCK_B_L (Bitfield-Mask: 0x03)                        */
#define DMAC_CFG2_L_LOCK_CH_L_Pos (12UL)          /*!< LOCK_CH_L (Bit 12)                                    */
#define DMAC_CFG2_L_LOCK_CH_L_Msk (0x3000UL)      /*!< LOCK_CH_L (Bitfield-Mask: 0x03)                       */
#define DMAC_CFG2_L_HS_SEL_SRC_Pos (11UL)         /*!< HS_SEL_SRC (Bit 11)                                   */
#define DMAC_CFG2_L_HS_SEL_SRC_Msk (0x800UL)      /*!< HS_SEL_SRC (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG2_L_HS_SEL_DST_Pos (10UL)         /*!< HS_SEL_DST (Bit 10)                                   */
#define DMAC_CFG2_L_HS_SEL_DST_Msk (0x400UL)      /*!< HS_SEL_DST (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG2_L_FIFO_EMPTY_Pos (9UL)          /*!< FIFO_EMPTY (Bit 9)                                    */
#define DMAC_CFG2_L_FIFO_EMPTY_Msk (0x200UL)      /*!< FIFO_EMPTY (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG2_L_CH_SUSP_Pos (8UL)             /*!< CH_SUSP (Bit 8)                                       */
#define DMAC_CFG2_L_CH_SUSP_Msk (0x100UL)         /*!< CH_SUSP (Bitfield-Mask: 0x01)                         */
#define DMAC_CFG2_L_CH_PRIOR_Pos (5UL)            /*!< CH_PRIOR (Bit 5)                                      */
#define DMAC_CFG2_L_CH_PRIOR_Msk (0xe0UL)         /*!< CH_PRIOR (Bitfield-Mask: 0x07)                        */
/* ========================================================  CFG3_L  ========================================================= */
#define DMAC_CFG3_L_RELOAD_DST_Pos (31UL)         /*!< RELOAD_DST (Bit 31)                                   */
#define DMAC_CFG3_L_RELOAD_DST_Msk (0x80000000UL) /*!< RELOAD_DST (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG3_L_RELOAD_SRC_Pos (30UL)         /*!< RELOAD_SRC (Bit 30)                                   */
#define DMAC_CFG3_L_RELOAD_SRC_Msk (0x40000000UL) /*!< RELOAD_SRC (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG3_L_MAX_ABRST_Pos (20UL)          /*!< MAX_ABRST (Bit 20)                                    */
#define DMAC_CFG3_L_MAX_ABRST_Msk (0x3ff00000UL)  /*!< MAX_ABRST (Bitfield-Mask: 0x3ff)                      */
#define DMAC_CFG3_L_SRC_HS_POL_Pos (19UL)         /*!< SRC_HS_POL (Bit 19)                                   */
#define DMAC_CFG3_L_SRC_HS_POL_Msk (0x80000UL)    /*!< SRC_HS_POL (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG3_L_DST_HS_POL_Pos (18UL)         /*!< DST_HS_POL (Bit 18)                                   */
#define DMAC_CFG3_L_DST_HS_POL_Msk (0x40000UL)    /*!< DST_HS_POL (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG3_L_LOCK_B_Pos (17UL)             /*!< LOCK_B (Bit 17)                                       */
#define DMAC_CFG3_L_LOCK_B_Msk (0x20000UL)        /*!< LOCK_B (Bitfield-Mask: 0x01)                          */
#define DMAC_CFG3_L_LOCK_CH_Pos (16UL)            /*!< LOCK_CH (Bit 16)                                      */
#define DMAC_CFG3_L_LOCK_CH_Msk (0x10000UL)       /*!< LOCK_CH (Bitfield-Mask: 0x01)                         */
#define DMAC_CFG3_L_LOCK_B_L_Pos (14UL)           /*!< LOCK_B_L (Bit 14)                                     */
#define DMAC_CFG3_L_LOCK_B_L_Msk (0xc000UL)       /*!< LOCK_B_L (Bitfield-Mask: 0x03)                        */
#define DMAC_CFG3_L_LOCK_CH_L_Pos (12UL)          /*!< LOCK_CH_L (Bit 12)                                    */
#define DMAC_CFG3_L_LOCK_CH_L_Msk (0x3000UL)      /*!< LOCK_CH_L (Bitfield-Mask: 0x03)                       */
#define DMAC_CFG3_L_HS_SEL_SRC_Pos (11UL)         /*!< HS_SEL_SRC (Bit 11)                                   */
#define DMAC_CFG3_L_HS_SEL_SRC_Msk (0x800UL)      /*!< HS_SEL_SRC (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG3_L_HS_SEL_DST_Pos (10UL)         /*!< HS_SEL_DST (Bit 10)                                   */
#define DMAC_CFG3_L_HS_SEL_DST_Msk (0x400UL)      /*!< HS_SEL_DST (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG3_L_FIFO_EMPTY_Pos (9UL)          /*!< FIFO_EMPTY (Bit 9)                                    */
#define DMAC_CFG3_L_FIFO_EMPTY_Msk (0x200UL)      /*!< FIFO_EMPTY (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG3_L_CH_SUSP_Pos (8UL)             /*!< CH_SUSP (Bit 8)                                       */
#define DMAC_CFG3_L_CH_SUSP_Msk (0x100UL)         /*!< CH_SUSP (Bitfield-Mask: 0x01)                         */
#define DMAC_CFG3_L_CH_PRIOR_Pos (5UL)            /*!< CH_PRIOR (Bit 5)                                      */
#define DMAC_CFG3_L_CH_PRIOR_Msk (0xe0UL)         /*!< CH_PRIOR (Bitfield-Mask: 0x07)                        */
/* ========================================================  CFG4_L  ========================================================= */
#define DMAC_CFG4_L_RELOAD_DST_Pos (31UL)         /*!< RELOAD_DST (Bit 31)                                   */
#define DMAC_CFG4_L_RELOAD_DST_Msk (0x80000000UL) /*!< RELOAD_DST (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG4_L_RELOAD_SRC_Pos (30UL)         /*!< RELOAD_SRC (Bit 30)                                   */
#define DMAC_CFG4_L_RELOAD_SRC_Msk (0x40000000UL) /*!< RELOAD_SRC (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG4_L_MAX_ABRST_Pos (20UL)          /*!< MAX_ABRST (Bit 20)                                    */
#define DMAC_CFG4_L_MAX_ABRST_Msk (0x3ff00000UL)  /*!< MAX_ABRST (Bitfield-Mask: 0x3ff)                      */
#define DMAC_CFG4_L_SRC_HS_POL_Pos (19UL)         /*!< SRC_HS_POL (Bit 19)                                   */
#define DMAC_CFG4_L_SRC_HS_POL_Msk (0x80000UL)    /*!< SRC_HS_POL (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG4_L_DST_HS_POL_Pos (18UL)         /*!< DST_HS_POL (Bit 18)                                   */
#define DMAC_CFG4_L_DST_HS_POL_Msk (0x40000UL)    /*!< DST_HS_POL (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG4_L_LOCK_B_Pos (17UL)             /*!< LOCK_B (Bit 17)                                       */
#define DMAC_CFG4_L_LOCK_B_Msk (0x20000UL)        /*!< LOCK_B (Bitfield-Mask: 0x01)                          */
#define DMAC_CFG4_L_LOCK_CH_Pos (16UL)            /*!< LOCK_CH (Bit 16)                                      */
#define DMAC_CFG4_L_LOCK_CH_Msk (0x10000UL)       /*!< LOCK_CH (Bitfield-Mask: 0x01)                         */
#define DMAC_CFG4_L_LOCK_B_L_Pos (14UL)           /*!< LOCK_B_L (Bit 14)                                     */
#define DMAC_CFG4_L_LOCK_B_L_Msk (0xc000UL)       /*!< LOCK_B_L (Bitfield-Mask: 0x03)                        */
#define DMAC_CFG4_L_LOCK_CH_L_Pos (12UL)          /*!< LOCK_CH_L (Bit 12)                                    */
#define DMAC_CFG4_L_LOCK_CH_L_Msk (0x3000UL)      /*!< LOCK_CH_L (Bitfield-Mask: 0x03)                       */
#define DMAC_CFG4_L_HS_SEL_SRC_Pos (11UL)         /*!< HS_SEL_SRC (Bit 11)                                   */
#define DMAC_CFG4_L_HS_SEL_SRC_Msk (0x800UL)      /*!< HS_SEL_SRC (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG4_L_HS_SEL_DST_Pos (10UL)         /*!< HS_SEL_DST (Bit 10)                                   */
#define DMAC_CFG4_L_HS_SEL_DST_Msk (0x400UL)      /*!< HS_SEL_DST (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG4_L_FIFO_EMPTY_Pos (9UL)          /*!< FIFO_EMPTY (Bit 9)                                    */
#define DMAC_CFG4_L_FIFO_EMPTY_Msk (0x200UL)      /*!< FIFO_EMPTY (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG4_L_CH_SUSP_Pos (8UL)             /*!< CH_SUSP (Bit 8)                                       */
#define DMAC_CFG4_L_CH_SUSP_Msk (0x100UL)         /*!< CH_SUSP (Bitfield-Mask: 0x01)                         */
#define DMAC_CFG4_L_CH_PRIOR_Pos (5UL)            /*!< CH_PRIOR (Bit 5)                                      */
#define DMAC_CFG4_L_CH_PRIOR_Msk (0xe0UL)         /*!< CH_PRIOR (Bitfield-Mask: 0x07)                        */
/* ========================================================  CFG5_L  ========================================================= */
#define DMAC_CFG5_L_RELOAD_DST_Pos (31UL)         /*!< RELOAD_DST (Bit 31)                                   */
#define DMAC_CFG5_L_RELOAD_DST_Msk (0x80000000UL) /*!< RELOAD_DST (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG5_L_RELOAD_SRC_Pos (30UL)         /*!< RELOAD_SRC (Bit 30)                                   */
#define DMAC_CFG5_L_RELOAD_SRC_Msk (0x40000000UL) /*!< RELOAD_SRC (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG5_L_MAX_ABRST_Pos (20UL)          /*!< MAX_ABRST (Bit 20)                                    */
#define DMAC_CFG5_L_MAX_ABRST_Msk (0x3ff00000UL)  /*!< MAX_ABRST (Bitfield-Mask: 0x3ff)                      */
#define DMAC_CFG5_L_SRC_HS_POL_Pos (19UL)         /*!< SRC_HS_POL (Bit 19)                                   */
#define DMAC_CFG5_L_SRC_HS_POL_Msk (0x80000UL)    /*!< SRC_HS_POL (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG5_L_DST_HS_POL_Pos (18UL)         /*!< DST_HS_POL (Bit 18)                                   */
#define DMAC_CFG5_L_DST_HS_POL_Msk (0x40000UL)    /*!< DST_HS_POL (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG5_L_LOCK_B_Pos (17UL)             /*!< LOCK_B (Bit 17)                                       */
#define DMAC_CFG5_L_LOCK_B_Msk (0x20000UL)        /*!< LOCK_B (Bitfield-Mask: 0x01)                          */
#define DMAC_CFG5_L_LOCK_CH_Pos (16UL)            /*!< LOCK_CH (Bit 16)                                      */
#define DMAC_CFG5_L_LOCK_CH_Msk (0x10000UL)       /*!< LOCK_CH (Bitfield-Mask: 0x01)                         */
#define DMAC_CFG5_L_LOCK_B_L_Pos (14UL)           /*!< LOCK_B_L (Bit 14)                                     */
#define DMAC_CFG5_L_LOCK_B_L_Msk (0xc000UL)       /*!< LOCK_B_L (Bitfield-Mask: 0x03)                        */
#define DMAC_CFG5_L_LOCK_CH_L_Pos (12UL)          /*!< LOCK_CH_L (Bit 12)                                    */
#define DMAC_CFG5_L_LOCK_CH_L_Msk (0x3000UL)      /*!< LOCK_CH_L (Bitfield-Mask: 0x03)                       */
#define DMAC_CFG5_L_HS_SEL_SRC_Pos (11UL)         /*!< HS_SEL_SRC (Bit 11)                                   */
#define DMAC_CFG5_L_HS_SEL_SRC_Msk (0x800UL)      /*!< HS_SEL_SRC (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG5_L_HS_SEL_DST_Pos (10UL)         /*!< HS_SEL_DST (Bit 10)                                   */
#define DMAC_CFG5_L_HS_SEL_DST_Msk (0x400UL)      /*!< HS_SEL_DST (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG5_L_FIFO_EMPTY_Pos (9UL)          /*!< FIFO_EMPTY (Bit 9)                                    */
#define DMAC_CFG5_L_FIFO_EMPTY_Msk (0x200UL)      /*!< FIFO_EMPTY (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG5_L_CH_SUSP_Pos (8UL)             /*!< CH_SUSP (Bit 8)                                       */
#define DMAC_CFG5_L_CH_SUSP_Msk (0x100UL)         /*!< CH_SUSP (Bitfield-Mask: 0x01)                         */
#define DMAC_CFG5_L_CH_PRIOR_Pos (5UL)            /*!< CH_PRIOR (Bit 5)                                      */
#define DMAC_CFG5_L_CH_PRIOR_Msk (0xe0UL)         /*!< CH_PRIOR (Bitfield-Mask: 0x07)                        */
/* ========================================================  CFG6_L  ========================================================= */
#define DMAC_CFG6_L_RELOAD_DST_Pos (31UL)         /*!< RELOAD_DST (Bit 31)                                   */
#define DMAC_CFG6_L_RELOAD_DST_Msk (0x80000000UL) /*!< RELOAD_DST (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG6_L_RELOAD_SRC_Pos (30UL)         /*!< RELOAD_SRC (Bit 30)                                   */
#define DMAC_CFG6_L_RELOAD_SRC_Msk (0x40000000UL) /*!< RELOAD_SRC (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG6_L_MAX_ABRST_Pos (20UL)          /*!< MAX_ABRST (Bit 20)                                    */
#define DMAC_CFG6_L_MAX_ABRST_Msk (0x3ff00000UL)  /*!< MAX_ABRST (Bitfield-Mask: 0x3ff)                      */
#define DMAC_CFG6_L_SRC_HS_POL_Pos (19UL)         /*!< SRC_HS_POL (Bit 19)                                   */
#define DMAC_CFG6_L_SRC_HS_POL_Msk (0x80000UL)    /*!< SRC_HS_POL (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG6_L_DST_HS_POL_Pos (18UL)         /*!< DST_HS_POL (Bit 18)                                   */
#define DMAC_CFG6_L_DST_HS_POL_Msk (0x40000UL)    /*!< DST_HS_POL (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG6_L_LOCK_B_Pos (17UL)             /*!< LOCK_B (Bit 17)                                       */
#define DMAC_CFG6_L_LOCK_B_Msk (0x20000UL)        /*!< LOCK_B (Bitfield-Mask: 0x01)                          */
#define DMAC_CFG6_L_LOCK_CH_Pos (16UL)            /*!< LOCK_CH (Bit 16)                                      */
#define DMAC_CFG6_L_LOCK_CH_Msk (0x10000UL)       /*!< LOCK_CH (Bitfield-Mask: 0x01)                         */
#define DMAC_CFG6_L_LOCK_B_L_Pos (14UL)           /*!< LOCK_B_L (Bit 14)                                     */
#define DMAC_CFG6_L_LOCK_B_L_Msk (0xc000UL)       /*!< LOCK_B_L (Bitfield-Mask: 0x03)                        */
#define DMAC_CFG6_L_LOCK_CH_L_Pos (12UL)          /*!< LOCK_CH_L (Bit 12)                                    */
#define DMAC_CFG6_L_LOCK_CH_L_Msk (0x3000UL)      /*!< LOCK_CH_L (Bitfield-Mask: 0x03)                       */
#define DMAC_CFG6_L_HS_SEL_SRC_Pos (11UL)         /*!< HS_SEL_SRC (Bit 11)                                   */
#define DMAC_CFG6_L_HS_SEL_SRC_Msk (0x800UL)      /*!< HS_SEL_SRC (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG6_L_HS_SEL_DST_Pos (10UL)         /*!< HS_SEL_DST (Bit 10)                                   */
#define DMAC_CFG6_L_HS_SEL_DST_Msk (0x400UL)      /*!< HS_SEL_DST (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG6_L_FIFO_EMPTY_Pos (9UL)          /*!< FIFO_EMPTY (Bit 9)                                    */
#define DMAC_CFG6_L_FIFO_EMPTY_Msk (0x200UL)      /*!< FIFO_EMPTY (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG6_L_CH_SUSP_Pos (8UL)             /*!< CH_SUSP (Bit 8)                                       */
#define DMAC_CFG6_L_CH_SUSP_Msk (0x100UL)         /*!< CH_SUSP (Bitfield-Mask: 0x01)                         */
#define DMAC_CFG6_L_CH_PRIOR_Pos (5UL)            /*!< CH_PRIOR (Bit 5)                                      */
#define DMAC_CFG6_L_CH_PRIOR_Msk (0xe0UL)         /*!< CH_PRIOR (Bitfield-Mask: 0x07)                        */
/* ========================================================  CFG7_L  ========================================================= */
#define DMAC_CFG7_L_RELOAD_DST_Pos (31UL)         /*!< RELOAD_DST (Bit 31)                                   */
#define DMAC_CFG7_L_RELOAD_DST_Msk (0x80000000UL) /*!< RELOAD_DST (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG7_L_RELOAD_SRC_Pos (30UL)         /*!< RELOAD_SRC (Bit 30)                                   */
#define DMAC_CFG7_L_RELOAD_SRC_Msk (0x40000000UL) /*!< RELOAD_SRC (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG7_L_MAX_ABRST_Pos (20UL)          /*!< MAX_ABRST (Bit 20)                                    */
#define DMAC_CFG7_L_MAX_ABRST_Msk (0x3ff00000UL)  /*!< MAX_ABRST (Bitfield-Mask: 0x3ff)                      */
#define DMAC_CFG7_L_SRC_HS_POL_Pos (19UL)         /*!< SRC_HS_POL (Bit 19)                                   */
#define DMAC_CFG7_L_SRC_HS_POL_Msk (0x80000UL)    /*!< SRC_HS_POL (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG7_L_DST_HS_POL_Pos (18UL)         /*!< DST_HS_POL (Bit 18)                                   */
#define DMAC_CFG7_L_DST_HS_POL_Msk (0x40000UL)    /*!< DST_HS_POL (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG7_L_LOCK_B_Pos (17UL)             /*!< LOCK_B (Bit 17)                                       */
#define DMAC_CFG7_L_LOCK_B_Msk (0x20000UL)        /*!< LOCK_B (Bitfield-Mask: 0x01)                          */
#define DMAC_CFG7_L_LOCK_CH_Pos (16UL)            /*!< LOCK_CH (Bit 16)                                      */
#define DMAC_CFG7_L_LOCK_CH_Msk (0x10000UL)       /*!< LOCK_CH (Bitfield-Mask: 0x01)                         */
#define DMAC_CFG7_L_LOCK_B_L_Pos (14UL)           /*!< LOCK_B_L (Bit 14)                                     */
#define DMAC_CFG7_L_LOCK_B_L_Msk (0xc000UL)       /*!< LOCK_B_L (Bitfield-Mask: 0x03)                        */
#define DMAC_CFG7_L_LOCK_CH_L_Pos (12UL)          /*!< LOCK_CH_L (Bit 12)                                    */
#define DMAC_CFG7_L_LOCK_CH_L_Msk (0x3000UL)      /*!< LOCK_CH_L (Bitfield-Mask: 0x03)                       */
#define DMAC_CFG7_L_HS_SEL_SRC_Pos (11UL)         /*!< HS_SEL_SRC (Bit 11)                                   */
#define DMAC_CFG7_L_HS_SEL_SRC_Msk (0x800UL)      /*!< HS_SEL_SRC (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG7_L_HS_SEL_DST_Pos (10UL)         /*!< HS_SEL_DST (Bit 10)                                   */
#define DMAC_CFG7_L_HS_SEL_DST_Msk (0x400UL)      /*!< HS_SEL_DST (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG7_L_FIFO_EMPTY_Pos (9UL)          /*!< FIFO_EMPTY (Bit 9)                                    */
#define DMAC_CFG7_L_FIFO_EMPTY_Msk (0x200UL)      /*!< FIFO_EMPTY (Bitfield-Mask: 0x01)                      */
#define DMAC_CFG7_L_CH_SUSP_Pos (8UL)             /*!< CH_SUSP (Bit 8)                                       */
#define DMAC_CFG7_L_CH_SUSP_Msk (0x100UL)         /*!< CH_SUSP (Bitfield-Mask: 0x01)                         */
#define DMAC_CFG7_L_CH_PRIOR_Pos (5UL)            /*!< CH_PRIOR (Bit 5)                                      */
#define DMAC_CFG7_L_CH_PRIOR_Msk (0xe0UL)         /*!< CH_PRIOR (Bitfield-Mask: 0x07)                        */
/* ========================================================  CFG1_H  ========================================================= */
#define DMAC_CFG1_H_DEST_PER_Pos (11UL)     /*!< DEST_PER (Bit 11)                                     */
#define DMAC_CFG1_H_DEST_PER_Msk (0x7800UL) /*!< DEST_PER (Bitfield-Mask: 0x0f)                        */
#define DMAC_CFG1_H_SRC_PER_Pos (7UL)       /*!< SRC_PER (Bit 7)                                       */
#define DMAC_CFG1_H_SRC_PER_Msk (0x780UL)   /*!< SRC_PER (Bitfield-Mask: 0x0f)                         */
#define DMAC_CFG1_H_SS_UPD_EN_Pos (6UL)     /*!< SS_UPD_EN (Bit 6)                                     */
#define DMAC_CFG1_H_SS_UPD_EN_Msk (0x40UL)  /*!< SS_UPD_EN (Bitfield-Mask: 0x01)                       */
#define DMAC_CFG1_H_DS_UPD_EN_Pos (5UL)     /*!< DS_UPD_EN (Bit 5)                                     */
#define DMAC_CFG1_H_DS_UPD_EN_Msk (0x20UL)  /*!< DS_UPD_EN (Bitfield-Mask: 0x01)                       */
#define DMAC_CFG1_H_PROTCTL_Pos (2UL)       /*!< PROTCTL (Bit 2)                                       */
#define DMAC_CFG1_H_PROTCTL_Msk (0x1cUL)    /*!< PROTCTL (Bitfield-Mask: 0x07)                         */
#define DMAC_CFG1_H_FIFO_MODE_Pos (1UL)     /*!< FIFO_MODE (Bit 1)                                     */
#define DMAC_CFG1_H_FIFO_MODE_Msk (0x2UL)   /*!< FIFO_MODE (Bitfield-Mask: 0x01)                       */
#define DMAC_CFG1_H_FCMODE_Pos (0UL)        /*!< FCMODE (Bit 0)                                        */
#define DMAC_CFG1_H_FCMODE_Msk (0x1UL)      /*!< FCMODE (Bitfield-Mask: 0x01)                          */
/* ========================================================  CFG2_H  ========================================================= */
#define DMAC_CFG2_H_DEST_PER_Pos (11UL)     /*!< DEST_PER (Bit 11)                                     */
#define DMAC_CFG2_H_DEST_PER_Msk (0x7800UL) /*!< DEST_PER (Bitfield-Mask: 0x0f)                        */
#define DMAC_CFG2_H_SRC_PER_Pos (7UL)       /*!< SRC_PER (Bit 7)                                       */
#define DMAC_CFG2_H_SRC_PER_Msk (0x780UL)   /*!< SRC_PER (Bitfield-Mask: 0x0f)                         */
#define DMAC_CFG2_H_SS_UPD_EN_Pos (6UL)     /*!< SS_UPD_EN (Bit 6)                                     */
#define DMAC_CFG2_H_SS_UPD_EN_Msk (0x40UL)  /*!< SS_UPD_EN (Bitfield-Mask: 0x01)                       */
#define DMAC_CFG2_H_DS_UPD_EN_Pos (5UL)     /*!< DS_UPD_EN (Bit 5)                                     */
#define DMAC_CFG2_H_DS_UPD_EN_Msk (0x20UL)  /*!< DS_UPD_EN (Bitfield-Mask: 0x01)                       */
#define DMAC_CFG2_H_PROTCTL_Pos (2UL)       /*!< PROTCTL (Bit 2)                                       */
#define DMAC_CFG2_H_PROTCTL_Msk (0x1cUL)    /*!< PROTCTL (Bitfield-Mask: 0x07)                         */
#define DMAC_CFG2_H_FIFO_MODE_Pos (1UL)     /*!< FIFO_MODE (Bit 1)                                     */
#define DMAC_CFG2_H_FIFO_MODE_Msk (0x2UL)   /*!< FIFO_MODE (Bitfield-Mask: 0x01)                       */
#define DMAC_CFG2_H_FCMODE_Pos (0UL)        /*!< FCMODE (Bit 0)                                        */
#define DMAC_CFG2_H_FCMODE_Msk (0x1UL)      /*!< FCMODE (Bitfield-Mask: 0x01)                          */
/* ========================================================  CFG3_H  ========================================================= */
#define DMAC_CFG3_H_DEST_PER_Pos (11UL)     /*!< DEST_PER (Bit 11)                                     */
#define DMAC_CFG3_H_DEST_PER_Msk (0x7800UL) /*!< DEST_PER (Bitfield-Mask: 0x0f)                        */
#define DMAC_CFG3_H_SRC_PER_Pos (7UL)       /*!< SRC_PER (Bit 7)                                       */
#define DMAC_CFG3_H_SRC_PER_Msk (0x780UL)   /*!< SRC_PER (Bitfield-Mask: 0x0f)                         */
#define DMAC_CFG3_H_SS_UPD_EN_Pos (6UL)     /*!< SS_UPD_EN (Bit 6)                                     */
#define DMAC_CFG3_H_SS_UPD_EN_Msk (0x40UL)  /*!< SS_UPD_EN (Bitfield-Mask: 0x01)                       */
#define DMAC_CFG3_H_DS_UPD_EN_Pos (5UL)     /*!< DS_UPD_EN (Bit 5)                                     */
#define DMAC_CFG3_H_DS_UPD_EN_Msk (0x20UL)  /*!< DS_UPD_EN (Bitfield-Mask: 0x01)                       */
#define DMAC_CFG3_H_PROTCTL_Pos (2UL)       /*!< PROTCTL (Bit 2)                                       */
#define DMAC_CFG3_H_PROTCTL_Msk (0x1cUL)    /*!< PROTCTL (Bitfield-Mask: 0x07)                         */
#define DMAC_CFG3_H_FIFO_MODE_Pos (1UL)     /*!< FIFO_MODE (Bit 1)                                     */
#define DMAC_CFG3_H_FIFO_MODE_Msk (0x2UL)   /*!< FIFO_MODE (Bitfield-Mask: 0x01)                       */
#define DMAC_CFG3_H_FCMODE_Pos (0UL)        /*!< FCMODE (Bit 0)                                        */
#define DMAC_CFG3_H_FCMODE_Msk (0x1UL)      /*!< FCMODE (Bitfield-Mask: 0x01)                          */
/* ========================================================  CFG4_H  ========================================================= */
#define DMAC_CFG4_H_DEST_PER_Pos (11UL)     /*!< DEST_PER (Bit 11)                                     */
#define DMAC_CFG4_H_DEST_PER_Msk (0x7800UL) /*!< DEST_PER (Bitfield-Mask: 0x0f)                        */
#define DMAC_CFG4_H_SRC_PER_Pos (7UL)       /*!< SRC_PER (Bit 7)                                       */
#define DMAC_CFG4_H_SRC_PER_Msk (0x780UL)   /*!< SRC_PER (Bitfield-Mask: 0x0f)                         */
#define DMAC_CFG4_H_SS_UPD_EN_Pos (6UL)     /*!< SS_UPD_EN (Bit 6)                                     */
#define DMAC_CFG4_H_SS_UPD_EN_Msk (0x40UL)  /*!< SS_UPD_EN (Bitfield-Mask: 0x01)                       */
#define DMAC_CFG4_H_DS_UPD_EN_Pos (5UL)     /*!< DS_UPD_EN (Bit 5)                                     */
#define DMAC_CFG4_H_DS_UPD_EN_Msk (0x20UL)  /*!< DS_UPD_EN (Bitfield-Mask: 0x01)                       */
#define DMAC_CFG4_H_PROTCTL_Pos (2UL)       /*!< PROTCTL (Bit 2)                                       */
#define DMAC_CFG4_H_PROTCTL_Msk (0x1cUL)    /*!< PROTCTL (Bitfield-Mask: 0x07)                         */
#define DMAC_CFG4_H_FIFO_MODE_Pos (1UL)     /*!< FIFO_MODE (Bit 1)                                     */
#define DMAC_CFG4_H_FIFO_MODE_Msk (0x2UL)   /*!< FIFO_MODE (Bitfield-Mask: 0x01)                       */
#define DMAC_CFG4_H_FCMODE_Pos (0UL)        /*!< FCMODE (Bit 0)                                        */
#define DMAC_CFG4_H_FCMODE_Msk (0x1UL)      /*!< FCMODE (Bitfield-Mask: 0x01)                          */
/* ========================================================  CFG5_H  ========================================================= */
#define DMAC_CFG5_H_DEST_PER_Pos (11UL)     /*!< DEST_PER (Bit 11)                                     */
#define DMAC_CFG5_H_DEST_PER_Msk (0x7800UL) /*!< DEST_PER (Bitfield-Mask: 0x0f)                        */
#define DMAC_CFG5_H_SRC_PER_Pos (7UL)       /*!< SRC_PER (Bit 7)                                       */
#define DMAC_CFG5_H_SRC_PER_Msk (0x780UL)   /*!< SRC_PER (Bitfield-Mask: 0x0f)                         */
#define DMAC_CFG5_H_SS_UPD_EN_Pos (6UL)     /*!< SS_UPD_EN (Bit 6)                                     */
#define DMAC_CFG5_H_SS_UPD_EN_Msk (0x40UL)  /*!< SS_UPD_EN (Bitfield-Mask: 0x01)                       */
#define DMAC_CFG5_H_DS_UPD_EN_Pos (5UL)     /*!< DS_UPD_EN (Bit 5)                                     */
#define DMAC_CFG5_H_DS_UPD_EN_Msk (0x20UL)  /*!< DS_UPD_EN (Bitfield-Mask: 0x01)                       */
#define DMAC_CFG5_H_PROTCTL_Pos (2UL)       /*!< PROTCTL (Bit 2)                                       */
#define DMAC_CFG5_H_PROTCTL_Msk (0x1cUL)    /*!< PROTCTL (Bitfield-Mask: 0x07)                         */
#define DMAC_CFG5_H_FIFO_MODE_Pos (1UL)     /*!< FIFO_MODE (Bit 1)                                     */
#define DMAC_CFG5_H_FIFO_MODE_Msk (0x2UL)   /*!< FIFO_MODE (Bitfield-Mask: 0x01)                       */
#define DMAC_CFG5_H_FCMODE_Pos (0UL)        /*!< FCMODE (Bit 0)                                        */
#define DMAC_CFG5_H_FCMODE_Msk (0x1UL)      /*!< FCMODE (Bitfield-Mask: 0x01)                          */
/* ========================================================  CFG6_H  ========================================================= */
#define DMAC_CFG6_H_DEST_PER_Pos (11UL)     /*!< DEST_PER (Bit 11)                                     */
#define DMAC_CFG6_H_DEST_PER_Msk (0x7800UL) /*!< DEST_PER (Bitfield-Mask: 0x0f)                        */
#define DMAC_CFG6_H_SRC_PER_Pos (7UL)       /*!< SRC_PER (Bit 7)                                       */
#define DMAC_CFG6_H_SRC_PER_Msk (0x780UL)   /*!< SRC_PER (Bitfield-Mask: 0x0f)                         */
#define DMAC_CFG6_H_SS_UPD_EN_Pos (6UL)     /*!< SS_UPD_EN (Bit 6)                                     */
#define DMAC_CFG6_H_SS_UPD_EN_Msk (0x40UL)  /*!< SS_UPD_EN (Bitfield-Mask: 0x01)                       */
#define DMAC_CFG6_H_DS_UPD_EN_Pos (5UL)     /*!< DS_UPD_EN (Bit 5)                                     */
#define DMAC_CFG6_H_DS_UPD_EN_Msk (0x20UL)  /*!< DS_UPD_EN (Bitfield-Mask: 0x01)                       */
#define DMAC_CFG6_H_PROTCTL_Pos (2UL)       /*!< PROTCTL (Bit 2)                                       */
#define DMAC_CFG6_H_PROTCTL_Msk (0x1cUL)    /*!< PROTCTL (Bitfield-Mask: 0x07)                         */
#define DMAC_CFG6_H_FIFO_MODE_Pos (1UL)     /*!< FIFO_MODE (Bit 1)                                     */
#define DMAC_CFG6_H_FIFO_MODE_Msk (0x2UL)   /*!< FIFO_MODE (Bitfield-Mask: 0x01)                       */
#define DMAC_CFG6_H_FCMODE_Pos (0UL)        /*!< FCMODE (Bit 0)                                        */
#define DMAC_CFG6_H_FCMODE_Msk (0x1UL)      /*!< FCMODE (Bitfield-Mask: 0x01)                          */
/* ========================================================  CFG7_H  ========================================================= */
#define DMAC_CFG7_H_DEST_PER_Pos (11UL)     /*!< DEST_PER (Bit 11)                                     */
#define DMAC_CFG7_H_DEST_PER_Msk (0x7800UL) /*!< DEST_PER (Bitfield-Mask: 0x0f)                        */
#define DMAC_CFG7_H_SRC_PER_Pos (7UL)       /*!< SRC_PER (Bit 7)                                       */
#define DMAC_CFG7_H_SRC_PER_Msk (0x780UL)   /*!< SRC_PER (Bitfield-Mask: 0x0f)                         */
#define DMAC_CFG7_H_SS_UPD_EN_Pos (6UL)     /*!< SS_UPD_EN (Bit 6)                                     */
#define DMAC_CFG7_H_SS_UPD_EN_Msk (0x40UL)  /*!< SS_UPD_EN (Bitfield-Mask: 0x01)                       */
#define DMAC_CFG7_H_DS_UPD_EN_Pos (5UL)     /*!< DS_UPD_EN (Bit 5)                                     */
#define DMAC_CFG7_H_DS_UPD_EN_Msk (0x20UL)  /*!< DS_UPD_EN (Bitfield-Mask: 0x01)                       */
#define DMAC_CFG7_H_PROTCTL_Pos (2UL)       /*!< PROTCTL (Bit 2)                                       */
#define DMAC_CFG7_H_PROTCTL_Msk (0x1cUL)    /*!< PROTCTL (Bitfield-Mask: 0x07)                         */
#define DMAC_CFG7_H_FIFO_MODE_Pos (1UL)     /*!< FIFO_MODE (Bit 1)                                     */
#define DMAC_CFG7_H_FIFO_MODE_Msk (0x2UL)   /*!< FIFO_MODE (Bitfield-Mask: 0x01)                       */
#define DMAC_CFG7_H_FCMODE_Pos (0UL)        /*!< FCMODE (Bit 0)                                        */
#define DMAC_CFG7_H_FCMODE_Msk (0x1UL)      /*!< FCMODE (Bitfield-Mask: 0x01)                          */
/* =========================================================  SGR1  ========================================================== */
#define DMAC_SGR1_SGC_Pos (20UL)         /*!< SGC (Bit 20)                                          */
#define DMAC_SGR1_SGC_Msk (0xfff00000UL) /*!< SGC (Bitfield-Mask: 0xfff)                            */
#define DMAC_SGR1_SGI_Pos (0UL)          /*!< SGI (Bit 0)                                           */
#define DMAC_SGR1_SGI_Msk (0xfffffUL)    /*!< SGI (Bitfield-Mask: 0xfffff)                          */
/* =========================================================  SGR2  ========================================================== */
#define DMAC_SGR2_SGC_Pos (20UL)         /*!< SGC (Bit 20)                                          */
#define DMAC_SGR2_SGC_Msk (0xfff00000UL) /*!< SGC (Bitfield-Mask: 0xfff)                            */
#define DMAC_SGR2_SGI_Pos (0UL)          /*!< SGI (Bit 0)                                           */
#define DMAC_SGR2_SGI_Msk (0xfffffUL)    /*!< SGI (Bitfield-Mask: 0xfffff)                          */
/* =========================================================  SGR3  ========================================================== */
#define DMAC_SGR3_SGC_Pos (20UL)         /*!< SGC (Bit 20)                                          */
#define DMAC_SGR3_SGC_Msk (0xfff00000UL) /*!< SGC (Bitfield-Mask: 0xfff)                            */
#define DMAC_SGR3_SGI_Pos (0UL)          /*!< SGI (Bit 0)                                           */
#define DMAC_SGR3_SGI_Msk (0xfffffUL)    /*!< SGI (Bitfield-Mask: 0xfffff)                          */
/* =========================================================  SGR4  ========================================================== */
#define DMAC_SGR4_SGC_Pos (20UL)         /*!< SGC (Bit 20)                                          */
#define DMAC_SGR4_SGC_Msk (0xfff00000UL) /*!< SGC (Bitfield-Mask: 0xfff)                            */
#define DMAC_SGR4_SGI_Pos (0UL)          /*!< SGI (Bit 0)                                           */
#define DMAC_SGR4_SGI_Msk (0xfffffUL)    /*!< SGI (Bitfield-Mask: 0xfffff)                          */
/* =========================================================  SGR5  ========================================================== */
#define DMAC_SGR5_SGC_Pos (20UL)         /*!< SGC (Bit 20)                                          */
#define DMAC_SGR5_SGC_Msk (0xfff00000UL) /*!< SGC (Bitfield-Mask: 0xfff)                            */
#define DMAC_SGR5_SGI_Pos (0UL)          /*!< SGI (Bit 0)                                           */
#define DMAC_SGR5_SGI_Msk (0xfffffUL)    /*!< SGI (Bitfield-Mask: 0xfffff)                          */
/* =========================================================  SGR6  ========================================================== */
#define DMAC_SGR6_SGC_Pos (20UL)         /*!< SGC (Bit 20)                                          */
#define DMAC_SGR6_SGC_Msk (0xfff00000UL) /*!< SGC (Bitfield-Mask: 0xfff)                            */
#define DMAC_SGR6_SGI_Pos (0UL)          /*!< SGI (Bit 0)                                           */
#define DMAC_SGR6_SGI_Msk (0xfffffUL)    /*!< SGI (Bitfield-Mask: 0xfffff)                          */
/* =========================================================  SGR7  ========================================================== */
#define DMAC_SGR7_SGC_Pos (20UL)         /*!< SGC (Bit 20)                                          */
#define DMAC_SGR7_SGC_Msk (0xfff00000UL) /*!< SGC (Bitfield-Mask: 0xfff)                            */
#define DMAC_SGR7_SGI_Pos (0UL)          /*!< SGI (Bit 0)                                           */
#define DMAC_SGR7_SGI_Msk (0xfffffUL)    /*!< SGI (Bitfield-Mask: 0xfffff)                          */
/* =========================================================  DSR1  ========================================================== */
#define DMAC_DSR1_DSC_Pos (20UL)         /*!< DSC (Bit 20)                                          */
#define DMAC_DSR1_DSC_Msk (0xfff00000UL) /*!< DSC (Bitfield-Mask: 0xfff)                            */
#define DMAC_DSR1_DSI_Pos (0UL)          /*!< DSI (Bit 0)                                           */
#define DMAC_DSR1_DSI_Msk (0xfffffUL)    /*!< DSI (Bitfield-Mask: 0xfffff)                          */
/* =========================================================  DSR2  ========================================================== */
#define DMAC_DSR2_DSC_Pos (20UL)         /*!< DSC (Bit 20)                                          */
#define DMAC_DSR2_DSC_Msk (0xfff00000UL) /*!< DSC (Bitfield-Mask: 0xfff)                            */
#define DMAC_DSR2_DSI_Pos (0UL)          /*!< DSI (Bit 0)                                           */
#define DMAC_DSR2_DSI_Msk (0xfffffUL)    /*!< DSI (Bitfield-Mask: 0xfffff)                          */
/* =========================================================  DSR3  ========================================================== */
#define DMAC_DSR3_DSC_Pos (20UL)         /*!< DSC (Bit 20)                                          */
#define DMAC_DSR3_DSC_Msk (0xfff00000UL) /*!< DSC (Bitfield-Mask: 0xfff)                            */
#define DMAC_DSR3_DSI_Pos (0UL)          /*!< DSI (Bit 0)                                           */
#define DMAC_DSR3_DSI_Msk (0xfffffUL)    /*!< DSI (Bitfield-Mask: 0xfffff)                          */
/* =========================================================  DSR4  ========================================================== */
#define DMAC_DSR4_DSC_Pos (20UL)         /*!< DSC (Bit 20)                                          */
#define DMAC_DSR4_DSC_Msk (0xfff00000UL) /*!< DSC (Bitfield-Mask: 0xfff)                            */
#define DMAC_DSR4_DSI_Pos (0UL)          /*!< DSI (Bit 0)                                           */
#define DMAC_DSR4_DSI_Msk (0xfffffUL)    /*!< DSI (Bitfield-Mask: 0xfffff)                          */
/* =========================================================  DSR5  ========================================================== */
#define DMAC_DSR5_DSC_Pos (20UL)         /*!< DSC (Bit 20)                                          */
#define DMAC_DSR5_DSC_Msk (0xfff00000UL) /*!< DSC (Bitfield-Mask: 0xfff)                            */
#define DMAC_DSR5_DSI_Pos (0UL)          /*!< DSI (Bit 0)                                           */
#define DMAC_DSR5_DSI_Msk (0xfffffUL)    /*!< DSI (Bitfield-Mask: 0xfffff)                          */
/* =========================================================  DSR6  ========================================================== */
#define DMAC_DSR6_DSC_Pos (20UL)         /*!< DSC (Bit 20)                                          */
#define DMAC_DSR6_DSC_Msk (0xfff00000UL) /*!< DSC (Bitfield-Mask: 0xfff)                            */
#define DMAC_DSR6_DSI_Pos (0UL)          /*!< DSI (Bit 0)                                           */
#define DMAC_DSR6_DSI_Msk (0xfffffUL)    /*!< DSI (Bitfield-Mask: 0xfffff)                          */
/* =========================================================  DSR7  ========================================================== */
#define DMAC_DSR7_DSC_Pos (20UL)         /*!< DSC (Bit 20)                                          */
#define DMAC_DSR7_DSC_Msk (0xfff00000UL) /*!< DSC (Bitfield-Mask: 0xfff)                            */
#define DMAC_DSR7_DSI_Pos (0UL)          /*!< DSI (Bit 0)                                           */
#define DMAC_DSR7_DSI_Msk (0xfffffUL)    /*!< DSI (Bitfield-Mask: 0xfffff)                          */
/* ========================================================  RawTfr  ========================================================= */
#define DMAC_RawTfr_RAW_Pos (0UL)    /*!< RAW (Bit 0)                                           */
#define DMAC_RawTfr_RAW_Msk (0xffUL) /*!< RAW (Bitfield-Mask: 0xff)                             */
/* =======================================================  RawBlock  ======================================================== */
#define DMAC_RawBlock_RAW_Pos (0UL)    /*!< RAW (Bit 0)                                           */
#define DMAC_RawBlock_RAW_Msk (0xffUL) /*!< RAW (Bitfield-Mask: 0xff)                             */
/* ======================================================  RawSrcTran  ======================================================= */
#define DMAC_RawSrcTran_RAW_Pos (0UL)    /*!< RAW (Bit 0)                                           */
#define DMAC_RawSrcTran_RAW_Msk (0xffUL) /*!< RAW (Bitfield-Mask: 0xff)                             */
/* ======================================================  RawDstTran  ======================================================= */
#define DMAC_RawDstTran_RAW_Pos (0UL)    /*!< RAW (Bit 0)                                           */
#define DMAC_RawDstTran_RAW_Msk (0xffUL) /*!< RAW (Bitfield-Mask: 0xff)                             */
/* ========================================================  RawErr  ========================================================= */
#define DMAC_RawErr_RAW_Pos (0UL)    /*!< RAW (Bit 0)                                           */
#define DMAC_RawErr_RAW_Msk (0xffUL) /*!< RAW (Bitfield-Mask: 0xff)                             */
/* =======================================================  StatusTfr  ======================================================= */
#define DMAC_StatusTfr_STATUS_Pos (0UL)    /*!< STATUS (Bit 0)                                        */
#define DMAC_StatusTfr_STATUS_Msk (0xffUL) /*!< STATUS (Bitfield-Mask: 0xff)                          */
/* ======================================================  StatusBlock  ====================================================== */
#define DMAC_StatusBlock_STATUS_Pos (0UL)    /*!< STATUS (Bit 0)                                        */
#define DMAC_StatusBlock_STATUS_Msk (0xffUL) /*!< STATUS (Bitfield-Mask: 0xff)                          */
/* =====================================================  StatusSrcTran  ===================================================== */
#define DMAC_StatusSrcTran_STATUS_Pos (0UL)    /*!< STATUS (Bit 0)                                        */
#define DMAC_StatusSrcTran_STATUS_Msk (0xffUL) /*!< STATUS (Bitfield-Mask: 0xff)                          */
/* =====================================================  StatusDstTran  ===================================================== */
#define DMAC_StatusDstTran_STATUS_Pos (0UL)    /*!< STATUS (Bit 0)                                        */
#define DMAC_StatusDstTran_STATUS_Msk (0xffUL) /*!< STATUS (Bitfield-Mask: 0xff)                          */
/* =======================================================  StatusErr  ======================================================= */
#define DMAC_StatusErr_STATUS_Pos (0UL)    /*!< STATUS (Bit 0)                                        */
#define DMAC_StatusErr_STATUS_Msk (0xffUL) /*!< STATUS (Bitfield-Mask: 0xff)                          */
/* ========================================================  MaskTfr  ======================================================== */
#define DMAC_MaskTfr_INT_MASK_WE_Pos (8UL)      /*!< INT_MASK_WE (Bit 8)                                   */
#define DMAC_MaskTfr_INT_MASK_WE_Msk (0xff00UL) /*!< INT_MASK_WE (Bitfield-Mask: 0xff)                     */
/* =======================================================  MaskBlock  ======================================================= */
#define DMAC_MaskBlock_INT_MASK_WE_Pos (8UL)      /*!< INT_MASK_WE (Bit 8)                                   */
#define DMAC_MaskBlock_INT_MASK_WE_Msk (0xff00UL) /*!< INT_MASK_WE (Bitfield-Mask: 0xff)                     */
/* ======================================================  MaskSrcTran  ====================================================== */
#define DMAC_MaskSrcTran_INT_MASK_WE_Pos (8UL)      /*!< INT_MASK_WE (Bit 8)                                   */
#define DMAC_MaskSrcTran_INT_MASK_WE_Msk (0xff00UL) /*!< INT_MASK_WE (Bitfield-Mask: 0xff)                     */
/* ======================================================  MaskDstTran  ====================================================== */
#define DMAC_MaskDstTran_INT_MASK_WE_Pos (8UL)      /*!< INT_MASK_WE (Bit 8)                                   */
#define DMAC_MaskDstTran_INT_MASK_WE_Msk (0xff00UL) /*!< INT_MASK_WE (Bitfield-Mask: 0xff)                     */
/* ========================================================  MaskErr  ======================================================== */
#define DMAC_MaskErr_INT_MASK_WE_Pos (8UL)      /*!< INT_MASK_WE (Bit 8)                                   */
#define DMAC_MaskErr_INT_MASK_WE_Msk (0xff00UL) /*!< INT_MASK_WE (Bitfield-Mask: 0xff)                     */
/* =======================================================  ClearTfr  ======================================================== */
#define DMAC_ClearTfr_CLEAR_Pos (0UL)    /*!< CLEAR (Bit 0)                                         */
#define DMAC_ClearTfr_CLEAR_Msk (0xffUL) /*!< CLEAR (Bitfield-Mask: 0xff)                           */
/* ======================================================  ClearBlock  ======================================================= */
#define DMAC_ClearBlock_CLEAR_Pos (0UL)    /*!< CLEAR (Bit 0)                                         */
#define DMAC_ClearBlock_CLEAR_Msk (0xffUL) /*!< CLEAR (Bitfield-Mask: 0xff)                           */
/* =====================================================  ClearSrcTran  ====================================================== */
#define DMAC_ClearSrcTran_CLEAR_Pos (0UL)    /*!< CLEAR (Bit 0)                                         */
#define DMAC_ClearSrcTran_CLEAR_Msk (0xffUL) /*!< CLEAR (Bitfield-Mask: 0xff)                           */
/* =====================================================  ClearDstTran  ====================================================== */
#define DMAC_ClearDstTran_CLEAR_Pos (0UL)    /*!< CLEAR (Bit 0)                                         */
#define DMAC_ClearDstTran_CLEAR_Msk (0xffUL) /*!< CLEAR (Bitfield-Mask: 0xff)                           */
/* =======================================================  ClearErr  ======================================================== */
#define DMAC_ClearErr_CLEAR_Pos (0UL)    /*!< CLEAR (Bit 0)                                         */
#define DMAC_ClearErr_CLEAR_Msk (0xffUL) /*!< CLEAR (Bitfield-Mask: 0xff)                           */
/* =======================================================  StatusInt  ======================================================= */
#define DMAC_StatusInt_ERR_Pos (4UL)     /*!< ERR (Bit 4)                                           */
#define DMAC_StatusInt_ERR_Msk (0x10UL)  /*!< ERR (Bitfield-Mask: 0x01)                             */
#define DMAC_StatusInt_DSTT_Pos (3UL)    /*!< DSTT (Bit 3)                                          */
#define DMAC_StatusInt_DSTT_Msk (0x8UL)  /*!< DSTT (Bitfield-Mask: 0x01)                            */
#define DMAC_StatusInt_SRCT_Pos (2UL)    /*!< SRCT (Bit 2)                                          */
#define DMAC_StatusInt_SRCT_Msk (0x4UL)  /*!< SRCT (Bitfield-Mask: 0x01)                            */
#define DMAC_StatusInt_BLOCK_Pos (1UL)   /*!< BLOCK (Bit 1)                                         */
#define DMAC_StatusInt_BLOCK_Msk (0x2UL) /*!< BLOCK (Bitfield-Mask: 0x01)                           */
#define DMAC_StatusInt_TFR_Pos (0UL)     /*!< TFR (Bit 0)                                           */
#define DMAC_StatusInt_TFR_Msk (0x1UL)   /*!< TFR (Bitfield-Mask: 0x01)                             */
/* =======================================================  ReqSrcReg  ======================================================= */
#define DMAC_ReqSrcReg_SRC_REQ_WE_Pos (8UL)      /*!< SRC_REQ_WE (Bit 8)                                    */
#define DMAC_ReqSrcReg_SRC_REQ_WE_Msk (0xff00UL) /*!< SRC_REQ_WE (Bitfield-Mask: 0xff)                      */
#define DMAC_ReqSrcReg_SRC_REQ_Pos (0UL)         /*!< SRC_REQ (Bit 0)                                       */
#define DMAC_ReqSrcReg_SRC_REQ_Msk (0xffUL)      /*!< SRC_REQ (Bitfield-Mask: 0xff)                         */
/* =======================================================  ReqDstReg  ======================================================= */
#define DMAC_ReqDstReg_DST_REQ_WE_Pos (8UL)      /*!< DST_REQ_WE (Bit 8)                                    */
#define DMAC_ReqDstReg_DST_REQ_WE_Msk (0xff00UL) /*!< DST_REQ_WE (Bitfield-Mask: 0xff)                      */
#define DMAC_ReqDstReg_DST_REQ_Pos (0UL)         /*!< DST_REQ (Bit 0)                                       */
#define DMAC_ReqDstReg_DST_REQ_Msk (0xffUL)      /*!< DST_REQ (Bitfield-Mask: 0xff)                         */
/* =====================================================  SglReqSrcReg  ====================================================== */
#define DMAC_SglReqSrcReg_SRC_SGLREQ_WE_Pos (8UL)      /*!< SRC_SGLREQ_WE (Bit 8)                                 */
#define DMAC_SglReqSrcReg_SRC_SGLREQ_WE_Msk (0xff00UL) /*!< SRC_SGLREQ_WE (Bitfield-Mask: 0xff)                   */
#define DMAC_SglReqSrcReg_SRC_SGLREQ_Pos (0UL)         /*!< SRC_SGLREQ (Bit 0)                                    */
#define DMAC_SglReqSrcReg_SRC_SGLREQ_Msk (0xffUL)      /*!< SRC_SGLREQ (Bitfield-Mask: 0xff)                      */
/* =====================================================  SglReqDstReg  ====================================================== */
#define DMAC_SglReqDstReg_DST_SGLREQ_WE_Pos (8UL)      /*!< DST_SGLREQ_WE (Bit 8)                                 */
#define DMAC_SglReqDstReg_DST_SGLREQ_WE_Msk (0xff00UL) /*!< DST_SGLREQ_WE (Bitfield-Mask: 0xff)                   */
#define DMAC_SglReqDstReg_DST_SGLREQ_Pos (0UL)         /*!< DST_SGLREQ (Bit 0)                                    */
#define DMAC_SglReqDstReg_DST_SGLREQ_Msk (0xffUL)      /*!< DST_SGLREQ (Bitfield-Mask: 0xff)                      */
/* =======================================================  LstSrcReg  ======================================================= */
#define DMAC_LstSrcReg_LSTSRC_WE_Pos (8UL)      /*!< LSTSRC_WE (Bit 8)                                     */
#define DMAC_LstSrcReg_LSTSRC_WE_Msk (0xff00UL) /*!< LSTSRC_WE (Bitfield-Mask: 0xff)                       */
#define DMAC_LstSrcReg_LSTSRC_Pos (0UL)         /*!< LSTSRC (Bit 0)                                        */
#define DMAC_LstSrcReg_LSTSRC_Msk (0xffUL)      /*!< LSTSRC (Bitfield-Mask: 0xff)                          */
/* =======================================================  LstDstReg  ======================================================= */
#define DMAC_LstDstReg_LSTDST_WE_Pos (8UL)      /*!< LSTDST_WE (Bit 8)                                     */
#define DMAC_LstDstReg_LSTDST_WE_Msk (0xff00UL) /*!< LSTDST_WE (Bitfield-Mask: 0xff)                       */
#define DMAC_LstDstReg_LSTDST_Pos (0UL)         /*!< LSTDST (Bit 0)                                        */
#define DMAC_LstDstReg_LSTDST_Msk (0xffUL)      /*!< LSTDST (Bitfield-Mask: 0xff)                          */
/* =======================================================  DmaCfgReg  ======================================================= */
#define DMAC_DmaCfgReg_DMA_EN_Pos (0UL)   /*!< DMA_EN (Bit 0)                                        */
#define DMAC_DmaCfgReg_DMA_EN_Msk (0x1UL) /*!< DMA_EN (Bitfield-Mask: 0x01)                          */
/* ========================================================  ChEnReg  ======================================================== */
#define DMAC_ChEnReg_CH_EN_Pos (0UL)         /*!< CH_EN (Bit 0)                                         */
#define DMAC_ChEnReg_CH_EN_Msk (0xffUL)      /*!< CH_EN (Bitfield-Mask: 0xff)                           */
#define DMAC_ChEnReg_CH_EN_WE_Pos (8UL)      /*!< CH_EN_WE (Bit 8)                                      */
#define DMAC_ChEnReg_CH_EN_WE_Msk (0xff00UL) /*!< CH_EN_WE (Bitfield-Mask: 0xff)                        */
/* =======================================================  DmaIdReg  ======================================================== */
#define DMAC_DmaIdReg_DMA_ID_Pos (0UL)          /*!< DMA_ID (Bit 0)                                        */
#define DMAC_DmaIdReg_DMA_ID_Msk (0xffffffffUL) /*!< DMA_ID (Bitfield-Mask: 0xffffffff)                    */
/* ======================================================  DmaTestReg  ======================================================= */
#define DMAC_DmaTestReg_TEST_SLV_IF_Pos (0UL)   /*!< TEST_SLV_IF (Bit 0)                                   */
#define DMAC_DmaTestReg_TEST_SLV_IF_Msk (0x1UL) /*!< TEST_SLV_IF (Bitfield-Mask: 0x01)                     */
/* ===================================================  DMA_COMP_PARAMS_6  =================================================== */
#define DMAC_DMA_COMP_PARAMS_6_CH7_FIFO_DEPTH_Pos (28UL)         /*!< CH7_FIFO_DEPTH (Bit 28)                               */
#define DMAC_DMA_COMP_PARAMS_6_CH7_FIFO_DEPTH_Msk (0x70000000UL) /*!< CH7_FIFO_DEPTH (Bitfield-Mask: 0x07)                  */
#define DMAC_DMA_COMP_PARAMS_6_CH7_SMS_Pos (25UL)                /*!< CH7_SMS (Bit 25)                                      */
#define DMAC_DMA_COMP_PARAMS_6_CH7_SMS_Msk (0xe000000UL)         /*!< CH7_SMS (Bitfield-Mask: 0x07)                         */
#define DMAC_DMA_COMP_PARAMS_6_CH7_LMS_Pos (22UL)                /*!< CH7_LMS (Bit 22)                                      */
#define DMAC_DMA_COMP_PARAMS_6_CH7_LMS_Msk (0x1c00000UL)         /*!< CH7_LMS (Bitfield-Mask: 0x07)                         */
#define DMAC_DMA_COMP_PARAMS_6_CH7_DMS_Pos (19UL)                /*!< CH7_DMS (Bit 19)                                      */
#define DMAC_DMA_COMP_PARAMS_6_CH7_DMS_Msk (0x380000UL)          /*!< CH7_DMS (Bitfield-Mask: 0x07)                         */
#define DMAC_DMA_COMP_PARAMS_6_CH7_MAX_MULT_SIZE_Pos (16UL)      /*!< CH7_MAX_MULT_SIZE (Bit 16)                            */
#define DMAC_DMA_COMP_PARAMS_6_CH7_MAX_MULT_SIZE_Msk (0x70000UL) /*!< CH7_MAX_MULT_SIZE (Bitfield-Mask: 0x07)               */
#define DMAC_DMA_COMP_PARAMS_6_CH7_FC_Pos (14UL)                 /*!< CH7_FC (Bit 14)                                       */
#define DMAC_DMA_COMP_PARAMS_6_CH7_FC_Msk (0x4000UL)             /*!< CH7_FC (Bitfield-Mask: 0x01)                          */
#define DMAC_DMA_COMP_PARAMS_6_CH7_HC_LLP_Pos (13UL)             /*!< CH7_HC_LLP (Bit 13)                                   */
#define DMAC_DMA_COMP_PARAMS_6_CH7_HC_LLP_Msk (0x2000UL)         /*!< CH7_HC_LLP (Bitfield-Mask: 0x01)                      */
#define DMAC_DMA_COMP_PARAMS_6_CH7_CTL_WB_EN_Pos (12UL)          /*!< CH7_CTL_WB_EN (Bit 12)                                */
#define DMAC_DMA_COMP_PARAMS_6_CH7_CTL_WB_EN_Msk (0x1000UL)      /*!< CH7_CTL_WB_EN (Bitfield-Mask: 0x01)                   */
#define DMAC_DMA_COMP_PARAMS_6_CH7_MULTI_BLK_EN_Pos (11UL)       /*!< CH7_MULTI_BLK_EN (Bit 11)                             */
#define DMAC_DMA_COMP_PARAMS_6_CH7_MULTI_BLK_EN_Msk (0x800UL)    /*!< CH7_MULTI_BLK_EN (Bitfield-Mask: 0x01)                */
#define DMAC_DMA_COMP_PARAMS_6_CH7_LOCK_EN_Pos (10UL)            /*!< CH7_LOCK_EN (Bit 10)                                  */
#define DMAC_DMA_COMP_PARAMS_6_CH7_LOCK_EN_Msk (0x400UL)         /*!< CH7_LOCK_EN (Bitfield-Mask: 0x01)                     */
#define DMAC_DMA_COMP_PARAMS_6_CH7_SRC_GAT_EN_Pos (9UL)          /*!< CH7_SRC_GAT_EN (Bit 9)                                */
#define DMAC_DMA_COMP_PARAMS_6_CH7_SRC_GAT_EN_Msk (0x200UL)      /*!< CH7_SRC_GAT_EN (Bitfield-Mask: 0x01)                  */
#define DMAC_DMA_COMP_PARAMS_6_CH7_DST_SCA_EN_Pos (8UL)          /*!< CH7_DST_SCA_EN (Bit 8)                                */
#define DMAC_DMA_COMP_PARAMS_6_CH7_DST_SCA_EN_Msk (0x100UL)      /*!< CH7_DST_SCA_EN (Bitfield-Mask: 0x01)                  */
#define DMAC_DMA_COMP_PARAMS_6_CH7_STAT_SRC_Pos (7UL)            /*!< CH7_STAT_SRC (Bit 7)                                  */
#define DMAC_DMA_COMP_PARAMS_6_CH7_STAT_SRC_Msk (0x80UL)         /*!< CH7_STAT_SRC (Bitfield-Mask: 0x01)                    */
#define DMAC_DMA_COMP_PARAMS_6_CH7_STAT_DST_Pos (6UL)            /*!< CH7_STAT_DST (Bit 6)                                  */
#define DMAC_DMA_COMP_PARAMS_6_CH7_STAT_DST_Msk (0x40UL)         /*!< CH7_STAT_DST (Bitfield-Mask: 0x01)                    */
#define DMAC_DMA_COMP_PARAMS_6_CH7_STW_Pos (3UL)                 /*!< CH7_STW (Bit 3)                                       */
#define DMAC_DMA_COMP_PARAMS_6_CH7_STW_Msk (0x38UL)              /*!< CH7_STW (Bitfield-Mask: 0x07)                         */
#define DMAC_DMA_COMP_PARAMS_6_CH7_DTW_Pos (0UL)                 /*!< CH7_DTW (Bit 0)                                       */
#define DMAC_DMA_COMP_PARAMS_6_CH7_DTW_Msk (0x7UL)               /*!< CH7_DTW (Bitfield-Mask: 0x07)                         */
/* ==================================================  DMA_COMP_PARAMS_5H  =================================================== */
#define DMAC_DMA_COMP_PARAMS_5H_CH5_FIFO_DEPTH_Pos (28UL)         /*!< CH5_FIFO_DEPTH (Bit 28)                               */
#define DMAC_DMA_COMP_PARAMS_5H_CH5_FIFO_DEPTH_Msk (0x70000000UL) /*!< CH5_FIFO_DEPTH (Bitfield-Mask: 0x07)                  */
#define DMAC_DMA_COMP_PARAMS_5H_CH5_SMS_Pos (25UL)                /*!< CH5_SMS (Bit 25)                                      */
#define DMAC_DMA_COMP_PARAMS_5H_CH5_SMS_Msk (0xe000000UL)         /*!< CH5_SMS (Bitfield-Mask: 0x07)                         */
#define DMAC_DMA_COMP_PARAMS_5H_CH5_LMS_Pos (22UL)                /*!< CH5_LMS (Bit 22)                                      */
#define DMAC_DMA_COMP_PARAMS_5H_CH5_LMS_Msk (0x1c00000UL)         /*!< CH5_LMS (Bitfield-Mask: 0x07)                         */
#define DMAC_DMA_COMP_PARAMS_5H_CH5_DMS_Pos (19UL)                /*!< CH5_DMS (Bit 19)                                      */
#define DMAC_DMA_COMP_PARAMS_5H_CH5_DMS_Msk (0x380000UL)          /*!< CH5_DMS (Bitfield-Mask: 0x07)                         */
#define DMAC_DMA_COMP_PARAMS_5H_CH5_MAX_MULT_SIZE_Pos (16UL)      /*!< CH5_MAX_MULT_SIZE (Bit 16)                            */
#define DMAC_DMA_COMP_PARAMS_5H_CH5_MAX_MULT_SIZE_Msk (0x70000UL) /*!< CH5_MAX_MULT_SIZE (Bitfield-Mask: 0x07)               */
#define DMAC_DMA_COMP_PARAMS_5H_CH5_FC_Pos (14UL)                 /*!< CH5_FC (Bit 14)                                       */
#define DMAC_DMA_COMP_PARAMS_5H_CH5_FC_Msk (0x4000UL)             /*!< CH5_FC (Bitfield-Mask: 0x01)                          */
#define DMAC_DMA_COMP_PARAMS_5H_CH5_HC_LLP_Pos (13UL)             /*!< CH5_HC_LLP (Bit 13)                                   */
#define DMAC_DMA_COMP_PARAMS_5H_CH5_HC_LLP_Msk (0x2000UL)         /*!< CH5_HC_LLP (Bitfield-Mask: 0x01)                      */
#define DMAC_DMA_COMP_PARAMS_5H_CH5_CTL_WB_EN_Pos (12UL)          /*!< CH5_CTL_WB_EN (Bit 12)                                */
#define DMAC_DMA_COMP_PARAMS_5H_CH5_CTL_WB_EN_Msk (0x1000UL)      /*!< CH5_CTL_WB_EN (Bitfield-Mask: 0x01)                   */
#define DMAC_DMA_COMP_PARAMS_5H_CH5_MULTI_BLK_EN_Pos (11UL)       /*!< CH5_MULTI_BLK_EN (Bit 11)                             */
#define DMAC_DMA_COMP_PARAMS_5H_CH5_MULTI_BLK_EN_Msk (0x800UL)    /*!< CH5_MULTI_BLK_EN (Bitfield-Mask: 0x01)                */
#define DMAC_DMA_COMP_PARAMS_5H_CH5_LOCK_EN_Pos (10UL)            /*!< CH5_LOCK_EN (Bit 10)                                  */
#define DMAC_DMA_COMP_PARAMS_5H_CH5_LOCK_EN_Msk (0x400UL)         /*!< CH5_LOCK_EN (Bitfield-Mask: 0x01)                     */
#define DMAC_DMA_COMP_PARAMS_5H_CH5_SRC_GAT_EN_Pos (9UL)          /*!< CH5_SRC_GAT_EN (Bit 9)                                */
#define DMAC_DMA_COMP_PARAMS_5H_CH5_SRC_GAT_EN_Msk (0x200UL)      /*!< CH5_SRC_GAT_EN (Bitfield-Mask: 0x01)                  */
#define DMAC_DMA_COMP_PARAMS_5H_CH5_DST_SCA_EN_Pos (8UL)          /*!< CH5_DST_SCA_EN (Bit 8)                                */
#define DMAC_DMA_COMP_PARAMS_5H_CH5_DST_SCA_EN_Msk (0x100UL)      /*!< CH5_DST_SCA_EN (Bitfield-Mask: 0x01)                  */
#define DMAC_DMA_COMP_PARAMS_5H_CH5_STAT_SRC_Pos (7UL)            /*!< CH5_STAT_SRC (Bit 7)                                  */
#define DMAC_DMA_COMP_PARAMS_5H_CH5_STAT_SRC_Msk (0x80UL)         /*!< CH5_STAT_SRC (Bitfield-Mask: 0x01)                    */
#define DMAC_DMA_COMP_PARAMS_5H_CH5_STAT_DST_Pos (6UL)            /*!< CH5_STAT_DST (Bit 6)                                  */
#define DMAC_DMA_COMP_PARAMS_5H_CH5_STAT_DST_Msk (0x40UL)         /*!< CH5_STAT_DST (Bitfield-Mask: 0x01)                    */
#define DMAC_DMA_COMP_PARAMS_5H_CH5_STW_Pos (3UL)                 /*!< CH5_STW (Bit 3)                                       */
#define DMAC_DMA_COMP_PARAMS_5H_CH5_STW_Msk (0x38UL)              /*!< CH5_STW (Bitfield-Mask: 0x07)                         */
#define DMAC_DMA_COMP_PARAMS_5H_CH5_DTW_Pos (0UL)                 /*!< CH5_DTW (Bit 0)                                       */
#define DMAC_DMA_COMP_PARAMS_5H_CH5_DTW_Msk (0x7UL)               /*!< CH5_DTW (Bitfield-Mask: 0x07)                         */
/* ==================================================  DMA_COMP_PARAMS_5L  =================================================== */
#define DMAC_DMA_COMP_PARAMS_5L_CH6_FIFO_DEPTH_Pos (28UL)         /*!< CH6_FIFO_DEPTH (Bit 28)                               */
#define DMAC_DMA_COMP_PARAMS_5L_CH6_FIFO_DEPTH_Msk (0x70000000UL) /*!< CH6_FIFO_DEPTH (Bitfield-Mask: 0x07)                  */
#define DMAC_DMA_COMP_PARAMS_5L_CH6_SMS_Pos (25UL)                /*!< CH6_SMS (Bit 25)                                      */
#define DMAC_DMA_COMP_PARAMS_5L_CH6_SMS_Msk (0xe000000UL)         /*!< CH6_SMS (Bitfield-Mask: 0x07)                         */
#define DMAC_DMA_COMP_PARAMS_5L_CH6_LMS_Pos (22UL)                /*!< CH6_LMS (Bit 22)                                      */
#define DMAC_DMA_COMP_PARAMS_5L_CH6_LMS_Msk (0x1c00000UL)         /*!< CH6_LMS (Bitfield-Mask: 0x07)                         */
#define DMAC_DMA_COMP_PARAMS_5L_CH6_DMS_Pos (19UL)                /*!< CH6_DMS (Bit 19)                                      */
#define DMAC_DMA_COMP_PARAMS_5L_CH6_DMS_Msk (0x380000UL)          /*!< CH6_DMS (Bitfield-Mask: 0x07)                         */
#define DMAC_DMA_COMP_PARAMS_5L_CH6_MAX_MULT_SIZE_Pos (16UL)      /*!< CH6_MAX_MULT_SIZE (Bit 16)                            */
#define DMAC_DMA_COMP_PARAMS_5L_CH6_MAX_MULT_SIZE_Msk (0x70000UL) /*!< CH6_MAX_MULT_SIZE (Bitfield-Mask: 0x07)               */
#define DMAC_DMA_COMP_PARAMS_5L_CH6_FC_Pos (14UL)                 /*!< CH6_FC (Bit 14)                                       */
#define DMAC_DMA_COMP_PARAMS_5L_CH6_FC_Msk (0x4000UL)             /*!< CH6_FC (Bitfield-Mask: 0x01)                          */
#define DMAC_DMA_COMP_PARAMS_5L_CH6_HC_LLP_Pos (13UL)             /*!< CH6_HC_LLP (Bit 13)                                   */
#define DMAC_DMA_COMP_PARAMS_5L_CH6_HC_LLP_Msk (0x2000UL)         /*!< CH6_HC_LLP (Bitfield-Mask: 0x01)                      */
#define DMAC_DMA_COMP_PARAMS_5L_CH6_CTL_WB_EN_Pos (12UL)          /*!< CH6_CTL_WB_EN (Bit 12)                                */
#define DMAC_DMA_COMP_PARAMS_5L_CH6_CTL_WB_EN_Msk (0x1000UL)      /*!< CH6_CTL_WB_EN (Bitfield-Mask: 0x01)                   */
#define DMAC_DMA_COMP_PARAMS_5L_CH6_MULTI_BLK_EN_Pos (11UL)       /*!< CH6_MULTI_BLK_EN (Bit 11)                             */
#define DMAC_DMA_COMP_PARAMS_5L_CH6_MULTI_BLK_EN_Msk (0x800UL)    /*!< CH6_MULTI_BLK_EN (Bitfield-Mask: 0x01)                */
#define DMAC_DMA_COMP_PARAMS_5L_CH6_LOCK_EN_Pos (10UL)            /*!< CH6_LOCK_EN (Bit 10)                                  */
#define DMAC_DMA_COMP_PARAMS_5L_CH6_LOCK_EN_Msk (0x400UL)         /*!< CH6_LOCK_EN (Bitfield-Mask: 0x01)                     */
#define DMAC_DMA_COMP_PARAMS_5L_CH6_SRC_GAT_EN_Pos (9UL)          /*!< CH6_SRC_GAT_EN (Bit 9)                                */
#define DMAC_DMA_COMP_PARAMS_5L_CH6_SRC_GAT_EN_Msk (0x200UL)      /*!< CH6_SRC_GAT_EN (Bitfield-Mask: 0x01)                  */
#define DMAC_DMA_COMP_PARAMS_5L_CH6_DST_SCA_EN_Pos (8UL)          /*!< CH6_DST_SCA_EN (Bit 8)                                */
#define DMAC_DMA_COMP_PARAMS_5L_CH6_DST_SCA_EN_Msk (0x100UL)      /*!< CH6_DST_SCA_EN (Bitfield-Mask: 0x01)                  */
#define DMAC_DMA_COMP_PARAMS_5L_CH6_STAT_SRC_Pos (7UL)            /*!< CH6_STAT_SRC (Bit 7)                                  */
#define DMAC_DMA_COMP_PARAMS_5L_CH6_STAT_SRC_Msk (0x80UL)         /*!< CH6_STAT_SRC (Bitfield-Mask: 0x01)                    */
#define DMAC_DMA_COMP_PARAMS_5L_CH6_STAT_DST_Pos (6UL)            /*!< CH6_STAT_DST (Bit 6)                                  */
#define DMAC_DMA_COMP_PARAMS_5L_CH6_STAT_DST_Msk (0x40UL)         /*!< CH6_STAT_DST (Bitfield-Mask: 0x01)                    */
#define DMAC_DMA_COMP_PARAMS_5L_CH6_STW_Pos (3UL)                 /*!< CH6_STW (Bit 3)                                       */
#define DMAC_DMA_COMP_PARAMS_5L_CH6_STW_Msk (0x38UL)              /*!< CH6_STW (Bitfield-Mask: 0x07)                         */
#define DMAC_DMA_COMP_PARAMS_5L_CH6_DTW_Pos (0UL)                 /*!< CH6_DTW (Bit 0)                                       */
#define DMAC_DMA_COMP_PARAMS_5L_CH6_DTW_Msk (0x7UL)               /*!< CH6_DTW (Bitfield-Mask: 0x07)                         */
/* ==================================================  DMA_COMP_PARAMS_4H  =================================================== */
#define DMAC_DMA_COMP_PARAMS_4H_CH3_FIFO_DEPTH_Pos (28UL)         /*!< CH3_FIFO_DEPTH (Bit 28)                               */
#define DMAC_DMA_COMP_PARAMS_4H_CH3_FIFO_DEPTH_Msk (0x70000000UL) /*!< CH3_FIFO_DEPTH (Bitfield-Mask: 0x07)                  */
#define DMAC_DMA_COMP_PARAMS_4H_CH3_SMS_Pos (25UL)                /*!< CH3_SMS (Bit 25)                                      */
#define DMAC_DMA_COMP_PARAMS_4H_CH3_SMS_Msk (0xe000000UL)         /*!< CH3_SMS (Bitfield-Mask: 0x07)                         */
#define DMAC_DMA_COMP_PARAMS_4H_CH3_LMS_Pos (22UL)                /*!< CH3_LMS (Bit 22)                                      */
#define DMAC_DMA_COMP_PARAMS_4H_CH3_LMS_Msk (0x1c00000UL)         /*!< CH3_LMS (Bitfield-Mask: 0x07)                         */
#define DMAC_DMA_COMP_PARAMS_4H_CH3_DMS_Pos (19UL)                /*!< CH3_DMS (Bit 19)                                      */
#define DMAC_DMA_COMP_PARAMS_4H_CH3_DMS_Msk (0x380000UL)          /*!< CH3_DMS (Bitfield-Mask: 0x07)                         */
#define DMAC_DMA_COMP_PARAMS_4H_CH3_MAX_MULT_SIZE_Pos (16UL)      /*!< CH3_MAX_MULT_SIZE (Bit 16)                            */
#define DMAC_DMA_COMP_PARAMS_4H_CH3_MAX_MULT_SIZE_Msk (0x70000UL) /*!< CH3_MAX_MULT_SIZE (Bitfield-Mask: 0x07)               */
#define DMAC_DMA_COMP_PARAMS_4H_CH3_FC_Pos (14UL)                 /*!< CH3_FC (Bit 14)                                       */
#define DMAC_DMA_COMP_PARAMS_4H_CH3_FC_Msk (0x4000UL)             /*!< CH3_FC (Bitfield-Mask: 0x01)                          */
#define DMAC_DMA_COMP_PARAMS_4H_CH3_HC_LLP_Pos (13UL)             /*!< CH3_HC_LLP (Bit 13)                                   */
#define DMAC_DMA_COMP_PARAMS_4H_CH3_HC_LLP_Msk (0x2000UL)         /*!< CH3_HC_LLP (Bitfield-Mask: 0x01)                      */
#define DMAC_DMA_COMP_PARAMS_4H_CH3_CTL_WB_EN_Pos (12UL)          /*!< CH3_CTL_WB_EN (Bit 12)                                */
#define DMAC_DMA_COMP_PARAMS_4H_CH3_CTL_WB_EN_Msk (0x1000UL)      /*!< CH3_CTL_WB_EN (Bitfield-Mask: 0x01)                   */
#define DMAC_DMA_COMP_PARAMS_4H_CH3_MULTI_BLK_EN_Pos (11UL)       /*!< CH3_MULTI_BLK_EN (Bit 11)                             */
#define DMAC_DMA_COMP_PARAMS_4H_CH3_MULTI_BLK_EN_Msk (0x800UL)    /*!< CH3_MULTI_BLK_EN (Bitfield-Mask: 0x01)                */
#define DMAC_DMA_COMP_PARAMS_4H_CH3_LOCK_EN_Pos (10UL)            /*!< CH3_LOCK_EN (Bit 10)                                  */
#define DMAC_DMA_COMP_PARAMS_4H_CH3_LOCK_EN_Msk (0x400UL)         /*!< CH3_LOCK_EN (Bitfield-Mask: 0x01)                     */
#define DMAC_DMA_COMP_PARAMS_4H_CH3_SRC_GAT_EN_Pos (9UL)          /*!< CH3_SRC_GAT_EN (Bit 9)                                */
#define DMAC_DMA_COMP_PARAMS_4H_CH3_SRC_GAT_EN_Msk (0x200UL)      /*!< CH3_SRC_GAT_EN (Bitfield-Mask: 0x01)                  */
#define DMAC_DMA_COMP_PARAMS_4H_CH3_DST_SCA_EN_Pos (8UL)          /*!< CH3_DST_SCA_EN (Bit 8)                                */
#define DMAC_DMA_COMP_PARAMS_4H_CH3_DST_SCA_EN_Msk (0x100UL)      /*!< CH3_DST_SCA_EN (Bitfield-Mask: 0x01)                  */
#define DMAC_DMA_COMP_PARAMS_4H_CH3_STAT_SRC_Pos (7UL)            /*!< CH3_STAT_SRC (Bit 7)                                  */
#define DMAC_DMA_COMP_PARAMS_4H_CH3_STAT_SRC_Msk (0x80UL)         /*!< CH3_STAT_SRC (Bitfield-Mask: 0x01)                    */
#define DMAC_DMA_COMP_PARAMS_4H_CH3_STAT_DST_Pos (6UL)            /*!< CH3_STAT_DST (Bit 6)                                  */
#define DMAC_DMA_COMP_PARAMS_4H_CH3_STAT_DST_Msk (0x40UL)         /*!< CH3_STAT_DST (Bitfield-Mask: 0x01)                    */
#define DMAC_DMA_COMP_PARAMS_4H_CH3_STW_Pos (3UL)                 /*!< CH3_STW (Bit 3)                                       */
#define DMAC_DMA_COMP_PARAMS_4H_CH3_STW_Msk (0x38UL)              /*!< CH3_STW (Bitfield-Mask: 0x07)                         */
#define DMAC_DMA_COMP_PARAMS_4H_CH3_DTW_Pos (0UL)                 /*!< CH3_DTW (Bit 0)                                       */
#define DMAC_DMA_COMP_PARAMS_4H_CH3_DTW_Msk (0x7UL)               /*!< CH3_DTW (Bitfield-Mask: 0x07)                         */
/* ==================================================  DMA_COMP_PARAMS_4L  =================================================== */
#define DMAC_DMA_COMP_PARAMS_4L_CH4_FIFO_DEPTH_Pos (28UL)         /*!< CH4_FIFO_DEPTH (Bit 28)                               */
#define DMAC_DMA_COMP_PARAMS_4L_CH4_FIFO_DEPTH_Msk (0x70000000UL) /*!< CH4_FIFO_DEPTH (Bitfield-Mask: 0x07)                  */
#define DMAC_DMA_COMP_PARAMS_4L_CH4_SMS_Pos (25UL)                /*!< CH4_SMS (Bit 25)                                      */
#define DMAC_DMA_COMP_PARAMS_4L_CH4_SMS_Msk (0xe000000UL)         /*!< CH4_SMS (Bitfield-Mask: 0x07)                         */
#define DMAC_DMA_COMP_PARAMS_4L_CH4_LMS_Pos (22UL)                /*!< CH4_LMS (Bit 22)                                      */
#define DMAC_DMA_COMP_PARAMS_4L_CH4_LMS_Msk (0x1c00000UL)         /*!< CH4_LMS (Bitfield-Mask: 0x07)                         */
#define DMAC_DMA_COMP_PARAMS_4L_CH4_DMS_Pos (19UL)                /*!< CH4_DMS (Bit 19)                                      */
#define DMAC_DMA_COMP_PARAMS_4L_CH4_DMS_Msk (0x380000UL)          /*!< CH4_DMS (Bitfield-Mask: 0x07)                         */
#define DMAC_DMA_COMP_PARAMS_4L_CH4_MAX_MULT_SIZE_Pos (16UL)      /*!< CH4_MAX_MULT_SIZE (Bit 16)                            */
#define DMAC_DMA_COMP_PARAMS_4L_CH4_MAX_MULT_SIZE_Msk (0x70000UL) /*!< CH4_MAX_MULT_SIZE (Bitfield-Mask: 0x07)               */
#define DMAC_DMA_COMP_PARAMS_4L_CH4_FC_Pos (14UL)                 /*!< CH4_FC (Bit 14)                                       */
#define DMAC_DMA_COMP_PARAMS_4L_CH4_FC_Msk (0x4000UL)             /*!< CH4_FC (Bitfield-Mask: 0x01)                          */
#define DMAC_DMA_COMP_PARAMS_4L_CH4_HC_LLP_Pos (13UL)             /*!< CH4_HC_LLP (Bit 13)                                   */
#define DMAC_DMA_COMP_PARAMS_4L_CH4_HC_LLP_Msk (0x2000UL)         /*!< CH4_HC_LLP (Bitfield-Mask: 0x01)                      */
#define DMAC_DMA_COMP_PARAMS_4L_CH4_CTL_WB_EN_Pos (12UL)          /*!< CH4_CTL_WB_EN (Bit 12)                                */
#define DMAC_DMA_COMP_PARAMS_4L_CH4_CTL_WB_EN_Msk (0x1000UL)      /*!< CH4_CTL_WB_EN (Bitfield-Mask: 0x01)                   */
#define DMAC_DMA_COMP_PARAMS_4L_CH4_MULTI_BLK_EN_Pos (11UL)       /*!< CH4_MULTI_BLK_EN (Bit 11)                             */
#define DMAC_DMA_COMP_PARAMS_4L_CH4_MULTI_BLK_EN_Msk (0x800UL)    /*!< CH4_MULTI_BLK_EN (Bitfield-Mask: 0x01)                */
#define DMAC_DMA_COMP_PARAMS_4L_CH4_LOCK_EN_Pos (10UL)            /*!< CH4_LOCK_EN (Bit 10)                                  */
#define DMAC_DMA_COMP_PARAMS_4L_CH4_LOCK_EN_Msk (0x400UL)         /*!< CH4_LOCK_EN (Bitfield-Mask: 0x01)                     */
#define DMAC_DMA_COMP_PARAMS_4L_CH4_SRC_GAT_EN_Pos (9UL)          /*!< CH4_SRC_GAT_EN (Bit 9)                                */
#define DMAC_DMA_COMP_PARAMS_4L_CH4_SRC_GAT_EN_Msk (0x200UL)      /*!< CH4_SRC_GAT_EN (Bitfield-Mask: 0x01)                  */
#define DMAC_DMA_COMP_PARAMS_4L_CH4_DST_SCA_EN_Pos (8UL)          /*!< CH4_DST_SCA_EN (Bit 8)                                */
#define DMAC_DMA_COMP_PARAMS_4L_CH4_DST_SCA_EN_Msk (0x100UL)      /*!< CH4_DST_SCA_EN (Bitfield-Mask: 0x01)                  */
#define DMAC_DMA_COMP_PARAMS_4L_CH4_STAT_SRC_Pos (7UL)            /*!< CH4_STAT_SRC (Bit 7)                                  */
#define DMAC_DMA_COMP_PARAMS_4L_CH4_STAT_SRC_Msk (0x80UL)         /*!< CH4_STAT_SRC (Bitfield-Mask: 0x01)                    */
#define DMAC_DMA_COMP_PARAMS_4L_CH4_STAT_DST_Pos (6UL)            /*!< CH4_STAT_DST (Bit 6)                                  */
#define DMAC_DMA_COMP_PARAMS_4L_CH4_STAT_DST_Msk (0x40UL)         /*!< CH4_STAT_DST (Bitfield-Mask: 0x01)                    */
#define DMAC_DMA_COMP_PARAMS_4L_CH4_STW_Pos (3UL)                 /*!< CH4_STW (Bit 3)                                       */
#define DMAC_DMA_COMP_PARAMS_4L_CH4_STW_Msk (0x38UL)              /*!< CH4_STW (Bitfield-Mask: 0x07)                         */
#define DMAC_DMA_COMP_PARAMS_4L_CH4_DTW_Pos (0UL)                 /*!< CH4_DTW (Bit 0)                                       */
#define DMAC_DMA_COMP_PARAMS_4L_CH4_DTW_Msk (0x7UL)               /*!< CH4_DTW (Bitfield-Mask: 0x07)                         */
/* ==================================================  DMA_COMP_PARAMS_3H  =================================================== */
#define DMAC_DMA_COMP_PARAMS_3H_CH1_FIFO_DEPTH_Pos (28UL)         /*!< CH1_FIFO_DEPTH (Bit 28)                               */
#define DMAC_DMA_COMP_PARAMS_3H_CH1_FIFO_DEPTH_Msk (0x70000000UL) /*!< CH1_FIFO_DEPTH (Bitfield-Mask: 0x07)                  */
#define DMAC_DMA_COMP_PARAMS_3H_CH1_SMS_Pos (25UL)                /*!< CH1_SMS (Bit 25)                                      */
#define DMAC_DMA_COMP_PARAMS_3H_CH1_SMS_Msk (0xe000000UL)         /*!< CH1_SMS (Bitfield-Mask: 0x07)                         */
#define DMAC_DMA_COMP_PARAMS_3H_CH1_LMS_Pos (22UL)                /*!< CH1_LMS (Bit 22)                                      */
#define DMAC_DMA_COMP_PARAMS_3H_CH1_LMS_Msk (0x1c00000UL)         /*!< CH1_LMS (Bitfield-Mask: 0x07)                         */
#define DMAC_DMA_COMP_PARAMS_3H_CH1_DMS_Pos (19UL)                /*!< CH1_DMS (Bit 19)                                      */
#define DMAC_DMA_COMP_PARAMS_3H_CH1_DMS_Msk (0x380000UL)          /*!< CH1_DMS (Bitfield-Mask: 0x07)                         */
#define DMAC_DMA_COMP_PARAMS_3H_CH1_MAX_MULT_SIZE_Pos (16UL)      /*!< CH1_MAX_MULT_SIZE (Bit 16)                            */
#define DMAC_DMA_COMP_PARAMS_3H_CH1_MAX_MULT_SIZE_Msk (0x70000UL) /*!< CH1_MAX_MULT_SIZE (Bitfield-Mask: 0x07)               */
#define DMAC_DMA_COMP_PARAMS_3H_CH1_FC_Pos (14UL)                 /*!< CH1_FC (Bit 14)                                       */
#define DMAC_DMA_COMP_PARAMS_3H_CH1_FC_Msk (0x4000UL)             /*!< CH1_FC (Bitfield-Mask: 0x01)                          */
#define DMAC_DMA_COMP_PARAMS_3H_CH1_HC_LLP_Pos (13UL)             /*!< CH1_HC_LLP (Bit 13)                                   */
#define DMAC_DMA_COMP_PARAMS_3H_CH1_HC_LLP_Msk (0x2000UL)         /*!< CH1_HC_LLP (Bitfield-Mask: 0x01)                      */
#define DMAC_DMA_COMP_PARAMS_3H_CH1_CTL_WB_EN_Pos (12UL)          /*!< CH1_CTL_WB_EN (Bit 12)                                */
#define DMAC_DMA_COMP_PARAMS_3H_CH1_CTL_WB_EN_Msk (0x1000UL)      /*!< CH1_CTL_WB_EN (Bitfield-Mask: 0x01)                   */
#define DMAC_DMA_COMP_PARAMS_3H_CH1_MULTI_BLK_EN_Pos (11UL)       /*!< CH1_MULTI_BLK_EN (Bit 11)                             */
#define DMAC_DMA_COMP_PARAMS_3H_CH1_MULTI_BLK_EN_Msk (0x800UL)    /*!< CH1_MULTI_BLK_EN (Bitfield-Mask: 0x01)                */
#define DMAC_DMA_COMP_PARAMS_3H_CH1_LOCK_EN_Pos (10UL)            /*!< CH1_LOCK_EN (Bit 10)                                  */
#define DMAC_DMA_COMP_PARAMS_3H_CH1_LOCK_EN_Msk (0x400UL)         /*!< CH1_LOCK_EN (Bitfield-Mask: 0x01)                     */
#define DMAC_DMA_COMP_PARAMS_3H_CH1_SRC_GAT_EN_Pos (9UL)          /*!< CH1_SRC_GAT_EN (Bit 9)                                */
#define DMAC_DMA_COMP_PARAMS_3H_CH1_SRC_GAT_EN_Msk (0x200UL)      /*!< CH1_SRC_GAT_EN (Bitfield-Mask: 0x01)                  */
#define DMAC_DMA_COMP_PARAMS_3H_CH1_DST_SCA_EN_Pos (8UL)          /*!< CH1_DST_SCA_EN (Bit 8)                                */
#define DMAC_DMA_COMP_PARAMS_3H_CH1_DST_SCA_EN_Msk (0x100UL)      /*!< CH1_DST_SCA_EN (Bitfield-Mask: 0x01)                  */
#define DMAC_DMA_COMP_PARAMS_3H_CH1_STAT_SRC_Pos (7UL)            /*!< CH1_STAT_SRC (Bit 7)                                  */
#define DMAC_DMA_COMP_PARAMS_3H_CH1_STAT_SRC_Msk (0x80UL)         /*!< CH1_STAT_SRC (Bitfield-Mask: 0x01)                    */
#define DMAC_DMA_COMP_PARAMS_3H_CH1_STAT_DST_Pos (6UL)            /*!< CH1_STAT_DST (Bit 6)                                  */
#define DMAC_DMA_COMP_PARAMS_3H_CH1_STAT_DST_Msk (0x40UL)         /*!< CH1_STAT_DST (Bitfield-Mask: 0x01)                    */
#define DMAC_DMA_COMP_PARAMS_3H_CH1_STW_Pos (3UL)                 /*!< CH1_STW (Bit 3)                                       */
#define DMAC_DMA_COMP_PARAMS_3H_CH1_STW_Msk (0x38UL)              /*!< CH1_STW (Bitfield-Mask: 0x07)                         */
#define DMAC_DMA_COMP_PARAMS_3H_CH1_DTW_Pos (0UL)                 /*!< CH1_DTW (Bit 0)                                       */
#define DMAC_DMA_COMP_PARAMS_3H_CH1_DTW_Msk (0x7UL)               /*!< CH1_DTW (Bitfield-Mask: 0x07)                         */
/* ==================================================  DMA_COMP_PARAMS_3L  =================================================== */
#define DMAC_DMA_COMP_PARAMS_3L_CH2_FIFO_DEPTH_Pos (28UL)         /*!< CH2_FIFO_DEPTH (Bit 28)                               */
#define DMAC_DMA_COMP_PARAMS_3L_CH2_FIFO_DEPTH_Msk (0x70000000UL) /*!< CH2_FIFO_DEPTH (Bitfield-Mask: 0x07)                  */
#define DMAC_DMA_COMP_PARAMS_3L_CH2_SMS_Pos (25UL)                /*!< CH2_SMS (Bit 25)                                      */
#define DMAC_DMA_COMP_PARAMS_3L_CH2_SMS_Msk (0xe000000UL)         /*!< CH2_SMS (Bitfield-Mask: 0x07)                         */
#define DMAC_DMA_COMP_PARAMS_3L_CH2_LMS_Pos (22UL)                /*!< CH2_LMS (Bit 22)                                      */
#define DMAC_DMA_COMP_PARAMS_3L_CH2_LMS_Msk (0x1c00000UL)         /*!< CH2_LMS (Bitfield-Mask: 0x07)                         */
#define DMAC_DMA_COMP_PARAMS_3L_CH2_DMS_Pos (19UL)                /*!< CH2_DMS (Bit 19)                                      */
#define DMAC_DMA_COMP_PARAMS_3L_CH2_DMS_Msk (0x380000UL)          /*!< CH2_DMS (Bitfield-Mask: 0x07)                         */
#define DMAC_DMA_COMP_PARAMS_3L_CH2_MAX_MULT_SIZE_Pos (16UL)      /*!< CH2_MAX_MULT_SIZE (Bit 16)                            */
#define DMAC_DMA_COMP_PARAMS_3L_CH2_MAX_MULT_SIZE_Msk (0x70000UL) /*!< CH2_MAX_MULT_SIZE (Bitfield-Mask: 0x07)               */
#define DMAC_DMA_COMP_PARAMS_3L_CH2_FC_Pos (14UL)                 /*!< CH2_FC (Bit 14)                                       */
#define DMAC_DMA_COMP_PARAMS_3L_CH2_FC_Msk (0x4000UL)             /*!< CH2_FC (Bitfield-Mask: 0x01)                          */
#define DMAC_DMA_COMP_PARAMS_3L_CH2_HC_LLP_Pos (13UL)             /*!< CH2_HC_LLP (Bit 13)                                   */
#define DMAC_DMA_COMP_PARAMS_3L_CH2_HC_LLP_Msk (0x2000UL)         /*!< CH2_HC_LLP (Bitfield-Mask: 0x01)                      */
#define DMAC_DMA_COMP_PARAMS_3L_CH2_CTL_WB_EN_Pos (12UL)          /*!< CH2_CTL_WB_EN (Bit 12)                                */
#define DMAC_DMA_COMP_PARAMS_3L_CH2_CTL_WB_EN_Msk (0x1000UL)      /*!< CH2_CTL_WB_EN (Bitfield-Mask: 0x01)                   */
#define DMAC_DMA_COMP_PARAMS_3L_CH2_MULTI_BLK_EN_Pos (11UL)       /*!< CH2_MULTI_BLK_EN (Bit 11)                             */
#define DMAC_DMA_COMP_PARAMS_3L_CH2_MULTI_BLK_EN_Msk (0x800UL)    /*!< CH2_MULTI_BLK_EN (Bitfield-Mask: 0x01)                */
#define DMAC_DMA_COMP_PARAMS_3L_CH2_LOCK_EN_Pos (10UL)            /*!< CH2_LOCK_EN (Bit 10)                                  */
#define DMAC_DMA_COMP_PARAMS_3L_CH2_LOCK_EN_Msk (0x400UL)         /*!< CH2_LOCK_EN (Bitfield-Mask: 0x01)                     */
#define DMAC_DMA_COMP_PARAMS_3L_CH2_SRC_GAT_EN_Pos (9UL)          /*!< CH2_SRC_GAT_EN (Bit 9)                                */
#define DMAC_DMA_COMP_PARAMS_3L_CH2_SRC_GAT_EN_Msk (0x200UL)      /*!< CH2_SRC_GAT_EN (Bitfield-Mask: 0x01)                  */
#define DMAC_DMA_COMP_PARAMS_3L_CH2_DST_SCA_EN_Pos (8UL)          /*!< CH2_DST_SCA_EN (Bit 8)                                */
#define DMAC_DMA_COMP_PARAMS_3L_CH2_DST_SCA_EN_Msk (0x100UL)      /*!< CH2_DST_SCA_EN (Bitfield-Mask: 0x01)                  */
#define DMAC_DMA_COMP_PARAMS_3L_CH2_STAT_SRC_Pos (7UL)            /*!< CH2_STAT_SRC (Bit 7)                                  */
#define DMAC_DMA_COMP_PARAMS_3L_CH2_STAT_SRC_Msk (0x80UL)         /*!< CH2_STAT_SRC (Bitfield-Mask: 0x01)                    */
#define DMAC_DMA_COMP_PARAMS_3L_CH2_STAT_DST_Pos (6UL)            /*!< CH2_STAT_DST (Bit 6)                                  */
#define DMAC_DMA_COMP_PARAMS_3L_CH2_STAT_DST_Msk (0x40UL)         /*!< CH2_STAT_DST (Bitfield-Mask: 0x01)                    */
#define DMAC_DMA_COMP_PARAMS_3L_CH2_STW_Pos (3UL)                 /*!< CH2_STW (Bit 3)                                       */
#define DMAC_DMA_COMP_PARAMS_3L_CH2_STW_Msk (0x38UL)              /*!< CH2_STW (Bitfield-Mask: 0x07)                         */
#define DMAC_DMA_COMP_PARAMS_3L_CH2_DTW_Pos (0UL)                 /*!< CH2_DTW (Bit 0)                                       */
#define DMAC_DMA_COMP_PARAMS_3L_CH2_DTW_Msk (0x7UL)               /*!< CH2_DTW (Bitfield-Mask: 0x07)                         */
/* ==================================================  DMA_COMP_PARAMS_2H  =================================================== */
#define DMAC_DMA_COMP_PARAMS_2H_CH7_MULTI_BLK_TYPE_Pos (28UL)         /*!< CH7_MULTI_BLK_TYPE (Bit 28)                           */
#define DMAC_DMA_COMP_PARAMS_2H_CH7_MULTI_BLK_TYPE_Msk (0xf0000000UL) /*!< CH7_MULTI_BLK_TYPE (Bitfield-Mask: 0x0f)            */
#define DMAC_DMA_COMP_PARAMS_2H_CH6_MULTI_BLK_TYPE_Pos (24UL)         /*!< CH6_MULTI_BLK_TYPE (Bit 24)                           */
#define DMAC_DMA_COMP_PARAMS_2H_CH6_MULTI_BLK_TYPE_Msk (0xf000000UL)  /*!< CH6_MULTI_BLK_TYPE (Bitfield-Mask: 0x0f)             */
#define DMAC_DMA_COMP_PARAMS_2H_CH5_MULTI_BLK_TYPE_Pos (20UL)         /*!< CH5_MULTI_BLK_TYPE (Bit 20)                           */
#define DMAC_DMA_COMP_PARAMS_2H_CH5_MULTI_BLK_TYPE_Msk (0xf00000UL)   /*!< CH5_MULTI_BLK_TYPE (Bitfield-Mask: 0x0f)              */
#define DMAC_DMA_COMP_PARAMS_2H_CH4_MULTI_BLK_TYPE_Pos (16UL)         /*!< CH4_MULTI_BLK_TYPE (Bit 16)                           */
#define DMAC_DMA_COMP_PARAMS_2H_CH4_MULTI_BLK_TYPE_Msk (0xf0000UL)    /*!< CH4_MULTI_BLK_TYPE (Bitfield-Mask: 0x0f)              */
#define DMAC_DMA_COMP_PARAMS_2H_CH3_MAX_MULT_SIZE_Pos (12UL)          /*!< CH3_MAX_MULT_SIZE (Bit 12)                            */
#define DMAC_DMA_COMP_PARAMS_2H_CH3_MAX_MULT_SIZE_Msk (0xf000UL)      /*!< CH3_MAX_MULT_SIZE (Bitfield-Mask: 0x0f)               */
#define DMAC_DMA_COMP_PARAMS_2H_CH2_MULTI_BLK_TYPE_Pos (8UL)          /*!< CH2_MULTI_BLK_TYPE (Bit 8)                            */
#define DMAC_DMA_COMP_PARAMS_2H_CH2_MULTI_BLK_TYPE_Msk (0xf00UL)      /*!< CH2_MULTI_BLK_TYPE (Bitfield-Mask: 0x0f)              */
#define DMAC_DMA_COMP_PARAMS_2H_CH1_MULTI_BLK_TYPE_Pos (4UL)          /*!< CH1_MULTI_BLK_TYPE (Bit 4)                            */
#define DMAC_DMA_COMP_PARAMS_2H_CH1_MULTI_BLK_TYPE_Msk (0xf0UL)       /*!< CH1_MULTI_BLK_TYPE (Bitfield-Mask: 0x0f)              */
#define DMAC_DMA_COMP_PARAMS_2H_CH0_MULTI_BLK_TYPE_Pos (0UL)          /*!< CH0_MULTI_BLK_TYPE (Bit 0)                            */
#define DMAC_DMA_COMP_PARAMS_2H_CH0_MULTI_BLK_TYPE_Msk (0xfUL)        /*!< CH0_MULTI_BLK_TYPE (Bitfield-Mask: 0x0f)              */
/* ==================================================  DMA_COMP_PARAMS_2L  =================================================== */
#define DMAC_DMA_COMP_PARAMS_2L_CH0_FIFO_DEPTH_Pos (28UL)         /*!< CH0_FIFO_DEPTH (Bit 28)                               */
#define DMAC_DMA_COMP_PARAMS_2L_CH0_FIFO_DEPTH_Msk (0x70000000UL) /*!< CH0_FIFO_DEPTH (Bitfield-Mask: 0x07)                  */
#define DMAC_DMA_COMP_PARAMS_2L_CH0_SMS_Pos (25UL)                /*!< CH0_SMS (Bit 25)                                      */
#define DMAC_DMA_COMP_PARAMS_2L_CH0_SMS_Msk (0xe000000UL)         /*!< CH0_SMS (Bitfield-Mask: 0x07)                         */
#define DMAC_DMA_COMP_PARAMS_2L_CH0_LMS_Pos (22UL)                /*!< CH0_LMS (Bit 22)                                      */
#define DMAC_DMA_COMP_PARAMS_2L_CH0_LMS_Msk (0x1c00000UL)         /*!< CH0_LMS (Bitfield-Mask: 0x07)                         */
#define DMAC_DMA_COMP_PARAMS_2L_CH0_DMS_Pos (19UL)                /*!< CH0_DMS (Bit 19)                                      */
#define DMAC_DMA_COMP_PARAMS_2L_CH0_DMS_Msk (0x380000UL)          /*!< CH0_DMS (Bitfield-Mask: 0x07)                         */
#define DMAC_DMA_COMP_PARAMS_2L_CH0_MAX_MULT_SIZE_Pos (16UL)      /*!< CH0_MAX_MULT_SIZE (Bit 16)                            */
#define DMAC_DMA_COMP_PARAMS_2L_CH0_MAX_MULT_SIZE_Msk (0x70000UL) /*!< CH0_MAX_MULT_SIZE (Bitfield-Mask: 0x07)               */
#define DMAC_DMA_COMP_PARAMS_2L_CH0_FC_Pos (14UL)                 /*!< CH0_FC (Bit 14)                                       */
#define DMAC_DMA_COMP_PARAMS_2L_CH0_FC_Msk (0xc000UL)             /*!< CH0_FC (Bitfield-Mask: 0x03)                          */
#define DMAC_DMA_COMP_PARAMS_2L_CH0_HC_LLP_Pos (13UL)             /*!< CH0_HC_LLP (Bit 13)                                   */
#define DMAC_DMA_COMP_PARAMS_2L_CH0_HC_LLP_Msk (0x2000UL)         /*!< CH0_HC_LLP (Bitfield-Mask: 0x01)                      */
#define DMAC_DMA_COMP_PARAMS_2L_CH0_CTL_WB_EN_Pos (12UL)          /*!< CH0_CTL_WB_EN (Bit 12)                                */
#define DMAC_DMA_COMP_PARAMS_2L_CH0_CTL_WB_EN_Msk (0x1000UL)      /*!< CH0_CTL_WB_EN (Bitfield-Mask: 0x01)                   */
#define DMAC_DMA_COMP_PARAMS_2L_CH0_MULTI_BLK_EN_Pos (11UL)       /*!< CH0_MULTI_BLK_EN (Bit 11)                             */
#define DMAC_DMA_COMP_PARAMS_2L_CH0_MULTI_BLK_EN_Msk (0x800UL)    /*!< CH0_MULTI_BLK_EN (Bitfield-Mask: 0x01)                */
#define DMAC_DMA_COMP_PARAMS_2L_CH0_LOCK_EN_Pos (10UL)            /*!< CH0_LOCK_EN (Bit 10)                                  */
#define DMAC_DMA_COMP_PARAMS_2L_CH0_LOCK_EN_Msk (0x400UL)         /*!< CH0_LOCK_EN (Bitfield-Mask: 0x01)                     */
#define DMAC_DMA_COMP_PARAMS_2L_CH0_SRC_GAT_EN_Pos (9UL)          /*!< CH0_SRC_GAT_EN (Bit 9)                                */
#define DMAC_DMA_COMP_PARAMS_2L_CH0_SRC_GAT_EN_Msk (0x200UL)      /*!< CH0_SRC_GAT_EN (Bitfield-Mask: 0x01)                  */
#define DMAC_DMA_COMP_PARAMS_2L_CH0_DST_SCA_EN_Pos (8UL)          /*!< CH0_DST_SCA_EN (Bit 8)                                */
#define DMAC_DMA_COMP_PARAMS_2L_CH0_DST_SCA_EN_Msk (0x100UL)      /*!< CH0_DST_SCA_EN (Bitfield-Mask: 0x01)                  */
#define DMAC_DMA_COMP_PARAMS_2L_CH0_STAT_SRC_Pos (7UL)            /*!< CH0_STAT_SRC (Bit 7)                                  */
#define DMAC_DMA_COMP_PARAMS_2L_CH0_STAT_SRC_Msk (0x80UL)         /*!< CH0_STAT_SRC (Bitfield-Mask: 0x01)                    */
#define DMAC_DMA_COMP_PARAMS_2L_CH0_STAT_DST_Pos (6UL)            /*!< CH0_STAT_DST (Bit 6)                                  */
#define DMAC_DMA_COMP_PARAMS_2L_CH0_STAT_DST_Msk (0x40UL)         /*!< CH0_STAT_DST (Bitfield-Mask: 0x01)                    */
#define DMAC_DMA_COMP_PARAMS_2L_CH0_STW_Pos (3UL)                 /*!< CH0_STW (Bit 3)                                       */
#define DMAC_DMA_COMP_PARAMS_2L_CH0_STW_Msk (0x38UL)              /*!< CH0_STW (Bitfield-Mask: 0x07)                         */
#define DMAC_DMA_COMP_PARAMS_2L_CH0_DTW_Pos (0UL)                 /*!< CH0_DTW (Bit 0)                                       */
#define DMAC_DMA_COMP_PARAMS_2L_CH0_DTW_Msk (0x7UL)               /*!< CH0_DTW (Bitfield-Mask: 0x07)                         */
/* ==================================================  DMA_COMP_PARAMS_1H  =================================================== */
#define DMAC_DMA_COMP_PARAMS_1H_STATIC_ENDIAN_SELECT_Pos (29UL)         /*!< STATIC_ENDIAN_SELECT (Bit 29)                         */
#define DMAC_DMA_COMP_PARAMS_1H_STATIC_ENDIAN_SELECT_Msk (0x20000000UL) /*!< STATIC_ENDIAN_SELECT (Bitfield-Mask: 0x01)        */
#define DMAC_DMA_COMP_PARAMS_1H_ADD_ENCODED_PARAMS_Pos (28UL)           /*!< ADD_ENCODED_PARAMS (Bit 28)                           */
#define DMAC_DMA_COMP_PARAMS_1H_ADD_ENCODED_PARAMS_Msk (0x10000000UL)   /*!< ADD_ENCODED_PARAMS (Bitfield-Mask: 0x01)            */
#define DMAC_DMA_COMP_PARAMS_1H_NUM_HS_INT_Pos (23UL)                   /*!< NUM_HS_INT (Bit 23)                                   */
#define DMAC_DMA_COMP_PARAMS_1H_NUM_HS_INT_Msk (0xf800000UL)            /*!< NUM_HS_INT (Bitfield-Mask: 0x1f)                      */
#define DMAC_DMA_COMP_PARAMS_1H_M1_HDATA_WIDTH_Pos (21UL)               /*!< M1_HDATA_WIDTH (Bit 21)                               */
#define DMAC_DMA_COMP_PARAMS_1H_M1_HDATA_WIDTH_Msk (0x600000UL)         /*!< M1_HDATA_WIDTH (Bitfield-Mask: 0x03)                  */
#define DMAC_DMA_COMP_PARAMS_1H_M2_HDATA_WIDTH_Pos (19UL)               /*!< M2_HDATA_WIDTH (Bit 19)                               */
#define DMAC_DMA_COMP_PARAMS_1H_M2_HDATA_WIDTH_Msk (0x180000UL)         /*!< M2_HDATA_WIDTH (Bitfield-Mask: 0x03)                  */
#define DMAC_DMA_COMP_PARAMS_1H_M3_HDATA_WIDTH_Pos (17UL)               /*!< M3_HDATA_WIDTH (Bit 17)                               */
#define DMAC_DMA_COMP_PARAMS_1H_M3_HDATA_WIDTH_Msk (0x60000UL)          /*!< M3_HDATA_WIDTH (Bitfield-Mask: 0x03)                  */
#define DMAC_DMA_COMP_PARAMS_1H_M4_HDATA_WIDTH_Pos (15UL)               /*!< M4_HDATA_WIDTH (Bit 15)                               */
#define DMAC_DMA_COMP_PARAMS_1H_M4_HDATA_WIDTH_Msk (0x18000UL)          /*!< M4_HDATA_WIDTH (Bitfield-Mask: 0x03)                  */
#define DMAC_DMA_COMP_PARAMS_1H_S_HDATA_WIDTH_Pos (13UL)                /*!< S_HDATA_WIDTH (Bit 13)                                */
#define DMAC_DMA_COMP_PARAMS_1H_S_HDATA_WIDTH_Msk (0x6000UL)            /*!< S_HDATA_WIDTH (Bitfield-Mask: 0x03)                   */
#define DMAC_DMA_COMP_PARAMS_1H_NUM_MASTER_INT_Pos (11UL)               /*!< NUM_MASTER_INT (Bit 11)                               */
#define DMAC_DMA_COMP_PARAMS_1H_NUM_MASTER_INT_Msk (0x800UL)            /*!< NUM_MASTER_INT (Bitfield-Mask: 0x01)                  */
#define DMAC_DMA_COMP_PARAMS_1H_NUM_CHANNELS_Pos (8UL)                  /*!< NUM_CHANNELS (Bit 8)                                  */
#define DMAC_DMA_COMP_PARAMS_1H_NUM_CHANNELS_Msk (0x300UL)              /*!< NUM_CHANNELS (Bitfield-Mask: 0x03)                    */
#define DMAC_DMA_COMP_PARAMS_1H_MABRST_Pos (3UL)                        /*!< MABRST (Bit 3)                                        */
#define DMAC_DMA_COMP_PARAMS_1H_MABRST_Msk (0x8UL)                      /*!< MABRST (Bitfield-Mask: 0x01)                          */
#define DMAC_DMA_COMP_PARAMS_1H_INTR_IO_Pos (1UL)                       /*!< INTR_IO (Bit 1)                                       */
#define DMAC_DMA_COMP_PARAMS_1H_INTR_IO_Msk (0x6UL)                     /*!< INTR_IO (Bitfield-Mask: 0x03)                         */
#define DMAC_DMA_COMP_PARAMS_1H_BIG_ENDIAN_Pos (0UL)                    /*!< BIG_ENDIAN (Bit 0)                                    */
#define DMAC_DMA_COMP_PARAMS_1H_BIG_ENDIAN_Msk (0x1UL)                  /*!< BIG_ENDIAN (Bitfield-Mask: 0x01)                      */
/* ==================================================  DMA_COMP_PARAMS_1L  =================================================== */
#define DMAC_DMA_COMP_PARAMS_1L_CH7_MAX_BLK_SIZE_Pos (28UL)         /*!< CH7_MAX_BLK_SIZE (Bit 28)                             */
#define DMAC_DMA_COMP_PARAMS_1L_CH7_MAX_BLK_SIZE_Msk (0xf0000000UL) /*!< CH7_MAX_BLK_SIZE (Bitfield-Mask: 0x0f)                */
#define DMAC_DMA_COMP_PARAMS_1L_CH6_MAX_BLK_SIZE_Pos (24UL)         /*!< CH6_MAX_BLK_SIZE (Bit 24)                             */
#define DMAC_DMA_COMP_PARAMS_1L_CH6_MAX_BLK_SIZE_Msk (0xf000000UL)  /*!< CH6_MAX_BLK_SIZE (Bitfield-Mask: 0x0f)                */
#define DMAC_DMA_COMP_PARAMS_1L_CH5_MAX_BLK_SIZE_Pos (20UL)         /*!< CH5_MAX_BLK_SIZE (Bit 20)                             */
#define DMAC_DMA_COMP_PARAMS_1L_CH5_MAX_BLK_SIZE_Msk (0xf00000UL)   /*!< CH5_MAX_BLK_SIZE (Bitfield-Mask: 0x0f)                */
#define DMAC_DMA_COMP_PARAMS_1L_CH4_MAX_BLK_SIZE_Pos (16UL)         /*!< CH4_MAX_BLK_SIZE (Bit 16)                             */
#define DMAC_DMA_COMP_PARAMS_1L_CH4_MAX_BLK_SIZE_Msk (0xf0000UL)    /*!< CH4_MAX_BLK_SIZE (Bitfield-Mask: 0x0f)                */
#define DMAC_DMA_COMP_PARAMS_1L_CH3_MAX_BLK_SIZE_Pos (12UL)         /*!< CH3_MAX_BLK_SIZE (Bit 12)                             */
#define DMAC_DMA_COMP_PARAMS_1L_CH3_MAX_BLK_SIZE_Msk (0xf000UL)     /*!< CH3_MAX_BLK_SIZE (Bitfield-Mask: 0x0f)                */
#define DMAC_DMA_COMP_PARAMS_1L_CH2_MAX_BLK_SIZE_Pos (8UL)          /*!< CH2_MAX_BLK_SIZE (Bit 8)                              */
#define DMAC_DMA_COMP_PARAMS_1L_CH2_MAX_BLK_SIZE_Msk (0xf00UL)      /*!< CH2_MAX_BLK_SIZE (Bitfield-Mask: 0x0f)                */
#define DMAC_DMA_COMP_PARAMS_1L_CH1_MAX_BLK_SIZE_Pos (4UL)          /*!< CH1_MAX_BLK_SIZE (Bit 4)                              */
#define DMAC_DMA_COMP_PARAMS_1L_CH1_MAX_BLK_SIZE_Msk (0xf0UL)       /*!< CH1_MAX_BLK_SIZE (Bitfield-Mask: 0x0f)                */
#define DMAC_DMA_COMP_PARAMS_1L_CH0_MAX_BLK_SIZE_Pos (0UL)          /*!< CH0_MAX_BLK_SIZE (Bit 0)                              */
#define DMAC_DMA_COMP_PARAMS_1L_CH0_MAX_BLK_SIZE_Msk (0xfUL)        /*!< CH0_MAX_BLK_SIZE (Bitfield-Mask: 0x0f)                */
/* ==================================================  DMA_COMP_ID_VERSION  ================================================== */
#define DMAC_DMA_COMP_ID_VERSION_DMA_COMP_VERSION_Pos (0UL)          /*!< DMA_COMP_VERSION (Bit 0)                              */
#define DMAC_DMA_COMP_ID_VERSION_DMA_COMP_VERSION_Msk (0xffffffffUL) /*!< DMA_COMP_VERSION (Bitfield-Mask: 0xffffffff)         */
/* ===================================================  DMA_COMP_ID_TYPE  ==================================================== */
#define DMAC_DMA_COMP_ID_TYPE_DMA_COMP_TYPE_Pos (0UL)          /*!< DMA_COMP_TYPE (Bit 0)                                 */
#define DMAC_DMA_COMP_ID_TYPE_DMA_COMP_TYPE_Msk (0xffffffffUL) /*!< DMA_COMP_TYPE (Bitfield-Mask: 0xffffffff)             */
  /**
   * @}
   */

  /* Exported macro ------------------------------------------------------------*/
  /* Exported functions ------------------------------------------------------- */

  /* Function used to set the DMA configuration to the default reset state ******/
  void DMA_DeInit(DMA_Channel_TypeDef *DMAy_Channelx);

  /* Initialization and Configuration functions *********************************/
  void DMA_Init(DMA_Channel_TypeDef *DMAy_Channelx, DMA_InitTypeDef *DMA_InitStruct);
  void DMA_StructInit(DMA_InitTypeDef *DMA_InitStruct);
  void DMA_Cmd(DMA_Channel_TypeDef *DMAy_Channelx, FunctionalState NewState);
  void DMA_RemapConfig(DMA_Channel_TypeDef *DMAy_Channelx, uint32_t req_num, uint32_t DMA_Request);

  /* Data Counter functions******************************************************/
  void DMA_SetCurrDataCounter(DMA_Channel_TypeDef *DMAy_Channelx, uint16_t DataNumber);
  uint16_t DMA_GetCurrDataCounter(DMA_Channel_TypeDef *DMAy_Channelx);

  /* Interrupts and flags management functions **********************************/
  void DMA_ITConfig(DMA_Channel_TypeDef *DMAy_Channelx, uint32_t DMA_IT, FunctionalState NewState);
  FlagStatus DMA_GetFlagStatus(uint32_t DMAy_FLAG);
  void DMA_ClearFlag(uint32_t DMAy_FLAG);
  ITStatus DMA_GetITStatus(uint32_t DMAy_IT);
  void DMA_ClearITPendingBit(uint32_t DMAy_IT);

#ifdef __cplusplus
}
#endif

#endif /*__LCM32F037_DMA_H */

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT LCMicroelectronics *****END OF FILE****/
