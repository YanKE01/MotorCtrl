#include <stdio.h>
#include "lcm32f037.h"
#include "lcm32f037_rcc.h"
#include "lcm32f037_gpio.h"
#include "lcm32f037_ssp.h"
/********************************************************************************
 * @function:  SSP0-MASTERMODE
 * @attention:
 ******************************************************************************/
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

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource4, GPIO_AF_0); // FSS
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_0); // SCK
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_0); // MISO
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_0); // MOSI
}
void SSP0_Master_Cfg(void)
{
	SPI_InitTypeDef SPI_InitStruct;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SSP0, ENABLE);

	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;	   // if Master mode is needed,edit it !
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b; // data length in transmitting.
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;		   // idal status
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;	   // sample
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;	 // MSB is alaways.
	SPI_InitStruct.SPI_SlaveTx = SPI_SlaveTx_Enable; // control whether the spi send data only in slave mode.
	SPI_Init(SPI0, &SPI_InitStruct);

	SPI_ITConfig(SPI0, SPI_IT_Tx | SPI_IT_Rx, ENABLE);
	SPI_Cmd(SPI0, ENABLE);

	NVIC_ClearPendingIRQ(SPI0_IRQn);
	NVIC_SetPriority(SPI0_IRQn, 0);
	NVIC_EnableIRQ(SPI0_IRQn);
}
int main()
{
	SystemInit();
	SetSysClock(); //Ö÷ÆµÅäÖÃ
	IO_Init();
	TX_offset = 0;
	RX_offset = 0;
	SSP0_Master_Cfg();
	SPI_SendData8(SPI0, Master_TX_BUFF[TX_offset++]);
	while (1)
		;
}
void SSP0_Handler(void)
{
	if (SPI_GetITStatus(SPI0, SPI_IT_Rx) == 1)
	{
		Master_RX_BUFF[RX_offset++] = SPI_ReceiveData8(SPI0);
	}
	if (SPI_GetITStatus(SPI0, SPI_IT_Tx) == 1)
	{
		SPI_SendData8(SPI0, Master_TX_BUFF[TX_offset++]);
	}
	if (TX_offset >= 8)
	{
		TX_offset = 0;
		RX_offset = 0;
	}
}
