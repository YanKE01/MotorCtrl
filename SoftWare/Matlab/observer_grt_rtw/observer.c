/*
 * observer.c
 *
 * Code generation for model "observer".
 *
 * Model version              : 1.424
 * Simulink Coder version : 9.5 (R2021a) 14-Nov-2020
 * C source code generated on : Fri Jan 27 12:28:46 2023
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "observer.h"
#include "observer_private.h"

/* Block states (default storage) */
DW_observer_T observer_DW;

/* External inputs (root inport signals with default storage) */
ExtU_observer_T observer_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_observer_T observer_Y;

/* Real-time model */
static RT_MODEL_observer_T observer_M_;
RT_MODEL_observer_T *const observer_M = &observer_M_;

/* Model step function */
void observer_step(void)
{
  real_T rtb_Delay1;
  real_T rtb_Delay3;
  real_T rtb_ealpha_hat;
  real_T rtb_ealpha_hat_tmp;
  real_T rtb_ebeta_hat;

  /* Delay: '<S1>/Delay1' */
  rtb_Delay1 = observer_DW.Delay1_DSTATE;

  /* Delay: '<S1>/Delay3' */
  rtb_Delay3 = observer_DW.Delay3_DSTATE;

  /* Gain: '<S1>/Gain5' incorporates:
   *  Gain: '<S1>/Gain12'
   */
  rtb_ebeta_hat = observer_P.G2 * observer_P.Ts;

  /* Gain: '<S1>/Gain6' incorporates:
   *  Gain: '<S1>/Gain13'
   *  Inport: '<Root>/omega'
   */
  rtb_ealpha_hat_tmp = observer_P.Ts * observer_U.omega;

  /* Sum: '<S1>/Add2' incorporates:
   *  Delay: '<S1>/Delay'
   *  Delay: '<S1>/Delay5'
   *  Gain: '<S1>/Gain5'
   *  Gain: '<S1>/Gain6'
   *  Product: '<S1>/Product'
   *  Sum: '<S1>/Add1'
   */
  rtb_ealpha_hat = (rtb_ebeta_hat * (observer_DW.Delay_DSTATE -
    observer_DW.Delay5_DSTATE) + rtb_Delay1) + rtb_ealpha_hat_tmp * rtb_Delay3;

  /* Outport: '<Root>/Ealpha^' */
  observer_Y.Ealpha = rtb_ealpha_hat;

  /* Sum: '<S1>/Add5' incorporates:
   *  Delay: '<S1>/Delay2'
   *  Delay: '<S1>/Delay7'
   *  Gain: '<S1>/Gain12'
   *  Product: '<S1>/Product1'
   *  Sum: '<S1>/Add4'
   */
  rtb_ebeta_hat = (rtb_ebeta_hat * (observer_DW.Delay2_DSTATE -
    observer_DW.Delay7_DSTATE) + rtb_Delay3) - rtb_ealpha_hat_tmp * rtb_Delay1;

  /* Outport: '<Root>/Ebeta^' */
  observer_Y.Ebeta = rtb_ebeta_hat;

  /* Update for Delay: '<S1>/Delay1' */
  observer_DW.Delay1_DSTATE = rtb_ealpha_hat;

  /* Gain: '<S1>/Gain3' incorporates:
   *  Gain: '<S1>/Gain11'
   *  Gain: '<S1>/Gain2'
   *  Gain: '<S1>/Gain9'
   */
  rtb_ealpha_hat = observer_P.Ts / observer_P.L;

  /* Gain: '<S1>/Gain4' incorporates:
   *  Gain: '<S1>/Gain10'
   */
  rtb_ealpha_hat_tmp = (1.0 - observer_P.Rs * observer_P.Ts / observer_P.L) +
    observer_P.G1 * observer_P.Ts;

  /* Update for Delay: '<S1>/Delay' incorporates:
   *  Delay: '<S1>/Delay4'
   *  Delay: '<S1>/Delay5'
   *  Gain: '<S1>/Gain'
   *  Gain: '<S1>/Gain1'
   *  Gain: '<S1>/Gain2'
   *  Gain: '<S1>/Gain3'
   *  Gain: '<S1>/Gain4'
   *  Sum: '<S1>/Add'
   */
  observer_DW.Delay_DSTATE = ((rtb_ealpha_hat_tmp * observer_DW.Delay_DSTATE -
    rtb_ealpha_hat * rtb_Delay1) + rtb_ealpha_hat * observer_DW.Delay4_DSTATE) -
    observer_P.G1 * observer_DW.Delay5_DSTATE * observer_P.Ts;

  /* Update for Delay: '<S1>/Delay5' incorporates:
   *  Inport: '<Root>/ialpha'
   */
  observer_DW.Delay5_DSTATE = observer_U.ialpha;

  /* Update for Delay: '<S1>/Delay3' */
  observer_DW.Delay3_DSTATE = rtb_ebeta_hat;

  /* Update for Delay: '<S1>/Delay2' incorporates:
   *  Delay: '<S1>/Delay6'
   *  Delay: '<S1>/Delay7'
   *  Gain: '<S1>/Gain10'
   *  Gain: '<S1>/Gain11'
   *  Gain: '<S1>/Gain7'
   *  Gain: '<S1>/Gain8'
   *  Gain: '<S1>/Gain9'
   *  Sum: '<S1>/Add3'
   */
  observer_DW.Delay2_DSTATE = ((rtb_ealpha_hat_tmp * observer_DW.Delay2_DSTATE -
    rtb_ealpha_hat * rtb_Delay3) + rtb_ealpha_hat * observer_DW.Delay6_DSTATE) -
    observer_P.G1 * observer_DW.Delay7_DSTATE * observer_P.Ts;

  /* Update for Delay: '<S1>/Delay7' incorporates:
   *  Inport: '<Root>/ibeta'
   */
  observer_DW.Delay7_DSTATE = observer_U.ibeta;

  /* Update for Delay: '<S1>/Delay4' incorporates:
   *  Inport: '<Root>/ualpha'
   */
  observer_DW.Delay4_DSTATE = observer_U.ualpha;

  /* Update for Delay: '<S1>/Delay6' incorporates:
   *  Inport: '<Root>/ubeta'
   */
  observer_DW.Delay6_DSTATE = observer_U.ubeta;

  /* Matfile logging */
  rt_UpdateTXYLogVars(observer_M->rtwLogInfo, (&observer_M->Timing.taskTime0));

  /* signal main to stop simulation */
  {                                    /* Sample time: [1.0E-5s, 0.0s] */
    if ((rtmGetTFinal(observer_M)!=-1) &&
        !((rtmGetTFinal(observer_M)-observer_M->Timing.taskTime0) >
          observer_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(observer_M, "Simulation finished");
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++observer_M->Timing.clockTick0)) {
    ++observer_M->Timing.clockTickH0;
  }

  observer_M->Timing.taskTime0 = observer_M->Timing.clockTick0 *
    observer_M->Timing.stepSize0 + observer_M->Timing.clockTickH0 *
    observer_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void observer_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)observer_M, 0,
                sizeof(RT_MODEL_observer_T));
  rtmSetTFinal(observer_M, 1.0);
  observer_M->Timing.stepSize0 = 1.0E-5;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = (NULL);
    observer_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(observer_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(observer_M->rtwLogInfo, (NULL));
    rtliSetLogT(observer_M->rtwLogInfo, "tout");
    rtliSetLogX(observer_M->rtwLogInfo, "");
    rtliSetLogXFinal(observer_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(observer_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(observer_M->rtwLogInfo, 4);
    rtliSetLogMaxRows(observer_M->rtwLogInfo, 0);
    rtliSetLogDecimation(observer_M->rtwLogInfo, 1);
    rtliSetLogY(observer_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(observer_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(observer_M->rtwLogInfo, (NULL));
  }

  /* states (dwork) */
  (void) memset((void *)&observer_DW, 0,
                sizeof(DW_observer_T));

  /* external inputs */
  (void)memset(&observer_U, 0, sizeof(ExtU_observer_T));

  /* external outputs */
  (void) memset((void *)&observer_Y, 0,
                sizeof(ExtY_observer_T));

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(observer_M->rtwLogInfo, 0.0, rtmGetTFinal
    (observer_M), observer_M->Timing.stepSize0, (&rtmGetErrorStatus(observer_M)));

  /* InitializeConditions for Delay: '<S1>/Delay1' */
  observer_DW.Delay1_DSTATE = observer_P.Delay1_InitialCondition;

  /* InitializeConditions for Delay: '<S1>/Delay' */
  observer_DW.Delay_DSTATE = observer_P.Delay_InitialCondition;

  /* InitializeConditions for Delay: '<S1>/Delay5' */
  observer_DW.Delay5_DSTATE = observer_P.Delay5_InitialCondition;

  /* InitializeConditions for Delay: '<S1>/Delay3' */
  observer_DW.Delay3_DSTATE = observer_P.Delay3_InitialCondition;

  /* InitializeConditions for Delay: '<S1>/Delay2' */
  observer_DW.Delay2_DSTATE = observer_P.Delay2_InitialCondition;

  /* InitializeConditions for Delay: '<S1>/Delay7' */
  observer_DW.Delay7_DSTATE = observer_P.Delay7_InitialCondition;

  /* InitializeConditions for Delay: '<S1>/Delay4' */
  observer_DW.Delay4_DSTATE = observer_P.Delay4_InitialCondition;

  /* InitializeConditions for Delay: '<S1>/Delay6' */
  observer_DW.Delay6_DSTATE = observer_P.Delay6_InitialCondition;
}

/* Model terminate function */
void observer_terminate(void)
{
  /* (no terminate code required) */
}
