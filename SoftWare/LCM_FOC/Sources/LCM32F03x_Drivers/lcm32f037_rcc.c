/**
 ******************************************************************************
 * @file    lcm32f037_rcc.c
 * @author  MCD Application Team
 * @version V1.0.0
 * @date    2021-05-21
 * @brief   This file provides all the rcc emulation firmware functions.
 ******************************************************************************/
/**
 ******************************************************************************
 * @attention:
 *
 *
 *
 *
 ******************************************************************************/
//宏定义需要配合SystemInit()函数使用，在主程序中调用此函数
//如果不调用SystemInit()。sysclk默认使用内部rch 16mhz

//#define HSI_SYSCLK_FREQ_8MHz 8000000
//#define HSI_SYSCLK_FREQ_16MHz 16000000
//#define HSI_SYSCLK_FREQ_24MHz 24000000
//#define HSI_SYSCLK_FREQ_32MHz 32000000
//#define HSI_SYSCLK_FREQ_40MHz 40000000
//#define HSI_SYSCLK_FREQ_48MHz 48000000
//#define HSI_SYSCLK_FREQ_56MHz  56000000
//#define HSI_SYSCLK_FREQ_64MHz 64000000
//#define HSI_SYSCLK_FREQ_72MHz 72000000
//#define HSI_SYSCLK_FREQ_84MHz  84000000
//#define HSI_SYSCLK_FREQ_88MHz  88000000
//#define HSI_SYSCLK_FREQ_92MHz  92000000
#define HSI_SYSCLK_FREQ_96MHz 96000000

//#define HSE_SYSCLK_FREQ_8MHz   8000000
//#define HSE_SYSCLK_FREQ_16MHz  16000000
//#define HSE_SYSCLK_FREQ_24MHz 24000000
//#define HSE_SYSCLK_FREQ_32MHz  32000000          //以外部晶振16M 为前提  （8m晶振频率减半,sysclk16MHZ）
//#define HSE_SYSCLK_FREQ_40MHz  40000000
//#define HSE_SYSCLK_FREQ_48MHz 48000000
//#define HSE_SYSCLK_FREQ_56MHz  56000000
//#define HSE_SYSCLK_FREQ_64MHz 64000000
//#define HSE_SYSCLK_FREQ_72MHz 72000000
//#define HSE_SYSCLK_FREQ_84MHz  84000000
//#define HSE_SYSCLK_FREQ_88MHz  88000000
//#define HSE_SYSCLK_FREQ_92MHz  92000000
//#define HSE_SYSCLK_FREQ_96MHz 96000000

#include "lcm32f037_conf.h"
#include "lcm32f037.h"
#include "lcm32f037_rcc.h"
#include "lcm32f037_flash.h"
#include "lcm32f037_gpio.h"
#include "lcm32f037_pwr.h"

void delay10us(uint32_t u32Cnt)
{
    uint32_t u32end;
    uint32_t TempLoad;
    uint32_t TempVal;
    uint32_t TempCtrl;
    TempLoad = SysTick->LOAD;
    TempVal = SysTick->VAL;
    TempCtrl = SysTick->CTRL;

    SysTick->CTRL = 0;
    SysTick->LOAD = 0xFFFFFF;
    SysTick->VAL = 0;
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
#if (HSI_SYSCLK_FREQ_8MHz | HSE_SYSCLK_FREQ_8MHz)
    u32end = 0xFFFFB0; // 0x1000000 - SystemCoreClock/100000
#endif
#if (HSI_SYSCLK_FREQ_16MHz | HSE_SYSCLK_FREQ_16MHz)
    u32end = 0xFFFF60; // 0x1000000 - SystemCoreClock/100000
#endif
#if (HSI_SYSCLK_FREQ_24MHz | HSE_SYSCLK_FREQ_24MHz)
    u32end = 0xFFFF10; // 0x1000000 - SystemCoreClock/100000
#endif
#if (HSI_SYSCLK_FREQ_32MHz | HSE_SYSCLK_FREQ_32MHz)
    u32end = 0xFFFEC0; // 0x1000000 - SystemCoreClock/100000
#endif
#if (HSI_SYSCLK_FREQ_40MHz | HSE_SYSCLK_FREQ_40MHz)
    u32end = 0xFFFE70; // 0x1000000 - SystemCoreClock/100000
#endif
#if (HSI_SYSCLK_FREQ_48MHz | HSE_SYSCLK_FREQ_48MHz)
    u32end = 0xFFFE20; // 0x1000000 - SystemCoreClock/100000
#endif
#if (HSI_SYSCLK_FREQ_56MHz | HSE_SYSCLK_FREQ_56MHz)
    u32end = 0xFFFDD0; // 0x1000000 - SystemCoreClock/100000
#endif
#if (HSI_SYSCLK_FREQ_64MHz | HSE_SYSCLK_FREQ_56MHz)
    u32end = 0xFFFD80; // 0x1000000 - SystemCoreClock/100000
#endif
#if (HSI_SYSCLK_FREQ_72MHz | HSE_SYSCLK_FREQ_72MHz)
    u32end = 0xFFFD30; // 0x1000000 - SystemCoreClock/100000
#endif
#if (HSI_SYSCLK_FREQ_84MHz | HSE_SYSCLK_FREQ_84MHz)
    u32end = 0xFFFCB8; // 0x1000000 - SystemCoreClock/100000
#endif
#if (HSI_SYSCLK_FREQ_88MHz | HSE_SYSCLK_FREQ_88MHz)
    u32end = 0xFFFC90; // 0x1000000 - SystemCoreClock/100000
#endif
#if (HSI_SYSCLK_FREQ_92MHz | HSE_SYSCLK_FREQ_92MHz)
    u32end = 0xFFFC68; // 0x1000000 - SystemCoreClock/100000
#endif
#if (HSI_SYSCLK_FREQ_96MHz | HSE_SYSCLK_FREQ_96MHz)
    u32end = 0xFFFC40; // 0x1000000 - SystemCoreClock/100000
#endif
    while (u32Cnt-- > 0)
    {
        SysTick->VAL = 0;
        while (SysTick->VAL > u32end)
        {
            ;
        }
    }
    SysTick->LOAD = TempLoad;
    SysTick->VAL = TempVal;
    SysTick->CTRL = TempCtrl;
}
/*--------------------------------------------------------------------------------------------
开晶振复用管脚： PF1 PF0
  --------------------------------------------------------------------------------------------*/

void OSCH_GPIO_INIT()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);
    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
    GPIO_Init(GPIOF, &GPIO_InitStructure);
    GPIO_PinAFConfig(GPIOF, GPIO_PinSource0, GPIO_AF_2);
    GPIO_PinAFConfig(GPIOF, GPIO_PinSource1, GPIO_AF_2);
}

/*--------------------------------------------------------------------------------------------
FLASH 取指延迟设置
  --------------------------------------------------------------------------------------------*/
void FLASH_LATENCY(uint8_t clkrank)
{
    switch (clkrank)
    {
    case 0x00:
        FLASH->ACR = 0x00000010;
        break;
    case 0x01:
        FLASH->ACR = 0x00000011;
        break;
    case 0x02:
        FLASH->ACR = 0x00000012;
        break;
    default:
        break;
    }
}

void Sysclk_ResetRch(void) //运行中 变频之前 需要调用此函数
{
    chipctrl_access();
    CHIPCTRL->CLK_CFG &= 0xFFCFFFFF; // rch
    __dekey();
    chipctrl_access();
    CHIPCTRL->CLK_CFG = 0x00080000; // rch
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_SYS_CLK_LOCK_Msk))
        ;
    FLASH_LATENCY(0);
}

//////////////////////////////////////////////内部晶振16MHZ 为基础//////////////////////////
void HSI_SetSysClockTo8()
{
    FLASH_LATENCY(0); // 0:sysclk<32MHz 1:32<=sysclk<64Mhz  2:64<=sysclk<=96MHz
    chipctrl_access();
    CHIPCTRL->CLK_CFG = 0x00080000; // rch
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_RCH_STB_Msk))
        ;
    chipctrl_access();
    CHIPCTRL->CLK_CFG |= 0x00000040; // 046:3.69M   47:3.2M   48:2.82M   49:2.4M  080:16M
    __dekey();
}
void HSI_SetSysClockTo16()
{
    FLASH_LATENCY(0); // 0:sysclk<32MHz 1:32<=sysclk<64Mhz  2:64<=sysclk<=96MHz
    chipctrl_access();
    CHIPCTRL->CLK_CFG = 0x00080000; // rch
    __dekey();
}
void HSI_SetSysClockTo24()
{
    FLASH_LATENCY(1); // 0:sysclk<32MHz 1:32<=sysclk<64Mhz  2:64<=sysclk<=96MHz
    chipctrl_access();
    CHIPCTRL->CLK_CFG = 0x00080000; // rch
    __dekey();

    chipctrl_access();
    CHIPCTRL->PLL_CFG = 0x00001016;
    __dekey();
    chipctrl_access();
    CHIPCTRL->CLK_CFG |= 0x00090000;
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_PLL_LOCK_Msk))
        ;
    chipctrl_access();
    CHIPCTRL->CLK_CFG |= 0x00290000;
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_SYS_CLK_LOCK_Msk))
        ;
}
void HSI_SetSysClockTo32()
{
    FLASH_LATENCY(1); // 0:sysclk<32MHz 1:32<=sysclk<64Mhz  2:64<=sysclk<=96MHz
    chipctrl_access();
    CHIPCTRL->CLK_CFG = 0x00080000; // rch
    __dekey();

    chipctrl_access();
    CHIPCTRL->PLL_CFG = 0x0000101E;
    __dekey();
    chipctrl_access();
    CHIPCTRL->CLK_CFG |= 0x00090000;
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_PLL_LOCK_Msk))
        ;
    chipctrl_access();
    CHIPCTRL->CLK_CFG |= 0x00290000;
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_SYS_CLK_LOCK_Msk))
        ;
}
void HSI_SetSysClockTo40()
{
    FLASH_LATENCY(1); // 0:sysclk<32MHz 1:32<=sysclk<64Mhz  2:64<=sysclk<=96MHz
    chipctrl_access();
    CHIPCTRL->CLK_CFG = 0x00080000; // rch
    __dekey();

    chipctrl_access();
    CHIPCTRL->PLL_CFG = 0x00001026;
    __dekey();
    chipctrl_access();
    CHIPCTRL->CLK_CFG |= 0x00090000;
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_PLL_LOCK_Msk))
        ;
    chipctrl_access();
    CHIPCTRL->CLK_CFG |= 0x00290000;
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_SYS_CLK_LOCK_Msk))
        ;
}
void HSI_SetSysClockTo48()
{
    FLASH_LATENCY(1); // 0:sysclk<32MHz 1:32<=sysclk<64Mhz  2:64<=sysclk<=96MHz
    chipctrl_access();
    CHIPCTRL->CLK_CFG = 0x00080000; // rch
    __dekey();

    chipctrl_access();
    CHIPCTRL->PLL_CFG = 0x0000102E;
    __dekey();
    chipctrl_access();
    CHIPCTRL->CLK_CFG |= 0x00090000;
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_PLL_LOCK_Msk))
        ;
    chipctrl_access();
    CHIPCTRL->CLK_CFG |= 0x00290000;
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_SYS_CLK_LOCK_Msk))
        ;
}
void HSI_SetSysClockTo56()
{
    FLASH_LATENCY(2); // 0:sysclk<32MHz 1:32<=sysclk<64Mhz  2:64<=sysclk<=96MHz
    chipctrl_access();
    CHIPCTRL->CLK_CFG = 0x00080000; // rch
    __dekey();

    chipctrl_access();
    CHIPCTRL->PLL_CFG = 0x00001036; // 8X7
    __dekey();
    chipctrl_access();
    CHIPCTRL->CLK_CFG |= 0x00090000;
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_PLL_LOCK_Msk))
        ;
    chipctrl_access();
    CHIPCTRL->CLK_CFG |= 0x00290000;
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_SYS_CLK_LOCK_Msk))
        ;
}

void HSI_SetSysClockTo64()
{
    FLASH_LATENCY(2); // 0:sysclk<32MHz 1:32<=sysclk<64Mhz  2:64<=sysclk<=96MHz
    chipctrl_access();
    CHIPCTRL->CLK_CFG = 0x00080000; // rch
    __dekey();
    chipctrl_access();
    CHIPCTRL->PLL_CFG = 0x0000103E;
    __dekey();
    chipctrl_access();
    CHIPCTRL->CLK_CFG |= 0x00090000;
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_PLL_LOCK_Msk))
        ;
    chipctrl_access();
    CHIPCTRL->CLK_CFG |= 0x00290000;
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_SYS_CLK_LOCK_Msk))
        ;
}
void HSI_SetSysClockTo72()
{
    FLASH_LATENCY(2); // 0:sysclk<32MHz 1:32<=sysclk<64Mhz  2:64<=sysclk<=96MHz
    chipctrl_access();
    CHIPCTRL->CLK_CFG = 0x00080000; // rch
    __dekey();

    chipctrl_access();
    CHIPCTRL->PLL_CFG = 0x00001046; // 8X9
    __dekey();
    chipctrl_access();
    CHIPCTRL->CLK_CFG |= 0x00090000;
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_PLL_LOCK_Msk))
        ;
    chipctrl_access();
    CHIPCTRL->CLK_CFG |= 0x00290000;
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_SYS_CLK_LOCK_Msk))
        ;
}
void HSI_SetSysClockTo84()
{
    PWR_LDODriverLevel(PWR_DRV_150uA); //内核 LDO 驱动模式配置,2：150uA；3：200uA 自耗电流运行模式
    FLASH_LATENCY(2);                  // 0:sysclk<32MHz 1:32<=sysclk<64Mhz  2:64<=sysclk<=96MHz
    chipctrl_access();
    CHIPCTRL->CLK_CFG = 0x00080000; // rch
    __dekey();
    chipctrl_access();
    CHIPCTRL->PLL_CFG = 0x00001052;
    __dekey();
    chipctrl_access();
    CHIPCTRL->CLK_CFG |= 0x00090000;
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_PLL_LOCK_Msk))
        ;
    chipctrl_access();
    CHIPCTRL->CLK_CFG |= 0x00290000;
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_SYS_CLK_LOCK_Msk))
        ;
}
void HSI_SetSysClockTo88()
{
    PWR_LDODriverLevel(PWR_DRV_200uA); //内核 LDO 驱动模式配置,2：150uA；3：200uA 自耗电流运行模式
    FLASH_LATENCY(2);                  // 0:sysclk<32MHz 1:32<=sysclk<64Mhz  2:64<=sysclk<=96MHz
    chipctrl_access();
    CHIPCTRL->CLK_CFG = 0x00080000; // rch
    __dekey();
    chipctrl_access();
    CHIPCTRL->PLL_CFG = 0x00001056;
    __dekey();
    chipctrl_access();
    CHIPCTRL->CLK_CFG |= 0x00090000;
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_PLL_LOCK_Msk))
        ;
    chipctrl_access();
    CHIPCTRL->CLK_CFG |= 0x00290000;
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_SYS_CLK_LOCK_Msk))
        ;
}
void HSI_SetSysClockTo92()
{
    PWR_LDODriverLevel(PWR_DRV_200uA); //内核 LDO 驱动模式配置,2：150uA；3：200uA 自耗电流运行模式
    FLASH_LATENCY(2);                  // 0:sysclk<32MHz 1:32<=sysclk<64Mhz  2:64<=sysclk<=96MHz
    chipctrl_access();
    CHIPCTRL->CLK_CFG = 0x00080000; // rch
    __dekey();
    chipctrl_access();
    CHIPCTRL->PLL_CFG = 0x0000105A;
    __dekey();
    chipctrl_access();
    CHIPCTRL->CLK_CFG |= 0x00090000;
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_PLL_LOCK_Msk))
        ;
    chipctrl_access();
    CHIPCTRL->CLK_CFG |= 0x00290000;
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_SYS_CLK_LOCK_Msk))
        ;
}
void HSI_SetSysClockTo96()
{
    PWR_LDODriverLevel(PWR_DRV_200uA); //内核 LDO 驱动模式配置,2：150uA；3：200uA 自耗电流运行模式
    FLASH_LATENCY(2);                  // 0:sysclk<32MHz 1:32<=sysclk<64Mhz  2:64<=sysclk<=96MHz
    chipctrl_access();
    CHIPCTRL->CLK_CFG = 0x00080000; // rch
    __dekey();
    chipctrl_access();
    CHIPCTRL->PLL_CFG = 0x0000105E;
    __dekey();
    chipctrl_access();
    CHIPCTRL->CLK_CFG |= 0x00090000;
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_PLL_LOCK_Msk))
        ;
    chipctrl_access();
    CHIPCTRL->CLK_CFG |= 0x00290000;
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_SYS_CLK_LOCK_Msk))
        ;
}

/////////////////////////////////////外部高振以16MHZ 为基础////////////////////////////////
void HSE_SetSysClockTo8()
{
    OSCH_GPIO_INIT(); //晶振脚复用
    FLASH_LATENCY(0); // 0:sysclk<32MHz 1:32<=sysclk<64Mhz  2:64<=sysclk<=96MHz
    chipctrl_access();
    CHIPCTRL->CLK_CFG = 0x000A0000; //外部时钟输入使能
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_OSCH_STB_Msk)) //等待晶振稳定
        ;
    chipctrl_access();
    CHIPCTRL->CLK_CFG |= 0x00100040; // 046:3.69M   47:3.2M   48:2.82M   49:2.4M  080:16M
    __dekey();
}
void HSE_SetSysClockTo16()
{
    OSCH_GPIO_INIT(); //晶振脚复用
    FLASH_LATENCY(0); // 0:sysclk<32MHz 1:32<=sysclk<64Mhz  2:64<=sysclk<=96MHz
    chipctrl_access();
    CHIPCTRL->CLK_CFG = 0x000A0000; //外部时钟输入使能
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_OSCH_STB_Msk)) //等待晶振稳定
        ;
    chipctrl_access();
    CHIPCTRL->CLK_CFG |= 0x00100000;
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_SYS_CLK_LOCK_Msk))
        ;
}
void HSE_SetSysClockTo24()
{
    OSCH_GPIO_INIT(); //晶振脚复用
    FLASH_LATENCY(2); // 0:sysclk<32MHz 1:32<=sysclk<64Mhz  2:64<=sysclk<=96MHz
    chipctrl_access();
    CHIPCTRL->CLK_CFG = 0x000A0000; //外部时钟输入使能
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_OSCH_STB_Msk))
        ; //等待晶振稳定
    chipctrl_access();
    CHIPCTRL->PLL_CFG = 0x00001017; // 4*OSCH 16x4//此处配置PLL分频和输入源   64M 1F;48M 17;72M 23;
    __dekey();
    chipctrl_access();
    CHIPCTRL->CLK_CFG |= 0x000B0000;
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_PLL_LOCK_Msk))
        ;
    chipctrl_access();
    CHIPCTRL->CLK_CFG |= 0x002B0000;
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_SYS_CLK_LOCK_Msk))
        ;
}
void HSE_SetSysClockTo32()
{
    OSCH_GPIO_INIT(); //晶振脚复用
    FLASH_LATENCY(1); // 0:sysclk<32MHz 1:32<=sysclk<64Mhz  2:64<=sysclk<=96MHz
    chipctrl_access();
    CHIPCTRL->CLK_CFG = 0x000A0000; //外部时钟输入使能
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_OSCH_STB_Msk)) //等待晶振稳定
        ;
    chipctrl_access();
    CHIPCTRL->PLL_CFG = 0x0000101f; // 4*OSCH 16x4//此处配置PLL分频和输入源   64M 1F;48M 17;72M 23;
    __dekey();
    chipctrl_access();
    CHIPCTRL->CLK_CFG |= 0x000B0000;
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_PLL_LOCK_Msk))
        ;
    chipctrl_access();
    CHIPCTRL->CLK_CFG |= 0x002B0000;
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_SYS_CLK_LOCK_Msk))
        ;
}
void HSE_SetSysClockTo40()
{
    OSCH_GPIO_INIT(); //晶振脚复用
    FLASH_LATENCY(1); // 0:sysclk<32MHz 1:32<=sysclk<64Mhz  2:64<=sysclk<=96MHz
    chipctrl_access();
    CHIPCTRL->CLK_CFG = 0x000A0000; //外部时钟输入使能
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_OSCH_STB_Msk)) //等待晶振稳定
        ;
    chipctrl_access();
    CHIPCTRL->PLL_CFG = 0x00001027; // 4*OSCH 16x4//此处配置PLL分频和输入源   64M 1F;48M 17;72M 23;
    __dekey();
    chipctrl_access();
    CHIPCTRL->CLK_CFG |= 0x000B0000;
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_PLL_LOCK_Msk))
        ;
    chipctrl_access();
    CHIPCTRL->CLK_CFG |= 0x002B0000;
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_SYS_CLK_LOCK_Msk))
        ;
}
void HSE_SetSysClockTo48()
{
    OSCH_GPIO_INIT(); //晶振脚复用
    FLASH_LATENCY(2); // 0:sysclk<32MHz 1:32<=sysclk<64Mhz  2:64<=sysclk<=96MHz
    chipctrl_access();
    CHIPCTRL->CLK_CFG = 0x000A0000; //外部时钟输入使能
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_OSCH_STB_Msk)) //等待晶振稳定
        ;
    chipctrl_access();
    CHIPCTRL->PLL_CFG = 0x0000102F; // 4*OSCH 16x4//此处配置PLL分频和输入源   64M 1F;48M 17;72M 23;
    __dekey();
    chipctrl_access();
    CHIPCTRL->CLK_CFG |= 0x000B0000;
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_PLL_LOCK_Msk))
        ;
    chipctrl_access();
    CHIPCTRL->CLK_CFG |= 0x002B0000;
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_SYS_CLK_LOCK_Msk))
        ;
}
void HSE_SetSysClockTo56()
{
    OSCH_GPIO_INIT(); //晶振脚复用
    FLASH_LATENCY(2); // 0:sysclk<32MHz 1:32<=sysclk<64Mhz  2:64<=sysclk<=96MHz
    chipctrl_access();
    CHIPCTRL->CLK_CFG = 0x000A0000; //外部时钟输入使能
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_OSCH_STB_Msk)) //等待晶振稳定
        ;
    chipctrl_access();
    CHIPCTRL->PLL_CFG = 0x00001037; // 4*OSCH 16x4//此处配置PLL分频和输入源   64M 1F;48M 17;72M 23;
    __dekey();
    chipctrl_access();
    CHIPCTRL->CLK_CFG |= 0x000B0000;
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_PLL_LOCK_Msk))
        ;
    chipctrl_access();
    CHIPCTRL->CLK_CFG |= 0x002B0000;
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_SYS_CLK_LOCK_Msk))
        ;
}
void HSE_SetSysClockTo64()
{
    OSCH_GPIO_INIT(); //晶振脚复用
    FLASH_LATENCY(2); // 0:sysclk<32MHz 1:32<=sysclk<64Mhz  2:64<=sysclk<=96MHz
    chipctrl_access();
    CHIPCTRL->CLK_CFG = 0x000A0000; //外部时钟输入使能
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_OSCH_STB_Msk)) //等待晶振稳定
        ;
    chipctrl_access();
    CHIPCTRL->PLL_CFG = 0x0000103F; // 4*OSCH 16x4//此处配置PLL分频和输入源   64M 1F;48M 17;72M 23;
    __dekey();
    chipctrl_access();
    CHIPCTRL->CLK_CFG |= 0x000B0000;
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_PLL_LOCK_Msk))
        ;
    chipctrl_access();
    CHIPCTRL->CLK_CFG |= 0x002B0000;
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_SYS_CLK_LOCK_Msk))
        ;
}

void HSE_SetSysClockTo72()
{
    OSCH_GPIO_INIT(); //晶振脚复用
    FLASH_LATENCY(2); // 0:sysclk<32MHz 1:32<=sysclk<64Mhz  2:64<=sysclk<=96MHz
    chipctrl_access();
    CHIPCTRL->CLK_CFG = 0x000A0000; //外部时钟输入使能
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_OSCH_STB_Msk)) //等待晶振稳定
        ;
    chipctrl_access();
    CHIPCTRL->PLL_CFG = 0x00001047; // 4*OSCH 16x4//此处配置PLL分频和输入源   64M 1F;48M 17;72M 23;
    __dekey();
    chipctrl_access();
    CHIPCTRL->CLK_CFG |= 0x000B0000;
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_PLL_LOCK_Msk))
        ;
    chipctrl_access();
    CHIPCTRL->CLK_CFG |= 0x002B0000;
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_SYS_CLK_LOCK_Msk))
        ;
}
void HSE_SetSysClockTo84()
{
    PWR_LDODriverLevel(PWR_DRV_150uA); //内核 LDO 驱动模式配置,2：150uA；3：200uA 自耗电流运行模式
    OSCH_GPIO_INIT();                  //晶振脚复用
    FLASH_LATENCY(2);                  // 0:sysclk<32MHz 1:32<=sysclk<64Mhz  2:64<=sysclk<=96MHz
    chipctrl_access();
    CHIPCTRL->CLK_CFG = 0x000A0000; //外部时钟输入使能
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_OSCH_STB_Msk))
        ; //等待晶振稳定
    chipctrl_access();
    CHIPCTRL->PLL_CFG = 0x00001053; ////96M=0x0000015F;92M=0x0000015B;88M=0x00000157;84M=0x00000153;
    __dekey();
    chipctrl_access();
    CHIPCTRL->CLK_CFG |= 0x000B0000;
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_PLL_LOCK_Msk))
        ;
    chipctrl_access();
    CHIPCTRL->CLK_CFG |= 0x002B0000;
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_SYS_CLK_LOCK_Msk))
        ;
}
void HSE_SetSysClockTo88()
{
    PWR_LDODriverLevel(PWR_DRV_200uA); //内核 LDO 驱动模式配置,2：150uA；3：200uA 自耗电流运行模式
    OSCH_GPIO_INIT();                  //晶振脚复用
    FLASH_LATENCY(2);                  // 0:sysclk<32MHz 1:32<=sysclk<64Mhz  2:64<=sysclk<=96MHz
    chipctrl_access();
    CHIPCTRL->CLK_CFG = 0x000A0000; //外部时钟输入使能
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_OSCH_STB_Msk))
        ; //等待晶振稳定
    chipctrl_access();
    CHIPCTRL->PLL_CFG = 0x00001057; ////96M=0x0000015F;92M=0x0000015B;88M=0x00000157;84M=0x00000153;
    __dekey();
    chipctrl_access();
    CHIPCTRL->CLK_CFG |= 0x000B0000;
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_PLL_LOCK_Msk))
        ;
    chipctrl_access();
    CHIPCTRL->CLK_CFG |= 0x002B0000;
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_SYS_CLK_LOCK_Msk))
        ;
}
void HSE_SetSysClockTo92()
{
    PWR_LDODriverLevel(PWR_DRV_200uA); //内核 LDO 驱动模式配置,2：150uA；3：200uA 自耗电流运行模式
    OSCH_GPIO_INIT();                  //晶振脚复用
    FLASH_LATENCY(2);                  // 0:sysclk<32MHz 1:32<=sysclk<64Mhz  2:64<=sysclk<=96MHz
    chipctrl_access();
    CHIPCTRL->CLK_CFG = 0x000A0000; //外部时钟输入使能
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_OSCH_STB_Msk))
        ; //等待晶振稳定
    chipctrl_access();
    CHIPCTRL->PLL_CFG = 0x0000105B; ////96M=0x0000015F;92M=0x0000015B;88M=0x00000157;84M=0x00000153;
    __dekey();
    chipctrl_access();
    CHIPCTRL->CLK_CFG |= 0x000B0000;
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_PLL_LOCK_Msk))
        ;
    chipctrl_access();
    CHIPCTRL->CLK_CFG |= 0x002B0000;
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_SYS_CLK_LOCK_Msk))
        ;
}
void HSE_SetSysClockTo96()
{
    PWR_LDODriverLevel(PWR_DRV_200uA); //内核 LDO 驱动模式配置,2：150uA；3：200uA 自耗电流运行模式
    OSCH_GPIO_INIT();                  //晶振脚复用
    FLASH_LATENCY(2);                  // 0:sysclk<32MHz 1:32<=sysclk<64Mhz  2:64<=sysclk<=96MHz
    chipctrl_access();
    CHIPCTRL->CLK_CFG = 0x000A0000; //外部时钟输入使能
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_OSCH_STB_Msk))
        ; //等待晶振稳定
    chipctrl_access();
    CHIPCTRL->PLL_CFG = 0x0000105F; ////96M=0x0000015F;92M=0x0000015B;88M=0x00000157;84M=0x00000153;
    __dekey();
    chipctrl_access();
    CHIPCTRL->CLK_CFG |= 0x000B0000;
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_PLL_LOCK_Msk))
        ;
    chipctrl_access();
    CHIPCTRL->CLK_CFG |= 0x002B0000;
    __dekey();
    while (!(CHIPCTRL->STS & CHIPCTRL_STS_SYS_CLK_LOCK_Msk))
        ;
}

void SystemInit(void)
{
    RCC_DeInit();
}

void SetSysClock(void)
{

#if HSI_SYSCLK_FREQ_8MHz
    HSI_SetSysClockTo8();
#endif
#if HSI_SYSCLK_FREQ_16MHz
    HSI_SetSysClockTo16();
#endif
#if HSI_SYSCLK_FREQ_24MHz
    HSI_SetSysClockTo24();
#endif
#if HSI_SYSCLK_FREQ_32MHz
    HSI_SetSysClockTo32();
#endif
#if HSI_SYSCLK_FREQ_40MHz
    HSI_SetSysClockTo40();
#endif
#if HSI_SYSCLK_FREQ_48MHz
    HSI_SetSysClockTo48();
#endif
#if HSI_SYSCLK_FREQ_56MHz
    HSI_SetSysClockTo56();
#endif
#if HSI_SYSCLK_FREQ_64MHz            // 2.5V以下频率变小
    PWR_LVRConfig(PWR_LVRLevel_2V5); //设置LVR复位点
    PWR_LVRCmd(ENABLE);              // LVR使能
    delay10us(1000);
    HSI_SetSysClockTo64();
#endif
#if HSI_SYSCLK_FREQ_72MHz            // 2.7V以下频率变小
    PWR_LVRConfig(PWR_LVRLevel_2V5); //设置LVR复位点
    PWR_LVRCmd(ENABLE);              // LVR使能
    delay10us(1000);
    HSI_SetSysClockTo72();
#endif
#if HSI_SYSCLK_FREQ_84MHz
    PWR_LVRConfig(PWR_LVRLevel_4V0); //设置LVR复位点
    PWR_LVRCmd(ENABLE);              // LVR使能
    delay10us(1000);
    HSI_SetSysClockTo84();
#endif
#if HSI_SYSCLK_FREQ_88MHz
    PWR_LVRConfig(PWR_LVRLevel_4V0); //设置LVR复位点
    PWR_LVRCmd(ENABLE);              // LVR使能
    delay10us(1000);
    HSI_SetSysClockTo88();
#endif
#if HSI_SYSCLK_FREQ_92MHz
    PWR_LVRConfig(PWR_LVRLevel_4V0); //设置LVR复位点
    PWR_LVRCmd(ENABLE);              // LVR使能
    delay10us(1000);
    HSI_SetSysClockTo92();
#endif
#if HSI_SYSCLK_FREQ_96MHz
//    PWR_LVRConfig(PWR_LVRLevel_4V0); //设置LVR复位点
    PWR_LVRCmd(ENABLE);              // LVR使能
    delay10us(1000);
    HSI_SetSysClockTo96();
#endif

#if HSE_SYSCLK_FREQ_8MHz
    HSE_SetSysClockTo8();
#endif
#if HSE_SYSCLK_FREQ_16MHz
    HSE_SetSysClockTo16();
#endif
#if HSE_SYSCLK_FREQ_24MHz
    HSE_SetSysClockTo24();
#endif
#if HSE_SYSCLK_FREQ_32MHz
    HSE_SetSysClockTo32();
#endif
#if HSE_SYSCLK_FREQ_40MHz
    HSE_SetSysClockTo40();
#endif
#if HSE_SYSCLK_FREQ_48MHz
    HSE_SetSysClockTo48();
#endif
#if HSE_SYSCLK_FREQ_56MHz
    HSE_SetSysClockTo56();
#endif
#if HSE_SYSCLK_FREQ_64MHz            // 2.6V以下频率变小
    PWR_LVRConfig(PWR_LVRLevel_2V5); //设置LVR复位点
    PWR_LVRCmd(ENABLE);              // LVR使能
    delay10us(1000);
    HSE_SetSysClockTo64();
#endif
#if HSE_SYSCLK_FREQ_72MHz            // 2.8V以下频率变小
    PWR_LVRConfig(PWR_LVRLevel_2V5); //设置LVR复位点
    PWR_LVRCmd(ENABLE);              // LVR使能
    delay10us(1000);
    HSE_SetSysClockTo72();
#endif
#if HSE_SYSCLK_FREQ_84MHz
    PWR_LVRConfig(PWR_LVRLevel_4V0); //设置LVR复位点
    PWR_LVRCmd(ENABLE);              // LVR使能
    delay10us(1000);
    HSE_SetSysClockTo84();
#endif
#if HSE_SYSCLK_FREQ_88MHz
    PWR_LVRConfig(PWR_LVRLevel_4V0); //设置LVR复位点
    PWR_LVRCmd(ENABLE);              // LVR使能
    delay10us(1000);
    HSE_SetSysClockTo88();
#endif
#if HSE_SYSCLK_FREQ_92MHz
    PWR_LVRConfig(PWR_LVRLevel_4V0); //设置LVR复位点
    PWR_LVRCmd(ENABLE);              // LVR使能
    delay10us(1000);
    HSE_SetSysClockTo92();
#endif
#if HSE_SYSCLK_FREQ_96MHz
    PWR_LVRConfig(PWR_LVRLevel_4V0); //设置LVR复位点
    PWR_LVRCmd(ENABLE);              // LVR使能
    delay10us(1000);
    HSE_SetSysClockTo96();
#endif


}
void RCC_DeInit(void)
{
    chipctrl_access();
    CHIPCTRL->CLK_CFG = 0x00080000;
    __dekey();
    chipctrl_access();
    CHIPCTRL->CTRL = 0x00000000;
    __dekey();
    chipctrl_access();
    CHIPCTRL->OSCH_CFG = 0x00000007;
    __dekey();
    chipctrl_access();
    CHIPCTRL->BDCR_b.BDRST = 1; // 0：WT domain software not reset
    __dekey();
    chipctrl_access();
    CHIPCTRL->BDCR = 0x00007004;
    __dekey();
    sysctrl_access();
    SYSCTRL->ClkEnR0 = 0x00060000; // SRAM0、SRAM1 enable
    __dekey();
}

void RCC_HSEConfig(uint8_t RCC_HSE) //外部高震得开关和bypass使能
{
    /* Check the parameters */
    assert_param(IS_RCC_HSE(RCC_HSE));

    /* Reset HSEON and HSEBYP bits before configuring the HSE ------------------*/
    chipctrl_access();
    CHIPCTRL->CLK_CFG_b.OSCH_EN = RCC_HSE_OFF;
    __dekey();

    chipctrl_access();
    CHIPCTRL->OSCH_CFG_b.OSCH_BYP = 0;
    __dekey();

    /* Set the new HSE configuration -------------------------------------------*/
    if (RCC_HSE < 2)
    {
        chipctrl_access();
        CHIPCTRL->CLK_CFG_b.OSCH_EN = RCC_HSE;
        __dekey();
    }
    else //打开OSCH 并开启 OSCH bypass.
    {
        chipctrl_access();
        CHIPCTRL->CLK_CFG_b.OSCH_EN = RCC_HSE_ON;
        __dekey();

        chipctrl_access();
        CHIPCTRL->OSCH_CFG_b.OSCH_BYP = 1;
        __dekey();
    }
}

/**
 * @brief  Waits for HSE start-up.
 * @retval An ErrorStatus enumeration value:
 *          - SUCCESS: HSE oscillator is stable and ready to use
 *          - ERROR: HSE oscillator not yet ready
 */
ErrorStatus RCC_WaitForHSEStartUp(void) //@zhang edit end。
{
    __IO uint32_t StartUpCounter = 0;
    ErrorStatus status = ERROR;
    FlagStatus HSEStatus = RESET;

#define HSE_STARTUP_TIMEOUT ((uint16_t)0x5000)

    /* Wait till HSE is ready and if timeout is reached exit */
    do
    {
        HSEStatus = RCC_GetFlagStatus(RCC_FLAG_HSERDY);
        StartUpCounter++;
    } while ((StartUpCounter != HSE_STARTUP_TIMEOUT) && (HSEStatus == RESET));

    if (RCC_GetFlagStatus(RCC_FLAG_HSERDY) != RESET)
    {
        status = SUCCESS;
    }
    else
    {
        status = ERROR;
    }
    return (status);
}

/**
 * @brief  Adjusts the Internal High Speed oscillator (HSI) calibration value.
 * @param  HSICalibrationValue: specifies the HSI calibration trimming value.
 *          This parameter must be a number between 0 and 0x1F.
 * @retval None
 */
void RCC_AdjustHSICalibrationValue(uint8_t HSICalibrationValue) //@zhng
{
    chipctrl_access();
    CHIPCTRL->RCH_CFG = HSICalibrationValue & 0x0FFF;
    __dekey();
}

/**
 * @brief  Enables or disables the Internal High Speed oscillator (HSI).
 * @param  NewState: new state of the HSI.
 *          This parameter can be: ENABLE or DISABLE.
 * @note   When the HSI is stopped, HSIRDY flag goes low after 6 HSI oscillator
 *         clock cycles.
 * @retval None
 */
void RCC_HSICmd(FunctionalState NewState) //@zhang rch
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {

        chipctrl_access();
        CHIPCTRL->CLK_CFG_b.RCH_EN = 0;
        __dekey();
    }
    else
    {
        chipctrl_access();
        CHIPCTRL->CLK_CFG_b.RCH_EN = 1;
        __dekey();
    }
}

/**
 * @brief  Configures the External Low Speed oscillator (LSE).
 * @param  RCC_LSE: specifies the new state of the LSE.
 *          This parameter can be one of the following values:
 *            @arg RCC_LSE_OFF: turn OFF the LSE oscillator, LSERDY flag goes low after
 *                              6 LSE oscillator clock cycles.
 *            @arg RCC_LSE_ON: turn ON the LSE oscillator
 *            @arg RCC_LSE_Bypass: LSE oscillator bypassed with external clock
 * @retval None
 */
void RCC_LSEConfig(uint32_t RCC_LSE) //@zhang oscl
{
    /* Check the parameters */
    assert_param(IS_RCC_LSE(RCC_LSE));

    /* Reset LSEON and LSEBYP bits before configuring the LSE ------------------*/
    /* Reset LSEON bit */

    chipctrl_access();
    CHIPCTRL->BDCR_b.OSCL_EN = 0;
    __dekey();

    /* Reset LSEBYP bit */
    chipctrl_access();
    CHIPCTRL->BDCR_b.OSCL_BYP = 0;
    __dekey();

    /* Configure LSE */

    if (RCC_LSE == RCC_LSE_ON)
    {
        chipctrl_access();
        CHIPCTRL->BDCR_b.OSCL_EN = 1;
        __dekey();
    }
    if (RCC_LSE == RCC_LSE_Bypass)
    {
        chipctrl_access();
        CHIPCTRL->BDCR_b.OSCL_BYP = 1;
        __dekey();

        chipctrl_access();
        CHIPCTRL->BDCR_b.OSCL_EN = 1;
        __dekey();
    }
    else //(RCC_LSE==RCC_LSE_OFF)
    {
        chipctrl_access();
        CHIPCTRL->BDCR_b.OSCL_EN = 0;
        __dekey();
    }
}

/**
 * @brief  Configures the External Low Speed oscillator (LSE) drive capability.
 * @param  RCC_LSEDrive: specifies the new state of the LSE drive capability.
 *          This parameter can be one of the following values:
 *            @arg RCC_LSEDrive_Low: LSE oscillator low drive capability.
 *            @arg RCC_LSEDrive_MediumLow: LSE oscillator medium low drive capability.
 *            @arg RCC_LSEDrive_MediumHigh: LSE oscillator medium high drive capability.
 *            @arg RCC_LSEDrive_High: LSE oscillator high drive capability.
 * @retval None
 */
void RCC_LSEDriveConfig(uint32_t RCC_LSEDrive)
{
    (void)RCC_LSEDrive;
}

/**
 * @brief  Enables or disables the Internal Low Speed oscillator (LSI).
 * @note   After enabling the LSI, the application software should wait on
 *         LSIRDY flag to be set indicating that LSI clock is stable and can
 *         be used to clock the IWDG and/or the RTC.
 * @note   LSI can not be disabled if the IWDG is running.
 * @param  NewState: new state of the LSI.
 *          This parameter can be: ENABLE or DISABLE.
 * @note   When the LSI is stopped, LSIRDY flag goes low after 6 LSI oscillator
 *         clock cycles.
 * @retval None
 */
void RCC_LSICmd(FunctionalState NewState) //@zhang rcl
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        chipctrl_access();
        CHIPCTRL->RCL_CFG_b.RCL_EN = 1;
        __dekey();
    }
    else
    {
        chipctrl_access();
        CHIPCTRL->RCL_CFG_b.RCL_EN = 0;
        __dekey();
    }
}

/**
 * @brief  Enables or disables the Clock Security System.
 * @note   If a failure is detected on the HSE oscillator clock, this oscillator
 *         is automatically disabled and an interrupt is generated to inform the
 *         software about the failure (Clock Security System Interrupt, CSSI),
 *         allowing the MCU to perform rescue operations. The CSSI is linked to
 *         the Cortex-M0 NMI (Non-Maskable Interrupt) exception vector.
 * @param  NewState: new state of the Clock Security System.
 *          This parameter can be: ENABLE or DISABLE.
 * @retval None
 */
void RCC_ClockSecuritySystemCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        chipctrl_access();
        CHIPCTRL->CTRL_b.CSS_EN = 1;
        __dekey();
    }
    else
    {
        chipctrl_access();
        CHIPCTRL->CTRL_b.CSS_EN = 0;
        __dekey();
    }
}
//#if defined (LCM32F037_MD)

//#else
/**
 * @brief  Selects the clock source to output on MCO pin (PA8) and the corresponding
 *         prescsaler.
 * @note   PA8 should be configured in alternate function mode.
 * @param  RCC_MCOSource: specifies the clock source to output.
 *          This parameter can be one of the following values:
 *            @arg RCC_MCOSource_NoClock: No clock selected.
 *            @arg RCC_MCOSource_HSI14: HSI14 oscillator clock selected.
 *            @arg RCC_MCOSource_LSI: LSI oscillator clock selected.
 *            @arg RCC_MCOSource_LSE: LSE oscillator clock selected.
 *            @arg RCC_MCOSource_SYSCLK: System clock selected.
 *            @arg RCC_MCOSource_HSI: HSI oscillator clock selected.
 *            @arg RCC_MCOSource_HSE: HSE oscillator clock selected.
 *            @arg RCC_MCOSource_PLLCLK_Div2: PLL clock divided by 2 selected.
 *            @arg RCC_MCOSource_PLLCLK: PLL clock selected.
 * @param  RCC_MCOPrescaler: specifies the prescaler on MCO pin.
 *          This parameter can be one of the following values:
 *            @arg RCC_MCOPrescaler_1: MCO clock is divided by 1.
 *            @arg RCC_MCOPrescaler_2: MCO clock is divided by 2.
 *            @arg RCC_MCOPrescaler_4: MCO clock is divided by 4.
 *            @arg RCC_MCOPrescaler_8: MCO clock is divided by 8.
 *            @arg RCC_MCOPrescaler_16: MCO clock is divided by 16.
 *            @arg RCC_MCOPrescaler_32: MCO clock is divided by 32.
 *            @arg RCC_MCOPrescaler_64: MCO clock is divided by 64.
 *            @arg RCC_MCOPrescaler_128: MCO clock is divided by 128.
 * @retval None
 */
void RCC_MCOConfig(uint8_t RCC_MCOSource, uint32_t RCC_MCOPrescaler)
{
    /* Check the parameters */
    assert_param(IS_RCC_MCO_SOURCE(RCC_MCOSource));
    assert_param(IS_RCC_MCO_PRESCALER(RCC_MCOPrescaler));

    sysctrl_access();
    SYSCTRL->ClkEnR1_b.MCO_SEL = RCC_MCOSource;
    __dekey();

    sysctrl_access();
    SYSCTRL->ClkEnR1_b.MCO_DIV = RCC_MCOPrescaler;
    __dekey();
}
//#endif /* LCM32F037_MD */
/**
 * @}
 */

/** @defgroup RCC_Group2 System AHB and APB busses clocks configuration functions
 *  @brief   System, AHB and APB busses clocks configuration functions
 *
@verbatim
 ===============================================================================
     ##### System, AHB and APB busses clocks configuration functions #####
 ===============================================================================

    [..] This section provide functions allowing to configure the System, AHB and
         APB busses clocks.
         (#) Several clock sources can be used to drive the System clock (SYSCLK): HSI,
             HSE and PLL.
             The AHB clock (HCLK) is derived from System clock through configurable prescaler
             and used to clock the CPU, memory and peripherals mapped on AHB bus (DMA and GPIO).
             and APB (PCLK) clocks are derived from AHB clock through
             configurable prescalers and used to clock the peripherals mapped on these busses.
             You can use "RCC_GetClocksFreq()" function to retrieve the frequencies of these clocks.

         -@- All the peripheral clocks are derived from the System clock (SYSCLK) except:
             (+@) The ADC clock which is derived from HSI14 or APB (APB divided by a
                  programmable prescaler: 2 or 4).
             (+@) The CEC clock which is derived from LSE or HSI divided by 244.
             (+@) The I2C clock which is derived from HSI or system clock (SYSCLK).
             (+@) The USART clock which is derived from HSI, system clock (SYSCLK), APB or LSE.
             (+@) IWDG clock which is always the LSI clock.

         (#) The maximum frequency of the SYSCLK, HCLK and PCLK is 48 MHz.
             Depending on the maximum frequency, the FLASH wait states (WS) should be
             adapted accordingly:
        +--------------------------------------------- +
        |  Wait states  |   HCLK clock frequency (MHz) |
        |---------------|------------------------------|
        |0WS(1CPU cycle)|       0 < HCLK <= 24         |
        |---------------|------------------------------|
        |1WS(2CPU cycle)|       24 < HCLK <= 48        |
        +----------------------------------------------+

         (#) After reset, the System clock source is the HSI (8 MHz) with 0 WS and
             prefetch is disabled.

    [..] It is recommended to use the following software sequences to tune the number
         of wait states needed to access the Flash memory with the CPU frequency (HCLK).
         (+) Increasing the CPU frequency
         (++) Program the Flash Prefetch buffer, using "FLASH_PrefetchBufferCmd(ENABLE)"
              function
         (++) Check that Flash Prefetch buffer activation is taken into account by
              reading FLASH_ACR using the FLASH_GetPrefetchBufferStatus() function
         (++) Program Flash WS to 1, using "FLASH_SetLatency(FLASH_Latency_1)" function
         (++) Check that the new number of WS is taken into account by reading FLASH_ACR
         (++) Modify the CPU clock source, using "RCC_SYSCLKConfig()" function
         (++) If needed, modify the CPU clock prescaler by using "RCC_HCLKConfig()" function
         (++) Check that the new CPU clock source is taken into account by reading
              the clock source status, using "RCC_GetSYSCLKSource()" function
         (+) Decreasing the CPU frequency
         (++) Modify the CPU clock source, using "RCC_SYSCLKConfig()" function
         (++) If needed, modify the CPU clock prescaler by using "RCC_HCLKConfig()" function
         (++) Check that the new CPU clock source is taken into account by reading
              the clock source status, using "RCC_GetSYSCLKSource()" function
         (++) Program the new number of WS, using "FLASH_SetLatency()" function
         (++) Check that the new number of WS is taken into account by reading FLASH_ACR
         (++) Disable the Flash Prefetch buffer using "FLASH_PrefetchBufferCmd(DISABLE)"
              function
         (++) Check that Flash Prefetch buffer deactivation is taken into account by reading FLASH_ACR
              using the FLASH_GetPrefetchBufferStatus() function.

@endverbatim
  * @{
  */

/**
 * @brief  Configures the system clock (SYSCLK).
 * @note   The HSI is used (enabled by hardware) as system clock source after
 *         startup from Reset, wake-up from STOP and STANDBY mode, or in case
 *         of failure of the HSE used directly or indirectly as system clock
 *         (if the Clock Security System CSS is enabled).
 * @note   A switch from one clock source to another occurs only if the target
 *         clock source is ready (clock stable after startup delay or PLL locked).
 *         If a clock source which is not yet ready is selected, the switch will
 *         occur when the clock source will be ready.
 *         You can use RCC_GetSYSCLKSource() function to know which clock is
 *         currently used as system clock source.
 * @param  RCC_SYSCLKSource: specifies the clock source used as system clock source
 *          This parameter can be one of the following values:
 *            @arg RCC_SYSCLKSource_HSI:    HSI selected as system clock source
 *            @arg RCC_SYSCLKSource_HSE:    HSE selected as system clock source
 *            @arg RCC_SYSCLKSource_PLLCLK: PLL selected as system clock source
 * @retval None
 */
void RCC_SYSCLKConfig(uint32_t RCC_SYSCLKSource)
{
    unsigned int tmpreg;
    assert_param(IS_RCC_SYSCLK_SOURCE(RCC_SYSCLKSource));
    tmpreg = CHIPCTRL->CLK_CFG;
    tmpreg &= ~(3 << 20);
    tmpreg |= (RCC_SYSCLKSource << 20);
    chipctrl_access();
    CHIPCTRL->CLK_CFG = tmpreg;
    CHIPCTRL->CLK_CFG = tmpreg;
    CHIPCTRL->CLK_CFG = tmpreg;
    __dekey();
}

/**
 * @brief  Returns the clock source used as system clock.
 * @param  None
 * @retval The clock source used as system clock. The returned value can be one
 *         of the following values:
 *           - 0x00: HSI used as system clock
 *           - 0x04: HSE used as system clock
 *           - 0x08: PLL used as system clock
 */
uint8_t RCC_GetSYSCLKSource(void) //@zhang
{
    return (CHIPCTRL->CLK_CFG_b.CLK_SRC_SEL);
}

/**
 * @brief  Configures the AHB clock (HCLK).
 * @param  RCC_SYSCLK: defines the AHB clock divider. This clock is derived from
 *         the system clock (SYSCLK).
 *          This parameter can be one of the following values:
 *            @arg RCC_SYSCLK_Div1:   AHB clock = SYSCLK
 *            @arg RCC_SYSCLK_Div2:   AHB clock = SYSCLK/2
 *            @arg RCC_SYSCLK_Div4:   AHB clock = SYSCLK/4
 *            @arg RCC_SYSCLK_Div8:   AHB clock = SYSCLK/8
 *            @arg RCC_SYSCLK_Div16:  AHB clock = SYSCLK/16
 *            @arg RCC_SYSCLK_Div64:  AHB clock = SYSCLK/64
 *            @arg RCC_SYSCLK_Div128: AHB clock = SYSCLK/128
 *            @arg RCC_SYSCLK_Div256: AHB clock = SYSCLK/256
 *            @arg RCC_SYSCLK_Div512: AHB clock = SYSCLK/512
 * @retval None
 */
void RCC_HCLKConfig(uint32_t RCC_SYSCLK) //@zhang
{
    // 00xx_xxxx: SYS_CLK = SYS_CLK_IN
    // 01xx_xxxx: SYS_CLK = SYS_CLK_IN / (2 * (SYS_CLK_SEL[5:0]+1))
    // 10xx_xxxx: SYS_CLK = SYS_CLK_IN / 3
    // 11xx_xxxx: SYS_CLK = SYS_CLK_IN / 5
    chipctrl_access();
    CHIPCTRL->CLK_CFG_b.SYS_CLK_SEL = RCC_SYSCLK;
    __dekey();
}

/**
 * @brief  Configures the APB clock (PCLK).
 * @param  RCC_HCLK: defines the APB clock divider. This clock is derived from
 *         the AHB clock (HCLK).
 *          This parameter can be one of the following values:
 *            @arg RCC_HCLK_Div1: APB clock = HCLK
 *            @arg RCC_HCLK_Div2: APB clock = HCLK/2
 *            @arg RCC_HCLK_Div4: APB clock = HCLK/4
 *            @arg RCC_HCLK_Div8: APB clock = HCLK/8
 *            @arg RCC_HCLK_Div16: APB clock = HCLK/16
 * @retval None
 */
void RCC_PCLK0Config(uint32_t RCC_HCLK)
{
    assert_param(IS_RCC_PCLK(RCC_HCLK));
    chipctrl_access();
    CHIPCTRL->CLK_CFG_b.APB0_DIV = RCC_HCLK;
    __dekey();
}
void RCC_PCLK1Config(uint32_t RCC_HCLK)
{
    assert_param(IS_RCC_PCLK(RCC_HCLK));
    chipctrl_access();
    CHIPCTRL->CLK_CFG_b.APB1_DIV = RCC_HCLK;
    __dekey();
}

/**
 * @brief  Configures the ADC clock (ADCCLK).
 * @param  RCC_ADCCLK: defines the ADC clock source. This clock is derived
 *         from the HSI14 or APB clock (PCLK).
 *          This parameter can be one of the following values:
 *             @arg RCC_ADCCLK_HSI14: ADC clock = HSI14 (14MHz)
 *             @arg RCC_ADCCLK_PCLK_Div2: ADC clock = PCLK/2
 *             @arg RCC_ADCCLK_PCLK_Div4: ADC clock = PCLK/4
 * @retval None
 */
void RCC_ADCCLKConfig(uint32_t RCC_ADCCLK)
{
    (void)RCC_ADCCLK;
}

/**
 * @brief  Configures the CEC clock (CECCLK).
 * @param  RCC_CECCLK: defines the CEC clock source. This clock is derived
 *         from the HSI or LSE clock.
 *          This parameter can be one of the following values:
 *             @arg RCC_CECCLK_HSI_Div244: CEC clock = HSI/244 (32768Hz)
 *             @arg RCC_CECCLK_LSE: CEC clock = LSE
 * @retval None
 */
void RCC_CECCLKConfig(uint32_t RCC_CECCLK)
{
    (void)RCC_CECCLK;
}

/**

  */
void RCC_I2C0CLKConfig(uint32_t RCC_I2C0CLK)
{
    /* Check the parameters */
    assert_param(IS_RCC_I2C0CLK(RCC_I2C0CLK));
    sysctrl_access();
    SYSCTRL->ClkEnR1_b.I2C0_CLKSEL = RCC_I2C0CLK;
    __dekey();
}

void RCC_SPI0CLKConfig(uint32_t RCC_SSP0CLK)
{
    /* Check the parameters */
    assert_param(IS_RCC_SSP0CLK(RCC_SSP0CLK));
    sysctrl_access();
    SYSCTRL->ClkEnR1_b.SSP0_CLKSEL = RCC_SSP0CLK;
    __dekey();
}
void RCC_SPI2CLKConfig(uint32_t RCC_SSP2CLK)
{
    /* Check the parameters */
    assert_param(IS_RCC_SSP2CLK(RCC_SSP2CLK));
    sysctrl_access();
    SYSCTRL->ClkEnR1_b.SSP2_CLKSEL = RCC_SSP2CLK;
    __dekey();
}
void RCC_UART1CLKConfig(uint32_t RCC_UART1CLK)
{
    /* Check the parameters */
    assert_param(IS_RCC_UART1CLK(RCC_UART1CLK));

    sysctrl_access();
    SYSCTRL->ClkEnR1_b.UART1_CLKSEL = RCC_UART1CLK;
    __dekey();
}

void RCC_UART0CLKConfig(uint32_t RCC_UART0CLK)
{
    /* Check the parameters */
    assert_param(IS_RCC_UART0CLK(RCC_UART0CLK));

    sysctrl_access();
    SYSCTRL->ClkEnR1_b.UART0_CLKSEL = RCC_UART0CLK;
    __dekey();
}

/**
 * @brief  Returns the frequencies of the System, AHB and APB busses clocks.
 * @note    The frequency returned by this function is not the real frequency
 *           in the chip. It is calculated based on the predefined constant and
 *           the source selected by RCC_SYSCLKConfig():
 *
 * @note     If SYSCLK source is HSI, function returns constant HSI_VALUE(*)
 *
 * @note     If SYSCLK source is HSE, function returns constant HSE_VALUE(**)
 *
 * @note     If SYSCLK source is PLL, function returns constant HSE_VALUE(**)
 *             or HSI_VALUE(*) multiplied by the PLL factors.
 *
 * @note     (*) HSI_VALUE is a constant defined in LCM32f037.h file (default value
 *               8 MHz) but the real value may vary depending on the variations
 *               in voltage and temperature, refer to RCC_AdjustHSICalibrationValue().
 *
 * @note     (**) HSE_VALUE is a constant defined in LCM32f037.h file (default value
 *                8 MHz), user has to ensure that HSE_VALUE is same as the real
 *                frequency of the crystal used. Otherwise, this function may
 *                return wrong result.
 *
 * @note   The result of this function could be not correct when using fractional
 *         value for HSE crystal.
 *
 * @param  RCC_Clocks: pointer to a RCC_ClocksTypeDef structure which will hold
 *         the clocks frequencies.
 *
 * @note   This function can be used by the user application to compute the
 *         baudrate for the communication peripherals or configure other parameters.
 * @note   Each time SYSCLK, HCLK and/or PCLK clock changes, this function
 *         must be called to update the structure's field. Otherwise, any
 *         configuration based on this function will be incorrect.
 *
 * @retval None
 */

/**
 * @}
 */

/** @defgroup RCC_Group3 Peripheral clocks configuration functions
 *  @brief   Peripheral clocks configuration functions
 *
@verbatim
 ===============================================================================
             #####Peripheral clocks configuration functions #####
 ===============================================================================

    [..] This section provide functions allowing to configure the Peripheral clocks.
         (#) The RTC clock which is derived from the LSE, LSI or  HSE_Div32 (HSE
             divided by 32).
         (#) After restart from Reset or wakeup from STANDBY, all peripherals are off
             except internal SRAM, Flash and SWD. Before to start using a peripheral you
             have to enable its interface clock. You can do this using RCC_AHBPeriphClockCmd(),
             RCC_APB2PeriphClockCmd() and RCC_APB1PeriphClockCmd() functions.
         (#) To reset the peripherals configuration (to the default state after device reset)
             you can use RCC_AHBPeriphResetCmd(), RCC_APB2PeriphResetCmd() and
             RCC_APB1PeriphResetCmd() functions.

@endverbatim
  * @{
  */

/**
 * @brief  Configures the RTC clock (RTCCLK).
 * @note   As the RTC clock configuration bits are in the Backup domain and write
 *         access is denied to this domain after reset, you have to enable write
 *         access using PWR_BackupAccessCmd(ENABLE) function before to configure
 *         the RTC clock source (to be done once after reset).
 *
 * @param  RCC_RTCCLKSource: specifies the RTC clock source.
 *          This parameter can be one of the following values:
 *            @arg RCC_RTCCLKSource_HSE_Div32: HSE divided by 32 selected as RTC clock
 *
 *
 * @note   The maximum input clock frequency for RTC is 2MHz (when using HSE as
 *         RTC clock source).
 *
 * @retval None
 */

/**
 * @note   This function must be used only after the RTC clock source was selected
 *         using the RCC_RTCCLKConfig function.
 *          This parameter can be: ENABLE or DISABLE.
 * @retval None
 */
void RCC_WTCLKConfig(uint32_t RCC_WTCLKSource)
{
    /* Check the parameters */
    assert_param(IS_RCC_WTCLK_SOURCE(RCC_WTCLKSource));
    /* Select the RTC clock source */
    chipctrl_access();
    CHIPCTRL->BDCR_b.WT_SEL = RCC_WTCLKSource; //时钟源//RCL
    __dekey();
}
/**
 * @brief  Enables or disables the RTC clock.
 * @note   This function must be used only after the RTC clock source was selected
 *         using the RCC_RTCCLKConfig function.
 * @param  NewState: new state of the RTC clock.
 *          This parameter can be: ENABLE or DISABLE.
 * @retval None
 */
void RCC_WTCLKCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE)
    {
        chipctrl_access();
        CHIPCTRL->BDCR_b.WT_EN = 1;
    }
    else
    {
        chipctrl_access();
        CHIPCTRL->BDCR_b.WT_EN = 0;
    }
    __dekey();
}
void RCC_BackupResetCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        chipctrl_access();
        CHIPCTRL->BDCR_b.BDRST = 1;
        __dekey();
    }
    else
    {
        chipctrl_access();
        CHIPCTRL->BDCR_b.BDRST = 0;
        __dekey();
    }
}

/**
 * @brief  Enables or disables the AHB peripheral clock.
 * @note   After reset, the peripheral clock (used for registers read/write access)
 *         is disabled and the application software has to enable this clock before
 *         using it.
 * @param  RCC_AHBPeriph: specifies the AHB peripheral to gates its clock.
 *          This parameter can be any combination of the following values:
 *             @arg RCC_AHBPeriph_GPIOA: GPIOA clock
 *             @arg RCC_AHBPeriph_GPIOB: GPIOB clock
 *             @arg RCC_AHBPeriph_GPIOC: GPIOC clock
 *             @arg RCC_AHBPeriph_GPIOD: GPIOD clock
 *             @arg RCC_AHBPeriph_GPIOF: GPIOF clock
 *             @arg RCC_AHBPeriph_TS:    TS clock
 *             @arg RCC_AHBPeriph_CRC:   CRC clock
 *             @arg RCC_AHBPeriph_FLITF: (has effect only when the Flash memory is in power down mode)
 *             @arg RCC_AHBPeriph_SRAM:  SRAM clock
 *             @arg RCC_AHBPeriph_DMA1:  DMA1 clock
 * @param  NewState: new state of the specified peripheral clock.
 *          This parameter can be: ENABLE or DISABLE.
 * @retval None
 */
void RCC_AHBPeriphClockCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RCC_AHB_PERIPH(RCC_AHBPeriph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        sysctrl_access();
        SYSCTRL->ClkEnR0 |= RCC_AHBPeriph;
        __dekey();
    }
    else
    {
        sysctrl_access();
        SYSCTRL->ClkEnR0 &= ~RCC_AHBPeriph;
        __dekey();
    }
}

/**
  * @brief  Enables or disables the High Speed APB (APB2) peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @param  RCC_APB2Periph: specifies the APB2 peripheral to gates its clock.
  *          This parameter can be any combination of the following values:
  *             @arg RCC_APB2Periph_SYSCFG: SYSCFG clock
  *             @arg RCC_APB2Periph_ADC1:   ADC1 clock
  *             @arg RCC_APB2Periph_TIM1:   TIM1 clock

  *             @arg RCC_APB2Periph_USART1: USART1 clock
  *             @arg RCC_APB2Periph_TIM15:  TIM15 clock
  *             @arg RCC_APB2Periph_TIM16:  TIM16 clock
  *             @arg RCC_APB2Periph_TIM17:  TIM17 clock
  *             @arg RCC_APB2Periph_DBGMCU: DBGMCU clock
  * @param  NewState: new state of the specified peripheral clock.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */

/**
  * @brief  Enables or disables the Low Speed APB (APB1) peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @param  RCC_APB1Periph: specifies the APB1 peripheral to gates its clock.
  *          This parameter can be any combination of the following values:
  *           @arg RCC_APB1Periph_TIM2:   TIM2 clock
  *           @arg RCC_APB1Periph_TIM3:   TIM3 clock
  *           @arg RCC_APB1Periph_TIM6:   TIM6 clock
  *           @arg RCC_APB1Periph_TIM14:  TIM14 clock
  *           @arg RCC_APB1Periph_WWDG:   WWDG clock

  *           @arg RCC_APB1Periph_USART2: USART2 clock

  *           @arg RCC_APB1Periph_PWR:    PWR clock
  *           @arg RCC_APB1Periph_DAC:    DAC clock
  *           @arg RCC_APB1Periph_CEC:    CEC clock
  * @param  NewState: new state of the specified peripheral clock.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APB1PeriphClockCmd(uint32_t RCC_APB1Periph, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RCC_APB1_PERIPH(RCC_APB1Periph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (RCC_APB1Periph == RCC_APB1Periph_EXTI || RCC_APB1Periph == RCC_APB1Periph_ANACTRL)
    {
        if (NewState != DISABLE)
        {
            sysctrl_access();
            SYSCTRL->ClkEnR2 |= RCC_APB1Periph;
            __dekey();
        }
        else
        {
            sysctrl_access();
            SYSCTRL->ClkEnR2 &= ~RCC_APB1Periph;
            __dekey();
        }
    }
    else
    {
        if (NewState != DISABLE)
        {
            sysctrl_access();
            SYSCTRL->ClkEnR0 |= RCC_APB1Periph;
            __dekey();
        }
        else
        {
            sysctrl_access();
            SYSCTRL->ClkEnR0 &= ~RCC_APB1Periph;
            __dekey();
        }
    }
}

/**
 * @brief  Forces or releases AHB peripheral reset.
 * @param  RCC_AHBPeriph: specifies the AHB peripheral to reset.
 *          This parameter can be any combination of the following values:
 *             @arg RCC_AHBPeriph_GPIOA: GPIOA clock
 *             @arg RCC_AHBPeriph_GPIOB: GPIOB clock
 *             @arg RCC_AHBPeriph_GPIOC: GPIOC clock
 *             @arg RCC_AHBPeriph_GPIOD: GPIOD clock
 *             @arg RCC_AHBPeriph_GPIOF: GPIOF clock
 *             @arg RCC_AHBPeriph_TS:    TS clock
 * @param  NewState: new state of the specified peripheral reset.
 *          This parameter can be: ENABLE or DISABLE.
 * @retval None
 */
void RCC_AHBPeriphResetCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RCC_AHB_RST_PERIPH(RCC_AHBPeriph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        sysctrl_access();
        SYSCTRL->RST0 &= ~RCC_AHBPeriph;
        __dekey();
    }
    else
    {
        sysctrl_access();
        SYSCTRL->RST0 |= RCC_AHBPeriph;
        __dekey();
    }
}

/**
  * @brief  Forces or releases High Speed APB (APB2) peripheral reset.
  * @param  RCC_APB2Periph: specifies the APB2 peripheral to reset.
  *          This parameter can be any combination of the following values:
  *             @arg RCC_APB2Periph_SYSCFG: SYSCFG clock
  *             @arg RCC_APB2Periph_ADC1:   ADC1 clock
  *             @arg RCC_APB2Periph_TIM1:   TIM1 clock

  *             @arg RCC_APB2Periph_USART1: USART1 clock
  *             @arg RCC_APB2Periph_TIM15:  TIM15 clock
  *             @arg RCC_APB2Periph_TIM16:  TIM16 clock
  *             @arg RCC_APB2Periph_TIM17:  TIM17 clock
  *             @arg RCC_APB2Periph_DBGMCU: DBGMCU clock
  * @param  NewState: new state of the specified peripheral reset.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APB0PeriphResetCmd(uint32_t RCC_APB0Periph, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RCC_APB0_PERIPH(RCC_APB0Periph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        sysctrl_access();
        SYSCTRL->RST0 &= ~RCC_APB0Periph;
        __dekey();
    }
    else
    {
        sysctrl_access();
        SYSCTRL->RST0 |= RCC_APB0Periph;
        __dekey();
    }
}

void RCC_APB0PeriphClockCmd(uint32_t RCC_APB0Periph, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RCC_APB0_PERIPH(RCC_APB0Periph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        sysctrl_access();
        SYSCTRL->ClkEnR0 |= RCC_APB0Periph;
        __dekey();
    }
    else
    {
        sysctrl_access();
        SYSCTRL->ClkEnR0 &= ~RCC_APB0Periph;
        __dekey();
    }
}

/**
  * @brief  Forces or releases Low Speed APB (APB1) peripheral reset.
  * @param  RCC_APB1Periph: specifies the APB1 peripheral to reset.
  *          This parameter can be any combination of the following values:
  *           @arg RCC_APB1Periph_TIM2:   TIM2 clock
  *           @arg RCC_APB1Periph_TIM3:   TIM3 clock
  *           @arg RCC_APB1Periph_TIM6:   TIM6 clock
  *           @arg RCC_APB1Periph_TIM14:  TIM14 clock
  *           @arg RCC_APB1Periph_WWDG:   WWDG clock

  *           @arg RCC_APB1Periph_USART2: USART2 clock
  *           @arg RCC_APB1Periph_PWR:    PWR clock
  *           @arg RCC_APB1Periph_DAC:    DAC clock
  *           @arg RCC_APB1Periph_CEC:    CEC clock
  * @param  NewState: new state of the specified peripheral clock.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APB1PeriphResetCmd(uint32_t RCC_APB1Periph, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RCC_APB1_PERIPH(RCC_APB1Periph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (RCC_APB1Periph == RCC_APB1Periph_EXTI || RCC_APB1Periph == RCC_APB1Periph_ANACTRL)
    {
        if (NewState != DISABLE)
        {
            sysctrl_access();
            SYSCTRL->RST1 &= ~RCC_APB1Periph;
            __dekey();
        }
        else
        {
            sysctrl_access();
            SYSCTRL->RST1 |= RCC_APB1Periph;
            __dekey();
        }
    }
    else
    {
        if (NewState != DISABLE)
        {
            sysctrl_access();
            SYSCTRL->RST0 &= ~RCC_APB1Periph;
            __dekey();
        }
        else
        {
            sysctrl_access();
            SYSCTRL->RST0 |= RCC_APB1Periph;
            __dekey();
        }
    }
}
/**
 * @}
 */

/** @defgroup RCC_Group4 Interrupts and flags management functions
 *  @brief   Interrupts and flags management functions
 *
@verbatim
 ===============================================================================
             ##### Interrupts and flags management functions #####
 ===============================================================================
@endverbatim
  * @{
  */

/**
 * @brief  Enables or disables the specified RCC interrupts.
 * @note   The CSS interrupt doesn't have an enable bit; once the CSS is enabled
 *         and if the HSE clock fails, the CSS interrupt occurs and an NMI is
 *         automatically generated. The NMI will be executed indefinitely, and
 *         since NMI has higher priority than any other IRQ (and main program)
 *         the application will be stacked in the NMI ISR unless the CSS interrupt
 *         pending bit is cleared.
 * @param  RCC_IT: specifies the RCC interrupt sources to be enabled or disabled.
 *          This parameter can be any combination of the following values:
 *              @arg RCC_IT_LSIRDY: LSI ready interrupt
 *              @arg RCC_IT_LSERDY: LSE ready interrupt
 *              @arg RCC_IT_HSIRDY: HSI ready interrupt
 *              @arg RCC_IT_HSERDY: HSE ready interrupt
 *              @arg RCC_IT_PLLRDY: PLL ready interrupt
 *              @arg RCC_IT_HSI14RDY: HSI14 ready interrupt
 * @param  NewState: new state of the specified RCC interrupts.
 *          This parameter can be: ENABLE or DISABLE.
 * @retval None
 */
void RCC_ITConfig(uint8_t RCC_IT, FunctionalState NewState) //@zhang 用来配置和晶振相关的中断
{
    /* Check the parameters */
    assert_param(IS_RCC_IT(RCC_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        chipctrl_access();
        CHIPCTRL->CTRL |= RCC_IT;
        __dekey();
    }
    else
    {
        chipctrl_access();
        CHIPCTRL->CTRL &= ~RCC_IT;
        __dekey();
    }
}

/**
 * @brief  Checks whether the specified RCC flag is set or not.
 * @param  RCC_FLAG: specifies the flag to check.
 *          This parameter can be one of the following values:
 *             -@arg RCC_FLAG_HSIRDY: HSI oscillator clock ready
 *             -@arg RCC_FLAG_HSERDY: HSE oscillator clock ready
 *             @arg RCC_FLAG_PLLRDY: PLL clock ready
 *             -@arg RCC_FLAG_LSERDY: LSE oscillator clock ready
 *             @arg RCC_FLAG_LSIRDY: LSI oscillator clock ready
 *             @arg RCC_FLAG_OBLRST: Option Byte Loader (OBL) reset
 *             @arg RCC_FLAG_PINRST: Pin reset
 *             @arg RCC_FLAG_V18PWRRSTF:  V1.8 power domain reset
 *             @arg RCC_FLAG_PORRST: POR/PDR reset
 *             @arg RCC_FLAG_SFTRST: Software reset
 *             @arg RCC_FLAG_IWDGRST: Independent Watchdog reset
 *             @arg RCC_FLAG_WWDGRST: Window Watchdog reset
 *             @arg RCC_FLAG_LPWRRST: Low Power reset
 *             @arg RCC_FLAG_HSI14RDY: HSI14 oscillator clock ready
 * @retval The new state of RCC_FLAG (SET or RESET).
 */
FlagStatus RCC_GetFlagStatus(uint8_t RCC_FLAG) //@zhang edit(end).
{
    /* Check the parameters */
    assert_param(IS_RCC_FLAG(RCC_FLAG));

    if ((CHIPCTRL->STS >> RCC_FLAG) & 0x01)
    {
        return SET;
    }
    return RESET;
}

ITStatus RCC_GetITStatus(uint8_t RCC_IT)
{
    ITStatus bitstatus = RESET;

    /* Check the parameters */
    assert_param(IS_RCC_GET_IT(RCC_IT));

    /* Check the status of the specified RCC interrupt */
    if ((CHIPCTRL->STS >> RCC_IT) & 0x01)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    /* Return the RCC_IT status */
    return bitstatus;
}

void RCC_GetClockFreq(RCC_ClocksTypeDef *RCC_Clocks)
{
    uint32_t v_clk_src_sel;
    uint32_t v_pll_src;
    uint32_t v_pll_str;
    uint32_t v_sys_clk_sel;
    uint32_t v_sys_clk_sel76;
    uint32_t v_sys_clk_sel50;
    uint32_t v_regtmp;

    v_clk_src_sel = CHIPCTRL->CLK_CFG_b.CLK_SRC_SEL;
    v_pll_src = CHIPCTRL->PLL_CFG_b.PLL_SRC;

    RCC_Clocks->HSI_Frequency = _LCM32_GBL_HSI_nHZ;
    RCC_Clocks->LSI_Frequency = _LCM32_GBL_LSI_nHZ;
    RCC_Clocks->HSE_Frequency = _LCM32_GBL_HSE_nHZ;
    RCC_Clocks->LSE_Frequency = _LCM32_GBL_LSE_nHZ;

    if (v_clk_src_sel == 0) // RCH as sysclk
    {
        RCC_Clocks->SYSCLK_IN_Frequency = RCC_Clocks->HSI_Frequency;
    }
    else if (v_clk_src_sel == 2) // PLL as sysclk
    {
        if (v_pll_src) // HSE
        {
            v_pll_str = RCC_Clocks->HSE_Frequency;
        }
        else // HSI
        {
            v_pll_str = RCC_Clocks->HSI_Frequency;
        }
        RCC_Clocks->PLL_Frequency = v_pll_str / (CHIPCTRL->PLL_CFG_b.PLL_DM + 1) * (CHIPCTRL->PLL_CFG_b.PLL_DN + 1) / 2 / (CHIPCTRL->PLL_CFG_b.PLL_OD + 1);
        RCC_Clocks->SYSCLK_IN_Frequency = RCC_Clocks->PLL_Frequency;
    }
    else if (v_clk_src_sel == 1) // HSE as sysclk
    {
        RCC_Clocks->SYSCLK_IN_Frequency = RCC_Clocks->HSE_Frequency;
    }
    else // LSE as sysclk
    {
        RCC_Clocks->SYSCLK_IN_Frequency = RCC_Clocks->LSI_Frequency;
    }

    /*sys_clk after prescale*/
    v_sys_clk_sel = CHIPCTRL->CLK_CFG_b.SYS_CLK_SEL;
    v_sys_clk_sel76 = (v_sys_clk_sel >> 6) & (0x03);
    v_sys_clk_sel50 = (v_sys_clk_sel >> 0) & (0x3f);
    switch (v_sys_clk_sel76)
    {
    case 0x00:
        RCC_Clocks->SYSCLK_Frequency = RCC_Clocks->SYSCLK_IN_Frequency;
        break;
    case 0x01:
        RCC_Clocks->SYSCLK_Frequency = (RCC_Clocks->SYSCLK_IN_Frequency) / (2 * (v_sys_clk_sel50 + 1));
        break;
    case 0x02:
        RCC_Clocks->SYSCLK_Frequency = (RCC_Clocks->SYSCLK_IN_Frequency) / 3;
        break;
    case 0x03:
        RCC_Clocks->SYSCLK_Frequency = (RCC_Clocks->SYSCLK_IN_Frequency) / 5;
        break;
    default:
        break;
    }
    RCC_Clocks->HCLK_Frequency = RCC_Clocks->SYSCLK_Frequency;
    v_regtmp = CHIPCTRL->CLK_CFG_b.APB0_DIV;
    RCC_Clocks->PCLK0_Frequency = RCC_Clocks->SYSCLK_Frequency / (v_regtmp + 1);
    v_regtmp = CHIPCTRL->CLK_CFG_b.APB1_DIV;
    RCC_Clocks->PCLK1_Frequency = RCC_Clocks->SYSCLK_Frequency / (v_regtmp + 1);
    /*UART0 clk*/
    switch (SYSCTRL->ClkEnR1_b.UART0_CLKSEL)
    {
    case 0x00:
        RCC_Clocks->UART0_Frequency = RCC_Clocks->PCLK1_Frequency;
        break;
    case 0x01:
        RCC_Clocks->UART0_Frequency = RCC_Clocks->SYSCLK_IN_Frequency;
        break;
    case 0x02:
        RCC_Clocks->UART0_Frequency = RCC_Clocks->HSI_Frequency;
        break;
    case 0x03:
        RCC_Clocks->UART0_Frequency = RCC_Clocks->LSE_Frequency;
        break;
    default:
        break;
    }

    /*UART1 clk*/
    switch (SYSCTRL->ClkEnR1_b.UART1_CLKSEL)
    {
    case 0x00:
        RCC_Clocks->UART1_Frequency = RCC_Clocks->PCLK1_Frequency;
        break;
    case 0x01:
        RCC_Clocks->UART1_Frequency = RCC_Clocks->SYSCLK_IN_Frequency;
        break;
    case 0x02:
        RCC_Clocks->UART1_Frequency = RCC_Clocks->HSI_Frequency;
        break;
    case 0x03:
        RCC_Clocks->UART1_Frequency = RCC_Clocks->LSE_Frequency;
        break;
    default:
        break;
    }

    /*I2C0 clk*/
    switch (SYSCTRL->ClkEnR1_b.I2C0_CLKSEL)
    {
    case 0x00:
        RCC_Clocks->I2C0_Frequency = RCC_Clocks->PCLK1_Frequency;
        break;
    case 0x01:
        RCC_Clocks->I2C0_Frequency = RCC_Clocks->SYSCLK_IN_Frequency;
        break;
    case 0x02:
        RCC_Clocks->I2C0_Frequency = RCC_Clocks->HSI_Frequency;
        break;
    case 0x03:
        RCC_Clocks->I2C0_Frequency = RCC_Clocks->LSE_Frequency;
        break;
    default:
        break;
    }

    /*SPI0 clk*/
    switch (SYSCTRL->ClkEnR1_b.SSP0_CLKSEL)
    {
    case 0x00:
        RCC_Clocks->SPI0_Frequency = RCC_Clocks->PCLK1_Frequency;
        break;
    case 0x01:
        RCC_Clocks->SPI0_Frequency = RCC_Clocks->SYSCLK_IN_Frequency;
        break;
    case 0x02:
        RCC_Clocks->SPI0_Frequency = RCC_Clocks->HSI_Frequency;
        break;
    case 0x03:
        RCC_Clocks->SPI0_Frequency = RCC_Clocks->LSE_Frequency;
        break;
    default:
        break;
    }

    /*SPI2 clk*/
    switch (SYSCTRL->ClkEnR1_b.SSP2_CLKSEL)
    {
    case 0x00:
        RCC_Clocks->SPI2_Frequency = RCC_Clocks->PCLK1_Frequency;
        break;
    case 0x01:
        RCC_Clocks->SPI2_Frequency = RCC_Clocks->SYSCLK_IN_Frequency;
        break;
    case 0x02:
        RCC_Clocks->SPI2_Frequency = RCC_Clocks->HSI_Frequency;
        break;
    case 0x03:
        RCC_Clocks->SPI2_Frequency = RCC_Clocks->LSE_Frequency;
        break;
    default:
        break;
    }
}

/*
 * \breif PLL init for client user silly.
 *  please use it directly and don`t need invoke FUNCTION:RCC_Deinit();
 */

/************************ (C) COPYRIGHT LCMicroelectronics *****END OF FILE****/
