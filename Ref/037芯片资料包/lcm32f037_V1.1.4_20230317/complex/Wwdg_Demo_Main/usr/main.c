#include "stdio.h"
#include "string.h"
#include "lcm32f037.h"
#include "lcm32f037_gpio.h"
#include "lcm32f037_rcc.h"
#include "lcm32f037_iwdg.h"
#include "lcm32f037_wwdg.h"
#include "lcm32f037_conf.h"
#include "lcm32f037_tim.h"
/**
  ******************************************************************************
  * @function: ���ڿ��Ź�
  * @attention: 
  * 
  * 
  * 
  ******************************************************************************/
uint8_t WWDG_CNT = 0x7f;

void delay(uint32_t dly)
{
  volatile uint32_t i = 0;
  while (i++ < dly)
    ;
}
void GPIO_Config()
{
  GPIO_InitTypeDef GPIO_InitStruct;
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
}
void WWDG_NVIC_Init()
{
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void WWDG_Init(uint8_t tr, uint8_t wr, uint32_t fprer)
{
  RCC_AHBPeriphClockCmd(RCC_APB0Periph_WWDG, ENABLE); //   WWDGʱ��ʹ��

  WWDG_CNT = tr & WWDG_CNT; //��ʼ��WWDG_CNT.
  WWDG_SetPrescaler(fprer); ////����IWDGԤ��Ƶֵ

  WWDG_SetWindowValue(wr); //���ô���ֵ

  WWDG_Enable(WWDG_CNT); //ʹ�ܿ��Ź� ,	���� counter .

  WWDG_ClearFlag(); //�����ǰ�����жϱ�־λ

  WWDG_NVIC_Init(); //��ʼ�����ڿ��Ź� NVIC

  WWDG_EnableIT(); //�������ڿ��Ź��ж�
}

int main(void)
{
  GPIO_Config();
  GPIO_SetBits(GPIOA, GPIO_Pin_11);
  delay(50000);
  GPIO_ResetBits(GPIOA, GPIO_Pin_11);
  delay(50000);                            //��λָʾ����
  WWDG_Init(0X7f, 0X5F, WWDG_Prescaler_8); //������ֵΪ7f,���ڼĴ���Ϊ5f,��Ƶ��Ϊ8

  while (1)
  {
    //		WWDG_SetCounter(0x50);
    //		delay(5000);
  }
}

void WWDG_Handler(void)
{
  GPIO_SetBits(GPIOA, GPIO_Pin_12);
  WWDG_SetCounter(0x50); //�������˾��,���ڿ��Ź���������λ

  WWDG_ClearFlag(); //�����ǰ�����жϱ�־λ
  GPIO_ResetBits(GPIOA, GPIO_Pin_12);
}

#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* cUser can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
}
#endif

/**
  * @}
  */
