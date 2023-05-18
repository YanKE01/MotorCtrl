#define EXPORT_MDS_CLARKPARK_H
	#include "MDS_ClarkePark.h"
#undef EXPORT_MDS_CLARKPARK_H

const s16 CP_cSinCosTable[256] = CP_SIN_COS_TABLE;


/*******************************************************************************
* Function Name  : Clarke Transformation
*******************************************************************************/
void MDS_vCurrClarke(UGT_S_CURRABC_STRU *Curr_Input, UGT_S_CURRALBE_STRU *Curr_Output)
{	
	Curr_Output->s16Alpha = Curr_Input->s16As;
	Curr_Output->s16Beta = _IQ15mpyIQ12(IQ15_DIV_SQRT_3,Curr_Input->s16As) + (_IQ15mpyIQ12(IQ15_DIV_SQRT_3,Curr_Input->s16Bs)<<1);
}

/*******************************************************************************
* Function Name  : Reverse Clarke Transformation
*******************************************************************************/
void MDS_vCurrRevClarke(UGT_S_CURRALBE_STRU *Curr_Input, UGT_S_CURRABC_STRU *Curr_Output)
{	
	Curr_Output->s16As = Curr_Input->s16Alpha;
	Curr_Output->s16Bs = -(Curr_Input->s16Alpha>>1) + _IQ14mpyIQ12(IQ14_SQRT_3_DIV_2,Curr_Input->s16Beta);
	Curr_Output->s16Cs = -Curr_Output->s16As - Curr_Output->s16Bs;
}

/*******************************************************************************
* Function Name  : Clarke Transformation
*******************************************************************************/
void MDS_vCurrPark(UGT_S_CURRALBE_STRU *Curr_Input, UGT_S_TRIG_STRU Trig_SinCos , UGT_S_CURRDQ_STRU *Curr_Output)
{	
	Curr_Output->s16Dr = _IQ15mpyIQ12(Curr_Input->s16Alpha, Trig_SinCos.s16Cos) + _IQ15mpyIQ12(Curr_Input->s16Beta, Trig_SinCos.s16Sin);
	Curr_Output->s16Qr = -_IQ15mpyIQ12(Curr_Input->s16Alpha, Trig_SinCos.s16Sin)+ _IQ15mpyIQ12(Curr_Input->s16Beta, Trig_SinCos.s16Cos);
}

/*******************************************************************************
* Function Name  : Clarke Transformation
*******************************************************************************/
void MDS_vCurrRevPark(UGT_S_CURRDQ_STRU *Curr_Input, UGT_S_TRIG_STRU Trig_SinCos , UGT_S_CURRALBE_STRU *Curr_Output)
{	
	Curr_Output->s16Alpha = _IQ15mpyIQ12(Curr_Input->s16Dr, Trig_SinCos.s16Cos) - _IQ15mpyIQ12(Curr_Input->s16Qr, Trig_SinCos.s16Sin);
	Curr_Output->s16Beta  = _IQ15mpyIQ12(Curr_Input->s16Dr, Trig_SinCos.s16Sin) + _IQ15mpyIQ12(Curr_Input->s16Qr, Trig_SinCos.s16Cos);
}


/*******************************************************************************
* Function Name  : Clarke Transformation
*******************************************************************************/
void MDS_vVoltClarke(UGT_S_VOLTAGEALL_STRU *Volt)
{		
	Volt->sVoltageAlphaBetaCalc.s16Alpha = Volt->sVoltageAbc.s16UAsCalc;
	Volt->sVoltageAlphaBetaCalc.s16Beta = _IQ15mpyIQ12(IQ15_DIV_SQRT_3, Volt->sVoltageAbc.s16UAsCalc) + (_IQ15mpyIQ12(IQ15_DIV_SQRT_3,Volt->sVoltageAbc.s16UBsCalc)<<1);
}

void MDS_vVoltMeasClarke(UGT_S_VOLTAGEALL_STRU  *Volt)
{																																								
	Volt->sVoltageAlphaBetaMeas.s16Alpha = _IQ12mpyIQ12((Volt->sVoltageAbc.s16UAsMeas-((Volt->sVoltageAbc.s16UBsMeas + Volt->sVoltageAbc.s16UCsMeas)>>1)), UPDS_UALPHA_MEAS_GAIN_IQ12);					
	Volt->sVoltageAlphaBetaMeas.s16Beta	 = _IQ12mpyIQ12((Volt->sVoltageAbc.s16UBsMeas - Volt->sVoltageAbc.s16UCsMeas), UPDS_UBETA_MEAS_GAIN_IQ12);		
}

/*******************************************************************************
* Function Name  : Clarke Transformation
*******************************************************************************/
void MDS_vVoltPark(UGT_S_VOLTALBE_STRU *In, UGT_S_TRIG_STRU Trig_SinCos, UGT_S_VOLTDQ_STRU *Out)
{	
	Out->s16Dr = _IQ15mpyIQ12(In->s16Alpha, Trig_SinCos.s16Cos) + _IQ15mpyIQ12(In->s16Beta, Trig_SinCos.s16Sin);
	Out->s16Qr = -_IQ15mpyIQ12(In->s16Alpha, Trig_SinCos.s16Sin)+ _IQ15mpyIQ12(In->s16Beta, Trig_SinCos.s16Cos);	
}

void MDS_vVoltRevPark(UGT_S_VOLTDQ_STRU *In, UGT_S_TRIG_STRU Trig_SinCos, UGT_S_VOLTALBE_STRU *Out)
{	
	Out->s16Alpha = _IQ15mpyIQ12(In->s16Dr, Trig_SinCos.s16Cos) - _IQ15mpyIQ12(In->s16Qr, Trig_SinCos.s16Sin);
	Out->s16Beta  = _IQ15mpyIQ12(In->s16Dr, Trig_SinCos.s16Sin) + _IQ15mpyIQ12(In->s16Qr, Trig_SinCos.s16Cos);
}

/*******************************************************************************
* Function Name  : Trig_Functions 
* Description    : This function returns Cosine and Sine functions of the input 
*                  angle
* Input          : angle in s16 format
* Output         : Cosine and Sine in s16 format
* Return         : none.
*******************************************************************************/
void MDS_vTrigFunctions(UGT_S_TRIG_STRU *v, s16 hAngle)
{
  u16 hindex;
	  
  /* 10 bit index computation  */  
  hindex = (u16)(hAngle + 32768);  
//  hindex /= 64;   
  hindex = hindex>>6;  	
	
  switch (hindex & SIN_MASK) 
  {
  case U0_90:
		v->s16Sin = CP_cSinCosTable[(u8)(hindex)];
		v->s16Cos = CP_cSinCosTable[(u8)(0xFF-(u8)(hindex))];
    break;
  
  case U90_180:  
		v->s16Sin = CP_cSinCosTable[(u8)(0xFF-(u8)(hindex))];
		v->s16Cos = -CP_cSinCosTable[(u8)(hindex)];
    break;
  
  case U180_270:
		v->s16Sin = -CP_cSinCosTable[(u8)(hindex)];
		v->s16Cos = -CP_cSinCosTable[(u8)(0xFF-(u8)(hindex))];
    break;
  
  case U270_360:
		v->s16Sin =  -CP_cSinCosTable[(u8)(0xFF-(u8)(hindex))];
		v->s16Cos =  CP_cSinCosTable[(u8)(hindex)]; 
    break;
  default:
    break;
  }
}





/*******************************************************************************
* Function Name  : RevPark_Circle_Limitation
* Description    : Check if
*      						 Udq.Dr^2 + Udq.Qr^2^2 <= 32767^2
*                  Apply limitation if previous condition is not met,
*                  by keeping a constant ratio 
*                  Udq/mag(Udq.Dr)
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void MDS_vVoltRevParkCircleLimit(UGT_S_VOLTDQ_STRU *Udq)
{
	s32 temp;
             
	temp = (s32)Udq->s16Dr * Udq->s16Dr +  (s32)Udq->s16Qr  * Udq->s16Qr;  // min value 0, max value 2*32767*32767
              
	if( temp > MAX_MODULE_SQUARE ) // (Vd^2+Vq^2) > MAX_MODULE^2 ?
   {
		 u16 index;

		 temp = temp>>24;
		 temp -= START_INDEX ;   // min value 0, max value 127 - START_INDEX
		 index = circle_limit_table[(u8)temp];
								
		 Udq->s16Dr = ((s32)Udq->s16Dr * (u16)(index))>>15; 
		 Udq->s16Qr = ((s32)Udq->s16Qr * (u16)(index))>>15; 
   }

} 
