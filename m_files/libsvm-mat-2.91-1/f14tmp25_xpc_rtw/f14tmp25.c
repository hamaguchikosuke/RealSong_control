/*
 * f14tmp25.c
 *
 * Code generation for model "f14tmp25".
 *
 * Model version              : 1.0
 * Simulink Coder version : 8.3 (R2012b) 20-Jul-2012
 * C source code generated on : Mon Sep 16 12:50:49 2013
 *
 * Target selection: xpctarget.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->32-bit x86 compatible
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "rt_logging_mmi.h"
#include "f14tmp25_capi.h"
#include "f14tmp25.h"
#include "f14tmp25_private.h"

/* Block signals (auto storage) */
BlockIO_f14tmp25 f14tmp25_B;

/* Continuous states */
ContinuousStates_f14tmp25 f14tmp25_X;

/* Block states (auto storage) */
D_Work_f14tmp25 f14tmp25_DWork;

/* Real-time model */
rtModel_f14tmp25 f14tmp25_rtM_;
rtModel_f14tmp25 *const f14tmp25_rtM = &f14tmp25_rtM_;
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
  (f14tmp25_rtM->Timing.TaskCounters.TID[2])++;
  if ((f14tmp25_rtM->Timing.TaskCounters.TID[2]) > 9) {/* Sample time: [0.1s, 0.0s] */
    f14tmp25_rtM->Timing.TaskCounters.TID[2] = 0;
  }

  f14tmp25_rtM->Timing.sampleHits[2] = (f14tmp25_rtM->Timing.TaskCounters.TID[2]
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
  int_T nXc = 250;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  f14tmp25_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  f14tmp25_output();
  f14tmp25_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  f14tmp25_output();
  f14tmp25_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  f14tmp25_output();
  f14tmp25_derivatives();

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
void f14tmp25_output(void)
{
  real_T temp;
  if (rtmIsMajorTimeStep(f14tmp25_rtM)) {
    /* set solver stop time */
    if (!(f14tmp25_rtM->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&f14tmp25_rtM->solverInfo,
                            ((f14tmp25_rtM->Timing.clockTickH0 + 1) *
        f14tmp25_rtM->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&f14tmp25_rtM->solverInfo,
                            ((f14tmp25_rtM->Timing.clockTick0 + 1) *
        f14tmp25_rtM->Timing.stepSize0 + f14tmp25_rtM->Timing.clockTickH0 *
        f14tmp25_rtM->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(f14tmp25_rtM)) {
    f14tmp25_rtM->Timing.t[0] = rtsiGetT(&f14tmp25_rtM->solverInfo);
  }

  /* TransferFcn: '<S26>/Transfer Fcn.2' */
  f14tmp25_B.TransferFcn2 = f14tmp25_P.TransferFcn2_C*
    f14tmp25_X.TransferFcn2_CSTATE;

  /* Gain: '<S1>/Gain5' */
  f14tmp25_B.Gain5 = f14tmp25_P.Gain5_Gain * f14tmp25_B.TransferFcn2;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* Derivative: '<S29>/Derivative' */
  {
    real_T t = f14tmp25_rtM->Timing.t[0];
    real_T timeStampA = f14tmp25_DWork.Derivative_RWORK.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative_RWORK.TimeStampB;
    real_T *lastU = &f14tmp25_DWork.Derivative_RWORK.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp25_B.Derivative = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp25_DWork.Derivative_RWORK.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp25_B.Derivative = (f14tmp25_B.TransferFcn2 - *lastU++) / deltaT;
    }
  }

  /* TransferFcn: '<S26>/Transfer Fcn.1' */
  f14tmp25_B.TransferFcn1 = f14tmp25_P.TransferFcn1_C*
    f14tmp25_X.TransferFcn1_CSTATE;

  /* Derivative: '<S29>/Derivative1' */
  {
    real_T t = f14tmp25_rtM->Timing.t[0];
    real_T timeStampA = f14tmp25_DWork.Derivative1_RWORK.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative1_RWORK.TimeStampB;
    real_T *lastU = &f14tmp25_DWork.Derivative1_RWORK.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp25_B.Derivative1 = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp25_DWork.Derivative1_RWORK.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp25_B.Derivative1 = (f14tmp25_B.TransferFcn1 - *lastU++) / deltaT;
    }
  }

  /* Gain: '<S29>/Gain1' */
  f14tmp25_B.Gain1 = f14tmp25_P.Gain1_Gain * f14tmp25_B.Derivative1;

  /* Product: '<S29>/Product' incorporates:
   *  Constant: '<S29>/Constant'
   */
  f14tmp25_B.Product = f14tmp25_B.TransferFcn1 * f14tmp25_P.Constant_Value;

  /* Sum: '<S29>/Sum1' */
  f14tmp25_B.Sum1 = (f14tmp25_B.Gain1 - f14tmp25_B.Derivative) +
    f14tmp25_B.Product;

  /* Gain: '<S29>/Gain2' */
  f14tmp25_B.Gain2 = f14tmp25_P.Gain2_Gain * f14tmp25_B.Sum1;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* SignalGenerator: '<S1>/Pilot' */
  temp = f14tmp25_P.Pilot_Frequency * f14tmp25_rtM->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    f14tmp25_B.Pilot = f14tmp25_P.Pilot_Amplitude;
  } else {
    f14tmp25_B.Pilot = -f14tmp25_P.Pilot_Amplitude;
  }

  /* End of SignalGenerator: '<S1>/Pilot' */

  /* Sum: '<S1>/Sum1' */
  f14tmp25_B.Sum1_k = f14tmp25_B.Pilot + 0.0;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* TransferFcn: '<S1>/Actuator Model' */
  f14tmp25_B.ActuatorModel = f14tmp25_P.ActuatorModel_C*
    f14tmp25_X.ActuatorModel_CSTATE;

  /* Gain: '<S26>/Gain3' */
  f14tmp25_B.Gain3 = f14tmp25_P.Gain3_Gain * f14tmp25_B.TransferFcn1;

  /* Gain: '<S26>/Gain4' */
  f14tmp25_B.Gain4 = f14tmp25_P.Gain4_Gain * f14tmp25_B.TransferFcn2;

  /* Gain: '<S26>/Gain5' */
  f14tmp25_B.Gain5_b = f14tmp25_P.Gain5_Gain_j * f14tmp25_B.ActuatorModel;

  /* Gain: '<S26>/Gain6' */
  f14tmp25_B.Gain6 = f14tmp25_P.Gain6_Gain * f14tmp25_B.ActuatorModel;

  /* TransferFcn: '<S28>/W-gust model' */
  f14tmp25_B.Wgustmodel = f14tmp25_P.Wgustmodel_C[0]*
    f14tmp25_X.Wgustmodel_CSTATE[0] + f14tmp25_P.Wgustmodel_C[1]*
    f14tmp25_X.Wgustmodel_CSTATE[1];

  /* Gain: '<S1>/Gain' */
  f14tmp25_B.Gain = f14tmp25_P.Gain_Gain * f14tmp25_B.Wgustmodel;

  /* Sum: '<S26>/Sum1' */
  f14tmp25_B.Sum1_o = (f14tmp25_B.Gain5_b - f14tmp25_B.Gain) + f14tmp25_B.Gain3;

  /* Gain: '<S1>/Gain2' */
  f14tmp25_B.Gain2_f = f14tmp25_P.Gain2_Gain_p * f14tmp25_B.Wgustmodel;

  /* TransferFcn: '<S28>/Q-gust model' */
  f14tmp25_B.Qgustmodel = f14tmp25_P.Qgustmodel_D*f14tmp25_B.Wgustmodel;
  f14tmp25_B.Qgustmodel += f14tmp25_P.Qgustmodel_C*f14tmp25_X.Qgustmodel_CSTATE;

  /* Gain: '<S1>/Gain1' */
  f14tmp25_B.Gain1_h = f14tmp25_P.Gain1_Gain_h * f14tmp25_B.Qgustmodel;

  /* Sum: '<S1>/Sum' */
  f14tmp25_B.Sum = f14tmp25_B.Gain2_f + f14tmp25_B.Gain1_h;

  /* Sum: '<S26>/Sum2' */
  f14tmp25_B.Sum2 = (f14tmp25_B.Gain4 - f14tmp25_B.Sum) + f14tmp25_B.Gain6;

  /* TransferFcn: '<S27>/Alpha-sensor Low-pass Filter' */
  f14tmp25_B.AlphasensorLowpassFilter = f14tmp25_P.AlphasensorLowpassFilter_C*
    f14tmp25_X.AlphasensorLowpassFilter_CSTATE;

  /* TransferFcn: '<S27>/Stick Prefilter' */
  f14tmp25_B.StickPrefilter = f14tmp25_P.StickPrefilter_C*
    f14tmp25_X.StickPrefilter_CSTATE;

  /* TransferFcn: '<S27>/Pitch Rate Lead Filter' */
  f14tmp25_B.PitchRateLeadFilter = f14tmp25_P.PitchRateLeadFilter_D*
    f14tmp25_B.TransferFcn1;
  f14tmp25_B.PitchRateLeadFilter += f14tmp25_P.PitchRateLeadFilter_C*
    f14tmp25_X.PitchRateLeadFilter_CSTATE;

  /* Gain: '<S27>/Gain2' */
  f14tmp25_B.Gain2_e = f14tmp25_P.Gain2_Gain_k * f14tmp25_B.PitchRateLeadFilter;

  /* Gain: '<S27>/Gain3' */
  f14tmp25_B.Gain3_g = f14tmp25_P.Gain3_Gain_i *
    f14tmp25_B.AlphasensorLowpassFilter;

  /* Sum: '<S27>/Sum1' */
  f14tmp25_B.Sum1_d = f14tmp25_B.Gain2_e + f14tmp25_B.Gain3_g;

  /* Sum: '<S27>/Sum2' */
  f14tmp25_B.Sum2_f = f14tmp25_B.StickPrefilter - f14tmp25_B.Sum1_d;

  /* Gain: '<S27>/Gain' */
  f14tmp25_B.Gain_d = f14tmp25_P.Gain_Gain_k * f14tmp25_B.Sum2_f;

  /* TransferFcn: '<S27>/Proportional plus integral compensator' */
  f14tmp25_B.Proportionalplusintegralcompens =
    f14tmp25_P.Proportionalplusintegralcompe_i*
    f14tmp25_X.Proportionalplusintegralcompens;

  /* Sum: '<S27>/Sum' */
  f14tmp25_B.Sum_n = f14tmp25_B.Gain_d +
    f14tmp25_B.Proportionalplusintegralcompens;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* RandomNumber: '<S30>/White Noise' */
    f14tmp25_B.WhiteNoise = f14tmp25_DWork.NextOutput;

    /* Gain: '<S30>/Output' */
    f14tmp25_B.Output = f14tmp25_P.Output_Gain * f14tmp25_B.WhiteNoise;
  }

  /* TransferFcn: '<S31>/Transfer Fcn.2' */
  f14tmp25_B.TransferFcn2_b = f14tmp25_P.TransferFcn2_C_k*
    f14tmp25_X.TransferFcn2_CSTATE_h;

  /* Gain: '<S2>/Gain5' */
  f14tmp25_B.Gain5_h = f14tmp25_P.Gain5_Gain_o * f14tmp25_B.TransferFcn2_b;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* Derivative: '<S34>/Derivative' */
  {
    real_T t = f14tmp25_rtM->Timing.t[0];
    real_T timeStampA = f14tmp25_DWork.Derivative_RWORK_f.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative_RWORK_f.TimeStampB;
    real_T *lastU = &f14tmp25_DWork.Derivative_RWORK_f.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp25_B.Derivative_k = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp25_DWork.Derivative_RWORK_f.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_f.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp25_B.Derivative_k = (f14tmp25_B.TransferFcn2_b - *lastU++) / deltaT;
    }
  }

  /* TransferFcn: '<S31>/Transfer Fcn.1' */
  f14tmp25_B.TransferFcn1_a = f14tmp25_P.TransferFcn1_C_g*
    f14tmp25_X.TransferFcn1_CSTATE_p;

  /* Derivative: '<S34>/Derivative1' */
  {
    real_T t = f14tmp25_rtM->Timing.t[0];
    real_T timeStampA = f14tmp25_DWork.Derivative1_RWORK_o.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative1_RWORK_o.TimeStampB;
    real_T *lastU = &f14tmp25_DWork.Derivative1_RWORK_o.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp25_B.Derivative1_a = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp25_DWork.Derivative1_RWORK_o.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_o.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp25_B.Derivative1_a = (f14tmp25_B.TransferFcn1_a - *lastU++) / deltaT;
    }
  }

  /* Gain: '<S34>/Gain1' */
  f14tmp25_B.Gain1_c = f14tmp25_P.Gain1_Gain_n * f14tmp25_B.Derivative1_a;

  /* Product: '<S34>/Product' incorporates:
   *  Constant: '<S34>/Constant'
   */
  f14tmp25_B.Product_a = f14tmp25_B.TransferFcn1_a * f14tmp25_P.Constant_Value_m;

  /* Sum: '<S34>/Sum1' */
  f14tmp25_B.Sum1_di = (f14tmp25_B.Gain1_c - f14tmp25_B.Derivative_k) +
    f14tmp25_B.Product_a;

  /* Gain: '<S34>/Gain2' */
  f14tmp25_B.Gain2_l = f14tmp25_P.Gain2_Gain_e * f14tmp25_B.Sum1_di;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* SignalGenerator: '<S2>/Pilot' */
  temp = f14tmp25_P.Pilot_Frequency_d * f14tmp25_rtM->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    f14tmp25_B.Pilot_k = f14tmp25_P.Pilot_Amplitude_n;
  } else {
    f14tmp25_B.Pilot_k = -f14tmp25_P.Pilot_Amplitude_n;
  }

  /* End of SignalGenerator: '<S2>/Pilot' */

  /* Sum: '<S2>/Sum1' */
  f14tmp25_B.Sum1_n = f14tmp25_B.Pilot_k + 0.0;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* TransferFcn: '<S2>/Actuator Model' */
  f14tmp25_B.ActuatorModel_n = f14tmp25_P.ActuatorModel_C_f*
    f14tmp25_X.ActuatorModel_CSTATE_a;

  /* Gain: '<S31>/Gain3' */
  f14tmp25_B.Gain3_a = f14tmp25_P.Gain3_Gain_k * f14tmp25_B.TransferFcn1_a;

  /* Gain: '<S31>/Gain4' */
  f14tmp25_B.Gain4_p = f14tmp25_P.Gain4_Gain_f * f14tmp25_B.TransferFcn2_b;

  /* Gain: '<S31>/Gain5' */
  f14tmp25_B.Gain5_h4 = f14tmp25_P.Gain5_Gain_g * f14tmp25_B.ActuatorModel_n;

  /* Gain: '<S31>/Gain6' */
  f14tmp25_B.Gain6_m = f14tmp25_P.Gain6_Gain_b * f14tmp25_B.ActuatorModel_n;

  /* TransferFcn: '<S33>/W-gust model' */
  f14tmp25_B.Wgustmodel_j = f14tmp25_P.Wgustmodel_C_a[0]*
    f14tmp25_X.Wgustmodel_CSTATE_f[0]
    + f14tmp25_P.Wgustmodel_C_a[1]*f14tmp25_X.Wgustmodel_CSTATE_f[1];

  /* Gain: '<S2>/Gain' */
  f14tmp25_B.Gain_n = f14tmp25_P.Gain_Gain_l * f14tmp25_B.Wgustmodel_j;

  /* Sum: '<S31>/Sum1' */
  f14tmp25_B.Sum1_e = (f14tmp25_B.Gain5_h4 - f14tmp25_B.Gain_n) +
    f14tmp25_B.Gain3_a;

  /* Gain: '<S2>/Gain2' */
  f14tmp25_B.Gain2_o = f14tmp25_P.Gain2_Gain_h * f14tmp25_B.Wgustmodel_j;

  /* TransferFcn: '<S33>/Q-gust model' */
  f14tmp25_B.Qgustmodel_c = f14tmp25_P.Qgustmodel_D_c*f14tmp25_B.Wgustmodel_j;
  f14tmp25_B.Qgustmodel_c += f14tmp25_P.Qgustmodel_C_p*
    f14tmp25_X.Qgustmodel_CSTATE_d;

  /* Gain: '<S2>/Gain1' */
  f14tmp25_B.Gain1_i = f14tmp25_P.Gain1_Gain_p * f14tmp25_B.Qgustmodel_c;

  /* Sum: '<S2>/Sum' */
  f14tmp25_B.Sum_e = f14tmp25_B.Gain2_o + f14tmp25_B.Gain1_i;

  /* Sum: '<S31>/Sum2' */
  f14tmp25_B.Sum2_c = (f14tmp25_B.Gain4_p - f14tmp25_B.Sum_e) +
    f14tmp25_B.Gain6_m;

  /* TransferFcn: '<S32>/Alpha-sensor Low-pass Filter' */
  f14tmp25_B.AlphasensorLowpassFilter_e =
    f14tmp25_P.AlphasensorLowpassFilter_C_g*
    f14tmp25_X.AlphasensorLowpassFilter_CSTA_g;

  /* TransferFcn: '<S32>/Stick Prefilter' */
  f14tmp25_B.StickPrefilter_h = f14tmp25_P.StickPrefilter_C_p*
    f14tmp25_X.StickPrefilter_CSTATE_a;

  /* TransferFcn: '<S32>/Pitch Rate Lead Filter' */
  f14tmp25_B.PitchRateLeadFilter_f = f14tmp25_P.PitchRateLeadFilter_D_f*
    f14tmp25_B.TransferFcn1_a;
  f14tmp25_B.PitchRateLeadFilter_f += f14tmp25_P.PitchRateLeadFilter_C_l*
    f14tmp25_X.PitchRateLeadFilter_CSTATE_k;

  /* Gain: '<S32>/Gain2' */
  f14tmp25_B.Gain2_j = f14tmp25_P.Gain2_Gain_et *
    f14tmp25_B.PitchRateLeadFilter_f;

  /* Gain: '<S32>/Gain3' */
  f14tmp25_B.Gain3_l = f14tmp25_P.Gain3_Gain_b *
    f14tmp25_B.AlphasensorLowpassFilter_e;

  /* Sum: '<S32>/Sum1' */
  f14tmp25_B.Sum1_i = f14tmp25_B.Gain2_j + f14tmp25_B.Gain3_l;

  /* Sum: '<S32>/Sum2' */
  f14tmp25_B.Sum2_k = f14tmp25_B.StickPrefilter_h - f14tmp25_B.Sum1_i;

  /* Gain: '<S32>/Gain' */
  f14tmp25_B.Gain_e = f14tmp25_P.Gain_Gain_a * f14tmp25_B.Sum2_k;

  /* TransferFcn: '<S32>/Proportional plus integral compensator' */
  f14tmp25_B.Proportionalplusintegralcompe_j =
    f14tmp25_P.Proportionalplusintegralcomp_mx*
    f14tmp25_X.Proportionalplusintegralcompe_n;

  /* Sum: '<S32>/Sum' */
  f14tmp25_B.Sum_l = f14tmp25_B.Gain_e +
    f14tmp25_B.Proportionalplusintegralcompe_j;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* RandomNumber: '<S35>/White Noise' */
    f14tmp25_B.WhiteNoise_l = f14tmp25_DWork.NextOutput_f;

    /* Gain: '<S35>/Output' */
    f14tmp25_B.Output_e = f14tmp25_P.Output_Gain_l * f14tmp25_B.WhiteNoise_l;
  }

  /* TransferFcn: '<S36>/Transfer Fcn.2' */
  f14tmp25_B.TransferFcn2_d = f14tmp25_P.TransferFcn2_C_kv*
    f14tmp25_X.TransferFcn2_CSTATE_g;

  /* Gain: '<S3>/Gain5' */
  f14tmp25_B.Gain5_k = f14tmp25_P.Gain5_Gain_oi * f14tmp25_B.TransferFcn2_d;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* Derivative: '<S39>/Derivative' */
  {
    real_T t = f14tmp25_rtM->Timing.t[0];
    real_T timeStampA = f14tmp25_DWork.Derivative_RWORK_p.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative_RWORK_p.TimeStampB;
    real_T *lastU = &f14tmp25_DWork.Derivative_RWORK_p.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp25_B.Derivative_kd = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp25_DWork.Derivative_RWORK_p.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_p.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp25_B.Derivative_kd = (f14tmp25_B.TransferFcn2_d - *lastU++) / deltaT;
    }
  }

  /* TransferFcn: '<S36>/Transfer Fcn.1' */
  f14tmp25_B.TransferFcn1_b = f14tmp25_P.TransferFcn1_C_m*
    f14tmp25_X.TransferFcn1_CSTATE_o;

  /* Derivative: '<S39>/Derivative1' */
  {
    real_T t = f14tmp25_rtM->Timing.t[0];
    real_T timeStampA = f14tmp25_DWork.Derivative1_RWORK_c.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative1_RWORK_c.TimeStampB;
    real_T *lastU = &f14tmp25_DWork.Derivative1_RWORK_c.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp25_B.Derivative1_e = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp25_DWork.Derivative1_RWORK_c.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_c.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp25_B.Derivative1_e = (f14tmp25_B.TransferFcn1_b - *lastU++) / deltaT;
    }
  }

  /* Gain: '<S39>/Gain1' */
  f14tmp25_B.Gain1_a = f14tmp25_P.Gain1_Gain_m * f14tmp25_B.Derivative1_e;

  /* Product: '<S39>/Product' incorporates:
   *  Constant: '<S39>/Constant'
   */
  f14tmp25_B.Product_d = f14tmp25_B.TransferFcn1_b * f14tmp25_P.Constant_Value_f;

  /* Sum: '<S39>/Sum1' */
  f14tmp25_B.Sum1_h = (f14tmp25_B.Gain1_a - f14tmp25_B.Derivative_kd) +
    f14tmp25_B.Product_d;

  /* Gain: '<S39>/Gain2' */
  f14tmp25_B.Gain2_f0 = f14tmp25_P.Gain2_Gain_k5 * f14tmp25_B.Sum1_h;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* SignalGenerator: '<S3>/Pilot' */
  temp = f14tmp25_P.Pilot_Frequency_g * f14tmp25_rtM->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    f14tmp25_B.Pilot_m = f14tmp25_P.Pilot_Amplitude_c;
  } else {
    f14tmp25_B.Pilot_m = -f14tmp25_P.Pilot_Amplitude_c;
  }

  /* End of SignalGenerator: '<S3>/Pilot' */

  /* Sum: '<S3>/Sum1' */
  f14tmp25_B.Sum1_j = f14tmp25_B.Pilot_m + 0.0;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* TransferFcn: '<S3>/Actuator Model' */
  f14tmp25_B.ActuatorModel_i = f14tmp25_P.ActuatorModel_C_d*
    f14tmp25_X.ActuatorModel_CSTATE_j;

  /* Gain: '<S36>/Gain3' */
  f14tmp25_B.Gain3_k = f14tmp25_P.Gain3_Gain_iq * f14tmp25_B.TransferFcn1_b;

  /* Gain: '<S36>/Gain4' */
  f14tmp25_B.Gain4_h = f14tmp25_P.Gain4_Gain_fx * f14tmp25_B.TransferFcn2_d;

  /* Gain: '<S36>/Gain5' */
  f14tmp25_B.Gain5_bp = f14tmp25_P.Gain5_Gain_ot * f14tmp25_B.ActuatorModel_i;

  /* Gain: '<S36>/Gain6' */
  f14tmp25_B.Gain6_l = f14tmp25_P.Gain6_Gain_d * f14tmp25_B.ActuatorModel_i;

  /* TransferFcn: '<S38>/W-gust model' */
  f14tmp25_B.Wgustmodel_n = f14tmp25_P.Wgustmodel_C_e[0]*
    f14tmp25_X.Wgustmodel_CSTATE_m[0]
    + f14tmp25_P.Wgustmodel_C_e[1]*f14tmp25_X.Wgustmodel_CSTATE_m[1];

  /* Gain: '<S3>/Gain' */
  f14tmp25_B.Gain_i = f14tmp25_P.Gain_Gain_c * f14tmp25_B.Wgustmodel_n;

  /* Sum: '<S36>/Sum1' */
  f14tmp25_B.Sum1_p = (f14tmp25_B.Gain5_bp - f14tmp25_B.Gain_i) +
    f14tmp25_B.Gain3_k;

  /* Gain: '<S3>/Gain2' */
  f14tmp25_B.Gain2_d = f14tmp25_P.Gain2_Gain_c * f14tmp25_B.Wgustmodel_n;

  /* TransferFcn: '<S38>/Q-gust model' */
  f14tmp25_B.Qgustmodel_a = f14tmp25_P.Qgustmodel_D_n*f14tmp25_B.Wgustmodel_n;
  f14tmp25_B.Qgustmodel_a += f14tmp25_P.Qgustmodel_C_e*
    f14tmp25_X.Qgustmodel_CSTATE_i;

  /* Gain: '<S3>/Gain1' */
  f14tmp25_B.Gain1_c5 = f14tmp25_P.Gain1_Gain_d * f14tmp25_B.Qgustmodel_a;

  /* Sum: '<S3>/Sum' */
  f14tmp25_B.Sum_ec = f14tmp25_B.Gain2_d + f14tmp25_B.Gain1_c5;

  /* Sum: '<S36>/Sum2' */
  f14tmp25_B.Sum2_i = (f14tmp25_B.Gain4_h - f14tmp25_B.Sum_ec) +
    f14tmp25_B.Gain6_l;

  /* TransferFcn: '<S37>/Alpha-sensor Low-pass Filter' */
  f14tmp25_B.AlphasensorLowpassFilter_m =
    f14tmp25_P.AlphasensorLowpassFilter_C_c*
    f14tmp25_X.AlphasensorLowpassFilter_CSTA_e;

  /* TransferFcn: '<S37>/Stick Prefilter' */
  f14tmp25_B.StickPrefilter_j = f14tmp25_P.StickPrefilter_C_f*
    f14tmp25_X.StickPrefilter_CSTATE_ak;

  /* TransferFcn: '<S37>/Pitch Rate Lead Filter' */
  f14tmp25_B.PitchRateLeadFilter_b = f14tmp25_P.PitchRateLeadFilter_D_i*
    f14tmp25_B.TransferFcn1_b;
  f14tmp25_B.PitchRateLeadFilter_b += f14tmp25_P.PitchRateLeadFilter_C_b*
    f14tmp25_X.PitchRateLeadFilter_CSTATE_m;

  /* Gain: '<S37>/Gain2' */
  f14tmp25_B.Gain2_i = f14tmp25_P.Gain2_Gain_d *
    f14tmp25_B.PitchRateLeadFilter_b;

  /* Gain: '<S37>/Gain3' */
  f14tmp25_B.Gain3_p = f14tmp25_P.Gain3_Gain_a *
    f14tmp25_B.AlphasensorLowpassFilter_m;

  /* Sum: '<S37>/Sum1' */
  f14tmp25_B.Sum1_nd = f14tmp25_B.Gain2_i + f14tmp25_B.Gain3_p;

  /* Sum: '<S37>/Sum2' */
  f14tmp25_B.Sum2_j = f14tmp25_B.StickPrefilter_j - f14tmp25_B.Sum1_nd;

  /* Gain: '<S37>/Gain' */
  f14tmp25_B.Gain_l = f14tmp25_P.Gain_Gain_j * f14tmp25_B.Sum2_j;

  /* TransferFcn: '<S37>/Proportional plus integral compensator' */
  f14tmp25_B.Proportionalplusintegralcompe_i =
    f14tmp25_P.Proportionalplusintegralcomp_kq*
    f14tmp25_X.Proportionalplusintegralcompe_f;

  /* Sum: '<S37>/Sum' */
  f14tmp25_B.Sum_k = f14tmp25_B.Gain_l +
    f14tmp25_B.Proportionalplusintegralcompe_i;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* RandomNumber: '<S40>/White Noise' */
    f14tmp25_B.WhiteNoise_g = f14tmp25_DWork.NextOutput_n;

    /* Gain: '<S40>/Output' */
    f14tmp25_B.Output_o = f14tmp25_P.Output_Gain_m * f14tmp25_B.WhiteNoise_g;
  }

  /* TransferFcn: '<S41>/Transfer Fcn.2' */
  f14tmp25_B.TransferFcn2_e = f14tmp25_P.TransferFcn2_C_g*
    f14tmp25_X.TransferFcn2_CSTATE_h0;

  /* Gain: '<S4>/Gain5' */
  f14tmp25_B.Gain5_bk = f14tmp25_P.Gain5_Gain_p * f14tmp25_B.TransferFcn2_e;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* Derivative: '<S44>/Derivative' */
  {
    real_T t = f14tmp25_rtM->Timing.t[0];
    real_T timeStampA = f14tmp25_DWork.Derivative_RWORK_c.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative_RWORK_c.TimeStampB;
    real_T *lastU = &f14tmp25_DWork.Derivative_RWORK_c.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp25_B.Derivative_b = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp25_DWork.Derivative_RWORK_c.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_c.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp25_B.Derivative_b = (f14tmp25_B.TransferFcn2_e - *lastU++) / deltaT;
    }
  }

  /* TransferFcn: '<S41>/Transfer Fcn.1' */
  f14tmp25_B.TransferFcn1_o = f14tmp25_P.TransferFcn1_C_mz*
    f14tmp25_X.TransferFcn1_CSTATE_h;

  /* Derivative: '<S44>/Derivative1' */
  {
    real_T t = f14tmp25_rtM->Timing.t[0];
    real_T timeStampA = f14tmp25_DWork.Derivative1_RWORK_d.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative1_RWORK_d.TimeStampB;
    real_T *lastU = &f14tmp25_DWork.Derivative1_RWORK_d.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp25_B.Derivative1_l = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp25_DWork.Derivative1_RWORK_d.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_d.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp25_B.Derivative1_l = (f14tmp25_B.TransferFcn1_o - *lastU++) / deltaT;
    }
  }

  /* Gain: '<S44>/Gain1' */
  f14tmp25_B.Gain1_g = f14tmp25_P.Gain1_Gain_pr * f14tmp25_B.Derivative1_l;

  /* Product: '<S44>/Product' incorporates:
   *  Constant: '<S44>/Constant'
   */
  f14tmp25_B.Product_g = f14tmp25_B.TransferFcn1_o *
    f14tmp25_P.Constant_Value_fk;

  /* Sum: '<S44>/Sum1' */
  f14tmp25_B.Sum1_f = (f14tmp25_B.Gain1_g - f14tmp25_B.Derivative_b) +
    f14tmp25_B.Product_g;

  /* Gain: '<S44>/Gain2' */
  f14tmp25_B.Gain2_i5 = f14tmp25_P.Gain2_Gain_n * f14tmp25_B.Sum1_f;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* SignalGenerator: '<S4>/Pilot' */
  temp = f14tmp25_P.Pilot_Frequency_i * f14tmp25_rtM->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    f14tmp25_B.Pilot_a = f14tmp25_P.Pilot_Amplitude_j;
  } else {
    f14tmp25_B.Pilot_a = -f14tmp25_P.Pilot_Amplitude_j;
  }

  /* End of SignalGenerator: '<S4>/Pilot' */

  /* Sum: '<S4>/Sum1' */
  f14tmp25_B.Sum1_m = f14tmp25_B.Pilot_a + 0.0;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* TransferFcn: '<S4>/Actuator Model' */
  f14tmp25_B.ActuatorModel_d = f14tmp25_P.ActuatorModel_C_ft*
    f14tmp25_X.ActuatorModel_CSTATE_h;

  /* Gain: '<S41>/Gain3' */
  f14tmp25_B.Gain3_i = f14tmp25_P.Gain3_Gain_p * f14tmp25_B.TransferFcn1_o;

  /* Gain: '<S41>/Gain4' */
  f14tmp25_B.Gain4_pj = f14tmp25_P.Gain4_Gain_p * f14tmp25_B.TransferFcn2_e;

  /* Gain: '<S41>/Gain5' */
  f14tmp25_B.Gain5_j = f14tmp25_P.Gain5_Gain_f * f14tmp25_B.ActuatorModel_d;

  /* Gain: '<S41>/Gain6' */
  f14tmp25_B.Gain6_j = f14tmp25_P.Gain6_Gain_a * f14tmp25_B.ActuatorModel_d;

  /* TransferFcn: '<S43>/W-gust model' */
  f14tmp25_B.Wgustmodel_f = f14tmp25_P.Wgustmodel_C_d[0]*
    f14tmp25_X.Wgustmodel_CSTATE_g[0]
    + f14tmp25_P.Wgustmodel_C_d[1]*f14tmp25_X.Wgustmodel_CSTATE_g[1];

  /* Gain: '<S4>/Gain' */
  f14tmp25_B.Gain_g = f14tmp25_P.Gain_Gain_i * f14tmp25_B.Wgustmodel_f;

  /* Sum: '<S41>/Sum1' */
  f14tmp25_B.Sum1_b = (f14tmp25_B.Gain5_j - f14tmp25_B.Gain_g) +
    f14tmp25_B.Gain3_i;

  /* Gain: '<S4>/Gain2' */
  f14tmp25_B.Gain2_h = f14tmp25_P.Gain2_Gain_cm * f14tmp25_B.Wgustmodel_f;

  /* TransferFcn: '<S43>/Q-gust model' */
  f14tmp25_B.Qgustmodel_o = f14tmp25_P.Qgustmodel_D_d*f14tmp25_B.Wgustmodel_f;
  f14tmp25_B.Qgustmodel_o += f14tmp25_P.Qgustmodel_C_j*
    f14tmp25_X.Qgustmodel_CSTATE_p;

  /* Gain: '<S4>/Gain1' */
  f14tmp25_B.Gain1_gb = f14tmp25_P.Gain1_Gain_j * f14tmp25_B.Qgustmodel_o;

  /* Sum: '<S4>/Sum' */
  f14tmp25_B.Sum_d = f14tmp25_B.Gain2_h + f14tmp25_B.Gain1_gb;

  /* Sum: '<S41>/Sum2' */
  f14tmp25_B.Sum2_p = (f14tmp25_B.Gain4_pj - f14tmp25_B.Sum_d) +
    f14tmp25_B.Gain6_j;

  /* TransferFcn: '<S42>/Alpha-sensor Low-pass Filter' */
  f14tmp25_B.AlphasensorLowpassFilter_k =
    f14tmp25_P.AlphasensorLowpassFilter_C_d*
    f14tmp25_X.AlphasensorLowpassFilter_CSTA_j;

  /* TransferFcn: '<S42>/Stick Prefilter' */
  f14tmp25_B.StickPrefilter_d = f14tmp25_P.StickPrefilter_C_m*
    f14tmp25_X.StickPrefilter_CSTATE_i;

  /* TransferFcn: '<S42>/Pitch Rate Lead Filter' */
  f14tmp25_B.PitchRateLeadFilter_e = f14tmp25_P.PitchRateLeadFilter_D_j*
    f14tmp25_B.TransferFcn1_o;
  f14tmp25_B.PitchRateLeadFilter_e += f14tmp25_P.PitchRateLeadFilter_C_n*
    f14tmp25_X.PitchRateLeadFilter_CSTATE_c;

  /* Gain: '<S42>/Gain2' */
  f14tmp25_B.Gain2_ih = f14tmp25_P.Gain2_Gain_hu *
    f14tmp25_B.PitchRateLeadFilter_e;

  /* Gain: '<S42>/Gain3' */
  f14tmp25_B.Gain3_b = f14tmp25_P.Gain3_Gain_g *
    f14tmp25_B.AlphasensorLowpassFilter_k;

  /* Sum: '<S42>/Sum1' */
  f14tmp25_B.Sum1_g = f14tmp25_B.Gain2_ih + f14tmp25_B.Gain3_b;

  /* Sum: '<S42>/Sum2' */
  f14tmp25_B.Sum2_b = f14tmp25_B.StickPrefilter_d - f14tmp25_B.Sum1_g;

  /* Gain: '<S42>/Gain' */
  f14tmp25_B.Gain_h = f14tmp25_P.Gain_Gain_m * f14tmp25_B.Sum2_b;

  /* TransferFcn: '<S42>/Proportional plus integral compensator' */
  f14tmp25_B.Proportionalplusintegralcompe_c =
    f14tmp25_P.Proportionalplusintegralcompe_n*
    f14tmp25_X.Proportionalplusintegralcompe_g;

  /* Sum: '<S42>/Sum' */
  f14tmp25_B.Sum_nw = f14tmp25_B.Gain_h +
    f14tmp25_B.Proportionalplusintegralcompe_c;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* RandomNumber: '<S45>/White Noise' */
    f14tmp25_B.WhiteNoise_d = f14tmp25_DWork.NextOutput_g;

    /* Gain: '<S45>/Output' */
    f14tmp25_B.Output_g = f14tmp25_P.Output_Gain_c * f14tmp25_B.WhiteNoise_d;
  }

  /* TransferFcn: '<S46>/Transfer Fcn.2' */
  f14tmp25_B.TransferFcn2_en = f14tmp25_P.TransferFcn2_C_l*
    f14tmp25_X.TransferFcn2_CSTATE_m;

  /* Gain: '<S5>/Gain5' */
  f14tmp25_B.Gain5_hk = f14tmp25_P.Gain5_Gain_n * f14tmp25_B.TransferFcn2_en;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* Derivative: '<S49>/Derivative' */
  {
    real_T t = f14tmp25_rtM->Timing.t[0];
    real_T timeStampA = f14tmp25_DWork.Derivative_RWORK_j.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative_RWORK_j.TimeStampB;
    real_T *lastU = &f14tmp25_DWork.Derivative_RWORK_j.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp25_B.Derivative_j = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp25_DWork.Derivative_RWORK_j.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_j.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp25_B.Derivative_j = (f14tmp25_B.TransferFcn2_en - *lastU++) / deltaT;
    }
  }

  /* TransferFcn: '<S46>/Transfer Fcn.1' */
  f14tmp25_B.TransferFcn1_c = f14tmp25_P.TransferFcn1_C_gz*
    f14tmp25_X.TransferFcn1_CSTATE_i;

  /* Derivative: '<S49>/Derivative1' */
  {
    real_T t = f14tmp25_rtM->Timing.t[0];
    real_T timeStampA = f14tmp25_DWork.Derivative1_RWORK_e.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative1_RWORK_e.TimeStampB;
    real_T *lastU = &f14tmp25_DWork.Derivative1_RWORK_e.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp25_B.Derivative1_p = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp25_DWork.Derivative1_RWORK_e.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_e.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp25_B.Derivative1_p = (f14tmp25_B.TransferFcn1_c - *lastU++) / deltaT;
    }
  }

  /* Gain: '<S49>/Gain1' */
  f14tmp25_B.Gain1_ax = f14tmp25_P.Gain1_Gain_m3 * f14tmp25_B.Derivative1_p;

  /* Product: '<S49>/Product' incorporates:
   *  Constant: '<S49>/Constant'
   */
  f14tmp25_B.Product_h = f14tmp25_B.TransferFcn1_c * f14tmp25_P.Constant_Value_i;

  /* Sum: '<S49>/Sum1' */
  f14tmp25_B.Sum1_fy = (f14tmp25_B.Gain1_ax - f14tmp25_B.Derivative_j) +
    f14tmp25_B.Product_h;

  /* Gain: '<S49>/Gain2' */
  f14tmp25_B.Gain2_in = f14tmp25_P.Gain2_Gain_m * f14tmp25_B.Sum1_fy;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* SignalGenerator: '<S5>/Pilot' */
  temp = f14tmp25_P.Pilot_Frequency_b * f14tmp25_rtM->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    f14tmp25_B.Pilot_l = f14tmp25_P.Pilot_Amplitude_nq;
  } else {
    f14tmp25_B.Pilot_l = -f14tmp25_P.Pilot_Amplitude_nq;
  }

  /* End of SignalGenerator: '<S5>/Pilot' */

  /* Sum: '<S5>/Sum1' */
  f14tmp25_B.Sum1_k2 = f14tmp25_B.Pilot_l + 0.0;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* TransferFcn: '<S5>/Actuator Model' */
  f14tmp25_B.ActuatorModel_j = f14tmp25_P.ActuatorModel_C_da*
    f14tmp25_X.ActuatorModel_CSTATE_f;

  /* Gain: '<S46>/Gain3' */
  f14tmp25_B.Gain3_h = f14tmp25_P.Gain3_Gain_e * f14tmp25_B.TransferFcn1_c;

  /* Gain: '<S46>/Gain4' */
  f14tmp25_B.Gain4_f = f14tmp25_P.Gain4_Gain_i * f14tmp25_B.TransferFcn2_en;

  /* Gain: '<S46>/Gain5' */
  f14tmp25_B.Gain5_br = f14tmp25_P.Gain5_Gain_m * f14tmp25_B.ActuatorModel_j;

  /* Gain: '<S46>/Gain6' */
  f14tmp25_B.Gain6_a = f14tmp25_P.Gain6_Gain_n * f14tmp25_B.ActuatorModel_j;

  /* TransferFcn: '<S48>/W-gust model' */
  f14tmp25_B.Wgustmodel_c = f14tmp25_P.Wgustmodel_C_eb[0]*
    f14tmp25_X.Wgustmodel_CSTATE_a[0]
    + f14tmp25_P.Wgustmodel_C_eb[1]*f14tmp25_X.Wgustmodel_CSTATE_a[1];

  /* Gain: '<S5>/Gain' */
  f14tmp25_B.Gain_o = f14tmp25_P.Gain_Gain_o * f14tmp25_B.Wgustmodel_c;

  /* Sum: '<S46>/Sum1' */
  f14tmp25_B.Sum1_ez = (f14tmp25_B.Gain5_br - f14tmp25_B.Gain_o) +
    f14tmp25_B.Gain3_h;

  /* Gain: '<S5>/Gain2' */
  f14tmp25_B.Gain2_is = f14tmp25_P.Gain2_Gain_ck * f14tmp25_B.Wgustmodel_c;

  /* TransferFcn: '<S48>/Q-gust model' */
  f14tmp25_B.Qgustmodel_m = f14tmp25_P.Qgustmodel_D_p*f14tmp25_B.Wgustmodel_c;
  f14tmp25_B.Qgustmodel_m += f14tmp25_P.Qgustmodel_C_f*
    f14tmp25_X.Qgustmodel_CSTATE_h;

  /* Gain: '<S5>/Gain1' */
  f14tmp25_B.Gain1_b = f14tmp25_P.Gain1_Gain_o * f14tmp25_B.Qgustmodel_m;

  /* Sum: '<S5>/Sum' */
  f14tmp25_B.Sum_m = f14tmp25_B.Gain2_is + f14tmp25_B.Gain1_b;

  /* Sum: '<S46>/Sum2' */
  f14tmp25_B.Sum2_e = (f14tmp25_B.Gain4_f - f14tmp25_B.Sum_m) +
    f14tmp25_B.Gain6_a;

  /* TransferFcn: '<S47>/Alpha-sensor Low-pass Filter' */
  f14tmp25_B.AlphasensorLowpassFilter_j =
    f14tmp25_P.AlphasensorLowpassFilter_C_n*
    f14tmp25_X.AlphasensorLowpassFilter_CSTA_c;

  /* TransferFcn: '<S47>/Stick Prefilter' */
  f14tmp25_B.StickPrefilter_jd = f14tmp25_P.StickPrefilter_C_fv*
    f14tmp25_X.StickPrefilter_CSTATE_h;

  /* TransferFcn: '<S47>/Pitch Rate Lead Filter' */
  f14tmp25_B.PitchRateLeadFilter_k = f14tmp25_P.PitchRateLeadFilter_D_c*
    f14tmp25_B.TransferFcn1_c;
  f14tmp25_B.PitchRateLeadFilter_k += f14tmp25_P.PitchRateLeadFilter_C_k*
    f14tmp25_X.PitchRateLeadFilter_CSTATE_l;

  /* Gain: '<S47>/Gain2' */
  f14tmp25_B.Gain2_dg = f14tmp25_P.Gain2_Gain_hw *
    f14tmp25_B.PitchRateLeadFilter_k;

  /* Gain: '<S47>/Gain3' */
  f14tmp25_B.Gain3_h5 = f14tmp25_P.Gain3_Gain_c *
    f14tmp25_B.AlphasensorLowpassFilter_j;

  /* Sum: '<S47>/Sum1' */
  f14tmp25_B.Sum1_l = f14tmp25_B.Gain2_dg + f14tmp25_B.Gain3_h5;

  /* Sum: '<S47>/Sum2' */
  f14tmp25_B.Sum2_m = f14tmp25_B.StickPrefilter_jd - f14tmp25_B.Sum1_l;

  /* Gain: '<S47>/Gain' */
  f14tmp25_B.Gain_do = f14tmp25_P.Gain_Gain_m0 * f14tmp25_B.Sum2_m;

  /* TransferFcn: '<S47>/Proportional plus integral compensator' */
  f14tmp25_B.Proportionalplusintegralcompe_n =
    f14tmp25_P.Proportionalplusintegralcomp_nt*
    f14tmp25_X.Proportionalplusintegralcomp_gl;

  /* Sum: '<S47>/Sum' */
  f14tmp25_B.Sum_h = f14tmp25_B.Gain_do +
    f14tmp25_B.Proportionalplusintegralcompe_n;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* RandomNumber: '<S50>/White Noise' */
    f14tmp25_B.WhiteNoise_e = f14tmp25_DWork.NextOutput_h;

    /* Gain: '<S50>/Output' */
    f14tmp25_B.Output_a = f14tmp25_P.Output_Gain_k * f14tmp25_B.WhiteNoise_e;
  }

  /* TransferFcn: '<S51>/Transfer Fcn.2' */
  f14tmp25_B.TransferFcn2_eu = f14tmp25_P.TransferFcn2_C_i*
    f14tmp25_X.TransferFcn2_CSTATE_p;

  /* Gain: '<S6>/Gain5' */
  f14tmp25_B.Gain5_n = f14tmp25_P.Gain5_Gain_b * f14tmp25_B.TransferFcn2_eu;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* Derivative: '<S54>/Derivative' */
  {
    real_T t = f14tmp25_rtM->Timing.t[0];
    real_T timeStampA = f14tmp25_DWork.Derivative_RWORK_h.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative_RWORK_h.TimeStampB;
    real_T *lastU = &f14tmp25_DWork.Derivative_RWORK_h.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp25_B.Derivative_j5 = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp25_DWork.Derivative_RWORK_h.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_h.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp25_B.Derivative_j5 = (f14tmp25_B.TransferFcn2_eu - *lastU++) /
        deltaT;
    }
  }

  /* TransferFcn: '<S51>/Transfer Fcn.1' */
  f14tmp25_B.TransferFcn1_os = f14tmp25_P.TransferFcn1_C_g3*
    f14tmp25_X.TransferFcn1_CSTATE_n;

  /* Derivative: '<S54>/Derivative1' */
  {
    real_T t = f14tmp25_rtM->Timing.t[0];
    real_T timeStampA = f14tmp25_DWork.Derivative1_RWORK_p.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative1_RWORK_p.TimeStampB;
    real_T *lastU = &f14tmp25_DWork.Derivative1_RWORK_p.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp25_B.Derivative1_o = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp25_DWork.Derivative1_RWORK_p.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_p.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp25_B.Derivative1_o = (f14tmp25_B.TransferFcn1_os - *lastU++) /
        deltaT;
    }
  }

  /* Gain: '<S54>/Gain1' */
  f14tmp25_B.Gain1_j = f14tmp25_P.Gain1_Gain_e * f14tmp25_B.Derivative1_o;

  /* Product: '<S54>/Product' incorporates:
   *  Constant: '<S54>/Constant'
   */
  f14tmp25_B.Product_m = f14tmp25_B.TransferFcn1_os *
    f14tmp25_P.Constant_Value_h;

  /* Sum: '<S54>/Sum1' */
  f14tmp25_B.Sum1_gd = (f14tmp25_B.Gain1_j - f14tmp25_B.Derivative_j5) +
    f14tmp25_B.Product_m;

  /* Gain: '<S54>/Gain2' */
  f14tmp25_B.Gain2_jz = f14tmp25_P.Gain2_Gain_f * f14tmp25_B.Sum1_gd;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* SignalGenerator: '<S6>/Pilot' */
  temp = f14tmp25_P.Pilot_Frequency_i2 * f14tmp25_rtM->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    f14tmp25_B.Pilot_b = f14tmp25_P.Pilot_Amplitude_d;
  } else {
    f14tmp25_B.Pilot_b = -f14tmp25_P.Pilot_Amplitude_d;
  }

  /* End of SignalGenerator: '<S6>/Pilot' */

  /* Sum: '<S6>/Sum1' */
  f14tmp25_B.Sum1_kq = f14tmp25_B.Pilot_b + 0.0;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* TransferFcn: '<S6>/Actuator Model' */
  f14tmp25_B.ActuatorModel_f = f14tmp25_P.ActuatorModel_C_b*
    f14tmp25_X.ActuatorModel_CSTATE_aw;

  /* Gain: '<S51>/Gain3' */
  f14tmp25_B.Gain3_ho = f14tmp25_P.Gain3_Gain_j * f14tmp25_B.TransferFcn1_os;

  /* Gain: '<S51>/Gain4' */
  f14tmp25_B.Gain4_k = f14tmp25_P.Gain4_Gain_c * f14tmp25_B.TransferFcn2_eu;

  /* Gain: '<S51>/Gain5' */
  f14tmp25_B.Gain5_p = f14tmp25_P.Gain5_Gain_h * f14tmp25_B.ActuatorModel_f;

  /* Gain: '<S51>/Gain6' */
  f14tmp25_B.Gain6_j0 = f14tmp25_P.Gain6_Gain_a2 * f14tmp25_B.ActuatorModel_f;

  /* TransferFcn: '<S53>/W-gust model' */
  f14tmp25_B.Wgustmodel_nc = f14tmp25_P.Wgustmodel_C_c[0]*
    f14tmp25_X.Wgustmodel_CSTATE_j[0]
    + f14tmp25_P.Wgustmodel_C_c[1]*f14tmp25_X.Wgustmodel_CSTATE_j[1];

  /* Gain: '<S6>/Gain' */
  f14tmp25_B.Gain_f = f14tmp25_P.Gain_Gain_m1 * f14tmp25_B.Wgustmodel_nc;

  /* Sum: '<S51>/Sum1' */
  f14tmp25_B.Sum1_bx = (f14tmp25_B.Gain5_p - f14tmp25_B.Gain_f) +
    f14tmp25_B.Gain3_ho;

  /* Gain: '<S6>/Gain2' */
  f14tmp25_B.Gain2_fb = f14tmp25_P.Gain2_Gain_a * f14tmp25_B.Wgustmodel_nc;

  /* TransferFcn: '<S53>/Q-gust model' */
  f14tmp25_B.Qgustmodel_i = f14tmp25_P.Qgustmodel_D_nw*f14tmp25_B.Wgustmodel_nc;
  f14tmp25_B.Qgustmodel_i += f14tmp25_P.Qgustmodel_C_k*
    f14tmp25_X.Qgustmodel_CSTATE_pw;

  /* Gain: '<S6>/Gain1' */
  f14tmp25_B.Gain1_j5 = f14tmp25_P.Gain1_Gain_nf * f14tmp25_B.Qgustmodel_i;

  /* Sum: '<S6>/Sum' */
  f14tmp25_B.Sum_b = f14tmp25_B.Gain2_fb + f14tmp25_B.Gain1_j5;

  /* Sum: '<S51>/Sum2' */
  f14tmp25_B.Sum2_o = (f14tmp25_B.Gain4_k - f14tmp25_B.Sum_b) +
    f14tmp25_B.Gain6_j0;

  /* TransferFcn: '<S52>/Alpha-sensor Low-pass Filter' */
  f14tmp25_B.AlphasensorLowpassFilter_f =
    f14tmp25_P.AlphasensorLowpassFilter_C_e*
    f14tmp25_X.AlphasensorLowpassFilter_CST_j4;

  /* TransferFcn: '<S52>/Stick Prefilter' */
  f14tmp25_B.StickPrefilter_f = f14tmp25_P.StickPrefilter_C_fd*
    f14tmp25_X.StickPrefilter_CSTATE_p;

  /* TransferFcn: '<S52>/Pitch Rate Lead Filter' */
  f14tmp25_B.PitchRateLeadFilter_i = f14tmp25_P.PitchRateLeadFilter_D_o*
    f14tmp25_B.TransferFcn1_os;
  f14tmp25_B.PitchRateLeadFilter_i += f14tmp25_P.PitchRateLeadFilter_C_e*
    f14tmp25_X.PitchRateLeadFilter_CSTATE_c5;

  /* Gain: '<S52>/Gain2' */
  f14tmp25_B.Gain2_el = f14tmp25_P.Gain2_Gain_g *
    f14tmp25_B.PitchRateLeadFilter_i;

  /* Gain: '<S52>/Gain3' */
  f14tmp25_B.Gain3_kr = f14tmp25_P.Gain3_Gain_j4 *
    f14tmp25_B.AlphasensorLowpassFilter_f;

  /* Sum: '<S52>/Sum1' */
  f14tmp25_B.Sum1_hc = f14tmp25_B.Gain2_el + f14tmp25_B.Gain3_kr;

  /* Sum: '<S52>/Sum2' */
  f14tmp25_B.Sum2_g = f14tmp25_B.StickPrefilter_f - f14tmp25_B.Sum1_hc;

  /* Gain: '<S52>/Gain' */
  f14tmp25_B.Gain_nh = f14tmp25_P.Gain_Gain_h * f14tmp25_B.Sum2_g;

  /* TransferFcn: '<S52>/Proportional plus integral compensator' */
  f14tmp25_B.Proportionalplusintegralcompe_m =
    f14tmp25_P.Proportionalplusintegralcomp_il*
    f14tmp25_X.Proportionalplusintegralcompe_l;

  /* Sum: '<S52>/Sum' */
  f14tmp25_B.Sum_p = f14tmp25_B.Gain_nh +
    f14tmp25_B.Proportionalplusintegralcompe_m;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* RandomNumber: '<S55>/White Noise' */
    f14tmp25_B.WhiteNoise_c = f14tmp25_DWork.NextOutput_c;

    /* Gain: '<S55>/Output' */
    f14tmp25_B.Output_h = f14tmp25_P.Output_Gain_lv * f14tmp25_B.WhiteNoise_c;
  }

  /* TransferFcn: '<S56>/Transfer Fcn.2' */
  f14tmp25_B.TransferFcn2_be = f14tmp25_P.TransferFcn2_C_j*
    f14tmp25_X.TransferFcn2_CSTATE_n;

  /* Gain: '<S7>/Gain5' */
  f14tmp25_B.Gain5_nt = f14tmp25_P.Gain5_Gain_c * f14tmp25_B.TransferFcn2_be;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* Derivative: '<S59>/Derivative' */
  {
    real_T t = f14tmp25_rtM->Timing.t[0];
    real_T timeStampA = f14tmp25_DWork.Derivative_RWORK_hr.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative_RWORK_hr.TimeStampB;
    real_T *lastU = &f14tmp25_DWork.Derivative_RWORK_hr.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp25_B.Derivative_i = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp25_DWork.Derivative_RWORK_hr.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_hr.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp25_B.Derivative_i = (f14tmp25_B.TransferFcn2_be - *lastU++) / deltaT;
    }
  }

  /* TransferFcn: '<S56>/Transfer Fcn.1' */
  f14tmp25_B.TransferFcn1_n = f14tmp25_P.TransferFcn1_C_n*
    f14tmp25_X.TransferFcn1_CSTATE_b;

  /* Derivative: '<S59>/Derivative1' */
  {
    real_T t = f14tmp25_rtM->Timing.t[0];
    real_T timeStampA = f14tmp25_DWork.Derivative1_RWORK_cz.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative1_RWORK_cz.TimeStampB;
    real_T *lastU = &f14tmp25_DWork.Derivative1_RWORK_cz.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp25_B.Derivative1_e2 = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp25_DWork.Derivative1_RWORK_cz.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_cz.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp25_B.Derivative1_e2 = (f14tmp25_B.TransferFcn1_n - *lastU++) /
        deltaT;
    }
  }

  /* Gain: '<S59>/Gain1' */
  f14tmp25_B.Gain1_k = f14tmp25_P.Gain1_Gain_g * f14tmp25_B.Derivative1_e2;

  /* Product: '<S59>/Product' incorporates:
   *  Constant: '<S59>/Constant'
   */
  f14tmp25_B.Product_n = f14tmp25_B.TransferFcn1_n *
    f14tmp25_P.Constant_Value_hc;

  /* Sum: '<S59>/Sum1' */
  f14tmp25_B.Sum1_mt = (f14tmp25_B.Gain1_k - f14tmp25_B.Derivative_i) +
    f14tmp25_B.Product_n;

  /* Gain: '<S59>/Gain2' */
  f14tmp25_B.Gain2_h5 = f14tmp25_P.Gain2_Gain_b * f14tmp25_B.Sum1_mt;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* SignalGenerator: '<S7>/Pilot' */
  temp = f14tmp25_P.Pilot_Frequency_bf * f14tmp25_rtM->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    f14tmp25_B.Pilot_c = f14tmp25_P.Pilot_Amplitude_j5;
  } else {
    f14tmp25_B.Pilot_c = -f14tmp25_P.Pilot_Amplitude_j5;
  }

  /* End of SignalGenerator: '<S7>/Pilot' */

  /* Sum: '<S7>/Sum1' */
  f14tmp25_B.Sum1_gi = f14tmp25_B.Pilot_c + 0.0;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* TransferFcn: '<S7>/Actuator Model' */
  f14tmp25_B.ActuatorModel_ib = f14tmp25_P.ActuatorModel_C_k*
    f14tmp25_X.ActuatorModel_CSTATE_k;

  /* Gain: '<S56>/Gain3' */
  f14tmp25_B.Gain3_c = f14tmp25_P.Gain3_Gain_pa * f14tmp25_B.TransferFcn1_n;

  /* Gain: '<S56>/Gain4' */
  f14tmp25_B.Gain4_d = f14tmp25_P.Gain4_Gain_b * f14tmp25_B.TransferFcn2_be;

  /* Gain: '<S56>/Gain5' */
  f14tmp25_B.Gain5_m = f14tmp25_P.Gain5_Gain_pl * f14tmp25_B.ActuatorModel_ib;

  /* Gain: '<S56>/Gain6' */
  f14tmp25_B.Gain6_d = f14tmp25_P.Gain6_Gain_i * f14tmp25_B.ActuatorModel_ib;

  /* TransferFcn: '<S58>/W-gust model' */
  f14tmp25_B.Wgustmodel_d = f14tmp25_P.Wgustmodel_C_m[0]*
    f14tmp25_X.Wgustmodel_CSTATE_mw[0]
    + f14tmp25_P.Wgustmodel_C_m[1]*f14tmp25_X.Wgustmodel_CSTATE_mw[1];

  /* Gain: '<S7>/Gain' */
  f14tmp25_B.Gain_j = f14tmp25_P.Gain_Gain_b * f14tmp25_B.Wgustmodel_d;

  /* Sum: '<S56>/Sum1' */
  f14tmp25_B.Sum1_bq = (f14tmp25_B.Gain5_m - f14tmp25_B.Gain_j) +
    f14tmp25_B.Gain3_c;

  /* Gain: '<S7>/Gain2' */
  f14tmp25_B.Gain2_m = f14tmp25_P.Gain2_Gain_ej * f14tmp25_B.Wgustmodel_d;

  /* TransferFcn: '<S58>/Q-gust model' */
  f14tmp25_B.Qgustmodel_h = f14tmp25_P.Qgustmodel_D_b*f14tmp25_B.Wgustmodel_d;
  f14tmp25_B.Qgustmodel_h += f14tmp25_P.Qgustmodel_C_n*
    f14tmp25_X.Qgustmodel_CSTATE_l;

  /* Gain: '<S7>/Gain1' */
  f14tmp25_B.Gain1_cj = f14tmp25_P.Gain1_Gain_mf * f14tmp25_B.Qgustmodel_h;

  /* Sum: '<S7>/Sum' */
  f14tmp25_B.Sum_kc = f14tmp25_B.Gain2_m + f14tmp25_B.Gain1_cj;

  /* Sum: '<S56>/Sum2' */
  f14tmp25_B.Sum2_o5 = (f14tmp25_B.Gain4_d - f14tmp25_B.Sum_kc) +
    f14tmp25_B.Gain6_d;

  /* TransferFcn: '<S57>/Alpha-sensor Low-pass Filter' */
  f14tmp25_B.AlphasensorLowpassFilter_e0 =
    f14tmp25_P.AlphasensorLowpassFilter_C_f*
    f14tmp25_X.AlphasensorLowpassFilter_CST_ji;

  /* TransferFcn: '<S57>/Stick Prefilter' */
  f14tmp25_B.StickPrefilter_ha = f14tmp25_P.StickPrefilter_C_j*
    f14tmp25_X.StickPrefilter_CSTATE_d;

  /* TransferFcn: '<S57>/Pitch Rate Lead Filter' */
  f14tmp25_B.PitchRateLeadFilter_a = f14tmp25_P.PitchRateLeadFilter_D_b*
    f14tmp25_B.TransferFcn1_n;
  f14tmp25_B.PitchRateLeadFilter_a += f14tmp25_P.PitchRateLeadFilter_C_ls*
    f14tmp25_X.PitchRateLeadFilter_CSTATE_j;

  /* Gain: '<S57>/Gain2' */
  f14tmp25_B.Gain2_j0 = f14tmp25_P.Gain2_Gain_i *
    f14tmp25_B.PitchRateLeadFilter_a;

  /* Gain: '<S57>/Gain3' */
  f14tmp25_B.Gain3_ab = f14tmp25_P.Gain3_Gain_f *
    f14tmp25_B.AlphasensorLowpassFilter_e0;

  /* Sum: '<S57>/Sum1' */
  f14tmp25_B.Sum1_c = f14tmp25_B.Gain2_j0 + f14tmp25_B.Gain3_ab;

  /* Sum: '<S57>/Sum2' */
  f14tmp25_B.Sum2_kr = f14tmp25_B.StickPrefilter_ha - f14tmp25_B.Sum1_c;

  /* Gain: '<S57>/Gain' */
  f14tmp25_B.Gain_o3 = f14tmp25_P.Gain_Gain_be * f14tmp25_B.Sum2_kr;

  /* TransferFcn: '<S57>/Proportional plus integral compensator' */
  f14tmp25_B.Proportionalplusintegralcomp_ca =
    f14tmp25_P.Proportionalplusintegralcomp_aj*
    f14tmp25_X.Proportionalplusintegralcompe_p;

  /* Sum: '<S57>/Sum' */
  f14tmp25_B.Sum_eg = f14tmp25_B.Gain_o3 +
    f14tmp25_B.Proportionalplusintegralcomp_ca;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* RandomNumber: '<S60>/White Noise' */
    f14tmp25_B.WhiteNoise_m = f14tmp25_DWork.NextOutput_j;

    /* Gain: '<S60>/Output' */
    f14tmp25_B.Output_i = f14tmp25_P.Output_Gain_d * f14tmp25_B.WhiteNoise_m;
  }

  /* TransferFcn: '<S61>/Transfer Fcn.2' */
  f14tmp25_B.TransferFcn2_o = f14tmp25_P.TransferFcn2_C_l3*
    f14tmp25_X.TransferFcn2_CSTATE_o;

  /* Gain: '<S8>/Gain5' */
  f14tmp25_B.Gain5_hw = f14tmp25_P.Gain5_Gain_mp * f14tmp25_B.TransferFcn2_o;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* Derivative: '<S64>/Derivative' */
  {
    real_T t = f14tmp25_rtM->Timing.t[0];
    real_T timeStampA = f14tmp25_DWork.Derivative_RWORK_b.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative_RWORK_b.TimeStampB;
    real_T *lastU = &f14tmp25_DWork.Derivative_RWORK_b.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp25_B.Derivative_l = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp25_DWork.Derivative_RWORK_b.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_b.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp25_B.Derivative_l = (f14tmp25_B.TransferFcn2_o - *lastU++) / deltaT;
    }
  }

  /* TransferFcn: '<S61>/Transfer Fcn.1' */
  f14tmp25_B.TransferFcn1_m = f14tmp25_P.TransferFcn1_C_j*
    f14tmp25_X.TransferFcn1_CSTATE_nw;

  /* Derivative: '<S64>/Derivative1' */
  {
    real_T t = f14tmp25_rtM->Timing.t[0];
    real_T timeStampA = f14tmp25_DWork.Derivative1_RWORK_cb.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative1_RWORK_cb.TimeStampB;
    real_T *lastU = &f14tmp25_DWork.Derivative1_RWORK_cb.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp25_B.Derivative1_c = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp25_DWork.Derivative1_RWORK_cb.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_cb.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp25_B.Derivative1_c = (f14tmp25_B.TransferFcn1_m - *lastU++) / deltaT;
    }
  }

  /* Gain: '<S64>/Gain1' */
  f14tmp25_B.Gain1_as = f14tmp25_P.Gain1_Gain_a * f14tmp25_B.Derivative1_c;

  /* Product: '<S64>/Product' incorporates:
   *  Constant: '<S64>/Constant'
   */
  f14tmp25_B.Product_f = f14tmp25_B.TransferFcn1_m * f14tmp25_P.Constant_Value_g;

  /* Sum: '<S64>/Sum1' */
  f14tmp25_B.Sum1_mo = (f14tmp25_B.Gain1_as - f14tmp25_B.Derivative_l) +
    f14tmp25_B.Product_f;

  /* Gain: '<S64>/Gain2' */
  f14tmp25_B.Gain2_k = f14tmp25_P.Gain2_Gain_b3 * f14tmp25_B.Sum1_mo;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* SignalGenerator: '<S8>/Pilot' */
  temp = f14tmp25_P.Pilot_Frequency_e * f14tmp25_rtM->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    f14tmp25_B.Pilot_g = f14tmp25_P.Pilot_Amplitude_i;
  } else {
    f14tmp25_B.Pilot_g = -f14tmp25_P.Pilot_Amplitude_i;
  }

  /* End of SignalGenerator: '<S8>/Pilot' */

  /* Sum: '<S8>/Sum1' */
  f14tmp25_B.Sum1_m2 = f14tmp25_B.Pilot_g + 0.0;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* TransferFcn: '<S8>/Actuator Model' */
  f14tmp25_B.ActuatorModel_c = f14tmp25_P.ActuatorModel_C_by*
    f14tmp25_X.ActuatorModel_CSTATE_o;

  /* Gain: '<S61>/Gain3' */
  f14tmp25_B.Gain3_e = f14tmp25_P.Gain3_Gain_o * f14tmp25_B.TransferFcn1_m;

  /* Gain: '<S61>/Gain4' */
  f14tmp25_B.Gain4_l = f14tmp25_P.Gain4_Gain_h * f14tmp25_B.TransferFcn2_o;

  /* Gain: '<S61>/Gain5' */
  f14tmp25_B.Gain5_d = f14tmp25_P.Gain5_Gain_jk * f14tmp25_B.ActuatorModel_c;

  /* Gain: '<S61>/Gain6' */
  f14tmp25_B.Gain6_b = f14tmp25_P.Gain6_Gain_c * f14tmp25_B.ActuatorModel_c;

  /* TransferFcn: '<S63>/W-gust model' */
  f14tmp25_B.Wgustmodel_a = f14tmp25_P.Wgustmodel_C_i[0]*
    f14tmp25_X.Wgustmodel_CSTATE_e[0]
    + f14tmp25_P.Wgustmodel_C_i[1]*f14tmp25_X.Wgustmodel_CSTATE_e[1];

  /* Gain: '<S8>/Gain' */
  f14tmp25_B.Gain_ob = f14tmp25_P.Gain_Gain_ka * f14tmp25_B.Wgustmodel_a;

  /* Sum: '<S61>/Sum1' */
  f14tmp25_B.Sum1_fz = (f14tmp25_B.Gain5_d - f14tmp25_B.Gain_ob) +
    f14tmp25_B.Gain3_e;

  /* Gain: '<S8>/Gain2' */
  f14tmp25_B.Gain2_jo = f14tmp25_P.Gain2_Gain_k5j * f14tmp25_B.Wgustmodel_a;

  /* TransferFcn: '<S63>/Q-gust model' */
  f14tmp25_B.Qgustmodel_i1 = f14tmp25_P.Qgustmodel_D_h*f14tmp25_B.Wgustmodel_a;
  f14tmp25_B.Qgustmodel_i1 += f14tmp25_P.Qgustmodel_C_o*
    f14tmp25_X.Qgustmodel_CSTATE_b;

  /* Gain: '<S8>/Gain1' */
  f14tmp25_B.Gain1_p = f14tmp25_P.Gain1_Gain_gg * f14tmp25_B.Qgustmodel_i1;

  /* Sum: '<S8>/Sum' */
  f14tmp25_B.Sum_pj = f14tmp25_B.Gain2_jo + f14tmp25_B.Gain1_p;

  /* Sum: '<S61>/Sum2' */
  f14tmp25_B.Sum2_gl = (f14tmp25_B.Gain4_l - f14tmp25_B.Sum_pj) +
    f14tmp25_B.Gain6_b;

  /* TransferFcn: '<S62>/Alpha-sensor Low-pass Filter' */
  f14tmp25_B.AlphasensorLowpassFilter_o =
    f14tmp25_P.AlphasensorLowpassFilter_C_dk*
    f14tmp25_X.AlphasensorLowpassFilter_CST_ep;

  /* TransferFcn: '<S62>/Stick Prefilter' */
  f14tmp25_B.StickPrefilter_c = f14tmp25_P.StickPrefilter_C_jx*
    f14tmp25_X.StickPrefilter_CSTATE_hs;

  /* TransferFcn: '<S62>/Pitch Rate Lead Filter' */
  f14tmp25_B.PitchRateLeadFilter_g = f14tmp25_P.PitchRateLeadFilter_D_fn*
    f14tmp25_B.TransferFcn1_m;
  f14tmp25_B.PitchRateLeadFilter_g += f14tmp25_P.PitchRateLeadFilter_C_h*
    f14tmp25_X.PitchRateLeadFilter_CSTATE_h;

  /* Gain: '<S62>/Gain2' */
  f14tmp25_B.Gain2_dk = f14tmp25_P.Gain2_Gain_i1 *
    f14tmp25_B.PitchRateLeadFilter_g;

  /* Gain: '<S62>/Gain3' */
  f14tmp25_B.Gain3_kf = f14tmp25_P.Gain3_Gain_jo *
    f14tmp25_B.AlphasensorLowpassFilter_o;

  /* Sum: '<S62>/Sum1' */
  f14tmp25_B.Sum1_em = f14tmp25_B.Gain2_dk + f14tmp25_B.Gain3_kf;

  /* Sum: '<S62>/Sum2' */
  f14tmp25_B.Sum2_c3 = f14tmp25_B.StickPrefilter_c - f14tmp25_B.Sum1_em;

  /* Gain: '<S62>/Gain' */
  f14tmp25_B.Gain_na = f14tmp25_P.Gain_Gain_jp * f14tmp25_B.Sum2_c3;

  /* TransferFcn: '<S62>/Proportional plus integral compensator' */
  f14tmp25_B.Proportionalplusintegralcompe_p =
    f14tmp25_P.Proportionalplusintegralcomp_db*
    f14tmp25_X.Proportionalplusintegralcompe_h;

  /* Sum: '<S62>/Sum' */
  f14tmp25_B.Sum_pi = f14tmp25_B.Gain_na +
    f14tmp25_B.Proportionalplusintegralcompe_p;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* RandomNumber: '<S65>/White Noise' */
    f14tmp25_B.WhiteNoise_k = f14tmp25_DWork.NextOutput_d;

    /* Gain: '<S65>/Output' */
    f14tmp25_B.Output_n = f14tmp25_P.Output_Gain_kp * f14tmp25_B.WhiteNoise_k;
  }

  /* TransferFcn: '<S66>/Transfer Fcn.2' */
  f14tmp25_B.TransferFcn2_d1 = f14tmp25_P.TransferFcn2_C_n*
    f14tmp25_X.TransferFcn2_CSTATE_c;

  /* Gain: '<S9>/Gain5' */
  f14tmp25_B.Gain5_e = f14tmp25_P.Gain5_Gain_oy * f14tmp25_B.TransferFcn2_d1;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* Derivative: '<S69>/Derivative' */
  {
    real_T t = f14tmp25_rtM->Timing.t[0];
    real_T timeStampA = f14tmp25_DWork.Derivative_RWORK_jk.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative_RWORK_jk.TimeStampB;
    real_T *lastU = &f14tmp25_DWork.Derivative_RWORK_jk.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp25_B.Derivative_p = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp25_DWork.Derivative_RWORK_jk.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_jk.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp25_B.Derivative_p = (f14tmp25_B.TransferFcn2_d1 - *lastU++) / deltaT;
    }
  }

  /* TransferFcn: '<S66>/Transfer Fcn.1' */
  f14tmp25_B.TransferFcn1_b1 = f14tmp25_P.TransferFcn1_C_gzf*
    f14tmp25_X.TransferFcn1_CSTATE_bm;

  /* Derivative: '<S69>/Derivative1' */
  {
    real_T t = f14tmp25_rtM->Timing.t[0];
    real_T timeStampA = f14tmp25_DWork.Derivative1_RWORK_ev.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative1_RWORK_ev.TimeStampB;
    real_T *lastU = &f14tmp25_DWork.Derivative1_RWORK_ev.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp25_B.Derivative1_lu = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp25_DWork.Derivative1_RWORK_ev.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_ev.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp25_B.Derivative1_lu = (f14tmp25_B.TransferFcn1_b1 - *lastU++) /
        deltaT;
    }
  }

  /* Gain: '<S69>/Gain1' */
  f14tmp25_B.Gain1_e = f14tmp25_P.Gain1_Gain_m2 * f14tmp25_B.Derivative1_lu;

  /* Product: '<S69>/Product' incorporates:
   *  Constant: '<S69>/Constant'
   */
  f14tmp25_B.Product_p = f14tmp25_B.TransferFcn1_b1 *
    f14tmp25_P.Constant_Value_b;

  /* Sum: '<S69>/Sum1' */
  f14tmp25_B.Sum1_ia = (f14tmp25_B.Gain1_e - f14tmp25_B.Derivative_p) +
    f14tmp25_B.Product_p;

  /* Gain: '<S69>/Gain2' */
  f14tmp25_B.Gain2_dv = f14tmp25_P.Gain2_Gain_d5 * f14tmp25_B.Sum1_ia;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* SignalGenerator: '<S9>/Pilot' */
  temp = f14tmp25_P.Pilot_Frequency_bw * f14tmp25_rtM->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    f14tmp25_B.Pilot_kw = f14tmp25_P.Pilot_Amplitude_o;
  } else {
    f14tmp25_B.Pilot_kw = -f14tmp25_P.Pilot_Amplitude_o;
  }

  /* End of SignalGenerator: '<S9>/Pilot' */

  /* Sum: '<S9>/Sum1' */
  f14tmp25_B.Sum1_ij = f14tmp25_B.Pilot_kw + 0.0;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* TransferFcn: '<S9>/Actuator Model' */
  f14tmp25_B.ActuatorModel_m = f14tmp25_P.ActuatorModel_C_j*
    f14tmp25_X.ActuatorModel_CSTATE_ku;

  /* Gain: '<S66>/Gain3' */
  f14tmp25_B.Gain3_o = f14tmp25_P.Gain3_Gain_d * f14tmp25_B.TransferFcn1_b1;

  /* Gain: '<S66>/Gain4' */
  f14tmp25_B.Gain4_g = f14tmp25_P.Gain4_Gain_l * f14tmp25_B.TransferFcn2_d1;

  /* Gain: '<S66>/Gain5' */
  f14tmp25_B.Gain5_l = f14tmp25_P.Gain5_Gain_l * f14tmp25_B.ActuatorModel_m;

  /* Gain: '<S66>/Gain6' */
  f14tmp25_B.Gain6_n = f14tmp25_P.Gain6_Gain_cd * f14tmp25_B.ActuatorModel_m;

  /* TransferFcn: '<S68>/W-gust model' */
  f14tmp25_B.Wgustmodel_g = f14tmp25_P.Wgustmodel_C_o[0]*
    f14tmp25_X.Wgustmodel_CSTATE_fj[0]
    + f14tmp25_P.Wgustmodel_C_o[1]*f14tmp25_X.Wgustmodel_CSTATE_fj[1];

  /* Gain: '<S9>/Gain' */
  f14tmp25_B.Gain_fj = f14tmp25_P.Gain_Gain_o1 * f14tmp25_B.Wgustmodel_g;

  /* Sum: '<S66>/Sum1' */
  f14tmp25_B.Sum1_fo = (f14tmp25_B.Gain5_l - f14tmp25_B.Gain_fj) +
    f14tmp25_B.Gain3_o;

  /* Gain: '<S9>/Gain2' */
  f14tmp25_B.Gain2_lh = f14tmp25_P.Gain2_Gain_l * f14tmp25_B.Wgustmodel_g;

  /* TransferFcn: '<S68>/Q-gust model' */
  f14tmp25_B.Qgustmodel_mh = f14tmp25_P.Qgustmodel_D_pt*f14tmp25_B.Wgustmodel_g;
  f14tmp25_B.Qgustmodel_mh += f14tmp25_P.Qgustmodel_C_b*
    f14tmp25_X.Qgustmodel_CSTATE_a;

  /* Gain: '<S9>/Gain1' */
  f14tmp25_B.Gain1_kh = f14tmp25_P.Gain1_Gain_i * f14tmp25_B.Qgustmodel_mh;

  /* Sum: '<S9>/Sum' */
  f14tmp25_B.Sum_c = f14tmp25_B.Gain2_lh + f14tmp25_B.Gain1_kh;

  /* Sum: '<S66>/Sum2' */
  f14tmp25_B.Sum2_jr = (f14tmp25_B.Gain4_g - f14tmp25_B.Sum_c) +
    f14tmp25_B.Gain6_n;

  /* TransferFcn: '<S67>/Alpha-sensor Low-pass Filter' */
  f14tmp25_B.AlphasensorLowpassFilter_fj =
    f14tmp25_P.AlphasensorLowpassFilter_C_a*
    f14tmp25_X.AlphasensorLowpassFilter_CST_cd;

  /* TransferFcn: '<S67>/Stick Prefilter' */
  f14tmp25_B.StickPrefilter_l = f14tmp25_P.StickPrefilter_C_h*
    f14tmp25_X.StickPrefilter_CSTATE_f;

  /* TransferFcn: '<S67>/Pitch Rate Lead Filter' */
  f14tmp25_B.PitchRateLeadFilter_em = f14tmp25_P.PitchRateLeadFilter_D_p*
    f14tmp25_B.TransferFcn1_b1;
  f14tmp25_B.PitchRateLeadFilter_em += f14tmp25_P.PitchRateLeadFilter_C_a*
    f14tmp25_X.PitchRateLeadFilter_CSTATE_e;

  /* Gain: '<S67>/Gain2' */
  f14tmp25_B.Gain2_ew = f14tmp25_P.Gain2_Gain_cc *
    f14tmp25_B.PitchRateLeadFilter_em;

  /* Gain: '<S67>/Gain3' */
  f14tmp25_B.Gain3_c3 = f14tmp25_P.Gain3_Gain_ek *
    f14tmp25_B.AlphasensorLowpassFilter_fj;

  /* Sum: '<S67>/Sum1' */
  f14tmp25_B.Sum1_gq = f14tmp25_B.Gain2_ew + f14tmp25_B.Gain3_c3;

  /* Sum: '<S67>/Sum2' */
  f14tmp25_B.Sum2_a = f14tmp25_B.StickPrefilter_l - f14tmp25_B.Sum1_gq;

  /* Gain: '<S67>/Gain' */
  f14tmp25_B.Gain_c = f14tmp25_P.Gain_Gain_me * f14tmp25_B.Sum2_a;

  /* TransferFcn: '<S67>/Proportional plus integral compensator' */
  f14tmp25_B.Proportionalplusintegralcompe_l =
    f14tmp25_P.Proportionalplusintegralcomp_o2*
    f14tmp25_X.Proportionalplusintegralcompe_i;

  /* Sum: '<S67>/Sum' */
  f14tmp25_B.Sum_a = f14tmp25_B.Gain_c +
    f14tmp25_B.Proportionalplusintegralcompe_l;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* RandomNumber: '<S70>/White Noise' */
    f14tmp25_B.WhiteNoise_f = f14tmp25_DWork.NextOutput_l;

    /* Gain: '<S70>/Output' */
    f14tmp25_B.Output_gu = f14tmp25_P.Output_Gain_kt * f14tmp25_B.WhiteNoise_f;
  }

  /* TransferFcn: '<S71>/Transfer Fcn.2' */
  f14tmp25_B.TransferFcn2_n = f14tmp25_P.TransferFcn2_C_iu*
    f14tmp25_X.TransferFcn2_CSTATE_a;

  /* Gain: '<S10>/Gain5' */
  f14tmp25_B.Gain5_nv = f14tmp25_P.Gain5_Gain_m5 * f14tmp25_B.TransferFcn2_n;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* Derivative: '<S74>/Derivative' */
  {
    real_T t = f14tmp25_rtM->Timing.t[0];
    real_T timeStampA = f14tmp25_DWork.Derivative_RWORK_bz.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative_RWORK_bz.TimeStampB;
    real_T *lastU = &f14tmp25_DWork.Derivative_RWORK_bz.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp25_B.Derivative_m = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp25_DWork.Derivative_RWORK_bz.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_bz.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp25_B.Derivative_m = (f14tmp25_B.TransferFcn2_n - *lastU++) / deltaT;
    }
  }

  /* TransferFcn: '<S71>/Transfer Fcn.1' */
  f14tmp25_B.TransferFcn1_g = f14tmp25_P.TransferFcn1_C_i*
    f14tmp25_X.TransferFcn1_CSTATE_m;

  /* Derivative: '<S74>/Derivative1' */
  {
    real_T t = f14tmp25_rtM->Timing.t[0];
    real_T timeStampA = f14tmp25_DWork.Derivative1_RWORK_cd.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative1_RWORK_cd.TimeStampB;
    real_T *lastU = &f14tmp25_DWork.Derivative1_RWORK_cd.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp25_B.Derivative1_n = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp25_DWork.Derivative1_RWORK_cd.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_cd.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp25_B.Derivative1_n = (f14tmp25_B.TransferFcn1_g - *lastU++) / deltaT;
    }
  }

  /* Gain: '<S74>/Gain1' */
  f14tmp25_B.Gain1_bc = f14tmp25_P.Gain1_Gain_l * f14tmp25_B.Derivative1_n;

  /* Product: '<S74>/Product' incorporates:
   *  Constant: '<S74>/Constant'
   */
  f14tmp25_B.Product_i = f14tmp25_B.TransferFcn1_g * f14tmp25_P.Constant_Value_k;

  /* Sum: '<S74>/Sum1' */
  f14tmp25_B.Sum1_is = (f14tmp25_B.Gain1_bc - f14tmp25_B.Derivative_m) +
    f14tmp25_B.Product_i;

  /* Gain: '<S74>/Gain2' */
  f14tmp25_B.Gain2_n = f14tmp25_P.Gain2_Gain_fh * f14tmp25_B.Sum1_is;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* SignalGenerator: '<S10>/Pilot' */
  temp = f14tmp25_P.Pilot_Frequency_ga * f14tmp25_rtM->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    f14tmp25_B.Pilot_mj = f14tmp25_P.Pilot_Amplitude_if;
  } else {
    f14tmp25_B.Pilot_mj = -f14tmp25_P.Pilot_Amplitude_if;
  }

  /* End of SignalGenerator: '<S10>/Pilot' */

  /* Sum: '<S10>/Sum1' */
  f14tmp25_B.Sum1_fov = f14tmp25_B.Pilot_mj + 0.0;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* TransferFcn: '<S10>/Actuator Model' */
  f14tmp25_B.ActuatorModel_e = f14tmp25_P.ActuatorModel_C_jn*
    f14tmp25_X.ActuatorModel_CSTATE_c;

  /* Gain: '<S71>/Gain3' */
  f14tmp25_B.Gain3_oe = f14tmp25_P.Gain3_Gain_ao * f14tmp25_B.TransferFcn1_g;

  /* Gain: '<S71>/Gain4' */
  f14tmp25_B.Gain4_hg = f14tmp25_P.Gain4_Gain_o * f14tmp25_B.TransferFcn2_n;

  /* Gain: '<S71>/Gain5' */
  f14tmp25_B.Gain5_k2 = f14tmp25_P.Gain5_Gain_hj * f14tmp25_B.ActuatorModel_e;

  /* Gain: '<S71>/Gain6' */
  f14tmp25_B.Gain6_jf = f14tmp25_P.Gain6_Gain_p * f14tmp25_B.ActuatorModel_e;

  /* TransferFcn: '<S73>/W-gust model' */
  f14tmp25_B.Wgustmodel_do = f14tmp25_P.Wgustmodel_C_g[0]*
    f14tmp25_X.Wgustmodel_CSTATE_d[0]
    + f14tmp25_P.Wgustmodel_C_g[1]*f14tmp25_X.Wgustmodel_CSTATE_d[1];

  /* Gain: '<S10>/Gain' */
  f14tmp25_B.Gain_cs = f14tmp25_P.Gain_Gain_e * f14tmp25_B.Wgustmodel_do;

  /* Sum: '<S71>/Sum1' */
  f14tmp25_B.Sum1_dq = (f14tmp25_B.Gain5_k2 - f14tmp25_B.Gain_cs) +
    f14tmp25_B.Gain3_oe;

  /* Gain: '<S10>/Gain2' */
  f14tmp25_B.Gain2_ow = f14tmp25_P.Gain2_Gain_nv * f14tmp25_B.Wgustmodel_do;

  /* TransferFcn: '<S73>/Q-gust model' */
  f14tmp25_B.Qgustmodel_b = f14tmp25_P.Qgustmodel_D_ci*f14tmp25_B.Wgustmodel_do;
  f14tmp25_B.Qgustmodel_b += f14tmp25_P.Qgustmodel_C_bg*
    f14tmp25_X.Qgustmodel_CSTATE_o;

  /* Gain: '<S10>/Gain1' */
  f14tmp25_B.Gain1_o = f14tmp25_P.Gain1_Gain_no * f14tmp25_B.Qgustmodel_b;

  /* Sum: '<S10>/Sum' */
  f14tmp25_B.Sum_o = f14tmp25_B.Gain2_ow + f14tmp25_B.Gain1_o;

  /* Sum: '<S71>/Sum2' */
  f14tmp25_B.Sum2_kw = (f14tmp25_B.Gain4_hg - f14tmp25_B.Sum_o) +
    f14tmp25_B.Gain6_jf;

  /* TransferFcn: '<S72>/Alpha-sensor Low-pass Filter' */
  f14tmp25_B.AlphasensorLowpassFilter_c =
    f14tmp25_P.AlphasensorLowpassFilter_C_ee*
    f14tmp25_X.AlphasensorLowpassFilter_CST_ej;

  /* TransferFcn: '<S72>/Stick Prefilter' */
  f14tmp25_B.StickPrefilter_m = f14tmp25_P.StickPrefilter_C_o*
    f14tmp25_X.StickPrefilter_CSTATE_n;

  /* TransferFcn: '<S72>/Pitch Rate Lead Filter' */
  f14tmp25_B.PitchRateLeadFilter_fd = f14tmp25_P.PitchRateLeadFilter_D_cd*
    f14tmp25_B.TransferFcn1_g;
  f14tmp25_B.PitchRateLeadFilter_fd += f14tmp25_P.PitchRateLeadFilter_C_bz*
    f14tmp25_X.PitchRateLeadFilter_CSTATE_e4;

  /* Gain: '<S72>/Gain2' */
  f14tmp25_B.Gain2_b = f14tmp25_P.Gain2_Gain_dg *
    f14tmp25_B.PitchRateLeadFilter_fd;

  /* Gain: '<S72>/Gain3' */
  f14tmp25_B.Gain3_j = f14tmp25_P.Gain3_Gain_m *
    f14tmp25_B.AlphasensorLowpassFilter_c;

  /* Sum: '<S72>/Sum1' */
  f14tmp25_B.Sum1_gp = f14tmp25_B.Gain2_b + f14tmp25_B.Gain3_j;

  /* Sum: '<S72>/Sum2' */
  f14tmp25_B.Sum2_ee = f14tmp25_B.StickPrefilter_m - f14tmp25_B.Sum1_gp;

  /* Gain: '<S72>/Gain' */
  f14tmp25_B.Gain_cm = f14tmp25_P.Gain_Gain_ld * f14tmp25_B.Sum2_ee;

  /* TransferFcn: '<S72>/Proportional plus integral compensator' */
  f14tmp25_B.Proportionalplusintegralcompe_b =
    f14tmp25_P.Proportionalplusintegralcompe_e*
    f14tmp25_X.Proportionalplusintegralcomp_p5;

  /* Sum: '<S72>/Sum' */
  f14tmp25_B.Sum_bx = f14tmp25_B.Gain_cm +
    f14tmp25_B.Proportionalplusintegralcompe_b;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* RandomNumber: '<S75>/White Noise' */
    f14tmp25_B.WhiteNoise_g1 = f14tmp25_DWork.NextOutput_a;

    /* Gain: '<S75>/Output' */
    f14tmp25_B.Output_nn = f14tmp25_P.Output_Gain_e * f14tmp25_B.WhiteNoise_g1;
  }

  /* TransferFcn: '<S76>/Transfer Fcn.2' */
  f14tmp25_B.TransferFcn2_nh = f14tmp25_P.TransferFcn2_C_e*
    f14tmp25_X.TransferFcn2_CSTATE_l;

  /* Gain: '<S11>/Gain5' */
  f14tmp25_B.Gain5_pn = f14tmp25_P.Gain5_Gain_k * f14tmp25_B.TransferFcn2_nh;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* Derivative: '<S79>/Derivative' */
  {
    real_T t = f14tmp25_rtM->Timing.t[0];
    real_T timeStampA = f14tmp25_DWork.Derivative_RWORK_a.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative_RWORK_a.TimeStampB;
    real_T *lastU = &f14tmp25_DWork.Derivative_RWORK_a.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp25_B.Derivative_n = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp25_DWork.Derivative_RWORK_a.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_a.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp25_B.Derivative_n = (f14tmp25_B.TransferFcn2_nh - *lastU++) / deltaT;
    }
  }

  /* TransferFcn: '<S76>/Transfer Fcn.1' */
  f14tmp25_B.TransferFcn1_h = f14tmp25_P.TransferFcn1_C_ir*
    f14tmp25_X.TransferFcn1_CSTATE_iz;

  /* Derivative: '<S79>/Derivative1' */
  {
    real_T t = f14tmp25_rtM->Timing.t[0];
    real_T timeStampA = f14tmp25_DWork.Derivative1_RWORK_i.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative1_RWORK_i.TimeStampB;
    real_T *lastU = &f14tmp25_DWork.Derivative1_RWORK_i.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp25_B.Derivative1_m = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp25_DWork.Derivative1_RWORK_i.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_i.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp25_B.Derivative1_m = (f14tmp25_B.TransferFcn1_h - *lastU++) / deltaT;
    }
  }

  /* Gain: '<S79>/Gain1' */
  f14tmp25_B.Gain1_l = f14tmp25_P.Gain1_Gain_at * f14tmp25_B.Derivative1_m;

  /* Product: '<S79>/Product' incorporates:
   *  Constant: '<S79>/Constant'
   */
  f14tmp25_B.Product_dp = f14tmp25_B.TransferFcn1_h *
    f14tmp25_P.Constant_Value_o;

  /* Sum: '<S79>/Sum1' */
  f14tmp25_B.Sum1_h5 = (f14tmp25_B.Gain1_l - f14tmp25_B.Derivative_n) +
    f14tmp25_B.Product_dp;

  /* Gain: '<S79>/Gain2' */
  f14tmp25_B.Gain2_a = f14tmp25_P.Gain2_Gain_pu * f14tmp25_B.Sum1_h5;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* SignalGenerator: '<S11>/Pilot' */
  temp = f14tmp25_P.Pilot_Frequency_c * f14tmp25_rtM->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    f14tmp25_B.Pilot_e = f14tmp25_P.Pilot_Amplitude_h;
  } else {
    f14tmp25_B.Pilot_e = -f14tmp25_P.Pilot_Amplitude_h;
  }

  /* End of SignalGenerator: '<S11>/Pilot' */

  /* Sum: '<S11>/Sum1' */
  f14tmp25_B.Sum1_jt = f14tmp25_B.Pilot_e + 0.0;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* TransferFcn: '<S11>/Actuator Model' */
  f14tmp25_B.ActuatorModel_k = f14tmp25_P.ActuatorModel_C_m*
    f14tmp25_X.ActuatorModel_CSTATE_hl;

  /* Gain: '<S76>/Gain3' */
  f14tmp25_B.Gain3_d = f14tmp25_P.Gain3_Gain_fb * f14tmp25_B.TransferFcn1_h;

  /* Gain: '<S76>/Gain4' */
  f14tmp25_B.Gain4_g2 = f14tmp25_P.Gain4_Gain_p3 * f14tmp25_B.TransferFcn2_nh;

  /* Gain: '<S76>/Gain5' */
  f14tmp25_B.Gain5_c = f14tmp25_P.Gain5_Gain_e * f14tmp25_B.ActuatorModel_k;

  /* Gain: '<S76>/Gain6' */
  f14tmp25_B.Gain6_p = f14tmp25_P.Gain6_Gain_e * f14tmp25_B.ActuatorModel_k;

  /* TransferFcn: '<S78>/W-gust model' */
  f14tmp25_B.Wgustmodel_nd = f14tmp25_P.Wgustmodel_C_p[0]*
    f14tmp25_X.Wgustmodel_CSTATE_mo[0]
    + f14tmp25_P.Wgustmodel_C_p[1]*f14tmp25_X.Wgustmodel_CSTATE_mo[1];

  /* Gain: '<S11>/Gain' */
  f14tmp25_B.Gain_k = f14tmp25_P.Gain_Gain_lw * f14tmp25_B.Wgustmodel_nd;

  /* Sum: '<S76>/Sum1' */
  f14tmp25_B.Sum1_jj = (f14tmp25_B.Gain5_c - f14tmp25_B.Gain_k) +
    f14tmp25_B.Gain3_d;

  /* Gain: '<S11>/Gain2' */
  f14tmp25_B.Gain2_ml = f14tmp25_P.Gain2_Gain_pn * f14tmp25_B.Wgustmodel_nd;

  /* TransferFcn: '<S78>/Q-gust model' */
  f14tmp25_B.Qgustmodel_l = f14tmp25_P.Qgustmodel_D_o*f14tmp25_B.Wgustmodel_nd;
  f14tmp25_B.Qgustmodel_l += f14tmp25_P.Qgustmodel_C_m*
    f14tmp25_X.Qgustmodel_CSTATE_p3;

  /* Gain: '<S11>/Gain1' */
  f14tmp25_B.Gain1_ap = f14tmp25_P.Gain1_Gain_gy * f14tmp25_B.Qgustmodel_l;

  /* Sum: '<S11>/Sum' */
  f14tmp25_B.Sum_i = f14tmp25_B.Gain2_ml + f14tmp25_B.Gain1_ap;

  /* Sum: '<S76>/Sum2' */
  f14tmp25_B.Sum2_f1 = (f14tmp25_B.Gain4_g2 - f14tmp25_B.Sum_i) +
    f14tmp25_B.Gain6_p;

  /* TransferFcn: '<S77>/Alpha-sensor Low-pass Filter' */
  f14tmp25_B.AlphasensorLowpassFilter_i =
    f14tmp25_P.AlphasensorLowpassFilter_C_fk*
    f14tmp25_X.AlphasensorLowpassFilter_CSTA_i;

  /* TransferFcn: '<S77>/Stick Prefilter' */
  f14tmp25_B.StickPrefilter_hq = f14tmp25_P.StickPrefilter_C_pu*
    f14tmp25_X.StickPrefilter_CSTATE_b;

  /* TransferFcn: '<S77>/Pitch Rate Lead Filter' */
  f14tmp25_B.PitchRateLeadFilter_d = f14tmp25_P.PitchRateLeadFilter_D_h*
    f14tmp25_B.TransferFcn1_h;
  f14tmp25_B.PitchRateLeadFilter_d += f14tmp25_P.PitchRateLeadFilter_C_i*
    f14tmp25_X.PitchRateLeadFilter_CSTATE_d;

  /* Gain: '<S77>/Gain2' */
  f14tmp25_B.Gain2_p = f14tmp25_P.Gain2_Gain_gj *
    f14tmp25_B.PitchRateLeadFilter_d;

  /* Gain: '<S77>/Gain3' */
  f14tmp25_B.Gain3_n = f14tmp25_P.Gain3_Gain_b2 *
    f14tmp25_B.AlphasensorLowpassFilter_i;

  /* Sum: '<S77>/Sum1' */
  f14tmp25_B.Sum1_a = f14tmp25_B.Gain2_p + f14tmp25_B.Gain3_n;

  /* Sum: '<S77>/Sum2' */
  f14tmp25_B.Sum2_mp = f14tmp25_B.StickPrefilter_hq - f14tmp25_B.Sum1_a;

  /* Gain: '<S77>/Gain' */
  f14tmp25_B.Gain_f5 = f14tmp25_P.Gain_Gain_cm * f14tmp25_B.Sum2_mp;

  /* TransferFcn: '<S77>/Proportional plus integral compensator' */
  f14tmp25_B.Proportionalplusintegralcompe_g =
    f14tmp25_P.Proportionalplusintegralcomp_ea*
    f14tmp25_X.Proportionalplusintegralcomp_he;

  /* Sum: '<S77>/Sum' */
  f14tmp25_B.Sum_km = f14tmp25_B.Gain_f5 +
    f14tmp25_B.Proportionalplusintegralcompe_g;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* RandomNumber: '<S80>/White Noise' */
    f14tmp25_B.WhiteNoise_a = f14tmp25_DWork.NextOutput_ag;

    /* Gain: '<S80>/Output' */
    f14tmp25_B.Output_b = f14tmp25_P.Output_Gain_k2 * f14tmp25_B.WhiteNoise_a;
  }

  /* TransferFcn: '<S81>/Transfer Fcn.2' */
  f14tmp25_B.TransferFcn2_f = f14tmp25_P.TransferFcn2_C_gn*
    f14tmp25_X.TransferFcn2_CSTATE_b;

  /* Gain: '<S12>/Gain5' */
  f14tmp25_B.Gain5_nb = f14tmp25_P.Gain5_Gain_nx * f14tmp25_B.TransferFcn2_f;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* Derivative: '<S84>/Derivative' */
  {
    real_T t = f14tmp25_rtM->Timing.t[0];
    real_T timeStampA = f14tmp25_DWork.Derivative_RWORK_l.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative_RWORK_l.TimeStampB;
    real_T *lastU = &f14tmp25_DWork.Derivative_RWORK_l.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp25_B.Derivative_a = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp25_DWork.Derivative_RWORK_l.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_l.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp25_B.Derivative_a = (f14tmp25_B.TransferFcn2_f - *lastU++) / deltaT;
    }
  }

  /* TransferFcn: '<S81>/Transfer Fcn.1' */
  f14tmp25_B.TransferFcn1_e = f14tmp25_P.TransferFcn1_C_e*
    f14tmp25_X.TransferFcn1_CSTATE_l;

  /* Derivative: '<S84>/Derivative1' */
  {
    real_T t = f14tmp25_rtM->Timing.t[0];
    real_T timeStampA = f14tmp25_DWork.Derivative1_RWORK_eb.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative1_RWORK_eb.TimeStampB;
    real_T *lastU = &f14tmp25_DWork.Derivative1_RWORK_eb.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp25_B.Derivative1_b = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp25_DWork.Derivative1_RWORK_eb.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_eb.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp25_B.Derivative1_b = (f14tmp25_B.TransferFcn1_e - *lastU++) / deltaT;
    }
  }

  /* Gain: '<S84>/Gain1' */
  f14tmp25_B.Gain1_d = f14tmp25_P.Gain1_Gain_n2 * f14tmp25_B.Derivative1_b;

  /* Product: '<S84>/Product' incorporates:
   *  Constant: '<S84>/Constant'
   */
  f14tmp25_B.Product_ik = f14tmp25_B.TransferFcn1_e *
    f14tmp25_P.Constant_Value_ha;

  /* Sum: '<S84>/Sum1' */
  f14tmp25_B.Sum1_dh = (f14tmp25_B.Gain1_d - f14tmp25_B.Derivative_a) +
    f14tmp25_B.Product_ik;

  /* Gain: '<S84>/Gain2' */
  f14tmp25_B.Gain2_ny = f14tmp25_P.Gain2_Gain_nx * f14tmp25_B.Sum1_dh;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* SignalGenerator: '<S12>/Pilot' */
  temp = f14tmp25_P.Pilot_Frequency_h * f14tmp25_rtM->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    f14tmp25_B.Pilot_f = f14tmp25_P.Pilot_Amplitude_dw;
  } else {
    f14tmp25_B.Pilot_f = -f14tmp25_P.Pilot_Amplitude_dw;
  }

  /* End of SignalGenerator: '<S12>/Pilot' */

  /* Sum: '<S12>/Sum1' */
  f14tmp25_B.Sum1_oo = f14tmp25_B.Pilot_f + 0.0;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* TransferFcn: '<S12>/Actuator Model' */
  f14tmp25_B.ActuatorModel_o = f14tmp25_P.ActuatorModel_C_dv*
    f14tmp25_X.ActuatorModel_CSTATE_d;

  /* Gain: '<S81>/Gain3' */
  f14tmp25_B.Gain3_nz = f14tmp25_P.Gain3_Gain_n * f14tmp25_B.TransferFcn1_e;

  /* Gain: '<S81>/Gain4' */
  f14tmp25_B.Gain4_fm = f14tmp25_P.Gain4_Gain_f0 * f14tmp25_B.TransferFcn2_f;

  /* Gain: '<S81>/Gain5' */
  f14tmp25_B.Gain5_hb = f14tmp25_P.Gain5_Gain_lt * f14tmp25_B.ActuatorModel_o;

  /* Gain: '<S81>/Gain6' */
  f14tmp25_B.Gain6_i = f14tmp25_P.Gain6_Gain_bp * f14tmp25_B.ActuatorModel_o;

  /* TransferFcn: '<S83>/W-gust model' */
  f14tmp25_B.Wgustmodel_c5 = f14tmp25_P.Wgustmodel_C_cv[0]*
    f14tmp25_X.Wgustmodel_CSTATE_n[0]
    + f14tmp25_P.Wgustmodel_C_cv[1]*f14tmp25_X.Wgustmodel_CSTATE_n[1];

  /* Gain: '<S12>/Gain' */
  f14tmp25_B.Gain_e4 = f14tmp25_P.Gain_Gain_m1g * f14tmp25_B.Wgustmodel_c5;

  /* Sum: '<S81>/Sum1' */
  f14tmp25_B.Sum1_bk = (f14tmp25_B.Gain5_hb - f14tmp25_B.Gain_e4) +
    f14tmp25_B.Gain3_nz;

  /* Gain: '<S12>/Gain2' */
  f14tmp25_B.Gain2_pz = f14tmp25_P.Gain2_Gain_pr * f14tmp25_B.Wgustmodel_c5;

  /* TransferFcn: '<S83>/Q-gust model' */
  f14tmp25_B.Qgustmodel_j = f14tmp25_P.Qgustmodel_D_pk*f14tmp25_B.Wgustmodel_c5;
  f14tmp25_B.Qgustmodel_j += f14tmp25_P.Qgustmodel_C_i*
    f14tmp25_X.Qgustmodel_CSTATE_g;

  /* Gain: '<S12>/Gain1' */
  f14tmp25_B.Gain1_du = f14tmp25_P.Gain1_Gain_gb * f14tmp25_B.Qgustmodel_j;

  /* Sum: '<S12>/Sum' */
  f14tmp25_B.Sum_h4 = f14tmp25_B.Gain2_pz + f14tmp25_B.Gain1_du;

  /* Sum: '<S81>/Sum2' */
  f14tmp25_B.Sum2_ol = (f14tmp25_B.Gain4_fm - f14tmp25_B.Sum_h4) +
    f14tmp25_B.Gain6_i;

  /* TransferFcn: '<S82>/Alpha-sensor Low-pass Filter' */
  f14tmp25_B.AlphasensorLowpassFilter_p =
    f14tmp25_P.AlphasensorLowpassFilter_C_m*
    f14tmp25_X.AlphasensorLowpassFilter_CSTA_b;

  /* TransferFcn: '<S82>/Stick Prefilter' */
  f14tmp25_B.StickPrefilter_cq = f14tmp25_P.StickPrefilter_C_mg*
    f14tmp25_X.StickPrefilter_CSTATE_j;

  /* TransferFcn: '<S82>/Pitch Rate Lead Filter' */
  f14tmp25_B.PitchRateLeadFilter_c = f14tmp25_P.PitchRateLeadFilter_D_fx*
    f14tmp25_B.TransferFcn1_e;
  f14tmp25_B.PitchRateLeadFilter_c += f14tmp25_P.PitchRateLeadFilter_C_nz*
    f14tmp25_X.PitchRateLeadFilter_CSTATE_f;

  /* Gain: '<S82>/Gain2' */
  f14tmp25_B.Gain2_ar = f14tmp25_P.Gain2_Gain_kt *
    f14tmp25_B.PitchRateLeadFilter_c;

  /* Gain: '<S82>/Gain3' */
  f14tmp25_B.Gain3_n3 = f14tmp25_P.Gain3_Gain_ca *
    f14tmp25_B.AlphasensorLowpassFilter_p;

  /* Sum: '<S82>/Sum1' */
  f14tmp25_B.Sum1_ot = f14tmp25_B.Gain2_ar + f14tmp25_B.Gain3_n3;

  /* Sum: '<S82>/Sum2' */
  f14tmp25_B.Sum2_px = f14tmp25_B.StickPrefilter_cq - f14tmp25_B.Sum1_ot;

  /* Gain: '<S82>/Gain' */
  f14tmp25_B.Gain_p = f14tmp25_P.Gain_Gain_lq * f14tmp25_B.Sum2_px;

  /* TransferFcn: '<S82>/Proportional plus integral compensator' */
  f14tmp25_B.Proportionalplusintegralcompe_h =
    f14tmp25_P.Proportionalplusintegralcompe_j*
    f14tmp25_X.Proportionalplusintegralcompe_o;

  /* Sum: '<S82>/Sum' */
  f14tmp25_B.Sum_my = f14tmp25_B.Gain_p +
    f14tmp25_B.Proportionalplusintegralcompe_h;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* RandomNumber: '<S85>/White Noise' */
    f14tmp25_B.WhiteNoise_dw = f14tmp25_DWork.NextOutput_m;

    /* Gain: '<S85>/Output' */
    f14tmp25_B.Output_l = f14tmp25_P.Output_Gain_cn * f14tmp25_B.WhiteNoise_dw;
  }

  /* TransferFcn: '<S86>/Transfer Fcn.2' */
  f14tmp25_B.TransferFcn2_l = f14tmp25_P.TransferFcn2_C_a*
    f14tmp25_X.TransferFcn2_CSTATE_n5;

  /* Gain: '<S13>/Gain5' */
  f14tmp25_B.Gain5_py = f14tmp25_P.Gain5_Gain_cw * f14tmp25_B.TransferFcn2_l;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* Derivative: '<S89>/Derivative' */
  {
    real_T t = f14tmp25_rtM->Timing.t[0];
    real_T timeStampA = f14tmp25_DWork.Derivative_RWORK_lu.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative_RWORK_lu.TimeStampB;
    real_T *lastU = &f14tmp25_DWork.Derivative_RWORK_lu.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp25_B.Derivative_lz = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp25_DWork.Derivative_RWORK_lu.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_lu.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp25_B.Derivative_lz = (f14tmp25_B.TransferFcn2_l - *lastU++) / deltaT;
    }
  }

  /* TransferFcn: '<S86>/Transfer Fcn.1' */
  f14tmp25_B.TransferFcn1_gi = f14tmp25_P.TransferFcn1_C_gb*
    f14tmp25_X.TransferFcn1_CSTATE_k;

  /* Derivative: '<S89>/Derivative1' */
  {
    real_T t = f14tmp25_rtM->Timing.t[0];
    real_T timeStampA = f14tmp25_DWork.Derivative1_RWORK_k.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative1_RWORK_k.TimeStampB;
    real_T *lastU = &f14tmp25_DWork.Derivative1_RWORK_k.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp25_B.Derivative1_j = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp25_DWork.Derivative1_RWORK_k.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_k.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp25_B.Derivative1_j = (f14tmp25_B.TransferFcn1_gi - *lastU++) /
        deltaT;
    }
  }

  /* Gain: '<S89>/Gain1' */
  f14tmp25_B.Gain1_g4 = f14tmp25_P.Gain1_Gain_em * f14tmp25_B.Derivative1_j;

  /* Product: '<S89>/Product' incorporates:
   *  Constant: '<S89>/Constant'
   */
  f14tmp25_B.Product_b = f14tmp25_B.TransferFcn1_gi *
    f14tmp25_P.Constant_Value_bm;

  /* Sum: '<S89>/Sum1' */
  f14tmp25_B.Sum1_ev = (f14tmp25_B.Gain1_g4 - f14tmp25_B.Derivative_lz) +
    f14tmp25_B.Product_b;

  /* Gain: '<S89>/Gain2' */
  f14tmp25_B.Gain2_g = f14tmp25_P.Gain2_Gain_h5 * f14tmp25_B.Sum1_ev;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* SignalGenerator: '<S13>/Pilot' */
  temp = f14tmp25_P.Pilot_Frequency_k * f14tmp25_rtM->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    f14tmp25_B.Pilot_h = f14tmp25_P.Pilot_Amplitude_e;
  } else {
    f14tmp25_B.Pilot_h = -f14tmp25_P.Pilot_Amplitude_e;
  }

  /* End of SignalGenerator: '<S13>/Pilot' */

  /* Sum: '<S13>/Sum1' */
  f14tmp25_B.Sum1_n0 = f14tmp25_B.Pilot_h + 0.0;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* TransferFcn: '<S13>/Actuator Model' */
  f14tmp25_B.ActuatorModel_a = f14tmp25_P.ActuatorModel_C_bj*
    f14tmp25_X.ActuatorModel_CSTATE_fg;

  /* Gain: '<S86>/Gain3' */
  f14tmp25_B.Gain3_m = f14tmp25_P.Gain3_Gain_cd * f14tmp25_B.TransferFcn1_gi;

  /* Gain: '<S86>/Gain4' */
  f14tmp25_B.Gain4_c = f14tmp25_P.Gain4_Gain_j * f14tmp25_B.TransferFcn2_l;

  /* Gain: '<S86>/Gain5' */
  f14tmp25_B.Gain5_o = f14tmp25_P.Gain5_Gain_pd * f14tmp25_B.ActuatorModel_a;

  /* Gain: '<S86>/Gain6' */
  f14tmp25_B.Gain6_mc = f14tmp25_P.Gain6_Gain_f * f14tmp25_B.ActuatorModel_a;

  /* TransferFcn: '<S88>/W-gust model' */
  f14tmp25_B.Wgustmodel_e = f14tmp25_P.Wgustmodel_C_mc[0]*
    f14tmp25_X.Wgustmodel_CSTATE_i[0]
    + f14tmp25_P.Wgustmodel_C_mc[1]*f14tmp25_X.Wgustmodel_CSTATE_i[1];

  /* Gain: '<S13>/Gain' */
  f14tmp25_B.Gain_la = f14tmp25_P.Gain_Gain_d * f14tmp25_B.Wgustmodel_e;

  /* Sum: '<S86>/Sum1' */
  f14tmp25_B.Sum1_dr = (f14tmp25_B.Gain5_o - f14tmp25_B.Gain_la) +
    f14tmp25_B.Gain3_m;

  /* Gain: '<S13>/Gain2' */
  f14tmp25_B.Gain2_l0 = f14tmp25_P.Gain2_Gain_g3 * f14tmp25_B.Wgustmodel_e;

  /* TransferFcn: '<S88>/Q-gust model' */
  f14tmp25_B.Qgustmodel_jp = f14tmp25_P.Qgustmodel_D_i*f14tmp25_B.Wgustmodel_e;
  f14tmp25_B.Qgustmodel_jp += f14tmp25_P.Qgustmodel_C_j0*
    f14tmp25_X.Qgustmodel_CSTATE_k;

  /* Gain: '<S13>/Gain1' */
  f14tmp25_B.Gain1_bt = f14tmp25_P.Gain1_Gain_f * f14tmp25_B.Qgustmodel_jp;

  /* Sum: '<S13>/Sum' */
  f14tmp25_B.Sum_iw = f14tmp25_B.Gain2_l0 + f14tmp25_B.Gain1_bt;

  /* Sum: '<S86>/Sum2' */
  f14tmp25_B.Sum2_ola = (f14tmp25_B.Gain4_c - f14tmp25_B.Sum_iw) +
    f14tmp25_B.Gain6_mc;

  /* TransferFcn: '<S87>/Alpha-sensor Low-pass Filter' */
  f14tmp25_B.AlphasensorLowpassFilter_h =
    f14tmp25_P.AlphasensorLowpassFilter_C_gf*
    f14tmp25_X.AlphasensorLowpassFilter_CST_i1;

  /* TransferFcn: '<S87>/Stick Prefilter' */
  f14tmp25_B.StickPrefilter_i = f14tmp25_P.StickPrefilter_C_j0*
    f14tmp25_X.StickPrefilter_CSTATE_jz;

  /* TransferFcn: '<S87>/Pitch Rate Lead Filter' */
  f14tmp25_B.PitchRateLeadFilter_dg = f14tmp25_P.PitchRateLeadFilter_D_ft*
    f14tmp25_B.TransferFcn1_gi;
  f14tmp25_B.PitchRateLeadFilter_dg += f14tmp25_P.PitchRateLeadFilter_C_k4*
    f14tmp25_X.PitchRateLeadFilter_CSTATE_n;

  /* Gain: '<S87>/Gain2' */
  f14tmp25_B.Gain2_ph = f14tmp25_P.Gain2_Gain_eh *
    f14tmp25_B.PitchRateLeadFilter_dg;

  /* Gain: '<S87>/Gain3' */
  f14tmp25_B.Gain3_gl = f14tmp25_P.Gain3_Gain_my *
    f14tmp25_B.AlphasensorLowpassFilter_h;

  /* Sum: '<S87>/Sum1' */
  f14tmp25_B.Sum1_o0 = f14tmp25_B.Gain2_ph + f14tmp25_B.Gain3_gl;

  /* Sum: '<S87>/Sum2' */
  f14tmp25_B.Sum2_gk = f14tmp25_B.StickPrefilter_i - f14tmp25_B.Sum1_o0;

  /* Gain: '<S87>/Gain' */
  f14tmp25_B.Gain_hu = f14tmp25_P.Gain_Gain_jg * f14tmp25_B.Sum2_gk;

  /* TransferFcn: '<S87>/Proportional plus integral compensator' */
  f14tmp25_B.Proportionalplusintegralcompe_e =
    f14tmp25_P.Proportionalplusintegralcomp_lj*
    f14tmp25_X.Proportionalplusintegralcomp_hi;

  /* Sum: '<S87>/Sum' */
  f14tmp25_B.Sum_ou = f14tmp25_B.Gain_hu +
    f14tmp25_B.Proportionalplusintegralcompe_e;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* RandomNumber: '<S90>/White Noise' */
    f14tmp25_B.WhiteNoise_gw = f14tmp25_DWork.NextOutput_hq;

    /* Gain: '<S90>/Output' */
    f14tmp25_B.Output_c = f14tmp25_P.Output_Gain_me * f14tmp25_B.WhiteNoise_gw;
  }

  /* TransferFcn: '<S91>/Transfer Fcn.2' */
  f14tmp25_B.TransferFcn2_ne = f14tmp25_P.TransferFcn2_C_ik*
    f14tmp25_X.TransferFcn2_CSTATE_k;

  /* Gain: '<S14>/Gain5' */
  f14tmp25_B.Gain5_kd = f14tmp25_P.Gain5_Gain_ey * f14tmp25_B.TransferFcn2_ne;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* Derivative: '<S94>/Derivative' */
  {
    real_T t = f14tmp25_rtM->Timing.t[0];
    real_T timeStampA = f14tmp25_DWork.Derivative_RWORK_n.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative_RWORK_n.TimeStampB;
    real_T *lastU = &f14tmp25_DWork.Derivative_RWORK_n.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp25_B.Derivative_bl = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp25_DWork.Derivative_RWORK_n.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_n.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp25_B.Derivative_bl = (f14tmp25_B.TransferFcn2_ne - *lastU++) /
        deltaT;
    }
  }

  /* TransferFcn: '<S91>/Transfer Fcn.1' */
  f14tmp25_B.TransferFcn1_i = f14tmp25_P.TransferFcn1_C_o*
    f14tmp25_X.TransferFcn1_CSTATE_g;

  /* Derivative: '<S94>/Derivative1' */
  {
    real_T t = f14tmp25_rtM->Timing.t[0];
    real_T timeStampA = f14tmp25_DWork.Derivative1_RWORK_m.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative1_RWORK_m.TimeStampB;
    real_T *lastU = &f14tmp25_DWork.Derivative1_RWORK_m.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp25_B.Derivative1_f = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp25_DWork.Derivative1_RWORK_m.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_m.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp25_B.Derivative1_f = (f14tmp25_B.TransferFcn1_i - *lastU++) / deltaT;
    }
  }

  /* Gain: '<S94>/Gain1' */
  f14tmp25_B.Gain1_m = f14tmp25_P.Gain1_Gain_b * f14tmp25_B.Derivative1_f;

  /* Product: '<S94>/Product' incorporates:
   *  Constant: '<S94>/Constant'
   */
  f14tmp25_B.Product_l = f14tmp25_B.TransferFcn1_i * f14tmp25_P.Constant_Value_d;

  /* Sum: '<S94>/Sum1' */
  f14tmp25_B.Sum1_cl = (f14tmp25_B.Gain1_m - f14tmp25_B.Derivative_bl) +
    f14tmp25_B.Product_l;

  /* Gain: '<S94>/Gain2' */
  f14tmp25_B.Gain2_e5 = f14tmp25_P.Gain2_Gain_pl * f14tmp25_B.Sum1_cl;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* SignalGenerator: '<S14>/Pilot' */
  temp = f14tmp25_P.Pilot_Frequency_cr * f14tmp25_rtM->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    f14tmp25_B.Pilot_bf = f14tmp25_P.Pilot_Amplitude_b;
  } else {
    f14tmp25_B.Pilot_bf = -f14tmp25_P.Pilot_Amplitude_b;
  }

  /* End of SignalGenerator: '<S14>/Pilot' */

  /* Sum: '<S14>/Sum1' */
  f14tmp25_B.Sum1_co = f14tmp25_B.Pilot_bf + 0.0;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* TransferFcn: '<S14>/Actuator Model' */
  f14tmp25_B.ActuatorModel_o5 = f14tmp25_P.ActuatorModel_C_n*
    f14tmp25_X.ActuatorModel_CSTATE_ov;

  /* Gain: '<S91>/Gain3' */
  f14tmp25_B.Gain3_j2 = f14tmp25_P.Gain3_Gain_e0 * f14tmp25_B.TransferFcn1_i;

  /* Gain: '<S91>/Gain4' */
  f14tmp25_B.Gain4_o = f14tmp25_P.Gain4_Gain_n * f14tmp25_B.TransferFcn2_ne;

  /* Gain: '<S91>/Gain5' */
  f14tmp25_B.Gain5_l2 = f14tmp25_P.Gain5_Gain_hv * f14tmp25_B.ActuatorModel_o5;

  /* Gain: '<S91>/Gain6' */
  f14tmp25_B.Gain6_e = f14tmp25_P.Gain6_Gain_k * f14tmp25_B.ActuatorModel_o5;

  /* TransferFcn: '<S93>/W-gust model' */
  f14tmp25_B.Wgustmodel_dn = f14tmp25_P.Wgustmodel_C_n[0]*
    f14tmp25_X.Wgustmodel_CSTATE_p[0]
    + f14tmp25_P.Wgustmodel_C_n[1]*f14tmp25_X.Wgustmodel_CSTATE_p[1];

  /* Gain: '<S14>/Gain' */
  f14tmp25_B.Gain_obj = f14tmp25_P.Gain_Gain_lj * f14tmp25_B.Wgustmodel_dn;

  /* Sum: '<S91>/Sum1' */
  f14tmp25_B.Sum1_gl = (f14tmp25_B.Gain5_l2 - f14tmp25_B.Gain_obj) +
    f14tmp25_B.Gain3_j2;

  /* Gain: '<S14>/Gain2' */
  f14tmp25_B.Gain2_l4 = f14tmp25_P.Gain2_Gain_ir * f14tmp25_B.Wgustmodel_dn;

  /* TransferFcn: '<S93>/Q-gust model' */
  f14tmp25_B.Qgustmodel_k = f14tmp25_P.Qgustmodel_D_g*f14tmp25_B.Wgustmodel_dn;
  f14tmp25_B.Qgustmodel_k += f14tmp25_P.Qgustmodel_C_pp*
    f14tmp25_X.Qgustmodel_CSTATE_m;

  /* Gain: '<S14>/Gain1' */
  f14tmp25_B.Gain1_bx = f14tmp25_P.Gain1_Gain_gs * f14tmp25_B.Qgustmodel_k;

  /* Sum: '<S14>/Sum' */
  f14tmp25_B.Sum_b0 = f14tmp25_B.Gain2_l4 + f14tmp25_B.Gain1_bx;

  /* Sum: '<S91>/Sum2' */
  f14tmp25_B.Sum2_mr = (f14tmp25_B.Gain4_o - f14tmp25_B.Sum_b0) +
    f14tmp25_B.Gain6_e;

  /* TransferFcn: '<S92>/Alpha-sensor Low-pass Filter' */
  f14tmp25_B.AlphasensorLowpassFilter_o1 =
    f14tmp25_P.AlphasensorLowpassFilter_C_o*
    f14tmp25_X.AlphasensorLowpassFilter_CSTA_h;

  /* TransferFcn: '<S92>/Stick Prefilter' */
  f14tmp25_B.StickPrefilter_k = f14tmp25_P.StickPrefilter_C_g*
    f14tmp25_X.StickPrefilter_CSTATE_c;

  /* TransferFcn: '<S92>/Pitch Rate Lead Filter' */
  f14tmp25_B.PitchRateLeadFilter_j = f14tmp25_P.PitchRateLeadFilter_D_m*
    f14tmp25_B.TransferFcn1_i;
  f14tmp25_B.PitchRateLeadFilter_j += f14tmp25_P.PitchRateLeadFilter_C_it*
    f14tmp25_X.PitchRateLeadFilter_CSTATE_m2;

  /* Gain: '<S92>/Gain2' */
  f14tmp25_B.Gain2_aa = f14tmp25_P.Gain2_Gain_nm *
    f14tmp25_B.PitchRateLeadFilter_j;

  /* Gain: '<S92>/Gain3' */
  f14tmp25_B.Gain3_js = f14tmp25_P.Gain3_Gain_fp *
    f14tmp25_B.AlphasensorLowpassFilter_o1;

  /* Sum: '<S92>/Sum1' */
  f14tmp25_B.Sum1_os = f14tmp25_B.Gain2_aa + f14tmp25_B.Gain3_js;

  /* Sum: '<S92>/Sum2' */
  f14tmp25_B.Sum2_mn = f14tmp25_B.StickPrefilter_k - f14tmp25_B.Sum1_os;

  /* Gain: '<S92>/Gain' */
  f14tmp25_B.Gain_c0 = f14tmp25_P.Gain_Gain_og * f14tmp25_B.Sum2_mn;

  /* TransferFcn: '<S92>/Proportional plus integral compensator' */
  f14tmp25_B.Proportionalplusintegralcomp_ii =
    f14tmp25_P.Proportionalplusintegralcomp_dy*
    f14tmp25_X.Proportionalplusintegralcomp_gw;

  /* Sum: '<S92>/Sum' */
  f14tmp25_B.Sum_af = f14tmp25_B.Gain_c0 +
    f14tmp25_B.Proportionalplusintegralcomp_ii;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* RandomNumber: '<S95>/White Noise' */
    f14tmp25_B.WhiteNoise_h = f14tmp25_DWork.NextOutput_nm;

    /* Gain: '<S95>/Output' */
    f14tmp25_B.Output_k = f14tmp25_P.Output_Gain_n * f14tmp25_B.WhiteNoise_h;
  }

  /* TransferFcn: '<S96>/Transfer Fcn.2' */
  f14tmp25_B.TransferFcn2_a = f14tmp25_P.TransferFcn2_C_iy*
    f14tmp25_X.TransferFcn2_CSTATE_ki;

  /* Gain: '<S15>/Gain5' */
  f14tmp25_B.Gain5_kv = f14tmp25_P.Gain5_Gain_eyn * f14tmp25_B.TransferFcn2_a;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* Derivative: '<S99>/Derivative' */
  {
    real_T t = f14tmp25_rtM->Timing.t[0];
    real_T timeStampA = f14tmp25_DWork.Derivative_RWORK_d.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative_RWORK_d.TimeStampB;
    real_T *lastU = &f14tmp25_DWork.Derivative_RWORK_d.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp25_B.Derivative_im = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp25_DWork.Derivative_RWORK_d.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_d.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp25_B.Derivative_im = (f14tmp25_B.TransferFcn2_a - *lastU++) / deltaT;
    }
  }

  /* TransferFcn: '<S96>/Transfer Fcn.1' */
  f14tmp25_B.TransferFcn1_e3 = f14tmp25_P.TransferFcn1_C_a*
    f14tmp25_X.TransferFcn1_CSTATE_im;

  /* Derivative: '<S99>/Derivative1' */
  {
    real_T t = f14tmp25_rtM->Timing.t[0];
    real_T timeStampA = f14tmp25_DWork.Derivative1_RWORK_b.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative1_RWORK_b.TimeStampB;
    real_T *lastU = &f14tmp25_DWork.Derivative1_RWORK_b.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp25_B.Derivative1_ph = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp25_DWork.Derivative1_RWORK_b.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_b.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp25_B.Derivative1_ph = (f14tmp25_B.TransferFcn1_e3 - *lastU++) /
        deltaT;
    }
  }

  /* Gain: '<S99>/Gain1' */
  f14tmp25_B.Gain1_on = f14tmp25_P.Gain1_Gain_mj * f14tmp25_B.Derivative1_ph;

  /* Product: '<S99>/Product' incorporates:
   *  Constant: '<S99>/Constant'
   */
  f14tmp25_B.Product_dp5 = f14tmp25_B.TransferFcn1_e3 *
    f14tmp25_P.Constant_Value_a;

  /* Sum: '<S99>/Sum1' */
  f14tmp25_B.Sum1_h0 = (f14tmp25_B.Gain1_on - f14tmp25_B.Derivative_im) +
    f14tmp25_B.Product_dp5;

  /* Gain: '<S99>/Gain2' */
  f14tmp25_B.Gain2_gc = f14tmp25_P.Gain2_Gain_b0 * f14tmp25_B.Sum1_h0;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* SignalGenerator: '<S15>/Pilot' */
  temp = f14tmp25_P.Pilot_Frequency_m * f14tmp25_rtM->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    f14tmp25_B.Pilot_fw = f14tmp25_P.Pilot_Amplitude_a;
  } else {
    f14tmp25_B.Pilot_fw = -f14tmp25_P.Pilot_Amplitude_a;
  }

  /* End of SignalGenerator: '<S15>/Pilot' */

  /* Sum: '<S15>/Sum1' */
  f14tmp25_B.Sum1_lr = f14tmp25_B.Pilot_fw + 0.0;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* TransferFcn: '<S15>/Actuator Model' */
  f14tmp25_B.ActuatorModel_j1 = f14tmp25_P.ActuatorModel_C_o*
    f14tmp25_X.ActuatorModel_CSTATE_i;

  /* Gain: '<S96>/Gain3' */
  f14tmp25_B.Gain3_jn = f14tmp25_P.Gain3_Gain_c3 * f14tmp25_B.TransferFcn1_e3;

  /* Gain: '<S96>/Gain4' */
  f14tmp25_B.Gain4_or = f14tmp25_P.Gain4_Gain_jg * f14tmp25_B.TransferFcn2_a;

  /* Gain: '<S96>/Gain5' */
  f14tmp25_B.Gain5_i = f14tmp25_P.Gain5_Gain_d * f14tmp25_B.ActuatorModel_j1;

  /* Gain: '<S96>/Gain6' */
  f14tmp25_B.Gain6_dl = f14tmp25_P.Gain6_Gain_an * f14tmp25_B.ActuatorModel_j1;

  /* TransferFcn: '<S98>/W-gust model' */
  f14tmp25_B.Wgustmodel_gx = f14tmp25_P.Wgustmodel_C_f[0]*
    f14tmp25_X.Wgustmodel_CSTATE_o[0]
    + f14tmp25_P.Wgustmodel_C_f[1]*f14tmp25_X.Wgustmodel_CSTATE_o[1];

  /* Gain: '<S15>/Gain' */
  f14tmp25_B.Gain_gh = f14tmp25_P.Gain_Gain_ir * f14tmp25_B.Wgustmodel_gx;

  /* Sum: '<S96>/Sum1' */
  f14tmp25_B.Sum1_iav = (f14tmp25_B.Gain5_i - f14tmp25_B.Gain_gh) +
    f14tmp25_B.Gain3_jn;

  /* Gain: '<S15>/Gain2' */
  f14tmp25_B.Gain2_b4 = f14tmp25_P.Gain2_Gain_cq * f14tmp25_B.Wgustmodel_gx;

  /* TransferFcn: '<S98>/Q-gust model' */
  f14tmp25_B.Qgustmodel_kd = f14tmp25_P.Qgustmodel_D_k*f14tmp25_B.Wgustmodel_gx;
  f14tmp25_B.Qgustmodel_kd += f14tmp25_P.Qgustmodel_C_bf*
    f14tmp25_X.Qgustmodel_CSTATE_n;

  /* Gain: '<S15>/Gain1' */
  f14tmp25_B.Gain1_mh = f14tmp25_P.Gain1_Gain_k * f14tmp25_B.Qgustmodel_kd;

  /* Sum: '<S15>/Sum' */
  f14tmp25_B.Sum_lg = f14tmp25_B.Gain2_b4 + f14tmp25_B.Gain1_mh;

  /* Sum: '<S96>/Sum2' */
  f14tmp25_B.Sum2_bu = (f14tmp25_B.Gain4_or - f14tmp25_B.Sum_lg) +
    f14tmp25_B.Gain6_dl;

  /* TransferFcn: '<S97>/Alpha-sensor Low-pass Filter' */
  f14tmp25_B.AlphasensorLowpassFilter_kd =
    f14tmp25_P.AlphasensorLowpassFilter_C_nu*
    f14tmp25_X.AlphasensorLowpassFilter_CST_ef;

  /* TransferFcn: '<S97>/Stick Prefilter' */
  f14tmp25_B.StickPrefilter_dp = f14tmp25_P.StickPrefilter_C_jy*
    f14tmp25_X.StickPrefilter_CSTATE_n1;

  /* TransferFcn: '<S97>/Pitch Rate Lead Filter' */
  f14tmp25_B.PitchRateLeadFilter_an = f14tmp25_P.PitchRateLeadFilter_D_n*
    f14tmp25_B.TransferFcn1_e3;
  f14tmp25_B.PitchRateLeadFilter_an += f14tmp25_P.PitchRateLeadFilter_C_f*
    f14tmp25_X.PitchRateLeadFilter_CSTATE_mp;

  /* Gain: '<S97>/Gain2' */
  f14tmp25_B.Gain2_aw = f14tmp25_P.Gain2_Gain_hg *
    f14tmp25_B.PitchRateLeadFilter_an;

  /* Gain: '<S97>/Gain3' */
  f14tmp25_B.Gain3_b5 = f14tmp25_P.Gain3_Gain_m0 *
    f14tmp25_B.AlphasensorLowpassFilter_kd;

  /* Sum: '<S97>/Sum1' */
  f14tmp25_B.Sum1_hf = f14tmp25_B.Gain2_aw + f14tmp25_B.Gain3_b5;

  /* Sum: '<S97>/Sum2' */
  f14tmp25_B.Sum2_eu = f14tmp25_B.StickPrefilter_dp - f14tmp25_B.Sum1_hf;

  /* Gain: '<S97>/Gain' */
  f14tmp25_B.Gain_cg = f14tmp25_P.Gain_Gain_a3 * f14tmp25_B.Sum2_eu;

  /* TransferFcn: '<S97>/Proportional plus integral compensator' */
  f14tmp25_B.Proportionalplusintegralcom_iia =
    f14tmp25_P.Proportionalplusintegralcomp_gs*
    f14tmp25_X.Proportionalplusintegralcompe_j;

  /* Sum: '<S97>/Sum' */
  f14tmp25_B.Sum_kq = f14tmp25_B.Gain_cg +
    f14tmp25_B.Proportionalplusintegralcom_iia;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* RandomNumber: '<S100>/White Noise' */
    f14tmp25_B.WhiteNoise_ag = f14tmp25_DWork.NextOutput_i;

    /* Gain: '<S100>/Output' */
    f14tmp25_B.Output_gq = f14tmp25_P.Output_Gain_dh * f14tmp25_B.WhiteNoise_ag;
  }

  /* TransferFcn: '<S101>/Transfer Fcn.2' */
  f14tmp25_B.TransferFcn2_j = f14tmp25_P.TransferFcn2_C_h*
    f14tmp25_X.TransferFcn2_CSTATE_oa;

  /* Gain: '<S16>/Gain5' */
  f14tmp25_B.Gain5_nz = f14tmp25_P.Gain5_Gain_kt * f14tmp25_B.TransferFcn2_j;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* Derivative: '<S104>/Derivative' */
  {
    real_T t = f14tmp25_rtM->Timing.t[0];
    real_T timeStampA = f14tmp25_DWork.Derivative_RWORK_fd.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative_RWORK_fd.TimeStampB;
    real_T *lastU = &f14tmp25_DWork.Derivative_RWORK_fd.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp25_B.Derivative_g = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp25_DWork.Derivative_RWORK_fd.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_fd.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp25_B.Derivative_g = (f14tmp25_B.TransferFcn2_j - *lastU++) / deltaT;
    }
  }

  /* TransferFcn: '<S101>/Transfer Fcn.1' */
  f14tmp25_B.TransferFcn1_n3 = f14tmp25_P.TransferFcn1_C_h*
    f14tmp25_X.TransferFcn1_CSTATE_a;

  /* Derivative: '<S104>/Derivative1' */
  {
    real_T t = f14tmp25_rtM->Timing.t[0];
    real_T timeStampA = f14tmp25_DWork.Derivative1_RWORK_bx.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative1_RWORK_bx.TimeStampB;
    real_T *lastU = &f14tmp25_DWork.Derivative1_RWORK_bx.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp25_B.Derivative1_l2 = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp25_DWork.Derivative1_RWORK_bx.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_bx.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp25_B.Derivative1_l2 = (f14tmp25_B.TransferFcn1_n3 - *lastU++) /
        deltaT;
    }
  }

  /* Gain: '<S104>/Gain1' */
  f14tmp25_B.Gain1_n = f14tmp25_P.Gain1_Gain_nw * f14tmp25_B.Derivative1_l2;

  /* Product: '<S104>/Product' incorporates:
   *  Constant: '<S104>/Constant'
   */
  f14tmp25_B.Product_e = f14tmp25_B.TransferFcn1_n3 *
    f14tmp25_P.Constant_Value_fo;

  /* Sum: '<S104>/Sum1' */
  f14tmp25_B.Sum1_b2 = (f14tmp25_B.Gain1_n - f14tmp25_B.Derivative_g) +
    f14tmp25_B.Product_e;

  /* Gain: '<S104>/Gain2' */
  f14tmp25_B.Gain2_mw = f14tmp25_P.Gain2_Gain_iv * f14tmp25_B.Sum1_b2;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* SignalGenerator: '<S16>/Pilot' */
  temp = f14tmp25_P.Pilot_Frequency_o * f14tmp25_rtM->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    f14tmp25_B.Pilot_p = f14tmp25_P.Pilot_Amplitude_hb;
  } else {
    f14tmp25_B.Pilot_p = -f14tmp25_P.Pilot_Amplitude_hb;
  }

  /* End of SignalGenerator: '<S16>/Pilot' */

  /* Sum: '<S16>/Sum1' */
  f14tmp25_B.Sum1_ds = f14tmp25_B.Pilot_p + 0.0;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* TransferFcn: '<S16>/Actuator Model' */
  f14tmp25_B.ActuatorModel_g = f14tmp25_P.ActuatorModel_C_jw*
    f14tmp25_X.ActuatorModel_CSTATE_e;

  /* Gain: '<S101>/Gain3' */
  f14tmp25_B.Gain3_e3 = f14tmp25_P.Gain3_Gain_dc * f14tmp25_B.TransferFcn1_n3;

  /* Gain: '<S101>/Gain4' */
  f14tmp25_B.Gain4_d4 = f14tmp25_P.Gain4_Gain_np * f14tmp25_B.TransferFcn2_j;

  /* Gain: '<S101>/Gain5' */
  f14tmp25_B.Gain5_nu = f14tmp25_P.Gain5_Gain_ct * f14tmp25_B.ActuatorModel_g;

  /* Gain: '<S101>/Gain6' */
  f14tmp25_B.Gain6_ba = f14tmp25_P.Gain6_Gain_cq * f14tmp25_B.ActuatorModel_g;

  /* TransferFcn: '<S103>/W-gust model' */
  f14tmp25_B.Wgustmodel_i = f14tmp25_P.Wgustmodel_C_me[0]*
    f14tmp25_X.Wgustmodel_CSTATE_it[0]
    + f14tmp25_P.Wgustmodel_C_me[1]*f14tmp25_X.Wgustmodel_CSTATE_it[1];

  /* Gain: '<S16>/Gain' */
  f14tmp25_B.Gain_ii = f14tmp25_P.Gain_Gain_e3 * f14tmp25_B.Wgustmodel_i;

  /* Sum: '<S101>/Sum1' */
  f14tmp25_B.Sum1_bx5 = (f14tmp25_B.Gain5_nu - f14tmp25_B.Gain_ii) +
    f14tmp25_B.Gain3_e3;

  /* Gain: '<S16>/Gain2' */
  f14tmp25_B.Gain2_mc = f14tmp25_P.Gain2_Gain_ii * f14tmp25_B.Wgustmodel_i;

  /* TransferFcn: '<S103>/Q-gust model' */
  f14tmp25_B.Qgustmodel_d = f14tmp25_P.Qgustmodel_D_kl*f14tmp25_B.Wgustmodel_i;
  f14tmp25_B.Qgustmodel_d += f14tmp25_P.Qgustmodel_C_h*
    f14tmp25_X.Qgustmodel_CSTATE_ie;

  /* Gain: '<S16>/Gain1' */
  f14tmp25_B.Gain1_n3 = f14tmp25_P.Gain1_Gain_bc * f14tmp25_B.Qgustmodel_d;

  /* Sum: '<S16>/Sum' */
  f14tmp25_B.Sum_ns = f14tmp25_B.Gain2_mc + f14tmp25_B.Gain1_n3;

  /* Sum: '<S101>/Sum2' */
  f14tmp25_B.Sum2_ei = (f14tmp25_B.Gain4_d4 - f14tmp25_B.Sum_ns) +
    f14tmp25_B.Gain6_ba;

  /* TransferFcn: '<S102>/Alpha-sensor Low-pass Filter' */
  f14tmp25_B.AlphasensorLowpassFilter_b =
    f14tmp25_P.AlphasensorLowpassFilter_C_i*
    f14tmp25_X.AlphasensorLowpassFilter_CST_gn;

  /* TransferFcn: '<S102>/Stick Prefilter' */
  f14tmp25_B.StickPrefilter_ms = f14tmp25_P.StickPrefilter_C_k*
    f14tmp25_X.StickPrefilter_CSTATE_bs;

  /* TransferFcn: '<S102>/Pitch Rate Lead Filter' */
  f14tmp25_B.PitchRateLeadFilter_af = f14tmp25_P.PitchRateLeadFilter_D_hr*
    f14tmp25_B.TransferFcn1_n3;
  f14tmp25_B.PitchRateLeadFilter_af += f14tmp25_P.PitchRateLeadFilter_C_fn*
    f14tmp25_X.PitchRateLeadFilter_CSTATE_mo;

  /* Gain: '<S102>/Gain2' */
  f14tmp25_B.Gain2_hf = f14tmp25_P.Gain2_Gain_hm *
    f14tmp25_B.PitchRateLeadFilter_af;

  /* Gain: '<S102>/Gain3' */
  f14tmp25_B.Gain3_bi = f14tmp25_P.Gain3_Gain_gc *
    f14tmp25_B.AlphasensorLowpassFilter_b;

  /* Sum: '<S102>/Sum1' */
  f14tmp25_B.Sum1_en = f14tmp25_B.Gain2_hf + f14tmp25_B.Gain3_bi;

  /* Sum: '<S102>/Sum2' */
  f14tmp25_B.Sum2_il = f14tmp25_B.StickPrefilter_ms - f14tmp25_B.Sum1_en;

  /* Gain: '<S102>/Gain' */
  f14tmp25_B.Gain_b = f14tmp25_P.Gain_Gain_mx * f14tmp25_B.Sum2_il;

  /* TransferFcn: '<S102>/Proportional plus integral compensator' */
  f14tmp25_B.Proportionalplusintegralcompe_d =
    f14tmp25_P.Proportionalplusintegralcomp_ej*
    f14tmp25_X.Proportionalplusintegralcompe_k;

  /* Sum: '<S102>/Sum' */
  f14tmp25_B.Sum_bd = f14tmp25_B.Gain_b +
    f14tmp25_B.Proportionalplusintegralcompe_d;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* RandomNumber: '<S105>/White Noise' */
    f14tmp25_B.WhiteNoise_ml = f14tmp25_DWork.NextOutput_o;

    /* Gain: '<S105>/Output' */
    f14tmp25_B.Output_d = f14tmp25_P.Output_Gain_f * f14tmp25_B.WhiteNoise_ml;
  }

  /* TransferFcn: '<S106>/Transfer Fcn.2' */
  f14tmp25_B.TransferFcn2_br = f14tmp25_P.TransferFcn2_C_jy*
    f14tmp25_X.TransferFcn2_CSTATE_bv;

  /* Gain: '<S17>/Gain5' */
  f14tmp25_B.Gain5_a = f14tmp25_P.Gain5_Gain_gx * f14tmp25_B.TransferFcn2_br;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* Derivative: '<S109>/Derivative' */
  {
    real_T t = f14tmp25_rtM->Timing.t[0];
    real_T timeStampA = f14tmp25_DWork.Derivative_RWORK_nx.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative_RWORK_nx.TimeStampB;
    real_T *lastU = &f14tmp25_DWork.Derivative_RWORK_nx.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp25_B.Derivative_f = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp25_DWork.Derivative_RWORK_nx.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_nx.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp25_B.Derivative_f = (f14tmp25_B.TransferFcn2_br - *lastU++) / deltaT;
    }
  }

  /* TransferFcn: '<S106>/Transfer Fcn.1' */
  f14tmp25_B.TransferFcn1_ep = f14tmp25_P.TransferFcn1_C_ip*
    f14tmp25_X.TransferFcn1_CSTATE_kr;

  /* Derivative: '<S109>/Derivative1' */
  {
    real_T t = f14tmp25_rtM->Timing.t[0];
    real_T timeStampA = f14tmp25_DWork.Derivative1_RWORK_kl.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative1_RWORK_kl.TimeStampB;
    real_T *lastU = &f14tmp25_DWork.Derivative1_RWORK_kl.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp25_B.Derivative1_pf = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp25_DWork.Derivative1_RWORK_kl.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_kl.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp25_B.Derivative1_pf = (f14tmp25_B.TransferFcn1_ep - *lastU++) /
        deltaT;
    }
  }

  /* Gain: '<S109>/Gain1' */
  f14tmp25_B.Gain1_ga = f14tmp25_P.Gain1_Gain_eo * f14tmp25_B.Derivative1_pf;

  /* Product: '<S109>/Product' incorporates:
   *  Constant: '<S109>/Constant'
   */
  f14tmp25_B.Product_j = f14tmp25_B.TransferFcn1_ep *
    f14tmp25_P.Constant_Value_n;

  /* Sum: '<S109>/Sum1' */
  f14tmp25_B.Sum1_pu = (f14tmp25_B.Gain1_ga - f14tmp25_B.Derivative_f) +
    f14tmp25_B.Product_j;

  /* Gain: '<S109>/Gain2' */
  f14tmp25_B.Gain2_io = f14tmp25_P.Gain2_Gain_f2 * f14tmp25_B.Sum1_pu;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* SignalGenerator: '<S17>/Pilot' */
  temp = f14tmp25_P.Pilot_Frequency_bs * f14tmp25_rtM->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    f14tmp25_B.Pilot_pz = f14tmp25_P.Pilot_Amplitude_jy;
  } else {
    f14tmp25_B.Pilot_pz = -f14tmp25_P.Pilot_Amplitude_jy;
  }

  /* End of SignalGenerator: '<S17>/Pilot' */

  /* Sum: '<S17>/Sum1' */
  f14tmp25_B.Sum1_cx = f14tmp25_B.Pilot_pz + 0.0;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* TransferFcn: '<S17>/Actuator Model' */
  f14tmp25_B.ActuatorModel_l = f14tmp25_P.ActuatorModel_C_ju*
    f14tmp25_X.ActuatorModel_CSTATE_l;

  /* Gain: '<S106>/Gain3' */
  f14tmp25_B.Gain3_nv = f14tmp25_P.Gain3_Gain_mv * f14tmp25_B.TransferFcn1_ep;

  /* Gain: '<S106>/Gain4' */
  f14tmp25_B.Gain4_kp = f14tmp25_P.Gain4_Gain_on * f14tmp25_B.TransferFcn2_br;

  /* Gain: '<S106>/Gain5' */
  f14tmp25_B.Gain5_eq = f14tmp25_P.Gain5_Gain_a * f14tmp25_B.ActuatorModel_l;

  /* Gain: '<S106>/Gain6' */
  f14tmp25_B.Gain6_f = f14tmp25_P.Gain6_Gain_h * f14tmp25_B.ActuatorModel_l;

  /* TransferFcn: '<S108>/W-gust model' */
  f14tmp25_B.Wgustmodel_o = f14tmp25_P.Wgustmodel_C_o2[0]*
    f14tmp25_X.Wgustmodel_CSTATE_h[0]
    + f14tmp25_P.Wgustmodel_C_o2[1]*f14tmp25_X.Wgustmodel_CSTATE_h[1];

  /* Gain: '<S17>/Gain' */
  f14tmp25_B.Gain_m = f14tmp25_P.Gain_Gain_cr * f14tmp25_B.Wgustmodel_o;

  /* Sum: '<S106>/Sum1' */
  f14tmp25_B.Sum1_kk = (f14tmp25_B.Gain5_eq - f14tmp25_B.Gain_m) +
    f14tmp25_B.Gain3_nv;

  /* Gain: '<S17>/Gain2' */
  f14tmp25_B.Gain2_kq = f14tmp25_P.Gain2_Gain_dq * f14tmp25_B.Wgustmodel_o;

  /* TransferFcn: '<S108>/Q-gust model' */
  f14tmp25_B.Qgustmodel_hf = f14tmp25_P.Qgustmodel_D_m*f14tmp25_B.Wgustmodel_o;
  f14tmp25_B.Qgustmodel_hf += f14tmp25_P.Qgustmodel_C_hg*
    f14tmp25_X.Qgustmodel_CSTATE_kp;

  /* Gain: '<S17>/Gain1' */
  f14tmp25_B.Gain1_ki = f14tmp25_P.Gain1_Gain_ee * f14tmp25_B.Qgustmodel_hf;

  /* Sum: '<S17>/Sum' */
  f14tmp25_B.Sum_f = f14tmp25_B.Gain2_kq + f14tmp25_B.Gain1_ki;

  /* Sum: '<S106>/Sum2' */
  f14tmp25_B.Sum2_ky = (f14tmp25_B.Gain4_kp - f14tmp25_B.Sum_f) +
    f14tmp25_B.Gain6_f;

  /* TransferFcn: '<S107>/Alpha-sensor Low-pass Filter' */
  f14tmp25_B.AlphasensorLowpassFilter_ob =
    f14tmp25_P.AlphasensorLowpassFilter_C_fg*
    f14tmp25_X.AlphasensorLowpassFilter_CSTA_p;

  /* TransferFcn: '<S107>/Stick Prefilter' */
  f14tmp25_B.StickPrefilter_kv = f14tmp25_P.StickPrefilter_C_a*
    f14tmp25_X.StickPrefilter_CSTATE_pr;

  /* TransferFcn: '<S107>/Pitch Rate Lead Filter' */
  f14tmp25_B.PitchRateLeadFilter_fw = f14tmp25_P.PitchRateLeadFilter_D_cw*
    f14tmp25_B.TransferFcn1_ep;
  f14tmp25_B.PitchRateLeadFilter_fw += f14tmp25_P.PitchRateLeadFilter_C_k3*
    f14tmp25_X.PitchRateLeadFilter_CSTATE_fn;

  /* Gain: '<S107>/Gain2' */
  f14tmp25_B.Gain2_lr = f14tmp25_P.Gain2_Gain_j *
    f14tmp25_B.PitchRateLeadFilter_fw;

  /* Gain: '<S107>/Gain3' */
  f14tmp25_B.Gain3_j0 = f14tmp25_P.Gain3_Gain_gu *
    f14tmp25_B.AlphasensorLowpassFilter_ob;

  /* Sum: '<S107>/Sum1' */
  f14tmp25_B.Sum1_ft = f14tmp25_B.Gain2_lr + f14tmp25_B.Gain3_j0;

  /* Sum: '<S107>/Sum2' */
  f14tmp25_B.Sum2_e1 = f14tmp25_B.StickPrefilter_kv - f14tmp25_B.Sum1_ft;

  /* Gain: '<S107>/Gain' */
  f14tmp25_B.Gain_mg = f14tmp25_P.Gain_Gain_f * f14tmp25_B.Sum2_e1;

  /* TransferFcn: '<S107>/Proportional plus integral compensator' */
  f14tmp25_B.Proportionalplusintegralcompe_k =
    f14tmp25_P.Proportionalplusintegralcom_gsn*
    f14tmp25_X.Proportionalplusintegralcomp_lg;

  /* Sum: '<S107>/Sum' */
  f14tmp25_B.Sum_ab = f14tmp25_B.Gain_mg +
    f14tmp25_B.Proportionalplusintegralcompe_k;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* RandomNumber: '<S110>/White Noise' */
    f14tmp25_B.WhiteNoise_cv = f14tmp25_DWork.NextOutput_h5;

    /* Gain: '<S110>/Output' */
    f14tmp25_B.Output_b0 = f14tmp25_P.Output_Gain_k21 * f14tmp25_B.WhiteNoise_cv;
  }

  /* TransferFcn: '<S111>/Transfer Fcn.2' */
  f14tmp25_B.TransferFcn2_m = f14tmp25_P.TransferFcn2_C_kd*
    f14tmp25_X.TransferFcn2_CSTATE_ku;

  /* Gain: '<S18>/Gain5' */
  f14tmp25_B.Gain5_l5 = f14tmp25_P.Gain5_Gain_ke * f14tmp25_B.TransferFcn2_m;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* Derivative: '<S114>/Derivative' */
  {
    real_T t = f14tmp25_rtM->Timing.t[0];
    real_T timeStampA = f14tmp25_DWork.Derivative_RWORK_bp.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative_RWORK_bp.TimeStampB;
    real_T *lastU = &f14tmp25_DWork.Derivative_RWORK_bp.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp25_B.Derivative_mv = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp25_DWork.Derivative_RWORK_bp.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_bp.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp25_B.Derivative_mv = (f14tmp25_B.TransferFcn2_m - *lastU++) / deltaT;
    }
  }

  /* TransferFcn: '<S111>/Transfer Fcn.1' */
  f14tmp25_B.TransferFcn1_j = f14tmp25_P.TransferFcn1_C_d*
    f14tmp25_X.TransferFcn1_CSTATE_ku;

  /* Derivative: '<S114>/Derivative1' */
  {
    real_T t = f14tmp25_rtM->Timing.t[0];
    real_T timeStampA = f14tmp25_DWork.Derivative1_RWORK_mv.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative1_RWORK_mv.TimeStampB;
    real_T *lastU = &f14tmp25_DWork.Derivative1_RWORK_mv.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp25_B.Derivative1_pz = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp25_DWork.Derivative1_RWORK_mv.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_mv.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp25_B.Derivative1_pz = (f14tmp25_B.TransferFcn1_j - *lastU++) /
        deltaT;
    }
  }

  /* Gain: '<S114>/Gain1' */
  f14tmp25_B.Gain1_ih = f14tmp25_P.Gain1_Gain_gs4 * f14tmp25_B.Derivative1_pz;

  /* Product: '<S114>/Product' incorporates:
   *  Constant: '<S114>/Constant'
   */
  f14tmp25_B.Product_ev = f14tmp25_B.TransferFcn1_j *
    f14tmp25_P.Constant_Value_kk;

  /* Sum: '<S114>/Sum1' */
  f14tmp25_B.Sum1_fi = (f14tmp25_B.Gain1_ih - f14tmp25_B.Derivative_mv) +
    f14tmp25_B.Product_ev;

  /* Gain: '<S114>/Gain2' */
  f14tmp25_B.Gain2_ix = f14tmp25_P.Gain2_Gain_ie * f14tmp25_B.Sum1_fi;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* SignalGenerator: '<S18>/Pilot' */
  temp = f14tmp25_P.Pilot_Frequency_l * f14tmp25_rtM->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    f14tmp25_B.Pilot_pg = f14tmp25_P.Pilot_Amplitude_oj;
  } else {
    f14tmp25_B.Pilot_pg = -f14tmp25_P.Pilot_Amplitude_oj;
  }

  /* End of SignalGenerator: '<S18>/Pilot' */

  /* Sum: '<S18>/Sum1' */
  f14tmp25_B.Sum1_i1 = f14tmp25_B.Pilot_pg + 0.0;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* TransferFcn: '<S18>/Actuator Model' */
  f14tmp25_B.ActuatorModel_p = f14tmp25_P.ActuatorModel_C_p*
    f14tmp25_X.ActuatorModel_CSTATE_hh;

  /* Gain: '<S111>/Gain3' */
  f14tmp25_B.Gain3_lz = f14tmp25_P.Gain3_Gain_ou * f14tmp25_B.TransferFcn1_j;

  /* Gain: '<S111>/Gain4' */
  f14tmp25_B.Gain4_i = f14tmp25_P.Gain4_Gain_fe * f14tmp25_B.TransferFcn2_m;

  /* Gain: '<S111>/Gain5' */
  f14tmp25_B.Gain5_bb = f14tmp25_P.Gain5_Gain_nv * f14tmp25_B.ActuatorModel_p;

  /* Gain: '<S111>/Gain6' */
  f14tmp25_B.Gain6_c = f14tmp25_P.Gain6_Gain_dl * f14tmp25_B.ActuatorModel_p;

  /* TransferFcn: '<S113>/W-gust model' */
  f14tmp25_B.Wgustmodel_a1 = f14tmp25_P.Wgustmodel_C_k[0]*
    f14tmp25_X.Wgustmodel_CSTATE_e5[0]
    + f14tmp25_P.Wgustmodel_C_k[1]*f14tmp25_X.Wgustmodel_CSTATE_e5[1];

  /* Gain: '<S18>/Gain' */
  f14tmp25_B.Gain_a = f14tmp25_P.Gain_Gain_ob * f14tmp25_B.Wgustmodel_a1;

  /* Sum: '<S111>/Sum1' */
  f14tmp25_B.Sum1_hu = (f14tmp25_B.Gain5_bb - f14tmp25_B.Gain_a) +
    f14tmp25_B.Gain3_lz;

  /* Gain: '<S18>/Gain2' */
  f14tmp25_B.Gain2_ki = f14tmp25_P.Gain2_Gain_eq * f14tmp25_B.Wgustmodel_a1;

  /* TransferFcn: '<S113>/Q-gust model' */
  f14tmp25_B.Qgustmodel_kt = f14tmp25_P.Qgustmodel_D_my*f14tmp25_B.Wgustmodel_a1;
  f14tmp25_B.Qgustmodel_kt += f14tmp25_P.Qgustmodel_C_l*
    f14tmp25_X.Qgustmodel_CSTATE_f;

  /* Gain: '<S18>/Gain1' */
  f14tmp25_B.Gain1_kl = f14tmp25_P.Gain1_Gain_al * f14tmp25_B.Qgustmodel_kt;

  /* Sum: '<S18>/Sum' */
  f14tmp25_B.Sum_pa = f14tmp25_B.Gain2_ki + f14tmp25_B.Gain1_kl;

  /* Sum: '<S111>/Sum2' */
  f14tmp25_B.Sum2_oq = (f14tmp25_B.Gain4_i - f14tmp25_B.Sum_pa) +
    f14tmp25_B.Gain6_c;

  /* TransferFcn: '<S112>/Alpha-sensor Low-pass Filter' */
  f14tmp25_B.AlphasensorLowpassFilter_og =
    f14tmp25_P.AlphasensorLowpassFilter_C_ib*
    f14tmp25_X.AlphasensorLowpassFilter_CST_ba;

  /* TransferFcn: '<S112>/Stick Prefilter' */
  f14tmp25_B.StickPrefilter_ky = f14tmp25_P.StickPrefilter_C_b*
    f14tmp25_X.StickPrefilter_CSTATE_p3;

  /* TransferFcn: '<S112>/Pitch Rate Lead Filter' */
  f14tmp25_B.PitchRateLeadFilter_g0 = f14tmp25_P.PitchRateLeadFilter_D_l*
    f14tmp25_B.TransferFcn1_j;
  f14tmp25_B.PitchRateLeadFilter_g0 += f14tmp25_P.PitchRateLeadFilter_C_m*
    f14tmp25_X.PitchRateLeadFilter_CSTATE_ke;

  /* Gain: '<S112>/Gain2' */
  f14tmp25_B.Gain2_k2 = f14tmp25_P.Gain2_Gain_hk *
    f14tmp25_B.PitchRateLeadFilter_g0;

  /* Gain: '<S112>/Gain3' */
  f14tmp25_B.Gain3_no = f14tmp25_P.Gain3_Gain_i5 *
    f14tmp25_B.AlphasensorLowpassFilter_og;

  /* Sum: '<S112>/Sum1' */
  f14tmp25_B.Sum1_iao = f14tmp25_B.Gain2_k2 + f14tmp25_B.Gain3_no;

  /* Sum: '<S112>/Sum2' */
  f14tmp25_B.Sum2_n = f14tmp25_B.StickPrefilter_ky - f14tmp25_B.Sum1_iao;

  /* Gain: '<S112>/Gain' */
  f14tmp25_B.Gain_lag = f14tmp25_P.Gain_Gain_ma * f14tmp25_B.Sum2_n;

  /* TransferFcn: '<S112>/Proportional plus integral compensator' */
  f14tmp25_B.Proportionalplusintegralcomp_ce =
    f14tmp25_P.Proportionalplusintegralcomp_cm*
    f14tmp25_X.Proportionalplusintegralcompe_c;

  /* Sum: '<S112>/Sum' */
  f14tmp25_B.Sum_em = f14tmp25_B.Gain_lag +
    f14tmp25_B.Proportionalplusintegralcomp_ce;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* RandomNumber: '<S115>/White Noise' */
    f14tmp25_B.WhiteNoise_ae = f14tmp25_DWork.NextOutput_ai;

    /* Gain: '<S115>/Output' */
    f14tmp25_B.Output_dm = f14tmp25_P.Output_Gain_i * f14tmp25_B.WhiteNoise_ae;
  }

  /* TransferFcn: '<S116>/Transfer Fcn.2' */
  f14tmp25_B.TransferFcn2_ja = f14tmp25_P.TransferFcn2_C_lj*
    f14tmp25_X.TransferFcn2_CSTATE_e;

  /* Gain: '<S19>/Gain5' */
  f14tmp25_B.Gain5_k5 = f14tmp25_P.Gain5_Gain_j0 * f14tmp25_B.TransferFcn2_ja;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* Derivative: '<S119>/Derivative' */
  {
    real_T t = f14tmp25_rtM->Timing.t[0];
    real_T timeStampA = f14tmp25_DWork.Derivative_RWORK_k.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative_RWORK_k.TimeStampB;
    real_T *lastU = &f14tmp25_DWork.Derivative_RWORK_k.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp25_B.Derivative_pw = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp25_DWork.Derivative_RWORK_k.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_k.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp25_B.Derivative_pw = (f14tmp25_B.TransferFcn2_ja - *lastU++) /
        deltaT;
    }
  }

  /* TransferFcn: '<S116>/Transfer Fcn.1' */
  f14tmp25_B.TransferFcn1_k = f14tmp25_P.TransferFcn1_C_l*
    f14tmp25_X.TransferFcn1_CSTATE_j;

  /* Derivative: '<S119>/Derivative1' */
  {
    real_T t = f14tmp25_rtM->Timing.t[0];
    real_T timeStampA = f14tmp25_DWork.Derivative1_RWORK_bm.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative1_RWORK_bm.TimeStampB;
    real_T *lastU = &f14tmp25_DWork.Derivative1_RWORK_bm.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp25_B.Derivative1_g = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp25_DWork.Derivative1_RWORK_bm.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_bm.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp25_B.Derivative1_g = (f14tmp25_B.TransferFcn1_k - *lastU++) / deltaT;
    }
  }

  /* Gain: '<S119>/Gain1' */
  f14tmp25_B.Gain1_gao = f14tmp25_P.Gain1_Gain_fm * f14tmp25_B.Derivative1_g;

  /* Product: '<S119>/Product' incorporates:
   *  Constant: '<S119>/Constant'
   */
  f14tmp25_B.Product_hh = f14tmp25_B.TransferFcn1_k *
    f14tmp25_P.Constant_Value_fy;

  /* Sum: '<S119>/Sum1' */
  f14tmp25_B.Sum1_o0i = (f14tmp25_B.Gain1_gao - f14tmp25_B.Derivative_pw) +
    f14tmp25_B.Product_hh;

  /* Gain: '<S119>/Gain2' */
  f14tmp25_B.Gain2_h0 = f14tmp25_P.Gain2_Gain_kz * f14tmp25_B.Sum1_o0i;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* SignalGenerator: '<S19>/Pilot' */
  temp = f14tmp25_P.Pilot_Frequency_io * f14tmp25_rtM->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    f14tmp25_B.Pilot_gs = f14tmp25_P.Pilot_Amplitude_ow;
  } else {
    f14tmp25_B.Pilot_gs = -f14tmp25_P.Pilot_Amplitude_ow;
  }

  /* End of SignalGenerator: '<S19>/Pilot' */

  /* Sum: '<S19>/Sum1' */
  f14tmp25_B.Sum1_dd = f14tmp25_B.Pilot_gs + 0.0;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* TransferFcn: '<S19>/Actuator Model' */
  f14tmp25_B.ActuatorModel_ms = f14tmp25_P.ActuatorModel_C_l*
    f14tmp25_X.ActuatorModel_CSTATE_p;

  /* Gain: '<S116>/Gain3' */
  f14tmp25_B.Gain3_lc = f14tmp25_P.Gain3_Gain_pal * f14tmp25_B.TransferFcn1_k;

  /* Gain: '<S116>/Gain4' */
  f14tmp25_B.Gain4_j = f14tmp25_P.Gain4_Gain_cw * f14tmp25_B.TransferFcn2_ja;

  /* Gain: '<S116>/Gain5' */
  f14tmp25_B.Gain5_pj = f14tmp25_P.Gain5_Gain_j0q * f14tmp25_B.ActuatorModel_ms;

  /* Gain: '<S116>/Gain6' */
  f14tmp25_B.Gain6_fi = f14tmp25_P.Gain6_Gain_j * f14tmp25_B.ActuatorModel_ms;

  /* TransferFcn: '<S118>/W-gust model' */
  f14tmp25_B.Wgustmodel_h = f14tmp25_P.Wgustmodel_C_gf[0]*
    f14tmp25_X.Wgustmodel_CSTATE_k[0]
    + f14tmp25_P.Wgustmodel_C_gf[1]*f14tmp25_X.Wgustmodel_CSTATE_k[1];

  /* Gain: '<S19>/Gain' */
  f14tmp25_B.Gain_od = f14tmp25_P.Gain_Gain_hf * f14tmp25_B.Wgustmodel_h;

  /* Sum: '<S116>/Sum1' */
  f14tmp25_B.Sum1_fl = (f14tmp25_B.Gain5_pj - f14tmp25_B.Gain_od) +
    f14tmp25_B.Gain3_lc;

  /* Gain: '<S19>/Gain2' */
  f14tmp25_B.Gain2_nm = f14tmp25_P.Gain2_Gain_mq * f14tmp25_B.Wgustmodel_h;

  /* TransferFcn: '<S118>/Q-gust model' */
  f14tmp25_B.Qgustmodel_g = f14tmp25_P.Qgustmodel_D_a*f14tmp25_B.Wgustmodel_h;
  f14tmp25_B.Qgustmodel_g += f14tmp25_P.Qgustmodel_C_a*
    f14tmp25_X.Qgustmodel_CSTATE_ad;

  /* Gain: '<S19>/Gain1' */
  f14tmp25_B.Gain1_om = f14tmp25_P.Gain1_Gain_d2 * f14tmp25_B.Qgustmodel_g;

  /* Sum: '<S19>/Sum' */
  f14tmp25_B.Sum_en = f14tmp25_B.Gain2_nm + f14tmp25_B.Gain1_om;

  /* Sum: '<S116>/Sum2' */
  f14tmp25_B.Sum2_cx = (f14tmp25_B.Gain4_j - f14tmp25_B.Sum_en) +
    f14tmp25_B.Gain6_fi;

  /* TransferFcn: '<S117>/Alpha-sensor Low-pass Filter' */
  f14tmp25_B.AlphasensorLowpassFilter_jg =
    f14tmp25_P.AlphasensorLowpassFilter_C_m5*
    f14tmp25_X.AlphasensorLowpassFilter_CSTA_k;

  /* TransferFcn: '<S117>/Stick Prefilter' */
  f14tmp25_B.StickPrefilter_e = f14tmp25_P.StickPrefilter_C_hk*
    f14tmp25_X.StickPrefilter_CSTATE_ju;

  /* TransferFcn: '<S117>/Pitch Rate Lead Filter' */
  f14tmp25_B.PitchRateLeadFilter_ke = f14tmp25_P.PitchRateLeadFilter_D_bv*
    f14tmp25_B.TransferFcn1_k;
  f14tmp25_B.PitchRateLeadFilter_ke += f14tmp25_P.PitchRateLeadFilter_C_bm*
    f14tmp25_X.PitchRateLeadFilter_CSTATE_ez;

  /* Gain: '<S117>/Gain2' */
  f14tmp25_B.Gain2_nh = f14tmp25_P.Gain2_Gain_bf *
    f14tmp25_B.PitchRateLeadFilter_ke;

  /* Gain: '<S117>/Gain3' */
  f14tmp25_B.Gain3_bj = f14tmp25_P.Gain3_Gain_ae *
    f14tmp25_B.AlphasensorLowpassFilter_jg;

  /* Sum: '<S117>/Sum1' */
  f14tmp25_B.Sum1_om = f14tmp25_B.Gain2_nh + f14tmp25_B.Gain3_bj;

  /* Sum: '<S117>/Sum2' */
  f14tmp25_B.Sum2_gm = f14tmp25_B.StickPrefilter_e - f14tmp25_B.Sum1_om;

  /* Gain: '<S117>/Gain' */
  f14tmp25_B.Gain_df = f14tmp25_P.Gain_Gain_f3 * f14tmp25_B.Sum2_gm;

  /* TransferFcn: '<S117>/Proportional plus integral compensator' */
  f14tmp25_B.Proportionalplusintegralcomp_hc =
    f14tmp25_P.Proportionalplusintegralcomp_jf*
    f14tmp25_X.Proportionalplusintegralcomp_jd;

  /* Sum: '<S117>/Sum' */
  f14tmp25_B.Sum_kb = f14tmp25_B.Gain_df +
    f14tmp25_B.Proportionalplusintegralcomp_hc;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* RandomNumber: '<S120>/White Noise' */
    f14tmp25_B.WhiteNoise_p = f14tmp25_DWork.NextOutput_am;

    /* Gain: '<S120>/Output' */
    f14tmp25_B.Output_k4 = f14tmp25_P.Output_Gain_p * f14tmp25_B.WhiteNoise_p;
  }

  /* TransferFcn: '<S121>/Transfer Fcn.2' */
  f14tmp25_B.TransferFcn2_oz = f14tmp25_P.TransferFcn2_C_eq*
    f14tmp25_X.TransferFcn2_CSTATE_kz;

  /* Gain: '<S20>/Gain5' */
  f14tmp25_B.Gain5_cq = f14tmp25_P.Gain5_Gain_f5 * f14tmp25_B.TransferFcn2_oz;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* Derivative: '<S124>/Derivative' */
  {
    real_T t = f14tmp25_rtM->Timing.t[0];
    real_T timeStampA = f14tmp25_DWork.Derivative_RWORK_lc.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative_RWORK_lc.TimeStampB;
    real_T *lastU = &f14tmp25_DWork.Derivative_RWORK_lc.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp25_B.Derivative_fo = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp25_DWork.Derivative_RWORK_lc.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_lc.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp25_B.Derivative_fo = (f14tmp25_B.TransferFcn2_oz - *lastU++) /
        deltaT;
    }
  }

  /* TransferFcn: '<S121>/Transfer Fcn.1' */
  f14tmp25_B.TransferFcn1_iw = f14tmp25_P.TransferFcn1_C_jv*
    f14tmp25_X.TransferFcn1_CSTATE_pe;

  /* Derivative: '<S124>/Derivative1' */
  {
    real_T t = f14tmp25_rtM->Timing.t[0];
    real_T timeStampA = f14tmp25_DWork.Derivative1_RWORK_dt.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative1_RWORK_dt.TimeStampB;
    real_T *lastU = &f14tmp25_DWork.Derivative1_RWORK_dt.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp25_B.Derivative1_i = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp25_DWork.Derivative1_RWORK_dt.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_dt.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp25_B.Derivative1_i = (f14tmp25_B.TransferFcn1_iw - *lastU++) /
        deltaT;
    }
  }

  /* Gain: '<S124>/Gain1' */
  f14tmp25_B.Gain1_omh = f14tmp25_P.Gain1_Gain_mk * f14tmp25_B.Derivative1_i;

  /* Product: '<S124>/Product' incorporates:
   *  Constant: '<S124>/Constant'
   */
  f14tmp25_B.Product_ij = f14tmp25_B.TransferFcn1_iw *
    f14tmp25_P.Constant_Value_p;

  /* Sum: '<S124>/Sum1' */
  f14tmp25_B.Sum1_aj = (f14tmp25_B.Gain1_omh - f14tmp25_B.Derivative_fo) +
    f14tmp25_B.Product_ij;

  /* Gain: '<S124>/Gain2' */
  f14tmp25_B.Gain2_oj = f14tmp25_P.Gain2_Gain_de * f14tmp25_B.Sum1_aj;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* SignalGenerator: '<S20>/Pilot' */
  temp = f14tmp25_P.Pilot_Frequency_a * f14tmp25_rtM->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    f14tmp25_B.Pilot_h3 = f14tmp25_P.Pilot_Amplitude_hj;
  } else {
    f14tmp25_B.Pilot_h3 = -f14tmp25_P.Pilot_Amplitude_hj;
  }

  /* End of SignalGenerator: '<S20>/Pilot' */

  /* Sum: '<S20>/Sum1' */
  f14tmp25_B.Sum1_hc1 = f14tmp25_B.Pilot_h3 + 0.0;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* TransferFcn: '<S20>/Actuator Model' */
  f14tmp25_B.ActuatorModel_b = f14tmp25_P.ActuatorModel_C_a*
    f14tmp25_X.ActuatorModel_CSTATE_ol;

  /* Gain: '<S121>/Gain3' */
  f14tmp25_B.Gain3_as = f14tmp25_P.Gain3_Gain_ai * f14tmp25_B.TransferFcn1_iw;

  /* Gain: '<S121>/Gain4' */
  f14tmp25_B.Gain4_ld = f14tmp25_P.Gain4_Gain_d * f14tmp25_B.TransferFcn2_oz;

  /* Gain: '<S121>/Gain5' */
  f14tmp25_B.Gain5_iu = f14tmp25_P.Gain5_Gain_no * f14tmp25_B.ActuatorModel_b;

  /* Gain: '<S121>/Gain6' */
  f14tmp25_B.Gain6_b5 = f14tmp25_P.Gain6_Gain_nn * f14tmp25_B.ActuatorModel_b;

  /* TransferFcn: '<S123>/W-gust model' */
  f14tmp25_B.Wgustmodel_ox = f14tmp25_P.Wgustmodel_C_pf[0]*
    f14tmp25_X.Wgustmodel_CSTATE_if[0]
    + f14tmp25_P.Wgustmodel_C_pf[1]*f14tmp25_X.Wgustmodel_CSTATE_if[1];

  /* Gain: '<S20>/Gain' */
  f14tmp25_B.Gain_hr = f14tmp25_P.Gain_Gain_c0 * f14tmp25_B.Wgustmodel_ox;

  /* Sum: '<S121>/Sum1' */
  f14tmp25_B.Sum1_gg = (f14tmp25_B.Gain5_iu - f14tmp25_B.Gain_hr) +
    f14tmp25_B.Gain3_as;

  /* Gain: '<S20>/Gain2' */
  f14tmp25_B.Gain2_bh = f14tmp25_P.Gain2_Gain_l0 * f14tmp25_B.Wgustmodel_ox;

  /* TransferFcn: '<S123>/Q-gust model' */
  f14tmp25_B.Qgustmodel_n = f14tmp25_P.Qgustmodel_D_l*f14tmp25_B.Wgustmodel_ox;
  f14tmp25_B.Qgustmodel_n += f14tmp25_P.Qgustmodel_C_c*
    f14tmp25_X.Qgustmodel_CSTATE_mh;

  /* Gain: '<S20>/Gain1' */
  f14tmp25_B.Gain1_lq = f14tmp25_P.Gain1_Gain_a4 * f14tmp25_B.Qgustmodel_n;

  /* Sum: '<S20>/Sum' */
  f14tmp25_B.Sum_kh = f14tmp25_B.Gain2_bh + f14tmp25_B.Gain1_lq;

  /* Sum: '<S121>/Sum2' */
  f14tmp25_B.Sum2_oa = (f14tmp25_B.Gain4_ld - f14tmp25_B.Sum_kh) +
    f14tmp25_B.Gain6_b5;

  /* TransferFcn: '<S122>/Alpha-sensor Low-pass Filter' */
  f14tmp25_B.AlphasensorLowpassFilter_n =
    f14tmp25_P.AlphasensorLowpassFilter_C_es*
    f14tmp25_X.AlphasensorLowpassFilter_CST_ku;

  /* TransferFcn: '<S122>/Stick Prefilter' */
  f14tmp25_B.StickPrefilter_o = f14tmp25_P.StickPrefilter_C_b3*
    f14tmp25_X.StickPrefilter_CSTATE_m;

  /* TransferFcn: '<S122>/Pitch Rate Lead Filter' */
  f14tmp25_B.PitchRateLeadFilter_f1 = f14tmp25_P.PitchRateLeadFilter_D_a*
    f14tmp25_B.TransferFcn1_iw;
  f14tmp25_B.PitchRateLeadFilter_f1 += f14tmp25_P.PitchRateLeadFilter_C_at*
    f14tmp25_X.PitchRateLeadFilter_CSTATE_f0;

  /* Gain: '<S122>/Gain2' */
  f14tmp25_B.Gain2_fs = f14tmp25_P.Gain2_Gain_ne *
    f14tmp25_B.PitchRateLeadFilter_f1;

  /* Gain: '<S122>/Gain3' */
  f14tmp25_B.Gain3_f = f14tmp25_P.Gain3_Gain_h *
    f14tmp25_B.AlphasensorLowpassFilter_n;

  /* Sum: '<S122>/Sum1' */
  f14tmp25_B.Sum1_mx = f14tmp25_B.Gain2_fs + f14tmp25_B.Gain3_f;

  /* Sum: '<S122>/Sum2' */
  f14tmp25_B.Sum2_f5 = f14tmp25_B.StickPrefilter_o - f14tmp25_B.Sum1_mx;

  /* Gain: '<S122>/Gain' */
  f14tmp25_B.Gain_i2 = f14tmp25_P.Gain_Gain_oa * f14tmp25_B.Sum2_f5;

  /* TransferFcn: '<S122>/Proportional plus integral compensator' */
  f14tmp25_B.Proportionalplusintegralcomp_eg =
    f14tmp25_P.Proportionalplusintegralcomp_jp*
    f14tmp25_X.Proportionalplusintegralcomp_kq;

  /* Sum: '<S122>/Sum' */
  f14tmp25_B.Sum_mb = f14tmp25_B.Gain_i2 +
    f14tmp25_B.Proportionalplusintegralcomp_eg;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* RandomNumber: '<S125>/White Noise' */
    f14tmp25_B.WhiteNoise_ms = f14tmp25_DWork.NextOutput_e;

    /* Gain: '<S125>/Output' */
    f14tmp25_B.Output_al = f14tmp25_P.Output_Gain_pk * f14tmp25_B.WhiteNoise_ms;
  }

  /* TransferFcn: '<S126>/Transfer Fcn.2' */
  f14tmp25_B.TransferFcn2_jp = f14tmp25_P.TransferFcn2_C_f*
    f14tmp25_X.TransferFcn2_CSTATE_ar;

  /* Gain: '<S21>/Gain5' */
  f14tmp25_B.Gain5_o4 = f14tmp25_P.Gain5_Gain_hf * f14tmp25_B.TransferFcn2_jp;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* Derivative: '<S129>/Derivative' */
  {
    real_T t = f14tmp25_rtM->Timing.t[0];
    real_T timeStampA = f14tmp25_DWork.Derivative_RWORK_jt.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative_RWORK_jt.TimeStampB;
    real_T *lastU = &f14tmp25_DWork.Derivative_RWORK_jt.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp25_B.Derivative_gv = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp25_DWork.Derivative_RWORK_jt.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_jt.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp25_B.Derivative_gv = (f14tmp25_B.TransferFcn2_jp - *lastU++) /
        deltaT;
    }
  }

  /* TransferFcn: '<S126>/Transfer Fcn.1' */
  f14tmp25_B.TransferFcn1_f = f14tmp25_P.TransferFcn1_C_k*
    f14tmp25_X.TransferFcn1_CSTATE_id;

  /* Derivative: '<S129>/Derivative1' */
  {
    real_T t = f14tmp25_rtM->Timing.t[0];
    real_T timeStampA = f14tmp25_DWork.Derivative1_RWORK_pp.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative1_RWORK_pp.TimeStampB;
    real_T *lastU = &f14tmp25_DWork.Derivative1_RWORK_pp.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp25_B.Derivative1_oy = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp25_DWork.Derivative1_RWORK_pp.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_pp.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp25_B.Derivative1_oy = (f14tmp25_B.TransferFcn1_f - *lastU++) /
        deltaT;
    }
  }

  /* Gain: '<S129>/Gain1' */
  f14tmp25_B.Gain1_ho = f14tmp25_P.Gain1_Gain_ow * f14tmp25_B.Derivative1_oy;

  /* Product: '<S129>/Product' incorporates:
   *  Constant: '<S129>/Constant'
   */
  f14tmp25_B.Product_o = f14tmp25_B.TransferFcn1_f *
    f14tmp25_P.Constant_Value_oq;

  /* Sum: '<S129>/Sum1' */
  f14tmp25_B.Sum1_ap = (f14tmp25_B.Gain1_ho - f14tmp25_B.Derivative_gv) +
    f14tmp25_B.Product_o;

  /* Gain: '<S129>/Gain2' */
  f14tmp25_B.Gain2_di = f14tmp25_P.Gain2_Gain_ba * f14tmp25_B.Sum1_ap;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* SignalGenerator: '<S21>/Pilot' */
  temp = f14tmp25_P.Pilot_Frequency_ik * f14tmp25_rtM->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    f14tmp25_B.Pilot_j = f14tmp25_P.Pilot_Amplitude_cf;
  } else {
    f14tmp25_B.Pilot_j = -f14tmp25_P.Pilot_Amplitude_cf;
  }

  /* End of SignalGenerator: '<S21>/Pilot' */

  /* Sum: '<S21>/Sum1' */
  f14tmp25_B.Sum1_fih = f14tmp25_B.Pilot_j + 0.0;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* TransferFcn: '<S21>/Actuator Model' */
  f14tmp25_B.ActuatorModel_b4 = f14tmp25_P.ActuatorModel_C_j3*
    f14tmp25_X.ActuatorModel_CSTATE_g;

  /* Gain: '<S126>/Gain3' */
  f14tmp25_B.Gain3_c0 = f14tmp25_P.Gain3_Gain_nz * f14tmp25_B.TransferFcn1_f;

  /* Gain: '<S126>/Gain4' */
  f14tmp25_B.Gain4_dh = f14tmp25_P.Gain4_Gain_fw * f14tmp25_B.TransferFcn2_jp;

  /* Gain: '<S126>/Gain5' */
  f14tmp25_B.Gain5_f = f14tmp25_P.Gain5_Gain_i * f14tmp25_B.ActuatorModel_b4;

  /* Gain: '<S126>/Gain6' */
  f14tmp25_B.Gain6_j2 = f14tmp25_P.Gain6_Gain_f2 * f14tmp25_B.ActuatorModel_b4;

  /* TransferFcn: '<S128>/W-gust model' */
  f14tmp25_B.Wgustmodel_o4 = f14tmp25_P.Wgustmodel_C_no[0]*
    f14tmp25_X.Wgustmodel_CSTATE_iv[0]
    + f14tmp25_P.Wgustmodel_C_no[1]*f14tmp25_X.Wgustmodel_CSTATE_iv[1];

  /* Gain: '<S21>/Gain' */
  f14tmp25_B.Gain_i2f = f14tmp25_P.Gain_Gain_de * f14tmp25_B.Wgustmodel_o4;

  /* Sum: '<S126>/Sum1' */
  f14tmp25_B.Sum1_o3 = (f14tmp25_B.Gain5_f - f14tmp25_B.Gain_i2f) +
    f14tmp25_B.Gain3_c0;

  /* Gain: '<S21>/Gain2' */
  f14tmp25_B.Gain2_da = f14tmp25_P.Gain2_Gain_by * f14tmp25_B.Wgustmodel_o4;

  /* TransferFcn: '<S128>/Q-gust model' */
  f14tmp25_B.Qgustmodel_h0 = f14tmp25_P.Qgustmodel_D_g4*f14tmp25_B.Wgustmodel_o4;
  f14tmp25_B.Qgustmodel_h0 += f14tmp25_P.Qgustmodel_C_ci*
    f14tmp25_X.Qgustmodel_CSTATE_ob;

  /* Gain: '<S21>/Gain1' */
  f14tmp25_B.Gain1_br = f14tmp25_P.Gain1_Gain_nw2 * f14tmp25_B.Qgustmodel_h0;

  /* Sum: '<S21>/Sum' */
  f14tmp25_B.Sum_i2 = f14tmp25_B.Gain2_da + f14tmp25_B.Gain1_br;

  /* Sum: '<S126>/Sum2' */
  f14tmp25_B.Sum2_pt = (f14tmp25_B.Gain4_dh - f14tmp25_B.Sum_i2) +
    f14tmp25_B.Gain6_j2;

  /* TransferFcn: '<S127>/Alpha-sensor Low-pass Filter' */
  f14tmp25_B.AlphasensorLowpassFilter_bd =
    f14tmp25_P.AlphasensorLowpassFilter_C_gi*
    f14tmp25_X.AlphasensorLowpassFilter_CST_pj;

  /* TransferFcn: '<S127>/Stick Prefilter' */
  f14tmp25_B.StickPrefilter_ew = f14tmp25_P.StickPrefilter_C_pn*
    f14tmp25_X.StickPrefilter_CSTATE_ah;

  /* TransferFcn: '<S127>/Pitch Rate Lead Filter' */
  f14tmp25_B.PitchRateLeadFilter_h = f14tmp25_P.PitchRateLeadFilter_D_fb*
    f14tmp25_B.TransferFcn1_f;
  f14tmp25_B.PitchRateLeadFilter_h += f14tmp25_P.PitchRateLeadFilter_C_o*
    f14tmp25_X.PitchRateLeadFilter_CSTATE_p;

  /* Gain: '<S127>/Gain2' */
  f14tmp25_B.Gain2_fo = f14tmp25_P.Gain2_Gain_ca *
    f14tmp25_B.PitchRateLeadFilter_h;

  /* Gain: '<S127>/Gain3' */
  f14tmp25_B.Gain3_n1 = f14tmp25_P.Gain3_Gain_g4 *
    f14tmp25_B.AlphasensorLowpassFilter_bd;

  /* Sum: '<S127>/Sum1' */
  f14tmp25_B.Sum1_my = f14tmp25_B.Gain2_fo + f14tmp25_B.Gain3_n1;

  /* Sum: '<S127>/Sum2' */
  f14tmp25_B.Sum2_oh = f14tmp25_B.StickPrefilter_ew - f14tmp25_B.Sum1_my;

  /* Gain: '<S127>/Gain' */
  f14tmp25_B.Gain_ky = f14tmp25_P.Gain_Gain_n * f14tmp25_B.Sum2_oh;

  /* TransferFcn: '<S127>/Proportional plus integral compensator' */
  f14tmp25_B.Proportionalplusintegralcompe_a =
    f14tmp25_P.Proportionalplusintegralcomp_pv*
    f14tmp25_X.Proportionalplusintegralcomp_jw;

  /* Sum: '<S127>/Sum' */
  f14tmp25_B.Sum_cd = f14tmp25_B.Gain_ky +
    f14tmp25_B.Proportionalplusintegralcompe_a;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* RandomNumber: '<S130>/White Noise' */
    f14tmp25_B.WhiteNoise_mt = f14tmp25_DWork.NextOutput_k;

    /* Gain: '<S130>/Output' */
    f14tmp25_B.Output_bc = f14tmp25_P.Output_Gain_cg * f14tmp25_B.WhiteNoise_mt;
  }

  /* TransferFcn: '<S131>/Transfer Fcn.2' */
  f14tmp25_B.TransferFcn2_fa = f14tmp25_P.TransferFcn2_C_m*
    f14tmp25_X.TransferFcn2_CSTATE_lp;

  /* Gain: '<S22>/Gain5' */
  f14tmp25_B.Gain5_et = f14tmp25_P.Gain5_Gain_l3 * f14tmp25_B.TransferFcn2_fa;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* Derivative: '<S134>/Derivative' */
  {
    real_T t = f14tmp25_rtM->Timing.t[0];
    real_T timeStampA = f14tmp25_DWork.Derivative_RWORK_o.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative_RWORK_o.TimeStampB;
    real_T *lastU = &f14tmp25_DWork.Derivative_RWORK_o.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp25_B.Derivative_ps = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp25_DWork.Derivative_RWORK_o.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_o.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp25_B.Derivative_ps = (f14tmp25_B.TransferFcn2_fa - *lastU++) /
        deltaT;
    }
  }

  /* TransferFcn: '<S131>/Transfer Fcn.1' */
  f14tmp25_B.TransferFcn1_nf = f14tmp25_P.TransferFcn1_C_c*
    f14tmp25_X.TransferFcn1_CSTATE_je;

  /* Derivative: '<S134>/Derivative1' */
  {
    real_T t = f14tmp25_rtM->Timing.t[0];
    real_T timeStampA = f14tmp25_DWork.Derivative1_RWORK_eu.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative1_RWORK_eu.TimeStampB;
    real_T *lastU = &f14tmp25_DWork.Derivative1_RWORK_eu.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp25_B.Derivative1_pm = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp25_DWork.Derivative1_RWORK_eu.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_eu.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp25_B.Derivative1_pm = (f14tmp25_B.TransferFcn1_nf - *lastU++) /
        deltaT;
    }
  }

  /* Gain: '<S134>/Gain1' */
  f14tmp25_B.Gain1_e4 = f14tmp25_P.Gain1_Gain_bu * f14tmp25_B.Derivative1_pm;

  /* Product: '<S134>/Product' incorporates:
   *  Constant: '<S134>/Constant'
   */
  f14tmp25_B.Product_ap = f14tmp25_B.TransferFcn1_nf *
    f14tmp25_P.Constant_Value_gf;

  /* Sum: '<S134>/Sum1' */
  f14tmp25_B.Sum1_nb = (f14tmp25_B.Gain1_e4 - f14tmp25_B.Derivative_ps) +
    f14tmp25_B.Product_ap;

  /* Gain: '<S134>/Gain2' */
  f14tmp25_B.Gain2_ne = f14tmp25_P.Gain2_Gain_o * f14tmp25_B.Sum1_nb;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* SignalGenerator: '<S22>/Pilot' */
  temp = f14tmp25_P.Pilot_Frequency_iu * f14tmp25_rtM->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    f14tmp25_B.Pilot_c3 = f14tmp25_P.Pilot_Amplitude_l;
  } else {
    f14tmp25_B.Pilot_c3 = -f14tmp25_P.Pilot_Amplitude_l;
  }

  /* End of SignalGenerator: '<S22>/Pilot' */

  /* Sum: '<S22>/Sum1' */
  f14tmp25_B.Sum1_ec = f14tmp25_B.Pilot_c3 + 0.0;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* TransferFcn: '<S22>/Actuator Model' */
  f14tmp25_B.ActuatorModel_n2 = f14tmp25_P.ActuatorModel_C_g*
    f14tmp25_X.ActuatorModel_CSTATE_fk;

  /* Gain: '<S131>/Gain3' */
  f14tmp25_B.Gain3_c0d = f14tmp25_P.Gain3_Gain_ia * f14tmp25_B.TransferFcn1_nf;

  /* Gain: '<S131>/Gain4' */
  f14tmp25_B.Gain4_a = f14tmp25_P.Gain4_Gain_nt * f14tmp25_B.TransferFcn2_fa;

  /* Gain: '<S131>/Gain5' */
  f14tmp25_B.Gain5_ej = f14tmp25_P.Gain5_Gain_jj * f14tmp25_B.ActuatorModel_n2;

  /* Gain: '<S131>/Gain6' */
  f14tmp25_B.Gain6_cv = f14tmp25_P.Gain6_Gain_jg * f14tmp25_B.ActuatorModel_n2;

  /* TransferFcn: '<S133>/W-gust model' */
  f14tmp25_B.Wgustmodel_fj = f14tmp25_P.Wgustmodel_C_l[0]*
    f14tmp25_X.Wgustmodel_CSTATE_gw[0]
    + f14tmp25_P.Wgustmodel_C_l[1]*f14tmp25_X.Wgustmodel_CSTATE_gw[1];

  /* Gain: '<S22>/Gain' */
  f14tmp25_B.Gain_i1 = f14tmp25_P.Gain_Gain_fq * f14tmp25_B.Wgustmodel_fj;

  /* Sum: '<S131>/Sum1' */
  f14tmp25_B.Sum1_n02 = (f14tmp25_B.Gain5_ej - f14tmp25_B.Gain_i1) +
    f14tmp25_B.Gain3_c0d;

  /* Gain: '<S22>/Gain2' */
  f14tmp25_B.Gain2_fa = f14tmp25_P.Gain2_Gain_ih * f14tmp25_B.Wgustmodel_fj;

  /* TransferFcn: '<S133>/Q-gust model' */
  f14tmp25_B.Qgustmodel_ih = f14tmp25_P.Qgustmodel_D_j*f14tmp25_B.Wgustmodel_fj;
  f14tmp25_B.Qgustmodel_ih += f14tmp25_P.Qgustmodel_C_g*
    f14tmp25_X.Qgustmodel_CSTATE_e;

  /* Gain: '<S22>/Gain1' */
  f14tmp25_B.Gain1_b3 = f14tmp25_P.Gain1_Gain_dk * f14tmp25_B.Qgustmodel_ih;

  /* Sum: '<S22>/Sum' */
  f14tmp25_B.Sum_lm = f14tmp25_B.Gain2_fa + f14tmp25_B.Gain1_b3;

  /* Sum: '<S131>/Sum2' */
  f14tmp25_B.Sum2_bul = (f14tmp25_B.Gain4_a - f14tmp25_B.Sum_lm) +
    f14tmp25_B.Gain6_cv;

  /* TransferFcn: '<S132>/Alpha-sensor Low-pass Filter' */
  f14tmp25_B.AlphasensorLowpassFilter_pq =
    f14tmp25_P.AlphasensorLowpassFilter_C_cs*
    f14tmp25_X.AlphasensorLowpassFilter_CSTA_d;

  /* TransferFcn: '<S132>/Stick Prefilter' */
  f14tmp25_B.StickPrefilter_p = f14tmp25_P.StickPrefilter_C_i*
    f14tmp25_X.StickPrefilter_CSTATE_o;

  /* TransferFcn: '<S132>/Pitch Rate Lead Filter' */
  f14tmp25_B.PitchRateLeadFilter_aj = f14tmp25_P.PitchRateLeadFilter_D_m5*
    f14tmp25_B.TransferFcn1_nf;
  f14tmp25_B.PitchRateLeadFilter_aj += f14tmp25_P.PitchRateLeadFilter_C_ml*
    f14tmp25_X.PitchRateLeadFilter_CSTATE_a;

  /* Gain: '<S132>/Gain2' */
  f14tmp25_B.Gain2_m0 = f14tmp25_P.Gain2_Gain_cat *
    f14tmp25_B.PitchRateLeadFilter_aj;

  /* Gain: '<S132>/Gain3' */
  f14tmp25_B.Gain3_m2 = f14tmp25_P.Gain3_Gain_gk *
    f14tmp25_B.AlphasensorLowpassFilter_pq;

  /* Sum: '<S132>/Sum1' */
  f14tmp25_B.Sum1_ad = f14tmp25_B.Gain2_m0 + f14tmp25_B.Gain3_m2;

  /* Sum: '<S132>/Sum2' */
  f14tmp25_B.Sum2_d = f14tmp25_B.StickPrefilter_p - f14tmp25_B.Sum1_ad;

  /* Gain: '<S132>/Gain' */
  f14tmp25_B.Gain_i21 = f14tmp25_P.Gain_Gain_im * f14tmp25_B.Sum2_d;

  /* TransferFcn: '<S132>/Proportional plus integral compensator' */
  f14tmp25_B.Proportionalplusintegralcomp_le =
    f14tmp25_P.Proportionalplusintegralcomp_mq*
    f14tmp25_X.Proportionalplusintegralcomp_iz;

  /* Sum: '<S132>/Sum' */
  f14tmp25_B.Sum_cy = f14tmp25_B.Gain_i21 +
    f14tmp25_B.Proportionalplusintegralcomp_le;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* RandomNumber: '<S135>/White Noise' */
    f14tmp25_B.WhiteNoise_lu = f14tmp25_DWork.NextOutput_ct;

    /* Gain: '<S135>/Output' */
    f14tmp25_B.Output_hu = f14tmp25_P.Output_Gain_c3 * f14tmp25_B.WhiteNoise_lu;
  }

  /* TransferFcn: '<S136>/Transfer Fcn.2' */
  f14tmp25_B.TransferFcn2_jt = f14tmp25_P.TransferFcn2_C_o*
    f14tmp25_X.TransferFcn2_CSTATE_aw;

  /* Gain: '<S23>/Gain5' */
  f14tmp25_B.Gain5_mu = f14tmp25_P.Gain5_Gain_ld * f14tmp25_B.TransferFcn2_jt;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* Derivative: '<S139>/Derivative' */
  {
    real_T t = f14tmp25_rtM->Timing.t[0];
    real_T timeStampA = f14tmp25_DWork.Derivative_RWORK_o0.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative_RWORK_o0.TimeStampB;
    real_T *lastU = &f14tmp25_DWork.Derivative_RWORK_o0.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp25_B.Derivative_e = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp25_DWork.Derivative_RWORK_o0.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_o0.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp25_B.Derivative_e = (f14tmp25_B.TransferFcn2_jt - *lastU++) / deltaT;
    }
  }

  /* TransferFcn: '<S136>/Transfer Fcn.1' */
  f14tmp25_B.TransferFcn1_d = f14tmp25_P.TransferFcn1_C_g1*
    f14tmp25_X.TransferFcn1_CSTATE_be;

  /* Derivative: '<S139>/Derivative1' */
  {
    real_T t = f14tmp25_rtM->Timing.t[0];
    real_T timeStampA = f14tmp25_DWork.Derivative1_RWORK_j.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative1_RWORK_j.TimeStampB;
    real_T *lastU = &f14tmp25_DWork.Derivative1_RWORK_j.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp25_B.Derivative1_n2 = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp25_DWork.Derivative1_RWORK_j.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_j.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp25_B.Derivative1_n2 = (f14tmp25_B.TransferFcn1_d - *lastU++) /
        deltaT;
    }
  }

  /* Gain: '<S139>/Gain1' */
  f14tmp25_B.Gain1_m4 = f14tmp25_P.Gain1_Gain_dw * f14tmp25_B.Derivative1_n2;

  /* Product: '<S139>/Product' incorporates:
   *  Constant: '<S139>/Constant'
   */
  f14tmp25_B.Product_b2 = f14tmp25_B.TransferFcn1_d *
    f14tmp25_P.Constant_Value_f0;

  /* Sum: '<S139>/Sum1' */
  f14tmp25_B.Sum1_myl = (f14tmp25_B.Gain1_m4 - f14tmp25_B.Derivative_e) +
    f14tmp25_B.Product_b2;

  /* Gain: '<S139>/Gain2' */
  f14tmp25_B.Gain2_br = f14tmp25_P.Gain2_Gain_ap * f14tmp25_B.Sum1_myl;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* SignalGenerator: '<S23>/Pilot' */
  temp = f14tmp25_P.Pilot_Frequency_ol * f14tmp25_rtM->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    f14tmp25_B.Pilot_n = f14tmp25_P.Pilot_Amplitude_d2;
  } else {
    f14tmp25_B.Pilot_n = -f14tmp25_P.Pilot_Amplitude_d2;
  }

  /* End of SignalGenerator: '<S23>/Pilot' */

  /* Sum: '<S23>/Sum1' */
  f14tmp25_B.Sum1_ni = f14tmp25_B.Pilot_n + 0.0;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* TransferFcn: '<S23>/Actuator Model' */
  f14tmp25_B.ActuatorModel_n3 = f14tmp25_P.ActuatorModel_C_d3*
    f14tmp25_X.ActuatorModel_CSTATE_pq;

  /* Gain: '<S136>/Gain3' */
  f14tmp25_B.Gain3_bt = f14tmp25_P.Gain3_Gain_hy * f14tmp25_B.TransferFcn1_d;

  /* Gain: '<S136>/Gain4' */
  f14tmp25_B.Gain4_kk = f14tmp25_P.Gain4_Gain_m * f14tmp25_B.TransferFcn2_jt;

  /* Gain: '<S136>/Gain5' */
  f14tmp25_B.Gain5_nl = f14tmp25_P.Gain5_Gain_dk * f14tmp25_B.ActuatorModel_n3;

  /* Gain: '<S136>/Gain6' */
  f14tmp25_B.Gain6_ax = f14tmp25_P.Gain6_Gain_eb * f14tmp25_B.ActuatorModel_n3;

  /* TransferFcn: '<S138>/W-gust model' */
  f14tmp25_B.Wgustmodel_hc = f14tmp25_P.Wgustmodel_C_b[0]*
    f14tmp25_X.Wgustmodel_CSTATE_c[0]
    + f14tmp25_P.Wgustmodel_C_b[1]*f14tmp25_X.Wgustmodel_CSTATE_c[1];

  /* Gain: '<S23>/Gain' */
  f14tmp25_B.Gain_kd = f14tmp25_P.Gain_Gain_ae * f14tmp25_B.Wgustmodel_hc;

  /* Sum: '<S136>/Sum1' */
  f14tmp25_B.Sum1_m5 = (f14tmp25_B.Gain5_nl - f14tmp25_B.Gain_kd) +
    f14tmp25_B.Gain3_bt;

  /* Gain: '<S23>/Gain2' */
  f14tmp25_B.Gain2_fh = f14tmp25_P.Gain2_Gain_eg * f14tmp25_B.Wgustmodel_hc;

  /* TransferFcn: '<S138>/Q-gust model' */
  f14tmp25_B.Qgustmodel_ao = f14tmp25_P.Qgustmodel_D_e*f14tmp25_B.Wgustmodel_hc;
  f14tmp25_B.Qgustmodel_ao += f14tmp25_P.Qgustmodel_C_ic*
    f14tmp25_X.Qgustmodel_CSTATE_fh;

  /* Gain: '<S23>/Gain1' */
  f14tmp25_B.Gain1_j2 = f14tmp25_P.Gain1_Gain_ji * f14tmp25_B.Qgustmodel_ao;

  /* Sum: '<S23>/Sum' */
  f14tmp25_B.Sum_le = f14tmp25_B.Gain2_fh + f14tmp25_B.Gain1_j2;

  /* Sum: '<S136>/Sum2' */
  f14tmp25_B.Sum2_m4 = (f14tmp25_B.Gain4_kk - f14tmp25_B.Sum_le) +
    f14tmp25_B.Gain6_ax;

  /* TransferFcn: '<S137>/Alpha-sensor Low-pass Filter' */
  f14tmp25_B.AlphasensorLowpassFilter_na =
    f14tmp25_P.AlphasensorLowpassFilter_C_p*
    f14tmp25_X.AlphasensorLowpassFilter_CST_b1;

  /* TransferFcn: '<S137>/Stick Prefilter' */
  f14tmp25_B.StickPrefilter_mu = f14tmp25_P.StickPrefilter_C_l*
    f14tmp25_X.StickPrefilter_CSTATE_p2;

  /* TransferFcn: '<S137>/Pitch Rate Lead Filter' */
  f14tmp25_B.PitchRateLeadFilter_it = f14tmp25_P.PitchRateLeadFilter_D_bq*
    f14tmp25_B.TransferFcn1_d;
  f14tmp25_B.PitchRateLeadFilter_it += f14tmp25_P.PitchRateLeadFilter_C_j*
    f14tmp25_X.PitchRateLeadFilter_CSTATE_au;

  /* Gain: '<S137>/Gain2' */
  f14tmp25_B.Gain2_ju = f14tmp25_P.Gain2_Gain_a5 *
    f14tmp25_B.PitchRateLeadFilter_it;

  /* Gain: '<S137>/Gain3' */
  f14tmp25_B.Gain3_gr = f14tmp25_P.Gain3_Gain_dg *
    f14tmp25_B.AlphasensorLowpassFilter_na;

  /* Sum: '<S137>/Sum1' */
  f14tmp25_B.Sum1_aa = f14tmp25_B.Gain2_ju + f14tmp25_B.Gain3_gr;

  /* Sum: '<S137>/Sum2' */
  f14tmp25_B.Sum2_h = f14tmp25_B.StickPrefilter_mu - f14tmp25_B.Sum1_aa;

  /* Gain: '<S137>/Gain' */
  f14tmp25_B.Gain_dr = f14tmp25_P.Gain_Gain_d3 * f14tmp25_B.Sum2_h;

  /* TransferFcn: '<S137>/Proportional plus integral compensator' */
  f14tmp25_B.Proportionalplusintegralcomp_aj =
    f14tmp25_P.Proportionalplusintegralcomp_a4*
    f14tmp25_X.Proportionalplusintegralcomp_nm;

  /* Sum: '<S137>/Sum' */
  f14tmp25_B.Sum_nsk = f14tmp25_B.Gain_dr +
    f14tmp25_B.Proportionalplusintegralcomp_aj;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* RandomNumber: '<S140>/White Noise' */
    f14tmp25_B.WhiteNoise_l4 = f14tmp25_DWork.NextOutput_d2;

    /* Gain: '<S140>/Output' */
    f14tmp25_B.Output_p = f14tmp25_P.Output_Gain_c3r * f14tmp25_B.WhiteNoise_l4;
  }

  /* TransferFcn: '<S141>/Transfer Fcn.2' */
  f14tmp25_B.TransferFcn2_mc = f14tmp25_P.TransferFcn2_C_am*
    f14tmp25_X.TransferFcn2_CSTATE_ms;

  /* Gain: '<S24>/Gain5' */
  f14tmp25_B.Gain5_m5 = f14tmp25_P.Gain5_Gain_ev * f14tmp25_B.TransferFcn2_mc;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* Derivative: '<S144>/Derivative' */
  {
    real_T t = f14tmp25_rtM->Timing.t[0];
    real_T timeStampA = f14tmp25_DWork.Derivative_RWORK_p5.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative_RWORK_p5.TimeStampB;
    real_T *lastU = &f14tmp25_DWork.Derivative_RWORK_p5.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp25_B.Derivative_by = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp25_DWork.Derivative_RWORK_p5.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_p5.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp25_B.Derivative_by = (f14tmp25_B.TransferFcn2_mc - *lastU++) /
        deltaT;
    }
  }

  /* TransferFcn: '<S141>/Transfer Fcn.1' */
  f14tmp25_B.TransferFcn1_l = f14tmp25_P.TransferFcn1_C_gr*
    f14tmp25_X.TransferFcn1_CSTATE_nz;

  /* Derivative: '<S144>/Derivative1' */
  {
    real_T t = f14tmp25_rtM->Timing.t[0];
    real_T timeStampA = f14tmp25_DWork.Derivative1_RWORK_dy.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative1_RWORK_dy.TimeStampB;
    real_T *lastU = &f14tmp25_DWork.Derivative1_RWORK_dy.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp25_B.Derivative1_cp = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp25_DWork.Derivative1_RWORK_dy.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_dy.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp25_B.Derivative1_cp = (f14tmp25_B.TransferFcn1_l - *lastU++) /
        deltaT;
    }
  }

  /* Gain: '<S144>/Gain1' */
  f14tmp25_B.Gain1_ld = f14tmp25_P.Gain1_Gain_ge * f14tmp25_B.Derivative1_cp;

  /* Product: '<S144>/Product' incorporates:
   *  Constant: '<S144>/Constant'
   */
  f14tmp25_B.Product_a0 = f14tmp25_B.TransferFcn1_l *
    f14tmp25_P.Constant_Value_e;

  /* Sum: '<S144>/Sum1' */
  f14tmp25_B.Sum1_jv = (f14tmp25_B.Gain1_ld - f14tmp25_B.Derivative_by) +
    f14tmp25_B.Product_a0;

  /* Gain: '<S144>/Gain2' */
  f14tmp25_B.Gain2_ig = f14tmp25_P.Gain2_Gain_jn * f14tmp25_B.Sum1_jv;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* SignalGenerator: '<S24>/Pilot' */
  temp = f14tmp25_P.Pilot_Frequency_ay * f14tmp25_rtM->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    f14tmp25_B.Pilot_ff = f14tmp25_P.Pilot_Amplitude_g;
  } else {
    f14tmp25_B.Pilot_ff = -f14tmp25_P.Pilot_Amplitude_g;
  }

  /* End of SignalGenerator: '<S24>/Pilot' */

  /* Sum: '<S24>/Sum1' */
  f14tmp25_B.Sum1_jty = f14tmp25_B.Pilot_ff + 0.0;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* TransferFcn: '<S24>/Actuator Model' */
  f14tmp25_B.ActuatorModel_da = f14tmp25_P.ActuatorModel_C_ka*
    f14tmp25_X.ActuatorModel_CSTATE_fb;

  /* Gain: '<S141>/Gain3' */
  f14tmp25_B.Gain3_nn = f14tmp25_P.Gain3_Gain_on * f14tmp25_B.TransferFcn1_l;

  /* Gain: '<S141>/Gain4' */
  f14tmp25_B.Gain4_jo = f14tmp25_P.Gain4_Gain_k * f14tmp25_B.TransferFcn2_mc;

  /* Gain: '<S141>/Gain5' */
  f14tmp25_B.Gain5_ky = f14tmp25_P.Gain5_Gain_oik * f14tmp25_B.ActuatorModel_da;

  /* Gain: '<S141>/Gain6' */
  f14tmp25_B.Gain6_ii = f14tmp25_P.Gain6_Gain_ep * f14tmp25_B.ActuatorModel_da;

  /* TransferFcn: '<S143>/W-gust model' */
  f14tmp25_B.Wgustmodel_il = f14tmp25_P.Wgustmodel_C_aa[0]*
    f14tmp25_X.Wgustmodel_CSTATE_h3[0]
    + f14tmp25_P.Wgustmodel_C_aa[1]*f14tmp25_X.Wgustmodel_CSTATE_h3[1];

  /* Gain: '<S24>/Gain' */
  f14tmp25_B.Gain_l3 = f14tmp25_P.Gain_Gain_nx * f14tmp25_B.Wgustmodel_il;

  /* Sum: '<S141>/Sum1' */
  f14tmp25_B.Sum1_flb = (f14tmp25_B.Gain5_ky - f14tmp25_B.Gain_l3) +
    f14tmp25_B.Gain3_nn;

  /* Gain: '<S24>/Gain2' */
  f14tmp25_B.Gain2_jn = f14tmp25_P.Gain2_Gain_j4 * f14tmp25_B.Wgustmodel_il;

  /* TransferFcn: '<S143>/Q-gust model' */
  f14tmp25_B.Qgustmodel_lq = f14tmp25_P.Qgustmodel_D_ay*f14tmp25_B.Wgustmodel_il;
  f14tmp25_B.Qgustmodel_lq += f14tmp25_P.Qgustmodel_C_az*
    f14tmp25_X.Qgustmodel_CSTATE_c;

  /* Gain: '<S24>/Gain1' */
  f14tmp25_B.Gain1_g4a = f14tmp25_P.Gain1_Gain_oq * f14tmp25_B.Qgustmodel_lq;

  /* Sum: '<S24>/Sum' */
  f14tmp25_B.Sum_ah = f14tmp25_B.Gain2_jn + f14tmp25_B.Gain1_g4a;

  /* Sum: '<S141>/Sum2' */
  f14tmp25_B.Sum2_p1 = (f14tmp25_B.Gain4_jo - f14tmp25_B.Sum_ah) +
    f14tmp25_B.Gain6_ii;

  /* TransferFcn: '<S142>/Alpha-sensor Low-pass Filter' */
  f14tmp25_B.AlphasensorLowpassFilter_d =
    f14tmp25_P.AlphasensorLowpassFilter_C_pz*
    f14tmp25_X.AlphasensorLowpassFilter_CST_jw;

  /* TransferFcn: '<S142>/Stick Prefilter' */
  f14tmp25_B.StickPrefilter_ok = f14tmp25_P.StickPrefilter_C_n*
    f14tmp25_X.StickPrefilter_CSTATE_ns;

  /* TransferFcn: '<S142>/Pitch Rate Lead Filter' */
  f14tmp25_B.PitchRateLeadFilter_o = f14tmp25_P.PitchRateLeadFilter_D_i0*
    f14tmp25_B.TransferFcn1_l;
  f14tmp25_B.PitchRateLeadFilter_o += f14tmp25_P.PitchRateLeadFilter_C_em*
    f14tmp25_X.PitchRateLeadFilter_CSTATE_ds;

  /* Gain: '<S142>/Gain2' */
  f14tmp25_B.Gain2_elw = f14tmp25_P.Gain2_Gain_az *
    f14tmp25_B.PitchRateLeadFilter_o;

  /* Gain: '<S142>/Gain3' */
  f14tmp25_B.Gain3_ae = f14tmp25_P.Gain3_Gain_dp *
    f14tmp25_B.AlphasensorLowpassFilter_d;

  /* Sum: '<S142>/Sum1' */
  f14tmp25_B.Sum1_lg = f14tmp25_B.Gain2_elw + f14tmp25_B.Gain3_ae;

  /* Sum: '<S142>/Sum2' */
  f14tmp25_B.Sum2_fw = f14tmp25_B.StickPrefilter_ok - f14tmp25_B.Sum1_lg;

  /* Gain: '<S142>/Gain' */
  f14tmp25_B.Gain_nq = f14tmp25_P.Gain_Gain_ok * f14tmp25_B.Sum2_fw;

  /* TransferFcn: '<S142>/Proportional plus integral compensator' */
  f14tmp25_B.Proportionalplusintegralcomp_ap =
    f14tmp25_P.Proportionalplusintegralcomp_fa*
    f14tmp25_X.Proportionalplusintegralcompe_a;

  /* Sum: '<S142>/Sum' */
  f14tmp25_B.Sum_lq = f14tmp25_B.Gain_nq +
    f14tmp25_B.Proportionalplusintegralcomp_ap;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* RandomNumber: '<S145>/White Noise' */
    f14tmp25_B.WhiteNoise_lx = f14tmp25_DWork.NextOutput_g3;

    /* Gain: '<S145>/Output' */
    f14tmp25_B.Output_o4 = f14tmp25_P.Output_Gain_cw * f14tmp25_B.WhiteNoise_lx;
  }

  /* TransferFcn: '<S146>/Transfer Fcn.2' */
  f14tmp25_B.TransferFcn2_k = f14tmp25_P.TransferFcn2_C_hd*
    f14tmp25_X.TransferFcn2_CSTATE_bk;

  /* Gain: '<S25>/Gain5' */
  f14tmp25_B.Gain5_cl = f14tmp25_P.Gain5_Gain_cwc * f14tmp25_B.TransferFcn2_k;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* Derivative: '<S149>/Derivative' */
  {
    real_T t = f14tmp25_rtM->Timing.t[0];
    real_T timeStampA = f14tmp25_DWork.Derivative_RWORK_ch.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative_RWORK_ch.TimeStampB;
    real_T *lastU = &f14tmp25_DWork.Derivative_RWORK_ch.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp25_B.Derivative_c = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp25_DWork.Derivative_RWORK_ch.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_ch.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp25_B.Derivative_c = (f14tmp25_B.TransferFcn2_k - *lastU++) / deltaT;
    }
  }

  /* TransferFcn: '<S146>/Transfer Fcn.1' */
  f14tmp25_B.TransferFcn1_jd = f14tmp25_P.TransferFcn1_C_lp*
    f14tmp25_X.TransferFcn1_CSTATE_gr;

  /* Derivative: '<S149>/Derivative1' */
  {
    real_T t = f14tmp25_rtM->Timing.t[0];
    real_T timeStampA = f14tmp25_DWork.Derivative1_RWORK_n.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative1_RWORK_n.TimeStampB;
    real_T *lastU = &f14tmp25_DWork.Derivative1_RWORK_n.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp25_B.Derivative1_lq = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp25_DWork.Derivative1_RWORK_n.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_n.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp25_B.Derivative1_lq = (f14tmp25_B.TransferFcn1_jd - *lastU++) /
        deltaT;
    }
  }

  /* Gain: '<S149>/Gain1' */
  f14tmp25_B.Gain1_bh = f14tmp25_P.Gain1_Gain_j1 * f14tmp25_B.Derivative1_lq;

  /* Product: '<S149>/Product' incorporates:
   *  Constant: '<S149>/Constant'
   */
  f14tmp25_B.Product_fg = f14tmp25_B.TransferFcn1_jd *
    f14tmp25_P.Constant_Value_dx;

  /* Sum: '<S149>/Sum1' */
  f14tmp25_B.Sum1_a3 = (f14tmp25_B.Gain1_bh - f14tmp25_B.Derivative_c) +
    f14tmp25_B.Product_fg;

  /* Gain: '<S149>/Gain2' */
  f14tmp25_B.Gain2_c = f14tmp25_P.Gain2_Gain_fd * f14tmp25_B.Sum1_a3;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* SignalGenerator: '<S25>/Pilot' */
  temp = f14tmp25_P.Pilot_Frequency_ax * f14tmp25_rtM->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    f14tmp25_B.Pilot_ci = f14tmp25_P.Pilot_Amplitude_ob;
  } else {
    f14tmp25_B.Pilot_ci = -f14tmp25_P.Pilot_Amplitude_ob;
  }

  /* End of SignalGenerator: '<S25>/Pilot' */

  /* Sum: '<S25>/Sum1' */
  f14tmp25_B.Sum1_oz = f14tmp25_B.Pilot_ci + 0.0;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* TransferFcn: '<S25>/Actuator Model' */
  f14tmp25_B.ActuatorModel_h = f14tmp25_P.ActuatorModel_C_e*
    f14tmp25_X.ActuatorModel_CSTATE_iv;

  /* Gain: '<S146>/Gain3' */
  f14tmp25_B.Gain3_g4 = f14tmp25_P.Gain3_Gain_gx * f14tmp25_B.TransferFcn1_jd;

  /* Gain: '<S146>/Gain4' */
  f14tmp25_B.Gain4_lt = f14tmp25_P.Gain4_Gain_a * f14tmp25_B.TransferFcn2_k;

  /* Gain: '<S146>/Gain5' */
  f14tmp25_B.Gain5_jr = f14tmp25_P.Gain5_Gain_fc * f14tmp25_B.ActuatorModel_h;

  /* Gain: '<S146>/Gain6' */
  f14tmp25_B.Gain6_pl = f14tmp25_P.Gain6_Gain_l * f14tmp25_B.ActuatorModel_h;

  /* TransferFcn: '<S148>/W-gust model' */
  f14tmp25_B.Wgustmodel_k = f14tmp25_P.Wgustmodel_C_n5[0]*
    f14tmp25_X.Wgustmodel_CSTATE_b[0]
    + f14tmp25_P.Wgustmodel_C_n5[1]*f14tmp25_X.Wgustmodel_CSTATE_b[1];

  /* Gain: '<S25>/Gain' */
  f14tmp25_B.Gain_ih = f14tmp25_P.Gain_Gain_bj * f14tmp25_B.Wgustmodel_k;

  /* Sum: '<S146>/Sum1' */
  f14tmp25_B.Sum1_pn = (f14tmp25_B.Gain5_jr - f14tmp25_B.Gain_ih) +
    f14tmp25_B.Gain3_g4;

  /* Gain: '<S25>/Gain2' */
  f14tmp25_B.Gain2_ah = f14tmp25_P.Gain2_Gain_dz * f14tmp25_B.Wgustmodel_k;

  /* TransferFcn: '<S148>/Q-gust model' */
  f14tmp25_B.Qgustmodel_gx = f14tmp25_P.Qgustmodel_D_gi*f14tmp25_B.Wgustmodel_k;
  f14tmp25_B.Qgustmodel_gx += f14tmp25_P.Qgustmodel_C_jg*
    f14tmp25_X.Qgustmodel_CSTATE_lb;

  /* Gain: '<S25>/Gain1' */
  f14tmp25_B.Gain1_hc = f14tmp25_P.Gain1_Gain_pq * f14tmp25_B.Qgustmodel_gx;

  /* Sum: '<S25>/Sum' */
  f14tmp25_B.Sum_ob = f14tmp25_B.Gain2_ah + f14tmp25_B.Gain1_hc;

  /* Sum: '<S146>/Sum2' */
  f14tmp25_B.Sum2_hz = (f14tmp25_B.Gain4_lt - f14tmp25_B.Sum_ob) +
    f14tmp25_B.Gain6_pl;

  /* TransferFcn: '<S147>/Alpha-sensor Low-pass Filter' */
  f14tmp25_B.AlphasensorLowpassFilter_kr =
    f14tmp25_P.AlphasensorLowpassFilter_C_es0*
    f14tmp25_X.AlphasensorLowpassFilter_CST_iy;

  /* TransferFcn: '<S147>/Stick Prefilter' */
  f14tmp25_B.StickPrefilter_pi = f14tmp25_P.StickPrefilter_C_pz*
    f14tmp25_X.StickPrefilter_CSTATE_pb;

  /* TransferFcn: '<S147>/Pitch Rate Lead Filter' */
  f14tmp25_B.PitchRateLeadFilter_ik = f14tmp25_P.PitchRateLeadFilter_D_bk*
    f14tmp25_B.TransferFcn1_jd;
  f14tmp25_B.PitchRateLeadFilter_ik += f14tmp25_P.PitchRateLeadFilter_C_hc*
    f14tmp25_X.PitchRateLeadFilter_CSTATE_ak;

  /* Gain: '<S147>/Gain2' */
  f14tmp25_B.Gain2_id = f14tmp25_P.Gain2_Gain_iiy *
    f14tmp25_B.PitchRateLeadFilter_ik;

  /* Gain: '<S147>/Gain3' */
  f14tmp25_B.Gain3_oq = f14tmp25_P.Gain3_Gain_dg2 *
    f14tmp25_B.AlphasensorLowpassFilter_kr;

  /* Sum: '<S147>/Sum1' */
  f14tmp25_B.Sum1_dg = f14tmp25_B.Gain2_id + f14tmp25_B.Gain3_oq;

  /* Sum: '<S147>/Sum2' */
  f14tmp25_B.Sum2_jy = f14tmp25_B.StickPrefilter_pi - f14tmp25_B.Sum1_dg;

  /* Gain: '<S147>/Gain' */
  f14tmp25_B.Gain_er = f14tmp25_P.Gain_Gain_ni * f14tmp25_B.Sum2_jy;

  /* TransferFcn: '<S147>/Proportional plus integral compensator' */
  f14tmp25_B.Proportionalplusintegralcomp_gn =
    f14tmp25_P.Proportionalplusintegralcomp_gb*
    f14tmp25_X.Proportionalplusintegralcomp_ab;

  /* Sum: '<S147>/Sum' */
  f14tmp25_B.Sum_j = f14tmp25_B.Gain_er +
    f14tmp25_B.Proportionalplusintegralcomp_gn;
  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* RandomNumber: '<S150>/White Noise' */
    f14tmp25_B.WhiteNoise_fe = f14tmp25_DWork.NextOutput_ip;

    /* Gain: '<S150>/Output' */
    f14tmp25_B.Output_dn = f14tmp25_P.Output_Gain_o * f14tmp25_B.WhiteNoise_fe;
  }
}

/* Model update function */
void f14tmp25_update(void)
{
  /* Update for Derivative: '<S29>/Derivative' */
  {
    real_T timeStampA = f14tmp25_DWork.Derivative_RWORK.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative_RWORK.TimeStampB;
    real_T* lastTime = &f14tmp25_DWork.Derivative_RWORK.TimeStampA;
    real_T* lastU = &f14tmp25_DWork.Derivative_RWORK.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp25_DWork.Derivative_RWORK.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp25_DWork.Derivative_RWORK.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp25_rtM->Timing.t[0];
    *lastU++ = f14tmp25_B.TransferFcn2;
  }

  /* Update for Derivative: '<S29>/Derivative1' */
  {
    real_T timeStampA = f14tmp25_DWork.Derivative1_RWORK.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative1_RWORK.TimeStampB;
    real_T* lastTime = &f14tmp25_DWork.Derivative1_RWORK.TimeStampA;
    real_T* lastU = &f14tmp25_DWork.Derivative1_RWORK.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp25_DWork.Derivative1_RWORK.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp25_DWork.Derivative1_RWORK.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp25_rtM->Timing.t[0];
    *lastU++ = f14tmp25_B.TransferFcn1;
  }

  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* Update for RandomNumber: '<S30>/White Noise' */
    f14tmp25_DWork.NextOutput = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp25_DWork.RandSeed) * f14tmp25_P.WhiteNoise_StdDev +
      f14tmp25_P.WhiteNoise_Mean;
  }

  /* Update for Derivative: '<S34>/Derivative' */
  {
    real_T timeStampA = f14tmp25_DWork.Derivative_RWORK_f.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative_RWORK_f.TimeStampB;
    real_T* lastTime = &f14tmp25_DWork.Derivative_RWORK_f.TimeStampA;
    real_T* lastU = &f14tmp25_DWork.Derivative_RWORK_f.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp25_DWork.Derivative_RWORK_f.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_f.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp25_DWork.Derivative_RWORK_f.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_f.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp25_rtM->Timing.t[0];
    *lastU++ = f14tmp25_B.TransferFcn2_b;
  }

  /* Update for Derivative: '<S34>/Derivative1' */
  {
    real_T timeStampA = f14tmp25_DWork.Derivative1_RWORK_o.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative1_RWORK_o.TimeStampB;
    real_T* lastTime = &f14tmp25_DWork.Derivative1_RWORK_o.TimeStampA;
    real_T* lastU = &f14tmp25_DWork.Derivative1_RWORK_o.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp25_DWork.Derivative1_RWORK_o.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_o.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp25_DWork.Derivative1_RWORK_o.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_o.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp25_rtM->Timing.t[0];
    *lastU++ = f14tmp25_B.TransferFcn1_a;
  }

  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* Update for RandomNumber: '<S35>/White Noise' */
    f14tmp25_DWork.NextOutput_f = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp25_DWork.RandSeed_n) * f14tmp25_P.WhiteNoise_StdDev_n +
      f14tmp25_P.WhiteNoise_Mean_j;
  }

  /* Update for Derivative: '<S39>/Derivative' */
  {
    real_T timeStampA = f14tmp25_DWork.Derivative_RWORK_p.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative_RWORK_p.TimeStampB;
    real_T* lastTime = &f14tmp25_DWork.Derivative_RWORK_p.TimeStampA;
    real_T* lastU = &f14tmp25_DWork.Derivative_RWORK_p.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp25_DWork.Derivative_RWORK_p.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_p.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp25_DWork.Derivative_RWORK_p.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_p.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp25_rtM->Timing.t[0];
    *lastU++ = f14tmp25_B.TransferFcn2_d;
  }

  /* Update for Derivative: '<S39>/Derivative1' */
  {
    real_T timeStampA = f14tmp25_DWork.Derivative1_RWORK_c.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative1_RWORK_c.TimeStampB;
    real_T* lastTime = &f14tmp25_DWork.Derivative1_RWORK_c.TimeStampA;
    real_T* lastU = &f14tmp25_DWork.Derivative1_RWORK_c.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp25_DWork.Derivative1_RWORK_c.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_c.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp25_DWork.Derivative1_RWORK_c.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_c.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp25_rtM->Timing.t[0];
    *lastU++ = f14tmp25_B.TransferFcn1_b;
  }

  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* Update for RandomNumber: '<S40>/White Noise' */
    f14tmp25_DWork.NextOutput_n = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp25_DWork.RandSeed_b) * f14tmp25_P.WhiteNoise_StdDev_e +
      f14tmp25_P.WhiteNoise_Mean_n;
  }

  /* Update for Derivative: '<S44>/Derivative' */
  {
    real_T timeStampA = f14tmp25_DWork.Derivative_RWORK_c.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative_RWORK_c.TimeStampB;
    real_T* lastTime = &f14tmp25_DWork.Derivative_RWORK_c.TimeStampA;
    real_T* lastU = &f14tmp25_DWork.Derivative_RWORK_c.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp25_DWork.Derivative_RWORK_c.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_c.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp25_DWork.Derivative_RWORK_c.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_c.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp25_rtM->Timing.t[0];
    *lastU++ = f14tmp25_B.TransferFcn2_e;
  }

  /* Update for Derivative: '<S44>/Derivative1' */
  {
    real_T timeStampA = f14tmp25_DWork.Derivative1_RWORK_d.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative1_RWORK_d.TimeStampB;
    real_T* lastTime = &f14tmp25_DWork.Derivative1_RWORK_d.TimeStampA;
    real_T* lastU = &f14tmp25_DWork.Derivative1_RWORK_d.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp25_DWork.Derivative1_RWORK_d.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_d.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp25_DWork.Derivative1_RWORK_d.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_d.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp25_rtM->Timing.t[0];
    *lastU++ = f14tmp25_B.TransferFcn1_o;
  }

  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* Update for RandomNumber: '<S45>/White Noise' */
    f14tmp25_DWork.NextOutput_g = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp25_DWork.RandSeed_c) * f14tmp25_P.WhiteNoise_StdDev_l +
      f14tmp25_P.WhiteNoise_Mean_c;
  }

  /* Update for Derivative: '<S49>/Derivative' */
  {
    real_T timeStampA = f14tmp25_DWork.Derivative_RWORK_j.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative_RWORK_j.TimeStampB;
    real_T* lastTime = &f14tmp25_DWork.Derivative_RWORK_j.TimeStampA;
    real_T* lastU = &f14tmp25_DWork.Derivative_RWORK_j.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp25_DWork.Derivative_RWORK_j.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_j.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp25_DWork.Derivative_RWORK_j.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_j.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp25_rtM->Timing.t[0];
    *lastU++ = f14tmp25_B.TransferFcn2_en;
  }

  /* Update for Derivative: '<S49>/Derivative1' */
  {
    real_T timeStampA = f14tmp25_DWork.Derivative1_RWORK_e.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative1_RWORK_e.TimeStampB;
    real_T* lastTime = &f14tmp25_DWork.Derivative1_RWORK_e.TimeStampA;
    real_T* lastU = &f14tmp25_DWork.Derivative1_RWORK_e.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp25_DWork.Derivative1_RWORK_e.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_e.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp25_DWork.Derivative1_RWORK_e.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_e.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp25_rtM->Timing.t[0];
    *lastU++ = f14tmp25_B.TransferFcn1_c;
  }

  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* Update for RandomNumber: '<S50>/White Noise' */
    f14tmp25_DWork.NextOutput_h = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp25_DWork.RandSeed_h) * f14tmp25_P.WhiteNoise_StdDev_k +
      f14tmp25_P.WhiteNoise_Mean_h;
  }

  /* Update for Derivative: '<S54>/Derivative' */
  {
    real_T timeStampA = f14tmp25_DWork.Derivative_RWORK_h.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative_RWORK_h.TimeStampB;
    real_T* lastTime = &f14tmp25_DWork.Derivative_RWORK_h.TimeStampA;
    real_T* lastU = &f14tmp25_DWork.Derivative_RWORK_h.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp25_DWork.Derivative_RWORK_h.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_h.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp25_DWork.Derivative_RWORK_h.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_h.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp25_rtM->Timing.t[0];
    *lastU++ = f14tmp25_B.TransferFcn2_eu;
  }

  /* Update for Derivative: '<S54>/Derivative1' */
  {
    real_T timeStampA = f14tmp25_DWork.Derivative1_RWORK_p.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative1_RWORK_p.TimeStampB;
    real_T* lastTime = &f14tmp25_DWork.Derivative1_RWORK_p.TimeStampA;
    real_T* lastU = &f14tmp25_DWork.Derivative1_RWORK_p.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp25_DWork.Derivative1_RWORK_p.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_p.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp25_DWork.Derivative1_RWORK_p.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_p.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp25_rtM->Timing.t[0];
    *lastU++ = f14tmp25_B.TransferFcn1_os;
  }

  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* Update for RandomNumber: '<S55>/White Noise' */
    f14tmp25_DWork.NextOutput_c = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp25_DWork.RandSeed_d) * f14tmp25_P.WhiteNoise_StdDev_p +
      f14tmp25_P.WhiteNoise_Mean_hl;
  }

  /* Update for Derivative: '<S59>/Derivative' */
  {
    real_T timeStampA = f14tmp25_DWork.Derivative_RWORK_hr.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative_RWORK_hr.TimeStampB;
    real_T* lastTime = &f14tmp25_DWork.Derivative_RWORK_hr.TimeStampA;
    real_T* lastU = &f14tmp25_DWork.Derivative_RWORK_hr.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp25_DWork.Derivative_RWORK_hr.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_hr.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp25_DWork.Derivative_RWORK_hr.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_hr.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp25_rtM->Timing.t[0];
    *lastU++ = f14tmp25_B.TransferFcn2_be;
  }

  /* Update for Derivative: '<S59>/Derivative1' */
  {
    real_T timeStampA = f14tmp25_DWork.Derivative1_RWORK_cz.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative1_RWORK_cz.TimeStampB;
    real_T* lastTime = &f14tmp25_DWork.Derivative1_RWORK_cz.TimeStampA;
    real_T* lastU = &f14tmp25_DWork.Derivative1_RWORK_cz.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp25_DWork.Derivative1_RWORK_cz.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_cz.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp25_DWork.Derivative1_RWORK_cz.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_cz.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp25_rtM->Timing.t[0];
    *lastU++ = f14tmp25_B.TransferFcn1_n;
  }

  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* Update for RandomNumber: '<S60>/White Noise' */
    f14tmp25_DWork.NextOutput_j = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp25_DWork.RandSeed_f) * f14tmp25_P.WhiteNoise_StdDev_i +
      f14tmp25_P.WhiteNoise_Mean_l;
  }

  /* Update for Derivative: '<S64>/Derivative' */
  {
    real_T timeStampA = f14tmp25_DWork.Derivative_RWORK_b.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative_RWORK_b.TimeStampB;
    real_T* lastTime = &f14tmp25_DWork.Derivative_RWORK_b.TimeStampA;
    real_T* lastU = &f14tmp25_DWork.Derivative_RWORK_b.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp25_DWork.Derivative_RWORK_b.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_b.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp25_DWork.Derivative_RWORK_b.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_b.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp25_rtM->Timing.t[0];
    *lastU++ = f14tmp25_B.TransferFcn2_o;
  }

  /* Update for Derivative: '<S64>/Derivative1' */
  {
    real_T timeStampA = f14tmp25_DWork.Derivative1_RWORK_cb.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative1_RWORK_cb.TimeStampB;
    real_T* lastTime = &f14tmp25_DWork.Derivative1_RWORK_cb.TimeStampA;
    real_T* lastU = &f14tmp25_DWork.Derivative1_RWORK_cb.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp25_DWork.Derivative1_RWORK_cb.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_cb.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp25_DWork.Derivative1_RWORK_cb.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_cb.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp25_rtM->Timing.t[0];
    *lastU++ = f14tmp25_B.TransferFcn1_m;
  }

  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* Update for RandomNumber: '<S65>/White Noise' */
    f14tmp25_DWork.NextOutput_d = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp25_DWork.RandSeed_g) * f14tmp25_P.WhiteNoise_StdDev_h +
      f14tmp25_P.WhiteNoise_Mean_no;
  }

  /* Update for Derivative: '<S69>/Derivative' */
  {
    real_T timeStampA = f14tmp25_DWork.Derivative_RWORK_jk.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative_RWORK_jk.TimeStampB;
    real_T* lastTime = &f14tmp25_DWork.Derivative_RWORK_jk.TimeStampA;
    real_T* lastU = &f14tmp25_DWork.Derivative_RWORK_jk.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp25_DWork.Derivative_RWORK_jk.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_jk.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp25_DWork.Derivative_RWORK_jk.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_jk.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp25_rtM->Timing.t[0];
    *lastU++ = f14tmp25_B.TransferFcn2_d1;
  }

  /* Update for Derivative: '<S69>/Derivative1' */
  {
    real_T timeStampA = f14tmp25_DWork.Derivative1_RWORK_ev.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative1_RWORK_ev.TimeStampB;
    real_T* lastTime = &f14tmp25_DWork.Derivative1_RWORK_ev.TimeStampA;
    real_T* lastU = &f14tmp25_DWork.Derivative1_RWORK_ev.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp25_DWork.Derivative1_RWORK_ev.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_ev.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp25_DWork.Derivative1_RWORK_ev.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_ev.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp25_rtM->Timing.t[0];
    *lastU++ = f14tmp25_B.TransferFcn1_b1;
  }

  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* Update for RandomNumber: '<S70>/White Noise' */
    f14tmp25_DWork.NextOutput_l = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp25_DWork.RandSeed_bq) * f14tmp25_P.WhiteNoise_StdDev_p1 +
      f14tmp25_P.WhiteNoise_Mean_d;
  }

  /* Update for Derivative: '<S74>/Derivative' */
  {
    real_T timeStampA = f14tmp25_DWork.Derivative_RWORK_bz.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative_RWORK_bz.TimeStampB;
    real_T* lastTime = &f14tmp25_DWork.Derivative_RWORK_bz.TimeStampA;
    real_T* lastU = &f14tmp25_DWork.Derivative_RWORK_bz.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp25_DWork.Derivative_RWORK_bz.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_bz.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp25_DWork.Derivative_RWORK_bz.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_bz.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp25_rtM->Timing.t[0];
    *lastU++ = f14tmp25_B.TransferFcn2_n;
  }

  /* Update for Derivative: '<S74>/Derivative1' */
  {
    real_T timeStampA = f14tmp25_DWork.Derivative1_RWORK_cd.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative1_RWORK_cd.TimeStampB;
    real_T* lastTime = &f14tmp25_DWork.Derivative1_RWORK_cd.TimeStampA;
    real_T* lastU = &f14tmp25_DWork.Derivative1_RWORK_cd.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp25_DWork.Derivative1_RWORK_cd.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_cd.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp25_DWork.Derivative1_RWORK_cd.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_cd.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp25_rtM->Timing.t[0];
    *lastU++ = f14tmp25_B.TransferFcn1_g;
  }

  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* Update for RandomNumber: '<S75>/White Noise' */
    f14tmp25_DWork.NextOutput_a = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp25_DWork.RandSeed_e) * f14tmp25_P.WhiteNoise_StdDev_g +
      f14tmp25_P.WhiteNoise_Mean_m;
  }

  /* Update for Derivative: '<S79>/Derivative' */
  {
    real_T timeStampA = f14tmp25_DWork.Derivative_RWORK_a.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative_RWORK_a.TimeStampB;
    real_T* lastTime = &f14tmp25_DWork.Derivative_RWORK_a.TimeStampA;
    real_T* lastU = &f14tmp25_DWork.Derivative_RWORK_a.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp25_DWork.Derivative_RWORK_a.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_a.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp25_DWork.Derivative_RWORK_a.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_a.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp25_rtM->Timing.t[0];
    *lastU++ = f14tmp25_B.TransferFcn2_nh;
  }

  /* Update for Derivative: '<S79>/Derivative1' */
  {
    real_T timeStampA = f14tmp25_DWork.Derivative1_RWORK_i.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative1_RWORK_i.TimeStampB;
    real_T* lastTime = &f14tmp25_DWork.Derivative1_RWORK_i.TimeStampA;
    real_T* lastU = &f14tmp25_DWork.Derivative1_RWORK_i.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp25_DWork.Derivative1_RWORK_i.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_i.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp25_DWork.Derivative1_RWORK_i.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_i.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp25_rtM->Timing.t[0];
    *lastU++ = f14tmp25_B.TransferFcn1_h;
  }

  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* Update for RandomNumber: '<S80>/White Noise' */
    f14tmp25_DWork.NextOutput_ag = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp25_DWork.RandSeed_e1) * f14tmp25_P.WhiteNoise_StdDev_m +
      f14tmp25_P.WhiteNoise_Mean_dw;
  }

  /* Update for Derivative: '<S84>/Derivative' */
  {
    real_T timeStampA = f14tmp25_DWork.Derivative_RWORK_l.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative_RWORK_l.TimeStampB;
    real_T* lastTime = &f14tmp25_DWork.Derivative_RWORK_l.TimeStampA;
    real_T* lastU = &f14tmp25_DWork.Derivative_RWORK_l.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp25_DWork.Derivative_RWORK_l.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_l.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp25_DWork.Derivative_RWORK_l.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_l.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp25_rtM->Timing.t[0];
    *lastU++ = f14tmp25_B.TransferFcn2_f;
  }

  /* Update for Derivative: '<S84>/Derivative1' */
  {
    real_T timeStampA = f14tmp25_DWork.Derivative1_RWORK_eb.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative1_RWORK_eb.TimeStampB;
    real_T* lastTime = &f14tmp25_DWork.Derivative1_RWORK_eb.TimeStampA;
    real_T* lastU = &f14tmp25_DWork.Derivative1_RWORK_eb.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp25_DWork.Derivative1_RWORK_eb.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_eb.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp25_DWork.Derivative1_RWORK_eb.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_eb.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp25_rtM->Timing.t[0];
    *lastU++ = f14tmp25_B.TransferFcn1_e;
  }

  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* Update for RandomNumber: '<S85>/White Noise' */
    f14tmp25_DWork.NextOutput_m = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp25_DWork.RandSeed_bo) * f14tmp25_P.WhiteNoise_StdDev_ng +
      f14tmp25_P.WhiteNoise_Mean_k;
  }

  /* Update for Derivative: '<S89>/Derivative' */
  {
    real_T timeStampA = f14tmp25_DWork.Derivative_RWORK_lu.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative_RWORK_lu.TimeStampB;
    real_T* lastTime = &f14tmp25_DWork.Derivative_RWORK_lu.TimeStampA;
    real_T* lastU = &f14tmp25_DWork.Derivative_RWORK_lu.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp25_DWork.Derivative_RWORK_lu.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_lu.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp25_DWork.Derivative_RWORK_lu.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_lu.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp25_rtM->Timing.t[0];
    *lastU++ = f14tmp25_B.TransferFcn2_l;
  }

  /* Update for Derivative: '<S89>/Derivative1' */
  {
    real_T timeStampA = f14tmp25_DWork.Derivative1_RWORK_k.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative1_RWORK_k.TimeStampB;
    real_T* lastTime = &f14tmp25_DWork.Derivative1_RWORK_k.TimeStampA;
    real_T* lastU = &f14tmp25_DWork.Derivative1_RWORK_k.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp25_DWork.Derivative1_RWORK_k.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_k.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp25_DWork.Derivative1_RWORK_k.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_k.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp25_rtM->Timing.t[0];
    *lastU++ = f14tmp25_B.TransferFcn1_gi;
  }

  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* Update for RandomNumber: '<S90>/White Noise' */
    f14tmp25_DWork.NextOutput_hq = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp25_DWork.RandSeed_eo) * f14tmp25_P.WhiteNoise_StdDev_gu +
      f14tmp25_P.WhiteNoise_Mean_kt;
  }

  /* Update for Derivative: '<S94>/Derivative' */
  {
    real_T timeStampA = f14tmp25_DWork.Derivative_RWORK_n.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative_RWORK_n.TimeStampB;
    real_T* lastTime = &f14tmp25_DWork.Derivative_RWORK_n.TimeStampA;
    real_T* lastU = &f14tmp25_DWork.Derivative_RWORK_n.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp25_DWork.Derivative_RWORK_n.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_n.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp25_DWork.Derivative_RWORK_n.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_n.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp25_rtM->Timing.t[0];
    *lastU++ = f14tmp25_B.TransferFcn2_ne;
  }

  /* Update for Derivative: '<S94>/Derivative1' */
  {
    real_T timeStampA = f14tmp25_DWork.Derivative1_RWORK_m.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative1_RWORK_m.TimeStampB;
    real_T* lastTime = &f14tmp25_DWork.Derivative1_RWORK_m.TimeStampA;
    real_T* lastU = &f14tmp25_DWork.Derivative1_RWORK_m.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp25_DWork.Derivative1_RWORK_m.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_m.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp25_DWork.Derivative1_RWORK_m.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_m.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp25_rtM->Timing.t[0];
    *lastU++ = f14tmp25_B.TransferFcn1_i;
  }

  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* Update for RandomNumber: '<S95>/White Noise' */
    f14tmp25_DWork.NextOutput_nm = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp25_DWork.RandSeed_dr) * f14tmp25_P.WhiteNoise_StdDev_pf +
      f14tmp25_P.WhiteNoise_Mean_ko;
  }

  /* Update for Derivative: '<S99>/Derivative' */
  {
    real_T timeStampA = f14tmp25_DWork.Derivative_RWORK_d.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative_RWORK_d.TimeStampB;
    real_T* lastTime = &f14tmp25_DWork.Derivative_RWORK_d.TimeStampA;
    real_T* lastU = &f14tmp25_DWork.Derivative_RWORK_d.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp25_DWork.Derivative_RWORK_d.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_d.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp25_DWork.Derivative_RWORK_d.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_d.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp25_rtM->Timing.t[0];
    *lastU++ = f14tmp25_B.TransferFcn2_a;
  }

  /* Update for Derivative: '<S99>/Derivative1' */
  {
    real_T timeStampA = f14tmp25_DWork.Derivative1_RWORK_b.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative1_RWORK_b.TimeStampB;
    real_T* lastTime = &f14tmp25_DWork.Derivative1_RWORK_b.TimeStampA;
    real_T* lastU = &f14tmp25_DWork.Derivative1_RWORK_b.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp25_DWork.Derivative1_RWORK_b.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_b.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp25_DWork.Derivative1_RWORK_b.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_b.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp25_rtM->Timing.t[0];
    *lastU++ = f14tmp25_B.TransferFcn1_e3;
  }

  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* Update for RandomNumber: '<S100>/White Noise' */
    f14tmp25_DWork.NextOutput_i = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp25_DWork.RandSeed_m) * f14tmp25_P.WhiteNoise_StdDev_kj +
      f14tmp25_P.WhiteNoise_Mean_p;
  }

  /* Update for Derivative: '<S104>/Derivative' */
  {
    real_T timeStampA = f14tmp25_DWork.Derivative_RWORK_fd.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative_RWORK_fd.TimeStampB;
    real_T* lastTime = &f14tmp25_DWork.Derivative_RWORK_fd.TimeStampA;
    real_T* lastU = &f14tmp25_DWork.Derivative_RWORK_fd.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp25_DWork.Derivative_RWORK_fd.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_fd.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp25_DWork.Derivative_RWORK_fd.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_fd.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp25_rtM->Timing.t[0];
    *lastU++ = f14tmp25_B.TransferFcn2_j;
  }

  /* Update for Derivative: '<S104>/Derivative1' */
  {
    real_T timeStampA = f14tmp25_DWork.Derivative1_RWORK_bx.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative1_RWORK_bx.TimeStampB;
    real_T* lastTime = &f14tmp25_DWork.Derivative1_RWORK_bx.TimeStampA;
    real_T* lastU = &f14tmp25_DWork.Derivative1_RWORK_bx.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp25_DWork.Derivative1_RWORK_bx.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_bx.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp25_DWork.Derivative1_RWORK_bx.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_bx.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp25_rtM->Timing.t[0];
    *lastU++ = f14tmp25_B.TransferFcn1_n3;
  }

  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* Update for RandomNumber: '<S105>/White Noise' */
    f14tmp25_DWork.NextOutput_o = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp25_DWork.RandSeed_md) * f14tmp25_P.WhiteNoise_StdDev_pd +
      f14tmp25_P.WhiteNoise_Mean_b;
  }

  /* Update for Derivative: '<S109>/Derivative' */
  {
    real_T timeStampA = f14tmp25_DWork.Derivative_RWORK_nx.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative_RWORK_nx.TimeStampB;
    real_T* lastTime = &f14tmp25_DWork.Derivative_RWORK_nx.TimeStampA;
    real_T* lastU = &f14tmp25_DWork.Derivative_RWORK_nx.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp25_DWork.Derivative_RWORK_nx.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_nx.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp25_DWork.Derivative_RWORK_nx.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_nx.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp25_rtM->Timing.t[0];
    *lastU++ = f14tmp25_B.TransferFcn2_br;
  }

  /* Update for Derivative: '<S109>/Derivative1' */
  {
    real_T timeStampA = f14tmp25_DWork.Derivative1_RWORK_kl.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative1_RWORK_kl.TimeStampB;
    real_T* lastTime = &f14tmp25_DWork.Derivative1_RWORK_kl.TimeStampA;
    real_T* lastU = &f14tmp25_DWork.Derivative1_RWORK_kl.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp25_DWork.Derivative1_RWORK_kl.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_kl.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp25_DWork.Derivative1_RWORK_kl.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_kl.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp25_rtM->Timing.t[0];
    *lastU++ = f14tmp25_B.TransferFcn1_ep;
  }

  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* Update for RandomNumber: '<S110>/White Noise' */
    f14tmp25_DWork.NextOutput_h5 = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp25_DWork.RandSeed_fu) * f14tmp25_P.WhiteNoise_StdDev_a +
      f14tmp25_P.WhiteNoise_Mean_db;
  }

  /* Update for Derivative: '<S114>/Derivative' */
  {
    real_T timeStampA = f14tmp25_DWork.Derivative_RWORK_bp.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative_RWORK_bp.TimeStampB;
    real_T* lastTime = &f14tmp25_DWork.Derivative_RWORK_bp.TimeStampA;
    real_T* lastU = &f14tmp25_DWork.Derivative_RWORK_bp.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp25_DWork.Derivative_RWORK_bp.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_bp.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp25_DWork.Derivative_RWORK_bp.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_bp.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp25_rtM->Timing.t[0];
    *lastU++ = f14tmp25_B.TransferFcn2_m;
  }

  /* Update for Derivative: '<S114>/Derivative1' */
  {
    real_T timeStampA = f14tmp25_DWork.Derivative1_RWORK_mv.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative1_RWORK_mv.TimeStampB;
    real_T* lastTime = &f14tmp25_DWork.Derivative1_RWORK_mv.TimeStampA;
    real_T* lastU = &f14tmp25_DWork.Derivative1_RWORK_mv.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp25_DWork.Derivative1_RWORK_mv.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_mv.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp25_DWork.Derivative1_RWORK_mv.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_mv.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp25_rtM->Timing.t[0];
    *lastU++ = f14tmp25_B.TransferFcn1_j;
  }

  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* Update for RandomNumber: '<S115>/White Noise' */
    f14tmp25_DWork.NextOutput_ai = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp25_DWork.RandSeed_i) * f14tmp25_P.WhiteNoise_StdDev_mj +
      f14tmp25_P.WhiteNoise_Mean_i;
  }

  /* Update for Derivative: '<S119>/Derivative' */
  {
    real_T timeStampA = f14tmp25_DWork.Derivative_RWORK_k.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative_RWORK_k.TimeStampB;
    real_T* lastTime = &f14tmp25_DWork.Derivative_RWORK_k.TimeStampA;
    real_T* lastU = &f14tmp25_DWork.Derivative_RWORK_k.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp25_DWork.Derivative_RWORK_k.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_k.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp25_DWork.Derivative_RWORK_k.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_k.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp25_rtM->Timing.t[0];
    *lastU++ = f14tmp25_B.TransferFcn2_ja;
  }

  /* Update for Derivative: '<S119>/Derivative1' */
  {
    real_T timeStampA = f14tmp25_DWork.Derivative1_RWORK_bm.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative1_RWORK_bm.TimeStampB;
    real_T* lastTime = &f14tmp25_DWork.Derivative1_RWORK_bm.TimeStampA;
    real_T* lastU = &f14tmp25_DWork.Derivative1_RWORK_bm.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp25_DWork.Derivative1_RWORK_bm.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_bm.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp25_DWork.Derivative1_RWORK_bm.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_bm.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp25_rtM->Timing.t[0];
    *lastU++ = f14tmp25_B.TransferFcn1_k;
  }

  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* Update for RandomNumber: '<S120>/White Noise' */
    f14tmp25_DWork.NextOutput_am = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp25_DWork.RandSeed_fk) * f14tmp25_P.WhiteNoise_StdDev_f +
      f14tmp25_P.WhiteNoise_Mean_nk;
  }

  /* Update for Derivative: '<S124>/Derivative' */
  {
    real_T timeStampA = f14tmp25_DWork.Derivative_RWORK_lc.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative_RWORK_lc.TimeStampB;
    real_T* lastTime = &f14tmp25_DWork.Derivative_RWORK_lc.TimeStampA;
    real_T* lastU = &f14tmp25_DWork.Derivative_RWORK_lc.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp25_DWork.Derivative_RWORK_lc.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_lc.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp25_DWork.Derivative_RWORK_lc.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_lc.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp25_rtM->Timing.t[0];
    *lastU++ = f14tmp25_B.TransferFcn2_oz;
  }

  /* Update for Derivative: '<S124>/Derivative1' */
  {
    real_T timeStampA = f14tmp25_DWork.Derivative1_RWORK_dt.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative1_RWORK_dt.TimeStampB;
    real_T* lastTime = &f14tmp25_DWork.Derivative1_RWORK_dt.TimeStampA;
    real_T* lastU = &f14tmp25_DWork.Derivative1_RWORK_dt.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp25_DWork.Derivative1_RWORK_dt.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_dt.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp25_DWork.Derivative1_RWORK_dt.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_dt.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp25_rtM->Timing.t[0];
    *lastU++ = f14tmp25_B.TransferFcn1_iw;
  }

  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* Update for RandomNumber: '<S125>/White Noise' */
    f14tmp25_DWork.NextOutput_e = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp25_DWork.RandSeed_dd) * f14tmp25_P.WhiteNoise_StdDev_kq +
      f14tmp25_P.WhiteNoise_Mean_bf;
  }

  /* Update for Derivative: '<S129>/Derivative' */
  {
    real_T timeStampA = f14tmp25_DWork.Derivative_RWORK_jt.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative_RWORK_jt.TimeStampB;
    real_T* lastTime = &f14tmp25_DWork.Derivative_RWORK_jt.TimeStampA;
    real_T* lastU = &f14tmp25_DWork.Derivative_RWORK_jt.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp25_DWork.Derivative_RWORK_jt.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_jt.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp25_DWork.Derivative_RWORK_jt.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_jt.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp25_rtM->Timing.t[0];
    *lastU++ = f14tmp25_B.TransferFcn2_jp;
  }

  /* Update for Derivative: '<S129>/Derivative1' */
  {
    real_T timeStampA = f14tmp25_DWork.Derivative1_RWORK_pp.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative1_RWORK_pp.TimeStampB;
    real_T* lastTime = &f14tmp25_DWork.Derivative1_RWORK_pp.TimeStampA;
    real_T* lastU = &f14tmp25_DWork.Derivative1_RWORK_pp.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp25_DWork.Derivative1_RWORK_pp.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_pp.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp25_DWork.Derivative1_RWORK_pp.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_pp.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp25_rtM->Timing.t[0];
    *lastU++ = f14tmp25_B.TransferFcn1_f;
  }

  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* Update for RandomNumber: '<S130>/White Noise' */
    f14tmp25_DWork.NextOutput_k = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp25_DWork.RandSeed_j) * f14tmp25_P.WhiteNoise_StdDev_fh +
      f14tmp25_P.WhiteNoise_Mean_g;
  }

  /* Update for Derivative: '<S134>/Derivative' */
  {
    real_T timeStampA = f14tmp25_DWork.Derivative_RWORK_o.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative_RWORK_o.TimeStampB;
    real_T* lastTime = &f14tmp25_DWork.Derivative_RWORK_o.TimeStampA;
    real_T* lastU = &f14tmp25_DWork.Derivative_RWORK_o.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp25_DWork.Derivative_RWORK_o.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_o.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp25_DWork.Derivative_RWORK_o.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_o.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp25_rtM->Timing.t[0];
    *lastU++ = f14tmp25_B.TransferFcn2_fa;
  }

  /* Update for Derivative: '<S134>/Derivative1' */
  {
    real_T timeStampA = f14tmp25_DWork.Derivative1_RWORK_eu.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative1_RWORK_eu.TimeStampB;
    real_T* lastTime = &f14tmp25_DWork.Derivative1_RWORK_eu.TimeStampA;
    real_T* lastU = &f14tmp25_DWork.Derivative1_RWORK_eu.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp25_DWork.Derivative1_RWORK_eu.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_eu.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp25_DWork.Derivative1_RWORK_eu.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_eu.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp25_rtM->Timing.t[0];
    *lastU++ = f14tmp25_B.TransferFcn1_nf;
  }

  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* Update for RandomNumber: '<S135>/White Noise' */
    f14tmp25_DWork.NextOutput_ct = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp25_DWork.RandSeed_k) * f14tmp25_P.WhiteNoise_StdDev_m5 +
      f14tmp25_P.WhiteNoise_Mean_jo;
  }

  /* Update for Derivative: '<S139>/Derivative' */
  {
    real_T timeStampA = f14tmp25_DWork.Derivative_RWORK_o0.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative_RWORK_o0.TimeStampB;
    real_T* lastTime = &f14tmp25_DWork.Derivative_RWORK_o0.TimeStampA;
    real_T* lastU = &f14tmp25_DWork.Derivative_RWORK_o0.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp25_DWork.Derivative_RWORK_o0.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_o0.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp25_DWork.Derivative_RWORK_o0.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_o0.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp25_rtM->Timing.t[0];
    *lastU++ = f14tmp25_B.TransferFcn2_jt;
  }

  /* Update for Derivative: '<S139>/Derivative1' */
  {
    real_T timeStampA = f14tmp25_DWork.Derivative1_RWORK_j.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative1_RWORK_j.TimeStampB;
    real_T* lastTime = &f14tmp25_DWork.Derivative1_RWORK_j.TimeStampA;
    real_T* lastU = &f14tmp25_DWork.Derivative1_RWORK_j.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp25_DWork.Derivative1_RWORK_j.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_j.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp25_DWork.Derivative1_RWORK_j.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_j.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp25_rtM->Timing.t[0];
    *lastU++ = f14tmp25_B.TransferFcn1_d;
  }

  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* Update for RandomNumber: '<S140>/White Noise' */
    f14tmp25_DWork.NextOutput_d2 = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp25_DWork.RandSeed_ju) * f14tmp25_P.WhiteNoise_StdDev_id +
      f14tmp25_P.WhiteNoise_Mean_iu;
  }

  /* Update for Derivative: '<S144>/Derivative' */
  {
    real_T timeStampA = f14tmp25_DWork.Derivative_RWORK_p5.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative_RWORK_p5.TimeStampB;
    real_T* lastTime = &f14tmp25_DWork.Derivative_RWORK_p5.TimeStampA;
    real_T* lastU = &f14tmp25_DWork.Derivative_RWORK_p5.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp25_DWork.Derivative_RWORK_p5.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_p5.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp25_DWork.Derivative_RWORK_p5.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_p5.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp25_rtM->Timing.t[0];
    *lastU++ = f14tmp25_B.TransferFcn2_mc;
  }

  /* Update for Derivative: '<S144>/Derivative1' */
  {
    real_T timeStampA = f14tmp25_DWork.Derivative1_RWORK_dy.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative1_RWORK_dy.TimeStampB;
    real_T* lastTime = &f14tmp25_DWork.Derivative1_RWORK_dy.TimeStampA;
    real_T* lastU = &f14tmp25_DWork.Derivative1_RWORK_dy.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp25_DWork.Derivative1_RWORK_dy.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_dy.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp25_DWork.Derivative1_RWORK_dy.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_dy.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp25_rtM->Timing.t[0];
    *lastU++ = f14tmp25_B.TransferFcn1_l;
  }

  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* Update for RandomNumber: '<S145>/White Noise' */
    f14tmp25_DWork.NextOutput_g3 = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp25_DWork.RandSeed_nb) * f14tmp25_P.WhiteNoise_StdDev_pe +
      f14tmp25_P.WhiteNoise_Mean_f;
  }

  /* Update for Derivative: '<S149>/Derivative' */
  {
    real_T timeStampA = f14tmp25_DWork.Derivative_RWORK_ch.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative_RWORK_ch.TimeStampB;
    real_T* lastTime = &f14tmp25_DWork.Derivative_RWORK_ch.TimeStampA;
    real_T* lastU = &f14tmp25_DWork.Derivative_RWORK_ch.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp25_DWork.Derivative_RWORK_ch.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_ch.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp25_DWork.Derivative_RWORK_ch.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative_RWORK_ch.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp25_rtM->Timing.t[0];
    *lastU++ = f14tmp25_B.TransferFcn2_k;
  }

  /* Update for Derivative: '<S149>/Derivative1' */
  {
    real_T timeStampA = f14tmp25_DWork.Derivative1_RWORK_n.TimeStampA;
    real_T timeStampB = f14tmp25_DWork.Derivative1_RWORK_n.TimeStampB;
    real_T* lastTime = &f14tmp25_DWork.Derivative1_RWORK_n.TimeStampA;
    real_T* lastU = &f14tmp25_DWork.Derivative1_RWORK_n.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp25_DWork.Derivative1_RWORK_n.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_n.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp25_DWork.Derivative1_RWORK_n.TimeStampB;
        lastU = &f14tmp25_DWork.Derivative1_RWORK_n.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp25_rtM->Timing.t[0];
    *lastU++ = f14tmp25_B.TransferFcn1_jd;
  }

  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* Update for RandomNumber: '<S150>/White Noise' */
    f14tmp25_DWork.NextOutput_ip = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp25_DWork.RandSeed_ju4) * f14tmp25_P.WhiteNoise_StdDev_g0 +
      f14tmp25_P.WhiteNoise_Mean_o;
  }

  if (rtmIsMajorTimeStep(f14tmp25_rtM)) {
    rt_ertODEUpdateContinuousStates(&f14tmp25_rtM->solverInfo);
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
  if (!(++f14tmp25_rtM->Timing.clockTick0)) {
    ++f14tmp25_rtM->Timing.clockTickH0;
  }

  f14tmp25_rtM->Timing.t[0] = rtsiGetSolverStopTime(&f14tmp25_rtM->solverInfo);

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
    if (!(++f14tmp25_rtM->Timing.clockTick1)) {
      ++f14tmp25_rtM->Timing.clockTickH1;
    }

    f14tmp25_rtM->Timing.t[1] = f14tmp25_rtM->Timing.clockTick1 *
      f14tmp25_rtM->Timing.stepSize1 + f14tmp25_rtM->Timing.clockTickH1 *
      f14tmp25_rtM->Timing.stepSize1 * 4294967296.0;
  }

  if (rtmIsMajorTimeStep(f14tmp25_rtM) &&
      f14tmp25_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* Update absolute timer for sample time: [0.1s, 0.0s] */
    /* The "clockTick2" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick2"
     * and "Timing.stepSize2". Size of "clockTick2" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick2 and the high bits
     * Timing.clockTickH2. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++f14tmp25_rtM->Timing.clockTick2)) {
      ++f14tmp25_rtM->Timing.clockTickH2;
    }

    f14tmp25_rtM->Timing.t[2] = f14tmp25_rtM->Timing.clockTick2 *
      f14tmp25_rtM->Timing.stepSize2 + f14tmp25_rtM->Timing.clockTickH2 *
      f14tmp25_rtM->Timing.stepSize2 * 4294967296.0;
  }

  rate_scheduler();
}

/* Derivatives for root system: '<Root>' */
void f14tmp25_derivatives(void)
{
  /* Derivatives for TransferFcn: '<S26>/Transfer Fcn.2' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE = f14tmp25_B.Sum1_o;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE += (f14tmp25_P.TransferFcn2_A)*
      f14tmp25_X.TransferFcn2_CSTATE;
  }

  /* Derivatives for TransferFcn: '<S26>/Transfer Fcn.1' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE = f14tmp25_B.Sum2;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE += (f14tmp25_P.TransferFcn1_A)*
      f14tmp25_X.TransferFcn1_CSTATE;
  }

  /* Derivatives for TransferFcn: '<S1>/Actuator Model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE = f14tmp25_B.Sum_n;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE += (f14tmp25_P.ActuatorModel_A)*
      f14tmp25_X.ActuatorModel_CSTATE;
  }

  /* Derivatives for TransferFcn: '<S28>/W-gust model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE[0] = f14tmp25_B.Output;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE[0] += (f14tmp25_P.Wgustmodel_A[0])*
      f14tmp25_X.Wgustmodel_CSTATE[0] + (f14tmp25_P.Wgustmodel_A[1])*
      f14tmp25_X.Wgustmodel_CSTATE[1];
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE[1]= f14tmp25_X.Wgustmodel_CSTATE[0];
  }

  /* Derivatives for TransferFcn: '<S28>/Q-gust model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE = f14tmp25_B.Wgustmodel;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE += (f14tmp25_P.Qgustmodel_A)*
      f14tmp25_X.Qgustmodel_CSTATE;
  }

  /* Derivatives for TransferFcn: '<S27>/Alpha-sensor Low-pass Filter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CSTATE = f14tmp25_B.Gain5;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CSTATE +=
      (f14tmp25_P.AlphasensorLowpassFilter_A)*
      f14tmp25_X.AlphasensorLowpassFilter_CSTATE;
  }

  /* Derivatives for TransferFcn: '<S27>/Stick Prefilter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE = f14tmp25_B.Sum1_k;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE += (f14tmp25_P.StickPrefilter_A)*
      f14tmp25_X.StickPrefilter_CSTATE;
  }

  /* Derivatives for TransferFcn: '<S27>/Pitch Rate Lead Filter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE = f14tmp25_B.TransferFcn1;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE += (f14tmp25_P.PitchRateLeadFilter_A)*
      f14tmp25_X.PitchRateLeadFilter_CSTATE;
  }

  /* Derivatives for TransferFcn: '<S27>/Proportional plus integral compensator' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompens = f14tmp25_B.Sum2_f;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompens +=
      (f14tmp25_P.Proportionalplusintegralcompens)*
      f14tmp25_X.Proportionalplusintegralcompens;
  }

  /* Derivatives for TransferFcn: '<S31>/Transfer Fcn.2' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_h = f14tmp25_B.Sum1_e;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_h += (f14tmp25_P.TransferFcn2_A_j)*
      f14tmp25_X.TransferFcn2_CSTATE_h;
  }

  /* Derivatives for TransferFcn: '<S31>/Transfer Fcn.1' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_p = f14tmp25_B.Sum2_c;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_p += (f14tmp25_P.TransferFcn1_A_n)*
      f14tmp25_X.TransferFcn1_CSTATE_p;
  }

  /* Derivatives for TransferFcn: '<S2>/Actuator Model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_a = f14tmp25_B.Sum_l;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_a += (f14tmp25_P.ActuatorModel_A_j)*
      f14tmp25_X.ActuatorModel_CSTATE_a;
  }

  /* Derivatives for TransferFcn: '<S33>/W-gust model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_f[0] = f14tmp25_B.Output_e;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_f[0] += (f14tmp25_P.Wgustmodel_A_l[0])*
      f14tmp25_X.Wgustmodel_CSTATE_f[0]
      + (f14tmp25_P.Wgustmodel_A_l[1])*f14tmp25_X.Wgustmodel_CSTATE_f[1];
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_f[1]= f14tmp25_X.Wgustmodel_CSTATE_f[0];
  }

  /* Derivatives for TransferFcn: '<S33>/Q-gust model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_d = f14tmp25_B.Wgustmodel_j;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_d += (f14tmp25_P.Qgustmodel_A_e)*
      f14tmp25_X.Qgustmodel_CSTATE_d;
  }

  /* Derivatives for TransferFcn: '<S32>/Alpha-sensor Low-pass Filter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CSTA_g = f14tmp25_B.Gain5_h;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CSTA_g +=
      (f14tmp25_P.AlphasensorLowpassFilter_A_d)*
      f14tmp25_X.AlphasensorLowpassFilter_CSTA_g;
  }

  /* Derivatives for TransferFcn: '<S32>/Stick Prefilter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_a = f14tmp25_B.Sum1_n;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_a += (f14tmp25_P.StickPrefilter_A_c)*
      f14tmp25_X.StickPrefilter_CSTATE_a;
  }

  /* Derivatives for TransferFcn: '<S32>/Pitch Rate Lead Filter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_k = f14tmp25_B.TransferFcn1_a;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_k += (f14tmp25_P.PitchRateLeadFilter_A_c)*
      f14tmp25_X.PitchRateLeadFilter_CSTATE_k;
  }

  /* Derivatives for TransferFcn: '<S32>/Proportional plus integral compensator' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompe_n = f14tmp25_B.Sum2_k;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompe_n +=
      (f14tmp25_P.Proportionalplusintegralcompe_d)*
      f14tmp25_X.Proportionalplusintegralcompe_n;
  }

  /* Derivatives for TransferFcn: '<S36>/Transfer Fcn.2' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_g = f14tmp25_B.Sum1_p;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_g += (f14tmp25_P.TransferFcn2_A_ju)*
      f14tmp25_X.TransferFcn2_CSTATE_g;
  }

  /* Derivatives for TransferFcn: '<S36>/Transfer Fcn.1' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_o = f14tmp25_B.Sum2_i;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_o += (f14tmp25_P.TransferFcn1_A_j)*
      f14tmp25_X.TransferFcn1_CSTATE_o;
  }

  /* Derivatives for TransferFcn: '<S3>/Actuator Model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_j = f14tmp25_B.Sum_k;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_j += (f14tmp25_P.ActuatorModel_A_g)*
      f14tmp25_X.ActuatorModel_CSTATE_j;
  }

  /* Derivatives for TransferFcn: '<S38>/W-gust model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_m[0] = f14tmp25_B.Output_o;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_m[0] += (f14tmp25_P.Wgustmodel_A_a[0])*
      f14tmp25_X.Wgustmodel_CSTATE_m[0]
      + (f14tmp25_P.Wgustmodel_A_a[1])*f14tmp25_X.Wgustmodel_CSTATE_m[1];
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_m[1]= f14tmp25_X.Wgustmodel_CSTATE_m[0];
  }

  /* Derivatives for TransferFcn: '<S38>/Q-gust model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_i = f14tmp25_B.Wgustmodel_n;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_i += (f14tmp25_P.Qgustmodel_A_m)*
      f14tmp25_X.Qgustmodel_CSTATE_i;
  }

  /* Derivatives for TransferFcn: '<S37>/Alpha-sensor Low-pass Filter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CSTA_e = f14tmp25_B.Gain5_k;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CSTA_e +=
      (f14tmp25_P.AlphasensorLowpassFilter_A_b)*
      f14tmp25_X.AlphasensorLowpassFilter_CSTA_e;
  }

  /* Derivatives for TransferFcn: '<S37>/Stick Prefilter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_ak = f14tmp25_B.Sum1_j;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_ak += (f14tmp25_P.StickPrefilter_A_g)*
      f14tmp25_X.StickPrefilter_CSTATE_ak;
  }

  /* Derivatives for TransferFcn: '<S37>/Pitch Rate Lead Filter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_m = f14tmp25_B.TransferFcn1_b;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_m += (f14tmp25_P.PitchRateLeadFilter_A_g)*
      f14tmp25_X.PitchRateLeadFilter_CSTATE_m;
  }

  /* Derivatives for TransferFcn: '<S37>/Proportional plus integral compensator' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompe_f = f14tmp25_B.Sum2_j;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompe_f +=
      (f14tmp25_P.Proportionalplusintegralcompe_f)*
      f14tmp25_X.Proportionalplusintegralcompe_f;
  }

  /* Derivatives for TransferFcn: '<S41>/Transfer Fcn.2' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_h0 = f14tmp25_B.Sum1_b;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_h0 += (f14tmp25_P.TransferFcn2_A_i)*
      f14tmp25_X.TransferFcn2_CSTATE_h0;
  }

  /* Derivatives for TransferFcn: '<S41>/Transfer Fcn.1' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_h = f14tmp25_B.Sum2_p;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_h += (f14tmp25_P.TransferFcn1_A_d)*
      f14tmp25_X.TransferFcn1_CSTATE_h;
  }

  /* Derivatives for TransferFcn: '<S4>/Actuator Model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_h = f14tmp25_B.Sum_nw;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_h += (f14tmp25_P.ActuatorModel_A_f)*
      f14tmp25_X.ActuatorModel_CSTATE_h;
  }

  /* Derivatives for TransferFcn: '<S43>/W-gust model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_g[0] = f14tmp25_B.Output_g;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_g[0] += (f14tmp25_P.Wgustmodel_A_l4[0])*
      f14tmp25_X.Wgustmodel_CSTATE_g[0]
      + (f14tmp25_P.Wgustmodel_A_l4[1])*f14tmp25_X.Wgustmodel_CSTATE_g[1];
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_g[1]= f14tmp25_X.Wgustmodel_CSTATE_g[0];
  }

  /* Derivatives for TransferFcn: '<S43>/Q-gust model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_p = f14tmp25_B.Wgustmodel_f;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_p += (f14tmp25_P.Qgustmodel_A_g)*
      f14tmp25_X.Qgustmodel_CSTATE_p;
  }

  /* Derivatives for TransferFcn: '<S42>/Alpha-sensor Low-pass Filter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CSTA_j = f14tmp25_B.Gain5_bk;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CSTA_j +=
      (f14tmp25_P.AlphasensorLowpassFilter_A_bn)*
      f14tmp25_X.AlphasensorLowpassFilter_CSTA_j;
  }

  /* Derivatives for TransferFcn: '<S42>/Stick Prefilter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_i = f14tmp25_B.Sum1_m;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_i += (f14tmp25_P.StickPrefilter_A_i)*
      f14tmp25_X.StickPrefilter_CSTATE_i;
  }

  /* Derivatives for TransferFcn: '<S42>/Pitch Rate Lead Filter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_c = f14tmp25_B.TransferFcn1_o;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_c += (f14tmp25_P.PitchRateLeadFilter_A_o)*
      f14tmp25_X.PitchRateLeadFilter_CSTATE_c;
  }

  /* Derivatives for TransferFcn: '<S42>/Proportional plus integral compensator' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompe_g = f14tmp25_B.Sum2_b;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompe_g +=
      (f14tmp25_P.Proportionalplusintegralcompe_h)*
      f14tmp25_X.Proportionalplusintegralcompe_g;
  }

  /* Derivatives for TransferFcn: '<S46>/Transfer Fcn.2' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_m = f14tmp25_B.Sum1_ez;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_m += (f14tmp25_P.TransferFcn2_A_k)*
      f14tmp25_X.TransferFcn2_CSTATE_m;
  }

  /* Derivatives for TransferFcn: '<S46>/Transfer Fcn.1' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_i = f14tmp25_B.Sum2_e;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_i += (f14tmp25_P.TransferFcn1_A_o)*
      f14tmp25_X.TransferFcn1_CSTATE_i;
  }

  /* Derivatives for TransferFcn: '<S5>/Actuator Model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_f = f14tmp25_B.Sum_h;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_f += (f14tmp25_P.ActuatorModel_A_gl)*
      f14tmp25_X.ActuatorModel_CSTATE_f;
  }

  /* Derivatives for TransferFcn: '<S48>/W-gust model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_a[0] = f14tmp25_B.Output_a;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_a[0] += (f14tmp25_P.Wgustmodel_A_d[0])*
      f14tmp25_X.Wgustmodel_CSTATE_a[0]
      + (f14tmp25_P.Wgustmodel_A_d[1])*f14tmp25_X.Wgustmodel_CSTATE_a[1];
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_a[1]= f14tmp25_X.Wgustmodel_CSTATE_a[0];
  }

  /* Derivatives for TransferFcn: '<S48>/Q-gust model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_h = f14tmp25_B.Wgustmodel_c;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_h += (f14tmp25_P.Qgustmodel_A_i)*
      f14tmp25_X.Qgustmodel_CSTATE_h;
  }

  /* Derivatives for TransferFcn: '<S47>/Alpha-sensor Low-pass Filter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CSTA_c = f14tmp25_B.Gain5_hk;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CSTA_c +=
      (f14tmp25_P.AlphasensorLowpassFilter_A_g)*
      f14tmp25_X.AlphasensorLowpassFilter_CSTA_c;
  }

  /* Derivatives for TransferFcn: '<S47>/Stick Prefilter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_h = f14tmp25_B.Sum1_k2;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_h += (f14tmp25_P.StickPrefilter_A_co)*
      f14tmp25_X.StickPrefilter_CSTATE_h;
  }

  /* Derivatives for TransferFcn: '<S47>/Pitch Rate Lead Filter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_l = f14tmp25_B.TransferFcn1_c;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_l += (f14tmp25_P.PitchRateLeadFilter_A_p)*
      f14tmp25_X.PitchRateLeadFilter_CSTATE_l;
  }

  /* Derivatives for TransferFcn: '<S47>/Proportional plus integral compensator' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Proportionalplusintegralcomp_gl = f14tmp25_B.Sum2_m;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Proportionalplusintegralcomp_gl +=
      (f14tmp25_P.Proportionalplusintegralcomp_kf)*
      f14tmp25_X.Proportionalplusintegralcomp_gl;
  }

  /* Derivatives for TransferFcn: '<S51>/Transfer Fcn.2' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_p = f14tmp25_B.Sum1_bx;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_p += (f14tmp25_P.TransferFcn2_A_f)*
      f14tmp25_X.TransferFcn2_CSTATE_p;
  }

  /* Derivatives for TransferFcn: '<S51>/Transfer Fcn.1' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_n = f14tmp25_B.Sum2_o;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_n += (f14tmp25_P.TransferFcn1_A_m)*
      f14tmp25_X.TransferFcn1_CSTATE_n;
  }

  /* Derivatives for TransferFcn: '<S6>/Actuator Model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_aw = f14tmp25_B.Sum_p;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_aw += (f14tmp25_P.ActuatorModel_A_p)*
      f14tmp25_X.ActuatorModel_CSTATE_aw;
  }

  /* Derivatives for TransferFcn: '<S53>/W-gust model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_j[0] = f14tmp25_B.Output_h;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_j[0] += (f14tmp25_P.Wgustmodel_A_g[0])*
      f14tmp25_X.Wgustmodel_CSTATE_j[0]
      + (f14tmp25_P.Wgustmodel_A_g[1])*f14tmp25_X.Wgustmodel_CSTATE_j[1];
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_j[1]= f14tmp25_X.Wgustmodel_CSTATE_j[0];
  }

  /* Derivatives for TransferFcn: '<S53>/Q-gust model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_pw = f14tmp25_B.Wgustmodel_nc;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_pw += (f14tmp25_P.Qgustmodel_A_o)*
      f14tmp25_X.Qgustmodel_CSTATE_pw;
  }

  /* Derivatives for TransferFcn: '<S52>/Alpha-sensor Low-pass Filter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CST_j4 = f14tmp25_B.Gain5_n;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CST_j4 +=
      (f14tmp25_P.AlphasensorLowpassFilter_A_i)*
      f14tmp25_X.AlphasensorLowpassFilter_CST_j4;
  }

  /* Derivatives for TransferFcn: '<S52>/Stick Prefilter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_p = f14tmp25_B.Sum1_kq;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_p += (f14tmp25_P.StickPrefilter_A_cj)*
      f14tmp25_X.StickPrefilter_CSTATE_p;
  }

  /* Derivatives for TransferFcn: '<S52>/Pitch Rate Lead Filter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_c5 = f14tmp25_B.TransferFcn1_os;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_c5 += (f14tmp25_P.PitchRateLeadFilter_A_d)*
      f14tmp25_X.PitchRateLeadFilter_CSTATE_c5;
  }

  /* Derivatives for TransferFcn: '<S52>/Proportional plus integral compensator' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompe_l = f14tmp25_B.Sum2_g;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompe_l +=
      (f14tmp25_P.Proportionalplusintegralcomp_hd)*
      f14tmp25_X.Proportionalplusintegralcompe_l;
  }

  /* Derivatives for TransferFcn: '<S56>/Transfer Fcn.2' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_n = f14tmp25_B.Sum1_bq;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_n += (f14tmp25_P.TransferFcn2_A_iu)*
      f14tmp25_X.TransferFcn2_CSTATE_n;
  }

  /* Derivatives for TransferFcn: '<S56>/Transfer Fcn.1' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_b = f14tmp25_B.Sum2_o5;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_b += (f14tmp25_P.TransferFcn1_A_h)*
      f14tmp25_X.TransferFcn1_CSTATE_b;
  }

  /* Derivatives for TransferFcn: '<S7>/Actuator Model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_k = f14tmp25_B.Sum_eg;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_k += (f14tmp25_P.ActuatorModel_A_o)*
      f14tmp25_X.ActuatorModel_CSTATE_k;
  }

  /* Derivatives for TransferFcn: '<S58>/W-gust model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_mw[0] = f14tmp25_B.Output_i;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_mw[0] += (f14tmp25_P.Wgustmodel_A_k[0])*
      f14tmp25_X.Wgustmodel_CSTATE_mw[0]
      + (f14tmp25_P.Wgustmodel_A_k[1])*f14tmp25_X.Wgustmodel_CSTATE_mw[1];
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_mw[1]= f14tmp25_X.Wgustmodel_CSTATE_mw[0];
  }

  /* Derivatives for TransferFcn: '<S58>/Q-gust model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_l = f14tmp25_B.Wgustmodel_d;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_l += (f14tmp25_P.Qgustmodel_A_c)*
      f14tmp25_X.Qgustmodel_CSTATE_l;
  }

  /* Derivatives for TransferFcn: '<S57>/Alpha-sensor Low-pass Filter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CST_ji = f14tmp25_B.Gain5_nt;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CST_ji +=
      (f14tmp25_P.AlphasensorLowpassFilter_A_h)*
      f14tmp25_X.AlphasensorLowpassFilter_CST_ji;
  }

  /* Derivatives for TransferFcn: '<S57>/Stick Prefilter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_d = f14tmp25_B.Sum1_gi;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_d += (f14tmp25_P.StickPrefilter_A_d)*
      f14tmp25_X.StickPrefilter_CSTATE_d;
  }

  /* Derivatives for TransferFcn: '<S57>/Pitch Rate Lead Filter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_j = f14tmp25_B.TransferFcn1_n;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_j += (f14tmp25_P.PitchRateLeadFilter_A_a)*
      f14tmp25_X.PitchRateLeadFilter_CSTATE_j;
  }

  /* Derivatives for TransferFcn: '<S57>/Proportional plus integral compensator' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompe_p = f14tmp25_B.Sum2_kr;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompe_p +=
      (f14tmp25_P.Proportionalplusintegralcomp_n4)*
      f14tmp25_X.Proportionalplusintegralcompe_p;
  }

  /* Derivatives for TransferFcn: '<S61>/Transfer Fcn.2' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_o = f14tmp25_B.Sum1_fz;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_o += (f14tmp25_P.TransferFcn2_A_g)*
      f14tmp25_X.TransferFcn2_CSTATE_o;
  }

  /* Derivatives for TransferFcn: '<S61>/Transfer Fcn.1' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_nw = f14tmp25_B.Sum2_gl;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_nw += (f14tmp25_P.TransferFcn1_A_nv)*
      f14tmp25_X.TransferFcn1_CSTATE_nw;
  }

  /* Derivatives for TransferFcn: '<S8>/Actuator Model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_o = f14tmp25_B.Sum_pi;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_o += (f14tmp25_P.ActuatorModel_A_k)*
      f14tmp25_X.ActuatorModel_CSTATE_o;
  }

  /* Derivatives for TransferFcn: '<S63>/W-gust model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_e[0] = f14tmp25_B.Output_n;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_e[0] += (f14tmp25_P.Wgustmodel_A_h[0])*
      f14tmp25_X.Wgustmodel_CSTATE_e[0]
      + (f14tmp25_P.Wgustmodel_A_h[1])*f14tmp25_X.Wgustmodel_CSTATE_e[1];
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_e[1]= f14tmp25_X.Wgustmodel_CSTATE_e[0];
  }

  /* Derivatives for TransferFcn: '<S63>/Q-gust model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_b = f14tmp25_B.Wgustmodel_a;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_b += (f14tmp25_P.Qgustmodel_A_k)*
      f14tmp25_X.Qgustmodel_CSTATE_b;
  }

  /* Derivatives for TransferFcn: '<S62>/Alpha-sensor Low-pass Filter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CST_ep = f14tmp25_B.Gain5_hw;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CST_ep +=
      (f14tmp25_P.AlphasensorLowpassFilter_A_p)*
      f14tmp25_X.AlphasensorLowpassFilter_CST_ep;
  }

  /* Derivatives for TransferFcn: '<S62>/Stick Prefilter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_hs = f14tmp25_B.Sum1_m2;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_hs += (f14tmp25_P.StickPrefilter_A_cf)*
      f14tmp25_X.StickPrefilter_CSTATE_hs;
  }

  /* Derivatives for TransferFcn: '<S62>/Pitch Rate Lead Filter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_h = f14tmp25_B.TransferFcn1_m;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_h += (f14tmp25_P.PitchRateLeadFilter_A_n)*
      f14tmp25_X.PitchRateLeadFilter_CSTATE_h;
  }

  /* Derivatives for TransferFcn: '<S62>/Proportional plus integral compensator' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompe_h = f14tmp25_B.Sum2_c3;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompe_h +=
      (f14tmp25_P.Proportionalplusintegralcomp_pa)*
      f14tmp25_X.Proportionalplusintegralcompe_h;
  }

  /* Derivatives for TransferFcn: '<S66>/Transfer Fcn.2' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_c = f14tmp25_B.Sum1_fo;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_c += (f14tmp25_P.TransferFcn2_A_h)*
      f14tmp25_X.TransferFcn2_CSTATE_c;
  }

  /* Derivatives for TransferFcn: '<S66>/Transfer Fcn.1' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_bm = f14tmp25_B.Sum2_jr;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_bm += (f14tmp25_P.TransferFcn1_A_b)*
      f14tmp25_X.TransferFcn1_CSTATE_bm;
  }

  /* Derivatives for TransferFcn: '<S9>/Actuator Model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_ku = f14tmp25_B.Sum_a;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_ku += (f14tmp25_P.ActuatorModel_A_l)*
      f14tmp25_X.ActuatorModel_CSTATE_ku;
  }

  /* Derivatives for TransferFcn: '<S68>/W-gust model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_fj[0] = f14tmp25_B.Output_gu;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_fj[0] += (f14tmp25_P.Wgustmodel_A_i[0])*
      f14tmp25_X.Wgustmodel_CSTATE_fj[0]
      + (f14tmp25_P.Wgustmodel_A_i[1])*f14tmp25_X.Wgustmodel_CSTATE_fj[1];
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_fj[1]= f14tmp25_X.Wgustmodel_CSTATE_fj[0];
  }

  /* Derivatives for TransferFcn: '<S68>/Q-gust model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_a = f14tmp25_B.Wgustmodel_g;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_a += (f14tmp25_P.Qgustmodel_A_a)*
      f14tmp25_X.Qgustmodel_CSTATE_a;
  }

  /* Derivatives for TransferFcn: '<S67>/Alpha-sensor Low-pass Filter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CST_cd = f14tmp25_B.Gain5_e;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CST_cd +=
      (f14tmp25_P.AlphasensorLowpassFilter_A_it)*
      f14tmp25_X.AlphasensorLowpassFilter_CST_cd;
  }

  /* Derivatives for TransferFcn: '<S67>/Stick Prefilter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_f = f14tmp25_B.Sum1_ij;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_f += (f14tmp25_P.StickPrefilter_A_j)*
      f14tmp25_X.StickPrefilter_CSTATE_f;
  }

  /* Derivatives for TransferFcn: '<S67>/Pitch Rate Lead Filter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_e = f14tmp25_B.TransferFcn1_b1;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_e += (f14tmp25_P.PitchRateLeadFilter_A_e)*
      f14tmp25_X.PitchRateLeadFilter_CSTATE_e;
  }

  /* Derivatives for TransferFcn: '<S67>/Proportional plus integral compensator' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompe_i = f14tmp25_B.Sum2_a;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompe_i +=
      (f14tmp25_P.Proportionalplusintegralcomp_nc)*
      f14tmp25_X.Proportionalplusintegralcompe_i;
  }

  /* Derivatives for TransferFcn: '<S71>/Transfer Fcn.2' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_a = f14tmp25_B.Sum1_dq;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_a += (f14tmp25_P.TransferFcn2_A_o)*
      f14tmp25_X.TransferFcn2_CSTATE_a;
  }

  /* Derivatives for TransferFcn: '<S71>/Transfer Fcn.1' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_m = f14tmp25_B.Sum2_kw;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_m += (f14tmp25_P.TransferFcn1_A_me)*
      f14tmp25_X.TransferFcn1_CSTATE_m;
  }

  /* Derivatives for TransferFcn: '<S10>/Actuator Model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_c = f14tmp25_B.Sum_bx;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_c += (f14tmp25_P.ActuatorModel_A_ga)*
      f14tmp25_X.ActuatorModel_CSTATE_c;
  }

  /* Derivatives for TransferFcn: '<S73>/W-gust model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_d[0] = f14tmp25_B.Output_nn;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_d[0] += (f14tmp25_P.Wgustmodel_A_he[0])*
      f14tmp25_X.Wgustmodel_CSTATE_d[0]
      + (f14tmp25_P.Wgustmodel_A_he[1])*f14tmp25_X.Wgustmodel_CSTATE_d[1];
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_d[1]= f14tmp25_X.Wgustmodel_CSTATE_d[0];
  }

  /* Derivatives for TransferFcn: '<S73>/Q-gust model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_o = f14tmp25_B.Wgustmodel_do;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_o += (f14tmp25_P.Qgustmodel_A_l)*
      f14tmp25_X.Qgustmodel_CSTATE_o;
  }

  /* Derivatives for TransferFcn: '<S72>/Alpha-sensor Low-pass Filter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CST_ej = f14tmp25_B.Gain5_nv;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CST_ej +=
      (f14tmp25_P.AlphasensorLowpassFilter_A_f)*
      f14tmp25_X.AlphasensorLowpassFilter_CST_ej;
  }

  /* Derivatives for TransferFcn: '<S72>/Stick Prefilter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_n = f14tmp25_B.Sum1_fov;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_n += (f14tmp25_P.StickPrefilter_A_jy)*
      f14tmp25_X.StickPrefilter_CSTATE_n;
  }

  /* Derivatives for TransferFcn: '<S72>/Pitch Rate Lead Filter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_e4 = f14tmp25_B.TransferFcn1_g;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_e4 += (f14tmp25_P.PitchRateLeadFilter_A_h)*
      f14tmp25_X.PitchRateLeadFilter_CSTATE_e4;
  }

  /* Derivatives for TransferFcn: '<S72>/Proportional plus integral compensator' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Proportionalplusintegralcomp_p5 = f14tmp25_B.Sum2_ee;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Proportionalplusintegralcomp_p5 +=
      (f14tmp25_P.Proportionalplusintegralcomp_o3)*
      f14tmp25_X.Proportionalplusintegralcomp_p5;
  }

  /* Derivatives for TransferFcn: '<S76>/Transfer Fcn.2' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_l = f14tmp25_B.Sum1_jj;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_l += (f14tmp25_P.TransferFcn2_A_l)*
      f14tmp25_X.TransferFcn2_CSTATE_l;
  }

  /* Derivatives for TransferFcn: '<S76>/Transfer Fcn.1' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_iz = f14tmp25_B.Sum2_f1;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_iz += (f14tmp25_P.TransferFcn1_A_g)*
      f14tmp25_X.TransferFcn1_CSTATE_iz;
  }

  /* Derivatives for TransferFcn: '<S11>/Actuator Model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_hl = f14tmp25_B.Sum_km;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_hl += (f14tmp25_P.ActuatorModel_A_lr)*
      f14tmp25_X.ActuatorModel_CSTATE_hl;
  }

  /* Derivatives for TransferFcn: '<S78>/W-gust model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_mo[0] = f14tmp25_B.Output_b;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_mo[0] += (f14tmp25_P.Wgustmodel_A_gn[0])*
      f14tmp25_X.Wgustmodel_CSTATE_mo[0]
      + (f14tmp25_P.Wgustmodel_A_gn[1])*f14tmp25_X.Wgustmodel_CSTATE_mo[1];
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_mo[1]= f14tmp25_X.Wgustmodel_CSTATE_mo[0];
  }

  /* Derivatives for TransferFcn: '<S78>/Q-gust model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_p3 = f14tmp25_B.Wgustmodel_nd;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_p3 += (f14tmp25_P.Qgustmodel_A_d)*
      f14tmp25_X.Qgustmodel_CSTATE_p3;
  }

  /* Derivatives for TransferFcn: '<S77>/Alpha-sensor Low-pass Filter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CSTA_i = f14tmp25_B.Gain5_pn;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CSTA_i +=
      (f14tmp25_P.AlphasensorLowpassFilter_A_id)*
      f14tmp25_X.AlphasensorLowpassFilter_CSTA_i;
  }

  /* Derivatives for TransferFcn: '<S77>/Stick Prefilter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_b = f14tmp25_B.Sum1_jt;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_b += (f14tmp25_P.StickPrefilter_A_g0)*
      f14tmp25_X.StickPrefilter_CSTATE_b;
  }

  /* Derivatives for TransferFcn: '<S77>/Pitch Rate Lead Filter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_d = f14tmp25_B.TransferFcn1_h;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_d += (f14tmp25_P.PitchRateLeadFilter_A_l)*
      f14tmp25_X.PitchRateLeadFilter_CSTATE_d;
  }

  /* Derivatives for TransferFcn: '<S77>/Proportional plus integral compensator' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Proportionalplusintegralcomp_he = f14tmp25_B.Sum2_mp;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Proportionalplusintegralcomp_he +=
      (f14tmp25_P.Proportionalplusintegralcomp_d3)*
      f14tmp25_X.Proportionalplusintegralcomp_he;
  }

  /* Derivatives for TransferFcn: '<S81>/Transfer Fcn.2' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_b = f14tmp25_B.Sum1_bk;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_b += (f14tmp25_P.TransferFcn2_A_b)*
      f14tmp25_X.TransferFcn2_CSTATE_b;
  }

  /* Derivatives for TransferFcn: '<S81>/Transfer Fcn.1' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_l = f14tmp25_B.Sum2_ol;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_l += (f14tmp25_P.TransferFcn1_A_c)*
      f14tmp25_X.TransferFcn1_CSTATE_l;
  }

  /* Derivatives for TransferFcn: '<S12>/Actuator Model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_d = f14tmp25_B.Sum_my;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_d += (f14tmp25_P.ActuatorModel_A_b)*
      f14tmp25_X.ActuatorModel_CSTATE_d;
  }

  /* Derivatives for TransferFcn: '<S83>/W-gust model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_n[0] = f14tmp25_B.Output_l;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_n[0] += (f14tmp25_P.Wgustmodel_A_le[0])*
      f14tmp25_X.Wgustmodel_CSTATE_n[0]
      + (f14tmp25_P.Wgustmodel_A_le[1])*f14tmp25_X.Wgustmodel_CSTATE_n[1];
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_n[1]= f14tmp25_X.Wgustmodel_CSTATE_n[0];
  }

  /* Derivatives for TransferFcn: '<S83>/Q-gust model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_g = f14tmp25_B.Wgustmodel_c5;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_g += (f14tmp25_P.Qgustmodel_A_h)*
      f14tmp25_X.Qgustmodel_CSTATE_g;
  }

  /* Derivatives for TransferFcn: '<S82>/Alpha-sensor Low-pass Filter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CSTA_b = f14tmp25_B.Gain5_nb;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CSTA_b +=
      (f14tmp25_P.AlphasensorLowpassFilter_A_o)*
      f14tmp25_X.AlphasensorLowpassFilter_CSTA_b;
  }

  /* Derivatives for TransferFcn: '<S82>/Stick Prefilter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_j = f14tmp25_B.Sum1_oo;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_j += (f14tmp25_P.StickPrefilter_A_a)*
      f14tmp25_X.StickPrefilter_CSTATE_j;
  }

  /* Derivatives for TransferFcn: '<S82>/Pitch Rate Lead Filter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_f = f14tmp25_B.TransferFcn1_e;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_f += (f14tmp25_P.PitchRateLeadFilter_A_b)*
      f14tmp25_X.PitchRateLeadFilter_CSTATE_f;
  }

  /* Derivatives for TransferFcn: '<S82>/Proportional plus integral compensator' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompe_o = f14tmp25_B.Sum2_px;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompe_o +=
      (f14tmp25_P.Proportionalplusintegralcomp_ov)*
      f14tmp25_X.Proportionalplusintegralcompe_o;
  }

  /* Derivatives for TransferFcn: '<S86>/Transfer Fcn.2' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_n5 = f14tmp25_B.Sum1_dr;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_n5 += (f14tmp25_P.TransferFcn2_A_lg)*
      f14tmp25_X.TransferFcn2_CSTATE_n5;
  }

  /* Derivatives for TransferFcn: '<S86>/Transfer Fcn.1' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_k = f14tmp25_B.Sum2_ola;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_k += (f14tmp25_P.TransferFcn1_A_dl)*
      f14tmp25_X.TransferFcn1_CSTATE_k;
  }

  /* Derivatives for TransferFcn: '<S13>/Actuator Model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_fg = f14tmp25_B.Sum_ou;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_fg += (f14tmp25_P.ActuatorModel_A_gy)*
      f14tmp25_X.ActuatorModel_CSTATE_fg;
  }

  /* Derivatives for TransferFcn: '<S88>/W-gust model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_i[0] = f14tmp25_B.Output_c;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_i[0] += (f14tmp25_P.Wgustmodel_A_m[0])*
      f14tmp25_X.Wgustmodel_CSTATE_i[0]
      + (f14tmp25_P.Wgustmodel_A_m[1])*f14tmp25_X.Wgustmodel_CSTATE_i[1];
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_i[1]= f14tmp25_X.Wgustmodel_CSTATE_i[0];
  }

  /* Derivatives for TransferFcn: '<S88>/Q-gust model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_k = f14tmp25_B.Wgustmodel_e;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_k += (f14tmp25_P.Qgustmodel_A_b)*
      f14tmp25_X.Qgustmodel_CSTATE_k;
  }

  /* Derivatives for TransferFcn: '<S87>/Alpha-sensor Low-pass Filter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CST_i1 = f14tmp25_B.Gain5_py;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CST_i1 +=
      (f14tmp25_P.AlphasensorLowpassFilter_A_c)*
      f14tmp25_X.AlphasensorLowpassFilter_CST_i1;
  }

  /* Derivatives for TransferFcn: '<S87>/Stick Prefilter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_jz = f14tmp25_B.Sum1_n0;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_jz += (f14tmp25_P.StickPrefilter_A_e)*
      f14tmp25_X.StickPrefilter_CSTATE_jz;
  }

  /* Derivatives for TransferFcn: '<S87>/Pitch Rate Lead Filter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_n = f14tmp25_B.TransferFcn1_gi;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_n += (f14tmp25_P.PitchRateLeadFilter_A_i)*
      f14tmp25_X.PitchRateLeadFilter_CSTATE_n;
  }

  /* Derivatives for TransferFcn: '<S87>/Proportional plus integral compensator' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Proportionalplusintegralcomp_hi = f14tmp25_B.Sum2_gk;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Proportionalplusintegralcomp_hi +=
      (f14tmp25_P.Proportionalplusintegralcomp_hc)*
      f14tmp25_X.Proportionalplusintegralcomp_hi;
  }

  /* Derivatives for TransferFcn: '<S91>/Transfer Fcn.2' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_k = f14tmp25_B.Sum1_gl;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_k += (f14tmp25_P.TransferFcn2_A_f1)*
      f14tmp25_X.TransferFcn2_CSTATE_k;
  }

  /* Derivatives for TransferFcn: '<S91>/Transfer Fcn.1' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_g = f14tmp25_B.Sum2_mr;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_g += (f14tmp25_P.TransferFcn1_A_nq)*
      f14tmp25_X.TransferFcn1_CSTATE_g;
  }

  /* Derivatives for TransferFcn: '<S14>/Actuator Model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_ov = f14tmp25_B.Sum_af;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_ov += (f14tmp25_P.ActuatorModel_A_n)*
      f14tmp25_X.ActuatorModel_CSTATE_ov;
  }

  /* Derivatives for TransferFcn: '<S93>/W-gust model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_p[0] = f14tmp25_B.Output_k;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_p[0] += (f14tmp25_P.Wgustmodel_A_dc[0])*
      f14tmp25_X.Wgustmodel_CSTATE_p[0]
      + (f14tmp25_P.Wgustmodel_A_dc[1])*f14tmp25_X.Wgustmodel_CSTATE_p[1];
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_p[1]= f14tmp25_X.Wgustmodel_CSTATE_p[0];
  }

  /* Derivatives for TransferFcn: '<S93>/Q-gust model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_m = f14tmp25_B.Wgustmodel_dn;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_m += (f14tmp25_P.Qgustmodel_A_oe)*
      f14tmp25_X.Qgustmodel_CSTATE_m;
  }

  /* Derivatives for TransferFcn: '<S92>/Alpha-sensor Low-pass Filter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CSTA_h = f14tmp25_B.Gain5_kd;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CSTA_h +=
      (f14tmp25_P.AlphasensorLowpassFilter_A_bs)*
      f14tmp25_X.AlphasensorLowpassFilter_CSTA_h;
  }

  /* Derivatives for TransferFcn: '<S92>/Stick Prefilter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_c = f14tmp25_B.Sum1_co;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_c += (f14tmp25_P.StickPrefilter_A_ca)*
      f14tmp25_X.StickPrefilter_CSTATE_c;
  }

  /* Derivatives for TransferFcn: '<S92>/Pitch Rate Lead Filter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_m2 = f14tmp25_B.TransferFcn1_i;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_m2 += (f14tmp25_P.PitchRateLeadFilter_A_go)*
      f14tmp25_X.PitchRateLeadFilter_CSTATE_m2;
  }

  /* Derivatives for TransferFcn: '<S92>/Proportional plus integral compensator' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Proportionalplusintegralcomp_gw = f14tmp25_B.Sum2_mn;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Proportionalplusintegralcomp_gw +=
      (f14tmp25_P.Proportionalplusintegralcomp_fg)*
      f14tmp25_X.Proportionalplusintegralcomp_gw;
  }

  /* Derivatives for TransferFcn: '<S96>/Transfer Fcn.2' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_ki = f14tmp25_B.Sum1_iav;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_ki += (f14tmp25_P.TransferFcn2_A_iv)*
      f14tmp25_X.TransferFcn2_CSTATE_ki;
  }

  /* Derivatives for TransferFcn: '<S96>/Transfer Fcn.1' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_im = f14tmp25_B.Sum2_bu;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_im += (f14tmp25_P.TransferFcn1_A_gv)*
      f14tmp25_X.TransferFcn1_CSTATE_im;
  }

  /* Derivatives for TransferFcn: '<S15>/Actuator Model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_i = f14tmp25_B.Sum_kq;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_i += (f14tmp25_P.ActuatorModel_A_e)*
      f14tmp25_X.ActuatorModel_CSTATE_i;
  }

  /* Derivatives for TransferFcn: '<S98>/W-gust model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_o[0] = f14tmp25_B.Output_gq;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_o[0] += (f14tmp25_P.Wgustmodel_A_e[0])*
      f14tmp25_X.Wgustmodel_CSTATE_o[0]
      + (f14tmp25_P.Wgustmodel_A_e[1])*f14tmp25_X.Wgustmodel_CSTATE_o[1];
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_o[1]= f14tmp25_X.Wgustmodel_CSTATE_o[0];
  }

  /* Derivatives for TransferFcn: '<S98>/Q-gust model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_n = f14tmp25_B.Wgustmodel_gx;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_n += (f14tmp25_P.Qgustmodel_A_f)*
      f14tmp25_X.Qgustmodel_CSTATE_n;
  }

  /* Derivatives for TransferFcn: '<S97>/Alpha-sensor Low-pass Filter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CST_ef = f14tmp25_B.Gain5_kv;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CST_ef +=
      (f14tmp25_P.AlphasensorLowpassFilter_A_hx)*
      f14tmp25_X.AlphasensorLowpassFilter_CST_ef;
  }

  /* Derivatives for TransferFcn: '<S97>/Stick Prefilter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_n1 = f14tmp25_B.Sum1_lr;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_n1 += (f14tmp25_P.StickPrefilter_A_f)*
      f14tmp25_X.StickPrefilter_CSTATE_n1;
  }

  /* Derivatives for TransferFcn: '<S97>/Pitch Rate Lead Filter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_mp = f14tmp25_B.TransferFcn1_e3;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_mp += (f14tmp25_P.PitchRateLeadFilter_A_p0)*
      f14tmp25_X.PitchRateLeadFilter_CSTATE_mp;
  }

  /* Derivatives for TransferFcn: '<S97>/Proportional plus integral compensator' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompe_j = f14tmp25_B.Sum2_eu;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompe_j +=
      (f14tmp25_P.Proportionalplusintegralcomp_fo)*
      f14tmp25_X.Proportionalplusintegralcompe_j;
  }

  /* Derivatives for TransferFcn: '<S101>/Transfer Fcn.2' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_oa = f14tmp25_B.Sum1_bx5;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_oa += (f14tmp25_P.TransferFcn2_A_fp)*
      f14tmp25_X.TransferFcn2_CSTATE_oa;
  }

  /* Derivatives for TransferFcn: '<S101>/Transfer Fcn.1' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_a = f14tmp25_B.Sum2_ei;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_a += (f14tmp25_P.TransferFcn1_A_di)*
      f14tmp25_X.TransferFcn1_CSTATE_a;
  }

  /* Derivatives for TransferFcn: '<S16>/Actuator Model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_e = f14tmp25_B.Sum_bd;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_e += (f14tmp25_P.ActuatorModel_A_a)*
      f14tmp25_X.ActuatorModel_CSTATE_e;
  }

  /* Derivatives for TransferFcn: '<S103>/W-gust model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_it[0] = f14tmp25_B.Output_d;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_it[0] += (f14tmp25_P.Wgustmodel_A_f[0])*
      f14tmp25_X.Wgustmodel_CSTATE_it[0]
      + (f14tmp25_P.Wgustmodel_A_f[1])*f14tmp25_X.Wgustmodel_CSTATE_it[1];
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_it[1]= f14tmp25_X.Wgustmodel_CSTATE_it[0];
  }

  /* Derivatives for TransferFcn: '<S103>/Q-gust model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_ie = f14tmp25_B.Wgustmodel_i;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_ie += (f14tmp25_P.Qgustmodel_A_oy)*
      f14tmp25_X.Qgustmodel_CSTATE_ie;
  }

  /* Derivatives for TransferFcn: '<S102>/Alpha-sensor Low-pass Filter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CST_gn = f14tmp25_B.Gain5_nz;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CST_gn +=
      (f14tmp25_P.AlphasensorLowpassFilter_A_hc)*
      f14tmp25_X.AlphasensorLowpassFilter_CST_gn;
  }

  /* Derivatives for TransferFcn: '<S102>/Stick Prefilter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_bs = f14tmp25_B.Sum1_ds;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_bs += (f14tmp25_P.StickPrefilter_A_i1)*
      f14tmp25_X.StickPrefilter_CSTATE_bs;
  }

  /* Derivatives for TransferFcn: '<S102>/Pitch Rate Lead Filter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_mo = f14tmp25_B.TransferFcn1_n3;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_mo += (f14tmp25_P.PitchRateLeadFilter_A_it)*
      f14tmp25_X.PitchRateLeadFilter_CSTATE_mo;
  }

  /* Derivatives for TransferFcn: '<S102>/Proportional plus integral compensator' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompe_k = f14tmp25_B.Sum2_il;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompe_k +=
      (f14tmp25_P.Proportionalplusintegralcomp_dl)*
      f14tmp25_X.Proportionalplusintegralcompe_k;
  }

  /* Derivatives for TransferFcn: '<S106>/Transfer Fcn.2' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_bv = f14tmp25_B.Sum1_kk;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_bv += (f14tmp25_P.TransferFcn2_A_ir)*
      f14tmp25_X.TransferFcn2_CSTATE_bv;
  }

  /* Derivatives for TransferFcn: '<S106>/Transfer Fcn.1' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_kr = f14tmp25_B.Sum2_ky;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_kr += (f14tmp25_P.TransferFcn1_A_m5)*
      f14tmp25_X.TransferFcn1_CSTATE_kr;
  }

  /* Derivatives for TransferFcn: '<S17>/Actuator Model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_l = f14tmp25_B.Sum_ab;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_l += (f14tmp25_P.ActuatorModel_A_c)*
      f14tmp25_X.ActuatorModel_CSTATE_l;
  }

  /* Derivatives for TransferFcn: '<S108>/W-gust model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_h[0] = f14tmp25_B.Output_b0;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_h[0] += (f14tmp25_P.Wgustmodel_A_id[0])*
      f14tmp25_X.Wgustmodel_CSTATE_h[0]
      + (f14tmp25_P.Wgustmodel_A_id[1])*f14tmp25_X.Wgustmodel_CSTATE_h[1];
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_h[1]= f14tmp25_X.Wgustmodel_CSTATE_h[0];
  }

  /* Derivatives for TransferFcn: '<S108>/Q-gust model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_kp = f14tmp25_B.Wgustmodel_o;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_kp += (f14tmp25_P.Qgustmodel_A_n)*
      f14tmp25_X.Qgustmodel_CSTATE_kp;
  }

  /* Derivatives for TransferFcn: '<S107>/Alpha-sensor Low-pass Filter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CSTA_p = f14tmp25_B.Gain5_a;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CSTA_p +=
      (f14tmp25_P.AlphasensorLowpassFilter_A_k)*
      f14tmp25_X.AlphasensorLowpassFilter_CSTA_p;
  }

  /* Derivatives for TransferFcn: '<S107>/Stick Prefilter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_pr = f14tmp25_B.Sum1_cx;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_pr += (f14tmp25_P.StickPrefilter_A_em)*
      f14tmp25_X.StickPrefilter_CSTATE_pr;
  }

  /* Derivatives for TransferFcn: '<S107>/Pitch Rate Lead Filter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_fn = f14tmp25_B.TransferFcn1_ep;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_fn += (f14tmp25_P.PitchRateLeadFilter_A_pn)*
      f14tmp25_X.PitchRateLeadFilter_CSTATE_fn;
  }

  /* Derivatives for TransferFcn: '<S107>/Proportional plus integral compensator' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Proportionalplusintegralcomp_lg = f14tmp25_B.Sum2_e1;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Proportionalplusintegralcomp_lg +=
      (f14tmp25_P.Proportionalplusintegralcomp_jv)*
      f14tmp25_X.Proportionalplusintegralcomp_lg;
  }

  /* Derivatives for TransferFcn: '<S111>/Transfer Fcn.2' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_ku = f14tmp25_B.Sum1_hu;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_ku += (f14tmp25_P.TransferFcn2_A_p)*
      f14tmp25_X.TransferFcn2_CSTATE_ku;
  }

  /* Derivatives for TransferFcn: '<S111>/Transfer Fcn.1' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_ku = f14tmp25_B.Sum2_oq;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_ku += (f14tmp25_P.TransferFcn1_A_dw)*
      f14tmp25_X.TransferFcn1_CSTATE_ku;
  }

  /* Derivatives for TransferFcn: '<S18>/Actuator Model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_hh = f14tmp25_B.Sum_em;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_hh += (f14tmp25_P.ActuatorModel_A_af)*
      f14tmp25_X.ActuatorModel_CSTATE_hh;
  }

  /* Derivatives for TransferFcn: '<S113>/W-gust model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_e5[0] = f14tmp25_B.Output_dm;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_e5[0] += (f14tmp25_P.Wgustmodel_A_do[0])*
      f14tmp25_X.Wgustmodel_CSTATE_e5[0]
      + (f14tmp25_P.Wgustmodel_A_do[1])*f14tmp25_X.Wgustmodel_CSTATE_e5[1];
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_e5[1]= f14tmp25_X.Wgustmodel_CSTATE_e5[0];
  }

  /* Derivatives for TransferFcn: '<S113>/Q-gust model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_f = f14tmp25_B.Wgustmodel_a1;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_f += (f14tmp25_P.Qgustmodel_A_bl)*
      f14tmp25_X.Qgustmodel_CSTATE_f;
  }

  /* Derivatives for TransferFcn: '<S112>/Alpha-sensor Low-pass Filter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CST_ba = f14tmp25_B.Gain5_l5;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CST_ba +=
      (f14tmp25_P.AlphasensorLowpassFilter_A_cp)*
      f14tmp25_X.AlphasensorLowpassFilter_CST_ba;
  }

  /* Derivatives for TransferFcn: '<S112>/Stick Prefilter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_p3 = f14tmp25_B.Sum1_i1;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_p3 += (f14tmp25_P.StickPrefilter_A_ik)*
      f14tmp25_X.StickPrefilter_CSTATE_p3;
  }

  /* Derivatives for TransferFcn: '<S112>/Pitch Rate Lead Filter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_ke = f14tmp25_B.TransferFcn1_j;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_ke += (f14tmp25_P.PitchRateLeadFilter_A_g0)*
      f14tmp25_X.PitchRateLeadFilter_CSTATE_ke;
  }

  /* Derivatives for TransferFcn: '<S112>/Proportional plus integral compensator' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompe_c = f14tmp25_B.Sum2_n;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompe_c +=
      (f14tmp25_P.Proportionalplusintegralcomp_by)*
      f14tmp25_X.Proportionalplusintegralcompe_c;
  }

  /* Derivatives for TransferFcn: '<S116>/Transfer Fcn.2' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_e = f14tmp25_B.Sum1_fl;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_e += (f14tmp25_P.TransferFcn2_A_jz)*
      f14tmp25_X.TransferFcn2_CSTATE_e;
  }

  /* Derivatives for TransferFcn: '<S116>/Transfer Fcn.1' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_j = f14tmp25_B.Sum2_cx;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_j += (f14tmp25_P.TransferFcn1_A_a)*
      f14tmp25_X.TransferFcn1_CSTATE_j;
  }

  /* Derivatives for TransferFcn: '<S19>/Actuator Model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_p = f14tmp25_B.Sum_kb;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_p += (f14tmp25_P.ActuatorModel_A_pv)*
      f14tmp25_X.ActuatorModel_CSTATE_p;
  }

  /* Derivatives for TransferFcn: '<S118>/W-gust model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_k[0] = f14tmp25_B.Output_k4;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_k[0] += (f14tmp25_P.Wgustmodel_A_b[0])*
      f14tmp25_X.Wgustmodel_CSTATE_k[0]
      + (f14tmp25_P.Wgustmodel_A_b[1])*f14tmp25_X.Wgustmodel_CSTATE_k[1];
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_k[1]= f14tmp25_X.Wgustmodel_CSTATE_k[0];
  }

  /* Derivatives for TransferFcn: '<S118>/Q-gust model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_ad = f14tmp25_B.Wgustmodel_h;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_ad += (f14tmp25_P.Qgustmodel_A_gs)*
      f14tmp25_X.Qgustmodel_CSTATE_ad;
  }

  /* Derivatives for TransferFcn: '<S117>/Alpha-sensor Low-pass Filter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CSTA_k = f14tmp25_B.Gain5_k5;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CSTA_k +=
      (f14tmp25_P.AlphasensorLowpassFilter_A_pm)*
      f14tmp25_X.AlphasensorLowpassFilter_CSTA_k;
  }

  /* Derivatives for TransferFcn: '<S117>/Stick Prefilter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_ju = f14tmp25_B.Sum1_dd;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_ju += (f14tmp25_P.StickPrefilter_A_dg)*
      f14tmp25_X.StickPrefilter_CSTATE_ju;
  }

  /* Derivatives for TransferFcn: '<S117>/Pitch Rate Lead Filter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_ez = f14tmp25_B.TransferFcn1_k;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_ez += (f14tmp25_P.PitchRateLeadFilter_A_pq)*
      f14tmp25_X.PitchRateLeadFilter_CSTATE_ez;
  }

  /* Derivatives for TransferFcn: '<S117>/Proportional plus integral compensator' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Proportionalplusintegralcomp_jd = f14tmp25_B.Sum2_gm;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Proportionalplusintegralcomp_jd +=
      (f14tmp25_P.Proportionalplusintegralcomp_kg)*
      f14tmp25_X.Proportionalplusintegralcomp_jd;
  }

  /* Derivatives for TransferFcn: '<S121>/Transfer Fcn.2' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_kz = f14tmp25_B.Sum1_gg;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_kz += (f14tmp25_P.TransferFcn2_A_c)*
      f14tmp25_X.TransferFcn2_CSTATE_kz;
  }

  /* Derivatives for TransferFcn: '<S121>/Transfer Fcn.1' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_pe = f14tmp25_B.Sum2_oa;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_pe += (f14tmp25_P.TransferFcn1_A_oo)*
      f14tmp25_X.TransferFcn1_CSTATE_pe;
  }

  /* Derivatives for TransferFcn: '<S20>/Actuator Model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_ol = f14tmp25_B.Sum_mb;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_ol += (f14tmp25_P.ActuatorModel_A_gly)*
      f14tmp25_X.ActuatorModel_CSTATE_ol;
  }

  /* Derivatives for TransferFcn: '<S123>/W-gust model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_if[0] = f14tmp25_B.Output_al;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_if[0] += (f14tmp25_P.Wgustmodel_A_lv[0])*
      f14tmp25_X.Wgustmodel_CSTATE_if[0]
      + (f14tmp25_P.Wgustmodel_A_lv[1])*f14tmp25_X.Wgustmodel_CSTATE_if[1];
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_if[1]= f14tmp25_X.Wgustmodel_CSTATE_if[0];
  }

  /* Derivatives for TransferFcn: '<S123>/Q-gust model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_mh = f14tmp25_B.Wgustmodel_ox;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_mh += (f14tmp25_P.Qgustmodel_A_gl)*
      f14tmp25_X.Qgustmodel_CSTATE_mh;
  }

  /* Derivatives for TransferFcn: '<S122>/Alpha-sensor Low-pass Filter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CST_ku = f14tmp25_B.Gain5_cq;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CST_ku +=
      (f14tmp25_P.AlphasensorLowpassFilter_A_a)*
      f14tmp25_X.AlphasensorLowpassFilter_CST_ku;
  }

  /* Derivatives for TransferFcn: '<S122>/Stick Prefilter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_m = f14tmp25_B.Sum1_hc1;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_m += (f14tmp25_P.StickPrefilter_A_ee)*
      f14tmp25_X.StickPrefilter_CSTATE_m;
  }

  /* Derivatives for TransferFcn: '<S122>/Pitch Rate Lead Filter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_f0 = f14tmp25_B.TransferFcn1_iw;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_f0 += (f14tmp25_P.PitchRateLeadFilter_A_m)*
      f14tmp25_X.PitchRateLeadFilter_CSTATE_f0;
  }

  /* Derivatives for TransferFcn: '<S122>/Proportional plus integral compensator' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Proportionalplusintegralcomp_kq = f14tmp25_B.Sum2_f5;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Proportionalplusintegralcomp_kq +=
      (f14tmp25_P.Proportionalplusintegralcomp_mw)*
      f14tmp25_X.Proportionalplusintegralcomp_kq;
  }

  /* Derivatives for TransferFcn: '<S126>/Transfer Fcn.2' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_ar = f14tmp25_B.Sum1_o3;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_ar += (f14tmp25_P.TransferFcn2_A_lz)*
      f14tmp25_X.TransferFcn2_CSTATE_ar;
  }

  /* Derivatives for TransferFcn: '<S126>/Transfer Fcn.1' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_id = f14tmp25_B.Sum2_pt;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_id += (f14tmp25_P.TransferFcn1_A_by)*
      f14tmp25_X.TransferFcn1_CSTATE_id;
  }

  /* Derivatives for TransferFcn: '<S21>/Actuator Model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_g = f14tmp25_B.Sum_cd;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_g += (f14tmp25_P.ActuatorModel_A_o2)*
      f14tmp25_X.ActuatorModel_CSTATE_g;
  }

  /* Derivatives for TransferFcn: '<S128>/W-gust model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_iv[0] = f14tmp25_B.Output_bc;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_iv[0] += (f14tmp25_P.Wgustmodel_A_ei[0])*
      f14tmp25_X.Wgustmodel_CSTATE_iv[0]
      + (f14tmp25_P.Wgustmodel_A_ei[1])*f14tmp25_X.Wgustmodel_CSTATE_iv[1];
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_iv[1]= f14tmp25_X.Wgustmodel_CSTATE_iv[0];
  }

  /* Derivatives for TransferFcn: '<S128>/Q-gust model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_ob = f14tmp25_B.Wgustmodel_o4;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_ob += (f14tmp25_P.Qgustmodel_A_ad)*
      f14tmp25_X.Qgustmodel_CSTATE_ob;
  }

  /* Derivatives for TransferFcn: '<S127>/Alpha-sensor Low-pass Filter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CST_pj = f14tmp25_B.Gain5_o4;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CST_pj +=
      (f14tmp25_P.AlphasensorLowpassFilter_A_od)*
      f14tmp25_X.AlphasensorLowpassFilter_CST_pj;
  }

  /* Derivatives for TransferFcn: '<S127>/Stick Prefilter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_ah = f14tmp25_B.Sum1_fih;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_ah += (f14tmp25_P.StickPrefilter_A_n)*
      f14tmp25_X.StickPrefilter_CSTATE_ah;
  }

  /* Derivatives for TransferFcn: '<S127>/Pitch Rate Lead Filter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_p = f14tmp25_B.TransferFcn1_f;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_p += (f14tmp25_P.PitchRateLeadFilter_A_itf)*
      f14tmp25_X.PitchRateLeadFilter_CSTATE_p;
  }

  /* Derivatives for TransferFcn: '<S127>/Proportional plus integral compensator' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Proportionalplusintegralcomp_jw = f14tmp25_B.Sum2_oh;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Proportionalplusintegralcomp_jw +=
      (f14tmp25_P.Proportionalplusintegralcomp_lo)*
      f14tmp25_X.Proportionalplusintegralcomp_jw;
  }

  /* Derivatives for TransferFcn: '<S131>/Transfer Fcn.2' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_lp = f14tmp25_B.Sum1_n02;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_lp += (f14tmp25_P.TransferFcn2_A_m)*
      f14tmp25_X.TransferFcn2_CSTATE_lp;
  }

  /* Derivatives for TransferFcn: '<S131>/Transfer Fcn.1' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_je = f14tmp25_B.Sum2_bul;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_je += (f14tmp25_P.TransferFcn1_A_cw)*
      f14tmp25_X.TransferFcn1_CSTATE_je;
  }

  /* Derivatives for TransferFcn: '<S22>/Actuator Model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_fk = f14tmp25_B.Sum_cy;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_fk += (f14tmp25_P.ActuatorModel_A_gz)*
      f14tmp25_X.ActuatorModel_CSTATE_fk;
  }

  /* Derivatives for TransferFcn: '<S133>/W-gust model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_gw[0] = f14tmp25_B.Output_hu;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_gw[0] += (f14tmp25_P.Wgustmodel_A_c[0])*
      f14tmp25_X.Wgustmodel_CSTATE_gw[0]
      + (f14tmp25_P.Wgustmodel_A_c[1])*f14tmp25_X.Wgustmodel_CSTATE_gw[1];
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_gw[1]= f14tmp25_X.Wgustmodel_CSTATE_gw[0];
  }

  /* Derivatives for TransferFcn: '<S133>/Q-gust model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_e = f14tmp25_B.Wgustmodel_fj;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_e += (f14tmp25_P.Qgustmodel_A_el)*
      f14tmp25_X.Qgustmodel_CSTATE_e;
  }

  /* Derivatives for TransferFcn: '<S132>/Alpha-sensor Low-pass Filter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CSTA_d = f14tmp25_B.Gain5_et;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CSTA_d +=
      (f14tmp25_P.AlphasensorLowpassFilter_A_j)*
      f14tmp25_X.AlphasensorLowpassFilter_CSTA_d;
  }

  /* Derivatives for TransferFcn: '<S132>/Stick Prefilter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_o = f14tmp25_B.Sum1_ec;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_o += (f14tmp25_P.StickPrefilter_A_cc)*
      f14tmp25_X.StickPrefilter_CSTATE_o;
  }

  /* Derivatives for TransferFcn: '<S132>/Pitch Rate Lead Filter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_a = f14tmp25_B.TransferFcn1_nf;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_a += (f14tmp25_P.PitchRateLeadFilter_A_gq)*
      f14tmp25_X.PitchRateLeadFilter_CSTATE_a;
  }

  /* Derivatives for TransferFcn: '<S132>/Proportional plus integral compensator' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Proportionalplusintegralcomp_iz = f14tmp25_B.Sum2_d;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Proportionalplusintegralcomp_iz +=
      (f14tmp25_P.Proportionalplusintegralcomp_cd)*
      f14tmp25_X.Proportionalplusintegralcomp_iz;
  }

  /* Derivatives for TransferFcn: '<S136>/Transfer Fcn.2' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_aw = f14tmp25_B.Sum1_m5;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_aw += (f14tmp25_P.TransferFcn2_A_e)*
      f14tmp25_X.TransferFcn2_CSTATE_aw;
  }

  /* Derivatives for TransferFcn: '<S136>/Transfer Fcn.1' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_be = f14tmp25_B.Sum2_m4;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_be += (f14tmp25_P.TransferFcn1_A_f)*
      f14tmp25_X.TransferFcn1_CSTATE_be;
  }

  /* Derivatives for TransferFcn: '<S23>/Actuator Model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_pq = f14tmp25_B.Sum_nsk;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_pq += (f14tmp25_P.ActuatorModel_A_pn)*
      f14tmp25_X.ActuatorModel_CSTATE_pq;
  }

  /* Derivatives for TransferFcn: '<S138>/W-gust model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_c[0] = f14tmp25_B.Output_p;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_c[0] += (f14tmp25_P.Wgustmodel_A_g2[0])*
      f14tmp25_X.Wgustmodel_CSTATE_c[0]
      + (f14tmp25_P.Wgustmodel_A_g2[1])*f14tmp25_X.Wgustmodel_CSTATE_c[1];
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_c[1]= f14tmp25_X.Wgustmodel_CSTATE_c[0];
  }

  /* Derivatives for TransferFcn: '<S138>/Q-gust model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_fh = f14tmp25_B.Wgustmodel_hc;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_fh += (f14tmp25_P.Qgustmodel_A_d3)*
      f14tmp25_X.Qgustmodel_CSTATE_fh;
  }

  /* Derivatives for TransferFcn: '<S137>/Alpha-sensor Low-pass Filter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CST_b1 = f14tmp25_B.Gain5_mu;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CST_b1 +=
      (f14tmp25_P.AlphasensorLowpassFilter_A_n)*
      f14tmp25_X.AlphasensorLowpassFilter_CST_b1;
  }

  /* Derivatives for TransferFcn: '<S137>/Stick Prefilter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_p2 = f14tmp25_B.Sum1_ni;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_p2 += (f14tmp25_P.StickPrefilter_A_ng)*
      f14tmp25_X.StickPrefilter_CSTATE_p2;
  }

  /* Derivatives for TransferFcn: '<S137>/Pitch Rate Lead Filter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_au = f14tmp25_B.TransferFcn1_d;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_au += (f14tmp25_P.PitchRateLeadFilter_A_lo)*
      f14tmp25_X.PitchRateLeadFilter_CSTATE_au;
  }

  /* Derivatives for TransferFcn: '<S137>/Proportional plus integral compensator' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Proportionalplusintegralcomp_nm = f14tmp25_B.Sum2_h;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Proportionalplusintegralcomp_nm +=
      (f14tmp25_P.Proportionalplusintegralcomp_p1)*
      f14tmp25_X.Proportionalplusintegralcomp_nm;
  }

  /* Derivatives for TransferFcn: '<S141>/Transfer Fcn.2' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_ms = f14tmp25_B.Sum1_flb;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_ms += (f14tmp25_P.TransferFcn2_A_ja)*
      f14tmp25_X.TransferFcn2_CSTATE_ms;
  }

  /* Derivatives for TransferFcn: '<S141>/Transfer Fcn.1' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_nz = f14tmp25_B.Sum2_p1;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_nz += (f14tmp25_P.TransferFcn1_A_fq)*
      f14tmp25_X.TransferFcn1_CSTATE_nz;
  }

  /* Derivatives for TransferFcn: '<S24>/Actuator Model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_fb = f14tmp25_B.Sum_lq;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_fb += (f14tmp25_P.ActuatorModel_A_b1)*
      f14tmp25_X.ActuatorModel_CSTATE_fb;
  }

  /* Derivatives for TransferFcn: '<S143>/W-gust model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_h3[0] = f14tmp25_B.Output_o4;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_h3[0] += (f14tmp25_P.Wgustmodel_A_dm[0])*
      f14tmp25_X.Wgustmodel_CSTATE_h3[0]
      + (f14tmp25_P.Wgustmodel_A_dm[1])*f14tmp25_X.Wgustmodel_CSTATE_h3[1];
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_h3[1]= f14tmp25_X.Wgustmodel_CSTATE_h3[0];
  }

  /* Derivatives for TransferFcn: '<S143>/Q-gust model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_c = f14tmp25_B.Wgustmodel_il;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_c += (f14tmp25_P.Qgustmodel_A_mp)*
      f14tmp25_X.Qgustmodel_CSTATE_c;
  }

  /* Derivatives for TransferFcn: '<S142>/Alpha-sensor Low-pass Filter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CST_jw = f14tmp25_B.Gain5_m5;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CST_jw +=
      (f14tmp25_P.AlphasensorLowpassFilter_A_l)*
      f14tmp25_X.AlphasensorLowpassFilter_CST_jw;
  }

  /* Derivatives for TransferFcn: '<S142>/Stick Prefilter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_ns = f14tmp25_B.Sum1_jty;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_ns += (f14tmp25_P.StickPrefilter_A_m)*
      f14tmp25_X.StickPrefilter_CSTATE_ns;
  }

  /* Derivatives for TransferFcn: '<S142>/Pitch Rate Lead Filter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_ds = f14tmp25_B.TransferFcn1_l;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_ds += (f14tmp25_P.PitchRateLeadFilter_A_f)*
      f14tmp25_X.PitchRateLeadFilter_CSTATE_ds;
  }

  /* Derivatives for TransferFcn: '<S142>/Proportional plus integral compensator' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompe_a = f14tmp25_B.Sum2_fw;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompe_a +=
      (f14tmp25_P.Proportionalplusintegralcom_oyd)*
      f14tmp25_X.Proportionalplusintegralcompe_a;
  }

  /* Derivatives for TransferFcn: '<S146>/Transfer Fcn.2' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_bk = f14tmp25_B.Sum1_pn;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE_bk += (f14tmp25_P.TransferFcn2_A_bx)*
      f14tmp25_X.TransferFcn2_CSTATE_bk;
  }

  /* Derivatives for TransferFcn: '<S146>/Transfer Fcn.1' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_gr = f14tmp25_B.Sum2_hz;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE_gr += (f14tmp25_P.TransferFcn1_A_cm)*
      f14tmp25_X.TransferFcn1_CSTATE_gr;
  }

  /* Derivatives for TransferFcn: '<S25>/Actuator Model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_iv = f14tmp25_B.Sum_j;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE_iv += (f14tmp25_P.ActuatorModel_A_l5)*
      f14tmp25_X.ActuatorModel_CSTATE_iv;
  }

  /* Derivatives for TransferFcn: '<S148>/W-gust model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_b[0] = f14tmp25_B.Output_dn;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_b[0] += (f14tmp25_P.Wgustmodel_A_p[0])*
      f14tmp25_X.Wgustmodel_CSTATE_b[0]
      + (f14tmp25_P.Wgustmodel_A_p[1])*f14tmp25_X.Wgustmodel_CSTATE_b[1];
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE_b[1]= f14tmp25_X.Wgustmodel_CSTATE_b[0];
  }

  /* Derivatives for TransferFcn: '<S148>/Q-gust model' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_lb = f14tmp25_B.Wgustmodel_k;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE_lb += (f14tmp25_P.Qgustmodel_A_bh)*
      f14tmp25_X.Qgustmodel_CSTATE_lb;
  }

  /* Derivatives for TransferFcn: '<S147>/Alpha-sensor Low-pass Filter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CST_iy = f14tmp25_B.Gain5_cl;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CST_iy +=
      (f14tmp25_P.AlphasensorLowpassFilter_A_fm)*
      f14tmp25_X.AlphasensorLowpassFilter_CST_iy;
  }

  /* Derivatives for TransferFcn: '<S147>/Stick Prefilter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_pb = f14tmp25_B.Sum1_oz;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE_pb += (f14tmp25_P.StickPrefilter_A_aj)*
      f14tmp25_X.StickPrefilter_CSTATE_pb;
  }

  /* Derivatives for TransferFcn: '<S147>/Pitch Rate Lead Filter' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_ak = f14tmp25_B.TransferFcn1_jd;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE_ak += (f14tmp25_P.PitchRateLeadFilter_A_n2)*
      f14tmp25_X.PitchRateLeadFilter_CSTATE_ak;
  }

  /* Derivatives for TransferFcn: '<S147>/Proportional plus integral compensator' */
  {
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Proportionalplusintegralcomp_ab = f14tmp25_B.Sum2_jy;
    ((StateDerivatives_f14tmp25 *) f14tmp25_rtM->ModelData.derivs)
      ->Proportionalplusintegralcomp_ab +=
      (f14tmp25_P.Proportionalplusintegralcomp_io)*
      f14tmp25_X.Proportionalplusintegralcomp_ab;
  }
}

/* Model initialize function */
void f14tmp25_initialize(void)
{
  {
    uint32_T tseed;
    int32_T r;
    int32_T t;
    real_T tmp;

    /* Start for RandomNumber: '<S30>/White Noise' */
    tmp = floor(f14tmp25_P.WhiteNoise_Seed);
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

    f14tmp25_DWork.RandSeed = tseed;
    f14tmp25_DWork.NextOutput = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp25_DWork.RandSeed) * f14tmp25_P.WhiteNoise_StdDev +
      f14tmp25_P.WhiteNoise_Mean;

    /* End of Start for RandomNumber: '<S30>/White Noise' */
    /* Start for RandomNumber: '<S35>/White Noise' */
    tmp = floor(f14tmp25_P.WhiteNoise_Seed_i);
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

    f14tmp25_DWork.RandSeed_n = tseed;
    f14tmp25_DWork.NextOutput_f = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp25_DWork.RandSeed_n) * f14tmp25_P.WhiteNoise_StdDev_n +
      f14tmp25_P.WhiteNoise_Mean_j;

    /* End of Start for RandomNumber: '<S35>/White Noise' */
    /* Start for RandomNumber: '<S40>/White Noise' */
    tmp = floor(f14tmp25_P.WhiteNoise_Seed_g);
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

    f14tmp25_DWork.RandSeed_b = tseed;
    f14tmp25_DWork.NextOutput_n = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp25_DWork.RandSeed_b) * f14tmp25_P.WhiteNoise_StdDev_e +
      f14tmp25_P.WhiteNoise_Mean_n;

    /* End of Start for RandomNumber: '<S40>/White Noise' */
    /* Start for RandomNumber: '<S45>/White Noise' */
    tmp = floor(f14tmp25_P.WhiteNoise_Seed_e);
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

    f14tmp25_DWork.RandSeed_c = tseed;
    f14tmp25_DWork.NextOutput_g = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp25_DWork.RandSeed_c) * f14tmp25_P.WhiteNoise_StdDev_l +
      f14tmp25_P.WhiteNoise_Mean_c;

    /* End of Start for RandomNumber: '<S45>/White Noise' */
    /* Start for RandomNumber: '<S50>/White Noise' */
    tmp = floor(f14tmp25_P.WhiteNoise_Seed_p);
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

    f14tmp25_DWork.RandSeed_h = tseed;
    f14tmp25_DWork.NextOutput_h = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp25_DWork.RandSeed_h) * f14tmp25_P.WhiteNoise_StdDev_k +
      f14tmp25_P.WhiteNoise_Mean_h;

    /* End of Start for RandomNumber: '<S50>/White Noise' */
    /* Start for RandomNumber: '<S55>/White Noise' */
    tmp = floor(f14tmp25_P.WhiteNoise_Seed_b);
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

    f14tmp25_DWork.RandSeed_d = tseed;
    f14tmp25_DWork.NextOutput_c = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp25_DWork.RandSeed_d) * f14tmp25_P.WhiteNoise_StdDev_p +
      f14tmp25_P.WhiteNoise_Mean_hl;

    /* End of Start for RandomNumber: '<S55>/White Noise' */
    /* Start for RandomNumber: '<S60>/White Noise' */
    tmp = floor(f14tmp25_P.WhiteNoise_Seed_gf);
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

    f14tmp25_DWork.RandSeed_f = tseed;
    f14tmp25_DWork.NextOutput_j = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp25_DWork.RandSeed_f) * f14tmp25_P.WhiteNoise_StdDev_i +
      f14tmp25_P.WhiteNoise_Mean_l;

    /* End of Start for RandomNumber: '<S60>/White Noise' */
    /* Start for RandomNumber: '<S65>/White Noise' */
    tmp = floor(f14tmp25_P.WhiteNoise_Seed_c);
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

    f14tmp25_DWork.RandSeed_g = tseed;
    f14tmp25_DWork.NextOutput_d = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp25_DWork.RandSeed_g) * f14tmp25_P.WhiteNoise_StdDev_h +
      f14tmp25_P.WhiteNoise_Mean_no;

    /* End of Start for RandomNumber: '<S65>/White Noise' */
    /* Start for RandomNumber: '<S70>/White Noise' */
    tmp = floor(f14tmp25_P.WhiteNoise_Seed_m);
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

    f14tmp25_DWork.RandSeed_bq = tseed;
    f14tmp25_DWork.NextOutput_l = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp25_DWork.RandSeed_bq) * f14tmp25_P.WhiteNoise_StdDev_p1 +
      f14tmp25_P.WhiteNoise_Mean_d;

    /* End of Start for RandomNumber: '<S70>/White Noise' */
    /* Start for RandomNumber: '<S75>/White Noise' */
    tmp = floor(f14tmp25_P.WhiteNoise_Seed_p0);
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

    f14tmp25_DWork.RandSeed_e = tseed;
    f14tmp25_DWork.NextOutput_a = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp25_DWork.RandSeed_e) * f14tmp25_P.WhiteNoise_StdDev_g +
      f14tmp25_P.WhiteNoise_Mean_m;

    /* End of Start for RandomNumber: '<S75>/White Noise' */
    /* Start for RandomNumber: '<S80>/White Noise' */
    tmp = floor(f14tmp25_P.WhiteNoise_Seed_o);
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

    f14tmp25_DWork.RandSeed_e1 = tseed;
    f14tmp25_DWork.NextOutput_ag = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp25_DWork.RandSeed_e1) * f14tmp25_P.WhiteNoise_StdDev_m +
      f14tmp25_P.WhiteNoise_Mean_dw;

    /* End of Start for RandomNumber: '<S80>/White Noise' */
    /* Start for RandomNumber: '<S85>/White Noise' */
    tmp = floor(f14tmp25_P.WhiteNoise_Seed_d);
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

    f14tmp25_DWork.RandSeed_bo = tseed;
    f14tmp25_DWork.NextOutput_m = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp25_DWork.RandSeed_bo) * f14tmp25_P.WhiteNoise_StdDev_ng +
      f14tmp25_P.WhiteNoise_Mean_k;

    /* End of Start for RandomNumber: '<S85>/White Noise' */
    /* Start for RandomNumber: '<S90>/White Noise' */
    tmp = floor(f14tmp25_P.WhiteNoise_Seed_j);
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

    f14tmp25_DWork.RandSeed_eo = tseed;
    f14tmp25_DWork.NextOutput_hq = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp25_DWork.RandSeed_eo) * f14tmp25_P.WhiteNoise_StdDev_gu +
      f14tmp25_P.WhiteNoise_Mean_kt;

    /* End of Start for RandomNumber: '<S90>/White Noise' */
    /* Start for RandomNumber: '<S95>/White Noise' */
    tmp = floor(f14tmp25_P.WhiteNoise_Seed_pj);
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

    f14tmp25_DWork.RandSeed_dr = tseed;
    f14tmp25_DWork.NextOutput_nm = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp25_DWork.RandSeed_dr) * f14tmp25_P.WhiteNoise_StdDev_pf +
      f14tmp25_P.WhiteNoise_Mean_ko;

    /* End of Start for RandomNumber: '<S95>/White Noise' */
    /* Start for RandomNumber: '<S100>/White Noise' */
    tmp = floor(f14tmp25_P.WhiteNoise_Seed_a);
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

    f14tmp25_DWork.RandSeed_m = tseed;
    f14tmp25_DWork.NextOutput_i = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp25_DWork.RandSeed_m) * f14tmp25_P.WhiteNoise_StdDev_kj +
      f14tmp25_P.WhiteNoise_Mean_p;

    /* End of Start for RandomNumber: '<S100>/White Noise' */
    /* Start for RandomNumber: '<S105>/White Noise' */
    tmp = floor(f14tmp25_P.WhiteNoise_Seed_l);
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

    f14tmp25_DWork.RandSeed_md = tseed;
    f14tmp25_DWork.NextOutput_o = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp25_DWork.RandSeed_md) * f14tmp25_P.WhiteNoise_StdDev_pd +
      f14tmp25_P.WhiteNoise_Mean_b;

    /* End of Start for RandomNumber: '<S105>/White Noise' */
    /* Start for RandomNumber: '<S110>/White Noise' */
    tmp = floor(f14tmp25_P.WhiteNoise_Seed_pi);
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

    f14tmp25_DWork.RandSeed_fu = tseed;
    f14tmp25_DWork.NextOutput_h5 = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp25_DWork.RandSeed_fu) * f14tmp25_P.WhiteNoise_StdDev_a +
      f14tmp25_P.WhiteNoise_Mean_db;

    /* End of Start for RandomNumber: '<S110>/White Noise' */
    /* Start for RandomNumber: '<S115>/White Noise' */
    tmp = floor(f14tmp25_P.WhiteNoise_Seed_p4);
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

    f14tmp25_DWork.RandSeed_i = tseed;
    f14tmp25_DWork.NextOutput_ai = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp25_DWork.RandSeed_i) * f14tmp25_P.WhiteNoise_StdDev_mj +
      f14tmp25_P.WhiteNoise_Mean_i;

    /* End of Start for RandomNumber: '<S115>/White Noise' */
    /* Start for RandomNumber: '<S120>/White Noise' */
    tmp = floor(f14tmp25_P.WhiteNoise_Seed_cp);
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

    f14tmp25_DWork.RandSeed_fk = tseed;
    f14tmp25_DWork.NextOutput_am = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp25_DWork.RandSeed_fk) * f14tmp25_P.WhiteNoise_StdDev_f +
      f14tmp25_P.WhiteNoise_Mean_nk;

    /* End of Start for RandomNumber: '<S120>/White Noise' */
    /* Start for RandomNumber: '<S125>/White Noise' */
    tmp = floor(f14tmp25_P.WhiteNoise_Seed_gu);
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

    f14tmp25_DWork.RandSeed_dd = tseed;
    f14tmp25_DWork.NextOutput_e = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp25_DWork.RandSeed_dd) * f14tmp25_P.WhiteNoise_StdDev_kq +
      f14tmp25_P.WhiteNoise_Mean_bf;

    /* End of Start for RandomNumber: '<S125>/White Noise' */
    /* Start for RandomNumber: '<S130>/White Noise' */
    tmp = floor(f14tmp25_P.WhiteNoise_Seed_dk);
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

    f14tmp25_DWork.RandSeed_j = tseed;
    f14tmp25_DWork.NextOutput_k = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp25_DWork.RandSeed_j) * f14tmp25_P.WhiteNoise_StdDev_fh +
      f14tmp25_P.WhiteNoise_Mean_g;

    /* End of Start for RandomNumber: '<S130>/White Noise' */
    /* Start for RandomNumber: '<S135>/White Noise' */
    tmp = floor(f14tmp25_P.WhiteNoise_Seed_cc);
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

    f14tmp25_DWork.RandSeed_k = tseed;
    f14tmp25_DWork.NextOutput_ct = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp25_DWork.RandSeed_k) * f14tmp25_P.WhiteNoise_StdDev_m5 +
      f14tmp25_P.WhiteNoise_Mean_jo;

    /* End of Start for RandomNumber: '<S135>/White Noise' */
    /* Start for RandomNumber: '<S140>/White Noise' */
    tmp = floor(f14tmp25_P.WhiteNoise_Seed_ev);
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

    f14tmp25_DWork.RandSeed_ju = tseed;
    f14tmp25_DWork.NextOutput_d2 = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp25_DWork.RandSeed_ju) * f14tmp25_P.WhiteNoise_StdDev_id +
      f14tmp25_P.WhiteNoise_Mean_iu;

    /* End of Start for RandomNumber: '<S140>/White Noise' */
    /* Start for RandomNumber: '<S145>/White Noise' */
    tmp = floor(f14tmp25_P.WhiteNoise_Seed_cm);
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

    f14tmp25_DWork.RandSeed_nb = tseed;
    f14tmp25_DWork.NextOutput_g3 = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp25_DWork.RandSeed_nb) * f14tmp25_P.WhiteNoise_StdDev_pe +
      f14tmp25_P.WhiteNoise_Mean_f;

    /* End of Start for RandomNumber: '<S145>/White Noise' */
    /* Start for RandomNumber: '<S150>/White Noise' */
    tmp = floor(f14tmp25_P.WhiteNoise_Seed_ej);
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

    f14tmp25_DWork.RandSeed_ju4 = tseed;
    f14tmp25_DWork.NextOutput_ip = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp25_DWork.RandSeed_ju4) * f14tmp25_P.WhiteNoise_StdDev_g0 +
      f14tmp25_P.WhiteNoise_Mean_o;

    /* End of Start for RandomNumber: '<S150>/White Noise' */
  }

  /* InitializeConditions for TransferFcn: '<S26>/Transfer Fcn.2' */
  f14tmp25_X.TransferFcn2_CSTATE = 0.0;

  /* InitializeConditions for Derivative: '<S29>/Derivative' */
  f14tmp25_DWork.Derivative_RWORK.TimeStampA = rtInf;
  f14tmp25_DWork.Derivative_RWORK.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S26>/Transfer Fcn.1' */
  f14tmp25_X.TransferFcn1_CSTATE = 0.0;

  /* InitializeConditions for Derivative: '<S29>/Derivative1' */
  f14tmp25_DWork.Derivative1_RWORK.TimeStampA = rtInf;
  f14tmp25_DWork.Derivative1_RWORK.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S1>/Actuator Model' */
  f14tmp25_X.ActuatorModel_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S28>/W-gust model' */
  f14tmp25_X.Wgustmodel_CSTATE[0] = 0.0;
  f14tmp25_X.Wgustmodel_CSTATE[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S28>/Q-gust model' */
  f14tmp25_X.Qgustmodel_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S27>/Alpha-sensor Low-pass Filter' */
  f14tmp25_X.AlphasensorLowpassFilter_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S27>/Stick Prefilter' */
  f14tmp25_X.StickPrefilter_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S27>/Pitch Rate Lead Filter' */
  f14tmp25_X.PitchRateLeadFilter_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S27>/Proportional plus integral compensator' */
  f14tmp25_X.Proportionalplusintegralcompens = 0.0;

  /* InitializeConditions for TransferFcn: '<S31>/Transfer Fcn.2' */
  f14tmp25_X.TransferFcn2_CSTATE_h = 0.0;

  /* InitializeConditions for Derivative: '<S34>/Derivative' */
  f14tmp25_DWork.Derivative_RWORK_f.TimeStampA = rtInf;
  f14tmp25_DWork.Derivative_RWORK_f.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S31>/Transfer Fcn.1' */
  f14tmp25_X.TransferFcn1_CSTATE_p = 0.0;

  /* InitializeConditions for Derivative: '<S34>/Derivative1' */
  f14tmp25_DWork.Derivative1_RWORK_o.TimeStampA = rtInf;
  f14tmp25_DWork.Derivative1_RWORK_o.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S2>/Actuator Model' */
  f14tmp25_X.ActuatorModel_CSTATE_a = 0.0;

  /* InitializeConditions for TransferFcn: '<S33>/W-gust model' */
  f14tmp25_X.Wgustmodel_CSTATE_f[0] = 0.0;
  f14tmp25_X.Wgustmodel_CSTATE_f[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S33>/Q-gust model' */
  f14tmp25_X.Qgustmodel_CSTATE_d = 0.0;

  /* InitializeConditions for TransferFcn: '<S32>/Alpha-sensor Low-pass Filter' */
  f14tmp25_X.AlphasensorLowpassFilter_CSTA_g = 0.0;

  /* InitializeConditions for TransferFcn: '<S32>/Stick Prefilter' */
  f14tmp25_X.StickPrefilter_CSTATE_a = 0.0;

  /* InitializeConditions for TransferFcn: '<S32>/Pitch Rate Lead Filter' */
  f14tmp25_X.PitchRateLeadFilter_CSTATE_k = 0.0;

  /* InitializeConditions for TransferFcn: '<S32>/Proportional plus integral compensator' */
  f14tmp25_X.Proportionalplusintegralcompe_n = 0.0;

  /* InitializeConditions for TransferFcn: '<S36>/Transfer Fcn.2' */
  f14tmp25_X.TransferFcn2_CSTATE_g = 0.0;

  /* InitializeConditions for Derivative: '<S39>/Derivative' */
  f14tmp25_DWork.Derivative_RWORK_p.TimeStampA = rtInf;
  f14tmp25_DWork.Derivative_RWORK_p.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S36>/Transfer Fcn.1' */
  f14tmp25_X.TransferFcn1_CSTATE_o = 0.0;

  /* InitializeConditions for Derivative: '<S39>/Derivative1' */
  f14tmp25_DWork.Derivative1_RWORK_c.TimeStampA = rtInf;
  f14tmp25_DWork.Derivative1_RWORK_c.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S3>/Actuator Model' */
  f14tmp25_X.ActuatorModel_CSTATE_j = 0.0;

  /* InitializeConditions for TransferFcn: '<S38>/W-gust model' */
  f14tmp25_X.Wgustmodel_CSTATE_m[0] = 0.0;
  f14tmp25_X.Wgustmodel_CSTATE_m[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S38>/Q-gust model' */
  f14tmp25_X.Qgustmodel_CSTATE_i = 0.0;

  /* InitializeConditions for TransferFcn: '<S37>/Alpha-sensor Low-pass Filter' */
  f14tmp25_X.AlphasensorLowpassFilter_CSTA_e = 0.0;

  /* InitializeConditions for TransferFcn: '<S37>/Stick Prefilter' */
  f14tmp25_X.StickPrefilter_CSTATE_ak = 0.0;

  /* InitializeConditions for TransferFcn: '<S37>/Pitch Rate Lead Filter' */
  f14tmp25_X.PitchRateLeadFilter_CSTATE_m = 0.0;

  /* InitializeConditions for TransferFcn: '<S37>/Proportional plus integral compensator' */
  f14tmp25_X.Proportionalplusintegralcompe_f = 0.0;

  /* InitializeConditions for TransferFcn: '<S41>/Transfer Fcn.2' */
  f14tmp25_X.TransferFcn2_CSTATE_h0 = 0.0;

  /* InitializeConditions for Derivative: '<S44>/Derivative' */
  f14tmp25_DWork.Derivative_RWORK_c.TimeStampA = rtInf;
  f14tmp25_DWork.Derivative_RWORK_c.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S41>/Transfer Fcn.1' */
  f14tmp25_X.TransferFcn1_CSTATE_h = 0.0;

  /* InitializeConditions for Derivative: '<S44>/Derivative1' */
  f14tmp25_DWork.Derivative1_RWORK_d.TimeStampA = rtInf;
  f14tmp25_DWork.Derivative1_RWORK_d.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S4>/Actuator Model' */
  f14tmp25_X.ActuatorModel_CSTATE_h = 0.0;

  /* InitializeConditions for TransferFcn: '<S43>/W-gust model' */
  f14tmp25_X.Wgustmodel_CSTATE_g[0] = 0.0;
  f14tmp25_X.Wgustmodel_CSTATE_g[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S43>/Q-gust model' */
  f14tmp25_X.Qgustmodel_CSTATE_p = 0.0;

  /* InitializeConditions for TransferFcn: '<S42>/Alpha-sensor Low-pass Filter' */
  f14tmp25_X.AlphasensorLowpassFilter_CSTA_j = 0.0;

  /* InitializeConditions for TransferFcn: '<S42>/Stick Prefilter' */
  f14tmp25_X.StickPrefilter_CSTATE_i = 0.0;

  /* InitializeConditions for TransferFcn: '<S42>/Pitch Rate Lead Filter' */
  f14tmp25_X.PitchRateLeadFilter_CSTATE_c = 0.0;

  /* InitializeConditions for TransferFcn: '<S42>/Proportional plus integral compensator' */
  f14tmp25_X.Proportionalplusintegralcompe_g = 0.0;

  /* InitializeConditions for TransferFcn: '<S46>/Transfer Fcn.2' */
  f14tmp25_X.TransferFcn2_CSTATE_m = 0.0;

  /* InitializeConditions for Derivative: '<S49>/Derivative' */
  f14tmp25_DWork.Derivative_RWORK_j.TimeStampA = rtInf;
  f14tmp25_DWork.Derivative_RWORK_j.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S46>/Transfer Fcn.1' */
  f14tmp25_X.TransferFcn1_CSTATE_i = 0.0;

  /* InitializeConditions for Derivative: '<S49>/Derivative1' */
  f14tmp25_DWork.Derivative1_RWORK_e.TimeStampA = rtInf;
  f14tmp25_DWork.Derivative1_RWORK_e.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S5>/Actuator Model' */
  f14tmp25_X.ActuatorModel_CSTATE_f = 0.0;

  /* InitializeConditions for TransferFcn: '<S48>/W-gust model' */
  f14tmp25_X.Wgustmodel_CSTATE_a[0] = 0.0;
  f14tmp25_X.Wgustmodel_CSTATE_a[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S48>/Q-gust model' */
  f14tmp25_X.Qgustmodel_CSTATE_h = 0.0;

  /* InitializeConditions for TransferFcn: '<S47>/Alpha-sensor Low-pass Filter' */
  f14tmp25_X.AlphasensorLowpassFilter_CSTA_c = 0.0;

  /* InitializeConditions for TransferFcn: '<S47>/Stick Prefilter' */
  f14tmp25_X.StickPrefilter_CSTATE_h = 0.0;

  /* InitializeConditions for TransferFcn: '<S47>/Pitch Rate Lead Filter' */
  f14tmp25_X.PitchRateLeadFilter_CSTATE_l = 0.0;

  /* InitializeConditions for TransferFcn: '<S47>/Proportional plus integral compensator' */
  f14tmp25_X.Proportionalplusintegralcomp_gl = 0.0;

  /* InitializeConditions for TransferFcn: '<S51>/Transfer Fcn.2' */
  f14tmp25_X.TransferFcn2_CSTATE_p = 0.0;

  /* InitializeConditions for Derivative: '<S54>/Derivative' */
  f14tmp25_DWork.Derivative_RWORK_h.TimeStampA = rtInf;
  f14tmp25_DWork.Derivative_RWORK_h.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S51>/Transfer Fcn.1' */
  f14tmp25_X.TransferFcn1_CSTATE_n = 0.0;

  /* InitializeConditions for Derivative: '<S54>/Derivative1' */
  f14tmp25_DWork.Derivative1_RWORK_p.TimeStampA = rtInf;
  f14tmp25_DWork.Derivative1_RWORK_p.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S6>/Actuator Model' */
  f14tmp25_X.ActuatorModel_CSTATE_aw = 0.0;

  /* InitializeConditions for TransferFcn: '<S53>/W-gust model' */
  f14tmp25_X.Wgustmodel_CSTATE_j[0] = 0.0;
  f14tmp25_X.Wgustmodel_CSTATE_j[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S53>/Q-gust model' */
  f14tmp25_X.Qgustmodel_CSTATE_pw = 0.0;

  /* InitializeConditions for TransferFcn: '<S52>/Alpha-sensor Low-pass Filter' */
  f14tmp25_X.AlphasensorLowpassFilter_CST_j4 = 0.0;

  /* InitializeConditions for TransferFcn: '<S52>/Stick Prefilter' */
  f14tmp25_X.StickPrefilter_CSTATE_p = 0.0;

  /* InitializeConditions for TransferFcn: '<S52>/Pitch Rate Lead Filter' */
  f14tmp25_X.PitchRateLeadFilter_CSTATE_c5 = 0.0;

  /* InitializeConditions for TransferFcn: '<S52>/Proportional plus integral compensator' */
  f14tmp25_X.Proportionalplusintegralcompe_l = 0.0;

  /* InitializeConditions for TransferFcn: '<S56>/Transfer Fcn.2' */
  f14tmp25_X.TransferFcn2_CSTATE_n = 0.0;

  /* InitializeConditions for Derivative: '<S59>/Derivative' */
  f14tmp25_DWork.Derivative_RWORK_hr.TimeStampA = rtInf;
  f14tmp25_DWork.Derivative_RWORK_hr.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S56>/Transfer Fcn.1' */
  f14tmp25_X.TransferFcn1_CSTATE_b = 0.0;

  /* InitializeConditions for Derivative: '<S59>/Derivative1' */
  f14tmp25_DWork.Derivative1_RWORK_cz.TimeStampA = rtInf;
  f14tmp25_DWork.Derivative1_RWORK_cz.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S7>/Actuator Model' */
  f14tmp25_X.ActuatorModel_CSTATE_k = 0.0;

  /* InitializeConditions for TransferFcn: '<S58>/W-gust model' */
  f14tmp25_X.Wgustmodel_CSTATE_mw[0] = 0.0;
  f14tmp25_X.Wgustmodel_CSTATE_mw[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S58>/Q-gust model' */
  f14tmp25_X.Qgustmodel_CSTATE_l = 0.0;

  /* InitializeConditions for TransferFcn: '<S57>/Alpha-sensor Low-pass Filter' */
  f14tmp25_X.AlphasensorLowpassFilter_CST_ji = 0.0;

  /* InitializeConditions for TransferFcn: '<S57>/Stick Prefilter' */
  f14tmp25_X.StickPrefilter_CSTATE_d = 0.0;

  /* InitializeConditions for TransferFcn: '<S57>/Pitch Rate Lead Filter' */
  f14tmp25_X.PitchRateLeadFilter_CSTATE_j = 0.0;

  /* InitializeConditions for TransferFcn: '<S57>/Proportional plus integral compensator' */
  f14tmp25_X.Proportionalplusintegralcompe_p = 0.0;

  /* InitializeConditions for TransferFcn: '<S61>/Transfer Fcn.2' */
  f14tmp25_X.TransferFcn2_CSTATE_o = 0.0;

  /* InitializeConditions for Derivative: '<S64>/Derivative' */
  f14tmp25_DWork.Derivative_RWORK_b.TimeStampA = rtInf;
  f14tmp25_DWork.Derivative_RWORK_b.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S61>/Transfer Fcn.1' */
  f14tmp25_X.TransferFcn1_CSTATE_nw = 0.0;

  /* InitializeConditions for Derivative: '<S64>/Derivative1' */
  f14tmp25_DWork.Derivative1_RWORK_cb.TimeStampA = rtInf;
  f14tmp25_DWork.Derivative1_RWORK_cb.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S8>/Actuator Model' */
  f14tmp25_X.ActuatorModel_CSTATE_o = 0.0;

  /* InitializeConditions for TransferFcn: '<S63>/W-gust model' */
  f14tmp25_X.Wgustmodel_CSTATE_e[0] = 0.0;
  f14tmp25_X.Wgustmodel_CSTATE_e[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S63>/Q-gust model' */
  f14tmp25_X.Qgustmodel_CSTATE_b = 0.0;

  /* InitializeConditions for TransferFcn: '<S62>/Alpha-sensor Low-pass Filter' */
  f14tmp25_X.AlphasensorLowpassFilter_CST_ep = 0.0;

  /* InitializeConditions for TransferFcn: '<S62>/Stick Prefilter' */
  f14tmp25_X.StickPrefilter_CSTATE_hs = 0.0;

  /* InitializeConditions for TransferFcn: '<S62>/Pitch Rate Lead Filter' */
  f14tmp25_X.PitchRateLeadFilter_CSTATE_h = 0.0;

  /* InitializeConditions for TransferFcn: '<S62>/Proportional plus integral compensator' */
  f14tmp25_X.Proportionalplusintegralcompe_h = 0.0;

  /* InitializeConditions for TransferFcn: '<S66>/Transfer Fcn.2' */
  f14tmp25_X.TransferFcn2_CSTATE_c = 0.0;

  /* InitializeConditions for Derivative: '<S69>/Derivative' */
  f14tmp25_DWork.Derivative_RWORK_jk.TimeStampA = rtInf;
  f14tmp25_DWork.Derivative_RWORK_jk.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S66>/Transfer Fcn.1' */
  f14tmp25_X.TransferFcn1_CSTATE_bm = 0.0;

  /* InitializeConditions for Derivative: '<S69>/Derivative1' */
  f14tmp25_DWork.Derivative1_RWORK_ev.TimeStampA = rtInf;
  f14tmp25_DWork.Derivative1_RWORK_ev.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S9>/Actuator Model' */
  f14tmp25_X.ActuatorModel_CSTATE_ku = 0.0;

  /* InitializeConditions for TransferFcn: '<S68>/W-gust model' */
  f14tmp25_X.Wgustmodel_CSTATE_fj[0] = 0.0;
  f14tmp25_X.Wgustmodel_CSTATE_fj[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S68>/Q-gust model' */
  f14tmp25_X.Qgustmodel_CSTATE_a = 0.0;

  /* InitializeConditions for TransferFcn: '<S67>/Alpha-sensor Low-pass Filter' */
  f14tmp25_X.AlphasensorLowpassFilter_CST_cd = 0.0;

  /* InitializeConditions for TransferFcn: '<S67>/Stick Prefilter' */
  f14tmp25_X.StickPrefilter_CSTATE_f = 0.0;

  /* InitializeConditions for TransferFcn: '<S67>/Pitch Rate Lead Filter' */
  f14tmp25_X.PitchRateLeadFilter_CSTATE_e = 0.0;

  /* InitializeConditions for TransferFcn: '<S67>/Proportional plus integral compensator' */
  f14tmp25_X.Proportionalplusintegralcompe_i = 0.0;

  /* InitializeConditions for TransferFcn: '<S71>/Transfer Fcn.2' */
  f14tmp25_X.TransferFcn2_CSTATE_a = 0.0;

  /* InitializeConditions for Derivative: '<S74>/Derivative' */
  f14tmp25_DWork.Derivative_RWORK_bz.TimeStampA = rtInf;
  f14tmp25_DWork.Derivative_RWORK_bz.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S71>/Transfer Fcn.1' */
  f14tmp25_X.TransferFcn1_CSTATE_m = 0.0;

  /* InitializeConditions for Derivative: '<S74>/Derivative1' */
  f14tmp25_DWork.Derivative1_RWORK_cd.TimeStampA = rtInf;
  f14tmp25_DWork.Derivative1_RWORK_cd.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S10>/Actuator Model' */
  f14tmp25_X.ActuatorModel_CSTATE_c = 0.0;

  /* InitializeConditions for TransferFcn: '<S73>/W-gust model' */
  f14tmp25_X.Wgustmodel_CSTATE_d[0] = 0.0;
  f14tmp25_X.Wgustmodel_CSTATE_d[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S73>/Q-gust model' */
  f14tmp25_X.Qgustmodel_CSTATE_o = 0.0;

  /* InitializeConditions for TransferFcn: '<S72>/Alpha-sensor Low-pass Filter' */
  f14tmp25_X.AlphasensorLowpassFilter_CST_ej = 0.0;

  /* InitializeConditions for TransferFcn: '<S72>/Stick Prefilter' */
  f14tmp25_X.StickPrefilter_CSTATE_n = 0.0;

  /* InitializeConditions for TransferFcn: '<S72>/Pitch Rate Lead Filter' */
  f14tmp25_X.PitchRateLeadFilter_CSTATE_e4 = 0.0;

  /* InitializeConditions for TransferFcn: '<S72>/Proportional plus integral compensator' */
  f14tmp25_X.Proportionalplusintegralcomp_p5 = 0.0;

  /* InitializeConditions for TransferFcn: '<S76>/Transfer Fcn.2' */
  f14tmp25_X.TransferFcn2_CSTATE_l = 0.0;

  /* InitializeConditions for Derivative: '<S79>/Derivative' */
  f14tmp25_DWork.Derivative_RWORK_a.TimeStampA = rtInf;
  f14tmp25_DWork.Derivative_RWORK_a.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S76>/Transfer Fcn.1' */
  f14tmp25_X.TransferFcn1_CSTATE_iz = 0.0;

  /* InitializeConditions for Derivative: '<S79>/Derivative1' */
  f14tmp25_DWork.Derivative1_RWORK_i.TimeStampA = rtInf;
  f14tmp25_DWork.Derivative1_RWORK_i.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S11>/Actuator Model' */
  f14tmp25_X.ActuatorModel_CSTATE_hl = 0.0;

  /* InitializeConditions for TransferFcn: '<S78>/W-gust model' */
  f14tmp25_X.Wgustmodel_CSTATE_mo[0] = 0.0;
  f14tmp25_X.Wgustmodel_CSTATE_mo[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S78>/Q-gust model' */
  f14tmp25_X.Qgustmodel_CSTATE_p3 = 0.0;

  /* InitializeConditions for TransferFcn: '<S77>/Alpha-sensor Low-pass Filter' */
  f14tmp25_X.AlphasensorLowpassFilter_CSTA_i = 0.0;

  /* InitializeConditions for TransferFcn: '<S77>/Stick Prefilter' */
  f14tmp25_X.StickPrefilter_CSTATE_b = 0.0;

  /* InitializeConditions for TransferFcn: '<S77>/Pitch Rate Lead Filter' */
  f14tmp25_X.PitchRateLeadFilter_CSTATE_d = 0.0;

  /* InitializeConditions for TransferFcn: '<S77>/Proportional plus integral compensator' */
  f14tmp25_X.Proportionalplusintegralcomp_he = 0.0;

  /* InitializeConditions for TransferFcn: '<S81>/Transfer Fcn.2' */
  f14tmp25_X.TransferFcn2_CSTATE_b = 0.0;

  /* InitializeConditions for Derivative: '<S84>/Derivative' */
  f14tmp25_DWork.Derivative_RWORK_l.TimeStampA = rtInf;
  f14tmp25_DWork.Derivative_RWORK_l.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S81>/Transfer Fcn.1' */
  f14tmp25_X.TransferFcn1_CSTATE_l = 0.0;

  /* InitializeConditions for Derivative: '<S84>/Derivative1' */
  f14tmp25_DWork.Derivative1_RWORK_eb.TimeStampA = rtInf;
  f14tmp25_DWork.Derivative1_RWORK_eb.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S12>/Actuator Model' */
  f14tmp25_X.ActuatorModel_CSTATE_d = 0.0;

  /* InitializeConditions for TransferFcn: '<S83>/W-gust model' */
  f14tmp25_X.Wgustmodel_CSTATE_n[0] = 0.0;
  f14tmp25_X.Wgustmodel_CSTATE_n[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S83>/Q-gust model' */
  f14tmp25_X.Qgustmodel_CSTATE_g = 0.0;

  /* InitializeConditions for TransferFcn: '<S82>/Alpha-sensor Low-pass Filter' */
  f14tmp25_X.AlphasensorLowpassFilter_CSTA_b = 0.0;

  /* InitializeConditions for TransferFcn: '<S82>/Stick Prefilter' */
  f14tmp25_X.StickPrefilter_CSTATE_j = 0.0;

  /* InitializeConditions for TransferFcn: '<S82>/Pitch Rate Lead Filter' */
  f14tmp25_X.PitchRateLeadFilter_CSTATE_f = 0.0;

  /* InitializeConditions for TransferFcn: '<S82>/Proportional plus integral compensator' */
  f14tmp25_X.Proportionalplusintegralcompe_o = 0.0;

  /* InitializeConditions for TransferFcn: '<S86>/Transfer Fcn.2' */
  f14tmp25_X.TransferFcn2_CSTATE_n5 = 0.0;

  /* InitializeConditions for Derivative: '<S89>/Derivative' */
  f14tmp25_DWork.Derivative_RWORK_lu.TimeStampA = rtInf;
  f14tmp25_DWork.Derivative_RWORK_lu.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S86>/Transfer Fcn.1' */
  f14tmp25_X.TransferFcn1_CSTATE_k = 0.0;

  /* InitializeConditions for Derivative: '<S89>/Derivative1' */
  f14tmp25_DWork.Derivative1_RWORK_k.TimeStampA = rtInf;
  f14tmp25_DWork.Derivative1_RWORK_k.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S13>/Actuator Model' */
  f14tmp25_X.ActuatorModel_CSTATE_fg = 0.0;

  /* InitializeConditions for TransferFcn: '<S88>/W-gust model' */
  f14tmp25_X.Wgustmodel_CSTATE_i[0] = 0.0;
  f14tmp25_X.Wgustmodel_CSTATE_i[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S88>/Q-gust model' */
  f14tmp25_X.Qgustmodel_CSTATE_k = 0.0;

  /* InitializeConditions for TransferFcn: '<S87>/Alpha-sensor Low-pass Filter' */
  f14tmp25_X.AlphasensorLowpassFilter_CST_i1 = 0.0;

  /* InitializeConditions for TransferFcn: '<S87>/Stick Prefilter' */
  f14tmp25_X.StickPrefilter_CSTATE_jz = 0.0;

  /* InitializeConditions for TransferFcn: '<S87>/Pitch Rate Lead Filter' */
  f14tmp25_X.PitchRateLeadFilter_CSTATE_n = 0.0;

  /* InitializeConditions for TransferFcn: '<S87>/Proportional plus integral compensator' */
  f14tmp25_X.Proportionalplusintegralcomp_hi = 0.0;

  /* InitializeConditions for TransferFcn: '<S91>/Transfer Fcn.2' */
  f14tmp25_X.TransferFcn2_CSTATE_k = 0.0;

  /* InitializeConditions for Derivative: '<S94>/Derivative' */
  f14tmp25_DWork.Derivative_RWORK_n.TimeStampA = rtInf;
  f14tmp25_DWork.Derivative_RWORK_n.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S91>/Transfer Fcn.1' */
  f14tmp25_X.TransferFcn1_CSTATE_g = 0.0;

  /* InitializeConditions for Derivative: '<S94>/Derivative1' */
  f14tmp25_DWork.Derivative1_RWORK_m.TimeStampA = rtInf;
  f14tmp25_DWork.Derivative1_RWORK_m.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S14>/Actuator Model' */
  f14tmp25_X.ActuatorModel_CSTATE_ov = 0.0;

  /* InitializeConditions for TransferFcn: '<S93>/W-gust model' */
  f14tmp25_X.Wgustmodel_CSTATE_p[0] = 0.0;
  f14tmp25_X.Wgustmodel_CSTATE_p[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S93>/Q-gust model' */
  f14tmp25_X.Qgustmodel_CSTATE_m = 0.0;

  /* InitializeConditions for TransferFcn: '<S92>/Alpha-sensor Low-pass Filter' */
  f14tmp25_X.AlphasensorLowpassFilter_CSTA_h = 0.0;

  /* InitializeConditions for TransferFcn: '<S92>/Stick Prefilter' */
  f14tmp25_X.StickPrefilter_CSTATE_c = 0.0;

  /* InitializeConditions for TransferFcn: '<S92>/Pitch Rate Lead Filter' */
  f14tmp25_X.PitchRateLeadFilter_CSTATE_m2 = 0.0;

  /* InitializeConditions for TransferFcn: '<S92>/Proportional plus integral compensator' */
  f14tmp25_X.Proportionalplusintegralcomp_gw = 0.0;

  /* InitializeConditions for TransferFcn: '<S96>/Transfer Fcn.2' */
  f14tmp25_X.TransferFcn2_CSTATE_ki = 0.0;

  /* InitializeConditions for Derivative: '<S99>/Derivative' */
  f14tmp25_DWork.Derivative_RWORK_d.TimeStampA = rtInf;
  f14tmp25_DWork.Derivative_RWORK_d.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S96>/Transfer Fcn.1' */
  f14tmp25_X.TransferFcn1_CSTATE_im = 0.0;

  /* InitializeConditions for Derivative: '<S99>/Derivative1' */
  f14tmp25_DWork.Derivative1_RWORK_b.TimeStampA = rtInf;
  f14tmp25_DWork.Derivative1_RWORK_b.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S15>/Actuator Model' */
  f14tmp25_X.ActuatorModel_CSTATE_i = 0.0;

  /* InitializeConditions for TransferFcn: '<S98>/W-gust model' */
  f14tmp25_X.Wgustmodel_CSTATE_o[0] = 0.0;
  f14tmp25_X.Wgustmodel_CSTATE_o[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S98>/Q-gust model' */
  f14tmp25_X.Qgustmodel_CSTATE_n = 0.0;

  /* InitializeConditions for TransferFcn: '<S97>/Alpha-sensor Low-pass Filter' */
  f14tmp25_X.AlphasensorLowpassFilter_CST_ef = 0.0;

  /* InitializeConditions for TransferFcn: '<S97>/Stick Prefilter' */
  f14tmp25_X.StickPrefilter_CSTATE_n1 = 0.0;

  /* InitializeConditions for TransferFcn: '<S97>/Pitch Rate Lead Filter' */
  f14tmp25_X.PitchRateLeadFilter_CSTATE_mp = 0.0;

  /* InitializeConditions for TransferFcn: '<S97>/Proportional plus integral compensator' */
  f14tmp25_X.Proportionalplusintegralcompe_j = 0.0;

  /* InitializeConditions for TransferFcn: '<S101>/Transfer Fcn.2' */
  f14tmp25_X.TransferFcn2_CSTATE_oa = 0.0;

  /* InitializeConditions for Derivative: '<S104>/Derivative' */
  f14tmp25_DWork.Derivative_RWORK_fd.TimeStampA = rtInf;
  f14tmp25_DWork.Derivative_RWORK_fd.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S101>/Transfer Fcn.1' */
  f14tmp25_X.TransferFcn1_CSTATE_a = 0.0;

  /* InitializeConditions for Derivative: '<S104>/Derivative1' */
  f14tmp25_DWork.Derivative1_RWORK_bx.TimeStampA = rtInf;
  f14tmp25_DWork.Derivative1_RWORK_bx.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S16>/Actuator Model' */
  f14tmp25_X.ActuatorModel_CSTATE_e = 0.0;

  /* InitializeConditions for TransferFcn: '<S103>/W-gust model' */
  f14tmp25_X.Wgustmodel_CSTATE_it[0] = 0.0;
  f14tmp25_X.Wgustmodel_CSTATE_it[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S103>/Q-gust model' */
  f14tmp25_X.Qgustmodel_CSTATE_ie = 0.0;

  /* InitializeConditions for TransferFcn: '<S102>/Alpha-sensor Low-pass Filter' */
  f14tmp25_X.AlphasensorLowpassFilter_CST_gn = 0.0;

  /* InitializeConditions for TransferFcn: '<S102>/Stick Prefilter' */
  f14tmp25_X.StickPrefilter_CSTATE_bs = 0.0;

  /* InitializeConditions for TransferFcn: '<S102>/Pitch Rate Lead Filter' */
  f14tmp25_X.PitchRateLeadFilter_CSTATE_mo = 0.0;

  /* InitializeConditions for TransferFcn: '<S102>/Proportional plus integral compensator' */
  f14tmp25_X.Proportionalplusintegralcompe_k = 0.0;

  /* InitializeConditions for TransferFcn: '<S106>/Transfer Fcn.2' */
  f14tmp25_X.TransferFcn2_CSTATE_bv = 0.0;

  /* InitializeConditions for Derivative: '<S109>/Derivative' */
  f14tmp25_DWork.Derivative_RWORK_nx.TimeStampA = rtInf;
  f14tmp25_DWork.Derivative_RWORK_nx.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S106>/Transfer Fcn.1' */
  f14tmp25_X.TransferFcn1_CSTATE_kr = 0.0;

  /* InitializeConditions for Derivative: '<S109>/Derivative1' */
  f14tmp25_DWork.Derivative1_RWORK_kl.TimeStampA = rtInf;
  f14tmp25_DWork.Derivative1_RWORK_kl.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S17>/Actuator Model' */
  f14tmp25_X.ActuatorModel_CSTATE_l = 0.0;

  /* InitializeConditions for TransferFcn: '<S108>/W-gust model' */
  f14tmp25_X.Wgustmodel_CSTATE_h[0] = 0.0;
  f14tmp25_X.Wgustmodel_CSTATE_h[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S108>/Q-gust model' */
  f14tmp25_X.Qgustmodel_CSTATE_kp = 0.0;

  /* InitializeConditions for TransferFcn: '<S107>/Alpha-sensor Low-pass Filter' */
  f14tmp25_X.AlphasensorLowpassFilter_CSTA_p = 0.0;

  /* InitializeConditions for TransferFcn: '<S107>/Stick Prefilter' */
  f14tmp25_X.StickPrefilter_CSTATE_pr = 0.0;

  /* InitializeConditions for TransferFcn: '<S107>/Pitch Rate Lead Filter' */
  f14tmp25_X.PitchRateLeadFilter_CSTATE_fn = 0.0;

  /* InitializeConditions for TransferFcn: '<S107>/Proportional plus integral compensator' */
  f14tmp25_X.Proportionalplusintegralcomp_lg = 0.0;

  /* InitializeConditions for TransferFcn: '<S111>/Transfer Fcn.2' */
  f14tmp25_X.TransferFcn2_CSTATE_ku = 0.0;

  /* InitializeConditions for Derivative: '<S114>/Derivative' */
  f14tmp25_DWork.Derivative_RWORK_bp.TimeStampA = rtInf;
  f14tmp25_DWork.Derivative_RWORK_bp.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S111>/Transfer Fcn.1' */
  f14tmp25_X.TransferFcn1_CSTATE_ku = 0.0;

  /* InitializeConditions for Derivative: '<S114>/Derivative1' */
  f14tmp25_DWork.Derivative1_RWORK_mv.TimeStampA = rtInf;
  f14tmp25_DWork.Derivative1_RWORK_mv.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S18>/Actuator Model' */
  f14tmp25_X.ActuatorModel_CSTATE_hh = 0.0;

  /* InitializeConditions for TransferFcn: '<S113>/W-gust model' */
  f14tmp25_X.Wgustmodel_CSTATE_e5[0] = 0.0;
  f14tmp25_X.Wgustmodel_CSTATE_e5[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S113>/Q-gust model' */
  f14tmp25_X.Qgustmodel_CSTATE_f = 0.0;

  /* InitializeConditions for TransferFcn: '<S112>/Alpha-sensor Low-pass Filter' */
  f14tmp25_X.AlphasensorLowpassFilter_CST_ba = 0.0;

  /* InitializeConditions for TransferFcn: '<S112>/Stick Prefilter' */
  f14tmp25_X.StickPrefilter_CSTATE_p3 = 0.0;

  /* InitializeConditions for TransferFcn: '<S112>/Pitch Rate Lead Filter' */
  f14tmp25_X.PitchRateLeadFilter_CSTATE_ke = 0.0;

  /* InitializeConditions for TransferFcn: '<S112>/Proportional plus integral compensator' */
  f14tmp25_X.Proportionalplusintegralcompe_c = 0.0;

  /* InitializeConditions for TransferFcn: '<S116>/Transfer Fcn.2' */
  f14tmp25_X.TransferFcn2_CSTATE_e = 0.0;

  /* InitializeConditions for Derivative: '<S119>/Derivative' */
  f14tmp25_DWork.Derivative_RWORK_k.TimeStampA = rtInf;
  f14tmp25_DWork.Derivative_RWORK_k.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S116>/Transfer Fcn.1' */
  f14tmp25_X.TransferFcn1_CSTATE_j = 0.0;

  /* InitializeConditions for Derivative: '<S119>/Derivative1' */
  f14tmp25_DWork.Derivative1_RWORK_bm.TimeStampA = rtInf;
  f14tmp25_DWork.Derivative1_RWORK_bm.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S19>/Actuator Model' */
  f14tmp25_X.ActuatorModel_CSTATE_p = 0.0;

  /* InitializeConditions for TransferFcn: '<S118>/W-gust model' */
  f14tmp25_X.Wgustmodel_CSTATE_k[0] = 0.0;
  f14tmp25_X.Wgustmodel_CSTATE_k[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S118>/Q-gust model' */
  f14tmp25_X.Qgustmodel_CSTATE_ad = 0.0;

  /* InitializeConditions for TransferFcn: '<S117>/Alpha-sensor Low-pass Filter' */
  f14tmp25_X.AlphasensorLowpassFilter_CSTA_k = 0.0;

  /* InitializeConditions for TransferFcn: '<S117>/Stick Prefilter' */
  f14tmp25_X.StickPrefilter_CSTATE_ju = 0.0;

  /* InitializeConditions for TransferFcn: '<S117>/Pitch Rate Lead Filter' */
  f14tmp25_X.PitchRateLeadFilter_CSTATE_ez = 0.0;

  /* InitializeConditions for TransferFcn: '<S117>/Proportional plus integral compensator' */
  f14tmp25_X.Proportionalplusintegralcomp_jd = 0.0;

  /* InitializeConditions for TransferFcn: '<S121>/Transfer Fcn.2' */
  f14tmp25_X.TransferFcn2_CSTATE_kz = 0.0;

  /* InitializeConditions for Derivative: '<S124>/Derivative' */
  f14tmp25_DWork.Derivative_RWORK_lc.TimeStampA = rtInf;
  f14tmp25_DWork.Derivative_RWORK_lc.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S121>/Transfer Fcn.1' */
  f14tmp25_X.TransferFcn1_CSTATE_pe = 0.0;

  /* InitializeConditions for Derivative: '<S124>/Derivative1' */
  f14tmp25_DWork.Derivative1_RWORK_dt.TimeStampA = rtInf;
  f14tmp25_DWork.Derivative1_RWORK_dt.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S20>/Actuator Model' */
  f14tmp25_X.ActuatorModel_CSTATE_ol = 0.0;

  /* InitializeConditions for TransferFcn: '<S123>/W-gust model' */
  f14tmp25_X.Wgustmodel_CSTATE_if[0] = 0.0;
  f14tmp25_X.Wgustmodel_CSTATE_if[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S123>/Q-gust model' */
  f14tmp25_X.Qgustmodel_CSTATE_mh = 0.0;

  /* InitializeConditions for TransferFcn: '<S122>/Alpha-sensor Low-pass Filter' */
  f14tmp25_X.AlphasensorLowpassFilter_CST_ku = 0.0;

  /* InitializeConditions for TransferFcn: '<S122>/Stick Prefilter' */
  f14tmp25_X.StickPrefilter_CSTATE_m = 0.0;

  /* InitializeConditions for TransferFcn: '<S122>/Pitch Rate Lead Filter' */
  f14tmp25_X.PitchRateLeadFilter_CSTATE_f0 = 0.0;

  /* InitializeConditions for TransferFcn: '<S122>/Proportional plus integral compensator' */
  f14tmp25_X.Proportionalplusintegralcomp_kq = 0.0;

  /* InitializeConditions for TransferFcn: '<S126>/Transfer Fcn.2' */
  f14tmp25_X.TransferFcn2_CSTATE_ar = 0.0;

  /* InitializeConditions for Derivative: '<S129>/Derivative' */
  f14tmp25_DWork.Derivative_RWORK_jt.TimeStampA = rtInf;
  f14tmp25_DWork.Derivative_RWORK_jt.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S126>/Transfer Fcn.1' */
  f14tmp25_X.TransferFcn1_CSTATE_id = 0.0;

  /* InitializeConditions for Derivative: '<S129>/Derivative1' */
  f14tmp25_DWork.Derivative1_RWORK_pp.TimeStampA = rtInf;
  f14tmp25_DWork.Derivative1_RWORK_pp.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S21>/Actuator Model' */
  f14tmp25_X.ActuatorModel_CSTATE_g = 0.0;

  /* InitializeConditions for TransferFcn: '<S128>/W-gust model' */
  f14tmp25_X.Wgustmodel_CSTATE_iv[0] = 0.0;
  f14tmp25_X.Wgustmodel_CSTATE_iv[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S128>/Q-gust model' */
  f14tmp25_X.Qgustmodel_CSTATE_ob = 0.0;

  /* InitializeConditions for TransferFcn: '<S127>/Alpha-sensor Low-pass Filter' */
  f14tmp25_X.AlphasensorLowpassFilter_CST_pj = 0.0;

  /* InitializeConditions for TransferFcn: '<S127>/Stick Prefilter' */
  f14tmp25_X.StickPrefilter_CSTATE_ah = 0.0;

  /* InitializeConditions for TransferFcn: '<S127>/Pitch Rate Lead Filter' */
  f14tmp25_X.PitchRateLeadFilter_CSTATE_p = 0.0;

  /* InitializeConditions for TransferFcn: '<S127>/Proportional plus integral compensator' */
  f14tmp25_X.Proportionalplusintegralcomp_jw = 0.0;

  /* InitializeConditions for TransferFcn: '<S131>/Transfer Fcn.2' */
  f14tmp25_X.TransferFcn2_CSTATE_lp = 0.0;

  /* InitializeConditions for Derivative: '<S134>/Derivative' */
  f14tmp25_DWork.Derivative_RWORK_o.TimeStampA = rtInf;
  f14tmp25_DWork.Derivative_RWORK_o.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S131>/Transfer Fcn.1' */
  f14tmp25_X.TransferFcn1_CSTATE_je = 0.0;

  /* InitializeConditions for Derivative: '<S134>/Derivative1' */
  f14tmp25_DWork.Derivative1_RWORK_eu.TimeStampA = rtInf;
  f14tmp25_DWork.Derivative1_RWORK_eu.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S22>/Actuator Model' */
  f14tmp25_X.ActuatorModel_CSTATE_fk = 0.0;

  /* InitializeConditions for TransferFcn: '<S133>/W-gust model' */
  f14tmp25_X.Wgustmodel_CSTATE_gw[0] = 0.0;
  f14tmp25_X.Wgustmodel_CSTATE_gw[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S133>/Q-gust model' */
  f14tmp25_X.Qgustmodel_CSTATE_e = 0.0;

  /* InitializeConditions for TransferFcn: '<S132>/Alpha-sensor Low-pass Filter' */
  f14tmp25_X.AlphasensorLowpassFilter_CSTA_d = 0.0;

  /* InitializeConditions for TransferFcn: '<S132>/Stick Prefilter' */
  f14tmp25_X.StickPrefilter_CSTATE_o = 0.0;

  /* InitializeConditions for TransferFcn: '<S132>/Pitch Rate Lead Filter' */
  f14tmp25_X.PitchRateLeadFilter_CSTATE_a = 0.0;

  /* InitializeConditions for TransferFcn: '<S132>/Proportional plus integral compensator' */
  f14tmp25_X.Proportionalplusintegralcomp_iz = 0.0;

  /* InitializeConditions for TransferFcn: '<S136>/Transfer Fcn.2' */
  f14tmp25_X.TransferFcn2_CSTATE_aw = 0.0;

  /* InitializeConditions for Derivative: '<S139>/Derivative' */
  f14tmp25_DWork.Derivative_RWORK_o0.TimeStampA = rtInf;
  f14tmp25_DWork.Derivative_RWORK_o0.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S136>/Transfer Fcn.1' */
  f14tmp25_X.TransferFcn1_CSTATE_be = 0.0;

  /* InitializeConditions for Derivative: '<S139>/Derivative1' */
  f14tmp25_DWork.Derivative1_RWORK_j.TimeStampA = rtInf;
  f14tmp25_DWork.Derivative1_RWORK_j.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S23>/Actuator Model' */
  f14tmp25_X.ActuatorModel_CSTATE_pq = 0.0;

  /* InitializeConditions for TransferFcn: '<S138>/W-gust model' */
  f14tmp25_X.Wgustmodel_CSTATE_c[0] = 0.0;
  f14tmp25_X.Wgustmodel_CSTATE_c[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S138>/Q-gust model' */
  f14tmp25_X.Qgustmodel_CSTATE_fh = 0.0;

  /* InitializeConditions for TransferFcn: '<S137>/Alpha-sensor Low-pass Filter' */
  f14tmp25_X.AlphasensorLowpassFilter_CST_b1 = 0.0;

  /* InitializeConditions for TransferFcn: '<S137>/Stick Prefilter' */
  f14tmp25_X.StickPrefilter_CSTATE_p2 = 0.0;

  /* InitializeConditions for TransferFcn: '<S137>/Pitch Rate Lead Filter' */
  f14tmp25_X.PitchRateLeadFilter_CSTATE_au = 0.0;

  /* InitializeConditions for TransferFcn: '<S137>/Proportional plus integral compensator' */
  f14tmp25_X.Proportionalplusintegralcomp_nm = 0.0;

  /* InitializeConditions for TransferFcn: '<S141>/Transfer Fcn.2' */
  f14tmp25_X.TransferFcn2_CSTATE_ms = 0.0;

  /* InitializeConditions for Derivative: '<S144>/Derivative' */
  f14tmp25_DWork.Derivative_RWORK_p5.TimeStampA = rtInf;
  f14tmp25_DWork.Derivative_RWORK_p5.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S141>/Transfer Fcn.1' */
  f14tmp25_X.TransferFcn1_CSTATE_nz = 0.0;

  /* InitializeConditions for Derivative: '<S144>/Derivative1' */
  f14tmp25_DWork.Derivative1_RWORK_dy.TimeStampA = rtInf;
  f14tmp25_DWork.Derivative1_RWORK_dy.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S24>/Actuator Model' */
  f14tmp25_X.ActuatorModel_CSTATE_fb = 0.0;

  /* InitializeConditions for TransferFcn: '<S143>/W-gust model' */
  f14tmp25_X.Wgustmodel_CSTATE_h3[0] = 0.0;
  f14tmp25_X.Wgustmodel_CSTATE_h3[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S143>/Q-gust model' */
  f14tmp25_X.Qgustmodel_CSTATE_c = 0.0;

  /* InitializeConditions for TransferFcn: '<S142>/Alpha-sensor Low-pass Filter' */
  f14tmp25_X.AlphasensorLowpassFilter_CST_jw = 0.0;

  /* InitializeConditions for TransferFcn: '<S142>/Stick Prefilter' */
  f14tmp25_X.StickPrefilter_CSTATE_ns = 0.0;

  /* InitializeConditions for TransferFcn: '<S142>/Pitch Rate Lead Filter' */
  f14tmp25_X.PitchRateLeadFilter_CSTATE_ds = 0.0;

  /* InitializeConditions for TransferFcn: '<S142>/Proportional plus integral compensator' */
  f14tmp25_X.Proportionalplusintegralcompe_a = 0.0;

  /* InitializeConditions for TransferFcn: '<S146>/Transfer Fcn.2' */
  f14tmp25_X.TransferFcn2_CSTATE_bk = 0.0;

  /* InitializeConditions for Derivative: '<S149>/Derivative' */
  f14tmp25_DWork.Derivative_RWORK_ch.TimeStampA = rtInf;
  f14tmp25_DWork.Derivative_RWORK_ch.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S146>/Transfer Fcn.1' */
  f14tmp25_X.TransferFcn1_CSTATE_gr = 0.0;

  /* InitializeConditions for Derivative: '<S149>/Derivative1' */
  f14tmp25_DWork.Derivative1_RWORK_n.TimeStampA = rtInf;
  f14tmp25_DWork.Derivative1_RWORK_n.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S25>/Actuator Model' */
  f14tmp25_X.ActuatorModel_CSTATE_iv = 0.0;

  /* InitializeConditions for TransferFcn: '<S148>/W-gust model' */
  f14tmp25_X.Wgustmodel_CSTATE_b[0] = 0.0;
  f14tmp25_X.Wgustmodel_CSTATE_b[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S148>/Q-gust model' */
  f14tmp25_X.Qgustmodel_CSTATE_lb = 0.0;

  /* InitializeConditions for TransferFcn: '<S147>/Alpha-sensor Low-pass Filter' */
  f14tmp25_X.AlphasensorLowpassFilter_CST_iy = 0.0;

  /* InitializeConditions for TransferFcn: '<S147>/Stick Prefilter' */
  f14tmp25_X.StickPrefilter_CSTATE_pb = 0.0;

  /* InitializeConditions for TransferFcn: '<S147>/Pitch Rate Lead Filter' */
  f14tmp25_X.PitchRateLeadFilter_CSTATE_ak = 0.0;

  /* InitializeConditions for TransferFcn: '<S147>/Proportional plus integral compensator' */
  f14tmp25_X.Proportionalplusintegralcomp_ab = 0.0;
}

/* Model terminate function */
void f14tmp25_terminate(void)
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
  f14tmp25_output();

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  f14tmp25_update();

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
  f14tmp25_initialize();
}

void MdlTerminate(void)
{
  f14tmp25_terminate();
}

rtModel_f14tmp25 *f14tmp25(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)f14tmp25_rtM, 0,
                sizeof(rtModel_f14tmp25));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&f14tmp25_rtM->solverInfo,
                          &f14tmp25_rtM->Timing.simTimeStep);
    rtsiSetTPtr(&f14tmp25_rtM->solverInfo, &rtmGetTPtr(f14tmp25_rtM));
    rtsiSetStepSizePtr(&f14tmp25_rtM->solverInfo,
                       &f14tmp25_rtM->Timing.stepSize0);
    rtsiSetdXPtr(&f14tmp25_rtM->solverInfo, &f14tmp25_rtM->ModelData.derivs);
    rtsiSetContStatesPtr(&f14tmp25_rtM->solverInfo,
                         &f14tmp25_rtM->ModelData.contStates);
    rtsiSetNumContStatesPtr(&f14tmp25_rtM->solverInfo,
      &f14tmp25_rtM->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&f14tmp25_rtM->solverInfo, (&rtmGetErrorStatus
      (f14tmp25_rtM)));
    rtsiSetRTModelPtr(&f14tmp25_rtM->solverInfo, f14tmp25_rtM);
  }

  rtsiSetSimTimeStep(&f14tmp25_rtM->solverInfo, MAJOR_TIME_STEP);
  f14tmp25_rtM->ModelData.intgData.y = f14tmp25_rtM->ModelData.odeY;
  f14tmp25_rtM->ModelData.intgData.f[0] = f14tmp25_rtM->ModelData.odeF[0];
  f14tmp25_rtM->ModelData.intgData.f[1] = f14tmp25_rtM->ModelData.odeF[1];
  f14tmp25_rtM->ModelData.intgData.f[2] = f14tmp25_rtM->ModelData.odeF[2];
  f14tmp25_rtM->ModelData.intgData.f[3] = f14tmp25_rtM->ModelData.odeF[3];
  f14tmp25_rtM->ModelData.contStates = ((real_T *) &f14tmp25_X);
  rtsiSetSolverData(&f14tmp25_rtM->solverInfo, (void *)
                    &f14tmp25_rtM->ModelData.intgData);
  rtsiSetSolverName(&f14tmp25_rtM->solverInfo,"ode4");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = f14tmp25_rtM->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    mdlTsMap[2] = 2;
    f14tmp25_rtM->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    f14tmp25_rtM->Timing.sampleTimes = (&f14tmp25_rtM->Timing.sampleTimesArray[0]);
    f14tmp25_rtM->Timing.offsetTimes = (&f14tmp25_rtM->Timing.offsetTimesArray[0]);

    /* task periods */
    f14tmp25_rtM->Timing.sampleTimes[0] = (0.0);
    f14tmp25_rtM->Timing.sampleTimes[1] = (0.01);
    f14tmp25_rtM->Timing.sampleTimes[2] = (0.1);

    /* task offsets */
    f14tmp25_rtM->Timing.offsetTimes[0] = (0.0);
    f14tmp25_rtM->Timing.offsetTimes[1] = (0.0);
    f14tmp25_rtM->Timing.offsetTimes[2] = (0.0);
  }

  rtmSetTPtr(f14tmp25_rtM, &f14tmp25_rtM->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = f14tmp25_rtM->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    mdlSampleHits[2] = 1;
    f14tmp25_rtM->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(f14tmp25_rtM, 10.0);
  f14tmp25_rtM->Timing.stepSize0 = 0.01;
  f14tmp25_rtM->Timing.stepSize1 = 0.01;
  f14tmp25_rtM->Timing.stepSize2 = 0.1;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    f14tmp25_rtM->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(f14tmp25_rtM->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(f14tmp25_rtM->rtwLogInfo, (NULL));
    rtliSetLogT(f14tmp25_rtM->rtwLogInfo, "tout");
    rtliSetLogX(f14tmp25_rtM->rtwLogInfo, "");
    rtliSetLogXFinal(f14tmp25_rtM->rtwLogInfo, "");
    rtliSetSigLog(f14tmp25_rtM->rtwLogInfo, "");
    rtliSetLogVarNameModifier(f14tmp25_rtM->rtwLogInfo, "rt_");
    rtliSetLogFormat(f14tmp25_rtM->rtwLogInfo, 0);
    rtliSetLogMaxRows(f14tmp25_rtM->rtwLogInfo, 1000);
    rtliSetLogDecimation(f14tmp25_rtM->rtwLogInfo, 1);
    rtliSetLogY(f14tmp25_rtM->rtwLogInfo, "");
    rtliSetLogYSignalInfo(f14tmp25_rtM->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(f14tmp25_rtM->rtwLogInfo, (NULL));
  }

  f14tmp25_rtM->solverInfoPtr = (&f14tmp25_rtM->solverInfo);
  f14tmp25_rtM->Timing.stepSize = (0.01);
  rtsiSetFixedStepSize(&f14tmp25_rtM->solverInfo, 0.01);
  rtsiSetSolverMode(&f14tmp25_rtM->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  f14tmp25_rtM->ModelData.blockIO = ((void *) &f14tmp25_B);
  (void) memset(((void *) &f14tmp25_B), 0,
                sizeof(BlockIO_f14tmp25));

  /* parameters */
  f14tmp25_rtM->ModelData.defaultParam = ((real_T *)&f14tmp25_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &f14tmp25_X;
    f14tmp25_rtM->ModelData.contStates = (x);
    (void) memset((void *)&f14tmp25_X, 0,
                  sizeof(ContinuousStates_f14tmp25));
  }

  /* states (dwork) */
  f14tmp25_rtM->Work.dwork = ((void *) &f14tmp25_DWork);
  (void) memset((void *)&f14tmp25_DWork, 0,
                sizeof(D_Work_f14tmp25));

  /* Initialize DataMapInfo substructure containing ModelMap for C API */
  f14tmp25_InitializeDataMapInfo(f14tmp25_rtM);

  /* Initialize Sizes */
  f14tmp25_rtM->Sizes.numContStates = (250);/* Number of continuous states */
  f14tmp25_rtM->Sizes.numY = (0);      /* Number of model outputs */
  f14tmp25_rtM->Sizes.numU = (0);      /* Number of model inputs */
  f14tmp25_rtM->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  f14tmp25_rtM->Sizes.numSampTimes = (3);/* Number of sample times */
  f14tmp25_rtM->Sizes.numBlocks = (1000);/* Number of blocks */
  f14tmp25_rtM->Sizes.numBlockIO = (900);/* Number of block outputs */
  f14tmp25_rtM->Sizes.numBlockPrms = (1050);/* Sum of parameter "widths" */
  return f14tmp25_rtM;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
