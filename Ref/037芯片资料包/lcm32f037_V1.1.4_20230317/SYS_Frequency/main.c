#include "lcm32f037_conf.h"
#include "lcm32f037.h"
#include "lcm32f037_rcc.h"
#include "lcm32f037_gpio.h"
/*******************************
��Ƶ���÷�ʽ
********************************/

void GPIO_INIT() // IO��ʼ��
{
	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_0);
}
/*72M������Ƶ���÷�ʽ����ʵ����Ҫѡ���������ַ�ʽ��һ;
72Mһ����Ƶ�������SystemInit()����
��Ƶ�궨��ѡ��ʽ�վ�*/
int main()
{
	SystemInit();
	SetSysClock(); //��Ƶ����
	GPIO_INIT();
	RCC_MCOConfig(RCC_MCOSource_SYSCLK, RCC_MCOPrescaler_8); //��Ƶ�۲�,8��Ƶ
	while (1)
		;
}
