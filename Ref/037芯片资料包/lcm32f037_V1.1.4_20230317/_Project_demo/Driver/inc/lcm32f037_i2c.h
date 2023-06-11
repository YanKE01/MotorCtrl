
#ifndef LCM32F037_I2C_H
#define LCM32F037_I2C_H

#include <stdio.h>
#include "lcm32f037.h"


typedef struct
{
  uint32_t I2C_mode;                 /*master or Slave mode*/
  uint32_t I2C_Speed;                /*Speed=100 000 when bit rate is 100KHz */
  uint32_t I2C_SlaveAddressedLength; /*Slave addresse length*/
  uint32_t I2C_StopDetSlave;         /*whether access STOP_Intr whern address is not equal itself in slave mode*/
  uint32_t I2C_TxEmptyIntr;          /*whether generate TxEmpty intr*/
  uint32_t I2C_RxFifoFullHold;       /*whether hold bus when rxfifo full*/
  uint32_t I2C_StopDetMaster;        /*stop det if master active*/
} I2C_InitTypeDef;

/***************************IC_CON******************************/
typedef enum
{
  STANDARD_MODE = 0,
  FAST_MODE,
  HIGH_SPEED
} SpeedSelectType;
#define I2C_MasterOnlyMode ((uint32_t)0x00000041) //针对主机模式
#define I2C_SlaveOnlyMode ((uint32_t)0x00000000)

#define I2C_SPEED_STANDARD_MODE ((uint32_t)0x00000002) //针对主机模式
#define I2C_SPEED_FAST_MODE ((uint32_t)0x00000004)

#define I2C_SlaveAddressedLength_10bit ((uint32_t)0x00000008) //针对从机模式
#define I2C_SlaveAddressedLength_7bit ((uint32_t)0x00000000)

#define I2C_StopDet_SlaveActive ((uint32_t)0x00000080) //针对从机模式
#define I2C_StopDet_SlaveAlways ((uint32_t)0x00000000)

#define I2C_StopDet_MasterActive ((uint32_t)0x00000400) 
#define I2C_StopDet_MasterAlways ((uint32_t)0x00000000)

#define I2C_RxFifoFullHold_ENABLE ((uint32_t)0x00000200)
#define I2C_RxFifoFullHold_DISABLE ((uint32_t)0x00000000)

#define I2C_TxEmptyIntr_ENABLE ((uint32_t)0x00000100)
#define I2C_TxEmptyIntr_DISABLE ((uint32_t)0x00000000)

//发送 FIFO 阈值
#define I2C_TX_FIFO_IT_0 ((uint32_t)0x00000000)
#define I2C_TX_FIFO_IT_1 ((uint32_t)0x00000001)
#define I2C_TX_FIFO_IT_2 ((uint32_t)0x00000002)
#define I2C_TX_FIFO_IT_3 ((uint32_t)0x00000003)
#define I2C_TX_FIFO_IT_4 ((uint32_t)0x00000004)
#define I2C_TX_FIFO_IT_5 ((uint32_t)0x00000005)
#define I2C_TX_FIFO_IT_6 ((uint32_t)0x00000006)
#define I2C_TX_FIFO_IT_7 ((uint32_t)0x00000007)
#define IS_I2C_TX_FIFO_IT(TxFifoValue) ((TxFifoValue == I2C_TX_FIFO_IT_0) || \
                                        (TxFifoValue == I2C_TX_FIFO_IT_1) || \
                                        (TxFifoValue == I2C_TX_FIFO_IT_2) || \
                                        (TxFifoValue == I2C_TX_FIFO_IT_3) || \
                                        (TxFifoValue == I2C_TX_FIFO_IT_4) || \
                                        (TxFifoValue == I2C_TX_FIFO_IT_5) || \
                                        (TxFifoValue == I2C_TX_FIFO_IT_6) || \
                                        (TxFifoValue == I2C_TX_FIFO_IT_7))
//接收 FIFO 阈值
#define I2C_RX_FIFO_IT_0 ((uint32_t)0x00000000)
#define I2C_RX_FIFO_IT_1 ((uint32_t)0x00000001)
#define I2C_RX_FIFO_IT_2 ((uint32_t)0x00000002)
#define I2C_RX_FIFO_IT_3 ((uint32_t)0x00000003)
#define I2C_RX_FIFO_IT_4 ((uint32_t)0x00000004)
#define I2C_RX_FIFO_IT_5 ((uint32_t)0x00000005)
#define I2C_RX_FIFO_IT_6 ((uint32_t)0x00000006)
#define I2C_RX_FIFO_IT_7 ((uint32_t)0x00000007)
#define IS_I2C_RX_FIFO_IT(RxFifoValue) ((RxFifoValue == I2C_RX_FIFO_IT_0) || \
                                        (RxFifoValue == I2C_RX_FIFO_IT_1) || \
                                        (RxFifoValue == I2C_RX_FIFO_IT_2) || \
                                        (RxFifoValue == I2C_RX_FIFO_IT_3) || \
                                        (RxFifoValue == I2C_RX_FIFO_IT_4) || \
                                        (RxFifoValue == I2C_RX_FIFO_IT_5) || \
                                        (RxFifoValue == I2C_RX_FIFO_IT_6) || \
                                        (RxFifoValue == I2C_RX_FIFO_IT_7))

// DMA 使能
#define I2C_DMAReq_Rx I2C_DMA_CR_RDME_Msk
#define I2C_DMAReq_Tx I2C_DMA_CR_TDME_MSk
#define IS_I2C_DMAReq(I2C_DMAReq) ((I2C_DMAReq == I2C_DMAReq_Rx) || (I2C_DMAReq == I2C_DMAReq_Tx))

// DMA发送数据水平
#define I2C_TX_DMA_IT_0 ((uint32_t)0x00000000)
#define I2C_TX_DMA_IT_1 ((uint32_t)0x00000001)
#define I2C_TX_DMA_IT_2 ((uint32_t)0x00000002)
#define I2C_TX_DMA_IT_3 ((uint32_t)0x00000003)
#define I2C_TX_DMA_IT_4 ((uint32_t)0x00000004)
#define I2C_TX_DMA_IT_5 ((uint32_t)0x00000005)
#define I2C_TX_DMA_IT_6 ((uint32_t)0x00000006)
#define I2C_TX_DMA_IT_7 ((uint32_t)0x00000007)
#define IS_I2C_TX_DMA_IT(TxDMAValue) ((TxDMAValue == I2C_TX_DMA_IT_0) || \
                                      (TxDMAValue == I2C_TX_DMA_IT_1) || \
                                      (TxDMAValue == I2C_TX_DMA_IT_2) || \
                                      (TxDMAValue == I2C_TX_DMA_IT_3) || \
                                      (TxDMAValue == I2C_TX_DMA_IT_4) || \
                                      (TxDMAValue == I2C_TX_DMA_IT_5) || \
                                      (TxDMAValue == I2C_TX_DMA_IT_6) || \
                                      (TxDMAValue == I2C_TX_DMA_IT_7))
// DMA接收数据水平
#define I2C_RX_DMA_IT_0 ((uint32_t)0x00000000)
#define I2C_RX_DMA_IT_1 ((uint32_t)0x00000001)
#define I2C_RX_DMA_IT_2 ((uint32_t)0x00000002)
#define I2C_RX_DMA_IT_3 ((uint32_t)0x00000003)
#define I2C_RX_DMA_IT_4 ((uint32_t)0x00000004)
#define I2C_RX_DMA_IT_5 ((uint32_t)0x00000005)
#define I2C_RX_DMA_IT_6 ((uint32_t)0x00000006)
#define I2C_RX_DMA_IT_7 ((uint32_t)0x00000007)
#define IS_I2C_RX_DMA_IT(RxDMAValue) ((RxDMAValue == I2C_RX_DMA_IT_0) || \
                                      (RxDMAValue == I2C_RX_DMA_IT_1) || \
                                      (RxDMAValue == I2C_RX_DMA_IT_2) || \
                                      (RxDMAValue == I2C_RX_DMA_IT_3) || \
                                      (RxDMAValue == I2C_RX_DMA_IT_4) || \
                                      (RxDMAValue == I2C_RX_DMA_IT_5) || \
                                      (RxDMAValue == I2C_RX_DMA_IT_6) || \
                                      (RxDMAValue == I2C_RX_DMA_IT_7))
/**************************
 * I2C_Register
 * *********************************/
#define I2C_Register_CON ((uint8_t)0x00)
#define I2C_Register_TAR ((uint8_t)0x04)
#define I2C_Register_SAR ((uint8_t)0x08)
#define I2C_Register_HSMADDR ((uint8_t)0x0c)
#define I2C_Register_DATACMD ((uint8_t)0x10)
#define I2C_Register_SSHCNT ((uint8_t)0x14)
#define I2C_Register_SSLCNT ((uint8_t)0x18)
#define I2C_Register_FSHCNT ((uint8_t)0x1C)
#define I2C_Register_FSLCNT ((uint8_t)0x20)
#define I2C_Register_HSHCNT ((uint8_t)0x24)
#define I2C_Register_HSLCNT ((uint8_t)0x28)
#define I2C_Register_INTRSTAT ((uint8_t)0x2c)
#define I2C_Register_INTRMASK ((uint8_t)0x30)
#define I2C_Register_RAWINTRSTAT ((uint8_t)0x34)
#define I2C_Register_RXTL ((uint8_t)0x38)
#define I2C_Register_TXTL ((uint8_t)0x3c)
#define I2C_Register_CLRINTR ((uint8_t)0x40)
#define I2C_Register_CLRRXUNDER ((uint8_t)0x44)
#define I2C_Register_CLRRXOVER ((uint8_t)0x48)
#define I2C_Register_CLRTXOVER ((uint8_t)0x4c)
#define I2C_Register_CLRRDREQ ((uint8_t)0x50)
#define I2C_Register_CLRTXABRT ((uint8_t)0x54)
#define I2C_Register_CLRRXDONE ((uint8_t)0x58)
#define I2C_Register_CLRACTIVITY ((uint8_t)0x5c)
#define I2C_Register_CLRSTOP_DET ((uint8_t)0x60)
#define I2C_Register_CLRSTARTDET ((uint8_t)0x64)
#define I2C_Register_CLRGENCALL ((uint8_t)0x68)
#define I2C_Register_ENABLE ((uint8_t)0x6c)
#define I2C_Register_STATUS ((uint8_t)0x70)
#define I2C_Register_TXFLR ((uint8_t)0x74)
#define I2C_Register_RXFLR ((uint8_t)0x78)
#define I2C_Register_SDAHOLD ((uint8_t)0x7c)
#define I2C_Register_TXABRTSOURCE ((uint8_t)0x80)
#define I2C_Register_SLVDATANACK ((uint8_t)0x84)
#define I2C_Register_DMACR ((uint8_t)0x88)
#define I2C_Register_DMATDLR ((uint8_t)0x8c)
#define I2C_Register_DMARDLR ((uint8_t)0x90)
#define I2C_Register_SDASETUP ((uint8_t)0x94)
#define I2C_Register_ACKGENERALCALL ((uint8_t)0x98)
#define I2C_Register_ENABLESTATUS ((uint8_t)0x9c)
#define I2C_Register_FSSPKLEN ((uint8_t)0xa0)
#define I2C_Register_HSSPKLEN ((uint8_t)0xa4)
#define I2C_Register_CLRRESTARTDET ((uint8_t)0xa8)
#define I2C_Register_COMPPARAM1 ((uint8_t)0xf4)
#define I2C_Register_COMPVERSION ((uint8_t)0xf8)
#define I2C_Register_COMPTYPE ((uint8_t)0xfc)

#define IS_I2C_REGISTER(REGISTER) (((REGISTER) == I2C_Register_CON) ||            \
                                   ((REGISTER) == I2C_Register_TAR) ||            \
                                   ((REGISTER) == I2C_Register_SAR) ||            \
                                   ((REGISTER) == I2C_Register_HSMADDR) ||        \
                                   ((REGISTER) == I2C_Register_DATACMD) ||        \
                                   ((REGISTER) == I2C_Register_SSHCNT) ||         \
                                   ((REGISTER) == I2C_Register_SSLCNT) ||         \
                                   ((REGISTER) == I2C_Register_FSHCNT) ||         \
                                   ((REGISTER) == I2C_Register_FSLCNT) ||         \
                                   ((REGISTER) == I2C_Register_HSHCNT) ||         \
                                   ((REGISTER) == I2C_Register_HSLCNT) ||         \
                                   ((REGISTER) == I2C_Register_INTRSTAT) ||       \
                                   ((REGISTER) == I2C_Register_INTRMASK) ||       \
                                   ((REGISTER) == I2C_Register_RAWINTRSTAT) ||    \
                                   ((REGISTER) == I2C_Register_RXTL) ||           \
                                   ((REGISTER) == I2C_Register_TXTL) ||           \
                                   ((REGISTER) == I2C_Register_CLRINTR) ||        \
                                   ((REGISTER) == I2C_Register_CLRRXUNDER) ||     \
                                   ((REGISTER) == I2C_Register_CLRRXOVER) ||      \
                                   ((REGISTER) == I2C_Register_CLRTXOVER) ||      \
                                   ((REGISTER) == I2C_Register_CLRRDREQ) ||       \
                                   ((REGISTER) == I2C_Register_CLRTXABRT) ||      \
                                   ((REGISTER) == I2C_Register_CLRRXDONE) ||      \
                                   ((REGISTER) == I2C_Register_CLRACTIVITY) ||    \
                                   ((REGISTER) == I2C_Register_CLRSTOP_DET) ||    \
                                   ((REGISTER) == I2C_Register_CLRSTARTDET) ||    \
                                   ((REGISTER) == I2C_Register_CLRGENCALL) ||     \
                                   ((REGISTER) == I2C_Register_ENABLE) ||         \
                                   ((REGISTER) == I2C_Register_STATUS) ||         \
                                   ((REGISTER) == I2C_Register_TXFLR) ||          \
                                   ((REGISTER) == I2C_Register_RXFLR) ||          \
                                   ((REGISTER) == I2C_Register_SDAHOLD) ||        \
                                   ((REGISTER) == I2C_Register_TXABRTSOURCE) ||   \
                                   ((REGISTER) == I2C_Register_SLVDATANACK) ||    \
                                   ((REGISTER) == I2C_Register_DMACR) ||          \
                                   ((REGISTER) == I2C_Register_DMATDLR) ||        \
                                   ((REGISTER) == I2C_Register_DMARDLR) ||        \
                                   ((REGISTER) == I2C_Register_SDASETUP) ||       \
                                   ((REGISTER) == I2C_Register_ACKGENERALCALL) || \
                                   ((REGISTER) == I2C_Register_ENABLESTATUS) ||   \
                                   ((REGISTER) == I2C_Register_FSSPKLEN) ||       \
                                   ((REGISTER) == I2C_Register_HSSPKLEN) ||       \
                                   ((REGISTER) == I2C_Register_CLRRESTARTDET) ||  \
                                   ((REGISTER) == I2C_Register_COMPPARAM1) ||     \
                                   ((REGISTER) == I2C_Register_COMPVERSION) ||    \
                                   ((REGISTER) == I2C_Register_COMPTYPE))

/** @defgroup I2C_IT
 * @{
 */
#define I2C_IT_MST_ON_HOLD I2C_INTR_MST_ON_HOLD_Msk
#define I2C_IT_RESTART_DET I2C_INTR_RESTART_DET_Msk
#define I2C_IT_GEN_CALL I2C_INTR_GEN_CALL_Msk
#define I2C_IT_START_DET I2C_INTR_START_DET_Msk
#define I2C_IT_STOP_DET I2C_INTR_STOP_DET_Msk
#define I2C_IT_ACTIVITY I2C_INTR_ACTIVITY_Msk
#define I2C_IT_RX_DONE I2C_INTR_RX_DONE_Msk
#define I2C_IT_TX_ABRT I2C_INTR_TX_ABRT_Msk
#define I2C_IT_RD_REQ I2C_INTR_RD_REQ_Msk
#define I2C_IT_TX_EMPTY I2C_INTR_TX_EMPTY_Msk
#define I2C_IT_TX_OVER I2C_INTR_TX_OVER_Msk
#define I2C_IT_RX_FULL I2C_INTR_RX_FULL_Msk
#define I2C_IT_RX_OVER I2C_INTR_RX_OVER_Msk
#define I2C_IT_RX_UNDER I2C_INTR_RX_UNDER_Msk
#define I2C_IT_ALL (uint32_t)(0x3FFF)

#define IS_I2C_GET_IT(I2C_IT) (((I2C_IT) == I2C_IT_MST_ON_HOLD) || \
                               ((I2C_IT) == I2C_IT_RESTART_DET) || \
                               ((I2C_IT) == I2C_IT_GEN_CALL) ||    \
                               ((I2C_IT) == I2C_IT_START_DET) ||   \
                               ((I2C_IT) == I2C_IT_STOP_DET) ||    \
                               ((I2C_IT) == I2C_IT_ACTIVITY) ||    \
                               ((I2C_IT) == I2C_IT_RX_DONE) ||     \
                               ((I2C_IT) == I2C_IT_TX_ABRT) ||     \
                               ((I2C_IT) == I2C_IT_RD_REQ) ||      \
                               ((I2C_IT) == I2C_IT_TX_EMPTY) ||    \
                               ((I2C_IT) == I2C_IT_TX_OVER) ||     \
                               ((I2C_IT) == I2C_IT_RX_FULL) ||     \
                               ((I2C_IT) == I2C_IT_RX_OVER) ||     \
                               ((I2C_IT) == I2C_IT_RX_UNDER) ||    \
                               ((I2C_IT) == I2C_IT_ALL))

/** @defgroup I2C_RAW_INTR_STAT
 * @{
 */
#define I2C_FLAG_MST_ON_HOLD I2C_INTR_MST_ON_HOLD_Msk
#define I2C_FLAG_RESTART_DET I2C_INTR_RESTART_DET_Msk
#define I2C_FLAG_GEN_CALL I2C_INTR_GEN_CALL_Msk
#define I2C_FLAG_START_DET I2C_INTR_START_DET_Msk
#define I2C_FLAG_STOP_DET I2C_INTR_STOP_DET_Msk
#define I2C_FLAG_ACTIVITY I2C_INTR_ACTIVITY_Msk
#define I2C_FLAG_RX_DONE I2C_INTR_RX_DONE_Msk
#define I2C_FLAG_TX_ABRT I2C_INTR_TX_ABRT_Msk
#define I2C_FLAG_RD_REQ I2C_INTR_RD_REQ_Msk
#define I2C_FLAG_TX_EMPTY I2C_INTR_TX_EMPTY_Msk
#define I2C_FLAG_TX_OVER I2C_INTR_TX_OVER_Msk
#define I2C_FLAG_RX_FULL I2C_INTR_RX_FULL_Msk
#define I2C_FLAG_RX_OVER I2C_INTR_RX_OVER_Msk
#define I2C_FLAG_RX_UNDER I2C_INTR_RX_UNDER_Msk

#define IS_I2C_GET_FLAG(I2C_FLAG) (((I2C_FLAG) == I2C_FLAG_MST_ON_HOLD) || \
                                   ((I2C_FLAG) == I2C_FLAG_RESTART_DET) || \
                                   ((I2C_FLAG) == I2C_FLAG_GEN_CALL) ||    \
                                   ((I2C_FLAG) == I2C_FLAG_START_DET) ||   \
                                   ((I2C_FLAG) == I2C_FLAG_STOP_DET) ||    \
                                   ((I2C_FLAG) == I2C_FLAG_ACTIVITY) ||    \
                                   ((I2C_FLAG) == I2C_FLAG_RX_DONE) ||     \
                                   ((I2C_FLAG) == I2C_FLAG_TX_ABRT) ||     \
                                   ((I2C_FLAG) == I2C_FLAG_RD_REQ) ||      \
                                   ((I2C_FLAG) == I2C_FLAG_TX_EMPTY) ||    \
                                   ((I2C_FLAG) == I2C_FLAG_TX_OVER) ||     \
                                   ((I2C_FLAG) == I2C_FLAG_RX_FULL) ||     \
                                   ((I2C_FLAG) == I2C_FLAG_RX_OVER) ||     \
                                   ((I2C_FLAG) == I2C_FLAG_RX_UNDER))

/** @defgroup I2C_STATUS
 * @{
 */

#define I2C_STATUS_SLV_HOLD_RXFIFO_FULL I2C_STATUS_SHRFF_Msk
#define I2C_STATUS_SLV_HOLD_TXFIFO_EMPTY I2C_STATUS_SHTFE_Msk
#define I2C_STATUS_MST_HOLD_RXFIFO_FULL I2C_STATUS_MHRFF_Msk
#define I2C_STATUS_MST_HOLD_TXFIFO_EMPTY I2C_STATUS_MHRFE_Msk
#define I2C_STATUS_SLV_ACTIVITY I2C_STATUS_SLV_ACT_Msk
#define I2C_STATUS_MST_ACTIVITY I2C_STATUS_MST_ACT_Msk
#define I2C_STATUS_RFF I2C_STATUS_RFF_Msk
#define I2C_STATUS_RFNF I2C_STATUS_RFNF_Msk
#define I2C_STATUS_TFE I2C_STATUS_TFE_Msk
#define I2C_STATUS_TFNF I2C_STATUS_TFNF_Msk
#define I2C_STATUS_ACTIVITY I2C_STATUS_ACTIVITY_Msk

#define IS_I2C_GET_STATUS(STATUS) (((STATUS) == I2C_STATUS_SLV_HOLD_RXFIFO_FULL) ||  \
                                   ((STATUS) == I2C_STATUS_SLV_HOLD_TXFIFO_EMPTY) || \
                                   ((STATUS) == I2C_STATUS_MST_HOLD_RXFIFO_FULL) ||  \
                                   ((STATUS) == I2C_STATUS_MST_HOLD_TXFIFO_EMPTY) || \
                                   ((STATUS) == I2C_STATUS_SLV_ACTIVITY) ||          \
                                   ((STATUS) == I2C_STATUS_MST_ACTIVITY) ||          \
                                   ((STATUS) == I2C_STATUS_RFF) ||                   \
                                   ((STATUS) == I2C_STATUS_RFNF) ||                  \
                                   ((STATUS) == I2C_STATUS_TFE) ||                   \
                                   ((STATUS) == I2C_STATUS_RFNE) ||                  \
                                   ((STATUS) == I2C_STATUS_TFNF) ||                  \
                                   ((STATUS) == I2C_STATUS_ACTIVITY))

/**
 * @}
 */
#define IS_I2C_ALL_PERIPH(PERIPH)  (PERIPH) == I2C0)

/****************** Bit Definition for II2C I2C_CON Register **************/
#define I2C_CON_SDIMA_Pos 10
#define I2C_CON_SDIMA_Msk (0x1UL << I2C_CON_SDIMA_Pos)
#define I2C_CON_RFFHC_Pos 9
#define I2C_CON_RFFHC_Msk (0x1UL << I2C_CON_RFFHC_Pos)
#define I2C_CON_TXEC_Pos 8
#define I2C_CON_TXEC_Msk (0x1UL << I2C_CON_TXEC_Pos)
#define I2C_CON_SDIAD_Pos 7
#define I2C_CON_SDIAD_Msk (0x1UL << I2C_CON_SDIAD_Pos)
#define I2C_CON_SLV_DISAB_Pos 6
#define I2C_CON_SLV_DISAB_Msk (0x1UL << I2C_CON_SLV_DISAB_Pos)
#define I2C_SLV_DISABLE (0x1UL << I2C_CON_SLV_DISAB_Pos)
#define I2C_SLV_ENABLE (0x0UL << I2C_CON_SLV_DISAB_Pos)
#define I2C_CON_RESTEN_Pos 5
#define I2C_CON_RESTEN_Msk (0x1UL << I2C_CON_RESTEN_Pos)
#define I2C_CON_RESTEN_OFF (0x0UL << I2C_CON_RESTEN_Pos)
#define I2C_CON_RESTEN_ON (0x1UL << I2C_CON_RESTEN_Pos)
#define I2C_CON_10ADDR_MAS_Pos 4
#define I2C_CON_10ADDR_MAS_Msk (0x1UL << I2C_CON_10ADDR_MAS_Pos)
#define I2C_CON_10ADDR_MAS_OFF (0x0UL << I2C_CON_10ADDR_MAS_Pos)
#define I2C_CON_10ADDR_MAS_ON (0x1UL << I2C_CON_10ADDR_MAS_Pos)
#define I2C_CON_10ADDR_SLV_Pos 3
#define I2C_CON_10ADDR_SLV_Msk (0x1UL << I2C_CON_10ADDR_SLV_Pos)
#define I2C_CON_10ADDR_SLV_OFF (0x0UL << I2C_CON_10ADDR_SLV_Pos)
#define I2C_CON_10ADDR_SLV_ON (0x1UL << I2C_CON_10ADDR_SLV_Pos)
#define I2C_CON_SPEED_Pos 1
#define I2C_CON_SPEED_Msk (0x3UL << I2C_CON_SPEED_Pos)
#define I2C_CON_SPEED_STAD 1 //(0x1UL << I2C_CON_SPEED_Pos)
#define I2C_CON_SPEED_FAST 2 //(0x2UL << I2C_CON_SPEED_Pos)
#define I2C_CON_SPEED_HIGH 3 //(0x3UL << I2C_CON_SPEED_Pos)
#define I2C_CON_MST_MODE_Pos 0
#define I2C_CON_MST_MODE_Msk (0x1UL << I2C_CON_MST_MODE_Pos)
#define I2C_CON_MST_MODE_OFF (0x0UL << I2C_CON_MST_MODE_Pos)
#define I2C_CON_MST_MODE_ON (0x1UL << I2C_CON_MST_MODE_Pos)

/****************** Bit Definition for II2C I2C_TAR Register **************/
#define I2C_TAR_10ADDR_MAS_Pos 12
#define I2C_TAR_10ADDR_MAS_Msk (0x1UL << I2C_TAR_10ADDR_MAS_Pos)
#define I2C_TAR_ADD10 I2C_TAR_10ADDR_MAS_Msk
#define I2C_TAR_7ADDR_MAS (0x0UL << I2C_TAR_10ADDR_MAS_Pos)
#define I2C_TAR_10ADDR_MAS (0x1UL << I2C_TAR_10ADDR_MAS_Pos)
#define I2C_TAR_SPECIAL_Pos 11
#define I2C_TAR_SPECIAL_Msk (0x1UL << I2C_TAR_SPECIAL_Pos)
#define I2C_TAR_SPECIAL_OFF (0x0UL << I2C_TAR_SPECIAL_Pos)
#define I2C_TAR_SPECIAL_ON (0x1UL << I2C_TAR_SPECIAL_Pos)

#define I2C_TAR_GC_START_Pos 10
#define I2C_TAR_GC_START_Msk (0x1UL << I2C_TAR_GC_START_Pos)
#define I2C_TAR_GC_START_OFF (0x0UL << I2C_TAR_GC_START_Pos)
#define I2C_TAR_GC_START_ON (0x1UL << I2C_TAR_GC_START_Pos)

#define I2C_TAR_TAR_Pos 0
#define I2C_TAR_TAR_Msk (0x3FFUL << I2C_TAR_TAR_Pos)

/****************** Bit Definition for II2C I2C_SAR Register **************/
#define I2C_SAR_SAR_Pos 0
#define I2C_SAR_SAR_Msk (0x1FUL << I2C_SAR_SAR_Pos)

/****************** Bit Definition for II2C I2C_HS_MADDR Register **********/
#define I2C_HS_MAR_Pos 0
#define I2C_HS_MAR_Msk (0x1UL << I2C_HS_MAR_Pos)

/****************** Bit Definition for II2C I2C_DATA_CMD Register ********/
#define I2C_DATA_CMD_FDB_Pos 11
#define I2C_DATA_CMD_FDB_Msk (0x1UL << I2C_DATA_CMD_FDB_Pos)
#define I2C_DATA_CMD_RESTA_Pos 10
#define I2C_DATA_CMD_RESTA_Msk (0x1UL << I2C_DATA_CMD_RESTA_Pos)
#define I2C_DATA_CMD_STOP_Pos 9
#define I2C_DATA_CMD_STOP_Msk (0x1UL << I2C_DATA_CMD_STOP_Pos)
#define I2C_DATA_STOP_0 (0x0UL << I2C_DATA_CMD_STOP_Pos)
#define I2C_DATA_STOP_1 (0x1UL << I2C_DATA_CMD_STOP_Pos)
#define I2C_DATA_CMD_CMD_Pos 8
#define I2C_DATA_CMD_CMD_Msk (0x1UL << I2C_DATA_CMD_CMD_Pos)
#define I2C_DATA_CMD_WR (0x0UL << I2C_DATA_CMD_CMD_Pos)
#define I2C_DATA_CMD_RD (0x1UL << I2C_DATA_CMD_CMD_Pos)
#define I2C_DATA_DAT_Pos 0
#define I2C_DATA_DAT_Msk (0xFF << I2C_DATA_DAT_Pos)

/****************** Bit Definition for II2C I2C_SS_SCL_HCNT Register **************/
#define I2C_SS_SCL_HCNT_Pos 0
#define I2C_SS_SCL_HCNT_Msk (0xFFFFUL << I2C_SS_SCL_HCNT_Pos)

/****************** Bit Definition for II2C I2C_SS_SCL_LCNT Register **************/
#define I2C_SS_SCL_LCNT_Pos 0
#define I2C_SS_SCL_LCNT_Msk (0xFFFFUL << I2C_SS_SCL_LCNT_Pos)

/****************** Bit Definition for II2C I2C_FS_SCL_HCNT Register **************/
#define I2C_FS_SCL_HCNT_Pos 0
#define I2C_FS_SCL_HCNT_Msk (0xFFFFUL << I2C_FS_SCL_HCNT_Pos)

/****************** Bit Definition for II2C I2C_FS_SCL_LCNT Register **************/
#define I2C_FS_SCL_LCNT_Pos 0
#define I2C_FS_SCL_LCNT_Msk (0xFFFFUL << I2C_FS_SCL_LCNT_Pos)

/****************** Bit Definition for II2C I2C_HS_SCL_HCNT Register **************/
#define I2C_HS_SCL_HCNT_Pos 0
#define I2C_HS_SCL_HCNT_Msk (0xFFFFUL << I2C_HS_SCL_HCNT_Pos)

/****************** Bit Definition for II2C I2C_HS_SCL_LCNT Register **************/
#define I2C_HS_SCL_LCNT_Pos 0
#define I2C_HS_SCL_LCNT_Msk (0xFFFFUL << I2C_HS_SCL_LCNT_Pos)

/****************** Bit Definition for II2C I2C_INTR_STAT Register **************/
#define I2C_INTR_R_MST_ON_HOLD_Pos 13
#define I2C_INTR_R_MST_ON_HOLD_Msk (0x1UL << I2C_INTR_R_MST_ON_HOLD_Pos)
#define I2C_INTR_R_RESTART_DET_Pos 12
#define I2C_INTR_R_RESTART_DET_Msk (0x1UL << I2C_INTR_R_RESTART_DET_Pos)
#define I2C_INTR_R_GEN_CALL_Pos 11
#define I2C_INTR_R_GEN_CALL_Msk (0x1UL << I2C_INTR_R_GEN_CALL_Pos)
#define I2C_INTR_R_START_DET_Pos 10
#define I2C_INTR_R_START_DET_Msk (0x1UL << I2C_INTR_R_START_DET_Pos)
#define I2C_INTR_R_STOP_DET_Pos 9
#define I2C_INTR_R_STOP_DET_Msk (0x1UL << I2C_INTR_R_STOP_DET_Pos)
#define I2C_INTR_R_ACTIVITY_Pos 8
#define I2C_INTR_R_ACTIVITY_Msk (0x1UL << I2C_INTR_R_ACTIVITY_Pos)
#define I2C_INTR_R_RX_DONE_Pos 7
#define I2C_INTR_R_RX_DONE_Msk (0x1UL << I2C_INTR_R_RX_DONE_Pos)
#define I2C_INTR_R_TX_ABRT_Pos 6
#define I2C_INTR_R_TX_ABRT_Msk (0x1UL << I2C_INTR_R_TX_ABRT_Pos)
#define I2C_INTR_R_RD_REQ_Pos 5
#define I2C_INTR_R_RD_REQ_Msk (0x1UL << I2C_INTR_R_RD_REQ_Pos)
#define I2C_INTR_R_TX_EMPTY_Pos 4
#define I2C_INTR_R_TX_EMPTY_Msk (0x1UL << I2C_INTR_R_TX_EMPTY_Pos)
#define I2C_INTR_R_TX_OVER_Pos 3
#define I2C_INTR_R_TX_OVER_Msk (0x1UL << I2C_INTR_R_TX_OVER_Pos)
#define I2C_INTR_R_RX_FULL_Pos 2
#define I2C_INTR_R_RX_FULL_Msk (0x1UL << I2C_INTR_R_RX_FULL_Pos)
#define I2C_INTR_R_RX_OVER_Pos 1
#define I2C_INTR_R_RX_OVER_Msk (0x1UL << I2C_INTR_R_RX_OVER_Pos)
#define I2C_INTR_R_RX_UNDER_Pos 0
#define I2C_INTR_R_RX_UNDER_Msk (0x1UL << I2C_INTR_R_RX_UNDER_Pos)

/****************** Bit Definition for II2C I2C_INTR_MASK Register **************/
#define I2C_INTR_M_MST_ON_HOLD_Pos 13
#define I2C_INTR_M_MST_ON_HOLD_Msk (0x1UL << I2C_INTR_M_MST_ON_HOLD_Pos)
#define I2C_INTR_M_RESTART_DET_Pos 12
#define I2C_INTR_M_RESTART_DET_Msk (0x1UL << I2C_INTR_M_RESTART_DET_Pos)
#define I2C_INTR_M_GEN_CALL_Pos 11
#define I2C_INTR_M_GEN_CALL_Msk (0x1UL << I2C_INTR_M_GEN_CALL_Pos)
#define I2C_INTR_M_START_DET_Pos 10
#define I2C_INTR_M_START_DET_Msk (0x1UL << I2C_INTR_M_START_DET_Pos)
#define I2C_INTR_M_STOP_DET_Pos 9
#define I2C_INTR_M_STOP_DET_Msk (0x1UL << I2C_INTR_M_STOP_DET_Pos)
#define I2C_INTR_M_ACTIVITY_Pos 8
#define I2C_INTR_M_ACTIVITY_Msk (0x1UL << I2C_INTR_M_ACTIVITY_Pos)
#define I2C_INTR_M_RX_DONE_Pos 7
#define I2C_INTR_M_RX_DONE_Msk (0x1UL << I2C_INTR_M_RX_DONE_Pos)
#define I2C_INTR_M_TX_ABRT_Pos 6
#define I2C_INTR_M_TX_ABRT_Msk (0x1UL << I2C_INTR_M_TX_ABRT_Pos)
#define I2C_INTR_M_RD_REQ_Pos 5
#define I2C_INTR_M_RD_REQ_Msk (0x1UL << I2C_INTR_M_RD_REQ_Pos)
#define I2C_INTR_M_TX_EMPTY_Pos 4
#define I2C_INTR_M_TX_EMPTY_Msk (0x1UL << I2C_INTR_M_TX_EMPTY_Pos)
#define I2C_INTR_M_TX_OVER_Pos 3
#define I2C_INTR_M_TX_OVER_Msk (0x1UL << I2C_INTR_M_TX_OVER_Pos)
#define I2C_INTR_M_RX_FULL_Pos 2
#define I2C_INTR_M_RX_FULL_Msk (0x1UL << I2C_INTR_M_RX_FULL_Pos)
#define I2C_INTR_M_RX_OVER_Pos 1
#define I2C_INTR_M_RX_OVER_Msk (0x1UL << I2C_INTR_M_RX_OVER_Pos)
#define I2C_INTR_M_RX_UNDER_Pos 0
#define I2C_INTR_M_RX_UNDER_Msk (0x1UL << I2C_INTR_M_RX_UNDER_Pos)

/****************** Bit Definition for II2C I2C_RAW_INTR_STAT Register **************/
#define I2C_INTR_MST_ON_HOLD_Pos 13
#define I2C_INTR_MST_ON_HOLD_Msk (0x1UL << I2C_INTR_MST_ON_HOLD_Pos)
#define I2C_INTR_RESTART_DET_Pos 12
#define I2C_INTR_RESTART_DET_Msk (0x1UL << I2C_INTR_RESTART_DET_Pos)
#define I2C_INTR_GEN_CALL_Pos 11
#define I2C_INTR_GEN_CALL_Msk (0x1UL << I2C_INTR_GEN_CALL_Pos)
#define I2C_INTR_START_DET_Pos 10
#define I2C_INTR_START_DET_Msk (0x1UL << I2C_INTR_START_DET_Pos)
#define I2C_INTR_STOP_DET_Pos 9
#define I2C_INTR_STOP_DET_Msk (0x1UL << I2C_INTR_STOP_DET_Pos)
#define I2C_INTR_ACTIVITY_Pos 8
#define I2C_INTR_ACTIVITY_Msk (0x1UL << I2C_INTR_ACTIVITY_Pos)
#define I2C_INTR_RX_DONE_Pos 7
#define I2C_INTR_RX_DONE_Msk (0x1UL << I2C_INTR_RX_DONE_Pos)
#define I2C_INTR_TX_ABRT_Pos 6
#define I2C_INTR_TX_ABRT_Msk (0x1UL << I2C_INTR_TX_ABRT_Pos)
#define I2C_INTR_RD_REQ_Pos 5
#define I2C_INTR_RD_REQ_Msk (0x1UL << I2C_INTR_RD_REQ_Pos)
#define I2C_INTR_TX_EMPTY_Pos 4
#define I2C_INTR_TX_EMPTY_Msk (0x1UL << I2C_INTR_TX_EMPTY_Pos)
#define I2C_INTR_TX_OVER_Pos 3
#define I2C_INTR_TX_OVER_Msk (0x1UL << I2C_INTR_TX_OVER_Pos)
#define I2C_INTR_RX_FULL_Pos 2
#define I2C_INTR_RX_FULL_Msk (0x1UL << I2C_INTR_RX_FULL_Pos)
#define I2C_INTR_RX_OVER_Pos 1
#define I2C_INTR_RX_OVER_Msk (0x1UL << I2C_INTR_RX_OVER_Pos)
#define I2C_INTR_RX_UNDER_Pos 0
#define I2C_INTR_RX_UNDER_Msk (0x1UL << I2C_INTR_RX_UNDER_Pos)

/****************** Bit Definition for II2C I2C_RX_TL Register **************/
#define I2C_RX_TL_Pos 0
#define I2C_RX_TL_Msk (0xFFUL << I2C_RX_TL_Pos)

/****************** Bit Definition for II2C I2C_TX_TL Register **************/
#define I2C_TX_TL_Pos 0
#define I2C_TX_TL_Msk (0xFFUL << I2C_TX_TL_Pos)

/****************** Bit Definition for II2C I2C_CLR_INTR Register **************/
#define I2C_CLR_INTR_Pos 0
#define I2C_CLR_INTR_Msk (0x1UL << I2C_CLR_INTR_Pos)

/****************** Bit Definition for II2C I2C_CLR_RX_UNDER Register **************/
#define I2C_CLR_RX_UNDER_Pos 0
#define I2C_CLR_RX_UNDER_Msk (0x1UL << I2C_CLR_RX_UNDER_Pos)

/****************** Bit Definition for II2C I2C_CLR_RX_OVER Register **************/
#define I2C_CLR_RX_OVER_Pos 0
#define I2C_CLR_RX_OVER_Msk (0x1UL << I2C_CLR_RX_OVER_Pos)

/****************** Bit Definition for II2C I2C_CLR_TX_OVER Register **************/
#define I2C_CLR_TX_OVER_Pos 0
#define I2C_CLR_TX_OVER_Msk (0x1UL << I2C_CLR_TX_OVER_Pos)

/****************** Bit Definition for II2C I2C_CLR_RD_REQ Register **************/
#define I2C_CLR_RD_REQ_Pos 0
#define I2C_CLR_RD_REQ_Msk (0x1UL << I2C_CLR_RD_REQ_Pos)

/****************** Bit Definition for II2C I2C_CLR_TX_ABRT Register **************/
#define I2C_CLR_ABRT_Pos 0
#define I2C_CLR_ABRT_Msk (0x1UL << I2C_CLR_ABRT_Pos)

/****************** Bit Definition for II2C I2C_CLR_RX_DONE Register **************/
#define I2C_CLR_RX_DONE_Pos 0
#define I2C_CLR_RX_DONE_Msk (0x1UL << I2C_CLR_RX_DONE_Pos)

/****************** Bit Definition for II2C I2C_CLR_RX_ACTIVITY Register *********/
#define I2C_CLR_ACTIVITY_Pos 0
#define I2C_CLR_ACTIVITY_Msk (0x1UL << I2C_CLR_ACTIVITY_Pos)

/****************** Bit Definition for II2C I2C_CLR_STOP Register **************/
#define I2C_CLR_STOP_DET_Pos 0
#define I2C_CLR_STOP_DET_Msk (0x1UL << I2C_CLR_STOP_DET_Pos)

/****************** Bit Definition for II2C I2C_CLR_START_DET Register *********/
#define I2C_CLR_START_DET_Pos 0
#define I2C_CLR_START_DET_Msk (0X1UL << I2C_CLR_START_DET_Pos)

/****************** Bit Definition for II2C I2C_CLR_GEN_CALL Register **********/
#define I2C_CLR_GEN_CALL_Pos 0
#define I2C_CLR_GEN_CALL_Msk (0x1UL << I2C_CLR_GEN_CALL_Pos)

/****************** Bit Definition for II2C I2C_ENABLE Register **************/
#define I2C_ENABLE_TX_CMD_Pos 2
#define I2C_ENABLE_TX_CMD_Msk (0x1UL << I2C_ENABLE_TX_CMD_Pos)
#define I2C_ENABLE_ABORT_Pos 1
#define I2C_ENABLE_ABORT_Msk (0x1UL << I2C_ENABLE_ABORT_Pos)
#define I2C_ENBALE_Pos 0
#define I2C_ENABLE_Msk (0x1UL << I2C_ENBALE_Pos)
#define I2C_ENABLE_ON (0X1UL << I2C_ENST_EN_Pos)
#define I2C_ENABLE_OFF (0X0UL << I2C_ENST_EN_Pos)

/****************** Bit Definition for II2C I2C_STATUS Register **************/
#define I2C_STATUS_SHRFF_Pos 10
#define I2C_STATUS_SHRFF_Msk (0x1UL << I2C_STATUS_SHRFF_Pos)
#define I2C_STATUS_SHTFE_Pos 9
#define I2C_STATUS_SHTFE_Msk (0x1UL << I2C_STATUS_SHTFE_Pos)
#define I2C_STATUS_MHRFF_Pos 8
#define I2C_STATUS_MHRFF_Msk (0x1UL << I2C_STATUS_MHRFF_Pos)
#define I2C_STATUS_MHRFE_Pos 7
#define I2C_STATUS_MHRFE_Msk (0X1UL << I2C_STATUS_MHRFE_Pos)
#define I2C_STATUS_SLV_ACT_Pos 6
#define I2C_STATUS_SLV_ACT_Msk (0x1UL << I2C_STATUS_SLV_ACT_Pos)
#define I2C_STATUS_MST_ACT_Pos 5
#define I2C_STATUS_MST_ACT_Msk (0x1UL << I2C_STATUS_MST_ACT_Pos)
#define I2C_STATUS_RFF_Pos 4
#define I2C_STATUS_RFF_Msk (0x1UL << I2C_STATUS_RFF_Pos)
#define I2C_STATUS_RFNF_Pos 3
#define I2C_STATUS_RFNF_Msk (0x1UL << I2C_STATUS_RFNF_Pos)
#define I2C_STATUS_TFE_Pos 2
#define I2C_STATUS_TFE_Msk (0x1UL << I2C_STATUS_TFE_Pos)
#define I2C_STATUS_TFNF_Pos 1
#define I2C_STATUS_TFNF_Msk (0x1UL << I2C_STATUS_TFNF_Pos)
#define I2C_STATUS_ACTIVITY_Pos 0
#define I2C_STATUS_ACTIVITY_Msk (0x1UL << I2C_STATUS_ACTIVITY_Pos)

/****************** Bit Definition for II2C I2C_TXFLR Register **************/

/****************** Bit Definition for II2C I2C_RXFLR Register **************/

/****************** Bit Definition for II2C I2C_SDA_HOLD Register **********/
#define I2C_SDA_RX_HOLD_Pos 16
#define I2C_SDA_RX_HOLD_Msk (0xFF << I2C_SDA_RX_HOLD_Pos)
#define I2C_SDA_TX_HOLD_Pos 0
#define I2C_SDA_TX_HOLD_Msk (0xFFFF << I2C_SDA_TX_HOLD_Pos)

/****************** Bit Definition for II2C I2C_TX_ABRT_SOURCE Register ****/
#define I2C_TAS_TFC_Pos 23
#define I2C_TAS_TFC_Msk (0xFF << I2C_TAS_TFC_Pos)
#define I2C_TAS_AUA_Pos 16
#define I2C_TAS_AUA_Msk (0x1UL << I2C_TAS_AUA_Pos)
#define I2C_TAS_ASI_Pos 15
#define I2C_TAS_ASI_Msk (0x1UL << I2C_TAS_ASI_Pos)
#define I2C_TAS_ASLA_Pos 14
#define I2C_TAS_ASLA_Msk (0x1UL << I2C_TAS_ASLA_Pos)
#define I2C_TAS_ASFT_Pos 13
#define I2C_TAS_ASFT_Msk (0x1UL << I2C_TAS_ASFT_Pos)
#define I2C_TAS_ARB_LOST_Pos 12
#define I2C_TAS_ARB_LOST_Msk (0x1UL << I2C_TAS_ARB_LOST_Pos)
#define I2C_TAS_AMD_Pos 11
#define I2C_TAS_AMD_Msk (0x1UL << I2C_TAS_AMD_Pos)
#define I2C_TAS_A10BRN_Pos 10
#define I2C_TAS_A10BRN_Msk (0x1UL << I2C_TAS_A10BRN_Pos)
#define I2C_TAS_ASN_Pos 9
#define I2C_TAS_ASN_Msk (0x1UL << I2C_TAS_ASN_Pos)
#define I2C_TAS_AHN_Pos 8
#define I2C_TAS_AHN_Msk (0x1UL << I2C_TAS_AHN_Pos)
#define I2C_TAS_ASBA_Pos 7
#define I2C_TAS_ASBA_Msk (0x1UL << I2C_TAS_ASBA_Pos)
#define I2C_TAS_AHSA_Pos 6
#define I2C_TAS_AHSA_Msk (0x1UL << I2C_TAS_AHSA_Pos)
#define I2C_TAS_AGR_Pos 5
#define I2C_TAS_AGR_Msk (0x1UL << I2C_TAS_AGR_Pos)
#define I2C_TAS_AGN_Pos 4
#define I2C_TAS_AGN_Msk (0x1UL << I2C_TAS_AGN_Pos)
#define I2C_TAS_ATXN_Pos 3
#define I2C_TAS_ATXN_Msk (0x1UL << I2C_TAS_ATXN_Pos)
#define I2C_TAS_A10ADDR2N_Pos 2
#define I2C_TAS_A10ADDR2N_Msk (0x1UL << I2C_TAS_A10ADDR2N_Pos)
#define I2C_TAS_A10ADDR1N_Pos 1
#define I2C_TAS_A10ADDR1N_Msk (0x1UL << I2C_TAS_A10ADDR1N_Pos)
#define I2C_TAS_A7ADDRN_Pos 0
#define I2C_TAS_A7ADDRN_Msk (0x1UL << I2C_TAS_A7ADDRN_Pos)

/****************** Bit Definition for II2C I2C_SLV_DATA_NACK_ONLY Register *******/
#define I2C_SLV_DATA_NACK_Pos 0
#define I2C_SLV_DATA_NACK_Msk (0x1UL << I2C_SLV_DATA_NACK_Pos)

/****************** Bit Definition for II2C I2C_DMA_CR Register **************/
#define I2C_DMA_CR_TDME_Pos 1
#define I2C_DMA_CR_TDME_MSk (0x1UL << I2C_DMA_CR_TDME_Pos)
#define I2C_DMA_CR_RDME_Pos 0
#define I2C_DMA_CR_RDME_Msk (0x1UL << I2C_DMA_CR_RDME_Pos)

/****************** Bit Definition for II2C I2C_DMA_TDLR Register **************/

/****************** Bit Definition for II2C I2C_DMA_RDLR Register **************/

/****************** Bit Definition for II2C I2C_SDA_SETUP Register **************/
#define I2C_SDA_SETUP_Pos 0
#define I2C_SDA_SETUP_Msk (0xFFUL << I2C_SDA_SETUP_Pos)

/****************** Bit Definition for II2C I2C_ACK_GENERAL Register ************/
#define I2C_ACK_GEN_CALL_Pos 0
#define I2C_ACK_GEN_CALL_Msk (0x01UL << I2C_ACK_GEN_CALL_Pos)
#define I2C_ACK_GEN_CALL_ENABLE (0x01UL << I2C_ACK_GEN_CALL_Pos)

/****************** Bit Definition for II2C I2C_ENABLE_STATUS Register **********/
#define I2C_ENST_SLVRDL_Pos 2
#define I2C_ENST_SLVRDL_Msk (0x1UL << I2C_ENST_SLVRDL_Pos)
#define I2C_ENST_SLVDISWB_Pos 1
#define I2C_ENST_SLVDISWB_Msk (0x1UL << I2C_ENST_SLVDISWB_Pos)
#define I2C_ENST_EN_Pos 0
#define I2C_ENST_EN_Msk (0x1UL << I2C_ENST_EN_Pos) I2C_COMP_TYPE_Pos

/****************** Bit Definition for II2C I2C_FS_SPKLEN Register **************/
#define I2C_FS_SPKLEN_Pos 0
#define I2C_FS_SPKLEN_Msk (0x1UL << I2C_FS_SPKLEN_Pos)

/****************** Bit Definition for II2C I2C_HS_SPKLEN Register **************/
#define I2C_HS_SPKLEN_Pos 0
#define I2C_HS_SPKLEN_Msk (0x1UL << I2C_HS_SPKLEN_Pos)

/****************** Bit Definition for II2C I2C_CLR_RESTART_DET Register ***********/
#define I2C_CLR_RESTART_DET_Pos 0
#define I2C_CLR_RESTART_DET_Msk (0x1UL << I2C_CLR_RESTART_DET_Pos)

/****************** Bit Definition for II2C I2C_COMP_PARAM1 Register **************/
#define I2C_COMP_TX_BUFF_DEPTH_Pos 16
#define I2C_COMP_TX_BUFF_DEPTH_Msk (0xFFUL << I2C_COMP_TX_BUFF_DEPTH_Pos)
#define I2C_COMP_RX_BUFF_DEPTH_Pos 8
#define I2C_COMP_RX_BUFF_DEPTH_Msk (0xFFUL << I2C_COMP_RX_BUFF_DEPTH_Pos)
#define I2C_COMP_ADDEP_Pos 7
#define I2C_COMP_ADDEP_Msk (0x1UL << I2C_COMP_ADDEP_Pos)
#define I2C_COMP_HAS_DMA_Pos 6
#define I2C_COMP_HAS_DMA_Msk (0x1UL << I2C_COMP_HAS_DMA_Pos)
#define I2C_COMP_INTR_IO_Pos 5
#define I2C_COMP_INTR_IO_Msk (0x1UL << I2C_COMP_INTR_IO_Pos)
#define I2C_COMP_HCV_Pos 4
#define I2C_COMP_HCV_Msk (0x1UL << I2C_COMP_HCV_Pos)
#define I2C_COMP_MAXSPM_Pos 2
#define I2C_COMP_MAXSPM_Msk (0x3UL << I2C_COMP_MAXSPM_Pos)
#define I2C_COMP_APB_DAW_Pos 0
#define I2C_COMP_APB_DAW_Msk (0x3UL << I2C_COMP_APB_DAW_Pos)

/****************** Bit Definition for I2C I2C_COMP_VERSION Register ************/
#define I2C_COMP_VERSION_Pos 0
#define I2C_COMP_VERSION_Msk (0xFFFFFFFF << I2C_COMP_VERSION_Pos)

/****************** Bit Definition for I2C I2C_COMP_TYPE Register **************/
#define I2C_COMP_TYPE_Pos 0
#define I2C_COMP_TYPE_Msk (0XFFFFFFFF << I2C_COMP_TYPE_Pos)

/********************Address Length ***************/
#define LENGTH7 ((uint32_t)(0x07))
#define LENGTH10 ((uint32_t)(0x10))
/***************** I2C Function Definition **************/

/* =========================================================================================================================== */
/* ================    I2C0================ */
/* =========================================================================================================================== */

/* ==========================================================  CON  ========================================================== */
#define I2C0_CON_STOP_DET_IF_MASTER_ACTIVE_Pos (10UL)         /*!< SDIMA (Bit 10)   */
#define I2C0_CON_STOP_DET_IF_MASTER_ACTIVE_Msk (0x400UL)      /*!< SDIMA (Bitfield-Mask: 0x01)  */
#define I2C0_CON_RX_FIFO_FULL_HLD_CTRL_Pos (9UL)              /*!< RFFHC (Bit 9)   */
#define I2C0_CON_RX_FIFO_FULL_HLD_CTRL_Msk (0x200UL)          /*!< RFFHC (Bitfield-Mask: 0x01) */
#define I2C0_CON_TX_EMPTY_CTRL_Pos (8UL)                      /*!< TXEC (Bit 8) */
#define I2C0_CON_TX_EMPTY_CTRL_Msk (0x100UL)                  /*!< TXEC (Bitfield-Mask: 0x01)  */
#define I2C0_CON_STOP_DET_IFADDRESSED_Pos (7UL)               /*!< SDIAD (Bit 7)    */
#define I2C0_CON_STOP_DET_IFADDRESSED_Msk (0x80UL)            /*!< SDIAD (Bitfield-Mask: 0x01)  */
#define I2C0_CON_IC_SLAVE_DISABLE_Pos (6UL)                   /*!< SLVDIS (Bit 6)   */
#define I2C0_CON_IC_SLAVE_DISABLE_Msk (0x40UL)                /*!< SLVDIS (Bitfield-Mask: 0x01) */
#define I2C0_CON_IC_RESTART_EN_Pos (5UL)                      /*!< RESTEN (Bit 5) */
#define I2C0_CON_IC_RESTART_EN_Msk (0x20UL)                   /*!< RESTEN (Bitfield-Mask: 0x01)  */
#define I2C0_CON_IC_10BITADDR_MASTER_Pos (4UL)                /*!< 10ADDR_MAS (Bit 4)*/
#define I2C0_CON_IC_10BITADDR_MASTER_Msk (0x10UL)             /*!< 10ADDR_MAS (Bitfield-Mask: 0x01)   */
#define I2C0_CON_IC_10BITADDR_SLAVE_Pos (3UL)                 /*!< 10ADDR_SLV (Bit 3) */
#define I2C0_CON_IC_10BITADDR_SLAVE_Msk (0x8UL)               /*!< 10ADDR_SLV (Bitfield-Mask: 0x01)    */
#define I2C0_CON_SPEED_Pos (1UL)                              /*!< SPEED (Bit 1)  */
#define I2C0_CON_SPEED_Msk (0x6UL)                            /*!< SPEED (Bitfield-Mask: 0x03)*/
#define I2C0_CON_MASTER_MODE_Pos (0UL)                        /*!< MST_MODE (Bit 0) */
#define I2C0_CON_MASTER_MODE_Msk (0x1UL)                      /*!< MST_MODE (Bitfield-Mask: 0x01)    */
                                                              /* ==========================================================  TAR  ========================================================== */
#define I2C0_TAR_IC_10BITADDR_MASTER_Pos (12UL)               /*!< 10ADDR_MAS (Bit 12)    */
#define I2C0_TAR_IC_10BITADDR_MASTER_Msk (0x1000UL)           /*!< 10ADDR_MAS (Bitfield-Mask: 0x01)   */
#define I2C0_TAR_SPECIAL_Pos (11UL)                           /*!< SPECIAL (Bit 11)    */
#define I2C0_TAR_SPECIAL_Msk (0x800UL)                        /*!< SPECIAL (Bitfield-Mask: 0x01)   */
#define I2C0_TAR_GC_OR_START_Pos (10UL)                       /*!< GC_OR_START (Bit 10)*/
#define I2C0_TAR_GC_OR_START_Msk (0x400UL)                    /*!< GC_OR_START (Bitfield-Mask: 0x01)    */
#define I2C0_TAR_IC_TAR_Pos (0UL)                             /*!< IC_TAR (Bit 0) */
#define I2C0_TAR_IC_TAR_Msk (0x3ffUL)                         /*!< IC_TAR (Bitfield-Mask: 0x3ff)   */
                                                              /* ==========================================================  SAR  ========================================================== */
#define I2C0_SAR_IC_SAR_Pos (0UL)                             /*!< IC_SAR (Bit 0) */
#define I2C0_SAR_IC_SAR_Msk (0x3ffUL)                         /*!< IC_SAR (Bitfield-Mask: 0x3ff)   */
                                                              /* ========================================================  HSMADDR  ======================================================== */
#define I2C0_HSMADDR_IC_HS_MAR_Pos (0UL)                      /*!< IC_HS_MAR (Bit 0)   */
#define I2C0_HSMADDR_IC_HS_MAR_Msk (0x7UL)                    /*!< IC_HS_MAR (Bitfield-Mask: 0x07) */
                                                              /* ========================================================  DATACMD  ======================================================== */
#define I2C0_DATACMD_FIRST_DATA_BYTE_Pos (11UL)               /*!< FIRST_DATA_BYTE (Bit 11)   */
#define I2C0_DATACMD_FIRST_DATA_BYTE_Msk (0x800UL)            /*!< FIRST_DATA_BYTE (Bitfield-Mask: 0x01)*/
#define I2C0_DATACMD_RESTART_Pos (10UL)                       /*!< RESTART (Bit 10)    */
#define I2C0_DATACMD_RESTART_Msk (0x400UL)                    /*!< RESTART (Bitfield-Mask: 0x01)   */
#define I2C0_DATACMD_STOP_Pos (9UL)                           /*!< STOP (Bit 9)   */
#define I2C0_DATACMD_STOP_Msk (0x200UL)                       /*!< STOP (Bitfield-Mask: 0x01) */
#define I2C0_DATACMD_CMD_Pos (8UL)                            /*!< CMD (Bit 8)    */
#define I2C0_DATACMD_CMD_Msk (0x100UL)                        /*!< CMD (Bitfield-Mask: 0x01)  */
#define I2C0_DATACMD_DAT_Pos (0UL)                            /*!< DAT (Bit 0)    */
#define I2C0_DATACMD_DAT_Msk (0xffUL)                         /*!< DAT (Bitfield-Mask: 0xff)  */
                                                              /* ========================================================  SSHCNT  ========================================================= */
#define I2C0_SSHCNT_IC_SS_SCL_HCNT_Pos (0UL)                  /*!< SS_SCL_HCNT (Bit 0)*/
#define I2C0_SSHCNT_IC_SS_SCL_HCNT_Msk (0xffffUL)             /*!< SS_SCL_HCNT (Bitfield-Mask: 0xffff) */
                                                              /* ========================================================  SSLCNT  ========================================================= */
#define I2C0_SSLCNT_IC_SS_SCL_LCNT_Pos (0UL)                  /*!< SS_SCL_LCNT (Bit 0)*/
#define I2C0_SSLCNT_IC_SS_SCL_LCNT_Msk (0xffffUL)             /*!< SS_SCL_LCNT (Bitfield-Mask: 0xffff) */
                                                              /* ========================================================  FSHCNT  ========================================================= */
#define I2C0_FSHCNT_IC_FS_SCL_HCNT_Pos (0UL)                  /*!< FS_SCL_HCNT (Bit 0)*/
#define I2C0_FSHCNT_IC_FS_SCL_HCNT_Msk (0xffffUL)             /*!< FS_SCL_HCNT (Bitfield-Mask: 0xffff) */
                                                              /* ========================================================  FSLCNT  ========================================================= */
#define I2C0_FSLCNT_IC_FS_SCL_LCNT_Pos (0UL)                  /*!< FS_SCL_LCNT (Bit 0)*/
#define I2C0_FSLCNT_IC_FS_SCL_LCNT_Msk (0xffffUL)             /*!< FS_SCL_LCNT (Bitfield-Mask: 0xffff) */
                                                              /* ========================================================  HSHCNT  ========================================================= */
#define I2C0_HSHCNT_IC_HS_SCL_HCNT_Pos (0UL)                  /*!< HS_SCL_HCNT (Bit 0)*/
#define I2C0_HSHCNT_IC_HS_SCL_HCNT_Msk (0xffffUL)             /*!< HS_SCL_HCNT (Bitfield-Mask: 0xffff) */
                                                              /* ========================================================  HSLCNT  ========================================================= */
#define I2C0_HSLCNT_IC_HS_SCL_LCNT_Pos (0UL)                  /*!< HS_SCL_LCNT (Bit 0)*/
#define I2C0_HSLCNT_IC_HS_SCL_LCNT_Msk (0xffffUL)             /*!< HS_SCL_LCNT (Bitfield-Mask: 0xffff) */
                                                              /* =======================================================  INTRSTAT  ======================================================== */
#define I2C0_INTRSTAT_R_MST_ON_HOLD_Pos (13UL)                /*!< R_MST_ON_HOLD (Bit 13)*/
#define I2C0_INTRSTAT_R_MST_ON_HOLD_Msk (0x2000UL)            /*!< R_MST_ON_HOLD (Bitfield-Mask: 0x01)  */
#define I2C0_INTRSTAT_R_RESTART_DET_Pos (12UL)                /*!< R_RESTART_DET (Bit 12)*/
#define I2C0_INTRSTAT_R_RESTART_DET_Msk (0x1000UL)            /*!< R_RESTART_DET (Bitfield-Mask: 0x01)  */
#define I2C0_INTRSTAT_R_GEN_CALL_Pos (11UL)                   /*!< R_GEN_CALL (Bit 11) */
#define I2C0_INTRSTAT_R_GEN_CALL_Msk (0x800UL)                /*!< R_GEN_CALL (Bitfield-Mask: 0x01)*/
#define I2C0_INTRSTAT_R_START_DET_Pos (10UL)                  /*!< R_START_DET (Bit 10)*/
#define I2C0_INTRSTAT_R_START_DET_Msk (0x400UL)               /*!< R_START_DET (Bitfield-Mask: 0x01)    */
#define I2C0_INTRSTAT_R_STOP_DET_Pos (9UL)                    /*!< R_STOP_DET (Bit 9)  */
#define I2C0_INTRSTAT_R_STOP_DET_Msk (0x200UL)                /*!< R_STOP_DET (Bitfield-Mask: 0x01)*/
#define I2C0_INTRSTAT_R_ACTIVITY_Pos (8UL)                    /*!< R_ACTIVITY (Bit 8)  */
#define I2C0_INTRSTAT_R_ACTIVITY_Msk (0x100UL)                /*!< R_ACTIVITY (Bitfield-Mask: 0x01)*/
#define I2C0_INTRSTAT_R_RX_DONE_Pos (7UL)                     /*!< R_RX_DONE (Bit 7)   */
#define I2C0_INTRSTAT_R_RX_DONE_Msk (0x80UL)                  /*!< R_RX_DONE (Bitfield-Mask: 0x01) */
#define I2C0_INTRSTAT_R_TX_ABRT_Pos (6UL)                     /*!< R_TX_ABRT (Bit 6)   */
#define I2C0_INTRSTAT_R_TX_ABRT_Msk (0x40UL)                  /*!< R_TX_ABRT (Bitfield-Mask: 0x01) */
#define I2C0_INTRSTAT_R_RD_REQ_Pos (5UL)                      /*!< R_RD_REQ (Bit 5)    */
#define I2C0_INTRSTAT_R_RD_REQ_Msk (0x20UL)                   /*!< R_RD_REQ (Bitfield-Mask: 0x01)  */
#define I2C0_INTRSTAT_R_TX_EMPTY_Pos (4UL)                    /*!< R_TX_EMPTY (Bit 4)  */
#define I2C0_INTRSTAT_R_TX_EMPTY_Msk (0x10UL)                 /*!< R_TX_EMPTY (Bitfield-Mask: 0x01)*/
#define I2C0_INTRSTAT_R_TX_OVER_Pos (3UL)                     /*!< R_TX_OVER (Bit 3)   */
#define I2C0_INTRSTAT_R_TX_OVER_Msk (0x8UL)                   /*!< R_TX_OVER (Bitfield-Mask: 0x01) */
#define I2C0_INTRSTAT_R_RX_FULL_Pos (2UL)                     /*!< R_RX_FULL (Bit 2)   */
#define I2C0_INTRSTAT_R_RX_FULL_Msk (0x4UL)                   /*!< R_RX_FULL (Bitfield-Mask: 0x01) */
#define I2C0_INTRSTAT_R_RX_OVER_Pos (1UL)                     /*!< R_RX_OVER (Bit 1)   */
#define I2C0_INTRSTAT_R_RX_OVER_Msk (0x2UL)                   /*!< R_RX_OVER (Bitfield-Mask: 0x01) */
#define I2C0_INTRSTAT_R_RX_UNDER_Pos (0UL)                    /*!< R_RX_UNDER (Bit 0)  */
#define I2C0_INTRSTAT_R_RX_UNDER_Msk (0x1UL)                  /*!< R_RX_UNDER (Bitfield-Mask: 0x01)*/
                                                              /* =======================================================  INTRMASK  ======================================================== */
#define I2C0_INTRMASK_M_MST_ON_HOLD_Pos (13UL)                /*!< M_MST_ON_HOLD (Bit 13)*/
#define I2C0_INTRMASK_M_MST_ON_HOLD_Msk (0x2000UL)            /*!< M_MST_ON_HOLD (Bitfield-Mask: 0x01)  */
#define I2C0_INTRMASK_M_RESTART_DET_Pos (12UL)                /*!< M_RESTART_DET (Bit 12)*/
#define I2C0_INTRMASK_M_RESTART_DET_Msk (0x1000UL)            /*!< M_RESTART_DET (Bitfield-Mask: 0x01)  */
#define I2C0_INTRMASK_M_GEN_CALL_Pos (11UL)                   /*!< M_GEN_CALL (Bit 11) */
#define I2C0_INTRMASK_M_GEN_CALL_Msk (0x800UL)                /*!< M_GEN_CALL (Bitfield-Mask: 0x01)*/
#define I2C0_INTRMASK_M_START_DET_Pos (10UL)                  /*!< M_START_DET (Bit 10)*/
#define I2C0_INTRMASK_M_START_DET_Msk (0x400UL)               /*!< M_START_DET (Bitfield-Mask: 0x01)    */
#define I2C0_INTRMASK_M_STOP_DET_Pos (9UL)                    /*!< M_STOP_DET (Bit 9)  */
#define I2C0_INTRMASK_M_STOP_DET_Msk (0x200UL)                /*!< M_STOP_DET (Bitfield-Mask: 0x01)*/
#define I2C0_INTRMASK_M_ACTIVITY_Pos (8UL)                    /*!< M_ACTIVITY (Bit 8)  */
#define I2C0_INTRMASK_M_ACTIVITY_Msk (0x100UL)                /*!< M_ACTIVITY (Bitfield-Mask: 0x01)*/
#define I2C0_INTRMASK_M_RX_DONE_Pos (7UL)                     /*!< M_RX_DONE (Bit 7)   */
#define I2C0_INTRMASK_M_RX_DONE_Msk (0x80UL)                  /*!< M_RX_DONE (Bitfield-Mask: 0x01) */
#define I2C0_INTRMASK_M_TX_ABRT_Pos (6UL)                     /*!< M_TX_ABRT (Bit 6)   */
#define I2C0_INTRMASK_M_TX_ABRT_Msk (0x40UL)                  /*!< M_TX_ABRT (Bitfield-Mask: 0x01) */
#define I2C0_INTRMASK_M_RD_REQ_Pos (5UL)                      /*!< M_RD_REQ (Bit 5)    */
#define I2C0_INTRMASK_M_RD_REQ_Msk (0x20UL)                   /*!< M_RD_REQ (Bitfield-Mask: 0x01)  */
#define I2C0_INTRMASK_M_TX_EMPTY_Pos (4UL)                    /*!< M_TX_EMPTY (Bit 4)  */
#define I2C0_INTRMASK_M_TX_EMPTY_Msk (0x10UL)                 /*!< M_TX_EMPTY (Bitfield-Mask: 0x01)*/
#define I2C0_INTRMASK_M_TX_OVER_Pos (3UL)                     /*!< M_TX_OVER (Bit 3)   */
#define I2C0_INTRMASK_M_TX_OVER_Msk (0x8UL)                   /*!< M_TX_OVER (Bitfield-Mask: 0x01) */
#define I2C0_INTRMASK_M_RX_FULL_Pos (2UL)                     /*!< M_RX_FULL (Bit 2)   */
#define I2C0_INTRMASK_M_RX_FULL_Msk (0x4UL)                   /*!< M_RX_FULL (Bitfield-Mask: 0x01) */
#define I2C0_INTRMASK_M_RX_OVER_Pos (1UL)                     /*!< M_RX_OVER (Bit 1)   */
#define I2C0_INTRMASK_M_RX_OVER_Msk (0x2UL)                   /*!< M_RX_OVER (Bitfield-Mask: 0x01) */
#define I2C0_INTRMASK_M_RX_UNDER_Pos (0UL)                    /*!< M_RX_UNDER (Bit 0)  */
#define I2C0_INTRMASK_M_RX_UNDER_Msk (0x1UL)                  /*!< M_RX_UNDER (Bitfield-Mask: 0x01)*/
                                                              /* ======================================================  RAWINTRSTAT  ====================================================== */
#define I2C0_RAWINTRSTAT_MST_ON_HOLD_Pos (13UL)               /*!< MST_ON_HOLD (Bit 13)*/
#define I2C0_RAWINTRSTAT_MST_ON_HOLD_Msk (0x2000UL)           /*!< MST_ON_HOLD (Bitfield-Mask: 0x01)    */
#define I2C0_RAWINTRSTAT_RESTART_DET_Pos (12UL)               /*!< RESTART_DET (Bit 12)*/
#define I2C0_RAWINTRSTAT_RESTART_DET_Msk (0x1000UL)           /*!< RESTART_DET (Bitfield-Mask: 0x01)    */
#define I2C0_RAWINTRSTAT_GEN_CALL_Pos (11UL)                  /*!< GEN_CALL (Bit 11)   */
#define I2C0_RAWINTRSTAT_GEN_CALL_Msk (0x800UL)               /*!< GEN_CALL (Bitfield-Mask: 0x01)  */
#define I2C0_RAWINTRSTAT_START_DET_Pos (10UL)                 /*!< START_DET (Bit 10)  */
#define I2C0_RAWINTRSTAT_START_DET_Msk (0x400UL)              /*!< START_DET (Bitfield-Mask: 0x01) */
#define I2C0_RAWINTRSTAT_STOP_DET_Pos (9UL)                   /*!< STOP_DET (Bit 9)    */
#define I2C0_RAWINTRSTAT_STOP_DET_Msk (0x200UL)               /*!< STOP_DET (Bitfield-Mask: 0x01)  */
#define I2C0_RAWINTRSTAT_ACTIVITY_Pos (8UL)                   /*!< ACTIVITY (Bit 8)    */
#define I2C0_RAWINTRSTAT_ACTIVITY_Msk (0x100UL)               /*!< ACTIVITY (Bitfield-Mask: 0x01)  */
#define I2C0_RAWINTRSTAT_RX_DONE_Pos (7UL)                    /*!< RX_DONE (Bit 7)*/
#define I2C0_RAWINTRSTAT_RX_DONE_Msk (0x80UL)                 /*!< RX_DONE (Bitfield-Mask: 0x01)   */
#define I2C0_RAWINTRSTAT_TX_ABRT_Pos (6UL)                    /*!< TX_ABRT (Bit 6)*/
#define I2C0_RAWINTRSTAT_TX_ABRT_Msk (0x40UL)                 /*!< TX_ABRT (Bitfield-Mask: 0x01)   */
#define I2C0_RAWINTRSTAT_RD_REQ_Pos (5UL)                     /*!< RD_REQ (Bit 5) */
#define I2C0_RAWINTRSTAT_RD_REQ_Msk (0x20UL)                  /*!< RD_REQ (Bitfield-Mask: 0x01)    */
#define I2C0_RAWINTRSTAT_TX_EMPTY_Pos (4UL)                   /*!< TX_EMPTY (Bit 4)    */
#define I2C0_RAWINTRSTAT_TX_EMPTY_Msk (0x10UL)                /*!< TX_EMPTY (Bitfield-Mask: 0x01)  */
#define I2C0_RAWINTRSTAT_TX_OVER_Pos (3UL)                    /*!< TX_OVER (Bit 3)*/
#define I2C0_RAWINTRSTAT_TX_OVER_Msk (0x8UL)                  /*!< TX_OVER (Bitfield-Mask: 0x01)   */
#define I2C0_RAWINTRSTAT_RX_FULL_Pos (2UL)                    /*!< RX_FULL (Bit 2)*/
#define I2C0_RAWINTRSTAT_RX_FULL_Msk (0x4UL)                  /*!< RX_FULL (Bitfield-Mask: 0x01)   */
#define I2C0_RAWINTRSTAT_RX_OVER_Pos (1UL)                    /*!< RX_OVER (Bit 1)*/
#define I2C0_RAWINTRSTAT_RX_OVER_Msk (0x2UL)                  /*!< RX_OVER (Bitfield-Mask: 0x01)   */
#define I2C0_RAWINTRSTAT_RX_UNDER_Pos (0UL)                   /*!< RX_UNDER (Bit 0)    */
#define I2C0_RAWINTRSTAT_RX_UNDER_Msk (0x1UL)                 /*!< RX_UNDER (Bitfield-Mask: 0x01)  */
                                                              /* =========================================================  RXTL  ========================================================== */
#define I2C0_RXTL_RX_TL_Pos (0UL)                             /*!< RX_TL (Bit 0)  */
#define I2C0_RXTL_RX_TL_Msk (0xffUL)                          /*!< RX_TL (Bitfield-Mask: 0xff)*/
                                                              /* =========================================================  TXTL  ========================================================== */
#define I2C0_TXTL_TX_TL_Pos (0UL)                             /*!< TX_TL (Bit 0)  */
#define I2C0_TXTL_TX_TL_Msk (0xffUL)                          /*!< TX_TL (Bitfield-Mask: 0xff)*/
                                                              /* ========================================================  CLRINTR  ======================================================== */
#define I2C0_CLRINTR_CLR_INTR_Pos (0UL)                       /*!< CLR_INTR (Bit 0)    */
#define I2C0_CLRINTR_CLR_INTR_Msk (0x1UL)                     /*!< CLR_INTR (Bitfield-Mask: 0x01)  */
                                                              /* ======================================================  CLRRXUNDER  ======================================================= */
#define I2C0_CLRRXUNDER_CLR_RX_UNDER_Pos (0UL)                /*!< CLR_RX_UNDER (Bit 0)*/
#define I2C0_CLRRXUNDER_CLR_RX_UNDER_Msk (0x1UL)              /*!< CLR_RX_UNDER (Bitfield-Mask: 0x01)   */
                                                              /* =======================================================  CLRRXOVER  ======================================================= */
#define I2C0_CLRRXOVER_CLR_RX_OVER_Pos (0UL)                  /*!< CLR_RX_OVER (Bit 0) */
#define I2C0_CLRRXOVER_CLR_RX_OVER_Msk (0x1UL)                /*!< CLR_RX_OVER (Bitfield-Mask: 0x01)    */
                                                              /* =======================================================  CLRTXOVER  ======================================================= */
#define I2C0_CLRTXOVER_CLR_TX_OVER_Pos (0UL)                  /*!< CLR_TX_OVER (Bit 0) */
#define I2C0_CLRTXOVER_CLR_TX_OVER_Msk (0x1UL)                /*!< CLR_TX_OVER (Bitfield-Mask: 0x01)    */
                                                              /* =======================================================  CLRRDREQ  ======================================================== */
#define I2C0_CLRRDREQ_CLR_RD_REQ_Pos (0UL)                    /*!< CLR_RD_REQ (Bit 0)  */
#define I2C0_CLRRDREQ_CLR_RD_REQ_Msk (0x1UL)                  /*!< CLR_RD_REQ (Bitfield-Mask: 0x01)*/
                                                              /* =======================================================  CLRTXABRT  ======================================================= */
#define I2C0_CLRTXABRT_CLR_TX_ABRT_Pos (0UL)                  /*!< CLR_TX_ABRT (Bit 0) */
#define I2C0_CLRTXABRT_CLR_TX_ABRT_Msk (0x1UL)                /*!< CLR_TX_ABRT (Bitfield-Mask: 0x01)    */
                                                              /* =======================================================  CLRRXDONE  ======================================================= */
#define I2C0_CLRRXDONE_CLR_RX_DONE_Pos (0UL)                  /*!< CLR_RX_DONE (Bit 0) */
#define I2C0_CLRRXDONE_CLR_RX_DONE_Msk (0x1UL)                /*!< CLR_RX_DONE (Bitfield-Mask: 0x01)    */
                                                              /* ======================================================  CLRACTIVITY  ====================================================== */
#define I2C0_CLRACTIVITY_CLR_ACTIVITY_Pos (0UL)               /*!< CLR_ACTIVITY (Bit 0)*/
#define I2C0_CLRACTIVITY_CLR_ACTIVITY_Msk (0x1UL)             /*!< CLR_ACTIVITY (Bitfield-Mask: 0x01)   */
                                                              /* ======================================================  CLRSTOP_DET  ====================================================== */
#define I2C0_CLRSTOP_DET_CLR_STOP_DET_Pos (0UL)               /*!< CLR_STOP_DET (Bit 0)*/
#define I2C0_CLRSTOP_DET_CLR_STOP_DET_Msk (0x1UL)             /*!< CLR_STOP_DET (Bitfield-Mask: 0x01)   */
                                                              /* ======================================================  CLRSTARTDET  ====================================================== */
#define I2C0_CLRSTARTDET_CLR_START_DET_Pos (0UL)              /*!< CLR_START_DET (Bit 0) */
#define I2C0_CLRSTARTDET_CLR_START_DET_Msk (0x1UL)            /*!< CLR_START_DET (Bitfield-Mask: 0x01)  */
                                                              /* ======================================================  CLRGENCALL  ======================================================= */
#define I2C0_CLRGENCALL_CLR_GEN_CALL_Pos (0UL)                /*!< CLR_GEN_CALL (Bit 0)*/
#define I2C0_CLRGENCALL_CLR_GEN_CALL_Msk (0x1UL)              /*!< CLR_GEN_CALL (Bitfield-Mask: 0x01)   */
                                                              /* ========================================================  ENABLE  ========================================================= */
#define I2C0_ENABLE_TX_CMD_BLOCK_Pos (2UL)                    /*!< TX_CMD_BLOCK (Bit 2)*/
#define I2C0_ENABLE_TX_CMD_BLOCK_Msk (0x4UL)                  /*!< TX_CMD_BLOCK (Bitfield-Mask: 0x01)   */
#define I2C0_ENABLE_ABORT_Pos (1UL)                           /*!< ABORT (Bit 1)  */
#define I2C0_ENABLE_ABORT_Msk (0x2UL)                         /*!< ABORT (Bitfield-Mask: 0x01)*/
#define I2C0_ENABLE_ENABLE_Pos (0UL)                          /*!< ENABLE (Bit 0) */
#define I2C0_ENABLE_ENABLE_Msk (0x1UL)                        /*!< ENABLE (Bitfield-Mask: 0x01)    */
                                                              /* ========================================================  STATUS  ========================================================= */
#define I2C0_STATUS_SLV_HOLD_RX_FIFO_FULL_Pos (10UL)          /*!< SLV_HOLD_RX_FIFO_FULL (Bit 10)  */
#define I2C0_STATUS_SLV_HOLD_RX_FIFO_FULL_Msk (0x400UL)       /*!< SLV_HOLD_RX_FIFO_FULL (Bitfield-Mask: 0x01) */
#define I2C0_STATUS_SLV_HOLD_TX_FIFO_EMPTY_Pos (9UL)          /*!< SLV_HOLD_TX_FIFO_EMPTY (Bit 9)  */
#define I2C0_STATUS_SLV_HOLD_TX_FIFO_EMPTY_Msk (0x200UL)      /*!< SLV_HOLD_TX_FIFO_EMPTY (Bitfield-Mask: 0x01)*/
#define I2C0_STATUS_MST_HOLD_RX_FIFO_FULL_Pos (8UL)           /*!< MST_HOLD_RX_FIFO_FULL (Bit 8)   */
#define I2C0_STATUS_MST_HOLD_RX_FIFO_FULL_Msk (0x100UL)       /*!< MST_HOLD_RX_FIFO_FULL (Bitfield-Mask: 0x01) */
#define I2C0_STATUS_MST_HOLD_TX_FIFO_EMPTY_Pos (7UL)          /*!< MST_HOLD_TX_FIFO_EMPTY (Bit 7)  */
#define I2C0_STATUS_MST_HOLD_TX_FIFO_EMPTY_Msk (0x80UL)       /*!< MST_HOLD_TX_FIFO_EMPTY (Bitfield-Mask: 0x01)*/
#define I2C0_STATUS_SLV_ACTIVITY_Pos (6UL)                    /*!< SLV_ACTIVITY (Bit 6)*/
#define I2C0_STATUS_SLV_ACTIVITY_Msk (0x40UL)                 /*!< SLV_ACTIVITY (Bitfield-Mask: 0x01)   */
#define I2C0_STATUS_MST_ACTIVITY_Pos (5UL)                    /*!< MST_ACTIVITY (Bit 5)*/
#define I2C0_STATUS_MST_ACTIVITY_Msk (0x20UL)                 /*!< MST_ACTIVITY (Bitfield-Mask: 0x01)   */
#define I2C0_STATUS_RFF_Pos (4UL)                             /*!< RFF (Bit 4)    */
#define I2C0_STATUS_RFF_Msk (0x10UL)                          /*!< RFF (Bitfield-Mask: 0x01)  */
#define I2C0_STATUS_RFNE_Pos (3UL)                            /*!< RFNE (Bit 3)   */
#define I2C0_STATUS_RFNE_Msk (0x8UL)                          /*!< RFNE (Bitfield-Mask: 0x01) */
#define I2C0_STATUS_TFE_Pos (2UL)                             /*!< TFE (Bit 2)    */
#define I2C0_STATUS_TFE_Msk (0x4UL)                           /*!< TFE (Bitfield-Mask: 0x01)  */
#define I2C0_STATUS_TFNF_Pos (1UL)                            /*!< TFNF (Bit 1)   */
#define I2C0_STATUS_TFNF_Msk (0x2UL)                          /*!< TFNF (Bitfield-Mask: 0x01) */
#define I2C0_STATUS_ACTIVITY_Pos (0UL)                        /*!< ACTIVITY (Bit 0)    */
#define I2C0_STATUS_ACTIVITY_Msk (0x1UL)                      /*!< ACTIVITY (Bitfield-Mask: 0x01)  */
                                                              /* =========================================================  TXFLR  ========================================================= */
#define I2C0_TXFLR_TXFLR_Pos (0UL)                            /*!< TXFLR (Bit 0)  */
#define I2C0_TXFLR_TXFLR_Msk (0xffUL)                         /*!< TXFLR (Bitfield-Mask: 0xff)*/
                                                              /* =========================================================  RXFLR  ========================================================= */
#define I2C0_RXFLR_RXFLR_Pos (0UL)                            /*!< RXFLR (Bit 0)  */
#define I2C0_RXFLR_RXFLR_Msk (0xffUL)                         /*!< RXFLR (Bitfield-Mask: 0xff)*/
                                                              /* ========================================================  SDAHOLD  ======================================================== */
#define I2C0_SDAHOLD_IC_SDA_RX_HOLD_Pos (16UL)                /*!< IC_SDA_RX_HOLD (Bit 16)    */
#define I2C0_SDAHOLD_IC_SDA_RX_HOLD_Msk (0xff0000UL)          /*!< IC_SDA_RX_HOLD (Bitfield-Mask: 0xff) */
#define I2C0_SDAHOLD_IC_SDA_TX_HOLD_Pos (0UL)                 /*!< IC_SDA_TX_HOLD (Bit 0)*/
#define I2C0_SDAHOLD_IC_SDA_TX_HOLD_Msk (0xffffUL)            /*!< IC_SDA_TX_HOLD (Bitfield-Mask: 0xffff) */
                                                              /* =====================================================  TXABRTSOURCE  ====================================================== */
#define I2C0_TXABRTSOURCE_TX_FLUSH_CNT_Pos (23UL)             /*!< TX_FLUSH_CNT (Bit 23) */
#define I2C0_TXABRTSOURCE_TX_FLUSH_CNT_Msk (0x7f800000UL)     /*!< TX_FLUSH_CNT (Bitfield-Mask: 0xff)   */
#define I2C0_TXABRTSOURCE_ABRT_USER_ABRT_Pos (16UL)           /*!< ABRT_USER_ABRT (Bit 16)    */
#define I2C0_TXABRTSOURCE_ABRT_USER_ABRT_Msk (0x10000UL)      /*!< ABRT_USER_ABRT (Bitfield-Mask: 0x01) */
#define I2C0_TXABRTSOURCE_ABRT_SLVRD_INTX_Pos (15UL)          /*!< ABRT_SLVRD_INTX (Bit 15)   */
#define I2C0_TXABRTSOURCE_ABRT_SLVRD_INTX_Msk (0x8000UL)      /*!< ABRT_SLVRD_INTX (Bitfield-Mask: 0x01)*/
#define I2C0_TXABRTSOURCE_ABRT_SLV_ARBLOST_Pos (14UL)         /*!< ABRT_SLV_ARBLOST (Bit 14)  */
#define I2C0_TXABRTSOURCE_ABRT_SLV_ARBLOST_Msk (0x4000UL)     /*!< ABRT_SLV_ARBLOST (Bitfield-Mask: 0x01) */
#define I2C0_TXABRTSOURCE_ABRT_SLVFLUSH_TXFIFO_Pos (13UL)     /*!< ABRT_SLVFLUSH_TXFIFO (Bit 13)   */
#define I2C0_TXABRTSOURCE_ABRT_SLVFLUSH_TXFIFO_Msk (0x2000UL) /*!< ABRT_SLVFLUSH_TXFIFO (Bitfield-Mask: 0x01)  */
#define I2C0_TXABRTSOURCE_ARB_LOST_Pos (12UL)                 /*!< ARB_LOST (Bit 12)   */
#define I2C0_TXABRTSOURCE_ARB_LOST_Msk (0x1000UL)             /*!< ARB_LOST (Bitfield-Mask: 0x01)  */
#define I2C0_TXABRTSOURCE_ABRT_MASTER_DIS_Pos (11UL)          /*!< ABRT_MASTER_DIS (Bit 11)   */
#define I2C0_TXABRTSOURCE_ABRT_MASTER_DIS_Msk (0x800UL)       /*!< ABRT_MASTER_DIS (Bitfield-Mask: 0x01)*/
#define I2C0_TXABRTSOURCE_ABRT_10B_RD_NORSTRT_Pos (10UL)      /*!< ABRT_10B_RD_NORSTRT (Bit 10)    */
#define I2C0_TXABRTSOURCE_ABRT_10B_RD_NORSTRT_Msk (0x400UL)   /*!< ABRT_10B_RD_NORSTRT (Bitfield-Mask: 0x01)   */
#define I2C0_TXABRTSOURCE_ABRT_SBYTE_NORSTRT_Pos (9UL)        /*!< ABRT_SBYTE_NORSTRT (Bit 9) */
#define I2C0_TXABRTSOURCE_ABRT_SBYTE_NORSTRT_Msk (0x200UL)    /*!< ABRT_SBYTE_NORSTRT (Bitfield-Mask: 0x01)    */
#define I2C0_TXABRTSOURCE_ABRT_HS_NORSTRT_Pos (8UL)           /*!< ABRT_HS_NORSTRT (Bit 8)    */
#define I2C0_TXABRTSOURCE_ABRT_HS_NORSTRT_Msk (0x100UL)       /*!< ABRT_HS_NORSTRT (Bitfield-Mask: 0x01)*/
#define I2C0_TXABRTSOURCE_ABRT_SBYTE_ACKDET_Pos (7UL)         /*!< ABRT_SBYTE_ACKDET (Bit 7)  */
#define I2C0_TXABRTSOURCE_ABRT_SBYTE_ACKDET_Msk (0x80UL)      /*!< ABRT_SBYTE_ACKDET (Bitfield-Mask: 0x01)*/
#define I2C0_TXABRTSOURCE_ABRT_HS_ACKDET_Pos (6UL)            /*!< ABRT_HS_ACKDET (Bit 6)*/
#define I2C0_TXABRTSOURCE_ABRT_HS_ACKDET_Msk (0x40UL)         /*!< ABRT_HS_ACKDET (Bitfield-Mask: 0x01) */
#define I2C0_TXABRTSOURCE_ABRT_GCALL_READ_Pos (5UL)           /*!< ABRT_GCALL_READ (Bit 5)    */
#define I2C0_TXABRTSOURCE_ABRT_GCALL_READ_Msk (0x20UL)        /*!< ABRT_GCALL_READ (Bitfield-Mask: 0x01)*/
#define I2C0_TXABRTSOURCE_ABRT_GCALL_NOACK_Pos (4UL)          /*!< ABRT_GCALL_NOACK (Bit 4)   */
#define I2C0_TXABRTSOURCE_ABRT_GCALL_NOACK_Msk (0x10UL)       /*!< ABRT_GCALL_NOACK (Bitfield-Mask: 0x01) */
#define I2C0_TXABRTSOURCE_ABRT_TXDATA_NOACK_Pos (3UL)         /*!< ABRT_TXDATA_NOACK (Bit 3)  */
#define I2C0_TXABRTSOURCE_ABRT_TXDATA_NOACK_Msk (0x8UL)       /*!< ABRT_TXDATA_NOACK (Bitfield-Mask: 0x01)*/
#define I2C0_TXABRTSOURCE_ABRT_10ADDR2_NOACK_Pos (2UL)        /*!< ABRT_10ADDR2_NOACK (Bit 2) */
#define I2C0_TXABRTSOURCE_ABRT_10ADDR2_NOACK_Msk (0x4UL)      /*!< ABRT_10ADDR2_NOACK (Bitfield-Mask: 0x01)    */
#define I2C0_TXABRTSOURCE_ABRT_10ADDR1_NOACK_Pos (1UL)        /*!< ABRT_10ADDR1_NOACK (Bit 1) */
#define I2C0_TXABRTSOURCE_ABRT_10ADDR1_NOACK_Msk (0x2UL)      /*!< ABRT_10ADDR1_NOACK (Bitfield-Mask: 0x01)    */
#define I2C0_TXABRTSOURCE_ABRT_7B_ADDR_NOACK_Pos (0UL)        /*!< ABRT_7B_ADDR_NOACK (Bit 0) */
#define I2C0_TXABRTSOURCE_ABRT_7B_ADDR_NOACK_Msk (0x1UL)      /*!< ABRT_7B_ADDR_NOACK (Bitfield-Mask: 0x01)    */
                                                              /* ======================================================  SLVDATANACKONLY  ====================================================== */
#define I2C0_SLVDATANACK_NACK_Pos (0UL)                       /*!< NACK (Bit 0)   */
#define I2C0_SLVDATANACK_NACK_Msk (0x1UL)                     /*!< NACK (Bitfield-Mask: 0x01) */
                                                              /* =========================================================  DMACR  ========================================================= */
#define I2C0_DMACR_TDMAE_Pos (1UL)                            /*!< TDMAE (Bit 1)  */
#define I2C0_DMACR_TDMAE_Msk (0x2UL)                          /*!< TDMAE (Bitfield-Mask: 0x01)*/
#define I2C0_DMACR_RDMAE_Pos (0UL)                            /*!< RDMAE (Bit 0)  */
#define I2C0_DMACR_RDMAE_Msk (0x1UL)                          /*!< RDMAE (Bitfield-Mask: 0x01)*/
                                                              /* ========================================================  DMATDLR  ======================================================== */
#define I2C0_DMATDLR_DMATDL_Pos (0UL)                         /*!< DMATDL (Bit 0) */
#define I2C0_DMATDLR_DMATDL_Msk (0xffffffffUL)                /*!< DMATDL (Bitfield-Mask: 0xffffffff)   */
                                                              /* ========================================================  DMARDLR  ======================================================== */
#define I2C0_DMARDLR_DMARDL_Pos (0UL)                         /*!< DMARDL (Bit 0) */
#define I2C0_DMARDLR_DMARDL_Msk (0xffffffffUL)                /*!< DMARDL (Bitfield-Mask: 0xffffffff)   */
                                                              /* =======================================================  SDASETUP  ======================================================== */
#define I2C0_SDASETUP_SDA_SETUP_Pos (0UL)                     /*!< SDA_SETUP (Bit 0)   */
#define I2C0_SDASETUP_SDA_SETUP_Msk (0xffUL)                  /*!< SDA_SETUP (Bitfield-Mask: 0xff) */
                                                              /* ======================================================  ACKGENERALCALL  ======================================================= */
#define I2C0_ACKGENERALCALL_ACK_GEN_CALL_Pos (0UL)            /*!< ACK_GEN_CALL (Bit 0)*/
#define I2C0_ACKGENERALCALL_ACK_GEN_CALL_Msk (0x1UL)          /*!< ACK_GEN_CALL (Bitfield-Mask: 0x01)   */
                                                              /* =====================================================  ENABLESTATUS  ====================================================== */
#define I2C0_ENABLESTATUS_SLV_RX_DATA_LOST_Pos (2UL)          /*!< SLV_RX_DATA_LOST (Bit 2)   */
#define I2C0_ENABLESTATUS_SLV_RX_DATA_LOST_Msk (0x4UL)        /*!< SLV_RX_DATA_LOST (Bitfield-Mask: 0x01) */
#define I2C0_ENABLESTATUS_SLV_DISABLED_WHILE_BUSY_Pos (1UL)   /*!< SLV_DISABLED_WHILE_BUSY (Bit 1) */
#define I2C0_ENABLESTATUS_SLV_DISABLED_WHILE_BUSY_Msk (0x2UL) /*!< SLV_DISABLED_WHILE_BUSY (Bitfield-Mask: 0x01)    */
#define I2C0_ENABLESTATUS_IC_EN_Pos (0UL)                     /*!< IC_EN (Bit 0)  */
#define I2C0_ENABLESTATUS_IC_EN_Msk (0x1UL)                   /*!< IC_EN (Bitfield-Mask: 0x01)*/
                                                              /* =======================================================  FSSPKLEN  ======================================================== */
#define I2C0_FSSPKLEN_IC_FS_SPKLEN_Pos (0UL)                  /*!< IC_FS_SPKLEN (Bit 0)*/
#define I2C0_FSSPKLEN_IC_FS_SPKLEN_Msk (0x1UL)                /*!< IC_FS_SPKLEN (Bitfield-Mask: 0x01)   */
                                                              /* =======================================================  HSSPKLEN  ======================================================== */
#define I2C0_HSSPKLEN_IC_FS_SPKLEN_Pos (0UL)                  /*!< IC_FS_SPKLEN (Bit 0)*/
#define I2C0_HSSPKLEN_IC_FS_SPKLEN_Msk (0xffUL)               /*!< IC_FS_SPKLEN (Bitfield-Mask: 0xff)   */
                                                              /* =====================================================  CLRRESTARTDET  ===================================================== */
#define I2C0_CLRRESTARTDET_CLR_RESTART_DET_Pos (0UL)          /*!< CLR_RESTART_DET (Bit 0)    */
#define I2C0_CLRRESTARTDET_CLR_RESTART_DET_Msk (0x1UL)        /*!< CLR_RESTART_DET (Bitfield-Mask: 0x01)*/
                                                              /* ======================================================  COMPPARAM1  ======================================================= */
#define I2C0_COMPPARAM1_TX_BUFFER_DEPTH_Pos (16UL)            /*!< TX_BUFFER_DEPTH (Bit 16)   */
#define I2C0_COMPPARAM1_TX_BUFFER_DEPTH_Msk (0xff0000UL)      /*!< TX_BUFFER_DEPTH (Bitfield-Mask: 0xff)*/
#define I2C0_COMPPARAM1_RX_BUFFER_DEPTH_Pos (8UL)             /*!< RX_BUFFER_DEPTH (Bit 8)    */
#define I2C0_COMPPARAM1_RX_BUFFER_DEPTH_Msk (0xff00UL)        /*!< RX_BUFFER_DEPTH (Bitfield-Mask: 0xff)*/
#define I2C0_COMPPARAM1_ADD_ENCODED_PARAMS_Pos (7UL)          /*!< ADD_ENCODED_PARAMS (Bit 7) */
#define I2C0_COMPPARAM1_ADD_ENCODED_PARAMS_Msk (0x80UL)       /*!< ADD_ENCODED_PARAMS (Bitfield-Mask: 0x01)    */
#define I2C0_COMPPARAM1_HAS_DMA_Pos (6UL)                     /*!< HAS_DMA (Bit 6)*/
#define I2C0_COMPPARAM1_HAS_DMA_Msk (0x40UL)                  /*!< HAS_DMA (Bitfield-Mask: 0x01)   */
#define I2C0_COMPPARAM1_INTR_IO_Pos (5UL)                     /*!< INTR_IO (Bit 5)*/
#define I2C0_COMPPARAM1_INTR_IO_Msk (0x20UL)                  /*!< INTR_IO (Bitfield-Mask: 0x01)   */
#define I2C0_COMPPARAM1_HC_COUNT_VALUES_Pos (4UL)             /*!< HC_COUNT_VALUES (Bit 4)    */
#define I2C0_COMPPARAM1_HC_COUNT_VALUES_Msk (0x10UL)          /*!< HC_COUNT_VALUES (Bitfield-Mask: 0x01)*/
#define I2C0_COMPPARAM1_MAX_SPEED_MODE_Pos (2UL)              /*!< MAX_SPEED_MODE (Bit 2)*/
#define I2C0_COMPPARAM1_MAX_SPEED_MODE_Msk (0xcUL)            /*!< MAX_SPEED_MODE (Bitfield-Mask: 0x03) */
#define I2C0_COMPPARAM1_APB_DATA_WIDTH_Pos (0UL)              /*!< APB_DATA_WIDTH (Bit 0)*/
#define I2C0_COMPPARAM1_APB_DATA_WIDTH_Msk (0x3UL)            /*!< APB_DATA_WIDTH (Bitfield-Mask: 0x03) */
                                                              /* ======================================================  COMPVERSION  ====================================================== */
#define I2C0_COMPVERSION_IC_FS_SPKLEN_Pos (0UL)               /*!< IC_FS_SPKLEN (Bit 0)*/
#define I2C0_COMPVERSION_IC_FS_SPKLEN_Msk (0xffffffffUL)      /*!< IC_FS_SPKLEN (Bitfield-Mask: 0xffffffff)    */
                                                              /* =======================================================  COMPTYPE  ======================================================== */
#define I2C0_COMPTYPE_IC_COMP_TYPE_Pos (0UL)                  /*!< IC_COMP_TYPE (Bit 0)*/
#define I2C0_COMPTYPE_IC_COMP_TYPE_Msk (0xffffffffUL)         /*!< IC_COMP_TYPE (Bitfield-Mask: 0xffffffff)    */

/* i2c disable or enable */
void I2C_DeInit(I2C_TypeDef *I2Cx);
void SlaveAckGeneralCall(I2C_TypeDef *I2Cx, bool status);
void I2C_GenerateGeneralCall(I2C_TypeDef *I2Cx);
void I2C_ClearGeneralCall(I2C_TypeDef *I2Cx);
void I2C_GenerateStartByte(I2C_TypeDef *I2Cx);
void I2C_SetFrequent(I2C_TypeDef *I2Cx, int sclClock);
void I2C_TxFifoITthreshold(uint32_t TxFifoValue);
void I2C_RxFifoITthreshold(uint32_t RxFifoValue);
void I2C_TransferHandling(I2C_TypeDef *I2Cx, uint32_t Address);
void I2C_SlaveAddressConfig(I2C_TypeDef *I2Cx, uint32_t Address);
void I2C_Cmd(I2C_TypeDef *I2Cx, FunctionalState NewState);
void I2C_StructInit(I2C_InitTypeDef *I2C_InitStruct);
void I2C_Init(I2C_TypeDef *I2Cx, I2C_InitTypeDef *I2C_InitStruct);
uint32_t I2C_ReadRegister(I2C_TypeDef *I2Cx, uint8_t I2C_Register);
uint8_t I2C_ReadData(I2C_TypeDef *I2Cx);
uint8_t I2C_ReadData_Stop(I2C_TypeDef *I2Cx);
void I2C_WriteData(I2C_TypeDef *I2Cx, uint8_t Data);
void I2C_WriteData_Stop(I2C_TypeDef *I2Cx, uint8_t Data);
uint32_t I2C_ReceiveData(I2C_TypeDef *I2Cx);
void I2C_SendData(I2C_TypeDef *I2Cx, uint8_t Data);
void I2C_DMACmd(I2C_TypeDef *I2Cx, uint32_t I2C_DMAReq, FunctionalState NewState);
void I2C_TxDMAITthreshold(uint32_t TxDMAValue);
void I2C_RxDMAITthreshold(uint32_t RxDMAValue);
FlagStatus I2C_GetFlagStatus(I2C_TypeDef *I2Cx, uint32_t I2C_FLAG);
FlagStatus I2C_GetITStatus(I2C_TypeDef *I2Cx, uint32_t I2C_STATUS);
void I2C_ClearITPendingBit(I2C_TypeDef *I2Cx, uint32_t I2C_IT);
void I2C_ITConfig(I2C_TypeDef *I2Cx, uint32_t I2C_IT, FunctionalState NewState);

/*software IIC fuction*/
void IIC_Init(void);
uint8_t AT24CXX_ReadOneByte(uint16_t ReadAddr);                                   //指定地址读取一个字节
void AT24CXX_WriteOneByte(uint16_t WriteAddr, uint8_t DataToWrite);               //指定地址写入一个字节
void AT24CXX_WriteLenByte(uint16_t WriteAddr, uint32_t DataToWrite, uint8_t Len); //指定地址开始写入指定长度的数据
uint32_t AT24CXX_ReadLenByte(uint16_t ReadAddr, uint8_t Len);                     //指定地址开始读取指定长度数据
void AT24CXX_Write(uint16_t WriteAddr, uint8_t *pBuffer, uint16_t NumToWrite);    //从指定地址开始写入指定长度的数据
void AT24CXX_Read(uint16_t ReadAddr, uint8_t *pBuffer, uint16_t NumToRead);       //从指定地址开始读出指定长度的数据
#endif
