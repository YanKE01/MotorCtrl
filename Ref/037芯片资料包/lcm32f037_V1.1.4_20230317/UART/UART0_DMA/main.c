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

	RCC_UART0CLKConfig(RCC_UART0CLK_RCH); //选择UART0时钟源，不配置默认总线时钟

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
	DMA_InitStructure.DMA_PeripheralBaseAddr = UART_DR_Address;				//用来设置DMA传输的外设基地址
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&uart_send_buff;		//内存基地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;						//设置数据传输方向，即决定是从外设读取数据到内存还是从内存读数据到外设，这里我们是从外设ADC_DR寄存器读数据到内存
	DMA_InitStructure.DMA_BufferSize = UART_SIZE;							//设置单次传输(single transaction)的总数
	DMA_InitStructure.DMA_MSIZE = DMA_MSIZE_1;								//突发事务传输长度
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;		//设置传输数据的时候 （外设） 地址是不变还是递增。
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;					//设置传输数据的时候 （内存 ）地址是不变还是递增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //设置外设的数据长度是为字节传输（8bits）还是半字（16bits）还是字传输（32bits）
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;			//设置内存的数据长度，同上。
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;							//设置是否进行循环采集
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;						//设置优先级
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;							//内存到内存使能
	DMA_Init(DMA1_Channel2, &DMA_InitStructure);							//设置是否是存储器到存储器模式传输

	DMA_ITConfig(DMA1_Channel2, DMA1_IT_TC2, ENABLE);			   //配置DMA发送完成后中断
	DMA_RemapConfig(DMA1_Channel2, DMA_ReqNum0, DMA_REQ_UART0_TX); /// DMA请求号映射到外设

	DMA_Cmd(DMA1_Channel2, ENABLE);
	/*若需要DMA中断，则配置注释掉的*/
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
	SetSysClock(); //主频配置
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART0, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

	GPIO_Config(); //观测用，无实际意义
	UART0_Config();
	while (1)
	{
		if (DMA_GetFlagStatus(DMA1_FLAG_TC2) == 1) //查询方式清标志位
		{
			DMA_ClearITPendingBit(DMA1_FLAG_TC2);
			GPIO_SetBits(GPIOA, GPIO_Pin_1); //观测用，无实际意义
		}
		else
			GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	}
}
// void DMAC_CH1_2_Handler() //60us
//{
//	DMA_ClearITPendingBit(DMA1_FLAG_TC2);
// }
