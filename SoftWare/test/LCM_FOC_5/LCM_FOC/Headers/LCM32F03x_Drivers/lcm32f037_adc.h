#ifndef LCM32F037_ADC_H
#define LCM32F037_ADC_H
#include "lcm32f037.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define ADC1_DR_Address    ((u32)0x4001A020)
#define ADC_SIZE				10
#if(UPDS_UABC_MEAS_SEL == UPDS_UABC_MEAS_DISABLE)
	#define ADC_SAMPLE_NUM 	8 //YK-TEST 2023-6-11
#elif(UPDS_UABC_MEAS_SEL == UPDS_UABC_MEAS_ENABLE)	
	#define ADC_SAMPLE_NUM 	10
#endif
  /*--------------------------------------------------------------------------------------------
   adc 12parameters cfg:
  --------------------------------------------------------------------------------------------*/
  typedef struct
  {

    uint32_t ADC_ClkMode; /*   ADC ʱ�ӷ�Ƶ                                       */

    uint32_t ADC_Resolution; /*  adc��������λ������ ���ͺ���ʱֻ֧��12bit           */

    FunctionalState ADC_ContinuousConvMode; /*  ����ת��ģʽ�Ƿ�ʹ��                                */

    FunctionalState ADC_AutoWatiMode; /*�Զ��ӳ�ת����һ�㱣֤��ͨ������˳�򲻴���            */

    FunctionalState ADC_DMA; /* DMA*/

    FunctionalState ADC_DiscMode; /* ����ģʽ*/

    FunctionalState ADC_SamecMode; /*ͬʱ���� */

    uint32_t ADC_ExternalTrigConvEdge; /*   ��������or��ƽ����
	                                               < Selects the external trigger Edge and enables the
                                                 trigger of a regular group. This parameter can be a value
                                                 of @ref ADC_external_trigger_edge_conversion */

    uint32_t ADC_ExternalTrigConv; /*   �ⲿ����Դѡ��
	                                               !< Defines the external trigger used to start the analog
                                                 to digital conversion of regular channels. This parameter
                                                 can be a value of @ref ADC_external_trigger_sources_for_channels_conversion */

    uint32_t ADC_DataAlign;     /*   ���ݶ��뷽��
	                                               !< Specifies whether the ADC data alignment is left or right.
                                                 This parameter can be a value of @ref ADC_data_align */
    uint32_t ADC_DMATRIG_LEVEL; /*�ô��� DMA ����� FIFO ˮƽ���� DMAEN ʹ��ǰ��������*/

    uint32_t ADC_ScanDirection; /*   ͨ��ɨ�跽������
	                                               !< Specifies in which direction the channels will be scanned
                                                 in the sequence. 
                                                 This parameter can be a value of @ref ADC_Scan_Direction */
    uint32_t ADC_Vref;          /*	ADC-vref select		*/

  } ADC_InitTypeDef;

/*--------------------------------------------------------------------------------------------
 ADC_CLK_MODE SELECT: ADCCLK<=24mhz ; 
 Going out of range can lead to unpredictable errors;
  --------------------------------------------------------------------------------------------*/
//ͬ��ʱ�� sysclk
#define ADC_ClockMode_sysnClk ((uint32_t)0x00000000) /*!< ��ϵͳʱ��ͬ�� */
#define ADC_ClockMode_SynClkDiv2 (0X01 << 27)        /*!<  Synchronous clock mode divided by 2 */
#define ADC_ClockMode_SynClkDiv4 (0X02 << 27)        /*!<  Synchronous clock mode divided by 4 */
#define ADC_ClockMode_SynClkDiv6 (0X03 << 27)        /*!<  Synchronous clock mode divided by 6 */
#define ADC_ClockMode_SynClkDiv8 (0X04 << 27)        /*!<  Synchronous clock mode divided by 8 */
#define ADC_ClockMode_SynClkDiv10 (0X05 << 27)       /*!<  Synchronous clock mode divided by 10 */
#define ADC_ClockMode_SynClkDiv12 (0X06 << 27)       /*!<  Synchronous clock mode divided by 12 */
#define ADC_ClockMode_SynClkDiv16 (0X07 << 27)       /*!<  Synchronous clock mode divided by 16 */
//�첽ʱ��pllclk
#define ADC_ClockMode_PLLClk ((uint32_t)0x80000000) /*!< ��pllʱ�����������첽ʱ�� */
#define ADC_ClockMode_PLLClkDiv2 (0X11 << 27)       /*!<  PLL clock mode divided by 2 */
#define ADC_ClockMode_PLLClkDiv4 (0X12 << 27)       /*!<  PLL clock mode divided by 4 */
#define ADC_ClockMode_PLLClkDiv6 (0X13 << 27)       /*!<  PLL clock mode divided by 6 */
#define ADC_ClockMode_PLLClkDiv8 (0X14 << 27)       /*!<  PLL clock mode divided by 8 */
#define ADC_ClockMode_PLLClkDiv10 (0X15 << 27)      /*!<  PLL clock mode divided by 10 */
#define ADC_ClockMode_PLLClkDiv12 (0X16 << 27)      /*!<  PLL clock mode divided by 12 */
#define ADC_ClockMode_PLLClkDiv16 (0X17 << 27)      /*!<  PLL clock mode divided by 16 */

/*--------------------------------------------------------------------------------------------
RESLUTION BIT:just 12bit
  --------------------------------------------------------------------------------------------*/
#define ADC_Resolution_12b ((uint32_t)0x00000000)
/****************** RESLUTION BIT **************/
#define ADC_DataAlign_Right ((uint32_t)0x00000000)
#define ADC_DataAlign_Left ((uint32_t)0x00000020)

/*--------------------------------------------------------------------------------------------
scan align  :
  --------------------------------------------------------------------------------------------*/
#define ADC_ScanDirection_Upward ((uint32_t)0x00000000)
#define ADC_ScanDirection_Backward (0x1UL << 2)

/*--------------------------------------------------------------------------------------------
EXT_TRIG_EDGE :
  --------------------------------------------------------------------------------------------*/
#define ADC_ExternalTrigConvEdge_None ((uint32_t)0x00000000)
#define ADC_ExternalTrigConvEdge_Rising (1 << 0)
#define ADC_ExternalTrigConvEdge_Falling (2 << 0)
#define ADC_ExternalTrigConvEdge_RisingFalling (3 << 0)

/*--------------------------------------------------------------------------------------------
EXT_TRIG_SOURCE :
  --------------------------------------------------------------------------------------------*/
#define ADC_ExternalTrigConv_SoftWare ((uint32_t)0x00000000)
/* 5 */
#define ADC_ExternalTrigConv_T1_TRGO ((uint32_t)0x80000000)
#define ADC_ExternalTrigConv_T3_TRGO ((uint32_t)0x80100000)
#define ADC_ExternalTrigConv_T15_TRGO ((uint32_t)0x80200000)
#define ADC_ExternalTrigConv_ACMP5 ((uint32_t)0x80300000)
/* 4 */
#define ADC_ExternalTrigConv_T1_CC4 ((uint32_t)0x40000000)
#define ADC_ExternalTrigConv_T3_CC4 ((uint32_t)0x40040000)
#define ADC_ExternalTrigConv_T17_CC1 ((uint32_t)0x40080000)
#define ADC_ExternalTrigConv_ACMP0 ((uint32_t)0x400C0000)
/* 3 */
#define ADC_ExternalTrigConv_T1_CC3 ((uint32_t)0x20000000)
#define ADC_ExternalTrigConv_T3_CC3 ((uint32_t)0x20010000)
#define ADC_ExternalTrigConv_T16_CC1 ((uint32_t)0x20020000)
#define ADC_ExternalTrigConv_EXTI11 ((uint32_t)0x20030000)
/* 2 */
#define ADC_ExternalTrigConv_T1_CC2 ((uint32_t)0x10000000)
#define ADC_ExternalTrigConv_T3_CC2 ((uint32_t)0x10004000)
#define ADC_ExternalTrigConv_T15_CC2 ((uint32_t)0x10008000)
#define ADC_ExternalTrigConv_EXTI3 ((uint32_t)0x1000C000)
/* 1 */
#define ADC_ExternalTrigConv_T1_CC1 ((uint32_t)0x08000000)
#define ADC_ExternalTrigConv_T3_CC1 ((uint32_t)0x08001000)
#define ADC_ExternalTrigConv_T15_CC1 ((uint32_t)0x08002000)
#define ADC_ExternalTrigConv_EXTI1 ((uint32_t)0x08003000)

  /*--------------------------------------------------------------------------------------------
atchdog_Channel : SELECT
  --------------------------------------------------------------------------------------------*/
#define ADC_AnalogWatchdog_Channel_0 ((uint32_t)0x00000000)
#define ADC_AnalogWatchdog_Channel_1 ((uint32_t)0x08000000)
#define ADC_AnalogWatchdog_Channel_2 ((uint32_t)0x10000000)
#define ADC_AnalogWatchdog_Channel_3 ((uint32_t)0x18000000)
#define ADC_AnalogWatchdog_Channel_4 ((uint32_t)0x20000000)
#define ADC_AnalogWatchdog_Channel_5 ((uint32_t)0x21000000)
#define ADC_AnalogWatchdog_Channel_6 ((uint32_t)0x30000000)
#define ADC_AnalogWatchdog_Channel_7 ((uint32_t)0x38000000)
#define ADC_AnalogWatchdog_Channel_8 ((uint32_t)0x40000000)
#define ADC_AnalogWatchdog_Channel_9 ((uint32_t)0x48000000)
#define ADC_AnalogWatchdog_Channel_10 ((uint32_t)0x50000000)
#define ADC_AnalogWatchdog_Channel_11 ((uint32_t)0x58000000)
#define ADC_AnalogWatchdog_Channel_12 ((uint32_t)0x60000000)
#define ADC_AnalogWatchdog_Channel_13 ((uint32_t)0x68000000)
#define ADC_AnalogWatchdog_Channel_14 ((uint32_t)0x70000000)
#define ADC_AnalogWatchdog_Channel_15 ((uint32_t)0x78000000)

#define FIFO_DMA_NOEMPTY ((uint32_t)0x00000000)
#define FIFO_DMA_4LEVEL ((uint32_t)0x00000008)
#define FIFO_DMA_8LEVEL ((uint32_t)0x00000010)
#define FIFO_DMA_12LEVEL ((uint32_t)0x00000018)
  /*--------------------------------------------------------------------------------------------
adc-samptime select
  --------------------------------------------------------------------------------------------*/
#define ADC_SampleTime_1Cycles ((uint32_t)0x00000000)
#define ADC_SampleTime_2Cycles ((uint32_t)0x00000001)
#define ADC_SampleTime_3Cycles ((uint32_t)0x00000002)
#define ADC_SampleTime_4Cycles ((uint32_t)0x00000003)
#define ADC_SampleTime_5Cycles ((uint32_t)0x00000004)
#define ADC_SampleTime_6Cycles ((uint32_t)0x00000005)
#define ADC_SampleTime_7Cycles ((uint32_t)0x00000006)
#define ADC_SampleTime_8Cycles ((uint32_t)0x00000007)

#define ADC_ConverTime_10Cycles ((uint32_t)0x00000570)
#define ADC_ConverTime_15Cycles ((uint32_t)0x000007f0)
#define ADC_ConverTime_20Cycles ((uint32_t)0x00000A70)

  /*--------------------------------------------------------------------------------------------
ADC-vref select
  --------------------------------------------------------------------------------------------*/
#define ADC_Vref_Internal_3V3 ((uint32_t)0x00000001)
#define ADC_Vref_Internal_3V3_data ((uint32_t)0x00000000)
#define ADC_Vref_Internal_5V ((uint32_t)0x00000002)
#define ADC_Vref_Internal_5V_data ((uint32_t)0x00000008)

#define ADC_Vref_Externa_Vrh2V5 ((uint32_t)0x00000003)
#define ADC_Vref_Externa_Vrh2V5_data (0x4UL << 16)

#define ADC_Vref_Externa_Vrh4V ((uint32_t)0x00000004)
#define ADC_Vref_Externa_Vrh4V_data (0x6UL << 16)

#define ADC_Vref_Externa_VDD ((uint32_t)0x00000005)
#define ADC_Vref_Externa_VDD_data (0x0UL << 16)

#define ADC_Vref_Externa_IO ((uint32_t)0x00000006)
#define ADC_Vref_Externa_IO_data (0x2UL << 18)

#define ADC_Vref_ExternaIO_VRH_C ((uint32_t)0x00000007)
#define ADC_Vref_ExternaIO_VRH_C_data (0x3UL << 18)

/*--------------------------------------------------------------------------------------------
 ADC-Channel select
  --------------------------------------------------------------------------------------------*/
#define ADC_Channel_0 ((uint32_t)0x00000001)
#define ADC_Channel_1 ((uint32_t)0x00000002)
#define ADC_Channel_2 ((uint32_t)0x00000004)
#define ADC_Channel_3 ((uint32_t)0x00000008)
#define ADC_Channel_4 ((uint32_t)0x00000010)
#define ADC_Channel_5 ((uint32_t)0x00000020)
#define ADC_Channel_6 ((uint32_t)0x00000040)
#define ADC_Channel_7 ((uint32_t)0x00000080)
#define ADC_Channel_8 ((uint32_t)0x00000100)
#define ADC_Channel_9 ((uint32_t)0x00000200)
#define ADC_Channel_10 ((uint32_t)0x00000400)
#define ADC_Channel_11 ((uint32_t)0x00000800)
#define ADC_Channel_12 ((uint32_t)0x00001000)
#define ADC_Channel_13 ((uint32_t)0x00002000)
#define ADC_Channel_14 ((uint32_t)0x00004000)
#define ADC_Channel_15 ((uint32_t)0x00008000)
#define ADC_Channel_16 ((uint32_t)0x00030000)
#define ADC_Channel_17 ((uint32_t)0x00020000)

#define ADC_Channel_TempSensor ((uint32_t)ADC_Channel_17)
#define ADC_Channel_Vrefint ((uint32_t)ADC_Channel_16)

#define ADC_FLAG_ADRDY ADC_ISR_ADRDY_Msk
#define ADC_FLAG_EOSMP ADC_ISR_EOSMP_Msk
#define ADC_FLAG_EOC ADC_ISR_EOC_Msk
#define ADC_FLAG_EOSEQ ADC_ISR_EOSEQ_Msk
#define ADC_FLAG_OVR ADC_ISR_OVR_Msk
#define ADC_FLAG_AWD ADC_ISR_AWD_Msk

#define ADC_CFGR2_Con_Pos 0
#define ADC_CFGR2_Con_Msk (0x1fUL << ADC_CFGR1_AWDCH_Pos)
///****************** Bit Definition for ADC_SMPR Register **************/
#define ADC_Convert_Pos 7
#define ADC_Convert_Msk (0x1fUL << ADC_SMPR_SMP_Pos)
#define ADC_Adjust_Pos 4
#define ADC_Adjust_Msk (0x7UL << ADC_SMPR_SMP_Pos)

/* =========================================================================================================================== */
/* ================                                            ADC                                            ================ */
/* =========================================================================================================================== */

/* ==========================================================  ISR  ========================================================== */
#define ADC_ISR_FIFO_FULL_Pos (12UL)            /*!< AWD (Bit 7)                                           */
#define ADC_ISR_FIFO_FULL_Msk (0x1000UL)        /*!< AWD (Bitfield-Mask: 0x01)                             */
#define ADC_ISR_FIFO_ALMOST_FULL_Pos (11UL)     /*!< AWD (Bit 7)                                           */
#define ADC_ISR_FIFO_ALMOST_FULL_Msk (0x800UL)  /*!< AWD (Bitfield-Mask: 0x01)                             */
#define ADC_ISR_FIFO_HALF_FULL_Pos (10UL)       /*!< AWD (Bit 7)                                           */
#define ADC_ISR_FIFO_HALF_FULL_Msk (0x400UL)    /*!< AWD (Bitfield-Mask: 0x01)                             */
#define ADC_ISR_FIFO_ALMOST_EMPTY_Pos (9UL)     /*!< AWD (Bit 7)                                           */
#define ADC_ISR_FIFO_ALMOST_EMPTY_Msk (0x200UL) /*!< AWD (Bitfield-Mask: 0x01)                             */
#define ADC_ISR_FIFO_EMPTY_Pos (8UL)            /*!< AWD (Bit 7)                                           */
#define ADC_ISR_FIFO_EMPTY_Msk (0x100UL)        /*!< AWD (Bitfield-Mask: 0x01)                             */
#define ADC_ISR_AWD_Pos (7UL)                   /*!< AWD (Bit 7)                                           */
#define ADC_ISR_AWD_Msk (0x80UL)                /*!< AWD (Bitfield-Mask: 0x01)                             */
#define ADC_ISR_OVR_Pos (4UL)                   /*!< OVR (Bit 4)                                           */
#define ADC_ISR_OVR_Msk (0x10UL)                /*!< OVR (Bitfield-Mask: 0x01)                             */
#define ADC_ISR_EOSEQ_Pos (3UL)                 /*!< EOSEQ (Bit 3)                                         */
#define ADC_ISR_EOSEQ_Msk (0x8UL)               /*!< EOSEQ (Bitfield-Mask: 0x01)                           */
#define ADC_ISR_EOC_Pos (2UL)                   /*!< EOC (Bit 2)                                           */
#define ADC_ISR_EOC_Msk (0x4UL)                 /*!< EOC (Bitfield-Mask: 0x01)                             */
#define ADC_ISR_EOSMP_Pos (1UL)                 /*!< EOSMP (Bit 1)                                         */
#define ADC_ISR_EOSMP_Msk (0x2UL)               /*!< EOSMP (Bitfield-Mask: 0x01)                           */
#define ADC_ISR_ADRDY_Pos (0UL)                 /*!< ADRDY (Bit 0)                                         */
#define ADC_ISR_ADRDY_Msk (0x1UL)               /*!< ADRDY (Bitfield-Mask: 0x01)                           */
/* ==========================================================  IER  ========================================================== */
#define ADC_IER_AWDIE_Pos (7UL)     /*!< AWDIE (Bit 7)                                         */
#define ADC_IER_AWDIE_Msk (0x80UL)  /*!< AWDIE (Bitfield-Mask: 0x01)                           */
#define ADC_IER_OVRIE_Pos (4UL)     /*!< OVRIE (Bit 4)                                         */
#define ADC_IER_OVRIE_Msk (0x10UL)  /*!< OVRIE (Bitfield-Mask: 0x01)                           */
#define ADC_IER_EOSIE_Pos (3UL)     /*!< EOSIE (Bit 3)                                         */
#define ADC_IER_EOSIE_Msk (0x8UL)   /*!< EOSIE (Bitfield-Mask: 0x01)                           */
#define ADC_IER_EOCIE_Pos (2UL)     /*!< EOCIE (Bit 2)                                         */
#define ADC_IER_EOCIE_Msk (0x4UL)   /*!< EOCIE (Bitfield-Mask: 0x01)                           */
#define ADC_IER_EOSMPIE_Pos (1UL)   /*!< EOSMPIE (Bit 1)                                       */
#define ADC_IER_EOSMPIE_Msk (0x2UL) /*!< EOSMPIE (Bitfield-Mask: 0x01)                         */
#define ADC_IER_ADRDYIE_Pos (0UL)   /*!< ADRDYIE (Bit 0)                                       */
#define ADC_IER_ADRDYIE_Msk (0x1UL) /*!< ADRDYIE (Bitfield-Mask: 0x01)                         */
/* ==========================================================  CR  =========================================================== */
#define ADC_CR_ADSTP_Pos (4UL)     /*!< ADSTP (Bit 4)                                         */
#define ADC_CR_ADSTP_Msk (0x10UL)  /*!< ADSTP (Bitfield-Mask: 0x01)                           */
#define ADC_CR_ADSTART_Pos (2UL)   /*!< ADSTART (Bit 2)                                       */
#define ADC_CR_ADSTART_Msk (0x4UL) /*!< ADSTART (Bitfield-Mask: 0x01)                         */
#define ADC_CR_ADDIS_Pos (1UL)     /*!< ADDIS (Bit 1)                                         */
#define ADC_CR_ADDIS_Msk (0x2UL)   /*!< ADDIS (Bitfield-Mask: 0x01)                           */
#define ADC_CR_ADEN_Pos (0UL)      /*!< ADEN (Bit 0)                                          */
#define ADC_CR_ADEN_Msk (0x1UL)    /*!< ADEN (Bitfield-Mask: 0x01)                            */
/* =========================================================  CFGR1  ========================================================= */
#define ADC_CFGR1_AWDCH_Pos (27UL)         /*!< AWDCH (Bit 27)                                        */
#define ADC_CFGR1_AWDCH_Msk (0x78000000UL) /*!< AWDCH (Bitfield-Mask: 0x0f)                           */
#define ADC_CFGR1_AWDEN_Pos (23UL)         /*!< AWDEN (Bit 23)                                        */
#define ADC_CFGR1_AWDEN_Msk (0x800000UL)   /*!< AWDEN (Bitfield-Mask: 0x01)                           */
#define ADC_CFGR1_AWDSGL_Pos (22UL)        /*!< AWDSGL (Bit 22)                                       */
#define ADC_CFGR1_AWDSGL_Msk (0x400000UL)  /*!< AWDSGL (Bitfield-Mask: 0x01)                          */
#define ADC_CFGR1_DISCEN_Pos (16UL)        /*!< DISCEN (Bit 16)                                       */
#define ADC_CFGR1_DISCEN_Msk (0x10000UL)   /*!< DISCEN (Bitfield-Mask: 0x01)                          */
#define ADC_CFGR1_WAIT_Pos (14UL)          /*!< WAIT (Bit 14)                                         */
#define ADC_CFGR1_WAIT_Msk (0x4000UL)      /*!< WAIT (Bitfield-Mask: 0x01)                            */
#define ADC_CFGR1_CONT_Pos (13UL)          /*!< CONT (Bit 13)                                         */
#define ADC_CFGR1_CONT_Msk (0x2000UL)      /*!< CONT (Bitfield-Mask: 0x01)                            */
#define ADC_CFGR1_OVRMOD_Pos (12UL)        /*!< OVRMOD (Bit 12)                                       */
#define ADC_CFGR1_OVRMOD_Msk (0x1000UL)    /*!< OVRMOD (Bitfield-Mask: 0x01)                          */
#define ADC_CFGR1_ALIGN_Pos (5UL)          /*!< ALIGN (Bit 5)                                         */
#define ADC_CFGR1_ALIGN_Msk (0x20UL)       /*!< ALIGN (Bitfield-Mask: 0x01)                           */
#define ADC_CFGR1_SCANDIR_Pos (2UL)        /*!< SCANDIR (Bit 2)                                       */
#define ADC_CFGR1_SCANDIR_Msk (0x4UL)      /*!< SCANDIR (Bitfield-Mask: 0x01)                         */
#define ADC_CFGR1_DMAEN_Pos (0UL)          /*!< DMAEN (Bit 0)                                         */
#define ADC_CFGR1_DMAEN_Msk (0x1UL)        /*!< DMAEN (Bitfield-Mask: 0x01)                           */
/* =========================================================  CFGR2  ========================================================= */
#define ADC_CFGR2_CKMODE_Pos (27UL)         /*!< CKMODE (Bit 27)                                       */
#define ADC_CFGR2_CKMODE_Msk (0xf8000000UL) /*!< CKMODE (Bitfield-Mask: 0x1f)                          */
#define ADC_CFGR2_LP_EN_Pos (10UL)          /*!< LP_EN (Bit 10)                                        */
#define ADC_CFGR2_LP_EN_Msk (0x400UL)       /*!< LP_EN (Bitfield-Mask: 0x01)                           */
#define ADC_CFGR2_LP_Pos (9UL)              /*!< LP (Bit 9)                                            */
#define ADC_CFGR2_LP_Msk (0x200UL)          /*!< LP (Bitfield-Mask: 0x01)                              */
#define ADC_CFGR2_PWR_SET_Pos (3UL)         /*!< PWR_SET (Bit 3)                                       */
#define ADC_CFGR2_PWR_SET_Msk (0x8UL)       /*!< PWR_SET (Bitfield-Mask: 0x01)                         */
#define ADC_CFGR2_PULSE_Pos (2UL)           /*!< PULSE (Bit 2)                                         */
#define ADC_CFGR2_PULSE_Msk (0x4UL)         /*!< PULSE (Bitfield-Mask: 0x01)                           */
#define ADC_CFGR2_EXT_REF_Pos (1UL)         /*!< EXT_REF (Bit 1)                                       */
#define ADC_CFGR2_EXT_REF_Msk (0x2UL)       /*!< EXT_REF (Bitfield-Mask: 0x01)                         */
#define ADC_CFGR2_CON_Pos (0UL)             /*!< CON (Bit 0)                                           */
#define ADC_CFGR2_CON_Msk (0x1UL)           /*!< CON (Bitfield-Mask: 0x01)                             */
/* =========================================================  SMPR  ========================================================== */
#define ADC_SMPR_CONVERT_Pos (7UL)     /*!< CONVERT (Bit 7)                                       */
#define ADC_SMPR_CONVERT_Msk (0xf80UL) /*!< CONVERT (Bitfield-Mask: 0x1f)                         */
#define ADC_SMPR_ADJUST_Pos (4UL)      /*!< ADJUST (Bit 4)                                        */
#define ADC_SMPR_ADJUST_Msk (0x70UL)   /*!< ADJUST (Bitfield-Mask: 0x07)                          */
#define ADC_SMPR_SMP_Pos (0UL)         /*!< SMP (Bit 0)                                           */
#define ADC_SMPR_SMP_Msk (0x7UL)       /*!< SMP (Bitfield-Mask: 0x07)                             */
/* ==========================================================  TR  =========================================================== */
#define ADC_TR_HT_Pos (16UL)        /*!< HT (Bit 16)                                           */
#define ADC_TR_HT_Msk (0xfff0000UL) /*!< HT (Bitfield-Mask: 0xfff)                             */
#define ADC_TR_LT_Pos (0UL)         /*!< LT (Bit 0)                                            */
#define ADC_TR_LT_Msk (0xfffUL)     /*!< LT (Bitfield-Mask: 0xfff)                             */
/* ========================================================  CHSELR  ========================================================= */
#define ADC_CHSELR_CHSELR_Pos (0UL)      /*!< CHSELR (Bit 0)                                        */
#define ADC_CHSELR_CHSELR_Msk (0xffffUL) /*!< CHSELR (Bitfield-Mask: 0xffff)                        */
/* ==========================================================  DR  =========================================================== */
#define ADC_DR_DATA_Pos (0UL)      /*!< DATA (Bit 0)                                          */
#define ADC_DR_DATA_Msk (0xffffUL) /*!< DATA (Bitfield-Mask: 0xffff)                          */
/* =========================================================  TRIM  ========================================================== */
#define ADC_TRIM_VOS_TRIM_Pos (16UL)       /*!< VOS_TRIM (Bit 16)                                     */
#define ADC_TRIM_VOS_TRIM_Msk (0xff0000UL) /*!< VOS_TRIM (Bitfield-Mask: 0xff)                        */
#define ADC_TRIM_GAIN_TRIM_Pos (0UL)       /*!< GAIN_TRIM (Bit 0)                                     */
#define ADC_TRIM_GAIN_TRIM_Msk (0xffUL)    /*!< GAIN_TRIM (Bitfield-Mask: 0xff)                       */
/* ========================================================  EXTCFG  ========================================================= */
#define ADC_EXTCFG_EXTSE_Pos (27UL)          /*!< EXTSE (Bit 27)                                        */
#define ADC_EXTCFG_EXTSE_Msk (0xf8000000UL)  /*!< EXTSE (Bitfield-Mask: 0x1f)                           */
#define ADC_EXTCFG_EXTSELG4_Pos (20UL)       /*!< EXTSELG4 (Bit 20)                                     */
#define ADC_EXTCFG_EXTSELG4_Msk (0x300000UL) /*!< EXTSELG4 (Bitfield-Mask: 0x03)                        */
#define ADC_EXTCFG_EXTSELG3_Pos (18UL)       /*!< EXTSELG3 (Bit 18)                                     */
#define ADC_EXTCFG_EXTSELG3_Msk (0xc0000UL)  /*!< EXTSELG3 (Bitfield-Mask: 0x03)                        */
#define ADC_EXTCFG_EXTSELG2_Pos (16UL)       /*!< EXTSELG2 (Bit 16)                                     */
#define ADC_EXTCFG_EXTSELG2_Msk (0x30000UL)  /*!< EXTSELG2 (Bitfield-Mask: 0x03)                        */
#define ADC_EXTCFG_EXTSELG1_Pos (14UL)       /*!< EXTSELG1 (Bit 14)                                     */
#define ADC_EXTCFG_EXTSELG1_Msk (0xc000UL)   /*!< EXTSELG1 (Bitfield-Mask: 0x03)                        */
#define ADC_EXTCFG_EXTSELG0_Pos (12UL)       /*!< EXTSELG0 (Bit 12)                                     */
#define ADC_EXTCFG_EXTSELG0_Msk (0x3000UL)   /*!< EXTSELG0 (Bitfield-Mask: 0x03)                        */
#define ADC_EXTCFG_EXTDTG_Pos (4UL)          /*!< EXTDTG (Bit 4)                                        */
#define ADC_EXTCFG_EXTDTG_Msk (0xff0UL)      /*!< EXTDTG (Bitfield-Mask: 0xff)                          */
#define ADC_EXTCFG_OP_MODE_Pos (3UL)         /*!< OP_MODE (Bit 3)                                       */
#define ADC_EXTCFG_OP_MODE_Msk (0x8UL)       /*!< OP_MODE (Bitfield-Mask: 0x01)                         */
#define ADC_EXTCFG_EDEG_MODE_Pos (2UL)       /*!< EDEG_MODE (Bit 2)                                     */
#define ADC_EXTCFG_EDEG_MODE_Msk (0x4UL)     /*!< EDEG_MODE (Bitfield-Mask: 0x01)                       */
#define ADC_EXTCFG_EXTEN_Pos (0UL)           /*!< EXTEN (Bit 0)                                         */
#define ADC_EXTCFG_EXTEN_Msk (0x3UL)         /*!< EXTEN (Bitfield-Mask: 0x03)                           */
/* ========================================================  TESTCFG  ======================================================== */
#define ADC_TESTCFG_PD_ADC_Pos (14UL)     /*!< PD_ADC (Bit 14)                                       */
#define ADC_TESTCFG_PD_ADC_Msk (0x4000UL) /*!< PD_ADC (Bitfield-Mask: 0x01)                          */
#define ADC_TESTCFG_PD_REF_Pos (13UL)     /*!< PD_REF (Bit 13)                                       */
#define ADC_TESTCFG_PD_REF_Msk (0x2000UL) /*!< PD_REF (Bitfield-Mask: 0x01)                          */
#define ADC_TESTCFG_PD_SH2_Pos (12UL)     /*!< PD_SH2 (Bit 12)                                       */
#define ADC_TESTCFG_PD_SH2_Msk (0x1000UL) /*!< PD_SH2 (Bitfield-Mask: 0x01)                          */
#define ADC_TESTCFG_PD_SH1_Pos (11UL)     /*!< PD_SH1 (Bit 11)                                       */
#define ADC_TESTCFG_PD_SH1_Msk (0x800UL)  /*!< PD_SH1 (Bitfield-Mask: 0x01)                          */
#define ADC_TESTCFG_RMD_Pos (10UL)        /*!< RMD (Bit 10)                                          */
#define ADC_TESTCFG_RMD_Msk (0x400UL)     /*!< RMD (Bitfield-Mask: 0x01)                             */
#define ADC_TESTCFG_RTA_Pos (9UL)         /*!< RTA (Bit 9)                                           */
#define ADC_TESTCFG_RTA_Msk (0x200UL)     /*!< RTA (Bitfield-Mask: 0x01)                             */
#define ADC_TESTCFG_RT_Pos (6UL)          /*!< RT (Bit 6)                                            */
#define ADC_TESTCFG_RT_Msk (0x1c0UL)      /*!< RT (Bitfield-Mask: 0x07)                              */
#define ADC_TESTCFG_RI_Pos (2UL)          /*!< RI (Bit 2)                                            */
#define ADC_TESTCFG_RI_Msk (0x3cUL)       /*!< RI (Bitfield-Mask: 0x0f)                              */
#define ADC_TESTCFG_TT_Pos (1UL)          /*!< TT (Bit 1)                                            */
#define ADC_TESTCFG_TT_Msk (0x2UL)        /*!< TT (Bitfield-Mask: 0x01)                              */
#define ADC_TESTCFG_TEST_Pos (0UL)        /*!< TEST (Bit 0)                                          */
#define ADC_TESTCFG_TEST_Msk (0x1UL)      /*!< TEST (Bitfield-Mask: 0x01)                            */
  /*  Function used to set the ADC configuration to the default reset state *****/
  void ADC_DeInit(ADC_TypeDef *ADCx); //����adʱ��

  /* Initialization and Configuration functions *********************************/
  void ADC_Init(ADC_TypeDef *ADCx, ADC_InitTypeDef *ADC_InitStruct); //��ʼ��adc ����12��������Ҫ����
  void ADC_StructInit(ADC_InitTypeDef *ADC_InitStruct);              //ADC �����ṹ���ֵ����
  void ADC_Cmd(ADC_TypeDef *ADCx, FunctionalState NewState);         //ʹ��ADC

  /* Power saving functions *****************************************************/
  void ADC_AutoPowerOffCmd(ADC_TypeDef *ADCx, FunctionalState NewState); //adc �Զ�����ʹ�ܺ���

  /* Analog Watchdog configuration functions ************************************/
  void ADC_AnalogWatchdogCmd(ADC_TypeDef *ADCx, FunctionalState NewState);                                   //ADCģ�⿪�Ź�
  void ADC_AnalogWatchdogThresholdsConfig(ADC_TypeDef *ADCx, uint16_t HighThreshold, uint16_t LowThreshold); //ģ�⿴�Ź���ֵ
  void ADC_AnalogWatchdogSingleChannelConfig(ADC_TypeDef *ADCx, uint32_t ADC_AnalogWatchdog_Channel);        //��ͨ�����Ź�ѡ��
  void ADC_AnalogWatchdogSingleChannelCmd(ADC_TypeDef *ADCx, FunctionalState NewState);                      //��ͨ�����Ź�ʹ��

  /* Temperature Sensor , Vrefint and Vbat management function ******************/
  void ADC_TempSensorCmd(FunctionalState NewState); //�¶ȴ���������ʹ��
  void ADC_VrefintCmd(FunctionalState NewState);    //�ڲ���ѹ����ʹ��

  /* Channels Configuration functions *******************************************/
  void ADC_ChannelConfig(ADC_TypeDef *ADCx, uint32_t ADC_Channel, uint32_t ADC_ConverTime, uint32_t ADC_AdjustTime, uint32_t ADC_SampleTime);
  //ͨ������ʱ������

  void ADC_StopOfConversion(ADC_TypeDef *ADCx);       //ֹͣADCת��
  void ADC_StartOfConversion(ADC_TypeDef *ADCx);      //��ʼadcת��
  uint16_t ADC_GetConversionValue(ADC_TypeDef *ADCx); //��ȡת�����
  void ADC_CloseAdc(ADC_TypeDef *ADCx);               //�ر�ADCģ��

  void ADC_VrefintSelect(ADC_TypeDef *ADCx, uint32_t ADC_Vref); //ADC�ο���ѹѡ��

  /* Interrupts and flags management functions **********************************/
  void ADC_ITConfig(ADC_TypeDef *ADCx, uint32_t ADC_IT, FunctionalState NewState); //ADC�ж�ʹ��
  FlagStatus ADC_GetFlagStatus(ADC_TypeDef *ADCx, uint32_t ADC_FLAG);              //ADC״̬��־λ��ȡ
  void ADC_ClearFlag(ADC_TypeDef *ADCx, uint32_t ADC_FLAG);                        //��ADC״̬��־λ
  ITStatus ADC_GetITStatus(ADC_TypeDef *ADCx, uint32_t ADC_IT);                    //��ȡ�жϱ�־λ
  void ADC_ClearITPendingBit(ADC_TypeDef *ADCx, uint32_t ADC_IT);                  //����жϱ�־λ

#ifdef __cplusplus
}
#endif
#endif
