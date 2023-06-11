/**
 ******************************************************************************
 * @file    lcm32f037_acmp.c
 * @author  MCD Application Team
 * @version V1.0.0
 * @date    2021-05-21
 * @brief   This file provides all the acmp emulation firmware functions.
 ******************************************************************************/
/**
 ******************************************************************************
 * @attention:
 *
 *
 *
 *
 ******************************************************************************/
#include "lcm32f037_acmp.h"
#include "lcm32f037.h"
#include "lcm32f037_rcc.h"

/*--------------------------------------------------------------------------------------------
ANACTRL时钟关闭 :DAC ACMP OPA 三者公用一个时钟使能 ,DEINIT 函数用一次即可
  --------------------------------------------------------------------------------------------*/
void ACMP_DeInit(void)
{
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_ANACTRL, ENABLE);
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_ANACTRL, DISABLE);
}

/*--------------------------------------------------------------------------------------------
比较器初始化0
  --------------------------------------------------------------------------------------------*/
void ACMP0_Init(ACMP_InitTypeDef *ACMP_InitStruct)
{
  uint32_t tmpreg = 0;
  uint32_t tmpreg1 = 0;
  uint32_t tmpreg2 = 0;
  tmpreg = ACMP->ACMP0_CSR;
  tmpreg &= ~(0x00007FF8);

  tmpreg1 = ACMP->ACMP0_MUXCR;
  tmpreg1 &= ~(0x33fffffe);

  tmpreg2 = ACMP->ACMP0_EXTCFG;
  tmpreg2 &= ~(0xffffffff);

  tmpreg |= (ACMP_InitStruct->ACMP_P_Select | ACMP_InitStruct->ACMP_N_Select | ACMP_InitStruct->ACMP_Blanking | ACMP_InitStruct->ACMP_Delay_time |
             ACMP_InitStruct->ACMP_Is | (ACMP_InitStruct->ACMP_FREN << 1) | (ACMP_InitStruct->ACMP_HYSEN << 2) | (ACMP_InitStruct->ACMP_FS << 8));

  tmpreg1 |= ((ACMP_InitStruct->CMP_INTENMASK << 29) | ACMP_InitStruct->TRIG_MODE | ACMP_InitStruct->CHNL_CNT_TIME | (ACMP_InitStruct->CMP_SEQ_MODE << 1));

  tmpreg2 |= ((ACMP_InitStruct->EXTEN_Signal_andmode << 3) | ACMP_InitStruct->EXTSELECT | ACMP_InitStruct->EXTEN_MODE_SEL | ACMP_InitStruct->EXTEN_EDGE_MODE | ACMP_InitStruct->TRIG_DELAY_TIME |
              ACMP_InitStruct->TRIG_SOURCE | ACMP_InitStruct->CP_EXTSP | ACMP_InitStruct->SYN_MODE);

  ACMP->ACMP0_CSR = tmpreg;
  ACMP->ACMP0_MUXCR = tmpreg1;
  ACMP->ACMP0_EXTCFG = tmpreg2;
}
/*--------------------------------------------------------------------------------------------
比较器初始化1
  --------------------------------------------------------------------------------------------*/
void ACMP1_Init(ACMP_InitTypeDef *ACMP_InitStruct)
{
  uint32_t tmpreg = 0;
  uint32_t tmpreg1 = 0;
  uint32_t tmpreg2 = 0;
  tmpreg = ACMP->ACMP1_CSR;
  tmpreg &= ~(0x00007FF8);

  tmpreg1 = ACMP->ACMP1_MUXCR;
  tmpreg1 &= ~(0x33fffffe);

  tmpreg2 = ACMP->ACMP1_EXTCFG;
  tmpreg2 &= ~(0xffffffff);

  tmpreg |= (ACMP_InitStruct->ACMP_P_Select | ACMP_InitStruct->ACMP_N_Select | ACMP_InitStruct->ACMP_Blanking | ACMP_InitStruct->ACMP_Delay_time |
             ACMP_InitStruct->ACMP_Is | (ACMP_InitStruct->ACMP_FREN << 1) | (ACMP_InitStruct->ACMP_HYSEN << 2) | (ACMP_InitStruct->ACMP_FS << 8));

  tmpreg1 |= ((ACMP_InitStruct->CMP_INTENMASK << 29) | ACMP_InitStruct->TRIG_MODE | ACMP_InitStruct->CHNL_CNT_TIME | (ACMP_InitStruct->CMP_SEQ_MODE << 1));

  tmpreg2 |= ((ACMP_InitStruct->EXTEN_Signal_andmode << 3) | ACMP_InitStruct->EXTSELECT | ACMP_InitStruct->EXTEN_MODE_SEL | ACMP_InitStruct->EXTEN_EDGE_MODE | ACMP_InitStruct->TRIG_DELAY_TIME |
              ACMP_InitStruct->TRIG_SOURCE | ACMP_InitStruct->CP_EXTSP | ACMP_InitStruct->SYN_MODE);

  ACMP->ACMP1_CSR = tmpreg;
  ACMP->ACMP1_MUXCR = tmpreg1;
  ACMP->ACMP1_EXTCFG = tmpreg2;
}
/*--------------------------------------------------------------------------------------------
比较器初始化2
  --------------------------------------------------------------------------------------------*/
void ACMP2_Init(ACMP_InitTypeDef *ACMP_InitStruct)
{
  uint32_t tmpreg = 0;
  uint32_t tmpreg1 = 0;
  uint32_t tmpreg2 = 0;
  tmpreg = ACMP->ACMP2_CSR;
  tmpreg &= ~(0x00007FF8);

  tmpreg1 = ACMP->ACMP2_MUXCR;
  tmpreg1 &= ~(0x33fffffe);

  tmpreg2 = ACMP->ACMP2_EXTCFG;
  tmpreg2 &= ~(0xffffffff);

  tmpreg |= ( ACMP_InitStruct->ACMP_Blanking | ACMP_InitStruct->ACMP_Delay_time |
             ACMP_InitStruct->ACMP_Is | (ACMP_InitStruct->ACMP_FREN << 1) | (ACMP_InitStruct->ACMP_HYSEN << 2) | (ACMP_InitStruct->ACMP_FS << 8));

  tmpreg1 |= ((ACMP_InitStruct->CMP_INTENMASK << 29) | ACMP_InitStruct->TRIG_MODE | ACMP_InitStruct->CHNL_CNT_TIME | (ACMP_InitStruct->CMP_SEQ_MODE << 1));

  tmpreg2 |= ((ACMP_InitStruct->EXTEN_Signal_andmode << 3) | ACMP_InitStruct->EXTSELECT | ACMP_InitStruct->EXTEN_MODE_SEL | ACMP_InitStruct->EXTEN_EDGE_MODE | ACMP_InitStruct->TRIG_DELAY_TIME |
              ACMP_InitStruct->TRIG_SOURCE | ACMP_InitStruct->CP_EXTSP | ACMP_InitStruct->SYN_MODE);

  ACMP->ACMP2_CSR = tmpreg;
  ACMP->ACMP2_MUXCR = tmpreg1;
  ACMP->ACMP2_EXTCFG = tmpreg2;
}
/*--------------------------------------------------------------------------------------------
比较器参数定义
  --------------------------------------------------------------------------------------------*/
void ACMP_StructInit(ACMP_InitTypeDef *ACMP_InitStruct)
{
  /*--------------- Reset OPA init structure parameters values -----------------*/
  ACMP_InitStruct->ACMP_P_Select = CP0_PS_CPP0EXT_INPUT; //比较器正端输入选择

  ACMP_InitStruct->ACMP_N_Select = CP0_NS_CPN0EXT_INPUT; //比较器负端输入选择

  ACMP_InitStruct->ACMP_Delay_time = CP_NODelay_time; //输出延迟配置

  ACMP_InitStruct->ACMP_Blanking = CP_NOBLANKING; //比较器消隐源选择

  ACMP_InitStruct->ACMP_Is = CP_IS_POS; //比较器输出极性

  ACMP_InitStruct->ACMP_HYSEN = DISABLE; //迟滞使能配置

  ACMP_InitStruct->ACMP_FREN = DISABLE; //快速响应使能

  ACMP_InitStruct->ACMP_FS = DISABLE; //输出滤波使能配置

  ACMP_InitStruct->CMP_INTENMASK = DISABLE; //比较器连续比较中断使能屏蔽

  ACMP_InitStruct->CMP_SEQ_MODE = DISABLE; //连续模式使能

  ACMP_InitStruct->TRIG_MODE = CP_TIRG_INASOFT; //触发模式：软件或者外部硬件触发

  ACMP_InitStruct->CHNL_CNT_TIME = CHNL_CNT_TIME_64CLK; //比较器通道切换时钟周期选择

  ACMP_InitStruct->EXTSELECT = ENABLE_EXTSELG0; // Two sets of trigger sources enable control bits

  ACMP_InitStruct->EXTEN_Signal_andmode = DISABLE; // Trigger signal logic 'or' or 'and'

  ACMP_InitStruct->CP_EXTSP = CP_EXTSP_POS; //触发信号极性选择

  ACMP_InitStruct->SYN_MODE = CP_SYN_MODE; //外部触发同步或异步

  ACMP_InitStruct->TRIG_SOURCE = TRIG_TIM1_CC1; //触发源选择

  ACMP_InitStruct->TRIG_DELAY_TIME = TRIG_DELAY_TIME_128CLK; //外部触发延迟时钟

  ACMP_InitStruct->EXTEN_EDGE_MODE = CP_Edge_model; //外部触发信号方式

  ACMP_InitStruct->EXTEN_MODE_SEL = CP_EXTEN_TRIG_DIS; //外部触发模式选择
};

/*--------------------------------------------------------------------------------------------
 ACMP0  io_INPUT select
 In continuous mode, pseledata means  ACMP0_MUXCR Bits 23:16(P_AMXU_CFG[7:0]) munber;
 In discontinuous mode,pseledata means  ACMP0_MUXCR Bits 18:16(P_AMUX_CFG[2:0]) munber;

 nselectdata means  ACMP0_MUXCR Bits 25:24(N_AMUX_SEL) munber
  --------------------------------------------------------------------------------------------*/
void ACMP0_SEQ_INPUT_SELECT(FunctionalState NewState, uint8_t pseledata, uint8_t nselectdata)
{
  if (NewState != DISABLE) //连续模式
  {
    ACMP->ACMP0_MUXCR |= 0x00000002;
    ACMP->ACMP0_MUXCR |= (pseledata << 16) | (nselectdata << 24);
  }
  else //非连续模式
  {
    ACMP->ACMP0_MUXCR &= (~(0x00000002));
    ACMP->ACMP0_MUXCR |= (pseledata << 16) | (nselectdata << 24);
  }
}
/*--------------------------------------------------------------------------------------------
 ACMP1  io_INPUT select
 In continuous mode, pseledata means  ACMP0_MUXCR Bits 23:16(P_AMXU_CFG[7:0]) munber;
 In discontinuous mode,pseledata means  ACMP0_MUXCR Bits 18:16(P_AMUX_CFG[2:0]) munber;

 nselectdata means  ACMP0_MUXCR Bits 25:24(N_AMUX_SEL) munber
  --------------------------------------------------------------------------------------------*/
void ACMP1_SEQ_INPUT_SELECT(FunctionalState NewState, uint8_t pseledata, uint8_t nselectdata)
{
  if (NewState != DISABLE) //连续模式
  {
    ACMP->ACMP1_MUXCR |= 0x00000002;
    ACMP->ACMP1_MUXCR |= (pseledata << 16) | (nselectdata << 24);
  }
  else //非连续模式
  {
    ACMP->ACMP1_MUXCR &= (~(0x00000002));
    ACMP->ACMP1_MUXCR |= (pseledata << 16) | (nselectdata << 24);
  }
}
/*--------------------------------------------------------------------------------------------
 ACMP2  io_INPUT select
 In continuous mode, pseledata means  ACMP0_MUXCR Bits 23:16(P_AMXU_CFG[7:0]) munber;
 In discontinuous mode,pseledata means  ACMP0_MUXCR Bits 18:16(P_AMUX_CFG[2:0]) munber;

 nselectdata means  ACMP0_MUXCR Bits 25:24(N_AMUX_SEL) munber
  --------------------------------------------------------------------------------------------*/
void ACMP2_SEQ_INPUT_SELECT(FunctionalState NewState, uint8_t pseledata, uint8_t nselectdata)
{
  if (NewState != DISABLE) //连续模式
  {
    ACMP->ACMP2_MUXCR |= 0x00000002;
    ACMP->ACMP2_MUXCR |= (pseledata << 16) | (nselectdata << 24);
  }
  else //非连续模式
  {
    ACMP->ACMP2_MUXCR &= (~(0x00000002));
    ACMP->ACMP2_MUXCR |= (pseledata << 16) | (nselectdata << 24);
  }
}
/*--------------------------------------------------------------------------------------------
ACMP start(only soft trigger need  to configurate this)
  --------------------------------------------------------------------------------------------*/
void SATRT_OFACMP0()
{
  ACMP->ACMP0_MUXCR |= 0x00000001;
}
void SATRT_OFACMP1()
{
  ACMP->ACMP1_MUXCR |= 0x00000001;
}
void SATRT_OFACMP2()
{
  ACMP->ACMP2_MUXCR |= 0x00000001;
}

/*--------------------------------------------------------------------------------------------
get the results of continuous compare
  --------------------------------------------------------------------------------------------*/
uint32_t GET_ACMP0_SEQ_RESLUT(void)
{
  return ((ACMP->ACMP0_MUXCR & ANACTRL_ACMPX_MUXCR_CPOUT_PF_Msk) >> ANACTRL_ACMPX_MUXCR_CPOUT_PF_Pos);
}

uint32_t GET_ACMP1_SEQ_RESLUT(void)
{
  return ((ACMP->ACMP1_MUXCR & ANACTRL_ACMPX_MUXCR_CPOUT_PF_Msk) >> ANACTRL_ACMPX_MUXCR_CPOUT_PF_Pos);
}
uint32_t GET_ACMP2_SEQ_RESLUT(void)
{
  return ((ACMP->ACMP2_MUXCR & ANACTRL_ACMPX_MUXCR_CPOUT_PF_Msk) >> ANACTRL_ACMPX_MUXCR_CPOUT_PF_Pos);
}
/*--------------------------------------------------------------------------------------------
enable  ACMP0
  --------------------------------------------------------------------------------------------*/
void ACMP0_Cmd(FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    ACMP->ACMP0_CSR |= (0x00000001);
  }
  else
  {
    ACMP->ACMP0_CSR &= (~(0x00000001));
  }
}
/*--------------------------------------------------------------------------------------------
enable  ACMP1
  --------------------------------------------------------------------------------------------*/
void ACMP1_Cmd(FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    ACMP->ACMP1_CSR |= (0x00000001);
  }
  else
  {
    ACMP->ACMP1_CSR &= (~(0x00000001));
  }
}
/*--------------------------------------------------------------------------------------------
enable  ACMP2
  --------------------------------------------------------------------------------------------*/
void ACMP2_Cmd(FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    ACMP->ACMP2_CSR |= (0x00000001);
  }
  else
  {
    ACMP->ACMP2_CSR &= (~(0x00000001));
  }
}

/*--------------------------------------------------------------------------------------------
比较器快速响应使能
  --------------------------------------------------------------------------------------------*/
void ACMP0_FREN_Cmd(FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    ACMP->ACMP0_CSR |= (0x00000002);
  }
  else
  {
    ACMP->ACMP0_CSR &= (~(0x00000002));
  }
}

/*--------------------------------------------------------------------------------------------
比较器校准值 赋值   读取函数
  --------------------------------------------------------------------------------------------*/
void acmp0_trim(uint32_t trim)
{

  ANACTRL->ACMP0_CSR = (ANACTRL->ACMP0_CSR & ~ANACTRL_ACMPX_CSR_CP_PF_Msk) |
                       (trim << ANACTRL_ACMPX_CSR_CP_PF_Pos);
}

uint32_t get_acmp0_trim(void)
{
  return ((ANACTRL->ACMP0_CSR & ANACTRL_ACMPX_CSR_CP_PF_Msk) >> ANACTRL_ACMPX_CSR_CP_PF_Pos);
}

void acmp1_trim(uint32_t trim)
{

  ANACTRL->ACMP1_CSR = (ANACTRL->ACMP1_CSR & ~ANACTRL_ACMPX_CSR_CP_PF_Msk) |
                       (trim << ANACTRL_ACMPX_CSR_CP_PF_Pos);
}

uint32_t get_acmp1_trim(void)
{
  return ((ANACTRL->ACMP1_CSR & ANACTRL_ACMPX_CSR_CP_PF_Msk) >> ANACTRL_ACMPX_CSR_CP_PF_Pos);
}

void acmp2_trim(uint32_t trim)
{

  ANACTRL->ACMP2_CSR = (ANACTRL->ACMP2_CSR & ~ANACTRL_ACMPX_CSR_CP_PF_Msk) |
                       (trim << ANACTRL_ACMPX_CSR_CP_PF_Pos);
}

uint32_t get_acmp2_trim(void)
{
  return ((ANACTRL->ACMP2_CSR & ANACTRL_ACMPX_CSR_CP_PF_Msk) >> ANACTRL_ACMPX_CSR_CP_PF_Pos);
}

/*--------------------------------------------------------------------------------------------
比较器校准函数
  --------------------------------------------------------------------------------------------*/
void ACMP_TrimInit()
{
  uint8_t cptrim = 0x00;
  unsigned char tmpregs = 0;
  unsigned char flag = 0;

  tmpregs = ((ANACTRL->ACMP2_CSR) >> 28) & 0x01;

  if (tmpregs == 0)
  {
    while (flag != 1)
    {
      acmp2_trim(cptrim);
      //			delay(1000);
      tmpregs = ((ANACTRL->ACMP2_CSR) >> 28) & 0x01;
      if (tmpregs == 1)
      {
        flag = 1;
      }
      else if (cptrim == 0x1f)
      {
        flag = 1;
      }
      else
      {
        cptrim++;
      }
    }
  }
}

/***********************
 * Hallmid IP1 config
 * ***********************************************/
void Hallmid_IP1_Config(uint32_t HALL_IP1, FunctionalState NewState)
{
  if (NewState == ENABLE)
  {
    ANACTRL->HALL_CR_b.HALL_IP1_SEL = HALL_IP1;
    ANACTRL->HALL_CR_b.HALL_SW1 = 1;
  }
  else
  {
    ANACTRL->HALL_CR_b.HALL_SW1 = 0;
  }
} /***********************
   * Hallmid IP1 config
   * ***********************************************/
void Hallmid_IP2_Config(uint32_t HALL_IP2, FunctionalState NewState)
{
  if (NewState == ENABLE)
  {
    ANACTRL->HALL_CR_b.HALL_IP2_SEL = HALL_IP2;
    ANACTRL->HALL_CR_b.HALL_SW2 = 1;
  }
  else
  {
    ANACTRL->HALL_CR_b.HALL_SW2 = 0;
  }
} /***********************
   * Hallmid IP1 config
   * ***********************************************/
void Hallmid_IP3_Config(uint32_t HALL_IP3, FunctionalState NewState)
{
  if (NewState == ENABLE)
  {
    ANACTRL->HALL_CR_b.HALL_IP3_SEL = HALL_IP3;
    ANACTRL->HALL_CR_b.HALL_SW3 = 1;
  }
  else
  {
    ANACTRL->HALL_CR_b.HALL_SW3 = 0;
  }
}
/*--------------------------------------------------------------------------------------------
enable  Hallmid
  --------------------------------------------------------------------------------------------*/
void Hallmid_Cmd(FunctionalState NewState)
{
  if (NewState == ENABLE)
  {
    ANACTRL->HALL_CR_b.HALL_MID_EN = 1;
  }
  else
  {
    ANACTRL->HALL_CR_b.HALL_MID_EN = 0;
  }
}
