#include "lcm32f037_conf.h"
#include "lcm32f037.h"
#include "lcm32f037_rcc.h"
#include "lcm32f037_gpio.h"
#include "lcm32f037_pwr.h"
#include "lcm32f037_exti.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 ******************************************************************************
 * @function:  lvd lvr
 * @attention:
 ******************************************************************************/
void Delay(uint16_t i)
{
  while (i--)
    ;
}
void GPIO_Cfg()
{
  GPIO_InitTypeDef GPIO_InitStruct;
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
}

int main()
{
  SystemInit();
  SetSysClock(); //��Ƶ����

  PWR_LVRConfig(PWR_LVRLevel_2V8);                     //����LVR��λ��
  PWR_LVRCmd(ENABLE);                                  // LVRʹ��
  PWR_LVDConfig(PWR_LVDInternal, PWR_LVDInternal_3V1); //����ڲ���ѹ�����õ�ѹ��
  PWR_LVDCmd(ENABLE);                                  // LVDʹ��
  GPIO_Cfg();
  while (1)
  {
    if (CHIPCTRL->STS_b.LVDFLG == SET) // 0: VDDH/VDDA ��ѹֵ���ڼ���ѹ;1: VDDH/VDDA ��ѹֵ���ڼ���ѹ
    {
      GPIO_WriteBit(GPIOA, GPIO_Pin_0, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_0)));
      Delay(1000);
    }
    if (CHIPCTRL->RST_CSR_b.LVR_FLAG == SET) //��ѹ��⸴λ����Ӳ�����ã����д 1 �����
    {
      // PWR_LVRClearFlag();
      GPIO_WriteBit(GPIOA, GPIO_Pin_1, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_1)));
      Delay(1000);
    }
    if (CHIPCTRL->RST_CSR_b.POR_FLAG == SET) //�ϵ縴λ��־(POR/POR_PDR)����Ӳ�����ã����д 1 �����
    {
      // PWR_POR_PDRClearFlag();
      GPIO_WriteBit(GPIOA, GPIO_Pin_2, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_2)));
      Delay(1000);
    }
  }
}
