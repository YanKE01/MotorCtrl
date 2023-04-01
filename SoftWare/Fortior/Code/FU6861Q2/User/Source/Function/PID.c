/**
 * @copyright (C) COPYRIGHT 2022 Fortiortech Shenzhen
 * @file      PID.c
 * @author    Fortiortech  Appliction Team
 * @since     Create:2021-05-14
 * @date      Last modify:2022-07-14
 * @brief     This file contains PID function used for Motor Control
 */
/* Includes -------------------------------------------------------------------------------------*/
#include <FU68xx_2.h>
#include <Myproject.h>

/* Private variables ----------------------------------------------------------------------------*/

//Ramp_TypeDef xdata SpeedRamp;
PID_TypeDef xdata SpeedPID;
PID_TypeDef xdata CurrentPID;


/**
 * @brief      速度PID参数初始化
 */
void SpeedPIDInit(void)
{
 
    SpeedPID.Kp = _Q12(0.7);
    SpeedPID.Ki = _Q12(0.01);
    SpeedPID.Err = 0;
    SpeedPID.Err_Last1 = 0;
    SpeedPID.Err_Err = 0;
    
    SpeedPID.Out = _Q15(0.99);
    SpeedPID.OutMax = _Q15(0.99);
    SpeedPID.OutMin = _Q15(0.0);
    
}


/**
 * @brief      电流PID参数初始化
 */
void CurrentPIDInit(void)
{
    CurrentPID.Kp = 0;
    CurrentPID.Ki = 0;
    CurrentPID.Err = 0;
    CurrentPID.Err_Last1 = 0;
    CurrentPID.Err_Err = 0;
    
    CurrentPID.Out = 0;
    CurrentPID.OutMax = 0;
    CurrentPID.OutMin = 0;
}

/** 
 * @brief        不带MDU的软件PI
 * @param[in]    PID
 * @param[in]    Ref
 * @param[in]    Cur
 * @return       PID运算结果
 */
int16 PIDControl(PID_TypeDef * PID, int16 Ref, int16 Cur)
{
    int32 Kp_Out, Ki_Out, PID_Out;
    
    /*PI运算时间67us*/
    if (!PID->Err)
    {
        PID->Err_Last1 = Ref - Cur;                                           // 初始化PID上次偏差
        PID->Err = Ref - Cur;                                                 // 初始化PID当前偏差
        PID->Err_Err = PID->Err - PID->Err_Last1;                             // 初始化PID上次偏差和上上次偏差之差
    }
    else
    {
        PID->Err_Last1 = PID->Err;                                            // 保存PID上次偏差
        PID->Err = Ref - Cur;                                                 // 计算PID当前偏差
        PID->Err_Err = PID->Err - PID->Err_Last1;                             // 计算PID上次偏差和上上次偏差之差
    }
    
    Kp_Out = ((int32)PID->Kp * (int32)PID->Err_Err) >> 12;
    Ki_Out = ((int32)PID->Ki * (int32)PID->Err) >> 12;
    PID_Out = PID->Out;
    PID_Out += Kp_Out + Ki_Out;
    
    if (PID_Out > PID->OutMax)
    {
        PID_Out = PID->OutMax;                                                 // PID最高输出
    }
    
    if (PID_Out < PID->OutMin)
    {
        PID_Out = PID->OutMin;                                                 // PID最低输出
    }
    
    PID->Out = PID_Out;
    return PID->Out;
}


/** 
 * @brief        带MDU的软件PI
 * @param[in]    PID
 * @param[in]    Ref
 * @param[in]    Cur
 * @return       PID运算结果
 */
int16 PID_Control(PID_TypeDef * PID, int16 Ref, int16 Cur)
{
    int32 xdata Kp_Out;
    int32 xdata Ki_Out;
    int32 xdata PID_Out;
    
    /*PI运算时间42us*/
    if (!PID->Err)
    {
        PID->Err_Last1 = Ref - Cur;                                           // 初始化PID上次偏差
        PID->Err = Ref - Cur;                                                 // 初始化PID当前偏差
        PID->Err_Err = PID->Err - PID->Err_Last1;                             // 初始化PID上次偏差和上上次偏差之差
    }
    else
    {
        PID->Err_Last1 = PID->Err;                                            // 保存PID上次偏差
        PID->Err = Ref - Cur;                                                 // 计算PID当前偏差
        PID->Err_Err = PID->Err - PID->Err_Last1;                             // 计算PID上次偏差和上上次偏差之差
    }
    
    MDU_MUL_IDATA_U32(PID->Kp, PID->Err_Err,&Kp_Out);
    MDU_MUL_IDATA_U32(PID->Ki, PID->Err,&Ki_Out);
    
    PID_Out = PID->Out;
    PID_Out += Kp_Out + Ki_Out;
    
    if (PID_Out > PID->OutMax)
    {
        PID_Out = PID->OutMax;                                                // PID最高输出
    }
    
    if (PID_Out < PID->OutMin)
    {
        PID_Out = PID->OutMin;                                                // PID最低输出
    }
    
    PID->Out = PID_Out;
    return PID->Out;
}


