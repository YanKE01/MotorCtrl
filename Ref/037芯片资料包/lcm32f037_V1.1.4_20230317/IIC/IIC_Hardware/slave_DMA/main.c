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
IIC  IO初始化
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
从机配置
**************************************/
void I2C0_Slave()
{
	I2C_InitTypeDef I2C_InitStruct;
	I2C_InitStruct.I2C_mode = I2C_SlaveOnlyMode;							 //从机模式
	I2C_InitStruct.I2C_StopDetSlave = I2C_StopDet_SlaveActive;				 //从机模式下，当寻址匹配时产生STOP_DET中断
	I2C_InitStruct.I2C_RxFifoFullHold = I2C_RxFifoFullHold_ENABLE;			 //决定I2C在RX FIFO达到RX_RX_BUFFER_DEPTH时是否hold总线
	I2C_InitStruct.I2C_TxEmptyIntr = I2C_TxEmptyIntr_ENABLE;				 //控制TX_EMPTY中断的产生方式
	I2C_InitStruct.I2C_SlaveAddressedLength = I2C_SlaveAddressedLength_7bit; //地址长度
	I2C_Init(I2C0, &I2C_InitStruct);
	I2C_SlaveAddressConfig(I2C0, 0x05);		 //设置地址
	I2C_ITConfig(I2C0, I2C_IT_ALL, DISABLE); //中断配置
	I2C_ClearITPendingBit(I2C0, I2C_IT_ALL); //清中断
//使用DMA将接收数据从外设到数组Receive_Buff
#if DMA_ENABLE
	DMA_InitTypeDef DMA_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA, ENABLE);

	DMA_DeInit(DMA1_Channel2);
	DMA_InitStructure.DMA_PeripheralBaseAddr = I2C_DR_Address;				//用来设置DMA传输的外设基地址
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&Receive_Buff;			//内存基地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;						//设置数据传输方向，即决定是从外设读取数据到内存还是从内存读数据到外设，这里我们是从外设ADC_DR寄存器读数据到内存
	DMA_InitStructure.DMA_BufferSize =I2C_SIZE ;									//设置一次传输数据量的大小
	DMA_InitStructure.DMA_MSIZE = DMA_MSIZE_1;								//突发事务传输长度
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;		//设置传输数据的时候 （外设） 地址是不变还是递增。
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;					//设置传输数据的时候 （内存 ）地址是不变还是递增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //设置外设的数据长度是为字节传输（8bits）还是半字（16bits）还是字传输（32bits）
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;			//设置内存的数据长度，同上。
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;							//设置是否进行循环采集
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;						//设置优先级
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;							//内存到内存使能
	DMA_Init(DMA1_Channel2, &DMA_InitStructure);							//设置是否是存储器到存储器模式传输

	DMA_ITConfig(DMA1_Channel2, DMA1_FLAG_TC2, ENABLE);			  //配置DMA发送完成后中断
	DMA_RemapConfig(DMA1_Channel2, DMA_ReqNum1, DMA_REQ_I2C0_RX); /// DMA请求号映射到外设

	DMA_Cmd(DMA1_Channel2, ENABLE);

	NVIC_ClearPendingIRQ(DMAC_CH1_2_IRQn);
	NVIC_EnableIRQ(DMAC_CH1_2_IRQn);
#endif
	I2C_DMACmd(I2C0, I2C_DMAReq_Rx, ENABLE); //接收DMA使能
	I2C_RxDMAITthreshold(I2C_RX_DMA_IT_0);	 //接收数据水平,当接收 FIFO 内有效数据的个数大于或等于 DMARDL+1时，产生一个dma_rx_req 信号。
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
