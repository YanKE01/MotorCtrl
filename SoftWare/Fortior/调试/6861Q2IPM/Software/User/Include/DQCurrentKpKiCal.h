#ifndef __DQCURRENTKPKI_H_
#define __DQCURRENTKPKI_H_

typedef struct
{    
    int16    DCurrentKpk;
    int16    QCurrentKpk;
    int16    DCurrentKik;
    int16    QCurrentKik;
    int16    KpwmkValue;
    
    int16    DCurrentKp;
    int16    QCurrentKp;
    int16    DCurrentKi;
    int16    QCurrentKi;
    int16    KpwmValue;
}DQCurrentPITypeDef;

#define DQCurrentKpKiCalEnable                  (0)

#define DQCURRENT_KP_KI_CAL_LD                  (LD)
#define DQCURRENT_KP_KI_CAL_LQ                  (LQ)

#define h (20.0)//ÖÐÆµ´ø¿í

extern DQCurrentPITypeDef  xdata DQCurrentPI;

extern void DQCurrentKpKiCalInit(float MotorLd , float MotorLq , float Ts , float VoltageBase , float CurrentBase , float hValue);
extern void DQCurrentKpKiCal(void);

#endif
