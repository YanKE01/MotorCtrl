#include "lcm32f037_adc.h"
#include "lcm32f037_opa.h"
#include "lcm32f037_tim.h"
#include "lcm32f037_dma.h"
#include "lcm32f037_flash.h"
#include "lcm32f037_dac.h"
/*****************
demoΪ�������ADC
***********************************************************************************************/
#define DMA_ENABLE 1
#define ADC_SIZE 6
#define ADC1_DR_Address (0x4001A020)
unsigned int ADCConvertedRawData[ADC_SIZE] = {0};
void GPIOConfiguration(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_1); // PA0(AN1)=ADCIN[0]

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_1); // PA1(AN1)=ADCIN[1]

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_2); // PA2(AN2)=ADCIN[2]

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_1); // PA3(AN1)=ADCIN[3]

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource4, GPIO_AF_2); // PA4(AN2)=ADCIN[4]

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_1); // PA5(AN1)=ADCIN[5]

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_2); // tim1_ch1   pA8
}
void ADCConfiguration(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;

	ADC_InitStructure.ADC_ClkMode = ADC_ClockMode_SynClkDiv4;					  //ѡ��ת��ʱ��Դ
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;						  //����
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;							  //ת��ģʽ0=����;1=����;��ʾ����һ��ת��һ��ͨ������һ������
	ADC_InitStructure.ADC_AutoWatiMode = ENABLE;								  //��λ��������ú������ʹ���� / �ر��Զ��ӳ�ת��ģʽ
	ADC_InitStructure.ADC_DMATRIG_LEVEL = FIFO_DMA_NOEMPTY;						  //������ô��� DMA ����� FIFO ˮƽ���� DMAEN ʹ��ǰ�������ã�������� DMA �ڰ���ʱ�Ĵ���
	ADC_InitStructure.ADC_DMA = ENABLE;											  //�Ƿ������� DMA ���������Զ�����ת���Ľ������
	ADC_InitStructure.ADC_DiscMode = DISABLE;									  // 0=����ģʽ��ֹ;1=����ģʽ����
	ADC_InitStructure.ADC_SamecMode = DISABLE;									  //����ģʽѡ��0=��������;1=ͬʱ����
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_Rising; //������ʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_TRGO;		  //����Դ
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;						  //���ݶ��뷽ʽ
	ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;				  // 0=��ǰɨ�� (�� CHSEL0 �� CHSEL15);1=���ɨ��( �� CHSEL15 �� CHSEL0)
	ADC_InitStructure.ADC_Vref = ADC_Vref_Externa_Vrh4V;							  //�ο���ѹѡ��
	ADC_Init(ADC, &ADC_InitStructure);

	ADC_ChannelConfig(ADC, ADC_Channel_0, 15, 7, 7); //����ͨ����CONVERT��ADJUST,SMP
	ADC_ChannelConfig(ADC, ADC_Channel_1, 15, 7, 7);
	ADC_ChannelConfig(ADC, ADC_Channel_2, 15, 7, 7);
	ADC_ChannelConfig(ADC, ADC_Channel_3, 15, 7, 7);
	ADC_ChannelConfig(ADC, ADC_Channel_4, 15, 7, 7);
	ADC_ChannelConfig(ADC, ADC_Channel_5, 15, 7, 7);

	ADC_Cmd(ADC, ENABLE);

#if DMA_ENABLE
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA, ENABLE);
	/*DMA1 channel1 configuration ----------------------------------------------*/
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;				//��������DMA������������ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADCConvertedRawData;	//�ڴ����ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;						//�������ݴ��䷽�򣬼������Ǵ������ȡ���ݵ��ڴ滹�Ǵ��ڴ�����ݵ����裬���������Ǵ�����ADC_DR�Ĵ��������ݵ��ڴ�
	DMA_InitStructure.DMA_BufferSize = ADC_SIZE;							//����һ�δ����������Ĵ�С
	DMA_InitStructure.DMA_MSIZE = DMA_MSIZE_1;								//ͻ�������䳤��
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;		//���ô������ݵ�ʱ�� �����裩 ��ַ�ǲ��仹�ǵ�����
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;					//���ô������ݵ�ʱ�� ���ڴ� ����ַ�ǲ��仹�ǵ���
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word; //������������ݳ�����Ϊ�ֽڴ��䣨8bits�����ǰ��֣�16bits�������ִ��䣨32bits��
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;			//�����ڴ�����ݳ��ȣ�ͬ�ϡ�
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;							//�����Ƿ����ѭ���ɼ�
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;						//�������ȼ�
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure); //�����Ƿ��Ǵ洢�����洢��ģʽ����
	/* Enable DMA1 channel1 TC interupt*/
	DMA_ITConfig(DMA1_Channel1, DMA1_FLAG_TC1, ENABLE); //����DMA������ɺ��ж�
	DMA_RemapConfig(DMA1_Channel1, DMA_ReqNum5, DMA_REQ_ADC);
	/* Enable DMA1 channel1 */
	DMA_Cmd(DMA1_Channel1, ENABLE);
#endif
}
void tim1_cfg_init()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	uint16_t TimerPeriod;
	uint16_t Channel1Pulse, Channel2Pulse, Channel3Pulse, Channel4Pulse;
	TimerPeriod = 800;	 // 16000000/20000;
	Channel1Pulse = 400; // TimerPeriod/2;
	Channel2Pulse = 400; // TimerPeriod/2;
	Channel3Pulse = 400; // TimerPeriod/2;
	Channel4Pulse = 400; // TimerPeriod/2;

	/* Time Base configuration */
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1;
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

	TIM_SelectOutputTrigger(TIM1, TIM_TRGOSource_OC4Ref); //ѡ��TRGO�������Դ

	TIM_CtrlPWMOutputs(TIM1, ENABLE); //����TRGO����ADC�ɲ���Ҫʹ�ܣ�����ͨ��CCx����,��ͨ��IO�۲�PWM���Σ�����ʹ�ܣ�

	TIM_Cmd(TIM1, ENABLE);
}
int main()
{
	SystemInit();
	SetSysClock(); //��Ƶ����

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_ADC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM1, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);
	NVIC_ClearPendingIRQ(DMAC_CH1_2_IRQn);
	NVIC_EnableIRQ(DMAC_CH1_2_IRQn); //ʹ��DMA�ж�

	GPIOConfiguration(); // GPIO����
	tim1_cfg_init();
	ADCConfiguration();			// ADC��ʼ��
	ADC_StartOfConversion(ADC); // ADC ��ʼת������

	while (1)
		;
}
uint32_t datad, testCount;
int temperature;
void DMAC_CH1_2_Handler(void)
{
	DMA_ClearITPendingBit(DMA1_FLAG_TC1);
	testCount++;
	if (testCount > 10000) //����1000�κ���ͨ����VTS�����л���
	{
		testCount = 0;
		/**********************��VTSͨ��***********************/
		ADC_StopOfConversion(ADC);						  //ֹͣADC
		ADC->ISR = 0x0000000e;							  //���ADC��־λ
		ADC->CFGR1 &= 0xfffffffe;						  // DMA��ʹ��
		ADC->EXTCFG = 0;								  //����Դ:�������(���Բ��Ĵ���Դ��������Ҫѡ��)
		ADC_ChannelConfig(ADC, ADC_Channel_16, 15, 7, 7); //�¶ȴ�����: �� ST=1��SV=0 ʱѡ�� ADC_IN16������ͨ��(ADC_IN0~15��ADC_IN17)����
		ADC_StartOfConversion(ADC);						  // ADC��ʼת������
		datad = ADC_GetConversionValue(ADC);			  //��ȡ�¶ȴ�����ADֵ
		temperature = ADC_GetVTStemperature(datad, 4000); //��ȡ��ǰ�¶�
		/**********************�л�ԭ����***********************/
		ADC_StopOfConversion(ADC);						 //ֹͣADC
		ADC->ISR = 0x0000000e;							 //���ADC��־λ
		ADC->CFGR1 |= 0x01;								 // DMAʹ��
		ADC->EXTCFG = 0x80000001;						 //����Դ:T1_TRGO������
		ADC_ChannelConfig(ADC, ADC_Channel_0, 15, 7, 7); //����ͨ��
		ADC_ChannelConfig(ADC, ADC_Channel_1, 15, 7, 7);
		ADC_ChannelConfig(ADC, ADC_Channel_2, 15, 7, 7);
		ADC_ChannelConfig(ADC, ADC_Channel_3, 15, 7, 7);
		ADC_ChannelConfig(ADC, ADC_Channel_4, 15, 7, 7);
		ADC_ChannelConfig(ADC, ADC_Channel_5, 15, 7, 7);
		ADC_StartOfConversion(ADC); // ADC��ʼת������
	}
}