#include "lcm32f037_conf.h"
#include "lcm32f037.h"
#include "lcm32f037_rcc.h"
#include "lcm32f037_uart.h"
#include "lcm32f037_gpio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lcm32f037_div.h"
#include "lcm32f037_tim.h"
#include "lcm32f037_acmp.h"
#include "lcm32f037_dac.h"
#include "lcm32f037_exti.h"
/***********
demo���ã�ͨ��2����ͨ��1��������壻
������ģʽ��
������ģʽ����ʱʱ�� = TIM_CCR1 - 0   ������ =  TIM_ARR - TIM_CCR1
������ģʽ����ʱʱ�� = TIM_ARR - TIM_CCR1    ������ = TIM_CCR1 - 0
***************************************************************************/

void GPIO_Config()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_2); // tim1_ch1   pA8

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_3); // tim1_ch2    pa9
}

static void tim1_cfg_init()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_TimeBaseStructure.TIM_Period = 2000;					//��ʱ������ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = 16 - 1;				//Ԥ��Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;				//ʱ�Ӳ���Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //������ģʽ
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);				//��ʼ����ʱ��ʱ��

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //������ǿ�����ģʽ����������Ĵ���TIM1->CCMR1��OC1M[2:0]
	TIM_OCInitStructure.TIM_Pulse = 1500;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);

	//	TIM_ICStructInit(&TIM_ICInitStructure);//��ʼ�����벶��ṹ��
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;				// TIM1 CH2 ����Ϊ���벶��ģʽ
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;		//�����ز���
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //�ܽ���Ĵ���ֱ�Ӷ�Ӧ
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;			//�����Ƶ
	TIM_ICInitStructure.TIM_ICFilter = 0;							//���˲�
	TIM_ICInit(TIM1, &TIM_ICInitStructure);							//��ʼ��TIM1 CH2

	TIM_SelectOnePulseMode(TIM1, TIM_OPMode_Single); //ѡ��ʱ��Ϊ������ģʽ
	TIM_DTS_Cfg(TIM1);
	TIM_TI2E_Set(TIM1);
	TIM_SelectInputTrigger(TIM1, TIM_TS_TI2FP2);	  //ѡ�񴥷�ԴΪIC2
	TIM_SelectSlaveMode(TIM1, TIM_SlaveMode_Trigger); //ѡ��ʱ����ģʽΪ�����ش���
	TIM_CtrlPWMOutputs(TIM1, ENABLE);

	TIM_Cmd(TIM1, ENABLE);
}

int main()
{
	SystemInit();
	SetSysClock(); //��Ƶ����
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM1, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	GPIO_Config();	 // PWM GPIOSET
	tim1_cfg_init(); // TIM1 SET

	while (1)
		;
}
