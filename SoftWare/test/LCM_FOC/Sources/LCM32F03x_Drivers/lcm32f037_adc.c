/**
  ******************************************************************************
  * @file    lcm32f037_adc.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    2021-05-21
  * @brief   This file provides all the adc emulation firmware functions.
  ******************************************************************************/
/**
  ******************************************************************************
  * @attention:
  * 
  * 
  * 
  * 
  ******************************************************************************/

#include "lcm32f037_adc.h"
#include "lcm32f037_rcc.h"

/*--------------------------------------------------------------------------------------------
   adc dis,open adc clk again ADCʱ�Ӹ�λʹ�ܺ���
  --------------------------------------------------------------------------------------------*/
void ADC_DeInit(ADC_TypeDef *ADCx)
{
  if (ADCx == ADC)
  {
    /* Release ADC1 from reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_ADC, ENABLE);
    /* Enable ADC1 reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_ADC, DISABLE);
  }
}

/*--------------------------------------------------------------------------------------------
  adc enable /ADCʹ��
  --------------------------------------------------------------------------------------------*/
void ADC_Cmd(ADC_TypeDef *ADCx, FunctionalState State)
{
  if (State != DISABLE)
  {
    /* Set the ADEN bit to Enable the ADC peripheral */
    ADC->CR_b.ADEN = 1;
    ADC->TESTCFG_b.PD_ADC = 0;
    ADC->TESTCFG_b.PD_REF = 0;
    ADC->TESTCFG_b.PD_SH2 = 0;
    ADC->TESTCFG_b.PD_SH1 = 0;
    do
    {
    } while (ADC->ISR_b.ADRDY == 0);
  }
  else
  {
    /* Set the ADDIS to Disable the ADC peripheral */
    ADC->CR_b.ADSTP = 1;
    do
    {
    } while (ADC->CR_b.ADSTP);
    ADC->CR_b.ADDIS = 1;
    do
    {
    } while (ADC->CR_b.ADEN);
  }
}

/*--------------------------------------------------------------------------------------------
  adc init:12 parameters/ADC�ṹ���ʼ��
  --------------------------------------------------------------------------------------------*/
void ADC_Init(ADC_TypeDef *ADCx, ADC_InitTypeDef *ADC_InitStruct)
{
  uint32_t tmpreg = 0;
  uint32_t tmpregg = 0;
  uint32_t clktmpreg = 0;

  uint32_t AD_SELECT_DATA = 0;
  uint32_t AD_TRIM_temp = 0;

  /* Get the ADCx CFGR value */
  clktmpreg = ADC->CFGR2;

  tmpreg = ADC->CFGR1;
  tmpregg = ADC->EXTCFG;
  /* Clear SCANDIR, RES[1:0], ALIGN, EXTSEL[2:0], EXTEN[1:0] and CONT bits */
  tmpreg &= 0x00000000;
  tmpregg &= 0x00000000;
  clktmpreg &= 0x07ffffff;

  tmpreg |= (uint32_t)(ADC_InitStruct->ADC_Resolution | ((uint32_t)(ADC_InitStruct->ADC_ContinuousConvMode) << 13) |
                       ((uint32_t)(ADC_InitStruct->ADC_AutoWatiMode) << 14) | ((uint32_t)(ADC_InitStruct->ADC_DMATRIG_LEVEL)) |
                       ((uint32_t)(ADC_InitStruct->ADC_DiscMode) << 16) | ADC_InitStruct->ADC_DataAlign | ADC_InitStruct->ADC_ScanDirection);

  tmpregg |= (uint32_t)(ADC_InitStruct->ADC_ExternalTrigConvEdge | ADC_InitStruct->ADC_ExternalTrigConv);

  clktmpreg = (uint32_t)(ADC_InitStruct->ADC_ClkMode | ADC_InitStruct->ADC_SamecMode);

  ADC->CFGR1 = tmpreg;
  ADC->CFGR1 |= ((uint32_t)(ADC_InitStruct->ADC_DMA));
  ADC->EXTCFG = tmpregg;
  ADC->TESTCFG = 0x000000dc;
  ADC->CFGR2 = clktmpreg;

  AD_SELECT_DATA = ADC_InitStruct->ADC_Vref;

  AD_TRIM_temp = (*(volatile uint32_t *)(0x1FFFF5EC)); //

  if (AD_TRIM_temp == 0xffffffff)
  {
    AD_TRIM_temp = 0x00440055;
  }
  else
  {
    AD_TRIM_temp = ADC->TRIM;
  }
  ADC->TRIM = AD_TRIM_temp;

  if (AD_SELECT_DATA == 1) //in vdd 33
  {
    ADC->CFGR2 |= ADC_Vref_Internal_3V3_data;
  }
  else if (AD_SELECT_DATA == 2) //ex vdd 33
  {
    ADC->CFGR2 |= ADC_Vref_Internal_5V_data;
  }
  else if (AD_SELECT_DATA == 3)
  {
    ADC->CFGR2 |= (1 << 1);
    chipctrl_access();
    CHIPCTRL->PWR_CFG |= ADC_Vref_Externa_Vrh2V5_data;
    __dekey();
  }
  else if (AD_SELECT_DATA == 4)
  {
    ADC->CFGR2 |= (1 << 1);
    chipctrl_access();
    CHIPCTRL->PWR_CFG |= ADC_Vref_Externa_Vrh4V_data;
    __dekey();
  }
  else if (AD_SELECT_DATA == 5)
  {
    ADC->CFGR2 |= (1 << 1);
    chipctrl_access();
    CHIPCTRL->PWR_CFG |= ADC_Vref_Externa_VDD_data;
    __dekey();
  }
  else if (AD_SELECT_DATA == 6)
  {
    ADC->CFGR2 |= (1 << 1);
    chipctrl_access();
    CHIPCTRL->PWR_CFG |= ADC_Vref_Externa_IO_data;
    __dekey();
  }
  else if (AD_SELECT_DATA == 7)
  {
    ADC->CFGR2 |= (1 << 1);
    chipctrl_access();
    CHIPCTRL->PWR_CFG |= ADC_Vref_ExternaIO_VRH_C_data;
    __dekey();
  }
}

/*--------------------------------------------------------------------------------------------
   12 parameters for adc
  --------------------------------------------------------------------------------------------*/
void ADC_StructInit(ADC_InitTypeDef *ADC_InitStruct)
{
  /* Reset ADC init structure parameters values */
  /* Initialize the ADC_Resolution member */
  ADC_InitStruct->ADC_ClkMode = ADC_ClockMode_sysnClk; //clk set ��sysclk or pll

  ADC_InitStruct->ADC_Resolution = ADC_Resolution_12b; //8b or 12b  ��������12λ

  /* Initialize the ADC_ContinuousConvMode member */
  ADC_InitStruct->ADC_ContinuousConvMode = DISABLE; //����ģʽת��������һ�Σ�һֱ��ͣת��

  ADC_InitStruct->ADC_AutoWatiMode = DISABLE; //�Զ��ӳ�ת��ģʽ��ֻ�����ݱ����ߣ����ܽ�����һ��ת��

  ADC_InitStruct->ADC_DMATRIG_LEVEL = FIFO_DMA_NOEMPTY; //FIFO �ǿ�ʱ������һ�� DMA ����

  ADC_InitStruct->ADC_DMA = DISABLE; //cfg1 bit0��ADC dma����ʹ��

  ADC_InitStruct->ADC_DiscMode = DISABLE; //cfg1 bit16 ����ģʽ������һ��ת��1�� ͨ��

  ADC_InitStruct->ADC_SamecMode = DISABLE; //cfg2 bit0 ͬʱ����ģʽ

  /* Initialize the ADC_ExternalTrigConvEdge member */
  ADC_InitStruct->ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None; //�ⲿ����

  /* Initialize the ADC_ExternalTrigConv member */
  ADC_InitStruct->ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_TRGO; //�ⲿ����Դ

  /* Initialize the ADC_DataAlign member */
  ADC_InitStruct->ADC_DataAlign = ADC_DataAlign_Right; //�����Ҷ���

  /* Initialize the ADC_ScanDirection member */
  ADC_InitStruct->ADC_ScanDirection = ADC_ScanDirection_Upward; //ͨ��ɨ�跽��

  ADC_InitStruct->ADC_Vref = ADC_Vref_Internal_3V3;
}

/*--------------------------------------------------------------------------------------------
   auto power off mode for adc
  --------------------------------------------------------------------------------------------*/
void ADC_AutoPowerOffCmd(ADC_TypeDef *ADCx, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    /* Enable the ADC Automatic Power-Off */
    ADC->CFGR2 |= (2 << 9);
  }
  else
  {
    /* Disable the ADC Automatic Power-Off */
    ADC->CFGR2 &= ~(1 << 10);
  }
}

/*--------------------------------------------------------------------------------------------
   anglogwatchdog enable
  --------------------------------------------------------------------------------------------*/
void ADC_AnalogWatchdogCmd(ADC_TypeDef *ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  if (NewState != DISABLE)
  {
    /* Enable the ADC Analog Watchdog */
    ADC->CFGR1 |= ADC_CFGR1_AWDEN_Msk;
  }
  else
  {
    /* Disable the ADC Analog Watchdog */
    ADC->CFGR1 &= (uint32_t)~ADC_CFGR1_AWDEN_Msk;
  }
}

/*--------------------------------------------------------------------------------------------
   anglogwatchdog low-high
  --------------------------------------------------------------------------------------------*/
void ADC_AnalogWatchdogThresholdsConfig(ADC_TypeDef *ADCx, uint16_t HighThreshold, uint16_t LowThreshold)
{

  /* Set the ADCx high and low threshold */
  ADC->TR = LowThreshold | ((uint32_t)HighThreshold << 16);
}

/*--------------------------------------------------------------------------------------------
   adc anglogwatchdog for which channel
  --------------------------------------------------------------------------------------------*/
void ADC_AnalogWatchdogSingleChannelConfig(ADC_TypeDef *ADCx, uint32_t ADC_AnalogWatchdog_Channel)
{
  uint32_t tmpreg = 0;

  /* Get the old register value */
  tmpreg = ADC->CFGR1;

  /* Clear the Analog watchdog channel select bits */
  tmpreg &= ~(0xf << 27);

  /* Set the Analog watchdog channel */
  tmpreg |= ADC_AnalogWatchdog_Channel;

  /* Store the new register value */
  ADC->CFGR1 = tmpreg;
}

/*--------------------------------------------------------------------------------------------
   adc anglogwatchdog for single or all channel
  --------------------------------------------------------------------------------------------*/
void ADC_AnalogWatchdogSingleChannelCmd(ADC_TypeDef *ADCx, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    /* Enable the ADC Analog Watchdog Single Channel */
    ADC->CFGR1 |= ADC_CFGR1_AWDSGL_Msk;
  }
  else
  {
    /* Disable the ADC Analog Watchdog Single Channel */
    ADC->CFGR1 &= (uint32_t)~ADC_CFGR1_AWDSGL_Msk;
  }
}

/*--------------------------------------------------------------------------------------------
  enable adc channel for tempsensor,other channel cant use
  --------------------------------------------------------------------------------------------*/
void ADC_TempSensorCmd(FunctionalState NewState)
{
  /* Check the parameters */
  //  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the temperature sensor channel*/
    ADC->CHSELR |= (uint32_t)(1 << 17);
  }
  else
  {
    /* Disable the temperature sensor channel*/
    ADC->CHSELR &= (uint32_t)(~(1 << 17));
  }
}

/*--------------------------------------------------------------------------------------------
  enable adc channel for vrefint,other channel cant use
  --------------------------------------------------------------------------------------------*/
void ADC_VrefintCmd(FunctionalState NewState)
{
  /* Check the parameters */
  //assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the Vrefint channel*/
    ADC->CHSELR |= (uint32_t)(3 << 16);
  }
  else
  {
    /* Disable the Vrefint channel*/
    ADC->CHSELR &= (uint32_t)(~(3 << 16));
  }
}

/*--------------------------------------------------------------------------------------------
  set adc channel sample
  --------------------------------------------------------------------------------------------*/
void ADC_ChannelConfig(ADC_TypeDef *ADCx, uint32_t ADC_Channel, uint32_t ADC_ConverTime, uint32_t ADC_AdjustTime, uint32_t ADC_SampleTime)
{
  uint32_t tmpreg = 0;

  /* Configure the ADC Channel */
  ADC->CHSELR |= (uint32_t)ADC_Channel;

  /* Clear the Sampling time Selection bits */
  tmpreg &= ~(ADC_SMPR_SMP_Msk | ADC_Convert_Msk | ADC_Adjust_Msk);

  /* Set the ADC Sampling Time register */
  tmpreg |= (uint32_t)((ADC_SampleTime << 0) | (ADC_ConverTime << 7) | (ADC_AdjustTime << 4));

  /* Configure the ADC Sample time register */
  ADC->SMPR = tmpreg;
}

/*--------------------------------------------------------------------------------------------
  STOP ADC��ֹͣ��ǰת��
  --------------------------------------------------------------------------------------------*/
void ADC_StopOfConversion(ADC_TypeDef *ADCx)
{
  /* Check the parameters */
  //assert_param(IS_ADC_ALL_PERIPH(ADCx));
  if (ADC->CR & ADC_CR_ADSTART_Msk)
  {
    ADC->CR |= (uint32_t)ADC_CR_ADSTP_Msk;
  }
  while (ADC->CR & ADC_CR_ADSTP_Msk)
    ;
}

/*--------------------------------------------------------------------------------------------
  START ADC 
  --------------------------------------------------------------------------------------------*/
void ADC_StartOfConversion(ADC_TypeDef *ADCx)
{
  /* Check the parameters */
  //assert_param(IS_ADC_ALL_PERIPH(ADCx));
  ADC->CR |= 0x00000001; // ADEN
  while (!(ADC->ISR & ADC_ISR_ADRDY_Msk))
    ;
  ADC->CR |= (uint32_t)ADC_CR_ADSTART_Msk; // ADSTART
}

/*--------------------------------------------------------------------------------------------
  get adc value
  --------------------------------------------------------------------------------------------*/
uint16_t ADC_GetConversionValue(ADC_TypeDef *ADCx)
{
  /* Check the parameters */
  //assert_param(IS_ADC_ALL_PERIPH(ADCx));
  /* Return the selected ADC conversion value */
  while (!(ADC->ISR & ADC_ISR_EOC_Msk))
    ;

  //	ADC->ISR|=ADC_ISR_EOC_Msk;
  return (uint16_t)ADC->DR;

  //return (uint16_t) ADC->DR;
}

/*--------------------------------------------------------------------------------------------
  ֹͣ��ر� ADCģ��
  --------------------------------------------------------------------------------------------*/
void ADC_CloseAdc(ADC_TypeDef *ADCx)
{
  /* Check the parameters */
  //assert_param(IS_ADC_ALL_PERIPH(ADCx));
  if (ADC->CR & ADC_CR_ADSTART_Msk)
  {
    ADC->CR |= ADC_CR_ADSTP_Msk;
  }
  while (ADC->CR & ADC_CR_ADSTP_Msk)
    ;
  ADC->CR |= ADC_CR_ADDIS_Msk;
  while (ADC->CR & ADC_CR_ADEN_Msk)
    ;
}

/*--------------------------------------------------------------------------------------------
  ʹ���ж�
  --------------------------------------------------------------------------------------------*/
void ADC_ITConfig(ADC_TypeDef *ADCx, uint32_t ADC_IT, FunctionalState NewState)
{

  if (NewState != DISABLE)
  {
    /* Enable the selected ADC interrupts */
    ADC->IER |= ADC_IT;
  }
  else
  {
    /* Disable the selected ADC interrupts */
    ADC->IER &= (~(uint32_t)ADC_IT);
  }
}

/*--------------------------------------------------------------------------------------------
  ��ADC��־״̬
  --------------------------------------------------------------------------------------------*/
FlagStatus ADC_GetFlagStatus(ADC_TypeDef *ADCx, uint32_t ADC_FLAG)
{
  FlagStatus bitstatus = RESET;
  uint32_t tmpreg = 0;

  /* Check the parameters */
  //assert_param(IS_ADC_ALL_PERIPH(ADCx));
  //assert_param(IS_ADC_GET_FLAG(ADC_FLAG));

  tmpreg = ADC->ISR;

  /* Check the status of the specified ADC flag */
  if ((tmpreg & ADC_FLAG) != (uint32_t)RESET)
  {
    /* ADC_FLAG is set */
    bitstatus = SET;
  }
  else
  {
    /* ADC_FLAG is reset */
    bitstatus = RESET;
  }
  /* Return the ADC_FLAG status */
  return bitstatus;
}

/*--------------------------------------------------------------------------------------------
  ��� ADC ��־λ
  --------------------------------------------------------------------------------------------*/
void ADC_ClearFlag(ADC_TypeDef *ADCx, uint32_t ADC_FLAG)
{
  /* Check the parameters */
  //assert_param(IS_ADC_ALL_PERIPH(ADCx));
  //assert_param(IS_ADC_CLEAR_FLAG(ADC_FLAG));

  /* Clear the selected ADC flags */
  if (ADC->ISR & (uint32_t)ADC_FLAG)
  {
    ADC->ISR |= (uint32_t)ADC_FLAG;
  }
}
/*--------------------------------------------------------------------------------------------
  �� ADC ��־
  --------------------------------------------------------------------------------------------*/
ITStatus ADC_GetITStatus(ADC_TypeDef *ADCx, uint32_t ADC_IT)
{
  ITStatus bitstatus = RESET;
  uint32_t enablestatus = 0;

  /* Check the parameters */
  // assert_param(IS_ADC_ALL_PERIPH(ADCx));
  // assert_param(IS_ADC_GET_IT(ADC_IT));

  /* Get the ADC_IT enable bit status */
  enablestatus = (uint32_t)(ADC->IER & ADC_IT);

  /* Check the status of the specified ADC interrupt */
  if (((uint32_t)(ADC->ISR & ADC_IT) != (uint32_t)RESET) && (enablestatus != (uint32_t)RESET))
  {
    /* ADC_IT is set */
    bitstatus = SET;
  }
  else
  {
    /* ADC_IT is reset */
    bitstatus = RESET;
  }
  /* Return the ADC_IT status */
  return bitstatus;
}

/*--------------------------------------------------------------------------------------------
 ��� ADC �жϱ�־λ
  --------------------------------------------------------------------------------------------*/
void ADC_ClearITPendingBit(ADC_TypeDef *ADCx, uint32_t ADC_IT)
{
  /* Check the parameters */
  //assert_param(IS_ADC_ALL_PERIPH(ADCx));
  //assert_param(IS_ADC_CLEAR_IT(ADC_IT));

  /* Clear the selected ADC interrupt pending bits */
  ADC->ISR = (uint32_t)ADC_IT;
}

/*--------------------------------------------------------------------------------------------
   ADC �ο���ѹѡ��
  --------------------------------------------------------------------------------------------*/
void ADC_VrefintSelect(ADC_TypeDef *ADCx, uint32_t ADC_Vref)
{
  uint32_t AD_SELECT_DATA = 0;
  uint32_t AD_TRIM_temp = 0;
  uint32_t power = 0;
  uint32_t sys = 0;
  AD_SELECT_DATA = (uint32_t)ADC_Vref;

  AD_TRIM_temp = (*(volatile uint32_t *)(0x1ffff5EC));

  if (AD_TRIM_temp == 0xffffffff)
  {
    AD_TRIM_temp = 0x00440055;
  }
  else
  {
    AD_TRIM_temp = ADC->TRIM;
  }
  ADC->TRIM = AD_TRIM_temp;

  power = CHIPCTRL->PWR_CFG;
  sys = ADC->CFGR2;

  power &= 0xfff0ffff;
  sys &= 0xfffffff5;

  if (AD_SELECT_DATA == 1) //in vdd 33
  {
    sys |= ADC_Vref_Internal_3V3_data;
  }
  else if (AD_SELECT_DATA == 2) //ex vdd 33
  {
    sys |= ADC_Vref_Internal_5V_data;
  }
  else if (AD_SELECT_DATA == 3)
  {
    sys |= (1 << 1);
    power |= ADC_Vref_Externa_Vrh2V5_data;
  }
  else if (AD_SELECT_DATA == 4)
  {
    sys |= (1 << 1);
    power |= ADC_Vref_Externa_Vrh4V_data;
  }
  else if (AD_SELECT_DATA == 5)
  {
    sys |= (1 << 1);
    power |= ADC_Vref_Externa_VDD_data;
  }
  else if (AD_SELECT_DATA == 6)
  {
    ADC->CFGR2 |= (1 << 1);
    power |= ADC_Vref_Externa_IO_data;
  }
  else if (AD_SELECT_DATA == 7)
  {
    sys |= (1 << 1);
    power |= ADC_Vref_ExternaIO_VRH_C_data;
  }
  else
  {
    sys |= ADC_Vref_Internal_3V3_data;
  }
  chipctrl_access();
  CHIPCTRL->PWR_CFG = power;
  __dekey();
  ADC->CFGR2 = sys;
}