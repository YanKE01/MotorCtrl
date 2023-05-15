#ifndef LCM32F037_UART_H
#define LCM32F037_UART_H
#include "lcm32f037.h"
#include <stdint.h>
/******************** UART Regist Struct Definition *********************/

typedef struct
{
  uint32_t UART_BaudRate;
  uint32_t UART_WordLength;
  uint32_t UART_StopBits;
  uint32_t UART_Parity;
  uint32_t UART_Mode;
  uint32_t UART_HardwareFlowControl;
} UART_InitTypeDef;

/**
  *@{UART_WordLength
  */
#define UART_WordLength_5b ((uint32_t)0x00000000)
#define UART_WordLength_6b ((uint32_t)0x00000020)
#define UART_WordLength_7b ((uint32_t)0x00000040)
#define UART_WordLength_8b ((uint32_t)0x00000060)

/**
  @}
  */
/**
  *@{UART_StopBits
  */
#define UART_StopBits_1 ((uint32_t)0x00000000)
#define UART_StopBits_2 ((uint32_t)0x00000008)
/**
  *@}
  */
/**
  *@{UART_Parity
  */
#define UART_Parity_No ((uint32_t)0x00)
#define UART_Parity_Even ((uint32_t)0x06)
#define UART_Parity_Odd ((uint32_t)0x02)
#define UART_Parity_One ((uint32_t)0x82)
#define UART_Parity_Zero ((uint32_t)0x86)
/**
  *@}
  */
/**
  *@{UART_Mode
  */
#define UART_Mode_Rx ((uint32_t)0x200)
#define UART_Mode_Tx ((uint32_t)0x100)
/**
  *@}
  */
/**
  *@{UART_HardwareFlowControl
  */
#define UART_HardwareFlowControl_None ((uint32_t)0x0000)
#define UART_HardwareFlowControl_RTS ((uint32_t)0x4000)
#define UART_HardwareFlowControl_CTS ((uint32_t)0x8000)
#define UART_HardwareFlowControl_RTS_CTS ((uint32_t)0xC000)
/**
  *@}
  */
/**
  *@{UART_DMAReq
  */
#define UART_DMAReq_Tx ((uint32_t)0x0002)
#define UART_DMAReq_Rx ((uint32_t)0x0001)
/**
  *@}
  */
/**
  *@{UART_DirectionMode
  */
#define UART_Direction_Tx (UARTCR_TXE_ON)
#define UART_Direction_Rx (UARTCR_RXE_ON)
#define IS_UART_DIRECTION(UART_DirectionMode) ((UART_DirectionMode == UART_Direction_Tx) || \
                                               (UART_DirectionMode == UART_Direction_Rx))
/**
  *@}
  */
/**
  *@{UART_FIFOSelect
  */
#define UART_FIFOSelect_Rx ((uint32_t)0x03)
#define UART_FIFOSelect_Tx ((uint32_t)0x00)
#define IS_UART_FIFO_SELECT(FIFOSelect) ((FIFOSelect == UART_FIFOSelect_Rx) || \
                                         (FIFOSelect == UART_FIFOSelect_Tx))
/**
  *@}
  */
/**
  *@{UART_FIFO_LEAVEL
  */
#define UART_RXIFLSEL_LEAVEL_1_8 (0x0UL << 3)
#define UART_RXIFLSEL_LEAVEL_1_4 (0x1UL << 3)
#define UART_RXIFLSEL_LEAVEL_1_2 (0x2UL << 3)
#define UART_RXIFLSEL_LEAVEL_3_4 (0x3UL << 3)
#define UART_RXIFLSEL_LEAVEL_7_8 (0x4UL << 3)
#define IS_UART_RXIFLSEL_LEAVEL(FIFOLEAVEL) ((FIFOLEAVEL == UART_RXIFLSEL_LEAVEL_1_8) || \
                                             (FIFOLEAVEL == UART_RXIFLSEL_LEAVEL_1_4) || \
                                             (FIFOLEAVEL == UART_RXIFLSEL_LEAVEL_1_2) || \
                                             (FIFOLEAVEL == UART_RXIFLSEL_LEAVEL_3_4) || \
                                             (FIFOLEAVEL == UART_RXIFLSEL_LEAVEL_7_8))

#define UART_TXIFLSEL_LEAVEL_1_8 ((uint32_t)0x00)
#define UART_TXIFLSEL_LEAVEL_1_4 ((uint32_t)0x01)
#define UART_TXIFLSEL_LEAVEL_1_2 ((uint32_t)0x02)
#define UART_TXIFLSEL_LEAVEL_3_4 ((uint32_t)0x03)
#define UART_TXIFLSEL_LEAVEL_7_8 ((uint32_t)0x04)
#define IS_UART_TXIFLSEL_LEAVEL(FIFOLEAVEL) ((FIFOLEAVEL == UART_TXIFLSEL_LEAVEL_1_8) || \
                                             (FIFOLEAVEL == UART_TXIFLSEL_LEAVEL_1_4) || \
                                             (FIFOLEAVEL == UART_TXIFLSEL_LEAVEL_1_2) || \
                                             (FIFOLEAVEL == UART_TXIFLSEL_LEAVEL_3_4) || \
                                             (FIFOLEAVEL == UART_TXIFLSEL_LEAVEL_7_8))
/**
  *@}
  */
/**IMSC
  *@defgroup{UART_IT    
  */
#define UART_IT_OE ((uint32_t)0x400)
#define UART_IT_BE ((uint32_t)0x200)
#define UART_IT_PE ((uint32_t)0x100)
#define UART_IT_FE ((uint32_t)0x080)
#define UART_IT_RT ((uint32_t)0x040)
#define UART_IT_TX ((uint32_t)0x020)
#define UART_IT_RX ((uint32_t)0x010)
#define UART_IT_CTS ((uint32_t)0x002)
#define IS_UART_IT(UART_IT) ((UART_IT == UART_IT_OE) || \
                             (UART_IT == UART_IT_BE) || \
                             (UART_IT == UART_IT_PE) || \
                             (UART_IT == UART_IT_FE) || \
                             (UART_IT == UART_IT_RT) || \
                             (UART_IT == UART_IT_TX) || \
                             (UART_IT == UART_IT_RX) || \
                             (UART_IT == UART_IT_CTS) ||)
/**
  *@}
  */
/**RIS
  *@{UART_STATUSFLAG  UARTFR
  */

#define UART_FLAG_RI UART_STATUS_RI
#define UART_FLAG_TXFE UART_STATUS_TXFE
#define UART_FLAG_RXFF UART_STATUS_RXFF
#define UART_FLAG_TXFF UART_STATUS_TXFF
#define UART_FLAG_RXFE UART_STATUS_RXFE
#define UART_FLAG_BUSY UART_STATUS_BUSY

#define UART_FLAG_CTS UART_STATUS_CTS

#define UART_STATUS_RI ((uint32_t)0x100)
#define UART_STATUS_TXFE ((uint32_t)0X080)
#define UART_STATUS_RXFF ((uint32_t)0x040)
#define UART_STATUS_TXFF ((uint32_t)0X020)
#define UART_STATUS_RXFE ((uint32_t)0x010)
#define UART_STATUS_BUSY ((uint32_t)0X008)
#define UART_STATUS_nCTS ((uint32_t)0X001)
#define IS_UART_STATUSFLAG(FLAG) ((FLAG == UART_STATUS_RI) ||   \
                                  (FLAG == UART_STATUS_TXFE) || \
                                  (FLAG == UART_STATUS_RXFF) || \
                                  (FLAG == UART_STATUS_TXFF) || \
                                  (FLAG == UART_STATUS_RXFE) || \
                                  (FLAG == UART_STATUS_BUSY) || \
                                  (FLAG == UART_STATUS_CTS))
/**
  *
  */
/**
  *@{UART_RX_ERROR_FLAG
  */
#define UART_RX_ERROR_OE ((uint32_t)0x08 << 12)
#define UART_RX_ERROR_BE ((uint32_t)0x04 << 12)
#define UART_RX_ERROR_PE ((uint32_t)0x02 << 12)
#define UART_RX_ERROR_FE ((uint32_t)0x01 << 12)
#define UART_RX_ERROR_FLAG(ERROR) ((ERROR == UART_RX_ERROR_OE) || \
                                   (ERROR == UART_RX_ERROR_BE) || \
                                   (ERROR == UART_RX_ERROR_PE) || \
                                   (ERROR == UART_RX_ERROR_FE))
/**
  *@}
  */
/****************** Bit Definition for UARTDR Register **************/
#define UARTDR_Pos 0
#define UARTDR_Msk (0xfffUL << UARTDR_Pos)
#define UARTDR_OE_Pos 11
#define UARTDR_OE_Msk (0x1UL << UARTDR_OE_Pos)
#define UARTDR_BE_Pos 10
#define UARTDR_BE_Msk (0x1UL << UARTDR_BE_Pos)
#define UARTDR_PE_Pos 9
#define UARTDR_PE_Msk (0x1UL << UARTDR_PE_Pos)
#define UARTDR_FE_Pos 8
#define UARTDR_FE_Msk (0x1UL << UARTDR_FE_Pos)
#define UARTDR_DATA_Pos 7
#define UARTDR_DATA_Msk (0xff << UARTDR_DATA_Pos)

/****************** Bit Definition for UARTRSR Register **************/
#define UART_ECR_OE_Pos 3
#define UART_ECR_OE_Msk (0x1UL << UART_ECR_OE_Pos)
#define UART_ECR_BE_Pos 2
#define UART_ECR_BE_Msk (0x1UL << UART_ECR_BE_Pos)
#define UART_ECR_PE_Pos 1
#define UART_ECR_PE_Msk (0x1UL << UART_ECR_PE_Pos)
#define UART_ECR_FE_Pos 0
#define UART_ECR_FE_Msk (0x1UL << UART_ECR_FE_Pos)

/****************** Bit Definition for UARTFR Register **************/
#define UARTFR_RI_Pos 8
#define UARTFR_RI_Msk (0x1UL << UARTFR_RI_Pos)
#define UARTFR_TXFE_Pos 7
#define UARTFR_TXFE_Msk (0x1UL << UARTFR_TXFE_Pos)
#define UARTFR_TXFE (0X1UL << UARTFR_TXFE_Pos)
#define UARTFR_RXFF_Pos 6
#define UARTFR_RXFF_Msk (0x1UL << UARTFR_RXFF_Pos)
#define UARTFR_RXFF (0x1UL << UARTFR_RXFF_Pos)
#define UARTFR_TXFF_Pos 5
#define UARTFR_TXFF_Msk (0x1UL << UARTFR_TXFF_Pos)
#define UARTFR_TXFF (0x1UL << UARTFR_TXFF_Pos)
#define UARTFR_RXFE_Pos 4
#define UARTFR_RXFE_Msk (0x1UL << UARTFR_RXFE_Pos)
#define UARTFR_RXFE (0x1UL << UARTFR_RXFE_Pos)
#define UARTFR_BUSY_Pos 3
#define UARTFR_BUSY_Msk (0x1UL << UARTFR_BUSY_Pos)
#define UARTFR_CTS_Pos 0
#define UARTFR_CTS_Msk (0x1UL << UARTFR_CTS_Pos)

/****************** Bit Definition for UARTILPR Register **************/
#define UARTILPR_Pos 0
#define UARTILPR_Msk (0xffUL << UARTILPR_Pos)

/****************** Bit Definition for UARTILBRD Register **************/
#define UARTIBRD_Pos 0
#define UARTIBRD_Msk (0xffff << UARTIBRD_Pos)

/****************** Bit Definition for UARTIFBRD Register **************/
#define UARTFBRD_Pos 0
#define UARTFBRD_Msk (0x3f << UARTFBRD_Pos)

/****************** Bit Definition for UARTLCR Register **************/
#define UARTLCR_SPS_Pos 7
#define UARTLCR_SPS_Msk (0x1UL << UARTLCR_SPS_Pos)
#define UARTLCR_SPS_OFF (0x0UL << UARTLCR_SPS_Pos)
#define UARTLCR_SPS_ON (0x1UL << UARTLCR_SPS_Pos)
#define UARTLCR_WLEN_Pos 5
#define UARTLCR_WLEN_8 (0x3UL << UARTLCR_WLEN_Pos)
#define UARTLCR_WLEN_7 (0x2UL << UARTLCR_WLEN_Pos)
#define UARTLCR_WLEN_6 (0x1UL << UARTLCR_WLEN_Pos)
#define UARTLCR_WLEN_5 (0x0UL << UARTLCR_WLEN_Pos)
#define UARTLCR_FEN_Pos 4
#define UARTLCR_FEN_Msk (0x1UL << UARTLCR_FEN_Pos)
#define UARTLCR_FEN_OFF (0x0UL << UARTLCR_FEN_Pos)
#define UARTLCR_FEN_ON (0x1UL << UARTLCR_FEN_Pos)
#define UARTLCR_STP2_Pos 3
#define UARTLCR_STP2_Msk (0x1UL << UARTLCR_STP2_Pos)
#define UARTLCR_STP2_OFF (0x0UL << UARTLCR_STP2_Pos)
#define UARTLCR_STP2_ON (0x1UL << UARTLCR_STP2_Pos)
#define UARTLCR_EPS_Pos 2
#define UARTLCR_EPS_Msk (0x1UL << UARTLCR_EPS_Pos)
#define UARTLCR_EPS_ODD (0x0UL << UARTLCR_EPS_Pos)
#define UARTLCR_EPS_EVEN (0x1UL << UARTLCR_EPS_Pos)
#define UARTLCR_PEN_Pos 1
#define UARTLCR_PEN_Msk (0x1UL << UARTLCR_PEN_Pos)
#define UARTLCR_PEN_OFF (0x0UL << UARTLCR_PEN_Pos)
#define UARTLCR_PEN_ON (0x1UL << UARTLCR_PEN_Pos)
#define UARTLCR_BRK_Pos 0
#define UARTLCR_BRK_Msk (0x0UL << UARTLCR_BRK_Pos)
//#define     UARTLCR_BRK_OFF     (0x0UL << UARTLCR_BRK_Pos)
#define UARTLCR_BRK (0x1UL << UARTLCR_BRK_Pos)

/*
 *      PEN   EPS  SPS  Paritybit ( transmitted or checked )
 *       0     x    x     not  transmitted or check
 *       1     1    0     Even parity
 *       1     0    0     Odd  parity
 *       1     0    1     1
 *       1     1    1     0
 */

/****************** Bit Definition for UARTCR Register **************/
#define UARTCR_CTSEN_Pos 15
#define UARTCR_CTSEN_Msk (0x1UL << UARTCR_CTSEN_Pos)
#define UARTCR_RTSEN_Pos 14RT_AFCE_OFF,
#define UARTCR_RTSEN_Msk (0x1UL << UARTCR_RTSEN_Pos)

#define UARTCR_RTS_Pos 11
#define UARTCR_RTS_Msk (0x1UL << UARTCR_RTS_Pos)
#define UARTCR_DTR_Pos 10
#define UARTCR_DTR_Msk (0x1UL << UARTCR_DTR_Pos)
#define UARTCR_RXE_Pos 9
#define UARTCR_RXE_Msk (0x1UL << UARTCR_RXE_Pos)
#define UARTCR_RXE_ON (0x1UL << UARTCR_RXE_Pos)
#define UARTCR_TXE_Pos 8
#define UARTCR_TXE_Msk (0x1UL << UARTCR_TXE_Pos)
#define UARTCR_TXE_ON (0x1UL << UARTCR_TXE_Pos)
#define UARTCR_LBM_Pos 7
#define UARTCR_LBM_Msk (0x1UL << UARTCR_LBM_Pos)
#define UARTCR_LBM_ON (0x1UL << UARTCR_LBM_Pos)
#define UARTCR_LBM_OFF (0x0UL << UARTCR_LBM_Pos)

#define UARTCR_SIRLP_Pos 2
#define UARTCR_SIRLP_Msk (0x1UL << UARTCR_SIRLP_Pos)
#define UARTCR_SIREN_Pos 1
#define UARTCR_SIREN_Msk (0x1UL << UARTCR_SIREN_Pos)
#define UART_SIREN_OFF (0x0UL << UARTCR_SIREN_Pos)
#define UART_SIREN_ON (0x1UL << UARTCR_SIREN_Pos)
#define UARTCR_EN_Pos 0
#define UARTCR_EN_Msk (0x1UL << UARTCR_EN_Pos)
#define UARTEN_ON (0x1UL << UARTCR_EN_Pos)
#define UARTEN_OFF (0x0UL << UARTCR_EN_Pos)

/****************** Bit Definition for UARTIFLS Register **************/
#define UARTIFLS_RX_Pos 3
#define UARTIFLS_RX_Msk (0x7UL << UARTIFLS_RX_Pos)
#define UARTIFLS_RX1_8FULL (0x0UL << UARTIFLS_RX_Pos)
#define UARTIFLS_RX1_4FULL (0x1UL << UARTIFLS_RX_Pos)
#define UARTIFLS_RX1_2FULL (0x2UL << UARTIFLS_RX_Pos)
#define UARTIFLS_RX3_4FULL (0x3UL << UARTIFLS_RX_Pos)
#define UARTIFLS_RX7_8FULL (0x4UL << UARTIFLS_RX_Pos)
#define UARTIFLS_TX_Pos 0
#define UARTIFLS_TX_Msk (0x7UL << UARTIFLS_TX_Pos)
#define UARTIFLS_TX1_8FULL (0x0UL << UARTIFLS_TX_Pos)
#define UARTIFLS_TX1_4FULL (0x1UL << UARTIFLS_TX_Pos)
#define UARTIFLS_TX1_2FULL (0x2UL << UARTIFLS_TX_Pos)
#define UARTIFLS_TX3_4FULL (0x3UL << UARTIFLS_TX_Pos)
#define UARTIFLS_TX7_8FULL (0x4UL << UARTIFLS_TX_Pos)

/****************** Bit Definition for UARTIMSC Register **************/
#define UARTIMSC_OEIM_Pos 10
#define UARTIMSC_OEIM_Msk (0x1UL << UARTIMSC_OEIM_Pos)
#define UARTIMSC_BEIM_Pos 9
#define UARTIMSC_BEIM_Msk (0x1UL << UARTIMSC_BEIM_Pos)
#define UARTIMSC_PEIM_Pos 8
#define UARTIMSC_PEIM_Msk (0x1UL << UARTIMSC_PEIM_Pos)
#define UARTIMSC_FEIM_Pos 7
#define UARTIMSC_FEIM_Msk (0x1UL << UARTIMSC_FEIM_Pos)
#define UARTIMSC_RTIM_Pos 6
#define UARTIMSC_RTIM_Msk (0x1UL << UARTIMSC_RTIM_Pos)
#define UARTIMSC_TXIM_Pos 5
#define UARTIMSC_TXIM_Msk (0x1UL << UARTIMSC_TXIM_Pos)
#define UART_TX_INTR_OFF (0x0UL << UARTIMSC_TXIM_Pos)
#define UART_TX_INTR_ON (0x1UL << UARTIMSC_TXIM_Pos)
#define UARTIMSC_RXIM_Pos 4
#define UARTIMSC_RXIM_Msk (0x1UL << UARTIMSC_RXIM_Pos)
#define UART_RX_INTR_OFF (0x0UL << UARTIMSC_RXIM_Pos)
#define UART_RX_INTR_ON (0x1UL << UARTIMSC_RXIM_Pos)

/****************** Bit Definition for UARTICR Register **************/
#define UARTICR_OEIC_Pos 10
#define UARTICR_OEIC_Msk (0x1UL << UARTICR_OEIC_Pos)
#define UARTICR_OEIC (0x1UL << UARTICR_OEIC_Pos)
#define UARTICR_BEIC_Pos 9
#define UARTICR_BEIC_Msk (0x1UL << UARTICR_BEIC_Pos)
#define UARTICR_BEIC (0x1UL << UARTICR_BEIC_Pos)
#define UARTICR_PEIC_Pos 8
#define UARTICR_PEIC_Msk (0x1UL << UARTICR_PEIC_Pos)
#define UARTICR_PEIC (0x1UL << UARTICR_PEIC_Pos)
#define UARTICR_FEIC_Pos 7
#define UARTICR_FEIC_Msk (0x1UL << UARTICR_FEIC_Pos)
#define UARTICR_FEIC (0x1UL << UARTICR_FEIC_Pos)
#define UARTICR_RTIC_Pos 6
#define UARTICR_RTIC_Msk (0x1UL << UARTICR_RTIC_Pos)
#define UARTICR_RTIC (0x1UL << UARTICR_RTIC_Pos)
#define UARTICR_TXIC_Pos 5
#define UARTICR_TXIC_Msk (0x1UL << UARTICR_TXIC_Pos)
#define UARTICR_TXIC (0x1UL << UARTICR_TXIC_Pos)
#define UARTICR_RXIC_Pos 4
#define UARTICR_RXIC_Msk (0x1UL << UARTICR_RXIC_Pos)
#define UARTICR_RXIC (0x1UL << UARTICR_RXIC_Pos)

/* ==========================================================  DR  =========================================================== */
#define UART0_DR_OE_Pos (11UL)     /*!< OE (Bit 11)                                           */
#define UART0_DR_OE_Msk (0x800UL)  /*!< OE (Bitfield-Mask: 0x01)                              */
#define UART0_DR_BE_Pos (10UL)     /*!< BE (Bit 10)                                           */
#define UART0_DR_BE_Msk (0x400UL)  /*!< BE (Bitfield-Mask: 0x01)                              */
#define UART0_DR_PE_Pos (9UL)      /*!< PE (Bit 9)                                            */
#define UART0_DR_PE_Msk (0x200UL)  /*!< PE (Bitfield-Mask: 0x01)                              */
#define UART0_DR_FE_Pos (8UL)      /*!< FE (Bit 8)                                            */
#define UART0_DR_FE_Msk (0x100UL)  /*!< FE (Bitfield-Mask: 0x01)                              */
#define UART0_DR_DATA_Pos (0UL)    /*!< DATA (Bit 0)                                          */
#define UART0_DR_DATA_Msk (0xffUL) /*!< DATA (Bitfield-Mask: 0xff)                            */
/* ==========================================================  RSR  ========================================================== */
#define UART0_RSR_OE_Pos (3UL)   /*!< OE (Bit 3)                                            */
#define UART0_RSR_OE_Msk (0x8UL) /*!< OE (Bitfield-Mask: 0x01)                              */
#define UART0_RSR_BE_Pos (2UL)   /*!< BE (Bit 2)                                            */
#define UART0_RSR_BE_Msk (0x4UL) /*!< BE (Bitfield-Mask: 0x01)                              */
#define UART0_RSR_PE_Pos (1UL)   /*!< PE (Bit 1)                                            */
#define UART0_RSR_PE_Msk (0x2UL) /*!< PE (Bitfield-Mask: 0x01)                              */
#define UART0_RSR_FE_Pos (0UL)   /*!< FE (Bit 0)                                            */
#define UART0_RSR_FE_Msk (0x1UL) /*!< FE (Bitfield-Mask: 0x01)                              */
/* ==========================================================  FR  =========================================================== */
#define UART0_FR_RI_Pos (8UL)      /*!< RI (Bit 8)                                            */
#define UART0_FR_RI_Msk (0x100UL)  /*!< RI (Bitfield-Mask: 0x01)                              */
#define UART0_FR_TXFE_Pos (7UL)    /*!< TXFE (Bit 7)                                          */
#define UART0_FR_TXFE_Msk (0x80UL) /*!< TXFE (Bitfield-Mask: 0x01)                            */
#define UART0_FR_RXFF_Pos (6UL)    /*!< RXFF (Bit 6)                                          */
#define UART0_FR_RXFF_Msk (0x40UL) /*!< RXFF (Bitfield-Mask: 0x01)                            */
#define UART0_FR_TXFF_Pos (5UL)    /*!< TXFF (Bit 5)                                          */
#define UART0_FR_TXFF_Msk (0x20UL) /*!< TXFF (Bitfield-Mask: 0x01)                            */
#define UART0_FR_RXFE_Pos (4UL)    /*!< RXFE (Bit 4)                                          */
#define UART0_FR_RXFE_Msk (0x10UL) /*!< RXFE (Bitfield-Mask: 0x01)                            */
#define UART0_FR_BUSY_Pos (3UL)    /*!< BUSY (Bit 3)                                          */
#define UART0_FR_BUSY_Msk (0x8UL)  /*!< BUSY (Bitfield-Mask: 0x01)                            */
#define UART0_FR_DCD_Pos (2UL)     /*!< DCD (Bit 2)                                           */
#define UART0_FR_DCD_Msk (0x4UL)   /*!< DCD (Bitfield-Mask: 0x01)                             */
#define UART0_FR_DSR_Pos (1UL)     /*!< DSR (Bit 1)                                           */
#define UART0_FR_DSR_Msk (0x2UL)   /*!< DSR (Bitfield-Mask: 0x01)                             */
#define UART0_FR_CTS_Pos (0UL)     /*!< CTS (Bit 0)                                           */
#define UART0_FR_CTS_Msk (0x1UL)   /*!< CTS (Bitfield-Mask: 0x01)                             */
/* =========================================================  ILPR  ========================================================== */
#define UART0_ILPR_ILPDVSR_Pos (0UL)    /*!< ILPDVSR (Bit 0)                                       */
#define UART0_ILPR_ILPDVSR_Msk (0xffUL) /*!< ILPDVSR (Bitfield-Mask: 0xff)                         */
/* =========================================================  IBRD  ========================================================== */
#define UART0_IBRD_BAUD_DIVINT_Pos (0UL)      /*!< BAUD_DIVINT (Bit 0)                                   */
#define UART0_IBRD_BAUD_DIVINT_Msk (0xffffUL) /*!< BAUD_DIVINT (Bitfield-Mask: 0x7fff)                   */
/* =========================================================  FBRD  ========================================================== */
#define UART0_FBRD_BAUD_DIVFRAC_Pos (0UL)    /*!< BAUD_DIVFRAC (Bit 0)                                  */
#define UART0_FBRD_BAUD_DIVFRAC_Msk (0x3fUL) /*!< BAUD_DIVFRAC (Bitfield-Mask: 0x3f)                    */
/* ==========================================================  LCR  ========================================================== */
#define UART0_LCR_SPS_Pos (7UL)     /*!< SPS (Bit 7)                                           */
#define UART0_LCR_SPS_Msk (0x80UL)  /*!< SPS (Bitfield-Mask: 0x01)                             */
#define UART0_LCR_WLEN_Pos (5UL)    /*!< WLEN (Bit 5)                                          */
#define UART0_LCR_WLEN_Msk (0x60UL) /*!< WLEN (Bitfield-Mask: 0x03)                            */
#define UART0_LCR_FEN_Pos (4UL)     /*!< FEN (Bit 4)                                           */
#define UART0_LCR_FEN_Msk (0x10UL)  /*!< FEN (Bitfield-Mask: 0x01)                             */
#define UART0_LCR_STP2_Pos (3UL)    /*!< STP2 (Bit 3)                                          */
#define UART0_LCR_STP2_Msk (0x8UL)  /*!< STP2 (Bitfield-Mask: 0x01)                            */
#define UART0_LCR_EPS_Pos (2UL)     /*!< EPS (Bit 2)                                           */
#define UART0_LCR_EPS_Msk (0x4UL)   /*!< EPS (Bitfield-Mask: 0x01)                             */
#define UART0_LCR_PEN_Pos (1UL)     /*!< PEN (Bit 1)                                           */
#define UART0_LCR_PEN_Msk (0x2UL)   /*!< PEN (Bitfield-Mask: 0x01)                             */
#define UART0_LCR_BRK_Pos (0UL)     /*!< BRK (Bit 0)                                           */
#define UART0_LCR_BRK_Msk (0x1UL)   /*!< BRK (Bitfield-Mask: 0x01)                             */
/* ==========================================================  CR  =========================================================== */
#define UART0_CR_CTSEn_Pos (15UL)     /*!< CTSEn (Bit 15)                                        */
#define UART0_CR_CTSEn_Msk (0x8000UL) /*!< CTSEn (Bitfield-Mask: 0x01)                           */
#define UART0_CR_RTSEn_Pos (14UL)     /*!< RTSEn (Bit 14)                                        */
#define UART0_CR_RTSEn_Msk (0x4000UL) /*!< RTSEn (Bitfield-Mask: 0x01)                           */
#define UART0_CR_Out2_Pos (13UL)      /*!< Out2 (Bit 13)                                         */
#define UART0_CR_Out2_Msk (0x2000UL)  /*!< Out2 (Bitfield-Mask: 0x01)                            */
#define UART0_CR_Out1_Pos (12UL)      /*!< Out1 (Bit 12)                                         */
#define UART0_CR_Out1_Msk (0x1000UL)  /*!< Out1 (Bitfield-Mask: 0x01)                            */
#define UART0_CR_RTS_Pos (11UL)       /*!< RTS (Bit 11)                                          */
#define UART0_CR_RTS_Msk (0x800UL)    /*!< RTS (Bitfield-Mask: 0x01)                             */
#define UART0_CR_DTR_Pos (10UL)       /*!< DTR (Bit 10)                                          */
#define UART0_CR_DTR_Msk (0x400UL)    /*!< DTR (Bitfield-Mask: 0x01)                             */
#define UART0_CR_RXE_Pos (9UL)        /*!< RXE (Bit 9)                                           */
#define UART0_CR_RXE_Msk (0x200UL)    /*!< RXE (Bitfield-Mask: 0x01)                             */
#define UART0_CR_TXE_Pos (8UL)        /*!< TXE (Bit 8)                                           */
#define UART0_CR_TXE_Msk (0x100UL)    /*!< TXE (Bitfield-Mask: 0x01)                             */
#define UART0_CR_LBE_Pos (7UL)        /*!< LBE (Bit 7)                                           */
#define UART0_CR_LBE_Msk (0x80UL)     /*!< LBE (Bitfield-Mask: 0x01)                             */
#define UART0_CR_SIRLP_Pos (2UL)      /*!< SIRLP (Bit 2)                                         */
#define UART0_CR_SIRLP_Msk (0x4UL)    /*!< SIRLP (Bitfield-Mask: 0x01)                           */
#define UART0_CR_SIREN_Pos (1UL)      /*!< SIREN (Bit 1)                                         */
#define UART0_CR_SIREN_Msk (0x2UL)    /*!< SIREN (Bitfield-Mask: 0x01)                           */
#define UART0_CR_UARTEN_Pos (0UL)     /*!< UARTEN (Bit 0)                                        */
#define UART0_CR_UARTEN_Msk (0x1UL)   /*!< UARTEN (Bitfield-Mask: 0x01)                          */
/* =========================================================  IFLS  ========================================================== */
#define UART0_IFLS_OEIM_Pos (10UL)    /*!< OEIM (Bit 10)                                         */
#define UART0_IFLS_OEIM_Msk (0x400UL) /*!< OEIM (Bitfield-Mask: 0x01)                            */
#define UART0_IFLS_BEIM_Pos (9UL)     /*!< BEIM (Bit 9)                                          */
#define UART0_IFLS_BEIM_Msk (0x200UL) /*!< BEIM (Bitfield-Mask: 0x01)                            */
#define UART0_IFLS_PEIM_Pos (7UL)     /*!< PEIM (Bit 7)                                          */
#define UART0_IFLS_PEIM_Msk (0x80UL)  /*!< PEIM (Bitfield-Mask: 0x01)                            */
#define UART0_IFLS_RTIM_Pos (6UL)     /*!< RTIM (Bit 6)                                          */
#define UART0_IFLS_RTIM_Msk (0x40UL)  /*!< RTIM (Bitfield-Mask: 0x01)                            */
#define UART0_IFLS_TXIM_Pos (5UL)     /*!< TXIM (Bit 5)                                          */
#define UART0_IFLS_TXIM_Msk (0x20UL)  /*!< TXIM (Bitfield-Mask: 0x01)                            */
#define UART0_IFLS_RXIM_Pos (4UL)     /*!< RXIM (Bit 4)                                          */
#define UART0_IFLS_RXIM_Msk (0x10UL)  /*!< RXIM (Bitfield-Mask: 0x01)                            */
#define UART0_IFLS_DSRMIM_Pos (3UL)   /*!< DSRMIM (Bit 3)                                        */
#define UART0_IFLS_DSRMIM_Msk (0x8UL) /*!< DSRMIM (Bitfield-Mask: 0x01)                          */
#define UART0_IFLS_DCDMIM_Pos (2UL)   /*!< DCDMIM (Bit 2)                                        */
#define UART0_IFLS_DCDMIM_Msk (0x4UL) /*!< DCDMIM (Bitfield-Mask: 0x01)                          */
#define UART0_IFLS_CTSMIM_Pos (1UL)   /*!< CTSMIM (Bit 1)                                        */
#define UART0_IFLS_CTSMIM_Msk (0x2UL) /*!< CTSMIM (Bitfield-Mask: 0x01)                          */
#define UART0_IFLS_RIMIM_Pos (0UL)    /*!< RIMIM (Bit 0)                                         */
#define UART0_IFLS_RIMIM_Msk (0x1UL)  /*!< RIMIM (Bitfield-Mask: 0x01)                           */
/* =========================================================  IMSC  ========================================================== */
#define UART0_IMSC_OEIM_Pos (10UL)    /*!< OEIM (Bit 10)                                         */
#define UART0_IMSC_OEIM_Msk (0x400UL) /*!< OEIM (Bitfield-Mask: 0x01)                            */
#define UART0_IMSC_BEIM_Pos (9UL)     /*!< BEIM (Bit 9)                                          */
#define UART0_IMSC_BEIM_Msk (0x200UL) /*!< BEIM (Bitfield-Mask: 0x01)                            */
#define UART0_IMSC_PEIM_Pos (7UL)     /*!< PEIM (Bit 7)                                          */
#define UART0_IMSC_PEIM_Msk (0x80UL)  /*!< PEIM (Bitfield-Mask: 0x01)                            */
#define UART0_IMSC_RTIM_Pos (6UL)     /*!< RTIM (Bit 6)                                          */
#define UART0_IMSC_RTIM_Msk (0x40UL)  /*!< RTIM (Bitfield-Mask: 0x01)                            */
#define UART0_IMSC_TXIM_Pos (5UL)     /*!< TXIM (Bit 5)                                          */
#define UART0_IMSC_TXIM_Msk (0x20UL)  /*!< TXIM (Bitfield-Mask: 0x01)                            */
#define UART0_IMSC_RXIM_Pos (4UL)     /*!< RXIM (Bit 4)                                          */
#define UART0_IMSC_RXIM_Msk (0x10UL)  /*!< RXIM (Bitfield-Mask: 0x01)                            */
#define UART0_IMSC_DSRMIM_Pos (3UL)   /*!< DSRMIM (Bit 3)                                        */
#define UART0_IMSC_DSRMIM_Msk (0x8UL) /*!< DSRMIM (Bitfield-Mask: 0x01)                          */
#define UART0_IMSC_DCDMIM_Pos (2UL)   /*!< DCDMIM (Bit 2)                                        */
#define UART0_IMSC_DCDMIM_Msk (0x4UL) /*!< DCDMIM (Bitfield-Mask: 0x01)                          */
#define UART0_IMSC_CTSMIM_Pos (1UL)   /*!< CTSMIM (Bit 1)                                        */
#define UART0_IMSC_CTSMIM_Msk (0x2UL) /*!< CTSMIM (Bitfield-Mask: 0x01)                          */
#define UART0_IMSC_RIMIM_Pos (0UL)    /*!< RIMIM (Bit 0)                                         */
#define UART0_IMSC_RIMIM_Msk (0x1UL)  /*!< RIMIM (Bitfield-Mask: 0x01)                           */
/* ==========================================================  RIS  ========================================================== */
#define UART0_RIS_OERIS_Pos (10UL)    /*!< OERIS (Bit 10)                                        */
#define UART0_RIS_OERIS_Msk (0x400UL) /*!< OERIS (Bitfield-Mask: 0x01)                           */
#define UART0_RIS_BERIS_Pos (9UL)     /*!< BERIS (Bit 9)                                         */
#define UART0_RIS_BERIS_Msk (0x200UL) /*!< BERIS (Bitfield-Mask: 0x01)                           */
#define UART0_RIS_PERIS_Pos (8UL)     /*!< PERIS (Bit 8)                                         */
#define UART0_RIS_PERIS_Msk (0x100UL) /*!< PERIS (Bitfield-Mask: 0x01)                           */
#define UART0_RIS_FERIS_Pos (7UL)     /*!< FERIS (Bit 7)                                         */
#define UART0_RIS_FERIS_Msk (0x80UL)  /*!< FERIS (Bitfield-Mask: 0x01)                           */
#define UART0_RIS_RTRIS_Pos (6UL)     /*!< RTRIS (Bit 6)                                         */
#define UART0_RIS_RTRIS_Msk (0x40UL)  /*!< RTRIS (Bitfield-Mask: 0x01)                           */
#define UART0_RIS_TXRIS_Pos (5UL)     /*!< TXRIS (Bit 5)                                         */
#define UART0_RIS_TXRIS_Msk (0x20UL)  /*!< TXRIS (Bitfield-Mask: 0x01)                           */
#define UART0_RIS_RXRIS_Pos (4UL)     /*!< RXRIS (Bit 4)                                         */
#define UART0_RIS_RXRIS_Msk (0x10UL)  /*!< RXRIS (Bitfield-Mask: 0x01)                           */
#define UART0_RIS_DSRRMIS_Pos (3UL)   /*!< DSRRMIS (Bit 3)                                       */
#define UART0_RIS_DSRRMIS_Msk (0x8UL) /*!< DSRRMIS (Bitfield-Mask: 0x01)                         */
#define UART0_RIS_DCDRMIS_Pos (2UL)   /*!< DCDRMIS (Bit 2)                                       */
#define UART0_RIS_DCDRMIS_Msk (0x4UL) /*!< DCDRMIS (Bitfield-Mask: 0x01)                         */
#define UART0_RIS_CTSRMIS_Pos (1UL)   /*!< CTSRMIS (Bit 1)                                       */
#define UART0_RIS_CTSRMIS_Msk (0x2UL) /*!< CTSRMIS (Bitfield-Mask: 0x01)                         */
#define UART0_RIS_RIRMIS_Pos (0UL)    /*!< RIRMIS (Bit 0)                                        */
#define UART0_RIS_RIRMIS_Msk (0x1UL)  /*!< RIRMIS (Bitfield-Mask: 0x01)                          */
/* ==========================================================  MIS  ========================================================== */
#define UART0_MIS_OEMIS_Pos (10UL)    /*!< OEMIS (Bit 10)                                        */
#define UART0_MIS_OEMIS_Msk (0x400UL) /*!< OEMIS (Bitfield-Mask: 0x01)                           */
#define UART0_MIS_BEMIS_Pos (9UL)     /*!< BEMIS (Bit 9)                                         */
#define UART0_MIS_BEMIS_Msk (0x200UL) /*!< BEMIS (Bitfield-Mask: 0x01)                           */
#define UART0_MIS_PEMIS_Pos (8UL)     /*!< PEMIS (Bit 8)                                         */
#define UART0_MIS_PEMIS_Msk (0x100UL) /*!< PEMIS (Bitfield-Mask: 0x01)                           */
#define UART0_MIS_FEMIS_Pos (7UL)     /*!< FEMIS (Bit 7)                                         */
#define UART0_MIS_FEMIS_Msk (0x80UL)  /*!< FEMIS (Bitfield-Mask: 0x01)                           */
#define UART0_MIS_RTMIS_Pos (6UL)     /*!< RTMIS (Bit 6)                                         */
#define UART0_MIS_RTMIS_Msk (0x40UL)  /*!< RTMIS (Bitfield-Mask: 0x01)                           */
#define UART0_MIS_TXMIS_Pos (5UL)     /*!< TXMIS (Bit 5)                                         */
#define UART0_MIS_TXMIS_Msk (0x20UL)  /*!< TXMIS (Bitfield-Mask: 0x01)                           */
#define UART0_MIS_RXMIS_Pos (4UL)     /*!< RXMIS (Bit 4)                                         */
#define UART0_MIS_RXMIS_Msk (0x10UL)  /*!< RXMIS (Bitfield-Mask: 0x01)                           */
#define UART0_MIS_DSRMMIS_Pos (3UL)   /*!< DSRMMIS (Bit 3)                                       */
#define UART0_MIS_DSRMMIS_Msk (0x8UL) /*!< DSRMMIS (Bitfield-Mask: 0x01)                         */
#define UART0_MIS_DCDMMIS_Pos (2UL)   /*!< DCDMMIS (Bit 2)                                       */
#define UART0_MIS_DCDMMIS_Msk (0x4UL) /*!< DCDMMIS (Bitfield-Mask: 0x01)                         */
#define UART0_MIS_CTSMMIS_Pos (1UL)   /*!< CTSMMIS (Bit 1)                                       */
#define UART0_MIS_CTSMMIS_Msk (0x2UL) /*!< CTSMMIS (Bitfield-Mask: 0x01)                         */
#define UART0_MIS_RIMMIS_Pos (0UL)    /*!< RIMMIS (Bit 0)                                        */
#define UART0_MIS_RIMMIS_Msk (0x1UL)  /*!< RIMMIS (Bitfield-Mask: 0x01)                          */
/* ==========================================================  ICR  ========================================================== */
#define UART0_ICR_OEIC_Pos (10UL)     /*!< OEIC (Bit 10)                                         */
#define UART0_ICR_OEIC_Msk (0x400UL)  /*!< OEIC (Bitfield-Mask: 0x01)                            */
#define UART0_ICR_BEIC_Pos (9UL)      /*!< BEIC (Bit 9)                                          */
#define UART0_ICR_BEIC_Msk (0x200UL)  /*!< BEIC (Bitfield-Mask: 0x01)                            */
#define UART0_ICR_PEMIS_Pos (8UL)     /*!< PEMIS (Bit 8)                                         */
#define UART0_ICR_PEMIS_Msk (0x100UL) /*!< PEMIS (Bitfield-Mask: 0x01)                           */
#define UART0_ICR_FEIC_Pos (7UL)      /*!< FEIC (Bit 7)                                          */
#define UART0_ICR_FEIC_Msk (0x80UL)   /*!< FEIC (Bitfield-Mask: 0x01)                            */
#define UART0_ICR_RTIC_Pos (6UL)      /*!< RTIC (Bit 6)                                          */
#define UART0_ICR_RTIC_Msk (0x40UL)   /*!< RTIC (Bitfield-Mask: 0x01)                            */
#define UART0_ICR_TXIC_Pos (5UL)      /*!< TXIC (Bit 5)                                          */
#define UART0_ICR_TXIC_Msk (0x20UL)   /*!< TXIC (Bitfield-Mask: 0x01)                            */
#define UART0_ICR_RXIC_Pos (4UL)      /*!< RXIC (Bit 4)                                          */
#define UART0_ICR_RXIC_Msk (0x10UL)   /*!< RXIC (Bitfield-Mask: 0x01)                            */
#define UART0_ICR_DSRMIC_Pos (3UL)    /*!< DSRMIC (Bit 3)                                        */
#define UART0_ICR_DSRMIC_Msk (0x8UL)  /*!< DSRMIC (Bitfield-Mask: 0x01)                          */
#define UART0_ICR_DCDMIC_Pos (2UL)    /*!< DCDMIC (Bit 2)                                        */
#define UART0_ICR_DCDMIC_Msk (0x4UL)  /*!< DCDMIC (Bitfield-Mask: 0x01)                          */
#define UART0_ICR_CTSMIC_Pos (1UL)    /*!< CTSMIC (Bit 1)                                        */
#define UART0_ICR_CTSMIC_Msk (0x2UL)  /*!< CTSMIC (Bitfield-Mask: 0x01)                          */
#define UART0_ICR_RIMIC_Pos (0UL)     /*!< RIMIC (Bit 0)                                         */
#define UART0_ICR_RIMIC_Msk (0x1UL)   /*!< RIMIC (Bitfield-Mask: 0x01)                           */
/* =========================================================  DMACR  ========================================================= */
#define UART0_DMACR_DMAONERR_Pos (2UL)   /*!< DMAONERR (Bit 2)                                      */
#define UART0_DMACR_DMAONERR_Msk (0x4UL) /*!< DMAONERR (Bitfield-Mask: 0x01)                        */
#define UART0_DMACR_TXDMAE_Pos (1UL)     /*!< TXDMAE (Bit 1)                                        */
#define UART0_DMACR_TXDMAE_Msk (0x2UL)   /*!< TXDMAE (Bitfield-Mask: 0x01)                          */
#define UART0_DMACR_RXDMAE_Pos (0UL)     /*!< RXDMAE (Bit 0)                                        */
#define UART0_DMACR_RXDMAE_Msk (0x1UL)   /*!< RXDMAE (Bitfield-Mask: 0x01)                          */
//void UART_DeInit(UART_TypeDef* UARTx);
void UART_BaudRateConfig(UART_TypeDef *UARTx, uint32_t baud);
void UART_FIFOLevelConfig(UART_TypeDef *UARTx, uint32_t FIFOSelect, uint32_t LeavelSelect);
//void UART_Init(UART_TypeDef* UARTx, UART_InitTypeDef* UART_InitStruct);
void UART_Init(UART_TypeDef *UARTx, UART_InitTypeDef *UART_InitStruct);
void UART_StructInit(UART_InitTypeDef *UART_InitStruct);
//void UART_ClockInit(UART_TypeDef* UARTx, UART_ClockInitTypeDef* UART_ClockInitStruct);
//void UART_ClockStructInit(UART_ClockInitTypeDef* UART_ClockInitStruct);
void UART_Cmd(UART_TypeDef *UARTx, FunctionalState NewState);
void UART_DirectionModeCmd(UART_TypeDef *UARTx, uint32_t UART_DirectionMode, FunctionalState NewState);
void UART_SetPrescaler(UART_TypeDef *UARTx, uint8_t UART_Prescaler); /* Not available for LCM32F03X LCM32F037 devices */
void UART_OverSampling8Cmd(UART_TypeDef *UARTx, FunctionalState NewState);
void UART_OneBitMethodCmd(UART_TypeDef *UARTx, FunctionalState NewState);
void UART_MSBFirstCmd(UART_TypeDef *UARTx, FunctionalState NewState);
void UART_DataInvCmd(UART_TypeDef *UARTx, FunctionalState NewState);
void UART_InvPinCmd(UART_TypeDef *UARTx, uint32_t UART_InvPin, FunctionalState NewState);
void UART_SWAPPinCmd(UART_TypeDef *UARTx, FunctionalState NewState);
void UART_ReceiverTimeOutCmd(UART_TypeDef *UARTx, FunctionalState NewState);
void UART_SetReceiverTimeOut(UART_TypeDef *UARTx, uint32_t UART_ReceiverTimeOut);
void UART_FIFOEnable(UART_TypeDef *UARTx, uint32_t NewState);

/* STOP Mode functions ********************************************************/
void UART_STOPModeCmd(UART_TypeDef *UARTx, FunctionalState NewState);
void UART_StopModeWakeUpSourceConfig(UART_TypeDef *UARTx, uint32_t UART_WakeUpSource); /* Not available for LCM32F03X LCM32F037 devices */

/* AutoBaudRate functions *****************************************************/
void UART_AutoBaudRateCmd(UART_TypeDef *UARTx, FunctionalState NewState);
void UART_AutoBaudRateConfig(UART_TypeDef *UARTx, uint32_t UART_AutoBaudRate);

/* Data transfers functions ***************************************************/
void UART_SendData(UART_TypeDef *UARTx, uint8_t Data);
uint16_t UART_ReceiveData(UART_TypeDef *UARTx);

/* Multi-Processor Communication functions ************************************/
void UART_SetAddress(UART_TypeDef *UARTx, uint8_t UART_Address);
void UART_MuteModeWakeUpConfig(UART_TypeDef *UARTx, uint32_t UART_WakeUp);
void UART_MuteModeCmd(UART_TypeDef *UARTx, FunctionalState NewState);
void UART_AddressDetectionConfig(UART_TypeDef *UARTx, uint32_t UART_AddressLength);

/* LIN mode functions *********************************************************/
void UART_LINBreakDetectLengthConfig(UART_TypeDef *UARTx, uint32_t UART_LINBreakDetectLength); /* Not available for LCM32F03X devices */
void UART_LINCmd(UART_TypeDef *UARTx, FunctionalState NewState);                               /* Not available for LCM32F03X devices */

/* Half-duplex mode function **************************************************/
void UART_HalfDuplexCmd(UART_TypeDef *UARTx, FunctionalState NewState);

/* Smartcard mode functions ***************************************************/
void UART_SmartCardCmd(UART_TypeDef *UARTx, FunctionalState NewState);     /* Not available for LCM32F03X devices */
void UART_SmartCardNACKCmd(UART_TypeDef *UARTx, FunctionalState NewState); /* Not available for LCM32F03X devices */
void UART_SetGuardTime(UART_TypeDef *UARTx, uint8_t UART_GuardTime);       /* Not available for LCM32F03X devices */
void UART_SetAutoRetryCount(UART_TypeDef *UARTx, uint8_t UART_AutoCount);  /* Not available for LCM32F03X devices */
void UART_SetBlockLength(UART_TypeDef *UARTx, uint8_t UART_BlockLength);   /* Not available for LCM32F03X devices */

/* IrDA mode functions ********************************************************/
void UART_IrDAConfig(UART_TypeDef *UARTx, uint32_t UART_IrDAMode); /* Not available for LCM32F03X devices */
void UART_IrDACmd(UART_TypeDef *UARTx, FunctionalState NewState);  /* Not available for LCM32F03X devices */

/* RS485 mode functions *******************************************************/
void UART_DECmd(UART_TypeDef *UARTx, FunctionalState NewState);
void UART_DEPolarityConfig(UART_TypeDef *UARTx, uint32_t UART_DEPolarity);
void UART_SetDEAssertionTime(UART_TypeDef *UARTx, uint32_t UART_DEAssertionTime);
void UART_SetDEDeassertionTime(UART_TypeDef *UARTx, uint32_t UART_DEDeassertionTime);

/* DMA transfers management functions *****************************************/
void UART_DMACmd(UART_TypeDef *UARTx, uint32_t UART_DMAReq, FunctionalState NewState);
void UART_DMAReceptionErrorConfig(UART_TypeDef *UARTx, uint32_t UART_DMAOnError);

/* Interrupts and flags management functions **********************************/
void UART_ITConfig(UART_TypeDef *UARTx, uint32_t UART_IT, FunctionalState NewState);
void UART_RequestCmd(UART_TypeDef *UARTx, uint32_t UART_Request, FunctionalState NewState);
void UART_OverrunDetectionConfig(UART_TypeDef *UARTx, uint32_t UART_OVRDetection);
FlagStatus UART_GetFlagStatus(UART_TypeDef *UARTx, uint32_t UART_FLAG);
void UART_ClearFlag(UART_TypeDef *UARTx, uint32_t UART_FLAG);
ITStatus UART_GetITStatus(UART_TypeDef *UARTx, uint32_t UART_IT);
void UART_ClearITPendingBit(UART_TypeDef *UARTx, uint32_t UART_IT);
#endif
