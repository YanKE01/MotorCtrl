;/**************************************************************************//**
; * @file     startup_LCM32F0xx.s
; * @brief    CMSIS Core Device Startup File for
; *           ARMCM0 Device Series
; * @version  V5.00
; * @date     
; ******************************************************************************/
;/*
; * Copyright .
; *
; * SPDX-License-Identifier: Apache-2.0
; *
; * Licensed under the Apache License, Version 2.0 (the License); you may
; * not use this file except in compliance with the License.
; * You may obtain a copy of the License at
; *
; * www.apache.org/licenses/LICENSE-2.0
; *
; * Unless required by applicable law or agreed to in writing, software
; * distributed under the License is distributed on an AS IS BASIS, WITHOUT
; * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
; * See the License for the specific language governing permissions and
; * limitations under the License.
; */

;/*
;//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
;*/
;*/@author 
;*/@ref
; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>
;一般而言标签代表一个地址，变量的地址，函数的地址，或者代码段(section)的地址，这里的地址一般为起始地址,



Stack_Size      EQU     0x00000400                        ;表示想要定义stack的大小为1024 byte （1KB），但本句话并不执行分配操作，相当于C宏。// (R13)SP=0x20000000 + Stack_Size; 向下增长的栈
                                                                                                                                             ; (R13)SP=0x20000800 + Stack_Size; 向下增长的栈
                AREA    STACK, NOINIT, READWRITE, ALIGN=3 ;定义代码段属性，对齐方式
Stack_Mem       SPACE   Stack_Size                        ;space 指令用于分配多少字节的空间，并初始化为0（两个作用）；本句话表示从stace_mem表示的起始地址分配连续的大小为1KB空间备用并初始化为0
__initial_sp                                              ;栈顶指针


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000800                       ;表示想要定义heap的大小为3072 byte（3KB），但本句话并不执行分配操作。

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3 ;指定该代码段的属性和对齐方式
__heap_base                                              ;堆的起始地址
Heap_Mem        SPACE   Heap_Size                        ;执行空间分配任务（备用），并初始化为0，起始地址为Heap_Mem定义的地址
__heap_limit                                             ;堆的边界


                PRESERVE8                               ;The PRESERVE8 directive specifies that the current file preserves eight-byte alignment of the stack.
                                                        ;It sets the PRES8 build attribute to inform the linker.
                                                        
                THUMB                                   ;This option instructs the assembler to interpret instructions as Thumb instructions, using the UAL syntax. 
                                                        ;This is equivalent to a THUMB directive at the start of the source file.


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY          ;reset 是段名字，DATA指明本段是数据，而不数指令，readonly是访问权限
                EXPORT  __Vectors                      ;导出一个外部标号，用于在C语言中调用
                EXPORT  __Vectors_End                  ;导出标号 __Vector_End
                EXPORT  __Vectors_Size                 ;导出标号 __Vector_Size

__Vectors       DCD     __initial_sp                ; Top of Stack     ;DCD是一个伪指令，告诉编译器怎么做，但本身并不编译成机器码，DCD分配word存储空间  //MSP
                DCD     Reset_Handler               ; Reset Handler    ;复位向量
                DCD     NMI_Handler                 ; NMI Handler      ;其他中断向量表
                DCD     HardFault_Handler           ; Hard Fault Handler
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     SVC_Handler                 ; SVCall Handler
                DCD     0                           ; Reserved
                DCD     0                           ; Reserved
                DCD     PendSV_Handler              ; PendSV Handler
                DCD     SysTick_Handler             ; SysTick Handler

                ; External Interrupts               ;外设中断
                DCD     WWDG_Handler                ; 00 : WWDG                 Handler
				DCD     LVD_Handler                 ; 01 : LVD                  Handler
                DCD     WT_Handler                  ; 02 : WT                   Handler
                DCD     EFLS_Handler                ; 03 : EFLS                 Handler
                DCD     CHIPCTRL_Handler            ; 04 : CHIPCTRL             Handler
                DCD     EXTI0_1_Handler             ; 05 : EXTI0_1              Handler
                DCD     EXTI2_3_Handler             ; 06 : EXTI2_3              Handler
                DCD     EXTI4_15_Handler            ; 07 : EXTI4_15             Handler
                DCD     LCD_ACMP0_2_Handler         ; 08 : LCD_ACMP0_2          Handler
                DCD     DMAC_CH0_Handler            ; 09 : DMAC_CH0             Handler
                DCD     DMAC_CH1_2_Handler          ; 10 : DMAC_CH1_2           Handler
                DCD     DMAC_CH3_5_Handler          ; 11 : DMAC_CH3_5           Handler
                DCD     ADC_Handler                 ; 12 : ADC                  Handler
                DCD     TIM1_NON_CC_Handler         ; 13 : TIM1_NON_CC          Handler
                DCD     TIM1_CC_Handler             ; 14 : TIM1_CC              Handler
                DCD     TIM2_ACMP3_5_PLC_ZC_Handler ; 15 : TIM2_ACMP3_5_PLC_ZC  Handler
                DCD     TIM3_Handler                ; 16 : TIM3                 Handler
                DCD     TIM6_DAC0_2_Handler         ; 17 : TIM6_DAC0_2          Handler
                DCD     TIM7_DAC3_5_PLC_Handler     ; 18 : TIM7_DAC3_5_PLC      Handler
                DCD     TIM14_Handler               ; 19 : TIM14                Handler
                DCD     TIM15_Handler               ; 20 : TIM15                Handler
                DCD     TIM16_Handler               ; 21 : TIM16                Handler
                DCD     TIM17_Handler               ; 22 : TIM17                Handler
                DCD     I2C0_Handler                ; 23 : I2C0                 Handler 
                DCD     I2C1RVE_Handler             ; 24 : I2C1rve              Handler					
                DCD     SSP0_Handler                ; 25 : SSP0                 Handler 
                DCD     SSP2_Handler                ; 26 : ssp2                 Handler					
                DCD     UART0_Handler               ; 27 : UART0                Handler
                DCD     UART1_Handler               ; 28 : UART1                Handler
                DCD     UART2_5_Handler             ; 29 : UART2_5              Handler
                DCD     CAN_Handler                 ; 30 : CAN                  Handler
                DCD     DIV_Handler                 ; 31 : DIV                  Handler

__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors   ;计算中断向量表空间大小

                AREA    |.text|, CODE, READONLY     ;规定段名为*.text的段空间为代码段，用双|包起来是为了防止命名以数字开头，访问权限为RO


; Reset Handler

Reset_Handler   PROC                                ;PROC等同于FUNCTION，用来指明一个函数的开始
				EXPORT  Reset_Handler      [WEAK]   ;weak表明如果外部函数想要覆写这个函数，这里表示同意覆写；这句话的含义是说明Reset_Handler的函数属性为允许被重写的全局函数；
                IMPORT  SystemInit                      ;IMPORT表示.将要.引用一个外部函数，一般来说是在外部C文件中定义了的函数
                IMPORT  __main                          ;引入__main 函数（找不到的，因为这是编译工具链自己产生的），该函数不是C语言中的main()函数，但该函数会在执行过程中跳到mian();
                LDR     R0, =SystemInit                 
                                                        ;LDR伪指令，将systeminit函数地址的地址本身加载到R0寄存器。会被替换成MOV R0, #SystemInit
                BLX     R0                              ;跳转指令，在跳转前先保存跳转前下一条要执行的指令到LR，然后跳转到 systeminit 函数
                LDR     R0, =__main                     ;LDR伪指令，将__main 函数地址加载到R0寄存器
                BX      R0                              ;跳转指令，跳转到__main 函数；（严格地讲这里的__main是先复制rom里的rw-data到ram后，再将PC定位到c中main函数指针）
                ENDP                                    ;定义一个函数的结束，和ENDFUNC作用相同


; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC                                ;定义函数的开始
                EXPORT  NMI_Handler                 [WEAK];EXPORT导出给C语言调用
                B       .                           ;B. 表示条转到当前指令，既什么也不执行
                ENDP
HardFault_Handler  PROC
                EXPORT  HardFault_Handler           [WEAK]
                BX      LR
				ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler                 [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler              [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler             [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT  WWDG_Handler                [WEAK]
				EXPORT  LVD_Handler                 [WEAK]
                EXPORT  WT_Handler                  [WEAK]
                EXPORT  EFLS_Handler                [WEAK]
                EXPORT  CHIPCTRL_Handler            [WEAK]
                EXPORT  EXTI0_1_Handler             [WEAK]
                EXPORT  EXTI2_3_Handler             [WEAK]
                EXPORT  EXTI4_15_Handler            [WEAK]
                EXPORT  LCD_ACMP0_2_Handler         [WEAK]
                EXPORT  DMAC_CH0_Handler            [WEAK]
                EXPORT  DMAC_CH1_2_Handler          [WEAK]
                EXPORT  DMAC_CH3_5_Handler          [WEAK]
                EXPORT  ADC_Handler                 [WEAK]
                EXPORT  TIM1_NON_CC_Handler         [WEAK]
                EXPORT  TIM1_CC_Handler             [WEAK]
                EXPORT  TIM2_ACMP3_5_PLC_ZC_Handler [WEAK]
                EXPORT  TIM3_Handler                [WEAK]
                EXPORT  TIM6_DAC0_2_Handler         [WEAK]
                EXPORT  TIM7_DAC3_5_PLC_Handler     [WEAK]
                EXPORT  TIM14_Handler               [WEAK]
                EXPORT  TIM15_Handler               [WEAK]
                EXPORT  TIM16_Handler               [WEAK]
                EXPORT  TIM17_Handler               [WEAK]
                EXPORT  I2C0_Handler                [WEAK]
				EXPORT  I2C1RVE_Handler             [WEAK]
                EXPORT  SSP0_Handler                [WEAK]
				EXPORT  SSP2_Handler                [WEAK]
                EXPORT  UART0_Handler               [WEAK]
                EXPORT  UART1_Handler               [WEAK]
                EXPORT  UART2_5_Handler             [WEAK]
                EXPORT  CAN_Handler                 [WEAK]
                EXPORT  DIV_Handler                 [WEAK]
                

WWDG_Handler
LVD_Handler
WT_Handler
EFLS_Handler
CHIPCTRL_Handler
EXTI0_1_Handler
EXTI2_3_Handler
EXTI4_15_Handler
LCD_ACMP0_2_Handler
DMAC_CH0_Handler
DMAC_CH1_2_Handler
DMAC_CH3_5_Handler
ADC_Handler
TIM1_NON_CC_Handler
TIM1_CC_Handler
TIM2_ACMP3_5_PLC_ZC_Handler
TIM3_Handler
TIM6_DAC0_2_Handler
TIM7_DAC3_5_PLC_Handler
TIM14_Handler
TIM15_Handler
TIM16_Handler
TIM17_Handler
I2C0_Handler
I2C1RVE_Handler
SSP0_Handler
SSP2_Handler
UART0_Handler
UART1_Handler
UART2_5_Handler
CAN_Handler
DIV_Handler
                B       .

                ENDP


                ALIGN


; User Initial Stack & Heap

                IF      :DEF:__MICROLIB

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap

__user_initial_stackheap PROC
                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR
                ENDP

                ALIGN

                ENDIF


                END

	ALIGN
    EXPORT  OS_CPU_SR_Save                                      ; Functions declared in this file
    EXPORT  OS_CPU_SR_Restore





;One memory region is for the stack and the other is for the heap. The size of the heap region can be zero. The stack region can be in allocated memory or inherited from the execution environment.
;To use the two-region model rather than the default single-region model, use either:
;IMPORT __use_two_region_memory from assembly language
;#pragma import(__use_two_region_memory) from C.



















