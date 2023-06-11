#include "lcm32f037_conf.h"
#include "lcm32f037.h"
#include "lcm32f037_rcc.h"
#include "lcm32f037_flash.h"
#include "lcm32f037_gpio.h"
#include "lcm32f037_uart.h"

#define PAGE_SIZE (0x200)	 /* 512byte */
#define FLASH_SIZE (0x10000) /* 64 KBytes */
#define FLASH_IMAGE_SIZE (uint32_t)(FLASH_SIZE - (0x08010000 - 0x0800F000))

#define OSCH_IN 0
#define PLL_IN 1
#define BYPASS_IN 2
#define HSI_IN 3
#define WORLD_WRITE 0 //
#define HALF_WRITE 1

uint8_t R_BUF0, UART_CNT, start_flag, Rec_Flag = 0;
uint8_t UART_BUFF[8];
uint16_t half_word_data;
uint32_t temp_prog_addr, prog_addr, word_data;
FLASH_Status flash_write_status;

void delay(uint32_t delaytime)
{
	while (delaytime--)
		;
}
uint32_t MAINFLASH_DATA_READ(uint16_t target_address)
{
	uint32_t readdata;
	readdata = *(volatile uint32_t *)(target_address);
	return readdata;
}

void Uart1_Send_Buff(uint8_t R_BUF1)
{
	UART1->DR = R_BUF1;
	while (UART_GetFlagStatus(UART1, UART_FLAG_TXFE) == RESET)
		;
}

void MAINFLASH_READ(uint32_t start_address, uint32_t range)
{
	uint32_t addrflg;
	for (addrflg = start_address; addrflg <= start_address + range; addrflg += 0x04) //Addr_Range
	{

		Uart1_Send_Buff((uint8_t)(MAINFLASH_DATA_READ(addrflg) >> 24));
		delay(1000);
		Uart1_Send_Buff((uint8_t)(MAINFLASH_DATA_READ(addrflg) >> 16));
		delay(1000);
		Uart1_Send_Buff((uint8_t)(MAINFLASH_DATA_READ(addrflg) >> 8));
		delay(1000);
		Uart1_Send_Buff((uint8_t)MAINFLASH_DATA_READ(addrflg));
		delay(1000);
	}
}

void MAINFLASH_WRITE(uint32_t start_address, uint8_t write_mode)
{
	if (start_flag)
	{
		prog_addr = start_address;
		temp_prog_addr = prog_addr;
		start_flag = 0;
	}
	if (Rec_Flag >= 4)
	{
		switch (write_mode)
		{
		case HALF_WRITE:
		{

			half_word_data = ((uint16_t)UART_BUFF[2] << 8) | UART_BUFF[1];
			if (((temp_prog_addr / PAGE_SIZE) != (prog_addr / PAGE_SIZE)))
				flash_write_status = FLASH_ErasePage(prog_addr);
			if (flash_write_status == FLASH_COMPLETE)
				;
			flash_write_status = FLASH_ProgramHalfWord(prog_addr, half_word_data);
			temp_prog_addr = prog_addr;
			prog_addr += 0x02;
			UART_CNT = 0;
			Rec_Flag = 0;
		};
		break;

		case WORLD_WRITE:
		{

			word_data = (UART_BUFF[0] << 24) | (UART_BUFF[1] << 16) | (UART_BUFF[2] << 8) | UART_BUFF[3];
			if (((temp_prog_addr / PAGE_SIZE) != (prog_addr / PAGE_SIZE)) && (flash_write_status == FLASH_COMPLETE))
				flash_write_status = FLASH_ErasePage(prog_addr);

			if (flash_write_status == FLASH_COMPLETE)
				;

			flash_write_status = FLASH_ProgramWord(prog_addr, word_data);

			temp_prog_addr = prog_addr;
			prog_addr += 0x04;
			UART_CNT = 0;
			Rec_Flag = 0;
		};
		break;
		default:
			break;
		}
	}
}

void UART1_Init()
{
	UART_InitTypeDef UART_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART1, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_UART1CLKConfig(RCC_UART1CLK_RCH);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_1);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; //	PA2--UART1.Tx  PA3--UART1.Rx
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	UART_StructInit(&UART_InitStruct);
	UART_InitStruct.UART_BaudRate = 9600;
	UART_InitStruct.UART_WordLength = UART_WordLength_8b;
	UART_InitStruct.UART_StopBits = UART_StopBits_1;
	UART_InitStruct.UART_Parity = UART_Parity_No;
	UART_InitStruct.UART_HardwareFlowControl = UART_HardwareFlowControl_None;
	UART_InitStruct.UART_Mode = UART_Mode_Rx | UART_Mode_Tx;
	UART_Init(UART1, &UART_InitStruct);
	UART_ITConfig(UART1, UART_IT_RX, ENABLE);
	UART_Cmd(UART1, ENABLE);
	/* Clear flag for 1st byte */
	UART_GetFlagStatus(UART1, UART_STATUS_TXFE);

	NVIC_ClearPendingIRQ(UART1_IRQn);
	NVIC_SetPriority(UART1_IRQn, 1);
	NVIC_EnableIRQ(UART1_IRQn);

	UART_CNT = 0;
}

void SysClkInit(uint8_t CLK_flg)
{
	OSCH_GPIO_INIT();
	switch (CLK_flg)
	{
	case OSCH_IN:
	{
		FLASH_LATENCY(0); //0:sysclk<32MHz 1:32<=sysclk<64Mhz  2:64<=sysclk<=96MHz
		chipctrl_access();
		CHIPCTRL->CLK_CFG = 0x000A0000; //外部时钟输入使能
		while (!(CHIPCTRL->STS & CHIPCTRL_STS_OSCH_STB_Msk))
			;
		chipctrl_access();
		CHIPCTRL->CLK_CFG |= 0x00100000;
		__dekey();
		while (!(CHIPCTRL->STS & CHIPCTRL_STS_SYS_CLK_LOCK_Msk))
			;
	};
	break;

	case PLL_IN:
	{
		FLASH_LATENCY(2); //0:sysclk<32MHz 1:32<=sysclk<64Mhz  2:64<=sysclk<=96MHz
		chipctrl_access();
		CHIPCTRL->CLK_CFG = 0x000A0000; //外部时钟输入使能
		while (!(CHIPCTRL->STS & CHIPCTRL_STS_OSCH_STB_Msk))
			;
		chipctrl_access();
		CHIPCTRL->PLL_CFG = 0x00000021; //4.5*OSCH //此处配置PLL分频和输入源
		chipctrl_access();
		CHIPCTRL->CLK_CFG |= 0x000B0000;
		while (!(CHIPCTRL->STS & CHIPCTRL_STS_PLL_LOCK_Msk))
			;
		chipctrl_access();
		CHIPCTRL->CLK_CFG |= 0x002B0000;
		__dekey();
		while (!(CHIPCTRL->STS & CHIPCTRL_STS_SYS_CLK_LOCK_Msk))
			;
	};
	break;

	case BYPASS_IN:
	{
		FLASH_LATENCY(0); //0:sysclk<32MHz 1:32<=sysclk<64Mhz  2:64<=sysclk<=96MHz
		chipctrl_access();
		CHIPCTRL->OSCH_CFG = 0x00000087; // Bypass使能
		chipctrl_access();
		CHIPCTRL->CLK_CFG = 0x000A0000;	 //外部时钟输入使能
		while (!(CHIPCTRL->STS & CHIPCTRL_STS_OSCH_STB_Msk))
			;
		chipctrl_access();
		CHIPCTRL->CLK_CFG |= 0x00100000;
		__dekey();
		while (!(CHIPCTRL->STS & CHIPCTRL_STS_SYS_CLK_LOCK_Msk))
			;
	};
	break;

	case HSI_IN:
	{
		FLASH_LATENCY(0); //0:sysclk<32MHz 1:32<=sysclk<64Mhz  2:64<=sysclk<=96MHz
		chipctrl_access();
		CHIPCTRL->CLK_CFG = 0x00080000;
		__dekey();
		while (!(CHIPCTRL->STS & CHIPCTRL_STS_RCH_STB_Msk))
			;
	};
	break;

	default:
		break;
	}
}

int main()
{

	SysClkInit(HSI_IN); //CLK_channel :RCH = 16MHZ
	UART1_Init();		//TX:PA2  Baudrate:9600 Databits:8 Stopbits:1
	FLASH_Unlock();
	start_flag = 1;
	//MAINFLASH_READ(0x08000000, 0x2000);//StartAdress,range
	while (1)
	{
		MAINFLASH_WRITE(0x0800C000, HALF_WRITE); //StartAdress ,write_mode
	}
}

void UART1_Handler()
{
	if (UART_GetFlagStatus(UART1, UART_STATUS_RXFE) == RESET) //接收到数据
	{
		R_BUF0 = UART1->DR;
		UART_BUFF[UART_CNT] = R_BUF0;
		++UART_CNT;
		Rec_Flag++;
	}
}
