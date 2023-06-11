#include "stdio.h"
#include "string.h"
#include "lcm32f037.h"
#include "lcm32f037_gpio.h"
#include "lcm32f037_rcc.h"
#include "lcm32f037_i2c.h"
#include "lcm32f037_uart.h"
#include "lcm32f037_dma.h"
#include "stdbool.h"
/************************************************************
FUNCTION:
*************************************************************************/
#define DMA_ENABLE 1
#define I2C_SIZE 10UL
#define I2C_DR_Address (0x40013010)

#define WriteLength 10
uint8_t Receive_Buff[WriteLength] = {0};
uint8_t Send_Buff[WriteLength] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A};
uint8_t ReceiveOffset, SendOffset;
void Delay(uint32_t delay_time)
{
	while (delay_time--)
		;
}

/************************
IIC  IO��ʼ��
**************************************/
void GPIO_Cfg()
{
	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_I2C0CLKConfig(RCC_I2C0CLK_RCH);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; // I2C0:PA9_SCL  PA10_SDA
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_4);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_4);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}

/************************
�ӻ�����
**************************************/
void I2C0_Slave()
{
	I2C_InitTypeDef I2C_InitStruct;
	I2C_InitStruct.I2C_mode = I2C_SlaveOnlyMode;							 //�ӻ�ģʽ
	I2C_InitStruct.I2C_StopDetSlave = I2C_StopDet_SlaveActive;				 //�ӻ�ģʽ�£���Ѱַƥ��ʱ����STOP_DET�ж�
	I2C_InitStruct.I2C_RxFifoFullHold = I2C_RxFifoFullHold_ENABLE;			 //����I2C��RX FIFO�ﵽRX_RX_BUFFER_DEPTHʱ�Ƿ�hold����
	I2C_InitStruct.I2C_TxEmptyIntr = I2C_TxEmptyIntr_ENABLE;				 //����TX_EMPTY�жϵĲ�����ʽ
	I2C_InitStruct.I2C_SlaveAddressedLength = I2C_SlaveAddressedLength_7bit; //��ַ����
	I2C_Init(I2C0, &I2C_InitStruct);
	I2C_SlaveAddressConfig(I2C0, 0x05);		 //���õ�ַ
	I2C_ITConfig(I2C0, I2C_IT_ALL, DISABLE); //�ж�����
	I2C_ClearITPendingBit(I2C0, I2C_IT_ALL); //���ж�
//ʹ��DMA���������ݴ����赽����Receive_Buff
#if DMA_ENABLE
	DMA_InitTypeDef DMA_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA, ENABLE);

	DMA_DeInit(DMA1_Channel2);
	DMA_InitStructure.DMA_PeripheralBaseAddr = I2C_DR_Address;				//��������DMA������������ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&Receive_Buff;			//�ڴ����ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;						//�������ݴ��䷽�򣬼������Ǵ������ȡ���ݵ��ڴ滹�Ǵ��ڴ�����ݵ����裬���������Ǵ�����ADC_DR�Ĵ��������ݵ��ڴ�
	DMA_InitStructure.DMA_BufferSize =I2C_SIZE ;									//����һ�δ����������Ĵ�С
	DMA_InitStructure.DMA_MSIZE = DMA_MSIZE_1;								//ͻ�������䳤��
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;		//���ô������ݵ�ʱ�� �����裩 ��ַ�ǲ��仹�ǵ�����
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;					//���ô������ݵ�ʱ�� ���ڴ� ����ַ�ǲ��仹�ǵ���
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //������������ݳ�����Ϊ�ֽڴ��䣨8bits�����ǰ��֣�16bits�������ִ��䣨32bits��
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;			//�����ڴ�����ݳ��ȣ�ͬ�ϡ�
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;							//�����Ƿ����ѭ���ɼ�
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;						//�������ȼ�
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;							//�ڴ浽�ڴ�ʹ��
	DMA_Init(DMA1_Channel2, &DMA_InitStructure);							//�����Ƿ��Ǵ洢�����洢��ģʽ����

	DMA_ITConfig(DMA1_Channel2, DMA1_FLAG_TC2, ENABLE);			  //����DMA������ɺ��ж�
	DMA_RemapConfig(DMA1_Channel2, DMA_ReqNum1, DMA_REQ_I2C0_RX); /// DMA�����ӳ�䵽����

	DMA_Cmd(DMA1_Channel2, ENABLE);

	NVIC_ClearPendingIRQ(DMAC_CH1_2_IRQn);
	NVIC_EnableIRQ(DMAC_CH1_2_IRQn);
#endif
	I2C_DMACmd(I2C0, I2C_DMAReq_Rx, ENABLE); //����DMAʹ��
	I2C_RxDMAITthreshold(I2C_RX_DMA_IT_0);	 //��������ˮƽ,������ FIFO ����Ч���ݵĸ������ڻ���� DMARDL+1ʱ������һ��dma_rx_req �źš�
	I2C_Cmd(I2C0, ENABLE);
}

int main(void)
{
	uint8_t i;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C0, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	GPIO_Cfg();
	I2C0_Slave();
	while (1)
		;
}
void DMAC_CH1_2_Handler() // 60us
{
	DMA_ClearITPendingBit(DMA1_FLAG_TC2);
}
