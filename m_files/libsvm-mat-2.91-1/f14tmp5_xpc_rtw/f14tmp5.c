/*
 * f14tmp5.c
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
#include "rt_logging_mmi.h"
#include "f14tmp5_capi.h"
#include "f14tmp5.h"
#include "f14tmp5_private.h"

/* Block signals (auto storage) */
BlockIO_f14tmp5 f14tmp5_B;

/* Continuous states */
ContinuousStates_f14tmp5 f14tmp5_X;

/* Block states (auto storage) */
D_Work_f14tmp5 f14tmp5_DWork;

/* Real-time model */
rtModel_f14tmp5 f14tmp5_rtM_;
rtModel_f14tmp5 *const f14tmp5_rtM = &f14tmp5_rtM_;
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
  (f14tmp5_rtM->Timing.TaskCounters.TID[2])++;
  if ((f14tmp5_rtM->Timing.TaskCounters.TID[2]) > 9) {/* Sample time: [0.1s, 0.0s] */
    f14tmp5_rtM->Timing.TaskCounters.TID[2] = 0;
  }

  f14tmp5_rtM->Timing.sampleHits[2] = (f14tmp5_rtM->Timing.TaskCounters.TID[2] ==
    0);
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
  int_T nXc = 50;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  f14tmp5_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  f14tmp5_output();
  f14tmp5_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  f14tmp5_output();
  f14tmp5_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  f14tmp5_output();
  f14tmp5_derivatives();

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
void f14tmp5_output(void)
{
  real_T temp;
  if (rtmIsMajorTimeStep(f14tmp5_rtM)) {
    /* set solver stop time */
    if (!(f14tmp5_rtM->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&f14tmp5_rtM->solverInfo,
                            ((f14tmp5_rtM->Timing.clockTickH0 + 1) *
        f14tmp5_rtM->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&f14tmp5_rtM->solverInfo,
                            ((f14tmp5_rtM->Timing.clockTick0 + 1) *
        f14tmp5_rtM->Timing.stepSize0 + f14tmp5_rtM->Timing.clockTickH0 *
        f14tmp5_rtM->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(f14tmp5_rtM)) {
    f14tmp5_rtM->Timing.t[0] = rtsiGetT(&f14tmp5_rtM->solverInfo);
  }

  /* TransferFcn: '<S6>/Transfer Fcn.2' */
  f14tmp5_B.TransferFcn2 = f14tmp5_P.TransferFcn2_C*
    f14tmp5_X.TransferFcn2_CSTATE;

  /* Gain: '<S1>/Gain5' */
  f14tmp5_B.Gain5 = f14tmp5_P.Gain5_Gain * f14tmp5_B.TransferFcn2;
  if (rtmIsMajorTimeStep(f14tmp5_rtM) &&
      f14tmp5_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* Derivative: '<S9>/Derivative' */
  {
    real_T t = f14tmp5_rtM->Timing.t[0];
    real_T timeStampA = f14tmp5_DWork.Derivative_RWORK.TimeStampA;
    real_T timeStampB = f14tmp5_DWork.Derivative_RWORK.TimeStampB;
    real_T *lastU = &f14tmp5_DWork.Derivative_RWORK.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp5_B.Derivative = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp5_DWork.Derivative_RWORK.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp5_DWork.Derivative_RWORK.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp5_B.Derivative = (f14tmp5_B.TransferFcn2 - *lastU++) / deltaT;
    }
  }

  /* TransferFcn: '<S6>/Transfer Fcn.1' */
  f14tmp5_B.TransferFcn1 = f14tmp5_P.TransferFcn1_C*
    f14tmp5_X.TransferFcn1_CSTATE;

  /* Derivative: '<S9>/Derivative1' */
  {
    real_T t = f14tmp5_rtM->Timing.t[0];
    real_T timeStampA = f14tmp5_DWork.Derivative1_RWORK.TimeStampA;
    real_T timeStampB = f14tmp5_DWork.Derivative1_RWORK.TimeStampB;
    real_T *lastU = &f14tmp5_DWork.Derivative1_RWORK.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp5_B.Derivative1 = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp5_DWork.Derivative1_RWORK.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp5_DWork.Derivative1_RWORK.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp5_B.Derivative1 = (f14tmp5_B.TransferFcn1 - *lastU++) / deltaT;
    }
  }

  /* Gain: '<S9>/Gain1' */
  f14tmp5_B.Gain1 = f14tmp5_P.Gain1_Gain * f14tmp5_B.Derivative1;

  /* Product: '<S9>/Product' incorporates:
   *  Constant: '<S9>/Constant'
   */
  f14tmp5_B.Product = f14tmp5_B.TransferFcn1 * f14tmp5_P.Constant_Value;

  /* Sum: '<S9>/Sum1' */
  f14tmp5_B.Sum1 = (f14tmp5_B.Gain1 - f14tmp5_B.Derivative) + f14tmp5_B.Product;

  /* Gain: '<S9>/Gain2' */
  f14tmp5_B.Gain2 = f14tmp5_P.Gain2_Gain * f14tmp5_B.Sum1;
  if (rtmIsMajorTimeStep(f14tmp5_rtM) &&
      f14tmp5_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* SignalGenerator: '<S1>/Pilot' */
  temp = f14tmp5_P.Pilot_Frequency * f14tmp5_rtM->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    f14tmp5_B.Pilot = f14tmp5_P.Pilot_Amplitude;
  } else {
    f14tmp5_B.Pilot = -f14tmp5_P.Pilot_Amplitude;
  }

  /* End of SignalGenerator: '<S1>/Pilot' */

  /* Sum: '<S1>/Sum1' */
  f14tmp5_B.Sum1_k = f14tmp5_B.Pilot + 0.0;
  if (rtmIsMajorTimeStep(f14tmp5_rtM) &&
      f14tmp5_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* TransferFcn: '<S1>/Actuator Model' */
  f14tmp5_B.ActuatorModel = f14tmp5_P.ActuatorModel_C*
    f14tmp5_X.ActuatorModel_CSTATE;

  /* Gain: '<S6>/Gain3' */
  f14tmp5_B.Gain3 = f14tmp5_P.Gain3_Gain * f14tmp5_B.TransferFcn1;

  /* Gain: '<S6>/Gain4' */
  f14tmp5_B.Gain4 = f14tmp5_P.Gain4_Gain * f14tmp5_B.TransferFcn2;

  /* Gain: '<S6>/Gain5' */
  f14tmp5_B.Gain5_b = f14tmp5_P.Gain5_Gain_j * f14tmp5_B.ActuatorModel;

  /* Gain: '<S6>/Gain6' */
  f14tmp5_B.Gain6 = f14tmp5_P.Gain6_Gain * f14tmp5_B.ActuatorModel;

  /* TransferFcn: '<S8>/W-gust model' */
  f14tmp5_B.Wgustmodel = f14tmp5_P.Wgustmodel_C[0]*f14tmp5_X.Wgustmodel_CSTATE[0]
    + f14tmp5_P.Wgustmodel_C[1]*f14tmp5_X.Wgustmodel_CSTATE[1];

  /* Gain: '<S1>/Gain' */
  f14tmp5_B.Gain = f14tmp5_P.Gain_Gain * f14tmp5_B.Wgustmodel;

  /* Sum: '<S6>/Sum1' */
  f14tmp5_B.Sum1_o = (f14tmp5_B.Gain5_b - f14tmp5_B.Gain) + f14tmp5_B.Gain3;

  /* Gain: '<S1>/Gain2' */
  f14tmp5_B.Gain2_f = f14tmp5_P.Gain2_Gain_p * f14tmp5_B.Wgustmodel;

  /* TransferFcn: '<S8>/Q-gust model' */
  f14tmp5_B.Qgustmodel = f14tmp5_P.Qgustmodel_D*f14tmp5_B.Wgustmodel;
  f14tmp5_B.Qgustmodel += f14tmp5_P.Qgustmodel_C*f14tmp5_X.Qgustmodel_CSTATE;

  /* Gain: '<S1>/Gain1' */
  f14tmp5_B.Gain1_h = f14tmp5_P.Gain1_Gain_h * f14tmp5_B.Qgustmodel;

  /* Sum: '<S1>/Sum' */
  f14tmp5_B.Sum = f14tmp5_B.Gain2_f + f14tmp5_B.Gain1_h;

  /* Sum: '<S6>/Sum2' */
  f14tmp5_B.Sum2 = (f14tmp5_B.Gain4 - f14tmp5_B.Sum) + f14tmp5_B.Gain6;

  /* TransferFcn: '<S7>/Alpha-sensor Low-pass Filter' */
  f14tmp5_B.AlphasensorLowpassFilter = f14tmp5_P.AlphasensorLowpassFilter_C*
    f14tmp5_X.AlphasensorLowpassFilter_CSTATE;

  /* TransferFcn: '<S7>/Stick Prefilter' */
  f14tmp5_B.StickPrefilter = f14tmp5_P.StickPrefilter_C*
    f14tmp5_X.StickPrefilter_CSTATE;

  /* TransferFcn: '<S7>/Pitch Rate Lead Filter' */
  f14tmp5_B.PitchRateLeadFilter = f14tmp5_P.PitchRateLeadFilter_D*
    f14tmp5_B.TransferFcn1;
  f14tmp5_B.PitchRateLeadFilter += f14tmp5_P.PitchRateLeadFilter_C*
    f14tmp5_X.PitchRateLeadFilter_CSTATE;

  /* Gain: '<S7>/Gain2' */
  f14tmp5_B.Gain2_e = f14tmp5_P.Gain2_Gain_k * f14tmp5_B.PitchRateLeadFilter;

  /* Gain: '<S7>/Gain3' */
  f14tmp5_B.Gain3_g = f14tmp5_P.Gain3_Gain_i *
    f14tmp5_B.AlphasensorLowpassFilter;

  /* Sum: '<S7>/Sum1' */
  f14tmp5_B.Sum1_d = f14tmp5_B.Gain2_e + f14tmp5_B.Gain3_g;

  /* Sum: '<S7>/Sum2' */
  f14tmp5_B.Sum2_f = f14tmp5_B.StickPrefilter - f14tmp5_B.Sum1_d;

  /* Gain: '<S7>/Gain' */
  f14tmp5_B.Gain_d = f14tmp5_P.Gain_Gain_k * f14tmp5_B.Sum2_f;

  /* TransferFcn: '<S7>/Proportional plus integral compensator' */
  f14tmp5_B.Proportionalplusintegralcompens =
    f14tmp5_P.Proportionalplusintegralcompe_i*
    f14tmp5_X.Proportionalplusintegralcompens;

  /* Sum: '<S7>/Sum' */
  f14tmp5_B.Sum_n = f14tmp5_B.Gain_d + f14tmp5_B.Proportionalplusintegralcompens;
  if (rtmIsMajorTimeStep(f14tmp5_rtM) &&
      f14tmp5_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* RandomNumber: '<S10>/White Noise' */
    f14tmp5_B.WhiteNoise = f14tmp5_DWork.NextOutput;

    /* Gain: '<S10>/Output' */
    f14tmp5_B.Output = f14tmp5_P.Output_Gain * f14tmp5_B.WhiteNoise;
  }

  /* TransferFcn: '<S11>/Transfer Fcn.2' */
  f14tmp5_B.TransferFcn2_b = f14tmp5_P.TransferFcn2_C_k*
    f14tmp5_X.TransferFcn2_CSTATE_h;

  /* Gain: '<S2>/Gain5' */
  f14tmp5_B.Gain5_h = f14tmp5_P.Gain5_Gain_o * f14tmp5_B.TransferFcn2_b;
  if (rtmIsMajorTimeStep(f14tmp5_rtM) &&
      f14tmp5_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* Derivative: '<S14>/Derivative' */
  {
    real_T t = f14tmp5_rtM->Timing.t[0];
    real_T timeStampA = f14tmp5_DWork.Derivative_RWORK_f.TimeStampA;
    real_T timeStampB = f14tmp5_DWork.Derivative_RWORK_f.TimeStampB;
    real_T *lastU = &f14tmp5_DWork.Derivative_RWORK_f.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp5_B.Derivative_k = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp5_DWork.Derivative_RWORK_f.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp5_DWork.Derivative_RWORK_f.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp5_B.Derivative_k = (f14tmp5_B.TransferFcn2_b - *lastU++) / deltaT;
    }
  }

  /* TransferFcn: '<S11>/Transfer Fcn.1' */
  f14tmp5_B.TransferFcn1_a = f14tmp5_P.TransferFcn1_C_g*
    f14tmp5_X.TransferFcn1_CSTATE_p;

  /* Derivative: '<S14>/Derivative1' */
  {
    real_T t = f14tmp5_rtM->Timing.t[0];
    real_T timeStampA = f14tmp5_DWork.Derivative1_RWORK_o.TimeStampA;
    real_T timeStampB = f14tmp5_DWork.Derivative1_RWORK_o.TimeStampB;
    real_T *lastU = &f14tmp5_DWork.Derivative1_RWORK_o.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp5_B.Derivative1_a = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp5_DWork.Derivative1_RWORK_o.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp5_DWork.Derivative1_RWORK_o.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp5_B.Derivative1_a = (f14tmp5_B.TransferFcn1_a - *lastU++) / deltaT;
    }
  }

  /* Gain: '<S14>/Gain1' */
  f14tmp5_B.Gain1_c = f14tmp5_P.Gain1_Gain_n * f14tmp5_B.Derivative1_a;

  /* Product: '<S14>/Product' incorporates:
   *  Constant: '<S14>/Constant'
   */
  f14tmp5_B.Product_a = f14tmp5_B.TransferFcn1_a * f14tmp5_P.Constant_Value_m;

  /* Sum: '<S14>/Sum1' */
  f14tmp5_B.Sum1_di = (f14tmp5_B.Gain1_c - f14tmp5_B.Derivative_k) +
    f14tmp5_B.Product_a;

  /* Gain: '<S14>/Gain2' */
  f14tmp5_B.Gain2_l = f14tmp5_P.Gain2_Gain_e * f14tmp5_B.Sum1_di;
  if (rtmIsMajorTimeStep(f14tmp5_rtM) &&
      f14tmp5_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* SignalGenerator: '<S2>/Pilot' */
  temp = f14tmp5_P.Pilot_Frequency_d * f14tmp5_rtM->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    f14tmp5_B.Pilot_k = f14tmp5_P.Pilot_Amplitude_n;
  } else {
    f14tmp5_B.Pilot_k = -f14tmp5_P.Pilot_Amplitude_n;
  }

  /* End of SignalGenerator: '<S2>/Pilot' */

  /* Sum: '<S2>/Sum1' */
  f14tmp5_B.Sum1_n = f14tmp5_B.Pilot_k + 0.0;
  if (rtmIsMajorTimeStep(f14tmp5_rtM) &&
      f14tmp5_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* TransferFcn: '<S2>/Actuator Model' */
  f14tmp5_B.ActuatorModel_n = f14tmp5_P.ActuatorModel_C_f*
    f14tmp5_X.ActuatorModel_CSTATE_a;

  /* Gain: '<S11>/Gain3' */
  f14tmp5_B.Gain3_a = f14tmp5_P.Gain3_Gain_k * f14tmp5_B.TransferFcn1_a;

  /* Gain: '<S11>/Gain4' */
  f14tmp5_B.Gain4_p = f14tmp5_P.Gain4_Gain_f * f14tmp5_B.TransferFcn2_b;

  /* Gain: '<S11>/Gain5' */
  f14tmp5_B.Gain5_h4 = f14tmp5_P.Gain5_Gain_g * f14tmp5_B.ActuatorModel_n;

  /* Gain: '<S11>/Gain6' */
  f14tmp5_B.Gain6_m = f14tmp5_P.Gain6_Gain_b * f14tmp5_B.ActuatorModel_n;

  /* TransferFcn: '<S13>/W-gust model' */
  f14tmp5_B.Wgustmodel_j = f14tmp5_P.Wgustmodel_C_a[0]*
    f14tmp5_X.Wgustmodel_CSTATE_f[0] + f14tmp5_P.Wgustmodel_C_a[1]*
    f14tmp5_X.Wgustmodel_CSTATE_f[1];

  /* Gain: '<S2>/Gain' */
  f14tmp5_B.Gain_n = f14tmp5_P.Gain_Gain_l * f14tmp5_B.Wgustmodel_j;

  /* Sum: '<S11>/Sum1' */
  f14tmp5_B.Sum1_e = (f14tmp5_B.Gain5_h4 - f14tmp5_B.Gain_n) + f14tmp5_B.Gain3_a;

  /* Gain: '<S2>/Gain2' */
  f14tmp5_B.Gain2_o = f14tmp5_P.Gain2_Gain_h * f14tmp5_B.Wgustmodel_j;

  /* TransferFcn: '<S13>/Q-gust model' */
  f14tmp5_B.Qgustmodel_c = f14tmp5_P.Qgustmodel_D_c*f14tmp5_B.Wgustmodel_j;
  f14tmp5_B.Qgustmodel_c += f14tmp5_P.Qgustmodel_C_p*
    f14tmp5_X.Qgustmodel_CSTATE_d;

  /* Gain: '<S2>/Gain1' */
  f14tmp5_B.Gain1_i = f14tmp5_P.Gain1_Gain_p * f14tmp5_B.Qgustmodel_c;

  /* Sum: '<S2>/Sum' */
  f14tmp5_B.Sum_e = f14tmp5_B.Gain2_o + f14tmp5_B.Gain1_i;

  /* Sum: '<S11>/Sum2' */
  f14tmp5_B.Sum2_c = (f14tmp5_B.Gain4_p - f14tmp5_B.Sum_e) + f14tmp5_B.Gain6_m;

  /* TransferFcn: '<S12>/Alpha-sensor Low-pass Filter' */
  f14tmp5_B.AlphasensorLowpassFilter_e = f14tmp5_P.AlphasensorLowpassFilter_C_g*
    f14tmp5_X.AlphasensorLowpassFilter_CSTA_g;

  /* TransferFcn: '<S12>/Stick Prefilter' */
  f14tmp5_B.StickPrefilter_h = f14tmp5_P.StickPrefilter_C_p*
    f14tmp5_X.StickPrefilter_CSTATE_a;

  /* TransferFcn: '<S12>/Pitch Rate Lead Filter' */
  f14tmp5_B.PitchRateLeadFilter_f = f14tmp5_P.PitchRateLeadFilter_D_f*
    f14tmp5_B.TransferFcn1_a;
  f14tmp5_B.PitchRateLeadFilter_f += f14tmp5_P.PitchRateLeadFilter_C_l*
    f14tmp5_X.PitchRateLeadFilter_CSTATE_k;

  /* Gain: '<S12>/Gain2' */
  f14tmp5_B.Gain2_j = f14tmp5_P.Gain2_Gain_et * f14tmp5_B.PitchRateLeadFilter_f;

  /* Gain: '<S12>/Gain3' */
  f14tmp5_B.Gain3_l = f14tmp5_P.Gain3_Gain_b *
    f14tmp5_B.AlphasensorLowpassFilter_e;

  /* Sum: '<S12>/Sum1' */
  f14tmp5_B.Sum1_i = f14tmp5_B.Gain2_j + f14tmp5_B.Gain3_l;

  /* Sum: '<S12>/Sum2' */
  f14tmp5_B.Sum2_k = f14tmp5_B.StickPrefilter_h - f14tmp5_B.Sum1_i;

  /* Gain: '<S12>/Gain' */
  f14tmp5_B.Gain_e = f14tmp5_P.Gain_Gain_a * f14tmp5_B.Sum2_k;

  /* TransferFcn: '<S12>/Proportional plus integral compensator' */
  f14tmp5_B.Proportionalplusintegralcompe_j =
    f14tmp5_P.Proportionalplusintegralcomp_mx*
    f14tmp5_X.Proportionalplusintegralcompe_n;

  /* Sum: '<S12>/Sum' */
  f14tmp5_B.Sum_l = f14tmp5_B.Gain_e + f14tmp5_B.Proportionalplusintegralcompe_j;
  if (rtmIsMajorTimeStep(f14tmp5_rtM) &&
      f14tmp5_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* RandomNumber: '<S15>/White Noise' */
    f14tmp5_B.WhiteNoise_l = f14tmp5_DWork.NextOutput_f;

    /* Gain: '<S15>/Output' */
    f14tmp5_B.Output_e = f14tmp5_P.Output_Gain_l * f14tmp5_B.WhiteNoise_l;
  }

  /* TransferFcn: '<S16>/Transfer Fcn.2' */
  f14tmp5_B.TransferFcn2_l = f14tmp5_P.TransferFcn2_C_a*
    f14tmp5_X.TransferFcn2_CSTATE_n;

  /* Gain: '<S3>/Gain5' */
  f14tmp5_B.Gain5_p = f14tmp5_P.Gain5_Gain_c * f14tmp5_B.TransferFcn2_l;
  if (rtmIsMajorTimeStep(f14tmp5_rtM) &&
      f14tmp5_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* Derivative: '<S19>/Derivative' */
  {
    real_T t = f14tmp5_rtM->Timing.t[0];
    real_T timeStampA = f14tmp5_DWork.Derivative_RWORK_l.TimeStampA;
    real_T timeStampB = f14tmp5_DWork.Derivative_RWORK_l.TimeStampB;
    real_T *lastU = &f14tmp5_DWork.Derivative_RWORK_l.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp5_B.Derivative_l = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp5_DWork.Derivative_RWORK_l.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp5_DWork.Derivative_RWORK_l.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp5_B.Derivative_l = (f14tmp5_B.TransferFcn2_l - *lastU++) / deltaT;
    }
  }

  /* TransferFcn: '<S16>/Transfer Fcn.1' */
  f14tmp5_B.TransferFcn1_g = f14tmp5_P.TransferFcn1_C_gb*
    f14tmp5_X.TransferFcn1_CSTATE_k;

  /* Derivative: '<S19>/Derivative1' */
  {
    real_T t = f14tmp5_rtM->Timing.t[0];
    real_T timeStampA = f14tmp5_DWork.Derivative1_RWORK_k.TimeStampA;
    real_T timeStampB = f14tmp5_DWork.Derivative1_RWORK_k.TimeStampB;
    real_T *lastU = &f14tmp5_DWork.Derivative1_RWORK_k.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp5_B.Derivative1_j = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp5_DWork.Derivative1_RWORK_k.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp5_DWork.Derivative1_RWORK_k.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp5_B.Derivative1_j = (f14tmp5_B.TransferFcn1_g - *lastU++) / deltaT;
    }
  }

  /* Gain: '<S19>/Gain1' */
  f14tmp5_B.Gain1_g = f14tmp5_P.Gain1_Gain_e * f14tmp5_B.Derivative1_j;

  /* Product: '<S19>/Product' incorporates:
   *  Constant: '<S19>/Constant'
   */
  f14tmp5_B.Product_b = f14tmp5_B.TransferFcn1_g * f14tmp5_P.Constant_Value_b;

  /* Sum: '<S19>/Sum1' */
  f14tmp5_B.Sum1_ev = (f14tmp5_B.Gain1_g - f14tmp5_B.Derivative_l) +
    f14tmp5_B.Product_b;

  /* Gain: '<S19>/Gain2' */
  f14tmp5_B.Gain2_g = f14tmp5_P.Gain2_Gain_h5 * f14tmp5_B.Sum1_ev;
  if (rtmIsMajorTimeStep(f14tmp5_rtM) &&
      f14tmp5_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* SignalGenerator: '<S3>/Pilot' */
  temp = f14tmp5_P.Pilot_Frequency_k * f14tmp5_rtM->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    f14tmp5_B.Pilot_h = f14tmp5_P.Pilot_Amplitude_e;
  } else {
    f14tmp5_B.Pilot_h = -f14tmp5_P.Pilot_Amplitude_e;
  }

  /* End of SignalGenerator: '<S3>/Pilot' */

  /* Sum: '<S3>/Sum1' */
  f14tmp5_B.Sum1_n0 = f14tmp5_B.Pilot_h + 0.0;
  if (rtmIsMajorTimeStep(f14tmp5_rtM) &&
      f14tmp5_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* TransferFcn: '<S3>/Actuator Model' */
  f14tmp5_B.ActuatorModel_a = f14tmp5_P.ActuatorModel_C_b*
    f14tmp5_X.ActuatorModel_CSTATE_f;

  /* Gain: '<S16>/Gain3' */
  f14tmp5_B.Gain3_m = f14tmp5_P.Gain3_Gain_c * f14tmp5_B.TransferFcn1_g;

  /* Gain: '<S16>/Gain4' */
  f14tmp5_B.Gain4_c = f14tmp5_P.Gain4_Gain_j * f14tmp5_B.TransferFcn2_l;

  /* Gain: '<S16>/Gain5' */
  f14tmp5_B.Gain5_o = f14tmp5_P.Gain5_Gain_p * f14tmp5_B.ActuatorModel_a;

  /* Gain: '<S16>/Gain6' */
  f14tmp5_B.Gain6_mc = f14tmp5_P.Gain6_Gain_f * f14tmp5_B.ActuatorModel_a;

  /* TransferFcn: '<S18>/W-gust model' */
  f14tmp5_B.Wgustmodel_e = f14tmp5_P.Wgustmodel_C_m[0]*
    f14tmp5_X.Wgustmodel_CSTATE_i[0] + f14tmp5_P.Wgustmodel_C_m[1]*
    f14tmp5_X.Wgustmodel_CSTATE_i[1];

  /* Gain: '<S3>/Gain' */
  f14tmp5_B.Gain_l = f14tmp5_P.Gain_Gain_d * f14tmp5_B.Wgustmodel_e;

  /* Sum: '<S16>/Sum1' */
  f14tmp5_B.Sum1_dr = (f14tmp5_B.Gain5_o - f14tmp5_B.Gain_l) + f14tmp5_B.Gain3_m;

  /* Gain: '<S3>/Gain2' */
  f14tmp5_B.Gain2_l0 = f14tmp5_P.Gain2_Gain_g * f14tmp5_B.Wgustmodel_e;

  /* TransferFcn: '<S18>/Q-gust model' */
  f14tmp5_B.Qgustmodel_j = f14tmp5_P.Qgustmodel_D_i*f14tmp5_B.Wgustmodel_e;
  f14tmp5_B.Qgustmodel_j += f14tmp5_P.Qgustmodel_C_j*
    f14tmp5_X.Qgustmodel_CSTATE_k;

  /* Gain: '<S3>/Gain1' */
  f14tmp5_B.Gain1_b = f14tmp5_P.Gain1_Gain_f * f14tmp5_B.Qgustmodel_j;

  /* Sum: '<S3>/Sum' */
  f14tmp5_B.Sum_i = f14tmp5_B.Gain2_l0 + f14tmp5_B.Gain1_b;

  /* Sum: '<S16>/Sum2' */
  f14tmp5_B.Sum2_o = (f14tmp5_B.Gain4_c - f14tmp5_B.Sum_i) + f14tmp5_B.Gain6_mc;

  /* TransferFcn: '<S17>/Alpha-sensor Low-pass Filter' */
  f14tmp5_B.AlphasensorLowpassFilter_h = f14tmp5_P.AlphasensorLowpassFilter_C_gf*
    f14tmp5_X.AlphasensorLowpassFilter_CSTA_i;

  /* TransferFcn: '<S17>/Stick Prefilter' */
  f14tmp5_B.StickPrefilter_i = f14tmp5_P.StickPrefilter_C_j*
    f14tmp5_X.StickPrefilter_CSTATE_j;

  /* TransferFcn: '<S17>/Pitch Rate Lead Filter' */
  f14tmp5_B.PitchRateLeadFilter_d = f14tmp5_P.PitchRateLeadFilter_D_ft*
    f14tmp5_B.TransferFcn1_g;
  f14tmp5_B.PitchRateLeadFilter_d += f14tmp5_P.PitchRateLeadFilter_C_k*
    f14tmp5_X.PitchRateLeadFilter_CSTATE_n;

  /* Gain: '<S17>/Gain2' */
  f14tmp5_B.Gain2_p = f14tmp5_P.Gain2_Gain_eh * f14tmp5_B.PitchRateLeadFilter_d;

  /* Gain: '<S17>/Gain3' */
  f14tmp5_B.Gain3_gl = f14tmp5_P.Gain3_Gain_m *
    f14tmp5_B.AlphasensorLowpassFilter_h;

  /* Sum: '<S17>/Sum1' */
  f14tmp5_B.Sum1_o0 = f14tmp5_B.Gain2_p + f14tmp5_B.Gain3_gl;

  /* Sum: '<S17>/Sum2' */
  f14tmp5_B.Sum2_g = f14tmp5_B.StickPrefilter_i - f14tmp5_B.Sum1_o0;

  /* Gain: '<S17>/Gain' */
  f14tmp5_B.Gain_h = f14tmp5_P.Gain_Gain_j * f14tmp5_B.Sum2_g;

  /* TransferFcn: '<S17>/Proportional plus integral compensator' */
  f14tmp5_B.Proportionalplusintegralcompe_e =
    f14tmp5_P.Proportionalplusintegralcompe_l*
    f14tmp5_X.Proportionalplusintegralcompe_h;

  /* Sum: '<S17>/Sum' */
  f14tmp5_B.Sum_o = f14tmp5_B.Gain_h + f14tmp5_B.Proportionalplusintegralcompe_e;
  if (rtmIsMajorTimeStep(f14tmp5_rtM) &&
      f14tmp5_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* RandomNumber: '<S20>/White Noise' */
    f14tmp5_B.WhiteNoise_g = f14tmp5_DWork.NextOutput_h;

    /* Gain: '<S20>/Output' */
    f14tmp5_B.Output_c = f14tmp5_P.Output_Gain_m * f14tmp5_B.WhiteNoise_g;
  }

  /* TransferFcn: '<S21>/Transfer Fcn.2' */
  f14tmp5_B.TransferFcn2_j = f14tmp5_P.TransferFcn2_C_l*
    f14tmp5_X.TransferFcn2_CSTATE_e;

  /* Gain: '<S4>/Gain5' */
  f14tmp5_B.Gain5_k = f14tmp5_P.Gain5_Gain_j0 * f14tmp5_B.TransferFcn2_j;
  if (rtmIsMajorTimeStep(f14tmp5_rtM) &&
      f14tmp5_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* Derivative: '<S24>/Derivative' */
  {
    real_T t = f14tmp5_rtM->Timing.t[0];
    real_T timeStampA = f14tmp5_DWork.Derivative_RWORK_k.TimeStampA;
    real_T timeStampB = f14tmp5_DWork.Derivative_RWORK_k.TimeStampB;
    real_T *lastU = &f14tmp5_DWork.Derivative_RWORK_k.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp5_B.Derivative_p = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp5_DWork.Derivative_RWORK_k.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp5_DWork.Derivative_RWORK_k.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp5_B.Derivative_p = (f14tmp5_B.TransferFcn2_j - *lastU++) / deltaT;
    }
  }

  /* TransferFcn: '<S21>/Transfer Fcn.1' */
  f14tmp5_B.TransferFcn1_k = f14tmp5_P.TransferFcn1_C_l*
    f14tmp5_X.TransferFcn1_CSTATE_j;

  /* Derivative: '<S24>/Derivative1' */
  {
    real_T t = f14tmp5_rtM->Timing.t[0];
    real_T timeStampA = f14tmp5_DWork.Derivative1_RWORK_b.TimeStampA;
    real_T timeStampB = f14tmp5_DWork.Derivative1_RWORK_b.TimeStampB;
    real_T *lastU = &f14tmp5_DWork.Derivative1_RWORK_b.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp5_B.Derivative1_g = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp5_DWork.Derivative1_RWORK_b.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp5_DWork.Derivative1_RWORK_b.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp5_B.Derivative1_g = (f14tmp5_B.TransferFcn1_k - *lastU++) / deltaT;
    }
  }

  /* Gain: '<S24>/Gain1' */
  f14tmp5_B.Gain1_ga = f14tmp5_P.Gain1_Gain_fm * f14tmp5_B.Derivative1_g;

  /* Product: '<S24>/Product' incorporates:
   *  Constant: '<S24>/Constant'
   */
  f14tmp5_B.Product_h = f14tmp5_B.TransferFcn1_k * f14tmp5_P.Constant_Value_f;

  /* Sum: '<S24>/Sum1' */
  f14tmp5_B.Sum1_o0i = (f14tmp5_B.Gain1_ga - f14tmp5_B.Derivative_p) +
    f14tmp5_B.Product_h;

  /* Gain: '<S24>/Gain2' */
  f14tmp5_B.Gain2_h = f14tmp5_P.Gain2_Gain_kz * f14tmp5_B.Sum1_o0i;
  if (rtmIsMajorTimeStep(f14tmp5_rtM) &&
      f14tmp5_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* SignalGenerator: '<S4>/Pilot' */
  temp = f14tmp5_P.Pilot_Frequency_i * f14tmp5_rtM->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    f14tmp5_B.Pilot_g = f14tmp5_P.Pilot_Amplitude_o;
  } else {
    f14tmp5_B.Pilot_g = -f14tmp5_P.Pilot_Amplitude_o;
  }

  /* End of SignalGenerator: '<S4>/Pilot' */

  /* Sum: '<S4>/Sum1' */
  f14tmp5_B.Sum1_dd = f14tmp5_B.Pilot_g + 0.0;
  if (rtmIsMajorTimeStep(f14tmp5_rtM) &&
      f14tmp5_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* TransferFcn: '<S4>/Actuator Model' */
  f14tmp5_B.ActuatorModel_m = f14tmp5_P.ActuatorModel_C_l*
    f14tmp5_X.ActuatorModel_CSTATE_p;

  /* Gain: '<S21>/Gain3' */
  f14tmp5_B.Gain3_lc = f14tmp5_P.Gain3_Gain_p * f14tmp5_B.TransferFcn1_k;

  /* Gain: '<S21>/Gain4' */
  f14tmp5_B.Gain4_j = f14tmp5_P.Gain4_Gain_c * f14tmp5_B.TransferFcn2_j;

  /* Gain: '<S21>/Gain5' */
  f14tmp5_B.Gain5_pj = f14tmp5_P.Gain5_Gain_j0q * f14tmp5_B.ActuatorModel_m;

  /* Gain: '<S21>/Gain6' */
  f14tmp5_B.Gain6_f = f14tmp5_P.Gain6_Gain_j * f14tmp5_B.ActuatorModel_m;

  /* TransferFcn: '<S23>/W-gust model' */
  f14tmp5_B.Wgustmodel_h = f14tmp5_P.Wgustmodel_C_g[0]*
    f14tmp5_X.Wgustmodel_CSTATE_k[0] + f14tmp5_P.Wgustmodel_C_g[1]*
    f14tmp5_X.Wgustmodel_CSTATE_k[1];

  /* Gain: '<S4>/Gain' */
  f14tmp5_B.Gain_o = f14tmp5_P.Gain_Gain_h * f14tmp5_B.Wgustmodel_h;

  /* Sum: '<S21>/Sum1' */
  f14tmp5_B.Sum1_f = (f14tmp5_B.Gain5_pj - f14tmp5_B.Gain_o) +
    f14tmp5_B.Gain3_lc;

  /* Gain: '<S4>/Gain2' */
  f14tmp5_B.Gain2_n = f14tmp5_P.Gain2_Gain_m * f14tmp5_B.Wgustmodel_h;

  /* TransferFcn: '<S23>/Q-gust model' */
  f14tmp5_B.Qgustmodel_g = f14tmp5_P.Qgustmodel_D_a*f14tmp5_B.Wgustmodel_h;
  f14tmp5_B.Qgustmodel_g += f14tmp5_P.Qgustmodel_C_a*
    f14tmp5_X.Qgustmodel_CSTATE_a;

  /* Gain: '<S4>/Gain1' */
  f14tmp5_B.Gain1_o = f14tmp5_P.Gain1_Gain_d * f14tmp5_B.Qgustmodel_g;

  /* Sum: '<S4>/Sum' */
  f14tmp5_B.Sum_en = f14tmp5_B.Gain2_n + f14tmp5_B.Gain1_o;

  /* Sum: '<S21>/Sum2' */
  f14tmp5_B.Sum2_cx = (f14tmp5_B.Gain4_j - f14tmp5_B.Sum_en) + f14tmp5_B.Gain6_f;

  /* TransferFcn: '<S22>/Alpha-sensor Low-pass Filter' */
  f14tmp5_B.AlphasensorLowpassFilter_j = f14tmp5_P.AlphasensorLowpassFilter_C_m*
    f14tmp5_X.AlphasensorLowpassFilter_CSTA_k;

  /* TransferFcn: '<S22>/Stick Prefilter' */
  f14tmp5_B.StickPrefilter_e = f14tmp5_P.StickPrefilter_C_h*
    f14tmp5_X.StickPrefilter_CSTATE_ju;

  /* TransferFcn: '<S22>/Pitch Rate Lead Filter' */
  f14tmp5_B.PitchRateLeadFilter_k = f14tmp5_P.PitchRateLeadFilter_D_b*
    f14tmp5_B.TransferFcn1_k;
  f14tmp5_B.PitchRateLeadFilter_k += f14tmp5_P.PitchRateLeadFilter_C_b*
    f14tmp5_X.PitchRateLeadFilter_CSTATE_e;

  /* Gain: '<S22>/Gain2' */
  f14tmp5_B.Gain2_nh = f14tmp5_P.Gain2_Gain_b * f14tmp5_B.PitchRateLeadFilter_k;

  /* Gain: '<S22>/Gain3' */
  f14tmp5_B.Gain3_b = f14tmp5_P.Gain3_Gain_a *
    f14tmp5_B.AlphasensorLowpassFilter_j;

  /* Sum: '<S22>/Sum1' */
  f14tmp5_B.Sum1_om = f14tmp5_B.Gain2_nh + f14tmp5_B.Gain3_b;

  /* Sum: '<S22>/Sum2' */
  f14tmp5_B.Sum2_gm = f14tmp5_B.StickPrefilter_e - f14tmp5_B.Sum1_om;

  /* Gain: '<S22>/Gain' */
  f14tmp5_B.Gain_df = f14tmp5_P.Gain_Gain_f * f14tmp5_B.Sum2_gm;

  /* TransferFcn: '<S22>/Proportional plus integral compensator' */
  f14tmp5_B.Proportionalplusintegralcompe_h =
    f14tmp5_P.Proportionalplusintegralcompe_j*
    f14tmp5_X.Proportionalplusintegralcompe_j;

  /* Sum: '<S22>/Sum' */
  f14tmp5_B.Sum_k = f14tmp5_B.Gain_df +
    f14tmp5_B.Proportionalplusintegralcompe_h;
  if (rtmIsMajorTimeStep(f14tmp5_rtM) &&
      f14tmp5_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* RandomNumber: '<S25>/White Noise' */
    f14tmp5_B.WhiteNoise_p = f14tmp5_DWork.NextOutput_a;

    /* Gain: '<S25>/Output' */
    f14tmp5_B.Output_k = f14tmp5_P.Output_Gain_p * f14tmp5_B.WhiteNoise_p;
  }

  /* TransferFcn: '<S26>/Transfer Fcn.2' */
  f14tmp5_B.TransferFcn2_o = f14tmp5_P.TransferFcn2_C_e*
    f14tmp5_X.TransferFcn2_CSTATE_k;

  /* Gain: '<S5>/Gain5' */
  f14tmp5_B.Gain5_c = f14tmp5_P.Gain5_Gain_f * f14tmp5_B.TransferFcn2_o;
  if (rtmIsMajorTimeStep(f14tmp5_rtM) &&
      f14tmp5_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* Derivative: '<S29>/Derivative' */
  {
    real_T t = f14tmp5_rtM->Timing.t[0];
    real_T timeStampA = f14tmp5_DWork.Derivative_RWORK_lc.TimeStampA;
    real_T timeStampB = f14tmp5_DWork.Derivative_RWORK_lc.TimeStampB;
    real_T *lastU = &f14tmp5_DWork.Derivative_RWORK_lc.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp5_B.Derivative_f = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp5_DWork.Derivative_RWORK_lc.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp5_DWork.Derivative_RWORK_lc.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp5_B.Derivative_f = (f14tmp5_B.TransferFcn2_o - *lastU++) / deltaT;
    }
  }

  /* TransferFcn: '<S26>/Transfer Fcn.1' */
  f14tmp5_B.TransferFcn1_i = f14tmp5_P.TransferFcn1_C_j*
    f14tmp5_X.TransferFcn1_CSTATE_pe;

  /* Derivative: '<S29>/Derivative1' */
  {
    real_T t = f14tmp5_rtM->Timing.t[0];
    real_T timeStampA = f14tmp5_DWork.Derivative1_RWORK_d.TimeStampA;
    real_T timeStampB = f14tmp5_DWork.Derivative1_RWORK_d.TimeStampB;
    real_T *lastU = &f14tmp5_DWork.Derivative1_RWORK_d.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp5_B.Derivative1_i = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp5_DWork.Derivative1_RWORK_d.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp5_DWork.Derivative1_RWORK_d.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp5_B.Derivative1_i = (f14tmp5_B.TransferFcn1_i - *lastU++) / deltaT;
    }
  }

  /* Gain: '<S29>/Gain1' */
  f14tmp5_B.Gain1_om = f14tmp5_P.Gain1_Gain_m * f14tmp5_B.Derivative1_i;

  /* Product: '<S29>/Product' incorporates:
   *  Constant: '<S29>/Constant'
   */
  f14tmp5_B.Product_i = f14tmp5_B.TransferFcn1_i * f14tmp5_P.Constant_Value_p;

  /* Sum: '<S29>/Sum1' */
  f14tmp5_B.Sum1_a = (f14tmp5_B.Gain1_om - f14tmp5_B.Derivative_f) +
    f14tmp5_B.Product_i;

  /* Gain: '<S29>/Gain2' */
  f14tmp5_B.Gain2_oj = f14tmp5_P.Gain2_Gain_d * f14tmp5_B.Sum1_a;
  if (rtmIsMajorTimeStep(f14tmp5_rtM) &&
      f14tmp5_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* SignalGenerator: '<S5>/Pilot' */
  temp = f14tmp5_P.Pilot_Frequency_a * f14tmp5_rtM->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    f14tmp5_B.Pilot_h3 = f14tmp5_P.Pilot_Amplitude_h;
  } else {
    f14tmp5_B.Pilot_h3 = -f14tmp5_P.Pilot_Amplitude_h;
  }

  /* End of SignalGenerator: '<S5>/Pilot' */

  /* Sum: '<S5>/Sum1' */
  f14tmp5_B.Sum1_h = f14tmp5_B.Pilot_h3 + 0.0;
  if (rtmIsMajorTimeStep(f14tmp5_rtM) &&
      f14tmp5_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* TransferFcn: '<S5>/Actuator Model' */
  f14tmp5_B.ActuatorModel_b = f14tmp5_P.ActuatorModel_C_a*
    f14tmp5_X.ActuatorModel_CSTATE_o;

  /* Gain: '<S26>/Gain3' */
  f14tmp5_B.Gain3_as = f14tmp5_P.Gain3_Gain_ai * f14tmp5_B.TransferFcn1_i;

  /* Gain: '<S26>/Gain4' */
  f14tmp5_B.Gain4_l = f14tmp5_P.Gain4_Gain_d * f14tmp5_B.TransferFcn2_o;

  /* Gain: '<S26>/Gain5' */
  f14tmp5_B.Gain5_i = f14tmp5_P.Gain5_Gain_n * f14tmp5_B.ActuatorModel_b;

  /* Gain: '<S26>/Gain6' */
  f14tmp5_B.Gain6_b = f14tmp5_P.Gain6_Gain_n * f14tmp5_B.ActuatorModel_b;

  /* TransferFcn: '<S28>/W-gust model' */
  f14tmp5_B.Wgustmodel_o = f14tmp5_P.Wgustmodel_C_p[0]*
    f14tmp5_X.Wgustmodel_CSTATE_if[0]
    + f14tmp5_P.Wgustmodel_C_p[1]*f14tmp5_X.Wgustmodel_CSTATE_if[1];

  /* Gain: '<S5>/Gain' */
  f14tmp5_B.Gain_hr = f14tmp5_P.Gain_Gain_c * f14tmp5_B.Wgustmodel_o;

  /* Sum: '<S26>/Sum1' */
  f14tmp5_B.Sum1_g = (f14tmp5_B.Gain5_i - f14tmp5_B.Gain_hr) +
    f14tmp5_B.Gain3_as;

  /* Gain: '<S5>/Gain2' */
  f14tmp5_B.Gain2_b = f14tmp5_P.Gain2_Gain_l * f14tmp5_B.Wgustmodel_o;

  /* TransferFcn: '<S28>/Q-gust model' */
  f14tmp5_B.Qgustmodel_n = f14tmp5_P.Qgustmodel_D_l*f14tmp5_B.Wgustmodel_o;
  f14tmp5_B.Qgustmodel_n += f14tmp5_P.Qgustmodel_C_c*
    f14tmp5_X.Qgustmodel_CSTATE_m;

  /* Gain: '<S5>/Gain1' */
  f14tmp5_B.Gain1_l = f14tmp5_P.Gain1_Gain_a * f14tmp5_B.Qgustmodel_n;

  /* Sum: '<S5>/Sum' */
  f14tmp5_B.Sum_kh = f14tmp5_B.Gain2_b + f14tmp5_B.Gain1_l;

  /* Sum: '<S26>/Sum2' */
  f14tmp5_B.Sum2_oa = (f14tmp5_B.Gain4_l - f14tmp5_B.Sum_kh) + f14tmp5_B.Gain6_b;

  /* TransferFcn: '<S27>/Alpha-sensor Low-pass Filter' */
  f14tmp5_B.AlphasensorLowpassFilter_n = f14tmp5_P.AlphasensorLowpassFilter_C_e*
    f14tmp5_X.AlphasensorLowpassFilter_CST_ku;

  /* TransferFcn: '<S27>/Stick Prefilter' */
  f14tmp5_B.StickPrefilter_o = f14tmp5_P.StickPrefilter_C_b*
    f14tmp5_X.StickPrefilter_CSTATE_m;

  /* TransferFcn: '<S27>/Pitch Rate Lead Filter' */
  f14tmp5_B.PitchRateLeadFilter_f1 = f14tmp5_P.PitchRateLeadFilter_D_a*
    f14tmp5_B.TransferFcn1_i;
  f14tmp5_B.PitchRateLeadFilter_f1 += f14tmp5_P.PitchRateLeadFilter_C_a*
    f14tmp5_X.PitchRateLeadFilter_CSTATE_f;

  /* Gain: '<S27>/Gain2' */
  f14tmp5_B.Gain2_fs = f14tmp5_P.Gain2_Gain_n * f14tmp5_B.PitchRateLeadFilter_f1;

  /* Gain: '<S27>/Gain3' */
  f14tmp5_B.Gain3_f = f14tmp5_P.Gain3_Gain_h *
    f14tmp5_B.AlphasensorLowpassFilter_n;

  /* Sum: '<S27>/Sum1' */
  f14tmp5_B.Sum1_m = f14tmp5_B.Gain2_fs + f14tmp5_B.Gain3_f;

  /* Sum: '<S27>/Sum2' */
  f14tmp5_B.Sum2_f5 = f14tmp5_B.StickPrefilter_o - f14tmp5_B.Sum1_m;

  /* Gain: '<S27>/Gain' */
  f14tmp5_B.Gain_i = f14tmp5_P.Gain_Gain_o * f14tmp5_B.Sum2_f5;

  /* TransferFcn: '<S27>/Proportional plus integral compensator' */
  f14tmp5_B.Proportionalplusintegralcomp_eg =
    f14tmp5_P.Proportionalplusintegralcomp_jp*
    f14tmp5_X.Proportionalplusintegralcompe_k;

  /* Sum: '<S27>/Sum' */
  f14tmp5_B.Sum_m = f14tmp5_B.Gain_i + f14tmp5_B.Proportionalplusintegralcomp_eg;
  if (rtmIsMajorTimeStep(f14tmp5_rtM) &&
      f14tmp5_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* RandomNumber: '<S30>/White Noise' */
    f14tmp5_B.WhiteNoise_m = f14tmp5_DWork.NextOutput_e;

    /* Gain: '<S30>/Output' */
    f14tmp5_B.Output_a = f14tmp5_P.Output_Gain_pk * f14tmp5_B.WhiteNoise_m;
  }
}

/* Model update function */
void f14tmp5_update(void)
{
  /* Update for Derivative: '<S9>/Derivative' */
  {
    real_T timeStampA = f14tmp5_DWork.Derivative_RWORK.TimeStampA;
    real_T timeStampB = f14tmp5_DWork.Derivative_RWORK.TimeStampB;
    real_T* lastTime = &f14tmp5_DWork.Derivative_RWORK.TimeStampA;
    real_T* lastU = &f14tmp5_DWork.Derivative_RWORK.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp5_DWork.Derivative_RWORK.TimeStampB;
        lastU = &f14tmp5_DWork.Derivative_RWORK.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp5_DWork.Derivative_RWORK.TimeStampB;
        lastU = &f14tmp5_DWork.Derivative_RWORK.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp5_rtM->Timing.t[0];
    *lastU++ = f14tmp5_B.TransferFcn2;
  }

  /* Update for Derivative: '<S9>/Derivative1' */
  {
    real_T timeStampA = f14tmp5_DWork.Derivative1_RWORK.TimeStampA;
    real_T timeStampB = f14tmp5_DWork.Derivative1_RWORK.TimeStampB;
    real_T* lastTime = &f14tmp5_DWork.Derivative1_RWORK.TimeStampA;
    real_T* lastU = &f14tmp5_DWork.Derivative1_RWORK.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp5_DWork.Derivative1_RWORK.TimeStampB;
        lastU = &f14tmp5_DWork.Derivative1_RWORK.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp5_DWork.Derivative1_RWORK.TimeStampB;
        lastU = &f14tmp5_DWork.Derivative1_RWORK.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp5_rtM->Timing.t[0];
    *lastU++ = f14tmp5_B.TransferFcn1;
  }

  if (rtmIsMajorTimeStep(f14tmp5_rtM) &&
      f14tmp5_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* Update for RandomNumber: '<S10>/White Noise' */
    f14tmp5_DWork.NextOutput = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp5_DWork.RandSeed) * f14tmp5_P.WhiteNoise_StdDev +
      f14tmp5_P.WhiteNoise_Mean;
  }

  /* Update for Derivative: '<S14>/Derivative' */
  {
    real_T timeStampA = f14tmp5_DWork.Derivative_RWORK_f.TimeStampA;
    real_T timeStampB = f14tmp5_DWork.Derivative_RWORK_f.TimeStampB;
    real_T* lastTime = &f14tmp5_DWork.Derivative_RWORK_f.TimeStampA;
    real_T* lastU = &f14tmp5_DWork.Derivative_RWORK_f.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp5_DWork.Derivative_RWORK_f.TimeStampB;
        lastU = &f14tmp5_DWork.Derivative_RWORK_f.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp5_DWork.Derivative_RWORK_f.TimeStampB;
        lastU = &f14tmp5_DWork.Derivative_RWORK_f.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp5_rtM->Timing.t[0];
    *lastU++ = f14tmp5_B.TransferFcn2_b;
  }

  /* Update for Derivative: '<S14>/Derivative1' */
  {
    real_T timeStampA = f14tmp5_DWork.Derivative1_RWORK_o.TimeStampA;
    real_T timeStampB = f14tmp5_DWork.Derivative1_RWORK_o.TimeStampB;
    real_T* lastTime = &f14tmp5_DWork.Derivative1_RWORK_o.TimeStampA;
    real_T* lastU = &f14tmp5_DWork.Derivative1_RWORK_o.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp5_DWork.Derivative1_RWORK_o.TimeStampB;
        lastU = &f14tmp5_DWork.Derivative1_RWORK_o.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp5_DWork.Derivative1_RWORK_o.TimeStampB;
        lastU = &f14tmp5_DWork.Derivative1_RWORK_o.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp5_rtM->Timing.t[0];
    *lastU++ = f14tmp5_B.TransferFcn1_a;
  }

  if (rtmIsMajorTimeStep(f14tmp5_rtM) &&
      f14tmp5_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* Update for RandomNumber: '<S15>/White Noise' */
    f14tmp5_DWork.NextOutput_f = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp5_DWork.RandSeed_n) * f14tmp5_P.WhiteNoise_StdDev_n +
      f14tmp5_P.WhiteNoise_Mean_j;
  }

  /* Update for Derivative: '<S19>/Derivative' */
  {
    real_T timeStampA = f14tmp5_DWork.Derivative_RWORK_l.TimeStampA;
    real_T timeStampB = f14tmp5_DWork.Derivative_RWORK_l.TimeStampB;
    real_T* lastTime = &f14tmp5_DWork.Derivative_RWORK_l.TimeStampA;
    real_T* lastU = &f14tmp5_DWork.Derivative_RWORK_l.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp5_DWork.Derivative_RWORK_l.TimeStampB;
        lastU = &f14tmp5_DWork.Derivative_RWORK_l.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp5_DWork.Derivative_RWORK_l.TimeStampB;
        lastU = &f14tmp5_DWork.Derivative_RWORK_l.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp5_rtM->Timing.t[0];
    *lastU++ = f14tmp5_B.TransferFcn2_l;
  }

  /* Update for Derivative: '<S19>/Derivative1' */
  {
    real_T timeStampA = f14tmp5_DWork.Derivative1_RWORK_k.TimeStampA;
    real_T timeStampB = f14tmp5_DWork.Derivative1_RWORK_k.TimeStampB;
    real_T* lastTime = &f14tmp5_DWork.Derivative1_RWORK_k.TimeStampA;
    real_T* lastU = &f14tmp5_DWork.Derivative1_RWORK_k.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp5_DWork.Derivative1_RWORK_k.TimeStampB;
        lastU = &f14tmp5_DWork.Derivative1_RWORK_k.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp5_DWork.Derivative1_RWORK_k.TimeStampB;
        lastU = &f14tmp5_DWork.Derivative1_RWORK_k.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp5_rtM->Timing.t[0];
    *lastU++ = f14tmp5_B.TransferFcn1_g;
  }

  if (rtmIsMajorTimeStep(f14tmp5_rtM) &&
      f14tmp5_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* Update for RandomNumber: '<S20>/White Noise' */
    f14tmp5_DWork.NextOutput_h = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp5_DWork.RandSeed_e) * f14tmp5_P.WhiteNoise_StdDev_g +
      f14tmp5_P.WhiteNoise_Mean_k;
  }

  /* Update for Derivative: '<S24>/Derivative' */
  {
    real_T timeStampA = f14tmp5_DWork.Derivative_RWORK_k.TimeStampA;
    real_T timeStampB = f14tmp5_DWork.Derivative_RWORK_k.TimeStampB;
    real_T* lastTime = &f14tmp5_DWork.Derivative_RWORK_k.TimeStampA;
    real_T* lastU = &f14tmp5_DWork.Derivative_RWORK_k.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp5_DWork.Derivative_RWORK_k.TimeStampB;
        lastU = &f14tmp5_DWork.Derivative_RWORK_k.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp5_DWork.Derivative_RWORK_k.TimeStampB;
        lastU = &f14tmp5_DWork.Derivative_RWORK_k.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp5_rtM->Timing.t[0];
    *lastU++ = f14tmp5_B.TransferFcn2_j;
  }

  /* Update for Derivative: '<S24>/Derivative1' */
  {
    real_T timeStampA = f14tmp5_DWork.Derivative1_RWORK_b.TimeStampA;
    real_T timeStampB = f14tmp5_DWork.Derivative1_RWORK_b.TimeStampB;
    real_T* lastTime = &f14tmp5_DWork.Derivative1_RWORK_b.TimeStampA;
    real_T* lastU = &f14tmp5_DWork.Derivative1_RWORK_b.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp5_DWork.Derivative1_RWORK_b.TimeStampB;
        lastU = &f14tmp5_DWork.Derivative1_RWORK_b.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp5_DWork.Derivative1_RWORK_b.TimeStampB;
        lastU = &f14tmp5_DWork.Derivative1_RWORK_b.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp5_rtM->Timing.t[0];
    *lastU++ = f14tmp5_B.TransferFcn1_k;
  }

  if (rtmIsMajorTimeStep(f14tmp5_rtM) &&
      f14tmp5_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* Update for RandomNumber: '<S25>/White Noise' */
    f14tmp5_DWork.NextOutput_a = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp5_DWork.RandSeed_f) * f14tmp5_P.WhiteNoise_StdDev_f +
      f14tmp5_P.WhiteNoise_Mean_n;
  }

  /* Update for Derivative: '<S29>/Derivative' */
  {
    real_T timeStampA = f14tmp5_DWork.Derivative_RWORK_lc.TimeStampA;
    real_T timeStampB = f14tmp5_DWork.Derivative_RWORK_lc.TimeStampB;
    real_T* lastTime = &f14tmp5_DWork.Derivative_RWORK_lc.TimeStampA;
    real_T* lastU = &f14tmp5_DWork.Derivative_RWORK_lc.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp5_DWork.Derivative_RWORK_lc.TimeStampB;
        lastU = &f14tmp5_DWork.Derivative_RWORK_lc.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp5_DWork.Derivative_RWORK_lc.TimeStampB;
        lastU = &f14tmp5_DWork.Derivative_RWORK_lc.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp5_rtM->Timing.t[0];
    *lastU++ = f14tmp5_B.TransferFcn2_o;
  }

  /* Update for Derivative: '<S29>/Derivative1' */
  {
    real_T timeStampA = f14tmp5_DWork.Derivative1_RWORK_d.TimeStampA;
    real_T timeStampB = f14tmp5_DWork.Derivative1_RWORK_d.TimeStampB;
    real_T* lastTime = &f14tmp5_DWork.Derivative1_RWORK_d.TimeStampA;
    real_T* lastU = &f14tmp5_DWork.Derivative1_RWORK_d.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp5_DWork.Derivative1_RWORK_d.TimeStampB;
        lastU = &f14tmp5_DWork.Derivative1_RWORK_d.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp5_DWork.Derivative1_RWORK_d.TimeStampB;
        lastU = &f14tmp5_DWork.Derivative1_RWORK_d.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp5_rtM->Timing.t[0];
    *lastU++ = f14tmp5_B.TransferFcn1_i;
  }

  if (rtmIsMajorTimeStep(f14tmp5_rtM) &&
      f14tmp5_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* Update for RandomNumber: '<S30>/White Noise' */
    f14tmp5_DWork.NextOutput_e = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp5_DWork.RandSeed_d) * f14tmp5_P.WhiteNoise_StdDev_k +
      f14tmp5_P.WhiteNoise_Mean_b;
  }

  if (rtmIsMajorTimeStep(f14tmp5_rtM)) {
    rt_ertODEUpdateContinuousStates(&f14tmp5_rtM->solverInfo);
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
  if (!(++f14tmp5_rtM->Timing.clockTick0)) {
    ++f14tmp5_rtM->Timing.clockTickH0;
  }

  f14tmp5_rtM->Timing.t[0] = rtsiGetSolverStopTime(&f14tmp5_rtM->solverInfo);

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
    if (!(++f14tmp5_rtM->Timing.clockTick1)) {
      ++f14tmp5_rtM->Timing.clockTickH1;
    }

    f14tmp5_rtM->Timing.t[1] = f14tmp5_rtM->Timing.clockTick1 *
      f14tmp5_rtM->Timing.stepSize1 + f14tmp5_rtM->Timing.clockTickH1 *
      f14tmp5_rtM->Timing.stepSize1 * 4294967296.0;
  }

  if (rtmIsMajorTimeStep(f14tmp5_rtM) &&
      f14tmp5_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* Update absolute timer for sample time: [0.1s, 0.0s] */
    /* The "clockTick2" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick2"
     * and "Timing.stepSize2". Size of "clockTick2" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick2 and the high bits
     * Timing.clockTickH2. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++f14tmp5_rtM->Timing.clockTick2)) {
      ++f14tmp5_rtM->Timing.clockTickH2;
    }

    f14tmp5_rtM->Timing.t[2] = f14tmp5_rtM->Timing.clockTick2 *
      f14tmp5_rtM->Timing.stepSize2 + f14tmp5_rtM->Timing.clockTickH2 *
      f14tmp5_rtM->Timing.stepSize2 * 4294967296.0;
  }

  rate_scheduler();
}

/* Derivatives for root system: '<Root>' */
void f14tmp5_derivatives(void)
{
  /* Derivatives for TransferFcn: '<S6>/Transfer Fcn.2' */
  {
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE = f14tmp5_B.Sum1_o;
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE += (f14tmp5_P.TransferFcn2_A)*
      f14tmp5_X.TransferFcn2_CSTATE;
  }

  /* Derivatives for TransferFcn: '<S6>/Transfer Fcn.1' */
  {
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE = f14tmp5_B.Sum2;
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE += (f14tmp5_P.TransferFcn1_A)*
      f14tmp5_X.TransferFcn1_CSTATE;
  }

  /* Derivatives for TransferFcn: '<S1>/Actuator Model' */
  {
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE = f14tmp5_B.Sum_n;
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE += (f14tmp5_P.ActuatorModel_A)*
      f14tmp5_X.ActuatorModel_CSTATE;
  }

  /* Derivatives for TransferFcn: '<S8>/W-gust model' */
  {
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE[0] = f14tmp5_B.Output;
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE[0] += (f14tmp5_P.Wgustmodel_A[0])*
      f14tmp5_X.Wgustmodel_CSTATE[0] + (f14tmp5_P.Wgustmodel_A[1])*
      f14tmp5_X.Wgustmodel_CSTATE[1];
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE[1]= f14tmp5_X.Wgustmodel_CSTATE[0];
  }

  /* Derivatives for TransferFcn: '<S8>/Q-gust model' */
  {
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE = f14tmp5_B.Wgustmodel;
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE += (f14tmp5_P.Qgustmodel_A)*
      f14tmp5_X.Qgustmodel_CSTATE;
  }

  /* Derivatives for TransferFcn: '<S7>/Alpha-sensor Low-pass Filter' */
  {
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CSTATE = f14tmp5_B.Gain5;
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CSTATE += (f14tmp5_P.AlphasensorLowpassFilter_A)*
      f14tmp5_X.AlphasensorLowpassFilter_CSTATE;
  }

  /* Derivatives for TransferFcn: '<S7>/Stick Prefilter' */
  {
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE = f14tmp5_B.Sum1_k;
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE += (f14tmp5_P.StickPrefilter_A)*
      f14tmp5_X.StickPrefilter_CSTATE;
  }

  /* Derivatives for TransferFcn: '<S7>/Pitch Rate Lead Filter' */
  {
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE = f14tmp5_B.TransferFcn1;
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE += (f14tmp5_P.PitchRateLeadFilter_A)*
      f14tmp5_X.PitchRateLeadFilter_CSTATE;
  }

  /* Derivatives for TransferFcn: '<S7>/Proportional plus integral compensator' */
  {
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompens = f14tmp5_B.Sum2_f;
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompens +=
      (f14tmp5_P.Proportionalplusintegralcompens)*
      f14tmp5_X.Proportionalplusintegralcompens;
  }

  /* Derivatives for TransferFcn: '<S11>/Transfer Fcn.2' */
  {
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_h = f14tmp5_B.Sum1_e;
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_h += (f14tmp5_P.TransferFcn2_A_j)*
      f14tmp5_X.TransferFcn2_CSTATE_h;
  }

  /* Derivatives for TransferFcn: '<S11>/Transfer Fcn.1' */
  {
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_p = f14tmp5_B.Sum2_c;
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_p += (f14tmp5_P.TransferFcn1_A_n)*
      f14tmp5_X.TransferFcn1_CSTATE_p;
  }

  /* Derivatives for TransferFcn: '<S2>/Actuator Model' */
  {
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_a = f14tmp5_B.Sum_l;
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_a += (f14tmp5_P.ActuatorModel_A_j)*
      f14tmp5_X.ActuatorModel_CSTATE_a;
  }

  /* Derivatives for TransferFcn: '<S13>/W-gust model' */
  {
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_f[0] = f14tmp5_B.Output_e;
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_f[0] += (f14tmp5_P.Wgustmodel_A_l[0])*
      f14tmp5_X.Wgustmodel_CSTATE_f[0]
      + (f14tmp5_P.Wgustmodel_A_l[1])*f14tmp5_X.Wgustmodel_CSTATE_f[1];
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_f[1]= f14tmp5_X.Wgustmodel_CSTATE_f[0];
  }

  /* Derivatives for TransferFcn: '<S13>/Q-gust model' */
  {
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_d = f14tmp5_B.Wgustmodel_j;
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_d += (f14tmp5_P.Qgustmodel_A_e)*
      f14tmp5_X.Qgustmodel_CSTATE_d;
  }

  /* Derivatives for TransferFcn: '<S12>/Alpha-sensor Low-pass Filter' */
  {
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CSTA_g = f14tmp5_B.Gain5_h;
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CSTA_g +=
      (f14tmp5_P.AlphasensorLowpassFilter_A_d)*
      f14tmp5_X.AlphasensorLowpassFilter_CSTA_g;
  }

  /* Derivatives for TransferFcn: '<S12>/Stick Prefilter' */
  {
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_a = f14tmp5_B.Sum1_n;
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_a += (f14tmp5_P.StickPrefilter_A_c)*
      f14tmp5_X.StickPrefilter_CSTATE_a;
  }

  /* Derivatives for TransferFcn: '<S12>/Pitch Rate Lead Filter' */
  {
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_k = f14tmp5_B.TransferFcn1_a;
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_k += (f14tmp5_P.PitchRateLeadFilter_A_c)*
      f14tmp5_X.PitchRateLeadFilter_CSTATE_k;
  }

  /* Derivatives for TransferFcn: '<S12>/Proportional plus integral compensator' */
  {
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompe_n = f14tmp5_B.Sum2_k;
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompe_n +=
      (f14tmp5_P.Proportionalplusintegralcompe_d)*
      f14tmp5_X.Proportionalplusintegralcompe_n;
  }

  /* Derivatives for TransferFcn: '<S16>/Transfer Fcn.2' */
  {
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_n = f14tmp5_B.Sum1_dr;
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_n += (f14tmp5_P.TransferFcn2_A_l)*
      f14tmp5_X.TransferFcn2_CSTATE_n;
  }

  /* Derivatives for TransferFcn: '<S16>/Transfer Fcn.1' */
  {
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_k = f14tmp5_B.Sum2_o;
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_k += (f14tmp5_P.TransferFcn1_A_d)*
      f14tmp5_X.TransferFcn1_CSTATE_k;
  }

  /* Derivatives for TransferFcn: '<S3>/Actuator Model' */
  {
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_f = f14tmp5_B.Sum_o;
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_f += (f14tmp5_P.ActuatorModel_A_g)*
      f14tmp5_X.ActuatorModel_CSTATE_f;
  }

  /* Derivatives for TransferFcn: '<S18>/W-gust model' */
  {
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_i[0] = f14tmp5_B.Output_c;
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_i[0] += (f14tmp5_P.Wgustmodel_A_m[0])*
      f14tmp5_X.Wgustmodel_CSTATE_i[0]
      + (f14tmp5_P.Wgustmodel_A_m[1])*f14tmp5_X.Wgustmodel_CSTATE_i[1];
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_i[1]= f14tmp5_X.Wgustmodel_CSTATE_i[0];
  }

  /* Derivatives for TransferFcn: '<S18>/Q-gust model' */
  {
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_k = f14tmp5_B.Wgustmodel_e;
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_k += (f14tmp5_P.Qgustmodel_A_b)*
      f14tmp5_X.Qgustmodel_CSTATE_k;
  }

  /* Derivatives for TransferFcn: '<S17>/Alpha-sensor Low-pass Filter' */
  {
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CSTA_i = f14tmp5_B.Gain5_p;
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CSTA_i +=
      (f14tmp5_P.AlphasensorLowpassFilter_A_c)*
      f14tmp5_X.AlphasensorLowpassFilter_CSTA_i;
  }

  /* Derivatives for TransferFcn: '<S17>/Stick Prefilter' */
  {
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_j = f14tmp5_B.Sum1_n0;
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_j += (f14tmp5_P.StickPrefilter_A_e)*
      f14tmp5_X.StickPrefilter_CSTATE_j;
  }

  /* Derivatives for TransferFcn: '<S17>/Pitch Rate Lead Filter' */
  {
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_n = f14tmp5_B.TransferFcn1_g;
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_n += (f14tmp5_P.PitchRateLeadFilter_A_i)*
      f14tmp5_X.PitchRateLeadFilter_CSTATE_n;
  }

  /* Derivatives for TransferFcn: '<S17>/Proportional plus integral compensator' */
  {
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompe_h = f14tmp5_B.Sum2_g;
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompe_h +=
      (f14tmp5_P.Proportionalplusintegralcompe_h)*
      f14tmp5_X.Proportionalplusintegralcompe_h;
  }

  /* Derivatives for TransferFcn: '<S21>/Transfer Fcn.2' */
  {
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_e = f14tmp5_B.Sum1_f;
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_e += (f14tmp5_P.TransferFcn2_A_jz)*
      f14tmp5_X.TransferFcn2_CSTATE_e;
  }

  /* Derivatives for TransferFcn: '<S21>/Transfer Fcn.1' */
  {
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_j = f14tmp5_B.Sum2_cx;
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_j += (f14tmp5_P.TransferFcn1_A_a)*
      f14tmp5_X.TransferFcn1_CSTATE_j;
  }

  /* Derivatives for TransferFcn: '<S4>/Actuator Model' */
  {
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_p = f14tmp5_B.Sum_k;
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_p += (f14tmp5_P.ActuatorModel_A_p)*
      f14tmp5_X.ActuatorModel_CSTATE_p;
  }

  /* Derivatives for TransferFcn: '<S23>/W-gust model' */
  {
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_k[0] = f14tmp5_B.Output_k;
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_k[0] += (f14tmp5_P.Wgustmodel_A_b[0])*
      f14tmp5_X.Wgustmodel_CSTATE_k[0]
      + (f14tmp5_P.Wgustmodel_A_b[1])*f14tmp5_X.Wgustmodel_CSTATE_k[1];
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_k[1]= f14tmp5_X.Wgustmodel_CSTATE_k[0];
  }

  /* Derivatives for TransferFcn: '<S23>/Q-gust model' */
  {
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_a = f14tmp5_B.Wgustmodel_h;
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_a += (f14tmp5_P.Qgustmodel_A_g)*
      f14tmp5_X.Qgustmodel_CSTATE_a;
  }

  /* Derivatives for TransferFcn: '<S22>/Alpha-sensor Low-pass Filter' */
  {
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CSTA_k = f14tmp5_B.Gain5_k;
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CSTA_k +=
      (f14tmp5_P.AlphasensorLowpassFilter_A_p)*
      f14tmp5_X.AlphasensorLowpassFilter_CSTA_k;
  }

  /* Derivatives for TransferFcn: '<S22>/Stick Prefilter' */
  {
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_ju = f14tmp5_B.Sum1_dd;
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_ju += (f14tmp5_P.StickPrefilter_A_d)*
      f14tmp5_X.StickPrefilter_CSTATE_ju;
  }

  /* Derivatives for TransferFcn: '<S22>/Pitch Rate Lead Filter' */
  {
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_e = f14tmp5_B.TransferFcn1_k;
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_e += (f14tmp5_P.PitchRateLeadFilter_A_p)*
      f14tmp5_X.PitchRateLeadFilter_CSTATE_e;
  }

  /* Derivatives for TransferFcn: '<S22>/Proportional plus integral compensator' */
  {
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompe_j = f14tmp5_B.Sum2_gm;
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompe_j +=
      (f14tmp5_P.Proportionalplusintegralcomp_kg)*
      f14tmp5_X.Proportionalplusintegralcompe_j;
  }

  /* Derivatives for TransferFcn: '<S26>/Transfer Fcn.2' */
  {
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_k = f14tmp5_B.Sum1_g;
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_k += (f14tmp5_P.TransferFcn2_A_c)*
      f14tmp5_X.TransferFcn2_CSTATE_k;
  }

  /* Derivatives for TransferFcn: '<S26>/Transfer Fcn.1' */
  {
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_pe = f14tmp5_B.Sum2_oa;
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_pe += (f14tmp5_P.TransferFcn1_A_o)*
      f14tmp5_X.TransferFcn1_CSTATE_pe;
  }

  /* Derivatives for TransferFcn: '<S5>/Actuator Model' */
  {
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_o = f14tmp5_B.Sum_m;
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_o += (f14tmp5_P.ActuatorModel_A_gl)*
      f14tmp5_X.ActuatorModel_CSTATE_o;
  }

  /* Derivatives for TransferFcn: '<S28>/W-gust model' */
  {
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_if[0] = f14tmp5_B.Output_a;
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_if[0] += (f14tmp5_P.Wgustmodel_A_lv[0])*
      f14tmp5_X.Wgustmodel_CSTATE_if[0]
      + (f14tmp5_P.Wgustmodel_A_lv[1])*f14tmp5_X.Wgustmodel_CSTATE_if[1];
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_if[1]= f14tmp5_X.Wgustmodel_CSTATE_if[0];
  }

  /* Derivatives for TransferFcn: '<S28>/Q-gust model' */
  {
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_m = f14tmp5_B.Wgustmodel_o;
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_m += (f14tmp5_P.Qgustmodel_A_gl)*
      f14tmp5_X.Qgustmodel_CSTATE_m;
  }

  /* Derivatives for TransferFcn: '<S27>/Alpha-sensor Low-pass Filter' */
  {
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CST_ku = f14tmp5_B.Gain5_c;
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CST_ku +=
      (f14tmp5_P.AlphasensorLowpassFilter_A_a)*
      f14tmp5_X.AlphasensorLowpassFilter_CST_ku;
  }

  /* Derivatives for TransferFcn: '<S27>/Stick Prefilter' */
  {
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_m = f14tmp5_B.Sum1_h;
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_m += (f14tmp5_P.StickPrefilter_A_ee)*
      f14tmp5_X.StickPrefilter_CSTATE_m;
  }

  /* Derivatives for TransferFcn: '<S27>/Pitch Rate Lead Filter' */
  {
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_f = f14tmp5_B.TransferFcn1_i;
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_f += (f14tmp5_P.PitchRateLeadFilter_A_m)*
      f14tmp5_X.PitchRateLeadFilter_CSTATE_f;
  }

  /* Derivatives for TransferFcn: '<S27>/Proportional plus integral compensator' */
  {
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompe_k = f14tmp5_B.Sum2_f5;
    ((StateDerivatives_f14tmp5 *) f14tmp5_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompe_k +=
      (f14tmp5_P.Proportionalplusintegralcomp_mw)*
      f14tmp5_X.Proportionalplusintegralcompe_k;
  }
}

/* Model initialize function */
void f14tmp5_initialize(void)
{
  {
    uint32_T tseed;
    int32_T r;
    int32_T t;
    real_T tmp;

    /* Start for RandomNumber: '<S10>/White Noise' */
    tmp = floor(f14tmp5_P.WhiteNoise_Seed);
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

    f14tmp5_DWork.RandSeed = tseed;
    f14tmp5_DWork.NextOutput = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp5_DWork.RandSeed) * f14tmp5_P.WhiteNoise_StdDev +
      f14tmp5_P.WhiteNoise_Mean;

    /* End of Start for RandomNumber: '<S10>/White Noise' */
    /* Start for RandomNumber: '<S15>/White Noise' */
    tmp = floor(f14tmp5_P.WhiteNoise_Seed_i);
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

    f14tmp5_DWork.RandSeed_n = tseed;
    f14tmp5_DWork.NextOutput_f = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp5_DWork.RandSeed_n) * f14tmp5_P.WhiteNoise_StdDev_n +
      f14tmp5_P.WhiteNoise_Mean_j;

    /* End of Start for RandomNumber: '<S15>/White Noise' */
    /* Start for RandomNumber: '<S20>/White Noise' */
    tmp = floor(f14tmp5_P.WhiteNoise_Seed_j);
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

    f14tmp5_DWork.RandSeed_e = tseed;
    f14tmp5_DWork.NextOutput_h = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp5_DWork.RandSeed_e) * f14tmp5_P.WhiteNoise_StdDev_g +
      f14tmp5_P.WhiteNoise_Mean_k;

    /* End of Start for RandomNumber: '<S20>/White Noise' */
    /* Start for RandomNumber: '<S25>/White Noise' */
    tmp = floor(f14tmp5_P.WhiteNoise_Seed_c);
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

    f14tmp5_DWork.RandSeed_f = tseed;
    f14tmp5_DWork.NextOutput_a = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp5_DWork.RandSeed_f) * f14tmp5_P.WhiteNoise_StdDev_f +
      f14tmp5_P.WhiteNoise_Mean_n;

    /* End of Start for RandomNumber: '<S25>/White Noise' */
    /* Start for RandomNumber: '<S30>/White Noise' */
    tmp = floor(f14tmp5_P.WhiteNoise_Seed_g);
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

    f14tmp5_DWork.RandSeed_d = tseed;
    f14tmp5_DWork.NextOutput_e = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp5_DWork.RandSeed_d) * f14tmp5_P.WhiteNoise_StdDev_k +
      f14tmp5_P.WhiteNoise_Mean_b;

    /* End of Start for RandomNumber: '<S30>/White Noise' */
  }

  /* InitializeConditions for TransferFcn: '<S6>/Transfer Fcn.2' */
  f14tmp5_X.TransferFcn2_CSTATE = 0.0;

  /* InitializeConditions for Derivative: '<S9>/Derivative' */
  f14tmp5_DWork.Derivative_RWORK.TimeStampA = rtInf;
  f14tmp5_DWork.Derivative_RWORK.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S6>/Transfer Fcn.1' */
  f14tmp5_X.TransferFcn1_CSTATE = 0.0;

  /* InitializeConditions for Derivative: '<S9>/Derivative1' */
  f14tmp5_DWork.Derivative1_RWORK.TimeStampA = rtInf;
  f14tmp5_DWork.Derivative1_RWORK.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S1>/Actuator Model' */
  f14tmp5_X.ActuatorModel_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S8>/W-gust model' */
  f14tmp5_X.Wgustmodel_CSTATE[0] = 0.0;
  f14tmp5_X.Wgustmodel_CSTATE[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S8>/Q-gust model' */
  f14tmp5_X.Qgustmodel_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S7>/Alpha-sensor Low-pass Filter' */
  f14tmp5_X.AlphasensorLowpassFilter_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S7>/Stick Prefilter' */
  f14tmp5_X.StickPrefilter_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S7>/Pitch Rate Lead Filter' */
  f14tmp5_X.PitchRateLeadFilter_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S7>/Proportional plus integral compensator' */
  f14tmp5_X.Proportionalplusintegralcompens = 0.0;

  /* InitializeConditions for TransferFcn: '<S11>/Transfer Fcn.2' */
  f14tmp5_X.TransferFcn2_CSTATE_h = 0.0;

  /* InitializeConditions for Derivative: '<S14>/Derivative' */
  f14tmp5_DWork.Derivative_RWORK_f.TimeStampA = rtInf;
  f14tmp5_DWork.Derivative_RWORK_f.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S11>/Transfer Fcn.1' */
  f14tmp5_X.TransferFcn1_CSTATE_p = 0.0;

  /* InitializeConditions for Derivative: '<S14>/Derivative1' */
  f14tmp5_DWork.Derivative1_RWORK_o.TimeStampA = rtInf;
  f14tmp5_DWork.Derivative1_RWORK_o.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S2>/Actuator Model' */
  f14tmp5_X.ActuatorModel_CSTATE_a = 0.0;

  /* InitializeConditions for TransferFcn: '<S13>/W-gust model' */
  f14tmp5_X.Wgustmodel_CSTATE_f[0] = 0.0;
  f14tmp5_X.Wgustmodel_CSTATE_f[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S13>/Q-gust model' */
  f14tmp5_X.Qgustmodel_CSTATE_d = 0.0;

  /* InitializeConditions for TransferFcn: '<S12>/Alpha-sensor Low-pass Filter' */
  f14tmp5_X.AlphasensorLowpassFilter_CSTA_g = 0.0;

  /* InitializeConditions for TransferFcn: '<S12>/Stick Prefilter' */
  f14tmp5_X.StickPrefilter_CSTATE_a = 0.0;

  /* InitializeConditions for TransferFcn: '<S12>/Pitch Rate Lead Filter' */
  f14tmp5_X.PitchRateLeadFilter_CSTATE_k = 0.0;

  /* InitializeConditions for TransferFcn: '<S12>/Proportional plus integral compensator' */
  f14tmp5_X.Proportionalplusintegralcompe_n = 0.0;

  /* InitializeConditions for TransferFcn: '<S16>/Transfer Fcn.2' */
  f14tmp5_X.TransferFcn2_CSTATE_n = 0.0;

  /* InitializeConditions for Derivative: '<S19>/Derivative' */
  f14tmp5_DWork.Derivative_RWORK_l.TimeStampA = rtInf;
  f14tmp5_DWork.Derivative_RWORK_l.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S16>/Transfer Fcn.1' */
  f14tmp5_X.TransferFcn1_CSTATE_k = 0.0;

  /* InitializeConditions for Derivative: '<S19>/Derivative1' */
  f14tmp5_DWork.Derivative1_RWORK_k.TimeStampA = rtInf;
  f14tmp5_DWork.Derivative1_RWORK_k.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S3>/Actuator Model' */
  f14tmp5_X.ActuatorModel_CSTATE_f = 0.0;

  /* InitializeConditions for TransferFcn: '<S18>/W-gust model' */
  f14tmp5_X.Wgustmodel_CSTATE_i[0] = 0.0;
  f14tmp5_X.Wgustmodel_CSTATE_i[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S18>/Q-gust model' */
  f14tmp5_X.Qgustmodel_CSTATE_k = 0.0;

  /* InitializeConditions for TransferFcn: '<S17>/Alpha-sensor Low-pass Filter' */
  f14tmp5_X.AlphasensorLowpassFilter_CSTA_i = 0.0;

  /* InitializeConditions for TransferFcn: '<S17>/Stick Prefilter' */
  f14tmp5_X.StickPrefilter_CSTATE_j = 0.0;

  /* InitializeConditions for TransferFcn: '<S17>/Pitch Rate Lead Filter' */
  f14tmp5_X.PitchRateLeadFilter_CSTATE_n = 0.0;

  /* InitializeConditions for TransferFcn: '<S17>/Proportional plus integral compensator' */
  f14tmp5_X.Proportionalplusintegralcompe_h = 0.0;

  /* InitializeConditions for TransferFcn: '<S21>/Transfer Fcn.2' */
  f14tmp5_X.TransferFcn2_CSTATE_e = 0.0;

  /* InitializeConditions for Derivative: '<S24>/Derivative' */
  f14tmp5_DWork.Derivative_RWORK_k.TimeStampA = rtInf;
  f14tmp5_DWork.Derivative_RWORK_k.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S21>/Transfer Fcn.1' */
  f14tmp5_X.TransferFcn1_CSTATE_j = 0.0;

  /* InitializeConditions for Derivative: '<S24>/Derivative1' */
  f14tmp5_DWork.Derivative1_RWORK_b.TimeStampA = rtInf;
  f14tmp5_DWork.Derivative1_RWORK_b.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S4>/Actuator Model' */
  f14tmp5_X.ActuatorModel_CSTATE_p = 0.0;

  /* InitializeConditions for TransferFcn: '<S23>/W-gust model' */
  f14tmp5_X.Wgustmodel_CSTATE_k[0] = 0.0;
  f14tmp5_X.Wgustmodel_CSTATE_k[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S23>/Q-gust model' */
  f14tmp5_X.Qgustmodel_CSTATE_a = 0.0;

  /* InitializeConditions for TransferFcn: '<S22>/Alpha-sensor Low-pass Filter' */
  f14tmp5_X.AlphasensorLowpassFilter_CSTA_k = 0.0;

  /* InitializeConditions for TransferFcn: '<S22>/Stick Prefilter' */
  f14tmp5_X.StickPrefilter_CSTATE_ju = 0.0;

  /* InitializeConditions for TransferFcn: '<S22>/Pitch Rate Lead Filter' */
  f14tmp5_X.PitchRateLeadFilter_CSTATE_e = 0.0;

  /* InitializeConditions for TransferFcn: '<S22>/Proportional plus integral compensator' */
  f14tmp5_X.Proportionalplusintegralcompe_j = 0.0;

  /* InitializeConditions for TransferFcn: '<S26>/Transfer Fcn.2' */
  f14tmp5_X.TransferFcn2_CSTATE_k = 0.0;

  /* InitializeConditions for Derivative: '<S29>/Derivative' */
  f14tmp5_DWork.Derivative_RWORK_lc.TimeStampA = rtInf;
  f14tmp5_DWork.Derivative_RWORK_lc.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S26>/Transfer Fcn.1' */
  f14tmp5_X.TransferFcn1_CSTATE_pe = 0.0;

  /* InitializeConditions for Derivative: '<S29>/Derivative1' */
  f14tmp5_DWork.Derivative1_RWORK_d.TimeStampA = rtInf;
  f14tmp5_DWork.Derivative1_RWORK_d.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S5>/Actuator Model' */
  f14tmp5_X.ActuatorModel_CSTATE_o = 0.0;

  /* InitializeConditions for TransferFcn: '<S28>/W-gust model' */
  f14tmp5_X.Wgustmodel_CSTATE_if[0] = 0.0;
  f14tmp5_X.Wgustmodel_CSTATE_if[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S28>/Q-gust model' */
  f14tmp5_X.Qgustmodel_CSTATE_m = 0.0;

  /* InitializeConditions for TransferFcn: '<S27>/Alpha-sensor Low-pass Filter' */
  f14tmp5_X.AlphasensorLowpassFilter_CST_ku = 0.0;

  /* InitializeConditions for TransferFcn: '<S27>/Stick Prefilter' */
  f14tmp5_X.StickPrefilter_CSTATE_m = 0.0;

  /* InitializeConditions for TransferFcn: '<S27>/Pitch Rate Lead Filter' */
  f14tmp5_X.PitchRateLeadFilter_CSTATE_f = 0.0;

  /* InitializeConditions for TransferFcn: '<S27>/Proportional plus integral compensator' */
  f14tmp5_X.Proportionalplusintegralcompe_k = 0.0;
}

/* Model terminate function */
void f14tmp5_terminate(void)
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
  f14tmp5_output();

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  f14tmp5_update();

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
  f14tmp5_initialize();
}

void MdlTerminate(void)
{
  f14tmp5_terminate();
}

rtModel_f14tmp5 *f14tmp5(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)f14tmp5_rtM, 0,
                sizeof(rtModel_f14tmp5));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&f14tmp5_rtM->solverInfo,
                          &f14tmp5_rtM->Timing.simTimeStep);
    rtsiSetTPtr(&f14tmp5_rtM->solverInfo, &rtmGetTPtr(f14tmp5_rtM));
    rtsiSetStepSizePtr(&f14tmp5_rtM->solverInfo, &f14tmp5_rtM->Timing.stepSize0);
    rtsiSetdXPtr(&f14tmp5_rtM->solverInfo, &f14tmp5_rtM->ModelData.derivs);
    rtsiSetContStatesPtr(&f14tmp5_rtM->solverInfo,
                         &f14tmp5_rtM->ModelData.contStates);
    rtsiSetNumContStatesPtr(&f14tmp5_rtM->solverInfo,
      &f14tmp5_rtM->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&f14tmp5_rtM->solverInfo, (&rtmGetErrorStatus
      (f14tmp5_rtM)));
    rtsiSetRTModelPtr(&f14tmp5_rtM->solverInfo, f14tmp5_rtM);
  }

  rtsiSetSimTimeStep(&f14tmp5_rtM->solverInfo, MAJOR_TIME_STEP);
  f14tmp5_rtM->ModelData.intgData.y = f14tmp5_rtM->ModelData.odeY;
  f14tmp5_rtM->ModelData.intgData.f[0] = f14tmp5_rtM->ModelData.odeF[0];
  f14tmp5_rtM->ModelData.intgData.f[1] = f14tmp5_rtM->ModelData.odeF[1];
  f14tmp5_rtM->ModelData.intgData.f[2] = f14tmp5_rtM->ModelData.odeF[2];
  f14tmp5_rtM->ModelData.intgData.f[3] = f14tmp5_rtM->ModelData.odeF[3];
  f14tmp5_rtM->ModelData.contStates = ((real_T *) &f14tmp5_X);
  rtsiSetSolverData(&f14tmp5_rtM->solverInfo, (void *)
                    &f14tmp5_rtM->ModelData.intgData);
  rtsiSetSolverName(&f14tmp5_rtM->solverInfo,"ode4");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = f14tmp5_rtM->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    mdlTsMap[2] = 2;
    f14tmp5_rtM->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    f14tmp5_rtM->Timing.sampleTimes = (&f14tmp5_rtM->Timing.sampleTimesArray[0]);
    f14tmp5_rtM->Timing.offsetTimes = (&f14tmp5_rtM->Timing.offsetTimesArray[0]);

    /* task periods */
    f14tmp5_rtM->Timing.sampleTimes[0] = (0.0);
    f14tmp5_rtM->Timing.sampleTimes[1] = (0.01);
    f14tmp5_rtM->Timing.sampleTimes[2] = (0.1);

    /* task offsets */
    f14tmp5_rtM->Timing.offsetTimes[0] = (0.0);
    f14tmp5_rtM->Timing.offsetTimes[1] = (0.0);
    f14tmp5_rtM->Timing.offsetTimes[2] = (0.0);
  }

  rtmSetTPtr(f14tmp5_rtM, &f14tmp5_rtM->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = f14tmp5_rtM->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    mdlSampleHits[2] = 1;
    f14tmp5_rtM->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(f14tmp5_rtM, 10.0);
  f14tmp5_rtM->Timing.stepSize0 = 0.01;
  f14tmp5_rtM->Timing.stepSize1 = 0.01;
  f14tmp5_rtM->Timing.stepSize2 = 0.1;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    f14tmp5_rtM->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(f14tmp5_rtM->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(f14tmp5_rtM->rtwLogInfo, (NULL));
    rtliSetLogT(f14tmp5_rtM->rtwLogInfo, "tout");
    rtliSetLogX(f14tmp5_rtM->rtwLogInfo, "");
    rtliSetLogXFinal(f14tmp5_rtM->rtwLogInfo, "");
    rtliSetSigLog(f14tmp5_rtM->rtwLogInfo, "");
    rtliSetLogVarNameModifier(f14tmp5_rtM->rtwLogInfo, "rt_");
    rtliSetLogFormat(f14tmp5_rtM->rtwLogInfo, 0);
    rtliSetLogMaxRows(f14tmp5_rtM->rtwLogInfo, 1000);
    rtliSetLogDecimation(f14tmp5_rtM->rtwLogInfo, 1);
    rtliSetLogY(f14tmp5_rtM->rtwLogInfo, "");
    rtliSetLogYSignalInfo(f14tmp5_rtM->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(f14tmp5_rtM->rtwLogInfo, (NULL));
  }

  f14tmp5_rtM->solverInfoPtr = (&f14tmp5_rtM->solverInfo);
  f14tmp5_rtM->Timing.stepSize = (0.01);
  rtsiSetFixedStepSize(&f14tmp5_rtM->solverInfo, 0.01);
  rtsiSetSolverMode(&f14tmp5_rtM->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  f14tmp5_rtM->ModelData.blockIO = ((void *) &f14tmp5_B);
  (void) memset(((void *) &f14tmp5_B), 0,
                sizeof(BlockIO_f14tmp5));

  /* parameters */
  f14tmp5_rtM->ModelData.defaultParam = ((real_T *)&f14tmp5_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &f14tmp5_X;
    f14tmp5_rtM->ModelData.contStates = (x);
    (void) memset((void *)&f14tmp5_X, 0,
                  sizeof(ContinuousStates_f14tmp5));
  }

  /* states (dwork) */
  f14tmp5_rtM->Work.dwork = ((void *) &f14tmp5_DWork);
  (void) memset((void *)&f14tmp5_DWork, 0,
                sizeof(D_Work_f14tmp5));

  /* Initialize DataMapInfo substructure containing ModelMap for C API */
  f14tmp5_InitializeDataMapInfo(f14tmp5_rtM);

  /* Initialize Sizes */
  f14tmp5_rtM->Sizes.numContStates = (50);/* Number of continuous states */
  f14tmp5_rtM->Sizes.numY = (0);       /* Number of model outputs */
  f14tmp5_rtM->Sizes.numU = (0);       /* Number of model inputs */
  f14tmp5_rtM->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  f14tmp5_rtM->Sizes.numSampTimes = (3);/* Number of sample times */
  f14tmp5_rtM->Sizes.numBlocks = (200);/* Number of blocks */
  f14tmp5_rtM->Sizes.numBlockIO = (180);/* Number of block outputs */
  f14tmp5_rtM->Sizes.numBlockPrms = (210);/* Sum of parameter "widths" */
  return f14tmp5_rtM;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
