#ifndef SOURCE_USER_USART_H_
#define SOURCE_USER_USART_H_

#include "lcm32f037_lib.h"
#include "UserIncludes.h"

#if defined(EXPORT_USER_USART_H_)
  #define EXTERN
#else
  #define EXTERN extern
#endif
	
#define UU_SEND_FINISH 			(u16)0x0002	
#define UU_RECEIVE_FINISH 	(u16)0x0004	

#define FLASH_SETTING 			(1)
	
	
//#define PAGE_SIZE (0x200)	 /* 512byte */
#define WORLD_WRITE 	0 //
#define HALF_WRITE 		1
#define FLASH_START_PAGE_ADDRESS (0x08007F00)  //512 Bytes, Page: 62
#define UU_FLASH_READDATA_LENGTH	(35)

#define UART_SET 		(1)
#define UART_START  (2)
#define UART_STOP 	(3)

EXTERN void UU_vUsartDataInit(UGT_S_USARTDATA_STRU *v);	
EXTERN void UU_vSendDataDMA(DMA_Channel_TypeDef *DMAy_Channelx, uint32_t arr, uint16_t size);
EXTERN void UU_vUartData1Prepare(void);
EXTERN void UU_vUartData2Prepare(void);
EXTERN u8 	UU_u8UARTRecCheck(void);
EXTERN void MAINFLASH_READ(uint32_t start_address, uint32_t range);
EXTERN void UU_vUartDataFlashWrite(uint32_t start_address, uint8_t write_mode);
EXTERN void UU_vFlashRead(u32 start_address, u32 halfwordlength);
EXTERN void UU_vScopeDataSeleect(s16 *s16ScopeData, u8 u8Select);
EXTERN void UU_vUartReceDataRead(UGT_S_USARTDATA_STRU *v);
	
#undef EXTERN
#endif
	