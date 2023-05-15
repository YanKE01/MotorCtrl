#define EXPORT_MDS_GLOBALS


#include "lcm32f037_lib.h"
#include "UserIncludes.h"

/*******************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
int main(void)
{
	UP_vDeviceInit();
	US_vUserAppInit();

	while(1)
	{
		MDS_vMotorAppCommand();
		MDS_vMotorControlState();

		MDS_vVSPCheck();		
		//5.64ms,增加了后半部分至21ms
		if(UG_sUsartData.sUsartEvent.Bits.UpdateSetPara == 1)
		{
			TIM_Cmd(TIM1, DISABLE);
			UPDS_SYSTICK_DISABLE;
			UU_vUartReceDataRead(&UG_sUsartData);
			#if (UPDS_DEBUG_MODE == UPDS_SOFTTOOL_DEBUG) 
			MDS_vMotorParaReadFromFlash(&UG_sSystemControllers.sMotorPara,UG_sUsartData.u16FlashReadData);
			#elif (UPDS_DEBUG_MODE == UPDS_KEIL_DEBUG)
			MDS_vMotorParaReadFromHfile(&UG_sSystemControllers.sMotorPara);
			#endif
			US_vSystParaInitPowerup();
			MDS_vOtherInitFromUserSetting(&UG_sSystemControllers.sMotorPara);
			UP_vOPA012Config();
			UP_vTimerConfiguration();			
			UG_sUsartData.sUsartEvent.Bits.UpdateSetPara = 0;
			UG_sUsartData.sUsartEvent.Bits.WriteFlash 		= 1;
//		UG_sSysStateErr.sSystemStatePre = UG_sSysStateErr.sSystemState;
//			UG_sSysStateErr.sSystemState 		= UGT_E_SS_INIT_B;	
			TIM_Cmd(TIM1, ENABLE);
			UPDS_SYSTICK_ENABLE;
		}
	UD_vDataTransform(&UG_sUsartData.sFlashReadDataUpdata);		
	}
}
