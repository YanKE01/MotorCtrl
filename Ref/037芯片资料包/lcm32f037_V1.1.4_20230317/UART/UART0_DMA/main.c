#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lcm32f037.h"
#include "lcm32f037_uart.h"
#include "lcm32f037_gpio.h"
#include "lcm32f037_rcc.h"
#include "lcm32f037_dma.h"
/**
 ******************************************************************************
 * @function: uart0_DMA
 * @attention: TX=PB0  RX=PB1
 ******************************************************************************/
#define DMA_ENABLE 1

#define UART_SIZE 8UL
#define UART_DR_Address (0x40014000)
uint8_t uart_send_buff[8] = {0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11};

void delay(uint32_t dly)
{
	volatile uint32_t i = 0;
	while (i++ < dly)
		;
}

void UART0_Config()
{
	UART_InitTypeDef UART_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_UART0CLKConfig(RCC_UART0CLK_RCH); //ѡ��UART0ʱ��Դ��������Ĭ������ʱ��

	//	GPIO_PinAFConfig(GPIOB, GPIO_PinSource0, GPIO_AF_4);
	//	GPIO_PinAFConfig(GPIOB, GPIO_PinSource1, GPIO_AF_5);
	//	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; //	PB0--UART0.Tx  PB1--UART0.Rx
	//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	//	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	//	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	//	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	//	GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_0);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_0);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; //	PB6--UART0.Tx  PB7--UART0.Rx
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	UART_StructInit(&UART_InitStruct);
	UART_InitStruct.UART_BaudRate = 115200;
	UART_InitStruct.UART_WordLength = UART_WordLength_8b;
	UART_InitStruct.UART_StopBits = UART_StopBits_1;
	UART_InitStruct.UART_Parity = UART_Parity_No;
	UART_InitStruct.UART_HardwareFlowControl = UART_HardwareFlowControl_None;
	UART_InitStruct.UART_Mode = UART_Mode_Rx | UART_Mode_Tx;
	UART_Init(UART0, &UART_InitStruct);

	UART_FIFOEnable(UART0, ENABLE);

#if DMA_ENABLE
	DMA_InitTypeDef DMA_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA, ENABLE);

	DMA_DeInit(DMA1_Channel2);
	DMA_InitStructure.DMA_PeripheralBaseAddr = UART_DR_Address;				//��������DMA������������ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&uart_send_buff;		//�ڴ����ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;						//�������ݴ��䷽�򣬼������Ǵ������ȡ���ݵ��ڴ滹�Ǵ��ڴ�����ݵ����裬���������Ǵ�����ADC_DR�Ĵ��������ݵ��ڴ�
	DMA_InitStructure.DMA_BufferSize = UART_SIZE;							//���õ��δ���(single transaction)������
	DMA_InitStructure.DMA_MSIZE = DMA_MSIZE_1;								//ͻ�������䳤��
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;		//���ô������ݵ�ʱ�� �����裩 ��ַ�ǲ��仹�ǵ�����
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;					//���ô������ݵ�ʱ�� ���ڴ� ����ַ�ǲ��仹�ǵ���
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //������������ݳ�����Ϊ�ֽڴ��䣨8bits�����ǰ��֣�16bits�������ִ��䣨32bits��
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;			//�����ڴ�����ݳ��ȣ�ͬ�ϡ�
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;							//�����Ƿ����ѭ���ɼ�
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;						//�������ȼ�
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;							//�ڴ浽�ڴ�ʹ��
	DMA_Init(DMA1_Channel2, &DMA_InitStructure);							//�����Ƿ��Ǵ洢�����洢��ģʽ����

	DMA_ITConfig(DMA1_Channel2, DMA1_IT_TC2, ENABLE);			   //����DMA������ɺ��ж�
	DMA_RemapConfig(DMA1_Channel2, DMA_ReqNum0, DMA_REQ_UART0_TX); /// DMA�����ӳ�䵽����

	DMA_Cmd(DMA1_Channel2, ENABLE);
	/*����ҪDMA�жϣ�������ע�͵���*/
//	NVIC_ClearPendingIRQ(DMAC_CH1_2_IRQn);
//	NVIC_EnableIRQ(DMAC_CH1_2_IRQn);
#endif
	UART_DMACmd(UART0, UART_DMAReq_Tx, ENABLE);
	UART_Cmd(UART0, ENABLE);
}

void GPIO_Config()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
int main()
{
	RCC_DeInit();
	SystemInit();
	SetSysClock(); //��Ƶ����
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART0, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

	GPIO_Config(); //�۲��ã���ʵ������
	UART0_Config();
	while (1)
	{
		if (DMA_GetFlagStatus(DMA1_FLAG_TC2) == 1) //��ѯ��ʽ���־λ
		{
			DMA_ClearITPendingBit(DMA1_FLAG_TC2);
			GPIO_SetBits(GPIOA, GPIO_Pin_1); //�۲��ã���ʵ������
		}
		else
			GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	}
}
// void DMAC_CH1_2_Handler() //60us
//{
//	DMA_ClearITPendingBit(DMA1_FLAG_TC2);
// }
