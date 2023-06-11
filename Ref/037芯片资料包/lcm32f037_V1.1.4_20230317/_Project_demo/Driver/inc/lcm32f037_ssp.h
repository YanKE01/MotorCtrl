#ifndef LCM32F037_SSP_H
#define LCM32F037_SSP_H
#include "stdint.h"
#include "lcm32f037.h"

typedef struct
{
  uint16_t SPI_Mode; /*!< Specifies the SPI mode (Master/Slave).
                                         This parameter can be a value of @ref SPI_mode */

  uint16_t SPI_DataSize; /*!< Specifies the SPI data size.
                                         This parameter can be a value of @ref SPI_data_size */

  uint16_t SPI_CPOL; /*!< Specifies the serial clock steady state.
                                         This parameter can be a value of @ref SPI_Clock_Polarity */

  uint16_t SPI_CPHA; /*!< Specifies the clock active edge for the bit capture.
                                         This parameter can be a value of @ref SPI_Clock_Phase */

  uint16_t SPI_BaudRatePrescaler; /*!< Specifies the Baud Rate prescaler value which will be
                                         used to configure the transmit and receive SCK clock.
                                         This parameter can be a value of @ref SPI_BaudRate_Prescaler
                                         @note The communication clock is derived from the master
                                               clock. The slave clock does not need to be set. */

  uint16_t SPI_FirstBit; /*!< Specifies whether data transfers start from MSB or LSB bit.
                                         This parameter can be a value of @ref SPI_MSB_LSB_transmission */
  uint16_t SPI_SlaveTx;  /* < Specifies whether spi transmite data when as spi_slave mode. */

} SPI_InitTypeDef;

#define IS_SPI_ALL_PERIPH(PERIPH) (((ERIPH) == SPI0) || ((ERIPH) == SPI2))

#define IS_SPI_0_2_PERIPH(PERIPH) (((PERIPH) == SPI0)||((PERIPH) == SPI2))

/** @defgroup SPI_mode
 * @{
 */

#define SPI_Mode_Master ((uint16_t)0x0000)
#define SPI_Mode_Slave ((uint16_t)0x0004)
#define IS_SPI_MODE(MODE) (((MODE) == SPI_Mode_Master) || \
                           ((MODE) == SPI_Mode_Slave))
/**
 * @}
 */

/**
 * @{bit definations
 */
#define SSP_CR1_SSE ((uint16_t)0x0002)

#define SSP_CR0_FRF_MT ((uint16_t)0x0000)
#define SSP_CR0_FRF_TI ((uint16_t)0x0010)
#define SSP_CR0_FRF_NM ((uint16_t)0x0020)

#define SSPCR0_FRF_SPI ((uint16_t)0x0030)
/**
 * @}
 */
/** @defgroup SPI_data_size
 * @{
 */

#define SPI_DataSize_4b ((uint16_t)0x03)
#define SPI_DataSize_5b ((uint16_t)0x04)
#define SPI_DataSize_6b ((uint16_t)0x05)
#define SPI_DataSize_7b ((uint16_t)0x06)
#define SPI_DataSize_8b ((uint16_t)0x07)
#define SPI_DataSize_9b ((uint16_t)0x08)
#define SPI_DataSize_10b ((uint16_t)0x09)
#define SPI_DataSize_11b ((uint16_t)0x0A)
#define SPI_DataSize_12b ((uint16_t)0x0B)
#define SPI_DataSize_13b ((uint16_t)0x0C)
#define SPI_DataSize_14b ((uint16_t)0x0D)
#define SPI_DataSize_15b ((uint16_t)0x0E)
#define SPI_DataSize_16b ((uint16_t)0x0F)
#define IS_SPI_DATA_SIZE(SIZE) (((SIZE) == SPI_DataSize_4b) ||  \
                                ((SIZE) == SPI_DataSize_5b) ||  \
                                ((SIZE) == SPI_DataSize_6b) ||  \
                                ((SIZE) == SPI_DataSize_7b) ||  \
                                ((SIZE) == SPI_DataSize_8b) ||  \
                                ((SIZE) == SPI_DataSize_9b) ||  \
                                ((SIZE) == SPI_DataSize_10b) || \
                                ((SIZE) == SPI_DataSize_11b) || \
                                ((SIZE) == SPI_DataSize_12b) || \
                                ((SIZE) == SPI_DataSize_13b) || \
                                ((SIZE) == SPI_DataSize_14b) || \
                                ((SIZE) == SPI_DataSize_15b) || \
                                ((SIZE) == SPI_DataSize_16b))
/**
 * @}
 */

/** @defgroup SPI_Clock_Polarity
 * @{
 */

#define SPI_CPOL_Low ((uint16_t)0x0000)
#define SPI_CPOL_High ((uint16_t)0x0040)
#define IS_SPI_CPOL(CPOL) (((CPOL) == SPI_CPOL_Low) || \
                           ((CPOL) == SPI_CPOL_High))
/**
 * @}
 */

/** @defgroup SPI_Clock_Phase
 * @{
 */

#define SPI_CPHA_1Edge ((uint16_t)0x0000)
#define SPI_CPHA_2Edge ((uint16_t)0x0080)
#define IS_SPI_CPHA(CPHA) (((CPHA) == SPI_CPHA_1Edge) || \
                           ((CPHA) == SPI_CPHA_2Edge))
/**
 * @}
 */

/** @defgroup SPI_BaudRate_Prescaler
 * @{
 */

#define SPI_BaudRatePrescaler_2 ((uint16_t)0x0000)
#define SPI_BaudRatePrescaler_4 ((uint16_t)0x0100)
#define SPI_BaudRatePrescaler_8 ((uint16_t)0x0300)
#define SPI_BaudRatePrescaler_16        ((uint16_t)0x0700
#define SPI_BaudRatePrescaler_32 ((uint16_t)0x0F00)
#define SPI_BaudRatePrescaler_64 ((uint16_t)0x1F00)
#define SPI_BaudRatePrescaler_128 ((uint16_t)0x3F00)
#define SPI_BaudRatePrescaler_256 ((uint16_t)0x7F00)
#define IS_SPI_BAUDRATE_PRESCALER(PRESCALER) (((PRESCALER) == SPI_BaudRatePrescaler_2) ||   \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_4) ||   \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_8) ||   \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_16) ||  \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_32) ||  \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_64) ||  \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_128) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_256))
/**
 * @}
 */

/** @defgroup SPI_MSB_LSB_transmission
 * @{  LCM32F003 ONLY  MSB
 */

#define SPI_FirstBit_MSB ((uint16_t)0x0000)
#define SPI_FirstBit_LSB ((uint16_t)0x0000)
#define IS_SPI_FIRST_BIT(BIT) (((BIT) == SPI_FirstBit_MSB) || \
                               ((BIT) == SPI_FirstBit_LSB))
/**
 * @}
 */
/** @defgroup SPI_SlaveTx
 * @{
 */
#define SPI_SlaveTx_Enable ((uint16_t)0x0000)
#define SPI_SlaveTx_Disable ((uint16_t)0x0008)
#define IS_SPI_SLAVE_TX(STATUS) (((STATUS) == SPI_SlaveTx_Enable) || \
                                 ((STATUS) == SPI_SlaveTx_Disable))
/**
 * @}
 */
/** @defgroup SPI_I2S_DMA_transfer_requests
 * @{
 */
#define SPI_DMAReq_Tx ((uint16_t)0x0002)
#define SPI_DMAReq_Rx ((uint16_t)0x0001)
#define IS_SPI_DMA_REQ(REQ) ((REQ == SPI_DMAReq_Tx) || (REQ == SPI_DMAReq_Rx))
/**
 * @}
 */

/** @defgroup SPI_I2S_interrupts_definition
 * @{
 */

#define SPI_IT_Tx ((uint16_t)0x0008)
#define SPI_IT_Rx ((uint16_t)0x0004)
#define SPI_IT_RT ((uint16_t)0x0002)
#define SPI_IT_ROR ((uint16_t)0x0001)
#define SPI_IT_ALL ((uint16_t)0x00FF)
#define IS_SPI_CONFIG_IT(IT) (((IT) == SPI_IT_Tx) ||  \
                              ((IT) == SPI_IT_Rx) ||  \
                              ((IT) == SPI_IT_RT) ||  \
                              ((IT) == SPI_IT_ROR) || \
                              ((IT) == SPI_IT_ALL))
/**
 * @}
 */

/** @defgroup SPI_flags_definition
 * @{
 */

#define SPI_FLAG_BSY ((uint16_t)0x0010)
#define SPI_FLAG_RFF ((uint16_t)0x0008)
#define SPI_FLAG_RNE ((uint16_t)0x0004)
#define SPI_FLAG_TNF ((uint16_t)0x0002)
#define SPI_FLAG_TFE ((uint16_t)0x0001)
#define SPI_ERROR_FLAG_RT ((uint16_t)0x0002)
#define SPI_ERROR_FLAF_ROR ((uint16_t)0x0001)

#define IS_SPI_CLEAR_FLAG(ERROR_FLAG) (((ERROR_FLAG) == SPI_FLAG_CRCERR) || ((ERROR_FLAG) == SPI_ERROR_FLAF_ROR))
#define IS_SPI_GET_FLAG(FLAG) (((FLAG) == SPI_FLAG_BSY) || ((FLAG) == SPI_FLAG_RFF) || \
                               ((FLAG) == SPI_FLAG_RNE) || ((FLAG) == SPI_FLAG_TNF) || \
                               ((FLAG) == SPI_FLAG_TFE))
/**
 * @}
 */

/* =========================================================================================================================== */
/* ================                                            SPI                                            ================ */
/* =========================================================================================================================== */

/* ========================================================  SSPCR0  ========================================================= */
#define SPI_SSPCR0_SCR_Pos (8UL)      /*!< SCR (Bit 8)                                           */
#define SPI_SSPCR0_SCR_Msk (0xff00UL) /*!< SCR (Bitfield-Mask: 0xff)                             */
#define SPI_SSPCR0_SPH_Pos (7UL)      /*!< SPH (Bit 7)                                           */
#define SPI_SSPCR0_SPH_Msk (0x80UL)   /*!< SPH (Bitfield-Mask: 0x01)                             */
#define SPI_SSPCR0_SPO_Pos (6UL)      /*!< SPO (Bit 6)                                           */
#define SPI_SSPCR0_SPO_Msk (0x40UL)   /*!< SPO (Bitfield-Mask: 0x01)                             */
#define SPI_SSPCR0_FRF_Pos (4UL)      /*!< FRF (Bit 4)                                           */
#define SPI_SSPCR0_FRF_Msk (0x30UL)   /*!< FRF (Bitfield-Mask: 0x03)                             */
#define SPI_SSPCR0_DSS_Pos (0UL)      /*!< DSS (Bit 0)                                           */
#define SPI_SSPCR0_DSS_Msk (0xfUL)    /*!< DSS (Bitfield-Mask: 0x0f)                             */
/* ========================================================  SSPCR1  ========================================================= */
#define SPI_SSPCR1_SOD_Pos (3UL)   /*!< SOD (Bit 3)                                           */
#define SPI_SSPCR1_SOD_Msk (0x8UL) /*!< SOD (Bitfield-Mask: 0x01)                             */
#define SPI_SSPCR1_MS_Pos (2UL)    /*!< MS (Bit 2)                                            */
#define SPI_SSPCR1_MS_Msk (0x4UL)  /*!< MS (Bitfield-Mask: 0x01)                              */
#define SPI_SSPCR1_SSE_Pos (1UL)   /*!< SSE (Bit 1)                                           */
#define SPI_SSPCR1_SSE_Msk (0x2UL) /*!< SSE (Bitfield-Mask: 0x01)                             */
#define SPI_SSPCR1_LBM_Pos (0UL)   /*!< LBM (Bit 0)                                           */
#define SPI_SSPCR1_LBM_Msk (0x1UL) /*!< LBM (Bitfield-Mask: 0x01)                             */
/* =========================================================  SSPDR  ========================================================= */
#define SPI_SSPDR_DATA_Pos (0UL)      /*!< DATA (Bit 0)                                          */
#define SPI_SSPDR_DATA_Msk (0xffffUL) /*!< DATA (Bitfield-Mask: 0xffff)                          */
/* =========================================================  SSPSR  ========================================================= */
#define SPI_SSPSR_BSY_Pos (4UL)    /*!< BSY (Bit 4)                                           */
#define SPI_SSPSR_BSY_Msk (0x10UL) /*!< BSY (Bitfield-Mask: 0x01)                             */
#define SPI_SSPSR_RFF_Pos (3UL)    /*!< RFF (Bit 3)                                           */
#define SPI_SSPSR_RFF_Msk (0x8UL)  /*!< RFF (Bitfield-Mask: 0x01)                             */
#define SPI_SSPSR_RNE_Pos (2UL)    /*!< RNE (Bit 2)                                           */
#define SPI_SSPSR_RNE_Msk (0x4UL)  /*!< RNE (Bitfield-Mask: 0x01)                             */
#define SPI_SSPSR_TNF_Pos (1UL)    /*!< TNF (Bit 1)                                           */
#define SPI_SSPSR_TNF_Msk (0x2UL)  /*!< TNF (Bitfield-Mask: 0x01)                             */
#define SPI_SSPSR_TFE_Pos (0UL)    /*!< TFE (Bit 0)                                           */
#define SPI_SSPSR_TFE_Msk (0x1UL)  /*!< TFE (Bitfield-Mask: 0x01)                             */
/* ========================================================  SSPCPSR  ======================================================== */
#define SPI_SSPCPSR_CPSDVSR_Pos (0UL)    /*!< CPSDVSR (Bit 0)                                       */
#define SPI_SSPCPSR_CPSDVSR_Msk (0xffUL) /*!< CPSDVSR (Bitfield-Mask: 0xff)                         */
/* ========================================================  SSPIMSC  ======================================================== */
#define SPI_SSPIMSC_TXIM_Pos (3UL)    /*!< TXIM (Bit 3)                                          */
#define SPI_SSPIMSC_TXIM_Msk (0x8UL)  /*!< TXIM (Bitfield-Mask: 0x01)                            */
#define SPI_SSPIMSC_RXIM_Pos (2UL)    /*!< RXIM (Bit 2)                                          */
#define SPI_SSPIMSC_RXIM_Msk (0x4UL)  /*!< RXIM (Bitfield-Mask: 0x01)                            */
#define SPI_SSPIMSC_RTIM_Pos (1UL)    /*!< RTIM (Bit 1)                                          */
#define SPI_SSPIMSC_RTIM_Msk (0x2UL)  /*!< RTIM (Bitfield-Mask: 0x01)                            */
#define SPI_SSPIMSC_RORIM_Pos (0UL)   /*!< RORIM (Bit 0)                                         */
#define SPI_SSPIMSC_RORIM_Msk (0x1UL) /*!< RORIM (Bitfield-Mask: 0x01)                           */
/* ========================================================  SSPRIS  ========================================================= */
#define SPI_SSPRIS_TXRIS_Pos (3UL)    /*!< TXRIS (Bit 3)                                         */
#define SPI_SSPRIS_TXRIS_Msk (0x8UL)  /*!< TXRIS (Bitfield-Mask: 0x01)                           */
#define SPI_SSPRIS_RXRIS_Pos (2UL)    /*!< RXRIS (Bit 2)                                         */
#define SPI_SSPRIS_RXRIS_Msk (0x4UL)  /*!< RXRIS (Bitfield-Mask: 0x01)                           */
#define SPI_SSPRIS_RTRIS_Pos (1UL)    /*!< RTRIS (Bit 1)                                         */
#define SPI_SSPRIS_RTRIS_Msk (0x2UL)  /*!< RTRIS (Bitfield-Mask: 0x01)                           */
#define SPI_SSPRIS_RORRIS_Pos (0UL)   /*!< RORRIS (Bit 0)                                        */
#define SPI_SSPRIS_RORRIS_Msk (0x1UL) /*!< RORRIS (Bitfield-Mask: 0x01)                          */
/* ========================================================  SSPMIS  ========================================================= */
#define SPI_SSPMIS_TXMIS_Pos (3UL)    /*!< TXMIS (Bit 3)                                         */
#define SPI_SSPMIS_TXMIS_Msk (0x8UL)  /*!< TXMIS (Bitfield-Mask: 0x01)                           */
#define SPI_SSPMIS_RXMIS_Pos (2UL)    /*!< RXMIS (Bit 2)                                         */
#define SPI_SSPMIS_RXMIS_Msk (0x4UL)  /*!< RXMIS (Bitfield-Mask: 0x01)                           */
#define SPI_SSPMIS_RTMIS_Pos (1UL)    /*!< RTMIS (Bit 1)                                         */
#define SPI_SSPMIS_RTMIS_Msk (0x2UL)  /*!< RTMIS (Bitfield-Mask: 0x01)                           */
#define SPI_SSPMIS_RORMIS_Pos (0UL)   /*!< RORMIS (Bit 0)                                        */
#define SPI_SSPMIS_RORMIS_Msk (0x1UL) /*!< RORMIS (Bitfield-Mask: 0x01)                          */
/* ========================================================  SSPICR  ========================================================= */
#define SPI_SSPICR_RTIC_Pos (1UL)    /*!< RTIC (Bit 1)                                          */
#define SPI_SSPICR_RTIC_Msk (0x2UL)  /*!< RTIC (Bitfield-Mask: 0x01)                            */
#define SPI_SSPICR_RORIC_Pos (0UL)   /*!< RORIC (Bit 0)                                         */
#define SPI_SSPICR_RORIC_Msk (0x1UL) /*!< RORIC (Bitfield-Mask: 0x01)                           */
/* =======================================================  SSPDMACR  ======================================================== */
#define SPI_SSPDMACR_TXDMAE_Pos (1UL)   /*!< TXDMAE (Bit 1)                                        */
#define SPI_SSPDMACR_TXDMAE_Msk (0x2UL) /*!< TXDMAE (Bitfield-Mask: 0x01)                          */
#define SPI_SSPDMACR_RXDMAE_Pos (0UL)   /*!< RXDMAE (Bit 0)                                        */
#define SPI_SSPDMACR_RXDMAE_Msk (0x1UL) /*!< RXDMAE (Bitfield-Mask: 0x01)                          */

void SPI_DeInit(SPI_TypeDef *SPIx);
void SPI_StructInit(SPI_InitTypeDef *SPI_InitStruct);
void SPI_Init(SPI_TypeDef *SPIx, SPI_InitTypeDef *SPI_InitStruct);
void SPI_Cmd(SPI_TypeDef *SPIx, FunctionalState NewState);
void SPI_TIModeCmd(SPI_TypeDef *SPIx, FunctionalState NewState);
void SPI_NMModeCmd(SPI_TypeDef *SPIx, FunctionalState NewState);
void SPI_DataSizeConfig(SPI_TypeDef *SPIx, uint16_t SPI_DataSize);
void SPI_SendData8(SPI_TypeDef *SPIx, uint8_t Data);
void SPI_SendData16(SPI_TypeDef *SPIx, uint16_t Data);
uint8_t SPI_ReceiveData8(SPI_TypeDef *SPIx);
uint16_t SPI_ReceiveData16(SPI_TypeDef *SPIx);
void SPI_DMACmd(SPI_TypeDef *SPIx, uint16_t SPI_DMAReq, FunctionalState NewState);
void SPI_ITConfig(SPI_TypeDef *SPIx, uint8_t SPI_IT, FunctionalState NewState);
FlagStatus SPI_GetFlagStatus(SPI_TypeDef *SPIx, uint16_t SPI_FLAG);
void SPI_ClearFlag(SPI_TypeDef *SPIx, uint16_t SPI_ERROR_FLAG);
ITStatus SPI_GetITStatus(SPI_TypeDef *SPIx, uint8_t SPI_IT);
ITStatus SPI_GetITRawStatus(SPI_TypeDef *SPIx, uint8_t SPI_IT);
#endif
