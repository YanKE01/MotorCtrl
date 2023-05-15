
/* Includes ------------------------------------------------------------------*/
#include "lcm32f037.h"

/* Include of other module interface headers ---------------------------------*/
/* Local includes ------------------------------------------------------------*/

#include "lcm32f037_it.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : TB_Init
* Description    : TimeBase peripheral initialization. The base time is set to 
*                  500usec and the related interrupt is enabled  
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TB_Init(void)
{   

  /* SystemFrequency / 1000    1ms中断一次
	 * SystemFrequency / 100000	 10us中断一次
	 * SystemFrequency / 1000000 1us中断一次
	 */
	SysTick_Config(24000);
	
}




/******************* (C) COPYRIGHT 2008 LCMicroelectronics *****END OF FILE****/
