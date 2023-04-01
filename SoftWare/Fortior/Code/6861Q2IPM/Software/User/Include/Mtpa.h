#ifndef __Mtpa_H_
#define __Mtpa_H_

#define MTPAENABLE  (0)

#define MTPALD (LD)
#define MTPALQ (LQ)

#define MTPAPsi (Psi)

#define MotorStartMtpaTx  (-5000)

typedef struct
{
    int16 MtpaTheta;
    int16 MtpaThetaTemp;
    int16 MtpaSinThetaTemp;
    int16 MtpaCosTheta;
    int16 MtpaCosThetaAbs;
    int16 MtpaCosTheta_2;
    int16 MtpaCos2Theta;
    int16 MtpaCos2ThetaAbs;
   
    int16 MtpaTx;
    int16 MtpaIs;
    int16 MtpaIsk;
    
    int16 MtpaId;
    int16 MtpaIq;

    int16 Mtpak1;
    int16 Mtpak2;
    int16 Mtpak3;
}MCMtpa;
extern void MtpaControl(void);
extern void MtpaInit(float MtpaPsi , float MtpaLd , float MtpaLq , float CurrentBase , int16 StartMtpaTx);

extern MCMtpa              idata   Mtpa;

#endif
