/**
  ******************************************************************************
  * @file    Project/LCM32F037_StdPeriph_Templates/LCM32f037_conf.h 
  * @author  MCD Application Team
  * @version V0.4.44
  * @date    14-04-2021
  * @brief   Library configuration file.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LCM32F037_CONF_H
#define __LCM32F037_CONF_H

#include "lcm32f037_rcc.h"
#include "lcm32f037_uart.h"
#include "lcm32f037_gpio.h"
//#include "lcm32f037_div.h"
#include "lcm32f037_adc.h"
//#include "lcm32f037_opa.h"
//#include "lcm32f037_dbgmcu.h"
//#include "lcm32f037_dma.h"
//#include "lcm32f037_exti.h"
//#include "lcm32f037_flash.h"
//#include "lcm32f037_i2c.h"
//#include "lcm32f037_iwdg.h"
//#include "lcm32f037_pwr.h"
//#include "lcm32f037_ssp.h"
//#include "lcm32f037_tim.h"
//#include "lcm32f037_acmp.h"
//#include "lcm32f037_dac.h"
//#include "lcm32f037_wwdg.h"

/* Exported macro ------------------------------------------------------------*/
#ifdef USE_FULL_ASSERT

//测试时可以放开这个宏定义，这时如果只有一个链接错误说明参数校验是成功的，具体为什么有一个错误，
//原因参见：http://www.openedv.com/forum.php?mod=viewthread&tid=233944&page=1&extra=
//  https://www.cnblogs.com/vivohan/p/8470680.html
#define uint8_t unsigned char
#define uint32_t unsigned int
/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function which reports 
  *         the name of the source file and the source line number of the call 
  *         that failed. If expr is true, it returns no value.
  * @retval None
  */
#define assert_param(expr) ((expr) ? ((void)0) : (assert_failed((uint8_t *)__FILE__, __LINE__)))
/* Exported functions ------------------------------------------------------- */
void assert_failed(uint8_t *file, uint32_t line);

#undef uint8_t
#undef uint32_t
#else
#define assert_param(expr) ((void)0)
#endif /* USE_FULL_ASSERT */

#endif /* __LCM32F037_CONF_H */

/************************ (C) COPYRIGHT LCMicroelectronics *****END OF FILE****/
