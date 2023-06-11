#define EXPORT_USER_PERIPHERALINIT_H_
	#include "User_PeripheralInit.h"
#undef EXPORT_USER_PERIPHERALINIT_H_

/*******************************************************************************
* Function Name  : RCC_Configuration
* Description    : Configures the different system clocks.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

void UP_vDeviceInit(void)
{
	u32 i; 
	chipctrl_access();
	CHIPCTRL->PWR_CFG |= (5<<1)|(1<<0);
	for(i=0;i<1000000;i++);	
	SystemInit();	//��Ƶ��72M����96M��ʱ���50.4us����38.4us;��������IQ24����IQ12��ʱ����ٵ�35.2us,obs 16bit 30us,��һ�����˼�22.6us	
	SetSysClock();
	UP_vPeriphClockCmdInit();
	SysTick_Config(UPDS_SYS_TICK_PERIOD);
	#if (UPDS_DEBUG_MODE == UPDS_SOFTTOOL_DEBUG) 
//	UU_vFlashRead(FLASH_START_PAGE_ADDRESS,UPDS_UART_REC_COMMAND1_HALFWOED_LENGTH);
	MDS_vMotorParaReadFromFlash(&UG_sSystemControllers.sMotorPara,UG_sUsartData.u16FlashReadData);
	#elif (UPDS_DEBUG_MODE == UPDS_KEIL_DEBUG)
	MDS_vMotorParaReadFromHfile(&UG_sSystemControllers.sMotorPara);
	#endif
	US_vSystParaInitPowerup();
	MDS_vOtherInitFromUserSetting(&UG_sSystemControllers.sMotorPara);
	UP_vGPIOConfiguration();
	UP_vOPA012Config();
	UP_vADCConfiguration();
//	UP_vUART_Config();
	UP_vDAC1_5_Config();
	//UP_vACMPconfiguration();
	UP_vTimerConfiguration();
	User_vNVICConfiguration();
	
}

/*******************************************************************************
* Function Name  : GPIO_Configuration
* Description    : Configures the TIM1 Pins.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/


void UP_vTimerConfiguration(void)
{

  /* TIM1 clock enable */
	
		TIM_TimeBaseInitTypeDef 	TIM_TimeBaseStructure;
		GPIO_InitTypeDef 					GPIO_InitStructure;

		TIM_OCInitTypeDef  				TIM_OCInitStructure;
		TIM_BDTRInitTypeDef				TIM_BDTRInitStructure;
		
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM1 , ENABLE);
  	/* Time Base configuration */
		TIM_TimeBaseStructure.TIM_Prescaler = 0x0;
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1;
	  #if (UPDS_DEBUG_MODE == UPDS_KEIL_DEBUG)
		TIM_TimeBaseStructure.TIM_Period = UG_sSystemControllers.sMotorPara.u16PWMPerood1;
		#else
		TIM_TimeBaseStructure.TIM_Period = UG_sSystemControllers.sMotorPara.u16PWMPerood1;
		#endif	
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV2;
		
		// Initial condition is REP=0 to set the UPDATE only on the underflow
		TIM_TimeBaseStructure.TIM_RepetitionCounter = UP_REP_RATE;
		TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
		TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;                  
		TIM_OCInitStructure.TIM_Pulse = 0x505*2/3; //dummy value
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
		TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;         
		TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
		TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;          

		TIM_OC1Init(TIM1, &TIM_OCInitStructure); 
		TIM_OC2Init(TIM1, &TIM_OCInitStructure);
		TIM_OC3Init(TIM1, &TIM_OCInitStructure);
		
		
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
		TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;                  
		TIM_OCInitStructure.TIM_Pulse = 1;//UP_PWM_PERIOD-1; //dummy value
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
		TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;         
		TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
		TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset; 
         

		TIM_OC4Init(TIM1, &TIM_OCInitStructure);
		/* Enables the TIM1 Preload on CC1 Register */
		TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
		/* Enables the TIM1 Preload on CC2 Register */
		TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
		/* Enables the TIM1 Preload on CC3 Register */
		TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
		/* Enables the TIM1 Preload on CC4 Register */
		TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);

//����CMPɲ��
		sysctrl_access();
//		SYSCTRL->EDU_CFG4 |= (1 << 9); //�Ƚ���ACMP1��ΪBreakɲ��Դ
		SYSCTRL->EDU_CFG4 |= (1 << 17); //�Ƚ���ACMP1��ΪBreakɲ��Դ
		__dekey()
	
	
  	/* Automatic Output enable, Break, dead time and lock configuration	 */
  TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
  TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
  TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_OFF;//TIM_LOCKLevel_1; //
	#if (UPDS_DEBUG_MODE == UPDS_KEIL_DEBUG)
  TIM_BDTRInitStructure.TIM_DeadTime = UG_sSystemControllers.sMotorPara.u16Deadtime;
	#else
	TIM_BDTRInitStructure.TIM_DeadTime = UG_sSystemControllers.sMotorPara.u16Deadtime;
	#endif
  TIM_BDTRInitStructure.TIM_Break = TIM_Break_Enable;
  TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;
  TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Disable;

  TIM_BDTRConfig(TIM1, &TIM_BDTRInitStructure);

		TIM1->BDTR |=(1<<25);  //  ����ɲ������Ϊ�ߵ�ƽ��Ч
		TIM1->BDTR |=(0<<26);  //  AOE2��ʹ��
		TIM1->BDTR |=(1<<24);  //  ɲ��2 BK2Eʹ��	


  	/* Main Output Enable */
		TIM_CtrlPWMOutputs(TIM1, ENABLE);

		/*ʹ��Ԥװ��*/
		TIM_ARRPreloadConfig(TIM1, ENABLE);
		
  	TIM_ITConfig(TIM1, TIM_IT_Update, DISABLE);
		
		TIM1->CR2 |= TIM_MMS_OC4;

		TIM_ITConfig(TIM1, TIM_DIER_BIE, DISABLE); 
//  	/* TIM1 counter enable */
//  	TIM_Cmd(TIM1, ENABLE);

		TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCx_Enable);
		TIM_CCxNCmd(TIM1, TIM_Channel_1, TIM_CCxN_Enable);
		TIM_CCxCmd(TIM1, TIM_Channel_2, TIM_CCx_Enable);
		TIM_CCxNCmd(TIM1, TIM_Channel_2, TIM_CCxN_Enable);
		TIM_CCxCmd(TIM1, TIM_Channel_3, TIM_CCx_Enable);
		TIM_CCxNCmd(TIM1, TIM_Channel_3, TIM_CCxN_Enable);
		TIM_CCxCmd(TIM1, TIM_Channel_4, TIM_CCx_Enable);

		#if (UPDS_CHIP_TYPE_SEL	== UPDS_LCM037_24PIN)	
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_2);//TIM1_CH1     VH
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_3);//TIM1_CH2     WH
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_3);//TIM1_CH3    UH

		GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_4);//TIM1_CH1N    WL
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_4);//TIM1_CH2N    VL
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource1, GPIO_AF_2);//TIM1_CH3N    UL

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 |GPIO_Pin_5 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ;
		GPIO_Init(GPIOA, &GPIO_InitStructure);	
		
		GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		
		#elif (UPDS_CHIP_TYPE_SEL	== UPDS_LCM037_32PIN)
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_5);//TIM1_CH1     VH
		GPIO_PinAFConfig(GPIOF, GPIO_PinSource3, GPIO_AF_2);//TIM1_CH2     WH
		GPIO_PinAFConfig(GPIOF, GPIO_PinSource4, GPIO_AF_2);//TIM1_CH3     UH

		GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_1);//TIM1_CH1N    WL
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_2);//TIM1_CH2N    VL
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_4);//TIM1_CH3N    UL

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 |GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_6;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ;
		GPIO_Init(GPIOB, &GPIO_InitStructure);	
		
		GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_3 | GPIO_Pin_4;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
		GPIO_Init(GPIOF, &GPIO_InitStructure);		
		
		#endif
		
}

void UP_vBreakEnable(void)
{
	TIM1->BDTR |= (TIM_Break_Enable);//Bit 12 BKE: Break enable;����򿪣����������Ӳ���ر�PWM
	//���TIM1���жϴ�����λ
//  TIM_ClearITPendingBit(TIM1, TIM_IT_Break);
//	
//	//ʹ��ָ����TIM�ж�
//  TIM_ITConfig(TIM1, TIM_IT_Break,ENABLE);
}

void UP_vBreakDisable(void)
{
	TIM1->BDTR &= (~TIM_Break_Enable);//Bit 12 BKE: Break enable;����򿪣����������Ӳ���ر�PWM
}

/*******************************************************************************
* Function Name  : ENC_Init
* Description    : General Purpose Timer x set-up for encoder speed/position 
*                  sensors
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

void UP_vOpa0_config()
{
	GPIO_InitTypeDef  GPIO_InitStruct; 
	OPA_InitTypeDef 	OPA_InitStruct;
#if (UPDS_CHIP_TYPE_SEL	== UPDS_LCM037_24PIN)
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2,  GPIO_AF_1);

	GPIO_InitStruct.GPIO_Pin  			= GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Mode 			= GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_Speed 			= GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType 			= GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd 			= GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
		
	OPA_InitStruct.OPA_Oppselect   	= OPA0_Oppselect_PA2;
	OPA_InitStruct.OPA_Opnselect   	= OPA0_Opnselect_NIN;
	OPA_InitStruct.OPA_Gain     		= OPA_Gain_8;
	OPA_InitStruct.OPA_BiasVoltage  = OPA_BiasVoltage_EN ;
	OPA_InitStruct.OPA_FeedbackRes  = OPA_FeedbackRes_EN;
	OPA_InitStruct.OPA_Opoto_Gpio  	= OPA_OPOEX_EN;
	OPA_InitStruct.OPA_OppRES_short = OPA_OppRES_short_DISEN;
	OPA_InitStruct.OPA_OpnRES_short = OPA_OpnRES_short_DISEN; 
	OPA_Init(OPA0,&OPA_InitStruct);
	OPA_Cmd(OPA0,ENABLE);
	
#elif (UPDS_CHIP_TYPE_SEL	== UPDS_LCM037_32PIN)

 	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9,  GPIO_AF_2);
 	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8,  GPIO_AF_2);
	
	GPIO_InitStruct.GPIO_Pin  	= GPIO_Pin_9|GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType 	= GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd 	= GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
		
	OPA_InitStruct.OPA_Oppselect   	= OPA0_Oppselect_PA9;
	OPA_InitStruct.OPA_Opnselect   	= OPA0_Opnselect_PA8;
	OPA_InitStruct.OPA_Gain     		= OPA_Gain_6;
	OPA_InitStruct.OPA_BiasVoltage  = OPA_BiasVoltage_EN;
	OPA_InitStruct.OPA_FeedbackRes  = OPA_FeedbackRes_EN;
	OPA_InitStruct.OPA_Opoto_Gpio  	= OPA_OPOEX_EN;
	OPA_InitStruct.OPA_OppRES_short = OPA_OppRES_short_DISEN;
	OPA_InitStruct.OPA_OpnRES_short = OPA_OpnRES_short_DISEN; 
	OPA_Init(OPA0,&OPA_InitStruct);
	OPA_Cmd(OPA0,ENABLE);
	
#endif
}

void UP_vOpa1_config()
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	OPA_InitTypeDef 	OPA_InitStruct;
#if (UPDS_CHIP_TYPE_SEL	== UPDS_LCM037_24PIN)
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource0,  GPIO_AF_1);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource1,  GPIO_AF_1);

	GPIO_InitStruct.GPIO_Pin  	= GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType 	= GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd 	=  GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOF,&GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin  	= GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType 	= GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd 	= GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOF,&GPIO_InitStruct);


	OPA_InitStruct.OPA_Oppselect 		= OPA1_Oppselect_PF0;
	OPA_InitStruct.OPA_Opnselect 		= OPA1_Opnselect_PF1;
	OPA_InitStruct.OPA_Gain 				= OPA_Gain_6;
	OPA_InitStruct.OPA_BiasVoltage 	= OPA_BiasVoltage_EN;
	OPA_InitStruct.OPA_FeedbackRes 	= OPA_FeedbackRes_EN;
	OPA_InitStruct.OPA_Opoto_Gpio 	= OPA_OPOEX_EN;
	OPA_InitStruct.OPA_OppRES_short = OPA_OppRES_short_DISEN;
	OPA_InitStruct.OPA_OpnRES_short = OPA_OpnRES_short_DISEN;
	OPA_Init(OPA1,&OPA_InitStruct);
	OPA_Cmd(OPA1,ENABLE);
	
#elif (UPDS_CHIP_TYPE_SEL	== UPDS_LCM037_32PIN) 
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource0,  GPIO_AF_1);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource1,  GPIO_AF_1);
	
	GPIO_InitStruct.GPIO_Pin  	= GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_Level_2;
	GPIO_InitStruct.GPIO_OType 	= GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd 	= GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOF,&GPIO_InitStruct);

	OPA_InitStruct.OPA_Oppselect 		= OPA1_Oppselect_PF0;
	OPA_InitStruct.OPA_Opnselect 		= OPA1_Opnselect_PF1;
	OPA_InitStruct.OPA_Gain 				= OPA_Gain_6;
	OPA_InitStruct.OPA_BiasVoltage 	= OPA_BiasVoltage_EN;
	OPA_InitStruct.OPA_FeedbackRes 	= OPA_FeedbackRes_EN;
	OPA_InitStruct.OPA_Opoto_Gpio 	= OPA_OPOEX_EN;
	OPA_InitStruct.OPA_OppRES_short = OPA_OppRES_short_DISEN;
	OPA_InitStruct.OPA_OpnRES_short = OPA_OpnRES_short_DISEN;
	OPA_Init(OPA1,&OPA_InitStruct);
	OPA_Cmd(OPA1,ENABLE);

#endif
}
void UP_vOpa2_config()
{
	 	GPIO_InitTypeDef    GPIO_InitStruct;
	  OPA_InitTypeDef 		OPA_InitStruct;
#if (UPDS_CHIP_TYPE_SEL	== UPDS_LCM037_24PIN)		
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource0,  GPIO_AF_2);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource7,  GPIO_AF_1);

		GPIO_InitStruct.GPIO_Pin 		= GPIO_Pin_7 ;
		GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_AN;
		GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_Level_2;
		GPIO_InitStruct.GPIO_OType 	= GPIO_OType_PP;
		GPIO_InitStruct.GPIO_PuPd 	= GPIO_PuPd_NOPULL;
		GPIO_Init(GPIOA, &GPIO_InitStruct);

		GPIO_InitStruct.GPIO_Pin 		= GPIO_Pin_0;
		GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_AN;
		GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_Level_2;
		GPIO_InitStruct.GPIO_OType 	= GPIO_OType_PP;
		GPIO_InitStruct.GPIO_PuPd 	= GPIO_PuPd_NOPULL;
		GPIO_Init(GPIOB, &GPIO_InitStruct);

		OPA_InitStruct.OPA_Oppselect 		= OPA2_Oppselect_PB0;
		OPA_InitStruct.OPA_Opnselect 		= OPA2_Opnselect_PA7 ;
		OPA_InitStruct.OPA_Gain 				= OPA_Gain_6 ;
		OPA_InitStruct.OPA_BiasVoltage 	= OPA_BiasVoltage_EN ;
		OPA_InitStruct.OPA_FeedbackRes 	= OPA_FeedbackRes_EN;
		OPA_InitStruct.OPA_Opoto_Gpio 	= OPA_OPOEX_EN;
		OPA_InitStruct.OPA_OppRES_short = OPA_OppRES_short_DISEN;
		OPA_InitStruct.OPA_OpnRES_short = OPA_OpnRES_short_DISEN;
		OPA_Init(OPA2,&OPA_InitStruct);
		OPA_Cmd(OPA2,ENABLE);
		
#elif (UPDS_CHIP_TYPE_SEL	== UPDS_LCM037_32PIN) 
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource5,  GPIO_AF_1);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource6,  GPIO_AF_2);

		GPIO_InitStruct.GPIO_Pin 		= GPIO_Pin_5|GPIO_Pin_6;
		GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_AN;
		GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_Level_2;
		GPIO_InitStruct.GPIO_OType 	= GPIO_OType_PP;
		GPIO_InitStruct.GPIO_PuPd 	= GPIO_PuPd_NOPULL;
		GPIO_Init(GPIOA, &GPIO_InitStruct);

		OPA_InitStruct.OPA_Oppselect 		= OPA2_Oppselect_PA5;
		OPA_InitStruct.OPA_Opnselect 		= OPA2_Opnselect_PA6;
		OPA_InitStruct.OPA_Gain 				= OPA_Gain_6;
		OPA_InitStruct.OPA_BiasVoltage 	= OPA_BiasVoltage_EN ;
		OPA_InitStruct.OPA_FeedbackRes 	= OPA_FeedbackRes_EN;
		OPA_InitStruct.OPA_Opoto_Gpio 	= OPA_OPOEX_EN;
		OPA_InitStruct.OPA_OppRES_short = OPA_OppRES_short_DISEN;
		OPA_InitStruct.OPA_OpnRES_short = OPA_OpnRES_short_DISEN;
		OPA_Init(OPA2,&OPA_InitStruct);
		OPA_Cmd(OPA2,ENABLE);
		
#endif
}

void UP_vOPA012Config()
{
	UP_vOpa0_config();
	UP_vOpa1_config();
	UP_vOpa2_config();
	#if (UPDS_CHIP_TYPE_SEL	== UPDS_LCM037_24PIN)	
	ANACTRL->ANA_CSR &= (~0X0300);	//00 :VSS; 01 :PA8(YA2);10 :PF1(YA1);11 :PA6
	#elif (UPDS_CHIP_TYPE_SEL	== UPDS_LCM037_32PIN) 
	ANACTRL->ANA_CSR &= (~0X0300);	//00 :VSS; 01 :PA8(YA2);10 :PF1(YA1);11 :PA6
	ANACTRL->ANA_CSR |= (0X0300);		//00 :VSS; 01 :PA8(YA2);10 :PF1(YA1);11 :PA6
	#endif	
}

void UP_vGPIOConfiguration(void)
{
		GPIO_InitTypeDef       GPIO_InitStruct;
	  /* ��1������ GPIO ��ʱ�� */	
	  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOF , ENABLE);

#if (UPDS_CHIP_TYPE_SEL	== UPDS_LCM037_24PIN)		
	GPIO_ResetBits(GPIOA, GPIO_Pin_3 );
	GPIO_ResetBits(GPIOA, GPIO_Pin_5 );
	GPIO_ResetBits(GPIOB, GPIO_Pin_1 );
	
	GPIO_ResetBits(GPIOA, GPIO_Pin_8 );
	GPIO_ResetBits(GPIOA, GPIO_Pin_9 );
	GPIO_ResetBits(GPIOA, GPIO_Pin_10 );

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0, GPIO_AF_1);  //PA0 speed	
	GPIO_InitStruct.GPIO_Pin  	= GPIO_Pin_0;
  GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_AN;
  GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_Level_2;
  GPIO_InitStruct.GPIO_OType 	= GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd 	= GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&GPIO_InitStruct);

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6, GPIO_AF_1);  //PA6 Udc	
	GPIO_InitStruct.GPIO_Pin  	= GPIO_Pin_6;
  GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_AN;
  GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_Level_2;
  GPIO_InitStruct.GPIO_OType 	= GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd 	= GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&GPIO_InitStruct);

	//DAC
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource6, GPIO_AF_1);//PB6  
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource7, GPIO_AF_1);	//PB7  
	
	GPIO_InitStruct.GPIO_Pin 		= GPIO_Pin_6 ;
	GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_PuPd 	= GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin 		= GPIO_Pin_7 ;
	GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_PuPd 	= GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStruct);		
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource4,  GPIO_AF_1);   //PA4  opa0N

	GPIO_InitStruct.GPIO_Pin  	= GPIO_Pin_4;
  GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_AN;
  GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_Level_2;
  GPIO_InitStruct.GPIO_OType 	= GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd 	= GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
		
	GPIO_InitStruct.GPIO_Pin 		= GPIO_Pin_12;
	GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_PuPd 	= GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin 		= GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_PuPd 	= GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin 		= GPIO_Pin_4;
	GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_PuPd 	= GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin 		= GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_PuPd 	= GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin 		= GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_PuPd 	= GPIO_PuPd_UPDOWN;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
		
#elif (UPDS_CHIP_TYPE_SEL	== UPDS_LCM037_32PIN)
	GPIO_ResetBits(GPIOB, GPIO_Pin_7 );
	GPIO_ResetBits(GPIOF, GPIO_Pin_3 );
	GPIO_ResetBits(GPIOF, GPIO_Pin_4 );
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_3 );
	GPIO_ResetBits(GPIOB, GPIO_Pin_4 );
	GPIO_ResetBits(GPIOB, GPIO_Pin_6 );
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource4, GPIO_AF_2);  //PA4 Udc	
	GPIO_InitStruct.GPIO_Pin  	= GPIO_Pin_4;
  GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_AN;
  GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_Level_2;
  GPIO_InitStruct.GPIO_OType 	= GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd 	= GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&GPIO_InitStruct);

	GPIO_PinAFConfig(GPIOB,GPIO_PinSource1, GPIO_AF_1);  //PB1 Idc ���˲�
	GPIO_InitStruct.GPIO_Pin  	= GPIO_Pin_1;
 GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_AN;
 GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_Level_2;
 GPIO_InitStruct.GPIO_OType 	= GPIO_OType_PP;
 GPIO_InitStruct.GPIO_PuPd 	= GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3, GPIO_AF_1);  //PA3 MosTemp
	GPIO_InitStruct.GPIO_Pin  	= GPIO_Pin_3;
  GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_AN;
  GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_Level_2;
  GPIO_InitStruct.GPIO_OType 	= GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd 	= GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
//	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7, GPIO_AF_2);  //OPA1 Out Idc
//	GPIO_InitStruct.GPIO_Pin  	= GPIO_Pin_7;
//  GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_AN;
//  GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_Level_2;
//  GPIO_InitStruct.GPIO_OType 	= GPIO_OType_PP;
//  GPIO_InitStruct.GPIO_PuPd 	= GPIO_PuPd_NOPULL;
//	GPIO_Init(GPIOA,&GPIO_InitStruct);

	GPIO_PinAFConfig(GPIOB,GPIO_PinSource0, GPIO_AF_2);  //PB0 ADC YK-TEST
	GPIO_InitStruct.GPIO_Pin  	= GPIO_Pin_0;
  GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_AN;
  GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_Level_2;
  GPIO_InitStruct.GPIO_OType 	= GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd 	= GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
		
#endif
}

void UP_vADCConfiguration(void)
{
		ADC_InitTypeDef	ADC_InitStructure;
		DMA_InitTypeDef DMA_InitStructure;	
	
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_ADC,ENABLE);
	
		ADC_StructInit(&ADC_InitStructure);			
	
		ADC_VrefintSelect(ADC,4);	//ѡ��ο���ƽ 1��3.3V  2��5.0V  3:2.5V  4:4.0V  5:VDD  6: �ⲿIO����ο���ѹ  7��VRH���			
		/* ADC configuration ------------------------------------------------------*/
		/* Configure the ADC in continous mode withe a resolutuion equal to 12 bits  */
		ADC_InitStructure.ADC_ClkMode = ADC_ClockMode_SynClkDiv4; //	ADC->CFGR2->(0X01<<27)	SYS_CLK/2 ʱ�ӷ�Ƶϵ��
		ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;		//	ADC->CFGR1->0x00
		ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; 			// 	ADC->CFGR1->bit13 0:����ת��ģʽ   				1������ת��ģʽ
		ADC_InitStructure.ADC_AutoWatiMode = ENABLE; 							//	ADC->CFGR1->bit13 0:�Զ��ӳ�ת��ģʽ�ر�  1: �Զ��ӳ�ת��ģʽ����
	  ADC_InitStructure.ADC_DMATRIG_LEVEL = FIFO_DMA_NOEMPTY;	
		ADC_InitStructure.ADC_DMA = ENABLE; 											//	ADC->CFGR1->bit0	0��DMA disabled 				1�� DMA enabled
		
		ADC_InitStructure.ADC_DiscMode 	 = DISABLE; 								//	ADC->CFGR1->bit16 0�� ����ģʽ��ֹ				1�� ����ģʽ����
		ADC_InitStructure.ADC_SamecMode  = ENABLE; 								//	ADC->CFGR2->bit0	0����������ģʽ  				1��ͬʱ����
		ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_Falling;	//ADC->EXTCFG->bit0&1->10���ⲿ�½��ش���
		ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_TRGO;					//ADC->EXTCFG   TIM1_TRGO��������
		ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;													//	ADC->CFGR1->bit5		0: �Ҷ���		1: �����
		ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Backward;								// 	ADC->CFGR1->bit2 		0�� ��ǰɨ�� (�� CHSEL0 �� CHSEL15 )	1�� ���ɨ�� (�� CHSEL15 �� CHSEL0 )
		ADC_InitStructure.ADC_Vref = ADC_Vref_Externa_Vrh4V ;  //ADC_Vref_Internal_3V3;		
		ADC_Init(ADC, &ADC_InitStructure);

		//notez ��Ϊ��backward scan�� ��� ADCConvertedRawData[ADC_SIZE]�д洢�����ݷֱ���
		#if (UPDS_CHIP_TYPE_SEL	== UPDS_LCM037_24PIN)	
		ADC_ChannelConfig(ADC,ADC_Channel_0,7,1,1); 	//VSP
		ADC_ChannelConfig(ADC,ADC_Channel_2,7,1,1);		//OP2,Iv	
    ADC_ChannelConfig(ADC,ADC_Channel_4,7,1,1);		//VTH		
		ADC_ChannelConfig(ADC,ADC_Channel_6,7,1,1); 	//Udc
		ADC_ChannelConfig(ADC,ADC_Channel_11,7,1,1); 	//OPA0��Idc
		ADC_ChannelConfig(ADC,ADC_Channel_12,7,1,1); 	//OP1,Iu  
		#elif (UPDS_CHIP_TYPE_SEL	== UPDS_LCM037_32PIN)
			#if(UPDS_UABC_MEAS_SEL == UPDS_UABC_MEAS_DISABLE)

			ADC_ChannelConfig(ADC,ADC_Channel_2,7,1,1);		//OP2,Iv	
//			ADC_ChannelConfig(ADC,ADC_Channel_3,7,1,1); 	//NTC			
			ADC_ChannelConfig(ADC,ADC_Channel_4,7,1,1);		//Udc	
			ADC_ChannelConfig(ADC,ADC_Channel_8,7,1,1);		//PB0 YK-TEST 2023-6-11

			ADC_ChannelConfig(ADC,ADC_Channel_9,7,1,1); 	//PB1 YK-TEST 2023-6-11			
			ADC_ChannelConfig(ADC,ADC_Channel_11,7,1,1); 	//OPA0��Iu
			ADC_ChannelConfig(ADC,ADC_Channel_12,7,1,1); 	//OP1��Idc
//			ADC_ChannelConfig(ADC,ADC_Channel_13,7,1,1); 	//EMPTY		

			#elif(UPDS_UABC_MEAS_SEL == UPDS_UABC_MEAS_ENABLE)
			ADC_ChannelConfig(ADC,ADC_Channel_0,7,1,1); 	//Udc
			ADC_ChannelConfig(ADC,ADC_Channel_2,7,1,1);		//OP2,Iv		
			ADC_ChannelConfig(ADC,ADC_Channel_3,7,1,1);		//Udc
			ADC_ChannelConfig(ADC,ADC_Channel_6,7,1,1);		//VAN		
			ADC_ChannelConfig(ADC,ADC_Channel_7,7,1,1);		//VBN				
			
			ADC_ChannelConfig(ADC,ADC_Channel_8,7,1,1); 	//VCN			
			ADC_ChannelConfig(ADC,ADC_Channel_9,7,1,1); 	//Idc ���˲�
			ADC_ChannelConfig(ADC,ADC_Channel_11,7,1,1); 	//OPA0��Idc
			ADC_ChannelConfig(ADC,ADC_Channel_12,7,1,1); 	//OP1��Iu
			ADC_ChannelConfig(ADC,ADC_Channel_13,7,1,1); 	//Speed
			#endif
		#endif		
					
		ADC_Cmd(ADC, ENABLE);     
				
		ADC_StartOfConversion(ADC);		

//DMA����ADC���ݣ�ADC������洢��DR�Ĵ��������������������ַΪDR�Ĵ������������ڴ����ַ�����Զ������顣
			
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA,ENABLE);

		/*DMA1 channel1 configuration ----------------------------------------------*/
		DMA_DeInit(DMA1_Channel1);
		DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;//��������DMA������������ַ
		DMA_InitStructure.DMA_MemoryBaseAddr = (u32) &ADCConvertedRawData;//�ڴ����ַ
		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;//�������ݴ��䷽�򣬼������Ǵ������ȡ���ݵ��ڴ滹�Ǵ��ڴ�����ݵ����裬���������Ǵ�����ADC_DR�Ĵ��������ݵ��ڴ�		
		
		DMA_InitStructure.DMA_BufferSize = ADC_SAMPLE_NUM;//����һ�δ����������Ĵ�С
	
	//Peripheral:adj.��Χ��
		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//���ô������ݵ�ʱ�� �����裩 ��ַ�ǲ��仹�ǵ�����
		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//���ô������ݵ�ʱ�� ���ڴ� ����ַ�ǲ��仹�ǵ���
		DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;//������������ݳ�����Ϊ�ֽڴ��䣨8bits�����ǰ��֣�16bits�������ִ��䣨32bits��
		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;//�����ڴ�����ݳ��ȣ�ͬ�ϡ�
		DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//�����Ƿ����ѭ���ɼ�
		DMA_InitStructure.DMA_Priority = DMA_Priority_High;//�������ȼ�
		DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
		DMA_Init(DMA1_Channel1, &DMA_InitStructure);//�����Ƿ��Ǵ洢�����洢��ģʽ����

//	DMA_ClearITPendingBit(DMA1_FLAG_TC1);

		/* Enable DMA1 channel1 TC interupt*/
		DMA_ITConfig(DMA1_Channel1, DMA1_FLAG_TC1, ENABLE);//����DMA������ɺ��ж�
		
		DMA_RemapConfig(DMA1_Channel1, DMA_ReqNum5, DMA_REQ_ADC);
		DMA_SetCurrDataCounter(DMA1_Channel1, ADC_SAMPLE_NUM);
		
		/* Enable DMA1 channel1 */
		DMA_Cmd(DMA1_Channel1, ENABLE);
//}	
	
}

void UP_vUART_Config()
{
	UART_InitTypeDef UART_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	DMA_InitTypeDef DMA_InitStructure;

	RCC_UART0CLKConfig(RCC_UART0CLK_RCH); //ѡ��UART0ʱ��Դ��������Ĭ������ʱ��

	UART_StructInit(&UART_InitStruct);
	UART_InitStruct.UART_BaudRate = UPDS_USARTBANDRATE;
	UART_InitStruct.UART_WordLength = UART_WordLength_8b;
	UART_InitStruct.UART_StopBits = UART_StopBits_1;
	UART_InitStruct.UART_Parity = UART_Parity_No;
	UART_InitStruct.UART_HardwareFlowControl = UART_HardwareFlowControl_None;
	UART_InitStruct.UART_Mode = UART_Mode_Rx | UART_Mode_Tx;
	UART_Init(UART0, &UART_InitStruct);

	UART_FIFOLevelConfig(UART0,UART_RXIFLSEL_LEAVEL_1_8,UART_TXIFLSEL_LEAVEL_1_2);
	UART_FIFOEnable(UART0, ENABLE);
	
	DMA_DeInit(DMA1_Channel0);
	DMA_InitStructure.DMA_PeripheralBaseAddr = UPDS_UART_DR_ADDRESS;				//��������DMA������������ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&UG_sUsartData.u8SendData1;		//�ڴ����ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;						//�������ݴ��䷽�򣬼������Ǵ������ȡ���ݵ��ڴ滹�Ǵ��ڴ�����ݵ����裬���������Ǵ�����ADC_DR�Ĵ��������ݵ��ڴ�
	DMA_InitStructure.DMA_BufferSize = 1;									//����һ�δ����������Ĵ�С
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;		//���ô������ݵ�ʱ�� �����裩 ��ַ�ǲ��仹�ǵ�����
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;					//���ô������ݵ�ʱ�� ���ڴ� ����ַ�ǲ��仹�ǵ���
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //������������ݳ�����Ϊ�ֽڴ��䣨8bits�����ǰ��֣�16bits�������ִ��䣨32bits��
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//DMA_Mode_Circular;//			//�����ڴ�����ݳ��ȣ�ͬ�ϡ�
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;//DMA_Mode_Circular;							//�����Ƿ����ѭ���ɼ�
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;						//�������ȼ�
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;							//�ڴ浽�ڴ�ʹ��
	DMA_Init(DMA1_Channel0, &DMA_InitStructure);							//�����Ƿ��Ǵ洢�����洢��ģʽ����


	DMA_ITConfig(DMA1_Channel0, DMA1_IT_TC0, ENABLE); //����DMA������ɺ��ж�

	DMA_SetCurrDataCounter(DMA1_Channel0, UPDS_UART_SIZE);

	DMA_Cmd(DMA1_Channel0, ENABLE);
//	/*����ҪDMA�жϣ�������ע�͵���*/
////	NVIC_ClearPendingIRQ(DMAC_CH1_2_IRQn);
////	NVIC_EnableIRQ(DMAC_CH1_2_IRQn);


////����
//	/*DMA_DeInit(DMA1_Channel3);
//	DMA_InitStructure.DMA_PeripheralBaseAddr = UPDS_UART_DR_ADDRESS;				//��������DMA������������ַ
//	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&UG_sUsartData.u8ReceiveData;		//�ڴ����ַ
//	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;						//�������ݴ��䷽�򣬼������Ǵ������ȡ���ݵ��ڴ滹�Ǵ��ڴ�����ݵ����裬���������Ǵ�����ADC_DR�Ĵ��������ݵ��ڴ�
//	DMA_InitStructure.DMA_BufferSize = UPDS_UART_REC_COMMAND1_LENGTH;									//����һ�δ����������Ĵ�С
//	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;		//���ô������ݵ�ʱ�� �����裩 ��ַ�ǲ��仹�ǵ�����
//	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;					//���ô������ݵ�ʱ�� ���ڴ� ����ַ�ǲ��仹�ǵ���
//	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //������������ݳ�����Ϊ�ֽڴ��䣨8bits�����ǰ��֣�16bits�������ִ��䣨32bits��
//	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;			//�����ڴ�����ݳ��ȣ�ͬ�ϡ�
//	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;//DMA_Mode_Normal;//DMA_Mode_Circular;							//�����Ƿ����ѭ���ɼ�
//	DMA_InitStructure.DMA_Priority = DMA_Priority_High;						//�������ȼ�
//	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;							//�ڴ浽�ڴ�ʹ��
//	DMA_Init(DMA1_Channel3, &DMA_InitStructure);							//�����Ƿ��Ǵ洢�����洢��ģʽ����


//	//DMA_ITConfig(DMA1_Channel3, DMA1_IT_TC3, ENABLE); //����DMA������ɺ��ж�

//	DMA_SetCurrDataCounter(DMA1_Channel3, UPDS_UART_REC_COMMAND1_LENGTH);
//	DMA_RemapConfig(DMA1_Channel3, DMA_ReqNum1, DMA_REQ_UART0_RX);
//	//DMA_Cmd(DMA1_Channel3, DISABLE);
//	DMA_Cmd(DMA1_Channel3, ENABLE);
//	*/
	UART_DMACmd(UART0, UART_DMAReq_Tx, ENABLE);
	//UART_DMACmd(UART0, UART_DMAReq_Rx, ENABLE);


	UART_ITConfig(UART0, UART_IT_RX, ENABLE);

	NVIC_ClearPendingIRQ(UART0_IRQn);
	NVIC_EnableIRQ(UART0_IRQn);
	
	UART_Cmd(UART0, ENABLE);
  UART_GetFlagStatus(UART0, UART_STATUS_TXFE);
	
  DMA_ClearITPendingBit(DMA1_FLAG_TC0);	

}


void UP_vDAC1_5_Config()
{
	
	DAC_InitTypeDef DAC_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	
//	GPIO_PinAFConfig(GPIOB,GPIO_PinSource6, GPIO_AF_1);//DAC
//	GPIO_PinAFConfig(GPIOB,GPIO_PinSource7, GPIO_AF_1);	

//	
//	GPIO_InitStruct.GPIO_Pin =   GPIO_Pin_6 ;
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
//	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
//	GPIO_Init(GPIOB, &GPIO_InitStruct);

//	GPIO_InitStruct.GPIO_Pin =   GPIO_Pin_7 ;
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
//	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
//	GPIO_Init(GPIOB, &GPIO_InitStruct);		
	
//	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10, GPIO_AF_2);//DAC
//	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_10;
//  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
//  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
//  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
//  GPIO_InitStruct.GPIO_PuPd =  GPIO_PuPd_NOPULL;
//	GPIO_Init(GPIOA,&GPIO_InitStruct);	

	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_ANACTRL,ENABLE);

	DAC_InitStruct.DAC_EXTrigger_Edge = DAC_EXTrigger_edge_dis;
	DAC_InitStruct.DAC_Trigger_Source = DAC_Trigger_Software;
	DAC_InitStruct.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStruct.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
	DAC_InitStruct.DAC_OutputBuffer = DAC0_OutputBuffer_Enable;
	DAC_InitStruct.DAC_Vref_Select = DAC_Vref_Avdd;//DAC_Vref_Pum_4v;//
	DAC_InitStruct.DAC_DmaMode = DISABLE;
	DAC_InitStruct.DAC_DMAUDR_IE = DISABLE;
	DAC_Init(DAC0, &DAC_InitStruct);
	DAC_Cmd(DAC0, ENABLE);

	
	DAC_InitStruct.DAC_EXTrigger_Edge = DAC_EXTrigger_edge_dis;
	DAC_InitStruct.DAC_Trigger_Source = DAC_Trigger_Software;
	DAC_InitStruct.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStruct.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
	DAC_InitStruct.DAC_OutputBuffer = DAC1_OutputBuffer_Enable;
	DAC_InitStruct.DAC_Vref_Select = DAC_Vref_Avdd;//DAC_Vref_Pum_4v;
	DAC_InitStruct.DAC_DmaMode = DISABLE;
	DAC_InitStruct.DAC_DMAUDR_IE = DISABLE;
	DAC_Init(DAC1, &DAC_InitStruct);
	DAC_Cmd(DAC1, ENABLE);


}

void UP_vACMPconfiguration(void)
{
 
	ACMP_InitTypeDef ACMP_InitStruct;

	ACMP_InitStruct.ACMP_P_Select = CP1_PS_CPP1EXT_INPUT; //?????   ??????? ??OPA0-out 
	ACMP_InitStruct.ACMP_N_Select = CP1_NS_DAC1OUT;    //DAC1/PB0       ??????? DAC1-out
	ACMP_InitStruct.ACMP_Delay_time = CP_NODelay_time;   //??????
	ACMP_InitStruct.ACMP_Blanking = CP_NOBLANKING;    //????????
	ACMP_InitStruct.ACMP_Is = CP_IS_POS;      //???????
	ACMP_InitStruct.ACMP_HYSEN = DISABLE;      //??????
	ACMP_InitStruct.ACMP_FREN = ENABLE;       //??????
	ACMP_InitStruct.ACMP_FS = DISABLE;       //????????

	ACMP_InitStruct.CMP_INTENMASK = DISABLE;    //
	ACMP_InitStruct.CMP_SEQ_MODE = DISABLE;     //����������
	ACMP_InitStruct.TRIG_MODE = CP_TIRG_INASOFT;   //�������
	ACMP_InitStruct.CHNL_CNT_TIME = CHNL_CNT_TIME_64CLK; //?????????????
	ACMP1_Init(&ACMP_InitStruct);
	ACMP1_SEQ_INPUT_SELECT(DISABLE, 6, 1); //111:CP1_P_P01��OPA0OUT,DAC1 as negative
	ACMP1_Cmd(ENABLE);

	SATRT_OFACMP1(); //only soft trigger need

}
void UP_vPeriphClockCmdInit(void)
{
	RCC_ClocksTypeDef RCC_Clocks;
	RCC_GetClockFreq(&RCC_Clocks);	
	RCC_AHBPeriphClockCmd(RCC_APB1Periph_UART0, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_ANACTRL,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA|RCC_AHBPeriph_GPIOB|RCC_AHBPeriph_GPIOC|RCC_AHBPeriph_GPIOF,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_APB1Periph_ADC,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA|RCC_AHBPeriph_CRC|RCC_AHBPeriph_DIV,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_FLASH, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_EXTI, ENABLE);
}
