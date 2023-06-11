#ifndef LCM32F037_TIM_H
#define LCM32F037_TIM_H

#include "stdint.h"
#include "core_cm0.h"
#include "lcm32f037.h"

/*******************  Bit definition for TIM_CR1 register  ********************/
#define TIM_CR1_CEN ((uint16_t)0x0001)  /*!<Counter enable */
#define TIM_CR1_UDIS ((uint16_t)0x0002) /*!<Update disable */
#define TIM_CR1_URS ((uint16_t)0x0004)  /*!<Update request source */
#define TIM_CR1_OPM ((uint16_t)0x0008)  /*!<One pulse mode */
#define TIM_CR1_DIR ((uint16_t)0x0010)  /*!<Direction */

#define TIM_CR1_CMS ((uint16_t)0x0060)   /*!<CMS[1:0] bits (Center-aligned mode selection) */
#define TIM_CR1_CMS_0 ((uint16_t)0x0020) /*!<Bit 0 */
#define TIM_CR1_CMS_1 ((uint16_t)0x0040) /*!<Bit 1 */

#define TIM_CR1_ARPE ((uint16_t)0x0080) /*!<Auto-reload preload enable */

#define TIM_CR1_CKD ((uint16_t)0x0300)   /*!<CKD[1:0] bits (clock division) */
#define TIM_CR1_CKD_0 ((uint16_t)0x0000) 
#define TIM_CR1_CKD_2 ((uint16_t)0x0100) 
#define TIM_CR1_CKD_4 ((uint16_t)0x0200) 

#define TIM_CR1_DTSE ((uint16_t)0x00010000) /*!<DTS clock enable */
#define TIM_CR1_ETRE ((uint16_t)0x00020000) /*!<ETRE input detection/filter enable */
#define TIM_CR1_TI1E ((uint16_t)0x00040000) /*!<TI1E input detection/filter enable */
#define TIM_CR1_TI2E ((uint16_t)0x00080000) /*!<TI2E input detection/filter enable */

#define TIM_CR1_CENNCE ((uint16_t)0x00400000) /*!<OCREF clear enable when CEN disable */
#define TIM_CR1_OCF ((uint16_t)0x00800000)    /*!<OC/OCN filter enable */

#define TIM_CR1_AS ((uint16_t)0x01000000) /*!<shadow register enable */

/*******************  Bit definition for TIM_CR2 register  ********************/
#define TIM_CR2_CCPC ((uint16_t)0x0001) /*!<Capture/Compare Preloaded Control */
#define TIM_CR2_CCUS ((uint16_t)0x0004) /*!<Capture/Compare Control Update Selection */
#define TIM_CR2_CCDS ((uint16_t)0x0008) /*!<Capture/Compare DMA Selection */

#define TIM_CR2_MMS ((uint16_t)0x0070)   /*!<MMS[2:0] bits (Master Mode Selection) */
#define TIM_CR2_MMS_0 ((uint16_t)0x0010) /*!<Bit 0 */
#define TIM_CR2_MMS_1 ((uint16_t)0x0020) /*!<Bit 1 */
#define TIM_CR2_MMS_2 ((uint16_t)0x0040) /*!<Bit 2 */

#define TIM_CR2_TI1S ((uint16_t)0x0080)  /*!<TI1 Selection */
#define TIM_CR2_OIS1 ((uint16_t)0x0100)  /*!<Output Idle state 1 (OC1 output) */
#define TIM_CR2_OIS1N ((uint16_t)0x0200) /*!<Output Idle state 1 (OC1N output) */
#define TIM_CR2_OIS2 ((uint16_t)0x0400)  /*!<Output Idle state 2 (OC2 output) */
#define TIM_CR2_OIS2N ((uint16_t)0x0800) /*!<Output Idle state 2 (OC2N output) */
#define TIM_CR2_OIS3 ((uint16_t)0x1000)  /*!<Output Idle state 3 (OC3 output) */
#define TIM_CR2_OIS3N ((uint16_t)0x2000) /*!<Output Idle state 3 (OC3N output) */
#define TIM_CR2_OIS4 ((uint16_t)0x4000)  /*!<Output Idle state 4 (OC4 output) */

#define TIM_CR2_TrigS ((uint16_t)0x00010000) /*!<TIMx_oc1_trig choose  1:oc1&cen  0:cen */

/*******************  Bit definition for TIM_SMCR register  *******************/
#define TIM_SMCR_SMS ((uint16_t)0x0007)   /*!<SMS[2:0] bits (Slave mode selection) */
#define TIM_SMCR_SMS_0 ((uint16_t)0x0001) /*!<Bit 0 */
#define TIM_SMCR_SMS_1 ((uint16_t)0x0002) /*!<Bit 1 */
#define TIM_SMCR_SMS_2 ((uint16_t)0x0004) /*!<Bit 2 */

#define TIM_SMCR_OCCS ((uint16_t)0x0008) /*!< OCREF clear selection */

#define TIM_SMCR_TS ((uint16_t)0x0070)   /*!<TS[2:0] bits (Trigger selection) */
#define TIM_SMCR_TS_0 ((uint16_t)0x0010) /*!<Bit 0 */
#define TIM_SMCR_TS_1 ((uint16_t)0x0020) /*!<Bit 1 */
#define TIM_SMCR_TS_2 ((uint16_t)0x0040) /*!<Bit 2 */

#define TIM_SMCR_MSM ((uint16_t)0x0080) /*!<Master/slave mode */

#define TIM_SMCR_ETF ((uint16_t)0x0F00)   /*!<ETF[3:0] bits (External trigger filter) */
#define TIM_SMCR_ETF_0 ((uint16_t)0x0100) /*!<Bit 0 */
#define TIM_SMCR_ETF_1 ((uint16_t)0x0200) /*!<Bit 1 */
#define TIM_SMCR_ETF_2 ((uint16_t)0x0400) /*!<Bit 2 */
#define TIM_SMCR_ETF_3 ((uint16_t)0x0800) /*!<Bit 3 */

#define TIM_SMCR_ETPS ((uint16_t)0x3000)   /*!<ETPS[1:0] bits (External trigger prescaler) */
#define TIM_SMCR_ETPS_0 ((uint16_t)0x1000) /*!<Bit 0 */
#define TIM_SMCR_ETPS_1 ((uint16_t)0x2000) /*!<Bit 1 */

#define TIM_SMCR_ECE ((uint16_t)0x4000) /*!<External clock enable */
#define TIM_SMCR_ETP ((uint16_t)0x8000) /*!<External trigger polarity */

/*******************  Bit definition for TIM_DIER register  *******************/
#define TIM_DIER_UIE ((uint16_t)0x0001)   /*!<Update interrupt enable */
#define TIM_DIER_CC1IE ((uint16_t)0x0002) /*!<Capture/Compare 1 interrupt enable */
#define TIM_DIER_CC2IE ((uint16_t)0x0004) /*!<Capture/Compare 2 interrupt enable */
#define TIM_DIER_CC3IE ((uint16_t)0x0008) /*!<Capture/Compare 3 interrupt enable */
#define TIM_DIER_CC4IE ((uint16_t)0x0010) /*!<Capture/Compare 4 interrupt enable */
#define TIM_DIER_COMIE ((uint16_t)0x0020) /*!<COM interrupt enable */
#define TIM_DIER_TIE ((uint16_t)0x0040)   /*!<Trigger interrupt enable */
#define TIM_DIER_BIE ((uint16_t)0x0080)   /*!<Break interrupt enable */
#define TIM_DIER_UDE ((uint16_t)0x0100)   /*!<Update DMA request enable */
#define TIM_DIER_CC1DE ((uint16_t)0x0200) /*!<Capture/Compare 1 DMA request enable */
#define TIM_DIER_CC2DE ((uint16_t)0x0400) /*!<Capture/Compare 2 DMA request enable */
#define TIM_DIER_CC3DE ((uint16_t)0x0800) /*!<Capture/Compare 3 DMA request enable */
#define TIM_DIER_CC4DE ((uint16_t)0x1000) /*!<Capture/Compare 4 DMA request enable */
#define TIM_DIER_COMDE ((uint16_t)0x2000) /*!<COM DMA request enable */
#define TIM_DIER_TDE ((uint16_t)0x4000)   /*!<Trigger DMA request enable */

/********************  Bit definition for TIM_SR register  ********************/
#define TIM_SR_UIF ((uint16_t)0x0001)   /*!<Update interrupt Flag */
#define TIM_SR_CC1IF ((uint16_t)0x0002) /*!<Capture/Compare 1 interrupt Flag */
#define TIM_SR_CC2IF ((uint16_t)0x0004) /*!<Capture/Compare 2 interrupt Flag */
#define TIM_SR_CC3IF ((uint16_t)0x0008) /*!<Capture/Compare 3 interrupt Flag */
#define TIM_SR_CC4IF ((uint16_t)0x0010) /*!<Capture/Compare 4 interrupt Flag */
#define TIM_SR_COMIF ((uint16_t)0x0020) /*!<COM interrupt Flag */
#define TIM_SR_TIF ((uint16_t)0x0040)   /*!<Trigger interrupt Flag */
#define TIM_SR_BIF ((uint16_t)0x0080)   /*!<Break interrupt Flag */
#define TIM_SR_CC1OF ((uint16_t)0x0200) /*!<Capture/Compare 1 Overcapture Flag */
#define TIM_SR_CC2OF ((uint16_t)0x0400) /*!<Capture/Compare 2 Overcapture Flag */
#define TIM_SR_CC3OF ((uint16_t)0x0800) /*!<Capture/Compare 3 Overcapture Flag */
#define TIM_SR_CC4OF ((uint16_t)0x1000) /*!<Capture/Compare 4 Overcapture Flag */

/*******************  Bit definition for TIM_EGR register  ********************/
#define TIM_EGR_UG ((uint8_t)0x01)   /*!<Update Generation */
#define TIM_EGR_CC1G ((uint8_t)0x02) /*!<Capture/Compare 1 Generation */
#define TIM_EGR_CC2G ((uint8_t)0x04) /*!<Capture/Compare 2 Generation */
#define TIM_EGR_CC3G ((uint8_t)0x08) /*!<Capture/Compare 3 Generation */
#define TIM_EGR_CC4G ((uint8_t)0x10) /*!<Capture/Compare 4 Generation */
#define TIM_EGR_COMG ((uint8_t)0x20) /*!<Capture/Compare Control Update Generation */
#define TIM_EGR_TG ((uint8_t)0x40)   /*!<Trigger Generation */
#define TIM_EGR_BG ((uint8_t)0x80)   /*!<Break Generation */

/******************  Bit definition for TIM_CCMR1 register  *******************/
#define TIM_CCMR1_CC1S ((uint16_t)0x0003)   /*!<CC1S[1:0] bits (Capture/Compare 1 Selection) */
#define TIM_CCMR1_CC1S_0 ((uint16_t)0x0001) /*!<Bit 0 */
#define TIM_CCMR1_CC1S_1 ((uint16_t)0x0002) /*!<Bit 1 */

#define TIM_CCMR1_OC1FE ((uint16_t)0x0004) /*!<Output Compare 1 Fast enable */
#define TIM_CCMR1_OC1PE ((uint16_t)0x0008) /*!<Output Compare 1 Preload enable */

#define TIM_CCMR1_OC1M ((uint16_t)0x0070)   /*!<OC1M[2:0] bits (Output Compare 1 Mode) */
#define TIM_CCMR1_OC1M_0 ((uint16_t)0x0010) /*!<Bit 0 */
#define TIM_CCMR1_OC1M_1 ((uint16_t)0x0020) /*!<Bit 1 */
#define TIM_CCMR1_OC1M_2 ((uint16_t)0x0040) /*!<Bit 2 */

#define TIM_CCMR1_OC1CE ((uint16_t)0x0080) /*!<Output Compare 1Clear Enable */

#define TIM_CCMR1_CC2S ((uint16_t)0x0300)   /*!<CC2S[1:0] bits (Capture/Compare 2 Selection) */
#define TIM_CCMR1_CC2S_0 ((uint16_t)0x0100) /*!<Bit 0 */
#define TIM_CCMR1_CC2S_1 ((uint16_t)0x0200) /*!<Bit 1 */

#define TIM_CCMR1_OC2FE ((uint16_t)0x0400) /*!<Output Compare 2 Fast enable */
#define TIM_CCMR1_OC2PE ((uint16_t)0x0800) /*!<Output Compare 2 Preload enable */

#define TIM_CCMR1_OC2M ((uint16_t)0x7000)   /*!<OC2M[2:0] bits (Output Compare 2 Mode) */
#define TIM_CCMR1_OC2M_0 ((uint16_t)0x1000) /*!<Bit 0 */
#define TIM_CCMR1_OC2M_1 ((uint16_t)0x2000) /*!<Bit 1 */
#define TIM_CCMR1_OC2M_2 ((uint16_t)0x4000) /*!<Bit 2 */

#define TIM_CCMR1_OC2CE ((uint16_t)0x8000) /*!<Output Compare 2 Clear Enable */

/*----------------------------------------------------------------------------*/

#define TIM_CCMR1_IC1PSC ((uint16_t)0x000C)   /*!<IC1PSC[1:0] bits (Input Capture 1 Prescaler) */
#define TIM_CCMR1_IC1PSC_0 ((uint16_t)0x0004) /*!<Bit 0 */
#define TIM_CCMR1_IC1PSC_1 ((uint16_t)0x0008) /*!<Bit 1 */

#define TIM_CCMR1_IC1F ((uint16_t)0x00F0)   /*!<IC1F[3:0] bits (Input Capture 1 Filter) */
#define TIM_CCMR1_IC1F_0 ((uint16_t)0x0010) /*!<Bit 0 */
#define TIM_CCMR1_IC1F_1 ((uint16_t)0x0020) /*!<Bit 1 */
#define TIM_CCMR1_IC1F_2 ((uint16_t)0x0040) /*!<Bit 2 */
#define TIM_CCMR1_IC1F_3 ((uint16_t)0x0080) /*!<Bit 3 */

#define TIM_CCMR1_IC2PSC ((uint16_t)0x0C00)   /*!<IC2PSC[1:0] bits (Input Capture 2 Prescaler) */
#define TIM_CCMR1_IC2PSC_0 ((uint16_t)0x0400) /*!<Bit 0 */
#define TIM_CCMR1_IC2PSC_1 ((uint16_t)0x0800) /*!<Bit 1 */

#define TIM_CCMR1_IC2F ((uint16_t)0xF000)   /*!<IC2F[3:0] bits (Input Capture 2 Filter) */
#define TIM_CCMR1_IC2F_0 ((uint16_t)0x1000) /*!<Bit 0 */
#define TIM_CCMR1_IC2F_1 ((uint16_t)0x2000) /*!<Bit 1 */
#define TIM_CCMR1_IC2F_2 ((uint16_t)0x4000) /*!<Bit 2 */
#define TIM_CCMR1_IC2F_3 ((uint16_t)0x8000) /*!<Bit 3 */

/******************  Bit definition for TIM_CCMR2 register  *******************/
#define TIM_CCMR2_CC3S ((uint16_t)0x0003)   /*!<CC3S[1:0] bits (Capture/Compare 3 Selection) */
#define TIM_CCMR2_CC3S_0 ((uint16_t)0x0001) /*!<Bit 0 */
#define TIM_CCMR2_CC3S_1 ((uint16_t)0x0002) /*!<Bit 1 */

#define TIM_CCMR2_OC3FE ((uint16_t)0x0004) /*!<Output Compare 3 Fast enable */
#define TIM_CCMR2_OC3PE ((uint16_t)0x0008) /*!<Output Compare 3 Preload enable */

#define TIM_CCMR2_OC3M ((uint16_t)0x0070)   /*!<OC3M[2:0] bits (Output Compare 3 Mode) */
#define TIM_CCMR2_OC3M_0 ((uint16_t)0x0010) /*!<Bit 0 */
#define TIM_CCMR2_OC3M_1 ((uint16_t)0x0020) /*!<Bit 1 */
#define TIM_CCMR2_OC3M_2 ((uint16_t)0x0040) /*!<Bit 2 */

#define TIM_CCMR2_OC3CE ((uint16_t)0x0080) /*!<Output Compare 3 Clear Enable */

#define TIM_CCMR2_CC4S ((uint16_t)0x0300)   /*!<CC4S[1:0] bits (Capture/Compare 4 Selection) */
#define TIM_CCMR2_CC4S_0 ((uint16_t)0x0100) /*!<Bit 0 */
#define TIM_CCMR2_CC4S_1 ((uint16_t)0x0200) /*!<Bit 1 */

#define TIM_CCMR2_OC4FE ((uint16_t)0x0400) /*!<Output Compare 4 Fast enable */
#define TIM_CCMR2_OC4PE ((uint16_t)0x0800) /*!<Output Compare 4 Preload enable */

#define TIM_CCMR2_OC4M ((uint16_t)0x7000)   /*!<OC4M[2:0] bits (Output Compare 4 Mode) */
#define TIM_CCMR2_OC4M_0 ((uint16_t)0x1000) /*!<Bit 0 */
#define TIM_CCMR2_OC4M_1 ((uint16_t)0x2000) /*!<Bit 1 */
#define TIM_CCMR2_OC4M_2 ((uint16_t)0x4000) /*!<Bit 2 */

#define TIM_CCMR2_OC4CE ((uint16_t)0x8000) /*!<Output Compare 4 Clear Enable */

/*----------------------------------------------------------------------------*/

#define TIM_CCMR2_IC3PSC ((uint16_t)0x000C)   /*!<IC3PSC[1:0] bits (Input Capture 3 Prescaler) */
#define TIM_CCMR2_IC3PSC_0 ((uint16_t)0x0004) /*!<Bit 0 */
#define TIM_CCMR2_IC3PSC_1 ((uint16_t)0x0008) /*!<Bit 1 */

#define TIM_CCMR2_IC3F ((uint16_t)0x00F0)   /*!<IC3F[3:0] bits (Input Capture 3 Filter) */
#define TIM_CCMR2_IC3F_0 ((uint16_t)0x0010) /*!<Bit 0 */
#define TIM_CCMR2_IC3F_1 ((uint16_t)0x0020) /*!<Bit 1 */
#define TIM_CCMR2_IC3F_2 ((uint16_t)0x0040) /*!<Bit 2 */
#define TIM_CCMR2_IC3F_3 ((uint16_t)0x0080) /*!<Bit 3 */

#define TIM_CCMR2_IC4PSC ((uint16_t)0x0C00)   /*!<IC4PSC[1:0] bits (Input Capture 4 Prescaler) */
#define TIM_CCMR2_IC4PSC_0 ((uint16_t)0x0400) /*!<Bit 0 */
#define TIM_CCMR2_IC4PSC_1 ((uint16_t)0x0800) /*!<Bit 1 */

#define TIM_CCMR2_IC4F ((uint16_t)0xF000)   /*!<IC4F[3:0] bits (Input Capture 4 Filter) */
#define TIM_CCMR2_IC4F_0 ((uint16_t)0x1000) /*!<Bit 0 */
#define TIM_CCMR2_IC4F_1 ((uint16_t)0x2000) /*!<Bit 1 */
#define TIM_CCMR2_IC4F_2 ((uint16_t)0x4000) /*!<Bit 2 */
#define TIM_CCMR2_IC4F_3 ((uint16_t)0x8000) /*!<Bit 3 */

/*******************  Bit definition for TIM_CCER register  *******************/
#define TIM_CCER_CC1E ((uint16_t)0x0001)  /*!<Capture/Compare 1 output enable */
#define TIM_CCER_CC1P ((uint16_t)0x0002)  /*!<Capture/Compare 1 output Polarity */
#define TIM_CCER_CC1NE ((uint16_t)0x0004) /*!<Capture/Compare 1 Complementary output enable */
#define TIM_CCER_CC1NP ((uint16_t)0x0008) /*!<Capture/Compare 1 Complementary output Polarity */
#define TIM_CCER_CC2E ((uint16_t)0x0010)  /*!<Capture/Compare 2 output enable */
#define TIM_CCER_CC2P ((uint16_t)0x0020)  /*!<Capture/Compare 2 output Polarity */
#define TIM_CCER_CC2NE ((uint16_t)0x0040) /*!<Capture/Compare 2 Complementary output enable */
#define TIM_CCER_CC2NP ((uint16_t)0x0080) /*!<Capture/Compare 2 Complementary output Polarity */
#define TIM_CCER_CC3E ((uint16_t)0x0100)  /*!<Capture/Compare 3 output enable */
#define TIM_CCER_CC3P ((uint16_t)0x0200)  /*!<Capture/Compare 3 output Polarity */
#define TIM_CCER_CC3NE ((uint16_t)0x0400) /*!<Capture/Compare 3 Complementary output enable */
#define TIM_CCER_CC3NP ((uint16_t)0x0800) /*!<Capture/Compare 3 Complementary output Polarity */
#define TIM_CCER_CC4E ((uint16_t)0x1000)  /*!<Capture/Compare 4 output enable */
#define TIM_CCER_CC4P ((uint16_t)0x2000)  /*!<Capture/Compare 4 output Polarity */
#define TIM_CCER_CC4NP ((uint16_t)0x8000) /*!<Capture/Compare 4 Complementary output Polarity */

/*******************  Bit definition for TIM_CNT register  ********************/
#define TIM_CNT_CNT ((uint16_t)0xFFFF) /*!<Counter Value */

/*******************  Bit definition for TIM_PSC register  ********************/
#define TIM_PSC_PSC ((uint16_t)0xFFFF) /*!<Prescaler Value */

/*******************  Bit definition for TIM_ARR register  ********************/
#define TIM_ARR_ARR ((uint16_t)0xFFFF) /*!<actual auto-reload Value */

/*******************  Bit definition for TIM_RCR register  ********************/
#define TIM_RCR_REP ((uint8_t)0xFF) /*!<Repetition Counter Value */

/*******************  Bit definition for TIM_CCR1 register  *******************/
#define TIM_CCR1_CCR1 ((uint16_t)0xFFFF) /*!<Capture/Compare 1 Value */

/*******************  Bit definition for TIM_CCR2 register  *******************/
#define TIM_CCR2_CCR2 ((uint16_t)0xFFFF) /*!<Capture/Compare 2 Value */

/*******************  Bit definition for TIM_CCR3 register  *******************/
#define TIM_CCR3_CCR3 ((uint16_t)0xFFFF) /*!<Capture/Compare 3 Value */

/*******************  Bit definition for TIM_CCR4 register  *******************/
#define TIM_CCR4_CCR4 ((uint16_t)0xFFFF) /*!<Capture/Compare 4 Value */

/*******************  Bit definition for TIM_BDTR register  *******************/
#define TIM_BDTR_DTG ((uint16_t)0x00FF)   /*!<DTG[0:7] bits (Dead-Time Generator set-up) */
#define TIM_BDTR_DTG_0 ((uint16_t)0x0001) /*!<Bit 0 */
#define TIM_BDTR_DTG_1 ((uint16_t)0x0002) /*!<Bit 1 */
#define TIM_BDTR_DTG_2 ((uint16_t)0x0004) /*!<Bit 2 */
#define TIM_BDTR_DTG_3 ((uint16_t)0x0008) /*!<Bit 3 */
#define TIM_BDTR_DTG_4 ((uint16_t)0x0010) /*!<Bit 4 */
#define TIM_BDTR_DTG_5 ((uint16_t)0x0020) /*!<Bit 5 */
#define TIM_BDTR_DTG_6 ((uint16_t)0x0040) /*!<Bit 6 */
#define TIM_BDTR_DTG_7 ((uint16_t)0x0080) /*!<Bit 7 */

#define TIM_BDTR_LOCK ((uint16_t)0x0300)   /*!<LOCK[1:0] bits (Lock Configuration) */
#define TIM_BDTR_LOCK_0 ((uint16_t)0x0100) /*!<Bit 0 */
#define TIM_BDTR_LOCK_1 ((uint16_t)0x0200) /*!<Bit 1 */

#define TIM_BDTR_OSSI ((uint16_t)0x0400) /*!<Off-State Selection for Idle mode */
#define TIM_BDTR_OSSR ((uint16_t)0x0800) /*!<Off-State Selection for Run mode */
#define TIM_BDTR_BKE ((uint16_t)0x1000)  /*!<Break enable */
#define TIM_BDTR_BKP ((uint16_t)0x2000)  /*!<Break Polarity */
#define TIM_BDTR_AOE ((uint16_t)0x4000)  /*!<Automatic Output enable */
#define TIM_BDTR_MOE ((uint16_t)0x8000)  /*!<Main Output enable */

/*******************  Bit definition for TIM_DCR register  ********************/
#define TIM_DCR_DBA ((uint16_t)0x001F)   /*!<DBA[4:0] bits (DMA Base Address) */
#define TIM_DCR_DBA_0 ((uint16_t)0x0001) /*!<Bit 0 */
#define TIM_DCR_DBA_1 ((uint16_t)0x0002) /*!<Bit 1 */
#define TIM_DCR_DBA_2 ((uint16_t)0x0004) /*!<Bit 2 */
#define TIM_DCR_DBA_3 ((uint16_t)0x0008) /*!<Bit 3 */
#define TIM_DCR_DBA_4 ((uint16_t)0x0010) /*!<Bit 4 */

#define TIM_DCR_DSEL ((uint16_t)0x00E0)   /*!<DBA[4:0] bits (DMA Base Address) */
#define TIM_DCR_DSEL_0 ((uint16_t)0x0020) /*!<Bit 0 */
#define TIM_DCR_DSEL_1 ((uint16_t)0x0040) /*!<Bit 1 */
#define TIM_DCR_DSEL_2 ((uint16_t)0x0080) /*!<Bit 2 */

#define TIM_DCR_DBL ((uint16_t)0x1F00)   /*!<DBL[4:0] bits (DMA Burst Length) */
#define TIM_DCR_DBL_0 ((uint16_t)0x0100) /*!<Bit 0 */
#define TIM_DCR_DBL_1 ((uint16_t)0x0200) /*!<Bit 1 */
#define TIM_DCR_DBL_2 ((uint16_t)0x0400) /*!<Bit 2 */
#define TIM_DCR_DBL_3 ((uint16_t)0x0800) /*!<Bit 3 */
#define TIM_DCR_DBL_4 ((uint16_t)0x1000) /*!<Bit 4 */

/*******************  Bit definition for TIM_DMAR register  *******************/
#define TIM_DMAR_DMAB ((uint16_t)0xFFFF) /*!<DMA register for burst accesses */

/*******************  Bit definition for TIM_OR register  *********************/
#define TIM14_OR_TI1_RMP ((uint16_t)0x0003)   /*!<TI1_RMP[1:0] bits (TIM14 Input 4 remap) */
#define TIM14_OR_TI1_RMP_0 ((uint16_t)0x0001) /*!<Bit 0 */
#define TIM14_OR_TI1_RMP_1 ((uint16_t)0x0002) /*!<Bit 1 */

#define SMCR_ETR_MASK ((uint16_t)0x00FF)
#define CCMR_OFFSET ((uint16_t)0x0018)
#define CCER_CCE_SET ((uint16_t)0x0001)
#define CCER_CCNE_SET ((uint16_t)0x0004)
/********************************************************************************/

/***************** Bit Definition for TIM_CR1 Register **************/
#define TIM_CR1_AS_Pos 24
#define TIM_CR1_AS_Msk (0x1UL << TIM_CR1_AS_Pos)
#define TIM_AS_OFF (0x0UL << TIM_CR1_AS_Pos)
#define TIM_AS_ON (0x1UL << TIM_CR1_AS_Pos)
#define TIM_CR1_OCF_Pos 23
#define TIM_CR1_OCF_Msk (0x1UL << TIM_CR1_OCF_Pos)
#define TIM_OCF_OFF (0x0UL << TIM_CR1_OCF_Pos)
#define TIM_OCF_ON (0x1UL << TIM_CR1_OCF_Pos)
#define TIM_CR1_CENCE_Pos 22
#define TIM_CR1_CENCE_Msk (0x1UL << TIM_CR1_CENCE_Pos)
#define TIM_CENCE_OFF (0x0UL << TIM_CR1_CENCE_Pos)
#define TIM_CENCE_ON (0x1UL << TIM_CR1_CENCE_Pos)
#define TIM_CR1_TI4E_Pos 21
#define TIM_CR1_TI4E_Msk (0x1UL << TIM_CR1_TI4E_Pos)
#define TIM_TI4E_OFF (0x0UL << TIM_CR1_TI4E_Pos)
#define TIM_TI4E_ON (0x1UL << TIM_CR1_TI4E_Pos)
#define TIM_CR1_TI3E_Pos 20
#define TIM_CR1_TI3E_Msk (0x1UL << TIM_CR1_TI3E_Pos)
#define TIM_TI3E_OFF (0x0UL << TIM_CR1_TI3E_Pos)
#define TIM_TI3E_ON (0x1UL << TIM_CR1_TI3E_Pos)
#define TIM_CR1_TI2E_Pos 19
#define TIM_CR1_TI2E_Msk (0x1UL << TIM_CR1_TI2E_Pos)
#define TIM_TI2E_OFF (0x0UL << TIM_CR1_TI2E_Pos)
#define TIM_TI2E_ON (0x1UL << TIM_CR1_TI2E_Pos)
#define TIM_CR1_TI1E_Pos 18
#define TIM_CR1_TI1E_Msk (0x1UL << TIM_CR1_TI1E_Pos)
#define TIM_TI1E_OFF (0x0UL << TIM_CR1_TI1E_Pos)
#define TIM_TI1E_ON (0x1UL << TIM_CR1_TI1E_Pos)
#define TIM_CR1_ETRE_Pos 17
#define TIM_CR1_ETRE_Msk (0x1UL << TIM_CR1_ETRE_Pos)
#define TIM_ETRE_OFF (0x0UL << TIM_CR1_ETRE_Pos)
#define TIM_ETRE_ON (0x1UL << TIM_CR1_ETRE_Pos)
#define TIM_CR1_DTSE_Pos 16
#define TIM_CR1_DTSE_Msk (0x1UL << TIM_CR1_DTSE_Pos)
#define TIM_DTSE_OFF (0x0UL << TIM_CR1_DTSE_Pos)
#define TIM_DTSE_ON (0x1UL << TIM_CR1_DTSE_Pos)
#define TIM_CR1_CKD_Pos 8
#define TIM_CR1_CKD_Msk (0x3UL << TIM_CR1_CKD_Pos)
#define TIM_CKD_1 (0x0UL << TIM_CR1_CKD_Pos)
#define TIM_CKD_2 (0x1UL << TIM_CR1_CKD_Pos)
#define TIM_CKD_4 (0x2UL << TIM_CR1_CKD_Pos)
#define TIM_CR1_ARPE_Pos 7
#define TIM_CR1_ARPE_Msk (0x1UL << TIM_CR1_ARPE_Pos)
#define TIM_CR1_CMS_Pos 5
#define TIM_CR1_CMS_Msk (0x3UL << TIM_CR1_CMS_Pos)
#define TIM_CMS_EDGE (0x0UL << TIM_CR1_CMS_Pos)
#define TIM_CMS_MODE1 (0x1UL << TIM_CR1_CMS_Pos)
#define TIM_CMS_MODE2 (0x2UL << TIM_CR1_CMS_Pos)
#define TIM_CMS_MODE3 (0x3UL << TIM_CR1_CMS_Pos)
#define TIM_CR1_DIR_Pos 4
#define TIM_CR1_DIR_Msk (0x1UL << TIM_CR1_DIR_Pos)
#define TIM_DIR_UP (0x0UL << TIM_CR1_DIR_Pos)
#define TIM_DIR_DOWN (0x1UL << TIM_CR1_DIR_Pos)
#define TIM_CR1_OPM_Pos 3
#define TIM_CR1_OPM_Msk (0x1UL << TIM_CR1_OPM_Pos)
#define TIM_OPM_OFF (0x0UL << TIM_CR1_OPM_Pos)
#define TIM_OPM_ON (0x1UL << TIM_CR1_OPM_Pos)
#define TIM_CR1_URS_Pos 2
#define TIM_CR1_URS_Msk (0x1UL << TIM_CR1_URS_Pos)
#define TIM_CR1_UDIS_Pos 1
#define TIM_CR1_UDIS_Msk (0x1UL << TIM_CR1_UDIS_Pos)
#define TIM_CR1_CEN_Pos 0
#define TIM_CR1_CEN_Msk (0x1UL << TIM_CR1_CEN_Pos)
#define TIM_CEN_OFF (0x0UL << TIM_CR1_CEN_Pos)
#define TIM_CEN_ON (0x1UL << TIM_CR1_CEN_Pos)

/***************** Bit Definition for TIM_CR2 Register **************/
#define TIM_CR2_OIS4N_Pos 15
#define TIM_CR2_OIS4N_Msk (0x1UL << TIM_CR2_OIS4N_Pos)
#define TIM_OIS4N_0 (0x0UL << TIM_CR2_OIS4N_Pos)
#define TIM_OIS4N_1 (0x1UL << TIM_CR2_OIS4N_Pos)
#define TIM_CR2_OIS4_Pos 14
#define TIM_CR2_OIS4_Msk (0x1UL << TIM_CR2_OIS4_Pos)
#define TIM_OIS4_0 (0x0UL << TIM_CR2_OIS4_Pos)
#define TIM_OIS4_1 (0x1UL << TIM_CR2_OIS4_Pos)
#define TIM_CR2_OIS3N_Pos 13
#define TIM_CR2_OIS3N_Msk (0x1UL << TIM_CR2_OIS3N_Pos)
#define TIM_OIS3N_0 (0x0UL << TIM_CR2_OIS3N_Pos)
#define TIM_OIS3N_1 (0x1UL << TIM_CR2_OIS3N_Pos)
#define TIM_CR2_OIS3_Pos 12
#define TIM_CR2_OIS3_Msk (0x1UL << TIM_CR2_OIS3_Pos)
#define TIM_OIS3_0 (0x0UL << TIM_CR2_OIS3_Pos)
#define TIM_OIS3_1 (0x1UL << TIM_CR2_OIS3_Pos)
#define TIM_CR2_OIS2N_Pos 11
#define TIM_CR2_OIS2N_Msk (0x1UL << TIM_CR2_OIS2N_Pos)
#define TIM_OIS2N_0 (0x0UL << TIM_CR2_OIS2N_Pos)
#define TIM_OIS2N_1 (0x1UL << TIM_CR2_OIS2N_Pos)
#define TIM_CR2_OIS2_Pos 10
#define TIM_CR2_OIS2_Msk (0x1UL << TIM_CR2_OIS2_Pos)
#define TIM_OIS2_0 (0x0UL << TIM_CR2_OIS2_Pos)
#define TIM_OIS2_1 (0x1UL << TIM_CR2_OIS2_Pos)
#define TIM_CR2_OIS1N_Pos 9
#define TIM_CR2_OIS1N_Msk (0x1UL << TIM_CR2_OIS1N_Pos)
#define TIM_OIS1N_0 (0x0UL << TIM_CR2_OIS1N_Pos)
#define TIM_OIS1N_1 (0x1UL << TIM_CR2_OIS1N_Pos)
#define TIM_CR2_OIS1_Pos 8
#define TIM_CR2_OIS1_Msk (0x1UL << TIM_CR2_OIS1_Pos)
#define TIM_OIS1_0 (0x0UL << TIM_CR2_OIS1_Pos)
#define TIM_OIS1_1 (0x1UL << TIM_CR2_OIS1_Pos)
#define TIM_CR2_TI1S_Pos 7
#define TIM_CR2_TI1S_Msk (0x1UL << TIM_CR2_TI1S_Pos)
#define TIM_TI1S_0 (0x0UL << TIM_CR2_TI1S_Pos)
#define TIM_TI1S_1 (0x1UL << TIM_CR2_TI1S_Pos)
#define TIM_CR2_MMS_Pos 4
#define TIM_CR2_MMS_Msk (0x7UL << TIM_CR2_MMS_Pos)
#define TIM_MMS_RST (0x0UL << TIM_CR2_MMS_Pos)
#define TIM_MMS_EN (0x1UL << TIM_CR2_MMS_Pos)
#define TIM_MMS_UPDATE (0x2UL << TIM_CR2_MMS_Pos)
#define TIM_MMS_PULSE (0x3UL << TIM_CR2_MMS_Pos)
#define TIM_MMS_OC1 (0x4UL << TIM_CR2_MMS_Pos)
#define TIM_MMS_OC2 (0x5UL << TIM_CR2_MMS_Pos)
#define TIM_MMS_OC3 (0x6UL << TIM_CR2_MMS_Pos)
#define TIM_MMS_OC4 (0x7UL << TIM_CR2_MMS_Pos)
#define TIM_CR2_CCDS_Pos 3
#define TIM_CR2_CCDS_Msk (0x1UL << TIM_CR2_CCDS_Pos)
#define TIM_CR2_CCUS_Pos 2
#define TIM_CR2_CCUS_Msk (0x1UL << TIM_CR2_CCUS_Pos)
#define TIM_CCUS_COMG (0x0UL << TIM_CR2_CCUS_Pos)
#define TIM_CCUS_COMG_TRG (0x1UL << TIM_CR2_CCUS_Pos)
#define TIM_CR2_CCPC_Pos 0
#define TIM_CR2_CCPC_Msk (0x1UL << TIM_CR2_CCPC_Pos)
#define TIM_CCPC_OFF (0x0UL << TIM_CR2_CCPC_Pos)
#define TIM_CCPC_ON (0x1UL << TIM_CR2_CCPC_Pos)

/***************** Bit Definition for TIM_SMCR Register **************/
#define TIM_SMCR_OCCP_Pos 17
#define TIM_SMCR_OCCP_Msk (0x1UL << TIM_SMCR_OCCP_Pos)
#define TIM_OCCP_AH (0x0UL << TIM_SMCR_OCCP_Pos)
#define TIM_OCCP_AL (0x1UL << TIM_SMCR_OCCP_Pos)
#define TIM_SMCR_SMS_3_Pos 16
#define TIM_SMCR_SMS_3_Msk (0x1UL << TIM_SMCR_SMS_3_Pos)
#define TIM_SMCR_ETP_Pos 15
#define TIM_SMCR_ETP_Msk (0x1UL << TIM_SMCR_ETP_Pos)
#define TIM_ETP_AH (0x0UL << TIM_SMCR_ETP_Pos)
#define TIM_ETP_AL (0x1UL << TIM_SMCR_ETP_Pos)
#define TIM_SMCR_ECE_Pos 14
#define TIM_SMCR_ECE_Msk (0x1UL << TIM_SMCR_ECE_Pos)
#define TIM_ECE_OFF (0x0UL << TIM_SMCR_ECE_Pos)
#define TIM_ECE_ON (0x1UL << TIM_SMCR_ECE_Pos)
#define TIM_SMCR_ETPS_Pos 12
#define TIM_SMCR_ETPS_Msk (0x3UL << TIM_SMCR_ETPS_Pos)
#define TIM_ETPS_1 (0x0UL << TIM_SMCR_ETPS_Pos)
#define TIM_ETPS_2 (0x1UL << TIM_SMCR_ETPS_Pos)
#define TIM_ETPS_4 (0x2UL << TIM_SMCR_ETPS_Pos)
#define TIM_ETPS_8 (0x3UL << TIM_SMCR_ETPS_Pos)
#define TIM_SMCR_ETF_Pos 8
#define TIM_SMCR_ETF_Msk (0xFUL << TIM_SMCR_ETF_Pos)
#define TIM_ETF(n) ((n) << TIM_SMCR_ETF_Pos)
#define TIM_SMCR_MSM_Pos 7
#define TIM_SMCR_MSM_Msk (0x1UL << TIM_SMCR_MSM_Pos)
#define TIM_MSM_OFF (0x0UL << TIM_SMCR_MSM_Pos)
#define TIM_MSM_ON (0x1UL << TIM_SMCR_MSM_Pos)
#define TIM_SMCR_TS_Pos 4
#define TIM_SMCR_TS_Msk (0x7UL << TIM_SMCR_TS_Pos)
#define TIM_TS_ITR0 (0x0UL << TIM_SMCR_TS_Pos)
#define TIM_TS_ITR1 (0x1UL << TIM_SMCR_TS_Pos)
#define TIM_TS_ITR2 (0x2UL << TIM_SMCR_TS_Pos)
#define TIM_TS_ITR3 (0x3UL << TIM_SMCR_TS_Pos)
#define TIM_TS_TI1_ED (0x4UL << TIM_SMCR_TS_Pos)
#define TIM_TS_TI1 (0x5UL << TIM_SMCR_TS_Pos)
#define TIM_TS_TI2 (0x6UL << TIM_SMCR_TS_Pos)
#define TIM_TS_ETR (0x7UL << TIM_SMCR_TS_Pos)
#define TIM_SMCR_OCCS_Pos 3
#define TIM_SMCR_OCCS_Msk (0x1UL << TIM_SMCR_OCCS_Pos)
#define TIM_OCCS_CLRIN (0x0UL << TIM_SMCR_OCCS_Pos)
#define TIM_OCCS_ETRF (0x1UL << TIM_SMCR_OCCS_Pos)
#define TIM_SMCR_SMS_2_0_Pos 0
#define TIM_SMCR_SMS_2_0_Msk (0x7UL << TIM_SMCR_SMS_2_0_Pos)
#define TIM_SMCR_SMS_Msk (TIM_SMCR_SMS_3_Msk | TIM_SMCR_SMS_2_0_Msk)
#define TIM_SMS_DIS ((0x0UL << TIM_SMCR_SMS_3_Pos) | (0x0UL << TIM_SMCR_SMS_2_0_Pos))
#define TIM_SMS_ENC1 ((0x0UL << TIM_SMCR_SMS_3_Pos) | (0x1UL << TIM_SMCR_SMS_2_0_Pos))
#define TIM_SMS_ENC2 ((0x0UL << TIM_SMCR_SMS_3_Pos) | (0x2UL << TIM_SMCR_SMS_2_0_Pos))
#define TIM_SMS_ENC3 ((0x0UL << TIM_SMCR_SMS_3_Pos) | (0x3UL << TIM_SMCR_SMS_2_0_Pos))
#define TIM_SMS_RST ((0x0UL << TIM_SMCR_SMS_3_Pos) | (0x4UL << TIM_SMCR_SMS_2_0_Pos))
#define TIM_SMS_GATE ((0x0UL << TIM_SMCR_SMS_3_Pos) | (0x5UL << TIM_SMCR_SMS_2_0_Pos))
#define TIM_SMS_TRG ((0x0UL << TIM_SMCR_SMS_3_Pos) | (0x6UL << TIM_SMCR_SMS_2_0_Pos))
#define TIM_SMS_ECM1 ((0x0UL << TIM_SMCR_SMS_3_Pos) | (0x7UL << TIM_SMCR_SMS_2_0_Pos))
#define TIM_SMS_RST_TRG ((0x1UL << TIM_SMCR_SMS_3_Pos) | (0x0UL << TIM_SMCR_SMS_2_0_Pos))

/***************** Bit Definition for TIM_DIER Register **************/
#define TIM_DIER_TDE_Pos 14
#define TIM_DIER_TDE_Msk (0x1UL << TIM_DIER_TDE_Pos)
#define TIM_DIER_COMDE_Pos 13
#define TIM_DIER_COMDE_Msk (0x1UL << TIM_DIER_COMDE_Pos)
#define TIM_DIER_CC4DE_Pos 12
#define TIM_DIER_CC4DE_Msk (0x1UL << TIM_DIER_CC4DE_Pos)
#define TIM_DIER_CC3DE_Pos 11
#define TIM_DIER_CC3DE_Msk (0x1UL << TIM_DIER_CC3DE_Pos)
#define TIM_DIER_CC2DE_Pos 10
#define TIM_DIER_CC2DE_Msk (0x1UL << TIM_DIER_CC2DE_Pos)
#define TIM_DIER_CC1DE_Pos 9
#define TIM_DIER_CC1DE_Msk (0x1UL << TIM_DIER_CC1DE_Pos)
#define TIM_DIER_UDE_Pos 8
#define TIM_DIER_UDE_Msk (0x1UL << TIM_DIER_UDE_Pos)
#define TIM_DIER_BIE_Pos 7
#define TIM_DIER_BIE_Msk (0x1UL << TIM_DIER_BIE_Pos)
#define TIM_DIER_TIE_Pos 6
#define TIM_DIER_TIE_Msk (0x1UL << TIM_DIER_TIE_Pos)
#define TIM_DIER_COMIE_Pos 5
#define TIM_DIER_COMIE_Msk (0x1UL << TIM_DIER_COMIE_Pos)
#define TIM_DIER_CC4IE_Pos 4
#define TIM_DIER_CC4IE_Msk (0x1UL << TIM_DIER_CC4IE_Pos)
#define TIM_DIER_CC3IE_Pos 3
#define TIM_DIER_CC3IE_Msk (0x1UL << TIM_DIER_CC3IE_Pos)
#define TIM_DIER_CC2IE_Pos 2
#define TIM_DIER_CC2IE_Msk (0x1UL << TIM_DIER_CC2IE_Pos)
#define TIM_DIER_CC1IE_Pos 1
#define TIM_DIER_CC1IE_Msk (0x1UL << TIM_DIER_CC1IE_Pos)
#define TIM_DIER_UIE_Pos 0
#define TIM_DIER_UIE_Msk (0x1UL << TIM_DIER_UIE_Pos)

/***************** Bit Definition for TIM_SR Register **************/
#define TIM_SR_CC4OF_Pos 12
#define TIM_SR_CC4OF_Msk (0x1UL << TIM_SR_CC4OF_Pos)
#define TIM_SR_CC3OF_Pos 11
#define TIM_SR_CC3OF_Msk (0x1UL << TIM_SR_CC3OF_Pos)
#define TIM_SR_CC2OF_Pos 10
#define TIM_SR_CC2OF_Msk (0x1UL << TIM_SR_CC2OF_Pos)
#define TIM_SR_CC1OF_Pos 9
#define TIM_SR_CC1OF_Msk (0x1UL << TIM_SR_CC1OF_Pos)
#define TIM_SR_B2IF_Pos 8
#define TIM_SR_B2IF_Msk (0x1UL << TIM_SR_B2IF_Pos)
#define TIM_SR_BIF_Pos 7
#define TIM_SR_BIF_Msk (0x1UL << TIM_SR_BIF_Pos)
#define TIM_SR_TIF_Pos 6
#define TIM_SR_TIF_Msk (0x1UL << TIM_SR_TIF_Pos)
#define TIM_SR_COMIF_Pos 5
#define TIM_SR_COMIF_Msk (0x1UL << TIM_SR_COMIF_Pos)
#define TIM_SR_CC4IF_Pos 4
#define TIM_SR_CC4IF_Msk (0x1UL << TIM_SR_CC4IF_Pos)
#define TIM_SR_CC3IF_Pos 3
#define TIM_SR_CC3IF_Msk (0x1UL << TIM_SR_CC3IF_Pos)
#define TIM_SR_CC2IF_Pos 2
#define TIM_SR_CC2IF_Msk (0x1UL << TIM_SR_CC2IF_Pos)
#define TIM_SR_CC1IF_Pos 1
#define TIM_SR_CC1IF_Msk (0x1UL << TIM_SR_CC1IF_Pos)
#define TIM_SR_UIF_Pos 0
#define TIM_SR_UIF_Msk (0x1UL << TIM_SR_UIF_Pos)

/***************** Bit Definition for TIM_EGR Register **************/
#define TIM_EGR_B2G_Pos 8
#define TIM_EGR_B2G_Msk (0x1UL << TIM_EGR_B2G_Pos)
#define TIM_EGR_BG_Pos 7
#define TIM_EGR_BG_Msk (0x1UL << TIM_EGR_BG_Pos)
#define TIM_EGR_TG_Pos 6
#define TIM_EGR_TG_Msk (0x1UL << TIM_EGR_TG_Pos)
#define TIM_EGR_COMG_Pos 5
#define TIM_EGR_COMG_Msk (0x1UL << TIM_EGR_COMG_Pos)
#define TIM_EGR_CC4G_Pos 4
#define TIM_EGR_CC4G_Msk (0x1UL << TIM_EGR_CC4G_Pos)
#define TIM_EGR_CC3G_Pos 3
#define TIM_EGR_CC3G_Msk (0x1UL << TIM_EGR_CC3G_Pos)
#define TIM_EGR_CC2G_Pos 2
#define TIM_EGR_CC2G_Msk (0x1UL << TIM_EGR_CC2G_Pos)
#define TIM_EGR_CC1G_Pos 1
#define TIM_EGR_CC1G_Msk (0x1UL << TIM_EGR_CC1G_Pos)
#define TIM_EGR_UG_Pos 0
#define TIM_EGR_UG_Msk (0x1UL << TIM_EGR_UG_Pos)

/***************** Bit Definition for TIM_CCMR1 Register **************/
#define TIM_CCMR1_OC2TE_Pos 31
#define TIM_CCMR1_OC2TE_Msk (0x1UL << TIM_CCMR1_OC2TE_Pos)
#define TIM_OC2TE_OFF (0x0UL << TIM_CCMR1_OC2TE_Pos)
#define TIM_OC2TE_ON (0x1UL << TIM_CCMR1_OC2TE_Pos)
#define TIM_CCMR1_OC2TUE_Pos 30
#define TIM_CCMR1_OC2TUE_Msk (0x1UL << TIM_CCMR1_OC2TUE_Pos)
#define TIM_OC2TUE_OFF (0x0UL << TIM_CCMR1_OC2TUE_Pos)
#define TIM_OC2TUE_ON (0x1UL << TIM_CCMR1_OC2TUE_Pos)
#define TIM_CCMR1_OC1TE_Pos 23
#define TIM_CCMR1_OC1TE_Msk (0x1UL << TIM_CCMR1_OC1TE_Pos)
#define TIM_OC1TE_OFF (0x0UL << TIM_CCMR1_OC1TE_Pos)
#define TIM_OC1TE_ON (0x1UL << TIM_CCMR1_OC1TE_Pos)
#define TIM_CCMR1_OC1TUE_Pos 22
#define TIM_CCMR1_OC1TUE_Msk (0x1UL << TIM_CCMR1_OC1TUE_Pos)
#define TIM_OC1TUE_OFF (0x0UL << TIM_CCMR1_OC1TUE_Pos)
#define TIM_OC1TUE_ON (0x1UL << TIM_CCMR1_OC1TUE_Pos)
#define TIM_CCMR1_OC2CE_Pos 15
#define TIM_CCMR1_OC2CE_Msk (0x1UL << TIM_CCMR1_OC2CE_Pos)
#define TIM_OC2CE_OFF (0x0UL << TIM_CCMR1_OC2CE_Pos)
#define TIM_OC2CE_ON (0x1UL << TIM_CCMR1_OC2CE_Pos)
#define TIM_CCMR1_OC2M_Pos 12
#define TIM_CCMR1_OC2M_Msk (0x7UL << TIM_CCMR1_OC2M_Pos)
#define TIM_OC2M_FROZEN (0x0UL << TIM_CCMR1_OC2M_Pos)
#define TIM_OC2M_ACTIVE (0x1UL << TIM_CCMR1_OC2M_Pos)
#define TIM_OC2M_INACTIVE (0x2UL << TIM_CCMR1_OC2M_Pos)
#define TIM_OC2M_TOGGLE (0x3UL << TIM_CCMR1_OC2M_Pos)
#define TIM_OC2M_FORCE0 (0x4UL << TIM_CCMR1_OC2M_Pos)
#define TIM_OC2M_FORCE1 (0x5UL << TIM_CCMR1_OC2M_Pos)
#define TIM_OC2M_PWM1 (0x6UL << TIM_CCMR1_OC2M_Pos)
#define TIM_OC2M_PWM2 (0x7UL << TIM_CCMR1_OC2M_Pos)
#define TIM_CCMR1_OC2PE_Pos 11
#define TIM_CCMR1_OC2PE_Msk (0x1UL << TIM_CCMR1_OC2PE_Pos)
#define TIM_OC2PE_OFF (0x0UL << TIM_CCMR1_OC2PE_Pos)
#define TIM_OC2PE_ON (0x1UL << TIM_CCMR1_OC2PE_Pos)
#define TIM_CCMR1_OC2FE_Pos 10
#define TIM_CCMR1_OC2FE_Msk (0x1UL << TIM_CCMR1_OC2FE_Pos)
#define TIM_OC2FE_OFF (0x0UL << TIM_CCMR1_OC2FE_Pos)
#define TIM_OC2FE_ON (0x1UL << TIM_CCMR1_OC2FE_Pos)
#define TIM_CCMR1_OC1CE_Pos 7
#define TIM_CCMR1_OC1CE_Msk (0x1UL << TIM_CCMR1_OC1CE_Pos)
#define TIM_OC1CE_OFF (0x0UL << TIM_CCMR1_OC1CE_Pos)
#define TIM_OC1CE_ON (0x1UL << TIM_CCMR1_OC1CE_Pos)
#define TIM_CCMR1_OC1M_Pos 4
#define TIM_CCMR1_OC1M_Msk (0x7UL << TIM_CCMR1_OC1M_Pos)
#define TIM_OC1M_FROZEN (0x0UL << TIM_CCMR1_OC1M_Pos)
#define TIM_OC1M_ACTIVE (0x1UL << TIM_CCMR1_OC1M_Pos)
#define TIM_OC1M_INACTIVE (0x2UL << TIM_CCMR1_OC1M_Pos)
#define TIM_OC1M_TOGGLE (0x3UL << TIM_CCMR1_OC1M_Pos)
#define TIM_OC1M_FORCE0 (0x4UL << TIM_CCMR1_OC1M_Pos)
#define TIM_OC1M_FORCE1 (0x5UL << TIM_CCMR1_OC1M_Pos)
#define TIM_OC1M_PWM1 (0x6UL << TIM_CCMR1_OC1M_Pos)
#define TIM_OC1M_PWM2 (0x7UL << TIM_CCMR1_OC1M_Pos)
#define TIM_CCMR1_OC1PE_Pos 3
#define TIM_CCMR1_OC1PE_Msk (0x1UL << TIM_CCMR1_OC1PE_Pos)
#define TIM_OC1PE_OFF (0x0UL << TIM_CCMR1_OC1PE_Pos)
#define TIM_OC1PE_ON (0x1UL << TIM_CCMR1_OC1PE_Pos)
#define TIM_CCMR1_OC1FE_Pos 2
#define TIM_CCMR1_OC1FE_Msk (0x1UL << TIM_CCMR1_OC1FE_Pos)
#define TIM_OC1FE_OFF (0x0UL << TIM_CCMR1_OC1FE_Pos)
#define TIM_OC1FE_ON (0x1UL << TIM_CCMR1_OC1FE_Pos)
#define TIM_CCMR1_IC2F_Pos 12
#define TIM_CCMR1_IC2F_Msk (0xFUL << TIM_CCMR1_IC2F_Pos)
#define TIM_IC2F(n) ((n) << TIM_CCMR1_IC2F_Pos)
#define TIM_CCMR1_IC2PSC_Pos 10
#define TIM_CCMR1_IC2PSC_Msk (0x3UL << TIM_CCMR1_IC2PSC_Pos)
#define TIM_IC2PSC_1 (0x0UL << TIM_CCMR1_IC2PSC_Pos)
#define TIM_IC2PSC_2 (0x1UL << TIM_CCMR1_IC2PSC_Pos)
#define TIM_IC2PSC_4 (0x2UL << TIM_CCMR1_IC2PSC_Pos)
#define TIM_IC2PSC_8 (0x3UL << TIM_CCMR1_IC2PSC_Pos)
#define TIM_CCMR1_IC1F_Pos 4
#define TIM_CCMR1_IC1F_Msk (0xFUL << TIM_CCMR1_IC1F_Pos)
#define TIM_IC1F(n) ((n) << TIM_CCMR1_IC1F_Pos)
#define TIM_CCMR1_IC1PSC_Pos 2
#define TIM_CCMR1_IC1PSC_Msk (0x3UL << TIM_CCMR1_IC1PSC_Pos)
#define TIM_IC1PSC_1 (0x0UL << TIM_CCMR1_IC1PSC_Pos)
#define TIM_IC1PSC_2 (0x1UL << TIM_CCMR1_IC1PSC_Pos)
#define TIM_IC1PSC_4 (0x2UL << TIM_CCMR1_IC1PSC_Pos)
#define TIM_IC1PSC_8 (0x3UL << TIM_CCMR1_IC1PSC_Pos)
#define TIM_CCMR1_CC2S_Pos 8
#define TIM_CCMR1_CC2S_Msk (0x3UL << TIM_CCMR1_CC2S_Pos)
#define TIM_CC2S_OC (0x0UL << TIM_CCMR1_CC2S_Pos)
#define TIM_CC2S_IC_SAME (0x1UL << TIM_CCMR1_CC2S_Pos)
#define TIM_CC2S_IC_CROSS (0x2UL << TIM_CCMR1_CC2S_Pos)
#define TIM_CC2S_IC_TRC (0x3UL << TIM_CCMR1_CC2S_Pos)
#define TIM_CCMR1_CC1S_Pos 0
#define TIM_CCMR1_CC1S_Msk (0x3UL << TIM_CCMR1_CC1S_Pos)
#define TIM_CC1S_OC (0x0UL << TIM_CCMR1_CC1S_Pos)
#define TIM_CC1S_IC_SAME (0x1UL << TIM_CCMR1_CC1S_Pos)
#define TIM_CC1S_IC_CROSS (0x2UL << TIM_CCMR1_CC1S_Pos)
#define TIM_CC1S_IC_TRC (0x3UL << TIM_CCMR1_CC1S_Pos)

/***************** Bit Definition for TIM_CCMR2 Register **************/
#define TIM_CCMR2_OC4TE_Pos 31
#define TIM_CCMR2_OC4TE_Msk (0x1UL << TIM_CCMR2_OC4TE_Pos)
#define TIM_OC4TE_OFF (0x0UL << TIM_CCMR2_OC4TE_Pos)
#define TIM_OC4TE_ON (0x1UL << TIM_CCMR2_OC4TE_Pos)
#define TIM_CCMR2_OC4TUE_Pos 30
#define TIM_CCMR2_OC4TUE_Msk (0x1UL << TIM_CCMR2_OC4TUE_Pos)
#define TIM_OC4TUE_OFF (0x0UL << TIM_CCMR2_OC4TUE_Pos)
#define TIM_OC4TUE_ON (0x1UL << TIM_CCMR2_OC4TUE_Pos)
#define TIM_CCMR2_OC3TE_Pos 23
#define TIM_CCMR2_OC3TE_Msk (0x1UL << TIM_CCMR2_OC3TE_Pos)
#define TIM_OC3TE_OFF (0x0UL << TIM_CCMR2_OC3TE_Pos)
#define TIM_OC3TE_ON (0x1UL << TIM_CCMR2_OC3TE_Pos)
#define TIM_CCMR2_OC3TUE_Pos 22
#define TIM_CCMR2_OC3TUE_Msk (0x1UL << TIM_CCMR2_OC3TUE_Pos)
#define TIM_OC3TUE_OFF (0x0UL << TIM_CCMR2_OC3TUE_Pos)
#define TIM_OC3TUE_ON (0x1UL << TIM_CCMR2_OC3TUE_Pos)
#define TIM_CCMR2_OC4CE_Pos 15
#define TIM_CCMR2_OC4CE_Msk (0x1UL << TIM_CCMR2_OC4CE_Pos)
#define TIM_OC4CE_OFF (0x0UL << TIM_CCMR2_OC4CE_Pos)
#define TIM_OC4CE_ON (0x1UL << TIM_CCMR2_OC4CE_Pos)
#define TIM_CCMR2_OC4M_Pos 12
#define TIM_CCMR2_OC4M_Msk (0x7UL << TIM_CCMR2_OC4M_Pos)
#define TIM_OC4M_FROZEN (0x0UL << TIM_CCMR2_OC4M_Pos)
#define TIM_OC4M_ACTIVE (0x1UL << TIM_CCMR2_OC4M_Pos)
#define TIM_OC4M_INACTIVE (0x2UL << TIM_CCMR2_OC4M_Pos)
#define TIM_OC4M_TOGGLE (0x3UL << TIM_CCMR2_OC4M_Pos)
#define TIM_OC4M_FORCE0 (0x4UL << TIM_CCMR2_OC4M_Pos)
#define TIM_OC4M_FORCE1 (0x5UL << TIM_CCMR2_OC4M_Pos)
#define TIM_OC4M_PWM1 (0x6UL << TIM_CCMR2_OC4M_Pos)
#define TIM_OC4M_PWM2 (0x7UL << TIM_CCMR2_OC4M_Pos)
#define TIM_CCMR2_OC4PE_Pos 11
#define TIM_CCMR2_OC4PE_Msk (0x1UL << TIM_CCMR2_OC4PE_Pos)
#define TIM_OC4PE_OFF (0x0UL << TIM_CCMR2_OC4PE_Pos)
#define TIM_OC4PE_ON (0x1UL << TIM_CCMR2_OC4PE_Pos)
#define TIM_CCMR2_OC4FE_Pos 10
#define TIM_CCMR2_OC4FE_Msk (0x1UL << TIM_CCMR2_OC4FE_Pos)
#define TIM_OC4FE_OFF (0x0UL << TIM_CCMR2_OC4FE_Pos)
#define TIM_OC4FE_ON (0x1UL << TIM_CCMR2_OC4FE_Pos)
#define TIM_CCMR2_OC3CE_Pos 7
#define TIM_CCMR2_OC3CE_Msk (0x1UL << TIM_CCMR2_OC3CE_Pos)
#define TIM_OC3CE_OFF (0x0UL << TIM_CCMR2_OC3CE_Pos)
#define TIM_OC3CE_ON (0x1UL << TIM_CCMR2_OC3CE_Pos)
#define TIM_CCMR2_OC3M_Pos 4
#define TIM_CCMR2_OC3M_Msk (0x7UL << TIM_CCMR2_OC3M_Pos)
#define TIM_OC3M_FROZEN (0x0UL << TIM_CCMR2_OC3M_Pos)
#define TIM_OC3M_ACTIVE (0x1UL << TIM_CCMR2_OC3M_Pos)
#define TIM_OC3M_INACTIVE (0x2UL << TIM_CCMR2_OC3M_Pos)
#define TIM_OC3M_TOGGLE (0x3UL << TIM_CCMR2_OC3M_Pos)
#define TIM_OC3M_FORCE0 (0x4UL << TIM_CCMR2_OC3M_Pos)
#define TIM_OC3M_FORCE1 (0x5UL << TIM_CCMR2_OC3M_Pos)
#define TIM_OC3M_PWM1 (0x6UL << TIM_CCMR2_OC3M_Pos)
#define TIM_OC3M_PWM2 (0x7UL << TIM_CCMR2_OC3M_Pos)
#define TIM_CCMR2_OC3PE_Pos 3
#define TIM_CCMR2_OC3PE_Msk (0x1UL << TIM_CCMR2_OC3PE_Pos)
#define TIM_OC3PE_OFF (0x0UL << TIM_CCMR2_OC3PE_Pos)
#define TIM_OC3PE_ON (0x1UL << TIM_CCMR2_OC3PE_Pos)
#define TIM_CCMR2_OC3FE_Pos 2
#define TIM_CCMR2_OC3FE_Msk (0x1UL << TIM_CCMR2_OC3FE_Pos)
#define TIM_OC3FE_OFF (0x0UL << TIM_CCMR2_OC3FE_Pos)
#define TIM_OC3FE_ON (0x1UL << TIM_CCMR2_OC3FE_Pos)
#define TIM_CCMR2_IC4F_Pos 12
#define TIM_CCMR2_IC4F_Msk (0xFUL << TIM_CCMR2_IC4F_Pos)
#define TIM_IC4F(n) ((n) << TIM_CCMR2_IC4F_Pos)
#define TIM_CCMR2_IC4PSC_Pos 10
#define TIM_CCMR2_IC4PSC_Msk (0x3UL << TIM_CCMR2_IC4PSC_Pos)
#define TIM_IC4PSC_1 (0x0UL << TIM_CCMR2_IC4PSC_Pos)
#define TIM_IC4PSC_2 (0x1UL << TIM_CCMR2_IC4PSC_Pos)
#define TIM_IC4PSC_4 (0x2UL << TIM_CCMR2_IC4PSC_Pos)
#define TIM_IC4PSC_8 (0x3UL << TIM_CCMR2_IC4PSC_Pos)
#define TIM_CCMR2_IC3F_Pos 4
#define TIM_CCMR2_IC3F_Msk (0xFUL << TIM_CCMR2_IC3F_Pos)
#define TIM_IC3F(n) ((n) << TIM_CCMR2_IC3F_Pos)
#define TIM_CCMR2_IC3PSC_Pos 2
#define TIM_CCMR2_IC3PSC_Msk (0x3UL << TIM_CCMR2_IC3PSC_Pos)
#define TIM_IC3PSC_1 (0x0UL << TIM_CCMR2_IC3PSC_Pos)
#define TIM_IC3PSC_2 (0x1UL << TIM_CCMR2_IC3PSC_Pos)
#define TIM_IC3PSC_4 (0x2UL << TIM_CCMR2_IC3PSC_Pos)
#define TIM_IC3PSC_8 (0x3UL << TIM_CCMR2_IC3PSC_Pos)
#define TIM_CCMR2_CC4S_Pos 8
#define TIM_CCMR2_CC4S_Msk (0x3UL << TIM_CCMR2_CC4S_Pos)
#define TIM_CC4S_OC (0x0UL << TIM_CCMR2_CC4S_Pos)
#define TIM_CC4S_IC_SAME (0x1UL << TIM_CCMR2_CC4S_Pos)
#define TIM_CC4S_IC_CROSS (0x2UL << TIM_CCMR2_CC4S_Pos)
#define TIM_CC4S_IC_TRC (0x3UL << TIM_CCMR2_CC4S_Pos)
#define TIM_CCMR2_CC3S_Pos 0
#define TIM_CCMR2_CC3S_Msk (0x3UL << TIM_CCMR2_CC3S_Pos)
#define TIM_CC3S_OC (0x0UL << TIM_CCMR2_CC3S_Pos)
#define TIM_CC3S_IC_SAME (0x1UL << TIM_CCMR2_CC3S_Pos)
#define TIM_CC3S_IC_CROSS (0x2UL << TIM_CCMR2_CC3S_Pos)
#define TIM_CC3S_IC_TRC (0x3UL << TIM_CCMR2_CC3S_Pos)

/***************** Bit Definition for TIM_CCER Register **************/
#define TIM_CCER_CC4NP_Pos 15
#define TIM_CCER_CC4NP_Msk (0x1UL << TIM_CCER_CC4NP_Pos)
#define TIM_CC4NP_AH (0x0UL << TIM_CCER_CC4NP_Pos)
#define TIM_CC4NP_AL (0x1UL << TIM_CCER_CC4NP_Pos)
#define TIM_CCER_CC4NE_Pos 14
#define TIM_CCER_CC4NE_Msk (0x1UL << TIM_CCER_CC4NE_Pos)
#define TIM_CC4NE_OFF (0x0UL << TIM_CCER_CC4NE_Pos)
#define TIM_CC4NE_ON (0x1UL << TIM_CCER_CC4NE_Pos)
#define TIM_CCER_CC4P_Pos 13
#define TIM_CCER_CC4P_Msk (0x1UL << TIM_CCER_CC4P_Pos)
#define TIM_CC4P_AH (0x0UL << TIM_CCER_CC4P_Pos)
#define TIM_CC4P_AL (0x1UL << TIM_CCER_CC4P_Pos)
#define TIM_CCER_CC4E_Pos 12
#define TIM_CCER_CC4E_Msk (0x1UL << TIM_CCER_CC4E_Pos)
#define TIM_CC4E_OFF (0x0UL << TIM_CCER_CC4E_Pos)
#define TIM_CC4E_ON (0x1UL << TIM_CCER_CC4E_Pos)
#define TIM_CCER_CC3NP_Pos 11
#define TIM_CCER_CC3NP_Msk (0x1UL << TIM_CCER_CC3NP_Pos)
#define TIM_CC3NP_AH (0x0UL << TIM_CCER_CC3NP_Pos)
#define TIM_CC3NP_AL (0x1UL << TIM_CCER_CC3NP_Pos)
#define TIM_CCER_CC3NE_Pos 10
#define TIM_CCER_CC3NE_Msk (0x1UL << TIM_CCER_CC3NE_Pos)
#define TIM_CC3NE_OFF (0x0UL << TIM_CCER_CC3NE_Pos)
#define TIM_CC3NE_ON (0x1UL << TIM_CCER_CC3NE_Pos)
#define TIM_CCER_CC3P_Pos 9
#define TIM_CCER_CC3P_Msk (0x1UL << TIM_CCER_CC3P_Pos)
#define TIM_CC3P_AH (0x0UL << TIM_CCER_CC3P_Pos)
#define TIM_CC3P_AL (0x1UL << TIM_CCER_CC3P_Pos)
#define TIM_CCER_CC3E_Pos 8
#define TIM_CCER_CC3E_Msk (0x1UL << TIM_CCER_CC3E_Pos)
#define TIM_CC3E_OFF (0x0UL << TIM_CCER_CC3E_Pos)
#define TIM_CC3E_ON (0x1UL << TIM_CCER_CC3E_Pos)
#define TIM_CCER_CC2NP_Pos 7
#define TIM_CCER_CC2NP_Msk (0x1UL << TIM_CCER_CC2NP_Pos)
#define TIM_CC2NP_AH (0x0UL << TIM_CCER_CC2NP_Pos)
#define TIM_CC2NP_AL (0x1UL << TIM_CCER_CC2NP_Pos)
#define TIM_CCER_CC2NE_Pos 6
#define TIM_CCER_CC2NE_Msk (0x1UL << TIM_CCER_CC2NE_Pos)
#define TIM_CC2NE_OFF (0x0UL << TIM_CCER_CC2NE_Pos)
#define TIM_CC2NE_ON (0x1UL << TIM_CCER_CC2NE_Pos)
#define TIM_CCER_CC2P_Pos 5
#define TIM_CCER_CC2P_Msk (0x1UL << TIM_CCER_CC2P_Pos)
#define TIM_CC2P_AH (0x0UL << TIM_CCER_CC2P_Pos)
#define TIM_CC2P_AL (0x1UL << TIM_CCER_CC2P_Pos)
#define TIM_CCER_CC2E_Pos 4
#define TIM_CCER_CC2E_Msk (0x1UL << TIM_CCER_CC2E_Pos)
#define TIM_CC2E_OFF (0x0UL << TIM_CCER_CC2E_Pos)
#define TIM_CC2E_ON (0x1UL << TIM_CCER_CC2E_Pos)
#define TIM_CCER_CC1NP_Pos 3
#define TIM_CCER_CC1NP_Msk (0x1UL << TIM_CCER_CC1NP_Pos)
#define TIM_CC1NP_AH (0x0UL << TIM_CCER_CC1NP_Pos)
#define TIM_CC1NP_AL (0x1UL << TIM_CCER_CC1NP_Pos)
#define TIM_CCER_CC1NE_Pos 2
#define TIM_CCER_CC1NE_Msk (0x1UL << TIM_CCER_CC1NE_Pos)
#define TIM_CC1NE_OFF (0x0UL << TIM_CCER_CC1NE_Pos)
#define TIM_CC1NE_ON (0x1UL << TIM_CCER_CC1NE_Pos)
#define TIM_CCER_CC1P_Pos 1
#define TIM_CCER_CC1P_Msk (0x1UL << TIM_CCER_CC1P_Pos)
#define TIM_CC1P_AH (0x0UL << TIM_CCER_CC1P_Pos)
#define TIM_CC1P_AL (0x1UL << TIM_CCER_CC1P_Pos)
#define TIM_CCER_CC1E_Pos 0
#define TIM_CCER_CC1E_Msk (0x1UL << TIM_CCER_CC1E_Pos)
#define TIM_CC1E_OFF (0x0UL << TIM_CCER_CC1E_Pos)
#define TIM_CC1E_ON (0x1UL << TIM_CCER_CC1E_Pos)

/***************** Bit Definition for TIM_CNT Register **************/
#define TIM_CNT_CNT_Pos 0
#define TIM_CNT_CNT_Msk (0xFFFFUL << TIM_CNT_CNT_Pos)

/***************** Bit Definition for TIM_PSC Register **************/
#define TIM_PSC_PSC_Pos 0
#define TIM_PSC_PSC_Msk (0xFFFFUL << TIM_PSC_PSC_Pos)

/***************** Bit Definition for TIM_ARR Register **************/
#define TIM_ARR_ARR_Pos 0
#define TIM_ARR_ARR_Msk (0xFFFFUL << TIM_ARR_ARR_Pos)

/***************** Bit Definition for TIM_RCR Register **************/
#define TIM_RCR_REP_Pos 0
#define TIM_RCR_REP_Msk (0xFFUL << TIM_RCR_REP_Pos)

/***************** Bit Definition for TIM_CCR1 Register **************/
#define TIM_CCR1_CCR1_Pos 0
#define TIM_CCR1_CCR1_Msk (0xFFFFUL << TIM_CCR1_CCR1_Pos)

/***************** Bit Definition for TIM_CCR2 Register **************/
#define TIM_CCR2_CCR2_Pos 0
#define TIM_CCR2_CCR2_Msk (0xFFFFUL << TIM_CCR2_CCR2_Pos)

/***************** Bit Definition for TIM_CCR3 Register **************/
#define TIM_CCR3_CCR3_Pos 0
#define TIM_CCR3_CCR3_Msk (0xFFFFUL << TIM_CCR3_CCR3_Pos)

/***************** Bit Definition for TIM_CCR4 Register **************/
#define TIM_CCR4_CCR4_Pos 0
#define TIM_CCR4_CCR4_Msk (0xFFFFUL << TIM_CCR4_CCR4_Pos)

/***************** Bit Definition for TIM_BDTR Register **************/
#define TIM_BDTR_AOE2_Pos 26
#define TIM_BDTR_AOE2_Msk (0x1UL << TIM_BDTR_AOE2_Pos)
#define TIM_AOE2_OFF (0x0UL << TIM_BDTR_AOE2_Pos)
#define TIM_AOE2_ON (0x1UL << TIM_BDTR_AOE2_Pos)
#define TIM_BDTR_BK2P_Pos 25
#define TIM_BDTR_BK2P_Msk (0x1UL << TIM_BDTR_BK2P_Pos)
#define TIM_BK2P_AL (0x0UL << TIM_BDTR_BK2P_Pos)
#define TIM_BK2P_AH (0x1UL << TIM_BDTR_BK2P_Pos)
#define TIM_BDTR_BK2E_Pos 24
#define TIM_BDTR_BK2E_Msk (0x1UL << TIM_BDTR_BK2E_Pos)
#define TIM_BK2E_OFF (0x0UL << TIM_BDTR_BK2E_Pos)
#define TIM_BK2E_ON (0x1UL << TIM_BDTR_BK2E_Pos)
#define TIM_BDTR_MOE_Pos 15
#define TIM_BDTR_MOE_Msk (0x1UL << TIM_BDTR_MOE_Pos)
#define TIM_MOE_OFF (0x0UL << TIM_BDTR_MOE_Pos)
#define TIM_MOE_ON (0x1UL << TIM_BDTR_MOE_Pos)
#define TIM_BDTR_AOE_Pos 14
#define TIM_BDTR_AOE_Msk (0x1UL << TIM_BDTR_AOE_Pos)
#define TIM_AOE_OFF (0x0UL << TIM_BDTR_AOE_Pos)
#define TIM_AOE_ON (0x1UL << TIM_BDTR_AOE_Pos)
#define TIM_BDTR_BKP_Pos 13
#define TIM_BDTR_BKP_Msk (0x1UL << TIM_BDTR_BKP_Pos)
#define TIM_BKP_AL (0x0UL << TIM_BDTR_BKP_Pos)
#define TIM_BKP_AH (0x1UL << TIM_BDTR_BKP_Pos)
#define TIM_BDTR_BKE_Pos 12
#define TIM_BDTR_BKE_Msk (0x1UL << TIM_BDTR_BKE_Pos)
#define TIM_BKE_OFF (0x0UL << TIM_BDTR_BKE_Pos)
#define TIM_BKE_ON (0x1UL << TIM_BDTR_BKE_Pos)
#define TIM_BDTR_OSSR_Pos 11
#define TIM_BDTR_OSSR_Msk (0x1UL << TIM_BDTR_OSSR_Pos)
#define TIM_OSSR_DIS (0x0UL << TIM_BDTR_OSSR_Pos)
#define TIM_OSSR_EN (0x1UL << TIM_BDTR_OSSR_Pos)
#define TIM_BDTR_OSSI_Pos 10
#define TIM_BDTR_OSSI_Msk (0x1UL << TIM_BDTR_OSSI_Pos)
#define TIM_OSSI_DIS (0x0UL << TIM_BDTR_OSSI_Pos)
#define TIM_OSSI_EN (0x1UL << TIM_BDTR_OSSI_Pos)
#define TIM_BDTR_LOCK_Pos 8
#define TIM_BDTR_LOCK_Msk (0x3UL << TIM_BDTR_LOCK_Pos)
#define TIM_BDTR_DTG_Pos 0
#define TIM_BDTR_DTG_Msk (0xFFUL << TIM_BDTR_DTG_Pos)
#define TIM_DTG(n) ((n) << TIM_BDTR_DTG_Pos)

/***************** Bit Definition for TIM_DCR Register **************/
#define TIM_DCR_DBL_Pos 8
#define TIM_DCR_DBL_Msk (0x1FUL << TIM_DCR_DBL_Pos)
#define TIM_DBL(n) ((n) << TIM_DCR_DBL_Pos)
#define TIM_DCR_DSEL_Pos 5
#define TIM_DCR_DSEL_Msk (0x7UL << TIM_DCR_DSEL_Pos)
#define TIM_DSEL_DIS (0x0UL << TIM_DCR_DSEL_Pos)
#define TIM_DSEL_CH0 (0x1UL << TIM_DCR_DSEL_Pos)
#define TIM_DSEL_CH1 (0x2UL << TIM_DCR_DSEL_Pos)
#define TIM_DSEL_CH2 (0x3UL << TIM_DCR_DSEL_Pos)
#define TIM_DSEL_CH3 (0x4UL << TIM_DCR_DSEL_Pos)
#define TIM_DCR_DBA_Pos 0
#define TIM_DCR_DBA_Msk (0x1FUL << TIM_DCR_DBA_Pos)
#define TIM_DBA(n) ((n) << TIM_DCR_DBA_Pos)

/***************** Bit Definition for TIM_DMAR Register **************/
#define TIM_DMAR_DMAB_Pos 0
#define TIM_DMAR_DMAB_Msk (0xFFFFUL << TIM_DMAR_DMAB_Pos)

/***************** Bit Definition for TIM_OR Register **************/
#define TIM_OR_TI1_RMP_Pos 0
#define TIM_OR_TI1_RMP_Msk (0x3UL << TIM_OR_TI1_RMP_Pos)

/***************** Bit Definition for TIM_CCTR1 Register **************/
#define TIM_CCTR1_CCTR1_Pos 0
#define TIM_CCTR1_CCTR1_Msk (0xFFFFUL << TIM_CCTR1_CCTR1_Pos)

/***************** Bit Definition for TIM_CCTR2 Register **************/
#define TIM_CCTR2_CCTR2_Pos 0
#define TIM_CCTR2_CCTR2_Msk (0xFFFFUL << TIM_CCTR2_CCTR2_Pos)

/***************** Bit Definition for TIM_CCTR3 Register **************/
#define TIM_CCTR3_CCTR3_Pos 0
#define TIM_CCTR3_CCTR3_Msk (0xFFFFUL << TIM_CCTR3_CCTR3_Pos)

/***************** Bit Definition for TIM_CCTR4 Register **************/
#define TIM_CCTR4_CCTR4_Pos 0
#define TIM_CCTR4_CCTR4_Msk (0xFFFFUL << TIM_CCTR4_CCTR4_Pos)

/***************** Bit Definition for TIM_DLAMT Register **************/
#define TIM_DLAMT_DLS_Pos 17
#define TIM_DLAMT_DLS_Msk (0x1UL << TIM_DLAMT_DLS_Pos)
#define TIM_DLS_ACTIVE (0x0UL << TIM_DLAMT_DLS_Pos)
#define TIM_DLS_INACTIVE (0x1UL << TIM_DLAMT_DLS_Pos)
#define TIM_DLAMT_AMTDL_Pos 16
#define TIM_DLAMT_AMTDL_Msk (0x1UL << TIM_DLAMT_AMTDL_Pos)
#define TIM_AMTDL_OFF (0x0UL << TIM_DLAMT_AMTDL_Pos)
#define TIM_AMTDL_ON (0x1UL << TIM_DLAMT_AMTDL_Pos)
#define TIM_DLAMT_AMTG_Pos 8
#define TIM_DLAMT_AMTG_Msk (0xFFUL << TIM_DLAMT_AMTG_Pos)
#define TIM_AMTG(n) ((n) << TIM_DLAMT_AMTG_Pos)
#define TIM_DLAMT_DLG_Pos 0
#define TIM_DLAMT_DLG_Msk (0xFFUL << TIM_DLAMT_DLG_Pos)
#define TIM_DLG(n) ((n) << TIM_DLAMT_DLG_Pos)

/******************** TIMx Register Struct Definition *****************/

/**
 * @brief  NVIC Init Structure definition
 */

typedef struct
{
  uint16_t NVIC_IRQChannel; /*!< Specifies the IRQ channel to be enabled or disabled.
                                            This parameter can be a value of @ref IRQn_Type
                                          */

  uint8_t NVIC_IRQChannelPriority; /*!< Specifies the priority level for the IRQ channel specified
                                            in NVIC_IRQChannel. This parameter can be a value
                                            between 0 and 3.  */

  FunctionalState NVIC_IRQChannelCmd; /*!< Specifies whether the IRQ channel defined in NVIC_IRQChannel
                                            will be enabled or disabled.
                                            This parameter can be set either to ENABLE or DISABLE */
} NVIC_InitTypeDef;

typedef struct
{
  uint16_t TIM_Prescaler; /*!< Specifies the prescaler value used to divide the TIM clock.
                                       This parameter can be a number between 0x0000 and 0xFFFF */

  uint16_t TIM_CounterMode; /*!< Specifies the counter mode.
                                       This parameter can be a value of @ref TIM_Counter_Mode */

  uint32_t TIM_Period; /*!< Specifies the period value to be loaded into the active
                                       Auto-Reload Register at the next update event.
                                       This parameter must be a number between 0x0000 and 0xFFFF.  */

  uint16_t TIM_ClockDivision; /*!< Specifies the clock division.
                                      This parameter can be a value of @ref TIM_Clock_Division_CKD */

  uint8_t TIM_RepetitionCounter; /*!< Specifies the repetition counter value. Each time the RCR downcounter
                                       reaches zero, an update event is generated and counting restarts
                                       from the RCR value (N).
                                       This means in PWM mode that (N+1) corresponds to:
                                          - the number of PWM periods in edge-aligned mode
                                          - the number of half PWM period in center-aligned mode
                                       This parameter must be a number between 0x00 and 0xFF.
                                       @note This parameter is valid only for TIM1. */
} TIM_TimeBaseInitTypeDef;

typedef struct
{
  uint16_t TIM_OCMode; /*!< Specifies the TIM mode.
                                   This parameter can be a value of @ref TIM_Output_Compare_and_PWM_modes */

  uint16_t TIM_OutputState; /*!< Specifies the TIM Output Compare state.
                                   This parameter can be a value of @ref TIM_Output_Compare_state */

  uint16_t TIM_OutputNState; /*!< Specifies the TIM complementary Output Compare state.
                                   This parameter can be a value of @ref TIM_Output_Compare_N_state
                                   @note This parameter is valid only for TIM1. */

  uint32_t TIM_Pulse; /*!< Specifies the pulse value to be loaded into the Capture Compare Register.
                                   This parameter can be a number between 0x0000 and 0xFFFF ( or 0xFFFFFFFF
                                   for TIM2) */

  uint16_t TIM_OCPolarity; /*!< Specifies the output polarity.
                                   This parameter can be a value of @ref TIM_Output_Compare_Polarity */

  uint16_t TIM_OCNPolarity; /*!< Specifies the complementary output polarity.
                                   This parameter can be a value of @ref TIM_Output_Compare_N_Polarity
                                   @note This parameter is valid only for TIM1. */

  uint16_t TIM_OCIdleState; /*!< Specifies the TIM Output Compare pin state during Idle state.
                                   This parameter can be a value of @ref TIM_Output_Compare_Idle_State
                                   @note This parameter is valid only for TIM1. */

  uint16_t TIM_OCNIdleState; /*!< Specifies the TIM Output Compare pin state during Idle state.
                                   This parameter can be a value of @ref TIM_Output_Compare_N_Idle_State
                                   @note This parameter is valid only for TIM1. */
} TIM_OCInitTypeDef;

typedef struct
{

  uint16_t TIM_Channel; /*!< Specifies the TIM channel.
                                  This parameter can be a value of @ref TIM_Channel */

  uint16_t TIM_ICPolarity; /*!< Specifies the active edge of the input signal.
                                  This parameter can be a value of @ref TIM_Input_Capture_Polarity */

  uint16_t TIM_ICSelection; /*!< Specifies the input.
                                  This parameter can be a value of @ref TIM_Input_Capture_Selection */

  uint16_t TIM_ICPrescaler; /*!< Specifies the Input Capture Prescaler.
                                  This parameter can be a value of @ref TIM_Input_Capture_Prescaler */

  uint16_t TIM_ICFilter; /*!< Specifies the input capture filter.
                                  This parameter can be a number between 0x0 and 0xF */
} TIM_ICInitTypeDef;

typedef struct
{

  uint16_t TIM_OSSRState; /*!< Specifies the Off-State selection used in Run mode.
                                      This parameter can be a value of @ref TIM_OSSR_Off_State_Selection_for_Run_mode_state */

  uint16_t TIM_OSSIState; /*!< Specifies the Off-State used in Idle state.
                                      This parameter can be a value of @ref TIM_OSSI_Off_State_Selection_for_Idle_mode_state */

  uint16_t TIM_LOCKLevel; /*!< Specifies the LOCK level parameters.
                                      This parameter can be a value of @ref TIM_Lock_level */

  uint16_t TIM_DeadTime; /*!< Specifies the delay time between the switching-off and the
                                      switching-on of the outputs.
                                      This parameter can be a number between 0x00 and 0xFF  */

  uint16_t TIM_Break; /*!< Specifies whether the TIM Break input is enabled or not.
                                      This parameter can be a value of @ref TIM_Break_Input_enable_disable */

  uint16_t TIM_BreakPolarity; /*!< Specifies the TIM Break Input pin polarity.
                                      This parameter can be a value of @ref TIM_Break_Polarity */

  uint16_t TIM_AutomaticOutput; /*!< Specifies whether the TIM Automatic Output feature is enabled or not.
                                      This parameter can be a value of @ref TIM_AOE_Bit_Set_Reset */

} TIM_BDTRInitTypeDef;

#define IS_TIM_ALL_PERIPH(PERIPH) (((PERIPH) == TIM1) ||  \
                                   ((PERIPH) == TIM3) ||  \
                                   ((PERIPH) == TIM6) ||  \
                                   ((PERIPH) == TIM14) || \
                                   ((PERIPH) == TIM15) || \
                                   ((PERIPH) == TIM16) || \
                                   ((PERIPH) == TIM17))
/* LIST1: TIM 1 */
#define IS_TIM_LIST1_PERIPH(PERIPH) ((PERIPH) == TIM1)

/* LIST2: TIM 1, 15, 16 and 17 */
#define IS_TIM_LIST2_PERIPH(PERIPH) (((PERIPH) == TIM1) ||  \
                                     ((PERIPH) == TIM15) || \
                                     ((PERIPH) == TIM16) || \
                                     ((PERIPH) == TIM17))

/* LIST3: TIM 1, 2 and 3 */
#define IS_TIM_LIST3_PERIPH(PERIPH) (((PERIPH) == TIM1) || \
                                     ((PERIPH) == TIM2) || \
                                     ((PERIPH) == TIM3))

/* LIST4: TIM 1, 2, 3, 14, 15, 16 and 17 */
#define IS_TIM_LIST4_PERIPH(PERIPH) (((PERIPH) == TIM1) ||  \
                                     ((PERIPH) == TIM2) ||  \
                                     ((PERIPH) == TIM3) ||  \
                                     ((PERIPH) == TIM14) || \
                                     ((PERIPH) == TIM15) || \
                                     ((PERIPH) == TIM16) || \
                                     ((PERIPH) == TIM17))

/* LIST4: TIM 1, 2, 3, 15, 16 and 17 */
#define IS_TIM_LIST5_PERIPH(PERIPH) (((PERIPH) == TIM1) ||  \
                                     ((PERIPH) == TIM2) ||  \
                                     ((PERIPH) == TIM3) ||  \
                                     ((PERIPH) == TIM15) || \
                                     ((PERIPH) == TIM16) || \
                                     ((PERIPH) == TIM17))

/* LIST5: TIM 1, 2, 3 and 15 */
#define IS_TIM_LIST6_PERIPH(PERIPH) (((PERIPH) == TIM1) || \
                                     ((PERIPH) == TIM2) || \
                                     ((PERIPH) == TIM3) || \
                                     ((PERIPH) == TIM15))

/* LIST7: TIM 1, 2, 3, 6 and 14 */
#define IS_TIM_LIST7_PERIPH(PERIPH) (((PERIPH) == TIM1) || \
                                     ((PERIPH) == TIM2) || \
                                     ((PERIPH) == TIM3) || \
                                     ((PERIPH) == TIM6) || \
                                     ((PERIPH) == TIM14))

/* LIST8: TIM 1, 2, 3 and 14 */
#define IS_TIM_LIST8_PERIPH(PERIPH) (((PERIPH) == TIM1) || \
                                     ((PERIPH) == TIM2) || \
                                     ((PERIPH) == TIM3) || \
                                     ((PERIPH) == TIM14))

/* LIST9: TIM 1, 2, 3, 6 and 15 */
#define IS_TIM_LIST9_PERIPH(PERIPH) (((PERIPH) == TIM1) || \
                                     ((PERIPH) == TIM2) || \
                                     ((PERIPH) == TIM3) || \
                                     ((PERIPH) == TIM6) || \
                                     ((PERIPH) == TIM15))

/* LIST10: TIM 1, 2, 3, 6, 15, 16 and 17 */
#define IS_TIM_LIST10_PERIPH(PERIPH) (((PERIPH) == TIM1) ||  \
                                      ((PERIPH) == TIM2) ||  \
                                      ((PERIPH) == TIM3) ||  \
                                      ((PERIPH) == TIM6) ||  \
                                      ((PERIPH) == TIM15) || \
                                      ((PERIPH) == TIM16) || \
                                      ((PERIPH) == TIM17))

/* LIST1: TIM 11 */
#define IS_TIM_LIST11_PERIPH(PERIPH) ((PERIPH) == TIM14)

#define TIM_OCMode_Timing ((uint16_t)0x0000)
#define TIM_OCMode_Active ((uint16_t)0x0010)
#define TIM_OCMode_Inactive ((uint16_t)0x0020)
#define TIM_OCMode_Toggle ((uint16_t)0x0030)
#define TIM_OCMode_Invalid_Level ((uint16_t)0x0040)
#define TIM_OCMode_Active_Level ((uint16_t)0x0050)
#define TIM_OCMode_PWM1 ((uint16_t)0x0060)
#define TIM_OCMode_PWM2 ((uint16_t)0x0070)
#define IS_TIM_OC_MODE(MODE) (((MODE) == TIM_OCMode_Timing) ||   \
                              ((MODE) == TIM_OCMode_Active) ||   \
                              ((MODE) == TIM_OCMode_Inactive) || \
                              ((MODE) == TIM_OCMode_Toggle) ||   \
                              ((MODE) == TIM_OCMode_PWM1) ||     \
                              ((MODE) == TIM_OCMode_PWM2))
#define IS_TIM_OCM(MODE) (((MODE) == TIM_OCMode_Timing) ||       \
                          ((MODE) == TIM_OCMode_Active) ||       \
                          ((MODE) == TIM_OCMode_Inactive) ||     \
                          ((MODE) == TIM_OCMode_Toggle) ||       \
                          ((MODE) == TIM_OCMode_PWM1) ||         \
                          ((MODE) == TIM_OCMode_PWM2) ||         \
                          ((MODE) == TIM_ForcedAction_Active) || \
                          ((MODE) == TIM_ForcedAction_InActive))
/**
 * @}
 */

/** @defgroup TIM_One_Pulse_Mode
 * @{
 */

#define TIM_OPMode_Single ((uint16_t)0x0008)
#define TIM_OPMode_Repetitive ((uint16_t)0x0000)
#define IS_TIM_OPM_MODE(MODE) (((MODE) == TIM_OPMode_Single) || \
                               ((MODE) == TIM_OPMode_Repetitive))
/**
 * @}
 */

/** @defgroup TIM_Channel
 * @{
 */

#define TIM_Channel_1 ((uint16_t)0x0000)
#define TIM_Channel_2 ((uint16_t)0x0004)
#define TIM_Channel_3 ((uint16_t)0x0008)
#define TIM_Channel_4 ((uint16_t)0x000C)

#define IS_TIM_CHANNEL(CHANNEL) (((CHANNEL) == TIM_Channel_1) || \
                                 ((CHANNEL) == TIM_Channel_2) || \
                                 ((CHANNEL) == TIM_Channel_3) || \
                                 ((CHANNEL) == TIM_Channel_4))
#define IS_TIM_COMPLEMENTARY_CHANNEL(CHANNEL) (((CHANNEL) == TIM_Channel_1) || \
                                               ((CHANNEL) == TIM_Channel_2) || \
                                               ((CHANNEL) == TIM_Channel_3))
#define IS_TIM_PWMI_CHANNEL(CHANNEL) (((CHANNEL) == TIM_Channel_1) || \
                                      ((CHANNEL) == TIM_Channel_2))

/**
 * @}
 */

/** @defgroup TIM_Clock_Division_CKD
 * @{
 */

#define TIM_CKD_DIV1 ((uint16_t)0x0000)
#define TIM_CKD_DIV2 ((uint16_t)0x0100)
#define TIM_CKD_DIV4 ((uint16_t)0x0200)
#define IS_TIM_CKD_DIV(DIV) (((DIV) == TIM_CKD_DIV1) || \
                             ((DIV) == TIM_CKD_DIV2) || \
                             ((DIV) == TIM_CKD_DIV4))
/**
 * @}
 */

/** @defgroup TIM_Counter_Mode
 * @{
 */

#define TIM_CounterMode_Up ((uint16_t)0x0000)
#define TIM_CounterMode_Down ((uint16_t)0x0010)
#define TIM_CounterMode_CenterAligned1 ((uint16_t)0x0020)
#define TIM_CounterMode_CenterAligned2 ((uint16_t)0x0040)
#define TIM_CounterMode_CenterAligned3 ((uint16_t)0x0060)
#define IS_TIM_COUNTER_MODE(MODE) (((MODE) == TIM_CounterMode_Up) ||             \
                                   ((MODE) == TIM_CounterMode_Down) ||           \
                                   ((MODE) == TIM_CounterMode_CenterAligned1) || \
                                   ((MODE) == TIM_CounterMode_CenterAligned2) || \
                                   ((MODE) == TIM_CounterMode_CenterAligned3))
/**
 * @}
 */

/** @defgroup TIM_Output_Compare_Polarity
 * @{
 */

#define TIM_OCPolarity_High ((uint16_t)0x0000)
#define TIM_OCPolarity_Low ((uint16_t)0x0002)
#define IS_TIM_OC_POLARITY(POLARITY) (((POLARITY) == TIM_OCPolarity_High) || \
                                      ((POLARITY) == TIM_OCPolarity_Low))
/**
 * @}
 */

/** @defgroup TIM_Output_Compare_N_Polarity
 * @{
 */

#define TIM_OCNPolarity_High ((uint16_t)0x0000)
#define TIM_OCNPolarity_Low ((uint16_t)0x0008)
#define IS_TIM_OCN_POLARITY(POLARITY) (((POLARITY) == TIM_OCNPolarity_High) || \
                                       ((POLARITY) == TIM_OCNPolarity_Low))
/**
 * @}
 */

/** @defgroup TIM_Output_Compare_state
 * @{
 */

#define TIM_OutputState_Disable ((uint16_t)0x0000)
#define TIM_OutputState_Enable ((uint16_t)0x0001)
#define IS_TIM_OUTPUT_STATE(STATE) (((STATE) == TIM_OutputState_Disable) || \
                                    ((STATE) == TIM_OutputState_Enable))
/**
 * @}
 */

/** @defgroup TIM_Output_Compare_N_state
 * @{
 */

#define TIM_OutputNState_Disable ((uint16_t)0x0000)
#define TIM_OutputNState_Enable ((uint16_t)0x0004)
#define IS_TIM_OUTPUTN_STATE(STATE) (((STATE) == TIM_OutputNState_Disable) || \
                                     ((STATE) == TIM_OutputNState_Enable))
/**
 * @}
 */

/** @defgroup TIM_Capture_Compare_state
 * @{
 */

#define TIM_CCx_Enable ((uint16_t)0x0001)
#define TIM_CCx_Disable ((uint16_t)0x0000)
#define IS_TIM_CCX(CCX) (((CCX) == TIM_CCx_Enable) || \
                         ((CCX) == TIM_CCx_Disable))
/**
 * @}
 */

/** @defgroup TIM_Capture_Compare_N_state
 * @{
 */

#define TIM_CCxN_Enable ((uint16_t)0x0004)
#define TIM_CCxN_Disable ((uint16_t)0x0000)
#define IS_TIM_CCXN(CCXN) (((CCXN) == TIM_CCxN_Enable) || \
                           ((CCXN) == TIM_CCxN_Disable))
/**
 * @}
 */

/** @defgroup TIM_Break_Input_enable_disable
 * @{
 */

#define TIM_Break_Enable ((uint16_t)0x1000)
#define TIM_Break_Disable ((uint16_t)0x0000)
#define IS_TIM_BREAK_STATE(STATE) (((STATE) == TIM_Break_Enable) || \
                                   ((STATE) == TIM_Break_Disable))
/**
 * @}
 */

/** @defgroup TIM_Break_Polarity
 * @{
 */

#define TIM_BreakPolarity_Low ((uint16_t)0x0000)
#define TIM_BreakPolarity_High ((uint16_t)0x2000)
#define IS_TIM_BREAK_POLARITY(POLARITY) (((POLARITY) == TIM_BreakPolarity_Low) || \
                                         ((POLARITY) == TIM_BreakPolarity_High))
/**
 * @}
 */

/** @defgroup TIM_AOE_Bit_Set_Reset
 * @{
 */

#define TIM_AutomaticOutput_Enable ((uint16_t)0x4000)
#define TIM_AutomaticOutput_Disable ((uint16_t)0x0000)
#define IS_TIM_AUTOMATIC_OUTPUT_STATE(STATE) (((STATE) == TIM_AutomaticOutput_Enable) || \
                                              ((STATE) == TIM_AutomaticOutput_Disable))
/**
 * @}
 */

/** @defgroup TIM_Lock_level
 * @{
 */

#define TIM_LOCKLevel_OFF ((uint16_t)0x0000)
#define TIM_LOCKLevel_1 ((uint16_t)0x0100)
#define TIM_LOCKLevel_2 ((uint16_t)0x0200)
#define TIM_LOCKLevel_3 ((uint16_t)0x0300)
#define IS_TIM_LOCK_LEVEL(LEVEL) (((LEVEL) == TIM_LOCKLevel_OFF) || \
                                  ((LEVEL) == TIM_LOCKLevel_1) ||   \
                                  ((LEVEL) == TIM_LOCKLevel_2) ||   \
                                  ((LEVEL) == TIM_LOCKLevel_3))
/**
 * @}
 */

/** @defgroup TIM_OSSI_Off_State_Selection_for_Idle_mode_state
 * @{
 */

#define TIM_OSSIState_Enable ((uint16_t)0x0400)
#define TIM_OSSIState_Disable ((uint16_t)0x0000)
#define IS_TIM_OSSI_STATE(STATE) (((STATE) == TIM_OSSIState_Enable) || \
                                  ((STATE) == TIM_OSSIState_Disable))
/**
 * @}
 */

/** @defgroup TIM_OSSR_Off_State_Selection_for_Run_mode_state
 * @{
 */

#define TIM_OSSRState_Enable ((uint16_t)0x0800)
#define TIM_OSSRState_Disable ((uint16_t)0x0000)
#define IS_TIM_OSSR_STATE(STATE) (((STATE) == TIM_OSSRState_Enable) || \
                                  ((STATE) == TIM_OSSRState_Disable))
/**
 * @}
 */

/** @defgroup TIM_Output_Compare_Idle_State
 * @{
 */

#define TIM_OCIdleState_Set ((uint16_t)0x0100)
#define TIM_OCIdleState_Reset ((uint16_t)0x0000)
#define IS_TIM_OCIDLE_STATE(STATE) (((STATE) == TIM_OCIdleState_Set) || \
                                    ((STATE) == TIM_OCIdleState_Reset))
/**
 * @}
 */

/** @defgroup TIM_Output_Compare_N_Idle_State
 * @{
 */

#define TIM_OCNIdleState_Set ((uint16_t)0x0200)
#define TIM_OCNIdleState_Reset ((uint16_t)0x0000)
#define IS_TIM_OCNIDLE_STATE(STATE) (((STATE) == TIM_OCNIdleState_Set) || \
                                     ((STATE) == TIM_OCNIdleState_Reset))
/**
 * @}
 */

/** @defgroup TIM_Input_Capture_Polarity
 * @{
 */

#define TIM_ICPolarity_Rising ((uint16_t)0x0000)
#define TIM_ICPolarity_Falling ((uint16_t)0x0002)
#define TIM_ICPolarity_BothEdge ((uint16_t)0x000A)
#define IS_TIM_IC_POLARITY(POLARITY) (((POLARITY) == TIM_ICPolarity_Rising) ||  \
                                      ((POLARITY) == TIM_ICPolarity_Falling) || \
                                      ((POLARITY) == TIM_ICPolarity_BothEdge))
/**
 * @}
 */

/** @defgroup TIM_Input_Capture_Selection
 * @{
 */

#define TIM_ICSelection_DirectTI ((uint16_t)0x0001)   /*!< TIM Input 1, 2, 3 or 4 is selected to be \
                                                           connected to IC1, IC2, IC3 or IC4, respectively */
#define TIM_ICSelection_IndirectTI ((uint16_t)0x0002) /*!< TIM Input 1, 2, 3 or 4 is selected to be \
                                                           connected to IC2, IC1, IC4 or IC3, respectively. */
#define TIM_ICSelection_TRC ((uint16_t)0x0003)        /*!< TIM Input 1, 2, 3 or 4 is selected to be connected to TRC. */
#define IS_TIM_IC_SELECTION(SELECTION) (((SELECTION) == TIM_ICSelection_DirectTI) ||   \
                                        ((SELECTION) == TIM_ICSelection_IndirectTI) || \
                                        ((SELECTION) == TIM_ICSelection_TRC))
/**
 * @}
 */

/** @defgroup TIM_Input_Capture_Prescaler
 * @{
 */

#define TIM_ICPSC_DIV1 ((uint16_t)0x0000) /*!< Capture performed each time an edge is detected on the capture input. */
#define TIM_ICPSC_DIV2 ((uint16_t)0x0004) /*!< Capture performed once every 2 events. */
#define TIM_ICPSC_DIV4 ((uint16_t)0x0008) /*!< Capture performed once every 4 events. */
#define TIM_ICPSC_DIV8 ((uint16_t)0x000C) /*!< Capture performed once every 8 events. */
#define IS_TIM_IC_PRESCALER(PRESCALER) (((PRESCALER) == TIM_ICPSC_DIV1) || \
                                        ((PRESCALER) == TIM_ICPSC_DIV2) || \
                                        ((PRESCALER) == TIM_ICPSC_DIV4) || \
                                        ((PRESCALER) == TIM_ICPSC_DIV8))
/**
 * @}
 */

/** @defgroup TIM_interrupt_sources
 * @{
 */

#define TIM_IT_Update ((uint16_t)0x0001)
#define TIM_IT_CC1 ((uint16_t)0x0002)
#define TIM_IT_CC2 ((uint16_t)0x0004)
#define TIM_IT_CC3 ((uint16_t)0x0008)
#define TIM_IT_CC4 ((uint16_t)0x0010)
#define TIM_IT_COM ((uint16_t)0x0020)
#define TIM_IT_Trigger ((uint16_t)0x0040)
#define TIM_IT_Break ((uint16_t)0x0080)
#define IS_TIM_IT(IT) ((((IT) & (uint16_t)0xFF00) == 0x0000) && ((IT) != 0x0000))

#define IS_TIM_GET_IT(IT) (((IT) == TIM_IT_Update) ||  \
                           ((IT) == TIM_IT_CC1) ||     \
                           ((IT) == TIM_IT_CC2) ||     \
                           ((IT) == TIM_IT_CC3) ||     \
                           ((IT) == TIM_IT_CC4) ||     \
                           ((IT) == TIM_IT_COM) ||     \
                           ((IT) == TIM_IT_Trigger) || \
                           ((IT) == TIM_IT_Break))
/**
 * @}
 */

/** @defgroup TIM_DMA_Base_address
 * @{
 */

#define TIM_DMABase_CR1 ((uint16_t)0x0000)
#define TIM_DMABase_CR2 ((uint16_t)0x0001)
#define TIM_DMABase_SMCR ((uint16_t)0x0002)
#define TIM_DMABase_DIER ((uint16_t)0x0003)
#define TIM_DMABase_SR ((uint16_t)0x0004)
#define TIM_DMABase_EGR ((uint16_t)0x0005)
#define TIM_DMABase_CCMR1 ((uint16_t)0x0006)
#define TIM_DMABase_CCMR2 ((uint16_t)0x0007)
#define TIM_DMABase_CCER ((uint16_t)0x0008)
#define TIM_DMABase_CNT ((uint16_t)0x0009)
#define TIM_DMABase_PSC ((uint16_t)0x000A)
#define TIM_DMABase_ARR ((uint16_t)0x000B)
#define TIM_DMABase_RCR ((uint16_t)0x000C)
#define TIM_DMABase_CCR1 ((uint16_t)0x000D)
#define TIM_DMABase_CCR2 ((uint16_t)0x000E)
#define TIM_DMABase_CCR3 ((uint16_t)0x000F)
#define TIM_DMABase_CCR4 ((uint16_t)0x0010)
#define TIM_DMABase_BDTR ((uint16_t)0x0011)
#define TIM_DMABase_DCR ((uint16_t)0x0012)
#define TIM_DMABase_OR ((uint16_t)0x0013)
#define IS_TIM_DMA_BASE(BASE) (((BASE) == TIM_DMABase_CR1) ||   \
                               ((BASE) == TIM_DMABase_CR2) ||   \
                               ((BASE) == TIM_DMABase_SMCR) ||  \
                               ((BASE) == TIM_DMABase_DIER) ||  \
                               ((BASE) == TIM_DMABase_SR) ||    \
                               ((BASE) == TIM_DMABase_EGR) ||   \
                               ((BASE) == TIM_DMABase_CCMR1) || \
                               ((BASE) == TIM_DMABase_CCMR2) || \
                               ((BASE) == TIM_DMABase_CCER) ||  \
                               ((BASE) == TIM_DMABase_CNT) ||   \
                               ((BASE) == TIM_DMABase_PSC) ||   \
                               ((BASE) == TIM_DMABase_ARR) ||   \
                               ((BASE) == TIM_DMABase_RCR) ||   \
                               ((BASE) == TIM_DMABase_CCR1) ||  \
                               ((BASE) == TIM_DMABase_CCR2) ||  \
                               ((BASE) == TIM_DMABase_CCR3) ||  \
                               ((BASE) == TIM_DMABase_CCR4) ||  \
                               ((BASE) == TIM_DMABase_BDTR) ||  \
                               ((BASE) == TIM_DMABase_DCR) ||   \
                               ((BASE) == TIM_DMABase_OR))
/**
 * @}
 */

/** @defgroup TIM_DMA_Burst_Length
 * @{
 */

#define TIM_DMABurstLength_1Transfer ((uint16_t)0x0000)
#define TIM_DMABurstLength_2Transfers ((uint16_t)0x0100)
#define TIM_DMABurstLength_3Transfers ((uint16_t)0x0200)
#define TIM_DMABurstLength_4Transfers ((uint16_t)0x0300)
#define TIM_DMABurstLength_5Transfers ((uint16_t)0x0400)
#define TIM_DMABurstLength_6Transfers ((uint16_t)0x0500)
#define TIM_DMABurstLength_7Transfers ((uint16_t)0x0600)
#define TIM_DMABurstLength_8Transfers ((uint16_t)0x0700)
#define TIM_DMABurstLength_9Transfers ((uint16_t)0x0800)
#define TIM_DMABurstLength_10Transfers ((uint16_t)0x0900)
#define TIM_DMABurstLength_11Transfers ((uint16_t)0x0A00)
#define TIM_DMABurstLength_12Transfers ((uint16_t)0x0B00)
#define TIM_DMABurstLength_13Transfers ((uint16_t)0x0C00)
#define TIM_DMABurstLength_14Transfers ((uint16_t)0x0D00)
#define TIM_DMABurstLength_15Transfers ((uint16_t)0x0E00)
#define TIM_DMABurstLength_16Transfers ((uint16_t)0x0F00)
#define TIM_DMABurstLength_17Transfers ((uint16_t)0x1000)
#define TIM_DMABurstLength_18Transfers ((uint16_t)0x1100)
#define IS_TIM_DMA_LENGTH(LENGTH) (((LENGTH) == TIM_DMABurstLength_1Transfer) ||   \
                                   ((LENGTH) == TIM_DMABurstLength_2Transfers) ||  \
                                   ((LENGTH) == TIM_DMABurstLength_3Transfers) ||  \
                                   ((LENGTH) == TIM_DMABurstLength_4Transfers) ||  \
                                   ((LENGTH) == TIM_DMABurstLength_5Transfers) ||  \
                                   ((LENGTH) == TIM_DMABurstLength_6Transfers) ||  \
                                   ((LENGTH) == TIM_DMABurstLength_7Transfers) ||  \
                                   ((LENGTH) == TIM_DMABurstLength_8Transfers) ||  \
                                   ((LENGTH) == TIM_DMABurstLength_9Transfers) ||  \
                                   ((LENGTH) == TIM_DMABurstLength_10Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_11Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_12Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_13Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_14Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_15Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_16Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_17Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_18Transfers))
/**
 * @}
 */

/** @defgroup TIM_DMA_sources
 * @{
 */

#define TIM_DMA_Update ((uint16_t)0x0100)
#define TIM_DMA_CC1 ((uint16_t)0x0200)
#define TIM_DMA_CC2 ((uint16_t)0x0400)
#define TIM_DMA_CC3 ((uint16_t)0x0800)
#define TIM_DMA_CC4 ((uint16_t)0x1000)
#define TIM_DMA_COM ((uint16_t)0x2000)
#define TIM_DMA_Trigger ((uint16_t)0x4000)
#define IS_TIM_DMA_SOURCE(SOURCE) ((((SOURCE) & (uint16_t)0x80FF) == 0x0000) && ((SOURCE) != 0x0000))

/**
 * @}SYSCTRL_EDU_CFGx输入触发源配置
 */
#define TIM1_INPUT_TI1 ((uint8_t)0x00)
#define TIM1_INPUT_TI2 ((uint8_t)0x01)
#define TIM1_INPUT_TI3 ((uint8_t)0x02)
#define TIM1_INPUT_TI4 ((uint8_t)0x03)
#define TIM1_INPUT_ETR ((uint8_t)0x04)
#define IS_TIM1_INPUT_TI(TIx) ((TIx == TIM1_INPUT_TI1) || \
                               (TIx == TIM1_INPUT_TI2) || \
                               (TIx == TIM1_INPUT_TI3) || \
                               (TIx == TIM1_INPUT_TI4) || \
                               (TIx == TIM1_INPUT_ETR))
#define TIM1_IntputSource_IO ((uint32_t)0x00000000)
#define TIM1_IntputSource_AWD ((uint32_t)0x00000001)
#define TIM1_IntputSource_ACMP0_OUTPUT ((uint32_t)0x00000002)
#define TIM1_IntputSource_ACMP1_OUTPUT ((uint32_t)0x00000003)
#define TIM1_IntputSource_ACMP2_OUTPUT ((uint32_t)0x00000004)
#define TIM1_IntputSource_TIM15_OC1_TRIG ((uint32_t)0x00000005)
#define TIM1_IntputSource_TIM3_OC1_TRIG ((uint32_t)0x00000006)
#define TIM1_IntputSource_TIM14_OC1_TRIG ((uint32_t)0x00000007)
#define IS_TIM1_IntputSource(INx) ((INx == TIM1_IntputSource_IO) ||             \
                                   (INx == TIM1_IntputSource_AWD) ||            \
                                   (INx == TIM1_IntputSource_ACMP0_OUTPUT) ||   \
                                   (INx == TIM1_IntputSource_ACMP1_OUTPUT) ||   \
                                   (INx == TIM1_IntputSource_ACMP2_OUTPUT) ||   \
                                   (INx == TIM1_IntputSource_TIM15_OC1_TRIG) || \
                                   (INx == TIM1_IntputSource_TIM3_OC1_TRIG) ||  \
                                   (INx == TIM1_IntputSource_TIM14_OC1_TRIG))

#define TIM3_INPUT_TI1 ((uint8_t)0x00)
#define TIM3_INPUT_TI2 ((uint8_t)0x01)
#define TIM3_INPUT_TI3 ((uint8_t)0x02)
#define TIM3_INPUT_TI4 ((uint8_t)0x03)
#define TIM3_INPUT_ETR ((uint8_t)0x04)
#define IS_TIM3_INPUT_TI(TIx) ((TIx == TIM3_INPUT_TI1) || \
                               (TIx == TIM3_INPUT_TI2) || \
                               (TIx == TIM3_INPUT_TI3) || \
                               (TIx == TIM3_INPUT_TI4) || \
                               (TIx == TIM3_INPUT_ETR))
#define TIM3_IntputSource_IO ((uint32_t)0x00000000)
#define TIM3_IntputSource_AWD ((uint32_t)0x00000001)
#define TIM3_IntputSource_ACMP0_OUTPUT ((uint32_t)0x00000002)
#define TIM3_IntputSource_ACMP1_OUTPUT ((uint32_t)0x00000003)
#define TIM3_IntputSource_ACMP2_OUTPUT ((uint32_t)0x00000004)
#define TIM3_IntputSource_TIM1_OC1_TRIG ((uint32_t)0x00000005)
#define TIM3_IntputSource_TIM15_OC1_TRIG ((uint32_t)0x00000006)
#define TIM3_IntputSource_TIM16_OC1_TRIG ((uint32_t)0x00000007)
#define IS_TIM3_IntputSource(INx) ((INx == TIM3_IntputSource_IO) ||             \
                                   (INx == TIM3_IntputSource_AWD) ||            \
                                   (INx == TIM3_IntputSource_ACMP0_OUTPUT) ||   \
                                   (INx == TIM3_IntputSource_ACMP1_OUTPUT) ||   \
                                   (INx == TIM3_IntputSource_ACMP2_OUTPUT) ||   \
                                   (INx == TIM3_IntputSource_TIM1_OC1_TRIG) ||  \
                                   (INx == TIM3_IntputSource_TIM15_OC1_TRIG) || \
                                   (INx == TIM3_IntputSource_TIM16_OC1_TRIG))

#define TIM15_INPUT_TI1 ((uint8_t)0x00)
#define TIM15_INPUT_TI2 ((uint8_t)0x01)
#define TIM15_INPUT_ETR ((uint8_t)0x02)
#define IS_TIM15_INPUT_TI(TIx) ((TIx == TIM15_INPUT_TI1) || \
                                (TIx == TIM15_INPUT_TI2) || \
                                (TIx == TIM15_INPUT_ETR))
#define TIM15_IntputSource_IO ((uint32_t)0x00000000)
#define TIM15_IntputSource_AWD ((uint32_t)0x00000001)
#define TIM15_IntputSource_ACMP0_OUTPUT ((uint32_t)0x00000002)
#define TIM15_IntputSource_ACMP1_OUTPUT ((uint32_t)0x00000003)
#define TIM15_IntputSource_ACMP2_OUTPUT ((uint32_t)0x00000004)
#define TIM15_IntputSource_TIM1_OC1_TRIG ((uint32_t)0x00000005)
#define TIM15_IntputSource_TIM3_OC1_TRIG ((uint32_t)0x00000006)
#define TIM15_IntputSource_TIM14_OC1_TRIG ((uint32_t)0x00000007)
#define IS_TIM15_IntputSource(INx) ((INx == TIM15_IntputSource_IO) ||            \
                                    (INx == TIM15_IntputSource_AWD) ||           \
                                    (INx == TIM15_IntputSource_ACMP0_OUTPUT) ||  \
                                    (INx == TIM15_IntputSource_ACMP1_OUTPUT) ||  \
                                    (INx == TIM15_IntputSource_ACMP2_OUTPUT) ||  \
                                    (INx == TIM15_IntputSource_TIM1_OC1_TRIG) || \
                                    (INx == TIM15_IntputSource_TIM3_OC1_TRIG) || \
                                    (INx == TIM15_IntputSource_TIM14_OC1_TRIG))

#define TIM16_INPUT_TI1 ((uint8_t)0x00)
#define TIM16_INPUT_ETR ((uint8_t)0x01)
#define IS_TIM16_INPUT_TI(TIx) ((TIx == TIM16_INPUT_TI1) || (TIx == TIM16_INPUT_ETR))

#define TIM16_IntputSource_IO ((uint32_t)0x00000000)
#define TIM16_IntputSource_AWD ((uint32_t)0x00000001)
#define TIM16_IntputSource_ACMP0_OUTPUT ((uint32_t)0x00000002)
#define TIM16_IntputSource_ACMP1_OUTPUT ((uint32_t)0x00000003)
#define TIM16_IntputSource_ACMP2_OUTPUT ((uint32_t)0x00000004)
#define TIM16_IntputSource_TIM1_TRGO ((uint32_t)0x00000005)
#define TIM16_IntputSource_TIM3_TRGO ((uint32_t)0x00000006)
#define TIM16_IntputSource_TIM15_TRGO ((uint32_t)0x00000007)
#define IS_TIM16_IntputSource(INx) ((INx == TIM16_IntputSource_IO) ||           \
                                    (INx == TIM16_IntputSource_AWD) ||          \
                                    (INx == TIM16_IntputSource_ACMP0_OUTPUT) || \
                                    (INx == TIM16_IntputSource_ACMP1_OUTPUT) || \
                                    (INx == TIM16_IntputSource_ACMP2_OUTPUT) || \
                                    (INx == TIM16_IntputSource_TIM1_TRGO) ||    \
                                    (INx == TIM16_IntputSource_TIM3_TRGO) ||    \
                                    (INx == TIM16_IntputSource_TIM15_TRGO))

#define TIM17_INPUT_TI1 ((uint8_t)0x00)
#define TIM17_INPUT_ETR ((uint8_t)0x01)
#define IS_TIM17_INPUT_TI(TIx) ((TIx == TIM17_INPUT_TI1) || (TIx == TIM17_INPUT_ETR))

#define TIM17_IntputSource_IO ((uint32_t)0x00000000)
#define TIM17_IntputSource_AWD ((uint32_t)0x00000001)
#define TIM17_IntputSource_ACMP0_OUTPUT ((uint32_t)0x00000002)
#define TIM17_IntputSource_ACMP1_OUTPUT ((uint32_t)0x00000003)
#define TIM17_IntputSource_ACMP2_OUTPUT ((uint32_t)0x00000004)
#define TIM17_IntputSource_TIM1_TRGO ((uint32_t)0x00000005)
#define TIM17_IntputSource_TIM3_TRGO ((uint32_t)0x00000006)
#define TIM17_IntputSource_TIM15_TRGO ((uint32_t)0x00000007)
#define IS_TIM17_IntputSource(INx) ((INx == TIM17_IntputSource_IO) ||           \
                                    (INx == TIM17_IntputSource_AWD) ||          \
                                    (INx == TIM17_IntputSource_ACMP0_OUTPUT) || \
                                    (INx == TIM17_IntputSource_ACMP1_OUTPUT) || \
                                    (INx == TIM17_IntputSource_ACMP2_OUTPUT) || \
                                    (INx == TIM17_IntputSource_TIM1_TRGO) ||    \
                                    (INx == TIM17_IntputSource_TIM3_TRGO) ||    \
                                    (INx == TIM17_IntputSource_TIM15_TRGO))

/**
 * @}SYSCTRL_EDU_CFGx TIM1 break/break2/OCREF_CLR输入触发源配置
 */
// TIM1 break
#define TIM1_BreakSource_ACMP0_OUTPUT ((uint32_t)0x00000100)
#define TIM1_BreakSource_ACMP1_OUTPUT ((uint32_t)0x00000200)
#define TIM1_BreakSource_ACMP2_OUTPUT ((uint32_t)0x00000400)
#define TIM1_BreakSource_TIM3_TRGO ((uint32_t)0x00000800)
#define TIM1_BreakSource_TIM15_TRGO ((uint32_t)0x00001000)
#define TIM1_BreakSource_AWD ((uint32_t)0x00002000)
#define TIM1_BreakSource_IO ((uint32_t)0x00004000)
// TIM1 break2
#define TIM1_Break2Source_ACMP0_OUTPUT ((uint32_t)0x00010000)
#define TIM1_Break2Source_ACMP1_OUTPUT ((uint32_t)0x00020000)
#define TIM1_Break2Source_ACMP2_OUTPUT ((uint32_t)0x00040000)
#define TIM1_Break2Source_TIM17_OC1_TRIG ((uint32_t)0x00080000)
#define TIM1_Break2Source_TIM16_OC1_TRIG ((uint32_t)0x00100000)
#define TIM1_Break2Source_AWD ((uint32_t)0x00200000)
#define IS_TIM1_BreakSource(Source) ((Source == TIM1_BreakSource_ACMP0_OUTPUT) ||    \
                                     (Source == TIM1_BreakSource_ACMP1_OUTPUT) ||    \
                                     (Source == TIM1_BreakSource_ACMP2_OUTPUT) ||    \
                                     (Source == TIM1_BreakSource_TIM3_TRGO) ||       \
                                     (Source == TIM1_BreakSource_TIM15_TRGO) ||      \
                                     (Source == TIM1_BreakSource_AWD) ||             \
                                     (Source == TIM1_BreakSource_IO) ||              \
                                     (Source == TIM1_Break2Source_ACMP0_OUTPUT) ||   \
                                     (Source == TIM1_Break2Source_ACMP1_OUTPUT) ||   \
                                     (Source == TIM1_Break2Source_ACMP2_OUTPUT) ||   \
                                     (Source == TIM1_Break2Source_TIM17_OC1_TRIG) || \
                                     (Source == TIM1_Break2Source_TIM16_OC1_TRIG) || \
                                     (Source == TIM1_Break2Source_AWD))
// TIM1 OCREF_CLR
#define TIM1_OCREF_CLR_Source_ACMP0_OUTPUT ((uint32_t)0x01000000)
#define TIM1_OCREF_CLR_Source_ACMP1_OUTPUT ((uint32_t)0x02000000)
#define TIM1_OCREF_CLR_Source_ACMP2_OUTPUT ((uint32_t)0x04000000)
#define TIM1_OCREF_CLR_Source_TIM3_TRGO ((uint32_t)0x08000000)
#define TIM1_OCREF_CLR_Source_TIM15_TRGO ((uint32_t)0x10000000)
#define TIM1_OCREF_CLR_Source_AWD ((uint32_t)0x20000000)
#define IS_TIM1_OCREF_CLR_Source(Source) ((Source == TIM1_OCREF_CLR_Source_ACMP0_OUTPUT) || \
                                          (Source == TIM1_OCREF_CLR_Source_ACMP1_OUTPUT) || \
                                          (Source == TIM1_OCREF_CLR_Source_ACMP2_OUTPUT) || \
                                          (Source == TIM1_OCREF_CLR_Source_TIM3_TRGO) ||    \
                                          (Source == TIM1_OCREF_CLR_Source_TIM15_TRGO) ||   \
                                          (Source == TIM1_OCREF_CLR_Source_AWD))

// TIM3 OCREF_CLR
#define TIM3_OCREF_CLR_Source_ACMP0_OUTPUT ((uint32_t)0x00000100)
#define TIM3_OCREF_CLR_Source_ACMP1_OUTPUT ((uint32_t)0x00000200)
#define TIM3_OCREF_CLR_Source_ACMP2_OUTPUT ((uint32_t)0x00000400)
#define TIM3_OCREF_CLR_Source_TIM1_TRGO ((uint32_t)0x00000800)
#define TIM3_OCREF_CLR_Source_TIM15_TRGO ((uint32_t)0x00001000)
#define TIM3_OCREF_CLR_Source_AWD ((uint32_t)0x00002000)
#define IS_TIM3_OCREF_CLR_Source(Source) ((Source == TIM3_OCREF_CLR_Source_ACMP0_OUTPUT) || \
                                          (Source == TIM3_OCREF_CLR_Source_ACMP1_OUTPUT) || \
                                          (Source == TIM3_OCREF_CLR_Source_ACMP2_OUTPUT) || \
                                          (Source == TIM3_OCREF_CLR_Source_TIM1_TRGO) ||    \
                                          (Source == TIM3_OCREF_CLR_Source_TIM15_TRGO) ||   \
                                          (Source == TIM3_OCREF_CLR_Source_AWD))
// TIM15 break
#define TIM15_BreakSource_ACMP0_OUTPUT ((uint32_t)0x00000100)
#define TIM15_BreakSource_ACMP1_OUTPUT ((uint32_t)0x00000200)
#define TIM15_BreakSource_ACMP2_OUTPUT ((uint32_t)0x00000400)
#define TIM15_BreakSource_TIM3_TRGO ((uint32_t)0x00000800)
#define TIM15_BreakSource_TIM1_TRGO ((uint32_t)0x00001000)
#define TIM15_BreakSource_AWD ((uint32_t)0x00002000)
#define TIM15_BreakSource_IO ((uint32_t)0x00004000)
// TIM15 break2
#define TIM15_Break2Source_ACMP0_OUTPUT ((uint32_t)0x00010000)
#define TIM15_Break2Source_ACMP1_OUTPUT ((uint32_t)0x00020000)
#define TIM15_Break2Source_ACMP2_OUTPUT ((uint32_t)0x00040000)
#define TIM15_Break2Source_TIM17_OC1_TRIG ((uint32_t)0x00080000)
#define TIM15_Break2Source_TIM16_OC1_TRIG ((uint32_t)0x00100000)
#define TIM15_Break2Source_AWD ((uint32_t)0x00200000)
#define IS_TIM15_BreakSource(Source) ((Source == TIM15_BreakSource_ACMP0_OUTPUT) ||    \
                                      (Source == TIM15_BreakSource_ACMP1_OUTPUT) ||    \
                                      (Source == TIM15_BreakSource_ACMP2_OUTPUT) ||    \
                                      (Source == TIM15_BreakSource_TIM3_TRGO) ||       \
                                      (Source == TIM15_BreakSource_TIM1_TRGO) ||       \
                                      (Source == TIM15_BreakSource_AWD) ||             \
                                      (Source == TIM15_BreakSource_IO) ||              \
                                      (Source == TIM15_Break2Source_ACMP0_OUTPUT) ||   \
                                      (Source == TIM15_Break2Source_ACMP1_OUTPUT) ||   \
                                      (Source == TIM15_Break2Source_ACMP2_OUTPUT) ||   \
                                      (Source == TIM15_Break2Source_TIM17_OC1_TRIG) || \
                                      (Source == TIM15_Break2Source_TIM16_OC1_TRIG) || \
                                      (Source == TIM15_Break2Source_AWD))

// TIM16 break
#define TIM16_BreakSource_ACMP0_OUTPUT ((uint32_t)0x00000100)
#define TIM16_BreakSource_ACMP1_OUTPUT ((uint32_t)0x00000200)
#define TIM16_BreakSource_ACMP2_OUTPUT ((uint32_t)0x00000400)
#define TIM16_BreakSource_TIM3_TRGO ((uint32_t)0x00000800)
#define TIM16_BreakSource_TIM1_TRGO ((uint32_t)0x00001000)
#define TIM16_BreakSource_AWD ((uint32_t)0x00002000)
#define TIM16_BreakSource_IO ((uint32_t)0x00004000)
// TIM16 break2
#define TIM16_Break2Source_ACMP0_OUTPUT ((uint32_t)0x00010000)
#define TIM16_Break2Source_ACMP1_OUTPUT ((uint32_t)0x00020000)
#define TIM16_Break2Source_ACMP2_OUTPUT ((uint32_t)0x00040000)
#define TIM16_Break2Source_TIM17_OC1_TRIG ((uint32_t)0x00080000)
#define TIM16_Break2Source_TIM15_TRGO ((uint32_t)0x00100000)
#define TIM16_Break2Source_AWD ((uint32_t)0x00200000)
#define IS_TIM16_BreakSource(Source) ((Source == TIM16_BreakSource_ACMP0_OUTPUT) ||    \
                                      (Source == TIM16_BreakSource_ACMP1_OUTPUT) ||    \
                                      (Source == TIM16_BreakSource_ACMP2_OUTPUT) ||    \
                                      (Source == TIM16_BreakSource_TIM3_TRGO) ||       \
                                      (Source == TIM16_BreakSource_TIM1_TRGO) ||       \
                                      (Source == TIM16_BreakSource_AWD) ||             \
                                      (Source == TIM16_BreakSource_IO) ||              \
                                      (Source == TIM16_Break2Source_ACMP0_OUTPUT) ||   \
                                      (Source == TIM16_Break2Source_ACMP1_OUTPUT) ||   \
                                      (Source == TIM16_Break2Source_ACMP2_OUTPUT) ||   \
                                      (Source == TIM16_Break2Source_TIM17_OC1_TRIG) || \
                                      (Source == TIM16_Break2Source_TIM15_TRGO) ||     \
                                      (Source == TIM16_Break2Source_AWD))

// TIM17 break
#define TIM17_BreakSource_ACMP0_OUTPUT ((uint32_t)0x01000000)
#define TIM17_BreakSource_ACMP1_OUTPUT ((uint32_t)0x02000000)
#define TIM17_BreakSource_ACMP2_OUTPUT ((uint32_t)0x04000000)
#define TIM17_BreakSource_TIM3_TRGO ((uint32_t)0x08000000)
#define TIM17_BreakSource_TIM1_TRGO ((uint32_t)0x10000000)
#define TIM17_BreakSource_AWD ((uint32_t)0x20000000)
#define TIM17_BreakSource_IO ((uint32_t)0x40000000)
#define IS_TIM17_BreakSource(Source) ((Source == TIM17_BreakSource_ACMP0_OUTPUT) || \
                                      (Source == TIM17_BreakSource_ACMP1_OUTPUT) || \
                                      (Source == TIM17_BreakSource_ACMP2_OUTPUT) || \
                                      (Source == TIM17_BreakSource_TIM3_TRGO) ||    \
                                      (Source == TIM17_BreakSource_TIM1_TRGO) ||    \
                                      (Source == TIM17_Break2Source_AWD))
#define TIM_InputLevel_High 0
#define TIM_InputLevel_Low 1
#define IS_TIM_InputLevel(Level) (Level == TIM_InputLevel_High) || (Level == TIM_InputLevel_Low)

/** @defgroup TIM_External_Trigger_Prescaler
 * @{
 */

#define TIM_ExtTRGPSC_OFF ((uint16_t)0x0000)
#define TIM_ExtTRGPSC_DIV2 ((uint16_t)0x1000)
#define TIM_ExtTRGPSC_DIV4 ((uint16_t)0x2000)
#define TIM_ExtTRGPSC_DIV8 ((uint16_t)0x3000)
#define IS_TIM_EXT_PRESCALER(PRESCALER) (((PRESCALER) == TIM_ExtTRGPSC_OFF) ||  \
                                         ((PRESCALER) == TIM_ExtTRGPSC_DIV2) || \
                                         ((PRESCALER) == TIM_ExtTRGPSC_DIV4) || \
                                         ((PRESCALER) == TIM_ExtTRGPSC_DIV8))
/**
 * @}
 */

/** @defgroup TIM_Internal_Trigger_Selection
 * @{
 */

//#define TIM_TS_ITR0                        ((uint16_t)0x0000)
//#define TIM_TS_ITR1                        ((uint16_t)0x0010)
//#define TIM_TS_ITR2                        ((uint16_t)0x0020)
//#define TIM_TS_ITR3                        ((uint16_t)0x0030)
#define TIM_TS_TI1F_ED ((uint16_t)0x0040)
#define TIM_TS_TI1FP1 ((uint16_t)0x0050)
#define TIM_TS_TI2FP2 ((uint16_t)0x0060)
#define TIM_TS_ETRF ((uint16_t)0x0070)
#define IS_TIM_TRIGGER_SELECTION(SELECTION) (((SELECTION) == TIM_TS_ITR0) ||    \
                                             ((SELECTION) == TIM_TS_ITR1) ||    \
                                             ((SELECTION) == TIM_TS_ITR2) ||    \
                                             ((SELECTION) == TIM_TS_ITR3) ||    \
                                             ((SELECTION) == TIM_TS_TI1F_ED) || \
                                             ((SELECTION) == TIM_TS_TI1FP1) ||  \
                                             ((SELECTION) == TIM_TS_TI2FP2) ||  \
                                             ((SELECTION) == TIM_TS_ETRF))
#define IS_TIM_INTERNAL_TRIGGER_SELECTION(SELECTION) (((SELECTION) == TIM_TS_ITR0) || \
                                                      ((SELECTION) == TIM_TS_ITR1) || \
                                                      ((SELECTION) == TIM_TS_ITR2) || \
                                                      ((SELECTION) == TIM_TS_ITR3))
/**
 * @}
 */

/** @defgroup TIM_TIx_External_Clock_Source
 * @{
 */

#define TIM_TIxExternalCLK1Source_TI1 ((uint16_t)0x0050)
#define TIM_TIxExternalCLK1Source_TI2 ((uint16_t)0x0060)
#define TIM_TIxExternalCLK1Source_TI1ED ((uint16_t)0x0040)

/**
 * @}
 */

/** @defgroup TIM_External_Trigger_Polarity
 * @{
 */
#define TIM_ExtTRGPolarity_Inverted ((uint16_t)0x8000)
#define TIM_ExtTRGPolarity_NonInverted ((uint16_t)0x0000)
#define IS_TIM_EXT_POLARITY(POLARITY) (((POLARITY) == TIM_ExtTRGPolarity_Inverted) || \
                                       ((POLARITY) == TIM_ExtTRGPolarity_NonInverted))
/**
 * @}
 */

/** @defgroup TIM_Prescaler_Reload_Mode
 * @{
 */

#define TIM_PSCReloadMode_Update ((uint16_t)0x0000)
#define TIM_PSCReloadMode_Immediate ((uint16_t)0x0001)
#define IS_TIM_PRESCALER_RELOAD(RELOAD) (((RELOAD) == TIM_PSCReloadMode_Update) || \
                                         ((RELOAD) == TIM_PSCReloadMode_Immediate))
/**
 * @}
 */

/** @defgroup TIM_Forced_Action
 * @{
 */

#define TIM_ForcedAction_Active ((uint16_t)0x0050)
#define TIM_ForcedAction_InActive ((uint16_t)0x0040)
#define IS_TIM_FORCED_ACTION(ACTION) (((ACTION) == TIM_ForcedAction_Active) || \
                                      ((ACTION) == TIM_ForcedAction_InActive))
/**
 * @}
 */

/** @defgroup TIM_Encoder_Mode
 * @{
 */

#define TIM_EncoderMode_TI1 ((uint16_t)0x0001)
#define TIM_EncoderMode_TI2 ((uint16_t)0x0002)
#define TIM_EncoderMode_TI12 ((uint16_t)0x0003)
#define IS_TIM_ENCODER_MODE(MODE) (((MODE) == TIM_EncoderMode_TI1) || \
                                   ((MODE) == TIM_EncoderMode_TI2) || \
                                   ((MODE) == TIM_EncoderMode_TI12))
/**
 * @}
 */

/** @defgroup TIM_Event_Source
 * @{
 */

#define TIM_EventSource_Update ((uint16_t)0x0001)
#define TIM_EventSource_CC1 ((uint16_t)0x0002)
#define TIM_EventSource_CC2 ((uint16_t)0x0004)
#define TIM_EventSource_CC3 ((uint16_t)0x0008)
#define TIM_EventSource_CC4 ((uint16_t)0x0010)
#define TIM_EventSource_COM ((uint16_t)0x0020)
#define TIM_EventSource_Trigger ((uint16_t)0x0040)
#define TIM_EventSource_Break ((uint16_t)0x0080)
#define IS_TIM_EVENT_SOURCE(SOURCE) ((((SOURCE) & (uint16_t)0xFF00) == 0x0000) && ((SOURCE) != 0x0000))

/**
 * @}
 */

/** @defgroup TIM_Update_Source
 * @{
 */

#define TIM_UpdateSource_Global ((uint16_t)0x0000)  /*!< Source of update is the counter overflow/underflow \
                                                         or the setting of UG bit, or an update generation  \
                                                         through the slave mode controller. */
#define TIM_UpdateSource_Regular ((uint16_t)0x0001) /*!< Source of update is counter overflow/underflow. */
#define IS_TIM_UPDATE_SOURCE(SOURCE) (((SOURCE) == TIM_UpdateSource_Global) || \
                                      ((SOURCE) == TIM_UpdateSource_Regular))
/**
 * @}
 */

/** @defgroup TIM_Output_Compare_Preload_State
 * @{
 */

#define TIM_OCPreload_Enable ((uint16_t)0x0008)
#define TIM_OCPreload_Disable ((uint16_t)0x0000)
#define IS_TIM_OCPRELOAD_STATE(STATE) (((STATE) == TIM_OCPreload_Enable) || \
                                       ((STATE) == TIM_OCPreload_Disable))
/**
 * @}
 */

/** @defgroup TIM_Output_Compare_Fast_State
 * @{
 */

#define TIM_OCFast_Enable ((uint16_t)0x0004)
#define TIM_OCFast_Disable ((uint16_t)0x0000)
#define IS_TIM_OCFAST_STATE(STATE) (((STATE) == TIM_OCFast_Enable) || \
                                    ((STATE) == TIM_OCFast_Disable))

/**
 * @}
 */

/** @defgroup TIM_Output_Compare_Clear_State
 * @{
 */

#define TIM_OCClear_Enable ((uint16_t)0x0080)
#define TIM_OCClear_Disable ((uint16_t)0x0000)
#define IS_TIM_OCCLEAR_STATE(STATE) (((STATE) == TIM_OCClear_Enable) || \
                                     ((STATE) == TIM_OCClear_Disable))
/**
 * @}
 */

/** @defgroup TIM_Trigger_Output_Source
 * @{
 */

#define TIM_TRGOSource_Reset ((uint16_t)0x0000)
#define TIM_TRGOSource_Enable ((uint16_t)0x0010)
#define TIM_TRGOSource_Update ((uint16_t)0x0020)
#define TIM_TRGOSource_OC1 ((uint16_t)0x0030)
#define TIM_TRGOSource_OC1Ref ((uint16_t)0x0040)
#define TIM_TRGOSource_OC2Ref ((uint16_t)0x0050)
#define TIM_TRGOSource_OC3Ref ((uint16_t)0x0060)
#define TIM_TRGOSource_OC4Ref ((uint16_t)0x0070)
#define IS_TIM_TRGO_SOURCE(SOURCE) (((SOURCE) == TIM_TRGOSource_Reset) ||  \
                                    ((SOURCE) == TIM_TRGOSource_Enable) || \
                                    ((SOURCE) == TIM_TRGOSource_Update) || \
                                    ((SOURCE) == TIM_TRGOSource_OC1) ||    \
                                    ((SOURCE) == TIM_TRGOSource_OC1Ref) || \
                                    ((SOURCE) == TIM_TRGOSource_OC2Ref) || \
                                    ((SOURCE) == TIM_TRGOSource_OC3Ref) || \
                                    ((SOURCE) == TIM_TRGOSource_OC4Ref))
/**
 * @}
 */

/** @defgroup TIM_Slave_Mode
 * @{
 */

#define TIM_SlaveMode_Reset ((uint16_t)0x0004)
#define TIM_SlaveMode_Gated ((uint16_t)0x0005)
#define TIM_SlaveMode_Trigger ((uint16_t)0x0006)
#define TIM_SlaveMode_External1 ((uint16_t)0x0007)
#define IS_TIM_SLAVE_MODE(MODE) (((MODE) == TIM_SlaveMode_Reset) ||   \
                                 ((MODE) == TIM_SlaveMode_Gated) ||   \
                                 ((MODE) == TIM_SlaveMode_Trigger) || \
                                 ((MODE) == TIM_SlaveMode_External1))
/**
 * @}
 */

/** @defgroup TIM_Master_Slave_Mode
 * @{
 */

#define TIM_MasterSlaveMode_Enable ((uint16_t)0x0080)
#define TIM_MasterSlaveMode_Disable ((uint16_t)0x0000)
#define IS_TIM_MSM_STATE(STATE) (((STATE) == TIM_MasterSlaveMode_Enable) || \
                                 ((STATE) == TIM_MasterSlaveMode_Disable))
/**
 * @}
 */

/** @defgroup TIM_Flags
 * @{
 */

#define TIM_FLAG_Update ((uint16_t)0x0001)
#define TIM_FLAG_CC1 ((uint16_t)0x0002)
#define TIM_FLAG_CC2 ((uint16_t)0x0004)
#define TIM_FLAG_CC3 ((uint16_t)0x0008)
#define TIM_FLAG_CC4 ((uint16_t)0x0010)
#define TIM_FLAG_COM ((uint16_t)0x0020)
#define TIM_FLAG_Trigger ((uint16_t)0x0040)
#define TIM_FLAG_Break ((uint16_t)0x0080)
#define TIM_FLAG_Break2 ((uint16_t)0x0100)
#define TIM_FLAG_CC1OF ((uint16_t)0x0200)
#define TIM_FLAG_CC2OF ((uint16_t)0x0400)
#define TIM_FLAG_CC3OF ((uint16_t)0x0800)
#define TIM_FLAG_CC4OF ((uint16_t)0x1000)
#define IS_TIM_GET_FLAG(FLAG) (((FLAG) == TIM_FLAG_Update) ||  \
                               ((FLAG) == TIM_FLAG_CC1) ||     \
                               ((FLAG) == TIM_FLAG_CC2) ||     \
                               ((FLAG) == TIM_FLAG_CC3) ||     \
                               ((FLAG) == TIM_FLAG_CC4) ||     \
                               ((FLAG) == TIM_FLAG_COM) ||     \
                               ((FLAG) == TIM_FLAG_Trigger) || \
                               ((FLAG) == TIM_FLAG_Break) ||   \
                               ((FLAG) == TIM_FLAG_Break2) ||   \
                               ((FLAG) == TIM_FLAG_CC1OF) ||   \
                               ((FLAG) == TIM_FLAG_CC2OF) ||   \
                               ((FLAG) == TIM_FLAG_CC3OF) ||   \
                               ((FLAG) == TIM_FLAG_CC4OF))

#define IS_TIM_CLEAR_FLAG(TIM_FLAG) ((((TIM_FLAG) & (uint16_t)0xE100) == 0x0000) && ((TIM_FLAG) != 0x0000))
/**
 * @}
 */

/** @defgroup TIM_Input_Capture_Filer_Value
 * @{
 */

#define IS_TIM_IC_FILTER(ICFILTER) ((ICFILTER) <= 0xF)
/**
 * @}
 */

/** @defgroup TIM_External_Trigger_Filter
 * @{
 */

#define IS_TIM_EXT_FILTER(EXTFILTER) ((EXTFILTER) <= 0xF)
/**
 * @}
 */

/** @defgroup TIM_OCReferenceClear
 * @{
 */
#define TIM_OCReferenceClear_ETRF ((uint16_t)0x0008)
#define TIM_OCReferenceClear_OCREFCLR ((uint16_t)0x0000)
#define TIM_OCREFERENCECECLEAR_SOURCE(SOURCE) (((SOURCE) == TIM_OCReferenceClear_ETRF) || \
                                               ((SOURCE) == TIM_OCReferenceClear_OCREFCLR))

/**
 * @}
 */
/** @defgroup TIM_Remap
 * @{
 */
#define TIM14_GPIO ((uint16_t)0x0000)
#define TIM14_WT ((uint16_t)0x0001)
#define TIM14_HSEDiv32 ((uint16_t)0x0002)
#define TIM14_MCO ((uint16_t)0x0003)

#define IS_TIM_REMAP(TIM_REMAP) (((TIM_REMAP) == TIM14_GPIO) ||     \
                                 ((TIM_REMAP) == TIM14_WT_CLK) ||   \
                                 ((TIM_REMAP) == TIM14_HSEDiv32) || \
                                 ((TIM_REMAP) == TIM14_MCO))
/**
 * @}
 */

/** @defgroup TIM_Legacy
 * @{
 */

#define TIM_DMABurstLength_1Byte TIM_DMABurstLength_1Transfer
#define TIM_DMABurstLength_2Bytes TIM_DMABurstLength_2Transfers
#define TIM_DMABurstLength_3Bytes TIM_DMABurstLength_3Transfers
#define TIM_DMABurstLength_4Bytes TIM_DMABurstLength_4Transfers
#define TIM_DMABurstLength_5Bytes TIM_DMABurstLength_5Transfers
#define TIM_DMABurstLength_6Bytes TIM_DMABurstLength_6Transfers
#define TIM_DMABurstLength_7Bytes TIM_DMABurstLength_7Transfers
#define TIM_DMABurstLength_8Bytes TIM_DMABurstLength_8Transfers
#define TIM_DMABurstLength_9Bytes TIM_DMABurstLength_9Transfers
#define TIM_DMABurstLength_10Bytes TIM_DMABurstLength_10Transfers
#define TIM_DMABurstLength_11Bytes TIM_DMABurstLength_11Transfers
#define TIM_DMABurstLength_12Bytes TIM_DMABurstLength_12Transfers
#define TIM_DMABurstLength_13Bytes TIM_DMABurstLength_13Transfers
#define TIM_DMABurstLength_14Bytes TIM_DMABurstLength_14Transfers
#define TIM_DMABurstLength_15Bytes TIM_DMABurstLength_15Transfers
#define TIM_DMABurstLength_16Bytes TIM_DMABurstLength_16Transfers
#define TIM_DMABurstLength_17Bytes TIM_DMABurstLength_17Transfers
#define TIM_DMABurstLength_18Bytes TIM_DMABurstLength_18Transfers
/* TimeBase management ********************************************************/

/* =========================================================================================================================== */
/* ================                                           TIM1                                            ================ */
/* =========================================================================================================================== */

/* ==========================================================  CR1  ========================================================== */
#define TIM1_CR1_AS_Pos (24UL)          /*!< AS (Bit 24)                                           */
#define TIM1_CR1_AS_Msk (0x1000000UL)   /*!< AS (Bitfield-Mask: 0x01)                              */
#define TIM1_CR1_OCF_Pos (23UL)         /*!< OCF (Bit 23)                                          */
#define TIM1_CR1_OCF_Msk (0x800000UL)   /*!< OCF (Bitfield-Mask: 0x01)                             */
#define TIM1_CR1_CENCE_Pos (22UL)       /*!< CENCE (Bit 22)                                        */
#define TIM1_CR1_CENCE_Msk (0x400000UL) /*!< CENCE (Bitfield-Mask: 0x01)                           */
#define TIM1_CR1_TI4E_Pos (21UL)        /*!< TI4E (Bit 21)                                         */
#define TIM1_CR1_TI4E_Msk (0x200000UL)  /*!< TI4E (Bitfield-Mask: 0x01)                            */
#define TIM1_CR1_TI3E_Pos (20UL)        /*!< TI3E (Bit 20)                                         */
#define TIM1_CR1_TI3E_Msk (0x100000UL)  /*!< TI3E (Bitfield-Mask: 0x01)                            */
#define TIM1_CR1_TI2E_Pos (19UL)        /*!< TI2E (Bit 19)                                         */
#define TIM1_CR1_TI2E_Msk (0x80000UL)   /*!< TI2E (Bitfield-Mask: 0x01)                            */
#define TIM1_CR1_TI1E_Pos (18UL)        /*!< TI1E (Bit 18)                                         */
#define TIM1_CR1_TI1E_Msk (0x40000UL)   /*!< TI1E (Bitfield-Mask: 0x01)                            */
#define TIM1_CR1_ETRE_Pos (17UL)        /*!< ETRE (Bit 17)                                         */
#define TIM1_CR1_ETRE_Msk (0x20000UL)   /*!< ETRE (Bitfield-Mask: 0x01)                            */
#define TIM1_CR1_DTSE_Pos (16UL)        /*!< DTSE (Bit 16)                                         */
#define TIM1_CR1_DTSE_Msk (0x10000UL)   /*!< DTSE (Bitfield-Mask: 0x01)                            */
#define TIM1_CR1_CKD_Pos (8UL)          /*!< CKD (Bit 8)                                           */
#define TIM1_CR1_CKD_Msk (0x300UL)      /*!< CKD (Bitfield-Mask: 0x03)                             */
#define TIM1_CR1_ARPE_Pos (7UL)         /*!< ARPE (Bit 7)                                          */
#define TIM1_CR1_ARPE_Msk (0x80UL)      /*!< ARPE (Bitfield-Mask: 0x01)                            */
#define TIM1_CR1_CMS_Pos (5UL)          /*!< CMS (Bit 5)                                           */
#define TIM1_CR1_CMS_Msk (0x60UL)       /*!< CMS (Bitfield-Mask: 0x03)                             */
#define TIM1_CR1_DIR_Pos (4UL)          /*!< DIR (Bit 4)                                           */
#define TIM1_CR1_DIR_Msk (0x10UL)       /*!< DIR (Bitfield-Mask: 0x01)                             */
#define TIM1_CR1_OPM_Pos (3UL)          /*!< OPM (Bit 3)                                           */
#define TIM1_CR1_OPM_Msk (0x8UL)        /*!< OPM (Bitfield-Mask: 0x01)                             */
#define TIM1_CR1_URS_Pos (2UL)          /*!< URS (Bit 2)                                           */
#define TIM1_CR1_URS_Msk (0x4UL)        /*!< URS (Bitfield-Mask: 0x01)                             */
#define TIM1_CR1_UDIS_Pos (1UL)         /*!< UDIS (Bit 1)                                          */
#define TIM1_CR1_UDIS_Msk (0x2UL)       /*!< UDIS (Bitfield-Mask: 0x01)                            */
#define TIM1_CR1_CEN_Pos (0UL)          /*!< CEN (Bit 0)                                           */
#define TIM1_CR1_CEN_Msk (0x1UL)        /*!< CEN (Bitfield-Mask: 0x01)                             */
/* ==========================================================  CR2  ========================================================== */
#define TIM1_CR2_OIS4_Pos (14UL)      /*!< OIS4 (Bit 14)                                         */
#define TIM1_CR2_OIS4_Msk (0x4000UL)  /*!< OIS4 (Bitfield-Mask: 0x01)                            */
#define TIM1_CR2_OIS3N_Pos (13UL)     /*!< OIS3N (Bit 13)                                        */
#define TIM1_CR2_OIS3N_Msk (0x2000UL) /*!< OIS3N (Bitfield-Mask: 0x01)                           */
#define TIM1_CR2_OIS3_Pos (12UL)      /*!< OIS3 (Bit 12)                                         */
#define TIM1_CR2_OIS3_Msk (0x1000UL)  /*!< OIS3 (Bitfield-Mask: 0x01)                            */
#define TIM1_CR2_OIS2N_Pos (11UL)     /*!< OIS2N (Bit 11)                                        */
#define TIM1_CR2_OIS2N_Msk (0x800UL)  /*!< OIS2N (Bitfield-Mask: 0x01)                           */
#define TIM1_CR2_OIS2_Pos (10UL)      /*!< OIS2 (Bit 10)                                         */
#define TIM1_CR2_OIS2_Msk (0x400UL)   /*!< OIS2 (Bitfield-Mask: 0x01)                            */
#define TIM1_CR2_OIS1N_Pos (9UL)      /*!< OIS1N (Bit 9)                                         */
#define TIM1_CR2_OIS1N_Msk (0x200UL)  /*!< OIS1N (Bitfield-Mask: 0x01)                           */
#define TIM1_CR2_OIS1_Pos (8UL)       /*!< OIS1 (Bit 8)                                          */
#define TIM1_CR2_OIS1_Msk (0x100UL)   /*!< OIS1 (Bitfield-Mask: 0x01)                            */
#define TIM1_CR2_TI1S_Pos (7UL)       /*!< TI1S (Bit 7)                                          */
#define TIM1_CR2_TI1S_Msk (0x80UL)    /*!< TI1S (Bitfield-Mask: 0x01)                            */
#define TIM1_CR2_MMS_Pos (4UL)        /*!< MMS (Bit 4)                                           */
#define TIM1_CR2_MMS_Msk (0x70UL)     /*!< MMS (Bitfield-Mask: 0x07)                             */
#define TIM1_CR2_CCDS_Pos (3UL)       /*!< CCDS (Bit 3)                                          */
#define TIM1_CR2_CCDS_Msk (0x8UL)     /*!< CCDS (Bitfield-Mask: 0x01)                            */
#define TIM1_CR2_CCUS_Pos (2UL)       /*!< CCUS (Bit 2)                                          */
#define TIM1_CR2_CCUS_Msk (0x4UL)     /*!< CCUS (Bitfield-Mask: 0x01)                            */
#define TIM1_CR2_CCPC_Pos (0UL)       /*!< CCPC (Bit 0)                                          */
#define TIM1_CR2_CCPC_Msk (0x1UL)     /*!< CCPC (Bitfield-Mask: 0x01)                            */
/* =========================================================  SMCR  ========================================================== */
#define TIM1_SMCR_OCCP_Pos (17UL)      /*!< OCCP (Bit 17)                                         */
#define TIM1_SMCR_OCCP_Msk (0x20000UL) /*!< OCCP (Bitfield-Mask: 0x01)                            */
#define TIM1_SMCR_SMS3_Pos (16UL)      /*!< SMS3 (Bit 16)                                         */
#define TIM1_SMCR_SMS3_Msk (0x10000UL) /*!< SMS3 (Bitfield-Mask: 0x01)                            */
#define TIM1_SMCR_ETP_Pos (15UL)       /*!< ETP (Bit 15)                                          */
#define TIM1_SMCR_ETP_Msk (0x8000UL)   /*!< ETP (Bitfield-Mask: 0x01)                             */
#define TIM1_SMCR_ECE_Pos (14UL)       /*!< ECE (Bit 14)                                          */
#define TIM1_SMCR_ECE_Msk (0x4000UL)   /*!< ECE (Bitfield-Mask: 0x01)                             */
#define TIM1_SMCR_ETPS_Pos (12UL)      /*!< ETPS (Bit 12)                                         */
#define TIM1_SMCR_ETPS_Msk (0x3000UL)  /*!< ETPS (Bitfield-Mask: 0x03)                            */
#define TIM1_SMCR_ETF_Pos (8UL)        /*!< ETF (Bit 8)                                           */
#define TIM1_SMCR_ETF_Msk (0xf00UL)    /*!< ETF (Bitfield-Mask: 0x0f)                             */
#define TIM1_SMCR_MSM_Pos (7UL)        /*!< MSM (Bit 7)                                           */
#define TIM1_SMCR_MSM_Msk (0x80UL)     /*!< MSM (Bitfield-Mask: 0x01)                             */
#define TIM1_SMCR_TS_Pos (4UL)         /*!< TS (Bit 4)                                            */
#define TIM1_SMCR_TS_Msk (0x70UL)      /*!< TS (Bitfield-Mask: 0x07)                              */
#define TIM1_SMCR_SMS_Pos (0UL)        /*!< SMS (Bit 0)                                           */
#define TIM1_SMCR_SMS_Msk (0x7UL)      /*!< SMS (Bitfield-Mask: 0x07)                             */
/* =========================================================  DIER  ========================================================== */
#define TIM1_DIER_TDE_Pos (14UL)       /*!< TDE (Bit 14)                                          */
#define TIM1_DIER_TDE_Msk (0x4000UL)   /*!< TDE (Bitfield-Mask: 0x01)                             */
#define TIM1_DIER_COMDE_Pos (13UL)     /*!< COMDE (Bit 13)                                        */
#define TIM1_DIER_COMDE_Msk (0x2000UL) /*!< COMDE (Bitfield-Mask: 0x01)                           */
#define TIM1_DIER_CC4DE_Pos (12UL)     /*!< CC4DE (Bit 12)                                        */
#define TIM1_DIER_CC4DE_Msk (0x1000UL) /*!< CC4DE (Bitfield-Mask: 0x01)                           */
#define TIM1_DIER_CC3DE_Pos (11UL)     /*!< CC3DE (Bit 11)                                        */
#define TIM1_DIER_CC3DE_Msk (0x800UL)  /*!< CC3DE (Bitfield-Mask: 0x01)                           */
#define TIM1_DIER_CC2DE_Pos (10UL)     /*!< CC2DE (Bit 10)                                        */
#define TIM1_DIER_CC2DE_Msk (0x400UL)  /*!< CC2DE (Bitfield-Mask: 0x01)                           */
#define TIM1_DIER_CC1DE_Pos (9UL)      /*!< CC1DE (Bit 9)                                         */
#define TIM1_DIER_CC1DE_Msk (0x200UL)  /*!< CC1DE (Bitfield-Mask: 0x01)                           */
#define TIM1_DIER_UDE_Pos (8UL)        /*!< UDE (Bit 8)                                           */
#define TIM1_DIER_UDE_Msk (0x100UL)    /*!< UDE (Bitfield-Mask: 0x01)                             */
#define TIM1_DIER_TIE_Pos (6UL)        /*!< TIE (Bit 6)                                           */
#define TIM1_DIER_TIE_Msk (0x40UL)     /*!< TIE (Bitfield-Mask: 0x01)                             */
#define TIM1_DIER_CC4IE_Pos (4UL)      /*!< CC4IE (Bit 4)                                         */
#define TIM1_DIER_CC4IE_Msk (0x10UL)   /*!< CC4IE (Bitfield-Mask: 0x01)                           */
#define TIM1_DIER_CC3IE_Pos (3UL)      /*!< CC3IE (Bit 3)                                         */
#define TIM1_DIER_CC3IE_Msk (0x8UL)    /*!< CC3IE (Bitfield-Mask: 0x01)                           */
#define TIM1_DIER_CC2IE_Pos (2UL)      /*!< CC2IE (Bit 2)                                         */
#define TIM1_DIER_CC2IE_Msk (0x4UL)    /*!< CC2IE (Bitfield-Mask: 0x01)                           */
#define TIM1_DIER_CC1IE_Pos (1UL)      /*!< CC1IE (Bit 1)                                         */
#define TIM1_DIER_CC1IE_Msk (0x2UL)    /*!< CC1IE (Bitfield-Mask: 0x01)                           */
#define TIM1_DIER_UIE_Pos (0UL)        /*!< UIE (Bit 0)                                           */
#define TIM1_DIER_UIE_Msk (0x1UL)      /*!< UIE (Bitfield-Mask: 0x01)                             */
#define TIM1_DIER_BIE_Pos (7UL)        /*!< BIE (Bit 7)                                           */
#define TIM1_DIER_BIE_Msk (0x80UL)     /*!< BIE (Bitfield-Mask: 0x01)                             */
#define TIM1_DIER_COMIE_Pos (5UL)      /*!< COMIE (Bit 5)                                         */
#define TIM1_DIER_COMIE_Msk (0x20UL)   /*!< COMIE (Bitfield-Mask: 0x01)                           */
/* ==========================================================  SR  =========================================================== */
#define TIM1_SR_CC4OF_Pos (12UL)     /*!< CC4OF (Bit 12)                                        */
#define TIM1_SR_CC4OF_Msk (0x1000UL) /*!< CC4OF (Bitfield-Mask: 0x01)                           */
#define TIM1_SR_CC3OF_Pos (11UL)     /*!< CC3OF (Bit 11)                                        */
#define TIM1_SR_CC3OF_Msk (0x800UL)  /*!< CC3OF (Bitfield-Mask: 0x01)                           */
#define TIM1_SR_CC2OF_Pos (10UL)     /*!< CC2OF (Bit 10)                                        */
#define TIM1_SR_CC2OF_Msk (0x400UL)  /*!< CC2OF (Bitfield-Mask: 0x01)                           */
#define TIM1_SR_CC1OF_Pos (9UL)      /*!< CC1OF (Bit 9)                                         */
#define TIM1_SR_CC1OF_Msk (0x200UL)  /*!< CC1OF (Bitfield-Mask: 0x01)                           */
#define TIM1_SR_BIF_Pos (7UL)        /*!< BIF (Bit 7)                                           */
#define TIM1_SR_BIF_Msk (0x80UL)     /*!< BIF (Bitfield-Mask: 0x01)                             */
#define TIM1_SR_TIF_Pos (6UL)        /*!< TIF (Bit 6)                                           */
#define TIM1_SR_TIF_Msk (0x40UL)     /*!< TIF (Bitfield-Mask: 0x01)                             */
#define TIM1_SR_COMIF_Pos (5UL)      /*!< COMIF (Bit 5)                                         */
#define TIM1_SR_COMIF_Msk (0x20UL)   /*!< COMIF (Bitfield-Mask: 0x01)                           */
#define TIM1_SR_CC4IF_Pos (4UL)      /*!< CC4IF (Bit 4)                                         */
#define TIM1_SR_CC4IF_Msk (0x10UL)   /*!< CC4IF (Bitfield-Mask: 0x01)                           */
#define TIM1_SR_CC3IF_Pos (3UL)      /*!< CC3IF (Bit 3)                                         */
#define TIM1_SR_CC3IF_Msk (0x8UL)    /*!< CC3IF (Bitfield-Mask: 0x01)                           */
#define TIM1_SR_CC2IF_Pos (2UL)      /*!< CC2IF (Bit 2)                                         */
#define TIM1_SR_CC2IF_Msk (0x4UL)    /*!< CC2IF (Bitfield-Mask: 0x01)                           */
#define TIM1_SR_CC1IF_Pos (1UL)      /*!< CC1IF (Bit 1)                                         */
#define TIM1_SR_CC1IF_Msk (0x2UL)    /*!< CC1IF (Bitfield-Mask: 0x01)                           */
#define TIM1_SR_UIF_Pos (0UL)        /*!< UIF (Bit 0)                                           */
#define TIM1_SR_UIF_Msk (0x1UL)      /*!< UIF (Bitfield-Mask: 0x01)                             */
/* ==========================================================  EGR  ========================================================== */
#define TIM1_EGR_B2G_Pos (8UL)     /*!< B2G (Bit 8)                                           */
#define TIM1_EGR_B2G_Msk (0x100UL) /*!< B2G (Bitfield-Mask: 0x01)                             */
#define TIM1_EGR_BG_Pos (7UL)      /*!< BG (Bit 7)                                            */
#define TIM1_EGR_BG_Msk (0x80UL)   /*!< BG (Bitfield-Mask: 0x01)                              */
#define TIM1_EGR_TG_Pos (6UL)      /*!< TG (Bit 6)                                            */
#define TIM1_EGR_TG_Msk (0x40UL)   /*!< TG (Bitfield-Mask: 0x01)                              */
#define TIM1_EGR_COMG_Pos (5UL)    /*!< COMG (Bit 5)                                          */
#define TIM1_EGR_COMG_Msk (0x20UL) /*!< COMG (Bitfield-Mask: 0x01)                            */
#define TIM1_EGR_CC4G_Pos (4UL)    /*!< CC4G (Bit 4)                                          */
#define TIM1_EGR_CC4G_Msk (0x10UL) /*!< CC4G (Bitfield-Mask: 0x01)                            */
#define TIM1_EGR_CC3G_Pos (3UL)    /*!< CC3G (Bit 3)                                          */
#define TIM1_EGR_CC3G_Msk (0x8UL)  /*!< CC3G (Bitfield-Mask: 0x01)                            */
#define TIM1_EGR_CC2G_Pos (2UL)    /*!< CC2G (Bit 2)                                          */
#define TIM1_EGR_CC2G_Msk (0x4UL)  /*!< CC2G (Bitfield-Mask: 0x01)                            */
#define TIM1_EGR_CC1G_Pos (1UL)    /*!< CC1G (Bit 1)                                          */
#define TIM1_EGR_CC1G_Msk (0x2UL)  /*!< CC1G (Bitfield-Mask: 0x01)                            */
#define TIM1_EGR_UG_Pos (0UL)      /*!< UG (Bit 0)                                            */
#define TIM1_EGR_UG_Msk (0x1UL)    /*!< UG (Bitfield-Mask: 0x01)                              */
/* =====================================================  CCMR1_Output  ====================================================== */
#define TIM1_CCMR1_Output_OC2TE_Pos (31UL)          /*!< OC2TE (Bit 31)                                        */
#define TIM1_CCMR1_Output_OC2TE_Msk (0x80000000UL)  /*!< OC2TE (Bitfield-Mask: 0x01)                           */
#define TIM1_CCMR1_Output_OC2TUE_Pos (30UL)         /*!< OC2TUE (Bit 30)                                        */
#define TIM1_CCMR1_Output_OC2TUE_Msk (0x40000000UL) /*!< OC2TUE (Bitfield-Mask: 0x01)                           */
#define TIM1_CCMR1_Output_OC1TE_Pos (23UL)          /*!< OC1TE (Bit 23)                                        */
#define TIM1_CCMR1_Output_OC1TE_Msk (0x800000UL)    /*!< OC1TE (Bitfield-Mask: 0x01)                           */
#define TIM1_CCMR1_Output_OC1TUE_Pos (22UL)         /*!< OC1TUE (Bit 22)                                        */
#define TIM1_CCMR1_Output_OC1TUE_Msk (0x400000UL)   /*!< OC1TUE (Bitfield-Mask: 0x01)                           */

#define TIM1_CCMR1_Output_OC2CE_Pos (15UL)     /*!< OC2CE (Bit 15)                                        */
#define TIM1_CCMR1_Output_OC2CE_Msk (0x8000UL) /*!< OC2CE (Bitfield-Mask: 0x01)                           */
#define TIM1_CCMR1_Output_OC2M_Pos (12UL)      /*!< OC2M (Bit 12)                                         */
#define TIM1_CCMR1_Output_OC2M_Msk (0x7000UL)  /*!< OC2M (Bitfield-Mask: 0x07)                            */
#define TIM1_CCMR1_Output_OC2PE_Pos (11UL)     /*!< OC2PE (Bit 11)                                        */
#define TIM1_CCMR1_Output_OC2PE_Msk (0x800UL)  /*!< OC2PE (Bitfield-Mask: 0x01)                           */
#define TIM1_CCMR1_Output_OC2FE_Pos (10UL)     /*!< OC2FE (Bit 10)                                        */
#define TIM1_CCMR1_Output_OC2FE_Msk (0x400UL)  /*!< OC2FE (Bitfield-Mask: 0x01)                           */
#define TIM1_CCMR1_Output_CC2S_Pos (8UL)       /*!< CC2S (Bit 8)                                          */
#define TIM1_CCMR1_Output_CC2S_Msk (0x300UL)   /*!< CC2S (Bitfield-Mask: 0x03)                            */
#define TIM1_CCMR1_Output_OC1CE_Pos (7UL)      /*!< OC1CE (Bit 7)                                         */
#define TIM1_CCMR1_Output_OC1CE_Msk (0x80UL)   /*!< OC1CE (Bitfield-Mask: 0x01)                           */
#define TIM1_CCMR1_Output_OC1M_Pos (4UL)       /*!< OC1M (Bit 4)                                          */
#define TIM1_CCMR1_Output_OC1M_Msk (0x70UL)    /*!< OC1M (Bitfield-Mask: 0x07)                            */
#define TIM1_CCMR1_Output_OC1PE_Pos (3UL)      /*!< OC1PE (Bit 3)                                         */
#define TIM1_CCMR1_Output_OC1PE_Msk (0x8UL)    /*!< OC1PE (Bitfield-Mask: 0x01)                           */
#define TIM1_CCMR1_Output_OC1FE_Pos (2UL)      /*!< OC1FE (Bit 2)                                         */
#define TIM1_CCMR1_Output_OC1FE_Msk (0x4UL)    /*!< OC1FE (Bitfield-Mask: 0x01)                           */
#define TIM1_CCMR1_Output_CC1S_Pos (0UL)       /*!< CC1S (Bit 0)                                          */
#define TIM1_CCMR1_Output_CC1S_Msk (0x3UL)     /*!< CC1S (Bitfield-Mask: 0x03)                            */
/* ======================================================  CCMR1_Input  ====================================================== */
#define TIM1_CCMR1_Input_IC2F_Pos (12UL)      /*!< IC2F (Bit 12)                                         */
#define TIM1_CCMR1_Input_IC2F_Msk (0xf000UL)  /*!< IC2F (Bitfield-Mask: 0x0f)                            */
#define TIM1_CCMR1_Input_IC2PCS_Pos (10UL)    /*!< IC2PCS (Bit 10)                                       */
#define TIM1_CCMR1_Input_IC2PCS_Msk (0xc00UL) /*!< IC2PCS (Bitfield-Mask: 0x03)                          */
#define TIM1_CCMR1_Input_CC2S_Pos (8UL)       /*!< CC2S (Bit 8)                                          */
#define TIM1_CCMR1_Input_CC2S_Msk (0x300UL)   /*!< CC2S (Bitfield-Mask: 0x03)                            */
#define TIM1_CCMR1_Input_IC1F_Pos (4UL)       /*!< IC1F (Bit 4)                                          */
#define TIM1_CCMR1_Input_IC1F_Msk (0xf0UL)    /*!< IC1F (Bitfield-Mask: 0x0f)                            */
#define TIM1_CCMR1_Input_ICPCS_Pos (2UL)      /*!< IC1PSC (Bit 2)                                         */
#define TIM1_CCMR1_Input_ICPCS_Msk (0xcUL)    /*!< IC1PSC (Bitfield-Mask: 0x03)                           */
#define TIM1_CCMR1_Input_CC1S_Pos (0UL)       /*!< CC1S (Bit 0)                                          */
#define TIM1_CCMR1_Input_CC1S_Msk (0x3UL)     /*!< CC1S (Bitfield-Mask: 0x03)                            */
/* =====================================================  CCMR2_Output  ====================================================== */
#define TIM1_CCMR2_Output_OC4CE_Pos (15UL)     /*!< OC4CE (Bit 15)                                        */
#define TIM1_CCMR2_Output_OC4CE_Msk (0x8000UL) /*!< OC4CE (Bitfield-Mask: 0x01)                           */
#define TIM1_CCMR2_Output_OC4M_Pos (12UL)      /*!< OC4M (Bit 12)                                         */
#define TIM1_CCMR2_Output_OC4M_Msk (0x7000UL)  /*!< OC4M (Bitfield-Mask: 0x07)                            */
#define TIM1_CCMR2_Output_OC4PE_Pos (11UL)     /*!< OC4PE (Bit 11)                                        */
#define TIM1_CCMR2_Output_OC4PE_Msk (0x800UL)  /*!< OC4PE (Bitfield-Mask: 0x01)                           */
#define TIM1_CCMR2_Output_OC4FE_Pos (10UL)     /*!< OC4FE (Bit 10)                                        */
#define TIM1_CCMR2_Output_OC4FE_Msk (0x400UL)  /*!< OC4FE (Bitfield-Mask: 0x01)                           */
#define TIM1_CCMR2_Output_CC4S_Pos (8UL)       /*!< CC4S (Bit 8)                                          */
#define TIM1_CCMR2_Output_CC4S_Msk (0x300UL)   /*!< CC4S (Bitfield-Mask: 0x03)                            */
#define TIM1_CCMR2_Output_OC3CE_Pos (7UL)      /*!< OC3CE (Bit 7)                                         */
#define TIM1_CCMR2_Output_OC3CE_Msk (0x80UL)   /*!< OC3CE (Bitfield-Mask: 0x01)                           */
#define TIM1_CCMR2_Output_OC3M_Pos (4UL)       /*!< OC3M (Bit 4)                                          */
#define TIM1_CCMR2_Output_OC3M_Msk (0x70UL)    /*!< OC3M (Bitfield-Mask: 0x07)                            */
#define TIM1_CCMR2_Output_OC3PE_Pos (3UL)      /*!< OC3PE (Bit 3)                                         */
#define TIM1_CCMR2_Output_OC3PE_Msk (0x8UL)    /*!< OC3PE (Bitfield-Mask: 0x01)                           */
#define TIM1_CCMR2_Output_OC3FE_Pos (2UL)      /*!< OC3FE (Bit 2)                                         */
#define TIM1_CCMR2_Output_OC3FE_Msk (0x4UL)    /*!< OC3FE (Bitfield-Mask: 0x01)                           */
#define TIM1_CCMR2_Output_CC3S_Pos (0UL)       /*!< CC3S (Bit 0)                                          */
#define TIM1_CCMR2_Output_CC3S_Msk (0x3UL)     /*!< CC3S (Bitfield-Mask: 0x03)                            */
/* ======================================================  CCMR2_Input  ====================================================== */
#define TIM1_CCMR2_Input_IC4F_Pos (12UL)      /*!< IC4F (Bit 12)                                         */
#define TIM1_CCMR2_Input_IC4F_Msk (0xf000UL)  /*!< IC4F (Bitfield-Mask: 0x0f)                            */
#define TIM1_CCMR2_Input_IC4PSC_Pos (10UL)    /*!< IC4PSC (Bit 10)                                       */
#define TIM1_CCMR2_Input_IC4PSC_Msk (0xc00UL) /*!< IC4PSC (Bitfield-Mask: 0x03)                          */
#define TIM1_CCMR2_Input_CC4S_Pos (8UL)       /*!< CC4S (Bit 8)                                          */
#define TIM1_CCMR2_Input_CC4S_Msk (0x300UL)   /*!< CC4S (Bitfield-Mask: 0x03)                            */
#define TIM1_CCMR2_Input_IC3F_Pos (4UL)       /*!< IC3F (Bit 4)                                          */
#define TIM1_CCMR2_Input_IC3F_Msk (0xf0UL)    /*!< IC3F (Bitfield-Mask: 0x0f)                            */
#define TIM1_CCMR2_Input_IC3PSC_Pos (2UL)     /*!< IC3PSC (Bit 2)                                        */
#define TIM1_CCMR2_Input_IC3PSC_Msk (0xcUL)   /*!< IC3PSC (Bitfield-Mask: 0x03)                          */
#define TIM1_CCMR2_Input_CC3S_Pos (0UL)       /*!< CC3S (Bit 0)                                          */
#define TIM1_CCMR2_Input_CC3S_Msk (0x3UL)     /*!< CC3S (Bitfield-Mask: 0x03)                            */
/* =========================================================  CCER  ========================================================== */
#define TIM1_CCER_CC4P_Pos (13UL)     /*!< CC4P (Bit 13)                                         */
#define TIM1_CCER_CC4P_Msk (0x2000UL) /*!< CC4P (Bitfield-Mask: 0x01)                            */
#define TIM1_CCER_CC4E_Pos (12UL)     /*!< CC4E (Bit 12)                                         */
#define TIM1_CCER_CC4E_Msk (0x1000UL) /*!< CC4E (Bitfield-Mask: 0x01)                            */
#define TIM1_CCER_CC3NP_Pos (11UL)    /*!< CC3NP (Bit 11)                                        */
#define TIM1_CCER_CC3NP_Msk (0x800UL) /*!< CC3NP (Bitfield-Mask: 0x01)                           */
#define TIM1_CCER_CC3NE_Pos (10UL)    /*!< CC3NE (Bit 10)                                        */
#define TIM1_CCER_CC3NE_Msk (0x400UL) /*!< CC3NE (Bitfield-Mask: 0x01)                           */
#define TIM1_CCER_CC3P_Pos (9UL)      /*!< CC3P (Bit 9)                                          */
#define TIM1_CCER_CC3P_Msk (0x200UL)  /*!< CC3P (Bitfield-Mask: 0x01)                            */
#define TIM1_CCER_CC3E_Pos (8UL)      /*!< CC3E (Bit 8)                                          */
#define TIM1_CCER_CC3E_Msk (0x100UL)  /*!< CC3E (Bitfield-Mask: 0x01)                            */
#define TIM1_CCER_CC2NP_Pos (7UL)     /*!< CC2NP (Bit 7)                                         */
#define TIM1_CCER_CC2NP_Msk (0x80UL)  /*!< CC2NP (Bitfield-Mask: 0x01)                           */
#define TIM1_CCER_CC2NE_Pos (6UL)     /*!< CC2NE (Bit 6)                                         */
#define TIM1_CCER_CC2NE_Msk (0x40UL)  /*!< CC2NE (Bitfield-Mask: 0x01)                           */
#define TIM1_CCER_CC2P_Pos (5UL)      /*!< CC2P (Bit 5)                                          */
#define TIM1_CCER_CC2P_Msk (0x20UL)   /*!< CC2P (Bitfield-Mask: 0x01)                            */
#define TIM1_CCER_CC2E_Pos (4UL)      /*!< CC2E (Bit 4)                                          */
#define TIM1_CCER_CC2E_Msk (0x10UL)   /*!< CC2E (Bitfield-Mask: 0x01)                            */
#define TIM1_CCER_CC1NP_Pos (3UL)     /*!< CC1NP (Bit 3)                                         */
#define TIM1_CCER_CC1NP_Msk (0x8UL)   /*!< CC1NP (Bitfield-Mask: 0x01)                           */
#define TIM1_CCER_CC1NE_Pos (2UL)     /*!< CC1NE (Bit 2)                                         */
#define TIM1_CCER_CC1NE_Msk (0x4UL)   /*!< CC1NE (Bitfield-Mask: 0x01)                           */
#define TIM1_CCER_CC1P_Pos (1UL)      /*!< CC1P (Bit 1)                                          */
#define TIM1_CCER_CC1P_Msk (0x2UL)    /*!< CC1P (Bitfield-Mask: 0x01)                            */
#define TIM1_CCER_CC1E_Pos (0UL)      /*!< CC1E (Bit 0)                                          */
#define TIM1_CCER_CC1E_Msk (0x1UL)    /*!< CC1E (Bitfield-Mask: 0x01)                            */
/* ==========================================================  CNT  ========================================================== */
#define TIM1_CNT_CNT_Pos (0UL)      /*!< CNT (Bit 0)                                           */
#define TIM1_CNT_CNT_Msk (0xffffUL) /*!< CNT (Bitfield-Mask: 0xffff)                           */
/* ==========================================================  PSC  ========================================================== */
#define TIM1_PSC_PSC_Pos (0UL)      /*!< PSC (Bit 0)                                           */
#define TIM1_PSC_PSC_Msk (0xffffUL) /*!< PSC (Bitfield-Mask: 0xffff)                           */
/* ==========================================================  ARR  ========================================================== */
#define TIM1_ARR_ARR_Pos (0UL)      /*!< ARR (Bit 0)                                           */
#define TIM1_ARR_ARR_Msk (0xffffUL) /*!< ARR (Bitfield-Mask: 0xffff)                           */
/* =========================================================  CCR1  ========================================================== */
#define TIM1_CCR1_CCR1_Pos (0UL)      /*!< CCR1 (Bit 0)                                          */
#define TIM1_CCR1_CCR1_Msk (0xffffUL) /*!< CCR1 (Bitfield-Mask: 0xffff)                          */
/* =========================================================  CCR2  ========================================================== */
#define TIM1_CCR2_CCR2_Pos (0UL)      /*!< CCR2 (Bit 0)                                          */
#define TIM1_CCR2_CCR2_Msk (0xffffUL) /*!< CCR2 (Bitfield-Mask: 0xffff)                          */
/* =========================================================  CCR3  ========================================================== */
#define TIM1_CCR3_CCR3_Pos (0UL)      /*!< CCR3 (Bit 0)                                          */
#define TIM1_CCR3_CCR3_Msk (0xffffUL) /*!< CCR3 (Bitfield-Mask: 0xffff)                          */
/* =========================================================  CCR4  ========================================================== */
#define TIM1_CCR4_CCR4_Pos (0UL)      /*!< CCR4 (Bit 0)                                          */
#define TIM1_CCR4_CCR4_Msk (0xffffUL) /*!< CCR4 (Bitfield-Mask: 0xffff)                          */
/* ==========================================================  DCR  ========================================================== */
#define TIM1_DCR_DBL_Pos (8UL)      /*!< DBL (Bit 8)                                           */
#define TIM1_DCR_DBL_Msk (0x1f00UL) /*!< DBL (Bitfield-Mask: 0x1f)                             */
#define TIM1_DCR_DBA_Pos (0UL)      /*!< DBA (Bit 0)                                           */
#define TIM1_DCR_DBA_Msk (0x1fUL)   /*!< DBA (Bitfield-Mask: 0x1f)                             */
/* =========================================================  DMAR  ========================================================== */
#define TIM1_DMAR_DMAB_Pos (0UL)      /*!< DMAB (Bit 0)                                          */
#define TIM1_DMAR_DMAB_Msk (0xffffUL) /*!< DMAB (Bitfield-Mask: 0xffff)                          */
/* ==========================================================  RCR  ========================================================== */
#define TIM1_RCR_REP_Pos (0UL)    /*!< REP (Bit 0)                                           */
#define TIM1_RCR_REP_Msk (0xffUL) /*!< REP (Bitfield-Mask: 0xff)                             */
/* =========================================================  BDTR  ========================================================== */
#define TIM1_BDTR_MOE_Pos (15UL)     /*!< MOE (Bit 15)                                          */
#define TIM1_BDTR_MOE_Msk (0x8000UL) /*!< MOE (Bitfield-Mask: 0x01)                             */
#define TIM1_BDTR_AOE_Pos (14UL)     /*!< AOE (Bit 14)                                          */
#define TIM1_BDTR_AOE_Msk (0x4000UL) /*!< AOE (Bitfield-Mask: 0x01)                             */
#define TIM1_BDTR_BKP_Pos (13UL)     /*!< BKP (Bit 13)                                          */
#define TIM1_BDTR_BKP_Msk (0x2000UL) /*!< BKP (Bitfield-Mask: 0x01)                             */
#define TIM1_BDTR_BKE_Pos (12UL)     /*!< BKE (Bit 12)                                          */
#define TIM1_BDTR_BKE_Msk (0x1000UL) /*!< BKE (Bitfield-Mask: 0x01)                             */
#define TIM1_BDTR_OSSR_Pos (11UL)    /*!< OSSR (Bit 11)                                         */
#define TIM1_BDTR_OSSR_Msk (0x800UL) /*!< OSSR (Bitfield-Mask: 0x01)                            */
#define TIM1_BDTR_OSSI_Pos (10UL)    /*!< OSSI (Bit 10)                                         */
#define TIM1_BDTR_OSSI_Msk (0x400UL) /*!< OSSI (Bitfield-Mask: 0x01)                            */
#define TIM1_BDTR_LOCK_Pos (8UL)     /*!< LOCK (Bit 8)                                          */
#define TIM1_BDTR_LOCK_Msk (0x300UL) /*!< LOCK (Bitfield-Mask: 0x03)                            */
#define TIM1_BDTR_DTG_Pos (0UL)      /*!< DTG (Bit 0)                                           */
#define TIM1_BDTR_DTG_Msk (0xffUL)   /*!< DTG (Bitfield-Mask: 0xff)                             */
/* =========================================================  DLAMT  ========================================================== */
#define TIM1_DLAMT_DLS_Pos (17UL)
#define TIM1_DLAMT_DLS_Msk (0x2000UL)
#define TIM1_DLAMT_AMTDL_Pos (16UL)
#define TIM1_DLAMT_AMTDL_Msk (0x1000UL)
#define TIM1_DLAMT_ATMG_Pos (8UL)
#define TIM1_DLAMT_ATMG_Msk (0xFF00UL)
#define TIM1_DLAMT_DLG_Pos (0UL)
#define TIM1_DLAMT_DLG_Msk (0xFFUL)
/* =========================================================  OR  ========================================================== */
#define TIM1_OR_TL1RMP_Pos (0UL)
#define TIM1_OR_TL1RMP_Msk (0x3UL)
/* =========================================================  CCTR1  ========================================================== */
#define TIM1_CCTR1_Pos (0UL)
#define TIM1_CCTR1_Msk (0xFFFFUL)
/* =========================================================  CCTR2  ========================================================== */
#define TIM1_CCTR2_Pos (0UL)
#define TIM1_CCTR2_Msk (0xFFFFUL)
/* =========================================================  CCTR3  ========================================================== */
#define TIM1_CCTR3_Pos (0UL)
#define TIM1_CCTR3_Msk (0xFFFFUL)
/* =========================================================  CCTR4  ========================================================== */
#define TIM1_CCTR4_Pos (0UL)
#define TIM1_CCTR4_Msk (0xFFFFUL)

void TIM_DeInit(TIM_TypeDef *TIMx);
void TIM_TimeBaseInit(TIM_TypeDef *TIMx, TIM_TimeBaseInitTypeDef *TIM_TimeBaseInitStruct);
void TIM_TimeBaseStructInit(TIM_TimeBaseInitTypeDef *TIM_TimeBaseInitStruct);
void TIM_PrescalerConfig(TIM_TypeDef *TIMx, uint16_t Prescaler, uint16_t TIM_PSCReloadMode);
void TIM_CounterModeConfig(TIM_TypeDef *TIMx, uint16_t TIM_CounterMode);
void TIM_SetCounter(TIM_TypeDef *TIMx, uint32_t Counter);
void TIM_SetAutoreload(TIM_TypeDef *TIMx, uint32_t Autoreload);
uint32_t TIM_GetCounter(TIM_TypeDef *TIMx);
uint16_t TIM_GetPrescaler(TIM_TypeDef *TIMx);
void TIM_UpdateDisableConfig(TIM_TypeDef *TIMx, FunctionalState NewState);
void TIM_UpdateRequestConfig(TIM_TypeDef *TIMx, uint16_t TIM_UpdateSource);
void TIM_ARRPreloadConfig(TIM_TypeDef *TIMx, FunctionalState NewState);
void TIM_SelectOnePulseMode(TIM_TypeDef *TIMx, uint16_t TIM_OPMode);
void TIM_SetClockDivision(TIM_TypeDef *TIMx, uint16_t TIM_CKD);
void TIM_Cmd(TIM_TypeDef *TIMx, FunctionalState NewState);

/* Advanced-control timers (TIM1) specific features*******************/
void TIM_BDTRConfig(TIM_TypeDef *TIMx, TIM_BDTRInitTypeDef *TIM_BDTRInitStruct);
void TIM_BDTRStructInit(TIM_BDTRInitTypeDef *TIM_BDTRInitStruct);
void TIM_CtrlPWMOutputs(TIM_TypeDef *TIMx, FunctionalState NewState);

/* Output Compare management **************************************************/
void TIM_OC1Init(TIM_TypeDef *TIMx, TIM_OCInitTypeDef *TIM_OCInitStruct);
void TIM_OC2Init(TIM_TypeDef *TIMx, TIM_OCInitTypeDef *TIM_OCInitStruct);
void TIM_OC3Init(TIM_TypeDef *TIMx, TIM_OCInitTypeDef *TIM_OCInitStruct);
void TIM_OC4Init(TIM_TypeDef *TIMx, TIM_OCInitTypeDef *TIM_OCInitStruct);
void TIM_OCStructInit(TIM_OCInitTypeDef *TIM_OCInitStruct);
void TIM_SelectOCxM(TIM_TypeDef *TIMx, uint16_t TIM_Channel, uint16_t TIM_OCMode);
void TIM_SetCompare1(TIM_TypeDef *TIMx, uint32_t Compare1);
void TIM_SetCompare2(TIM_TypeDef *TIMx, uint32_t Compare2);
void TIM_SetCompare3(TIM_TypeDef *TIMx, uint32_t Compare3);
void TIM_SetCompare4(TIM_TypeDef *TIMx, uint32_t Compare4);
void TIM_ForcedOC1Config(TIM_TypeDef *TIMx, uint16_t TIM_ForcedAction);
void TIM_ForcedOC2Config(TIM_TypeDef *TIMx, uint16_t TIM_ForcedAction);
void TIM_ForcedOC3Config(TIM_TypeDef *TIMx, uint16_t TIM_ForcedAction);
void TIM_ForcedOC4Config(TIM_TypeDef *TIMx, uint16_t TIM_ForcedAction);
void TIM_CCPreloadControl(TIM_TypeDef *TIMx, FunctionalState NewState);
void TIM_OC1PreloadConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCPreload);
void TIM_OC2PreloadConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCPreload);
void TIM_OC3PreloadConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCPreload);
void TIM_OC4PreloadConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCPreload);
void TIM_OC1FastConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCFast);
void TIM_OC2FastConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCFast);
void TIM_OC3FastConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCFast);
void TIM_OC4FastConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCFast);
void TIM_ClearOC1Ref(TIM_TypeDef *TIMx, uint16_t TIM_OCClear);
void TIM_ClearOC2Ref(TIM_TypeDef *TIMx, uint16_t TIM_OCClear);
void TIM_ClearOC3Ref(TIM_TypeDef *TIMx, uint16_t TIM_OCClear);
void TIM_ClearOC4Ref(TIM_TypeDef *TIMx, uint16_t TIM_OCClear);
void TIM_OC1PolarityConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCPolarity);
void TIM_OC1NPolarityConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCNPolarity);
void TIM_OC2PolarityConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCPolarity);
void TIM_OC2NPolarityConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCNPolarity);
void TIM_OC3PolarityConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCPolarity);
void TIM_OC3NPolarityConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCNPolarity);
void TIM_OC4PolarityConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCPolarity);
void TIM_SelectOCREFClear(TIM_TypeDef *TIMx, uint16_t TIM_OCReferenceClear);
void TIM_CCxCmd(TIM_TypeDef *TIMx, uint16_t TIM_Channel, uint16_t TIM_CCx);
void TIM_CCxNCmd(TIM_TypeDef *TIMx, uint16_t TIM_Channel, uint16_t TIM_CCxN);
void TIM_SelectCOM(TIM_TypeDef *TIMx, FunctionalState NewState);

/* Input Capture management ***************************************************/
void TIM_ICInit(TIM_TypeDef *TIMx, TIM_ICInitTypeDef *TIM_ICInitStruct);
void TIM_ICStructInit(TIM_ICInitTypeDef *TIM_ICInitStruct);
void TIM_PWMIConfig(TIM_TypeDef *TIMx, TIM_ICInitTypeDef *TIM_ICInitStruct);
uint32_t TIM_GetCapture1(TIM_TypeDef *TIMx);
uint32_t TIM_GetCapture2(TIM_TypeDef *TIMx);
uint32_t TIM_GetCapture3(TIM_TypeDef *TIMx);
uint32_t TIM_GetCapture4(TIM_TypeDef *TIMx);
void TIM_SetIC1Prescaler(TIM_TypeDef *TIMx, uint16_t TIM_ICPSC);
void TIM_SetIC2Prescaler(TIM_TypeDef *TIMx, uint16_t TIM_ICPSC);
void TIM_SetIC3Prescaler(TIM_TypeDef *TIMx, uint16_t TIM_ICPSC);
void TIM_SetIC4Prescaler(TIM_TypeDef *TIMx, uint16_t TIM_ICPSC);

/* Interrupts, DMA and flags management ***************************************/
void TIM_ITConfig(TIM_TypeDef *TIMx, uint16_t TIM_IT, FunctionalState NewState);
void TIM_GenerateEvent(TIM_TypeDef *TIMx, uint16_t TIM_EventSource);
FlagStatus TIM_GetFlagStatus(TIM_TypeDef *TIMx, uint16_t TIM_FLAG);
void TIM_ClearFlag(TIM_TypeDef *TIMx, uint16_t TIM_FLAG);
ITStatus TIM_GetITStatus(TIM_TypeDef *TIMx, uint16_t TIM_IT);
void TIM_ClearITPendingBit(TIM_TypeDef *TIMx, uint16_t TIM_IT);
void TIM_DMAConfig(TIM_TypeDef *TIMx, uint16_t TIM_DMABase, uint16_t TIM_DMABurstLength);
void TIM_DMACmd(TIM_TypeDef *TIMx, uint16_t TIM_DMASource, FunctionalState NewState);
void TIM_SelectCCDMA(TIM_TypeDef *TIMx, FunctionalState NewState);

/* Clocks management **********************************************************/
void TIM_InternalClockConfig(TIM_TypeDef *TIMx);
void TIM_ITRxExternalClockConfig(TIM_TypeDef *TIMx, uint16_t TIM_InputTriggerSource);
void TIM_TIxExternalClockConfig(TIM_TypeDef *TIMx, uint16_t TIM_TIxExternalCLKSource,
                                uint16_t TIM_ICPolarity, uint16_t ICFilter);
void TIM_ETRClockMode1Config(TIM_TypeDef *TIMx, uint16_t TIM_ExtTRGPrescaler, uint16_t TIM_ExtTRGPolarity,
                             uint16_t ExtTRGFilter);
void TIM_ETRClockMode2Config(TIM_TypeDef *TIMx, uint16_t TIM_ExtTRGPrescaler,
                             uint16_t TIM_ExtTRGPolarity, uint16_t ExtTRGFilter);

/* Synchronization management *************************************************/
void TIM_SelectInputTrigger(TIM_TypeDef *TIMx, uint16_t TIM_InputTriggerSource);
void TIM_SelectOutputTrigger(TIM_TypeDef *TIMx, uint16_t TIM_TRGOSource);
void TIM_SelectSlaveMode(TIM_TypeDef *TIMx, uint16_t TIM_SlaveMode);
void TIM_SelectMasterSlaveMode(TIM_TypeDef *TIMx, uint16_t TIM_MasterSlaveMode);
void TIM_ETRConfig(TIM_TypeDef *TIMx, uint16_t TIM_ExtTRGPrescaler, uint16_t TIM_ExtTRGPolarity,
                   uint16_t ExtTRGFilter);

/* Specific interface management **********************************************/
void TIM_EncoderInterfaceConfig(TIM_TypeDef *TIMx, uint16_t TIM_EncoderMode,
                                uint16_t TIM_IC1Polarity, uint16_t TIM_IC2Polarity);
void TIM_SelectHallSensor(TIM_TypeDef *TIMx, FunctionalState NewState);

/* Specific remapping management **********************************************/
void TIM_RemapConfig(TIM_TypeDef *TIMx, uint16_t TIM_Remap);

void NVIC_Init(NVIC_InitTypeDef *NVIC_InitStruct);

void TIM_DTS_Cfg(TIM_TypeDef *TIMx);
void TIM_TI1E_Set(TIM_TypeDef *TIMx);
void TIM_TI2E_Set(TIM_TypeDef *TIMx);
void TIM_TI3E_Set(TIM_TypeDef *TIMx);
void TIM_TI4E_Set(TIM_TypeDef *TIMx);
/*SYSCTRL_EDU_CFGx confg****************************************************/
void TIM1_IntputSourceCfg(uint32_t TIx, uint32_t TIM_IntputSource);
void TIM3_IntputSourceCfg(uint32_t TIx, uint32_t TIM_IntputSource);
void TIM15_IntputSourceCfg(uint32_t TIx, uint32_t TIM_IntputSource);
void TIM16_IntputSourceCfg(uint32_t TIx, uint32_t TIM_IntputSource);
void TIM17_IntputSourceCfg(uint32_t TIx, uint32_t TIM_IntputSource);
void TIM1_BreakSourceCfg(uint32_t TIM_BreakSource, uint32_t TIM_Level);
void TIM15_BreakSourceCfg(uint32_t TIM_BreakSource, uint32_t TIM_Level);
void TIM16_BreakSourceCfg(uint32_t TIM_BreakSource, uint32_t TIM_Level);
void TIM17_BreakSourceCfg(uint32_t TIM_BreakSource, uint32_t TIM_Level);
void TIM1_OCREF_CLR_SourceCfg(uint32_t TIM_OCREF_CLR_Source, uint32_t TIM_Level);
void TIM3_OCREF_CLR_SourceCfg(uint32_t OCREF_CLR_Source, uint32_t TIM_Level);
#endif // __ADV_TIMER_H__
