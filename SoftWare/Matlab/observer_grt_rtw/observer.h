/*
 * observer.h
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

#ifndef RTW_HEADER_observer_h_
#define RTW_HEADER_observer_h_
#include <string.h>
#include <float.h>
#include <stddef.h>
#ifndef observer_COMMON_INCLUDES_
#define observer_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rt_logging.h"
#endif                                 /* observer_COMMON_INCLUDES_ */

#include "observer_types.h"

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
  real_T Delay1_DSTATE;                /* '<S1>/Delay1' */
  real_T Delay_DSTATE;                 /* '<S1>/Delay' */
  real_T Delay5_DSTATE;                /* '<S1>/Delay5' */
  real_T Delay3_DSTATE;                /* '<S1>/Delay3' */
  real_T Delay2_DSTATE;                /* '<S1>/Delay2' */
  real_T Delay7_DSTATE;                /* '<S1>/Delay7' */
  real_T Delay4_DSTATE;                /* '<S1>/Delay4' */
  real_T Delay6_DSTATE;                /* '<S1>/Delay6' */
} DW_observer_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T ualpha;                       /* '<Root>/ualpha' */
  real_T ubeta;                        /* '<Root>/ubeta' */
  real_T ialpha;                       /* '<Root>/ialpha' */
  real_T ibeta;                        /* '<Root>/ibeta' */
  real_T omega;                        /* '<Root>/omega' */
} ExtU_observer_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T Ealpha;                       /* '<Root>/Ealpha^' */
  real_T Ebeta;                        /* '<Root>/Ebeta^' */
} ExtY_observer_T;

/* Parameters (default storage) */
struct P_observer_T_ {
  real_T G1;                           /* Variable: G1
                                        * Referenced by:
                                        *   '<S1>/Gain'
                                        *   '<S1>/Gain10'
                                        *   '<S1>/Gain4'
                                        *   '<S1>/Gain7'
                                        */
  real_T G2;                           /* Variable: G2
                                        * Referenced by:
                                        *   '<S1>/Gain12'
                                        *   '<S1>/Gain5'
                                        */
  real_T L;                            /* Variable: L
                                        * Referenced by:
                                        *   '<S1>/Gain10'
                                        *   '<S1>/Gain11'
                                        *   '<S1>/Gain2'
                                        *   '<S1>/Gain3'
                                        *   '<S1>/Gain4'
                                        *   '<S1>/Gain9'
                                        */
  real_T Rs;                           /* Variable: Rs
                                        * Referenced by:
                                        *   '<S1>/Gain10'
                                        *   '<S1>/Gain4'
                                        */
  real_T Ts;                           /* Variable: Ts
                                        * Referenced by:
                                        *   '<S1>/Gain1'
                                        *   '<S1>/Gain10'
                                        *   '<S1>/Gain11'
                                        *   '<S1>/Gain12'
                                        *   '<S1>/Gain13'
                                        *   '<S1>/Gain2'
                                        *   '<S1>/Gain3'
                                        *   '<S1>/Gain4'
                                        *   '<S1>/Gain5'
                                        *   '<S1>/Gain6'
                                        *   '<S1>/Gain8'
                                        *   '<S1>/Gain9'
                                        */
  real_T Delay1_InitialCondition;      /* Expression: 0.0
                                        * Referenced by: '<S1>/Delay1'
                                        */
  real_T Delay_InitialCondition;       /* Expression: 0.0
                                        * Referenced by: '<S1>/Delay'
                                        */
  real_T Delay5_InitialCondition;      /* Expression: 0.0
                                        * Referenced by: '<S1>/Delay5'
                                        */
  real_T Delay3_InitialCondition;      /* Expression: 0.0
                                        * Referenced by: '<S1>/Delay3'
                                        */
  real_T Delay2_InitialCondition;      /* Expression: 0.0
                                        * Referenced by: '<S1>/Delay2'
                                        */
  real_T Delay7_InitialCondition;      /* Expression: 0.0
                                        * Referenced by: '<S1>/Delay7'
                                        */
  real_T Delay4_InitialCondition;      /* Expression: 0.0
                                        * Referenced by: '<S1>/Delay4'
                                        */
  real_T Delay6_InitialCondition;      /* Expression: 0.0
                                        * Referenced by: '<S1>/Delay6'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_observer_T {
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
extern P_observer_T observer_P;

/* Block states (default storage) */
extern DW_observer_T observer_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_observer_T observer_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_observer_T observer_Y;

/* Model entry point functions */
extern void observer_initialize(void);
extern void observer_step(void);
extern void observer_terminate(void);

/* Real-time Model object */
extern RT_MODEL_observer_T *const observer_M;

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
 * hilite_system('pmsm_foc/observer')    - opens subsystem pmsm_foc/observer
 * hilite_system('pmsm_foc/observer/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'pmsm_foc'
 * '<S1>'   : 'pmsm_foc/observer'
 */
#endif                                 /* RTW_HEADER_observer_h_ */
