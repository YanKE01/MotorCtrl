#include <stdio.h>
#include "lcm32f037.h"
#include "lcm32f037_rcc.h"
#include "lcm32f037_gpio.h"
#include "lcm32f037_ssp.h"
#include "lcm32f037_dma.h"

/********************************************************************************
 * @function:  SSP2-MASTERMODE
 * @attention:
 ******************************************************************************/
#define DMA_ENABLE 1

#define SSP2_SIZE 8UL
#define SSP2_DR_Address (0x40006008)

uint8_t Master_TX_BUFF[8] = {0X11, 0X22, 0X33, 0X44, 0X55, 0X66, 0X77, 0x88};
uint8_t Master_RX_BUFF[8] = {0};
uint8_t TX_offset, RX_offset;

void delay(int i)
{
	while (i--)
		;
}
void IO_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_Init(GPIOF, &GPIO_InitStruct);

	GPIO_PinAFConfig(GPIOF, GPIO_PinSource4, GPIO_AF_0); // FSS
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource3, GPIO_AF_0); // SCK

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_5); // MISO
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_4); // MOSI
}
void SSP2_Master_Cfg(void)
{
	SPI_InitTypeDef SPI_InitStruct;

	RCC_APB0PeriphClockCmd(RCC_APB0Periph_SSP2, ENABLE);

	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;	   // if Master mode is needed,edit it !
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b; // data length in transmitting.
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;		   // idal status
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;	   // sample
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;	 // MSB is alaways.
	SPI_InitStruct.SPI_SlaveTx = SPI_SlaveTx_Enable; // control whether the spi send data only in slave mode.
	SPI_Init(SPI2, &SPI_InitStruct);

#if DMA_ENABLE
	DMA_InitTypeDef DMA_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA, ENABLE);

	DMA_DeInit(DMA1_Channel2);
	DMA_InitStructure.DMA_PeripheralBaseAddr = SSP2_DR_Address;				//用来设置DMA传输的外设基地址
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&Master_TX_BUFF;		//内存基地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;						//设置数据传输方向，即决定是从外设读取数据到内存还是从内存读数据到外设，这里我们是从外设ADC_DR寄存器读数据到内存
	DMA_InitStructure.DMA_BufferSize = SSP2_SIZE;							//设置一次传输数据量的大小
	DMA_InitStructure.DMA_MSIZE = DMA_MSIZE_1;								//突发事务传输长度
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;		//设置传输数据的时候 （外设） 地址是不变还是递增。
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;					//设置传输数据的时候 （内存 ）地址是不变还是递增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //设置外设的数据长度是为字节传输（8bits）还是半字（16bits）还是字传输（32bits）
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;			//设置内存的数据长度，同上。
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;							//设置是否进行循环采集
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;						//设置优先级
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;							//内存到内存使能
	DMA_Init(DMA1_Channel2, &DMA_InitStructure);							//设置是否是存储器到存储器模式传输

	DMA_ITConfig(DMA1_Channel2, DMA1_IT_TC2, ENABLE);			  //配置DMA发送完成后中断
	DMA_RemapConfig(DMA1_Channel2, DMA_ReqNum0, DMA_REQ_SSP2_TX); /// DMA请求号映射到外设

	SPI_DMACmd(SPI2, SPI_DMAReq_Tx, ENABLE);
	SPI_Cmd(SPI2, ENABLE);

	DMA_Cmd(DMA1_Channel2, ENABLE);

	NVIC_ClearPendingIRQ(DMAC_CH1_2_IRQn);
	NVIC_EnableIRQ(DMAC_CH1_2_IRQn);
#endif
}
int main()
{
	SystemInit();
	SetSysClock(); //主频配置
	IO_Init();
	RX_offset = 0;
	SSP2_Master_Cfg();
	while (1)
	{
	}
}
void DMAC_CH1_2_Handler()
{
	DMA_ClearITPendingBit(DMA1_FLAG_TC2);
	if (SPI_GetITStatus(SPI2, SPI_IT_Rx) == 1)
	{
		Master_RX_BUFF[RX_offset++] = SPI_ReceiveData8(SPI2);
	}
	if (RX_offset >= 8)
	{
		RX_offset = 0;
	}
}
