/*
 * PLL_data.c
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

/* Block parameters (default storage) */
P_PLL_T PLL_P = {
  /* Mask Parameter: PIDController_I
   * Referenced by: '<S33>/Integral Gain'
   */
  0.5,

  /* Mask Parameter: PIDController_InitialConditionF
   * Referenced by: '<S36>/Integrator'
   */
  0.0,

  /* Mask Parameter: PIDController_P
   * Referenced by: '<S41>/Proportional Gain'
   */
  35.0,

  /* Computed Parameter: DiscreteTimeIntegrator_gainval
   * Referenced by: '<S1>/Discrete-Time Integrator'
   */
  1.0E-5,

  /* Expression: 0
   * Referenced by: '<S1>/Discrete-Time Integrator'
   */
  0.0,

  /* Computed Parameter: Integrator_gainval
   * Referenced by: '<S36>/Integrator'
   */
  1.0E-5
};
