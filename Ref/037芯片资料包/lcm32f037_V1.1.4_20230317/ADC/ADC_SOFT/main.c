#include "lcm32f037_adc.h"
#include "lcm32f037_opa.h"
#include "lcm32f037_tim.h"
#include "lcm32f037_dma.h"
#include "lcm32f037_flash.h"
#include "lcm32f037_dac.h"
/*****************
demoΪ�������ADC
***********************************************************************************************/
uint16_t TimerPeriod = 0;
uint16_t Channel1Pulse = 0, Channel2Pulse = 0, Channel3Pulse = 0, Channel4Pulse = 0;
uint32_t datad;

void GPIOConfiguration(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_1); // PA0=ADCIN[0]
}
void ADCConfiguration(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;

	ADC_InitStructure.ADC_ClkMode = ADC_ClockMode_sysnClk;						//ѡ��ת��ʱ��Դ
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;						//����
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;							//ת��ģʽ0=����;1=����;��ʾ����һ��ת��һ��ͨ������һ������
	ADC_InitStructure.ADC_AutoWatiMode = DISABLE;								//��λ��������ú������ʹ���� / �ر��Զ��ӳ�ת��ģʽ
	ADC_InitStructure.ADC_DMATRIG_LEVEL = FIFO_DMA_NOEMPTY;						//������ô��� DMA ����� FIFO ˮƽ���� DMAEN ʹ��ǰ�������ã�������� DMA �ڰ���ʱ�Ĵ���
	ADC_InitStructure.ADC_DMA = DISABLE;										//�Ƿ������� DMA ���������Զ�����ת���Ľ������
	ADC_InitStructure.ADC_DiscMode = DISABLE;									// 0=����ģʽ��ֹ;1=����ģʽ����
	ADC_InitStructure.ADC_SamecMode = DISABLE;									//����ģʽѡ��0=��������;1=ͬʱ����
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None; //������ʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_SoftWare;		//����Դ
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;						//���ݶ��뷽ʽ
	ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;				// 0=��ǰɨ�� (�� CHSEL0 �� CHSEL15);1=���ɨ��( �� CHSEL15 �� CHSEL0)
	ADC_InitStructure.ADC_Vref = ADC_Vref_Internal_3V3;							//�ο���ѹѡ��
	ADC_Init(ADC, &ADC_InitStructure);

	ADC_ChannelConfig(ADC, ADC_Channel_0, 15, 7, 7); //����ͨ����CONVERT��ADJUST,SMP
	ADC_Cmd(ADC, ENABLE);
}
int main()
{
	SystemInit();
	SetSysClock(); //��Ƶ����

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_ADC, ENABLE); //��ʱ��
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	GPIOConfiguration(); // GPIO����
	ADCConfiguration();	 // ADC��ʼ��

	ADC_StartOfConversion(ADC1); // ADC ��ʼת������
	while (1)
	{
		datad = ADC_GetConversionValue(ADC1);
	}
}
