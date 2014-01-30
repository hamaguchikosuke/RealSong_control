/*
 * xpcosc.c
 *
 * Code generation for model "xpcosc".
 *
 * Model version              : 1.9
 * Simulink Coder version : 8.3 (R2012b) 20-Jul-2012
 * C source code generated on : Mon Sep 16 12:45:56 2013
 *
 * Target selection: xpctarget.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->32-bit x86 compatible
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "rt_logging_mmi.h"
#include "xpcosc_capi.h"
#include "xpcosc.h"
#include "xpcosc_private.h"
#include "xpcosc_dt.h"

/* Block signals (auto storage) */
BlockIO_xpcosc xpcosc_B;

/* Continuous states */
ContinuousStates_xpcosc xpcosc_X;

/* Block states (auto storage) */
D_Work_xpcosc xpcosc_DWork;

/* External outputs (root outports fed by signals with auto storage) */
ExternalOutputs_xpcosc xpcosc_Y;

/* Real-time model */
rtModel_xpcosc xpcosc_rtM_;
rtModel_xpcosc *const xpcosc_rtM = &xpcosc_rtM_;

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
  int_T nXc = 2;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  xpcosc_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  xpcosc_output();
  xpcosc_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  xpcosc_output();
  xpcosc_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  xpcosc_output();
  xpcosc_derivatives();

  /* tnew = t + h
     ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void xpcosc_output(void)
{
  real_T temp;
  if (rtmIsMajorTimeStep(xpcosc_rtM)) {
    /* set solver stop time */
    if (!(xpcosc_rtM->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&xpcosc_rtM->solverInfo,
                            ((xpcosc_rtM->Timing.clockTickH0 + 1) *
        xpcosc_rtM->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&xpcosc_rtM->solverInfo,
                            ((xpcosc_rtM->Timing.clockTick0 + 1) *
        xpcosc_rtM->Timing.stepSize0 + xpcosc_rtM->Timing.clockTickH0 *
        xpcosc_rtM->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(xpcosc_rtM)) {
    xpcosc_rtM->Timing.t[0] = rtsiGetT(&xpcosc_rtM->solverInfo);
  }

  /* Integrator: '<Root>/Integrator1' */
  xpcosc_B.Integrator1 = xpcosc_X.Integrator1_CSTATE;

  /* SignalGenerator: '<Root>/Signal Generator' */
  temp = xpcosc_P.SignalGenerator_Frequency * xpcosc_rtM->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    xpcosc_B.SignalGenerator = xpcosc_P.SignalGenerator_Amplitude;
  } else {
    xpcosc_B.SignalGenerator = -xpcosc_P.SignalGenerator_Amplitude;
  }

  /* End of SignalGenerator: '<Root>/Signal Generator' */

  /* Outport: '<Root>/Outport' */
  xpcosc_Y.Outport[0] = xpcosc_B.Integrator1;
  xpcosc_Y.Outport[1] = xpcosc_B.SignalGenerator;
  if (rtmIsMajorTimeStep(xpcosc_rtM)) {
  }

  /* Gain: '<Root>/Gain' */
  xpcosc_B.Gain = xpcosc_P.Gain_Gain * xpcosc_B.Integrator1;

  /* Integrator: '<Root>/Integrator' */
  xpcosc_B.Integrator = xpcosc_X.Integrator_CSTATE;

  /* Gain: '<Root>/Gain1' */
  xpcosc_B.Gain1 = xpcosc_P.Gain1_Gain * xpcosc_B.Integrator;

  /* Gain: '<Root>/Gain2' */
  xpcosc_B.Gain2 = xpcosc_P.Gain2_Gain * xpcosc_B.SignalGenerator;

  /* Sum: '<Root>/Sum' */
  xpcosc_B.Sum = (xpcosc_B.Gain2 - xpcosc_B.Gain) - xpcosc_B.Gain1;
}

/* Model update function */
void xpcosc_update(void)
{
  if (rtmIsMajorTimeStep(xpcosc_rtM)) {
    rt_ertODEUpdateContinuousStates(&xpcosc_rtM->solverInfo);
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
  if (!(++xpcosc_rtM->Timing.clockTick0)) {
    ++xpcosc_rtM->Timing.clockTickH0;
  }

  xpcosc_rtM->Timing.t[0] = rtsiGetSolverStopTime(&xpcosc_rtM->solverInfo);

  {
    /* Update absolute timer for sample time: [0.00025s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++xpcosc_rtM->Timing.clockTick1)) {
      ++xpcosc_rtM->Timing.clockTickH1;
    }

    xpcosc_rtM->Timing.t[1] = xpcosc_rtM->Timing.clockTick1 *
      xpcosc_rtM->Timing.stepSize1 + xpcosc_rtM->Timing.clockTickH1 *
      xpcosc_rtM->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void xpcosc_derivatives(void)
{
  StateDerivatives_xpcosc *_rtXdot;
  _rtXdot = ((StateDerivatives_xpcosc *) xpcosc_rtM->ModelData.derivs);

  /* Derivatives for Integrator: '<Root>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = xpcosc_B.Integrator;

  /* Derivatives for Integrator: '<Root>/Integrator' */
  _rtXdot->Integrator_CSTATE = xpcosc_B.Sum;
}

/* Model initialize function */
void xpcosc_initialize(void)
{
  /* InitializeConditions for Integrator: '<Root>/Integrator1' */
  xpcosc_X.Integrator1_CSTATE = xpcosc_P.Integrator1_IC;

  /* InitializeConditions for Integrator: '<Root>/Integrator' */
  xpcosc_X.Integrator_CSTATE = xpcosc_P.Integrator_IC;
}

/* Model terminate function */
void xpcosc_terminate(void)
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
  xpcosc_output();

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  xpcosc_update();

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
  xpcosc_initialize();
}

void MdlTerminate(void)
{
  xpcosc_terminate();
}

rtModel_xpcosc *xpcosc(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)xpcosc_rtM, 0,
                sizeof(rtModel_xpcosc));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&xpcosc_rtM->solverInfo,
                          &xpcosc_rtM->Timing.simTimeStep);
    rtsiSetTPtr(&xpcosc_rtM->solverInfo, &rtmGetTPtr(xpcosc_rtM));
    rtsiSetStepSizePtr(&xpcosc_rtM->solverInfo, &xpcosc_rtM->Timing.stepSize0);
    rtsiSetdXPtr(&xpcosc_rtM->solverInfo, &xpcosc_rtM->ModelData.derivs);
    rtsiSetContStatesPtr(&xpcosc_rtM->solverInfo,
                         &xpcosc_rtM->ModelData.contStates);
    rtsiSetNumContStatesPtr(&xpcosc_rtM->solverInfo,
      &xpcosc_rtM->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&xpcosc_rtM->solverInfo, (&rtmGetErrorStatus
      (xpcosc_rtM)));
    rtsiSetRTModelPtr(&xpcosc_rtM->solverInfo, xpcosc_rtM);
  }

  rtsiSetSimTimeStep(&xpcosc_rtM->solverInfo, MAJOR_TIME_STEP);
  xpcosc_rtM->ModelData.intgData.y = xpcosc_rtM->ModelData.odeY;
  xpcosc_rtM->ModelData.intgData.f[0] = xpcosc_rtM->ModelData.odeF[0];
  xpcosc_rtM->ModelData.intgData.f[1] = xpcosc_rtM->ModelData.odeF[1];
  xpcosc_rtM->ModelData.intgData.f[2] = xpcosc_rtM->ModelData.odeF[2];
  xpcosc_rtM->ModelData.intgData.f[3] = xpcosc_rtM->ModelData.odeF[3];
  xpcosc_rtM->ModelData.contStates = ((real_T *) &xpcosc_X);
  rtsiSetSolverData(&xpcosc_rtM->solverInfo, (void *)
                    &xpcosc_rtM->ModelData.intgData);
  rtsiSetSolverName(&xpcosc_rtM->solverInfo,"ode4");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = xpcosc_rtM->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    xpcosc_rtM->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    xpcosc_rtM->Timing.sampleTimes = (&xpcosc_rtM->Timing.sampleTimesArray[0]);
    xpcosc_rtM->Timing.offsetTimes = (&xpcosc_rtM->Timing.offsetTimesArray[0]);

    /* task periods */
    xpcosc_rtM->Timing.sampleTimes[0] = (0.0);
    xpcosc_rtM->Timing.sampleTimes[1] = (0.00025);

    /* task offsets */
    xpcosc_rtM->Timing.offsetTimes[0] = (0.0);
    xpcosc_rtM->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(xpcosc_rtM, &xpcosc_rtM->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = xpcosc_rtM->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    xpcosc_rtM->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(xpcosc_rtM, 0.2);
  xpcosc_rtM->Timing.stepSize0 = 0.00025;
  xpcosc_rtM->Timing.stepSize1 = 0.00025;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    xpcosc_rtM->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    /*
     * Set pointers to the data and signal info each state
     */
    {
      static int_T rt_LoggedStateWidths[] = {
        1,
        1
      };

      static int_T rt_LoggedStateNumDimensions[] = {
        1,
        1
      };

      static int_T rt_LoggedStateDimensions[] = {
        1,
        1
      };

      static boolean_T rt_LoggedStateIsVarDims[] = {
        0,
        0
      };

      static BuiltInDTypeId rt_LoggedStateDataTypeIds[] = {
        SS_DOUBLE,
        SS_DOUBLE
      };

      static int_T rt_LoggedStateComplexSignals[] = {
        0,
        0
      };

      static const char_T *rt_LoggedStateLabels[] = {
        "CSTATE",
        "CSTATE"
      };

      static const char_T *rt_LoggedStateBlockNames[] = {
        "xpcosc/Integrator1",
        "xpcosc/Integrator"
      };

      static const char_T *rt_LoggedStateNames[] = {
        "",
        ""
      };

      static boolean_T rt_LoggedStateCrossMdlRef[] = {
        0,
        0
      };

      static RTWLogDataTypeConvert rt_RTWLogDataTypeConvert[] = {
        { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 },

        { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 }
      };

      static RTWLogSignalInfo rt_LoggedStateSignalInfo = {
        2,
        rt_LoggedStateWidths,
        rt_LoggedStateNumDimensions,
        rt_LoggedStateDimensions,
        rt_LoggedStateIsVarDims,
        (NULL),
        (NULL),
        rt_LoggedStateDataTypeIds,
        rt_LoggedStateComplexSignals,
        (NULL),

        { rt_LoggedStateLabels },
        (NULL),
        (NULL),
        (NULL),

        { rt_LoggedStateBlockNames },

        { rt_LoggedStateNames },
        rt_LoggedStateCrossMdlRef,
        rt_RTWLogDataTypeConvert
      };

      static void * rt_LoggedStateSignalPtrs[2];
      rtliSetLogXSignalPtrs(xpcosc_rtM->rtwLogInfo, (LogSignalPtrsType)
                            rt_LoggedStateSignalPtrs);
      rtliSetLogXSignalInfo(xpcosc_rtM->rtwLogInfo, &rt_LoggedStateSignalInfo);
      rt_LoggedStateSignalPtrs[0] = (void*)&xpcosc_X.Integrator1_CSTATE;
      rt_LoggedStateSignalPtrs[1] = (void*)&xpcosc_X.Integrator_CSTATE;
    }

    rtliSetLogT(xpcosc_rtM->rtwLogInfo, "tout");
    rtliSetLogX(xpcosc_rtM->rtwLogInfo, "xout");
    rtliSetLogXFinal(xpcosc_rtM->rtwLogInfo, "");
    rtliSetSigLog(xpcosc_rtM->rtwLogInfo, "");
    rtliSetLogVarNameModifier(xpcosc_rtM->rtwLogInfo, "rt_");
    rtliSetLogFormat(xpcosc_rtM->rtwLogInfo, 0);
    rtliSetLogMaxRows(xpcosc_rtM->rtwLogInfo, 0);
    rtliSetLogDecimation(xpcosc_rtM->rtwLogInfo, 1);

    /*
     * Set pointers to the data and signal info for each output
     */
    {
      static void * rt_LoggedOutputSignalPtrs[] = {
        &xpcosc_Y.Outport[0]
      };

      rtliSetLogYSignalPtrs(xpcosc_rtM->rtwLogInfo, ((LogSignalPtrsType)
        rt_LoggedOutputSignalPtrs));
    }

    {
      static int_T rt_LoggedOutputWidths[] = {
        2
      };

      static int_T rt_LoggedOutputNumDimensions[] = {
        1
      };

      static int_T rt_LoggedOutputDimensions[] = {
        2
      };

      static boolean_T rt_LoggedOutputIsVarDims[] = {
        0
      };

      static void* rt_LoggedCurrentSignalDimensions[] = {
        (NULL)
      };

      static int_T rt_LoggedCurrentSignalDimensionsSize[] = {
        4
      };

      static BuiltInDTypeId rt_LoggedOutputDataTypeIds[] = {
        SS_DOUBLE
      };

      static int_T rt_LoggedOutputComplexSignals[] = {
        0
      };

      static const char_T *rt_LoggedOutputLabels[] = {
        "" };

      static const char_T *rt_LoggedOutputBlockNames[] = {
        "xpcosc/Outport" };

      static RTWLogDataTypeConvert rt_RTWLogDataTypeConvert[] = {
        { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 }
      };

      static RTWLogSignalInfo rt_LoggedOutputSignalInfo[] = {
        {
          1,
          rt_LoggedOutputWidths,
          rt_LoggedOutputNumDimensions,
          rt_LoggedOutputDimensions,
          rt_LoggedOutputIsVarDims,
          rt_LoggedCurrentSignalDimensions,
          rt_LoggedCurrentSignalDimensionsSize,
          rt_LoggedOutputDataTypeIds,
          rt_LoggedOutputComplexSignals,
          (NULL),

          { rt_LoggedOutputLabels },
          (NULL),
          (NULL),
          (NULL),

          { rt_LoggedOutputBlockNames },

          { (NULL) },
          (NULL),
          rt_RTWLogDataTypeConvert
        }
      };

      rtliSetLogYSignalInfo(xpcosc_rtM->rtwLogInfo, rt_LoggedOutputSignalInfo);

      /* set currSigDims field */
      rt_LoggedCurrentSignalDimensions[0] = &rt_LoggedOutputWidths[0];
    }

    rtliSetLogY(xpcosc_rtM->rtwLogInfo, "yout");
  }

  /* External mode info */
  xpcosc_rtM->Sizes.checksums[0] = (3657533236U);
  xpcosc_rtM->Sizes.checksums[1] = (1582885141U);
  xpcosc_rtM->Sizes.checksums[2] = (1516398116U);
  xpcosc_rtM->Sizes.checksums[3] = (1640913541U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    xpcosc_rtM->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(xpcosc_rtM->extModeInfo,
      &xpcosc_rtM->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(xpcosc_rtM->extModeInfo, xpcosc_rtM->Sizes.checksums);
    rteiSetTPtr(xpcosc_rtM->extModeInfo, rtmGetTPtr(xpcosc_rtM));
  }

  xpcosc_rtM->solverInfoPtr = (&xpcosc_rtM->solverInfo);
  xpcosc_rtM->Timing.stepSize = (0.00025);
  rtsiSetFixedStepSize(&xpcosc_rtM->solverInfo, 0.00025);
  rtsiSetSolverMode(&xpcosc_rtM->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  xpcosc_rtM->ModelData.blockIO = ((void *) &xpcosc_B);

  {
    xpcosc_B.Integrator1 = 0.0;
    xpcosc_B.SignalGenerator = 0.0;
    xpcosc_B.Gain = 0.0;
    xpcosc_B.Integrator = 0.0;
    xpcosc_B.Gain1 = 0.0;
    xpcosc_B.Gain2 = 0.0;
    xpcosc_B.Sum = 0.0;
  }

  /* parameters */
  xpcosc_rtM->ModelData.defaultParam = ((real_T *)&xpcosc_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &xpcosc_X;
    xpcosc_rtM->ModelData.contStates = (x);
    (void) memset((void *)&xpcosc_X, 0,
                  sizeof(ContinuousStates_xpcosc));
  }

  /* states (dwork) */
  xpcosc_rtM->Work.dwork = ((void *) &xpcosc_DWork);
  (void) memset((void *)&xpcosc_DWork, 0,
                sizeof(D_Work_xpcosc));

  /* external outputs */
  xpcosc_rtM->ModelData.outputs = (&xpcosc_Y);
  xpcosc_Y.Outport[0] = 0.0;
  xpcosc_Y.Outport[1] = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    xpcosc_rtM->SpecialInfo.mappingInfo = (&dtInfo);
    xpcosc_rtM->SpecialInfo.xpcData = ((void*) &dtInfo);
    dtInfo.numDataTypes = 14;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.B = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.P = &rtPTransTable;
  }

  /* Initialize DataMapInfo substructure containing ModelMap for C API */
  xpcosc_InitializeDataMapInfo(xpcosc_rtM);

  /* Initialize Sizes */
  xpcosc_rtM->Sizes.numContStates = (2);/* Number of continuous states */
  xpcosc_rtM->Sizes.numY = (2);        /* Number of model outputs */
  xpcosc_rtM->Sizes.numU = (0);        /* Number of model inputs */
  xpcosc_rtM->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  xpcosc_rtM->Sizes.numSampTimes = (2);/* Number of sample times */
  xpcosc_rtM->Sizes.numBlocks = (9);   /* Number of blocks */
  xpcosc_rtM->Sizes.numBlockIO = (7);  /* Number of block outputs */
  xpcosc_rtM->Sizes.numBlockPrms = (7);/* Sum of parameter "widths" */
  return xpcosc_rtM;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
