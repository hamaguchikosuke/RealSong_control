/*
 * f14tmp5_capi.c
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
#include "rtw_capi.h"
#include "f14tmp5_private.h"

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

  { 8, 0, "Subsystem1/Gain",
    "", 0, 0, 0, 0, 0 },

  { 9, 0, "Subsystem1/Gain1",
    "", 0, 0, 0, 0, 0 },

  { 10, 0, "Subsystem1/Gain2",
    "", 0, 0, 0, 0, 0 },

  { 11, 0, "Subsystem1/Gain5",
    "", 0, 0, 0, 0, 0 },

  { 12, 0, "Subsystem1/Pilot",
    "", 0, 0, 0, 0, 0 },

  { 13, 0, "Subsystem1/Sum",
    "", 0, 0, 0, 0, 0 },

  { 14, 0, "Subsystem1/Sum1",
    "", 0, 0, 0, 0, 0 },

  { 15, 0, "Subsystem1/Actuator Model",
    "", 0, 0, 0, 0, 0 },

  { 16, 0, "Subsystem2/Gain",
    "", 0, 0, 0, 0, 0 },

  { 17, 0, "Subsystem2/Gain1",
    "", 0, 0, 0, 0, 0 },

  { 18, 0, "Subsystem2/Gain2",
    "", 0, 0, 0, 0, 0 },

  { 19, 0, "Subsystem2/Gain5",
    "", 0, 0, 0, 0, 0 },

  { 20, 0, "Subsystem2/Pilot",
    "", 0, 0, 0, 0, 0 },

  { 21, 0, "Subsystem2/Sum",
    "", 0, 0, 0, 0, 0 },

  { 22, 0, "Subsystem2/Sum1",
    "", 0, 0, 0, 0, 0 },

  { 23, 0, "Subsystem2/Actuator Model",
    "", 0, 0, 0, 0, 0 },

  { 24, 0, "Subsystem3/Gain",
    "", 0, 0, 0, 0, 0 },

  { 25, 0, "Subsystem3/Gain1",
    "", 0, 0, 0, 0, 0 },

  { 26, 0, "Subsystem3/Gain2",
    "", 0, 0, 0, 0, 0 },

  { 27, 0, "Subsystem3/Gain5",
    "", 0, 0, 0, 0, 0 },

  { 28, 0, "Subsystem3/Pilot",
    "", 0, 0, 0, 0, 0 },

  { 29, 0, "Subsystem3/Sum",
    "", 0, 0, 0, 0, 0 },

  { 30, 0, "Subsystem3/Sum1",
    "", 0, 0, 0, 0, 0 },

  { 31, 0, "Subsystem3/Actuator Model",
    "", 0, 0, 0, 0, 0 },

  { 32, 0, "Subsystem4/Gain",
    "", 0, 0, 0, 0, 0 },

  { 33, 0, "Subsystem4/Gain1",
    "", 0, 0, 0, 0, 0 },

  { 34, 0, "Subsystem4/Gain2",
    "", 0, 0, 0, 0, 0 },

  { 35, 0, "Subsystem4/Gain5",
    "", 0, 0, 0, 0, 0 },

  { 36, 0, "Subsystem4/Pilot",
    "", 0, 0, 0, 0, 0 },

  { 37, 0, "Subsystem4/Sum",
    "", 0, 0, 0, 0, 0 },

  { 38, 0, "Subsystem4/Sum1",
    "", 0, 0, 0, 0, 0 },

  { 39, 0, "Subsystem4/Actuator Model",
    "", 0, 0, 0, 0, 0 },

  { 40, 0, "Subsystem/Aircraft Dynamics Model/Gain3",
    "", 0, 0, 0, 0, 0 },

  { 41, 0, "Subsystem/Aircraft Dynamics Model/Gain4",
    "", 0, 0, 0, 0, 0 },

  { 42, 0, "Subsystem/Aircraft Dynamics Model/Gain5",
    "", 0, 0, 0, 0, 0 },

  { 43, 0, "Subsystem/Aircraft Dynamics Model/Gain6",
    "", 0, 0, 0, 0, 0 },

  { 44, 0, "Subsystem/Aircraft Dynamics Model/Sum1",
    "", 0, 0, 0, 0, 0 },

  { 45, 0, "Subsystem/Aircraft Dynamics Model/Sum2",
    "", 0, 0, 0, 0, 0 },

  { 46, 0, "Subsystem/Aircraft Dynamics Model/Transfer Fcn.1",
    "", 0, 0, 0, 0, 0 },

  { 47, 0, "Subsystem/Aircraft Dynamics Model/Transfer Fcn.2",
    "", 0, 0, 0, 0, 0 },

  { 48, 0, "Subsystem/Controller/Gain",
    "", 0, 0, 0, 0, 0 },

  { 49, 0, "Subsystem/Controller/Gain2",
    "", 0, 0, 0, 0, 0 },

  { 50, 0, "Subsystem/Controller/Gain3",
    "", 0, 0, 0, 0, 0 },

  { 51, 0, "Subsystem/Controller/Sum",
    "", 0, 0, 0, 0, 0 },

  { 52, 0, "Subsystem/Controller/Sum1",
    "", 0, 0, 0, 0, 0 },

  { 53, 0, "Subsystem/Controller/Sum2",
    "", 0, 0, 0, 0, 0 },

  { 54, 0, "Subsystem/Controller/Alpha-sensor Low-pass Filter",
    "", 0, 0, 0, 0, 0 },

  { 55, 0, "Subsystem/Controller/Pitch Rate Lead Filter",
    "", 0, 0, 0, 0, 0 },

  { 56, 0, "Subsystem/Controller/Proportional plus integral compensator",
    "", 0, 0, 0, 0, 0 },

  { 57, 0, "Subsystem/Controller/Stick Prefilter",
    "", 0, 0, 0, 0, 0 },

  { 58, 0, "Subsystem/Dryden Wind Gust Models/Q-gust model",
    "", 0, 0, 0, 0, 0 },

  { 59, 0, "Subsystem/Dryden Wind Gust Models/W-gust model",
    "", 0, 0, 0, 0, 0 },

  { 60, 0, "Subsystem/Nz pilot calculation/Derivative",
    "", 0, 0, 0, 0, 0 },

  { 61, 0, "Subsystem/Nz pilot calculation/Derivative1",
    "", 0, 0, 0, 0, 0 },

  { 62, 0, "Subsystem/Nz pilot calculation/Gain1",
    "", 0, 0, 0, 0, 0 },

  { 63, 0, "Subsystem/Nz pilot calculation/Gain2",
    "", 0, 0, 0, 0, 0 },

  { 64, 0, "Subsystem/Nz pilot calculation/Product",
    "", 0, 0, 0, 0, 0 },

  { 65, 0, "Subsystem/Nz pilot calculation/Sum1",
    "", 0, 0, 0, 0, 0 },

  { 66, 0, "Subsystem1/Aircraft Dynamics Model/Gain3",
    "", 0, 0, 0, 0, 0 },

  { 67, 0, "Subsystem1/Aircraft Dynamics Model/Gain4",
    "", 0, 0, 0, 0, 0 },

  { 68, 0, "Subsystem1/Aircraft Dynamics Model/Gain5",
    "", 0, 0, 0, 0, 0 },

  { 69, 0, "Subsystem1/Aircraft Dynamics Model/Gain6",
    "", 0, 0, 0, 0, 0 },

  { 70, 0, "Subsystem1/Aircraft Dynamics Model/Sum1",
    "", 0, 0, 0, 0, 0 },

  { 71, 0, "Subsystem1/Aircraft Dynamics Model/Sum2",
    "", 0, 0, 0, 0, 0 },

  { 72, 0, "Subsystem1/Aircraft Dynamics Model/Transfer Fcn.1",
    "", 0, 0, 0, 0, 0 },

  { 73, 0, "Subsystem1/Aircraft Dynamics Model/Transfer Fcn.2",
    "", 0, 0, 0, 0, 0 },

  { 74, 0, "Subsystem1/Controller/Gain",
    "", 0, 0, 0, 0, 0 },

  { 75, 0, "Subsystem1/Controller/Gain2",
    "", 0, 0, 0, 0, 0 },

  { 76, 0, "Subsystem1/Controller/Gain3",
    "", 0, 0, 0, 0, 0 },

  { 77, 0, "Subsystem1/Controller/Sum",
    "", 0, 0, 0, 0, 0 },

  { 78, 0, "Subsystem1/Controller/Sum1",
    "", 0, 0, 0, 0, 0 },

  { 79, 0, "Subsystem1/Controller/Sum2",
    "", 0, 0, 0, 0, 0 },

  { 80, 0, "Subsystem1/Controller/Alpha-sensor Low-pass Filter",
    "", 0, 0, 0, 0, 0 },

  { 81, 0, "Subsystem1/Controller/Pitch Rate Lead Filter",
    "", 0, 0, 0, 0, 0 },

  { 82, 0, "Subsystem1/Controller/Proportional plus integral compensator",
    "", 0, 0, 0, 0, 0 },

  { 83, 0, "Subsystem1/Controller/Stick Prefilter",
    "", 0, 0, 0, 0, 0 },

  { 84, 0, "Subsystem1/Dryden Wind Gust Models/Q-gust model",
    "", 0, 0, 0, 0, 0 },

  { 85, 0, "Subsystem1/Dryden Wind Gust Models/W-gust model",
    "", 0, 0, 0, 0, 0 },

  { 86, 0, "Subsystem1/Nz pilot calculation/Derivative",
    "", 0, 0, 0, 0, 0 },

  { 87, 0, "Subsystem1/Nz pilot calculation/Derivative1",
    "", 0, 0, 0, 0, 0 },

  { 88, 0, "Subsystem1/Nz pilot calculation/Gain1",
    "", 0, 0, 0, 0, 0 },

  { 89, 0, "Subsystem1/Nz pilot calculation/Gain2",
    "", 0, 0, 0, 0, 0 },

  { 90, 0, "Subsystem1/Nz pilot calculation/Product",
    "", 0, 0, 0, 0, 0 },

  { 91, 0, "Subsystem1/Nz pilot calculation/Sum1",
    "", 0, 0, 0, 0, 0 },

  { 92, 0, "Subsystem2/Aircraft Dynamics Model/Gain3",
    "", 0, 0, 0, 0, 0 },

  { 93, 0, "Subsystem2/Aircraft Dynamics Model/Gain4",
    "", 0, 0, 0, 0, 0 },

  { 94, 0, "Subsystem2/Aircraft Dynamics Model/Gain5",
    "", 0, 0, 0, 0, 0 },

  { 95, 0, "Subsystem2/Aircraft Dynamics Model/Gain6",
    "", 0, 0, 0, 0, 0 },

  { 96, 0, "Subsystem2/Aircraft Dynamics Model/Sum1",
    "", 0, 0, 0, 0, 0 },

  { 97, 0, "Subsystem2/Aircraft Dynamics Model/Sum2",
    "", 0, 0, 0, 0, 0 },

  { 98, 0, "Subsystem2/Aircraft Dynamics Model/Transfer Fcn.1",
    "", 0, 0, 0, 0, 0 },

  { 99, 0, "Subsystem2/Aircraft Dynamics Model/Transfer Fcn.2",
    "", 0, 0, 0, 0, 0 },

  { 100, 0, "Subsystem2/Controller/Gain",
    "", 0, 0, 0, 0, 0 },

  { 101, 0, "Subsystem2/Controller/Gain2",
    "", 0, 0, 0, 0, 0 },

  { 102, 0, "Subsystem2/Controller/Gain3",
    "", 0, 0, 0, 0, 0 },

  { 103, 0, "Subsystem2/Controller/Sum",
    "", 0, 0, 0, 0, 0 },

  { 104, 0, "Subsystem2/Controller/Sum1",
    "", 0, 0, 0, 0, 0 },

  { 105, 0, "Subsystem2/Controller/Sum2",
    "", 0, 0, 0, 0, 0 },

  { 106, 0, "Subsystem2/Controller/Alpha-sensor Low-pass Filter",
    "", 0, 0, 0, 0, 0 },

  { 107, 0, "Subsystem2/Controller/Pitch Rate Lead Filter",
    "", 0, 0, 0, 0, 0 },

  { 108, 0, "Subsystem2/Controller/Proportional plus integral compensator",
    "", 0, 0, 0, 0, 0 },

  { 109, 0, "Subsystem2/Controller/Stick Prefilter",
    "", 0, 0, 0, 0, 0 },

  { 110, 0, "Subsystem2/Dryden Wind Gust Models/Q-gust model",
    "", 0, 0, 0, 0, 0 },

  { 111, 0, "Subsystem2/Dryden Wind Gust Models/W-gust model",
    "", 0, 0, 0, 0, 0 },

  { 112, 0, "Subsystem2/Nz pilot calculation/Derivative",
    "", 0, 0, 0, 0, 0 },

  { 113, 0, "Subsystem2/Nz pilot calculation/Derivative1",
    "", 0, 0, 0, 0, 0 },

  { 114, 0, "Subsystem2/Nz pilot calculation/Gain1",
    "", 0, 0, 0, 0, 0 },

  { 115, 0, "Subsystem2/Nz pilot calculation/Gain2",
    "", 0, 0, 0, 0, 0 },

  { 116, 0, "Subsystem2/Nz pilot calculation/Product",
    "", 0, 0, 0, 0, 0 },

  { 117, 0, "Subsystem2/Nz pilot calculation/Sum1",
    "", 0, 0, 0, 0, 0 },

  { 118, 0, "Subsystem3/Aircraft Dynamics Model/Gain3",
    "", 0, 0, 0, 0, 0 },

  { 119, 0, "Subsystem3/Aircraft Dynamics Model/Gain4",
    "", 0, 0, 0, 0, 0 },

  { 120, 0, "Subsystem3/Aircraft Dynamics Model/Gain5",
    "", 0, 0, 0, 0, 0 },

  { 121, 0, "Subsystem3/Aircraft Dynamics Model/Gain6",
    "", 0, 0, 0, 0, 0 },

  { 122, 0, "Subsystem3/Aircraft Dynamics Model/Sum1",
    "", 0, 0, 0, 0, 0 },

  { 123, 0, "Subsystem3/Aircraft Dynamics Model/Sum2",
    "", 0, 0, 0, 0, 0 },

  { 124, 0, "Subsystem3/Aircraft Dynamics Model/Transfer Fcn.1",
    "", 0, 0, 0, 0, 0 },

  { 125, 0, "Subsystem3/Aircraft Dynamics Model/Transfer Fcn.2",
    "", 0, 0, 0, 0, 0 },

  { 126, 0, "Subsystem3/Controller/Gain",
    "", 0, 0, 0, 0, 0 },

  { 127, 0, "Subsystem3/Controller/Gain2",
    "", 0, 0, 0, 0, 0 },

  { 128, 0, "Subsystem3/Controller/Gain3",
    "", 0, 0, 0, 0, 0 },

  { 129, 0, "Subsystem3/Controller/Sum",
    "", 0, 0, 0, 0, 0 },

  { 130, 0, "Subsystem3/Controller/Sum1",
    "", 0, 0, 0, 0, 0 },

  { 131, 0, "Subsystem3/Controller/Sum2",
    "", 0, 0, 0, 0, 0 },

  { 132, 0, "Subsystem3/Controller/Alpha-sensor Low-pass Filter",
    "", 0, 0, 0, 0, 0 },

  { 133, 0, "Subsystem3/Controller/Pitch Rate Lead Filter",
    "", 0, 0, 0, 0, 0 },

  { 134, 0, "Subsystem3/Controller/Proportional plus integral compensator",
    "", 0, 0, 0, 0, 0 },

  { 135, 0, "Subsystem3/Controller/Stick Prefilter",
    "", 0, 0, 0, 0, 0 },

  { 136, 0, "Subsystem3/Dryden Wind Gust Models/Q-gust model",
    "", 0, 0, 0, 0, 0 },

  { 137, 0, "Subsystem3/Dryden Wind Gust Models/W-gust model",
    "", 0, 0, 0, 0, 0 },

  { 138, 0, "Subsystem3/Nz pilot calculation/Derivative",
    "", 0, 0, 0, 0, 0 },

  { 139, 0, "Subsystem3/Nz pilot calculation/Derivative1",
    "", 0, 0, 0, 0, 0 },

  { 140, 0, "Subsystem3/Nz pilot calculation/Gain1",
    "", 0, 0, 0, 0, 0 },

  { 141, 0, "Subsystem3/Nz pilot calculation/Gain2",
    "", 0, 0, 0, 0, 0 },

  { 142, 0, "Subsystem3/Nz pilot calculation/Product",
    "", 0, 0, 0, 0, 0 },

  { 143, 0, "Subsystem3/Nz pilot calculation/Sum1",
    "", 0, 0, 0, 0, 0 },

  { 144, 0, "Subsystem4/Aircraft Dynamics Model/Gain3",
    "", 0, 0, 0, 0, 0 },

  { 145, 0, "Subsystem4/Aircraft Dynamics Model/Gain4",
    "", 0, 0, 0, 0, 0 },

  { 146, 0, "Subsystem4/Aircraft Dynamics Model/Gain5",
    "", 0, 0, 0, 0, 0 },

  { 147, 0, "Subsystem4/Aircraft Dynamics Model/Gain6",
    "", 0, 0, 0, 0, 0 },

  { 148, 0, "Subsystem4/Aircraft Dynamics Model/Sum1",
    "", 0, 0, 0, 0, 0 },

  { 149, 0, "Subsystem4/Aircraft Dynamics Model/Sum2",
    "", 0, 0, 0, 0, 0 },

  { 150, 0, "Subsystem4/Aircraft Dynamics Model/Transfer Fcn.1",
    "", 0, 0, 0, 0, 0 },

  { 151, 0, "Subsystem4/Aircraft Dynamics Model/Transfer Fcn.2",
    "", 0, 0, 0, 0, 0 },

  { 152, 0, "Subsystem4/Controller/Gain",
    "", 0, 0, 0, 0, 0 },

  { 153, 0, "Subsystem4/Controller/Gain2",
    "", 0, 0, 0, 0, 0 },

  { 154, 0, "Subsystem4/Controller/Gain3",
    "", 0, 0, 0, 0, 0 },

  { 155, 0, "Subsystem4/Controller/Sum",
    "", 0, 0, 0, 0, 0 },

  { 156, 0, "Subsystem4/Controller/Sum1",
    "", 0, 0, 0, 0, 0 },

  { 157, 0, "Subsystem4/Controller/Sum2",
    "", 0, 0, 0, 0, 0 },

  { 158, 0, "Subsystem4/Controller/Alpha-sensor Low-pass Filter",
    "", 0, 0, 0, 0, 0 },

  { 159, 0, "Subsystem4/Controller/Pitch Rate Lead Filter",
    "", 0, 0, 0, 0, 0 },

  { 160, 0, "Subsystem4/Controller/Proportional plus integral compensator",
    "", 0, 0, 0, 0, 0 },

  { 161, 0, "Subsystem4/Controller/Stick Prefilter",
    "", 0, 0, 0, 0, 0 },

  { 162, 0, "Subsystem4/Dryden Wind Gust Models/Q-gust model",
    "", 0, 0, 0, 0, 0 },

  { 163, 0, "Subsystem4/Dryden Wind Gust Models/W-gust model",
    "", 0, 0, 0, 0, 0 },

  { 164, 0, "Subsystem4/Nz pilot calculation/Derivative",
    "", 0, 0, 0, 0, 0 },

  { 165, 0, "Subsystem4/Nz pilot calculation/Derivative1",
    "", 0, 0, 0, 0, 0 },

  { 166, 0, "Subsystem4/Nz pilot calculation/Gain1",
    "", 0, 0, 0, 0, 0 },

  { 167, 0, "Subsystem4/Nz pilot calculation/Gain2",
    "", 0, 0, 0, 0, 0 },

  { 168, 0, "Subsystem4/Nz pilot calculation/Product",
    "", 0, 0, 0, 0, 0 },

  { 169, 0, "Subsystem4/Nz pilot calculation/Sum1",
    "", 0, 0, 0, 0, 0 },

  { 170, 0, "Subsystem/Dryden Wind Gust Models/Band-Limited White Noise/Output",
    "", 0, 0, 0, 0, 1 },

  { 171, 0,
    "Subsystem/Dryden Wind Gust Models/Band-Limited White Noise/White Noise",
    "", 0, 0, 0, 0, 1 },

  { 172, 0, "Subsystem1/Dryden Wind Gust Models/Band-Limited White Noise/Output",
    "", 0, 0, 0, 0, 1 },

  { 173, 0,
    "Subsystem1/Dryden Wind Gust Models/Band-Limited White Noise/White Noise",
    "", 0, 0, 0, 0, 1 },

  { 174, 0, "Subsystem2/Dryden Wind Gust Models/Band-Limited White Noise/Output",
    "", 0, 0, 0, 0, 1 },

  { 175, 0,
    "Subsystem2/Dryden Wind Gust Models/Band-Limited White Noise/White Noise",
    "", 0, 0, 0, 0, 1 },

  { 176, 0, "Subsystem3/Dryden Wind Gust Models/Band-Limited White Noise/Output",
    "", 0, 0, 0, 0, 1 },

  { 177, 0,
    "Subsystem3/Dryden Wind Gust Models/Band-Limited White Noise/White Noise",
    "", 0, 0, 0, 0, 1 },

  { 178, 0, "Subsystem4/Dryden Wind Gust Models/Band-Limited White Noise/Output",
    "", 0, 0, 0, 0, 1 },

  { 179, 0,
    "Subsystem4/Dryden Wind Gust Models/Band-Limited White Noise/White Noise",
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
  { 180, "Subsystem/Gain",
    "Gain", 0, 0, 0 },

  { 181, "Subsystem/Gain1",
    "Gain", 0, 0, 0 },

  { 182, "Subsystem/Gain2",
    "Gain", 0, 0, 0 },

  { 183, "Subsystem/Gain5",
    "Gain", 0, 0, 0 },

  { 184, "Subsystem/Pilot",
    "Amplitude", 0, 0, 0 },

  { 185, "Subsystem/Pilot",
    "Frequency", 0, 0, 0 },

  { 186, "Subsystem/Actuator Model",
    "A", 0, 0, 0 },

  { 187, "Subsystem/Actuator Model",
    "C", 0, 0, 0 },

  { 188, "Subsystem1/Gain",
    "Gain", 0, 0, 0 },

  { 189, "Subsystem1/Gain1",
    "Gain", 0, 0, 0 },

  { 190, "Subsystem1/Gain2",
    "Gain", 0, 0, 0 },

  { 191, "Subsystem1/Gain5",
    "Gain", 0, 0, 0 },

  { 192, "Subsystem1/Pilot",
    "Amplitude", 0, 0, 0 },

  { 193, "Subsystem1/Pilot",
    "Frequency", 0, 0, 0 },

  { 194, "Subsystem1/Actuator Model",
    "A", 0, 0, 0 },

  { 195, "Subsystem1/Actuator Model",
    "C", 0, 0, 0 },

  { 196, "Subsystem2/Gain",
    "Gain", 0, 0, 0 },

  { 197, "Subsystem2/Gain1",
    "Gain", 0, 0, 0 },

  { 198, "Subsystem2/Gain2",
    "Gain", 0, 0, 0 },

  { 199, "Subsystem2/Gain5",
    "Gain", 0, 0, 0 },

  { 200, "Subsystem2/Pilot",
    "Amplitude", 0, 0, 0 },

  { 201, "Subsystem2/Pilot",
    "Frequency", 0, 0, 0 },

  { 202, "Subsystem2/Actuator Model",
    "A", 0, 0, 0 },

  { 203, "Subsystem2/Actuator Model",
    "C", 0, 0, 0 },

  { 204, "Subsystem3/Gain",
    "Gain", 0, 0, 0 },

  { 205, "Subsystem3/Gain1",
    "Gain", 0, 0, 0 },

  { 206, "Subsystem3/Gain2",
    "Gain", 0, 0, 0 },

  { 207, "Subsystem3/Gain5",
    "Gain", 0, 0, 0 },

  { 208, "Subsystem3/Pilot",
    "Amplitude", 0, 0, 0 },

  { 209, "Subsystem3/Pilot",
    "Frequency", 0, 0, 0 },

  { 210, "Subsystem3/Actuator Model",
    "A", 0, 0, 0 },

  { 211, "Subsystem3/Actuator Model",
    "C", 0, 0, 0 },

  { 212, "Subsystem4/Gain",
    "Gain", 0, 0, 0 },

  { 213, "Subsystem4/Gain1",
    "Gain", 0, 0, 0 },

  { 214, "Subsystem4/Gain2",
    "Gain", 0, 0, 0 },

  { 215, "Subsystem4/Gain5",
    "Gain", 0, 0, 0 },

  { 216, "Subsystem4/Pilot",
    "Amplitude", 0, 0, 0 },

  { 217, "Subsystem4/Pilot",
    "Frequency", 0, 0, 0 },

  { 218, "Subsystem4/Actuator Model",
    "A", 0, 0, 0 },

  { 219, "Subsystem4/Actuator Model",
    "C", 0, 0, 0 },

  { 220, "Subsystem/Aircraft Dynamics Model/Gain3",
    "Gain", 0, 0, 0 },

  { 221, "Subsystem/Aircraft Dynamics Model/Gain4",
    "Gain", 0, 0, 0 },

  { 222, "Subsystem/Aircraft Dynamics Model/Gain5",
    "Gain", 0, 0, 0 },

  { 223, "Subsystem/Aircraft Dynamics Model/Gain6",
    "Gain", 0, 0, 0 },

  { 224, "Subsystem/Aircraft Dynamics Model/Transfer Fcn.1",
    "A", 0, 0, 0 },

  { 225, "Subsystem/Aircraft Dynamics Model/Transfer Fcn.1",
    "C", 0, 0, 0 },

  { 226, "Subsystem/Aircraft Dynamics Model/Transfer Fcn.2",
    "A", 0, 0, 0 },

  { 227, "Subsystem/Aircraft Dynamics Model/Transfer Fcn.2",
    "C", 0, 0, 0 },

  { 228, "Subsystem/Controller/Gain",
    "Gain", 0, 0, 0 },

  { 229, "Subsystem/Controller/Gain2",
    "Gain", 0, 0, 0 },

  { 230, "Subsystem/Controller/Gain3",
    "Gain", 0, 0, 0 },

  { 231, "Subsystem/Controller/Alpha-sensor Low-pass Filter",
    "A", 0, 0, 0 },

  { 232, "Subsystem/Controller/Alpha-sensor Low-pass Filter",
    "C", 0, 0, 0 },

  { 233, "Subsystem/Controller/Pitch Rate Lead Filter",
    "A", 0, 0, 0 },

  { 234, "Subsystem/Controller/Pitch Rate Lead Filter",
    "C", 0, 0, 0 },

  { 235, "Subsystem/Controller/Pitch Rate Lead Filter",
    "D", 0, 0, 0 },

  { 236, "Subsystem/Controller/Proportional plus integral compensator",
    "A", 0, 0, 0 },

  { 237, "Subsystem/Controller/Proportional plus integral compensator",
    "C", 0, 0, 0 },

  { 238, "Subsystem/Controller/Stick Prefilter",
    "A", 0, 0, 0 },

  { 239, "Subsystem/Controller/Stick Prefilter",
    "C", 0, 0, 0 },

  { 240, "Subsystem/Dryden Wind Gust Models/Q-gust model",
    "A", 0, 0, 0 },

  { 241, "Subsystem/Dryden Wind Gust Models/Q-gust model",
    "C", 0, 0, 0 },

  { 242, "Subsystem/Dryden Wind Gust Models/Q-gust model",
    "D", 0, 0, 0 },

  { 243, "Subsystem/Dryden Wind Gust Models/W-gust model",
    "A", 0, 1, 0 },

  { 244, "Subsystem/Dryden Wind Gust Models/W-gust model",
    "C", 0, 2, 0 },

  { 245, "Subsystem/Nz pilot calculation/Constant",
    "Value", 0, 0, 0 },

  { 246, "Subsystem/Nz pilot calculation/Gain1",
    "Gain", 0, 0, 0 },

  { 247, "Subsystem/Nz pilot calculation/Gain2",
    "Gain", 0, 0, 0 },

  { 248, "Subsystem1/Aircraft Dynamics Model/Gain3",
    "Gain", 0, 0, 0 },

  { 249, "Subsystem1/Aircraft Dynamics Model/Gain4",
    "Gain", 0, 0, 0 },

  { 250, "Subsystem1/Aircraft Dynamics Model/Gain5",
    "Gain", 0, 0, 0 },

  { 251, "Subsystem1/Aircraft Dynamics Model/Gain6",
    "Gain", 0, 0, 0 },

  { 252, "Subsystem1/Aircraft Dynamics Model/Transfer Fcn.1",
    "A", 0, 0, 0 },

  { 253, "Subsystem1/Aircraft Dynamics Model/Transfer Fcn.1",
    "C", 0, 0, 0 },

  { 254, "Subsystem1/Aircraft Dynamics Model/Transfer Fcn.2",
    "A", 0, 0, 0 },

  { 255, "Subsystem1/Aircraft Dynamics Model/Transfer Fcn.2",
    "C", 0, 0, 0 },

  { 256, "Subsystem1/Controller/Gain",
    "Gain", 0, 0, 0 },

  { 257, "Subsystem1/Controller/Gain2",
    "Gain", 0, 0, 0 },

  { 258, "Subsystem1/Controller/Gain3",
    "Gain", 0, 0, 0 },

  { 259, "Subsystem1/Controller/Alpha-sensor Low-pass Filter",
    "A", 0, 0, 0 },

  { 260, "Subsystem1/Controller/Alpha-sensor Low-pass Filter",
    "C", 0, 0, 0 },

  { 261, "Subsystem1/Controller/Pitch Rate Lead Filter",
    "A", 0, 0, 0 },

  { 262, "Subsystem1/Controller/Pitch Rate Lead Filter",
    "C", 0, 0, 0 },

  { 263, "Subsystem1/Controller/Pitch Rate Lead Filter",
    "D", 0, 0, 0 },

  { 264, "Subsystem1/Controller/Proportional plus integral compensator",
    "A", 0, 0, 0 },

  { 265, "Subsystem1/Controller/Proportional plus integral compensator",
    "C", 0, 0, 0 },

  { 266, "Subsystem1/Controller/Stick Prefilter",
    "A", 0, 0, 0 },

  { 267, "Subsystem1/Controller/Stick Prefilter",
    "C", 0, 0, 0 },

  { 268, "Subsystem1/Dryden Wind Gust Models/Q-gust model",
    "A", 0, 0, 0 },

  { 269, "Subsystem1/Dryden Wind Gust Models/Q-gust model",
    "C", 0, 0, 0 },

  { 270, "Subsystem1/Dryden Wind Gust Models/Q-gust model",
    "D", 0, 0, 0 },

  { 271, "Subsystem1/Dryden Wind Gust Models/W-gust model",
    "A", 0, 1, 0 },

  { 272, "Subsystem1/Dryden Wind Gust Models/W-gust model",
    "C", 0, 2, 0 },

  { 273, "Subsystem1/Nz pilot calculation/Constant",
    "Value", 0, 0, 0 },

  { 274, "Subsystem1/Nz pilot calculation/Gain1",
    "Gain", 0, 0, 0 },

  { 275, "Subsystem1/Nz pilot calculation/Gain2",
    "Gain", 0, 0, 0 },

  { 276, "Subsystem2/Aircraft Dynamics Model/Gain3",
    "Gain", 0, 0, 0 },

  { 277, "Subsystem2/Aircraft Dynamics Model/Gain4",
    "Gain", 0, 0, 0 },

  { 278, "Subsystem2/Aircraft Dynamics Model/Gain5",
    "Gain", 0, 0, 0 },

  { 279, "Subsystem2/Aircraft Dynamics Model/Gain6",
    "Gain", 0, 0, 0 },

  { 280, "Subsystem2/Aircraft Dynamics Model/Transfer Fcn.1",
    "A", 0, 0, 0 },

  { 281, "Subsystem2/Aircraft Dynamics Model/Transfer Fcn.1",
    "C", 0, 0, 0 },

  { 282, "Subsystem2/Aircraft Dynamics Model/Transfer Fcn.2",
    "A", 0, 0, 0 },

  { 283, "Subsystem2/Aircraft Dynamics Model/Transfer Fcn.2",
    "C", 0, 0, 0 },

  { 284, "Subsystem2/Controller/Gain",
    "Gain", 0, 0, 0 },

  { 285, "Subsystem2/Controller/Gain2",
    "Gain", 0, 0, 0 },

  { 286, "Subsystem2/Controller/Gain3",
    "Gain", 0, 0, 0 },

  { 287, "Subsystem2/Controller/Alpha-sensor Low-pass Filter",
    "A", 0, 0, 0 },

  { 288, "Subsystem2/Controller/Alpha-sensor Low-pass Filter",
    "C", 0, 0, 0 },

  { 289, "Subsystem2/Controller/Pitch Rate Lead Filter",
    "A", 0, 0, 0 },

  { 290, "Subsystem2/Controller/Pitch Rate Lead Filter",
    "C", 0, 0, 0 },

  { 291, "Subsystem2/Controller/Pitch Rate Lead Filter",
    "D", 0, 0, 0 },

  { 292, "Subsystem2/Controller/Proportional plus integral compensator",
    "A", 0, 0, 0 },

  { 293, "Subsystem2/Controller/Proportional plus integral compensator",
    "C", 0, 0, 0 },

  { 294, "Subsystem2/Controller/Stick Prefilter",
    "A", 0, 0, 0 },

  { 295, "Subsystem2/Controller/Stick Prefilter",
    "C", 0, 0, 0 },

  { 296, "Subsystem2/Dryden Wind Gust Models/Q-gust model",
    "A", 0, 0, 0 },

  { 297, "Subsystem2/Dryden Wind Gust Models/Q-gust model",
    "C", 0, 0, 0 },

  { 298, "Subsystem2/Dryden Wind Gust Models/Q-gust model",
    "D", 0, 0, 0 },

  { 299, "Subsystem2/Dryden Wind Gust Models/W-gust model",
    "A", 0, 1, 0 },

  { 300, "Subsystem2/Dryden Wind Gust Models/W-gust model",
    "C", 0, 2, 0 },

  { 301, "Subsystem2/Nz pilot calculation/Constant",
    "Value", 0, 0, 0 },

  { 302, "Subsystem2/Nz pilot calculation/Gain1",
    "Gain", 0, 0, 0 },

  { 303, "Subsystem2/Nz pilot calculation/Gain2",
    "Gain", 0, 0, 0 },

  { 304, "Subsystem3/Aircraft Dynamics Model/Gain3",
    "Gain", 0, 0, 0 },

  { 305, "Subsystem3/Aircraft Dynamics Model/Gain4",
    "Gain", 0, 0, 0 },

  { 306, "Subsystem3/Aircraft Dynamics Model/Gain5",
    "Gain", 0, 0, 0 },

  { 307, "Subsystem3/Aircraft Dynamics Model/Gain6",
    "Gain", 0, 0, 0 },

  { 308, "Subsystem3/Aircraft Dynamics Model/Transfer Fcn.1",
    "A", 0, 0, 0 },

  { 309, "Subsystem3/Aircraft Dynamics Model/Transfer Fcn.1",
    "C", 0, 0, 0 },

  { 310, "Subsystem3/Aircraft Dynamics Model/Transfer Fcn.2",
    "A", 0, 0, 0 },

  { 311, "Subsystem3/Aircraft Dynamics Model/Transfer Fcn.2",
    "C", 0, 0, 0 },

  { 312, "Subsystem3/Controller/Gain",
    "Gain", 0, 0, 0 },

  { 313, "Subsystem3/Controller/Gain2",
    "Gain", 0, 0, 0 },

  { 314, "Subsystem3/Controller/Gain3",
    "Gain", 0, 0, 0 },

  { 315, "Subsystem3/Controller/Alpha-sensor Low-pass Filter",
    "A", 0, 0, 0 },

  { 316, "Subsystem3/Controller/Alpha-sensor Low-pass Filter",
    "C", 0, 0, 0 },

  { 317, "Subsystem3/Controller/Pitch Rate Lead Filter",
    "A", 0, 0, 0 },

  { 318, "Subsystem3/Controller/Pitch Rate Lead Filter",
    "C", 0, 0, 0 },

  { 319, "Subsystem3/Controller/Pitch Rate Lead Filter",
    "D", 0, 0, 0 },

  { 320, "Subsystem3/Controller/Proportional plus integral compensator",
    "A", 0, 0, 0 },

  { 321, "Subsystem3/Controller/Proportional plus integral compensator",
    "C", 0, 0, 0 },

  { 322, "Subsystem3/Controller/Stick Prefilter",
    "A", 0, 0, 0 },

  { 323, "Subsystem3/Controller/Stick Prefilter",
    "C", 0, 0, 0 },

  { 324, "Subsystem3/Dryden Wind Gust Models/Q-gust model",
    "A", 0, 0, 0 },

  { 325, "Subsystem3/Dryden Wind Gust Models/Q-gust model",
    "C", 0, 0, 0 },

  { 326, "Subsystem3/Dryden Wind Gust Models/Q-gust model",
    "D", 0, 0, 0 },

  { 327, "Subsystem3/Dryden Wind Gust Models/W-gust model",
    "A", 0, 1, 0 },

  { 328, "Subsystem3/Dryden Wind Gust Models/W-gust model",
    "C", 0, 2, 0 },

  { 329, "Subsystem3/Nz pilot calculation/Constant",
    "Value", 0, 0, 0 },

  { 330, "Subsystem3/Nz pilot calculation/Gain1",
    "Gain", 0, 0, 0 },

  { 331, "Subsystem3/Nz pilot calculation/Gain2",
    "Gain", 0, 0, 0 },

  { 332, "Subsystem4/Aircraft Dynamics Model/Gain3",
    "Gain", 0, 0, 0 },

  { 333, "Subsystem4/Aircraft Dynamics Model/Gain4",
    "Gain", 0, 0, 0 },

  { 334, "Subsystem4/Aircraft Dynamics Model/Gain5",
    "Gain", 0, 0, 0 },

  { 335, "Subsystem4/Aircraft Dynamics Model/Gain6",
    "Gain", 0, 0, 0 },

  { 336, "Subsystem4/Aircraft Dynamics Model/Transfer Fcn.1",
    "A", 0, 0, 0 },

  { 337, "Subsystem4/Aircraft Dynamics Model/Transfer Fcn.1",
    "C", 0, 0, 0 },

  { 338, "Subsystem4/Aircraft Dynamics Model/Transfer Fcn.2",
    "A", 0, 0, 0 },

  { 339, "Subsystem4/Aircraft Dynamics Model/Transfer Fcn.2",
    "C", 0, 0, 0 },

  { 340, "Subsystem4/Controller/Gain",
    "Gain", 0, 0, 0 },

  { 341, "Subsystem4/Controller/Gain2",
    "Gain", 0, 0, 0 },

  { 342, "Subsystem4/Controller/Gain3",
    "Gain", 0, 0, 0 },

  { 343, "Subsystem4/Controller/Alpha-sensor Low-pass Filter",
    "A", 0, 0, 0 },

  { 344, "Subsystem4/Controller/Alpha-sensor Low-pass Filter",
    "C", 0, 0, 0 },

  { 345, "Subsystem4/Controller/Pitch Rate Lead Filter",
    "A", 0, 0, 0 },

  { 346, "Subsystem4/Controller/Pitch Rate Lead Filter",
    "C", 0, 0, 0 },

  { 347, "Subsystem4/Controller/Pitch Rate Lead Filter",
    "D", 0, 0, 0 },

  { 348, "Subsystem4/Controller/Proportional plus integral compensator",
    "A", 0, 0, 0 },

  { 349, "Subsystem4/Controller/Proportional plus integral compensator",
    "C", 0, 0, 0 },

  { 350, "Subsystem4/Controller/Stick Prefilter",
    "A", 0, 0, 0 },

  { 351, "Subsystem4/Controller/Stick Prefilter",
    "C", 0, 0, 0 },

  { 352, "Subsystem4/Dryden Wind Gust Models/Q-gust model",
    "A", 0, 0, 0 },

  { 353, "Subsystem4/Dryden Wind Gust Models/Q-gust model",
    "C", 0, 0, 0 },

  { 354, "Subsystem4/Dryden Wind Gust Models/Q-gust model",
    "D", 0, 0, 0 },

  { 355, "Subsystem4/Dryden Wind Gust Models/W-gust model",
    "A", 0, 1, 0 },

  { 356, "Subsystem4/Dryden Wind Gust Models/W-gust model",
    "C", 0, 2, 0 },

  { 357, "Subsystem4/Nz pilot calculation/Constant",
    "Value", 0, 0, 0 },

  { 358, "Subsystem4/Nz pilot calculation/Gain1",
    "Gain", 0, 0, 0 },

  { 359, "Subsystem4/Nz pilot calculation/Gain2",
    "Gain", 0, 0, 0 },

  { 360, "Subsystem/Dryden Wind Gust Models/Band-Limited White Noise/Output",
    "Gain", 0, 0, 0 },

  { 361,
    "Subsystem/Dryden Wind Gust Models/Band-Limited White Noise/White Noise",
    "Mean", 0, 0, 0 },

  { 362,
    "Subsystem/Dryden Wind Gust Models/Band-Limited White Noise/White Noise",
    "StdDev", 0, 0, 0 },

  { 363,
    "Subsystem/Dryden Wind Gust Models/Band-Limited White Noise/White Noise",
    "Seed", 0, 0, 0 },

  { 364, "Subsystem1/Dryden Wind Gust Models/Band-Limited White Noise/Output",
    "Gain", 0, 0, 0 },

  { 365,
    "Subsystem1/Dryden Wind Gust Models/Band-Limited White Noise/White Noise",
    "Mean", 0, 0, 0 },

  { 366,
    "Subsystem1/Dryden Wind Gust Models/Band-Limited White Noise/White Noise",
    "StdDev", 0, 0, 0 },

  { 367,
    "Subsystem1/Dryden Wind Gust Models/Band-Limited White Noise/White Noise",
    "Seed", 0, 0, 0 },

  { 368, "Subsystem2/Dryden Wind Gust Models/Band-Limited White Noise/Output",
    "Gain", 0, 0, 0 },

  { 369,
    "Subsystem2/Dryden Wind Gust Models/Band-Limited White Noise/White Noise",
    "Mean", 0, 0, 0 },

  { 370,
    "Subsystem2/Dryden Wind Gust Models/Band-Limited White Noise/White Noise",
    "StdDev", 0, 0, 0 },

  { 371,
    "Subsystem2/Dryden Wind Gust Models/Band-Limited White Noise/White Noise",
    "Seed", 0, 0, 0 },

  { 372, "Subsystem3/Dryden Wind Gust Models/Band-Limited White Noise/Output",
    "Gain", 0, 0, 0 },

  { 373,
    "Subsystem3/Dryden Wind Gust Models/Band-Limited White Noise/White Noise",
    "Mean", 0, 0, 0 },

  { 374,
    "Subsystem3/Dryden Wind Gust Models/Band-Limited White Noise/White Noise",
    "StdDev", 0, 0, 0 },

  { 375,
    "Subsystem3/Dryden Wind Gust Models/Band-Limited White Noise/White Noise",
    "Seed", 0, 0, 0 },

  { 376, "Subsystem4/Dryden Wind Gust Models/Band-Limited White Noise/Output",
    "Gain", 0, 0, 0 },

  { 377,
    "Subsystem4/Dryden Wind Gust Models/Band-Limited White Noise/White Noise",
    "Mean", 0, 0, 0 },

  { 378,
    "Subsystem4/Dryden Wind Gust Models/Band-Limited White Noise/White Noise",
    "StdDev", 0, 0, 0 },

  { 379,
    "Subsystem4/Dryden Wind Gust Models/Band-Limited White Noise/White Noise",
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
  &f14tmp5_B.Gain,                     /* 0: Signal */
  &f14tmp5_B.Gain1_h,                  /* 1: Signal */
  &f14tmp5_B.Gain2_f,                  /* 2: Signal */
  &f14tmp5_B.Gain5,                    /* 3: Signal */
  &f14tmp5_B.Pilot,                    /* 4: Signal */
  &f14tmp5_B.Sum,                      /* 5: Signal */
  &f14tmp5_B.Sum1_k,                   /* 6: Signal */
  &f14tmp5_B.ActuatorModel,            /* 7: Signal */
  &f14tmp5_B.Gain_n,                   /* 8: Signal */
  &f14tmp5_B.Gain1_i,                  /* 9: Signal */
  &f14tmp5_B.Gain2_o,                  /* 10: Signal */
  &f14tmp5_B.Gain5_h,                  /* 11: Signal */
  &f14tmp5_B.Pilot_k,                  /* 12: Signal */
  &f14tmp5_B.Sum_e,                    /* 13: Signal */
  &f14tmp5_B.Sum1_n,                   /* 14: Signal */
  &f14tmp5_B.ActuatorModel_n,          /* 15: Signal */
  &f14tmp5_B.Gain_l,                   /* 16: Signal */
  &f14tmp5_B.Gain1_b,                  /* 17: Signal */
  &f14tmp5_B.Gain2_l0,                 /* 18: Signal */
  &f14tmp5_B.Gain5_p,                  /* 19: Signal */
  &f14tmp5_B.Pilot_h,                  /* 20: Signal */
  &f14tmp5_B.Sum_i,                    /* 21: Signal */
  &f14tmp5_B.Sum1_n0,                  /* 22: Signal */
  &f14tmp5_B.ActuatorModel_a,          /* 23: Signal */
  &f14tmp5_B.Gain_o,                   /* 24: Signal */
  &f14tmp5_B.Gain1_o,                  /* 25: Signal */
  &f14tmp5_B.Gain2_n,                  /* 26: Signal */
  &f14tmp5_B.Gain5_k,                  /* 27: Signal */
  &f14tmp5_B.Pilot_g,                  /* 28: Signal */
  &f14tmp5_B.Sum_en,                   /* 29: Signal */
  &f14tmp5_B.Sum1_dd,                  /* 30: Signal */
  &f14tmp5_B.ActuatorModel_m,          /* 31: Signal */
  &f14tmp5_B.Gain_hr,                  /* 32: Signal */
  &f14tmp5_B.Gain1_l,                  /* 33: Signal */
  &f14tmp5_B.Gain2_b,                  /* 34: Signal */
  &f14tmp5_B.Gain5_c,                  /* 35: Signal */
  &f14tmp5_B.Pilot_h3,                 /* 36: Signal */
  &f14tmp5_B.Sum_kh,                   /* 37: Signal */
  &f14tmp5_B.Sum1_h,                   /* 38: Signal */
  &f14tmp5_B.ActuatorModel_b,          /* 39: Signal */
  &f14tmp5_B.Gain3,                    /* 40: Signal */
  &f14tmp5_B.Gain4,                    /* 41: Signal */
  &f14tmp5_B.Gain5_b,                  /* 42: Signal */
  &f14tmp5_B.Gain6,                    /* 43: Signal */
  &f14tmp5_B.Sum1_o,                   /* 44: Signal */
  &f14tmp5_B.Sum2,                     /* 45: Signal */
  &f14tmp5_B.TransferFcn1,             /* 46: Signal */
  &f14tmp5_B.TransferFcn2,             /* 47: Signal */
  &f14tmp5_B.Gain_d,                   /* 48: Signal */
  &f14tmp5_B.Gain2_e,                  /* 49: Signal */
  &f14tmp5_B.Gain3_g,                  /* 50: Signal */
  &f14tmp5_B.Sum_n,                    /* 51: Signal */
  &f14tmp5_B.Sum1_d,                   /* 52: Signal */
  &f14tmp5_B.Sum2_f,                   /* 53: Signal */
  &f14tmp5_B.AlphasensorLowpassFilter, /* 54: Signal */
  &f14tmp5_B.PitchRateLeadFilter,      /* 55: Signal */
  &f14tmp5_B.Proportionalplusintegralcompens,/* 56: Signal */
  &f14tmp5_B.StickPrefilter,           /* 57: Signal */
  &f14tmp5_B.Qgustmodel,               /* 58: Signal */
  &f14tmp5_B.Wgustmodel,               /* 59: Signal */
  &f14tmp5_B.Derivative,               /* 60: Signal */
  &f14tmp5_B.Derivative1,              /* 61: Signal */
  &f14tmp5_B.Gain1,                    /* 62: Signal */
  &f14tmp5_B.Gain2,                    /* 63: Signal */
  &f14tmp5_B.Product,                  /* 64: Signal */
  &f14tmp5_B.Sum1,                     /* 65: Signal */
  &f14tmp5_B.Gain3_a,                  /* 66: Signal */
  &f14tmp5_B.Gain4_p,                  /* 67: Signal */
  &f14tmp5_B.Gain5_h4,                 /* 68: Signal */
  &f14tmp5_B.Gain6_m,                  /* 69: Signal */
  &f14tmp5_B.Sum1_e,                   /* 70: Signal */
  &f14tmp5_B.Sum2_c,                   /* 71: Signal */
  &f14tmp5_B.TransferFcn1_a,           /* 72: Signal */
  &f14tmp5_B.TransferFcn2_b,           /* 73: Signal */
  &f14tmp5_B.Gain_e,                   /* 74: Signal */
  &f14tmp5_B.Gain2_j,                  /* 75: Signal */
  &f14tmp5_B.Gain3_l,                  /* 76: Signal */
  &f14tmp5_B.Sum_l,                    /* 77: Signal */
  &f14tmp5_B.Sum1_i,                   /* 78: Signal */
  &f14tmp5_B.Sum2_k,                   /* 79: Signal */
  &f14tmp5_B.AlphasensorLowpassFilter_e,/* 80: Signal */
  &f14tmp5_B.PitchRateLeadFilter_f,    /* 81: Signal */
  &f14tmp5_B.Proportionalplusintegralcompe_j,/* 82: Signal */
  &f14tmp5_B.StickPrefilter_h,         /* 83: Signal */
  &f14tmp5_B.Qgustmodel_c,             /* 84: Signal */
  &f14tmp5_B.Wgustmodel_j,             /* 85: Signal */
  &f14tmp5_B.Derivative_k,             /* 86: Signal */
  &f14tmp5_B.Derivative1_a,            /* 87: Signal */
  &f14tmp5_B.Gain1_c,                  /* 88: Signal */
  &f14tmp5_B.Gain2_l,                  /* 89: Signal */
  &f14tmp5_B.Product_a,                /* 90: Signal */
  &f14tmp5_B.Sum1_di,                  /* 91: Signal */
  &f14tmp5_B.Gain3_m,                  /* 92: Signal */
  &f14tmp5_B.Gain4_c,                  /* 93: Signal */
  &f14tmp5_B.Gain5_o,                  /* 94: Signal */
  &f14tmp5_B.Gain6_mc,                 /* 95: Signal */
  &f14tmp5_B.Sum1_dr,                  /* 96: Signal */
  &f14tmp5_B.Sum2_o,                   /* 97: Signal */
  &f14tmp5_B.TransferFcn1_g,           /* 98: Signal */
  &f14tmp5_B.TransferFcn2_l,           /* 99: Signal */
  &f14tmp5_B.Gain_h,                   /* 100: Signal */
  &f14tmp5_B.Gain2_p,                  /* 101: Signal */
  &f14tmp5_B.Gain3_gl,                 /* 102: Signal */
  &f14tmp5_B.Sum_o,                    /* 103: Signal */
  &f14tmp5_B.Sum1_o0,                  /* 104: Signal */
  &f14tmp5_B.Sum2_g,                   /* 105: Signal */
  &f14tmp5_B.AlphasensorLowpassFilter_h,/* 106: Signal */
  &f14tmp5_B.PitchRateLeadFilter_d,    /* 107: Signal */
  &f14tmp5_B.Proportionalplusintegralcompe_e,/* 108: Signal */
  &f14tmp5_B.StickPrefilter_i,         /* 109: Signal */
  &f14tmp5_B.Qgustmodel_j,             /* 110: Signal */
  &f14tmp5_B.Wgustmodel_e,             /* 111: Signal */
  &f14tmp5_B.Derivative_l,             /* 112: Signal */
  &f14tmp5_B.Derivative1_j,            /* 113: Signal */
  &f14tmp5_B.Gain1_g,                  /* 114: Signal */
  &f14tmp5_B.Gain2_g,                  /* 115: Signal */
  &f14tmp5_B.Product_b,                /* 116: Signal */
  &f14tmp5_B.Sum1_ev,                  /* 117: Signal */
  &f14tmp5_B.Gain3_lc,                 /* 118: Signal */
  &f14tmp5_B.Gain4_j,                  /* 119: Signal */
  &f14tmp5_B.Gain5_pj,                 /* 120: Signal */
  &f14tmp5_B.Gain6_f,                  /* 121: Signal */
  &f14tmp5_B.Sum1_f,                   /* 122: Signal */
  &f14tmp5_B.Sum2_cx,                  /* 123: Signal */
  &f14tmp5_B.TransferFcn1_k,           /* 124: Signal */
  &f14tmp5_B.TransferFcn2_j,           /* 125: Signal */
  &f14tmp5_B.Gain_df,                  /* 126: Signal */
  &f14tmp5_B.Gain2_nh,                 /* 127: Signal */
  &f14tmp5_B.Gain3_b,                  /* 128: Signal */
  &f14tmp5_B.Sum_k,                    /* 129: Signal */
  &f14tmp5_B.Sum1_om,                  /* 130: Signal */
  &f14tmp5_B.Sum2_gm,                  /* 131: Signal */
  &f14tmp5_B.AlphasensorLowpassFilter_j,/* 132: Signal */
  &f14tmp5_B.PitchRateLeadFilter_k,    /* 133: Signal */
  &f14tmp5_B.Proportionalplusintegralcompe_h,/* 134: Signal */
  &f14tmp5_B.StickPrefilter_e,         /* 135: Signal */
  &f14tmp5_B.Qgustmodel_g,             /* 136: Signal */
  &f14tmp5_B.Wgustmodel_h,             /* 137: Signal */
  &f14tmp5_B.Derivative_p,             /* 138: Signal */
  &f14tmp5_B.Derivative1_g,            /* 139: Signal */
  &f14tmp5_B.Gain1_ga,                 /* 140: Signal */
  &f14tmp5_B.Gain2_h,                  /* 141: Signal */
  &f14tmp5_B.Product_h,                /* 142: Signal */
  &f14tmp5_B.Sum1_o0i,                 /* 143: Signal */
  &f14tmp5_B.Gain3_as,                 /* 144: Signal */
  &f14tmp5_B.Gain4_l,                  /* 145: Signal */
  &f14tmp5_B.Gain5_i,                  /* 146: Signal */
  &f14tmp5_B.Gain6_b,                  /* 147: Signal */
  &f14tmp5_B.Sum1_g,                   /* 148: Signal */
  &f14tmp5_B.Sum2_oa,                  /* 149: Signal */
  &f14tmp5_B.TransferFcn1_i,           /* 150: Signal */
  &f14tmp5_B.TransferFcn2_o,           /* 151: Signal */
  &f14tmp5_B.Gain_i,                   /* 152: Signal */
  &f14tmp5_B.Gain2_fs,                 /* 153: Signal */
  &f14tmp5_B.Gain3_f,                  /* 154: Signal */
  &f14tmp5_B.Sum_m,                    /* 155: Signal */
  &f14tmp5_B.Sum1_m,                   /* 156: Signal */
  &f14tmp5_B.Sum2_f5,                  /* 157: Signal */
  &f14tmp5_B.AlphasensorLowpassFilter_n,/* 158: Signal */
  &f14tmp5_B.PitchRateLeadFilter_f1,   /* 159: Signal */
  &f14tmp5_B.Proportionalplusintegralcomp_eg,/* 160: Signal */
  &f14tmp5_B.StickPrefilter_o,         /* 161: Signal */
  &f14tmp5_B.Qgustmodel_n,             /* 162: Signal */
  &f14tmp5_B.Wgustmodel_o,             /* 163: Signal */
  &f14tmp5_B.Derivative_f,             /* 164: Signal */
  &f14tmp5_B.Derivative1_i,            /* 165: Signal */
  &f14tmp5_B.Gain1_om,                 /* 166: Signal */
  &f14tmp5_B.Gain2_oj,                 /* 167: Signal */
  &f14tmp5_B.Product_i,                /* 168: Signal */
  &f14tmp5_B.Sum1_a,                   /* 169: Signal */
  &f14tmp5_B.Output,                   /* 170: Signal */
  &f14tmp5_B.WhiteNoise,               /* 171: Signal */
  &f14tmp5_B.Output_e,                 /* 172: Signal */
  &f14tmp5_B.WhiteNoise_l,             /* 173: Signal */
  &f14tmp5_B.Output_c,                 /* 174: Signal */
  &f14tmp5_B.WhiteNoise_g,             /* 175: Signal */
  &f14tmp5_B.Output_k,                 /* 176: Signal */
  &f14tmp5_B.WhiteNoise_p,             /* 177: Signal */
  &f14tmp5_B.Output_a,                 /* 178: Signal */
  &f14tmp5_B.WhiteNoise_m,             /* 179: Signal */
  &f14tmp5_P.Gain_Gain,                /* 180: Block Parameter */
  &f14tmp5_P.Gain1_Gain_h,             /* 181: Block Parameter */
  &f14tmp5_P.Gain2_Gain_p,             /* 182: Block Parameter */
  &f14tmp5_P.Gain5_Gain,               /* 183: Block Parameter */
  &f14tmp5_P.Pilot_Amplitude,          /* 184: Block Parameter */
  &f14tmp5_P.Pilot_Frequency,          /* 185: Block Parameter */
  &f14tmp5_P.ActuatorModel_A,          /* 186: Block Parameter */
  &f14tmp5_P.ActuatorModel_C,          /* 187: Block Parameter */
  &f14tmp5_P.Gain_Gain_l,              /* 188: Block Parameter */
  &f14tmp5_P.Gain1_Gain_p,             /* 189: Block Parameter */
  &f14tmp5_P.Gain2_Gain_h,             /* 190: Block Parameter */
  &f14tmp5_P.Gain5_Gain_o,             /* 191: Block Parameter */
  &f14tmp5_P.Pilot_Amplitude_n,        /* 192: Block Parameter */
  &f14tmp5_P.Pilot_Frequency_d,        /* 193: Block Parameter */
  &f14tmp5_P.ActuatorModel_A_j,        /* 194: Block Parameter */
  &f14tmp5_P.ActuatorModel_C_f,        /* 195: Block Parameter */
  &f14tmp5_P.Gain_Gain_d,              /* 196: Block Parameter */
  &f14tmp5_P.Gain1_Gain_f,             /* 197: Block Parameter */
  &f14tmp5_P.Gain2_Gain_g,             /* 198: Block Parameter */
  &f14tmp5_P.Gain5_Gain_c,             /* 199: Block Parameter */
  &f14tmp5_P.Pilot_Amplitude_e,        /* 200: Block Parameter */
  &f14tmp5_P.Pilot_Frequency_k,        /* 201: Block Parameter */
  &f14tmp5_P.ActuatorModel_A_g,        /* 202: Block Parameter */
  &f14tmp5_P.ActuatorModel_C_b,        /* 203: Block Parameter */
  &f14tmp5_P.Gain_Gain_h,              /* 204: Block Parameter */
  &f14tmp5_P.Gain1_Gain_d,             /* 205: Block Parameter */
  &f14tmp5_P.Gain2_Gain_m,             /* 206: Block Parameter */
  &f14tmp5_P.Gain5_Gain_j0,            /* 207: Block Parameter */
  &f14tmp5_P.Pilot_Amplitude_o,        /* 208: Block Parameter */
  &f14tmp5_P.Pilot_Frequency_i,        /* 209: Block Parameter */
  &f14tmp5_P.ActuatorModel_A_p,        /* 210: Block Parameter */
  &f14tmp5_P.ActuatorModel_C_l,        /* 211: Block Parameter */
  &f14tmp5_P.Gain_Gain_c,              /* 212: Block Parameter */
  &f14tmp5_P.Gain1_Gain_a,             /* 213: Block Parameter */
  &f14tmp5_P.Gain2_Gain_l,             /* 214: Block Parameter */
  &f14tmp5_P.Gain5_Gain_f,             /* 215: Block Parameter */
  &f14tmp5_P.Pilot_Amplitude_h,        /* 216: Block Parameter */
  &f14tmp5_P.Pilot_Frequency_a,        /* 217: Block Parameter */
  &f14tmp5_P.ActuatorModel_A_gl,       /* 218: Block Parameter */
  &f14tmp5_P.ActuatorModel_C_a,        /* 219: Block Parameter */
  &f14tmp5_P.Gain3_Gain,               /* 220: Block Parameter */
  &f14tmp5_P.Gain4_Gain,               /* 221: Block Parameter */
  &f14tmp5_P.Gain5_Gain_j,             /* 222: Block Parameter */
  &f14tmp5_P.Gain6_Gain,               /* 223: Block Parameter */
  &f14tmp5_P.TransferFcn1_A,           /* 224: Block Parameter */
  &f14tmp5_P.TransferFcn1_C,           /* 225: Block Parameter */
  &f14tmp5_P.TransferFcn2_A,           /* 226: Block Parameter */
  &f14tmp5_P.TransferFcn2_C,           /* 227: Block Parameter */
  &f14tmp5_P.Gain_Gain_k,              /* 228: Block Parameter */
  &f14tmp5_P.Gain2_Gain_k,             /* 229: Block Parameter */
  &f14tmp5_P.Gain3_Gain_i,             /* 230: Block Parameter */
  &f14tmp5_P.AlphasensorLowpassFilter_A,/* 231: Block Parameter */
  &f14tmp5_P.AlphasensorLowpassFilter_C,/* 232: Block Parameter */
  &f14tmp5_P.PitchRateLeadFilter_A,    /* 233: Block Parameter */
  &f14tmp5_P.PitchRateLeadFilter_C,    /* 234: Block Parameter */
  &f14tmp5_P.PitchRateLeadFilter_D,    /* 235: Block Parameter */
  &f14tmp5_P.Proportionalplusintegralcompens,/* 236: Block Parameter */
  &f14tmp5_P.Proportionalplusintegralcompe_i,/* 237: Block Parameter */
  &f14tmp5_P.StickPrefilter_A,         /* 238: Block Parameter */
  &f14tmp5_P.StickPrefilter_C,         /* 239: Block Parameter */
  &f14tmp5_P.Qgustmodel_A,             /* 240: Block Parameter */
  &f14tmp5_P.Qgustmodel_C,             /* 241: Block Parameter */
  &f14tmp5_P.Qgustmodel_D,             /* 242: Block Parameter */
  &f14tmp5_P.Wgustmodel_A[0],          /* 243: Block Parameter */
  &f14tmp5_P.Wgustmodel_C[0],          /* 244: Block Parameter */
  &f14tmp5_P.Constant_Value,           /* 245: Block Parameter */
  &f14tmp5_P.Gain1_Gain,               /* 246: Block Parameter */
  &f14tmp5_P.Gain2_Gain,               /* 247: Block Parameter */
  &f14tmp5_P.Gain3_Gain_k,             /* 248: Block Parameter */
  &f14tmp5_P.Gain4_Gain_f,             /* 249: Block Parameter */
  &f14tmp5_P.Gain5_Gain_g,             /* 250: Block Parameter */
  &f14tmp5_P.Gain6_Gain_b,             /* 251: Block Parameter */
  &f14tmp5_P.TransferFcn1_A_n,         /* 252: Block Parameter */
  &f14tmp5_P.TransferFcn1_C_g,         /* 253: Block Parameter */
  &f14tmp5_P.TransferFcn2_A_j,         /* 254: Block Parameter */
  &f14tmp5_P.TransferFcn2_C_k,         /* 255: Block Parameter */
  &f14tmp5_P.Gain_Gain_a,              /* 256: Block Parameter */
  &f14tmp5_P.Gain2_Gain_et,            /* 257: Block Parameter */
  &f14tmp5_P.Gain3_Gain_b,             /* 258: Block Parameter */
  &f14tmp5_P.AlphasensorLowpassFilter_A_d,/* 259: Block Parameter */
  &f14tmp5_P.AlphasensorLowpassFilter_C_g,/* 260: Block Parameter */
  &f14tmp5_P.PitchRateLeadFilter_A_c,  /* 261: Block Parameter */
  &f14tmp5_P.PitchRateLeadFilter_C_l,  /* 262: Block Parameter */
  &f14tmp5_P.PitchRateLeadFilter_D_f,  /* 263: Block Parameter */
  &f14tmp5_P.Proportionalplusintegralcompe_d,/* 264: Block Parameter */
  &f14tmp5_P.Proportionalplusintegralcomp_mx,/* 265: Block Parameter */
  &f14tmp5_P.StickPrefilter_A_c,       /* 266: Block Parameter */
  &f14tmp5_P.StickPrefilter_C_p,       /* 267: Block Parameter */
  &f14tmp5_P.Qgustmodel_A_e,           /* 268: Block Parameter */
  &f14tmp5_P.Qgustmodel_C_p,           /* 269: Block Parameter */
  &f14tmp5_P.Qgustmodel_D_c,           /* 270: Block Parameter */
  &f14tmp5_P.Wgustmodel_A_l[0],        /* 271: Block Parameter */
  &f14tmp5_P.Wgustmodel_C_a[0],        /* 272: Block Parameter */
  &f14tmp5_P.Constant_Value_m,         /* 273: Block Parameter */
  &f14tmp5_P.Gain1_Gain_n,             /* 274: Block Parameter */
  &f14tmp5_P.Gain2_Gain_e,             /* 275: Block Parameter */
  &f14tmp5_P.Gain3_Gain_c,             /* 276: Block Parameter */
  &f14tmp5_P.Gain4_Gain_j,             /* 277: Block Parameter */
  &f14tmp5_P.Gain5_Gain_p,             /* 278: Block Parameter */
  &f14tmp5_P.Gain6_Gain_f,             /* 279: Block Parameter */
  &f14tmp5_P.TransferFcn1_A_d,         /* 280: Block Parameter */
  &f14tmp5_P.TransferFcn1_C_gb,        /* 281: Block Parameter */
  &f14tmp5_P.TransferFcn2_A_l,         /* 282: Block Parameter */
  &f14tmp5_P.TransferFcn2_C_a,         /* 283: Block Parameter */
  &f14tmp5_P.Gain_Gain_j,              /* 284: Block Parameter */
  &f14tmp5_P.Gain2_Gain_eh,            /* 285: Block Parameter */
  &f14tmp5_P.Gain3_Gain_m,             /* 286: Block Parameter */
  &f14tmp5_P.AlphasensorLowpassFilter_A_c,/* 287: Block Parameter */
  &f14tmp5_P.AlphasensorLowpassFilter_C_gf,/* 288: Block Parameter */
  &f14tmp5_P.PitchRateLeadFilter_A_i,  /* 289: Block Parameter */
  &f14tmp5_P.PitchRateLeadFilter_C_k,  /* 290: Block Parameter */
  &f14tmp5_P.PitchRateLeadFilter_D_ft, /* 291: Block Parameter */
  &f14tmp5_P.Proportionalplusintegralcompe_h,/* 292: Block Parameter */
  &f14tmp5_P.Proportionalplusintegralcompe_l,/* 293: Block Parameter */
  &f14tmp5_P.StickPrefilter_A_e,       /* 294: Block Parameter */
  &f14tmp5_P.StickPrefilter_C_j,       /* 295: Block Parameter */
  &f14tmp5_P.Qgustmodel_A_b,           /* 296: Block Parameter */
  &f14tmp5_P.Qgustmodel_C_j,           /* 297: Block Parameter */
  &f14tmp5_P.Qgustmodel_D_i,           /* 298: Block Parameter */
  &f14tmp5_P.Wgustmodel_A_m[0],        /* 299: Block Parameter */
  &f14tmp5_P.Wgustmodel_C_m[0],        /* 300: Block Parameter */
  &f14tmp5_P.Constant_Value_b,         /* 301: Block Parameter */
  &f14tmp5_P.Gain1_Gain_e,             /* 302: Block Parameter */
  &f14tmp5_P.Gain2_Gain_h5,            /* 303: Block Parameter */
  &f14tmp5_P.Gain3_Gain_p,             /* 304: Block Parameter */
  &f14tmp5_P.Gain4_Gain_c,             /* 305: Block Parameter */
  &f14tmp5_P.Gain5_Gain_j0q,           /* 306: Block Parameter */
  &f14tmp5_P.Gain6_Gain_j,             /* 307: Block Parameter */
  &f14tmp5_P.TransferFcn1_A_a,         /* 308: Block Parameter */
  &f14tmp5_P.TransferFcn1_C_l,         /* 309: Block Parameter */
  &f14tmp5_P.TransferFcn2_A_jz,        /* 310: Block Parameter */
  &f14tmp5_P.TransferFcn2_C_l,         /* 311: Block Parameter */
  &f14tmp5_P.Gain_Gain_f,              /* 312: Block Parameter */
  &f14tmp5_P.Gain2_Gain_b,             /* 313: Block Parameter */
  &f14tmp5_P.Gain3_Gain_a,             /* 314: Block Parameter */
  &f14tmp5_P.AlphasensorLowpassFilter_A_p,/* 315: Block Parameter */
  &f14tmp5_P.AlphasensorLowpassFilter_C_m,/* 316: Block Parameter */
  &f14tmp5_P.PitchRateLeadFilter_A_p,  /* 317: Block Parameter */
  &f14tmp5_P.PitchRateLeadFilter_C_b,  /* 318: Block Parameter */
  &f14tmp5_P.PitchRateLeadFilter_D_b,  /* 319: Block Parameter */
  &f14tmp5_P.Proportionalplusintegralcomp_kg,/* 320: Block Parameter */
  &f14tmp5_P.Proportionalplusintegralcompe_j,/* 321: Block Parameter */
  &f14tmp5_P.StickPrefilter_A_d,       /* 322: Block Parameter */
  &f14tmp5_P.StickPrefilter_C_h,       /* 323: Block Parameter */
  &f14tmp5_P.Qgustmodel_A_g,           /* 324: Block Parameter */
  &f14tmp5_P.Qgustmodel_C_a,           /* 325: Block Parameter */
  &f14tmp5_P.Qgustmodel_D_a,           /* 326: Block Parameter */
  &f14tmp5_P.Wgustmodel_A_b[0],        /* 327: Block Parameter */
  &f14tmp5_P.Wgustmodel_C_g[0],        /* 328: Block Parameter */
  &f14tmp5_P.Constant_Value_f,         /* 329: Block Parameter */
  &f14tmp5_P.Gain1_Gain_fm,            /* 330: Block Parameter */
  &f14tmp5_P.Gain2_Gain_kz,            /* 331: Block Parameter */
  &f14tmp5_P.Gain3_Gain_ai,            /* 332: Block Parameter */
  &f14tmp5_P.Gain4_Gain_d,             /* 333: Block Parameter */
  &f14tmp5_P.Gain5_Gain_n,             /* 334: Block Parameter */
  &f14tmp5_P.Gain6_Gain_n,             /* 335: Block Parameter */
  &f14tmp5_P.TransferFcn1_A_o,         /* 336: Block Parameter */
  &f14tmp5_P.TransferFcn1_C_j,         /* 337: Block Parameter */
  &f14tmp5_P.TransferFcn2_A_c,         /* 338: Block Parameter */
  &f14tmp5_P.TransferFcn2_C_e,         /* 339: Block Parameter */
  &f14tmp5_P.Gain_Gain_o,              /* 340: Block Parameter */
  &f14tmp5_P.Gain2_Gain_n,             /* 341: Block Parameter */
  &f14tmp5_P.Gain3_Gain_h,             /* 342: Block Parameter */
  &f14tmp5_P.AlphasensorLowpassFilter_A_a,/* 343: Block Parameter */
  &f14tmp5_P.AlphasensorLowpassFilter_C_e,/* 344: Block Parameter */
  &f14tmp5_P.PitchRateLeadFilter_A_m,  /* 345: Block Parameter */
  &f14tmp5_P.PitchRateLeadFilter_C_a,  /* 346: Block Parameter */
  &f14tmp5_P.PitchRateLeadFilter_D_a,  /* 347: Block Parameter */
  &f14tmp5_P.Proportionalplusintegralcomp_mw,/* 348: Block Parameter */
  &f14tmp5_P.Proportionalplusintegralcomp_jp,/* 349: Block Parameter */
  &f14tmp5_P.StickPrefilter_A_ee,      /* 350: Block Parameter */
  &f14tmp5_P.StickPrefilter_C_b,       /* 351: Block Parameter */
  &f14tmp5_P.Qgustmodel_A_gl,          /* 352: Block Parameter */
  &f14tmp5_P.Qgustmodel_C_c,           /* 353: Block Parameter */
  &f14tmp5_P.Qgustmodel_D_l,           /* 354: Block Parameter */
  &f14tmp5_P.Wgustmodel_A_lv[0],       /* 355: Block Parameter */
  &f14tmp5_P.Wgustmodel_C_p[0],        /* 356: Block Parameter */
  &f14tmp5_P.Constant_Value_p,         /* 357: Block Parameter */
  &f14tmp5_P.Gain1_Gain_m,             /* 358: Block Parameter */
  &f14tmp5_P.Gain2_Gain_d,             /* 359: Block Parameter */
  &f14tmp5_P.Output_Gain,              /* 360: Block Parameter */
  &f14tmp5_P.WhiteNoise_Mean,          /* 361: Block Parameter */
  &f14tmp5_P.WhiteNoise_StdDev,        /* 362: Block Parameter */
  &f14tmp5_P.WhiteNoise_Seed,          /* 363: Block Parameter */
  &f14tmp5_P.Output_Gain_l,            /* 364: Block Parameter */
  &f14tmp5_P.WhiteNoise_Mean_j,        /* 365: Block Parameter */
  &f14tmp5_P.WhiteNoise_StdDev_n,      /* 366: Block Parameter */
  &f14tmp5_P.WhiteNoise_Seed_i,        /* 367: Block Parameter */
  &f14tmp5_P.Output_Gain_m,            /* 368: Block Parameter */
  &f14tmp5_P.WhiteNoise_Mean_k,        /* 369: Block Parameter */
  &f14tmp5_P.WhiteNoise_StdDev_g,      /* 370: Block Parameter */
  &f14tmp5_P.WhiteNoise_Seed_j,        /* 371: Block Parameter */
  &f14tmp5_P.Output_Gain_p,            /* 372: Block Parameter */
  &f14tmp5_P.WhiteNoise_Mean_n,        /* 373: Block Parameter */
  &f14tmp5_P.WhiteNoise_StdDev_f,      /* 374: Block Parameter */
  &f14tmp5_P.WhiteNoise_Seed_c,        /* 375: Block Parameter */
  &f14tmp5_P.Output_Gain_pk,           /* 376: Block Parameter */
  &f14tmp5_P.WhiteNoise_Mean_b,        /* 377: Block Parameter */
  &f14tmp5_P.WhiteNoise_StdDev_k,      /* 378: Block Parameter */
  &f14tmp5_P.WhiteNoise_Seed_g         /* 379: Block Parameter */
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
  { rtBlockSignals, 180 },

  { rtBlockParameters, 200,
    rtModelParameters, 0 },

  { NULL, 0 },

  { rtDataTypeMap, rtDimensionMap, rtFixPtMap,
    rtElementMap, rtSampleTimeMap, rtDimensionArray },
  "float", NULL
};

/* Cache pointers into DataMapInfo substructure of RTModel */
void f14tmp5_InitializeDataMapInfo(rtModel_f14tmp5 *f14tmp5_rtM
  )
{
  /* Set C-API version */
  rtwCAPI_SetVersion(f14tmp5_rtM->DataMapInfo.mmi, 1);

  /* Cache static C-API data into the Real-time Model Data structure */
  rtwCAPI_SetStaticMap(f14tmp5_rtM->DataMapInfo.mmi, &mmiStatic);

  /* Cache static C-API logging data into the Real-time Model Data structure */
  rtwCAPI_SetLoggingStaticMap(f14tmp5_rtM->DataMapInfo.mmi, NULL);

  /* Cache C-API Data Addresses into the Real-Time Model Data structure */
  rtwCAPI_SetDataAddressMap(f14tmp5_rtM->DataMapInfo.mmi, rtDataAddrMap);

  /* Cache C-API Data Run-Time Dimension Buffer Addresses into the Real-Time Model Data structure */
  rtwCAPI_SetVarDimsAddressMap(f14tmp5_rtM->DataMapInfo.mmi, rtVarDimsAddrMap);

  /* Cache the instance C-API logging pointer */
  rtwCAPI_SetInstanceLoggingInfo(f14tmp5_rtM->DataMapInfo.mmi, NULL);

  /* Set Reference to submodels */
  rtwCAPI_SetChildMMIArray(f14tmp5_rtM->DataMapInfo.mmi, NULL);
  rtwCAPI_SetChildMMIArrayLen(f14tmp5_rtM->DataMapInfo.mmi, 0);
}

/* EOF: f14tmp5_capi.c */
