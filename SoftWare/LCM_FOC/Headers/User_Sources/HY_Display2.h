#ifndef _HY_DISPLAY2_H
#define _HY_DISPLAY2_H

#include "lcm32f037.h"
#include "UserGlobals.h"

typedef enum TM1638_LED_INDEX
{
    POWER = 0,
    WELL,
    RPM,
    W,
    A,
    MPPT,
    TANK,
    V,
};



void HY_TM1638_Init();
void HY_TM1638_SetNumAuto(uint16_t num);
void HY_TM1638_SetLedState(uint8_t index, uint8_t status);
uint8_t HY_TM1638_ScanKey();
void HY_TM1638_Clear();
void HY_TM1638_SetFault(UGT_S_SYSTEMSTATE_STRU fault);

#endif
