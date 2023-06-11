#include "lcm32f037_conf.h"
#include "lcm32f037.h"
#include "lcm32f037_rcc.h"
#include "lcm32f037_flash.h"
#include "lcm32f037_gpio.h"
#include "lcm32f037_uart.h"
#include "lcm32f037_eeprom.h"
#include "stdio.h"
#include "string.h"
#define P_TestShot (GPIOA->IDR & (1 << 2))
uint16_t uart_send_buff[8] = {0x55, 0x66, 0x77, 0x88, 0x99, 0x88, 0x77, 0x66};
uint8_t R_BUF0, UART_CNT, start_flag, Rec_Flag = 0;
uint8_t UART_BUFF[8];
uint16_t half_word_data;
uint32_t temp_prog_addr, prog_addr, word_data;
FLASH_Status flash_write_status;
uint16_t DataVarr[8] = {0};
uint16_t write_cnt = 0;

void delay(uint32_t delaytime)
{
	while (delaytime--)
		;
}

void gpio_in_mode_set(GPIO_TypeDef *gpio_ptr, uint32_t port_num)
{
	gpio_ptr->MODER = (gpio_ptr->MODER & ~(0x3 << (port_num << 1))) |
					  (0x0 << (port_num << 1));
}
uint16_t tempAddr[NB_OF_VAR]= {0x1111, 0x2222, 0x3333, 0x4444, 0x5555, 0x6666, 0x7777, 0x8888};
int main()
{
	SystemInit();
	SetSysClock(); // 主频配置
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	FLASH_Unlock();

	//	write_cnt=150;
	//	gpio_in_mode_set(GPIOA,2);
	//	delay(100);
	//	while(P_TestShot);

	EE_Init();
	memcpy(VirtAddVarTab ,tempAddr,8);//不可缺少，否则换页会丢失数据
	EE_WriteVariable(tempAddr[0], 0x0001);
	EE_WriteVariable(tempAddr[1], 0x0002);
	EE_WriteVariable(tempAddr[2], 0x0003);
	EE_WriteVariable(tempAddr[3], 0x0004);
	EE_WriteVariable(tempAddr[4], 0x0005);
	EE_WriteVariable(tempAddr[5], 0x0006);
	EE_WriteVariable(tempAddr[6], 0x0007);
	EE_WriteVariable(tempAddr[7], 0x0008);

	EE_ReadVariable(tempAddr[0], &DataVarr[0]);
	EE_ReadVariable(tempAddr[1], &DataVarr[2]);
	EE_ReadVariable(tempAddr[2], &DataVarr[3]);
	EE_ReadVariable(tempAddr[3], &DataVarr[3]);
	EE_ReadVariable(tempAddr[4], &DataVarr[4]);
	EE_ReadVariable(tempAddr[5], &DataVarr[5]);
	EE_ReadVariable(tempAddr[6], &DataVarr[6]);
	EE_ReadVariable(tempAddr[7], &DataVarr[7]);
	while (1)
	{
		//		while(P_TestShot);
		//		EE_WriteVariable(0x1111, 0x4567);
		//		write_cnt--;
		//		if(write_cnt==150)
		//		{
		//			return 1;
		//		}
	}
}
