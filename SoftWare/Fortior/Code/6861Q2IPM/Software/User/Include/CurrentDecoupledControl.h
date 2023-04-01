#ifndef __CURRENT_DECOUPLED_CONTROL_H_
#define __CURRENT_DECOUPLED_CONTROL_H_

#define CurrentDecoupledControlEnable           (0)

#define CURRENT_DECOUPLED_CONTROL_LD            (LD)
#define CURRENT_DECOUPLED_CONTROL_LQ            (LQ)
typedef struct
{    
    int16    Omega;
    int16    DCurrent;
    int16    QCurrent;
    int16    DcVoltage;
    int16    DDutyQ15;
    int16    QDutyQ15;
    int16    DCurrentDecoupledControlK;
    int16    QCurrentDecoupledControlK;
    int16    DVoltageComponent;
    int16    DVoltageComponentAbs;
    int16    QVoltageComponent; 
    int16    QVoltageComponentAbs; 
       
}CurrentDecoupledControlTypeDef;


extern CurrentDecoupledControlTypeDef xdata mcCurrentDecoupledControl;
extern void CurrentDecoupledControlFunction(void);
extern void CurrentDecoupledControlFunctionInit(float MotorLd , float MotorLq  , float VoltageBase , float CurrentBase , float OmegaRadSec);

#endif