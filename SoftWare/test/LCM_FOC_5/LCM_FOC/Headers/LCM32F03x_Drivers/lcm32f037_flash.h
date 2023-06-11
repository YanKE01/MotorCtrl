#ifndef LCM32F037_FLASH_H
#define LCM32F037_FLASH_H
#include "LCM32F037.h"
#include "stdint.h"
#include "lcm32f037_conf.h"

#define __REG(addr) (*(volatile uint32_t *)(addr))
#define __REGH(addr) (*(volatile uint16_t *)(addr))
#define __REGB(addr) (*(volatile uint8_t *)(addr))
#define WR_REG(addr, data) (__REG((addr)) = (data))
#define WR_REGH(addr, data) (__REGH((addr)) = (data))
#define WR_REGB(addr, data) (__REGB((addr)) = (data))
#define RD_REG(addr) (__REG((addr)))
#define RD_REGH(addr) (__REGH((addr)))
#define RD_REGB(addr) (__REGB((addr)))
/** 
  * @brief  FLASH Status
  */
typedef enum
{
  FLASH_BUSY = 1,
  FLASH_ERROR_WRP,
  FLASH_ERROR_PROGRAM,
  FLASH_COMPLETE,
  FLASH_TIMEOUT
} FLASH_Status;

typedef struct
{
  __IO uint16_t USER; //0x0801 0000
  /*
  __IO uint16_t DATA0;//0x0801 0002
  __IO uint32_t DATA1;//0x0801 0004
  __IO uint32_t DATA2;//0x0801 0006
  */
  __IO uint16_t DATA[3];
  /*
  __IO uint16_t WRP0;//0x0801 0008 //<FLASH option byte write protection 0,
  __IO uint16_t WRP1;//0x0801 000A //<FLASH option byte write protection 1,
  __IO uint16_t WRP2;//0x0801 000C //<FLASH option byte write protection 2,
  __IO uint16_t WRP3;//0x0801 000E //<FLASH option byte write protection 3,
  */
  __IO uint16_t WRP[4];
  /*
  __IO uint16_t RDP0;//0x0801 0010
  __IO uint16_t RDP1;//0x0801 0012
  __IO uint16_t RDP2;//0x0801 0014
  __IO uint16_t RDP3;//0x0801 0016
  __IO uint16_t RDP4;//0x0801 0018
  __IO uint16_t RDP5;//0X0801 001A
  __IO uint16_t RDP6;//0x0801 001C
  __IO uint16_t RDP7;//0x0801 001E
  */
  __IO uint16_t RDP[8];
  /*
  __IO uint16_t RDP8;//0x0801 0020
  __IO uint16_t RDP9;//0x0801 0022
  __IO uint16_t RDP10;//0x0801 0024
  __IO uint16_t RDP11;//0x0801 0026
  */
  __IO uint16_t RDP2[4];
} OB_TypeDef;

#define FLASH_Latency_0 ((uint32_t)0x00000000) /*!< FLASH Zero Latency cycle */
#define FLASH_Latency_1 ((uint32_t)0x00000001) /*!< FLASH One Latency cycle */
#define FLASH_Latency_2 ((uint32_t)0x00000002) /*!< FLASH Two Latency cycle */

#define IS_FLASH_LATENCY(LATENCY) (((LATENCY) == FLASH_Latency_0) || \
                                   ((LATENCY) == FLASH_Latency_1) || \
                                   ((LATENCY) == FLASH_Latency_2))

/** @defgroup FLASH_Timeout_definition 
  * @{
  */
#define FLASH_ER_PRG_TIMEOUT ((uint32_t)0x000B0000)

/** @defgroup FLASH_Address 
  * @{
  */
#define IS_FLASH_PROGRAM_ADDRESS(ADDRESS) (((ADDRESS) >= 0x08000000) && ((ADDRESS) <= 0x0800FFFF)) /*main flash区域*/

/** 
  * @brief  FLASH_Read Protection Level  
  */
#define OB_RDP_Level_0 ((uint8_t)0xAA)
#define OB_RDP_Level_1 ((uint8_t)0xBB)
/*#define OB_RDP_Level_2   ((uint8_t)0xCC)*/ /* Warning: When enabling read protection level 2 
                                                it's no more possible to go back to level 1 or 0
                                                这�?�模式下不能使用debug，包括swd，从非main flash�?动mcu.
                                                */
#define OB_USER_DATA0 ((uint8_t)0x00)
#define OB_USER_DATA1 ((uint8_t)0x01)
#define OB_USER_DATA2 ((uint8_t)0x02)
#define IS_OB_USER_DATA(DATAx) ((DATAx == OB_USER_DATA0) || \
                                (DATAx == OB_USER_DATA1) || \
                                (DATAx == OB_USER_DATA2))

#define RDPRT2 ((uint32_t)0x00000100)
#define RDPRT ((uint32_t)0x000000FF)

#define IS_OB_RDP(LEVEL) (((LEVEL) == OB_RDP_Level_0) ||    \
                          ((LEVEL) == OB_RDP_Level_1)) /*|| \
                           ((LEVEL) == OB_RDP_Level_2))*/
/**
  * @}
  */

/** @defgroup FLASH_Flags 
  * @{
  */
#define FLASH_FLAG_BSY FLASH_SR_BSY       /*!< FLASH Busy flag */
#define FLASH_FLAG_PGERR FLASH_SR_PGERR   /*!< FLASH Programming error flag */
#define FLASH_FLAG_WRPERR FLASH_SR_WRPERR /*!< FLASH Write protected error flag */
#define FLASH_FLAG_EOP FLASH_SR_EOP       /*!< FLASH End of Programming flag */
#define IS_FLASH_CLEAR_FLAG(FLAG) ((((FLAG) & (uint32_t)0xFFFFFFC3) == 0x00000000) && ((FLAG) != 0x00000000))
#define IS_FLASH_GET_FLAG(FLASH_FLAG) ((FLASH_FLAG == FLASH_FLAG_BSY) ||     \
                                       (FLASH_FLAG == FLASH_FLAG_PGERR ||    \
                                        (FLASH_FLAG == FLASH_FLAG_WRPERR) || \
                                        (FLASH_FLAG == FLASH_FLAG_EOP)))

/*******************flash interrupt config*****************/
#define FLASH_IT_EOPIE ((uint32_t)0x00001000)
#define FLASH_IT_ERRIE ((uint32_t)0x00000400)
#define FLASH_IT_OPTWRE ((uint32_t)0x00000200)
#define IS_FLASH_IT(IT) ((IT == FLASH_IT_EOPIE) || \
                         (IT == FLASH_IT_ERRIE) || \
                         (IT == FLASH_IT_OPTWRE))

/** @defgroup FLASH_Option_Bytes_Write_Protection 
  * @{
  */
/*sector写保�?*/
#define OB_WRP_Pages0to3 ((uint32_t)0x00000001)     /* Write protection of page 0 to 3 */
#define OB_WRP_Pages4to7 ((uint32_t)0x00000002)     /* Write protection of page 4 to 7 */
#define OB_WRP_Pages8to11 ((uint32_t)0x00000004)    /* Write protection of page 8 to 11 */
#define OB_WRP_Pages12to15 ((uint32_t)0x00000008)   /* Write protection of page 12 to 15 */
#define OB_WRP_Pages16to19 ((uint32_t)0x00000010)   /* Write protection of page 16 to 19 */
#define OB_WRP_Pages20to23 ((uint32_t)0x00000020)   /* Write protection of page 20 to 23 */
#define OB_WRP_Pages24to27 ((uint32_t)0x00000040)   /* Write protection of page 24 to 27 */
#define OB_WRP_Pages28to31 ((uint32_t)0x00000080)   /* Write protection of page 28 to 31 */
#define OB_WRP_Pages32to35 ((uint32_t)0x00000100)   /* Write protection of page 32 to 35 */
#define OB_WRP_Pages36to39 ((uint32_t)0x00000200)   /* Write protection of page 36 to 39 */
#define OB_WRP_Pages40to43 ((uint32_t)0x00000400)   /* Write protection of page 40 to 43 */
#define OB_WRP_Pages44to47 ((uint32_t)0x00000800)   /* Write protection of page 44 to 47 */
#define OB_WRP_Pages48to51 ((uint32_t)0x00001000)   /* Write protection of page 48 to 51 */
#define OB_WRP_Pages52to55 ((uint32_t)0x00002000)   /* Write protection of page 52 to 55 */
#define OB_WRP_Pages56to59 ((uint32_t)0x00004000)   /* Write protection of page 56 to 59 */
#define OB_WRP_Pages60to63 ((uint32_t)0x00008000)   /* Write protection of page 60 to 63 */
#define OB_WRP_Pages64to67 ((uint32_t)0x00010000)   /* Write protection of page 64 to 67 */
#define OB_WRP_Pages68to71 ((uint32_t)0x00020000)   /* Write protection of page 68 to 71 */
#define OB_WRP_Pages72to75 ((uint32_t)0x00040000)   /* Write protection of page 72 to 75 */
#define OB_WRP_Pages76to79 ((uint32_t)0x00080000)   /* Write protection of page 76 to 79 */
#define OB_WRP_Pages80to83 ((uint32_t)0x00100000)   /* Write protection of page 80 to 83 */
#define OB_WRP_Pages84to87 ((uint32_t)0x00200000)   /* Write protection of page 84 to 87 */
#define OB_WRP_Pages88to91 ((uint32_t)0x00400000)   /* Write protection of page 88 to 91 */
#define OB_WRP_Pages92to95 ((uint32_t)0x00800000)   /* Write protection of page 92 to 95 */
#define OB_WRP_Pages96to99 ((uint32_t)0x01000000)   /* Write protection of page 96 to 99 */
#define OB_WRP_Pages100to103 ((uint32_t)0x02000000) /* Write protection of page 100 to 103 */
#define OB_WRP_Pages104to107 ((uint32_t)0x04000000) /* Write protection of page 104 to 107 */
#define OB_WRP_Pages108to111 ((uint32_t)0x08000000) /* Write protection of page 108 to 111 */
#define OB_WRP_Pages112to115 ((uint32_t)0x10000000) /* Write protection of page 112 to 115 */
#define OB_WRP_Pages116to119 ((uint32_t)0x20000000) /* Write protection of page 116 to 119 */
#define OB_WRP_Pages120to123 ((uint32_t)0x40000000) /* Write protection of page 120 to 123 */
#define OB_WRP_Pages124to127 ((uint32_t)0x80000000) /* Write protection of page 124 to 127 */
#define OB_WRP_AllPages ((uint32_t)0xFFFFFFFF)      /*!< Write protection of all Sectors */

#define IS_OB_WRP(PAGE) (((PAGE) != 0x0000000))

/*******************  Bit definition for FLASH_ACR register  ******************/
#define FLASH_ACR_LATENCY ((uint32_t)0x00000001) /*!< LATENCY bit (Latency) */

#define FLASH_ACR_PRFTBE ((uint32_t)0x00000010) /*!< Prefetch Buffer Enable */
#define FLASH_ACR_PRFTBS ((uint32_t)0x00000020) /*!< Prefetch Buffer Status */

/*******************  Bit definition for FLASH_CR register  *******************/
#define FLASH_CR_PG ((uint32_t)0x00000001)     /*!< Programming */
#define FLASH_CR_PER ((uint32_t)0x00000002)    /*!< Page Erase */
#define FLASH_CR_MER ((uint32_t)0x00000004)    /*!< Mass Erase */
#define FLASH_CR_OPTPG ((uint32_t)0x00000010)  /*!< Option Byte Programming */
#define FLASH_CR_OPTER ((uint32_t)0x00000020)  /*!< Option Byte Erase */
#define FLASH_CR_STRT ((uint32_t)0x00000040)   /*!< Start */
#define FLASH_CR_LOCK ((uint32_t)0x00000080)   /*!< Lock */
#define FLASH_CR_OPTWRE ((uint32_t)0x00000200) /*!< Option Bytes Write Enable */
#define FLASH_CR_ERRIE ((uint32_t)0x00000400)  /*!< Error Interrupt Enable */
#define FLASH_CR_EOPIE ((uint32_t)0x00001000)  /*!< End of operation interrupt enable */

/******************  FLASH Keys  **********************************************/
#define FLASH_FKEY1 ((uint32_t)0x45670123) /*!< Flash program erase key1 */
#define FLASH_FKEY2 ((uint32_t)0xCDEF89AB) /*!< Flash program erase key2: used with FLASH_PEKEY1 \
                                                to unlock the write access to the FPEC. */
/****************** BOOT selection & BOOT pin & BOOT bit *********************/
#define OB_SWD_PA13PA14 ((uint_8)0xEF)
#define OB_SWD_PA9PA10 ((uint_8)0xFF)
#define OB_IWDG_HARD ((uint_8)0xF7)
#define OB_IWDG_SOFT ((uint_8)0xEF)
#define OB_BOOT0_HARD ((uint_8)0xFB)
#define OB_BOOT0_SOFT ((uint_8)0xFF)
#define OB_BOOT1_L ((uint_8)0xFD)
#define OB_BOOT1_H ((uint_8)0xFF)
#define OB_BOOT0_L ((uint_8)0xFE)
#define OB_BOOT0_H ((uint_8)0xFF)

#define IS_OB_SWD_SEL(sources) ((sources == OB_SWD_PA13PA14) || (sources == OB_SWD_PA9PA10))
#define IS_OB_BOOT_SEL(sources) ((sources == OB_BOOT_HARD) || (sources == OB_BOOT_SOFT))
#define IS_OB_BOOT1(BOOT1) ((BOOT1 == OB_BOOT1_L) || (BOOT1 == OB_BOOT1_H))
#define IS_OB_BOOT0(BOOT0) ((BOOT0 == OB_BOOT0_L) || (BOOT0 == OB_BOOT0_H))

#define IS_OB_IWDG(CFG) ((CFG == OB_IWDG_HARD) || (CFG == IWDG_SOFT))

#define FLASH_SMKEYR1 ((uint32_t)0x4567FEDC)
#define FLASH_SMKEYR2 ((uint32_t)0xBA980123)

/************** Bit Definition for EFLS_CTRL_OPTKEYR Register ************/
#define FLASH_OPTKEY1 ((uint32_t)0x45670123)
#define FLASH_OPTKEY2 ((uint32_t)0xCDEF89AB)

/******************  Bit definition for FLASH_SR register  *******************/
#define FLASH_SR_BSY ((uint32_t)0x00000001)    /*!< Busy */
#define FLASH_SR_PGERR ((uint32_t)0x00000004)  /*!< Programming Error */
#define FLASH_SR_WRPERR ((uint32_t)0x00000010) /*!< Write Protection Error */
#define FLASH_SR_EOP ((uint32_t)0x00000020)    /*!< End of operation */

/******************  Bit definition for OB_WRP0 register  *********************/
#define OB_WRP0_WRP0 ((uint32_t)0x000000FF)  /*!< Flash memory write protection option bytes */
#define OB_WRP0_nWRP0 ((uint32_t)0x0000FF00) /*!< Flash memory write protection complemented option bytes */

/******************  Bit definition for OB_WRP1 register  *********************/
#define OB_WRP1_WRP1 ((uint32_t)0x00FF0000)  /*!< Flash memory write protection option bytes */
#define OB_WRP1_nWRP1 ((uint32_t)0xFF000000) /*!< Flash memory write protection complemented option bytes */

/******************  Bit definition for OB_WRP0 register  *********************/
#define OB_WRP0_WRP2 ((uint32_t)0x000000FF)  /*!< Flash memory write protection option bytes */
#define OB_WRP0_nWRP2 ((uint32_t)0x0000FF00) /*!< Flash memory write protection complemented option bytes */

/******************  Bit definition for OB_WRP1 register  *********************/
#define OB_WRP1_WRP3 ((uint32_t)0x00FF0000)  /*!< Flash memory write protection option bytes */
#define OB_WRP1_nWRP3 ((uint32_t)0xFF000000) /*!< Flash memory write protection complemented option bytes */

#define FLASH_ACR_PRFTBS_Pos (5UL)    /*!< PRFTBS (Bit 5)                                        */
#define FLASH_ACR_PRFTBS_Msk (0x20UL) /*!< PRFTBS (Bitfield-Mask: 0x01)                          */
#define FLASH_ACR_PRFTBE_Pos (4UL)    /*!< PRFTBE (Bit 4)                                        */
#define FLASH_ACR_PRFTBE_Msk (0x10UL) /*!< PRFTBE (Bitfield-Mask: 0x01)                          */
#define FLASH_ACR_LATENCY_Pos (0UL)   /*!< LATENCY (Bit 0)                                       */
#define FLASH_ACR_LATENCY_Msk (0x7UL) /*!< LATENCY (Bitfield-Mask: 0x07)                         */
/* =========================================================  KEYR  ========================================================== */
#define FLASH_KEYR_FKEY_Pos (0UL)          /*!< FKEY (Bit 0)                                          */
#define FLASH_KEYR_FKEY_Msk (0xffffffffUL) /*!< FKEY (Bitfield-Mask: 0xffffffff)                      */
/* ========================================================  OPTKEYR  ======================================================== */
#define FLASH_OPTKEYR_OPTKEY_Pos (0UL)          /*!< OPTKEY (Bit 0)                                        */
#define FLASH_OPTKEYR_OPTKEY_Msk (0xffffffffUL) /*!< OPTKEY (Bitfield-Mask: 0xffffffff)                    */
/* ==========================================================  SR  =========================================================== */
#define FLASH_SR_OBERR_Pos (20UL)              /*!< OBERR (Bit 20)                                        */
#define FLASH_SR_OBERR_Msk (0x100000UL)        /*!< OBERR (Bitfield-Mask: 0x01)                           */
#define FLASH_SR_OB_EMPTY_FLAG_Pos (19UL)      /*!< OB_EMPTY_FLAG (Bit 19)                                */
#define FLASH_SR_OB_EMPTY_FLAG_Msk (0x80000UL) /*!< OB_EMPTY_FLAG (Bitfield-Mask: 0x01)                   */
#define FLASH_SR_OB_BOOT0_PIN_Pos (18UL)       /*!< OB_BOOT0_PIN (Bit 18)                                 */
#define FLASH_SR_OB_BOOT0_PIN_Msk (0x40000UL)  /*!< OB_BOOT0_PIN (Bitfield-Mask: 0x01)                    */
#define FLASH_SR_OB_BOOT_MODE_Pos (16UL)       /*!< OB_BOOT_MODE (Bit 16)                                 */
#define FLASH_SR_OB_BOOT_MODE_Msk (0x30000UL)  /*!< OB_BOOT_MODE (Bitfield-Mask: 0x03)                    */
#define FLASH_SR_EOP_Pos (5UL)                 /*!< EOP (Bit 5)                                           */
#define FLASH_SR_EOP_Msk (0x20UL)              /*!< EOP (Bitfield-Mask: 0x01)                             */
#define FLASH_SR_WRPRTERR_Pos (4UL)            /*!< WRPRTERR (Bit 4)                                      */
#define FLASH_SR_WRPRTERR_Msk (0x10UL)         /*!< WRPRTERR (Bitfield-Mask: 0x01)                        */
#define FLASH_SR_PGERR_Pos (2UL)               /*!< PGERR (Bit 2)                                         */
#define FLASH_SR_PGERR_Msk (0x4UL)             /*!< PGERR (Bitfield-Mask: 0x01)                           */
#define FLASH_SR_BSY_Pos (0UL)                 /*!< BSY (Bit 0)                                           */
#define FLASH_SR_BSY_Msk (0x1UL)               /*!< BSY (Bitfield-Mask: 0x01)                             */
/* ==========================================================  CR  =========================================================== */
#define FLASH_CR_BOOT_MODE_Pos (24UL)        /*!< BOOT_MODE (Bit 24)                                    */
#define FLASH_CR_BOOT_MODE_Msk (0x3000000UL) /*!< BOOT_MODE (Bitfield-Mask: 0x03)                       */
#define FLASH_CR_SMLOCK_Pos (16UL)           /*!< SMLOCK (Bit 16)                                       */
#define FLASH_CR_SMLOCK_Msk (0x10000UL)      /*!< SMLOCK (Bitfield-Mask: 0x01)                          */
#define FLASH_CR_EOPIE_Pos (12UL)            /*!< EOPIE (Bit 12)                                        */
#define FLASH_CR_EOPIE_Msk (0x1000UL)        /*!< EOPIE (Bitfield-Mask: 0x01)                           */
#define FLASH_CR_ERRIE_Pos (10UL)            /*!< ERRIE (Bit 10)                                        */
#define FLASH_CR_ERRIE_Msk (0x400UL)         /*!< ERRIE (Bitfield-Mask: 0x01)                           */
#define FLASH_CR_OPTWRE_Pos (9UL)            /*!< OPTWRE (Bit 9)                                        */
#define FLASH_CR_OPTWRE_Msk (0x200UL)        /*!< OPTWRE (Bitfield-Mask: 0x01)                          */
#define FLASH_CR_LOCK_Pos (7UL)              /*!< LOCK (Bit 7)                                          */
#define FLASH_CR_LOCK_Msk (0x80UL)           /*!< LOCK (Bitfield-Mask: 0x01)                            */
#define FLASH_CR_STRT_Pos (6UL)              /*!< STRT (Bit 6)                                          */
#define FLASH_CR_STRT_Msk (0x40UL)           /*!< STRT (Bitfield-Mask: 0x01)                            */
#define FLASH_CR_OPTER_Pos (5UL)             /*!< OPTER (Bit 5)                                         */
#define FLASH_CR_OPTER_Msk (0x20UL)          /*!< OPTER (Bitfield-Mask: 0x01)                           */
#define FLASH_CR_OPTPG_Pos (4UL)             /*!< OPTPG (Bit 4)                                         */
#define FLASH_CR_OPTPG_Msk (0x10UL)          /*!< OPTPG (Bitfield-Mask: 0x01)                           */
#define FLASH_CR_MER_Pos (2UL)               /*!< MER (Bit 2)                                           */
#define FLASH_CR_MER_Msk (0x4UL)             /*!< MER (Bitfield-Mask: 0x01)                             */
#define FLASH_CR_PG_Pos (0UL)                /*!< PG (Bit 0)                                            */
#define FLASH_CR_PG_Msk (0x1UL)              /*!< PG (Bitfield-Mask: 0x01)                              */
/* ==========================================================  AR  =========================================================== */
#define FLASH_AR_FAR_Pos (0UL)          /*!< FAR (Bit 0)                                           */
#define FLASH_AR_FAR_Msk (0xffffffffUL) /*!< FAR (Bitfield-Mask: 0xffffffff)                       */
/* ==========================================================  OBR  ========================================================== */
#define FLASH_OBR_DATA2_Pos (24UL)         /*!< DATA2 (Bit 24)                                        */
#define FLASH_OBR_DATA2_Msk (0xff000000UL) /*!< DATA2 (Bitfield-Mask: 0xff)                           */
#define FLASH_OBR_DATA1_Pos (16UL)         /*!< DATA1 (Bit 16)                                        */
#define FLASH_OBR_DATA1_Msk (0xff0000UL)   /*!< DATA1 (Bitfield-Mask: 0xff)                           */
#define FLASH_OBR_DATA0_Pos (8UL)          /*!< DATA0 (Bit 8)                                         */
#define FLASH_OBR_DATA0_Msk (0xff00UL)     /*!< DATA0 (Bitfield-Mask: 0xff)                           */
#define FLASH_OBR_SWDSEL_Pos (4UL)         /*!< SWDSEL (Bit 4)                                        */
#define FLASH_OBR_SWDSEL_Msk (0x10UL)      /*!< SWDSEL (Bitfield-Mask: 0x01)                          */
#define FLASH_OBR_WDG_SW_Pos (3UL)         /*!< WDG_SW (Bit 3)                                        */
#define FLASH_OBR_WDG_SW_Msk (0x8UL)       /*!< WDG_SW (Bitfield-Mask: 0x01)                          */
#define FLASH_OBR_BOOT_SEL_Pos (2UL)       /*!< BOOT_SEL (Bit 2)                                      */
#define FLASH_OBR_BOOT_SEL_Msk (0x4UL)     /*!< BOOT_SEL (Bitfield-Mask: 0x01)                        */
#define FLASH_OBR_nBOOT1_Pos (1UL)         /*!< nBOOT1 (Bit 1)                                        */
#define FLASH_OBR_nBOOT1_Msk (0x2UL)       /*!< nBOOT1 (Bitfield-Mask: 0x01)                          */
#define FLASH_OBR_nBOOT0_Pos (0UL)         /*!< nBOOT0 (Bit 0)                                        */
#define FLASH_OBR_nBOOT0_Msk (0x1UL)       /*!< nBOOT0 (Bitfield-Mask: 0x01)                          */
/* =========================================================  CAL1  ========================================================== */
#define FLASH_CAL1_CAL1_Pos (0UL)          /*!< CAL1 (Bit 0)                                          */
#define FLASH_CAL1_CAL1_Msk (0xffffffffUL) /*!< CAL1 (Bitfield-Mask: 0xffffffff)                      */
/* =========================================================  RDPR  ========================================================== */
#define FLASH_RDPR_RDPRT2_Pos (8UL)     /*!< RDPRT2 (Bit 8)                                        */
#define FLASH_RDPR_RDPRT2_Msk (0x100UL) /*!< RDPRT2 (Bitfield-Mask: 0x01)                          */
#define FLASH_RDPR_RDPRT_Pos (0UL)      /*!< RDPRT (Bit 0)                                         */
#define FLASH_RDPR_RDPRT_Msk (0xffUL)   /*!< RDPRT (Bitfield-Mask: 0xff)                           */
/* =========================================================  WRPR  ========================================================== */
#define FLASH_WRPR_WRP_Pos (0UL)          /*!< WRP (Bit 0)                                           */
#define FLASH_WRPR_WRP_Msk (0xffffffffUL) /*!< WRP (Bitfield-Mask: 0xffffffff)                       */
/* =========================================================  CAL2  ========================================================== */
#define FLASH_CAL2_CAL2_Pos (0UL)          /*!< CAL2 (Bit 0)                                          */
#define FLASH_CAL2_CAL2_Msk (0xffffffffUL) /*!< CAL2 (Bitfield-Mask: 0xffffffff)                      */
/* =========================================================  CAL3  ========================================================== */
#define FLASH_CAL3_CAL3_Pos (0UL)          /*!< CAL3 (Bit 0)                                          */
#define FLASH_CAL3_CAL3_Msk (0xffffffffUL) /*!< CAL3 (Bitfield-Mask: 0xffffffff)                      */
/* =========================================================  CAL4  ========================================================== */
#define FLASH_CAL4_CAL4_Pos (0UL)          /*!< CAL4 (Bit 0)                                          */
#define FLASH_CAL4_CAL4_Msk (0xffffffffUL) /*!< CAL4 (Bitfield-Mask: 0xffffffff)                      */
/* ==========================================================  DEV  ========================================================== */
#define FLASH_DEV_DEV_Pos (0UL)          /*!< DEV (Bit 0)                                           */
#define FLASH_DEV_DEV_Msk (0xffffffffUL) /*!< DEV (Bitfield-Mask: 0xffffffff)                       */
/* ========================================================  SMKEYR  ========================================================= */
#define FLASH_SMKEYR_SMKEY_Pos (0UL)          /*!< SMKEY (Bit 0)                                         */
#define FLASH_SMKEYR_SMKEY_Msk (0xffffffffUL) /*!< SMKEY (Bitfield-Mask: 0xffffffff)                     */

/******************* 函数声明***************************************************/

//#define FLASH_CR_STRT_Pos           6
//#define FLASH_CR_STRT_Msk           (0x1UL << EFLS_CTRL_CR_STRT_Pos)
//#define FLASH_CR_OPTER_Pos          5
//#define FLASH_CR_OPTER_Msk          (0x1UL << EFLS_CTRL_CR_OPTER_Pos)
//#define FLASH_CR_OPTPG_Pos          4
//#define FLASH_CR_OPTPG_Msk          (0x1UL << EFLS_CTRL_CR_OPTPG_Pos)
//#define FLASH_CR_MER_Pos            2
//#define FLASH_CR_MER_Msk            (0x1UL << EFLS_CTRL_CR_MER_Pos)
#define FLASH_CR_PER_Pos 1
#define FLASH_CR_PER_Msk (0x1UL << EFLS_CTRL_CR_PER_Pos)
//#define FLASH_CR_PG_Pos             0
//#define FLASH_CR_PG_Msk             (0x1UL << EFLS_CTRL_CR_PG_Pos)
//#define FLASH_PG_ON                 (0x1UL << EFLS_CTRL_CR_PG_Pos)
//#define FALSH_PG_OFF                (0x0UL << EFLS_CTRL_CR_PG_Pos)

FLASH_Status FLASH_WaitForLastOperation(uint32_t Timeout);
FLASH_Status FLASH_GetStatus(void);
FlagStatus FLASH_OB_GetRDP(void);
void FLASH_SetLatency(uint32_t FLASH_Latency);
FlagStatus FLASH_GetPrefetchBufferStatus(void);
void FLASH_PrefetchBufferCmd(FunctionalState NewState);
void FLASH_Unlock(void);
void FLASH_Lock(void);
FLASH_Status FLASH_ErasePage(uint32_t Page_Address);
FLASH_Status FLASH_EraseAllPages(void);
FLASH_Status FLASH_ProgramWord(uint32_t Address, uint32_t Data);
FLASH_Status FLASH_ProgramHalfWord(uint32_t Address, uint16_t Data);
void FLASH_OB_Unlock(void);
void FLASH_OB_Lock(void);
void FLASH_OB_Launch(void);
FLASH_Status FLASH_OB_Erase(void);
FLASH_Status FLASH_OB_EnableWRP(uint32_t OB_WRP);
FLASH_Status FLASH_OB_RDPConfig(uint8_t OB_RDP);
FLASH_Status FLASH_OB_USERConfig(uint8_t SWD_SEL, uint8_t IWDG_SEL, uint8_t OB_BOOT_SEL, uint8_t OB_BOOT1, uint8_t OB_BOOT0);
FLASH_Status FLASH_OB_ProgramData(uint8_t DATAx, uint8_t OB_DATA);
void FLASH_ITConfig(uint32_t FLASH_IT, FunctionalState NewState);
FlagStatus FLASH_GetFlagStatus(uint32_t FLASH_FLAG);
uint8_t FLASH_OB_GetUser(void);
uint32_t FLASH_OB_GetWRP(void);
FLASH_Status FLASH_WaitForLastOperation(uint32_t Timeout);
FLASH_Status FLASH_GetStatus(void);
void FLASH_ClearFlag(uint32_t FLASH_FLAG);
FlagStatus FLASH_OB_GetRDP(void);
void ERASE_OPT(void);
void write_opt_flash_n(unsigned int addr, unsigned int data);
void ERASE_SYSTEM_MERMORY(void);
void write_sm_flash_n(unsigned int addr, unsigned int data);

void opa1_trim1(uint32_t trim);
void opa2_trim1(uint32_t trim);
void opa0_trim1(uint32_t trim);
void rcl_trim(uint32_t trim);
void rch_trim(uint32_t trim);
void bgr_trim(uint32_t trim);
void adc_trim(uint32_t trim);
void mco_set(uint32_t sel, uint32_t div);

#endif
