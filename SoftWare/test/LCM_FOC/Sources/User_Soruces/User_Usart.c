#define EXPORT_USER_USART_H_
	#include "User_Usart.h"
#undef EXPORT_USER_USART_H_

void UU_vUsartDataInit(UGT_S_USARTDATA_STRU *v)
{
	v->u8UartMode=0;
	v->u8UartRecIndex=0;
	v->u8UartRecCountNum=0;
	v->s16UartTargetValue=0;
	v->sUsartEvent.All=0;
}


void UU_vSendDataDMA(DMA_Channel_TypeDef *DMAy_Channelx, uint32_t arr, uint16_t size)
{
	if(DMA_GetFlagStatus(DMA1_FLAG_TC0) == SET)
	{
		DMA_Cmd(DMAy_Channelx, DISABLE);
		DMAy_Channelx->SAR = arr;
		DMA_SetCurrDataCounter(DMAy_Channelx, size);
		DMA_ClearITPendingBit(DMA1_FLAG_TC0);
		DMA_Cmd(DMAy_Channelx ,ENABLE);
	}
	
	//while (DMA_GetFlagStatus(DMA1_FLAG_TC0) != SET);
}

u8 UU_u8UARTRecCheck(void)
{
	u8 temp = 0;
	u16 i = 0;
	u8 res = 0;

	for(i = 0; i < UG_sUsartData.u8UartRecCountNum - 1; i++)
	{
		temp += UG_sUsartData.u8ReceiveData[i];
	}
	if(UG_sUsartData.u8ReceiveData[i] == temp)res=1;
	else res=0;

	return res;
}

void UU_vUartDataFlashWrite(uint32_t start_address, uint8_t write_mode)
{
	u32 i;
	u16 half_word_data;
	u32 temp_prog_addr, prog_addr;	
	u16 half_word_length;
	
	prog_addr = start_address;
	temp_prog_addr = prog_addr;
	
	//解锁
	FLASH_Unlock();
	
	//擦除
	UG_sUsartData.sFlashWriteStatus = FLASH_ErasePage(prog_addr);


	//写数据
	half_word_length=(UPDS_UART_REC_COMMAND1_LENGTH>>1)-1;
	for(i = 0; i < half_word_length; i++)
	{
		half_word_data = ((u16)UG_sUsartData.u8ReceiveData[2*i+2] << 8) | UG_sUsartData.u8ReceiveData[2*i+1];//i;//
		UG_sUsartData.sFlashWriteStatus = FLASH_ProgramHalfWord(prog_addr, half_word_data);
		while(UG_sUsartData.sFlashWriteStatus!=FLASH_COMPLETE);
		temp_prog_addr = prog_addr;
		if((i+1)==half_word_length)
		{
			UG_sUsartData.sUsartEvent.Bits.ReceiceFinish = 0;
		}
		else
		{
			prog_addr += 0x02;
		}
	};
	//上锁
	FLASH_Lock();
}
void UU_vUartData1Prepare(void)
{
	u8 sum = 0;
	u8 i;
	UU_vScopeDataSeleect(&UG_sUsartData.s16Scope[0],UG_sUsartData.u8ScopeSelect[0]);
	UU_vScopeDataSeleect(&UG_sUsartData.s16Scope[1],UG_sUsartData.u8ScopeSelect[1]);
	UU_vScopeDataSeleect(&UG_sUsartData.s16Scope[2],UG_sUsartData.u8ScopeSelect[2]);
	UU_vScopeDataSeleect(&UG_sUsartData.s16Scope[3],UG_sUsartData.u8ScopeSelect[3]);	
	UG_sUsartData.u8SendData1[0] = 0x33;
	UG_sUsartData.u8SendData1[1] = (UG_sUsartData.s16Scope[0])&0x00FF;
	UG_sUsartData.u8SendData1[2] = (UG_sUsartData.s16Scope[0] >>8)&0x00FF;
	UG_sUsartData.u8SendData1[3] = (UG_sUsartData.s16Scope[1])&0x00FF;
	UG_sUsartData.u8SendData1[4] = (UG_sUsartData.s16Scope[1] >>8)&0x00FF;
	UG_sUsartData.u8SendData1[5] = (UG_sUsartData.s16Scope[2])&0x00FF;
	UG_sUsartData.u8SendData1[6] = (UG_sUsartData.s16Scope[2] >>8)&0x00FF;
	UG_sUsartData.u8SendData1[7] = (UG_sUsartData.s16Scope[3])&0x00FF;
	UG_sUsartData.u8SendData1[8] = (UG_sUsartData.s16Scope[3]>>8)&0x00FF;
	UG_sUsartData.u8SendData1[9] = (UG_sSysStateErr.uSystemError.All) & 0x00FF;
	
	for(i=0;i<=9;i++)
	{
		sum += UG_sUsartData.u8SendData1[i];	
	}
	UG_sUsartData.u8SendData1[10] = sum;
}

void UU_vUartData2Prepare(void)
{
	u8 sum = 0;
	u8 i;
	
	UG_sUsartData.u8SendData2[0] = 0x44;
	UG_sUsartData.u8SendData2[1] = UG_sUsartData.sFlashReadDataUpdata.u16DCBusVoltage&0x00FF;
	UG_sUsartData.u8SendData2[2] = (UG_sUsartData.sFlashReadDataUpdata.u16DCBusVoltage >>8)&0x00FF;
	UG_sUsartData.u8SendData2[3] = UG_sUsartData.sFlashReadDataUpdata.u16PhaseCurrentMag & 0x00FF;
	UG_sUsartData.u8SendData2[4] = (UG_sUsartData.sFlashReadDataUpdata.u16PhaseCurrentMag >>8)&0x00FF;
	UG_sUsartData.u8SendData2[5] = UG_sUsartData.sFlashReadDataUpdata.s16PowerIn & 0x00FF;
	UG_sUsartData.u8SendData2[6] = (UG_sUsartData.sFlashReadDataUpdata.s16PowerIn >>8)&0x00FF;
	UG_sUsartData.u8SendData2[7] = (UG_sUsartData.sFlashReadDataUpdata.s16SpdRpm)&0x00FF;
	UG_sUsartData.u8SendData2[8] = (UG_sUsartData.sFlashReadDataUpdata.s16SpdRpm >>8)&0x00FF;
	UG_sUsartData.u8SendData2[9] = UG_sUsartData.sFlashReadDataUpdata.u8Temperature & 0x00FF;	
	for(i=0;i<=9;i++)
	{
		sum += UG_sUsartData.u8SendData2[i];	
	}
	UG_sUsartData.u8SendData2[10] = sum;
}


void UU_vFlashRead(u32 start_address, u32 halfwordlength)
{
	u32 index=0;
	FLASH_Unlock();
	for (index = 0; index < halfwordlength; index++)
	{
		UG_sUsartData.u16FlashReadData[index] = *(volatile u16 *)(start_address+(index<<1));
	}
	FLASH_Lock();
	
}

void UU_vUartReceDataRead(UGT_S_USARTDATA_STRU *v)
{
	u32 i=0;

	for(i = 0; i < UPDS_UART_REC_COMMAND1_HALFWOED_LENGTH; i++)
	{
		v->u16FlashReadData[i] = ((u16)v->u8ReceiveData[2*i+2] << 8) | v->u8ReceiveData[2*i+1];
	}
}



void UU_vScopeDataSeleect(s16 *s16ScopeData, u8 u8Select)
{
	switch (u8Select)
	{
		case 0: *s16ScopeData=UG_sCurrentAll.sCurrentAbc.s16As+0x7FFF; break;
		case 1: *s16ScopeData=UG_sCurrentAll.sCurrentAbc.s16Bs+0x7FFF; break;
		case 2: *s16ScopeData=UG_sCurrentAll.sCurrentAbc.s16Cs+0x7FFF; break;
//		case 0: *s16ScopeData=UG_sVoltageAll.sVoltageAbc.s16UAsMeas; break;
//		case 1: *s16ScopeData=UG_sVoltageAll.sVoltageAbc.s16UBsMeas; break;
//		case 2: *s16ScopeData=UG_sVoltageAll.sVoltageAbc.s16UCsMeas; break;
		case 3: *s16ScopeData=UG_sCurrentAll.sCurrentAlphaBeta.s16Alpha+0x7FFF;break;
		case 4: *s16ScopeData=UG_sCurrentAll.sCurrentAlphaBeta.s16Beta+0x7FFF;break;
//		case 3: *s16ScopeData=UG_sVoltageAll.sVoltageAlphaBetaCalc.s16Alpha+0x7FFF;break;
//		case 4: *s16ScopeData=(UG_sVoltageAll.sVoltageAlphaBetaMeas.s16Alpha<<3)+0x7FFF;break;
//		case 5: *s16ScopeData=UG_sVoltageAll.sVoltageAlphaBetaCalc.s16Beta+0x7FFF;break;
//		case 6: *s16ScopeData=(UG_sVoltageAll.sVoltageAlphaBetaMeas.s16Beta<<3)+0x7FFF;break;
		case 5: *s16ScopeData=UG_sCurrentAll.sCurrentDqUse.s16Dr+0x7FFF;break;
		case 6: *s16ScopeData=UG_sCurrentAll.sCurrentDqUse.s16Qr+0x7FFF;break;
		case 7: *s16ScopeData=(UG_sSystemControllers.sCommandAll.s32IqCommand>>9)+0x7FFF;break;
		case 8: *s16ScopeData=(UG_sSystemControllers.sCommandAll.s32SpdCommand>>9)+0x7FFF;break;
		case 9: *s16ScopeData=(UG_sSystemControllers.sCommandAll.s32SpdUse>>9)+0x7FFF;break;
		case 10: *s16ScopeData=(MDS_sCP.PI_CP.s32Ref>>9)+0x7FFF;break;
		case 11: *s16ScopeData=(MDS_sCP.PI_CP.s32Fbk>>9)+0x7FFF;break;
		case 12: *s16ScopeData=UG_sPositionAll.u16PosUse;break;
		case 13: *s16ScopeData=UG_sUsartData.sFlashReadDataUpdata.s16SpdRpm;break;
		case 14: *s16ScopeData=UG_sUsartData.sFlashReadDataUpdata.u16DCBusVoltage;break;
		case 15: *s16ScopeData=(UG_sADSampleAll.s16IdcLPFTem+0x7FFF); break;
		default: ;break;
	}

}


