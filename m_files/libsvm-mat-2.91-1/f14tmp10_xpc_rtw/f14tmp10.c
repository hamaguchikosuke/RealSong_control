/*
 * f14tmp10.c
 *
 * Code generation for model "f14tmp10".
 *
 * Model version              : 1.0
 * Simulink Coder version : 8.3 (R2012b) 20-Jul-2012
 * C source code generated on : Mon Sep 16 12:50:01 2013
 *
 * Target selection: xpctarget.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->32-bit x86 compatible
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "rt_logging_mmi.h"
#include "f14tmp10_capi.h"
#include "f14tmp10.h"
#include "f14tmp10_private.h"

/* Block signals (auto storage) */
BlockIO_f14tmp10 f14tmp10_B;

/* Continuous states */
ContinuousStates_f14tmp10 f14tmp10_X;

/* Block states (auto storage) */
D_Work_f14tmp10 f14tmp10_DWork;

/* Real-time model */
rtModel_f14tmp10 f14tmp10_rtM_;
rtModel_f14tmp10 *const f14tmp10_rtM = &f14tmp10_rtM_;
static void rate_scheduler(void);

/*
 *   This function updates active task flag for each subrate.
 * The function is called at model base rate, hence the
 * generated code self-manages all its subrates.
 */
static void rate_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (f14tmp10_rtM->Timing.TaskCounters.TID[2])++;
  if ((f14tmp10_rtM->Timing.TaskCounters.TID[2]) > 9) {/* Sample time: [0.1s, 0.0s] */
    f14tmp10_rtM->Timing.TaskCounters.TID[2] = 0;
  }

  f14tmp10_rtM->Timing.sampleHits[2] = (f14tmp10_rtM->Timing.TaskCounters.TID[2]
    == 0);
}

/*
 * This function updates continuous states using the ODE4 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE4_IntgData *id = (ODE4_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T *f3 = id->f[3];
  real_T temp;
  int_T i;
  int_T nXc = 100;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  f14tmp10_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  f14tmp10_output();
  f14tmp10_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  f14tmp10_output();
  f14tmp10_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  f14tmp10_output();
  f14tmp10_derivatives();

  /* tnew = t + h
     ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

real_T rt_urand_Upu32_Yd_f_pw_snf(uint32_T *u)
{
  uint32_T lo;
  uint32_T hi;

  /* Uniform random number generator (random number between 0 and 1)

     #define IA      16807                      magic multiplier = 7^5
     #define IM      2147483647                 modulus = 2^31-1
     #define IQ      127773                     IM div IA
     #define IR      2836                       IM modulo IA
     #define S       4.656612875245797e-10      reciprocal of 2^31-1
     test = IA * (seed % IQ) - IR * (seed/IQ)
     seed = test < 0 ? (test + IM) : test
     return (seed*S)
   */
  lo = *u % 127773U * 16807U;
  hi = *u / 127773U * 2836U;
  if (lo < hi) {
    *u = 2147483647U - (hi - lo);
  } else {
    *u = lo - hi;
  }

  return (real_T)*u * 4.6566128752457969E-10;
}

real_T rt_nrand_Upu32_Yd_f_pw_snf(uint32_T *u)
{
  real_T sr;
  real_T si;

  /* Normal (Gaussian) random number generator */
  do {
    sr = 2.0 * rt_urand_Upu32_Yd_f_pw_snf(u) - 1.0;
    si = 2.0 * rt_urand_Upu32_Yd_f_pw_snf(u) - 1.0;
    si = sr * sr + si * si;
  } while (si > 1.0);

  return sqrt(-2.0 * log(si) / si) * sr;
}

/* Model output function */
void f14tmp10_output(void)
{
  real_T temp;
  if (rtmIsMajorTimeStep(f14tmp10_rtM)) {
    /* set solver stop time */
    if (!(f14tmp10_rtM->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&f14tmp10_rtM->solverInfo,
                            ((f14tmp10_rtM->Timing.clockTickH0 + 1) *
        f14tmp10_rtM->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&f14tmp10_rtM->solverInfo,
                            ((f14tmp10_rtM->Timing.clockTick0 + 1) *
        f14tmp10_rtM->Timing.stepSize0 + f14tmp10_rtM->Timing.clockTickH0 *
        f14tmp10_rtM->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(f14tmp10_rtM)) {
    f14tmp10_rtM->Timing.t[0] = rtsiGetT(&f14tmp10_rtM->solverInfo);
  }

  /* TransferFcn: '<S11>/Transfer Fcn.2' */
  f14tmp10_B.TransferFcn2 = f14tmp10_P.TransferFcn2_C*
    f14tmp10_X.TransferFcn2_CSTATE;

  /* Gain: '<S1>/Gain5' */
  f14tmp10_B.Gain5 = f14tmp10_P.Gain5_Gain * f14tmp10_B.TransferFcn2;
  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* Derivative: '<S14>/Derivative' */
  {
    real_T t = f14tmp10_rtM->Timing.t[0];
    real_T timeStampA = f14tmp10_DWork.Derivative_RWORK.TimeStampA;
    real_T timeStampB = f14tmp10_DWork.Derivative_RWORK.TimeStampB;
    real_T *lastU = &f14tmp10_DWork.Derivative_RWORK.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp10_B.Derivative = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp10_DWork.Derivative_RWORK.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp10_DWork.Derivative_RWORK.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp10_B.Derivative = (f14tmp10_B.TransferFcn2 - *lastU++) / deltaT;
    }
  }

  /* TransferFcn: '<S11>/Transfer Fcn.1' */
  f14tmp10_B.TransferFcn1 = f14tmp10_P.TransferFcn1_C*
    f14tmp10_X.TransferFcn1_CSTATE;

  /* Derivative: '<S14>/Derivative1' */
  {
    real_T t = f14tmp10_rtM->Timing.t[0];
    real_T timeStampA = f14tmp10_DWork.Derivative1_RWORK.TimeStampA;
    real_T timeStampB = f14tmp10_DWork.Derivative1_RWORK.TimeStampB;
    real_T *lastU = &f14tmp10_DWork.Derivative1_RWORK.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp10_B.Derivative1 = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp10_DWork.Derivative1_RWORK.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp10_DWork.Derivative1_RWORK.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp10_B.Derivative1 = (f14tmp10_B.TransferFcn1 - *lastU++) / deltaT;
    }
  }

  /* Gain: '<S14>/Gain1' */
  f14tmp10_B.Gain1 = f14tmp10_P.Gain1_Gain * f14tmp10_B.Derivative1;

  /* Product: '<S14>/Product' incorporates:
   *  Constant: '<S14>/Constant'
   */
  f14tmp10_B.Product = f14tmp10_B.TransferFcn1 * f14tmp10_P.Constant_Value;

  /* Sum: '<S14>/Sum1' */
  f14tmp10_B.Sum1 = (f14tmp10_B.Gain1 - f14tmp10_B.Derivative) +
    f14tmp10_B.Product;

  /* Gain: '<S14>/Gain2' */
  f14tmp10_B.Gain2 = f14tmp10_P.Gain2_Gain * f14tmp10_B.Sum1;
  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* SignalGenerator: '<S1>/Pilot' */
  temp = f14tmp10_P.Pilot_Frequency * f14tmp10_rtM->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    f14tmp10_B.Pilot = f14tmp10_P.Pilot_Amplitude;
  } else {
    f14tmp10_B.Pilot = -f14tmp10_P.Pilot_Amplitude;
  }

  /* End of SignalGenerator: '<S1>/Pilot' */

  /* Sum: '<S1>/Sum1' */
  f14tmp10_B.Sum1_k = f14tmp10_B.Pilot + 0.0;
  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* TransferFcn: '<S1>/Actuator Model' */
  f14tmp10_B.ActuatorModel = f14tmp10_P.ActuatorModel_C*
    f14tmp10_X.ActuatorModel_CSTATE;

  /* Gain: '<S11>/Gain3' */
  f14tmp10_B.Gain3 = f14tmp10_P.Gain3_Gain * f14tmp10_B.TransferFcn1;

  /* Gain: '<S11>/Gain4' */
  f14tmp10_B.Gain4 = f14tmp10_P.Gain4_Gain * f14tmp10_B.TransferFcn2;

  /* Gain: '<S11>/Gain5' */
  f14tmp10_B.Gain5_b = f14tmp10_P.Gain5_Gain_j * f14tmp10_B.ActuatorModel;

  /* Gain: '<S11>/Gain6' */
  f14tmp10_B.Gain6 = f14tmp10_P.Gain6_Gain * f14tmp10_B.ActuatorModel;

  /* TransferFcn: '<S13>/W-gust model' */
  f14tmp10_B.Wgustmodel = f14tmp10_P.Wgustmodel_C[0]*
    f14tmp10_X.Wgustmodel_CSTATE[0] + f14tmp10_P.Wgustmodel_C[1]*
    f14tmp10_X.Wgustmodel_CSTATE[1];

  /* Gain: '<S1>/Gain' */
  f14tmp10_B.Gain = f14tmp10_P.Gain_Gain * f14tmp10_B.Wgustmodel;

  /* Sum: '<S11>/Sum1' */
  f14tmp10_B.Sum1_o = (f14tmp10_B.Gain5_b - f14tmp10_B.Gain) + f14tmp10_B.Gain3;

  /* Gain: '<S1>/Gain2' */
  f14tmp10_B.Gain2_f = f14tmp10_P.Gain2_Gain_p * f14tmp10_B.Wgustmodel;

  /* TransferFcn: '<S13>/Q-gust model' */
  f14tmp10_B.Qgustmodel = f14tmp10_P.Qgustmodel_D*f14tmp10_B.Wgustmodel;
  f14tmp10_B.Qgustmodel += f14tmp10_P.Qgustmodel_C*f14tmp10_X.Qgustmodel_CSTATE;

  /* Gain: '<S1>/Gain1' */
  f14tmp10_B.Gain1_h = f14tmp10_P.Gain1_Gain_h * f14tmp10_B.Qgustmodel;

  /* Sum: '<S1>/Sum' */
  f14tmp10_B.Sum = f14tmp10_B.Gain2_f + f14tmp10_B.Gain1_h;

  /* Sum: '<S11>/Sum2' */
  f14tmp10_B.Sum2 = (f14tmp10_B.Gain4 - f14tmp10_B.Sum) + f14tmp10_B.Gain6;

  /* TransferFcn: '<S12>/Alpha-sensor Low-pass Filter' */
  f14tmp10_B.AlphasensorLowpassFilter = f14tmp10_P.AlphasensorLowpassFilter_C*
    f14tmp10_X.AlphasensorLowpassFilter_CSTATE;

  /* TransferFcn: '<S12>/Stick Prefilter' */
  f14tmp10_B.StickPrefilter = f14tmp10_P.StickPrefilter_C*
    f14tmp10_X.StickPrefilter_CSTATE;

  /* TransferFcn: '<S12>/Pitch Rate Lead Filter' */
  f14tmp10_B.PitchRateLeadFilter = f14tmp10_P.PitchRateLeadFilter_D*
    f14tmp10_B.TransferFcn1;
  f14tmp10_B.PitchRateLeadFilter += f14tmp10_P.PitchRateLeadFilter_C*
    f14tmp10_X.PitchRateLeadFilter_CSTATE;

  /* Gain: '<S12>/Gain2' */
  f14tmp10_B.Gain2_e = f14tmp10_P.Gain2_Gain_k * f14tmp10_B.PitchRateLeadFilter;

  /* Gain: '<S12>/Gain3' */
  f14tmp10_B.Gain3_g = f14tmp10_P.Gain3_Gain_i *
    f14tmp10_B.AlphasensorLowpassFilter;

  /* Sum: '<S12>/Sum1' */
  f14tmp10_B.Sum1_d = f14tmp10_B.Gain2_e + f14tmp10_B.Gain3_g;

  /* Sum: '<S12>/Sum2' */
  f14tmp10_B.Sum2_f = f14tmp10_B.StickPrefilter - f14tmp10_B.Sum1_d;

  /* Gain: '<S12>/Gain' */
  f14tmp10_B.Gain_d = f14tmp10_P.Gain_Gain_k * f14tmp10_B.Sum2_f;

  /* TransferFcn: '<S12>/Proportional plus integral compensator' */
  f14tmp10_B.Proportionalplusintegralcompens =
    f14tmp10_P.Proportionalplusintegralcompe_i*
    f14tmp10_X.Proportionalplusintegralcompens;

  /* Sum: '<S12>/Sum' */
  f14tmp10_B.Sum_n = f14tmp10_B.Gain_d +
    f14tmp10_B.Proportionalplusintegralcompens;
  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* RandomNumber: '<S15>/White Noise' */
    f14tmp10_B.WhiteNoise = f14tmp10_DWork.NextOutput;

    /* Gain: '<S15>/Output' */
    f14tmp10_B.Output = f14tmp10_P.Output_Gain * f14tmp10_B.WhiteNoise;
  }

  /* TransferFcn: '<S16>/Transfer Fcn.2' */
  f14tmp10_B.TransferFcn2_b = f14tmp10_P.TransferFcn2_C_k*
    f14tmp10_X.TransferFcn2_CSTATE_h;

  /* Gain: '<S2>/Gain5' */
  f14tmp10_B.Gain5_h = f14tmp10_P.Gain5_Gain_o * f14tmp10_B.TransferFcn2_b;
  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* Derivative: '<S19>/Derivative' */
  {
    real_T t = f14tmp10_rtM->Timing.t[0];
    real_T timeStampA = f14tmp10_DWork.Derivative_RWORK_f.TimeStampA;
    real_T timeStampB = f14tmp10_DWork.Derivative_RWORK_f.TimeStampB;
    real_T *lastU = &f14tmp10_DWork.Derivative_RWORK_f.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp10_B.Derivative_k = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp10_DWork.Derivative_RWORK_f.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp10_DWork.Derivative_RWORK_f.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp10_B.Derivative_k = (f14tmp10_B.TransferFcn2_b - *lastU++) / deltaT;
    }
  }

  /* TransferFcn: '<S16>/Transfer Fcn.1' */
  f14tmp10_B.TransferFcn1_a = f14tmp10_P.TransferFcn1_C_g*
    f14tmp10_X.TransferFcn1_CSTATE_p;

  /* Derivative: '<S19>/Derivative1' */
  {
    real_T t = f14tmp10_rtM->Timing.t[0];
    real_T timeStampA = f14tmp10_DWork.Derivative1_RWORK_o.TimeStampA;
    real_T timeStampB = f14tmp10_DWork.Derivative1_RWORK_o.TimeStampB;
    real_T *lastU = &f14tmp10_DWork.Derivative1_RWORK_o.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp10_B.Derivative1_a = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp10_DWork.Derivative1_RWORK_o.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp10_DWork.Derivative1_RWORK_o.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp10_B.Derivative1_a = (f14tmp10_B.TransferFcn1_a - *lastU++) / deltaT;
    }
  }

  /* Gain: '<S19>/Gain1' */
  f14tmp10_B.Gain1_c = f14tmp10_P.Gain1_Gain_n * f14tmp10_B.Derivative1_a;

  /* Product: '<S19>/Product' incorporates:
   *  Constant: '<S19>/Constant'
   */
  f14tmp10_B.Product_a = f14tmp10_B.TransferFcn1_a * f14tmp10_P.Constant_Value_m;

  /* Sum: '<S19>/Sum1' */
  f14tmp10_B.Sum1_di = (f14tmp10_B.Gain1_c - f14tmp10_B.Derivative_k) +
    f14tmp10_B.Product_a;

  /* Gain: '<S19>/Gain2' */
  f14tmp10_B.Gain2_l = f14tmp10_P.Gain2_Gain_e * f14tmp10_B.Sum1_di;
  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* SignalGenerator: '<S2>/Pilot' */
  temp = f14tmp10_P.Pilot_Frequency_d * f14tmp10_rtM->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    f14tmp10_B.Pilot_k = f14tmp10_P.Pilot_Amplitude_n;
  } else {
    f14tmp10_B.Pilot_k = -f14tmp10_P.Pilot_Amplitude_n;
  }

  /* End of SignalGenerator: '<S2>/Pilot' */

  /* Sum: '<S2>/Sum1' */
  f14tmp10_B.Sum1_n = f14tmp10_B.Pilot_k + 0.0;
  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* TransferFcn: '<S2>/Actuator Model' */
  f14tmp10_B.ActuatorModel_n = f14tmp10_P.ActuatorModel_C_f*
    f14tmp10_X.ActuatorModel_CSTATE_a;

  /* Gain: '<S16>/Gain3' */
  f14tmp10_B.Gain3_a = f14tmp10_P.Gain3_Gain_k * f14tmp10_B.TransferFcn1_a;

  /* Gain: '<S16>/Gain4' */
  f14tmp10_B.Gain4_p = f14tmp10_P.Gain4_Gain_f * f14tmp10_B.TransferFcn2_b;

  /* Gain: '<S16>/Gain5' */
  f14tmp10_B.Gain5_h4 = f14tmp10_P.Gain5_Gain_g * f14tmp10_B.ActuatorModel_n;

  /* Gain: '<S16>/Gain6' */
  f14tmp10_B.Gain6_m = f14tmp10_P.Gain6_Gain_b * f14tmp10_B.ActuatorModel_n;

  /* TransferFcn: '<S18>/W-gust model' */
  f14tmp10_B.Wgustmodel_j = f14tmp10_P.Wgustmodel_C_a[0]*
    f14tmp10_X.Wgustmodel_CSTATE_f[0]
    + f14tmp10_P.Wgustmodel_C_a[1]*f14tmp10_X.Wgustmodel_CSTATE_f[1];

  /* Gain: '<S2>/Gain' */
  f14tmp10_B.Gain_n = f14tmp10_P.Gain_Gain_l * f14tmp10_B.Wgustmodel_j;

  /* Sum: '<S16>/Sum1' */
  f14tmp10_B.Sum1_e = (f14tmp10_B.Gain5_h4 - f14tmp10_B.Gain_n) +
    f14tmp10_B.Gain3_a;

  /* Gain: '<S2>/Gain2' */
  f14tmp10_B.Gain2_o = f14tmp10_P.Gain2_Gain_h * f14tmp10_B.Wgustmodel_j;

  /* TransferFcn: '<S18>/Q-gust model' */
  f14tmp10_B.Qgustmodel_c = f14tmp10_P.Qgustmodel_D_c*f14tmp10_B.Wgustmodel_j;
  f14tmp10_B.Qgustmodel_c += f14tmp10_P.Qgustmodel_C_p*
    f14tmp10_X.Qgustmodel_CSTATE_d;

  /* Gain: '<S2>/Gain1' */
  f14tmp10_B.Gain1_i = f14tmp10_P.Gain1_Gain_p * f14tmp10_B.Qgustmodel_c;

  /* Sum: '<S2>/Sum' */
  f14tmp10_B.Sum_e = f14tmp10_B.Gain2_o + f14tmp10_B.Gain1_i;

  /* Sum: '<S16>/Sum2' */
  f14tmp10_B.Sum2_c = (f14tmp10_B.Gain4_p - f14tmp10_B.Sum_e) +
    f14tmp10_B.Gain6_m;

  /* TransferFcn: '<S17>/Alpha-sensor Low-pass Filter' */
  f14tmp10_B.AlphasensorLowpassFilter_e =
    f14tmp10_P.AlphasensorLowpassFilter_C_g*
    f14tmp10_X.AlphasensorLowpassFilter_CSTA_g;

  /* TransferFcn: '<S17>/Stick Prefilter' */
  f14tmp10_B.StickPrefilter_h = f14tmp10_P.StickPrefilter_C_p*
    f14tmp10_X.StickPrefilter_CSTATE_a;

  /* TransferFcn: '<S17>/Pitch Rate Lead Filter' */
  f14tmp10_B.PitchRateLeadFilter_f = f14tmp10_P.PitchRateLeadFilter_D_f*
    f14tmp10_B.TransferFcn1_a;
  f14tmp10_B.PitchRateLeadFilter_f += f14tmp10_P.PitchRateLeadFilter_C_l*
    f14tmp10_X.PitchRateLeadFilter_CSTATE_k;

  /* Gain: '<S17>/Gain2' */
  f14tmp10_B.Gain2_j = f14tmp10_P.Gain2_Gain_et *
    f14tmp10_B.PitchRateLeadFilter_f;

  /* Gain: '<S17>/Gain3' */
  f14tmp10_B.Gain3_l = f14tmp10_P.Gain3_Gain_b *
    f14tmp10_B.AlphasensorLowpassFilter_e;

  /* Sum: '<S17>/Sum1' */
  f14tmp10_B.Sum1_i = f14tmp10_B.Gain2_j + f14tmp10_B.Gain3_l;

  /* Sum: '<S17>/Sum2' */
  f14tmp10_B.Sum2_k = f14tmp10_B.StickPrefilter_h - f14tmp10_B.Sum1_i;

  /* Gain: '<S17>/Gain' */
  f14tmp10_B.Gain_e = f14tmp10_P.Gain_Gain_a * f14tmp10_B.Sum2_k;

  /* TransferFcn: '<S17>/Proportional plus integral compensator' */
  f14tmp10_B.Proportionalplusintegralcompe_j =
    f14tmp10_P.Proportionalplusintegralcomp_mx*
    f14tmp10_X.Proportionalplusintegralcompe_n;

  /* Sum: '<S17>/Sum' */
  f14tmp10_B.Sum_l = f14tmp10_B.Gain_e +
    f14tmp10_B.Proportionalplusintegralcompe_j;
  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* RandomNumber: '<S20>/White Noise' */
    f14tmp10_B.WhiteNoise_l = f14tmp10_DWork.NextOutput_f;

    /* Gain: '<S20>/Output' */
    f14tmp10_B.Output_e = f14tmp10_P.Output_Gain_l * f14tmp10_B.WhiteNoise_l;
  }

  /* TransferFcn: '<S21>/Transfer Fcn.2' */
  f14tmp10_B.TransferFcn2_l = f14tmp10_P.TransferFcn2_C_a*
    f14tmp10_X.TransferFcn2_CSTATE_n;

  /* Gain: '<S3>/Gain5' */
  f14tmp10_B.Gain5_p = f14tmp10_P.Gain5_Gain_c * f14tmp10_B.TransferFcn2_l;
  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* Derivative: '<S24>/Derivative' */
  {
    real_T t = f14tmp10_rtM->Timing.t[0];
    real_T timeStampA = f14tmp10_DWork.Derivative_RWORK_l.TimeStampA;
    real_T timeStampB = f14tmp10_DWork.Derivative_RWORK_l.TimeStampB;
    real_T *lastU = &f14tmp10_DWork.Derivative_RWORK_l.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp10_B.Derivative_l = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp10_DWork.Derivative_RWORK_l.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp10_DWork.Derivative_RWORK_l.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp10_B.Derivative_l = (f14tmp10_B.TransferFcn2_l - *lastU++) / deltaT;
    }
  }

  /* TransferFcn: '<S21>/Transfer Fcn.1' */
  f14tmp10_B.TransferFcn1_g = f14tmp10_P.TransferFcn1_C_gb*
    f14tmp10_X.TransferFcn1_CSTATE_k;

  /* Derivative: '<S24>/Derivative1' */
  {
    real_T t = f14tmp10_rtM->Timing.t[0];
    real_T timeStampA = f14tmp10_DWork.Derivative1_RWORK_k.TimeStampA;
    real_T timeStampB = f14tmp10_DWork.Derivative1_RWORK_k.TimeStampB;
    real_T *lastU = &f14tmp10_DWork.Derivative1_RWORK_k.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp10_B.Derivative1_j = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp10_DWork.Derivative1_RWORK_k.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp10_DWork.Derivative1_RWORK_k.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp10_B.Derivative1_j = (f14tmp10_B.TransferFcn1_g - *lastU++) / deltaT;
    }
  }

  /* Gain: '<S24>/Gain1' */
  f14tmp10_B.Gain1_g = f14tmp10_P.Gain1_Gain_e * f14tmp10_B.Derivative1_j;

  /* Product: '<S24>/Product' incorporates:
   *  Constant: '<S24>/Constant'
   */
  f14tmp10_B.Product_b = f14tmp10_B.TransferFcn1_g * f14tmp10_P.Constant_Value_b;

  /* Sum: '<S24>/Sum1' */
  f14tmp10_B.Sum1_ev = (f14tmp10_B.Gain1_g - f14tmp10_B.Derivative_l) +
    f14tmp10_B.Product_b;

  /* Gain: '<S24>/Gain2' */
  f14tmp10_B.Gain2_g = f14tmp10_P.Gain2_Gain_h5 * f14tmp10_B.Sum1_ev;
  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* SignalGenerator: '<S3>/Pilot' */
  temp = f14tmp10_P.Pilot_Frequency_k * f14tmp10_rtM->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    f14tmp10_B.Pilot_h = f14tmp10_P.Pilot_Amplitude_e;
  } else {
    f14tmp10_B.Pilot_h = -f14tmp10_P.Pilot_Amplitude_e;
  }

  /* End of SignalGenerator: '<S3>/Pilot' */

  /* Sum: '<S3>/Sum1' */
  f14tmp10_B.Sum1_n0 = f14tmp10_B.Pilot_h + 0.0;
  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* TransferFcn: '<S3>/Actuator Model' */
  f14tmp10_B.ActuatorModel_a = f14tmp10_P.ActuatorModel_C_b*
    f14tmp10_X.ActuatorModel_CSTATE_f;

  /* Gain: '<S21>/Gain3' */
  f14tmp10_B.Gain3_m = f14tmp10_P.Gain3_Gain_c * f14tmp10_B.TransferFcn1_g;

  /* Gain: '<S21>/Gain4' */
  f14tmp10_B.Gain4_c = f14tmp10_P.Gain4_Gain_j * f14tmp10_B.TransferFcn2_l;

  /* Gain: '<S21>/Gain5' */
  f14tmp10_B.Gain5_o = f14tmp10_P.Gain5_Gain_p * f14tmp10_B.ActuatorModel_a;

  /* Gain: '<S21>/Gain6' */
  f14tmp10_B.Gain6_mc = f14tmp10_P.Gain6_Gain_f * f14tmp10_B.ActuatorModel_a;

  /* TransferFcn: '<S23>/W-gust model' */
  f14tmp10_B.Wgustmodel_e = f14tmp10_P.Wgustmodel_C_m[0]*
    f14tmp10_X.Wgustmodel_CSTATE_i[0]
    + f14tmp10_P.Wgustmodel_C_m[1]*f14tmp10_X.Wgustmodel_CSTATE_i[1];

  /* Gain: '<S3>/Gain' */
  f14tmp10_B.Gain_l = f14tmp10_P.Gain_Gain_d * f14tmp10_B.Wgustmodel_e;

  /* Sum: '<S21>/Sum1' */
  f14tmp10_B.Sum1_dr = (f14tmp10_B.Gain5_o - f14tmp10_B.Gain_l) +
    f14tmp10_B.Gain3_m;

  /* Gain: '<S3>/Gain2' */
  f14tmp10_B.Gain2_l0 = f14tmp10_P.Gain2_Gain_g * f14tmp10_B.Wgustmodel_e;

  /* TransferFcn: '<S23>/Q-gust model' */
  f14tmp10_B.Qgustmodel_j = f14tmp10_P.Qgustmodel_D_i*f14tmp10_B.Wgustmodel_e;
  f14tmp10_B.Qgustmodel_j += f14tmp10_P.Qgustmodel_C_j*
    f14tmp10_X.Qgustmodel_CSTATE_k;

  /* Gain: '<S3>/Gain1' */
  f14tmp10_B.Gain1_b = f14tmp10_P.Gain1_Gain_f * f14tmp10_B.Qgustmodel_j;

  /* Sum: '<S3>/Sum' */
  f14tmp10_B.Sum_i = f14tmp10_B.Gain2_l0 + f14tmp10_B.Gain1_b;

  /* Sum: '<S21>/Sum2' */
  f14tmp10_B.Sum2_o = (f14tmp10_B.Gain4_c - f14tmp10_B.Sum_i) +
    f14tmp10_B.Gain6_mc;

  /* TransferFcn: '<S22>/Alpha-sensor Low-pass Filter' */
  f14tmp10_B.AlphasensorLowpassFilter_h =
    f14tmp10_P.AlphasensorLowpassFilter_C_gf*
    f14tmp10_X.AlphasensorLowpassFilter_CSTA_i;

  /* TransferFcn: '<S22>/Stick Prefilter' */
  f14tmp10_B.StickPrefilter_i = f14tmp10_P.StickPrefilter_C_j*
    f14tmp10_X.StickPrefilter_CSTATE_j;

  /* TransferFcn: '<S22>/Pitch Rate Lead Filter' */
  f14tmp10_B.PitchRateLeadFilter_d = f14tmp10_P.PitchRateLeadFilter_D_ft*
    f14tmp10_B.TransferFcn1_g;
  f14tmp10_B.PitchRateLeadFilter_d += f14tmp10_P.PitchRateLeadFilter_C_k*
    f14tmp10_X.PitchRateLeadFilter_CSTATE_n;

  /* Gain: '<S22>/Gain2' */
  f14tmp10_B.Gain2_p = f14tmp10_P.Gain2_Gain_eh *
    f14tmp10_B.PitchRateLeadFilter_d;

  /* Gain: '<S22>/Gain3' */
  f14tmp10_B.Gain3_gl = f14tmp10_P.Gain3_Gain_m *
    f14tmp10_B.AlphasensorLowpassFilter_h;

  /* Sum: '<S22>/Sum1' */
  f14tmp10_B.Sum1_o0 = f14tmp10_B.Gain2_p + f14tmp10_B.Gain3_gl;

  /* Sum: '<S22>/Sum2' */
  f14tmp10_B.Sum2_g = f14tmp10_B.StickPrefilter_i - f14tmp10_B.Sum1_o0;

  /* Gain: '<S22>/Gain' */
  f14tmp10_B.Gain_h = f14tmp10_P.Gain_Gain_j * f14tmp10_B.Sum2_g;

  /* TransferFcn: '<S22>/Proportional plus integral compensator' */
  f14tmp10_B.Proportionalplusintegralcompe_e =
    f14tmp10_P.Proportionalplusintegralcompe_l*
    f14tmp10_X.Proportionalplusintegralcompe_h;

  /* Sum: '<S22>/Sum' */
  f14tmp10_B.Sum_o = f14tmp10_B.Gain_h +
    f14tmp10_B.Proportionalplusintegralcompe_e;
  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* RandomNumber: '<S25>/White Noise' */
    f14tmp10_B.WhiteNoise_g = f14tmp10_DWork.NextOutput_h;

    /* Gain: '<S25>/Output' */
    f14tmp10_B.Output_c = f14tmp10_P.Output_Gain_m * f14tmp10_B.WhiteNoise_g;
  }

  /* TransferFcn: '<S26>/Transfer Fcn.2' */
  f14tmp10_B.TransferFcn2_j = f14tmp10_P.TransferFcn2_C_l*
    f14tmp10_X.TransferFcn2_CSTATE_e;

  /* Gain: '<S4>/Gain5' */
  f14tmp10_B.Gain5_k = f14tmp10_P.Gain5_Gain_j0 * f14tmp10_B.TransferFcn2_j;
  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* Derivative: '<S29>/Derivative' */
  {
    real_T t = f14tmp10_rtM->Timing.t[0];
    real_T timeStampA = f14tmp10_DWork.Derivative_RWORK_k.TimeStampA;
    real_T timeStampB = f14tmp10_DWork.Derivative_RWORK_k.TimeStampB;
    real_T *lastU = &f14tmp10_DWork.Derivative_RWORK_k.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp10_B.Derivative_p = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp10_DWork.Derivative_RWORK_k.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp10_DWork.Derivative_RWORK_k.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp10_B.Derivative_p = (f14tmp10_B.TransferFcn2_j - *lastU++) / deltaT;
    }
  }

  /* TransferFcn: '<S26>/Transfer Fcn.1' */
  f14tmp10_B.TransferFcn1_k = f14tmp10_P.TransferFcn1_C_l*
    f14tmp10_X.TransferFcn1_CSTATE_j;

  /* Derivative: '<S29>/Derivative1' */
  {
    real_T t = f14tmp10_rtM->Timing.t[0];
    real_T timeStampA = f14tmp10_DWork.Derivative1_RWORK_b.TimeStampA;
    real_T timeStampB = f14tmp10_DWork.Derivative1_RWORK_b.TimeStampB;
    real_T *lastU = &f14tmp10_DWork.Derivative1_RWORK_b.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp10_B.Derivative1_g = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp10_DWork.Derivative1_RWORK_b.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp10_DWork.Derivative1_RWORK_b.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp10_B.Derivative1_g = (f14tmp10_B.TransferFcn1_k - *lastU++) / deltaT;
    }
  }

  /* Gain: '<S29>/Gain1' */
  f14tmp10_B.Gain1_ga = f14tmp10_P.Gain1_Gain_fm * f14tmp10_B.Derivative1_g;

  /* Product: '<S29>/Product' incorporates:
   *  Constant: '<S29>/Constant'
   */
  f14tmp10_B.Product_h = f14tmp10_B.TransferFcn1_k * f14tmp10_P.Constant_Value_f;

  /* Sum: '<S29>/Sum1' */
  f14tmp10_B.Sum1_o0i = (f14tmp10_B.Gain1_ga - f14tmp10_B.Derivative_p) +
    f14tmp10_B.Product_h;

  /* Gain: '<S29>/Gain2' */
  f14tmp10_B.Gain2_h = f14tmp10_P.Gain2_Gain_kz * f14tmp10_B.Sum1_o0i;
  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* SignalGenerator: '<S4>/Pilot' */
  temp = f14tmp10_P.Pilot_Frequency_i * f14tmp10_rtM->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    f14tmp10_B.Pilot_g = f14tmp10_P.Pilot_Amplitude_o;
  } else {
    f14tmp10_B.Pilot_g = -f14tmp10_P.Pilot_Amplitude_o;
  }

  /* End of SignalGenerator: '<S4>/Pilot' */

  /* Sum: '<S4>/Sum1' */
  f14tmp10_B.Sum1_dd = f14tmp10_B.Pilot_g + 0.0;
  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* TransferFcn: '<S4>/Actuator Model' */
  f14tmp10_B.ActuatorModel_m = f14tmp10_P.ActuatorModel_C_l*
    f14tmp10_X.ActuatorModel_CSTATE_p;

  /* Gain: '<S26>/Gain3' */
  f14tmp10_B.Gain3_lc = f14tmp10_P.Gain3_Gain_p * f14tmp10_B.TransferFcn1_k;

  /* Gain: '<S26>/Gain4' */
  f14tmp10_B.Gain4_j = f14tmp10_P.Gain4_Gain_c * f14tmp10_B.TransferFcn2_j;

  /* Gain: '<S26>/Gain5' */
  f14tmp10_B.Gain5_pj = f14tmp10_P.Gain5_Gain_j0q * f14tmp10_B.ActuatorModel_m;

  /* Gain: '<S26>/Gain6' */
  f14tmp10_B.Gain6_f = f14tmp10_P.Gain6_Gain_j * f14tmp10_B.ActuatorModel_m;

  /* TransferFcn: '<S28>/W-gust model' */
  f14tmp10_B.Wgustmodel_h = f14tmp10_P.Wgustmodel_C_g[0]*
    f14tmp10_X.Wgustmodel_CSTATE_k[0]
    + f14tmp10_P.Wgustmodel_C_g[1]*f14tmp10_X.Wgustmodel_CSTATE_k[1];

  /* Gain: '<S4>/Gain' */
  f14tmp10_B.Gain_o = f14tmp10_P.Gain_Gain_h * f14tmp10_B.Wgustmodel_h;

  /* Sum: '<S26>/Sum1' */
  f14tmp10_B.Sum1_f = (f14tmp10_B.Gain5_pj - f14tmp10_B.Gain_o) +
    f14tmp10_B.Gain3_lc;

  /* Gain: '<S4>/Gain2' */
  f14tmp10_B.Gain2_n = f14tmp10_P.Gain2_Gain_m * f14tmp10_B.Wgustmodel_h;

  /* TransferFcn: '<S28>/Q-gust model' */
  f14tmp10_B.Qgustmodel_g = f14tmp10_P.Qgustmodel_D_a*f14tmp10_B.Wgustmodel_h;
  f14tmp10_B.Qgustmodel_g += f14tmp10_P.Qgustmodel_C_a*
    f14tmp10_X.Qgustmodel_CSTATE_a;

  /* Gain: '<S4>/Gain1' */
  f14tmp10_B.Gain1_o = f14tmp10_P.Gain1_Gain_d * f14tmp10_B.Qgustmodel_g;

  /* Sum: '<S4>/Sum' */
  f14tmp10_B.Sum_en = f14tmp10_B.Gain2_n + f14tmp10_B.Gain1_o;

  /* Sum: '<S26>/Sum2' */
  f14tmp10_B.Sum2_cx = (f14tmp10_B.Gain4_j - f14tmp10_B.Sum_en) +
    f14tmp10_B.Gain6_f;

  /* TransferFcn: '<S27>/Alpha-sensor Low-pass Filter' */
  f14tmp10_B.AlphasensorLowpassFilter_j =
    f14tmp10_P.AlphasensorLowpassFilter_C_m*
    f14tmp10_X.AlphasensorLowpassFilter_CSTA_k;

  /* TransferFcn: '<S27>/Stick Prefilter' */
  f14tmp10_B.StickPrefilter_e = f14tmp10_P.StickPrefilter_C_h*
    f14tmp10_X.StickPrefilter_CSTATE_ju;

  /* TransferFcn: '<S27>/Pitch Rate Lead Filter' */
  f14tmp10_B.PitchRateLeadFilter_k = f14tmp10_P.PitchRateLeadFilter_D_b*
    f14tmp10_B.TransferFcn1_k;
  f14tmp10_B.PitchRateLeadFilter_k += f14tmp10_P.PitchRateLeadFilter_C_b*
    f14tmp10_X.PitchRateLeadFilter_CSTATE_e;

  /* Gain: '<S27>/Gain2' */
  f14tmp10_B.Gain2_nh = f14tmp10_P.Gain2_Gain_b *
    f14tmp10_B.PitchRateLeadFilter_k;

  /* Gain: '<S27>/Gain3' */
  f14tmp10_B.Gain3_b = f14tmp10_P.Gain3_Gain_a *
    f14tmp10_B.AlphasensorLowpassFilter_j;

  /* Sum: '<S27>/Sum1' */
  f14tmp10_B.Sum1_om = f14tmp10_B.Gain2_nh + f14tmp10_B.Gain3_b;

  /* Sum: '<S27>/Sum2' */
  f14tmp10_B.Sum2_gm = f14tmp10_B.StickPrefilter_e - f14tmp10_B.Sum1_om;

  /* Gain: '<S27>/Gain' */
  f14tmp10_B.Gain_df = f14tmp10_P.Gain_Gain_f * f14tmp10_B.Sum2_gm;

  /* TransferFcn: '<S27>/Proportional plus integral compensator' */
  f14tmp10_B.Proportionalplusintegralcompe_h =
    f14tmp10_P.Proportionalplusintegralcompe_j*
    f14tmp10_X.Proportionalplusintegralcompe_j;

  /* Sum: '<S27>/Sum' */
  f14tmp10_B.Sum_k = f14tmp10_B.Gain_df +
    f14tmp10_B.Proportionalplusintegralcompe_h;
  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* RandomNumber: '<S30>/White Noise' */
    f14tmp10_B.WhiteNoise_p = f14tmp10_DWork.NextOutput_a;

    /* Gain: '<S30>/Output' */
    f14tmp10_B.Output_k = f14tmp10_P.Output_Gain_p * f14tmp10_B.WhiteNoise_p;
  }

  /* TransferFcn: '<S31>/Transfer Fcn.2' */
  f14tmp10_B.TransferFcn2_o = f14tmp10_P.TransferFcn2_C_e*
    f14tmp10_X.TransferFcn2_CSTATE_k;

  /* Gain: '<S5>/Gain5' */
  f14tmp10_B.Gain5_c = f14tmp10_P.Gain5_Gain_f * f14tmp10_B.TransferFcn2_o;
  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* Derivative: '<S34>/Derivative' */
  {
    real_T t = f14tmp10_rtM->Timing.t[0];
    real_T timeStampA = f14tmp10_DWork.Derivative_RWORK_lc.TimeStampA;
    real_T timeStampB = f14tmp10_DWork.Derivative_RWORK_lc.TimeStampB;
    real_T *lastU = &f14tmp10_DWork.Derivative_RWORK_lc.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp10_B.Derivative_f = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp10_DWork.Derivative_RWORK_lc.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp10_DWork.Derivative_RWORK_lc.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp10_B.Derivative_f = (f14tmp10_B.TransferFcn2_o - *lastU++) / deltaT;
    }
  }

  /* TransferFcn: '<S31>/Transfer Fcn.1' */
  f14tmp10_B.TransferFcn1_i = f14tmp10_P.TransferFcn1_C_j*
    f14tmp10_X.TransferFcn1_CSTATE_pe;

  /* Derivative: '<S34>/Derivative1' */
  {
    real_T t = f14tmp10_rtM->Timing.t[0];
    real_T timeStampA = f14tmp10_DWork.Derivative1_RWORK_d.TimeStampA;
    real_T timeStampB = f14tmp10_DWork.Derivative1_RWORK_d.TimeStampB;
    real_T *lastU = &f14tmp10_DWork.Derivative1_RWORK_d.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp10_B.Derivative1_i = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp10_DWork.Derivative1_RWORK_d.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp10_DWork.Derivative1_RWORK_d.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp10_B.Derivative1_i = (f14tmp10_B.TransferFcn1_i - *lastU++) / deltaT;
    }
  }

  /* Gain: '<S34>/Gain1' */
  f14tmp10_B.Gain1_om = f14tmp10_P.Gain1_Gain_m * f14tmp10_B.Derivative1_i;

  /* Product: '<S34>/Product' incorporates:
   *  Constant: '<S34>/Constant'
   */
  f14tmp10_B.Product_i = f14tmp10_B.TransferFcn1_i * f14tmp10_P.Constant_Value_p;

  /* Sum: '<S34>/Sum1' */
  f14tmp10_B.Sum1_a = (f14tmp10_B.Gain1_om - f14tmp10_B.Derivative_f) +
    f14tmp10_B.Product_i;

  /* Gain: '<S34>/Gain2' */
  f14tmp10_B.Gain2_oj = f14tmp10_P.Gain2_Gain_d * f14tmp10_B.Sum1_a;
  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* SignalGenerator: '<S5>/Pilot' */
  temp = f14tmp10_P.Pilot_Frequency_a * f14tmp10_rtM->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    f14tmp10_B.Pilot_h3 = f14tmp10_P.Pilot_Amplitude_h;
  } else {
    f14tmp10_B.Pilot_h3 = -f14tmp10_P.Pilot_Amplitude_h;
  }

  /* End of SignalGenerator: '<S5>/Pilot' */

  /* Sum: '<S5>/Sum1' */
  f14tmp10_B.Sum1_h = f14tmp10_B.Pilot_h3 + 0.0;
  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* TransferFcn: '<S5>/Actuator Model' */
  f14tmp10_B.ActuatorModel_b = f14tmp10_P.ActuatorModel_C_a*
    f14tmp10_X.ActuatorModel_CSTATE_o;

  /* Gain: '<S31>/Gain3' */
  f14tmp10_B.Gain3_as = f14tmp10_P.Gain3_Gain_ai * f14tmp10_B.TransferFcn1_i;

  /* Gain: '<S31>/Gain4' */
  f14tmp10_B.Gain4_l = f14tmp10_P.Gain4_Gain_d * f14tmp10_B.TransferFcn2_o;

  /* Gain: '<S31>/Gain5' */
  f14tmp10_B.Gain5_i = f14tmp10_P.Gain5_Gain_n * f14tmp10_B.ActuatorModel_b;

  /* Gain: '<S31>/Gain6' */
  f14tmp10_B.Gain6_b = f14tmp10_P.Gain6_Gain_n * f14tmp10_B.ActuatorModel_b;

  /* TransferFcn: '<S33>/W-gust model' */
  f14tmp10_B.Wgustmodel_o = f14tmp10_P.Wgustmodel_C_p[0]*
    f14tmp10_X.Wgustmodel_CSTATE_if[0]
    + f14tmp10_P.Wgustmodel_C_p[1]*f14tmp10_X.Wgustmodel_CSTATE_if[1];

  /* Gain: '<S5>/Gain' */
  f14tmp10_B.Gain_hr = f14tmp10_P.Gain_Gain_c * f14tmp10_B.Wgustmodel_o;

  /* Sum: '<S31>/Sum1' */
  f14tmp10_B.Sum1_g = (f14tmp10_B.Gain5_i - f14tmp10_B.Gain_hr) +
    f14tmp10_B.Gain3_as;

  /* Gain: '<S5>/Gain2' */
  f14tmp10_B.Gain2_b = f14tmp10_P.Gain2_Gain_l * f14tmp10_B.Wgustmodel_o;

  /* TransferFcn: '<S33>/Q-gust model' */
  f14tmp10_B.Qgustmodel_n = f14tmp10_P.Qgustmodel_D_l*f14tmp10_B.Wgustmodel_o;
  f14tmp10_B.Qgustmodel_n += f14tmp10_P.Qgustmodel_C_c*
    f14tmp10_X.Qgustmodel_CSTATE_m;

  /* Gain: '<S5>/Gain1' */
  f14tmp10_B.Gain1_l = f14tmp10_P.Gain1_Gain_a * f14tmp10_B.Qgustmodel_n;

  /* Sum: '<S5>/Sum' */
  f14tmp10_B.Sum_kh = f14tmp10_B.Gain2_b + f14tmp10_B.Gain1_l;

  /* Sum: '<S31>/Sum2' */
  f14tmp10_B.Sum2_oa = (f14tmp10_B.Gain4_l - f14tmp10_B.Sum_kh) +
    f14tmp10_B.Gain6_b;

  /* TransferFcn: '<S32>/Alpha-sensor Low-pass Filter' */
  f14tmp10_B.AlphasensorLowpassFilter_n =
    f14tmp10_P.AlphasensorLowpassFilter_C_e*
    f14tmp10_X.AlphasensorLowpassFilter_CST_ku;

  /* TransferFcn: '<S32>/Stick Prefilter' */
  f14tmp10_B.StickPrefilter_o = f14tmp10_P.StickPrefilter_C_b*
    f14tmp10_X.StickPrefilter_CSTATE_m;

  /* TransferFcn: '<S32>/Pitch Rate Lead Filter' */
  f14tmp10_B.PitchRateLeadFilter_f1 = f14tmp10_P.PitchRateLeadFilter_D_a*
    f14tmp10_B.TransferFcn1_i;
  f14tmp10_B.PitchRateLeadFilter_f1 += f14tmp10_P.PitchRateLeadFilter_C_a*
    f14tmp10_X.PitchRateLeadFilter_CSTATE_f;

  /* Gain: '<S32>/Gain2' */
  f14tmp10_B.Gain2_fs = f14tmp10_P.Gain2_Gain_n *
    f14tmp10_B.PitchRateLeadFilter_f1;

  /* Gain: '<S32>/Gain3' */
  f14tmp10_B.Gain3_f = f14tmp10_P.Gain3_Gain_h *
    f14tmp10_B.AlphasensorLowpassFilter_n;

  /* Sum: '<S32>/Sum1' */
  f14tmp10_B.Sum1_m = f14tmp10_B.Gain2_fs + f14tmp10_B.Gain3_f;

  /* Sum: '<S32>/Sum2' */
  f14tmp10_B.Sum2_f5 = f14tmp10_B.StickPrefilter_o - f14tmp10_B.Sum1_m;

  /* Gain: '<S32>/Gain' */
  f14tmp10_B.Gain_i = f14tmp10_P.Gain_Gain_o * f14tmp10_B.Sum2_f5;

  /* TransferFcn: '<S32>/Proportional plus integral compensator' */
  f14tmp10_B.Proportionalplusintegralcomp_eg =
    f14tmp10_P.Proportionalplusintegralcomp_jp*
    f14tmp10_X.Proportionalplusintegralcompe_k;

  /* Sum: '<S32>/Sum' */
  f14tmp10_B.Sum_m = f14tmp10_B.Gain_i +
    f14tmp10_B.Proportionalplusintegralcomp_eg;
  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* RandomNumber: '<S35>/White Noise' */
    f14tmp10_B.WhiteNoise_m = f14tmp10_DWork.NextOutput_e;

    /* Gain: '<S35>/Output' */
    f14tmp10_B.Output_a = f14tmp10_P.Output_Gain_pk * f14tmp10_B.WhiteNoise_m;
  }

  /* TransferFcn: '<S36>/Transfer Fcn.2' */
  f14tmp10_B.TransferFcn2_jp = f14tmp10_P.TransferFcn2_C_f*
    f14tmp10_X.TransferFcn2_CSTATE_a;

  /* Gain: '<S6>/Gain5' */
  f14tmp10_B.Gain5_o4 = f14tmp10_P.Gain5_Gain_h * f14tmp10_B.TransferFcn2_jp;
  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* Derivative: '<S39>/Derivative' */
  {
    real_T t = f14tmp10_rtM->Timing.t[0];
    real_T timeStampA = f14tmp10_DWork.Derivative_RWORK_j.TimeStampA;
    real_T timeStampB = f14tmp10_DWork.Derivative_RWORK_j.TimeStampB;
    real_T *lastU = &f14tmp10_DWork.Derivative_RWORK_j.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp10_B.Derivative_g = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp10_DWork.Derivative_RWORK_j.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp10_DWork.Derivative_RWORK_j.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp10_B.Derivative_g = (f14tmp10_B.TransferFcn2_jp - *lastU++) / deltaT;
    }
  }

  /* TransferFcn: '<S36>/Transfer Fcn.1' */
  f14tmp10_B.TransferFcn1_f = f14tmp10_P.TransferFcn1_C_k*
    f14tmp10_X.TransferFcn1_CSTATE_i;

  /* Derivative: '<S39>/Derivative1' */
  {
    real_T t = f14tmp10_rtM->Timing.t[0];
    real_T timeStampA = f14tmp10_DWork.Derivative1_RWORK_p.TimeStampA;
    real_T timeStampB = f14tmp10_DWork.Derivative1_RWORK_p.TimeStampB;
    real_T *lastU = &f14tmp10_DWork.Derivative1_RWORK_p.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp10_B.Derivative1_o = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp10_DWork.Derivative1_RWORK_p.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp10_DWork.Derivative1_RWORK_p.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp10_B.Derivative1_o = (f14tmp10_B.TransferFcn1_f - *lastU++) / deltaT;
    }
  }

  /* Gain: '<S39>/Gain1' */
  f14tmp10_B.Gain1_ho = f14tmp10_P.Gain1_Gain_o * f14tmp10_B.Derivative1_o;

  /* Product: '<S39>/Product' incorporates:
   *  Constant: '<S39>/Constant'
   */
  f14tmp10_B.Product_o = f14tmp10_B.TransferFcn1_f * f14tmp10_P.Constant_Value_o;

  /* Sum: '<S39>/Sum1' */
  f14tmp10_B.Sum1_ap = (f14tmp10_B.Gain1_ho - f14tmp10_B.Derivative_g) +
    f14tmp10_B.Product_o;

  /* Gain: '<S39>/Gain2' */
  f14tmp10_B.Gain2_d = f14tmp10_P.Gain2_Gain_ba * f14tmp10_B.Sum1_ap;
  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* SignalGenerator: '<S6>/Pilot' */
  temp = f14tmp10_P.Pilot_Frequency_ik * f14tmp10_rtM->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    f14tmp10_B.Pilot_j = f14tmp10_P.Pilot_Amplitude_c;
  } else {
    f14tmp10_B.Pilot_j = -f14tmp10_P.Pilot_Amplitude_c;
  }

  /* End of SignalGenerator: '<S6>/Pilot' */

  /* Sum: '<S6>/Sum1' */
  f14tmp10_B.Sum1_fi = f14tmp10_B.Pilot_j + 0.0;
  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* TransferFcn: '<S6>/Actuator Model' */
  f14tmp10_B.ActuatorModel_b4 = f14tmp10_P.ActuatorModel_C_j*
    f14tmp10_X.ActuatorModel_CSTATE_g;

  /* Gain: '<S36>/Gain3' */
  f14tmp10_B.Gain3_c = f14tmp10_P.Gain3_Gain_n * f14tmp10_B.TransferFcn1_f;

  /* Gain: '<S36>/Gain4' */
  f14tmp10_B.Gain4_d = f14tmp10_P.Gain4_Gain_fw * f14tmp10_B.TransferFcn2_jp;

  /* Gain: '<S36>/Gain5' */
  f14tmp10_B.Gain5_f = f14tmp10_P.Gain5_Gain_i * f14tmp10_B.ActuatorModel_b4;

  /* Gain: '<S36>/Gain6' */
  f14tmp10_B.Gain6_j = f14tmp10_P.Gain6_Gain_f2 * f14tmp10_B.ActuatorModel_b4;

  /* TransferFcn: '<S38>/W-gust model' */
  f14tmp10_B.Wgustmodel_o4 = f14tmp10_P.Wgustmodel_C_n[0]*
    f14tmp10_X.Wgustmodel_CSTATE_iv[0]
    + f14tmp10_P.Wgustmodel_C_n[1]*f14tmp10_X.Wgustmodel_CSTATE_iv[1];

  /* Gain: '<S6>/Gain' */
  f14tmp10_B.Gain_i2 = f14tmp10_P.Gain_Gain_de * f14tmp10_B.Wgustmodel_o4;

  /* Sum: '<S36>/Sum1' */
  f14tmp10_B.Sum1_o3 = (f14tmp10_B.Gain5_f - f14tmp10_B.Gain_i2) +
    f14tmp10_B.Gain3_c;

  /* Gain: '<S6>/Gain2' */
  f14tmp10_B.Gain2_da = f14tmp10_P.Gain2_Gain_by * f14tmp10_B.Wgustmodel_o4;

  /* TransferFcn: '<S38>/Q-gust model' */
  f14tmp10_B.Qgustmodel_h = f14tmp10_P.Qgustmodel_D_g*f14tmp10_B.Wgustmodel_o4;
  f14tmp10_B.Qgustmodel_h += f14tmp10_P.Qgustmodel_C_ci*
    f14tmp10_X.Qgustmodel_CSTATE_o;

  /* Gain: '<S6>/Gain1' */
  f14tmp10_B.Gain1_br = f14tmp10_P.Gain1_Gain_nw * f14tmp10_B.Qgustmodel_h;

  /* Sum: '<S6>/Sum' */
  f14tmp10_B.Sum_i2 = f14tmp10_B.Gain2_da + f14tmp10_B.Gain1_br;

  /* Sum: '<S36>/Sum2' */
  f14tmp10_B.Sum2_p = (f14tmp10_B.Gain4_d - f14tmp10_B.Sum_i2) +
    f14tmp10_B.Gain6_j;

  /* TransferFcn: '<S37>/Alpha-sensor Low-pass Filter' */
  f14tmp10_B.AlphasensorLowpassFilter_b =
    f14tmp10_P.AlphasensorLowpassFilter_C_gi*
    f14tmp10_X.AlphasensorLowpassFilter_CSTA_p;

  /* TransferFcn: '<S37>/Stick Prefilter' */
  f14tmp10_B.StickPrefilter_ew = f14tmp10_P.StickPrefilter_C_pn*
    f14tmp10_X.StickPrefilter_CSTATE_ah;

  /* TransferFcn: '<S37>/Pitch Rate Lead Filter' */
  f14tmp10_B.PitchRateLeadFilter_h = f14tmp10_P.PitchRateLeadFilter_D_fb*
    f14tmp10_B.TransferFcn1_f;
  f14tmp10_B.PitchRateLeadFilter_h += f14tmp10_P.PitchRateLeadFilter_C_o*
    f14tmp10_X.PitchRateLeadFilter_CSTATE_p;

  /* Gain: '<S37>/Gain2' */
  f14tmp10_B.Gain2_fo = f14tmp10_P.Gain2_Gain_c *
    f14tmp10_B.PitchRateLeadFilter_h;

  /* Gain: '<S37>/Gain3' */
  f14tmp10_B.Gain3_n = f14tmp10_P.Gain3_Gain_g *
    f14tmp10_B.AlphasensorLowpassFilter_b;

  /* Sum: '<S37>/Sum1' */
  f14tmp10_B.Sum1_my = f14tmp10_B.Gain2_fo + f14tmp10_B.Gain3_n;

  /* Sum: '<S37>/Sum2' */
  f14tmp10_B.Sum2_oh = f14tmp10_B.StickPrefilter_ew - f14tmp10_B.Sum1_my;

  /* Gain: '<S37>/Gain' */
  f14tmp10_B.Gain_k = f14tmp10_P.Gain_Gain_n * f14tmp10_B.Sum2_oh;

  /* TransferFcn: '<S37>/Proportional plus integral compensator' */
  f14tmp10_B.Proportionalplusintegralcompe_a =
    f14tmp10_P.Proportionalplusintegralcomp_pv*
    f14tmp10_X.Proportionalplusintegralcomp_jw;

  /* Sum: '<S37>/Sum' */
  f14tmp10_B.Sum_c = f14tmp10_B.Gain_k +
    f14tmp10_B.Proportionalplusintegralcompe_a;
  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* RandomNumber: '<S40>/White Noise' */
    f14tmp10_B.WhiteNoise_mt = f14tmp10_DWork.NextOutput_k;

    /* Gain: '<S40>/Output' */
    f14tmp10_B.Output_b = f14tmp10_P.Output_Gain_c * f14tmp10_B.WhiteNoise_mt;
  }

  /* TransferFcn: '<S41>/Transfer Fcn.2' */
  f14tmp10_B.TransferFcn2_f = f14tmp10_P.TransferFcn2_C_m*
    f14tmp10_X.TransferFcn2_CSTATE_l;

  /* Gain: '<S7>/Gain5' */
  f14tmp10_B.Gain5_e = f14tmp10_P.Gain5_Gain_l * f14tmp10_B.TransferFcn2_f;
  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* Derivative: '<S44>/Derivative' */
  {
    real_T t = f14tmp10_rtM->Timing.t[0];
    real_T timeStampA = f14tmp10_DWork.Derivative_RWORK_o.TimeStampA;
    real_T timeStampB = f14tmp10_DWork.Derivative_RWORK_o.TimeStampB;
    real_T *lastU = &f14tmp10_DWork.Derivative_RWORK_o.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp10_B.Derivative_ps = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp10_DWork.Derivative_RWORK_o.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp10_DWork.Derivative_RWORK_o.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp10_B.Derivative_ps = (f14tmp10_B.TransferFcn2_f - *lastU++) / deltaT;
    }
  }

  /* TransferFcn: '<S41>/Transfer Fcn.1' */
  f14tmp10_B.TransferFcn1_n = f14tmp10_P.TransferFcn1_C_c*
    f14tmp10_X.TransferFcn1_CSTATE_je;

  /* Derivative: '<S44>/Derivative1' */
  {
    real_T t = f14tmp10_rtM->Timing.t[0];
    real_T timeStampA = f14tmp10_DWork.Derivative1_RWORK_e.TimeStampA;
    real_T timeStampB = f14tmp10_DWork.Derivative1_RWORK_e.TimeStampB;
    real_T *lastU = &f14tmp10_DWork.Derivative1_RWORK_e.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp10_B.Derivative1_p = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp10_DWork.Derivative1_RWORK_e.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp10_DWork.Derivative1_RWORK_e.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp10_B.Derivative1_p = (f14tmp10_B.TransferFcn1_n - *lastU++) / deltaT;
    }
  }

  /* Gain: '<S44>/Gain1' */
  f14tmp10_B.Gain1_e = f14tmp10_P.Gain1_Gain_b * f14tmp10_B.Derivative1_p;

  /* Product: '<S44>/Product' incorporates:
   *  Constant: '<S44>/Constant'
   */
  f14tmp10_B.Product_ap = f14tmp10_B.TransferFcn1_n *
    f14tmp10_P.Constant_Value_g;

  /* Sum: '<S44>/Sum1' */
  f14tmp10_B.Sum1_nb = (f14tmp10_B.Gain1_e - f14tmp10_B.Derivative_ps) +
    f14tmp10_B.Product_ap;

  /* Gain: '<S44>/Gain2' */
  f14tmp10_B.Gain2_ne = f14tmp10_P.Gain2_Gain_o * f14tmp10_B.Sum1_nb;
  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* SignalGenerator: '<S7>/Pilot' */
  temp = f14tmp10_P.Pilot_Frequency_iu * f14tmp10_rtM->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    f14tmp10_B.Pilot_c = f14tmp10_P.Pilot_Amplitude_l;
  } else {
    f14tmp10_B.Pilot_c = -f14tmp10_P.Pilot_Amplitude_l;
  }

  /* End of SignalGenerator: '<S7>/Pilot' */

  /* Sum: '<S7>/Sum1' */
  f14tmp10_B.Sum1_ec = f14tmp10_B.Pilot_c + 0.0;
  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* TransferFcn: '<S7>/Actuator Model' */
  f14tmp10_B.ActuatorModel_n2 = f14tmp10_P.ActuatorModel_C_g*
    f14tmp10_X.ActuatorModel_CSTATE_fk;

  /* Gain: '<S41>/Gain3' */
  f14tmp10_B.Gain3_c0 = f14tmp10_P.Gain3_Gain_ia * f14tmp10_B.TransferFcn1_n;

  /* Gain: '<S41>/Gain4' */
  f14tmp10_B.Gain4_a = f14tmp10_P.Gain4_Gain_n * f14tmp10_B.TransferFcn2_f;

  /* Gain: '<S41>/Gain5' */
  f14tmp10_B.Gain5_ej = f14tmp10_P.Gain5_Gain_jj * f14tmp10_B.ActuatorModel_n2;

  /* Gain: '<S41>/Gain6' */
  f14tmp10_B.Gain6_c = f14tmp10_P.Gain6_Gain_jg * f14tmp10_B.ActuatorModel_n2;

  /* TransferFcn: '<S43>/W-gust model' */
  f14tmp10_B.Wgustmodel_f = f14tmp10_P.Wgustmodel_C_l[0]*
    f14tmp10_X.Wgustmodel_CSTATE_g[0]
    + f14tmp10_P.Wgustmodel_C_l[1]*f14tmp10_X.Wgustmodel_CSTATE_g[1];

  /* Gain: '<S7>/Gain' */
  f14tmp10_B.Gain_i1 = f14tmp10_P.Gain_Gain_fq * f14tmp10_B.Wgustmodel_f;

  /* Sum: '<S41>/Sum1' */
  f14tmp10_B.Sum1_n02 = (f14tmp10_B.Gain5_ej - f14tmp10_B.Gain_i1) +
    f14tmp10_B.Gain3_c0;

  /* Gain: '<S7>/Gain2' */
  f14tmp10_B.Gain2_fa = f14tmp10_P.Gain2_Gain_i * f14tmp10_B.Wgustmodel_f;

  /* TransferFcn: '<S43>/Q-gust model' */
  f14tmp10_B.Qgustmodel_i = f14tmp10_P.Qgustmodel_D_j*f14tmp10_B.Wgustmodel_f;
  f14tmp10_B.Qgustmodel_i += f14tmp10_P.Qgustmodel_C_g*
    f14tmp10_X.Qgustmodel_CSTATE_e;

  /* Gain: '<S7>/Gain1' */
  f14tmp10_B.Gain1_b3 = f14tmp10_P.Gain1_Gain_dk * f14tmp10_B.Qgustmodel_i;

  /* Sum: '<S7>/Sum' */
  f14tmp10_B.Sum_lm = f14tmp10_B.Gain2_fa + f14tmp10_B.Gain1_b3;

  /* Sum: '<S41>/Sum2' */
  f14tmp10_B.Sum2_b = (f14tmp10_B.Gain4_a - f14tmp10_B.Sum_lm) +
    f14tmp10_B.Gain6_c;

  /* TransferFcn: '<S42>/Alpha-sensor Low-pass Filter' */
  f14tmp10_B.AlphasensorLowpassFilter_p =
    f14tmp10_P.AlphasensorLowpassFilter_C_c*
    f14tmp10_X.AlphasensorLowpassFilter_CSTA_d;

  /* TransferFcn: '<S42>/Stick Prefilter' */
  f14tmp10_B.StickPrefilter_p = f14tmp10_P.StickPrefilter_C_i*
    f14tmp10_X.StickPrefilter_CSTATE_o;

  /* TransferFcn: '<S42>/Pitch Rate Lead Filter' */
  f14tmp10_B.PitchRateLeadFilter_a = f14tmp10_P.PitchRateLeadFilter_D_m*
    f14tmp10_B.TransferFcn1_n;
  f14tmp10_B.PitchRateLeadFilter_a += f14tmp10_P.PitchRateLeadFilter_C_m*
    f14tmp10_X.PitchRateLeadFilter_CSTATE_a;

  /* Gain: '<S42>/Gain2' */
  f14tmp10_B.Gain2_m = f14tmp10_P.Gain2_Gain_ca *
    f14tmp10_B.PitchRateLeadFilter_a;

  /* Gain: '<S42>/Gain3' */
  f14tmp10_B.Gain3_m2 = f14tmp10_P.Gain3_Gain_gk *
    f14tmp10_B.AlphasensorLowpassFilter_p;

  /* Sum: '<S42>/Sum1' */
  f14tmp10_B.Sum1_ad = f14tmp10_B.Gain2_m + f14tmp10_B.Gain3_m2;

  /* Sum: '<S42>/Sum2' */
  f14tmp10_B.Sum2_d = f14tmp10_B.StickPrefilter_p - f14tmp10_B.Sum1_ad;

  /* Gain: '<S42>/Gain' */
  f14tmp10_B.Gain_i21 = f14tmp10_P.Gain_Gain_i * f14tmp10_B.Sum2_d;

  /* TransferFcn: '<S42>/Proportional plus integral compensator' */
  f14tmp10_B.Proportionalplusintegralcompe_l =
    f14tmp10_P.Proportionalplusintegralcomp_mq*
    f14tmp10_X.Proportionalplusintegralcompe_i;

  /* Sum: '<S42>/Sum' */
  f14tmp10_B.Sum_cy = f14tmp10_B.Gain_i21 +
    f14tmp10_B.Proportionalplusintegralcompe_l;
  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* RandomNumber: '<S45>/White Noise' */
    f14tmp10_B.WhiteNoise_lu = f14tmp10_DWork.NextOutput_c;

    /* Gain: '<S45>/Output' */
    f14tmp10_B.Output_h = f14tmp10_P.Output_Gain_c3 * f14tmp10_B.WhiteNoise_lu;
  }

  /* TransferFcn: '<S46>/Transfer Fcn.2' */
  f14tmp10_B.TransferFcn2_jt = f14tmp10_P.TransferFcn2_C_o*
    f14tmp10_X.TransferFcn2_CSTATE_aw;

  /* Gain: '<S8>/Gain5' */
  f14tmp10_B.Gain5_m = f14tmp10_P.Gain5_Gain_ld * f14tmp10_B.TransferFcn2_jt;
  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* Derivative: '<S49>/Derivative' */
  {
    real_T t = f14tmp10_rtM->Timing.t[0];
    real_T timeStampA = f14tmp10_DWork.Derivative_RWORK_o0.TimeStampA;
    real_T timeStampB = f14tmp10_DWork.Derivative_RWORK_o0.TimeStampB;
    real_T *lastU = &f14tmp10_DWork.Derivative_RWORK_o0.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp10_B.Derivative_e = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp10_DWork.Derivative_RWORK_o0.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp10_DWork.Derivative_RWORK_o0.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp10_B.Derivative_e = (f14tmp10_B.TransferFcn2_jt - *lastU++) / deltaT;
    }
  }

  /* TransferFcn: '<S46>/Transfer Fcn.1' */
  f14tmp10_B.TransferFcn1_d = f14tmp10_P.TransferFcn1_C_g1*
    f14tmp10_X.TransferFcn1_CSTATE_b;

  /* Derivative: '<S49>/Derivative1' */
  {
    real_T t = f14tmp10_rtM->Timing.t[0];
    real_T timeStampA = f14tmp10_DWork.Derivative1_RWORK_j.TimeStampA;
    real_T timeStampB = f14tmp10_DWork.Derivative1_RWORK_j.TimeStampB;
    real_T *lastU = &f14tmp10_DWork.Derivative1_RWORK_j.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp10_B.Derivative1_n = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp10_DWork.Derivative1_RWORK_j.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp10_DWork.Derivative1_RWORK_j.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp10_B.Derivative1_n = (f14tmp10_B.TransferFcn1_d - *lastU++) / deltaT;
    }
  }

  /* Gain: '<S49>/Gain1' */
  f14tmp10_B.Gain1_m = f14tmp10_P.Gain1_Gain_dw * f14tmp10_B.Derivative1_n;

  /* Product: '<S49>/Product' incorporates:
   *  Constant: '<S49>/Constant'
   */
  f14tmp10_B.Product_b2 = f14tmp10_B.TransferFcn1_d *
    f14tmp10_P.Constant_Value_f0;

  /* Sum: '<S49>/Sum1' */
  f14tmp10_B.Sum1_myl = (f14tmp10_B.Gain1_m - f14tmp10_B.Derivative_e) +
    f14tmp10_B.Product_b2;

  /* Gain: '<S49>/Gain2' */
  f14tmp10_B.Gain2_br = f14tmp10_P.Gain2_Gain_a * f14tmp10_B.Sum1_myl;
  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* SignalGenerator: '<S8>/Pilot' */
  temp = f14tmp10_P.Pilot_Frequency_o * f14tmp10_rtM->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    f14tmp10_B.Pilot_n = f14tmp10_P.Pilot_Amplitude_d;
  } else {
    f14tmp10_B.Pilot_n = -f14tmp10_P.Pilot_Amplitude_d;
  }

  /* End of SignalGenerator: '<S8>/Pilot' */

  /* Sum: '<S8>/Sum1' */
  f14tmp10_B.Sum1_ni = f14tmp10_B.Pilot_n + 0.0;
  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* TransferFcn: '<S8>/Actuator Model' */
  f14tmp10_B.ActuatorModel_n3 = f14tmp10_P.ActuatorModel_C_d*
    f14tmp10_X.ActuatorModel_CSTATE_pq;

  /* Gain: '<S46>/Gain3' */
  f14tmp10_B.Gain3_bt = f14tmp10_P.Gain3_Gain_hy * f14tmp10_B.TransferFcn1_d;

  /* Gain: '<S46>/Gain4' */
  f14tmp10_B.Gain4_k = f14tmp10_P.Gain4_Gain_m * f14tmp10_B.TransferFcn2_jt;

  /* Gain: '<S46>/Gain5' */
  f14tmp10_B.Gain5_n = f14tmp10_P.Gain5_Gain_d * f14tmp10_B.ActuatorModel_n3;

  /* Gain: '<S46>/Gain6' */
  f14tmp10_B.Gain6_a = f14tmp10_P.Gain6_Gain_e * f14tmp10_B.ActuatorModel_n3;

  /* TransferFcn: '<S48>/W-gust model' */
  f14tmp10_B.Wgustmodel_hc = f14tmp10_P.Wgustmodel_C_b[0]*
    f14tmp10_X.Wgustmodel_CSTATE_c[0]
    + f14tmp10_P.Wgustmodel_C_b[1]*f14tmp10_X.Wgustmodel_CSTATE_c[1];

  /* Gain: '<S8>/Gain' */
  f14tmp10_B.Gain_kd = f14tmp10_P.Gain_Gain_ae * f14tmp10_B.Wgustmodel_hc;

  /* Sum: '<S46>/Sum1' */
  f14tmp10_B.Sum1_m5 = (f14tmp10_B.Gain5_n - f14tmp10_B.Gain_kd) +
    f14tmp10_B.Gain3_bt;

  /* Gain: '<S8>/Gain2' */
  f14tmp10_B.Gain2_fh = f14tmp10_P.Gain2_Gain_eg * f14tmp10_B.Wgustmodel_hc;

  /* TransferFcn: '<S48>/Q-gust model' */
  f14tmp10_B.Qgustmodel_a = f14tmp10_P.Qgustmodel_D_e*f14tmp10_B.Wgustmodel_hc;
  f14tmp10_B.Qgustmodel_a += f14tmp10_P.Qgustmodel_C_i*
    f14tmp10_X.Qgustmodel_CSTATE_f;

  /* Gain: '<S8>/Gain1' */
  f14tmp10_B.Gain1_j = f14tmp10_P.Gain1_Gain_j * f14tmp10_B.Qgustmodel_a;

  /* Sum: '<S8>/Sum' */
  f14tmp10_B.Sum_le = f14tmp10_B.Gain2_fh + f14tmp10_B.Gain1_j;

  /* Sum: '<S46>/Sum2' */
  f14tmp10_B.Sum2_m = (f14tmp10_B.Gain4_k - f14tmp10_B.Sum_le) +
    f14tmp10_B.Gain6_a;

  /* TransferFcn: '<S47>/Alpha-sensor Low-pass Filter' */
  f14tmp10_B.AlphasensorLowpassFilter_na =
    f14tmp10_P.AlphasensorLowpassFilter_C_p*
    f14tmp10_X.AlphasensorLowpassFilter_CSTA_b;

  /* TransferFcn: '<S47>/Stick Prefilter' */
  f14tmp10_B.StickPrefilter_m = f14tmp10_P.StickPrefilter_C_l*
    f14tmp10_X.StickPrefilter_CSTATE_p;

  /* TransferFcn: '<S47>/Pitch Rate Lead Filter' */
  f14tmp10_B.PitchRateLeadFilter_i = f14tmp10_P.PitchRateLeadFilter_D_bq*
    f14tmp10_B.TransferFcn1_d;
  f14tmp10_B.PitchRateLeadFilter_i += f14tmp10_P.PitchRateLeadFilter_C_j*
    f14tmp10_X.PitchRateLeadFilter_CSTATE_au;

  /* Gain: '<S47>/Gain2' */
  f14tmp10_B.Gain2_ju = f14tmp10_P.Gain2_Gain_a5 *
    f14tmp10_B.PitchRateLeadFilter_i;

  /* Gain: '<S47>/Gain3' */
  f14tmp10_B.Gain3_gr = f14tmp10_P.Gain3_Gain_d *
    f14tmp10_B.AlphasensorLowpassFilter_na;

  /* Sum: '<S47>/Sum1' */
  f14tmp10_B.Sum1_aa = f14tmp10_B.Gain2_ju + f14tmp10_B.Gain3_gr;

  /* Sum: '<S47>/Sum2' */
  f14tmp10_B.Sum2_h = f14tmp10_B.StickPrefilter_m - f14tmp10_B.Sum1_aa;

  /* Gain: '<S47>/Gain' */
  f14tmp10_B.Gain_dr = f14tmp10_P.Gain_Gain_d3 * f14tmp10_B.Sum2_h;

  /* TransferFcn: '<S47>/Proportional plus integral compensator' */
  f14tmp10_B.Proportionalplusintegralcomp_aj =
    f14tmp10_P.Proportionalplusintegralcomp_a4*
    f14tmp10_X.Proportionalplusintegralcomp_nm;

  /* Sum: '<S47>/Sum' */
  f14tmp10_B.Sum_ns = f14tmp10_B.Gain_dr +
    f14tmp10_B.Proportionalplusintegralcomp_aj;
  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* RandomNumber: '<S50>/White Noise' */
    f14tmp10_B.WhiteNoise_l4 = f14tmp10_DWork.NextOutput_d;

    /* Gain: '<S50>/Output' */
    f14tmp10_B.Output_p = f14tmp10_P.Output_Gain_c3r * f14tmp10_B.WhiteNoise_l4;
  }

  /* TransferFcn: '<S51>/Transfer Fcn.2' */
  f14tmp10_B.TransferFcn2_m = f14tmp10_P.TransferFcn2_C_am*
    f14tmp10_X.TransferFcn2_CSTATE_m;

  /* Gain: '<S9>/Gain5' */
  f14tmp10_B.Gain5_m5 = f14tmp10_P.Gain5_Gain_e * f14tmp10_B.TransferFcn2_m;
  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* Derivative: '<S54>/Derivative' */
  {
    real_T t = f14tmp10_rtM->Timing.t[0];
    real_T timeStampA = f14tmp10_DWork.Derivative_RWORK_p.TimeStampA;
    real_T timeStampB = f14tmp10_DWork.Derivative_RWORK_p.TimeStampB;
    real_T *lastU = &f14tmp10_DWork.Derivative_RWORK_p.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp10_B.Derivative_b = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp10_DWork.Derivative_RWORK_p.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp10_DWork.Derivative_RWORK_p.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp10_B.Derivative_b = (f14tmp10_B.TransferFcn2_m - *lastU++) / deltaT;
    }
  }

  /* TransferFcn: '<S51>/Transfer Fcn.1' */
  f14tmp10_B.TransferFcn1_l = f14tmp10_P.TransferFcn1_C_gr*
    f14tmp10_X.TransferFcn1_CSTATE_n;

  /* Derivative: '<S54>/Derivative1' */
  {
    real_T t = f14tmp10_rtM->Timing.t[0];
    real_T timeStampA = f14tmp10_DWork.Derivative1_RWORK_dy.TimeStampA;
    real_T timeStampB = f14tmp10_DWork.Derivative1_RWORK_dy.TimeStampB;
    real_T *lastU = &f14tmp10_DWork.Derivative1_RWORK_dy.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp10_B.Derivative1_c = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp10_DWork.Derivative1_RWORK_dy.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp10_DWork.Derivative1_RWORK_dy.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp10_B.Derivative1_c = (f14tmp10_B.TransferFcn1_l - *lastU++) / deltaT;
    }
  }

  /* Gain: '<S54>/Gain1' */
  f14tmp10_B.Gain1_ld = f14tmp10_P.Gain1_Gain_g * f14tmp10_B.Derivative1_c;

  /* Product: '<S54>/Product' incorporates:
   *  Constant: '<S54>/Constant'
   */
  f14tmp10_B.Product_a0 = f14tmp10_B.TransferFcn1_l *
    f14tmp10_P.Constant_Value_e;

  /* Sum: '<S54>/Sum1' */
  f14tmp10_B.Sum1_j = (f14tmp10_B.Gain1_ld - f14tmp10_B.Derivative_b) +
    f14tmp10_B.Product_a0;

  /* Gain: '<S54>/Gain2' */
  f14tmp10_B.Gain2_i = f14tmp10_P.Gain2_Gain_j * f14tmp10_B.Sum1_j;
  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* SignalGenerator: '<S9>/Pilot' */
  temp = f14tmp10_P.Pilot_Frequency_ay * f14tmp10_rtM->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    f14tmp10_B.Pilot_f = f14tmp10_P.Pilot_Amplitude_g;
  } else {
    f14tmp10_B.Pilot_f = -f14tmp10_P.Pilot_Amplitude_g;
  }

  /* End of SignalGenerator: '<S9>/Pilot' */

  /* Sum: '<S9>/Sum1' */
  f14tmp10_B.Sum1_jt = f14tmp10_B.Pilot_f + 0.0;
  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* TransferFcn: '<S9>/Actuator Model' */
  f14tmp10_B.ActuatorModel_d = f14tmp10_P.ActuatorModel_C_k*
    f14tmp10_X.ActuatorModel_CSTATE_fb;

  /* Gain: '<S51>/Gain3' */
  f14tmp10_B.Gain3_nn = f14tmp10_P.Gain3_Gain_o * f14tmp10_B.TransferFcn1_l;

  /* Gain: '<S51>/Gain4' */
  f14tmp10_B.Gain4_jo = f14tmp10_P.Gain4_Gain_k * f14tmp10_B.TransferFcn2_m;

  /* Gain: '<S51>/Gain5' */
  f14tmp10_B.Gain5_ky = f14tmp10_P.Gain5_Gain_oi * f14tmp10_B.ActuatorModel_d;

  /* Gain: '<S51>/Gain6' */
  f14tmp10_B.Gain6_i = f14tmp10_P.Gain6_Gain_ep * f14tmp10_B.ActuatorModel_d;

  /* TransferFcn: '<S53>/W-gust model' */
  f14tmp10_B.Wgustmodel_i = f14tmp10_P.Wgustmodel_C_aa[0]*
    f14tmp10_X.Wgustmodel_CSTATE_h[0]
    + f14tmp10_P.Wgustmodel_C_aa[1]*f14tmp10_X.Wgustmodel_CSTATE_h[1];

  /* Gain: '<S9>/Gain' */
  f14tmp10_B.Gain_l3 = f14tmp10_P.Gain_Gain_nx * f14tmp10_B.Wgustmodel_i;

  /* Sum: '<S51>/Sum1' */
  f14tmp10_B.Sum1_fl = (f14tmp10_B.Gain5_ky - f14tmp10_B.Gain_l3) +
    f14tmp10_B.Gain3_nn;

  /* Gain: '<S9>/Gain2' */
  f14tmp10_B.Gain2_jn = f14tmp10_P.Gain2_Gain_j4 * f14tmp10_B.Wgustmodel_i;

  /* TransferFcn: '<S53>/Q-gust model' */
  f14tmp10_B.Qgustmodel_l = f14tmp10_P.Qgustmodel_D_ay*f14tmp10_B.Wgustmodel_i;
  f14tmp10_B.Qgustmodel_l += f14tmp10_P.Qgustmodel_C_az*
    f14tmp10_X.Qgustmodel_CSTATE_c;

  /* Gain: '<S9>/Gain1' */
  f14tmp10_B.Gain1_g4 = f14tmp10_P.Gain1_Gain_oq * f14tmp10_B.Qgustmodel_l;

  /* Sum: '<S9>/Sum' */
  f14tmp10_B.Sum_a = f14tmp10_B.Gain2_jn + f14tmp10_B.Gain1_g4;

  /* Sum: '<S51>/Sum2' */
  f14tmp10_B.Sum2_p1 = (f14tmp10_B.Gain4_jo - f14tmp10_B.Sum_a) +
    f14tmp10_B.Gain6_i;

  /* TransferFcn: '<S52>/Alpha-sensor Low-pass Filter' */
  f14tmp10_B.AlphasensorLowpassFilter_d =
    f14tmp10_P.AlphasensorLowpassFilter_C_pz*
    f14tmp10_X.AlphasensorLowpassFilter_CSTA_j;

  /* TransferFcn: '<S52>/Stick Prefilter' */
  f14tmp10_B.StickPrefilter_ok = f14tmp10_P.StickPrefilter_C_n*
    f14tmp10_X.StickPrefilter_CSTATE_n;

  /* TransferFcn: '<S52>/Pitch Rate Lead Filter' */
  f14tmp10_B.PitchRateLeadFilter_o = f14tmp10_P.PitchRateLeadFilter_D_i*
    f14tmp10_B.TransferFcn1_l;
  f14tmp10_B.PitchRateLeadFilter_o += f14tmp10_P.PitchRateLeadFilter_C_e*
    f14tmp10_X.PitchRateLeadFilter_CSTATE_d;

  /* Gain: '<S52>/Gain2' */
  f14tmp10_B.Gain2_el = f14tmp10_P.Gain2_Gain_az *
    f14tmp10_B.PitchRateLeadFilter_o;

  /* Gain: '<S52>/Gain3' */
  f14tmp10_B.Gain3_ae = f14tmp10_P.Gain3_Gain_dp *
    f14tmp10_B.AlphasensorLowpassFilter_d;

  /* Sum: '<S52>/Sum1' */
  f14tmp10_B.Sum1_l = f14tmp10_B.Gain2_el + f14tmp10_B.Gain3_ae;

  /* Sum: '<S52>/Sum2' */
  f14tmp10_B.Sum2_fw = f14tmp10_B.StickPrefilter_ok - f14tmp10_B.Sum1_l;

  /* Gain: '<S52>/Gain' */
  f14tmp10_B.Gain_nq = f14tmp10_P.Gain_Gain_ok * f14tmp10_B.Sum2_fw;

  /* TransferFcn: '<S52>/Proportional plus integral compensator' */
  f14tmp10_B.Proportionalplusintegralcomp_ap =
    f14tmp10_P.Proportionalplusintegralcompe_f*
    f14tmp10_X.Proportionalplusintegralcompe_a;

  /* Sum: '<S52>/Sum' */
  f14tmp10_B.Sum_lq = f14tmp10_B.Gain_nq +
    f14tmp10_B.Proportionalplusintegralcomp_ap;
  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* RandomNumber: '<S55>/White Noise' */
    f14tmp10_B.WhiteNoise_lx = f14tmp10_DWork.NextOutput_g;

    /* Gain: '<S55>/Output' */
    f14tmp10_B.Output_o = f14tmp10_P.Output_Gain_cw * f14tmp10_B.WhiteNoise_lx;
  }

  /* TransferFcn: '<S56>/Transfer Fcn.2' */
  f14tmp10_B.TransferFcn2_k = f14tmp10_P.TransferFcn2_C_h*
    f14tmp10_X.TransferFcn2_CSTATE_b;

  /* Gain: '<S10>/Gain5' */
  f14tmp10_B.Gain5_cl = f14tmp10_P.Gain5_Gain_cw * f14tmp10_B.TransferFcn2_k;
  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* Derivative: '<S59>/Derivative' */
  {
    real_T t = f14tmp10_rtM->Timing.t[0];
    real_T timeStampA = f14tmp10_DWork.Derivative_RWORK_c.TimeStampA;
    real_T timeStampB = f14tmp10_DWork.Derivative_RWORK_c.TimeStampB;
    real_T *lastU = &f14tmp10_DWork.Derivative_RWORK_c.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp10_B.Derivative_c = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp10_DWork.Derivative_RWORK_c.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp10_DWork.Derivative_RWORK_c.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp10_B.Derivative_c = (f14tmp10_B.TransferFcn2_k - *lastU++) / deltaT;
    }
  }

  /* TransferFcn: '<S56>/Transfer Fcn.1' */
  f14tmp10_B.TransferFcn1_j = f14tmp10_P.TransferFcn1_C_lp*
    f14tmp10_X.TransferFcn1_CSTATE_g;

  /* Derivative: '<S59>/Derivative1' */
  {
    real_T t = f14tmp10_rtM->Timing.t[0];
    real_T timeStampA = f14tmp10_DWork.Derivative1_RWORK_n.TimeStampA;
    real_T timeStampB = f14tmp10_DWork.Derivative1_RWORK_n.TimeStampB;
    real_T *lastU = &f14tmp10_DWork.Derivative1_RWORK_n.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp10_B.Derivative1_l = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp10_DWork.Derivative1_RWORK_n.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp10_DWork.Derivative1_RWORK_n.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp10_B.Derivative1_l = (f14tmp10_B.TransferFcn1_j - *lastU++) / deltaT;
    }
  }

  /* Gain: '<S59>/Gain1' */
  f14tmp10_B.Gain1_bh = f14tmp10_P.Gain1_Gain_j1 * f14tmp10_B.Derivative1_l;

  /* Product: '<S59>/Product' incorporates:
   *  Constant: '<S59>/Constant'
   */
  f14tmp10_B.Product_f = f14tmp10_B.TransferFcn1_j * f14tmp10_P.Constant_Value_d;

  /* Sum: '<S59>/Sum1' */
  f14tmp10_B.Sum1_a3 = (f14tmp10_B.Gain1_bh - f14tmp10_B.Derivative_c) +
    f14tmp10_B.Product_f;

  /* Gain: '<S59>/Gain2' */
  f14tmp10_B.Gain2_c = f14tmp10_P.Gain2_Gain_f * f14tmp10_B.Sum1_a3;
  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* SignalGenerator: '<S10>/Pilot' */
  temp = f14tmp10_P.Pilot_Frequency_ax * f14tmp10_rtM->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    f14tmp10_B.Pilot_ci = f14tmp10_P.Pilot_Amplitude_ob;
  } else {
    f14tmp10_B.Pilot_ci = -f14tmp10_P.Pilot_Amplitude_ob;
  }

  /* End of SignalGenerator: '<S10>/Pilot' */

  /* Sum: '<S10>/Sum1' */
  f14tmp10_B.Sum1_oz = f14tmp10_B.Pilot_ci + 0.0;
  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* TransferFcn: '<S10>/Actuator Model' */
  f14tmp10_B.ActuatorModel_h = f14tmp10_P.ActuatorModel_C_e*
    f14tmp10_X.ActuatorModel_CSTATE_i;

  /* Gain: '<S56>/Gain3' */
  f14tmp10_B.Gain3_g4 = f14tmp10_P.Gain3_Gain_gx * f14tmp10_B.TransferFcn1_j;

  /* Gain: '<S56>/Gain4' */
  f14tmp10_B.Gain4_lt = f14tmp10_P.Gain4_Gain_a * f14tmp10_B.TransferFcn2_k;

  /* Gain: '<S56>/Gain5' */
  f14tmp10_B.Gain5_j = f14tmp10_P.Gain5_Gain_fc * f14tmp10_B.ActuatorModel_h;

  /* Gain: '<S56>/Gain6' */
  f14tmp10_B.Gain6_p = f14tmp10_P.Gain6_Gain_l * f14tmp10_B.ActuatorModel_h;

  /* TransferFcn: '<S58>/W-gust model' */
  f14tmp10_B.Wgustmodel_k = f14tmp10_P.Wgustmodel_C_n5[0]*
    f14tmp10_X.Wgustmodel_CSTATE_b[0]
    + f14tmp10_P.Wgustmodel_C_n5[1]*f14tmp10_X.Wgustmodel_CSTATE_b[1];

  /* Gain: '<S10>/Gain' */
  f14tmp10_B.Gain_ih = f14tmp10_P.Gain_Gain_b * f14tmp10_B.Wgustmodel_k;

  /* Sum: '<S56>/Sum1' */
  f14tmp10_B.Sum1_p = (f14tmp10_B.Gain5_j - f14tmp10_B.Gain_ih) +
    f14tmp10_B.Gain3_g4;

  /* Gain: '<S10>/Gain2' */
  f14tmp10_B.Gain2_a = f14tmp10_P.Gain2_Gain_dz * f14tmp10_B.Wgustmodel_k;

  /* TransferFcn: '<S58>/Q-gust model' */
  f14tmp10_B.Qgustmodel_gx = f14tmp10_P.Qgustmodel_D_gi*f14tmp10_B.Wgustmodel_k;
  f14tmp10_B.Qgustmodel_gx += f14tmp10_P.Qgustmodel_C_jg*
    f14tmp10_X.Qgustmodel_CSTATE_l;

  /* Gain: '<S10>/Gain1' */
  f14tmp10_B.Gain1_hc = f14tmp10_P.Gain1_Gain_pq * f14tmp10_B.Qgustmodel_gx;

  /* Sum: '<S10>/Sum' */
  f14tmp10_B.Sum_ob = f14tmp10_B.Gain2_a + f14tmp10_B.Gain1_hc;

  /* Sum: '<S56>/Sum2' */
  f14tmp10_B.Sum2_hz = (f14tmp10_B.Gain4_lt - f14tmp10_B.Sum_ob) +
    f14tmp10_B.Gain6_p;

  /* TransferFcn: '<S57>/Alpha-sensor Low-pass Filter' */
  f14tmp10_B.AlphasensorLowpassFilter_k =
    f14tmp10_P.AlphasensorLowpassFilter_C_es*
    f14tmp10_X.AlphasensorLowpassFilter_CST_iy;

  /* TransferFcn: '<S57>/Stick Prefilter' */
  f14tmp10_B.StickPrefilter_pi = f14tmp10_P.StickPrefilter_C_pz*
    f14tmp10_X.StickPrefilter_CSTATE_pb;

  /* TransferFcn: '<S57>/Pitch Rate Lead Filter' */
  f14tmp10_B.PitchRateLeadFilter_ik = f14tmp10_P.PitchRateLeadFilter_D_bk*
    f14tmp10_B.TransferFcn1_j;
  f14tmp10_B.PitchRateLeadFilter_ik += f14tmp10_P.PitchRateLeadFilter_C_h*
    f14tmp10_X.PitchRateLeadFilter_CSTATE_ak;

  /* Gain: '<S57>/Gain2' */
  f14tmp10_B.Gain2_id = f14tmp10_P.Gain2_Gain_ii *
    f14tmp10_B.PitchRateLeadFilter_ik;

  /* Gain: '<S57>/Gain3' */
  f14tmp10_B.Gain3_o = f14tmp10_P.Gain3_Gain_dg *
    f14tmp10_B.AlphasensorLowpassFilter_k;

  /* Sum: '<S57>/Sum1' */
  f14tmp10_B.Sum1_dg = f14tmp10_B.Gain2_id + f14tmp10_B.Gain3_o;

  /* Sum: '<S57>/Sum2' */
  f14tmp10_B.Sum2_j = f14tmp10_B.StickPrefilter_pi - f14tmp10_B.Sum1_dg;

  /* Gain: '<S57>/Gain' */
  f14tmp10_B.Gain_er = f14tmp10_P.Gain_Gain_ni * f14tmp10_B.Sum2_j;

  /* TransferFcn: '<S57>/Proportional plus integral compensator' */
  f14tmp10_B.Proportionalplusintegralcompe_g =
    f14tmp10_P.Proportionalplusintegralcomp_gb*
    f14tmp10_X.Proportionalplusintegralcomp_ab;

  /* Sum: '<S57>/Sum' */
  f14tmp10_B.Sum_j = f14tmp10_B.Gain_er +
    f14tmp10_B.Proportionalplusintegralcompe_g;
  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* RandomNumber: '<S60>/White Noise' */
    f14tmp10_B.WhiteNoise_f = f14tmp10_DWork.NextOutput_i;

    /* Gain: '<S60>/Output' */
    f14tmp10_B.Output_d = f14tmp10_P.Output_Gain_o * f14tmp10_B.WhiteNoise_f;
  }
}

/* Model update function */
void f14tmp10_update(void)
{
  /* Update for Derivative: '<S14>/Derivative' */
  {
    real_T timeStampA = f14tmp10_DWork.Derivative_RWORK.TimeStampA;
    real_T timeStampB = f14tmp10_DWork.Derivative_RWORK.TimeStampB;
    real_T* lastTime = &f14tmp10_DWork.Derivative_RWORK.TimeStampA;
    real_T* lastU = &f14tmp10_DWork.Derivative_RWORK.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp10_DWork.Derivative_RWORK.TimeStampB;
        lastU = &f14tmp10_DWork.Derivative_RWORK.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp10_DWork.Derivative_RWORK.TimeStampB;
        lastU = &f14tmp10_DWork.Derivative_RWORK.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp10_rtM->Timing.t[0];
    *lastU++ = f14tmp10_B.TransferFcn2;
  }

  /* Update for Derivative: '<S14>/Derivative1' */
  {
    real_T timeStampA = f14tmp10_DWork.Derivative1_RWORK.TimeStampA;
    real_T timeStampB = f14tmp10_DWork.Derivative1_RWORK.TimeStampB;
    real_T* lastTime = &f14tmp10_DWork.Derivative1_RWORK.TimeStampA;
    real_T* lastU = &f14tmp10_DWork.Derivative1_RWORK.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp10_DWork.Derivative1_RWORK.TimeStampB;
        lastU = &f14tmp10_DWork.Derivative1_RWORK.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp10_DWork.Derivative1_RWORK.TimeStampB;
        lastU = &f14tmp10_DWork.Derivative1_RWORK.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp10_rtM->Timing.t[0];
    *lastU++ = f14tmp10_B.TransferFcn1;
  }

  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* Update for RandomNumber: '<S15>/White Noise' */
    f14tmp10_DWork.NextOutput = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp10_DWork.RandSeed) * f14tmp10_P.WhiteNoise_StdDev +
      f14tmp10_P.WhiteNoise_Mean;
  }

  /* Update for Derivative: '<S19>/Derivative' */
  {
    real_T timeStampA = f14tmp10_DWork.Derivative_RWORK_f.TimeStampA;
    real_T timeStampB = f14tmp10_DWork.Derivative_RWORK_f.TimeStampB;
    real_T* lastTime = &f14tmp10_DWork.Derivative_RWORK_f.TimeStampA;
    real_T* lastU = &f14tmp10_DWork.Derivative_RWORK_f.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp10_DWork.Derivative_RWORK_f.TimeStampB;
        lastU = &f14tmp10_DWork.Derivative_RWORK_f.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp10_DWork.Derivative_RWORK_f.TimeStampB;
        lastU = &f14tmp10_DWork.Derivative_RWORK_f.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp10_rtM->Timing.t[0];
    *lastU++ = f14tmp10_B.TransferFcn2_b;
  }

  /* Update for Derivative: '<S19>/Derivative1' */
  {
    real_T timeStampA = f14tmp10_DWork.Derivative1_RWORK_o.TimeStampA;
    real_T timeStampB = f14tmp10_DWork.Derivative1_RWORK_o.TimeStampB;
    real_T* lastTime = &f14tmp10_DWork.Derivative1_RWORK_o.TimeStampA;
    real_T* lastU = &f14tmp10_DWork.Derivative1_RWORK_o.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp10_DWork.Derivative1_RWORK_o.TimeStampB;
        lastU = &f14tmp10_DWork.Derivative1_RWORK_o.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp10_DWork.Derivative1_RWORK_o.TimeStampB;
        lastU = &f14tmp10_DWork.Derivative1_RWORK_o.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp10_rtM->Timing.t[0];
    *lastU++ = f14tmp10_B.TransferFcn1_a;
  }

  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* Update for RandomNumber: '<S20>/White Noise' */
    f14tmp10_DWork.NextOutput_f = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp10_DWork.RandSeed_n) * f14tmp10_P.WhiteNoise_StdDev_n +
      f14tmp10_P.WhiteNoise_Mean_j;
  }

  /* Update for Derivative: '<S24>/Derivative' */
  {
    real_T timeStampA = f14tmp10_DWork.Derivative_RWORK_l.TimeStampA;
    real_T timeStampB = f14tmp10_DWork.Derivative_RWORK_l.TimeStampB;
    real_T* lastTime = &f14tmp10_DWork.Derivative_RWORK_l.TimeStampA;
    real_T* lastU = &f14tmp10_DWork.Derivative_RWORK_l.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp10_DWork.Derivative_RWORK_l.TimeStampB;
        lastU = &f14tmp10_DWork.Derivative_RWORK_l.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp10_DWork.Derivative_RWORK_l.TimeStampB;
        lastU = &f14tmp10_DWork.Derivative_RWORK_l.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp10_rtM->Timing.t[0];
    *lastU++ = f14tmp10_B.TransferFcn2_l;
  }

  /* Update for Derivative: '<S24>/Derivative1' */
  {
    real_T timeStampA = f14tmp10_DWork.Derivative1_RWORK_k.TimeStampA;
    real_T timeStampB = f14tmp10_DWork.Derivative1_RWORK_k.TimeStampB;
    real_T* lastTime = &f14tmp10_DWork.Derivative1_RWORK_k.TimeStampA;
    real_T* lastU = &f14tmp10_DWork.Derivative1_RWORK_k.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp10_DWork.Derivative1_RWORK_k.TimeStampB;
        lastU = &f14tmp10_DWork.Derivative1_RWORK_k.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp10_DWork.Derivative1_RWORK_k.TimeStampB;
        lastU = &f14tmp10_DWork.Derivative1_RWORK_k.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp10_rtM->Timing.t[0];
    *lastU++ = f14tmp10_B.TransferFcn1_g;
  }

  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* Update for RandomNumber: '<S25>/White Noise' */
    f14tmp10_DWork.NextOutput_h = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp10_DWork.RandSeed_e) * f14tmp10_P.WhiteNoise_StdDev_g +
      f14tmp10_P.WhiteNoise_Mean_k;
  }

  /* Update for Derivative: '<S29>/Derivative' */
  {
    real_T timeStampA = f14tmp10_DWork.Derivative_RWORK_k.TimeStampA;
    real_T timeStampB = f14tmp10_DWork.Derivative_RWORK_k.TimeStampB;
    real_T* lastTime = &f14tmp10_DWork.Derivative_RWORK_k.TimeStampA;
    real_T* lastU = &f14tmp10_DWork.Derivative_RWORK_k.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp10_DWork.Derivative_RWORK_k.TimeStampB;
        lastU = &f14tmp10_DWork.Derivative_RWORK_k.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp10_DWork.Derivative_RWORK_k.TimeStampB;
        lastU = &f14tmp10_DWork.Derivative_RWORK_k.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp10_rtM->Timing.t[0];
    *lastU++ = f14tmp10_B.TransferFcn2_j;
  }

  /* Update for Derivative: '<S29>/Derivative1' */
  {
    real_T timeStampA = f14tmp10_DWork.Derivative1_RWORK_b.TimeStampA;
    real_T timeStampB = f14tmp10_DWork.Derivative1_RWORK_b.TimeStampB;
    real_T* lastTime = &f14tmp10_DWork.Derivative1_RWORK_b.TimeStampA;
    real_T* lastU = &f14tmp10_DWork.Derivative1_RWORK_b.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp10_DWork.Derivative1_RWORK_b.TimeStampB;
        lastU = &f14tmp10_DWork.Derivative1_RWORK_b.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp10_DWork.Derivative1_RWORK_b.TimeStampB;
        lastU = &f14tmp10_DWork.Derivative1_RWORK_b.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp10_rtM->Timing.t[0];
    *lastU++ = f14tmp10_B.TransferFcn1_k;
  }

  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* Update for RandomNumber: '<S30>/White Noise' */
    f14tmp10_DWork.NextOutput_a = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp10_DWork.RandSeed_f) * f14tmp10_P.WhiteNoise_StdDev_f +
      f14tmp10_P.WhiteNoise_Mean_n;
  }

  /* Update for Derivative: '<S34>/Derivative' */
  {
    real_T timeStampA = f14tmp10_DWork.Derivative_RWORK_lc.TimeStampA;
    real_T timeStampB = f14tmp10_DWork.Derivative_RWORK_lc.TimeStampB;
    real_T* lastTime = &f14tmp10_DWork.Derivative_RWORK_lc.TimeStampA;
    real_T* lastU = &f14tmp10_DWork.Derivative_RWORK_lc.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp10_DWork.Derivative_RWORK_lc.TimeStampB;
        lastU = &f14tmp10_DWork.Derivative_RWORK_lc.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp10_DWork.Derivative_RWORK_lc.TimeStampB;
        lastU = &f14tmp10_DWork.Derivative_RWORK_lc.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp10_rtM->Timing.t[0];
    *lastU++ = f14tmp10_B.TransferFcn2_o;
  }

  /* Update for Derivative: '<S34>/Derivative1' */
  {
    real_T timeStampA = f14tmp10_DWork.Derivative1_RWORK_d.TimeStampA;
    real_T timeStampB = f14tmp10_DWork.Derivative1_RWORK_d.TimeStampB;
    real_T* lastTime = &f14tmp10_DWork.Derivative1_RWORK_d.TimeStampA;
    real_T* lastU = &f14tmp10_DWork.Derivative1_RWORK_d.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp10_DWork.Derivative1_RWORK_d.TimeStampB;
        lastU = &f14tmp10_DWork.Derivative1_RWORK_d.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp10_DWork.Derivative1_RWORK_d.TimeStampB;
        lastU = &f14tmp10_DWork.Derivative1_RWORK_d.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp10_rtM->Timing.t[0];
    *lastU++ = f14tmp10_B.TransferFcn1_i;
  }

  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* Update for RandomNumber: '<S35>/White Noise' */
    f14tmp10_DWork.NextOutput_e = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp10_DWork.RandSeed_d) * f14tmp10_P.WhiteNoise_StdDev_k +
      f14tmp10_P.WhiteNoise_Mean_b;
  }

  /* Update for Derivative: '<S39>/Derivative' */
  {
    real_T timeStampA = f14tmp10_DWork.Derivative_RWORK_j.TimeStampA;
    real_T timeStampB = f14tmp10_DWork.Derivative_RWORK_j.TimeStampB;
    real_T* lastTime = &f14tmp10_DWork.Derivative_RWORK_j.TimeStampA;
    real_T* lastU = &f14tmp10_DWork.Derivative_RWORK_j.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp10_DWork.Derivative_RWORK_j.TimeStampB;
        lastU = &f14tmp10_DWork.Derivative_RWORK_j.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp10_DWork.Derivative_RWORK_j.TimeStampB;
        lastU = &f14tmp10_DWork.Derivative_RWORK_j.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp10_rtM->Timing.t[0];
    *lastU++ = f14tmp10_B.TransferFcn2_jp;
  }

  /* Update for Derivative: '<S39>/Derivative1' */
  {
    real_T timeStampA = f14tmp10_DWork.Derivative1_RWORK_p.TimeStampA;
    real_T timeStampB = f14tmp10_DWork.Derivative1_RWORK_p.TimeStampB;
    real_T* lastTime = &f14tmp10_DWork.Derivative1_RWORK_p.TimeStampA;
    real_T* lastU = &f14tmp10_DWork.Derivative1_RWORK_p.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp10_DWork.Derivative1_RWORK_p.TimeStampB;
        lastU = &f14tmp10_DWork.Derivative1_RWORK_p.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp10_DWork.Derivative1_RWORK_p.TimeStampB;
        lastU = &f14tmp10_DWork.Derivative1_RWORK_p.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp10_rtM->Timing.t[0];
    *lastU++ = f14tmp10_B.TransferFcn1_f;
  }

  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* Update for RandomNumber: '<S40>/White Noise' */
    f14tmp10_DWork.NextOutput_k = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp10_DWork.RandSeed_j) * f14tmp10_P.WhiteNoise_StdDev_fh +
      f14tmp10_P.WhiteNoise_Mean_g;
  }

  /* Update for Derivative: '<S44>/Derivative' */
  {
    real_T timeStampA = f14tmp10_DWork.Derivative_RWORK_o.TimeStampA;
    real_T timeStampB = f14tmp10_DWork.Derivative_RWORK_o.TimeStampB;
    real_T* lastTime = &f14tmp10_DWork.Derivative_RWORK_o.TimeStampA;
    real_T* lastU = &f14tmp10_DWork.Derivative_RWORK_o.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp10_DWork.Derivative_RWORK_o.TimeStampB;
        lastU = &f14tmp10_DWork.Derivative_RWORK_o.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp10_DWork.Derivative_RWORK_o.TimeStampB;
        lastU = &f14tmp10_DWork.Derivative_RWORK_o.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp10_rtM->Timing.t[0];
    *lastU++ = f14tmp10_B.TransferFcn2_f;
  }

  /* Update for Derivative: '<S44>/Derivative1' */
  {
    real_T timeStampA = f14tmp10_DWork.Derivative1_RWORK_e.TimeStampA;
    real_T timeStampB = f14tmp10_DWork.Derivative1_RWORK_e.TimeStampB;
    real_T* lastTime = &f14tmp10_DWork.Derivative1_RWORK_e.TimeStampA;
    real_T* lastU = &f14tmp10_DWork.Derivative1_RWORK_e.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp10_DWork.Derivative1_RWORK_e.TimeStampB;
        lastU = &f14tmp10_DWork.Derivative1_RWORK_e.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp10_DWork.Derivative1_RWORK_e.TimeStampB;
        lastU = &f14tmp10_DWork.Derivative1_RWORK_e.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp10_rtM->Timing.t[0];
    *lastU++ = f14tmp10_B.TransferFcn1_n;
  }

  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* Update for RandomNumber: '<S45>/White Noise' */
    f14tmp10_DWork.NextOutput_c = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp10_DWork.RandSeed_k) * f14tmp10_P.WhiteNoise_StdDev_m +
      f14tmp10_P.WhiteNoise_Mean_jo;
  }

  /* Update for Derivative: '<S49>/Derivative' */
  {
    real_T timeStampA = f14tmp10_DWork.Derivative_RWORK_o0.TimeStampA;
    real_T timeStampB = f14tmp10_DWork.Derivative_RWORK_o0.TimeStampB;
    real_T* lastTime = &f14tmp10_DWork.Derivative_RWORK_o0.TimeStampA;
    real_T* lastU = &f14tmp10_DWork.Derivative_RWORK_o0.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp10_DWork.Derivative_RWORK_o0.TimeStampB;
        lastU = &f14tmp10_DWork.Derivative_RWORK_o0.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp10_DWork.Derivative_RWORK_o0.TimeStampB;
        lastU = &f14tmp10_DWork.Derivative_RWORK_o0.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp10_rtM->Timing.t[0];
    *lastU++ = f14tmp10_B.TransferFcn2_jt;
  }

  /* Update for Derivative: '<S49>/Derivative1' */
  {
    real_T timeStampA = f14tmp10_DWork.Derivative1_RWORK_j.TimeStampA;
    real_T timeStampB = f14tmp10_DWork.Derivative1_RWORK_j.TimeStampB;
    real_T* lastTime = &f14tmp10_DWork.Derivative1_RWORK_j.TimeStampA;
    real_T* lastU = &f14tmp10_DWork.Derivative1_RWORK_j.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp10_DWork.Derivative1_RWORK_j.TimeStampB;
        lastU = &f14tmp10_DWork.Derivative1_RWORK_j.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp10_DWork.Derivative1_RWORK_j.TimeStampB;
        lastU = &f14tmp10_DWork.Derivative1_RWORK_j.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp10_rtM->Timing.t[0];
    *lastU++ = f14tmp10_B.TransferFcn1_d;
  }

  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* Update for RandomNumber: '<S50>/White Noise' */
    f14tmp10_DWork.NextOutput_d = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp10_DWork.RandSeed_ju) * f14tmp10_P.WhiteNoise_StdDev_i +
      f14tmp10_P.WhiteNoise_Mean_i;
  }

  /* Update for Derivative: '<S54>/Derivative' */
  {
    real_T timeStampA = f14tmp10_DWork.Derivative_RWORK_p.TimeStampA;
    real_T timeStampB = f14tmp10_DWork.Derivative_RWORK_p.TimeStampB;
    real_T* lastTime = &f14tmp10_DWork.Derivative_RWORK_p.TimeStampA;
    real_T* lastU = &f14tmp10_DWork.Derivative_RWORK_p.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp10_DWork.Derivative_RWORK_p.TimeStampB;
        lastU = &f14tmp10_DWork.Derivative_RWORK_p.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp10_DWork.Derivative_RWORK_p.TimeStampB;
        lastU = &f14tmp10_DWork.Derivative_RWORK_p.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp10_rtM->Timing.t[0];
    *lastU++ = f14tmp10_B.TransferFcn2_m;
  }

  /* Update for Derivative: '<S54>/Derivative1' */
  {
    real_T timeStampA = f14tmp10_DWork.Derivative1_RWORK_dy.TimeStampA;
    real_T timeStampB = f14tmp10_DWork.Derivative1_RWORK_dy.TimeStampB;
    real_T* lastTime = &f14tmp10_DWork.Derivative1_RWORK_dy.TimeStampA;
    real_T* lastU = &f14tmp10_DWork.Derivative1_RWORK_dy.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp10_DWork.Derivative1_RWORK_dy.TimeStampB;
        lastU = &f14tmp10_DWork.Derivative1_RWORK_dy.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp10_DWork.Derivative1_RWORK_dy.TimeStampB;
        lastU = &f14tmp10_DWork.Derivative1_RWORK_dy.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp10_rtM->Timing.t[0];
    *lastU++ = f14tmp10_B.TransferFcn1_l;
  }

  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* Update for RandomNumber: '<S55>/White Noise' */
    f14tmp10_DWork.NextOutput_g = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp10_DWork.RandSeed_nb) * f14tmp10_P.WhiteNoise_StdDev_p +
      f14tmp10_P.WhiteNoise_Mean_f;
  }

  /* Update for Derivative: '<S59>/Derivative' */
  {
    real_T timeStampA = f14tmp10_DWork.Derivative_RWORK_c.TimeStampA;
    real_T timeStampB = f14tmp10_DWork.Derivative_RWORK_c.TimeStampB;
    real_T* lastTime = &f14tmp10_DWork.Derivative_RWORK_c.TimeStampA;
    real_T* lastU = &f14tmp10_DWork.Derivative_RWORK_c.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp10_DWork.Derivative_RWORK_c.TimeStampB;
        lastU = &f14tmp10_DWork.Derivative_RWORK_c.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp10_DWork.Derivative_RWORK_c.TimeStampB;
        lastU = &f14tmp10_DWork.Derivative_RWORK_c.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp10_rtM->Timing.t[0];
    *lastU++ = f14tmp10_B.TransferFcn2_k;
  }

  /* Update for Derivative: '<S59>/Derivative1' */
  {
    real_T timeStampA = f14tmp10_DWork.Derivative1_RWORK_n.TimeStampA;
    real_T timeStampB = f14tmp10_DWork.Derivative1_RWORK_n.TimeStampB;
    real_T* lastTime = &f14tmp10_DWork.Derivative1_RWORK_n.TimeStampA;
    real_T* lastU = &f14tmp10_DWork.Derivative1_RWORK_n.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp10_DWork.Derivative1_RWORK_n.TimeStampB;
        lastU = &f14tmp10_DWork.Derivative1_RWORK_n.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp10_DWork.Derivative1_RWORK_n.TimeStampB;
        lastU = &f14tmp10_DWork.Derivative1_RWORK_n.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp10_rtM->Timing.t[0];
    *lastU++ = f14tmp10_B.TransferFcn1_j;
  }

  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* Update for RandomNumber: '<S60>/White Noise' */
    f14tmp10_DWork.NextOutput_i = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp10_DWork.RandSeed_ju4) * f14tmp10_P.WhiteNoise_StdDev_g0 +
      f14tmp10_P.WhiteNoise_Mean_o;
  }

  if (rtmIsMajorTimeStep(f14tmp10_rtM)) {
    rt_ertODEUpdateContinuousStates(&f14tmp10_rtM->solverInfo);
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
  if (!(++f14tmp10_rtM->Timing.clockTick0)) {
    ++f14tmp10_rtM->Timing.clockTickH0;
  }

  f14tmp10_rtM->Timing.t[0] = rtsiGetSolverStopTime(&f14tmp10_rtM->solverInfo);

  {
    /* Update absolute timer for sample time: [0.01s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++f14tmp10_rtM->Timing.clockTick1)) {
      ++f14tmp10_rtM->Timing.clockTickH1;
    }

    f14tmp10_rtM->Timing.t[1] = f14tmp10_rtM->Timing.clockTick1 *
      f14tmp10_rtM->Timing.stepSize1 + f14tmp10_rtM->Timing.clockTickH1 *
      f14tmp10_rtM->Timing.stepSize1 * 4294967296.0;
  }

  if (rtmIsMajorTimeStep(f14tmp10_rtM) &&
      f14tmp10_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* Update absolute timer for sample time: [0.1s, 0.0s] */
    /* The "clockTick2" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick2"
     * and "Timing.stepSize2". Size of "clockTick2" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick2 and the high bits
     * Timing.clockTickH2. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++f14tmp10_rtM->Timing.clockTick2)) {
      ++f14tmp10_rtM->Timing.clockTickH2;
    }

    f14tmp10_rtM->Timing.t[2] = f14tmp10_rtM->Timing.clockTick2 *
      f14tmp10_rtM->Timing.stepSize2 + f14tmp10_rtM->Timing.clockTickH2 *
      f14tmp10_rtM->Timing.stepSize2 * 4294967296.0;
  }

  rate_scheduler();
}

/* Derivatives for root system: '<Root>' */
void f14tmp10_derivatives(void)
{
  /* Derivatives for TransferFcn: '<S11>/Transfer Fcn.2' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE = f14tmp10_B.Sum1_o;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE += (f14tmp10_P.TransferFcn2_A)*
      f14tmp10_X.TransferFcn2_CSTATE;
  }

  /* Derivatives for TransferFcn: '<S11>/Transfer Fcn.1' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE = f14tmp10_B.Sum2;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE += (f14tmp10_P.TransferFcn1_A)*
      f14tmp10_X.TransferFcn1_CSTATE;
  }

  /* Derivatives for TransferFcn: '<S1>/Actuator Model' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE = f14tmp10_B.Sum_n;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE += (f14tmp10_P.ActuatorModel_A)*
      f14tmp10_X.ActuatorModel_CSTATE;
  }

  /* Derivatives for TransferFcn: '<S13>/W-gust model' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE[0] = f14tmp10_B.Output;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE[0] += (f14tmp10_P.Wgustmodel_A[0])*
      f14tmp10_X.Wgustmodel_CSTATE[0] + (f14tmp10_P.Wgustmodel_A[1])*
      f14tmp10_X.Wgustmodel_CSTATE[1];
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE[1]= f14tmp10_X.Wgustmodel_CSTATE[0];
  }

  /* Derivatives for TransferFcn: '<S13>/Q-gust model' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE = f14tmp10_B.Wgustmodel;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE += (f14tmp10_P.Qgustmodel_A)*
      f14tmp10_X.Qgustmodel_CSTATE;
  }

  /* Derivatives for TransferFcn: '<S12>/Alpha-sensor Low-pass Filter' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CSTATE = f14tmp10_B.Gain5;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CSTATE +=
      (f14tmp10_P.AlphasensorLowpassFilter_A)*
      f14tmp10_X.AlphasensorLowpassFilter_CSTATE;
  }

  /* Derivatives for TransferFcn: '<S12>/Stick Prefilter' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE = f14tmp10_B.Sum1_k;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE += (f14tmp10_P.StickPrefilter_A)*
      f14tmp10_X.StickPrefilter_CSTATE;
  }

  /* Derivatives for TransferFcn: '<S12>/Pitch Rate Lead Filter' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE = f14tmp10_B.TransferFcn1;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE += (f14tmp10_P.PitchRateLeadFilter_A)*
      f14tmp10_X.PitchRateLeadFilter_CSTATE;
  }

  /* Derivatives for TransferFcn: '<S12>/Proportional plus integral compensator' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompens = f14tmp10_B.Sum2_f;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompens +=
      (f14tmp10_P.Proportionalplusintegralcompens)*
      f14tmp10_X.Proportionalplusintegralcompens;
  }

  /* Derivatives for TransferFcn: '<S16>/Transfer Fcn.2' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_h = f14tmp10_B.Sum1_e;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_h += (f14tmp10_P.TransferFcn2_A_j)*
      f14tmp10_X.TransferFcn2_CSTATE_h;
  }

  /* Derivatives for TransferFcn: '<S16>/Transfer Fcn.1' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_p = f14tmp10_B.Sum2_c;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_p += (f14tmp10_P.TransferFcn1_A_n)*
      f14tmp10_X.TransferFcn1_CSTATE_p;
  }

  /* Derivatives for TransferFcn: '<S2>/Actuator Model' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_a = f14tmp10_B.Sum_l;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_a += (f14tmp10_P.ActuatorModel_A_j)*
      f14tmp10_X.ActuatorModel_CSTATE_a;
  }

  /* Derivatives for TransferFcn: '<S18>/W-gust model' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_f[0] = f14tmp10_B.Output_e;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_f[0] += (f14tmp10_P.Wgustmodel_A_l[0])*
      f14tmp10_X.Wgustmodel_CSTATE_f[0]
      + (f14tmp10_P.Wgustmodel_A_l[1])*f14tmp10_X.Wgustmodel_CSTATE_f[1];
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_f[1]= f14tmp10_X.Wgustmodel_CSTATE_f[0];
  }

  /* Derivatives for TransferFcn: '<S18>/Q-gust model' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_d = f14tmp10_B.Wgustmodel_j;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_d += (f14tmp10_P.Qgustmodel_A_e)*
      f14tmp10_X.Qgustmodel_CSTATE_d;
  }

  /* Derivatives for TransferFcn: '<S17>/Alpha-sensor Low-pass Filter' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CSTA_g = f14tmp10_B.Gain5_h;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CSTA_g +=
      (f14tmp10_P.AlphasensorLowpassFilter_A_d)*
      f14tmp10_X.AlphasensorLowpassFilter_CSTA_g;
  }

  /* Derivatives for TransferFcn: '<S17>/Stick Prefilter' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_a = f14tmp10_B.Sum1_n;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_a += (f14tmp10_P.StickPrefilter_A_c)*
      f14tmp10_X.StickPrefilter_CSTATE_a;
  }

  /* Derivatives for TransferFcn: '<S17>/Pitch Rate Lead Filter' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_k = f14tmp10_B.TransferFcn1_a;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_k += (f14tmp10_P.PitchRateLeadFilter_A_c)*
      f14tmp10_X.PitchRateLeadFilter_CSTATE_k;
  }

  /* Derivatives for TransferFcn: '<S17>/Proportional plus integral compensator' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompe_n = f14tmp10_B.Sum2_k;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompe_n +=
      (f14tmp10_P.Proportionalplusintegralcompe_d)*
      f14tmp10_X.Proportionalplusintegralcompe_n;
  }

  /* Derivatives for TransferFcn: '<S21>/Transfer Fcn.2' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_n = f14tmp10_B.Sum1_dr;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_n += (f14tmp10_P.TransferFcn2_A_l)*
      f14tmp10_X.TransferFcn2_CSTATE_n;
  }

  /* Derivatives for TransferFcn: '<S21>/Transfer Fcn.1' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_k = f14tmp10_B.Sum2_o;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_k += (f14tmp10_P.TransferFcn1_A_d)*
      f14tmp10_X.TransferFcn1_CSTATE_k;
  }

  /* Derivatives for TransferFcn: '<S3>/Actuator Model' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_f = f14tmp10_B.Sum_o;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_f += (f14tmp10_P.ActuatorModel_A_g)*
      f14tmp10_X.ActuatorModel_CSTATE_f;
  }

  /* Derivatives for TransferFcn: '<S23>/W-gust model' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_i[0] = f14tmp10_B.Output_c;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_i[0] += (f14tmp10_P.Wgustmodel_A_m[0])*
      f14tmp10_X.Wgustmodel_CSTATE_i[0]
      + (f14tmp10_P.Wgustmodel_A_m[1])*f14tmp10_X.Wgustmodel_CSTATE_i[1];
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_i[1]= f14tmp10_X.Wgustmodel_CSTATE_i[0];
  }

  /* Derivatives for TransferFcn: '<S23>/Q-gust model' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_k = f14tmp10_B.Wgustmodel_e;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_k += (f14tmp10_P.Qgustmodel_A_b)*
      f14tmp10_X.Qgustmodel_CSTATE_k;
  }

  /* Derivatives for TransferFcn: '<S22>/Alpha-sensor Low-pass Filter' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CSTA_i = f14tmp10_B.Gain5_p;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CSTA_i +=
      (f14tmp10_P.AlphasensorLowpassFilter_A_c)*
      f14tmp10_X.AlphasensorLowpassFilter_CSTA_i;
  }

  /* Derivatives for TransferFcn: '<S22>/Stick Prefilter' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_j = f14tmp10_B.Sum1_n0;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_j += (f14tmp10_P.StickPrefilter_A_e)*
      f14tmp10_X.StickPrefilter_CSTATE_j;
  }

  /* Derivatives for TransferFcn: '<S22>/Pitch Rate Lead Filter' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_n = f14tmp10_B.TransferFcn1_g;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_n += (f14tmp10_P.PitchRateLeadFilter_A_i)*
      f14tmp10_X.PitchRateLeadFilter_CSTATE_n;
  }

  /* Derivatives for TransferFcn: '<S22>/Proportional plus integral compensator' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompe_h = f14tmp10_B.Sum2_g;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompe_h +=
      (f14tmp10_P.Proportionalplusintegralcompe_h)*
      f14tmp10_X.Proportionalplusintegralcompe_h;
  }

  /* Derivatives for TransferFcn: '<S26>/Transfer Fcn.2' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_e = f14tmp10_B.Sum1_f;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_e += (f14tmp10_P.TransferFcn2_A_jz)*
      f14tmp10_X.TransferFcn2_CSTATE_e;
  }

  /* Derivatives for TransferFcn: '<S26>/Transfer Fcn.1' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_j = f14tmp10_B.Sum2_cx;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_j += (f14tmp10_P.TransferFcn1_A_a)*
      f14tmp10_X.TransferFcn1_CSTATE_j;
  }

  /* Derivatives for TransferFcn: '<S4>/Actuator Model' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_p = f14tmp10_B.Sum_k;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_p += (f14tmp10_P.ActuatorModel_A_p)*
      f14tmp10_X.ActuatorModel_CSTATE_p;
  }

  /* Derivatives for TransferFcn: '<S28>/W-gust model' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_k[0] = f14tmp10_B.Output_k;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_k[0] += (f14tmp10_P.Wgustmodel_A_b[0])*
      f14tmp10_X.Wgustmodel_CSTATE_k[0]
      + (f14tmp10_P.Wgustmodel_A_b[1])*f14tmp10_X.Wgustmodel_CSTATE_k[1];
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_k[1]= f14tmp10_X.Wgustmodel_CSTATE_k[0];
  }

  /* Derivatives for TransferFcn: '<S28>/Q-gust model' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_a = f14tmp10_B.Wgustmodel_h;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_a += (f14tmp10_P.Qgustmodel_A_g)*
      f14tmp10_X.Qgustmodel_CSTATE_a;
  }

  /* Derivatives for TransferFcn: '<S27>/Alpha-sensor Low-pass Filter' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CSTA_k = f14tmp10_B.Gain5_k;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CSTA_k +=
      (f14tmp10_P.AlphasensorLowpassFilter_A_p)*
      f14tmp10_X.AlphasensorLowpassFilter_CSTA_k;
  }

  /* Derivatives for TransferFcn: '<S27>/Stick Prefilter' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_ju = f14tmp10_B.Sum1_dd;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_ju += (f14tmp10_P.StickPrefilter_A_d)*
      f14tmp10_X.StickPrefilter_CSTATE_ju;
  }

  /* Derivatives for TransferFcn: '<S27>/Pitch Rate Lead Filter' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_e = f14tmp10_B.TransferFcn1_k;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_e += (f14tmp10_P.PitchRateLeadFilter_A_p)*
      f14tmp10_X.PitchRateLeadFilter_CSTATE_e;
  }

  /* Derivatives for TransferFcn: '<S27>/Proportional plus integral compensator' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompe_j = f14tmp10_B.Sum2_gm;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompe_j +=
      (f14tmp10_P.Proportionalplusintegralcomp_kg)*
      f14tmp10_X.Proportionalplusintegralcompe_j;
  }

  /* Derivatives for TransferFcn: '<S31>/Transfer Fcn.2' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_k = f14tmp10_B.Sum1_g;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_k += (f14tmp10_P.TransferFcn2_A_c)*
      f14tmp10_X.TransferFcn2_CSTATE_k;
  }

  /* Derivatives for TransferFcn: '<S31>/Transfer Fcn.1' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_pe = f14tmp10_B.Sum2_oa;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_pe += (f14tmp10_P.TransferFcn1_A_o)*
      f14tmp10_X.TransferFcn1_CSTATE_pe;
  }

  /* Derivatives for TransferFcn: '<S5>/Actuator Model' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_o = f14tmp10_B.Sum_m;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_o += (f14tmp10_P.ActuatorModel_A_gl)*
      f14tmp10_X.ActuatorModel_CSTATE_o;
  }

  /* Derivatives for TransferFcn: '<S33>/W-gust model' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_if[0] = f14tmp10_B.Output_a;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_if[0] += (f14tmp10_P.Wgustmodel_A_lv[0])*
      f14tmp10_X.Wgustmodel_CSTATE_if[0]
      + (f14tmp10_P.Wgustmodel_A_lv[1])*f14tmp10_X.Wgustmodel_CSTATE_if[1];
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_if[1]= f14tmp10_X.Wgustmodel_CSTATE_if[0];
  }

  /* Derivatives for TransferFcn: '<S33>/Q-gust model' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_m = f14tmp10_B.Wgustmodel_o;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_m += (f14tmp10_P.Qgustmodel_A_gl)*
      f14tmp10_X.Qgustmodel_CSTATE_m;
  }

  /* Derivatives for TransferFcn: '<S32>/Alpha-sensor Low-pass Filter' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CST_ku = f14tmp10_B.Gain5_c;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CST_ku +=
      (f14tmp10_P.AlphasensorLowpassFilter_A_a)*
      f14tmp10_X.AlphasensorLowpassFilter_CST_ku;
  }

  /* Derivatives for TransferFcn: '<S32>/Stick Prefilter' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_m = f14tmp10_B.Sum1_h;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_m += (f14tmp10_P.StickPrefilter_A_ee)*
      f14tmp10_X.StickPrefilter_CSTATE_m;
  }

  /* Derivatives for TransferFcn: '<S32>/Pitch Rate Lead Filter' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_f = f14tmp10_B.TransferFcn1_i;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_f += (f14tmp10_P.PitchRateLeadFilter_A_m)*
      f14tmp10_X.PitchRateLeadFilter_CSTATE_f;
  }

  /* Derivatives for TransferFcn: '<S32>/Proportional plus integral compensator' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompe_k = f14tmp10_B.Sum2_f5;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompe_k +=
      (f14tmp10_P.Proportionalplusintegralcomp_mw)*
      f14tmp10_X.Proportionalplusintegralcompe_k;
  }

  /* Derivatives for TransferFcn: '<S36>/Transfer Fcn.2' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_a = f14tmp10_B.Sum1_o3;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_a += (f14tmp10_P.TransferFcn2_A_lz)*
      f14tmp10_X.TransferFcn2_CSTATE_a;
  }

  /* Derivatives for TransferFcn: '<S36>/Transfer Fcn.1' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_i = f14tmp10_B.Sum2_p;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_i += (f14tmp10_P.TransferFcn1_A_b)*
      f14tmp10_X.TransferFcn1_CSTATE_i;
  }

  /* Derivatives for TransferFcn: '<S6>/Actuator Model' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_g = f14tmp10_B.Sum_c;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_g += (f14tmp10_P.ActuatorModel_A_o)*
      f14tmp10_X.ActuatorModel_CSTATE_g;
  }

  /* Derivatives for TransferFcn: '<S38>/W-gust model' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_iv[0] = f14tmp10_B.Output_b;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_iv[0] += (f14tmp10_P.Wgustmodel_A_e[0])*
      f14tmp10_X.Wgustmodel_CSTATE_iv[0]
      + (f14tmp10_P.Wgustmodel_A_e[1])*f14tmp10_X.Wgustmodel_CSTATE_iv[1];
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_iv[1]= f14tmp10_X.Wgustmodel_CSTATE_iv[0];
  }

  /* Derivatives for TransferFcn: '<S38>/Q-gust model' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_o = f14tmp10_B.Wgustmodel_o4;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_o += (f14tmp10_P.Qgustmodel_A_a)*
      f14tmp10_X.Qgustmodel_CSTATE_o;
  }

  /* Derivatives for TransferFcn: '<S37>/Alpha-sensor Low-pass Filter' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CSTA_p = f14tmp10_B.Gain5_o4;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CSTA_p +=
      (f14tmp10_P.AlphasensorLowpassFilter_A_o)*
      f14tmp10_X.AlphasensorLowpassFilter_CSTA_p;
  }

  /* Derivatives for TransferFcn: '<S37>/Stick Prefilter' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_ah = f14tmp10_B.Sum1_fi;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_ah += (f14tmp10_P.StickPrefilter_A_n)*
      f14tmp10_X.StickPrefilter_CSTATE_ah;
  }

  /* Derivatives for TransferFcn: '<S37>/Pitch Rate Lead Filter' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_p = f14tmp10_B.TransferFcn1_f;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_p += (f14tmp10_P.PitchRateLeadFilter_A_it)*
      f14tmp10_X.PitchRateLeadFilter_CSTATE_p;
  }

  /* Derivatives for TransferFcn: '<S37>/Proportional plus integral compensator' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Proportionalplusintegralcomp_jw = f14tmp10_B.Sum2_oh;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Proportionalplusintegralcomp_jw +=
      (f14tmp10_P.Proportionalplusintegralcomp_lo)*
      f14tmp10_X.Proportionalplusintegralcomp_jw;
  }

  /* Derivatives for TransferFcn: '<S41>/Transfer Fcn.2' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_l = f14tmp10_B.Sum1_n02;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_l += (f14tmp10_P.TransferFcn2_A_m)*
      f14tmp10_X.TransferFcn2_CSTATE_l;
  }

  /* Derivatives for TransferFcn: '<S41>/Transfer Fcn.1' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_je = f14tmp10_B.Sum2_b;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_je += (f14tmp10_P.TransferFcn1_A_c)*
      f14tmp10_X.TransferFcn1_CSTATE_je;
  }

  /* Derivatives for TransferFcn: '<S7>/Actuator Model' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_fk = f14tmp10_B.Sum_cy;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_fk += (f14tmp10_P.ActuatorModel_A_gz)*
      f14tmp10_X.ActuatorModel_CSTATE_fk;
  }

  /* Derivatives for TransferFcn: '<S43>/W-gust model' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_g[0] = f14tmp10_B.Output_h;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_g[0] += (f14tmp10_P.Wgustmodel_A_c[0])*
      f14tmp10_X.Wgustmodel_CSTATE_g[0]
      + (f14tmp10_P.Wgustmodel_A_c[1])*f14tmp10_X.Wgustmodel_CSTATE_g[1];
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_g[1]= f14tmp10_X.Wgustmodel_CSTATE_g[0];
  }

  /* Derivatives for TransferFcn: '<S43>/Q-gust model' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_e = f14tmp10_B.Wgustmodel_f;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_e += (f14tmp10_P.Qgustmodel_A_el)*
      f14tmp10_X.Qgustmodel_CSTATE_e;
  }

  /* Derivatives for TransferFcn: '<S42>/Alpha-sensor Low-pass Filter' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CSTA_d = f14tmp10_B.Gain5_e;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CSTA_d +=
      (f14tmp10_P.AlphasensorLowpassFilter_A_j)*
      f14tmp10_X.AlphasensorLowpassFilter_CSTA_d;
  }

  /* Derivatives for TransferFcn: '<S42>/Stick Prefilter' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_o = f14tmp10_B.Sum1_ec;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_o += (f14tmp10_P.StickPrefilter_A_cc)*
      f14tmp10_X.StickPrefilter_CSTATE_o;
  }

  /* Derivatives for TransferFcn: '<S42>/Pitch Rate Lead Filter' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_a = f14tmp10_B.TransferFcn1_n;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_a += (f14tmp10_P.PitchRateLeadFilter_A_g)*
      f14tmp10_X.PitchRateLeadFilter_CSTATE_a;
  }

  /* Derivatives for TransferFcn: '<S42>/Proportional plus integral compensator' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompe_i = f14tmp10_B.Sum2_d;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompe_i +=
      (f14tmp10_P.Proportionalplusintegralcompe_c)*
      f14tmp10_X.Proportionalplusintegralcompe_i;
  }

  /* Derivatives for TransferFcn: '<S46>/Transfer Fcn.2' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_aw = f14tmp10_B.Sum1_m5;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_aw += (f14tmp10_P.TransferFcn2_A_e)*
      f14tmp10_X.TransferFcn2_CSTATE_aw;
  }

  /* Derivatives for TransferFcn: '<S46>/Transfer Fcn.1' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_b = f14tmp10_B.Sum2_m;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_b += (f14tmp10_P.TransferFcn1_A_f)*
      f14tmp10_X.TransferFcn1_CSTATE_b;
  }

  /* Derivatives for TransferFcn: '<S8>/Actuator Model' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_pq = f14tmp10_B.Sum_ns;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_pq += (f14tmp10_P.ActuatorModel_A_pn)*
      f14tmp10_X.ActuatorModel_CSTATE_pq;
  }

  /* Derivatives for TransferFcn: '<S48>/W-gust model' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_c[0] = f14tmp10_B.Output_p;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_c[0] += (f14tmp10_P.Wgustmodel_A_g[0])*
      f14tmp10_X.Wgustmodel_CSTATE_c[0]
      + (f14tmp10_P.Wgustmodel_A_g[1])*f14tmp10_X.Wgustmodel_CSTATE_c[1];
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_c[1]= f14tmp10_X.Wgustmodel_CSTATE_c[0];
  }

  /* Derivatives for TransferFcn: '<S48>/Q-gust model' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_f = f14tmp10_B.Wgustmodel_hc;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_f += (f14tmp10_P.Qgustmodel_A_d)*
      f14tmp10_X.Qgustmodel_CSTATE_f;
  }

  /* Derivatives for TransferFcn: '<S47>/Alpha-sensor Low-pass Filter' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CSTA_b = f14tmp10_B.Gain5_m;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CSTA_b +=
      (f14tmp10_P.AlphasensorLowpassFilter_A_n)*
      f14tmp10_X.AlphasensorLowpassFilter_CSTA_b;
  }

  /* Derivatives for TransferFcn: '<S47>/Stick Prefilter' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_p = f14tmp10_B.Sum1_ni;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_p += (f14tmp10_P.StickPrefilter_A_ng)*
      f14tmp10_X.StickPrefilter_CSTATE_p;
  }

  /* Derivatives for TransferFcn: '<S47>/Pitch Rate Lead Filter' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_au = f14tmp10_B.TransferFcn1_d;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_au += (f14tmp10_P.PitchRateLeadFilter_A_l)*
      f14tmp10_X.PitchRateLeadFilter_CSTATE_au;
  }

  /* Derivatives for TransferFcn: '<S47>/Proportional plus integral compensator' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Proportionalplusintegralcomp_nm = f14tmp10_B.Sum2_h;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Proportionalplusintegralcomp_nm +=
      (f14tmp10_P.Proportionalplusintegralcomp_p1)*
      f14tmp10_X.Proportionalplusintegralcomp_nm;
  }

  /* Derivatives for TransferFcn: '<S51>/Transfer Fcn.2' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_m = f14tmp10_B.Sum1_fl;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_m += (f14tmp10_P.TransferFcn2_A_ja)*
      f14tmp10_X.TransferFcn2_CSTATE_m;
  }

  /* Derivatives for TransferFcn: '<S51>/Transfer Fcn.1' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_n = f14tmp10_B.Sum2_p1;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_n += (f14tmp10_P.TransferFcn1_A_fq)*
      f14tmp10_X.TransferFcn1_CSTATE_n;
  }

  /* Derivatives for TransferFcn: '<S9>/Actuator Model' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_fb = f14tmp10_B.Sum_lq;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_fb += (f14tmp10_P.ActuatorModel_A_b)*
      f14tmp10_X.ActuatorModel_CSTATE_fb;
  }

  /* Derivatives for TransferFcn: '<S53>/W-gust model' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_h[0] = f14tmp10_B.Output_o;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_h[0] += (f14tmp10_P.Wgustmodel_A_d[0])*
      f14tmp10_X.Wgustmodel_CSTATE_h[0]
      + (f14tmp10_P.Wgustmodel_A_d[1])*f14tmp10_X.Wgustmodel_CSTATE_h[1];
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_h[1]= f14tmp10_X.Wgustmodel_CSTATE_h[0];
  }

  /* Derivatives for TransferFcn: '<S53>/Q-gust model' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_c = f14tmp10_B.Wgustmodel_i;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_c += (f14tmp10_P.Qgustmodel_A_m)*
      f14tmp10_X.Qgustmodel_CSTATE_c;
  }

  /* Derivatives for TransferFcn: '<S52>/Alpha-sensor Low-pass Filter' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CSTA_j = f14tmp10_B.Gain5_m5;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CSTA_j +=
      (f14tmp10_P.AlphasensorLowpassFilter_A_l)*
      f14tmp10_X.AlphasensorLowpassFilter_CSTA_j;
  }

  /* Derivatives for TransferFcn: '<S52>/Stick Prefilter' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_n = f14tmp10_B.Sum1_jt;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_n += (f14tmp10_P.StickPrefilter_A_m)*
      f14tmp10_X.StickPrefilter_CSTATE_n;
  }

  /* Derivatives for TransferFcn: '<S52>/Pitch Rate Lead Filter' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_d = f14tmp10_B.TransferFcn1_l;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_d += (f14tmp10_P.PitchRateLeadFilter_A_f)*
      f14tmp10_X.PitchRateLeadFilter_CSTATE_d;
  }

  /* Derivatives for TransferFcn: '<S52>/Proportional plus integral compensator' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompe_a = f14tmp10_B.Sum2_fw;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompe_a +=
      (f14tmp10_P.Proportionalplusintegralcomp_oy)*
      f14tmp10_X.Proportionalplusintegralcompe_a;
  }

  /* Derivatives for TransferFcn: '<S56>/Transfer Fcn.2' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_b = f14tmp10_B.Sum1_p;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_b += (f14tmp10_P.TransferFcn2_A_b)*
      f14tmp10_X.TransferFcn2_CSTATE_b;
  }

  /* Derivatives for TransferFcn: '<S56>/Transfer Fcn.1' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_g = f14tmp10_B.Sum2_hz;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_g += (f14tmp10_P.TransferFcn1_A_cm)*
      f14tmp10_X.TransferFcn1_CSTATE_g;
  }

  /* Derivatives for TransferFcn: '<S10>/Actuator Model' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_i = f14tmp10_B.Sum_j;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_i += (f14tmp10_P.ActuatorModel_A_l)*
      f14tmp10_X.ActuatorModel_CSTATE_i;
  }

  /* Derivatives for TransferFcn: '<S58>/W-gust model' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_b[0] = f14tmp10_B.Output_d;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_b[0] += (f14tmp10_P.Wgustmodel_A_p[0])*
      f14tmp10_X.Wgustmodel_CSTATE_b[0]
      + (f14tmp10_P.Wgustmodel_A_p[1])*f14tmp10_X.Wgustmodel_CSTATE_b[1];
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_b[1]= f14tmp10_X.Wgustmodel_CSTATE_b[0];
  }

  /* Derivatives for TransferFcn: '<S58>/Q-gust model' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_l = f14tmp10_B.Wgustmodel_k;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_l += (f14tmp10_P.Qgustmodel_A_bh)*
      f14tmp10_X.Qgustmodel_CSTATE_l;
  }

  /* Derivatives for TransferFcn: '<S57>/Alpha-sensor Low-pass Filter' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CST_iy = f14tmp10_B.Gain5_cl;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CST_iy +=
      (f14tmp10_P.AlphasensorLowpassFilter_A_f)*
      f14tmp10_X.AlphasensorLowpassFilter_CST_iy;
  }

  /* Derivatives for TransferFcn: '<S57>/Stick Prefilter' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_pb = f14tmp10_B.Sum1_oz;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_pb += (f14tmp10_P.StickPrefilter_A_a)*
      f14tmp10_X.StickPrefilter_CSTATE_pb;
  }

  /* Derivatives for TransferFcn: '<S57>/Pitch Rate Lead Filter' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_ak = f14tmp10_B.TransferFcn1_j;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_ak += (f14tmp10_P.PitchRateLeadFilter_A_n)*
      f14tmp10_X.PitchRateLeadFilter_CSTATE_ak;
  }

  /* Derivatives for TransferFcn: '<S57>/Proportional plus integral compensator' */
  {
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Proportionalplusintegralcomp_ab = f14tmp10_B.Sum2_j;
    ((StateDerivatives_f14tmp10 *) f14tmp10_rtM->ModelData.derivs)
      ->Proportionalplusintegralcomp_ab +=
      (f14tmp10_P.Proportionalplusintegralcomp_io)*
      f14tmp10_X.Proportionalplusintegralcomp_ab;
  }
}

/* Model initialize function */
void f14tmp10_initialize(void)
{
  {
    uint32_T tseed;
    int32_T r;
    int32_T t;
    real_T tmp;

    /* Start for RandomNumber: '<S15>/White Noise' */
    tmp = floor(f14tmp10_P.WhiteNoise_Seed);
    if (rtIsNaN(tmp) || rtIsInf(tmp)) {
      tmp = 0.0;
    } else {
      tmp = fmod(tmp, 4.294967296E+9);
    }

    tseed = tmp < 0.0 ? (uint32_T)-(int32_T)(uint32_T)-tmp : (uint32_T)tmp;
    r = (int32_T)(tseed >> 16U);
    t = (int32_T)(tseed & 32768U);
    tseed = ((((tseed - ((uint32_T)r << 16U)) + (uint32_T)t) << 16U) + (uint32_T)
             t) + (uint32_T)r;
    if (tseed < 1U) {
      tseed = 1144108930U;
    } else {
      if (tseed > 2147483646U) {
        tseed = 2147483646U;
      }
    }

    f14tmp10_DWork.RandSeed = tseed;
    f14tmp10_DWork.NextOutput = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp10_DWork.RandSeed) * f14tmp10_P.WhiteNoise_StdDev +
      f14tmp10_P.WhiteNoise_Mean;

    /* End of Start for RandomNumber: '<S15>/White Noise' */
    /* Start for RandomNumber: '<S20>/White Noise' */
    tmp = floor(f14tmp10_P.WhiteNoise_Seed_i);
    if (rtIsNaN(tmp) || rtIsInf(tmp)) {
      tmp = 0.0;
    } else {
      tmp = fmod(tmp, 4.294967296E+9);
    }

    tseed = tmp < 0.0 ? (uint32_T)-(int32_T)(uint32_T)-tmp : (uint32_T)tmp;
    r = (int32_T)(tseed >> 16U);
    t = (int32_T)(tseed & 32768U);
    tseed = ((((tseed - ((uint32_T)r << 16U)) + (uint32_T)t) << 16U) + (uint32_T)
             t) + (uint32_T)r;
    if (tseed < 1U) {
      tseed = 1144108930U;
    } else {
      if (tseed > 2147483646U) {
        tseed = 2147483646U;
      }
    }

    f14tmp10_DWork.RandSeed_n = tseed;
    f14tmp10_DWork.NextOutput_f = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp10_DWork.RandSeed_n) * f14tmp10_P.WhiteNoise_StdDev_n +
      f14tmp10_P.WhiteNoise_Mean_j;

    /* End of Start for RandomNumber: '<S20>/White Noise' */
    /* Start for RandomNumber: '<S25>/White Noise' */
    tmp = floor(f14tmp10_P.WhiteNoise_Seed_j);
    if (rtIsNaN(tmp) || rtIsInf(tmp)) {
      tmp = 0.0;
    } else {
      tmp = fmod(tmp, 4.294967296E+9);
    }

    tseed = tmp < 0.0 ? (uint32_T)-(int32_T)(uint32_T)-tmp : (uint32_T)tmp;
    r = (int32_T)(tseed >> 16U);
    t = (int32_T)(tseed & 32768U);
    tseed = ((((tseed - ((uint32_T)r << 16U)) + (uint32_T)t) << 16U) + (uint32_T)
             t) + (uint32_T)r;
    if (tseed < 1U) {
      tseed = 1144108930U;
    } else {
      if (tseed > 2147483646U) {
        tseed = 2147483646U;
      }
    }

    f14tmp10_DWork.RandSeed_e = tseed;
    f14tmp10_DWork.NextOutput_h = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp10_DWork.RandSeed_e) * f14tmp10_P.WhiteNoise_StdDev_g +
      f14tmp10_P.WhiteNoise_Mean_k;

    /* End of Start for RandomNumber: '<S25>/White Noise' */
    /* Start for RandomNumber: '<S30>/White Noise' */
    tmp = floor(f14tmp10_P.WhiteNoise_Seed_c);
    if (rtIsNaN(tmp) || rtIsInf(tmp)) {
      tmp = 0.0;
    } else {
      tmp = fmod(tmp, 4.294967296E+9);
    }

    tseed = tmp < 0.0 ? (uint32_T)-(int32_T)(uint32_T)-tmp : (uint32_T)tmp;
    r = (int32_T)(tseed >> 16U);
    t = (int32_T)(tseed & 32768U);
    tseed = ((((tseed - ((uint32_T)r << 16U)) + (uint32_T)t) << 16U) + (uint32_T)
             t) + (uint32_T)r;
    if (tseed < 1U) {
      tseed = 1144108930U;
    } else {
      if (tseed > 2147483646U) {
        tseed = 2147483646U;
      }
    }

    f14tmp10_DWork.RandSeed_f = tseed;
    f14tmp10_DWork.NextOutput_a = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp10_DWork.RandSeed_f) * f14tmp10_P.WhiteNoise_StdDev_f +
      f14tmp10_P.WhiteNoise_Mean_n;

    /* End of Start for RandomNumber: '<S30>/White Noise' */
    /* Start for RandomNumber: '<S35>/White Noise' */
    tmp = floor(f14tmp10_P.WhiteNoise_Seed_g);
    if (rtIsNaN(tmp) || rtIsInf(tmp)) {
      tmp = 0.0;
    } else {
      tmp = fmod(tmp, 4.294967296E+9);
    }

    tseed = tmp < 0.0 ? (uint32_T)-(int32_T)(uint32_T)-tmp : (uint32_T)tmp;
    r = (int32_T)(tseed >> 16U);
    t = (int32_T)(tseed & 32768U);
    tseed = ((((tseed - ((uint32_T)r << 16U)) + (uint32_T)t) << 16U) + (uint32_T)
             t) + (uint32_T)r;
    if (tseed < 1U) {
      tseed = 1144108930U;
    } else {
      if (tseed > 2147483646U) {
        tseed = 2147483646U;
      }
    }

    f14tmp10_DWork.RandSeed_d = tseed;
    f14tmp10_DWork.NextOutput_e = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp10_DWork.RandSeed_d) * f14tmp10_P.WhiteNoise_StdDev_k +
      f14tmp10_P.WhiteNoise_Mean_b;

    /* End of Start for RandomNumber: '<S35>/White Noise' */
    /* Start for RandomNumber: '<S40>/White Noise' */
    tmp = floor(f14tmp10_P.WhiteNoise_Seed_d);
    if (rtIsNaN(tmp) || rtIsInf(tmp)) {
      tmp = 0.0;
    } else {
      tmp = fmod(tmp, 4.294967296E+9);
    }

    tseed = tmp < 0.0 ? (uint32_T)-(int32_T)(uint32_T)-tmp : (uint32_T)tmp;
    r = (int32_T)(tseed >> 16U);
    t = (int32_T)(tseed & 32768U);
    tseed = ((((tseed - ((uint32_T)r << 16U)) + (uint32_T)t) << 16U) + (uint32_T)
             t) + (uint32_T)r;
    if (tseed < 1U) {
      tseed = 1144108930U;
    } else {
      if (tseed > 2147483646U) {
        tseed = 2147483646U;
      }
    }

    f14tmp10_DWork.RandSeed_j = tseed;
    f14tmp10_DWork.NextOutput_k = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp10_DWork.RandSeed_j) * f14tmp10_P.WhiteNoise_StdDev_fh +
      f14tmp10_P.WhiteNoise_Mean_g;

    /* End of Start for RandomNumber: '<S40>/White Noise' */
    /* Start for RandomNumber: '<S45>/White Noise' */
    tmp = floor(f14tmp10_P.WhiteNoise_Seed_cc);
    if (rtIsNaN(tmp) || rtIsInf(tmp)) {
      tmp = 0.0;
    } else {
      tmp = fmod(tmp, 4.294967296E+9);
    }

    tseed = tmp < 0.0 ? (uint32_T)-(int32_T)(uint32_T)-tmp : (uint32_T)tmp;
    r = (int32_T)(tseed >> 16U);
    t = (int32_T)(tseed & 32768U);
    tseed = ((((tseed - ((uint32_T)r << 16U)) + (uint32_T)t) << 16U) + (uint32_T)
             t) + (uint32_T)r;
    if (tseed < 1U) {
      tseed = 1144108930U;
    } else {
      if (tseed > 2147483646U) {
        tseed = 2147483646U;
      }
    }

    f14tmp10_DWork.RandSeed_k = tseed;
    f14tmp10_DWork.NextOutput_c = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp10_DWork.RandSeed_k) * f14tmp10_P.WhiteNoise_StdDev_m +
      f14tmp10_P.WhiteNoise_Mean_jo;

    /* End of Start for RandomNumber: '<S45>/White Noise' */
    /* Start for RandomNumber: '<S50>/White Noise' */
    tmp = floor(f14tmp10_P.WhiteNoise_Seed_e);
    if (rtIsNaN(tmp) || rtIsInf(tmp)) {
      tmp = 0.0;
    } else {
      tmp = fmod(tmp, 4.294967296E+9);
    }

    tseed = tmp < 0.0 ? (uint32_T)-(int32_T)(uint32_T)-tmp : (uint32_T)tmp;
    r = (int32_T)(tseed >> 16U);
    t = (int32_T)(tseed & 32768U);
    tseed = ((((tseed - ((uint32_T)r << 16U)) + (uint32_T)t) << 16U) + (uint32_T)
             t) + (uint32_T)r;
    if (tseed < 1U) {
      tseed = 1144108930U;
    } else {
      if (tseed > 2147483646U) {
        tseed = 2147483646U;
      }
    }

    f14tmp10_DWork.RandSeed_ju = tseed;
    f14tmp10_DWork.NextOutput_d = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp10_DWork.RandSeed_ju) * f14tmp10_P.WhiteNoise_StdDev_i +
      f14tmp10_P.WhiteNoise_Mean_i;

    /* End of Start for RandomNumber: '<S50>/White Noise' */
    /* Start for RandomNumber: '<S55>/White Noise' */
    tmp = floor(f14tmp10_P.WhiteNoise_Seed_cm);
    if (rtIsNaN(tmp) || rtIsInf(tmp)) {
      tmp = 0.0;
    } else {
      tmp = fmod(tmp, 4.294967296E+9);
    }

    tseed = tmp < 0.0 ? (uint32_T)-(int32_T)(uint32_T)-tmp : (uint32_T)tmp;
    r = (int32_T)(tseed >> 16U);
    t = (int32_T)(tseed & 32768U);
    tseed = ((((tseed - ((uint32_T)r << 16U)) + (uint32_T)t) << 16U) + (uint32_T)
             t) + (uint32_T)r;
    if (tseed < 1U) {
      tseed = 1144108930U;
    } else {
      if (tseed > 2147483646U) {
        tseed = 2147483646U;
      }
    }

    f14tmp10_DWork.RandSeed_nb = tseed;
    f14tmp10_DWork.NextOutput_g = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp10_DWork.RandSeed_nb) * f14tmp10_P.WhiteNoise_StdDev_p +
      f14tmp10_P.WhiteNoise_Mean_f;

    /* End of Start for RandomNumber: '<S55>/White Noise' */
    /* Start for RandomNumber: '<S60>/White Noise' */
    tmp = floor(f14tmp10_P.WhiteNoise_Seed_ej);
    if (rtIsNaN(tmp) || rtIsInf(tmp)) {
      tmp = 0.0;
    } else {
      tmp = fmod(tmp, 4.294967296E+9);
    }

    tseed = tmp < 0.0 ? (uint32_T)-(int32_T)(uint32_T)-tmp : (uint32_T)tmp;
    r = (int32_T)(tseed >> 16U);
    t = (int32_T)(tseed & 32768U);
    tseed = ((((tseed - ((uint32_T)r << 16U)) + (uint32_T)t) << 16U) + (uint32_T)
             t) + (uint32_T)r;
    if (tseed < 1U) {
      tseed = 1144108930U;
    } else {
      if (tseed > 2147483646U) {
        tseed = 2147483646U;
      }
    }

    f14tmp10_DWork.RandSeed_ju4 = tseed;
    f14tmp10_DWork.NextOutput_i = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp10_DWork.RandSeed_ju4) * f14tmp10_P.WhiteNoise_StdDev_g0 +
      f14tmp10_P.WhiteNoise_Mean_o;

    /* End of Start for RandomNumber: '<S60>/White Noise' */
  }

  /* InitializeConditions for TransferFcn: '<S11>/Transfer Fcn.2' */
  f14tmp10_X.TransferFcn2_CSTATE = 0.0;

  /* InitializeConditions for Derivative: '<S14>/Derivative' */
  f14tmp10_DWork.Derivative_RWORK.TimeStampA = rtInf;
  f14tmp10_DWork.Derivative_RWORK.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S11>/Transfer Fcn.1' */
  f14tmp10_X.TransferFcn1_CSTATE = 0.0;

  /* InitializeConditions for Derivative: '<S14>/Derivative1' */
  f14tmp10_DWork.Derivative1_RWORK.TimeStampA = rtInf;
  f14tmp10_DWork.Derivative1_RWORK.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S1>/Actuator Model' */
  f14tmp10_X.ActuatorModel_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S13>/W-gust model' */
  f14tmp10_X.Wgustmodel_CSTATE[0] = 0.0;
  f14tmp10_X.Wgustmodel_CSTATE[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S13>/Q-gust model' */
  f14tmp10_X.Qgustmodel_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S12>/Alpha-sensor Low-pass Filter' */
  f14tmp10_X.AlphasensorLowpassFilter_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S12>/Stick Prefilter' */
  f14tmp10_X.StickPrefilter_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S12>/Pitch Rate Lead Filter' */
  f14tmp10_X.PitchRateLeadFilter_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S12>/Proportional plus integral compensator' */
  f14tmp10_X.Proportionalplusintegralcompens = 0.0;

  /* InitializeConditions for TransferFcn: '<S16>/Transfer Fcn.2' */
  f14tmp10_X.TransferFcn2_CSTATE_h = 0.0;

  /* InitializeConditions for Derivative: '<S19>/Derivative' */
  f14tmp10_DWork.Derivative_RWORK_f.TimeStampA = rtInf;
  f14tmp10_DWork.Derivative_RWORK_f.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S16>/Transfer Fcn.1' */
  f14tmp10_X.TransferFcn1_CSTATE_p = 0.0;

  /* InitializeConditions for Derivative: '<S19>/Derivative1' */
  f14tmp10_DWork.Derivative1_RWORK_o.TimeStampA = rtInf;
  f14tmp10_DWork.Derivative1_RWORK_o.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S2>/Actuator Model' */
  f14tmp10_X.ActuatorModel_CSTATE_a = 0.0;

  /* InitializeConditions for TransferFcn: '<S18>/W-gust model' */
  f14tmp10_X.Wgustmodel_CSTATE_f[0] = 0.0;
  f14tmp10_X.Wgustmodel_CSTATE_f[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S18>/Q-gust model' */
  f14tmp10_X.Qgustmodel_CSTATE_d = 0.0;

  /* InitializeConditions for TransferFcn: '<S17>/Alpha-sensor Low-pass Filter' */
  f14tmp10_X.AlphasensorLowpassFilter_CSTA_g = 0.0;

  /* InitializeConditions for TransferFcn: '<S17>/Stick Prefilter' */
  f14tmp10_X.StickPrefilter_CSTATE_a = 0.0;

  /* InitializeConditions for TransferFcn: '<S17>/Pitch Rate Lead Filter' */
  f14tmp10_X.PitchRateLeadFilter_CSTATE_k = 0.0;

  /* InitializeConditions for TransferFcn: '<S17>/Proportional plus integral compensator' */
  f14tmp10_X.Proportionalplusintegralcompe_n = 0.0;

  /* InitializeConditions for TransferFcn: '<S21>/Transfer Fcn.2' */
  f14tmp10_X.TransferFcn2_CSTATE_n = 0.0;

  /* InitializeConditions for Derivative: '<S24>/Derivative' */
  f14tmp10_DWork.Derivative_RWORK_l.TimeStampA = rtInf;
  f14tmp10_DWork.Derivative_RWORK_l.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S21>/Transfer Fcn.1' */
  f14tmp10_X.TransferFcn1_CSTATE_k = 0.0;

  /* InitializeConditions for Derivative: '<S24>/Derivative1' */
  f14tmp10_DWork.Derivative1_RWORK_k.TimeStampA = rtInf;
  f14tmp10_DWork.Derivative1_RWORK_k.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S3>/Actuator Model' */
  f14tmp10_X.ActuatorModel_CSTATE_f = 0.0;

  /* InitializeConditions for TransferFcn: '<S23>/W-gust model' */
  f14tmp10_X.Wgustmodel_CSTATE_i[0] = 0.0;
  f14tmp10_X.Wgustmodel_CSTATE_i[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S23>/Q-gust model' */
  f14tmp10_X.Qgustmodel_CSTATE_k = 0.0;

  /* InitializeConditions for TransferFcn: '<S22>/Alpha-sensor Low-pass Filter' */
  f14tmp10_X.AlphasensorLowpassFilter_CSTA_i = 0.0;

  /* InitializeConditions for TransferFcn: '<S22>/Stick Prefilter' */
  f14tmp10_X.StickPrefilter_CSTATE_j = 0.0;

  /* InitializeConditions for TransferFcn: '<S22>/Pitch Rate Lead Filter' */
  f14tmp10_X.PitchRateLeadFilter_CSTATE_n = 0.0;

  /* InitializeConditions for TransferFcn: '<S22>/Proportional plus integral compensator' */
  f14tmp10_X.Proportionalplusintegralcompe_h = 0.0;

  /* InitializeConditions for TransferFcn: '<S26>/Transfer Fcn.2' */
  f14tmp10_X.TransferFcn2_CSTATE_e = 0.0;

  /* InitializeConditions for Derivative: '<S29>/Derivative' */
  f14tmp10_DWork.Derivative_RWORK_k.TimeStampA = rtInf;
  f14tmp10_DWork.Derivative_RWORK_k.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S26>/Transfer Fcn.1' */
  f14tmp10_X.TransferFcn1_CSTATE_j = 0.0;

  /* InitializeConditions for Derivative: '<S29>/Derivative1' */
  f14tmp10_DWork.Derivative1_RWORK_b.TimeStampA = rtInf;
  f14tmp10_DWork.Derivative1_RWORK_b.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S4>/Actuator Model' */
  f14tmp10_X.ActuatorModel_CSTATE_p = 0.0;

  /* InitializeConditions for TransferFcn: '<S28>/W-gust model' */
  f14tmp10_X.Wgustmodel_CSTATE_k[0] = 0.0;
  f14tmp10_X.Wgustmodel_CSTATE_k[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S28>/Q-gust model' */
  f14tmp10_X.Qgustmodel_CSTATE_a = 0.0;

  /* InitializeConditions for TransferFcn: '<S27>/Alpha-sensor Low-pass Filter' */
  f14tmp10_X.AlphasensorLowpassFilter_CSTA_k = 0.0;

  /* InitializeConditions for TransferFcn: '<S27>/Stick Prefilter' */
  f14tmp10_X.StickPrefilter_CSTATE_ju = 0.0;

  /* InitializeConditions for TransferFcn: '<S27>/Pitch Rate Lead Filter' */
  f14tmp10_X.PitchRateLeadFilter_CSTATE_e = 0.0;

  /* InitializeConditions for TransferFcn: '<S27>/Proportional plus integral compensator' */
  f14tmp10_X.Proportionalplusintegralcompe_j = 0.0;

  /* InitializeConditions for TransferFcn: '<S31>/Transfer Fcn.2' */
  f14tmp10_X.TransferFcn2_CSTATE_k = 0.0;

  /* InitializeConditions for Derivative: '<S34>/Derivative' */
  f14tmp10_DWork.Derivative_RWORK_lc.TimeStampA = rtInf;
  f14tmp10_DWork.Derivative_RWORK_lc.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S31>/Transfer Fcn.1' */
  f14tmp10_X.TransferFcn1_CSTATE_pe = 0.0;

  /* InitializeConditions for Derivative: '<S34>/Derivative1' */
  f14tmp10_DWork.Derivative1_RWORK_d.TimeStampA = rtInf;
  f14tmp10_DWork.Derivative1_RWORK_d.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S5>/Actuator Model' */
  f14tmp10_X.ActuatorModel_CSTATE_o = 0.0;

  /* InitializeConditions for TransferFcn: '<S33>/W-gust model' */
  f14tmp10_X.Wgustmodel_CSTATE_if[0] = 0.0;
  f14tmp10_X.Wgustmodel_CSTATE_if[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S33>/Q-gust model' */
  f14tmp10_X.Qgustmodel_CSTATE_m = 0.0;

  /* InitializeConditions for TransferFcn: '<S32>/Alpha-sensor Low-pass Filter' */
  f14tmp10_X.AlphasensorLowpassFilter_CST_ku = 0.0;

  /* InitializeConditions for TransferFcn: '<S32>/Stick Prefilter' */
  f14tmp10_X.StickPrefilter_CSTATE_m = 0.0;

  /* InitializeConditions for TransferFcn: '<S32>/Pitch Rate Lead Filter' */
  f14tmp10_X.PitchRateLeadFilter_CSTATE_f = 0.0;

  /* InitializeConditions for TransferFcn: '<S32>/Proportional plus integral compensator' */
  f14tmp10_X.Proportionalplusintegralcompe_k = 0.0;

  /* InitializeConditions for TransferFcn: '<S36>/Transfer Fcn.2' */
  f14tmp10_X.TransferFcn2_CSTATE_a = 0.0;

  /* InitializeConditions for Derivative: '<S39>/Derivative' */
  f14tmp10_DWork.Derivative_RWORK_j.TimeStampA = rtInf;
  f14tmp10_DWork.Derivative_RWORK_j.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S36>/Transfer Fcn.1' */
  f14tmp10_X.TransferFcn1_CSTATE_i = 0.0;

  /* InitializeConditions for Derivative: '<S39>/Derivative1' */
  f14tmp10_DWork.Derivative1_RWORK_p.TimeStampA = rtInf;
  f14tmp10_DWork.Derivative1_RWORK_p.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S6>/Actuator Model' */
  f14tmp10_X.ActuatorModel_CSTATE_g = 0.0;

  /* InitializeConditions for TransferFcn: '<S38>/W-gust model' */
  f14tmp10_X.Wgustmodel_CSTATE_iv[0] = 0.0;
  f14tmp10_X.Wgustmodel_CSTATE_iv[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S38>/Q-gust model' */
  f14tmp10_X.Qgustmodel_CSTATE_o = 0.0;

  /* InitializeConditions for TransferFcn: '<S37>/Alpha-sensor Low-pass Filter' */
  f14tmp10_X.AlphasensorLowpassFilter_CSTA_p = 0.0;

  /* InitializeConditions for TransferFcn: '<S37>/Stick Prefilter' */
  f14tmp10_X.StickPrefilter_CSTATE_ah = 0.0;

  /* InitializeConditions for TransferFcn: '<S37>/Pitch Rate Lead Filter' */
  f14tmp10_X.PitchRateLeadFilter_CSTATE_p = 0.0;

  /* InitializeConditions for TransferFcn: '<S37>/Proportional plus integral compensator' */
  f14tmp10_X.Proportionalplusintegralcomp_jw = 0.0;

  /* InitializeConditions for TransferFcn: '<S41>/Transfer Fcn.2' */
  f14tmp10_X.TransferFcn2_CSTATE_l = 0.0;

  /* InitializeConditions for Derivative: '<S44>/Derivative' */
  f14tmp10_DWork.Derivative_RWORK_o.TimeStampA = rtInf;
  f14tmp10_DWork.Derivative_RWORK_o.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S41>/Transfer Fcn.1' */
  f14tmp10_X.TransferFcn1_CSTATE_je = 0.0;

  /* InitializeConditions for Derivative: '<S44>/Derivative1' */
  f14tmp10_DWork.Derivative1_RWORK_e.TimeStampA = rtInf;
  f14tmp10_DWork.Derivative1_RWORK_e.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S7>/Actuator Model' */
  f14tmp10_X.ActuatorModel_CSTATE_fk = 0.0;

  /* InitializeConditions for TransferFcn: '<S43>/W-gust model' */
  f14tmp10_X.Wgustmodel_CSTATE_g[0] = 0.0;
  f14tmp10_X.Wgustmodel_CSTATE_g[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S43>/Q-gust model' */
  f14tmp10_X.Qgustmodel_CSTATE_e = 0.0;

  /* InitializeConditions for TransferFcn: '<S42>/Alpha-sensor Low-pass Filter' */
  f14tmp10_X.AlphasensorLowpassFilter_CSTA_d = 0.0;

  /* InitializeConditions for TransferFcn: '<S42>/Stick Prefilter' */
  f14tmp10_X.StickPrefilter_CSTATE_o = 0.0;

  /* InitializeConditions for TransferFcn: '<S42>/Pitch Rate Lead Filter' */
  f14tmp10_X.PitchRateLeadFilter_CSTATE_a = 0.0;

  /* InitializeConditions for TransferFcn: '<S42>/Proportional plus integral compensator' */
  f14tmp10_X.Proportionalplusintegralcompe_i = 0.0;

  /* InitializeConditions for TransferFcn: '<S46>/Transfer Fcn.2' */
  f14tmp10_X.TransferFcn2_CSTATE_aw = 0.0;

  /* InitializeConditions for Derivative: '<S49>/Derivative' */
  f14tmp10_DWork.Derivative_RWORK_o0.TimeStampA = rtInf;
  f14tmp10_DWork.Derivative_RWORK_o0.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S46>/Transfer Fcn.1' */
  f14tmp10_X.TransferFcn1_CSTATE_b = 0.0;

  /* InitializeConditions for Derivative: '<S49>/Derivative1' */
  f14tmp10_DWork.Derivative1_RWORK_j.TimeStampA = rtInf;
  f14tmp10_DWork.Derivative1_RWORK_j.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S8>/Actuator Model' */
  f14tmp10_X.ActuatorModel_CSTATE_pq = 0.0;

  /* InitializeConditions for TransferFcn: '<S48>/W-gust model' */
  f14tmp10_X.Wgustmodel_CSTATE_c[0] = 0.0;
  f14tmp10_X.Wgustmodel_CSTATE_c[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S48>/Q-gust model' */
  f14tmp10_X.Qgustmodel_CSTATE_f = 0.0;

  /* InitializeConditions for TransferFcn: '<S47>/Alpha-sensor Low-pass Filter' */
  f14tmp10_X.AlphasensorLowpassFilter_CSTA_b = 0.0;

  /* InitializeConditions for TransferFcn: '<S47>/Stick Prefilter' */
  f14tmp10_X.StickPrefilter_CSTATE_p = 0.0;

  /* InitializeConditions for TransferFcn: '<S47>/Pitch Rate Lead Filter' */
  f14tmp10_X.PitchRateLeadFilter_CSTATE_au = 0.0;

  /* InitializeConditions for TransferFcn: '<S47>/Proportional plus integral compensator' */
  f14tmp10_X.Proportionalplusintegralcomp_nm = 0.0;

  /* InitializeConditions for TransferFcn: '<S51>/Transfer Fcn.2' */
  f14tmp10_X.TransferFcn2_CSTATE_m = 0.0;

  /* InitializeConditions for Derivative: '<S54>/Derivative' */
  f14tmp10_DWork.Derivative_RWORK_p.TimeStampA = rtInf;
  f14tmp10_DWork.Derivative_RWORK_p.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S51>/Transfer Fcn.1' */
  f14tmp10_X.TransferFcn1_CSTATE_n = 0.0;

  /* InitializeConditions for Derivative: '<S54>/Derivative1' */
  f14tmp10_DWork.Derivative1_RWORK_dy.TimeStampA = rtInf;
  f14tmp10_DWork.Derivative1_RWORK_dy.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S9>/Actuator Model' */
  f14tmp10_X.ActuatorModel_CSTATE_fb = 0.0;

  /* InitializeConditions for TransferFcn: '<S53>/W-gust model' */
  f14tmp10_X.Wgustmodel_CSTATE_h[0] = 0.0;
  f14tmp10_X.Wgustmodel_CSTATE_h[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S53>/Q-gust model' */
  f14tmp10_X.Qgustmodel_CSTATE_c = 0.0;

  /* InitializeConditions for TransferFcn: '<S52>/Alpha-sensor Low-pass Filter' */
  f14tmp10_X.AlphasensorLowpassFilter_CSTA_j = 0.0;

  /* InitializeConditions for TransferFcn: '<S52>/Stick Prefilter' */
  f14tmp10_X.StickPrefilter_CSTATE_n = 0.0;

  /* InitializeConditions for TransferFcn: '<S52>/Pitch Rate Lead Filter' */
  f14tmp10_X.PitchRateLeadFilter_CSTATE_d = 0.0;

  /* InitializeConditions for TransferFcn: '<S52>/Proportional plus integral compensator' */
  f14tmp10_X.Proportionalplusintegralcompe_a = 0.0;

  /* InitializeConditions for TransferFcn: '<S56>/Transfer Fcn.2' */
  f14tmp10_X.TransferFcn2_CSTATE_b = 0.0;

  /* InitializeConditions for Derivative: '<S59>/Derivative' */
  f14tmp10_DWork.Derivative_RWORK_c.TimeStampA = rtInf;
  f14tmp10_DWork.Derivative_RWORK_c.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S56>/Transfer Fcn.1' */
  f14tmp10_X.TransferFcn1_CSTATE_g = 0.0;

  /* InitializeConditions for Derivative: '<S59>/Derivative1' */
  f14tmp10_DWork.Derivative1_RWORK_n.TimeStampA = rtInf;
  f14tmp10_DWork.Derivative1_RWORK_n.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S10>/Actuator Model' */
  f14tmp10_X.ActuatorModel_CSTATE_i = 0.0;

  /* InitializeConditions for TransferFcn: '<S58>/W-gust model' */
  f14tmp10_X.Wgustmodel_CSTATE_b[0] = 0.0;
  f14tmp10_X.Wgustmodel_CSTATE_b[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S58>/Q-gust model' */
  f14tmp10_X.Qgustmodel_CSTATE_l = 0.0;

  /* InitializeConditions for TransferFcn: '<S57>/Alpha-sensor Low-pass Filter' */
  f14tmp10_X.AlphasensorLowpassFilter_CST_iy = 0.0;

  /* InitializeConditions for TransferFcn: '<S57>/Stick Prefilter' */
  f14tmp10_X.StickPrefilter_CSTATE_pb = 0.0;

  /* InitializeConditions for TransferFcn: '<S57>/Pitch Rate Lead Filter' */
  f14tmp10_X.PitchRateLeadFilter_CSTATE_ak = 0.0;

  /* InitializeConditions for TransferFcn: '<S57>/Proportional plus integral compensator' */
  f14tmp10_X.Proportionalplusintegralcomp_ab = 0.0;
}

/* Model terminate function */
void f14tmp10_terminate(void)
{
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/

/* Solver interface called by GRT_Main */
#ifndef USE_GENERATED_SOLVER

void rt_ODECreateIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEDestroyIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEUpdateContinuousStates(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

#endif

void MdlOutputs(int_T tid)
{
  f14tmp10_output();

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  f14tmp10_update();

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  f14tmp10_initialize();
}

void MdlTerminate(void)
{
  f14tmp10_terminate();
}

rtModel_f14tmp10 *f14tmp10(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)f14tmp10_rtM, 0,
                sizeof(rtModel_f14tmp10));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&f14tmp10_rtM->solverInfo,
                          &f14tmp10_rtM->Timing.simTimeStep);
    rtsiSetTPtr(&f14tmp10_rtM->solverInfo, &rtmGetTPtr(f14tmp10_rtM));
    rtsiSetStepSizePtr(&f14tmp10_rtM->solverInfo,
                       &f14tmp10_rtM->Timing.stepSize0);
    rtsiSetdXPtr(&f14tmp10_rtM->solverInfo, &f14tmp10_rtM->ModelData.derivs);
    rtsiSetContStatesPtr(&f14tmp10_rtM->solverInfo,
                         &f14tmp10_rtM->ModelData.contStates);
    rtsiSetNumContStatesPtr(&f14tmp10_rtM->solverInfo,
      &f14tmp10_rtM->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&f14tmp10_rtM->solverInfo, (&rtmGetErrorStatus
      (f14tmp10_rtM)));
    rtsiSetRTModelPtr(&f14tmp10_rtM->solverInfo, f14tmp10_rtM);
  }

  rtsiSetSimTimeStep(&f14tmp10_rtM->solverInfo, MAJOR_TIME_STEP);
  f14tmp10_rtM->ModelData.intgData.y = f14tmp10_rtM->ModelData.odeY;
  f14tmp10_rtM->ModelData.intgData.f[0] = f14tmp10_rtM->ModelData.odeF[0];
  f14tmp10_rtM->ModelData.intgData.f[1] = f14tmp10_rtM->ModelData.odeF[1];
  f14tmp10_rtM->ModelData.intgData.f[2] = f14tmp10_rtM->ModelData.odeF[2];
  f14tmp10_rtM->ModelData.intgData.f[3] = f14tmp10_rtM->ModelData.odeF[3];
  f14tmp10_rtM->ModelData.contStates = ((real_T *) &f14tmp10_X);
  rtsiSetSolverData(&f14tmp10_rtM->solverInfo, (void *)
                    &f14tmp10_rtM->ModelData.intgData);
  rtsiSetSolverName(&f14tmp10_rtM->solverInfo,"ode4");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = f14tmp10_rtM->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    mdlTsMap[2] = 2;
    f14tmp10_rtM->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    f14tmp10_rtM->Timing.sampleTimes = (&f14tmp10_rtM->Timing.sampleTimesArray[0]);
    f14tmp10_rtM->Timing.offsetTimes = (&f14tmp10_rtM->Timing.offsetTimesArray[0]);

    /* task periods */
    f14tmp10_rtM->Timing.sampleTimes[0] = (0.0);
    f14tmp10_rtM->Timing.sampleTimes[1] = (0.01);
    f14tmp10_rtM->Timing.sampleTimes[2] = (0.1);

    /* task offsets */
    f14tmp10_rtM->Timing.offsetTimes[0] = (0.0);
    f14tmp10_rtM->Timing.offsetTimes[1] = (0.0);
    f14tmp10_rtM->Timing.offsetTimes[2] = (0.0);
  }

  rtmSetTPtr(f14tmp10_rtM, &f14tmp10_rtM->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = f14tmp10_rtM->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    mdlSampleHits[2] = 1;
    f14tmp10_rtM->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(f14tmp10_rtM, 10.0);
  f14tmp10_rtM->Timing.stepSize0 = 0.01;
  f14tmp10_rtM->Timing.stepSize1 = 0.01;
  f14tmp10_rtM->Timing.stepSize2 = 0.1;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    f14tmp10_rtM->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(f14tmp10_rtM->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(f14tmp10_rtM->rtwLogInfo, (NULL));
    rtliSetLogT(f14tmp10_rtM->rtwLogInfo, "tout");
    rtliSetLogX(f14tmp10_rtM->rtwLogInfo, "");
    rtliSetLogXFinal(f14tmp10_rtM->rtwLogInfo, "");
    rtliSetSigLog(f14tmp10_rtM->rtwLogInfo, "");
    rtliSetLogVarNameModifier(f14tmp10_rtM->rtwLogInfo, "rt_");
    rtliSetLogFormat(f14tmp10_rtM->rtwLogInfo, 0);
    rtliSetLogMaxRows(f14tmp10_rtM->rtwLogInfo, 1000);
    rtliSetLogDecimation(f14tmp10_rtM->rtwLogInfo, 1);
    rtliSetLogY(f14tmp10_rtM->rtwLogInfo, "");
    rtliSetLogYSignalInfo(f14tmp10_rtM->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(f14tmp10_rtM->rtwLogInfo, (NULL));
  }

  f14tmp10_rtM->solverInfoPtr = (&f14tmp10_rtM->solverInfo);
  f14tmp10_rtM->Timing.stepSize = (0.01);
  rtsiSetFixedStepSize(&f14tmp10_rtM->solverInfo, 0.01);
  rtsiSetSolverMode(&f14tmp10_rtM->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  f14tmp10_rtM->ModelData.blockIO = ((void *) &f14tmp10_B);
  (void) memset(((void *) &f14tmp10_B), 0,
                sizeof(BlockIO_f14tmp10));

  /* parameters */
  f14tmp10_rtM->ModelData.defaultParam = ((real_T *)&f14tmp10_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &f14tmp10_X;
    f14tmp10_rtM->ModelData.contStates = (x);
    (void) memset((void *)&f14tmp10_X, 0,
                  sizeof(ContinuousStates_f14tmp10));
  }

  /* states (dwork) */
  f14tmp10_rtM->Work.dwork = ((void *) &f14tmp10_DWork);
  (void) memset((void *)&f14tmp10_DWork, 0,
                sizeof(D_Work_f14tmp10));

  /* Initialize DataMapInfo substructure containing ModelMap for C API */
  f14tmp10_InitializeDataMapInfo(f14tmp10_rtM);

  /* Initialize Sizes */
  f14tmp10_rtM->Sizes.numContStates = (100);/* Number of continuous states */
  f14tmp10_rtM->Sizes.numY = (0);      /* Number of model outputs */
  f14tmp10_rtM->Sizes.numU = (0);      /* Number of model inputs */
  f14tmp10_rtM->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  f14tmp10_rtM->Sizes.numSampTimes = (3);/* Number of sample times */
  f14tmp10_rtM->Sizes.numBlocks = (400);/* Number of blocks */
  f14tmp10_rtM->Sizes.numBlockIO = (360);/* Number of block outputs */
  f14tmp10_rtM->Sizes.numBlockPrms = (420);/* Sum of parameter "widths" */
  return f14tmp10_rtM;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
