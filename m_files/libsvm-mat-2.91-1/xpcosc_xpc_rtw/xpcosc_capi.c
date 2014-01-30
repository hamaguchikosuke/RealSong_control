/*
 * xpcosc_capi.c
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

#include "xpcosc.h"
#include "rtw_capi.h"
#include "xpcosc_private.h"

/* Block output signal information */
static const rtwCAPI_Signals rtBlockSignals[] = {
  /* addrMapIndex, sysNum, blockPath,
   * signalName, portNumber, dataTypeIndex, dimIndex, fxpIndex, sTimeIndex
   */
  { 0, 0, "Gain",
    "", 0, 0, 0, 0, 0 },

  { 1, 0, "Gain1",
    "", 0, 0, 0, 0, 0 },

  { 2, 0, "Gain2",
    "", 0, 0, 0, 0, 0 },

  { 3, 0, "Integrator",
    "", 0, 0, 0, 0, 0 },

  { 4, 0, "Integrator1",
    "", 0, 0, 0, 0, 0 },

  { 5, 0, "Signal Generator",
    "", 0, 0, 0, 0, 0 },

  { 6, 0, "Sum",
    "", 0, 0, 0, 0, 0 },

  {
    0, 0, NULL, NULL, 0, 0, 0, 0, 0
  }
};

/* Tunable block parameters */
static const rtwCAPI_BlockParameters rtBlockParameters[] = {
  /* addrMapIndex, blockPath,
   * paramName, dataTypeIndex, dimIndex, fixPtIdx
   */
  { 7, "Gain",
    "Gain", 0, 0, 0 },

  { 8, "Gain1",
    "Gain", 0, 0, 0 },

  { 9, "Gain2",
    "Gain", 0, 0, 0 },

  { 10, "Integrator",
    "InitialCondition", 0, 0, 0 },

  { 11, "Integrator1",
    "InitialCondition", 0, 0, 0 },

  { 12, "Signal Generator",
    "Amplitude", 0, 0, 0 },

  { 13, "Signal Generator",
    "Frequency", 0, 0, 0 },

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
  &xpcosc_B.Gain,                      /* 0: Signal */
  &xpcosc_B.Gain1,                     /* 1: Signal */
  &xpcosc_B.Gain2,                     /* 2: Signal */
  &xpcosc_B.Integrator,                /* 3: Signal */
  &xpcosc_B.Integrator1,               /* 4: Signal */
  &xpcosc_B.SignalGenerator,           /* 5: Signal */
  &xpcosc_B.Sum,                       /* 6: Signal */
  &xpcosc_P.Gain_Gain,                 /* 7: Block Parameter */
  &xpcosc_P.Gain1_Gain,                /* 8: Block Parameter */
  &xpcosc_P.Gain2_Gain,                /* 9: Block Parameter */
  &xpcosc_P.Integrator_IC,             /* 10: Block Parameter */
  &xpcosc_P.Integrator1_IC,            /* 11: Block Parameter */
  &xpcosc_P.SignalGenerator_Amplitude, /* 12: Block Parameter */
  &xpcosc_P.SignalGenerator_Frequency  /* 13: Block Parameter */
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
  { rtwCAPI_SCALAR, 0, 2, 0 }
};

/* Dimension Array- use dimArrayIndex to access elements of this array */
static const uint_T rtDimensionArray[] = {
  1,                                   /* 0 */
  1                                    /* 1 */
};

/* C-API stores floating point values in an array. The elements of this  *
 * are unique. This ensures that values which are shared across the model*
 * are stored in the most efficient way. These values are referenced by  *
 *           - rtwCAPI_FixPtMap.fracSlopePtr,                            *
 *           - rtwCAPI_FixPtMap.biasPtr,                                 *
 *           - rtwCAPI_SampleTimeMap.samplePeriodPtr,                    *
 *           - rtwCAPI_SampleTimeMap.sampleOffsetPtr                     */
static const real_T rtcapiStoredFloats[] = {
  0.0
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
    0, 0 }
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
  { rtBlockSignals, 7 },

  { rtBlockParameters, 7,
    rtModelParameters, 0 },

  { NULL, 0 },

  { rtDataTypeMap, rtDimensionMap, rtFixPtMap,
    rtElementMap, rtSampleTimeMap, rtDimensionArray },
  "float", NULL
};

/* Cache pointers into DataMapInfo substructure of RTModel */
void xpcosc_InitializeDataMapInfo(rtModel_xpcosc *xpcosc_rtM
  )
{
  /* Set C-API version */
  rtwCAPI_SetVersion(xpcosc_rtM->DataMapInfo.mmi, 1);

  /* Cache static C-API data into the Real-time Model Data structure */
  rtwCAPI_SetStaticMap(xpcosc_rtM->DataMapInfo.mmi, &mmiStatic);

  /* Cache static C-API logging data into the Real-time Model Data structure */
  rtwCAPI_SetLoggingStaticMap(xpcosc_rtM->DataMapInfo.mmi, NULL);

  /* Cache C-API Data Addresses into the Real-Time Model Data structure */
  rtwCAPI_SetDataAddressMap(xpcosc_rtM->DataMapInfo.mmi, rtDataAddrMap);

  /* Cache C-API Data Run-Time Dimension Buffer Addresses into the Real-Time Model Data structure */
  rtwCAPI_SetVarDimsAddressMap(xpcosc_rtM->DataMapInfo.mmi, rtVarDimsAddrMap);

  /* Cache the instance C-API logging pointer */
  rtwCAPI_SetInstanceLoggingInfo(xpcosc_rtM->DataMapInfo.mmi, NULL);

  /* Set Reference to submodels */
  rtwCAPI_SetChildMMIArray(xpcosc_rtM->DataMapInfo.mmi, NULL);
  rtwCAPI_SetChildMMIArrayLen(xpcosc_rtM->DataMapInfo.mmi, 0);
}

/* EOF: xpcosc_capi.c */
