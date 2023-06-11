/** Define to prevent recursive inclusion -------------------------------------*/
#ifndef LCM32F037_RCC_H
#define LCM32F037_RCC_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "lcm32f037.h"
#include "lcm32f037_conf.h"

     typedef struct
     {
          uint32_t HSI_Frequency;
          uint32_t LSI_Frequency;
          uint32_t HSE_Frequency;
          uint32_t LSE_Frequency;
          uint32_t SYSCLK_IN_Frequency; // system clock frequency before prescale
          uint32_t SYSCLK_Frequency;    // system clock frqeuency
          uint32_t HCLK_Frequency;      // AHB clock frequency
          uint32_t PCLK0_Frequency;     // APB0 clock frequency
          uint32_t PCLK1_Frequency;     // APB1 clock frequency
          uint32_t PLL_Frequency;       // PLL clock frequency;
          uint32_t UART0_Frequency;     // APB1 bridge.
          uint32_t UART1_Frequency;     // APB1 bridge.
          uint32_t I2C0_Frequency;      // APB1 bridge.

          uint32_t SPI0_Frequency; // APB1 bridge.
          uint32_t SPI2_Frequency; // APB0 bridge.

     } RCC_ClocksTypeDef;

     /** @defgroup RCC_HSE_configuration        @zhang
      * @{
      */

#define RCC_HSE_OFF (0)
#define RCC_HSE_ON (1)
#define RCC_HSE_Bypass (2)
#define IS_RCC_HSE(HSE) (((HSE) == RCC_HSE_OFF) || ((HSE) == RCC_HSE_ON) || \
                         ((HSE) == RCC_HSE_Bypass))

     /**
      * @}
      */

     /** @defgroup RCC_PLL_Clock_Source     @zhang
      * @{
      */

#define RCC_PLLSource_RCH 0
#define RCC_PLLSource_OSCH 1

#define IS_RCC_PLL_SOURCE(SOURCE) (((SOURCE) == RCC_PLLSource_RCH) || \
                                   ((SOURCE) == RCC_PLLSource_OSCH))
     /**
      * @}
      */

     /** @defgroup RCC_PLL_Multiplication_Factor   @zhang
      * @{
      */

#define RCC_PLLMul_OD_DIV1 (0UL << 12)
#define RCC_PLLMul_OD_DIV2 (1UL << 12)

#define RCC_PLLMul_DM_DIV1 (0UL << 8)
#define RCC_PLLMul_DM_DIV2 (1UL << 8)
#define RCC_PLLMul_DM_DIV3 (2UL << 8)
#define RCC_PLLMul_DM_DIV4 (3UL << 8)

#define RCC_PLLMul_DN_DIV1 (0UL << 2)
#define RCC_PLLMul_DN_DIV2 (1UL << 2)
#define RCC_PLLMul_DN_DIV3 (2UL << 2)
#define RCC_PLLMul_DN_DIV4 (3UL << 2)
#define RCC_PLLMul_DN_DIV5 (4UL << 2)
#define RCC_PLLMul_DN_DIV6 (5UL << 2)
#define RCC_PLLMul_DN_DIV7 (6UL << 2)
#define RCC_PLLMul_DN_DIV8 (7UL << 2)
#define RCC_PLLMul_DN_DIV9 (8UL << 2)
#define RCC_PLLMul_DN_DIV10 (9UL << 2)
#define RCC_PLLMul_DN_DIV11 (10UL << 2)
#define RCC_PLLMul_DN_DIV12 (11UL << 2)
#define RCC_PLLMul_DN_DIV13 (12UL << 2)
#define RCC_PLLMul_DN_DIV14 (13UL << 2)
#define RCC_PLLMul_DN_DIV15 (14UL << 2)
#define RCC_PLLMul_DN_DIV16 (15UL << 2)
#define RCC_PLLMul_DN_DIV17 (16UL << 2)
#define RCC_PLLMul_DN_DIV18 (17UL << 2)
#define RCC_PLLMul_DN_DIV19 (18UL << 2)
#define RCC_PLLMul_DN_DIV20 (19UL << 2)
#define RCC_PLLMul_DN_DIV21 (20UL << 2)
#define RCC_PLLMul_DN_DIV22 (21UL << 2)
#define RCC_PLLMul_DN_DIV23 (22UL << 2)
#define RCC_PLLMul_DN_DIV24 (23UL << 2)
#define RCC_PLLMul_DN_DIV25 (24UL << 2)
#define RCC_PLLMul_DN_DIV26 (25UL << 2)
#define RCC_PLLMul_DN_DIV27 (26UL << 2)
#define RCC_PLLMul_DN_DIV28 (27UL << 2)
#define RCC_PLLMul_DN_DIV29 (28UL << 2)
#define RCC_PLLMul_DN_DIV30 (29UL << 2)
#define RCC_PLLMul_DN_DIV31 (30UL << 2)
#define RCC_PLLMul_DN_DIV32 (31UL << 2)

     /**
      * @}
      */

     /** @defgroup RCC_System_Clock_Source   @zhang
      * @{
      */

#define RCC_SYSCLKSource_HSI 0
#define RCC_SYSCLKSource_HSE 1
#define RCC_SYSCLKSource_PLLCLK 2
#define RCC_SYSCLKSource_LSI 3
#define IS_RCC_SYSCLK_SOURCE(SOURCE) (((SOURCE) == RCC_SYSCLKSource_HSI) ||    \
                                      ((SOURCE) == RCC_SYSCLKSource_HSE) ||    \
                                      ((SOURCE) == RCC_SYSCLKSource_PLLCLK) || \
                                      ((SOURCE) == RCC_SYSCLKSource_LSI))

     /**
      * @}
      */

     /** @defgroup RCC_AHB_Clock_Source     @zhang
      * @{
      */

#define RCC_SYSCLK_Div1 0x00
#define RCC_SYSCLK_Div3 0x80
#define RCC_SYSCLK_Div5 0xC0
#define RCC_SYSCLK_Div(exp) ((exp << 1) - 1 + 0x40)
#define IS_RCC_HCLK(HCLK) (((HCLK) == RCC_SYSCLK_Div1) || ((HCLK) == RCC_SYSCLK_Div3) || \
                           ((HCLK) == RCC_SYSCLK_Div5) || ((HCLK) == RCC_SYSCLK_Div(exp)))
     /**
      * @}
      */

     /** @defgroup RCC_APB_Clock_Source   @zhang
      * @{
      */

#define RCC_HCLK_Div1 0
#define RCC_HCLK_Div2 1
#define RCC_HCLK_Div3 2
#define RCC_HCLK_Div4 3
#define RCC_HCLK_Div5 4
#define RCC_HCLK_Div6 5
#define RCC_HCLK_Div7 6
#define RCC_HCLK_Div8 7
#define RCC_HCLK_Div9 8
#define RCC_HCLK_Div10 9
#define RCC_HCLK_Div11 10
#define RCC_HCLK_Div12 11
#define RCC_HCLK_Div13 12
#define RCC_HCLK_Div14 13
#define RCC_HCLK_Div15 14
#define RCC_HCLK_Div16 15
#define IS_RCC_PCLK(PCLK) (((PCLK) < 16))
     /**
      * @}
      */

#define RCC_LSE_OFF 0
#define RCC_LSE_ON 1
#define RCC_LSE_Bypass 2
#define IS_RCC_LSE(RCC_LSE) ((RCC_LSE == RCC_LSE_OFF) || (RCC_LSE == RCC_LSE_ON) || (RCC_LSE == RCC_LSE_Bypass))

#define RCC_APB1Periph_FLASH (1UL << 16)
#define RCC_APB1Periph_EXTI (1UL << 6) /*ClkEnR2*/
#define RCC_APB1Periph_TIM1 (1UL << 19)
#define RCC_APB1Periph_I2C0 (1UL << 10)
#define RCC_APB1Periph_UART0 (1UL << 13)
#define RCC_APB1Periph_UART1 (1UL << 14)
#define RCC_APB1Periph_SSP0 (1UL << 12)
#define RCC_APB1Periph_ADC (1UL << 9)
#define RCC_APB1Periph_TIM15 (1UL << 28)
#define RCC_APB1Periph_TIM16 (1UL << 29)
#define RCC_APB1Periph_TIM17 (1UL << 30)
#define RCC_APB1Periph_ANACTRL (1UL << 5) /*ClkEnR2*/
#define IS_RCC_APB1_PERIPH(RCC_APB1Periph) ((RCC_APB1Periph == RCC_APB1Periph_EXTI) ||  \
                                            (RCC_APB1Periph == RCC_APB1Periph_TIM1) ||  \
                                            (RCC_APB1Periph == RCC_APB1Periph_I2C0) ||  \
                                            (RCC_APB1Periph == RCC_APB1Periph_UART0) || \
                                            (RCC_APB1Periph == RCC_APB1Periph_UART1) || \
                                            (RCC_APB1Periph == RCC_APB1Periph_UART2) || \
                                            (RCC_APB1Periph == RCC_APB1Periph_SSP0) ||  \
                                            (RCC_APB1Periph == RCC_APB1Periph_ADC) ||   \
                                            (RCC_APB1Periph == RCC_APB1Periph_TIM15) || \
                                            (RCC_APB1Periph == RCC_APB1Periph_TIM16) || \
                                            (RCC_APB1Periph == RCC_APB1Periph_TIM17) || \
                                            (RCC_APB1Periph == RCC_APB1Periph_ANACTRL))

#define RCC_FLAG_HSERDY 19
#define RCC_FLAG_HSIRDY 17
#define RCC_FLAG_LSERDY 18
#define RCC_FLAG_LSIRDY 16
#define IS_RCC_FLAG(RCC_FLAG) ((RCC_FLAG == RCC_FLAG_HSERDY) || \
                               (RCC_FLAG == RCC_FLAG_HSIRDY) || \
                               (RCC_FLAG == RCC_FLAG_LSERDY) || \
                               (RCC_FLAG == RCC_FLAG_LSIRDY))

#define RCC_IT_HSERDY 19
#define RCC_IT_HSIRDY 17
#define RCC_IT_LSERDY 18
#define RCC_IT_LSIRDY 16
#define IS_RCC_GET_IT(RCC_IT) ((RCC_IT == RCC_IT_HSERDY) || \
                               (RCC_IT == RCC_IT_HSIRDY) || \
                               (RCC_IT == RCC_IT_LSERDY) || \
                               (RCC_IT == RCC_IT_LSIRDY))

#define RCC_IT_LSI (1)
#define RCC_IT_LSE (4)
#define RCC_IT_HSI (2)
#define RCC_IT_HSE (8)
#define RCC_IT_PLL (16)
#define RCC_IT_CLXMUXERR (1UL << 5)
#define RCC_IT_CLKENERR (1UL << 6)
#define IS_RCC_IT(RCC_IT) ((RCC_IT == RCC_IT_LSI) ||       \
                           (RCC_IT == RCC_IT_LSE) ||       \
                           (RCC_IT == RCC_IT_HSI) ||       \
                           (RCC_IT == RCC_IT_PLL) ||       \
                           (RCC_IT == RCC_IT_CLXMUXERR) || \
                           (RCC_IT == RCC_IT_CLKENERR))

#define RCC_APB0Periph_UART3 (1U << 15)
#define RCC_APB0Periph_TIM6 (1U << 26)
#define RCC_APB0Periph_TIM14 (1U << 27)
#define RCC_APB0Periph_TIM16 (1U << 29)
#define RCC_APB0Periph_TIM3 (1U << 31)
#define RCC_APB0Periph_WWDG (1U << 20)
#define RCC_APB0Periph_SSP2 (1UL << 23)
#define IS_RCC_APB0_PERIPH(RCC_APB0Periph) ((RCC_APB0Periph == RCC_APB0Periph_UART3) || \
                                            (RCC_APB0Periph == RCC_APB0Periph_UART4) || \
                                            (RCC_APB0Periph == RCC_APB0Periph_TIM6) ||  \
                                            (RCC_APB0Periph == RCC_APB0Periph_TIM14) || \
                                            (RCC_APB0Periph == RCC_APB0Periph_TIM16) || \
                                            (RCC_APB0Periph == RCC_APB0Periph_TIM3) ||  \
                                            (RCC_APB0Periph == RCC_APB0Periph_SSP2) ||  \
                                            (RCC_APB0Periph == RCC_APB0Periph_WWDG))

#define RCC_AHBPeriph_GPIOA (1UL << 0)
#define RCC_AHBPeriph_GPIOB (1UL << 1)
#define RCC_AHBPeriph_GPIOC (1UL << 2)
#define RCC_AHBPeriph_GPIOF (1UL << 21)
#define RCC_AHBPeriph_DMA (1UL << 8)
#define RCC_AHBPeriph_CRC (1UL << 6)
#define RCC_AHBPeriph_DIV (1UL << 5)
#define IS_RCC_AHB_RST_PERIPH(RCC_AHBPeriph) ((RCC_AHBPeriph == RCC_AHBPeriph_GPIOA) || \
                                              (RCC_AHBPeriph == RCC_AHBPeriph_GPIOB) || \
                                              (RCC_AHBPeriph == RCC_AHBPeriph_GPIOC) || \
                                              (RCC_AHBPeriph == RCC_AHBPeriph_CRC) ||   \
                                              (RCC_AHBPeriph == RCC_AHBPeriph_DIV) ||   \
                                              (RCC_AHBPeriph == RCC_AHBPeriph_DMA) ||   \
                                              (RCC_AHBPeriph == RCC_AHBPeriph_GPIOF))

#define IS_RCC_AHB_PERIPH(RCC_AHBPeriph) ((RCC_AHBPeriph == RCC_AHBPeriph_GPIOA) || \
                                          (RCC_AHBPeriph == RCC_AHBPeriph_GPIOB) || \
                                          (RCC_AHBPeriph == RCC_AHBPeriph_GPIOC) || \
                                          (RCC_AHBPeriph == RCC_AHBPeriph_CRC) ||   \
                                          (RCC_AHBPeriph == RCC_AHBPeriph_DIV) ||   \
                                          (RCC_AHBPeriph == RCC_AHBPeriph_DMA) ||   \
                                          (RCC_AHBPeriph == RCC_AHBPeriph_GPIOF))

#define RCC_MCOSource_NoClock 0x0
#define RCC_MCOSource_PLL 0x1
#define RCC_MCOSource_PLL_CLK_IN 0x2
#define RCC_MCOSource_LSE 0x5
#define RCC_MCOSource_SYSCLK 0x3
#define RCC_MCOSource_HSI 0x6
#define RCC_MCOSource_HSE 0x7
#define RCC_MCOSource_LSI 0x4
#define IS_RCC_MCO_SOURCE(RCC_MCOSource) ((RCC_MCOSource == RCC_MCOSource_NoClock) ||    \
                                          (RCC_MCOSource == RCC_MCOSource_PLL) ||        \
                                          (RCC_MCOSource == RCC_MCOSource_PLL_CLK_IN) || \
                                          (RCC_MCOSource == RCC_MCOSource_LSE) ||        \
                                          (RCC_MCOSource == RCC_MCOSource_SYSCLK) ||     \
                                          (RCC_MCOSource == RCC_MCOSource_HSI) ||        \
                                          (RCC_MCOSource == RCC_MCOSource_HSE) ||        \
                                          (RCC_MCOSource == RCC_MCOSource_LSI))

#define RCC_MCOPrescaler_1 0x0
#define RCC_MCOPrescaler_2 0x1
#define RCC_MCOPrescaler_4 0x2
#define RCC_MCOPrescaler_8 0x3
#define RCC_MCOPrescaler_16 0x4
#define RCC_MCOPrescaler_32 0x5
#define RCC_MCOPrescaler_64 0x6
#define RCC_MCOPrescaler_128 0x7
#define IS_RCC_MCO_PRESCALER(RCC_MCOPrescaler) ((RCC_MCOPrescaler == RCC_MCOPrescaler_1) ||  \
                                                (RCC_MCOPrescaler == RCC_MCOPrescaler_2) ||  \
                                                (RCC_MCOPrescaler == RCC_MCOPrescaler_4) ||  \
                                                (RCC_MCOPrescaler == RCC_MCOPrescaler_8) ||  \
                                                (RCC_MCOPrescaler == RCC_MCOPrescaler_16) || \
                                                (RCC_MCOPrescaler == RCC_MCOPrescaler_32) || \
                                                (RCC_MCOPrescaler == RCC_MCOPrescaler_64) || \
                                                (RCC_MCOPrescaler == RCC_MCOPrescaler_128))

#define RCC_PLLMul_1 ((uint32_t)1)
#define RCC_PLLMul_2 ((uint32_t)2)
#define RCC_PLLMul_3 ((uint32_t)3)
#define RCC_PLLMul_4 ((uint32_t)4)
#define RCC_PLLMul_5 ((uint32_t)5)
#define RCC_PLLMul_6 ((uint32_t)6)
#define RCC_PLLMul_7 ((uint32_t)7)
#define RCC_PLLMul_8 ((uint32_t)8)
#define RCC_PLLMul_9 ((uint32_t)9)
#define RCC_PLLMul_10 ((uint32_t)10)
#define RCC_PLLMul_11 ((uint32_t)11)
#define RCC_PLLMul_12 ((uint32_t)12)
#define RCC_PLLMul_13 ((uint32_t)13)
#define RCC_PLLMul_14 ((uint32_t)14)
#define RCC_PLLMul_15 ((uint32_t)15)
#define RCC_PLLMul_16 ((uint32_t)16)
#define IS_RCC_PLL_MUL(RCC_PLLMul) ((RCC_PLLMul == RCC_PLLMul_1) ||  \
                                    (RCC_PLLMul == RCC_PLLMul_2) ||  \
                                    (RCC_PLLMul == RCC_PLLMul_3) ||  \
                                    (RCC_PLLMul == RCC_PLLMul_4) ||  \
                                    (RCC_PLLMul == RCC_PLLMul_5) ||  \
                                    (RCC_PLLMul == RCC_PLLMul_6) ||  \
                                    (RCC_PLLMul == RCC_PLLMul_7) ||  \
                                    (RCC_PLLMul == RCC_PLLMul_8) ||  \
                                    (RCC_PLLMul == RCC_PLLMul_9) ||  \
                                    (RCC_PLLMul == RCC_PLLMul_10) || \
                                    (RCC_PLLMul == RCC_PLLMul_11) || \
                                    (RCC_PLLMul == RCC_PLLMul_12) || \
                                    (RCC_PLLMul == RCC_PLLMul_13) || \
                                    (RCC_PLLMul == RCC_PLLMul_14) || \
                                    (RCC_PLLMul == RCC_PLLMul_15) || \
                                    (RCC_PLLMul == RCC_PLLMul_16))

#define RCC_WTCLKSource_NONE (0)
#define RCC_WTCLKSource_LSE (1)
#define RCC_WTCLKSource_LSI (2)
#define RCC_WTCLKSource_HSE_Div128 (3)
#define IS_RCC_WTCLK_SOURCE(RCC_WTCLKSource) ((RCC_WTCLKSource == RCC_WTCLKSource_NONE) || \
                                              (RCC_WTCLKSource == RCC_WTCLKSource_LSE) ||  \
                                              (RCC_WTCLKSource == RCC_WTCLKSource_LSI) ||  \
                                              (RCC_WTCLKSource == RCC_WTCLKSource_HSE_Div128))

#define RCC_UART0CLK_APB1 (0)
#define RCC_UART0CLK_SYS_CLK_IN (1)
#define RCC_UART0CLK_RCH (2)
#define RCC_UART0CLK_OSCL (3)
#define IS_RCC_UART0CLK(RCC_UART0CLK) ((RCC_UART0CLK == RCC_UART0CLK_APB1) ||       \
                                       (RCC_UART0CLK == RCC_UART0CLK_SYS_CLK_IN) || \
                                       (RCC_UART0CLK == RCC_UART0CLK_RCH) ||        \
                                       (RCC_UART0CLK == RCC_UART0CLK_OSCL))

#define RCC_UART1CLK_APB1 (0)
#define RCC_UART1CLK_SYS_CLK_IN (1)
#define RCC_UART1CLK_RCH (2)
#define RCC_UART1CLK_OSCL (3)
#define IS_RCC_UART1CLK(RCC_UART1CLK) ((RCC_UART1CLK == RCC_UART1CLK_APB1) ||       \
                                       (RCC_UART1CLK == RCC_UART1CLK_SYS_CLK_IN) || \
                                       (RCC_UART1CLK == RCC_UART1CLK_RCH) ||        \
                                       (RCC_UART1CLK == RCC_UART1CLK_OSCL))

#define RCC_SSP0CLK_APB1 (0)
#define RCC_SSP0CLK_SYS_CLK_IN (1)
#define RCC_SSP0CLK_RCH (2)
#define RCC_SSP0CLK_OSCL (3)
#define IS_RCC_SSP0CLK(RCC_SSP0CLK) ((RCC_SSP0CLK == RCC_SSP0CLK_APB1) ||       \
                                     (RCC_SSP0CLK == RCC_SSP0CLK_SYS_CLK_IN) || \
                                     (RCC_SSP0CLK == RCC_SSP0CLK_RCH) ||        \
                                     (RCC_SSP0CLK == RCC_SSP0CLK_OSCL))

#define RCC_SSP2CLK_APB1 (0)
#define RCC_SSP2CLK_SYS_CLK_IN (1)
#define RCC_SSP2CLK_RCH (2)
#define RCC_SSP2CLK_OSCL (3)
#define IS_RCC_SSP2CLK(RCC_SSP2CLK) ((RCC_SSP2CLK == RCC_SSP2CLK_APB1) ||       \
                                     (RCC_SSP2CLK == RCC_SSP2CLK_SYS_CLK_IN) || \
                                     (RCC_SSP2CLK == RCC_SSP2CLK_RCH) ||        \
                                     (RCC_SSP2CLK == RCC_SSP2CLK_OSCL))

#define RCC_I2C0CLK_APB1 (0)
#define RCC_I2C0CLK_SYS_CLK_IN (1)
#define RCC_I2C0CLK_RCH (2)
#define RCC_I2C0CLK_OSCL (3)
#define IS_RCC_I2C0CLK(RCC_I2C0CLK) ((RCC_I2C0CLK == RCC_I2C0CLK_APB1) ||       \
                                     (RCC_I2C0CLK == RCC_I2C0CLK_SYS_CLK_IN) || \
                                     (RCC_I2C0CLK == RCC_I2C0CLK_RCH) ||        \
                                     (RCC_I2C0CLK == RCC_I2C0CLK_OSCL))

     /**system**/
     void RCC_DeInit(void);                                     //ʱ�Ӹ�λ//
     void RCC_ClockSecuritySystemCmd(FunctionalState NewState); // CSS_EN//
     void RCC_MCOConfig(uint8_t RCC_MCOSource, uint32_t RCC_MCOPrescaler);
     void RCC_BackupResetCmd(FunctionalState NewState); // back domain
     void RCC_HCLKConfig(uint32_t RCC_SYSCLK);

     /*status*/
     FlagStatus RCC_GetFlagStatus(uint8_t RCC_FLAG);
     ITStatus RCC_GetITStatus(uint8_t RCC_IT);
     FlagStatus RCC_GetFlagStatus(uint8_t RCC_FLAG);

     /*interrupt*/
     void RCC_ITConfig(uint8_t RCC_IT, FunctionalState NewState);
     void RCC_ClearITPendingBit(uint8_t RCC_IT);

     /*HSI*/
     void RCC_AdjustHSICalibrationValue(uint8_t HSICalibrationValue); //
     void RCC_HSICmd(FunctionalState NewState);                       //

     /*HSE*/
     void RCC_HSEConfig(uint8_t RCC_HSE);     //�ⲿ����ÿ��غ�bypassʹ��//
     ErrorStatus RCC_WaitForHSEStartUp(void); //

     /*LSI*/
     void RCC_LSICmd(FunctionalState NewState); //

     /*LSE*/
     void RCC_LSEConfig(uint32_t RCC_LSE); //

     /*sys*/
     void RCC_SYSCLKConfig(uint32_t RCC_SYSCLKSource); //
     uint8_t RCC_GetSYSCLKSource(void);

     /*AHB*/
     void RCC_AHBPeriphClockCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState);
     void RCC_AHBPeriphResetCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState);

     /*APB0*/
     void RCC_PCLK0Config(uint32_t RCC_HCLK);
     void RCC_SPI2CLKConfig(uint32_t RCC_SSP2CLK);
     void RCC_APB0PeriphResetCmd(uint32_t RCC_APB0Periph, FunctionalState NewState);
     void RCC_APB0PeriphClockCmd(uint32_t RCC_APB1Periph, FunctionalState NewState);

     /*APB1*/
     void RCC_UART0CLKConfig(uint32_t RCC_UART0CLK);
     void RCC_UART1CLKConfig(uint32_t RCC_UART1CLK);
     void RCC_I2C0CLKConfig(uint32_t RCC_I2C0CLK);
     void RCC_SPI0CLKConfig(uint32_t RCC_SSP0CLK);
     void RCC_WTCLKConfig(uint32_t RCC_WTCLKSource);
     void RCC_WTCLKCmd(FunctionalState NewState);
     void RCC_APB1PeriphClockCmd(uint32_t RCC_APB1Periph, FunctionalState NewState);
     void RCC_APB1PeriphResetCmd(uint32_t RCC_APB1Periph, FunctionalState NewState);
     void RCC_PCLK1Config(uint32_t RCC_HCLK);
     void delay10us(uint32_t u32Cnt);
     /*read clk freq*/
     void RCC_GetClockFreq(RCC_ClocksTypeDef *RCC_Clocks);
     void OSCH_GPIO_INIT(void);
     void FLASH_LATENCY(uint8_t clkrank);
     void SystemInit(void);
     void Sysclk_ResetRch(void);
     void SetSysClock(void);
#ifdef __cplusplus
}
#endif

#endif /* __LCM32F037_RCC_H */
