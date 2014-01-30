/*
 * f14tmp1.c
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
#include "rt_logging_mmi.h"
#include "f14tmp1_capi.h"
#include "f14tmp1.h"
#include "f14tmp1_private.h"

/* Block signals (auto storage) */
BlockIO_f14tmp1 f14tmp1_B;

/* Continuous states */
ContinuousStates_f14tmp1 f14tmp1_X;

/* Block states (auto storage) */
D_Work_f14tmp1 f14tmp1_DWork;

/* Real-time model */
rtModel_f14tmp1 f14tmp1_rtM_;
rtModel_f14tmp1 *const f14tmp1_rtM = &f14tmp1_rtM_;
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
  (f14tmp1_rtM->Timing.TaskCounters.TID[2])++;
  if ((f14tmp1_rtM->Timing.TaskCounters.TID[2]) > 9) {/* Sample time: [0.1s, 0.0s] */
    f14tmp1_rtM->Timing.TaskCounters.TID[2] = 0;
  }

  f14tmp1_rtM->Timing.sampleHits[2] = (f14tmp1_rtM->Timing.TaskCounters.TID[2] ==
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
  int_T nXc = 10;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  f14tmp1_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  f14tmp1_output();
  f14tmp1_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  f14tmp1_output();
  f14tmp1_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  f14tmp1_output();
  f14tmp1_derivatives();

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
void f14tmp1_output(void)
{
  real_T temp;
  if (rtmIsMajorTimeStep(f14tmp1_rtM)) {
    /* set solver stop time */
    if (!(f14tmp1_rtM->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&f14tmp1_rtM->solverInfo,
                            ((f14tmp1_rtM->Timing.clockTickH0 + 1) *
        f14tmp1_rtM->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&f14tmp1_rtM->solverInfo,
                            ((f14tmp1_rtM->Timing.clockTick0 + 1) *
        f14tmp1_rtM->Timing.stepSize0 + f14tmp1_rtM->Timing.clockTickH0 *
        f14tmp1_rtM->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(f14tmp1_rtM)) {
    f14tmp1_rtM->Timing.t[0] = rtsiGetT(&f14tmp1_rtM->solverInfo);
  }

  /* TransferFcn: '<S2>/Transfer Fcn.2' */
  f14tmp1_B.TransferFcn2 = f14tmp1_P.TransferFcn2_C*
    f14tmp1_X.TransferFcn2_CSTATE;

  /* Gain: '<S1>/Gain5' */
  f14tmp1_B.Gain5 = f14tmp1_P.Gain5_Gain * f14tmp1_B.TransferFcn2;
  if (rtmIsMajorTimeStep(f14tmp1_rtM) &&
      f14tmp1_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* Derivative: '<S5>/Derivative' */
  {
    real_T t = f14tmp1_rtM->Timing.t[0];
    real_T timeStampA = f14tmp1_DWork.Derivative_RWORK.TimeStampA;
    real_T timeStampB = f14tmp1_DWork.Derivative_RWORK.TimeStampB;
    real_T *lastU = &f14tmp1_DWork.Derivative_RWORK.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp1_B.Derivative = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp1_DWork.Derivative_RWORK.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp1_DWork.Derivative_RWORK.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp1_B.Derivative = (f14tmp1_B.TransferFcn2 - *lastU++) / deltaT;
    }
  }

  /* TransferFcn: '<S2>/Transfer Fcn.1' */
  f14tmp1_B.TransferFcn1 = f14tmp1_P.TransferFcn1_C*
    f14tmp1_X.TransferFcn1_CSTATE;

  /* Derivative: '<S5>/Derivative1' */
  {
    real_T t = f14tmp1_rtM->Timing.t[0];
    real_T timeStampA = f14tmp1_DWork.Derivative1_RWORK.TimeStampA;
    real_T timeStampB = f14tmp1_DWork.Derivative1_RWORK.TimeStampB;
    real_T *lastU = &f14tmp1_DWork.Derivative1_RWORK.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      f14tmp1_B.Derivative1 = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &f14tmp1_DWork.Derivative1_RWORK.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &f14tmp1_DWork.Derivative1_RWORK.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      f14tmp1_B.Derivative1 = (f14tmp1_B.TransferFcn1 - *lastU++) / deltaT;
    }
  }

  /* Gain: '<S5>/Gain1' */
  f14tmp1_B.Gain1 = f14tmp1_P.Gain1_Gain * f14tmp1_B.Derivative1;

  /* Product: '<S5>/Product' incorporates:
   *  Constant: '<S5>/Constant'
   */
  f14tmp1_B.Product = f14tmp1_B.TransferFcn1 * f14tmp1_P.Constant_Value;

  /* Sum: '<S5>/Sum1' */
  f14tmp1_B.Sum1 = (f14tmp1_B.Gain1 - f14tmp1_B.Derivative) + f14tmp1_B.Product;

  /* Gain: '<S5>/Gain2' */
  f14tmp1_B.Gain2 = f14tmp1_P.Gain2_Gain * f14tmp1_B.Sum1;
  if (rtmIsMajorTimeStep(f14tmp1_rtM) &&
      f14tmp1_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* SignalGenerator: '<S1>/Pilot' */
  temp = f14tmp1_P.Pilot_Frequency * f14tmp1_rtM->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    f14tmp1_B.Pilot = f14tmp1_P.Pilot_Amplitude;
  } else {
    f14tmp1_B.Pilot = -f14tmp1_P.Pilot_Amplitude;
  }

  /* End of SignalGenerator: '<S1>/Pilot' */

  /* Sum: '<S1>/Sum1' */
  f14tmp1_B.Sum1_k = f14tmp1_B.Pilot + 0.0;
  if (rtmIsMajorTimeStep(f14tmp1_rtM) &&
      f14tmp1_rtM->Timing.TaskCounters.TID[1] == 0) {
  }

  /* TransferFcn: '<S1>/Actuator Model' */
  f14tmp1_B.ActuatorModel = f14tmp1_P.ActuatorModel_C*
    f14tmp1_X.ActuatorModel_CSTATE;

  /* Gain: '<S2>/Gain3' */
  f14tmp1_B.Gain3 = f14tmp1_P.Gain3_Gain * f14tmp1_B.TransferFcn1;

  /* Gain: '<S2>/Gain4' */
  f14tmp1_B.Gain4 = f14tmp1_P.Gain4_Gain * f14tmp1_B.TransferFcn2;

  /* Gain: '<S2>/Gain5' */
  f14tmp1_B.Gain5_b = f14tmp1_P.Gain5_Gain_j * f14tmp1_B.ActuatorModel;

  /* Gain: '<S2>/Gain6' */
  f14tmp1_B.Gain6 = f14tmp1_P.Gain6_Gain * f14tmp1_B.ActuatorModel;

  /* TransferFcn: '<S4>/W-gust model' */
  f14tmp1_B.Wgustmodel = f14tmp1_P.Wgustmodel_C[0]*f14tmp1_X.Wgustmodel_CSTATE[0]
    + f14tmp1_P.Wgustmodel_C[1]*f14tmp1_X.Wgustmodel_CSTATE[1];

  /* Gain: '<S1>/Gain' */
  f14tmp1_B.Gain = f14tmp1_P.Gain_Gain * f14tmp1_B.Wgustmodel;

  /* Sum: '<S2>/Sum1' */
  f14tmp1_B.Sum1_o = (f14tmp1_B.Gain5_b - f14tmp1_B.Gain) + f14tmp1_B.Gain3;

  /* Gain: '<S1>/Gain2' */
  f14tmp1_B.Gain2_f = f14tmp1_P.Gain2_Gain_p * f14tmp1_B.Wgustmodel;

  /* TransferFcn: '<S4>/Q-gust model' */
  f14tmp1_B.Qgustmodel = f14tmp1_P.Qgustmodel_D*f14tmp1_B.Wgustmodel;
  f14tmp1_B.Qgustmodel += f14tmp1_P.Qgustmodel_C*f14tmp1_X.Qgustmodel_CSTATE;

  /* Gain: '<S1>/Gain1' */
  f14tmp1_B.Gain1_h = f14tmp1_P.Gain1_Gain_h * f14tmp1_B.Qgustmodel;

  /* Sum: '<S1>/Sum' */
  f14tmp1_B.Sum = f14tmp1_B.Gain2_f + f14tmp1_B.Gain1_h;

  /* Sum: '<S2>/Sum2' */
  f14tmp1_B.Sum2 = (f14tmp1_B.Gain4 - f14tmp1_B.Sum) + f14tmp1_B.Gain6;

  /* TransferFcn: '<S3>/Alpha-sensor Low-pass Filter' */
  f14tmp1_B.AlphasensorLowpassFilter = f14tmp1_P.AlphasensorLowpassFilter_C*
    f14tmp1_X.AlphasensorLowpassFilter_CSTATE;

  /* TransferFcn: '<S3>/Stick Prefilter' */
  f14tmp1_B.StickPrefilter = f14tmp1_P.StickPrefilter_C*
    f14tmp1_X.StickPrefilter_CSTATE;

  /* TransferFcn: '<S3>/Pitch Rate Lead Filter' */
  f14tmp1_B.PitchRateLeadFilter = f14tmp1_P.PitchRateLeadFilter_D*
    f14tmp1_B.TransferFcn1;
  f14tmp1_B.PitchRateLeadFilter += f14tmp1_P.PitchRateLeadFilter_C*
    f14tmp1_X.PitchRateLeadFilter_CSTATE;

  /* Gain: '<S3>/Gain2' */
  f14tmp1_B.Gain2_e = f14tmp1_P.Gain2_Gain_k * f14tmp1_B.PitchRateLeadFilter;

  /* Gain: '<S3>/Gain3' */
  f14tmp1_B.Gain3_g = f14tmp1_P.Gain3_Gain_i *
    f14tmp1_B.AlphasensorLowpassFilter;

  /* Sum: '<S3>/Sum1' */
  f14tmp1_B.Sum1_d = f14tmp1_B.Gain2_e + f14tmp1_B.Gain3_g;

  /* Sum: '<S3>/Sum2' */
  f14tmp1_B.Sum2_f = f14tmp1_B.StickPrefilter - f14tmp1_B.Sum1_d;

  /* Gain: '<S3>/Gain' */
  f14tmp1_B.Gain_d = f14tmp1_P.Gain_Gain_k * f14tmp1_B.Sum2_f;

  /* TransferFcn: '<S3>/Proportional plus integral compensator' */
  f14tmp1_B.Proportionalplusintegralcompens =
    f14tmp1_P.Proportionalplusintegralcompe_i*
    f14tmp1_X.Proportionalplusintegralcompens;

  /* Sum: '<S3>/Sum' */
  f14tmp1_B.Sum_n = f14tmp1_B.Gain_d + f14tmp1_B.Proportionalplusintegralcompens;
  if (rtmIsMajorTimeStep(f14tmp1_rtM) &&
      f14tmp1_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* RandomNumber: '<S6>/White Noise' */
    f14tmp1_B.WhiteNoise = f14tmp1_DWork.NextOutput;

    /* Gain: '<S6>/Output' */
    f14tmp1_B.Output = f14tmp1_P.Output_Gain * f14tmp1_B.WhiteNoise;
  }
}

/* Model update function */
void f14tmp1_update(void)
{
  /* Update for Derivative: '<S5>/Derivative' */
  {
    real_T timeStampA = f14tmp1_DWork.Derivative_RWORK.TimeStampA;
    real_T timeStampB = f14tmp1_DWork.Derivative_RWORK.TimeStampB;
    real_T* lastTime = &f14tmp1_DWork.Derivative_RWORK.TimeStampA;
    real_T* lastU = &f14tmp1_DWork.Derivative_RWORK.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp1_DWork.Derivative_RWORK.TimeStampB;
        lastU = &f14tmp1_DWork.Derivative_RWORK.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp1_DWork.Derivative_RWORK.TimeStampB;
        lastU = &f14tmp1_DWork.Derivative_RWORK.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp1_rtM->Timing.t[0];
    *lastU++ = f14tmp1_B.TransferFcn2;
  }

  /* Update for Derivative: '<S5>/Derivative1' */
  {
    real_T timeStampA = f14tmp1_DWork.Derivative1_RWORK.TimeStampA;
    real_T timeStampB = f14tmp1_DWork.Derivative1_RWORK.TimeStampB;
    real_T* lastTime = &f14tmp1_DWork.Derivative1_RWORK.TimeStampA;
    real_T* lastU = &f14tmp1_DWork.Derivative1_RWORK.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &f14tmp1_DWork.Derivative1_RWORK.TimeStampB;
        lastU = &f14tmp1_DWork.Derivative1_RWORK.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &f14tmp1_DWork.Derivative1_RWORK.TimeStampB;
        lastU = &f14tmp1_DWork.Derivative1_RWORK.LastUAtTimeB;
      }
    }

    *lastTime = f14tmp1_rtM->Timing.t[0];
    *lastU++ = f14tmp1_B.TransferFcn1;
  }

  if (rtmIsMajorTimeStep(f14tmp1_rtM) &&
      f14tmp1_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* Update for RandomNumber: '<S6>/White Noise' */
    f14tmp1_DWork.NextOutput = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp1_DWork.RandSeed) * f14tmp1_P.WhiteNoise_StdDev +
      f14tmp1_P.WhiteNoise_Mean;
  }

  if (rtmIsMajorTimeStep(f14tmp1_rtM)) {
    rt_ertODEUpdateContinuousStates(&f14tmp1_rtM->solverInfo);
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
  if (!(++f14tmp1_rtM->Timing.clockTick0)) {
    ++f14tmp1_rtM->Timing.clockTickH0;
  }

  f14tmp1_rtM->Timing.t[0] = rtsiGetSolverStopTime(&f14tmp1_rtM->solverInfo);

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
    if (!(++f14tmp1_rtM->Timing.clockTick1)) {
      ++f14tmp1_rtM->Timing.clockTickH1;
    }

    f14tmp1_rtM->Timing.t[1] = f14tmp1_rtM->Timing.clockTick1 *
      f14tmp1_rtM->Timing.stepSize1 + f14tmp1_rtM->Timing.clockTickH1 *
      f14tmp1_rtM->Timing.stepSize1 * 4294967296.0;
  }

  if (rtmIsMajorTimeStep(f14tmp1_rtM) &&
      f14tmp1_rtM->Timing.TaskCounters.TID[2] == 0) {
    /* Update absolute timer for sample time: [0.1s, 0.0s] */
    /* The "clockTick2" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick2"
     * and "Timing.stepSize2". Size of "clockTick2" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick2 and the high bits
     * Timing.clockTickH2. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++f14tmp1_rtM->Timing.clockTick2)) {
      ++f14tmp1_rtM->Timing.clockTickH2;
    }

    f14tmp1_rtM->Timing.t[2] = f14tmp1_rtM->Timing.clockTick2 *
      f14tmp1_rtM->Timing.stepSize2 + f14tmp1_rtM->Timing.clockTickH2 *
      f14tmp1_rtM->Timing.stepSize2 * 4294967296.0;
  }

  rate_scheduler();
}

/* Derivatives for root system: '<Root>' */
void f14tmp1_derivatives(void)
{
  /* Derivatives for TransferFcn: '<S2>/Transfer Fcn.2' */
  {
    ((StateDerivatives_f14tmp1 *) f14tmp1_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE = f14tmp1_B.Sum1_o;
    ((StateDerivatives_f14tmp1 *) f14tmp1_rtM->ModelData.derivs)
      ->TransferFcn2_CSTATE += (f14tmp1_P.TransferFcn2_A)*
      f14tmp1_X.TransferFcn2_CSTATE;
  }

  /* Derivatives for TransferFcn: '<S2>/Transfer Fcn.1' */
  {
    ((StateDerivatives_f14tmp1 *) f14tmp1_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE = f14tmp1_B.Sum2;
    ((StateDerivatives_f14tmp1 *) f14tmp1_rtM->ModelData.derivs)
      ->TransferFcn1_CSTATE += (f14tmp1_P.TransferFcn1_A)*
      f14tmp1_X.TransferFcn1_CSTATE;
  }

  /* Derivatives for TransferFcn: '<S1>/Actuator Model' */
  {
    ((StateDerivatives_f14tmp1 *) f14tmp1_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE = f14tmp1_B.Sum_n;
    ((StateDerivatives_f14tmp1 *) f14tmp1_rtM->ModelData.derivs)
      ->ActuatorModel_CSTATE += (f14tmp1_P.ActuatorModel_A)*
      f14tmp1_X.ActuatorModel_CSTATE;
  }

  /* Derivatives for TransferFcn: '<S4>/W-gust model' */
  {
    ((StateDerivatives_f14tmp1 *) f14tmp1_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE[0] = f14tmp1_B.Output;
    ((StateDerivatives_f14tmp1 *) f14tmp1_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE[0] += (f14tmp1_P.Wgustmodel_A[0])*
      f14tmp1_X.Wgustmodel_CSTATE[0] + (f14tmp1_P.Wgustmodel_A[1])*
      f14tmp1_X.Wgustmodel_CSTATE[1];
    ((StateDerivatives_f14tmp1 *) f14tmp1_rtM->ModelData.derivs)
      ->Wgustmodel_CSTATE[1]= f14tmp1_X.Wgustmodel_CSTATE[0];
  }

  /* Derivatives for TransferFcn: '<S4>/Q-gust model' */
  {
    ((StateDerivatives_f14tmp1 *) f14tmp1_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE = f14tmp1_B.Wgustmodel;
    ((StateDerivatives_f14tmp1 *) f14tmp1_rtM->ModelData.derivs)
      ->Qgustmodel_CSTATE += (f14tmp1_P.Qgustmodel_A)*
      f14tmp1_X.Qgustmodel_CSTATE;
  }

  /* Derivatives for TransferFcn: '<S3>/Alpha-sensor Low-pass Filter' */
  {
    ((StateDerivatives_f14tmp1 *) f14tmp1_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CSTATE = f14tmp1_B.Gain5;
    ((StateDerivatives_f14tmp1 *) f14tmp1_rtM->ModelData.derivs)
      ->AlphasensorLowpassFilter_CSTATE += (f14tmp1_P.AlphasensorLowpassFilter_A)*
      f14tmp1_X.AlphasensorLowpassFilter_CSTATE;
  }

  /* Derivatives for TransferFcn: '<S3>/Stick Prefilter' */
  {
    ((StateDerivatives_f14tmp1 *) f14tmp1_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE = f14tmp1_B.Sum1_k;
    ((StateDerivatives_f14tmp1 *) f14tmp1_rtM->ModelData.derivs)
      ->StickPrefilter_CSTATE += (f14tmp1_P.StickPrefilter_A)*
      f14tmp1_X.StickPrefilter_CSTATE;
  }

  /* Derivatives for TransferFcn: '<S3>/Pitch Rate Lead Filter' */
  {
    ((StateDerivatives_f14tmp1 *) f14tmp1_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE = f14tmp1_B.TransferFcn1;
    ((StateDerivatives_f14tmp1 *) f14tmp1_rtM->ModelData.derivs)
      ->PitchRateLeadFilter_CSTATE += (f14tmp1_P.PitchRateLeadFilter_A)*
      f14tmp1_X.PitchRateLeadFilter_CSTATE;
  }

  /* Derivatives for TransferFcn: '<S3>/Proportional plus integral compensator' */
  {
    ((StateDerivatives_f14tmp1 *) f14tmp1_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompens = f14tmp1_B.Sum2_f;
    ((StateDerivatives_f14tmp1 *) f14tmp1_rtM->ModelData.derivs)
      ->Proportionalplusintegralcompens +=
      (f14tmp1_P.Proportionalplusintegralcompens)*
      f14tmp1_X.Proportionalplusintegralcompens;
  }
}

/* Model initialize function */
void f14tmp1_initialize(void)
{
  {
    uint32_T tseed;
    int32_T r;
    int32_T t;
    real_T tmp;

    /* Start for RandomNumber: '<S6>/White Noise' */
    tmp = floor(f14tmp1_P.WhiteNoise_Seed);
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

    f14tmp1_DWork.RandSeed = tseed;
    f14tmp1_DWork.NextOutput = rt_nrand_Upu32_Yd_f_pw_snf
      (&f14tmp1_DWork.RandSeed) * f14tmp1_P.WhiteNoise_StdDev +
      f14tmp1_P.WhiteNoise_Mean;

    /* End of Start for RandomNumber: '<S6>/White Noise' */
  }

  /* InitializeConditions for TransferFcn: '<S2>/Transfer Fcn.2' */
  f14tmp1_X.TransferFcn2_CSTATE = 0.0;

  /* InitializeConditions for Derivative: '<S5>/Derivative' */
  f14tmp1_DWork.Derivative_RWORK.TimeStampA = rtInf;
  f14tmp1_DWork.Derivative_RWORK.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S2>/Transfer Fcn.1' */
  f14tmp1_X.TransferFcn1_CSTATE = 0.0;

  /* InitializeConditions for Derivative: '<S5>/Derivative1' */
  f14tmp1_DWork.Derivative1_RWORK.TimeStampA = rtInf;
  f14tmp1_DWork.Derivative1_RWORK.TimeStampB = rtInf;

  /* InitializeConditions for TransferFcn: '<S1>/Actuator Model' */
  f14tmp1_X.ActuatorModel_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/W-gust model' */
  f14tmp1_X.Wgustmodel_CSTATE[0] = 0.0;
  f14tmp1_X.Wgustmodel_CSTATE[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Q-gust model' */
  f14tmp1_X.Qgustmodel_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S3>/Alpha-sensor Low-pass Filter' */
  f14tmp1_X.AlphasensorLowpassFilter_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S3>/Stick Prefilter' */
  f14tmp1_X.StickPrefilter_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S3>/Pitch Rate Lead Filter' */
  f14tmp1_X.PitchRateLeadFilter_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S3>/Proportional plus integral compensator' */
  f14tmp1_X.Proportionalplusintegralcompens = 0.0;
}

/* Model terminate function */
void f14tmp1_terminate(void)
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
  f14tmp1_output();

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  f14tmp1_update();

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
  f14tmp1_initialize();
}

void MdlTerminate(void)
{
  f14tmp1_terminate();
}

rtModel_f14tmp1 *f14tmp1(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)f14tmp1_rtM, 0,
                sizeof(rtModel_f14tmp1));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&f14tmp1_rtM->solverInfo,
                          &f14tmp1_rtM->Timing.simTimeStep);
    rtsiSetTPtr(&f14tmp1_rtM->solverInfo, &rtmGetTPtr(f14tmp1_rtM));
    rtsiSetStepSizePtr(&f14tmp1_rtM->solverInfo, &f14tmp1_rtM->Timing.stepSize0);
    rtsiSetdXPtr(&f14tmp1_rtM->solverInfo, &f14tmp1_rtM->ModelData.derivs);
    rtsiSetContStatesPtr(&f14tmp1_rtM->solverInfo,
                         &f14tmp1_rtM->ModelData.contStates);
    rtsiSetNumContStatesPtr(&f14tmp1_rtM->solverInfo,
      &f14tmp1_rtM->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&f14tmp1_rtM->solverInfo, (&rtmGetErrorStatus
      (f14tmp1_rtM)));
    rtsiSetRTModelPtr(&f14tmp1_rtM->solverInfo, f14tmp1_rtM);
  }

  rtsiSetSimTimeStep(&f14tmp1_rtM->solverInfo, MAJOR_TIME_STEP);
  f14tmp1_rtM->ModelData.intgData.y = f14tmp1_rtM->ModelData.odeY;
  f14tmp1_rtM->ModelData.intgData.f[0] = f14tmp1_rtM->ModelData.odeF[0];
  f14tmp1_rtM->ModelData.intgData.f[1] = f14tmp1_rtM->ModelData.odeF[1];
  f14tmp1_rtM->ModelData.intgData.f[2] = f14tmp1_rtM->ModelData.odeF[2];
  f14tmp1_rtM->ModelData.intgData.f[3] = f14tmp1_rtM->ModelData.odeF[3];
  f14tmp1_rtM->ModelData.contStates = ((real_T *) &f14tmp1_X);
  rtsiSetSolverData(&f14tmp1_rtM->solverInfo, (void *)
                    &f14tmp1_rtM->ModelData.intgData);
  rtsiSetSolverName(&f14tmp1_rtM->solverInfo,"ode4");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = f14tmp1_rtM->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    mdlTsMap[2] = 2;
    f14tmp1_rtM->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    f14tmp1_rtM->Timing.sampleTimes = (&f14tmp1_rtM->Timing.sampleTimesArray[0]);
    f14tmp1_rtM->Timing.offsetTimes = (&f14tmp1_rtM->Timing.offsetTimesArray[0]);

    /* task periods */
    f14tmp1_rtM->Timing.sampleTimes[0] = (0.0);
    f14tmp1_rtM->Timing.sampleTimes[1] = (0.01);
    f14tmp1_rtM->Timing.sampleTimes[2] = (0.1);

    /* task offsets */
    f14tmp1_rtM->Timing.offsetTimes[0] = (0.0);
    f14tmp1_rtM->Timing.offsetTimes[1] = (0.0);
    f14tmp1_rtM->Timing.offsetTimes[2] = (0.0);
  }

  rtmSetTPtr(f14tmp1_rtM, &f14tmp1_rtM->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = f14tmp1_rtM->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    mdlSampleHits[2] = 1;
    f14tmp1_rtM->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(f14tmp1_rtM, 10.0);
  f14tmp1_rtM->Timing.stepSize0 = 0.01;
  f14tmp1_rtM->Timing.stepSize1 = 0.01;
  f14tmp1_rtM->Timing.stepSize2 = 0.1;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    f14tmp1_rtM->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(f14tmp1_rtM->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(f14tmp1_rtM->rtwLogInfo, (NULL));
    rtliSetLogT(f14tmp1_rtM->rtwLogInfo, "tout");
    rtliSetLogX(f14tmp1_rtM->rtwLogInfo, "");
    rtliSetLogXFinal(f14tmp1_rtM->rtwLogInfo, "");
    rtliSetSigLog(f14tmp1_rtM->rtwLogInfo, "");
    rtliSetLogVarNameModifier(f14tmp1_rtM->rtwLogInfo, "rt_");
    rtliSetLogFormat(f14tmp1_rtM->rtwLogInfo, 0);
    rtliSetLogMaxRows(f14tmp1_rtM->rtwLogInfo, 1000);
    rtliSetLogDecimation(f14tmp1_rtM->rtwLogInfo, 1);
    rtliSetLogY(f14tmp1_rtM->rtwLogInfo, "");
    rtliSetLogYSignalInfo(f14tmp1_rtM->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(f14tmp1_rtM->rtwLogInfo, (NULL));
  }

  f14tmp1_rtM->solverInfoPtr = (&f14tmp1_rtM->solverInfo);
  f14tmp1_rtM->Timing.stepSize = (0.01);
  rtsiSetFixedStepSize(&f14tmp1_rtM->solverInfo, 0.01);
  rtsiSetSolverMode(&f14tmp1_rtM->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  f14tmp1_rtM->ModelData.blockIO = ((void *) &f14tmp1_B);
  (void) memset(((void *) &f14tmp1_B), 0,
                sizeof(BlockIO_f14tmp1));

  /* parameters */
  f14tmp1_rtM->ModelData.defaultParam = ((real_T *)&f14tmp1_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &f14tmp1_X;
    f14tmp1_rtM->ModelData.contStates = (x);
    (void) memset((void *)&f14tmp1_X, 0,
                  sizeof(ContinuousStates_f14tmp1));
  }

  /* states (dwork) */
  f14tmp1_rtM->Work.dwork = ((void *) &f14tmp1_DWork);
  (void) memset((void *)&f14tmp1_DWork, 0,
                sizeof(D_Work_f14tmp1));

  /* Initialize DataMapInfo substructure containing ModelMap for C API */
  f14tmp1_InitializeDataMapInfo(f14tmp1_rtM);

  /* Initialize Sizes */
  f14tmp1_rtM->Sizes.numContStates = (10);/* Number of continuous states */
  f14tmp1_rtM->Sizes.numY = (0);       /* Number of model outputs */
  f14tmp1_rtM->Sizes.numU = (0);       /* Number of model inputs */
  f14tmp1_rtM->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  f14tmp1_rtM->Sizes.numSampTimes = (3);/* Number of sample times */
  f14tmp1_rtM->Sizes.numBlocks = (40); /* Number of blocks */
  f14tmp1_rtM->Sizes.numBlockIO = (36);/* Number of block outputs */
  f14tmp1_rtM->Sizes.numBlockPrms = (42);/* Sum of parameter "widths" */
  return f14tmp1_rtM;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
