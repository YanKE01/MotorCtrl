/*
 * PLL.c
 *
 * Code generation for model "PLL".
 *
 * Model version              : 1.499
 * Simulink Coder version : 9.5 (R2021a) 14-Nov-2020
 * C source code generated on : Fri Jan 27 18:38:59 2023
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "PLL.h"
#include "PLL_private.h"

/* Block states (default storage) */
DW_PLL_T PLL_DW;

/* External inputs (root inport signals with default storage) */
ExtU_PLL_T PLL_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_PLL_T PLL_Y;

/* Real-time model */
static RT_MODEL_PLL_T PLL_M_;
RT_MODEL_PLL_T *const PLL_M = &PLL_M_;

/* Model step function */
void PLL_step(void)
{
  real_T rtb_Add;
  real_T rtb_Sum;

  /* Sum: '<S1>/Add' incorporates:
   *  DiscreteIntegrator: '<S1>/Discrete-Time Integrator'
   *  Inport: '<Root>/Ealpha'
   *  Inport: '<Root>/Ebeta'
   *  MATLAB Function: '<S1>/MATLAB Function'
   *  MATLAB Function: '<S1>/MATLAB Function1'
   *  Product: '<S1>/Product'
   *  Product: '<S1>/Product1'
   */
  rtb_Add = PLL_U.ebeta_hat * cos(PLL_DW.DiscreteTimeIntegrator_DSTATE) -
    PLL_U.ealpha_hat * sin(PLL_DW.DiscreteTimeIntegrator_DSTATE);

  /* Sum: '<S45>/Sum' incorporates:
   *  DiscreteIntegrator: '<S36>/Integrator'
   *  Gain: '<S41>/Proportional Gain'
   */
  rtb_Sum = PLL_P.PIDController_P * rtb_Add + PLL_DW.Integrator_DSTATE;

  /* Outport: '<Root>/Omega' */
  PLL_Y.Omega = rtb_Sum;

  /* Outport: '<Root>/theta' incorporates:
   *  DiscreteIntegrator: '<S1>/Discrete-Time Integrator'
   */
  PLL_Y.theta = PLL_DW.DiscreteTimeIntegrator_DSTATE;

  /* Update for DiscreteIntegrator: '<S1>/Discrete-Time Integrator' */
  PLL_DW.DiscreteTimeIntegrator_DSTATE += PLL_P.DiscreteTimeIntegrator_gainval *
    rtb_Sum;

  /* Update for DiscreteIntegrator: '<S36>/Integrator' incorporates:
   *  Gain: '<S33>/Integral Gain'
   */
  PLL_DW.Integrator_DSTATE += PLL_P.PIDController_I * rtb_Add *
    PLL_P.Integrator_gainval;

  /* Matfile logging */
  rt_UpdateTXYLogVars(PLL_M->rtwLogInfo, (&PLL_M->Timing.taskTime0));

  /* signal main to stop simulation */
  {                                    /* Sample time: [1.0E-5s, 0.0s] */
    if ((rtmGetTFinal(PLL_M)!=-1) &&
        !((rtmGetTFinal(PLL_M)-PLL_M->Timing.taskTime0) >
          PLL_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(PLL_M, "Simulation finished");
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
  if (!(++PLL_M->Timing.clockTick0)) {
    ++PLL_M->Timing.clockTickH0;
  }

  PLL_M->Timing.taskTime0 = PLL_M->Timing.clockTick0 * PLL_M->Timing.stepSize0 +
    PLL_M->Timing.clockTickH0 * PLL_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void PLL_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)PLL_M, 0,
                sizeof(RT_MODEL_PLL_T));
  rtmSetTFinal(PLL_M, 1.0);
  PLL_M->Timing.stepSize0 = 1.0E-5;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = (NULL);
    PLL_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(PLL_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(PLL_M->rtwLogInfo, (NULL));
    rtliSetLogT(PLL_M->rtwLogInfo, "tout");
    rtliSetLogX(PLL_M->rtwLogInfo, "");
    rtliSetLogXFinal(PLL_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(PLL_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(PLL_M->rtwLogInfo, 4);
    rtliSetLogMaxRows(PLL_M->rtwLogInfo, 0);
    rtliSetLogDecimation(PLL_M->rtwLogInfo, 1);
    rtliSetLogY(PLL_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(PLL_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(PLL_M->rtwLogInfo, (NULL));
  }

  /* states (dwork) */
  (void) memset((void *)&PLL_DW, 0,
                sizeof(DW_PLL_T));

  /* external inputs */
  (void)memset(&PLL_U, 0, sizeof(ExtU_PLL_T));

  /* external outputs */
  (void) memset((void *)&PLL_Y, 0,
                sizeof(ExtY_PLL_T));

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(PLL_M->rtwLogInfo, 0.0, rtmGetTFinal(PLL_M),
    PLL_M->Timing.stepSize0, (&rtmGetErrorStatus(PLL_M)));

  /* InitializeConditions for DiscreteIntegrator: '<S1>/Discrete-Time Integrator' */
  PLL_DW.DiscreteTimeIntegrator_DSTATE = PLL_P.DiscreteTimeIntegrator_IC;

  /* InitializeConditions for DiscreteIntegrator: '<S36>/Integrator' */
  PLL_DW.Integrator_DSTATE = PLL_P.PIDController_InitialConditionF;
}

/* Model terminate function */
void PLL_terminate(void)
{
  /* (no terminate code required) */
}
