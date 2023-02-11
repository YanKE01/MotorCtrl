/*
 * observer_data.c
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

/* Block parameters (default storage) */
P_observer_T observer_P = {
  /* Variable: G1
   * Referenced by:
   *   '<S1>/Gain'
   *   '<S1>/Gain10'
   *   '<S1>/Gain4'
   *   '<S1>/Gain7'
   */
  -4000.0,

  /* Variable: G2
   * Referenced by:
   *   '<S1>/Gain12'
   *   '<S1>/Gain5'
   */
  14000.0,

  /* Variable: L
   * Referenced by:
   *   '<S1>/Gain10'
   *   '<S1>/Gain11'
   *   '<S1>/Gain2'
   *   '<S1>/Gain3'
   *   '<S1>/Gain4'
   *   '<S1>/Gain9'
   */
  0.00395,

  /* Variable: Rs
   * Referenced by:
   *   '<S1>/Gain10'
   *   '<S1>/Gain4'
   */
  0.485,

  /* Variable: Ts
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
  1.0E-6,

  /* Expression: 0.0
   * Referenced by: '<S1>/Delay1'
   */
  0.0,

  /* Expression: 0.0
   * Referenced by: '<S1>/Delay'
   */
  0.0,

  /* Expression: 0.0
   * Referenced by: '<S1>/Delay5'
   */
  0.0,

  /* Expression: 0.0
   * Referenced by: '<S1>/Delay3'
   */
  0.0,

  /* Expression: 0.0
   * Referenced by: '<S1>/Delay2'
   */
  0.0,

  /* Expression: 0.0
   * Referenced by: '<S1>/Delay7'
   */
  0.0,

  /* Expression: 0.0
   * Referenced by: '<S1>/Delay4'
   */
  0.0,

  /* Expression: 0.0
   * Referenced by: '<S1>/Delay6'
   */
  0.0
};
