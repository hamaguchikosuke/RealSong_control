/*
 * f14tmp5_data.c
 *
 * Code generation for model "f14tmp5".
 *
 * Model version              : 1.0
 * Simulink Coder version : 8.3 (R2012b) 20-Jul-2012
 * C source code generated on : Mon Sep 16 12:49:21 2013
 *
 * Target selection: xpctarget.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->32-bit x86 compatible
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "f14tmp5.h"
#include "f14tmp5_private.h"

/* Block parameters (auto storage) */
Parameters_f14tmp5 f14tmp5_P = {
  -0.6385,                             /* Computed Parameter: TransferFcn2_A
                                        * Referenced by: '<S6>/Transfer Fcn.2'
                                        */
  1.0,                                 /* Computed Parameter: TransferFcn2_C
                                        * Referenced by: '<S6>/Transfer Fcn.2'
                                        */
  0.001450536698578474,                /* Expression: 1/Uo
                                        * Referenced by: '<S1>/Gain5'
                                        */
  -0.6571,                             /* Computed Parameter: TransferFcn1_A
                                        * Referenced by: '<S6>/Transfer Fcn.1'
                                        */
  1.0,                                 /* Computed Parameter: TransferFcn1_C
                                        * Referenced by: '<S6>/Transfer Fcn.1'
                                        */
  22.8,                                /* Expression: 22.8
                                        * Referenced by: '<S9>/Gain1'
                                        */
  689.4,                               /* Expression: Uo
                                        * Referenced by: '<S9>/Constant'
                                        */
  0.031055900621118009,                /* Expression: 1/g
                                        * Referenced by: '<S9>/Gain2'
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
                                        * Referenced by: '<S6>/Gain3'
                                        */
  -0.00592,                            /* Expression: Mw
                                        * Referenced by: '<S6>/Gain4'
                                        */
  -63.9979,                            /* Expression: Zd
                                        * Referenced by: '<S6>/Gain5'
                                        */
  -6.8847,                             /* Expression: Md
                                        * Referenced by: '<S6>/Gain6'
                                        */

  /*  Computed Parameter: Wgustmodel_A
   * Referenced by: '<S8>/W-gust model'
   */
  { -0.78901688496133815, -0.15563691118852338 },

  /*  Computed Parameter: Wgustmodel_C
   * Referenced by: '<S8>/W-gust model'
   */
  { 3.2636985073652349, 0.74337115819042854 },
  -0.6385,                             /* Expression: Zw
                                        * Referenced by: '<S1>/Gain'
                                        */
  -0.00592,                            /* Expression: Mw
                                        * Referenced by: '<S1>/Gain2'
                                        */
  -8.4553078435926761,                 /* Computed Parameter: Qgustmodel_A
                                        * Referenced by: '<S8>/Q-gust model'
                                        */
  -0.10355189850799512,                /* Computed Parameter: Qgustmodel_C
                                        * Referenced by: '<S8>/Q-gust model'
                                        */
  0.01224696964599171,                 /* Computed Parameter: Qgustmodel_D
                                        * Referenced by: '<S8>/Q-gust model'
                                        */
  -0.6571,                             /* Expression: Mq
                                        * Referenced by: '<S1>/Gain1'
                                        */
  -2.5258903763576663,                 /* Computed Parameter: AlphasensorLowpassFilter_A
                                        * Referenced by: '<S7>/Alpha-sensor Low-pass Filter'
                                        */
  2.5258903763576663,                  /* Computed Parameter: AlphasensorLowpassFilter_C
                                        * Referenced by: '<S7>/Alpha-sensor Low-pass Filter'
                                        */
  -10.0,                               /* Computed Parameter: StickPrefilter_A
                                        * Referenced by: '<S7>/Stick Prefilter'
                                        */
  10.0,                                /* Computed Parameter: StickPrefilter_C
                                        * Referenced by: '<S7>/Stick Prefilter'
                                        */
  -4.144,                              /* Computed Parameter: PitchRateLeadFilter_A
                                        * Referenced by: '<S7>/Pitch Rate Lead Filter'
                                        */
  -1.173,                              /* Computed Parameter: PitchRateLeadFilter_C
                                        * Referenced by: '<S7>/Pitch Rate Lead Filter'
                                        */
  1.0,                                 /* Computed Parameter: PitchRateLeadFilter_D
                                        * Referenced by: '<S7>/Pitch Rate Lead Filter'
                                        */
  0.8156,                              /* Expression: Kq
                                        * Referenced by: '<S7>/Gain2'
                                        */
  0.677,                               /* Expression: Ka
                                        * Referenced by: '<S7>/Gain3'
                                        */
  -1.746,                              /* Expression: Kf
                                        * Referenced by: '<S7>/Gain'
                                        */
  -0.0,                                /* Computed Parameter: Proportionalplusintegralcompens
                                        * Referenced by: '<S7>/Proportional plus integral compensator'
                                        */
  -3.864,                              /* Computed Parameter: Proportionalplusintegralcompe_i
                                        * Referenced by: '<S7>/Proportional plus integral compensator'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S10>/White Noise'
                                        */
  1.0,                                 /* Computed Parameter: WhiteNoise_StdDev
                                        * Referenced by: '<S10>/White Noise'
                                        */
  23341.0,                             /* Expression: seed
                                        * Referenced by: '<S10>/White Noise'
                                        */
  3.1622776601683791,                  /* Expression: [sqrt(Cov)]/[sqrt(Ts)]
                                        * Referenced by: '<S10>/Output'
                                        */
  -0.6385,                             /* Computed Parameter: TransferFcn2_A_j
                                        * Referenced by: '<S11>/Transfer Fcn.2'
                                        */
  1.0,                                 /* Computed Parameter: TransferFcn2_C_k
                                        * Referenced by: '<S11>/Transfer Fcn.2'
                                        */
  0.001450536698578474,                /* Expression: 1/Uo
                                        * Referenced by: '<S2>/Gain5'
                                        */
  -0.6571,                             /* Computed Parameter: TransferFcn1_A_n
                                        * Referenced by: '<S11>/Transfer Fcn.1'
                                        */
  1.0,                                 /* Computed Parameter: TransferFcn1_C_g
                                        * Referenced by: '<S11>/Transfer Fcn.1'
                                        */
  22.8,                                /* Expression: 22.8
                                        * Referenced by: '<S14>/Gain1'
                                        */
  689.4,                               /* Expression: Uo
                                        * Referenced by: '<S14>/Constant'
                                        */
  0.031055900621118009,                /* Expression: 1/g
                                        * Referenced by: '<S14>/Gain2'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S2>/Pilot'
                                        */
  0.079577471545947673,                /* Computed Parameter: Pilot_Frequency_d
                                        * Referenced by: '<S2>/Pilot'
                                        */
  -20.0,                               /* Computed Parameter: ActuatorModel_A_j
                                        * Referenced by: '<S2>/Actuator Model'
                                        */
  20.0,                                /* Computed Parameter: ActuatorModel_C_f
                                        * Referenced by: '<S2>/Actuator Model'
                                        */
  689.4,                               /* Expression: Uo
                                        * Referenced by: '<S11>/Gain3'
                                        */
  -0.00592,                            /* Expression: Mw
                                        * Referenced by: '<S11>/Gain4'
                                        */
  -63.9979,                            /* Expression: Zd
                                        * Referenced by: '<S11>/Gain5'
                                        */
  -6.8847,                             /* Expression: Md
                                        * Referenced by: '<S11>/Gain6'
                                        */

  /*  Computed Parameter: Wgustmodel_A_l
   * Referenced by: '<S13>/W-gust model'
   */
  { -0.78901688496133815, -0.15563691118852338 },

  /*  Computed Parameter: Wgustmodel_C_a
   * Referenced by: '<S13>/W-gust model'
   */
  { 3.2636985073652349, 0.74337115819042854 },
  -0.6385,                             /* Expression: Zw
                                        * Referenced by: '<S2>/Gain'
                                        */
  -0.00592,                            /* Expression: Mw
                                        * Referenced by: '<S2>/Gain2'
                                        */
  -8.4553078435926761,                 /* Computed Parameter: Qgustmodel_A_e
                                        * Referenced by: '<S13>/Q-gust model'
                                        */
  -0.10355189850799512,                /* Computed Parameter: Qgustmodel_C_p
                                        * Referenced by: '<S13>/Q-gust model'
                                        */
  0.01224696964599171,                 /* Computed Parameter: Qgustmodel_D_c
                                        * Referenced by: '<S13>/Q-gust model'
                                        */
  -0.6571,                             /* Expression: Mq
                                        * Referenced by: '<S2>/Gain1'
                                        */
  -2.5258903763576663,                 /* Computed Parameter: AlphasensorLowpassFilter_A_d
                                        * Referenced by: '<S12>/Alpha-sensor Low-pass Filter'
                                        */
  2.5258903763576663,                  /* Computed Parameter: AlphasensorLowpassFilter_C_g
                                        * Referenced by: '<S12>/Alpha-sensor Low-pass Filter'
                                        */
  -10.0,                               /* Computed Parameter: StickPrefilter_A_c
                                        * Referenced by: '<S12>/Stick Prefilter'
                                        */
  10.0,                                /* Computed Parameter: StickPrefilter_C_p
                                        * Referenced by: '<S12>/Stick Prefilter'
                                        */
  -4.144,                              /* Computed Parameter: PitchRateLeadFilter_A_c
                                        * Referenced by: '<S12>/Pitch Rate Lead Filter'
                                        */
  -1.173,                              /* Computed Parameter: PitchRateLeadFilter_C_l
                                        * Referenced by: '<S12>/Pitch Rate Lead Filter'
                                        */
  1.0,                                 /* Computed Parameter: PitchRateLeadFilter_D_f
                                        * Referenced by: '<S12>/Pitch Rate Lead Filter'
                                        */
  0.8156,                              /* Expression: Kq
                                        * Referenced by: '<S12>/Gain2'
                                        */
  0.677,                               /* Expression: Ka
                                        * Referenced by: '<S12>/Gain3'
                                        */
  -1.746,                              /* Expression: Kf
                                        * Referenced by: '<S12>/Gain'
                                        */
  -0.0,                                /* Computed Parameter: Proportionalplusintegralcompe_d
                                        * Referenced by: '<S12>/Proportional plus integral compensator'
                                        */
  -3.864,                              /* Computed Parameter: Proportionalplusintegralcomp_mx
                                        * Referenced by: '<S12>/Proportional plus integral compensator'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S15>/White Noise'
                                        */
  1.0,                                 /* Computed Parameter: WhiteNoise_StdDev_n
                                        * Referenced by: '<S15>/White Noise'
                                        */
  23341.0,                             /* Expression: seed
                                        * Referenced by: '<S15>/White Noise'
                                        */
  3.1622776601683791,                  /* Expression: [sqrt(Cov)]/[sqrt(Ts)]
                                        * Referenced by: '<S15>/Output'
                                        */
  -0.6385,                             /* Computed Parameter: TransferFcn2_A_l
                                        * Referenced by: '<S16>/Transfer Fcn.2'
                                        */
  1.0,                                 /* Computed Parameter: TransferFcn2_C_a
                                        * Referenced by: '<S16>/Transfer Fcn.2'
                                        */
  0.001450536698578474,                /* Expression: 1/Uo
                                        * Referenced by: '<S3>/Gain5'
                                        */
  -0.6571,                             /* Computed Parameter: TransferFcn1_A_d
                                        * Referenced by: '<S16>/Transfer Fcn.1'
                                        */
  1.0,                                 /* Computed Parameter: TransferFcn1_C_gb
                                        * Referenced by: '<S16>/Transfer Fcn.1'
                                        */
  22.8,                                /* Expression: 22.8
                                        * Referenced by: '<S19>/Gain1'
                                        */
  689.4,                               /* Expression: Uo
                                        * Referenced by: '<S19>/Constant'
                                        */
  0.031055900621118009,                /* Expression: 1/g
                                        * Referenced by: '<S19>/Gain2'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S3>/Pilot'
                                        */
  0.079577471545947673,                /* Computed Parameter: Pilot_Frequency_k
                                        * Referenced by: '<S3>/Pilot'
                                        */
  -20.0,                               /* Computed Parameter: ActuatorModel_A_g
                                        * Referenced by: '<S3>/Actuator Model'
                                        */
  20.0,                                /* Computed Parameter: ActuatorModel_C_b
                                        * Referenced by: '<S3>/Actuator Model'
                                        */
  689.4,                               /* Expression: Uo
                                        * Referenced by: '<S16>/Gain3'
                                        */
  -0.00592,                            /* Expression: Mw
                                        * Referenced by: '<S16>/Gain4'
                                        */
  -63.9979,                            /* Expression: Zd
                                        * Referenced by: '<S16>/Gain5'
                                        */
  -6.8847,                             /* Expression: Md
                                        * Referenced by: '<S16>/Gain6'
                                        */

  /*  Computed Parameter: Wgustmodel_A_m
   * Referenced by: '<S18>/W-gust model'
   */
  { -0.78901688496133815, -0.15563691118852338 },

  /*  Computed Parameter: Wgustmodel_C_m
   * Referenced by: '<S18>/W-gust model'
   */
  { 3.2636985073652349, 0.74337115819042854 },
  -0.6385,                             /* Expression: Zw
                                        * Referenced by: '<S3>/Gain'
                                        */
  -0.00592,                            /* Expression: Mw
                                        * Referenced by: '<S3>/Gain2'
                                        */
  -8.4553078435926761,                 /* Computed Parameter: Qgustmodel_A_b
                                        * Referenced by: '<S18>/Q-gust model'
                                        */
  -0.10355189850799512,                /* Computed Parameter: Qgustmodel_C_j
                                        * Referenced by: '<S18>/Q-gust model'
                                        */
  0.01224696964599171,                 /* Computed Parameter: Qgustmodel_D_i
                                        * Referenced by: '<S18>/Q-gust model'
                                        */
  -0.6571,                             /* Expression: Mq
                                        * Referenced by: '<S3>/Gain1'
                                        */
  -2.5258903763576663,                 /* Computed Parameter: AlphasensorLowpassFilter_A_c
                                        * Referenced by: '<S17>/Alpha-sensor Low-pass Filter'
                                        */
  2.5258903763576663,                  /* Computed Parameter: AlphasensorLowpassFilter_C_gf
                                        * Referenced by: '<S17>/Alpha-sensor Low-pass Filter'
                                        */
  -10.0,                               /* Computed Parameter: StickPrefilter_A_e
                                        * Referenced by: '<S17>/Stick Prefilter'
                                        */
  10.0,                                /* Computed Parameter: StickPrefilter_C_j
                                        * Referenced by: '<S17>/Stick Prefilter'
                                        */
  -4.144,                              /* Computed Parameter: PitchRateLeadFilter_A_i
                                        * Referenced by: '<S17>/Pitch Rate Lead Filter'
                                        */
  -1.173,                              /* Computed Parameter: PitchRateLeadFilter_C_k
                                        * Referenced by: '<S17>/Pitch Rate Lead Filter'
                                        */
  1.0,                                 /* Computed Parameter: PitchRateLeadFilter_D_ft
                                        * Referenced by: '<S17>/Pitch Rate Lead Filter'
                                        */
  0.8156,                              /* Expression: Kq
                                        * Referenced by: '<S17>/Gain2'
                                        */
  0.677,                               /* Expression: Ka
                                        * Referenced by: '<S17>/Gain3'
                                        */
  -1.746,                              /* Expression: Kf
                                        * Referenced by: '<S17>/Gain'
                                        */
  -0.0,                                /* Computed Parameter: Proportionalplusintegralcompe_h
                                        * Referenced by: '<S17>/Proportional plus integral compensator'
                                        */
  -3.864,                              /* Computed Parameter: Proportionalplusintegralcompe_l
                                        * Referenced by: '<S17>/Proportional plus integral compensator'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S20>/White Noise'
                                        */
  1.0,                                 /* Computed Parameter: WhiteNoise_StdDev_g
                                        * Referenced by: '<S20>/White Noise'
                                        */
  23341.0,                             /* Expression: seed
                                        * Referenced by: '<S20>/White Noise'
                                        */
  3.1622776601683791,                  /* Expression: [sqrt(Cov)]/[sqrt(Ts)]
                                        * Referenced by: '<S20>/Output'
                                        */
  -0.6385,                             /* Computed Parameter: TransferFcn2_A_jz
                                        * Referenced by: '<S21>/Transfer Fcn.2'
                                        */
  1.0,                                 /* Computed Parameter: TransferFcn2_C_l
                                        * Referenced by: '<S21>/Transfer Fcn.2'
                                        */
  0.001450536698578474,                /* Expression: 1/Uo
                                        * Referenced by: '<S4>/Gain5'
                                        */
  -0.6571,                             /* Computed Parameter: TransferFcn1_A_a
                                        * Referenced by: '<S21>/Transfer Fcn.1'
                                        */
  1.0,                                 /* Computed Parameter: TransferFcn1_C_l
                                        * Referenced by: '<S21>/Transfer Fcn.1'
                                        */
  22.8,                                /* Expression: 22.8
                                        * Referenced by: '<S24>/Gain1'
                                        */
  689.4,                               /* Expression: Uo
                                        * Referenced by: '<S24>/Constant'
                                        */
  0.031055900621118009,                /* Expression: 1/g
                                        * Referenced by: '<S24>/Gain2'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S4>/Pilot'
                                        */
  0.079577471545947673,                /* Computed Parameter: Pilot_Frequency_i
                                        * Referenced by: '<S4>/Pilot'
                                        */
  -20.0,                               /* Computed Parameter: ActuatorModel_A_p
                                        * Referenced by: '<S4>/Actuator Model'
                                        */
  20.0,                                /* Computed Parameter: ActuatorModel_C_l
                                        * Referenced by: '<S4>/Actuator Model'
                                        */
  689.4,                               /* Expression: Uo
                                        * Referenced by: '<S21>/Gain3'
                                        */
  -0.00592,                            /* Expression: Mw
                                        * Referenced by: '<S21>/Gain4'
                                        */
  -63.9979,                            /* Expression: Zd
                                        * Referenced by: '<S21>/Gain5'
                                        */
  -6.8847,                             /* Expression: Md
                                        * Referenced by: '<S21>/Gain6'
                                        */

  /*  Computed Parameter: Wgustmodel_A_b
   * Referenced by: '<S23>/W-gust model'
   */
  { -0.78901688496133815, -0.15563691118852338 },

  /*  Computed Parameter: Wgustmodel_C_g
   * Referenced by: '<S23>/W-gust model'
   */
  { 3.2636985073652349, 0.74337115819042854 },
  -0.6385,                             /* Expression: Zw
                                        * Referenced by: '<S4>/Gain'
                                        */
  -0.00592,                            /* Expression: Mw
                                        * Referenced by: '<S4>/Gain2'
                                        */
  -8.4553078435926761,                 /* Computed Parameter: Qgustmodel_A_g
                                        * Referenced by: '<S23>/Q-gust model'
                                        */
  -0.10355189850799512,                /* Computed Parameter: Qgustmodel_C_a
                                        * Referenced by: '<S23>/Q-gust model'
                                        */
  0.01224696964599171,                 /* Computed Parameter: Qgustmodel_D_a
                                        * Referenced by: '<S23>/Q-gust model'
                                        */
  -0.6571,                             /* Expression: Mq
                                        * Referenced by: '<S4>/Gain1'
                                        */
  -2.5258903763576663,                 /* Computed Parameter: AlphasensorLowpassFilter_A_p
                                        * Referenced by: '<S22>/Alpha-sensor Low-pass Filter'
                                        */
  2.5258903763576663,                  /* Computed Parameter: AlphasensorLowpassFilter_C_m
                                        * Referenced by: '<S22>/Alpha-sensor Low-pass Filter'
                                        */
  -10.0,                               /* Computed Parameter: StickPrefilter_A_d
                                        * Referenced by: '<S22>/Stick Prefilter'
                                        */
  10.0,                                /* Computed Parameter: StickPrefilter_C_h
                                        * Referenced by: '<S22>/Stick Prefilter'
                                        */
  -4.144,                              /* Computed Parameter: PitchRateLeadFilter_A_p
                                        * Referenced by: '<S22>/Pitch Rate Lead Filter'
                                        */
  -1.173,                              /* Computed Parameter: PitchRateLeadFilter_C_b
                                        * Referenced by: '<S22>/Pitch Rate Lead Filter'
                                        */
  1.0,                                 /* Computed Parameter: PitchRateLeadFilter_D_b
                                        * Referenced by: '<S22>/Pitch Rate Lead Filter'
                                        */
  0.8156,                              /* Expression: Kq
                                        * Referenced by: '<S22>/Gain2'
                                        */
  0.677,                               /* Expression: Ka
                                        * Referenced by: '<S22>/Gain3'
                                        */
  -1.746,                              /* Expression: Kf
                                        * Referenced by: '<S22>/Gain'
                                        */
  -0.0,                                /* Computed Parameter: Proportionalplusintegralcomp_kg
                                        * Referenced by: '<S22>/Proportional plus integral compensator'
                                        */
  -3.864,                              /* Computed Parameter: Proportionalplusintegralcompe_j
                                        * Referenced by: '<S22>/Proportional plus integral compensator'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S25>/White Noise'
                                        */
  1.0,                                 /* Computed Parameter: WhiteNoise_StdDev_f
                                        * Referenced by: '<S25>/White Noise'
                                        */
  23341.0,                             /* Expression: seed
                                        * Referenced by: '<S25>/White Noise'
                                        */
  3.1622776601683791,                  /* Expression: [sqrt(Cov)]/[sqrt(Ts)]
                                        * Referenced by: '<S25>/Output'
                                        */
  -0.6385,                             /* Computed Parameter: TransferFcn2_A_c
                                        * Referenced by: '<S26>/Transfer Fcn.2'
                                        */
  1.0,                                 /* Computed Parameter: TransferFcn2_C_e
                                        * Referenced by: '<S26>/Transfer Fcn.2'
                                        */
  0.001450536698578474,                /* Expression: 1/Uo
                                        * Referenced by: '<S5>/Gain5'
                                        */
  -0.6571,                             /* Computed Parameter: TransferFcn1_A_o
                                        * Referenced by: '<S26>/Transfer Fcn.1'
                                        */
  1.0,                                 /* Computed Parameter: TransferFcn1_C_j
                                        * Referenced by: '<S26>/Transfer Fcn.1'
                                        */
  22.8,                                /* Expression: 22.8
                                        * Referenced by: '<S29>/Gain1'
                                        */
  689.4,                               /* Expression: Uo
                                        * Referenced by: '<S29>/Constant'
                                        */
  0.031055900621118009,                /* Expression: 1/g
                                        * Referenced by: '<S29>/Gain2'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S5>/Pilot'
                                        */
  0.079577471545947673,                /* Computed Parameter: Pilot_Frequency_a
                                        * Referenced by: '<S5>/Pilot'
                                        */
  -20.0,                               /* Computed Parameter: ActuatorModel_A_gl
                                        * Referenced by: '<S5>/Actuator Model'
                                        */
  20.0,                                /* Computed Parameter: ActuatorModel_C_a
                                        * Referenced by: '<S5>/Actuator Model'
                                        */
  689.4,                               /* Expression: Uo
                                        * Referenced by: '<S26>/Gain3'
                                        */
  -0.00592,                            /* Expression: Mw
                                        * Referenced by: '<S26>/Gain4'
                                        */
  -63.9979,                            /* Expression: Zd
                                        * Referenced by: '<S26>/Gain5'
                                        */
  -6.8847,                             /* Expression: Md
                                        * Referenced by: '<S26>/Gain6'
                                        */

  /*  Computed Parameter: Wgustmodel_A_lv
   * Referenced by: '<S28>/W-gust model'
   */
  { -0.78901688496133815, -0.15563691118852338 },

  /*  Computed Parameter: Wgustmodel_C_p
   * Referenced by: '<S28>/W-gust model'
   */
  { 3.2636985073652349, 0.74337115819042854 },
  -0.6385,                             /* Expression: Zw
                                        * Referenced by: '<S5>/Gain'
                                        */
  -0.00592,                            /* Expression: Mw
                                        * Referenced by: '<S5>/Gain2'
                                        */
  -8.4553078435926761,                 /* Computed Parameter: Qgustmodel_A_gl
                                        * Referenced by: '<S28>/Q-gust model'
                                        */
  -0.10355189850799512,                /* Computed Parameter: Qgustmodel_C_c
                                        * Referenced by: '<S28>/Q-gust model'
                                        */
  0.01224696964599171,                 /* Computed Parameter: Qgustmodel_D_l
                                        * Referenced by: '<S28>/Q-gust model'
                                        */
  -0.6571,                             /* Expression: Mq
                                        * Referenced by: '<S5>/Gain1'
                                        */
  -2.5258903763576663,                 /* Computed Parameter: AlphasensorLowpassFilter_A_a
                                        * Referenced by: '<S27>/Alpha-sensor Low-pass Filter'
                                        */
  2.5258903763576663,                  /* Computed Parameter: AlphasensorLowpassFilter_C_e
                                        * Referenced by: '<S27>/Alpha-sensor Low-pass Filter'
                                        */
  -10.0,                               /* Computed Parameter: StickPrefilter_A_ee
                                        * Referenced by: '<S27>/Stick Prefilter'
                                        */
  10.0,                                /* Computed Parameter: StickPrefilter_C_b
                                        * Referenced by: '<S27>/Stick Prefilter'
                                        */
  -4.144,                              /* Computed Parameter: PitchRateLeadFilter_A_m
                                        * Referenced by: '<S27>/Pitch Rate Lead Filter'
                                        */
  -1.173,                              /* Computed Parameter: PitchRateLeadFilter_C_a
                                        * Referenced by: '<S27>/Pitch Rate Lead Filter'
                                        */
  1.0,                                 /* Computed Parameter: PitchRateLeadFilter_D_a
                                        * Referenced by: '<S27>/Pitch Rate Lead Filter'
                                        */
  0.8156,                              /* Expression: Kq
                                        * Referenced by: '<S27>/Gain2'
                                        */
  0.677,                               /* Expression: Ka
                                        * Referenced by: '<S27>/Gain3'
                                        */
  -1.746,                              /* Expression: Kf
                                        * Referenced by: '<S27>/Gain'
                                        */
  -0.0,                                /* Computed Parameter: Proportionalplusintegralcomp_mw
                                        * Referenced by: '<S27>/Proportional plus integral compensator'
                                        */
  -3.864,                              /* Computed Parameter: Proportionalplusintegralcomp_jp
                                        * Referenced by: '<S27>/Proportional plus integral compensator'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S30>/White Noise'
                                        */
  1.0,                                 /* Computed Parameter: WhiteNoise_StdDev_k
                                        * Referenced by: '<S30>/White Noise'
                                        */
  23341.0,                             /* Expression: seed
                                        * Referenced by: '<S30>/White Noise'
                                        */
  3.1622776601683791                   /* Expression: [sqrt(Cov)]/[sqrt(Ts)]
                                        * Referenced by: '<S30>/Output'
                                        */
};
