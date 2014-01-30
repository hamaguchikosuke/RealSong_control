/*
 * f14tmp1_data.c
 *
 * Code generation for model "f14tmp1".
 *
 * Model version              : 1.0
 * Simulink Coder version : 8.3 (R2012b) 20-Jul-2012
 * C source code generated on : Mon Sep 16 12:48:49 2013
 *
 * Target selection: xpctarget.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->32-bit x86 compatible
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "f14tmp1.h"
#include "f14tmp1_private.h"

/* Block parameters (auto storage) */
Parameters_f14tmp1 f14tmp1_P = {
  -0.6385,                             /* Computed Parameter: TransferFcn2_A
                                        * Referenced by: '<S2>/Transfer Fcn.2'
                                        */
  1.0,                                 /* Computed Parameter: TransferFcn2_C
                                        * Referenced by: '<S2>/Transfer Fcn.2'
                                        */
  0.001450536698578474,                /* Expression: 1/Uo
                                        * Referenced by: '<S1>/Gain5'
                                        */
  -0.6571,                             /* Computed Parameter: TransferFcn1_A
                                        * Referenced by: '<S2>/Transfer Fcn.1'
                                        */
  1.0,                                 /* Computed Parameter: TransferFcn1_C
                                        * Referenced by: '<S2>/Transfer Fcn.1'
                                        */
  22.8,                                /* Expression: 22.8
                                        * Referenced by: '<S5>/Gain1'
                                        */
  689.4,                               /* Expression: Uo
                                        * Referenced by: '<S5>/Constant'
                                        */
  0.031055900621118009,                /* Expression: 1/g
                                        * Referenced by: '<S5>/Gain2'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S1>/Pilot'
                                        */
  0.079577471545947673,                /* Computed Parameter: Pilot_Frequency
                                        * Referenced by: '<S1>/Pilot'
                                        */
  -20.0,                               /* Computed Parameter: ActuatorModel_A
                                        * Referenced by: '<S1>/Actuator Model'
                                        */
  20.0,                                /* Computed Parameter: ActuatorModel_C
                                        * Referenced by: '<S1>/Actuator Model'
                                        */
  689.4,                               /* Expression: Uo
                                        * Referenced by: '<S2>/Gain3'
                                        */
  -0.00592,                            /* Expression: Mw
                                        * Referenced by: '<S2>/Gain4'
                                        */
  -63.9979,                            /* Expression: Zd
                                        * Referenced by: '<S2>/Gain5'
                                        */
  -6.8847,                             /* Expression: Md
                                        * Referenced by: '<S2>/Gain6'
                                        */

  /*  Computed Parameter: Wgustmodel_A
   * Referenced by: '<S4>/W-gust model'
   */
  { -0.78901688496133815, -0.15563691118852338 },

  /*  Computed Parameter: Wgustmodel_C
   * Referenced by: '<S4>/W-gust model'
   */
  { 3.2636985073652349, 0.74337115819042854 },
  -0.6385,                             /* Expression: Zw
                                        * Referenced by: '<S1>/Gain'
                                        */
  -0.00592,                            /* Expression: Mw
                                        * Referenced by: '<S1>/Gain2'
                                        */
  -8.4553078435926761,                 /* Computed Parameter: Qgustmodel_A
                                        * Referenced by: '<S4>/Q-gust model'
                                        */
  -0.10355189850799512,                /* Computed Parameter: Qgustmodel_C
                                        * Referenced by: '<S4>/Q-gust model'
                                        */
  0.01224696964599171,                 /* Computed Parameter: Qgustmodel_D
                                        * Referenced by: '<S4>/Q-gust model'
                                        */
  -0.6571,                             /* Expression: Mq
                                        * Referenced by: '<S1>/Gain1'
                                        */
  -2.5258903763576663,                 /* Computed Parameter: AlphasensorLowpassFilter_A
                                        * Referenced by: '<S3>/Alpha-sensor Low-pass Filter'
                                        */
  2.5258903763576663,                  /* Computed Parameter: AlphasensorLowpassFilter_C
                                        * Referenced by: '<S3>/Alpha-sensor Low-pass Filter'
                                        */
  -10.0,                               /* Computed Parameter: StickPrefilter_A
                                        * Referenced by: '<S3>/Stick Prefilter'
                                        */
  10.0,                                /* Computed Parameter: StickPrefilter_C
                                        * Referenced by: '<S3>/Stick Prefilter'
                                        */
  -4.144,                              /* Computed Parameter: PitchRateLeadFilter_A
                                        * Referenced by: '<S3>/Pitch Rate Lead Filter'
                                        */
  -1.173,                              /* Computed Parameter: PitchRateLeadFilter_C
                                        * Referenced by: '<S3>/Pitch Rate Lead Filter'
                                        */
  1.0,                                 /* Computed Parameter: PitchRateLeadFilter_D
                                        * Referenced by: '<S3>/Pitch Rate Lead Filter'
                                        */
  0.8156,                              /* Expression: Kq
                                        * Referenced by: '<S3>/Gain2'
                                        */
  0.677,                               /* Expression: Ka
                                        * Referenced by: '<S3>/Gain3'
                                        */
  -1.746,                              /* Expression: Kf
                                        * Referenced by: '<S3>/Gain'
                                        */
  -0.0,                                /* Computed Parameter: Proportionalplusintegralcompens
                                        * Referenced by: '<S3>/Proportional plus integral compensator'
                                        */
  -3.864,                              /* Computed Parameter: Proportionalplusintegralcompe_i
                                        * Referenced by: '<S3>/Proportional plus integral compensator'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S6>/White Noise'
                                        */
  1.0,                                 /* Computed Parameter: WhiteNoise_StdDev
                                        * Referenced by: '<S6>/White Noise'
                                        */
  23341.0,                             /* Expression: seed
                                        * Referenced by: '<S6>/White Noise'
                                        */
  3.1622776601683791                   /* Expression: [sqrt(Cov)]/[sqrt(Ts)]
                                        * Referenced by: '<S6>/Output'
                                        */
};
