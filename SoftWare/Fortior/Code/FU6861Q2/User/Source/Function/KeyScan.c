/**************************** (C) COPYRIGHT 2015 Fortiortech shenzhen *****************************
    File Name          : KeyScan.c
    Author             : Billy Long Fortiortech  Market Dept
    Version            : V1.0
    Date               : 01/07/2015
    Description        : This file contains key scan function used for Motor Control.
***************************************************************************************************
    All Rights Reserved
**************************************************************************************************/


/* Includes -------------------------------------------------------------------------------------*/
#include <FU68xx.h>
#include <Myproject.h>

/* Private variables ----------------------------------------------------------------------------*/
KeyScanParam_TypeDef  KS;


/*  -------------------------------------------------------------------------------------------------
    Function Name : void KeyInit(void)
    Description   : ����������ʼ��
    Input         : ��
    Output                :   ��
    -------------------------------------------------------------------------------------------------*/
void KeyInit(void)
{
    KS.Key0Value = 0;
    KS.Key0TempValue = 0;
    KS.FlagKey0Press = 0;
    KS.Key0PressCnt = 0;
    KS.Key0InitCnt = 0;
    KS.Key1Value = 0;
    KS.Key1TempValue = 0;
    KS.FlagKey1Press = 0;
    KS.Key1PressCnt = 0;
    KS.Key1InitCnt = 0;
}

/*  -------------------------------------------------------------------------------------------------
    Function Name : uint8_t KeyValue(void)
    Description   : ���ܺ�������ȡ����ֵ��ѡ�񷵻ؼ�λֵ���ǹܽŵ�ƽKeyValue
    Input         : ��
    Output                :   ��λֵ���߹ܽŵ�ƽKeyValue
    -------------------------------------------------------------------------------------------------*/
uint8_t KeyValue(void)
{
    /* Key0 Scan */
    if (Key0)
    {
        KS.Key0PressCnt ++;
        
        if (KS.Key0PressCnt >= KeyFilterTime)
        {
            KS.Key0PressCnt = KeyFilterTime;
            KS.Key0Value = 1;
            
            if (KS.FlagKey0Press == 1)
            {
                KS.FlagKey0Press = 0;
                return 0;
            }
        }
    }
    else
    {
        KS.Key0PressCnt --;
        
        if (KS.Key0PressCnt <= -KeyFilterTime)
        {
            KS.Key0PressCnt = -KeyFilterTime;
            KS.Key0Value = 0;
            KS.FlagKey0Press = 1;
        }
    }
    
    /* Key1 Scan */
    if (Key1)
    {
        KS.Key1PressCnt ++;
        
        if (KS.Key1PressCnt >= KeyFilterTime)
        {
            KS.Key1PressCnt = KeyFilterTime;
            KS.Key1Value = 1;
            
            if (KS.FlagKey1Press == 1)
            {
                KS.FlagKey1Press = 0;
                return 1;
            }
        }
    }
    else
    {
        KS.Key1PressCnt --;
        
        if (KS.Key1PressCnt <= -KeyFilterTime)
        {
            KS.Key1PressCnt = -KeyFilterTime;
            KS.Key1Value = 0;
            KS.FlagKey1Press = 1;
        }
    }
    
    return 255;
}

/*  -------------------------------------------------------------------------------------------------
    Function Name : void KeyScan(void)
    Description   : ���ܺ���������ɨ�裬�����������ݳ���������
    Input         : ��
    Output                :   ��
    -------------------------------------------------------------------------------------------------*/
void KeyScan(void)
{
    //  while(KS.Key0InitCnt <= 1000)
    //  {
    //      KS.Key0InitCnt ++;
    //      KeyValue();
    //      KS.Key0TempValue = KS.Key0Value;
    //      if((KS.Key0PressCnt == KeyFilterTime)||(KS.Key0PressCnt == -KeyFilterTime))
    //      {
    //          MC.FR = KS.Key0Value;
    //      }
    //  }
    
    //  KeyValue();
    //  if(KS.Key0TempValue != KS.Key0Value)
    //  {
    //      KS.Key0TempValue = KS.Key0Value;
    //      MC.FlagFR = 1;
    //  }
    switch (KeyValue())
    {
        case 0:
            MC.FlagFR = 1;
            break;
            
        case 1:
            break;
            
        default:
            break;
    }
}
