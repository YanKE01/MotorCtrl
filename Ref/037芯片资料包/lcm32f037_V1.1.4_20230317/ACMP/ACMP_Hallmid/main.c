//
#include "lcm32f037.h"
#include "lcm32f037_gpio.h"
#include "lcm32f037_rcc.h"
#include "lcm32f037_dma.h"
#include "lcm32f037_adc.h"
#include "lcm32f037_tim.h"
#include "lcm32f037_acmp.h"
#include "lcm32f037_dac.h"
#include "lcm32f037_exti.h"
/*****************************************
 * ACMP��HALL_MID����
 * *********************************************/
void delay(int i)
{
	while (i--)
		;
}

void tim1_cfg_init()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	uint16_t TimerPeriod = 0;
	uint16_t Channel1Pulse = 0;
	TimerPeriod = 1000;
	Channel1Pulse = 400;

	/* Time Base configuration */
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = TimerPeriod;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

	/* Channel 1, 2,3 and 4 Configuration in PWM mode */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OCInitStructure.TIM_Pulse = Channel1Pulse;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;

	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);
	TIM_OC3Init(TIM1, &TIM_OCInitStructure);
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);

	TIM_CtrlPWMOutputs(TIM1, ENABLE); //����TRGO����ADC�ɲ���Ҫʹ�ܣ�����ͨ��CCx����,��ͨ��IO�۲�PWM���Σ�����ʹ�ܣ�

	TIM_Cmd(TIM1, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	//���ùܽ�Ϊ����ģʽ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	/* GPIOA GPIOE Clocks enable */
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_2); // TIM1_CH1
}
void Hallmid_Cfg()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource4, GPIO_AF_2); // HALL_CR.HALL_IP1
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_1); // HALL_CR.HALL_IP2
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_1); // HALL_CR.HALL_IP3
	Hallmid_IP1_Config(HALL_IP1_PA4, ENABLE);
	Hallmid_IP2_Config(HALL_IP1_PA4, ENABLE);
	Hallmid_IP3_Config(HALL_IP1_PA4, ENABLE);
	Hallmid_Cmd(ENABLE);
}
void DAC1_cfg()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_2); //���ڹ۲�DAC1_OUT

	DAC_InitTypeDef DAC_InitStruct;
	DAC_InitStruct.DAC_Trigger_Source = DAC_Trigger_Software;
	DAC_InitStruct.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStruct.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
	DAC_InitStruct.DAC_OutputBuffer = DAC1_OutputBuffer_Enable;
	DAC_InitStruct.DAC_Vref_Select = DAC_Vref_Avdd;
	DAC_InitStruct.DAC_EXTrigger_Edge = DAC_EXTrigger_edge_dis;
	DAC_InitStruct.DAC_DmaMode = DISABLE;
	DAC_InitStruct.DAC_DMAUDR_IE = DISABLE;
	DAC_Init(DAC1, &DAC_InitStruct);

	DAC_Cmd(DAC1, ENABLE);
	DAC_SetDac_10B_Data(DAC1, DAC_Align_10B_R, 0x1FF);
	DAC_SoftwareTriggerCmd(DAC1, ENABLE); //�������ʹ�ܣ���ʾ���� DAC ��һ�δ�������(ѡ�������������)
}
void acmp1_cfg()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_6); // ACMP2_OUT

	ACMP_InitTypeDef ACMP_InitStruct;
	ACMP_InitStruct.ACMP_P_Select = CP2_PS_DAC2_HALLMID; //�Ƚ�����������ѡ��
	ACMP_InitStruct.ACMP_N_Select = CP1_NS_DAC1OUT;		 //�Ƚ�����������ѡ��
	ACMP_InitStruct.ACMP_Delay_time = CP_NODelay_time;	 //����ӳ�����
	ACMP_InitStruct.ACMP_Blanking = CP_NOBLANKING;		 //�Ƚ�������Դѡ��
	ACMP_InitStruct.ACMP_Is = CP_IS_POS;				 //�Ƚ����������
	ACMP_InitStruct.ACMP_HYSEN = DISABLE;				 //����ʹ������
	ACMP_InitStruct.ACMP_FREN = ENABLE;					 //������Ӧʹ��
	ACMP_InitStruct.ACMP_FS = DISABLE;					 //����˲�ʹ������

	ACMP_InitStruct.CMP_INTENMASK = ENABLE;				 //�Ƚ��������Ƚ��ж�ʹ������
	ACMP_InitStruct.CMP_SEQ_MODE = ENABLE;				 //����ģʽʹ��
	ACMP_InitStruct.TRIG_MODE = CP_TIRG_EXTEN;			 //����ģʽ����������ⲿӲ������
	ACMP_InitStruct.CHNL_CNT_TIME = CHNL_CNT_TIME_64CLK; //�Ƚ���ͨ���л�ʱ������ѡ��

	//	ACMP_InitStruct.EXTSELECT = ENABLE_EXTSELG0;			  // Two sets of trigger sources enable control bits
	//	ACMP_InitStruct.EXTEN_Signal_andmode = ENABLE;			  // Trigger signal logic 'or' or 'and'
	//	ACMP_InitStruct.CP_EXTSP = CP_EXTSP_POS;				  //�����źż���ѡ��
	//	ACMP_InitStruct.SYN_MODE = CP_SYN_MODE;					  //�ⲿ����ͬ�����첽
	//	ACMP_InitStruct.TRIG_SOURCE = TRIG_TIM1_CC1;			  //����Դѡ��
	//	ACMP_InitStruct.TRIG_DELAY_TIME = TRIG_DELAY_TIME_128CLK; //�ⲿ�����ӳ�ʱ��
	//	ACMP_InitStruct.EXTEN_EDGE_MODE = CP_Edge_model;		  //�ⲿ�����źŷ�ʽ
	//	ACMP_InitStruct.EXTEN_MODE_SEL = CP_EXTEN_RISE;			  //�ⲿ����ģʽѡ��

	ACMP1_Init(&ACMP_InitStruct);
	//	ACMP1_SEQ_INPUT_SELECT(DISABLE, 5, 2); //ѡ������ͨ�����Ƿ����������ˣ�����
	ACMP1_Cmd(ENABLE);
}

void EXTI_Config()
{
	EXTI_InitTypeDef EXTI_InitStruct;
	EXTI_InitStruct.EXTI_Line = EXTI_Line20;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStruct);
	NVIC_ClearPendingIRQ(LCD_ACMP0_2_IRQn);
	NVIC_EnableIRQ(LCD_ACMP0_2_IRQn);
}
int main()
{
	SystemInit();
	SetSysClock(); //��Ƶ����
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_ANACTRL, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_EXTI, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM1, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	EXTI_Config();
	tim1_cfg_init();
	Hallmid_Cfg(); // IP1=PA4;IP2=PA6;IP3=PA7;
	DAC1_cfg();	   // DAC1_OUT=PA5
	acmp1_cfg();   // ACMP1_OUT=PA2
	while (1)
		;
}

void LCD_ACMP0_2_Handler() //�Ƚ����ж�
{
	EXTI_ClearITPendingBit(EXTI_Line20);
}
