/**
  ******************************************************************************
  * @file    lcm32f037_crc.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    2021-05-21
  * @brief   This file provides all the div emulation firmware functions.
  ******************************************************************************/
/**
  ******************************************************************************
  * @attention:
  * 
  * 
  * 
  * 
  ******************************************************************************/

#include "lcm32f037_crc.h"

//----------------------------------------------------------
//CRC
//----------------------------------------------------------

void Crc_initial_config_8( CRC_TypeDef * CRCx )
{
    CRCx->CRC_CTRL |=  CRC_GPS_CRC8 | CRC_BYTE_1 | CRC_CTRL_OVERFLOW_EN | CRC_CRTL_CORDIC_EN | CRC_RESET_CRC_EN | CRC_RESET_OFF | CRC_SWAP_00 ;
}

void Crc_initial_config_16a( CRC_TypeDef * CRCx )
{
    CRCx->CRC_CTRL =  CRC_GPS_CRC16a | CRC_LM_MSB | CRC_BYTE_2 | CRC_CTRL_OVERFLOW_EN | CRC_CRTL_CORDIC_EN | CRC_RESET_CRC_EN | CRC_RESET_OFF | CRC_SWAP_01 ;
}

void Crc_initial_config_16b( CRC_TypeDef * CRCx )
{
    CRCx->CRC_CTRL =  CRC_GPS_CRC16b | CRC_LM_MSB | CRC_BYTE_2 | CRC_CTRL_OVERFLOW_EN | CRC_CRTL_CORDIC_EN | CRC_RESET_CRC_EN | CRC_RESET_OFF | CRC_SWAP_01; 
}

void Crc_initial_config_32( CRC_TypeDef * CRCx )
{
    CRCx->CRC_CTRL =  CRC_GPS_CRC32 | CRC_LM_MSB | CRC_BYTE_4 | CRC_CTRL_OVERFLOW_EN | CRC_CRTL_CORDIC_EN | CRC_RESET_CRC_EN | CRC_RESET_OFF | CRC_SWAP_11;
}


void Crc_write_crc_data( CRC_TypeDef * CRCx, uint32_t crc_data )
{
    CRCx->CRC_DATA = crc_data;
}

uint32_t Crc_read_result( CRC_TypeDef * CRCx )
{
    uint32_t temp ;
    temp = CRCx->CRC_RESULT;
    return temp;
}

void Crc_write_result( CRC_TypeDef * CRCx )
{
    CRCx->CRC_RESULT = 0x0000;
}



