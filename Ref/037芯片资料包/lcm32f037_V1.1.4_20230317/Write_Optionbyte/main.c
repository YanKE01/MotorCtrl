#include "lcm32f037_conf.h"
#include "lcm32f037.h"
#include "lcm32f037_rcc.h"
#include "lcm32f037_flash.h"
#include "lcm32f037_gpio.h"
#include "lcm32f037_uart.h"
/**
 ******************************************************************************
 * @function:  OPT /SYS/; PROG
 * @attention:
 *
 *
 *
 ******************************************************************************/
void delay(uint32_t dly)
{
	volatile uint32_t i = 0;
	while (i++ < dly)
		;
}
void TRIM_INIT()
{
	uint32_t BGP;
	uint32_t RCH;
	uint32_t RCL;
	uint32_t RCH_TRIM;
	uint32_t RCL_TRIM;
	uint32_t ADCG;
	uint32_t ADCV;
	uint32_t adc_trim;
	uint32_t OP0_TRIM;
	uint32_t OP1_TRIM;
	uint32_t OP2_TRIM;
	uint32_t OPA_TRIM;
	uint32_t VBG_TRIM;
	uint32_t VBG_OP2_TRIM;

	OP2_TRIM = (ANACTRL->OPA2_CSR & 0x001f0000);
	OP2_TRIM = (OP2_TRIM ^ 0x001f0000) + (0x00e00000);
	OP2_TRIM = OP2_TRIM + (((OP2_TRIM & 0x00ff0000) << 8) ^ 0Xff000000);
	BGP = CHIPCTRL->BGR_CFG;
	BGP = (BGP ^ 0x0000001f) + (0x000000c0);
	VBG_TRIM = BGP + (((BGP & 0X000000FF) << 8) ^ 0X0000FF00);
	VBG_OP2_TRIM = OP2_TRIM + VBG_TRIM;
	write_sm_flash_n(0x1FFFF5E4, VBG_OP2_TRIM); // VBG校准值写入信息区

	RCH = CHIPCTRL->RCH_CFG;
	RCH = RCH & 0X000000FF;
	RCH = (RCH ^ 0x00ff007f);
	RCH_TRIM = RCH + (((RCH & 0X000000FF) << 8) ^ 0X0000FF00);
	write_sm_flash_n(0x1FFFF5E0, RCH_TRIM); // rch 校准直写入信息区

	RCL = CHIPCTRL->RCL_CFG;
	RCL = (RCL ^ 0x00ff001f) + (0x000000c0);
	RCL_TRIM = RCL + (((RCL & 0X000000FF) << 8) ^ 0X0000FF00);
	write_sm_flash_n(0x1FFFF5E8, RCL_TRIM); // rcl 校准值固化

	ADCG = (ADC->TRIM) & 0x000000ff; //写入
	ADCG = (ADCG << 16) ^ 0x005c0000;
	ADCG = ADCG + (((ADCG & 0X00ff0000) << 8) ^ 0Xff000000);
	ADCV = (ADC->TRIM) & 0x00ff0000;
	ADCV = (ADCV >> 16) ^ 0x00000068;
	ADCV = ADCV + (((ADCV & 0X000000FF) << 8) ^ 0x0000ff00);
	adc_trim = ADCG + ADCV;
	write_sm_flash_n(0x1FFFF5EC, adc_trim); // adc 校准值固化

	OP0_TRIM = ((ANACTRL->OPA0_CSR & 0x001f0000) >> 16);
	OP0_TRIM = (OP0_TRIM ^ 0x0000001f) + (0x000000e0);
	OP0_TRIM = OP0_TRIM + (((OP0_TRIM & 0x000000ff) << 8) ^ 0X0000FF00);
	OP1_TRIM = (ANACTRL->OPA1_CSR & 0x001f0000);
	OP1_TRIM = (OP1_TRIM ^ 0x001f0000) + (0x00e00000);
	OP1_TRIM = OP1_TRIM + (((OP1_TRIM & 0x00ff0000) << 8) ^ 0Xff000000);
	OPA_TRIM = OP1_TRIM + OP0_TRIM;
	write_sm_flash_n(0x1FFFF5F0, OPA_TRIM); // OPA0 1
}

void clkpout_gpio_cfg()
{

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_0);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_2);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}
int main()
{
	SystemInit();
	SetSysClock(); //主频配置
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM1, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_ANACTRL, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_ADC, ENABLE);
	/****************************************************/
	//  校准信息区字节

	//	rch_trim(0xB9); //0-FF  C0
	//	bgr_trim(0x23); //寄存器校准值 0-3F  20
	//	adc_trim(0x0060067);

	//	rcl_trim(0x3f);
	//	opa0_trim1(0x0d);
	//	opa1_trim1(0x10);
	//	opa2_trim1(0x10);

	clkpout_gpio_cfg();
	mco_set(3, 3); //系统时钟8分频

	chipctrl_access();
	CHIPCTRL->PWR_CFG = 0x000C0001; // vrh=2.5v PA0 2.5
	__dekey();

	//	ERASE_SYSTEM_MERMORY();  //擦除信息区 等校准字节
	//	TRIM_INIT();             //固化信息区 各个校准字节
	/*******************************************************/

	//烧死 boot0 ,固定从mainflash启动  PF3下拉无效
	//	ERASE_OPT();  //擦除选项字节   会恢复度保护
	//	write_opt_flash_n(0x1ffff600,0x00ff04Fb);//14eb写PA9 PA10 SWD;  0X00FF04FB 是 pa13PA14  且烧死boot
	//	write_opt_flash_n(0x1ffff610,0X55AA55AA);
	//	write_opt_flash_n(0x1ffff614,0X55AA55AA);
	//	write_opt_flash_n(0x1ffff618,0X55AA55AA);
	//	write_opt_flash_n(0x1ffff61C,0X55AA55AA);
	//	write_opt_flash_n(0x1ffff620,0X55AA55AA);

	while (1)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_1);
		delay(2000);
		GPIO_ResetBits(GPIOA, GPIO_Pin_1);
		delay(2000);
	}
}
