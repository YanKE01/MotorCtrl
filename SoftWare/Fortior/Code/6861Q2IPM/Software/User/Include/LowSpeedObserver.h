#ifndef __LowSpeedObserver_H_
#define __LowSpeedObserver_H_


#define LowSpeedObserverEnable            (1)

#define LowSpeedObserverLD                (LD)
#define LowSpeedObserverLQ                (LQ)

#define LowSpeedObserverGain1            (1500.0)  //1500
#define LowSpeedObserverGain2             _Q12(1.8)//1.2 //0.75

#define LowSpeedObserverToAoObserverSpeed_Q15  _Q15(1200.0   / MOTOR_SPEED_BASE)

#define SMOThetaComp                               _Q15(26.33 / 180.0)


typedef struct
{
    int16 LowSpeedObserverEd;
    int16 LowSpeedObserverEdTemp;
    
    int16 LowSpeedObserverEq;
    
    int16 LowSpeedObserverUDcbus;

    int16 LowSpeedObserverVd;          	          // 
    int16 LowSpeedObserverVq;          	          //    

    int16 LowSpeedObserverUd;          	          // 
    int16 LowSpeedObserverUq;          	          //    

    int16 LowSpeedObserverOmega;
    int16 LowSpeedObserverOmegaFlt;    
    
    int16 LowSpeedObserverK1;
    int16 LowSpeedObserverK2;
    int16 LowSpeedObserverK3_D;
    int16 LowSpeedObserverK3_Q;
    int16 LowSpeedObserverK4;
    
    int16 LowSpeedObserverUd1;
    int16 LowSpeedObserverUd2;
    int16 LowSpeedObserverUd3Temp;
    int16 LowSpeedObserverUd3;
    
    int16 LowSpeedObserverUq1;
    int16 LowSpeedObserverUq2;
    int16 LowSpeedObserverUq3Temp;
    int16 LowSpeedObserverUq3;

    int16 LowSpeedObserverDeltaThetaK;

    int16 LowSpeedObserverGain;
    int16 LowSpeedObserverOmegaErr;
    int16 LowSpeedObserverOmegaDelta;
    int16 LowSpeedObserverDeltaTheta;
    int16 LowSpeedObserverTheta;
    
    uint8 LowSpeedObserverToAoObserverEnable;
    int16 LowSpeedObserverToAoObserverSpeed;
    int16 LowSpeedObserverToAoObserverFlag;

}MCLowSpeedObserver;
extern MCLowSpeedObserver              data   LowSpeedObserver;
extern void LowSpeedObserverInit(float MotorRs , float MotorLd , float MotorLq , float DcbusVoltageBase , float BemfVoltageBase , float CurrentBase , float OmegaRadSec ,  float Ts , short Gain1 , short Gain2);

extern void LowSpeedObserverFunction(void);


#endif
