/*
 * PLL.h
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

#ifndef RTW_HEADER_PLL_h_
#define RTW_HEADER_PLL_h_
#include <math.h>
#include <string.h>
#include <float.h>
#include <stddef.h>
#ifndef PLL_COMMON_INCLUDES_
#define PLL_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rt_logging.h"
#endif                                 /* PLL_COMMON_INCLUDES_ */

#include "PLL_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rt_nonfinite.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetRTWLogInfo
#define rtmGetRTWLogInfo(rtm)          ((rtm)->rtwLogInfo)
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   ((rtm)->Timing.taskTime0)
#endif

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                (&(rtm)->Timing.taskTime0)
#endif

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T DiscreteTimeIntegrator_DSTATE;/* '<S1>/Discrete-Time Integrator' */
  real_T Integrator_DSTATE;            /* '<S36>/Integrator' */
} DW_PLL_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T ealpha_hat;                   /* '<Root>/Ealpha' */
  real_T ebeta_hat;                    /* '<Root>/Ebeta' */
} ExtU_PLL_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T Omega;                        /* '<Root>/Omega' */
  real_T theta;                        /* '<Root>/theta' */
} ExtY_PLL_T;

/* Parameters (default storage) */
struct P_PLL_T_ {
  real_T PIDController_I;              /* Mask Parameter: PIDController_I
                                        * Referenced by: '<S33>/Integral Gain'
                                        */
  real_T PIDController_InitialConditionF;
                              /* Mask Parameter: PIDController_InitialConditionF
                               * Referenced by: '<S36>/Integrator'
                               */
  real_T PIDController_P;              /* Mask Parameter: PIDController_P
                                        * Referenced by: '<S41>/Proportional Gain'
                                        */
  real_T DiscreteTimeIntegrator_gainval;
                           /* Computed Parameter: DiscreteTimeIntegrator_gainval
                            * Referenced by: '<S1>/Discrete-Time Integrator'
                            */
  real_T DiscreteTimeIntegrator_IC;    /* Expression: 0
                                        * Referenced by: '<S1>/Discrete-Time Integrator'
                                        */
  real_T Integrator_gainval;           /* Computed Parameter: Integrator_gainval
                                        * Referenced by: '<S36>/Integrator'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_PLL_T {
  const char_T *errorStatus;
  RTWLogInfo *rtwLogInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    time_T taskTime0;
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    time_T tFinal;
    boolean_T stopRequestedFlag;
  } Timing;
};

/* Block parameters (default storage) */
extern P_PLL_T PLL_P;

/* Block states (default storage) */
extern DW_PLL_T PLL_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_PLL_T PLL_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_PLL_T PLL_Y;

/* Model entry point functions */
extern void PLL_initialize(void);
extern void PLL_step(void);
extern void PLL_terminate(void);

/* Real-time Model object */
extern RT_MODEL_PLL_T *const PLL_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('pmsm_foc/PLL')    - opens subsystem pmsm_foc/PLL
 * hilite_system('pmsm_foc/PLL/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'pmsm_foc'
 * '<S1>'   : 'pmsm_foc/PLL'
 * '<S2>'   : 'pmsm_foc/PLL/MATLAB Function'
 * '<S3>'   : 'pmsm_foc/PLL/MATLAB Function1'
 * '<S4>'   : 'pmsm_foc/PLL/PID Controller'
 * '<S5>'   : 'pmsm_foc/PLL/PID Controller/Anti-windup'
 * '<S6>'   : 'pmsm_foc/PLL/PID Controller/D Gain'
 * '<S7>'   : 'pmsm_foc/PLL/PID Controller/Filter'
 * '<S8>'   : 'pmsm_foc/PLL/PID Controller/Filter ICs'
 * '<S9>'   : 'pmsm_foc/PLL/PID Controller/I Gain'
 * '<S10>'  : 'pmsm_foc/PLL/PID Controller/Ideal P Gain'
 * '<S11>'  : 'pmsm_foc/PLL/PID Controller/Ideal P Gain Fdbk'
 * '<S12>'  : 'pmsm_foc/PLL/PID Controller/Integrator'
 * '<S13>'  : 'pmsm_foc/PLL/PID Controller/Integrator ICs'
 * '<S14>'  : 'pmsm_foc/PLL/PID Controller/N Copy'
 * '<S15>'  : 'pmsm_foc/PLL/PID Controller/N Gain'
 * '<S16>'  : 'pmsm_foc/PLL/PID Controller/P Copy'
 * '<S17>'  : 'pmsm_foc/PLL/PID Controller/Parallel P Gain'
 * '<S18>'  : 'pmsm_foc/PLL/PID Controller/Reset Signal'
 * '<S19>'  : 'pmsm_foc/PLL/PID Controller/Saturation'
 * '<S20>'  : 'pmsm_foc/PLL/PID Controller/Saturation Fdbk'
 * '<S21>'  : 'pmsm_foc/PLL/PID Controller/Sum'
 * '<S22>'  : 'pmsm_foc/PLL/PID Controller/Sum Fdbk'
 * '<S23>'  : 'pmsm_foc/PLL/PID Controller/Tracking Mode'
 * '<S24>'  : 'pmsm_foc/PLL/PID Controller/Tracking Mode Sum'
 * '<S25>'  : 'pmsm_foc/PLL/PID Controller/Tsamp - Integral'
 * '<S26>'  : 'pmsm_foc/PLL/PID Controller/Tsamp - Ngain'
 * '<S27>'  : 'pmsm_foc/PLL/PID Controller/postSat Signal'
 * '<S28>'  : 'pmsm_foc/PLL/PID Controller/preSat Signal'
 * '<S29>'  : 'pmsm_foc/PLL/PID Controller/Anti-windup/Passthrough'
 * '<S30>'  : 'pmsm_foc/PLL/PID Controller/D Gain/Disabled'
 * '<S31>'  : 'pmsm_foc/PLL/PID Controller/Filter/Disabled'
 * '<S32>'  : 'pmsm_foc/PLL/PID Controller/Filter ICs/Disabled'
 * '<S33>'  : 'pmsm_foc/PLL/PID Controller/I Gain/Internal Parameters'
 * '<S34>'  : 'pmsm_foc/PLL/PID Controller/Ideal P Gain/Passthrough'
 * '<S35>'  : 'pmsm_foc/PLL/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S36>'  : 'pmsm_foc/PLL/PID Controller/Integrator/Discrete'
 * '<S37>'  : 'pmsm_foc/PLL/PID Controller/Integrator ICs/Internal IC'
 * '<S38>'  : 'pmsm_foc/PLL/PID Controller/N Copy/Disabled wSignal Specification'
 * '<S39>'  : 'pmsm_foc/PLL/PID Controller/N Gain/Disabled'
 * '<S40>'  : 'pmsm_foc/PLL/PID Controller/P Copy/Disabled'
 * '<S41>'  : 'pmsm_foc/PLL/PID Controller/Parallel P Gain/Internal Parameters'
 * '<S42>'  : 'pmsm_foc/PLL/PID Controller/Reset Signal/Disabled'
 * '<S43>'  : 'pmsm_foc/PLL/PID Controller/Saturation/Passthrough'
 * '<S44>'  : 'pmsm_foc/PLL/PID Controller/Saturation Fdbk/Disabled'
 * '<S45>'  : 'pmsm_foc/PLL/PID Controller/Sum/Sum_PI'
 * '<S46>'  : 'pmsm_foc/PLL/PID Controller/Sum Fdbk/Disabled'
 * '<S47>'  : 'pmsm_foc/PLL/PID Controller/Tracking Mode/Disabled'
 * '<S48>'  : 'pmsm_foc/PLL/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S49>'  : 'pmsm_foc/PLL/PID Controller/Tsamp - Integral/Passthrough'
 * '<S50>'  : 'pmsm_foc/PLL/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S51>'  : 'pmsm_foc/PLL/PID Controller/postSat Signal/Forward_Path'
 * '<S52>'  : 'pmsm_foc/PLL/PID Controller/preSat Signal/Forward_Path'
 */
#endif                                 /* RTW_HEADER_PLL_h_ */
