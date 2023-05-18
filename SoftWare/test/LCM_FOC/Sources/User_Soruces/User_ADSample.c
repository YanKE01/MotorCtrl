#define EXPORT_USER_ADSAMPLE_H_
	#include "User_ADSample.h"
#undef EXPORT_USER_ADSAMPLE_H_


u8 UA_u8CurrSampleOffest(UGT_S_ADSAMPLEALL_STRU *v, UGT_S_CURRABC_STRU *Curr, UGT_S_VOLTABC_STRU *Volt)
{
	static u16 ls_u16CurrSampleOffestIndex = 0;
	u16 u16IAs,u16IBs,u16ICs,u16Idc,u16IdcLPF,u16VSP;
	u16 u16UAn,u16UBn,u16UCn,u16Udc;
	u8 u8Finish = FALSE;

	if(UG_sSysStateErr.uControlReg.Bits.MotorDirection == UPDS_POSITIVE_DIRECTION)
	{
		u16IAs = (UPDS_IA_ADC)&0x0FFF;
		u16IBs = (UPDS_IB_ADC)&0x0FFF;
		u16Idc = (UPDS_IDC_ADC)&0x0FFF;
		u16IdcLPF = (UPDS_IDC_ADC)&0x0FFF;
		ls_u16CurrSampleOffestIndex++;

		if (ls_u16CurrSampleOffestIndex < UA_AD_OFFSET_SAMP_TIME_NUM)
		{
			v->u16IAsOffest = v->u16IAsOffest + ((((s32)(u16IAs) - v->u16IAsOffest)*UA_OFFEST_LPF_GAIN_IQ15)>>15);
			v->u16IBsOffest = v->u16IBsOffest + ((((s32)(u16IBs) - v->u16IBsOffest)*UA_OFFEST_LPF_GAIN_IQ15)>>15);
			v->u16IdcOffest = v->u16IdcOffest + ((((s32)(u16Idc) - v->u16IdcOffest)*UA_OFFEST_LPF_GAIN_IQ15)>>15);	
			v->u16IdcLPFOffest = v->u16IdcLPFOffest + ((((s32)(u16IdcLPF) - v->u16IdcLPFOffest)*UA_OFFEST_LPF_GAIN_IQ15)>>15);			
		}
		else
		{
			Curr->u16AsOffest = v->u16IAsOffest;
			Curr->u16BsOffest = v->u16IBsOffest;	
			Curr->u16IdcOffest = v->u16IdcOffest;	
			Curr->u16IdcLPFOffest = v->u16IdcLPFOffest;				
			
			ls_u16CurrSampleOffestIndex = 0;
			u8Finish = TRUE;
		}
	}
	else if(UG_sSysStateErr.uControlReg.Bits.MotorDirection == UPDS_NEGATIVE_DIRECTION)
	{
		u16ICs = (UPDS_IA_ADC)&0x0FFF;
		u16IBs = (UPDS_IB_ADC)&0x0FFF;	
		u16Idc = (UPDS_IDC_ADC)&0x0FFF;
		u16IdcLPF = (UPDS_IDC_ADC)&0x0FFF;
		ls_u16CurrSampleOffestIndex++;

		if (ls_u16CurrSampleOffestIndex < UA_AD_OFFSET_SAMP_TIME_NUM)
		{
			v->u16ICsOffest = v->u16ICsOffest + ((((s32)(u16ICs) - v->u16ICsOffest)*UA_OFFEST_LPF_GAIN_IQ15)>>15);
			v->u16IBsOffest = v->u16IBsOffest + ((((s32)(u16IBs) - v->u16IBsOffest)*UA_OFFEST_LPF_GAIN_IQ15)>>15);
			v->u16IdcOffest = v->u16IdcOffest + ((((s32)(u16Idc) - v->u16IdcOffest)*UA_OFFEST_LPF_GAIN_IQ15)>>15);
			v->u16IdcLPFOffest = v->u16IdcLPFOffest + ((((s32)(u16IdcLPF) - v->u16IdcLPFOffest)*UA_OFFEST_LPF_GAIN_IQ15)>>15);				
		}
		else
		{
			Curr->u16CsOffest = v->u16ICsOffest;
			Curr->u16BsOffest = v->u16IBsOffest;	
			Curr->u16IdcOffest = v->u16IdcOffest;
			Curr->u16IdcLPFOffest = v->u16IdcLPFOffest;	
			
			ls_u16CurrSampleOffestIndex = 0;
			u8Finish = TRUE;
		}
		}
	return (u8Finish);
}


void UA_vADSampleAll(UGT_S_ADSAMPLEALL_STRU *v)
{
	s32 s32IAs,s32IBs,s32ICs,s32Idc,s32IdcLPF;
	s32 s32Temp;
	s16 s16temp;

	if(UG_sSysStateErr.uControlReg.Bits.MotorDirection == UPDS_POSITIVE_DIRECTION)
	{		
		s32IAs = -(((s32)(UPDS_IA_ADC) - v->u16IAsOffest)<<4);			//IQ15
		s32IBs = -(((s32)(UPDS_IB_ADC) - v->u16IBsOffest)<<4);
		s32ICs = -s32IAs - s32IBs;
		s32Idc = (((s32)(UPDS_IDC_ADC) - v->u16IdcOffest)<<1);
		s32IdcLPF = (((s32)(UPDS_IDC_LPF_ADC) - v->u16IdcLPFOffest)<<1);
		#if(UPDS_UABC_MEAS_SEL == UPDS_UABC_MEAS_ENABLE)	
			v->s16UAnTem = UPDS_VAN_MEAS_ADC;
			v->s16UBnTem = UPDS_VBN_MEAS_ADC;
			v->s16UCnTem = UPDS_VCN_MEAS_ADC;
		#endif		
	}
	else if(UG_sSysStateErr.uControlReg.Bits.MotorDirection == UPDS_NEGATIVE_DIRECTION)
	{
		s32ICs = -(((s32)(UPDS_IA_ADC) - v->u16ICsOffest)<<4);			//IQ15
		s32IBs = -(((s32)(UPDS_IB_ADC) - v->u16IBsOffest)<<4);
		s32IAs = -s32ICs - s32IBs;
		s32Idc = (((s32)(UPDS_IDC_ADC) - v->u16IdcOffest)<<1);
		s32IdcLPF = (((s32)(UPDS_IDC_LPF_ADC) - v->u16IdcLPFOffest)<<1);
		#if(UPDS_UABC_MEAS_SEL == UPDS_UABC_MEAS_ENABLE)	
			v->s16UCnTem = UPDS_VAN_MEAS_ADC;
			v->s16UBnTem = UPDS_VBN_MEAS_ADC;
			v->s16UAnTem = UPDS_VCN_MEAS_ADC;
		#endif		
	}

	if(s32IAs > UA_IQ15_MAX) 				v->s16IAsTem = UA_IQ15_MAX;
	else if (s32IAs < UA_IQ15_MIN) 	v->s16IAsTem = UA_IQ15_MIN;
	else 														v->s16IAsTem = s32IAs;

	if(s32IBs > UA_IQ15_MAX) 				v->s16IBsTem = UA_IQ15_MAX;
	else if (s32IBs < UA_IQ15_MIN) 	v->s16IBsTem = UA_IQ15_MIN;
	else 														v->s16IBsTem = s32IBs;
	
	if(s32ICs > UA_IQ15_MAX) 				v->s16ICsTem = UA_IQ15_MAX;
	else if (s32ICs < UA_IQ15_MIN) 	v->s16ICsTem = UA_IQ15_MIN;
	else 														v->s16ICsTem = s32ICs;

	if(s32Idc > UA_IQ15_MAX) 				v->s16IdcTem = UA_IQ15_MAX;
	else if (s32Idc < UA_IQ15_MIN) 	v->s16IdcTem = UA_IQ15_MIN;
	else 														v->s16IdcTem = s32Idc;
	
	if(s32IdcLPF > UA_IQ15_MAX) 				v->s16IdcLPFTem = UA_IQ15_MAX;
	else if (s32IdcLPF < UA_IQ15_MIN) 	v->s16IdcLPFTem = UA_IQ15_MIN;
	else 																v->s16IdcLPFTem = s32IdcLPF;
	
#if (UPDS_CHIP_TYPE_SEL	== UPDS_LCM037_24PIN)	
	v->u16UdcTem = (UPDS_UDC_ADC);
#elif (UPDS_CHIP_TYPE_SEL	== UPDS_LCM037_32PIN)
	v->u16UdcTem = (UPDS_UDC_ADC);
#endif	

	v->s16IGBTTemp = (UPDS_MOS_TEMP_ADC<<3);
	v->s16IGBTTempLPF += ((v->s16IGBTTemp - v->s16IGBTTempLPF)>>5);


	v->s16VSPTem = ((UPDS_VSP_ADC) << 3);//s32Temp;//((ADCConvertedRawData[5]) << 3); //
	v->s16VSPLPF = v->s16VSPLPF + (((s32)v->s16VSPTem - v->s16VSPLPF)>>4); //_IQ15
//	v->s16VSPLPF = 0x7FFF;

}

void UA_vIABCConstruct(UGT_S_ADSAMPLEALL_STRU *v, UGT_S_CURRABC_STRU *Curr)
{

			Curr->s16As = v->s16IAsTem;
			Curr->s16Bs = v->s16IBsTem;
			Curr->s16Cs = v->s16ICsTem;	
//	s32 ls_tem = 0;
//	switch (Curr->u16SampleChooseNum)
//	{
//		case UA_SAMPLE_A_B_C:
//			Curr->s16As = v->s16IAsTem;
//			Curr->s16Bs = v->s16IBsTem;
//			Curr->s16Cs = v->s16ICsTem;
//			break;
//		
//		case UA_SAMPLE_A_B_NC:
//			Curr->s16As = v->s16IAsTem;
//			Curr->s16Bs = v->s16IBsTem;
//			ls_tem =-(s32)(Curr->s16As) - Curr->s16Bs;
//			if(ls_tem > UA_IQ15_MAX) ls_tem = UA_IQ15_MAX;
//			else if (ls_tem < UA_IQ15_MIN) ls_tem = UA_IQ15_MIN;
//			Curr->s16Cs = ls_tem;
//			break;
//		
//		case UA_SAMPLE_A_NB_C:
//			Curr->s16As = v->s16IAsTem;
//			Curr->s16Cs = v->s16ICsTem;
//			ls_tem =-(s32)(Curr->s16As) - Curr->s16Cs;
//			if(ls_tem > UA_IQ15_MAX) ls_tem = UA_IQ15_MAX;
//			else if (ls_tem < UA_IQ15_MIN) ls_tem = UA_IQ15_MIN;
//			Curr->s16Bs = ls_tem;
//			break;
//		
//		case UA_SAMPLE_NA_B_C:
//			Curr->s16Bs = v->s16IBsTem;
//			Curr->s16Cs = v->s16ICsTem;
//			ls_tem =-(s32)(Curr->s16Bs) - Curr->s16Cs;
//			if(ls_tem > UA_IQ15_MAX) ls_tem = UA_IQ15_MAX;
//			else if (ls_tem < UA_IQ15_MIN) ls_tem = UA_IQ15_MIN;
//			Curr->s16As = ls_tem;
//			break;
//		
//		case UA_SAMPLE_A_NB_NC:
//			Curr->s16As = v->s16IAsTem;
//			Curr->s16Bs = Curr->s16Bs;
//			Curr->s16Cs = Curr->s16Cs;
//			break;
//		
//		case UA_SAMPLE_NA_B_NC:
//			Curr->s16Bs = v->s16IBsTem;
//			Curr->s16As = Curr->s16As;
//			Curr->s16Cs = Curr->s16Cs;
//			break;
//		
//		case UA_SAMPLE_NA_NB_C:
//			Curr->s16Cs = v->s16ICsTem;
//			Curr->s16As = Curr->s16As;
//			Curr->s16Bs = Curr->s16Bs;
//			break;

//		case UA_SAMPLE_NA_NB_NC:
//			Curr->s16As = Curr->s16As;
//			Curr->s16Bs = Curr->s16Bs;
//			Curr->s16Cs = Curr->s16Cs;
//			break;
//		
//		default:
//			Curr->u16SampleErr ++;
//			break;		
//	}
	Curr->s32IAsBsCsSum = (s32)(Curr->s16As) + (s32)(Curr->s16Bs) + (s32)(Curr->s16Cs);
}

void UA_vVoltageConstruct(UGT_S_ADSAMPLEALL_STRU *v, UGT_S_VOLTABC_STRU *Volt)
{
	static s32 ls_UdcMeasLpf = 0;
	
#if(UPDS_UABC_MEAS_SEL == UPDS_UABC_MEAS_ENABLE)	
	Volt->s16UAsMeas = v->s16UAnTem;
	Volt->s16UBsMeas = v->s16UBnTem;
	Volt->s16UCsMeas = v->s16UCnTem;
#endif		

	
	ls_UdcMeasLpf +=  (((s32)(v->u16UdcTem) -ls_UdcMeasLpf)>>4);
	Volt->s16UdcMeas = ((ls_UdcMeasLpf)*Volt->s16UdcSamplePUGain )>>12; //IQ12*IQ12=IQ12(12+12-15)
//	Volt->s16UdcFluctuateGain = UPDS_SQRT3_IQ24 / Volt->s16UdcMeas ;
	//5us,直接除。DIV除2us,直接采用寄存器操作1.2us(64M),1.1s(72M)
	Volt->s16UdcFluctuateGain = LCM_DIV_RESULT;//DIV0->DIV_QUOTLO;	
	LCM_DIV(UPDS_SQRT3_IQ24,(s32)Volt->s16UdcMeas);

	if (Volt->s16UdcFluctuateGain > UPDS_UDC_UPDATA_MAX_IQ12)
		Volt->s16UdcFluctuateGain = UPDS_UDC_UPDATA_MAX_IQ12;
	else if(Volt->s16UdcFluctuateGain < UPDS_UDC_UPDATA_MIN_IQ12)
		Volt->s16UdcFluctuateGain=UPDS_UDC_UPDATA_MIN_IQ12;	
	MDS_vVoltageCalc(Volt);	

}

