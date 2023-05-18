// !!! Auto generated, Dont Modify !!!
#define FPGA
#define FPGA_XILINX
//#define FPGA_XC7A
#define FPGA_XC7K


/***********************************************************
 **** Global Chip Definitions & Configurations
***********************************************************/

/******************* Chip Mode Specific *******************/
#ifndef FPGA
    #ifndef ASIC
        #define ASIC
    #endif // ASIC
#endif // FPGA

/******************** Platform Specific *******************/
#define PLATFORM_BASELINE
//#define PLATFORM_STANDARD

/********************* eFlash Specific ********************/
//#define SOC_EFLS_64_BITS
#define SOC_EFLS_SECTOR_WIDTH           9   // 512B

#ifdef SOC_EFLS_64_BITS
    #define SOC_EFLS_JLFLS016K39DA          // non shrink

    #define SOC_EFLS_BIT_WIDTH          64
    #define SOC_EFLS_SIZE_WIDTH         17  // 128KB
    // First NVR for Option Bytes, Last NVR for Foundry,
    // The Other NVRs for System Memory
    #define SOC_EFLS_NVR_NUM            11

#else // SOC_EFLS_32_BITS
    #ifdef PLATFORM_BASELINE
      //#define SOC_EFLS_JLFLS008K29DA      // non shrink
        #define SOC_EFLS_JLFLS016K29DG      // non shrink

        #define SOC_EFLS_BIT_WIDTH      32
        #ifdef SOC_EFLS_JLFLS008K29DA
            #define SOC_EFLS_SIZE_WIDTH 15  // 32KB
        #elif defined SOC_EFLS_JLFLS016K29DG
            #define SOC_EFLS_SIZE_WIDTH 16  // 64KB
        #else
            !!! Error : Non Defined !!!
        #endif // SOC_EFLS_JLFLS008K29DA
        // First NVR for Option Bytes, Last NVR for Foundry,
        // The Other NVRs for System Memory
        #define SOC_EFLS_NVR_NUM        5
      //#define SOC_EFLS_CFG_ITF

    #else // PLATFORM_STANDARD
      //#define SOC_EFLS_JLFLS032K29DG      // non shrink
        #define SOC_EFLS_JLFLE032K29DG      // shrink
    
        #define SOC_EFLS_SIZE_WIDTH     17  // 128KB
        // First NVR for Option Bytes, Last NVR for Foundry,
        // The Other NVRs for System Memory
        #ifdef SOC_EFLS_JLFLS032K29DG
            #define SOC_EFLS_NVR_NUM    5
        #elif defined SOC_EFLS_JLFLE032K29DG
            #define SOC_EFLS_NVR_NUM    8
            #define SOC_EFLS_CFG_ITF
        #else
            !!! Error : Non Defined !!!
        #endif // SOC_EFLS_JLFLS032K29DG
    #endif // PLATFORM_BASELINE
#endif // SOC_EFLS_64_BITS

/********************* SRAM Specific ********************/
#ifdef PLATFORM_BASELINE
    #define SOC_RAM_SIZE_WIDTH      12  // 4KB
    #define SOC_RAM_DUAL_BANK
#else // PLATFORM_STANDARD
    #define SOC_RAM_SIZE_WIDTH      13  // 8KB
    #define SOC_RAM_DUAL_BANK
#endif // PLATFORM_BASELINE

/********************** MCU Specific **********************/
#define MCU_CM0_ON
//#define MCU_BITBAND_ON

/******************** GPIO Specific *********************/
// GPIO Port0 Switch
#define GPIO_PORT0_ON
// GPIO Port Number, max 16 Per GPIO Group
#define GPIO_PORT0_NUM          16

// GPIO Port1 Switch
#define GPIO_PORT1_ON
#ifdef PLATFORM_BASELINE
    #define GPIO_PORT1_NUM       8
#else // PLATFORM_STANDARD
    #define GPIO_PORT1_NUM      16
#endif // PLATFORM_BASELINE

// GPIO Port2 Switch
#ifndef PLATFORM_BASELINE
    #define GPIO_PORT2_ON
#endif // PLATFORM_BASELINE
#define GPIO_PORT2_NUM          16

// GPIO Port3 Switch
//#define GPIO_PORT3_ON
#define GPIO_PORT3_NUM          16

// GPIO Port4 Switch
//#define GPIO_PORT4_ON
#define GPIO_PORT4_NUM          16

// GPIO Port5 Switch
#define GPIO_PORT5_ON
#define GPIO_PORT5_NUM           8

/******************** MODULE Specific *********************/
// External SPI Flash Boot Switch
//#define MODULE_SPIBOOT_ON

// PPU Switch
//#define MODULE_PPU_ON

// TIM1 Switch
#define MODULE_TIM1_ON

// TIM3 Switch
#define MODULE_TIM3_ON

// TIM6 Switch
#define MODULE_TIM6_ON

// TIM14 Switch
#define MODULE_TIM14_ON

// TIM15 Switch
#define MODULE_TIM15_ON

// TIM16 Switch
#define MODULE_TIM16_ON

// TIM17 Switch
#define MODULE_TIM17_ON

// MULT Switch
//#define MODULE_MULT_ON

// DIV Switch
#define MODULE_DIV_ON

// CRC Switch
#define MODULE_CRC_ON

// CORDIC Switch
#ifndef PLATFORM_BASELINE
    #define MODULE_CORDIC_ON
#endif // PLATFORM_BASELINE

// UART2 Switch
//#define MODULE_UART2_ON

// UART3 Switch
#define MODULE_UART3_ON

// UART4 Switch
#ifndef PLATFORM_BASELINE
    #define MODULE_UART4_ON
#endif // PLATFORM_BASELINE

// UART5 Switch
#ifndef PLATFORM_BASELINE
    #define MODULE_UART5_ON
#endif // PLATFORM_BASELINE

// I2C1 Switch
#ifndef PLATFORM_BASELINE
    #define MODULE_I2C1_ON
#endif // PLATFORM_BASELINE

// SSP1 Switch
//#define MODULE_SSP1_ON

// SSP2 Switch
#ifndef PLATFORM_BASELINE
    #define MODULE_SSP2_ON
#endif // PLATFORM_BASELINE

// SSP3 Switch
//#define MODULE_SSP3_ON

// CAN Switch
#ifndef PLATFORM_BASELINE
    #define MODULE_CAN_ON
#endif // PLATFORM_BASELINE

// LCD Switch
//#define MODULE_LCD_ON

// PLC Switch
//#define MODULE_PLC_ON

// ADC Switch
#define MODULE_ADC_ON

// RTC Switch
#define MODULE_RTC_ON

/*********** SOC Bus Matrix Slave Address Space ***********/
// Number of Master and Slave
#define SOC_MST_NUM                 6
#define SOC_SLV_NUM                 9

// Slave Address Space
#define SOC_SLV1_ADDR_STR           0x08000000        // EFLASH
//#define SOC_SLV1_ADDR_END         (SOC_SLV1_ADDR_STR + (1 << SOC_EFLS_SIZE_WIDTH) + SOC_EFLS_NVR_NUM * (1 << SOC_EFLS_SECTOR_WIDTH))
#define SOC_SLV1_ADDR_END           (SOC_SLV1_ADDR_STR + (2 << SOC_EFLS_SIZE_WIDTH))
#define SOC_SLV2_ADDR_STR           0x28000000        // Reserved
#define SOC_SLV2_ADDR_END           0x28000000
#ifdef SOC_RAM_DUAL_BANK
    #define SOC_SLV3_ADDR_STR       0x20000000        // RAM0
    #define SOC_SLV3_ADDR_END       (SOC_SLV3_ADDR_STR + (1 << (SOC_RAM_SIZE_WIDTH - 1)))
    #define SOC_SLV4_ADDR_STR       SOC_SLV3_ADDR_END  // RAM1
    #define SOC_SLV4_ADDR_END       (SOC_SLV4_ADDR_STR + (1 << (SOC_RAM_SIZE_WIDTH - 1)))
#else
    #define SOC_SLV3_ADDR_STR       0x20000000        // RAM0
    #define SOC_SLV3_ADDR_END       (SOC_SLV3_ADDR_STR + (1 << SOC_RAM_SIZE_WIDTH))
    #define SOC_SLV4_ADDR_STR       SOC_SLV3_ADDR_END  // RAM1
    #define SOC_SLV4_ADDR_END       SOC_SLV4_ADDR_STR
#endif // SOC_RAM_DUAL_BANK
#define SOC_SLV5_ADDR_STR           0x48000000        // HPS0
#define SOC_SLV5_ADDR_END           0x48008000        
#define SOC_SLV6_ADDR_STR           0x48010000        // HPS1
#define SOC_SLV6_ADDR_END           0x48018000        
#define SOC_SLV7_ADDR_STR           0x40000000        // PPS0
#define SOC_SLV7_ADDR_END           0x40010000        
#define SOC_SLV8_ADDR_STR           0x40010000        // PPS1
#define SOC_SLV8_ADDR_END           0x40020000        
#define SOC_SLV9_ADDR_STR           0x50000000        // Reserved
#define SOC_SLV9_ADDR_END           0x50000000


/******************* eFlash Address Space ******************/
#define EFLS_MAIN_ADDR_STR           SOC_SLV1_ADDR_STR
#define EFLS_MAIN_ADDR_END          (EFLS_MAIN_ADDR_STR   + (1 << SOC_EFLS_SIZE_WIDTH))
#define EFLS_OPTION_ADDR_STR         EFLS_MAIN_ADDR_END
#define EFLS_OPTION_ADDR_END        (EFLS_OPTION_ADDR_STR + (1 << SOC_EFLS_SECTOR_WIDTH))
#define EFLS_SYSTEM_ADDR_STR         EFLS_OPTION_ADDR_END
#define EFLS_SYSTEM_ADDR_END        (EFLS_SYSTEM_ADDR_STR + (SOC_EFLS_NVR_NUM - 2) * (1 << SOC_EFLS_SECTOR_WIDTH))

/******************* Sram Address Space *******************/
    #define SRAM0_ADDR_STR      SOC_SLV3_ADDR_STR
    #define SRAM0_ADDR_END      SOC_SLV3_ADDR_END
#ifdef SOC_RAM_DUAL_BANK
    #define SRAM1_ADDR_STR      SOC_SLV4_ADDR_STR
    #define SRAM1_ADDR_END      SOC_SLV4_ADDR_END
#endif // SOC_RAM_DUAL_BANK

/******************* HPS0 Address Space *******************/
#define HPS0_SLV_NUM            8

#define HPS0_SLV_MAP_GPIO       0
#define HPS0_SLV_MAP_RSV1       1
#define HPS0_SLV_MAP_RSV2       2
#define HPS0_SLV_MAP_RSV3       3
#define HPS0_SLV_MAP_DMAC       4
#define HPS0_SLV_MAP_RSV5       5
#define HPS0_SLV_MAP_RSV6       6
#define HPS0_SLV_MAP_SYSCTRL    7

#define HPS0_ADDR_STR           SOC_SLV5_ADDR_STR
#define HPS0_ADDR_END           SOC_SLV5_ADDR_END
#define GPIO_ADDR_STR           (HPS0_ADDR_STR + (HPS0_SLV_MAP_GPIO << 12))
#define GPIO_ADDR_END           (GPIO_ADDR_STR + (1 << 12))
#define DMAC_ADDR_STR           (HPS0_ADDR_STR + (HPS0_SLV_MAP_DMAC << 12))
#define DMAC_ADDR_END           (DMAC_ADDR_STR + (1 << 12))
#define SYSCTRL_ADDR_STR        (HPS0_ADDR_STR + (HPS0_SLV_MAP_SYSCTRL << 12))
#define SYSCTRL_ADDR_END        (SYSCTRL_ADDR_STR + (1 << 12))

/******************* HPS1 Address Space *******************/
#define HPS1_SLV_NUM            8

#ifdef MODULE_CORDIC_ON
    #define HPS1_SLV_MAP_CORDIC 0
#else // MODULE_CORDIC_ON
    #define HPS1_SLV_MAP_RSV0   0
#endif // MODULE_CORDIC_ON

#ifdef MODULE_CRC_ON
    #define HPS1_SLV_MAP_CRC    1
#else // MODULE_CRC_ON
    #define HPS1_SLV_MAP_RSV1   1
#endif // MODULE_CRC_ON

#ifdef MCU_DUAL_CM0
    #define HPS1_SLV_MAP_CXC    2
#else
    #define HPS1_SLV_MAP_RSV2   2
#endif // MCU_DUAL_CM0

#ifdef MODULE_MULT_ON
    #define HPS1_SLV_MAP_MULT   3
#else // MODULE_MULT_ON
    #define HPS1_SLV_MAP_RSV3   3
#endif // MODULE_MULT_ON

#ifdef MODULE_DIV_ON
    #define HPS1_SLV_MAP_DIV    4
#else // MODULE_DIV_ON
    #define HPS1_SLV_MAP_RSV4   4
#endif // MODULE_DIV_ON

#define HPS1_SLV_MAP_RSV5       5
#define HPS1_SLV_MAP_RSV6       6
#define HPS1_SLV_MAP_RSV7       7

#define HPS1_ADDR_STR           SOC_SLV6_ADDR_STR
#define HPS1_ADDR_END           SOC_SLV6_ADDR_END
#ifdef MODULE_CORDIC_ON
    #define CORDIC_ADDR_STR     (HPS1_ADDR_STR + (HPS1_SLV_MAP_CORDIC << 12))
    #define CORDIC_ADDR_END     (CORDIC_ADDR_STR + (1 << 12))
#endif // MODULE_CORDIC_ON
#ifdef MODULE_CRC_ON
    #define CRC_ADDR_STR        (HPS1_ADDR_STR + (HPS1_SLV_MAP_CRC << 12))
    #define CRC_ADDR_END        (CRC_ADDR_STR + (1 << 12))
#endif // MODULE_CRC_ON
#ifdef MCU_DUAL_CM0
    #define CXC_ADDR_STR        (HPS1_ADDR_STR + (HPS1_SLV_MAP_CXC << 12))
    #define CXC_ADDR_END        (CXC_ADDR_STR + (1 << 12))
#endif // MCU_DUAL_CM0
#ifdef MODULE_MULT_ON
    #define MULT_ADDR_STR       (HPS1_ADDR_STR + (HPS1_SLV_MAP_MULT << 12))
    #define MULT_ADDR_END       (MULT_ADDR_STR + (1 << 12))
#endif // MODULE_MULT_ON
#ifdef MODULE_DIV_ON
    #define DIV_ADDR_STR        (HPS1_ADDR_STR + (HPS1_SLV_MAP_DIV << 12))
    #define DIV_ADDR_END        (DIV_ADDR_STR + (1 << 12))
#endif // MODULE_DIV_ON

/******************* PPS0 Address Space *******************/
#define PPS0_SLV_NUM            16

#ifdef MODULE_UART3_ON
    #define PPS0_SLV_MAP_UART3  0
#else
    #define PPS0_SLV_MAP_RSV0   0
#endif // MODULE_UART3_ON
#ifdef MODULE_UART4_ON
    #define PPS0_SLV_MAP_UART4  1
#else
    #define PPS0_SLV_MAP_RSV1   1
#endif // MODULE_UART4_ON
#ifdef MODULE_UART5_ON
    #define PPS0_SLV_MAP_UART5  2
#else
    #define PPS0_SLV_MAP_RSV2   2
#endif // MODULE_UART5_ON
#ifdef MODULE_I2C1_ON
    #define PPS0_SLV_MAP_I2C1   3
#else
    #define PPS0_SLV_MAP_RSV3   3
#endif // MODULE_I2C1_ON
#define PPS0_SLV_MAP_RSV4       4
#ifdef MODULE_CAN_ON
#define PPS0_SLV_MAP_CAN        5
#else
    #define PPS0_SLV_MAP_RSV5   5
#endif // MODULE_CAN_ON
#ifdef MODULE_SSP2_ON
    #define PPS0_SLV_MAP_SSP2   6
#else
    #define PPS0_SLV_MAP_RSV6   6
#endif // MODULE_SSP2_ON
#ifdef MODULE_SSP3_ON
    #define PPS0_SLV_MAP_SSP3   7
#else
    #define PPS0_SLV_MAP_RSV7   7
#endif // MODULE_SSP3_ON
#ifdef MODULE_LCD_ON
    #define PPS0_SLV_MAP_LCD    8
#else
    #define PPS0_SLV_MAP_RSV8   8
#endif // MODULE_LCD_ON
#ifdef MODULE_TIM6_ON
    #define PPS0_SLV_MAP_TIM6   9
#else
    #define PPS0_SLV_MAP_RSV9   9
#endif // MODULE_TIM6_ON
#ifdef MODULE_TIM14_ON
    #define PPS0_SLV_MAP_TIM14  10
#else
#define PPS0_SLV_MAP_RSV10      10
#endif // MODULE_TIM14_ON
#ifdef MODULE_TIM3_ON
    #define PPS0_SLV_MAP_TIM3   11
#else
    #define PPS0_SLV_MAP_RSV11  11
#endif // MODULE_TIM3_ON
#define PPS0_SLV_MAP_RSV12      12
#define PPS0_SLV_MAP_WWDG       13
#define PPS0_SLV_MAP_RSV14      14
#ifdef MODULE_PLC_ON
    #define PPS0_SLV_MAP_PLC    15
#else
    #define PPS0_SLV_MAP_RSV15  15
#endif // MODULE_PLC_ON

#define PPS0_ADDR_STR           SOC_SLV7_ADDR_STR
#define PPS0_ADDR_END           SOC_SLV7_ADDR_END
#ifdef MODULE_UART3_ON
    #define UART3_ADDR_STR      (PPS0_ADDR_STR + (PPS0_SLV_MAP_UART3 << 12))
    #define UART3_ADDR_END      (UART3_ADDR_STR + (1 << 12))
#endif // MODULE_UART3_ON
#ifdef MODULE_UART4_ON
    #define UART4_ADDR_STR      (PPS0_ADDR_STR + (PPS0_SLV_MAP_UART4 << 12))
    #define UART4_ADDR_END      (UART4_ADDR_STR + (1 << 12))
#endif // MODULE_UART4_ON
#ifdef MODULE_UART5_ON
    #define UART5_ADDR_STR      (PPS0_ADDR_STR + (PPS0_SLV_MAP_UART5 << 12))
    #define UART5_ADDR_END      (UART5_ADDR_STR + (1 << 12))
#endif // MODULE_UART5_ON
#ifdef MODULE_I2C1_ON
    #define I2C1_ADDR_STR       (PPS0_ADDR_STR + (PPS0_SLV_MAP_I2C1 << 12))
    #define I2C1_ADDR_END       (I2C1_ADDR_STR + (1 << 12))
#endif // MODULE_I2C1_ON
#ifdef MODULE_CAN_ON
    #define CAN_ADDR_STR        (PPS0_ADDR_STR + (PPS0_SLV_MAP_CAN << 12))
    #define CAN_ADDR_END        (CAN_ADDR_STR + (1 << 12))
#endif // MODULE_CAN_ON
#ifdef MODULE_SSP2_ON
    #define SSP2_ADDR_STR       (PPS0_ADDR_STR + (PPS0_SLV_MAP_SSP2 << 12))
    #define SSP2_ADDR_END       (SSP2_ADDR_STR + (1 << 12))
#endif // MODULE_SSP2_ON
#ifdef MODULE_SSP3_ON
    #define SSP3_ADDR_STR       (PPS0_ADDR_STR + (PPS0_SLV_MAP_SSP3 << 12))
    #define SSP3_ADDR_END       (SSP3_ADDR_STR + (1 << 12))
#endif // MODULE_SSP3_ON
#ifdef MODULE_LCD_ON
    #define LCD_ADDR_STR        (PPS0_ADDR_STR + (PPS0_SLV_MAP_LCD << 12))
    #define LCD_ADDR_END        (LCD_ADDR_STR + (1 << 12))
#endif // MODULE_LCD_ON
#ifdef MODULE_TIM6_ON
    #define TIM6_ADDR_STR       (PPS0_ADDR_STR + (PPS0_SLV_MAP_TIM6 << 12))
    #define TIM6_ADDR_END       (TIM6_ADDR_STR + (1 << 12))
#endif // MODULE_TIM6_ON
#ifdef MODULE_TIM14_ON
    #define TIM14_ADDR_STR      (PPS0_ADDR_STR + (PPS0_SLV_MAP_TIM14 << 12))
    #define TIM14_ADDR_END      (TIM14_ADDR_STR + (1 << 12))
#endif // MODULE_TIM14_ON
#ifdef MODULE_TIM3_ON
    #define TIM3_ADDR_STR       (PPS0_ADDR_STR + (PPS0_SLV_MAP_TIM3 << 12))
    #define TIM3_ADDR_END       (TIM3_ADDR_STR + (1 << 12))
#endif // MODULE_TIM3_ON
#define WWDG_ADDR_STR           (PPS0_ADDR_STR + (PPS0_SLV_MAP_WWDG << 12))
#define WWDG_ADDR_END           (WWDG_ADDR_STR + (1 << 12))
#ifdef MODULE_PLC_ON
    #define PLC_ADDR_STR        (PPS0_ADDR_STR + (PPS0_SLV_MAP_PLC << 12))
    #define PLC_ADDR_END        (PLC_ADDR_STR + (1 << 12))
#endif // MODULE_PLC_ON

/******************* PPS1 Address Space *******************/
#define PPS1_SLV_NUM            16

#ifdef MODULE_TIM1_ON
#define PPS1_SLV_MAP_TIM1       0
#else
    #define PPS1_SLV_MAP_RSV0   0
#endif // MODULE_TIM1_ON
#define PPS1_SLV_MAP_EXTI       1
#define PPS1_SLV_MAP_RSV2       2
#define PPS1_SLV_MAP_I2C0       3
#define PPS1_SLV_MAP_UART0      4
#define PPS1_SLV_MAP_UART1      5
#ifdef MODULE_UART2_ON
    #define PPS1_SLV_MAP_UART2  6
#else
    #define PPS1_SLV_MAP_RSV6   6
#endif // MODULE_UART2_ON
#define PPS1_SLV_MAP_CHIPCTRL   7
#define PPS1_SLV_MAP_SSP0       8
#ifdef MODULE_SSP1_ON
    #define PPS1_SLV_MAP_SSP1   9
#else
    #define PPS1_SLV_MAP_RSV9   9
#endif // MODULE_SSP1_ON
#define PPS1_SLV_MAP_ADC        10
#ifdef MODULE_TIM15_ON
    #define PPS1_SLV_MAP_TIM15  11
#else
    #define PPS1_SLV_MAP_RSV11  11
#endif // MODULE_TIM15_ON
#ifdef MODULE_TIM16_ON
    #define PPS1_SLV_MAP_TIM16  12
#else
    #define PPS1_SLV_MAP_RSV12  12
#endif // MODULE_TIM16_ON
#define PPS1_SLV_MAP_EFLS_CTRL  13
#ifdef MODULE_TIM17_ON
    #define PPS1_SLV_MAP_TIM17  14
#else
    #define PPS1_SLV_MAP_RSV14  14
#endif // MODULE_TIM17_ON
#define PPS1_SLV_MAP_RSV15      15

#define PPS1_ADDR_STR           SOC_SLV8_ADDR_STR
#define PPS1_ADDR_END           SOC_SLV8_ADDR_END
#ifdef MODULE_TIM1_ON
    #define TIM1_ADDR_STR       (PPS1_ADDR_STR + (PPS1_SLV_MAP_TIM1 << 12))
    #define TIM1_ADDR_END       (TIM1_ADDR_STR + (1 << 12))
#endif // MODULE_TIM1_ON
#define EXTI_ADDR_STR           (PPS1_ADDR_STR + (PPS1_SLV_MAP_EXTI << 12))
#define EXTI_ADDR_END           (EXTI_ADDR_STR + (1 << 12))
#define I2C0_ADDR_STR           (PPS1_ADDR_STR + (PPS1_SLV_MAP_I2C0 << 12))
#define I2C0_ADDR_END           (I2C0_ADDR_STR + (1 << 12))
#define UART0_ADDR_STR          (PPS1_ADDR_STR + (PPS1_SLV_MAP_UART0 << 12))
#define UART0_ADDR_END          (UART0_ADDR_STR + (1 << 12))
#define UART1_ADDR_STR          (PPS1_ADDR_STR + (PPS1_SLV_MAP_UART1 << 12))
#define UART1_ADDR_END          (UART1_ADDR_STR + (1 << 12))
#ifdef MODULE_UART2_ON
    #define UART2_ADDR_STR      (PPS1_ADDR_STR + (PPS1_SLV_MAP_UART2 << 12))
    #define UART2_ADDR_END      (UART2_ADDR_STR + (1 << 12))
#endif // MODULE_UART2_ON
#define CHIPCTRL_ADDR_STR       (PPS1_ADDR_STR + (PPS1_SLV_MAP_CHIPCTRL << 12))
#define CHIPCTRL_ADDR_END       (CHIPCTRL_ADDR_STR + (1 << 10))
#define IWDG_ADDR_STR           (CHIPCTRL_ADDR_END)
#define IWDG_ADDR_END           (IWDG_ADDR_STR + (1 << 10))
#define RTC_ADDR_STR            (IWDG_ADDR_END)
#define RTC_ADDR_END            (RTC_ADDR_STR + (1 << 10))
#define ANACTRL_ADDR_STR        (RTC_ADDR_END)
#define ANACTRL_ADDR_END        (ANACTRL_ADDR_STR + (1 << 10))
#define SSP0_ADDR_STR           (PPS1_ADDR_STR + (PPS1_SLV_MAP_SSP0 << 12))
#define SSP0_ADDR_END           (SSP0_ADDR_STR + (1 << 12))
#ifdef MODULE_SSP1_ON
    #define SSP1_ADDR_STR       (PPS1_ADDR_STR + (PPS1_SLV_MAP_SSP1 << 12))
    #define SSP1_ADDR_END       (SSP1_ADDR_STR + (1 << 12))
#endif // MODULE_SSP1_ON
#define ADC_ADDR_STR            (PPS1_ADDR_STR + (PPS1_SLV_MAP_ADC << 12))
#define ADC_ADDR_END            (ADC_ADDR_STR + (1 << 12))
#ifdef MODULE_TIM15_ON
    #define TIM15_ADDR_STR      (PPS1_ADDR_STR + (PPS1_SLV_MAP_TIM15 << 12))
    #define TIM15_ADDR_END      (TIM15_ADDR_STR + (1 << 12))
#endif // MODULE_TIM15_ON
#ifdef MODULE_TIM16_ON
    #define TIM16_ADDR_STR      (PPS1_ADDR_STR + (PPS1_SLV_MAP_TIM16 << 12))
    #define TIM16_ADDR_END      (TIM16_ADDR_STR + (1 << 12))
#endif // MODULE_TIM16_ON
#define EFLS_CTRL_ADDR_STR      (PPS1_ADDR_STR + (PPS1_SLV_MAP_EFLS_CTRL << 12))
#define EFLS_CTRL_ADDR_END      (EFLS_CTRL_ADDR_STR + (1 << 12))
#ifdef MODULE_TIM17_ON
    #define TIM17_ADDR_STR      (PPS1_ADDR_STR + (PPS1_SLV_MAP_TIM17 << 12))
    #define TIM17_ADDR_END      (TIM17_ADDR_STR + (1 << 12))
#endif // MODULE_TIM17_ON

