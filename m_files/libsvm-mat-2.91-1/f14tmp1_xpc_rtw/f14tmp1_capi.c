/*
 * f14tmp1_capi.c
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
#include "rtw_capi.h"
#include "f14tmp1_private.h"

/* Block output signal information */
static const rtwCAPI_Signals rtBlockSignals[] = {
  /* addrMapIndex, sysNum, blockPath,
   * signalName, portNumber, dataTypeIndex, dimIndex, fxpIndex, sTimeIndex
   */
  { 0, 0, "Subsystem/Gain",
    "", 0, 0, 0, 0, 0 },

  { 1, 0, "Subsystem/Gain1",
    "", 0, 0, 0, 0, 0 },

  { 2, 0, "Subsystem/Gain2",
    "", 0, 0, 0, 0, 0 },

  { 3, 0, "Subsystem/Gain5",
    "", 0, 0, 0, 0, 0 },

  { 4, 0, "Subsystem/Pilot",
    "", 0, 0, 0, 0, 0 },

  { 5, 0, "Subsystem/Sum",
    "", 0, 0, 0, 0, 0 },

  { 6, 0, "Subsystem/Sum1",
    "", 0, 0, 0, 0, 0 },

  { 7, 0, "Subsystem/Actuator Model",
    "", 0, 0, 0, 0, 0 },

  { 8, 0, "Subsystem/Aircraft Dynamics Model/Gain3",
    "", 0, 0, 0, 0, 0 },

  { 9, 0, "Subsystem/Aircraft Dynamics Model/Gain4",
    "", 0, 0, 0, 0, 0 },

  { 10, 0, "Subsystem/Aircraft Dynamics Model/Gain5",
    "", 0, 0, 0, 0, 0 },

  { 11, 0, "Subsystem/Aircraft Dynamics Model/Gain6",
    "", 0, 0, 0, 0, 0 },

  { 12, 0, "Subsystem/Aircraft Dynamics Model/Sum1",
    "", 0, 0, 0, 0, 0 },

  { 13, 0, "Subsystem/Aircraft Dynamics Model/Sum2",
    "", 0, 0, 0, 0, 0 },

  { 14, 0, "Subsystem/Aircraft Dynamics Model/Transfer Fcn.1",
    "", 0, 0, 0, 0, 0 },

  { 15, 0, "Subsystem/Aircraft Dynamics Model/Transfer Fcn.2",
    "", 0, 0, 0, 0, 0 },

  { 16, 0, "Subsystem/Controller/Gain",
    "", 0, 0, 0, 0, 0 },

  { 17, 0, "Subsystem/Controller/Gain2",
    "", 0, 0, 0, 0, 0 },

  { 18, 0, "Subsystem/Controller/Gain3",
    "", 0, 0, 0, 0, 0 },

  { 19, 0, "Subsystem/Controller/Sum",
    "", 0, 0, 0, 0, 0 },

  { 20, 0, "Subsystem/Controller/Sum1",
    "", 0, 0, 0, 0, 0 },

  { 21, 0, "Subsystem/Controller/Sum2",
    "", 0, 0, 0, 0, 0 },

  { 22, 0, "Subsystem/Controller/Alpha-sensor Low-pass Filter",
    "", 0, 0, 0, 0, 0 },

  { 23, 0, "Subsystem/Controller/Pitch Rate Lead Filter",
    "", 0, 0, 0, 0, 0 },

  { 24, 0, "Subsystem/Controller/Proportional plus integral compensator",
    "", 0, 0, 0, 0, 0 },

  { 25, 0, "Subsystem/Controller/Stick Prefilter",
    "", 0, 0, 0, 0, 0 },

  { 26, 0, "Subsystem/Dryden Wind Gust Models/Q-gust model",
    "", 0, 0, 0, 0, 0 },

  { 27, 0, "Subsystem/Dryden Wind Gust Models/W-gust model",
    "", 0, 0, 0, 0, 0 },

  { 28, 0, "Subsystem/Nz pilot calculation/Derivative",
    "", 0, 0, 0, 0, 0 },

  { 29, 0, "Subsystem/Nz pilot calculation/Derivative1",
    "", 0, 0, 0, 0, 0 },

  { 30, 0, "Subsystem/Nz pilot calculation/Gain1",
    "", 0, 0, 0, 0, 0 },

  { 31, 0, "Subsystem/Nz pilot calculation/Gain2",
    "", 0, 0, 0, 0, 0 },

  { 32, 0, "Subsystem/Nz pilot calculation/Product",
    "", 0, 0, 0, 0, 0 },

  { 33, 0, "Subsystem/Nz pilot calculation/Sum1",
    "", 0, 0, 0, 0, 0 },

  { 34, 0, "Subsystem/Dryden Wind Gust Models/Band-Limited White Noise/Output",
    "", 0, 0, 0, 0, 1 },

  { 35, 0,
    "Subsystem/Dryden Wind Gust Models/Band-Limited White Noise/White Noise",
    "", 0, 0, 0, 0, 1 },

  {
    0, 0, NULL, NULL, 0, 0, 0, 0, 0
  }
};

/* Tunable block parameters */
static const rtwCAPI_BlockParameters rtBlockParameters[] = {
  /* addrMapIndex, blockPath,
   * paramName, dataTypeIndex, dimIndex, fixPtIdx
   */
  { 36, "Subsystem/Gain",
    "Gain", 0, 0, 0 },

  { 37, "Subsystem/Gain1",
    "Gain", 0, 0, 0 },

  { 38, "Subsystem/Gain2",
    "Gain", 0, 0, 0 },

  { 39, "Subsystem/Gain5",
    "Gain", 0, 0, 0 },

  { 40, "Subsystem/Pilot",
    "Amplitude", 0, 0, 0 },

  { 41, "Subsystem/Pilot",
    "Frequency", 0, 0, 0 },

  { 42, "Subsystem/Actuator Model",
    "A", 0, 0, 0 },

  { 43, "Subsystem/Actuator Model",
    "C", 0, 0, 0 },

  { 44, "Subsystem/Aircraft Dynamics Model/Gain3",
    "Gain", 0, 0, 0 },

  { 45, "Subsystem/Aircraft Dynamics Model/Gain4",
    "Gain", 0, 0, 0 },

  { 46, "Subsystem/Aircraft Dynamics Model/Gain5",
    "Gain", 0, 0, 0 },

  { 47, "Subsystem/Aircraft Dynamics Model/Gain6",
    "Gain", 0, 0, 0 },

  { 48, "Subsystem/Aircraft Dynamics Model/Transfer Fcn.1",
    "A", 0, 0, 0 },

  { 49, "Subsystem/Aircraft Dynamics Model/Transfer Fcn.1",
    "C", 0, 0, 0 },

  { 50, "Subsystem/Aircraft Dynamics Model/Transfer Fcn.2",
    "A", 0, 0, 0 },

  { 51, "Subsystem/Aircraft Dynamics Model/Transfer Fcn.2",
    "C", 0, 0, 0 },

  { 52, "Subsystem/Controller/Gain",
    "Gain", 0, 0, 0 },

  { 53, "Subsystem/Controller/Gain2",
    "Gain", 0, 0, 0 },

  { 54, "Subsystem/Controller/Gain3",
    "Gain", 0, 0, 0 },

  { 55, "Subsystem/Controller/Alpha-sensor Low-pass Filter",
    "A", 0, 0, 0 },

  { 56, "Subsystem/Controller/Alpha-sensor Low-pass Filter",
    "C", 0, 0, 0 },

  { 57, "Subsystem/Controller/Pitch Rate Lead Filter",
    "A", 0, 0, 0 },

  { 58, "Subsystem/Controller/Pitch Rate Lead Filter",
    "C", 0, 0, 0 },

  { 59, "Subsystem/Controller/Pitch Rate Lead Filter",
    "D", 0, 0, 0 },

  { 60, "Subsystem/Controller/Proportional plus integral compensator",
    "A", 0, 0, 0 },

  { 61, "Subsystem/Controller/Proportional plus integral compensator",
    "C", 0, 0, 0 },

  { 62, "Subsystem/Controller/Stick Prefilter",
    "A", 0, 0, 0 },

  { 63, "Subsystem/Controller/Stick Prefilter",
    "C", 0, 0, 0 },

  { 64, "Subsystem/Dryden Wind Gust Models/Q-gust model",
    "A", 0, 0, 0 },

  { 65, "Subsystem/Dryden Wind Gust Models/Q-gust model",
    "C", 0, 0, 0 },

  { 66, "Subsystem/Dryden Wind Gust Models/Q-gust model",
    "D", 0, 0, 0 },

  { 67, "Subsystem/Dryden Wind Gust Models/W-gust model",
    "A", 0, 1, 0 },

  { 68, "Subsystem/Dryden Wind Gust Models/W-gust model",
    "C", 0, 2, 0 },

  { 69, "Subsystem/Nz pilot calculation/Constant",
    "Value", 0, 0, 0 },

  { 70, "Subsystem/Nz pilot calculation/Gain1",
    "Gain", 0, 0, 0 },

  { 71, "Subsystem/Nz pilot calculation/Gain2",
    "Gain", 0, 0, 0 },

  { 72, "Subsystem/Dryden Wind Gust Models/Band-Limited White Noise/Output",
    "Gain", 0, 0, 0 },

  { 73, "Subsystem/Dryden Wind Gust Models/Band-Limited White Noise/White Noise",
    "Mean", 0, 0, 0 },

  { 74, "Subsystem/Dryden Wind Gust Models/Band-Limited White Noise/White Noise",
    "StdDev", 0, 0, 0 },

  { 75, "Subsystem/Dryden Wind Gust Models/Band-Limited White Noise/White Noise",
    "Seed", 0, 0, 0 },

  {
    0, NULL, NULL, 0, 0, 0
  }
};

/* Tunable variable parameters */
static const rtwCAPI_ModelParameters rtModelParameters[] = {
  /* addrMapIndex, varName, dataTypeIndex, dimIndex, fixPtIndex */
  { 0, NULL, 0, 0, 0 }
};

/* Declare Data Addresses statically */
static void* rtDataAddrMap[] = {
  &f14tmp1_B.Gain,                     /* 0: Signal */
  &f14tmp1_B.Gain1_h,                  /* 1: Signal */
  &f14tmp1_B.Gain2_f,                  /* 2: Signal */
  &f14tmp1_B.Gain5,                    /* 3: Signal */
  &f14tmp1_B.Pilot,                    /* 4: Signal */
  &f14tmp1_B.Sum,                      /* 5: Signal */
  &f14tmp1_B.Sum1_k,                   /* 6: Signal */
  &f14tmp1_B.ActuatorModel,            /* 7: Signal */
  &f14tmp1_B.Gain3,                    /* 8: Signal */
  &f14tmp1_B.Gain4,                    /* 9: Signal */
  &f14tmp1_B.Gain5_b,                  /* 10: Signal */
  &f14tmp1_B.Gain6,                    /* 11: Signal */
  &f14tmp1_B.Sum1_o,                   /* 12: Signal */
  &f14tmp1_B.Sum2,                     /* 13: Signal */
  &f14tmp1_B.TransferFcn1,             /* 14: Signal */
  &f14tmp1_B.TransferFcn2,             /* 15: Signal */
  &f14tmp1_B.Gain_d,                   /* 16: Signal */
  &f14tmp1_B.Gain2_e,                  /* 17: Signal */
  &f14tmp1_B.Gain3_g,                  /* 18: Signal */
  &f14tmp1_B.Sum_n,                    /* 19: Signal */
  &f14tmp1_B.Sum1_d,                   /* 20: Signal */
  &f14tmp1_B.Sum2_f,                   /* 21: Signal */
  &f14tmp1_B.AlphasensorLowpassFilter, /* 22: Signal */
  &f14tmp1_B.PitchRateLeadFilter,      /* 23: Signal */
  &f14tmp1_B.Proportionalplusintegralcompens,/* 24: Signal */
  &f14tmp1_B.StickPrefilter,           /* 25: Signal */
  &f14tmp1_B.Qgustmodel,               /* 26: Signal */
  &f14tmp1_B.Wgustmodel,               /* 27: Signal */
  &f14tmp1_B.Derivative,               /* 28: Signal */
  &f14tmp1_B.Derivative1,              /* 29: Signal */
  &f14tmp1_B.Gain1,                    /* 30: Signal */
  &f14tmp1_B.Gain2,                    /* 31: Signal */
  &f14tmp1_B.Product,                  /* 32: Signal */
  &f14tmp1_B.Sum1,                     /* 33: Signal */
  &f14tmp1_B.Output,                   /* 34: Signal */
  &f14tmp1_B.WhiteNoise,               /* 35: Signal */
  &f14tmp1_P.Gain_Gain,                /* 36: Block Parameter */
  &f14tmp1_P.Gain1_Gain_h,             /* 37: Block Parameter */
  &f14tmp1_P.Gain2_Gain_p,             /* 38: Block Parameter */
  &f14tmp1_P.Gain5_Gain,               /* 39: Block Parameter */
  &f14tmp1_P.Pilot_Amplitude,          /* 40: Block Parameter */
  &f14tmp1_P.Pilot_Frequency,          /* 41: Block Parameter */
  &f14tmp1_P.ActuatorModel_A,          /* 42: Block Parameter */
  &f14tmp1_P.ActuatorModel_C,          /* 43: Block Parameter */
  &f14tmp1_P.Gain3_Gain,               /* 44: Block Parameter */
  &f14tmp1_P.Gain4_Gain,               /* 45: Block Parameter */
  &f14tmp1_P.Gain5_Gain_j,             /* 46: Block Parameter */
  &f14tmp1_P.Gain6_Gain,               /* 47: Block Parameter */
  &f14tmp1_P.TransferFcn1_A,           /* 48: Block Parameter */
  &f14tmp1_P.TransferFcn1_C,           /* 49: Block Parameter */
  &f14tmp1_P.TransferFcn2_A,           /* 50: Block Parameter */
  &f14tmp1_P.TransferFcn2_C,           /* 51: Block Parameter */
  &f14tmp1_P.Gain_Gain_k,              /* 52: Block Parameter */
  &f14tmp1_P.Gain2_Gain_k,             /* 53: Block Parameter */
  &f14tmp1_P.Gain3_Gain_i,             /* 54: Block Parameter */
  &f14tmp1_P.AlphasensorLowpassFilter_A,/* 55: Block Parameter */
  &f14tmp1_P.AlphasensorLowpassFilter_C,/* 56: Block Parameter */
  &f14tmp1_P.PitchRateLeadFilter_A,    /* 57: Block Parameter */
  &f14tmp1_P.PitchRateLeadFilter_C,    /* 58: Block Parameter */
  &f14tmp1_P.PitchRateLeadFilter_D,    /* 59: Block Parameter */
  &f14tmp1_P.Proportionalplusintegralcompens,/* 60: Block Parameter */
  &f14tmp1_P.Proportionalplusintegralcompe_i,/* 61: Block Parameter */
  &f14tmp1_P.StickPrefilter_A,         /* 62: Block Parameter */
  &f14tmp1_P.StickPrefilter_C,         /* 63: Block Parameter */
  &f14tmp1_P.Qgustmodel_A,             /* 64: Block Parameter */
  &f14tmp1_P.Qgustmodel_C,             /* 65: Block Parameter */
  &f14tmp1_P.Qgustmodel_D,             /* 66: Block Parameter */
  &f14tmp1_P.Wgustmodel_A[0],          /* 67: Block Parameter */
  &f14tmp1_P.Wgustmodel_C[0],          /* 68: Block Parameter */
  &f14tmp1_P.Constant_Value,           /* 69: Block Parameter */
  &f14tmp1_P.Gain1_Gain,               /* 70: Block Parameter */
  &f14tmp1_P.Gain2_Gain,               /* 71: Block Parameter */
  &f14tmp1_P.Output_Gain,              /* 72: Block Parameter */
  &f14tmp1_P.WhiteNoise_Mean,          /* 73: Block Parameter */
  &f14tmp1_P.WhiteNoise_StdDev,        /* 74: Block Parameter */
  &f14tmp1_P.WhiteNoise_Seed           /* 75: Block Parameter */
};

/* Declare Data Run-Time Dimension Buffer Addresses statically */
static int32_T* rtVarDimsAddrMap[] = {
  (NULL)
};

/* Data Type Map - use dataTypeMapIndex to access this structure */
static const rtwCAPI_DataTypeMap rtDataTypeMap[] = {
  /* cName, mwName, numElements, elemMapIndex, dataSize, slDataId, *
   * isComplex, isPointer */
  { "double", "real_T", 0, 0, sizeof(real_T), SS_DOUBLE, 0, 0 }
};

/* Structure Element Map - use elemMapIndex to access this structure */
static const rtwCAPI_ElementMap rtElementMap[] = {
  /* elementName, elementOffset, dataTypeIndex, dimIndex, fxpIndex */
  { NULL, 0, 0, 0, 0 },
};

/* Dimension Map - use dimensionMapIndex to access elements of ths structure*/
static const rtwCAPI_DimensionMap rtDimensionMap[] = {
  /* dataOrientation, dimArrayIndex, numDims, vardimsIndex */
  { rtwCAPI_SCALAR, 0, 2, 0 },

  { rtwCAPI_VECTOR, 2, 2, 0 },

  { rtwCAPI_VECTOR, 4, 2, 0 }
};

/* Dimension Array- use dimArrayIndex to access elements of this array */
static const uint_T rtDimensionArray[] = {
  1,                                   /* 0 */
  1,                                   /* 1 */
  2,                                   /* 2 */
  1,                                   /* 3 */
  1,                                   /* 4 */
  2                                    /* 5 */
};

/* C-API stores floating point values in an array. The elements of this  *
 * are unique. This ensures that values which are shared across the model*
 * are stored in the most efficient way. These values are referenced by  *
 *           - rtwCAPI_FixPtMap.fracSlopePtr,                            *
 *           - rtwCAPI_FixPtMap.biasPtr,                                 *
 *           - rtwCAPI_SampleTimeMap.samplePeriodPtr,                    *
 *           - rtwCAPI_SampleTimeMap.sampleOffsetPtr                     */
static const real_T rtcapiStoredFloats[] = {
  0.0, 0.1
};

/* Fixed Point Map */
static const rtwCAPI_FixPtMap rtFixPtMap[] = {
  /* fracSlopePtr, biasPtr, scaleType, wordLength, exponent, isSigned */
  { NULL, NULL, rtwCAPI_FIX_RESERVED, 0, 0, 0 },
};

/* Sample Time Map - use sTimeIndex to access elements of ths structure */
static const rtwCAPI_SampleTimeMap rtSampleTimeMap[] = {
  /* samplePeriodPtr, sampleOffsetPtr, tid, samplingMode */
  { (const void *) &rtcapiStoredFloats[0], (const void *) &rtcapiStoredFloats[0],
    0, 0 },

  { (const void *) &rtcapiStoredFloats[1], (const void *) &rtcapiStoredFloats[0],
    2, 0 }
};

static rtwCAPI_ModelMappingStaticInfo mmiStatic = {
  /* Signals:{signals, numSignals},
   * Params: {blockParameters, numBlockParameters,
   *          modelParameters, numModelParameters},
   * States: {states, numStates},
   * Maps:   {dataTypeMap, dimensionMap, fixPtMap,
   *          elementMap, sampleTimeMap, dimensionArray},
   * TargetType: targetType
   */
  { rtBlockSignals, 36 },

  { rtBlockParameters, 40,
    rtModelParameters, 0 },

  { NULL, 0 },

  { rtDataTypeMap, rtDimensionMap, rtFixPtMap,
    rtElementMap, rtSampleTimeMap, rtDimensionArray },
  "float", NULL
};

/* Cache pointers into DataMapInfo substructure of RTModel */
void f14tmp1_InitializeDataMapInfo(rtModel_f14tmp1 *f14tmp1_rtM
  )
{
  /* Set C-API version */
  rtwCAPI_SetVersion(f14tmp1_rtM->DataMapInfo.mmi, 1);

  /* Cache static C-API data into the Real-time Model Data structure */
  rtwCAPI_SetStaticMap(f14tmp1_rtM->DataMapInfo.mmi, &mmiStatic);

  /* Cache static C-API logging data into the Real-time Model Data structure */
  rtwCAPI_SetLoggingStaticMap(f14tmp1_rtM->DataMapInfo.mmi, NULL);

  /* Cache C-API Data Addresses into the Real-Time Model Data structure */
  rtwCAPI_SetDataAddressMap(f14tmp1_rtM->DataMapInfo.mmi, rtDataAddrMap);

  /* Cache C-API Data Run-Time Dimension Buffer Addresses into the Real-Time Model Data structure */
  rtwCAPI_SetVarDimsAddressMap(f14tmp1_rtM->DataMapInfo.mmi, rtVarDimsAddrMap);

  /* Cache the instance C-API logging pointer */
  rtwCAPI_SetInstanceLoggingInfo(f14tmp1_rtM->DataMapInfo.mmi, NULL);

  /* Set Reference to submodels */
  rtwCAPI_SetChildMMIArray(f14tmp1_rtM->DataMapInfo.mmi, NULL);
  rtwCAPI_SetChildMMIArrayLen(f14tmp1_rtM->DataMapInfo.mmi, 0);
}

/* EOF: f14tmp1_capi.c */
