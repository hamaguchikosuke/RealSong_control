/*
 * xpcminimal.c
 *
 * Code generation for model "xpcminimal".
 *
 * Model version              : 1.0
 * Simulink Coder version : 8.3 (R2012b) 20-Jul-2012
 * C source code generated on : Mon Sep 16 12:48:17 2013
 *
 * Target selection: xpctarget.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->32-bit x86 compatible
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "rt_logging_mmi.h"
#include "xpcminimal_capi.h"
#include "xpcminimal.h"
#include "xpcminimal_private.h"

/* Block signals (auto storage) */
BlockIO_xpcminimal xpcminimal_B;

/* Real-time model */
rtModel_xpcminimal xpcminimal_rtM_;
rtModel_xpcminimal *const xpcminimal_rtM = &xpcminimal_rtM_;

/* Model output function */
static void xpcminimal_output(void)
{
  /* Gain: '<Root>/Gain' incorporates:
   *  Constant: '<Root>/Constant'
   */
  xpcminimal_B.Gain = xpcminimal_P.Gain_Gain * xpcminimal_P.Constant_Value;
}

/* Model update function */
static void xpcminimal_update(void)
{
  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++xpcminimal_rtM->Timing.clockTick0)) {
    ++xpcminimal_rtM->Timing.clockTickH0;
  }

  xpcminimal_rtM->Timing.t[0] = xpcminimal_rtM->Timing.clockTick0 *
    xpcminimal_rtM->Timing.stepSize0 + xpcminimal_rtM->Timing.clockTickH0 *
    xpcminimal_rtM->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void xpcminimal_initialize(void)
{
}

/* Model terminate function */
void xpcminimal_terminate(void)
{
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  xpcminimal_output();

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  xpcminimal_update();

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
  xpcminimal_initialize();
}

void MdlTerminate(void)
{
  xpcminimal_terminate();
}

rtModel_xpcminimal *xpcminimal(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)xpcminimal_rtM, 0,
                sizeof(rtModel_xpcminimal));

  /* Initialize timing info */
  {
    int_T *mdlTsMap = xpcminimal_rtM->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    xpcminimal_rtM->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    xpcminimal_rtM->Timing.sampleTimes =
      (&xpcminimal_rtM->Timing.sampleTimesArray[0]);
    xpcminimal_rtM->Timing.offsetTimes =
      (&xpcminimal_rtM->Timing.offsetTimesArray[0]);

    /* task periods */
    xpcminimal_rtM->Timing.sampleTimes[0] = (0.001);

    /* task offsets */
    xpcminimal_rtM->Timing.offsetTimes[0] = (0.0);
  }

  rtmSetTPtr(xpcminimal_rtM, &xpcminimal_rtM->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = xpcminimal_rtM->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    xpcminimal_rtM->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(xpcminimal_rtM, 10.0);
  xpcminimal_rtM->Timing.stepSize0 = 0.001;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    xpcminimal_rtM->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(xpcminimal_rtM->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(xpcminimal_rtM->rtwLogInfo, (NULL));
    rtliSetLogT(xpcminimal_rtM->rtwLogInfo, "tout");
    rtliSetLogX(xpcminimal_rtM->rtwLogInfo, "");
    rtliSetLogXFinal(xpcminimal_rtM->rtwLogInfo, "");
    rtliSetSigLog(xpcminimal_rtM->rtwLogInfo, "");
    rtliSetLogVarNameModifier(xpcminimal_rtM->rtwLogInfo, "rt_");
    rtliSetLogFormat(xpcminimal_rtM->rtwLogInfo, 0);
    rtliSetLogMaxRows(xpcminimal_rtM->rtwLogInfo, 1000);
    rtliSetLogDecimation(xpcminimal_rtM->rtwLogInfo, 1);
    rtliSetLogY(xpcminimal_rtM->rtwLogInfo, "");
    rtliSetLogYSignalInfo(xpcminimal_rtM->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(xpcminimal_rtM->rtwLogInfo, (NULL));
  }

  xpcminimal_rtM->solverInfoPtr = (&xpcminimal_rtM->solverInfo);
  xpcminimal_rtM->Timing.stepSize = (0.001);
  rtsiSetFixedStepSize(&xpcminimal_rtM->solverInfo, 0.001);
  rtsiSetSolverMode(&xpcminimal_rtM->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  xpcminimal_rtM->ModelData.blockIO = ((void *) &xpcminimal_B);
  (void) memset(((void *) &xpcminimal_B), 0,
                sizeof(BlockIO_xpcminimal));

  /* parameters */
  xpcminimal_rtM->ModelData.defaultParam = ((real_T *)&xpcminimal_P);

  /* Initialize DataMapInfo substructure containing ModelMap for C API */
  xpcminimal_InitializeDataMapInfo(xpcminimal_rtM);

  /* Initialize Sizes */
  xpcminimal_rtM->Sizes.numContStates = (0);/* Number of continuous states */
  xpcminimal_rtM->Sizes.numY = (0);    /* Number of model outputs */
  xpcminimal_rtM->Sizes.numU = (0);    /* Number of model inputs */
  xpcminimal_rtM->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  xpcminimal_rtM->Sizes.numSampTimes = (1);/* Number of sample times */
  xpcminimal_rtM->Sizes.numBlocks = (2);/* Number of blocks */
  xpcminimal_rtM->Sizes.numBlockIO = (1);/* Number of block outputs */
  xpcminimal_rtM->Sizes.numBlockPrms = (2);/* Sum of parameter "widths" */
  return xpcminimal_rtM;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
