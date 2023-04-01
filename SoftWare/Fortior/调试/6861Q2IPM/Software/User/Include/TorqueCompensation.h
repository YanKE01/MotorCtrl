#ifndef __TorqueCompensation_H_
#define __TorqueCompensation_H_
typedef struct
{
    //uint16 MotorStartHoldTime;//回油时间结束才启动转矩补偿判断
    
    int16 MotorCurrentSpeed;
    int16 MotorTargetSpeed;
    int16 MotorDeltaSpeed;
    int16 MotorDeltaSpeedFlt;   
    int16 MotorDeltaSpeedFlt_LSB;

    int16 MachineDeltaTheta;
    int16 MachineTheta;

    int16 MotorDeltaSpeedAbs;
    int16 MotorDeltaSpeedAbsFlt;   
    int16 MotorDeltaSpeedAbsFlt_LSB;
    
    int16 TorqueCompensateEnterSpeedValue;//进入转矩补偿转速
    int16 TorqueCompensateExitSpeedValue;//进入转矩补偿转速
    
    int16 TorqueCompensateTheta;
    int16 TorqueCompensateInitTheta;
    int16 TorqueCompensateCosTheta; 
    int16 TorqueCompensateSinTheta; 
    int16 TorqueCompensateInitTheta1;
    
    int16 TorqueCompensateD;
    int16 TorqueCompensateDFlt;   //
    int16 TorqueCompensateDFlt_LSB;
    
    int16 TorqueCompensateC;
    int16 TorqueCompensateCFlt; //  
    int16 TorqueCompensateCFlt_LSB;
    
    int16 TorqueCompensateIqCurrentPeakValue;//补偿电流的幅值
    int16 TorqueCompensateIqCurrentValue;//补偿电流随机械周期实时变化的值

    int16 TorqueCompensateMechDeltaThetaKValue;
    int16 TorqueCompensateCLpfFcKValue;
    int16 TorqueCompensateDLpfFcKValue;
    int16 TorqueCompensatePeakKValue;
    int16 TorqueCompensatePeakKValueRef;
    int16 TorqueCompensatePeakKValueInc;
    uint8 TorqueCompensatePeakKValueIncCycle;
    uint8 TorqueCompensatePeakKValueIncCycleCnt;
    
    int16 TorqueCompensateDeltaOmegaAbsLpfFcKValue;
    int16 TorqueCompensateDeltaOmegaLpfFcKValue;
    
}MCTorqueCompensation;

typedef struct
{
    int16 Err;
    int16 Err_last;
    int16 Uk;
    uint16 Kp;
    uint16 Ki;
    int16     outMax;
    int16     outMin;  
}PI_Typedef;




#define TorqueCompensateMechDeltaThetaK             _Q15(TPWM_VALUE * MOTOR_SPEED_BASE  / 30.0)//转速标幺化后乘于该系数即可得到角度增量

#define TorqueCompensateDeltaOmegaLpfFc             (10.0)//HZ//100
#define TorqueCompensateDeltaOmegaLpfFc_K           _Q15(_2PI * TPWM_VALUE * TorqueCompensateDeltaOmegaLpfFc)

#define TorqueCompensateDeltaOmegaAbsLpfFc          (5.0)//HZ   2
#define TorqueCompensateDeltaOmegaAbsLpfFc_K        _Q15(_2PI * TPWM_VALUE * TorqueCompensateDeltaOmegaAbsLpfFc)

#define TorqueCompensateDLpfFc                      (100.0)//HZ1000  100
#define TorqueCompensateDLpfFc_K                    _Q15(_2PI * TPWM_VALUE * TorqueCompensateDLpfFc)

#define TorqueCompensateCLpfFc                      (5.0)//HZ   5.0
#define TorqueCompensateCLpfFc_K                    _Q15(_2PI * TPWM_VALUE * TorqueCompensateCLpfFc)

#define TorqueCompensatePeakKEnd                    _Q12(1.95)//1.5  //   1.1  1.3   1.25   1.95
#define TorqueCompensatePeakKStart                  _Q12(1.0)//1.2//0.8  1.0   1.2  0.8   1.0
#define TorqueCompensatePeakK_K                     _Q12((float)(TorqueCompensatePeakKEnd-TorqueCompensatePeakKStart)/(float)(OBS_K3T_SPEED_END-OBS_K3T_SPEED_START))

#define TorqueCompensateTheta_KP                    _Q12(8.0)//8.0   1.0   7.0
#define TorqueCompensateTheta_KI                    _Q15(0.9)//0.5   0.9   0.9

#define TorqueCompensateEnterSpeed                  S_Value(2200.0)//进入转矩补偿的转速阈值//2200
#define TorqueCompensateExitSpeed                   S_Value(2400.0)//退出转矩补偿的转速阈值//2400

#define TorqueCompensateDQCurrentKp                 _Q12(1.0)
#define TorqueCompensateDQCurrentKi                 _Q15(0.01)



extern MCTorqueCompensation            xdata   mcTorqueCompensation;
extern PI_Typedef                      xdata   mcTorqueCompensationThetaPI;
extern PI_Typedef xdata SpeedPI;
//extern void PI_Speed(PI_Typedef *PI);

extern void MCTorqueCompensationCodeInit(void);
extern void MCTorqueCompensationFunction(void);
extern void PI_Increment(PI_Typedef *PI);

#endif