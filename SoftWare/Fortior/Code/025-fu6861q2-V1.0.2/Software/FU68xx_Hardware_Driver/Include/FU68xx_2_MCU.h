/******************* (C) COPYRIGHT 2020 Fortiortech Shenzhen *******************
* File Name          : FU68xx_2_MCU.h
* Creat Author       : Bruce Long, R&D
* Modify Author      : Any Lin, R&D
* Creat Date         : 2020-08-13
* Modify Date        : 2020-11-12
* Description        :
********************************************************************************
* All Rights Reserved
*******************************************************************************/

#ifndef __FU68XX_2_MCU_H__
#define __FU68XX_2_MCU_H__

/**************************************************************************************************///Including Header Files
#include <FU68xx_2_Type.h>
/**************************************************************************************************///Define Macro
#define FREC                       24000000                           //               MCU工作频率
/**************************************************************************************************///Function Subject
#define SetReg(reg, val1, val2)    (reg = reg & (~(val1)) | (val2))   //               将reg中val1对应的位写val2
#define SetBit(reg, val)           (reg |=  (val))                    //               将reg中val对应的位写1
#define ClrBit(reg, val)           (reg &= ~(val))                    //               将reg中val对应的位写0
#define XorBit(reg, val)           (reg ^=  (val))                    //               将reg中val对应的位取反
#define ReadBit(reg, val)          ((reg & (val)) == (val))           //               判断reg中val对应的位是否为1
/**************************************************************************************************///Register Map
// 搜索快照寄存器请在Keil搜索"[0-9A-Z]__[A-Z]"，勾选"Match Case"和"Regular Expressior"
// 快速搜索外设方法:在搜索对话框中输入"//"+外设名称.例:搜索TIMER1,则输入"//TIM1"

/********************************************************************///SFR
 sfr16   DPTR                      = 0x82;                            // RV:0000H      8051指针

 sfr     PSW                       = 0xd0;                            // RV:  00H      8051状态寄存器
 sbit    CY                                         = PSW^7;          //                   rw-- 进/借位标志
 sbit    AC                                         = PSW^6;          //                   rw-- BCD进/借位标志
 sbit    F0                                         = PSW^5;          //                   rw-- 用户自定义标志0
 sbit    RS1                                        = PSW^4;          //                   rw-- R寄存器换页位1
 sbit    RS0                                        = PSW^3;          //                   rw-- R寄存器换页位0
 sbit    OV                                         = PSW^2;          //                   rw-- 算术运算溢出标志
 sbit    F1                                         = PSW^1;          //                   rw-- 用户自定义标志1
 sbit    P                                          = PSW^0;          //                   rw-- 奇偶标志
/********************************************************************///RST
 sfr     RST_SR                    = 0xc9;                            // RV:  xxH      复位状态寄存器
 #define RSTPOW                                     0x80              //                   r--- 上电复位标志
 #define RSTEXT                                     0x40              //                   r--- 外部复位标志
 #define RSTLVD                                     0x20              //                   r--- 低压复位标志
 #define RSTEOS                                     0x10              //                   r--- 电应力过度复位标志
 #define RSTWDT                                     0x08              //                   r--- 看门狗复位标志
 #define RSTFED                                     0x04              //                   r--- 代码保护复位
 #define RSTDBG                                     0x02              //                   r--- 调试接口复位
 #define RSTCLR                                     0x01              //                   rw1- 清除复位标志
/********************************************************************///IRQ
 // IRQ Channel
 // LVW             interrupt 0
 // INT0            interrupt 1
 // INT1            interrupt 2
 // DRV             interrupt 3
 // TIM2            interrupt 4
 // TIM1            interrupt 5
 // ADC             interrupt 6
 // CMP             interrupt 7
 // RTC             interrupt 8
 // TIM3            interrupt 9
 // TIM4/SysTick    interrupt 10
 // TSD             interrupt 11
 // UART            interrupt 12
 // I2C             interrupt 13
 // SPI             interrupt 14
 // DMA             interrupt 15

 sfr     TCON                      = 0x88;                            // RV:  00H      8051中断控制寄存器
 sbit    TSDIF                                      = TCON^5;         //                   rw-- TSD温度感应中断标志
 sbit    IT11                                       = TCON^4;         //                   rw-- 外部中断1触发配置1
 sbit    IT10                                       = TCON^3;         //                   rw-- 外部中断1触发配置0
 sbit    IF0                                        = TCON^2;         //                   rw-- 外部中断0标志
 sbit    IT01                                       = TCON^1;         //                   rw-- 外部中断0触发配置1
 sbit    IT00                                       = TCON^0;         //                   rw-- 外部中断0触发配置0

 sfr     IE                        = 0xa8;                            // RV:  00H      8051 中断开关
 sbit    EA                                         = IE^7;           //                   rw-- MCU总中断使能
 sbit    RTCIE                                      = IE^6;           //                   rw-- RTC中断使能
 sbit    ES0                                        = IE^4;           //                   rw-- UART中断使能
 sbit    SPIIE                                      = IE^3;           //                   rw-- SPI中断使能
 sbit    EX1                                        = IE^2;           //                   rw-- 外部中断1使能
 sbit    TSDIE                                      = IE^1;           //                   rw-- TSD中断使能
 sbit    EX0                                        = IE^0;           //                   rw-- 外部中断0使能

 sfr     IP0                       = 0xb8;                            // RV:  00H      外设中断优先级设置G0
 sbit    PDRV1                                      = IP0^7;          //                   rw-- DRV优先级配置1
 sbit    PDRV0                                      = IP0^6;          //                   rw-- DRV优先级配置0
 sbit    PX11                                       = IP0^5;          //                   rw-- 外部中断1优先级配置1
 sbit    PX10                                       = IP0^4;          //                   rw-- 外部中断1优先级配置0
 sbit    PX01                                       = IP0^3;          //                   rw-- 外部中断0优先级配置1
 sbit    PX00                                       = IP0^2;          //                   rw-- 外部中断0优先级配置0
 sbit    PLVW1                                      = IP0^1;          //                   rw-- LVW优先级配置1
 sbit    PLVW0                                      = IP0^0;          //                   rw-- LVW优先级配置0

 sfr     IP1                       = 0xc0;                            // RV:  00H      外设中断优先级设置G1
 sbit    PCMP1                                      = IP1^7;          //                   rw-- CMP优先级配置1
 sbit    PCMP0                                      = IP1^6;          //                   rw-- CMP优先级配置0
 sbit    PADC1                                      = IP1^5;          //                   rw-- ADC优先级配置1
 sbit    PADC0                                      = IP1^4;          //                   rw-- ADC优先级配置0
 sbit    PTIM11                                     = IP1^3;          //                   rw-- TIM1优先级配置1
 sbit    PTIM10                                     = IP1^2;          //                   rw-- TIM1优先级配置0
 sbit    PTIM21                                     = IP1^1;          //                   rw-- TIM2优先级配置1
 sbit    PTIM20                                     = IP1^0;          //                   rw-- TIM2优先级配置0

 sfr     IP2                       = 0xc8;                            // RV:  00H      外设中断优先级设置G2
 sbit    PTSD1                                      = IP2^7;          //                   rw-- TSD优先级配置1
 sbit    PTSD0                                      = IP2^6;          //                   rw-- TSD优先级配置0
 sbit    PTIM4S1                                    = IP2^5;          //                   rw-- TIM4/SysTick优先级配置1
 sbit    PTIM4S0                                    = IP2^4;          //                   rw-- TIM4/SysTick优先级配置0
 sbit    PTIM31                                     = IP2^3;          //                   rw-- TIM3优先级配置1
 sbit    PTIM30                                     = IP2^2;          //                   rw-- TIM3优先级配置0
 sbit    PRTC1                                      = IP2^1;          //                   rw-- RTC优先级配置1
 sbit    PRTC0                                      = IP2^0;          //                   rw-- RTC优先级配置0

 sfr     IP3                       = 0xd8;                            // RV:  00H      外设中断优先级设置G3
 sbit    PDMA1                                      = IP3^7;          //                   rw-- DMA优先级配置1
 sbit    PDMA0                                      = IP3^6;          //                   rw-- DMA优先级配置0
 sbit    PSPI1                                      = IP3^5;          //                   rw-- SPI优先级配置1
 sbit    PSPI0                                      = IP3^4;          //                   rw-- SPI优先级配置0
 sbit    PI2C1                                      = IP3^3;          //                   rw-- I2C优先级配置1
 sbit    PI2C0                                      = IP3^2;          //                   rw-- I2C优先级配置0
 sbit    PUART1                                     = IP3^1;          //                   rw-- UART优先级配置1
 sbit    PUART0                                     = IP3^0;          //                   rw-- UART优先级配置0
/********************************************************************///I2C
 #define I2C_CR                    *(_IO  uint8 xdata *)0x4028        // RV:  00H      I2C控制寄存器
 #define I2CEN                                      0x80              //                   rw-- I2C使能
 #define I2CMS                                      0x40              //                   rw-- 主/从机模式选择
 #define CMP4OUT                                    0x08              //                   r--- CMP4 OUT
 #define I2CSPD1                                    0x04              //                   rw-- 速度配置1
 #define I2CSPD0                                    0x02              //                   rw-- 速度配置0
 #define I2CIE                                      0x01              //                   rw-- 中断控制

 #define I2C_SR                    *(_IO  uint8 xdata *)0x402b        // RV:  00H      I2C状态寄存器
 #define I2CBSY                                     0x80              //                   r--- I2C忙标志
 #define DMOD                                       0x40              //                   rw-- I2C读写控制
 #define I2CSTA                                     0x10              //                   rw-- START信号控制
 #define I2CSTP                                     0x08              //                   rw-- STOP信号控制
 #define STR                                        0x04              //                   rw-- I2C事件完成标志
 #define NACK                                       0x02              //                   rw-- 应答信号控制
 #define I2CIF                                      0x01              //                   r--- 中断标志

 #define I2C_ID                    *(_IO  uint8 xdata *)0x4029        // RV:  00H      本机2C地址
 #define GC                                         0x01              //                   广播模式

 #define I2C_DR                    *(_IO  uint8 xdata *)0x402a        // RV:  00H      I2C数据寄存器
/********************************************************************///SPI
 #define SPI_CR0                   *(_IO  uint8 xdata *)0x4030        // RV:  0bH      SPI控制寄存器1
 #define SPIBSY                                     0x80              //                   r--- 忙标志
 #define SPIMS                                      0x40              //                   rw-- 主/从机配置
 #define CPHA                                       0x20              //                   rw-- 时钟相位
 #define CPOL                                       0x10              //                   rw-- 时钟空闲电平
 #define SLVSEL                                     0x08              //                   r--- NSS处理后的信号
 #define NSSIN                                      0x04              //                   r--- NSS即时信号
 #define SRMT                                       0x02              //                   r--- 移位寄存器空标志
 #define RXBMT                                      0x01              //                   r--- 接收缓冲器空标志

 #define SPI_CR1                   *(_IO  uint8 xdata *)0x4031        // RV:  02H      SPI控制寄存器2
 #define SPIIF                                      0x80              //                   rw0- 中断标志
 #define WCOL                                       0x40              //                   rw0- 写冲突标志
 #define MODF                                       0x20              //                   rw0- 模式错误标志
 #define RXOVR                                      0x10              //                   rw0- 接收溢出标志
 #define NSSMOD1                                    0x08              //                   rw-- SPI模式配置位1
 #define NSSMOD0                                    0x04              //                   rw-- SPI模式配置位0
 #define TXBMT                                      0x02              //                   r--- 发送缓冲器空标志
 #define SPIEN                                      0x01              //                   rw-- SPI使能

 #define SPI_CLK                   *(_IO  uint8 xdata *)0x4032        // RV:  00H      SPI时钟配置寄存器
 #define SPI_DR                    *(_IO  uint8 xdata *)0x4033        // RV:  00H      SPI数据寄存器
/********************************************************************///UART
 sfr     UT_CR                     = 0x98;                            // RV:  00H      UART控制寄存器
 sbit    UT_MOD1                                    = UT_CR^7;        //                   rw-- UART模式配置1
 sbit    UT_MOD0                                    = UT_CR^6;        //                   rw-- UART模式配置0
 sbit    SM2                                        = UT_CR^5;        //                   rw-- 多机通信使能
 sbit    REN                                        = UT_CR^4;        //                   rw-- 接收使能
 sbit    TB8                                        = UT_CR^3;        //                   rw-- 9位模式下发送的第9位
 sbit    RB8                                        = UT_CR^2;        //                   rw-- 9位模式下接收的第9位
 sbit    TI                                         = UT_CR^1;        //                   rw-- 发送完成标志
 sbit    RI                                         = UT_CR^0;        //                   rw-- 接收完成标志

 sfr16   UT_BAUD                   = 0x9a;                            // RV:009bH      UART波特率控制寄存器
 #define UART_2xBAUD                                0x8000            //                   rw--倍频使能

 sfr     UT_DR                     = 0x99;                            // RV:  00H      UART数据寄存器
/********************************************************************///MDU
 sfr     MDU_CR                    = 0xc1;                            // RV:  80H      MDU控制寄存器
 #define DIVDONE                                    0x80              //                   r--- 除法运算完成标志
 #define DIVERR                                     0x40              //                   r--- 除法运算错误标志
 #define ALIGN1                                     0x08              //                   rw-- 乘法右移配置1
 #define ALIGN0                                     0x04              //                   rw-- 乘法右移配置0
 #define MDSN                                       0x02              //                   rw-- 乘法符号配置
 #define DIVSTA                                     0x01              //                   rw-- 除法使能
 #define MDUBSY                                     0x80              //                   r--- 当使能SMDU时, 用于表示MDU繁忙
 #define MDUSTA3                                    0x40              //                   rw-- 当使能SMDU时, 用于表示启动计算单元3
 #define MDUSTA2                                    0x20              //                   rw-- 当使能SMDU时, 用于表示启动计算单元2
 #define MDUSTA1                                    0x10              //                   rw-- 当使能SMDU时, 用于表示启动计算单元1
 #define MDUSTA0                                    0x08              //                   rw-- 当使能SMDU时, 用于表示启动计算单元0
 #define MDUMOD2                                    0x04              //                   rw-- 当使能SMDU时, 用于表示MDU运行模式配置2
 #define MDUMOD1                                    0x02              //                   rw-- 当使能SMDU时, 用于表示MDU运行模式配置1
 #define MDUMOD0                                    0x01              //                   rw-- 当使能SMDU时, 用于表示MDU运行模式配置0

 sfr16   MDU_MA                    = 0xc2;                            // RV:0000H      乘法操作数A
 sfr16   MDU_MB                    = 0xca;                            // RV:0000H      乘法操作数B
 sfr16   MDU_DA01                  = 0xc4;                            // RV:0000H      除法操作数A-被除数或商的[15:0]
 sfr16   MDU_DA23                  = 0xc6;                            // RV:0000H      除法操作数A-被除数或商的[31:16]
 sfr16   MDU_DB01                  = 0xcc;                            // RV:0000H      除法操作数B-除数或余数[15:0]

 sfr     MDU_DA0                   = 0xc4;                            // RV:  00H      除法操作数A-除数或商的[7:0]
 sfr     MDU_DA1                   = 0xc5;                            // RV:  00H      除法操作数A-除数或商的[15:8]
 sfr     MDU_DA2                   = 0xc6;                            // RV:  00H      除法操作数A-除数或商的[23:16]
 sfr     MDU_DA3                   = 0xc7;                            // RV:  00H      除法操作数A-除数或商的[31:24]

 sfr     MDU_DB0                   = 0xcc;                            // RV:  00H      除法操作数B-除数或余数的[7:0]
 sfr     MDU_DB1                   = 0xcd;                            // RV:  00H      除法操作数B-除数或余数的[15:8]
/********************************************************************///PI
 sfr     PI_LPF_CR                 = 0xf9;                            //               PI/LPF/T2控制寄存器
 #define T2TSS                                      0x80              //                   rw-- TIM2步进模式输入使能
 #define T2RPD                                      0x40
 #define RANGE                                      0x04              //                   rw-- PI参数格式
 #define PISTA                                      0x02              //                   r0w- PI使能
 #define LPFSTA                                     0x01              //                   r0w- LPF使能

 sfr16   PI_EK                     = 0xea;                            // RV:0000H      误差输入
 sfr16   PI_UK                     = 0xec;                            // RV:0000H      结果输出
 sfr16   PI_KP                     = 0xee;                            // RV:0000H      比例参数
 sfr16   PI_KI                     = 0xf2;                            // RV:0000H      积分参数
 sfr16   PI_UKMAX                  = 0xf4;                            // RV:0000H      输出允许的最大值
 sfr16   PI_UKMIN                  = 0xf6;                            // RV:0000H      输出允许的最小值
/********************************************************************///LPF
 sfr     LPF_K                     = 0xdd;                            // RV:  00H      滤波系数
 sfr16   LPF_X                     = 0xde;                            // RV:0000H      滤波输入
 sfr16   LPF_Y                     = 0xe6;                            // RV:0000H      滤波输出
/********************************************************************///FOC
 #define FOC_CR1                   *(_IO  uint8 xdata *)0x40a0        // RV:  00H      FOC控制寄存器1
 #define OVMDL                                      0x80              //                   rw-- 过调制使能
 #define EFAE                                       0x40              //                   rw-- 估算器强制角度使能
 #define RFAE                                       0x20              //                   rw-- 强制爬坡角度使能
 #define ANGM                                       0x10              //                   rw-- 角度模式选择
 #define CSM1                                       0x08              //                   rw-- 电流采样模式配置1
 #define CSM0                                       0x04              //                   rw-- 电流采样模式配置0
 #define SPWMSEL                                    0x02              //                   rw-- SPWM模式选择
 #define SVPWMEN                                    0x01              //                   rw-- SVPWM/SPWM选择

 #define FOC_CR2                   *(_IO  uint8 xdata *)0x40a1        // RV:  00H      FOC控制寄存器2
 #define ESEL                                       0x80              //                   rw-- 估算器模式
 #define F5SEG                                      0x20              //                   rw-- 7/5段式SVPWM模式
 #define DSS                                        0x10              //                   rw-- 2/3电阻采样模式
 #define CSOC1                                      0x08              //                   rw-- 电流采样基准校准配置1
 #define CSOC0                                      0x04              //                   rw-- 电流采样基准校准配置0
 #define UQD                                        0x02              //                   rw-- 禁能Q轴PI
 #define UDD                                        0x01              //                   rw-- 禁能D轴PI

 #define FOC_EKP                   *(_IO  int16 xdata *)0x4074        // RV:0000H      估算器的PI的P参数
 #define FOC_EKI                   *(_IO  int16 xdata *)0x4076        // RV:0000H      估算器的PI的I参数
 #define FOC_KSLIDE                *(_IO  int16 xdata *)0x4078        // RV:0000H      估算器SMO模式下的KSLIDE  或  PLL模式下的KP
 #define FOC_EKLPFMIN              *(_IO  int16 xdata *)0x407a        // RV:0000H      估算器SMO模式下BMF的LPF系数最小值  或  PLL模式下的KI
 #define FOC_EBMFK                 *(_IO  int16 xdata *)0x407c        // RV:0000H      估算器反电动势的LPF系数
 #define FOC_OMEKLPF               *(_IO  int16 xdata *)0x407e        // RV:0000H      估算器速度计算的LPF系数
 #define FOC_FBASE                 *(_IO  int16 xdata *)0x4080        // RV:0000H      估算器角度增量(OMEGA)的系数
 #define FOC_EFREQACC              *(_IO uint16 xdata *)0x4082        // RV:0000H      估算器在强制角度模式下的OMEGA增量
 #define FOC_EFREQMIN              *(_IO  int16 xdata *)0x4084        // RV:0000H      估算器在强制角度模式下的OMEGA最小值
 #define FOC_EFREQHOLD             *(_IO  int16 xdata *)0x4086        // RV:0000H      估算器在强制角度模式下的OMEGA保持值
 #define FOC_EK3                   *(_IO  int16 xdata *)0x4088        // RV:0000H      估算器估算电流的系数3
 #define FOC_EK4                   *(_IO  int16 xdata *)0x408a        // RV:0000H      估算器估算电流的系数4
 #define FOC_EK1                   *(_IO  int16 xdata *)0x408c        // RV:0000H      估算器估算电流的系数1
 #define FOC_EK2                   *(_IO  int16 xdata *)0x408e        // RV:0000H      估算器估算电流的系数2
 #define FOC_IDREF                 *(_IO  int16 xdata *)0x4090        // RV:0000H      D轴电流参考值
 #define FOC_IQREF                 *(_IO  int16 xdata *)0x4092        // RV:0000H      Q轴电流参考值
 #define FOC_DQKP                  *(_IO  int16 xdata *)0x4094        // RV:0000H      DQ轴PI的比例参数
 #define FOC_DQKI                  *(_IO  int16 xdata *)0x4096        // RV:0000H      DQ轴PI的积分参数
 #define FOC__UDCFLT               *(_I   int16 xdata *)0x4098        // RV:0000H      滤波后的母线电压
 #define FOC_TSMIN                 *(_IO  uint8 xdata *)0x40a2        // RV:  00H      单电阻模式下的ADC采样窗口  或  双三电阻模式下死区补偿
 #define FOC_TGLI                  *(_IO  uint8 xdata *)0x40a3        // RV:  00H      上桥导通窄脉冲消除
 #define FOC_TBLO                  *(_IO  uint8 xdata *)0x40a4        // RV:  00H      三电阻电流采样的屏蔽时间
 #define FOC_TRGDLY                *(_IO   int8 xdata *)0x40a5        // RV:  00H      单电阻模式下ADC采样触发延迟  或  双三电阻模式下电流采样时机
 #define FOC_CSO                   *(_IO  int16 xdata *)0x40a6        // RV:4040H      电流采样基准值
 #define FOC__RTHESTEP             *(_IO  int16 xdata *)0x40a8        // RV:0000H      爬坡速度
 #define FOC_RTHEACC               *(_IO  int16 xdata *)0x40aa        // RV:0000H      爬坡加速度
 #define FOC__RTHECNT              *(_IO  uint8 xdata *)0x40ac        // RV:  00H      爬坡次数
 #define FOC_THECOR                *(_IO  uint8 xdata *)0x40ad        // RV:  01H      爬坡模式切换到估算模式的角度修正值
 #define FOC_THECOMP               *(_IO  int16 xdata *)0x40ae        // RV:0000H      角度补偿值，用于补偿估算器估算出的角度
 #define FOC_DMAX                  *(_IO  int16 xdata *)0x40b0        // RV:0000H      D轴PI控制器的输出上限
 #define FOC_DMIN                  *(_IO  int16 xdata *)0x40b2        // RV:0000H      D轴PI控制器的输出下限
 #define FOC_QMAX                  *(_IO  int16 xdata *)0x40b4        // RV:0000H      Q轴PI控制器的输出上限
 #define FOC_QMIN                  *(_IO  int16 xdata *)0x40b6        // RV:0000H      Q轴PI控制器的输出下限
 #define FOC__UD                   *(_IO  int16 xdata *)0x40b8        // RV:0000H      D轴电压输出值
 #define FOC__UQ                   *(_IO  int16 xdata *)0x40ba        // RV:0000H      Q轴电压输出值
 #define FOC__ID                   *(_I   int16 xdata *)0x40bc        // RV:0000H      D轴反馈电流值
 #define FOC__IQ                   *(_I   int16 xdata *)0x40be        // RV:0000H      Q轴反馈电流值
 #define FOC__IBET                 *(_I   int16 xdata *)0x40c0        // RV:0000H      X轴采样电流值
 #define FOC__VBET                 *(_I   int16 xdata *)0x40c2        // RV:0000H      X轴电压输出值
 #define FOC__VALP                 *(_I   int16 xdata *)0x40c4        // RV:0000H      Y轴电压输出值
 #define FOC__IC                   *(_I   int16 xdata *)0x40c6        // RV:0000H      相电流C
 #define FOC__IB                   *(_I   int16 xdata *)0x40c8        // RV:0000H      相电流B
 #define FOC__IA                   *(_I   int16 xdata *)0x40ca        // RV:0000H      相电流A
 #define FOC__THETA                *(_IO  int16 xdata *)0x40cc        // RV:0000H      电机电角度
 #define FOC__EALP                 *(_I   int16 xdata *)0x40d0        // RV:0000H      估算器估算反电动势的α轴值
 #define FOC__EBET                 *(_I   int16 xdata *)0x40d2        // RV:0000H      估算器估算反电动势的β轴值
 #define FOC__ETHETA               *(_IO  int16 xdata *)0x40ce        // RV:0000H      估算器估算的角度
 #define FOC__EOME                 *(_IO  int16 xdata *)0x40d4        // RV:0000H      估算器估算的速度
 #define FOC__ESQU                 *(_I   int16 xdata *)0x40d6        // RV:0000H      估算器计算的反电动势的平方
 #define FOC__POW                  *(_I   int16 xdata *)0x40d8        // RV:0000H      电机当前运行功率
/********************************************************************///TIM1
 #define TIM1_CR0                  *(_IO  uint8 xdata *)0x4068        // RV:  00H      TIMER1控制寄存器0
 #define T1RWEN                                     0x80              //                   r0w- T1RCEN操作允许
 #define T1CFLT1                                    0x40              //                   rw-- 换相滤波配置1
 #define T1CFLT0                                    0x20              //                   rw-- 换相滤波配置0
 #define T1FORC                                     0x10              //                   rw-- 60°强制换相
 #define T1OPS1                                     0x08              //                   rw-- 数据传输方式配置1
 #define T1OPS0                                     0x04              //                   rw-- 数据传输方式配置0
 #define T1BCEN                                     0x02              //                   rw-- 基本定时器计数使能
 #define T1RCEN                                     0x01              //                   rw-- 重载定时器计数使能

 #define TIM1_CR1                  *(_IO  uint8 xdata *)0x4069        // RV:  00H      TIMER1控制寄存器1
 #define T1BAPE                                     0x80              //                   rw-- TIM1__BARR自动装载使能

 #define TIM1_CR2                  *(_IO  uint8 xdata *)0x406a        // RV:  00H      TIMER1控制寄存器2
 #define T1BRS                                      0x80              //                   rw-- 基本定时器复位源选择

 #define TIM1_CR3                  *(_IO  uint8 xdata *)0x406b        // RV:  00H      TIMER1控制寄存器3
 #define T1AFL                                      0x80
 #define T1PSC2                                     0x40              //                   rw-- 定时器分频配置2
 #define T1PSC1                                     0x20              //                   rw-- 定时器分频配置1
 #define T1PSC0                                     0x10              //                   rw-- 定时器分频配置0
 #define T1TIS1                                     0x08              //                   rw-- 输入源选择配置1
 #define T1TIS0                                     0x04              //                   rw-- 输入源选择配置0
 #define T1INM1                                     0x02              //                   rw-- 输入源噪声滤波配置1
 #define T1INM0                                     0x01              //                   rw-- 输入源噪声滤波配置0

 #define TIM1_CR4                  *(_IO  uint8 xdata *)0x406c        // RV:  00H      TIMER1控制寄存器4
 #define T1CST2                                     0x04              //                   rw-- 换相状态机配置2
 #define T1CST1                                     0x02              //                   rw-- 换相状态机配置1
 #define T1CST0                                     0x01              //                   rw-- 换相状态机配置0

 #define TIM1_IER                  *(_IO  uint8 xdata *)0x406d        // RV:  00H      TIMER1中断控制
 #define T1UPD                                      0x80              //                   r0w- OPS=00时，触发数据传输
 #define T1MAME                                     0x40              //                   rw-- TIM1手动模式使能
 #define T1ADIE                                     0x20              //                   rw-- ADC检测中断使能
 #define T1BOIE                                     0x10              //                   rw-- 基本定时器上溢中断使能
 #define T1ROIE                                     0x08              //                   rw-- 重载定时器上溢中断使能
 #define T1WTIE                                     0x04              //                   rw-- 写入时序中断使能
 #define T1PDIE                                     0x02              //                   rw-- 位置检测中断使能
 #define T1BDIE                                     0x01              //                   rw-- 屏蔽续流结束中断使能

 #define TIM1_SR                   *(_IO  uint8 xdata *)0x406e        // RV:  00H      TIMER1状态
 #define T1ADIF                                     0x20              //                   rw0- ADC检测中断标志
 #define T1BOIF                                     0x10              //                   rw0- 基本定时器上溢中断标志
 #define T1ROIF                                     0x08              //                   rw0- 重载定时器上溢中断标志
 #define T1WTIF                                     0x04              //                   rw0- 写入时序中断标志
 #define T1PDIF                                     0x02              //                   rw0- 位置检测中断标志
 #define T1BDIF                                     0x01              //                   rw0- 屏蔽续流结束中断标志


 #define TIM1_DBR1                 *(_IO uint16 xdata *)0x4074        // RV:0000H      TIMER1在CST=1的数据
 #define TIM1_DBR2                 *(_IO uint16 xdata *)0x4076        // RV:0000H      TIMER1在CST=2的数据
 #define TIM1_DBR3                 *(_IO uint16 xdata *)0x4078        // RV:0000H      TIMER1在CST=3的数据
 #define TIM1_DBR4                 *(_IO uint16 xdata *)0x407a        // RV:0000H      TIMER1在CST=4的数据
 #define TIM1_DBR5                 *(_IO uint16 xdata *)0x407c        // RV:0000H      TIMER1在CST=5的数据
 #define TIM1_DBR6                 *(_IO uint16 xdata *)0x407e        // RV:0000H      TIMER1在CST=6的数据
 #define TIM1_DBR7                 *(_IO uint16 xdata *)0x4080        // RV:0000H      TIMER1在CST=7的数据
 #define T1CPE2                                     0x4000            //                   rw-- 输入沿极性和比较器选择配置2
 #define T1CPE1                                     0x2000            //                   rw-- 输入沿极性和比较器选择配置1
 #define T1CPE0                                     0x1000            //                   rw-- 输入沿极性和比较器选择配置0
 #define T1WHP                                      0x0800            //                   rw-- W相上管输出极性
 #define T1WLP                                      0x0400            //                   rw-- W相下管输出极性
 #define T1VHP                                      0x0200            //                   rw-- V相上管输出极性
 #define T1VLP                                      0x0100            //                   rw-- V相下管输出极性
 #define T1UHP                                      0x0080            //                   rw-- U相上管输出极性
 #define T1ULP                                      0x0040            //                   rw-- U相下管输出极性
 #define T1WHE                                      0x0020            //                   rw-- W相上管输出使能
 #define T1WLE                                      0x0010            //                   rw-- W相下管输出使能
 #define T1VHE                                      0x0008            //                   rw-- V相上管输出使能
 #define T1VLE                                      0x0004            //                   rw-- V相下管输出使能
 #define T1UHE                                      0x0002            //                   rw-- U相上管输出使能
 #define T1ULE                                      0x0001            //                   rw-- U相下管输出使能

 #define TIM1_BCOR                 *(_IO uint16 xdata *)0x4070        // RV:0000H      捕获基本定时器计数值滤波值
 #define TIM1__BCNTR               *(_IO uint16 xdata *)0x4082        // RV:0000H      基本定时器计数值
 #define TIM1__BCCR                *(_IO uint16 xdata *)0x4084        // RV:0000H      捕获基本定时器计数值
 #define TIM1__BARR                *(_IO uint16 xdata *)0x4086        // RV:0000H      基本定时器自动重载值
 #define TIM1__RARR                *(_IO uint16 xdata *)0x4088        // RV:0000H      重载定时器自动重载值
 #define TIM1__RCNTR               *(_IO uint16 xdata *)0x408a        // RV:0000H      重载定时器计数值
 #define TIM1__ITRIP               *(_I  uint16 xdata *)0x4098        // RV:0000H      滤波后的母线电流

 #define TIM1__UCOP                *(_IO uint16 xdata *)0x408c        // RV:0000H      导通相的电压 
 #define TIM1__UFLP                *(_IO uint16 xdata *)0x408e        // RV:0000H      悬空相的电压
 #define TIM1__URES                *(_IO  int16 xdata *)0x4090        // RV:0000H      电压计算结果
 #define TIM1__UIGN                *(_IO uint16 xdata *)0x4092        // RV:0000H      导通相忽略电压
 #define TIM1_KF                   *(_IO uint16 xdata *)0x4094        // RV:0000H      下降沿系数
 #define TIM1_KR                   *(_IO uint16 xdata *)0x4096        // RV:0000H      上升沿系数
/********************************************************************///TIM2
 sfr     TIM2_CR0                  = 0xa1;                            // RV:  00H      TIMER2控制寄存器0
 #define T2PSC2                                     0x80              //                   rw-- 定时器分频配置2
 #define T2PSC1                                     0x40              //                   rw-- 定时器分频配置1
 #define T2PSC0                                     0x20              //                   rw-- 定时器分频配置0
 #define T2OCM                                      0x10              //                   rw-- 定时器比较匹配模式/QEP&步进模式配置
 #define T2IRE                                      0x08              //                   rw-- 比较匹配/脉宽检测/方向改变中断使能
 #define T2CES                                      0x04              //                   rw-- 边沿模式选择
 #define T2MOD1                                     0x02              //                   rw-- 定时器模式配置1
 #define T2MOD0                                     0x01              //                   rw-- 定时器模式配置0

 sfr     TIM2_CR1                  = 0xa9;                            // RV:  00H      TIMER2控制寄存器1
 #define T2IR                                       0x80              //                   rw0- 比较匹配标志
 #define T2IP                                       0x40              //                   rw0- 周期检测/计数匹配标志
 #define T2IF                                       0x20              //                   rw0- 计数上溢标志
 #define T2IPE                                      0x10              //                   rw-- 周期检测/计数匹配中断使能
 #define T2IFE                                      0x08              //                   rw-- 上溢中断使能
 #define T2FE                                       0x04              //                   rw-- 噪声滤波使能
 #define T2DIR                                      0x02              //                   r--- QEP/步进方向信号
 #define T2EN                                       0x01              //                   rw-- 定时器使能

 sfr16   TIM2__CNTR                = 0xaa;                            // RV:0000H      TIMER2计数器
 sfr16   TIM2__DR                  = 0xac;                            // RV:0000H      TIMER2匹配计数器
 sfr16   TIM2__ARR                 = 0xae;                            // RV:0000H      TIMER2重载计数器
/********************************************************************///TIM3
 sfr     TIM3_CR0                  = 0x9c;                            // RV:  00H      TIMER3控制寄存器0
 #define T3PSC2                                     0x80              //                   rw-- 定时器分频配置2
 #define T3PSC1                                     0x40              //                   rw-- 定时器分频配置1
 #define T3PSC0                                     0x20              //                   rw-- 定时器分频配置0
 #define T3OCM                                      0x10              //                   rw-- 定时器比较匹配/捕获脉宽模式配置
 #define T3IRE                                      0x08              //                   rw-- 比较匹配/捕获脉宽中断
 #define T3OPM                                      0x02              //                   rw-- 单次模式使能
 #define T3MOD                                      0x01              //                   rw-- 定时器模式配置0

 sfr     TIM3_CR1                  = 0x9d;                            // RV:  00H      TIMER3控制寄存器1
 #define T3IR                                       0x80              //                   rw0- 比较匹配/捕获脉宽标志
 #define T3IP                                       0x40              //                   rw0- 周期检测标志
 #define T3IF                                       0x20              //                   rw0- 计数上溢标志
 #define T3IPE                                      0x10              //                   rw-- 周期检测中断使能
 #define T3IFE                                      0x08              //                   rw-- 上溢中断使能
 #define T3FE1                                      0x04              //                   rw-- 噪音滤波配置1
 #define T3FE0                                      0x02              //                   rw-- 噪音滤波配置0
 #define T3EN                                       0x01              //                   rw-- 定时器使能

 sfr16   TIM3__CNTR                = 0xa2;                            // RV:0000H      TIMER3计数值
 sfr16   TIM3__DR                  = 0xa4;                            // RV:0000H      TIMER3匹配值
 sfr16   TIM3__ARR                 = 0xa6;                            // RV:0000H      TIMER3重载值
/********************************************************************///TIM4
 sfr     TIM4_CR0                  = 0x9e;                            // RV:  00H      TIMER4控制寄存器0
 #define T4PSC2                                     0x80              //                   rw-- 定时器分频配置2
 #define T4PSC1                                     0x40              //                   rw-- 定时器分频配置1
 #define T4PSC0                                     0x20              //                   rw-- 定时器分频配置0
 #define T4OCM                                      0x10              //                   rw-- 定时器比较匹配/捕获脉宽模式配置
 #define T4IRE                                      0x08              //                   rw-- 比较匹配/捕获脉宽中断
 #define T4OPM                                      0x02              //                   rw-- 单次模式使能
 #define T4MOD                                      0x01              //                   rw-- 定时器模式配置0

 sfr     TIM4_CR1                  = 0x9f;                            // RV:  00H      TIMER4控制寄存器1
 #define T4IR                                       0x80              //                   rw0- 比较匹配/捕获脉宽标志
 #define T4IP                                       0x40              //                   rw0- 周期检测标志
 #define T4IF                                       0x20              //                   rw0- 计数上溢标志
 #define T4IPE                                      0x10              //                   rw-- 周期检测中断使能
 #define T4IFE                                      0x08              //                   rw-- 上溢中断使能
 #define T4FE1                                      0x04              //                   rw-- 噪音滤波配置1
 #define T4FE0                                      0x02              //                   rw-- 噪音滤波配置0
 #define T4EN                                       0x01              //                   rw-- 定时器使能

 sfr16   TIM4__CNTR                = 0x92;                            // RV:0000H      TIMER4计数值
 sfr16   TIM4__DR                  = 0x94;                            // RV:0000H      TIMER4匹配值
 sfr16   TIM4__ARR                 = 0x96;                            // RV:0000H      TIMER4重载值
/********************************************************************///SYSTICK
 #define SYST_ARR                  *(_IO uint16 xdata *)0x4064        // RV:5dbfH      SysTick重载值
/********************************************************************///DRV
 sfr     DRV_OUT                   = 0xf8;                            // RV:  00H      驱动输出控制寄存器
 sbit    MOE                                        = DRV_OUT^7;      //                   rw-- 主输出使能
 sbit    OISWXL                                     = DRV_OUT^5;      //                   rw-- WL & XL输出空闲电平
 sbit    OISWXH                                     = DRV_OUT^4;      //                   rw-- WH & XH输出空闲电平
 sbit    OISVL                                      = DRV_OUT^3;      //                   rw-- VL输出空闲电平
 sbit    OISVH                                      = DRV_OUT^2;      //                   rw-- VH输出空闲电平
 sbit    OISUL                                      = DRV_OUT^1;      //                   rw-- UL输出空闲电平
 sbit    OISUH                                      = DRV_OUT^0;      //                   rw-- UH输出空闲电平

 #define DRV_DR                    *(_IO uint16 xdata *)0x4058        // RV:0000H      手动控制输出时设定的比较值
 #define DRV_COMR                  *(_IO uint16 xdata *)0x405a        // RV:0000H      计数器的比较匹配值

 #define DRV_CMR                   *(_IO uint16 xdata *)0x405c        // RV:0000H      输出配置寄存器
 #define XHP                                        0x8000            //                   rw-- X相上管输出极性
 #define XLP                                        0x4000            //                   rw-- X相下管输出极性
 #define XHE                                        0x2000            //                   rw-- X相上管输出使能
 #define XLE                                        0x1000            //                   rw-- X相下管输出使能
 #define WHP                                        0x0800            //                   rw-- W相上管输出极性
 #define WLP                                        0x0400            //                   rw-- W相下管输出极性
 #define VHP                                        0x0200            //                   rw-- V相上管输出极性
 #define VLP                                        0x0100            //                   rw-- V相下管输出极性
 #define UHP                                        0x0080            //                   rw-- U相上管输出极性
 #define ULP                                        0x0040            //                   rw-- U相下管输出极性
 #define WHE                                        0x0020            //                   rw-- W相上管输出使能
 #define WLE                                        0x0010            //                   rw-- W相下管输出使能
 #define VHE                                        0x0008            //                   rw-- V相上管输出使能
 #define VLE                                        0x0004            //                   rw-- V相下管输出使能
 #define UHE                                        0x0002            //                   rw-- U相上管输出使能
 #define ULE                                        0x0001            //                   rw-- U相下管输出使能

 #define DRV_ARR                   *(_IO uint16 xdata *)0x405e        // RV:0000H      计数器重载值
 #define DRV_DTR                   *(_IO  uint8 xdata *)0x4060        // RV:  00H      上下管死区时间

 #define DRV_SR                    *(_IO  uint8 xdata *)0x4061        // RV:  00H      Driver状态寄存器
 #define SYSTIF                                     0x80              //                   rw0- SysTick中断标志
 #define SYSTIE                                     0x40              //                   rw-- SysTick中断使能
 #define FGIF                                       0x20              //                   rw0- FG中断标志
 #define DCIF                                       0x10              //                   rw0- 比较匹配中断标志
 #define FGIE                                       0x08              //                   rw-- FG中断使能
 #define DCIP                                       0x04              //                   rw-- 产生比较匹配中断的间隔
 #define DCIM1                                      0x02              //                   rw-- 比较匹配中断模式配置1
 #define DCIM0                                      0x01              //                   rw-- 比较匹配中断模式配置0

 #define DRV_CR                    *(_IO  uint8 xdata *)0x4062        // RV:  00H      Driver控制寄存器
 #define DRVEN                                      0x80              //                   rw-- 计数器使能
 #define DDIR                                       0x40              //                   rw-- 输出方向
 #define FOCEN                                      0x20              //                   rw-- FOC/SVPWM/SPWM模块使能
 #define DRPE                                       0x10              //                   rw-- DRV_DR预装载使能
 #define OCS                                        0x08              //                   rw-- 比较值来源选择
 #define MESEL                                      0x04              //                   rw-- ME核工作模式选择
 #define DRVOE                                      0x01              //                   rw-- Driver输出使能
/********************************************************************///WDT
 #define WDT_CR                    *(_IO  uint8 xdata *)0x4026        // RV:  00H      看门狗控制寄存器
 #define WDTF                                       0x02              //                   rw0- 看门狗复位标志
 #define WDTRF                                      0x01              //                   rw-- 看门狗初始化标志

 #define WDT_REL                   *(_IO  uint8 xdata *)0x4027        // RV:  00H      看门狗重载计数器
/********************************************************************///GPIO
 sfr     P0                        = 0x80;                            // RV:  00H      Port 0
 sbit    GP00                                       = P0^0;
 sbit    GP01                                       = P0^1;
 sbit    GP02                                       = P0^2;
 sbit    GP03                                       = P0^3;
 sbit    GP04                                       = P0^4;
 sbit    GP05                                       = P0^5;
 sbit    GP06                                       = P0^6;
 sbit    GP07                                       = P0^7;

 sfr     P1                        = 0x90;                            // RV:  00H      Port 1
 sbit    GP10                                       = P1^0;
 sbit    GP11                                       = P1^1;
 sbit    GP12                                       = P1^2;
 sbit    GP13                                       = P1^3;
 sbit    GP14                                       = P1^4;
 sbit    GP15                                       = P1^5;
 sbit    GP16                                       = P1^6;
 sbit    GP17                                       = P1^7;

 sfr     P2                        = 0xa0;                            // RV:  00H      Port 2
 sbit    GP20                                       = P2^0;
 sbit    GP21                                       = P2^1;
 sbit    GP22                                       = P2^2;
 sbit    GP23                                       = P2^3;
 sbit    GP24                                       = P2^4;
 sbit    GP25                                       = P2^5;
 sbit    GP26                                       = P2^6;
 sbit    GP27                                       = P2^7;

 sfr     P3                        = 0xb0;                            // RV:  00H      Port 3
 sbit    GP30                                       = P3^0;
 sbit    GP31                                       = P3^1;
 sbit    GP32                                       = P3^2;
 sbit    GP33                                       = P3^3;
 sbit    GP34                                       = P3^4;
 sbit    GP35                                       = P3^5;
 sbit    GP36                                       = P3^6;
 sbit    GP37                                       = P3^7;

 sfr     P4                        = 0xe8;                            // RV:  00H      Port 4
 sbit    GP40                                       = P4^0;
 sbit    GP41                                       = P4^1;
 sbit    GP42                                       = P4^2;

 sfr     P0_OE                     = 0xfc;                            // RV:  00H      P0输出使能寄存器
 #define P0_PU                     *(_IO  uint8 xdata *)0x4053        // RV:  00H      P0上拉使能寄存器
 #define P07                                        0x80              //                   rw-- 使能端口7
 #define P06                                        0x40              //                   rw-- 使能端口6
 #define P05                                        0x20              //                   rw-- 使能端口5
 #define P04                                        0x10              //                   rw-- 使能端口4
 #define P03                                        0x08              //                   rw-- 使能端口3
 #define P02                                        0x04              //                   rw-- 使能端口2
 #define P01                                        0x02              //                   rw-- 使能端口1
 #define P00                                        0x01              //                   rw-- 使能端口0

 sfr     P1_IE                     = 0xd1;                            // RV:  00H      P1外部中断使能寄存器
 sfr     P1_IF                     = 0xd2;                            // RV:  00H      P1外部中断状态寄存器
 sfr     P1_OE                     = 0xfd;                            // RV:  00H      P1输出使能寄存器
 #define P1_PU                     *(_IO  uint8 xdata *)0x4054        // RV:  00H      P1上拉使能寄存器
 #define P17                                        0x80              //                   rw-- 使能端口7
 #define P16                                        0x40              //                   rw-- 使能端口6
 #define P15                                        0x20              //                   rw-- 使能端口5
 #define P14                                        0x10              //                   rw-- 使能端口4
 #define P13                                        0x08              //                   rw-- 使能端口3
 #define P12                                        0x04              //                   rw-- 使能端口2
 #define P11                                        0x02              //                   rw-- 使能端口1
 #define P10                                        0x01              //                   rw-- 使能端口0

 #define P1_AN                     *(_IO  uint8 xdata *)0x4050        // RV:  00H      P1模拟使能寄存器
 #define P17                                        0x80              //                   rw-- 使能端口7
 #define P16                                        0x40              //                   rw-- 使能端口6
 #define P15                                        0x20              //                   rw-- 使能端口5
 #define P14                                        0x10              //                   rw-- 使能端口4
 #define HBMOD                                      0x08              //                   rw-- 端口3模式配置
 #define HDIO                                       0x04              //                   rw-- Gate Driver驱动能力选择
 #define ODE1                                       0x02              //                   rw-- P01漏极开路使能
 #define ODE0                                       0x01              //                   rw-- P00漏极开路使能

 sfr     P2_IE                     = 0xd3;                            // RV:  00H      P2外部中断使能寄存器
 sfr     P2_IF                     = 0xd4;                            // RV:  00H      P2外部中断状态寄存器
 sfr     P2_OE                     = 0xfe;                            // RV:  00H      P2输出使能寄存器
 #define P2_PU                     *(_IO  uint8 xdata *)0x4055        // RV:  00H      P2上拉使能寄存器
 #define P2_AN                     *(_IO  uint8 xdata *)0x4051        // RV:  00H      P2模拟使能寄存器
 #define P27                                        0x80              //                   rw-- 使能端口7
 #define P26                                        0x40              //                   rw-- 使能端口6
 #define P25                                        0x20              //                   rw-- 使能端口5
 #define P24                                        0x10              //                   rw-- 使能端口4
 #define P23                                        0x08              //                   rw-- 使能端口3
 #define P22                                        0x04              //                   rw-- 使能端口2
 #define P21                                        0x02              //                   rw-- 使能端口1
 #define P20                                        0x01              //                   rw-- 使能端口0

 sfr     P3_OE                     = 0xff;                            // RV:  00H      P3输出使能寄存器
 #define P3_PU                     *(_IO  uint8 xdata *)0x4056        // RV:  00H      P3上拉使能寄存器
 #define P37                                        0x80              //                   rw-- 使能端口7
 #define P36                                        0x40              //                   rw-- 使能端口6
 #define P35                                        0x20              //                   rw-- 使能端口5
 #define P34                                        0x10              //                   rw-- 使能端口4
 #define P33                                        0x08              //                   rw-- 使能端口3
 #define P32                                        0x04              //                   rw-- 使能端口2
 #define P31                                        0x02              //                   rw-- 使能端口1
 #define P30                                        0x01              //                   rw-- 使能端口0

 #define P3_AN                     *(_IO  uint8 xdata *)0x4052        // RV:  00H      P3模拟使能寄存器
 #define P35                                        0x20              //                   rw-- 使能端口5
 #define P34                                        0x10              //                   rw-- 使能端口4
 #define P33                                        0x08              //                   rw-- 使能端口3
 #define P32                                        0x04              //                   rw-- 使能端口2
 #define P31                                        0x02              //                   rw-- 使能端口1
 #define P30                                        0x01              //                   rw-- 使能端口0

 sfr     P4_OE                     = 0xe9;                            // RV:  00H      P4输出使能寄存器
 #define P4_PU                     *(_IO  uint8 xdata *)0x4057        // RV:  00H      P4上拉使能寄存器
 #define P42                                        0x04              //                   rw-- 使能端口2
 #define P41                                        0x02              //                   rw-- 使能端口1
 #define P40                                        0x01              //                   rw-- 使能端口0

 #define PIN7                                       0x80              //                   rw-- PIN7, 用于替代上面的端口编号
 #define PIN6                                       0x40              //                   rw-- PIN6, 用于替代上面的端口编号
 #define PIN5                                       0x20              //                   rw-- PIN5, 用于替代上面的端口编号
 #define PIN4                                       0x10              //                   rw-- PIN4, 用于替代上面的端口编号
 #define PIN3                                       0x08              //                   rw-- PIN3, 用于替代上面的端口编号
 #define PIN2                                       0x04              //                   rw-- PIN2, 用于替代上面的端口编号
 #define PIN1                                       0x02              //                   rw-- PIN1, 用于替代上面的端口编号
 #define PIN0                                       0x01              //                   rw-- PIN0, 用于替代上面的端口编号

 #define PH_SEL                    *(_IO  uint8 xdata *)0x404c        // RV:  00H      端口复用
 #define SPITMOD                                    0x80              //                   rw-- SPI从机发送端在发送完成后变为高阻态
 #define UARTEN                                     0x40              //                   rw-- 端口复用为UART
 #define UARTCH                                     0x20              //                   rw-- UART端口功能转移
 #define T4SEL                                      0x10              //                   rw-- 端口复用为TIM4
 #define T3SEL                                      0x08              //                   rw-- 端口复用为TIM3
 #define T2SEL                                      0x04              //                   rw-- 端口复用为TIM2
 #define T2SSEL                                     0x02              //                   rw-- 端口复用为TIM2S
 #define XOE                                        0x01              //                   rw-- 端口复用为X相驱动端
/********************************************************************///ADC
 #define ADC_MASK_SYSC             *(_IO uint16 xdata *)0x4036        // RV:3000H      ADC通道使能和部分通道采样时间配置
 #define CH11EN                                     0x0800            //                   rw-- ADC通道11使能
 #define CH10EN                                     0x0400            //                   rw-- ADC通道10使能
 #define CH9EN                                      0x0200            //                   rw-- ADC通道9使能
 #define CH8EN                                      0x0100            //                   rw-- ADC通道8使能
 #define CH7EN                                      0x0080            //                   rw-- ADC通道7使能
 #define CH6EN                                      0x0040            //                   rw-- ADC通道6使能
 #define CH5EN                                      0x0020            //                   rw-- ADC通道5使能
 #define CH4EN                                      0x0010            //                   rw-- ADC通道4使能
 #define CH3EN                                      0x0008            //                   rw-- ADC通道3使能
 #define CH2EN                                      0x0004            //                   rw-- ADC通道2使能
 #define CH1EN                                      0x0002            //                   rw-- ADC通道1使能
 #define CH0EN                                      0x0001            //                   rw-- ADC通道0使能

 #define ADC_CR                    *(_IO  uint8 xdata *)0x4039        // RV:  00H      ADC控制寄存器
 #define ADCEN                                      0x80              //                   rw-- 使能ADC
 #define ADCBSY                                     0x40              //                   rw1- ADC启动 & ADC忙标志
 #define ADCALIGN                                   0x04              //                   rw-- ADC数据次高位对齐
 #define ADCIE                                      0x02              //                   rw-- ADC中断使能
 #define ADCIF                                      0x01              //                   rw-- ADC中断标志

 #define ADC_SYSC                  *(_IO  uint8 xdata *)0x4038        // RV:  33H      ADC通道采样时间配置
 #define ADC0_DR                   *(_I  uint16 xdata *)0x0300        // RV:0000H      ADC通道11转换结果
 #define ADC1_DR                   *(_I  uint16 xdata *)0x0302        // RV:0000H      ADC通道10转换结果
 #define ADC2_DR                   *(_I  uint16 xdata *)0x0304        // RV:0000H      ADC通道9转换结果
 #define ADC3_DR                   *(_I  uint16 xdata *)0x0306        // RV:0000H      ADC通道8转换结果
 #define ADC4_DR                   *(_I  uint16 xdata *)0x0308        // RV:0000H      ADC通道7转换结果
 #define ADC5_DR                   *(_I  uint16 xdata *)0x030a        // RV:0000H      ADC通道6转换结果
 #define ADC6_DR                   *(_I  uint16 xdata *)0x030c        // RV:0000H      ADC通道5转换结果
 #define ADC7_DR                   *(_I  uint16 xdata *)0x030e        // RV:0000H      ADC通道4转换结果
 #define ADC8_DR                   *(_I  uint16 xdata *)0x0310        // RV:0000H      ADC通道3转换结果
 #define ADC9_DR                   *(_I  uint16 xdata *)0x0312        // RV:0000H      ADC通道2转换结果
 #define ADC10_DR                  *(_I  uint16 xdata *)0x0314        // RV:0000H      ADC通道1转换结果
 #define ADC11_DR                  *(_I  uint16 xdata *)0x0316        // RV:0000H      ADC通道0转换结果
/********************************************************************///DAC
 #define DAC_CR                    *(_IO  uint8 xdata *)0x4035        // RV:  00H      DAC控制寄存器
 #define DACEN                                      0x80              //                   rw-- DAC使能
 #define DACMOD                                     0x40              //                   rw-- DAC模式配置

 #define DAC_DR                    *(_IO  uint8 xdata *)0x404b        // RV:  00H      DAC输出值
/********************************************************************///DMA
 #define DMA0_CR0                  *(_IO uint8  xdata *)0x403a        // RV:  00H      DMA通道0配置 & DMA公共配置
 #define DMA1_CR0                  *(_IO uint8  xdata *)0x403b        // RV:  00H      DMA通道1配置 & Debug设置
 #define DMAEN                                      0x80              //                   rw-- DMA通道0/1使能
 #define DMABSY                                     0x40              //                   rw1- DMA通道0/1状态/启动
 #define DMACFG2                                    0x20              //                   rw-- DMA通道0/1外设与方向选择位2
 #define DMACFG1                                    0x10              //                   rw-- DMA通道0/1外设与方向选择位1
 #define DMACFG0                                    0x08              //                   rw-- DMA通道0/1外设与方向选择位0
 #define DBGSW                                      0x04              //                   rw-- DMA通道1  DBG模式指向区域
 #define DBGEN                                      0x02              //                   rw-- DMA通道1  DBG模式使能
 #define DMAIE                                      0x04              //                   rw-- DMA中断使能,位于DMA_CR0
 #define ENDIAN                                     0x02              //                   rw-- DMA数据传输顺序,位于DMA_CR0
 #define DMAIF                                      0x01              //                   rw0- DMA通道0/1中断标志位

 #define DMA0_CR1                  *(_IO uint16 xdata *)0x403c        // RV:0000H      DMA通道0传输长度和首地址配置
 #define DMA1_CR1                  *(_IO uint16 xdata *)0x403e        // RV:0000H      DMA通道1传输长度和首地址配置
/********************************************************************///VREF & VHALF
 #define VREF_VHALF_CR             *(_IO  uint8 xdata *)0x404f        // RV:  00H      VREF & VHALF控制寄存器
 #define VRVSEL1                                    0x80              //                   rw-- VREF电压配置1
 #define VRVSEL0                                    0x40              //                   rw-- VREF电压配置0
 #define VREFEN                                     0x10              //                   rw-- VREF使能
 #define VHALFEN                                    0x01              //                   rw-- VHALF使能
/********************************************************************///AMP
 #define AMP_CR                    *(_IO  uint8 xdata *)0x404e        // RV:  00H      运放控制寄存器
 #define AMP2EN                                     0x04              //                   rw-- 运放2使能
 #define AMP1EN                                     0x02              //                   rw-- 运放1使能
 #define AMP0EN                                     0x01              //                   rw-- 运放0使能
/********************************************************************///CMP
 sfr     CMP_CR0                   = 0xd5;                            // RV:  00H      比较器控制寄存器0
 #define CMP3IM1                                    0x80              //                   rw-- CMP3中断模式配置1
 #define CMP3IM0                                    0x40              //                   rw-- CMP3中断模式配置0
 #define CMP2IM1                                    0x20              //                   rw-- CMP2中断模式配置1
 #define CMP2IM0                                    0x10              //                   rw-- CMP2中断模式配置0
 #define CMP1IM1                                    0x08              //                   rw-- CMP1中断模式配置1
 #define CMP1IM0                                    0x04              //                   rw-- CMP1中断模式配置0
 #define CMP0IM1                                    0x02              //                   rw-- CMP0中断模式配置1
 #define CMP0IM0                                    0x01              //                   rw-- CMP0中断模式配置0

 sfr     CMP_CR1                   = 0xd6;                            // RV:  00H      比较器控制寄存器1
 #define HALLSEL                                    0x80              //                   rw-- 霍尔信号输入选择
 #define CMP3MOD1                                   0x40              //                   rw-- CMP3正输入端选择配置1
 #define CMP3MOD0                                   0x20              //                   rw-- CMP3正输入端选择配置0
 #define CMP3EN                                     0x10              //                   rw-- CMP3使能
 #define CMP3HYS                                    0x08              //                   rw-- CMP3迟滞使能
 #define CMP0HYS2                                   0x04              //                   rw-- CMP0迟滞电压配置2
 #define CMP0HYS1                                   0x02              //                   rw-- CMP0迟滞电压配置1
 #define CMP0HYS0                                   0x01              //                   rw-- CMP0迟滞电压配置0

 sfr     CMP_CR2                   = 0xda;                            // RV:  00H      比较器控制寄存器2
 #define CMP4EN                                     0x80              //                   rw-- CMP4使能
 #define CMP0MOD1                                   0x40              //                   rw-- CMP0模式配置1
 #define CMP0MOD0                                   0x20              //                   rw-- CMP0模式配置0
 #define CMP0SEL1                                   0x10              //                   rw-- CMP0端口组合配置1
 #define CMP0SEL0                                   0x08              //                   rw-- CMP0端口组合配置0
 #define CMP0CSEL1                                  0x04              //                   rw-- CMP0轮询速度配置1
 #define CMP0CSEL0                                  0x02              //                   rw-- CMP0轮询速度配置0
 #define CMP0EN                                     0x01              //                   rw-- CMP0使能

 sfr     CMP_CR3                   = 0xdc;                            // RV:  00H      比较器控制寄存器3
 #define CMPDTEN                                    0x80              //                   rw-- 比较器死区采样使能
 #define DBGSEL1                                    0x40              //                   rw-- DBG信号配置1
 #define DBGSEL0                                    0x20              //                   rw-- DBG信号配置0
 #define SAMSEL1                                    0x10              //                   rw-- CMP0/1/2 & ADC 采样时机配置1
 #define SAMSEL0                                    0x08              //                   rw-- CMP0/1/2 & ADC 采样时机配置0
 #define CMPSEL2                                    0x04              //                   rw-- 比较器输出选择配置2
 #define CMPSEL1                                    0x02              //                   rw-- 比较器输出选择配置1
 #define CMPSEL0                                    0x01              //                   rw-- 比较器输出选择配置0

 sfr     CMP_SR                    = 0xd7;                            // RV:  00H      比较器状态寄存器
 #define CMP3IF                                     0x80              //                   rw0- CMP3中断标志
 #define CMP2IF                                     0x40              //                   rw0- CMP2中断标志
 #define CMP1IF                                     0x20              //                   rw0- CMP1中断标志
 #define CMP0IF                                     0x10              //                   rw0- CMP0中断标志
 #define CMP3OUT                                    0x08              //                   r--- CMP3比较结果
 #define CMP2OUT                                    0x04              //                   r--- CMP2比较结果
 #define CMP1OUT                                    0x02              //                   r--- CMP1比较结果
 #define CMP0OUT                                    0x01              //                   r--- CMP0比较结果

 sfr     EVT_FILT                  = 0xd9;                            // RV:  00H      驱动保护功能
 #define TSDEN                                      0x80              //                   rw-- 温度感应使能
 #define TSDADJ1                                    0x40              //                   rw-- 感应温度配置1
 #define TSDADJ0                                    0x20              //                   rw-- 感应温度配置0
 #define MOEMD1                                     0x10              //                   rw-- MOE自动控制配置1
 #define MOEMD0                                     0x08              //                   rw-- MOE自动控制配置0
 #define EFSRC                                      0x04              //                   rw-- 母线保护滤波模块输入来源
 #define EFDIV1                                     0x02              //                   rw-- 母线电流保护滤波配置1
 #define EFDIV0                                     0x01              //                   rw-- 母线电流保护滤波配置0

 #define CMP_SAMR                  *(_IO  uint8 xdata *)0x40ad        // RV:  00H      比较器采样配置
/********************************************************************///FLASH
 sfr     FLA_KEY                   = 0x84;                            // RV:  00H      FLASH解锁寄存器
 #define FLAKSTA1                                   0x02              //                   rw-- FLASH解锁状态位1
 #define FLAKSTA0                                   0x01              //                   rw-- FLASH解锁状态位0

 sfr     FLA_CR                    = 0x85;                            // RV:  00H      FLASH控制寄存器
 #define FLAWNP                                     0x80              //                     rw-- FLASH单独操作使能
 #define FLAERR                                     0x10              //                   r--- FLASH错误标志位
 #define FLAACT                                     0x08              //                   rw1- FLASH操作开始
 #define FLAERS                                     0x02              //                   rw-- FLASH清除使能
 #define FLAEN                                      0x01              //                   rw-- FLASH编程使能
/********************************************************************///CRC
 #define CRC_DIN                   *(_O   uint8 xdata *)0x4021        // RV:  00H      CRC数据输入寄存器

 #define CRC_CR                    *(_IO  uint8 xdata *)0x4022        // RV:  10H      CRC控制寄存器
 #define CRCDONE                                    0x10              //                   r1-- 自动CRC完成标志
 #define CRCDINI                                    0x08              //                   r0w1 CRC初始化
 #define CRCVAL                                     0x04              //                   rw-- CRC初始化的值
 #define AUTOINT                                    0x02              //                   rw-- CRC自动计算使能
 #define CRCPNT                                     0x01              //                   rw-- CRC结果访问位置

 #define CRC_DR                    *(_IO  uint8 xdata *)0x4023        // RV:  00H      CRC结果输出寄存器
 #define CRC_BEG                   *(_IO  uint8 xdata *)0x4024        // RV:  00H      CRC自动计算的起始位置
 #define CRC_CNT                   *(_IO  uint8 xdata *)0x4025        // RV:  00H      CRC块数计数器
/********************************************************************///POWER
 sfr     PCON                      = 0x87;                            // RV:  00H      MCU功率控制寄存器
 #define GF3                                        0x20              //                   rw-- 通用标志3
 #define GF2                                        0x10              //                   rw-- 通用标志2
 #define GF1                                        0x08              //                   rw-- 通用标志1
 #define LDOM                                       0x04              //                   rw-- LDO5功耗模式选择
 #define STOP                                       0x02              //                   rw-- MCU睡眠使能
 #define IDEL                                       0x01              //                   rw-- MCU待机使能

 sfr     LVSR                      = 0xdb;                            // RV:  00H      状态寄存器
 #define EXT0CFG2                                   0x20              //                   rw-- 外部中断0端口配置2
 #define EXT0CFG1                                   0x10              //                   rw-- 外部中断0端口配置1
 #define EXT0CFG0                                   0x08              //                   rw-- 外部中断0端口配置0
 #define TSDF                                       0x04              //                   rw-- 过温标志位
 #define LVWF                                       0x02              //                   rw-- VCC低电压标志
 #define LVWIF                                      0x01              //                   rw-- VCC低电压中断标志

 #define CCFG1                     *(_IO  uint8 xdata *)0x401e        // RV:  00H      配置寄存器
 #define LVDENB                                     0x80              //                   rw-- 低压复位检测使能
 #define LVWIE                                      0x40              //                   rw-- VCC低压中断使能
 #define WDTEN                                      0x20              //                   rw-- 看门狗使能
 #define FCKSEL1                                    0x04              //                   rw-- 系统快时钟配置1
 #define FCKSEL0                                    0x02              //                   rw-- 系统快时钟配置0

/********************************************************************///NEW
 #define EXT0                      *(_IO  uint8 xdata *)0x40f0        // RV:  00H
 #define FAEN                                       0x20              //                   rw-- 使能后CMP_SAMR扩大4倍
 #define MOEMD2                                     0x10              //                   rw-- MOE逐波限流的10us档位
 #define T1COM_MD                                   0x08              //                   rw-- 方波换相模式选择
 #define CMPXO_P11                                  0x04              //                   rw-- P07比较器输出功能转移-->P11
 #define TIM4_CT                                    0x02              //                   rw-- P01 DBG/TIME4功能转移-->P06
 #define EXT0_P11                                   0x01              //                   rw-- P11 INT0

 #define TIM234_CTRL               *(_IO  uint8 xdata *)0x40f1        // RV:  00H
 #define MDU_EN_N                                   0x40              //                    rw-- 此位为1时, 关闭MDU启动SMDU
 #define TIM2_FAST_DIR                              0x20              //                    rw-- TIM2 QEP模式下, 快速识别方向
 #define TIM2_DR_SEL                                0x10              //                    rw-- TIM2 QEP模式下, 当计数值到达TIM2__DR或者0时复位为0或TIM2__DR
 #define TIM4_RCTRL                                 0x08              //                    rw-- TIM4_ARR溢出时DR=0/ffff
 #define TIM3_RCTRL                                 0x04              //                    rw-- TIM3_ARR溢出时DR=0/ffff
 #define TIM2_RCTRL                                 0x02              //                    rw-- TIM2_ARR溢出时DR=0/ffff
 #define TIM3_48M                                   0x01              //                    rw-- TIM3_48M输入捕获使能
 
 #define CMP_AMP                   *(_IO  uint8 xdata *)0x40f2        // RV:  00H
 #define DAC_D_0                                    0x80              //                    rw-- DAC数据寄存器最低位
 #define AMP_PH_GAIN2                               0x40              //                    rw-- AMP1/2 PGA增益控制位2 
 #define AMP_PH_GAIN1                               0x20              //                    rw-- AMP1/2 PGA增益控制位1
 #define AMP_PH_GAIN0                               0x10              //                    rw-- AMP1/2 PGA增益控制位0 
 #define AMP0_GAIN2                                 0x08              //                    rw-- AMP0 PGA增益控制位2
 #define AMP0_GAIN1                                 0x04              //                    rw-- AMP0 PGA增益控制位1 
 #define AMP0_GAIN0                                 0x02              //                    rw-- AMP0 PGA增益控制位0
 #define CMP3P4M_FS                                 0x01              //                    rw-- P27(CMP3P和CMP4M)功能转移至P34 
 
 #define TSD_ADJ                   *(_IO  uint8 xdata *)0x40f3        // RV:  00H
 #define AMP12M_GND                                 0x08              //                    rw-- P17(AMP1M)&P22(AMP2M)接GND使能
 #define AMP0M_GND                                  0x04              //                    rw-- P30(AMP0M)接GND使能
 #define TSDADJ3                                    0x02              //                    rw-- TSD温度配置最高位
 #define TSDADJ0_0                                  0x01              //                    rw-- TSD温度配置最低位 

 #define FOC_CR3                   *(_IO  uint8 xdata *)0x40ee        // RV:  00H      FOC控制寄存器3
 #define ICLR                                       0x80              //                   rw-- FOC__IA/B/CMAX清零
 #define MFP_EN                                     0x20              //                   rw-- MFP使能
 #define FOCUSTA                                    0x10              //                   rw-- 单电阻off采样使能
 #define FOCFEN                                     0x08              //                   rw-- FOC强制使能
 #define ESCMS                                      0x04              //                   rw-- ATAN估算使能
 #define TSMINH9                                    0x02              //                   rw-- 单电阻模式下的ADC采样窗口  或  双三电阻模式下死区补偿
 #define TSMINH8                                    0x01              //                   rw-- 单电阻模式下的ADC采样窗口  或  双三电阻模式下死区补偿

 #define FOC_DKP                   *(_IO  int16 xdata *)0x409c        // RV:0000H      D轴PI的比例参数
 #define FOC_DKI                   *(_IO  int16 xdata *)0x409e        // RV:0000H      D轴PI的积分参数
 #define FOC__IAMAX                *(_I  uint16 xdata *)0x40da        // RV:0000H      FOC IAMAX
 #define FOC__IBMAX                *(_I  uint16 xdata *)0x40dc        // RV:0000H      FOC IBMAX
 #define FOC__ICMAX                *(_I  uint16 xdata *)0x40de        // RV:0000H      FOC ICMAX
 #define FOC__EMF                  *(_I  uint16 xdata *)0x40e0        // RV:0000H      FOC反电动势
 #define FOC__UDCPS                *(_IO  int16 xdata *)0x40e2        // RV:0000H      FOC D轴的电压补偿值
 #define FOC__UQCPS                *(_IO  int16 xdata *)0x40e4        // RV:0000H      FOC Q轴的电压补偿值
 #define FOC__UQEX                 *(_I   int16 xdata *)0x40e6        // RV:0000H      FOC Q轴PI控制器的UQ溢出值

 #define FOC_ID_LPFK               *(_IO  uint8 xdata *)0x40e8        // RV:  FFH      FOC ID低通滤波系数
 #define FOC_IQ_LPFK               *(_IO  uint8 xdata *)0x40e9        // RV:  FFH      FOC IQ低通滤波系数
 #define FOC_KFG                   *(_IO uint16 xdata *)0x40ea        // RV:0000H      FOC TIM4 FG系数

 /******************************************************************************///RTC
 #define RTC_TM                    *(_IO uint16 xdata *)0x402c        // RV:FFFFH      RTC计数寄存器
 #define RTC_STA                   *(_IO  uint8 xdata *)0x402e        // RV:  00H      
 #define RTC_EN                                     0x80              //                    rw-- RTC使能
 #define RTC_IF                                     0x40              //                    rw-- RTC中断标志
 #define ISOSCSEL                                   0x20              //                    rw-- 时钟校准外部慢时钟P11选择使能
 #define ISOSCEN                                    0x10              //                    rw-- 内部慢时钟使能
/******************************************************************************///CLOCK_CAL
 #define CAL_CR0                   *(_IO  uint8 xdata *)0x4040        // RV:  00H
 #define CAL_STA                                    0x80              //                    w-- CLOCK_CAL使能, r-- 0-->Done 1-->ING
 #define CAL_CR1                   *(_IO  uint8 xdata *)0x4041        // RV:  00H
/******************************************************************************///SMDU
 #define MUL_LEN                        8                                       // 乘法单元所占字节数
 #define DIV_LEN                        12                                      // 除法单元所占字节数
 #define LPF_LEN                        8                                       // 低通滤波单元所占字节数
 #define SCAT_LEN                       10                                      // Sin/Cos/ATan单元所占字节数
 #define PI_LEN                         16                                      // PI单元所占字节数

 #define SCAT3_BADR                     0x328                                   // SMDU基地址/Sin/Cos/ATan单元3首地址
 #define SCAT2_BADR                     (SCAT3_BADR + SCAT_LEN)                 // Sin/Cos/ATan单元2首地址
 #define SCAT1_BADR                     (SCAT2_BADR + SCAT_LEN)                 // Sin/Cos/ATan单元1首地址
 #define SCAT0_BADR                     (SCAT1_BADR + SCAT_LEN)                 // Sin/Cos/ATan单元0首地址
 #define DIV3_BADR                      (SCAT0_BADR + SCAT_LEN)                 // 除法单元3首地址
 #define DIV2_BADR                      (DIV3_BADR  + DIV_LEN)                  // 除法单元2首地址
 #define MUL3_BADR                      (DIV2_BADR  + DIV_LEN)                  // 乘法单元3首地址
 #define MUL2_BADR                      (MUL3_BADR  + MUL_LEN)                  // 乘法单元2首地址
 #define PI3_BADR                       (MUL2_BADR  + MUL_LEN)                  // PI单元3首地址
 #define PI2_BADR                       (PI3_BADR   + PI_LEN)                   // PI单元2首地址
 #define LPF3_BADR                      (PI2_BADR   + PI_LEN)                   // 低通滤波单元3首地址
 #define LPF2_BADR                      (LPF3_BADR  + LPF_LEN)                  // 低通滤波单元2首地址
 #define DIV1_BADR                      (LPF2_BADR  + LPF_LEN)                  // 除法单元 1首地址
 #define DIV0_BADR                      (DIV1_BADR  + DIV_LEN)                  // 除法单元0首地址
 #define MUL1_BADR                      (DIV0_BADR  + DIV_LEN)                  // 乘法单元1首地址
 #define MUL0_BADR                      (MUL1_BADR  + MUL_LEN)                  // 乘法单元0首地址
 #define PI1_BADR                       (MUL0_BADR  + MUL_LEN)                  // PI单元1首地址
 #define PI0_BADR                       (PI1_BADR   + PI_LEN)                   // PI单元0首地址
 #define LPF1_BADR                      (PI0_BADR   + PI_LEN)                   // 低通滤波单元1首地址
 #define LPF0_BADR                      (LPF1_BADR  + LPF_LEN)                  // 低通滤波单元0首地址

 #define SCAT3_COS                *(_IO uint16 xdata *)(SCAT3_BADR + 0x00)      // rw-- Cos
 #define SCAT3_SIN                *(_IO uint16 xdata *)(SCAT3_BADR + 0x02)      // rw-- Sin
 #define SCAT3_THE                *(_IO uint16 xdata *)(SCAT3_BADR + 0x04)      // rw-- Angle
 #define SCAT3_RES1               *(_IO uint16 xdata *)(SCAT3_BADR + 0x06)      // rw-- Sin/Cos模式下为Cos; ATan模式下为幅值
 #define SCAT3_RES2               *(_IO uint16 xdata *)(SCAT3_BADR + 0x08)      // rw-- Sin/Cos模式下为Sin; ATan模式下为角度

 #define SCAT2_COS                *(_IO uint16 xdata *)(SCAT2_BADR + 0x00)      // rw-- Cos
 #define SCAT2_SIN                *(_IO uint16 xdata *)(SCAT2_BADR + 0x02)      // rw-- Sin
 #define SCAT2_THE                *(_IO uint16 xdata *)(SCAT2_BADR + 0x04)      // rw-- Angle
 #define SCAT2_RES1               *(_IO uint16 xdata *)(SCAT2_BADR + 0x06)      // rw-- Sin/Cos模式下为Cos; ATan模式下为幅值
 #define SCAT2_RES2               *(_IO uint16 xdata *)(SCAT2_BADR + 0x08)      // rw-- Sin/Cos模式下为Sin; ATan模式下为角度

 #define SCAT1_COS                *(_IO uint16 xdata *)(SCAT1_BADR + 0x00)      // rw-- Cos
 #define SCAT1_SIN                *(_IO uint16 xdata *)(SCAT1_BADR + 0x02)      // rw-- Sin
 #define SCAT1_THE                *(_IO uint16 xdata *)(SCAT1_BADR + 0x04)      // rw-- Angle
 #define SCAT1_RES1               *(_IO uint16 xdata *)(SCAT1_BADR + 0x06)      // rw-- Sin/Cos模式下为Cos; ATan模式下为幅值
 #define SCAT1_RES2               *(_IO uint16 xdata *)(SCAT1_BADR + 0x08)      // rw-- Sin/Cos模式下为Sin; ATan模式下为角度

 #define SCAT0_COS                *(_IO uint16 xdata *)(SCAT0_BADR + 0x00)      // rw-- Cos
 #define SCAT0_SIN                *(_IO uint16 xdata *)(SCAT0_BADR + 0x02)      // rw-- Sin
 #define SCAT0_THE                *(_IO uint16 xdata *)(SCAT0_BADR + 0x04)      // rw-- Angle
 #define SCAT0_RES1               *(_IO uint16 xdata *)(SCAT0_BADR + 0x06)      // rw-- Sin/Cos模式下为Cos; ATan模式下为幅值
 #define SCAT0_RES2               *(_IO uint16 xdata *)(SCAT0_BADR + 0x08)      // rw-- Sin/Cos模式下为Sin; ATan模式下为角度

 #define DIV3_DAH                 *(_IO uint16 xdata *)(DIV3_BADR  + 0x00)      // rw-- 被除数高16位
 #define DIV3_DAL                 *(_IO uint16 xdata *)(DIV3_BADR  + 0x02)      // rw-- 被除数低16位
 #define DIV3_DB                  *(_IO uint16 xdata *)(DIV3_BADR  + 0x04)      // rw-- 除数
 #define DIV3_DQH                 *(_IO uint16 xdata *)(DIV3_BADR  + 0x06)      // rw-- 商高16位
 #define DIV3_DQL                 *(_IO uint16 xdata *)(DIV3_BADR  + 0x08)      // rw-- 商低16位
 #define DIV3_DR                  *(_IO uint16 xdata *)(DIV3_BADR  + 0x0a)      // rw-- 余数

 #define DIV2_DAH                 *(_IO uint16 xdata *)(DIV2_BADR  + 0x00)      // rw-- 被除数高16位
 #define DIV2_DAL                 *(_IO uint16 xdata *)(DIV2_BADR  + 0x02)      // rw-- 被除数低16位
 #define DIV2_DB                  *(_IO uint16 xdata *)(DIV2_BADR  + 0x04)      // rw-- 除数
 #define DIV2_DQH                 *(_IO uint16 xdata *)(DIV2_BADR  + 0x06)      // rw-- 商高16位
 #define DIV2_DQL                 *(_IO uint16 xdata *)(DIV2_BADR  + 0x08)      // rw-- 商低16位
 #define DIV2_DR                  *(_IO uint16 xdata *)(DIV2_BADR  + 0x0a)      // rw-- 余数

 #define DIV1_DAH                 *(_IO uint16 xdata *)(DIV1_BADR  + 0x00)      // rw-- 被除数高16位
 #define DIV1_DAL                 *(_IO uint16 xdata *)(DIV1_BADR  + 0x02)      // rw-- 被除数低16位
 #define DIV1_DB                  *(_IO uint16 xdata *)(DIV1_BADR  + 0x04)      // rw-- 除数
 #define DIV1_DQH                 *(_IO uint16 xdata *)(DIV1_BADR  + 0x06)      // rw-- 商高16位
 #define DIV1_DQL                 *(_IO uint16 xdata *)(DIV1_BADR  + 0x08)      // rw-- 商低16位
 #define DIV1_DR                  *(_IO uint16 xdata *)(DIV1_BADR  + 0x0a)      // rw-- 余数

 #define DIV0_DAH                 *(_IO uint16 xdata *)(DIV0_BADR  + 0x00)      // rw-- 被除数高16位
 #define DIV0_DAL                 *(_IO uint16 xdata *)(DIV0_BADR  + 0x02)      // rw-- 被除数低16位
 #define DIV0_DB                  *(_IO uint16 xdata *)(DIV0_BADR  + 0x04)      // rw-- 除数
 #define DIV0_DQH                 *(_IO uint16 xdata *)(DIV0_BADR  + 0x06)      // rw-- 商高16位
 #define DIV0_DQL                 *(_IO uint16 xdata *)(DIV0_BADR  + 0x08)      // rw-- 商低16位
 #define DIV0_DR                  *(_IO uint16 xdata *)(DIV0_BADR  + 0x0a)      // rw-- 余数

 #define MUL3_MA                  *(_IO uint16 xdata *)(MUL3_BADR  + 0x00)      // rw-- 被乘数
 #define MUL3_MB                  *(_IO uint16 xdata *)(MUL3_BADR  + 0x02)      // rw-- 乘数
 #define MUL3_MCH                 *(_IO uint16 xdata *)(MUL3_BADR  + 0x04)      // rw-- 积高16位
 #define MUL3_MCL                 *(_IO uint16 xdata *)(MUL3_BADR  + 0x06)      // rw-- 积低16位

 #define MUL2_MA                  *(_IO uint16 xdata *)(MUL2_BADR  + 0x00)      // rw-- 被乘数
 #define MUL2_MB                  *(_IO uint16 xdata *)(MUL2_BADR  + 0x02)      // rw-- 乘数
 #define MUL2_MCH                 *(_IO uint16 xdata *)(MUL2_BADR  + 0x04)      // rw-- 积高16位
 #define MUL2_MCL                 *(_IO uint16 xdata *)(MUL2_BADR  + 0x06)      // rw-- 积低16位

 #define MUL1_MA                  *(_IO uint16 xdata *)(MUL1_BADR  + 0x00)      // rw-- 被乘数
 #define MUL1_MB                  *(_IO uint16 xdata *)(MUL1_BADR  + 0x02)      // rw-- 乘数
 #define MUL1_MCH                 *(_IO uint16 xdata *)(MUL1_BADR  + 0x04)      // rw-- 积高16位
 #define MUL1_MCL                 *(_IO uint16 xdata *)(MUL1_BADR  + 0x06)      // rw-- 积低16位

 #define MUL0_MA                  *(_IO uint16 xdata *)(MUL0_BADR  + 0x00)      // rw-- 被乘数
 #define MUL0_MB                  *(_IO uint16 xdata *)(MUL0_BADR  + 0x02)      // rw-- 乘数
 #define MUL0_MCH                 *(_IO uint16 xdata *)(MUL0_BADR  + 0x04)      // rw-- 积高16位
 #define MUL0_MCL                 *(_IO uint16 xdata *)(MUL0_BADR  + 0x06)      // rw-- 积低16位

 #define LPF3_K                   *(_IO  int16 xdata *)(LPF3_BADR  + 0x00)      // rw-- 滤波系数[32767, -32768]
 #define LPF3_X                   *(_IO  int16 xdata *)(LPF3_BADR  + 0x02)      // rw-- 滤波输入
 #define LPF3_YH                  *(_IO uint16 xdata *)(LPF3_BADR  + 0x04)      // rw-- 滤波结果高16位
 #define LPF3_YL                  *(_IO uint16 xdata *)(LPF3_BADR  + 0x06)      // rw-- 滤波结果低16位

 #define LPF2_K                   *(_IO  int16 xdata *)(LPF2_BADR  + 0x00)      // rw-- 滤波系数[32767, -32768]
 #define LPF2_X                   *(_IO  int16 xdata *)(LPF2_BADR  + 0x02)      // rw-- 滤波输入
 #define LPF2_YH                  *(_IO uint16 xdata *)(LPF2_BADR  + 0x04)      // rw-- 滤波结果高16位
 #define LPF2_YL                  *(_IO uint16 xdata *)(LPF2_BADR  + 0x06)      // rw-- 滤波结果低16位

 #define LPF1_K                   *(_IO  int16 xdata *)(LPF1_BADR  + 0x00)      // rw-- 滤波系数[32767, -32768]
 #define LPF1_X                   *(_IO  int16 xdata *)(LPF1_BADR  + 0x02)      // rw-- 滤波输入
 #define LPF1_YH                  *(_IO uint16 xdata *)(LPF1_BADR  + 0x04)      // rw-- 滤波结果高16位
 #define LPF1_YL                  *(_IO uint16 xdata *)(LPF1_BADR  + 0x06)      // rw-- 滤波结果低16位

 #define LPF0_K                   *(_IO  int16 xdata *)(LPF0_BADR  + 0x00)      // rw-- 滤波系数[32767, -32768]
 #define LPF0_X                   *(_IO  int16 xdata *)(LPF0_BADR  + 0x02)      // rw-- 滤波输入
 #define LPF0_YH                  *(_IO uint16 xdata *)(LPF0_BADR  + 0x04)      // rw-- 滤波结果高16位
 #define LPF0_YL                  *(_IO uint16 xdata *)(LPF0_BADR  + 0x06)      // rw-- 滤波结果低16位

 #define PI3_KP                   *(_IO  int16 xdata *)(PI3_BADR   + 0x00)      // rw-- Kp系数, Q12格式, 有效范围[32767, 0]
 #define PI3_EK1                  *(_IO  int16 xdata *)(PI3_BADR   + 0x02)      // rw-- 上一次的误差
 #define PI3_EK                   *(_IO  int16 xdata *)(PI3_BADR   + 0x04)      // rw-- 当前的误差
 #define PI3_KI                   *(_IO  int16 xdata *)(PI3_BADR   + 0x06)      // rw-- Ki系数, Q15格式, 有效范围[32767, 0]
 #define PI3_UKH                  *(_IO  int16 xdata *)(PI3_BADR   + 0x08)      // rw-- PI计算结果高16位
 #define PI3_UKL                  *(_IO  int16 xdata *)(PI3_BADR   + 0x0a)      // rw-- PI计算结果低16位
 #define PI3_UKMAX                *(_IO  int16 xdata *)(PI3_BADR   + 0x0c)      // rw-- UK限幅最大值
 #define PI3_UKMIN                *(_IO  int16 xdata *)(PI3_BADR   + 0x0e)      // rw-- UK限幅最小值

 #define PI2_KP                   *(_IO  int16 xdata *)(PI2_BADR   + 0x00)      // rw-- Kp系数, Q12格式, 有效范围[32767, 0]
 #define PI2_EK1                  *(_IO  int16 xdata *)(PI2_BADR   + 0x02)      // rw-- 上一次的误差
 #define PI2_EK                   *(_IO  int16 xdata *)(PI2_BADR   + 0x04)      // rw-- 当前的误差
 #define PI2_KI                   *(_IO  int16 xdata *)(PI2_BADR   + 0x06)      // rw-- Ki系数, Q15格式, 有效范围[32767, 0]
 #define PI2_UKH                  *(_IO  int16 xdata *)(PI2_BADR   + 0x08)      // rw-- PI计算结果高16位
 #define PI2_UKL                  *(_IO  int16 xdata *)(PI2_BADR   + 0x0a)      // rw-- PI计算结果低16位
 #define PI2_UKMAX                *(_IO  int16 xdata *)(PI2_BADR   + 0x0c)      // rw-- UK限幅最大值
 #define PI2_UKMIN                *(_IO  int16 xdata *)(PI2_BADR   + 0x0e)      // rw-- UK限幅最小值

 #define PI1_KP                   *(_IO  int16 xdata *)(PI1_BADR   + 0x00)      // rw-- Kp系数, Q12格式, 有效范围[32767, 0]
 #define PI1_EK1                  *(_IO  int16 xdata *)(PI1_BADR   + 0x02)      // rw-- 上一次的误差
 #define PI1_EK                   *(_IO  int16 xdata *)(PI1_BADR   + 0x04)      // rw-- 当前的误差
 #define PI1_KI                   *(_IO  int16 xdata *)(PI1_BADR   + 0x06)      // rw-- Ki系数, Q15格式, 有效范围[32767, 0]
 #define PI1_UKH                  *(_IO  int16 xdata *)(PI1_BADR   + 0x08)      // rw-- PI计算结果高16位
 #define PI1_UKL                  *(_IO  int16 xdata *)(PI1_BADR   + 0x0a)      // rw-- PI计算结果低16位
 #define PI1_UKMAX                *(_IO  int16 xdata *)(PI1_BADR   + 0x0c)      // rw-- UK限幅最大值
 #define PI1_UKMIN                *(_IO  int16 xdata *)(PI1_BADR   + 0x0e)      // rw-- UK限幅最小值

 #define PI0_KP                   *(_IO  int16 xdata *)(PI0_BADR   + 0x00)      // rw-- Kp系数, Q12格式, 有效范围[32767, 0]
 #define PI0_EK1                  *(_IO  int16 xdata *)(PI0_BADR   + 0x02)      // rw-- 上一次的误差
 #define PI0_EK                   *(_IO  int16 xdata *)(PI0_BADR   + 0x04)      // rw-- 当前的误差
 #define PI0_KI                   *(_IO  int16 xdata *)(PI0_BADR   + 0x06)      // rw-- Ki系数, Q15格式, 有效范围[32767, 0]
 #define PI0_UKH                  *(_IO  int16 xdata *)(PI0_BADR   + 0x08)      // rw-- PI计算结果高16位
 #define PI0_UKL                  *(_IO  int16 xdata *)(PI0_BADR   + 0x0a)      // rw-- PI计算结果低16位
 #define PI0_UKMAX                *(_IO  int16 xdata *)(PI0_BADR   + 0x0c)      // rw-- UK限幅最大值
 #define PI0_UKMIN                *(_IO  int16 xdata *)(PI0_BADR   + 0x0e)      // rw-- UK限幅最小值

#endif
