#ifndef __CRCCOMPUTE_H_
#define __CRCCOMPUTE_H_

typedef struct
{
    uint8 CRCValueHigh;
    uint8 CRCValueLow;
}CRCDealType; 

extern CRCDealType CRCDeal;
extern void CRC16Compute(uint8 CRCData[5]);

#endif